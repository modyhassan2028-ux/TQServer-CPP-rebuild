// CQCrossServer shell (v1 rebuild): listens for game-server connections,
// frames messages, feeds the routing kernel, runs the OnTimer heartbeat
// sweep. Mirrors crossshell.cpp from the decompiled binary.
#include "CrossKernel.h"
#include "CrossProtocol.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

static std::atomic<bool> g_bRunning{ false };

// minimal ini reader (System section of crossshell.ini)
static std::string ReadIni(const std::string& strPath, const std::string& strKey,
                           const std::string& strDefault) {
    std::ifstream f(strPath);
    std::string line;
    while (std::getline(f, line)) {
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq), val = line.substr(eq + 1);
        // trim
        auto trim = [](std::string& s) {
            size_t a = s.find_first_not_of(" \t\r");
            size_t b = s.find_last_not_of(" \t\r");
            s = a == std::string::npos ? "" : s.substr(a, b - a + 1);
        };
        trim(key); trim(val);
        if (key == strKey) return val;
    }
    return strDefault;
}

// per-connection state
struct Conn {
    SOCKET sock;
    cross::FrameDecoder decoder;
    std::vector<uint8_t> inBuf;
};

static void SendRaw(SOCKET sock, const std::vector<uint8_t>& pkt) {
    if (sock == INVALID_SOCKET) return;
    int n = ::send(sock, (const char*)pkt.data(), (int)pkt.size(), 0);
    (void)n;
}

// shared monotonic clock (ms) for the heartbeat rule - one epoch for the
// heartbeat dispatch and the OnTimer sweep (mixing clocks would drop live
// servers as silent)
static uint64_t NowMs() {
    return (uint64_t)std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

int main() {
    printf("[CROSS] TQServer-CPP CQCrossServer (v1 hub) starting\n");

    uint16_t usPort = (uint16_t)strtoul(
        ReadIni("data/crossshell.ini", "CROSS_PORT", "5820").c_str(), nullptr, 10);
    std::string strName = ReadIni("data/crossshell.ini", "CROSS_SERVER_NAME", "CrossHub");
    printf("[CROSS] name '%s', listening on %u\n", strName.c_str(), usPort);

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("[CROSS] WSAStartup failed\n");
        return 1;
    }

    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == INVALID_SOCKET) {
        printf("[CROSS] socket failed: %d\n", WSAGetLastError());
        return 1;
    }
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(usPort);
    if (bind(listener, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR ||
        listen(listener, 16) == SOCKET_ERROR) {
        printf("[CROSS] bind/listen failed: %d\n", WSAGetLastError());
        return 1;
    }

    // delivery callback: kernel -> socket. socket ids are stored as
    // uint64_t for kernel purity; here they are the SOCKET handles.
    cross::CCrossServerKernel kernel(
        [](uint64_t sock, const std::vector<uint8_t>& pkt) {
            SendRaw((SOCKET)sock, pkt);
        },
        [](const std::string& line) { printf("[CROSS] %s\n", line.c_str()); });

    g_bRunning.store(true);

    // OnTimer thread: heartbeat sweep every 10s (same steady_clock epoch
    // the heartbeat dispatch uses - mixing clocks would drop live servers)
    std::thread timer([&kernel]() {
        while (g_bRunning.load()) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            if (!g_bRunning.load()) break;
            kernel.OnDropSilent(NowMs());
        }
    });

    printf("[CROSS] ready - waiting for game servers\n");
    while (g_bRunning.load()) {
        SOCKET client = accept(listener, nullptr, nullptr);
        if (client == INVALID_SOCKET) break;
        printf("[CROSS] OS connection accepted (socket %llu)\n",
               (unsigned long long)client);
        std::thread([client, &kernel]() {
            Conn conn;
            conn.sock = client;
            uint8_t buf[4096];
            while (g_bRunning.load()) {
                int n = recv(client, (char*)buf, sizeof(buf), 0);
                if (n <= 0) break;
                uint16_t usType;
                std::vector<uint8_t> payload;
                {
                    bool bFresh = true;
                    for (;;) {
                        bool ok = bFresh ? conn.decoder.Feed(buf, (uint32_t)n, usType, payload)
                                         : conn.decoder.Drain(usType, payload);
                        if (!ok) break;
                        bFresh = false;
                        // dispatch to the kernel (routing rules live there)
                        switch (usType) {
                        case cross::MsgType_Hello: {
                            if (payload.size() >= sizeof(cross::HelloData)) {
                                cross::HelloData h;
                                std::memcpy(&h, payload.data(), sizeof(h));
                                kernel.OnHello((uint64_t)client, h);
                            }
                            break;
                        }
                        case cross::MsgType_Talk: {
                            if (payload.size() >= sizeof(cross::TalkData)) {
                                cross::TalkData t;
                                std::memcpy(&t, payload.data(), sizeof(t));
                                kernel.OnTalk((uint64_t)client, t);
                            }
                            break;
                        }
                        case cross::MsgType_Roster: {
                            if (payload.size() >= sizeof(cross::RosterData)) {
                                cross::RosterData r;
                                std::memcpy(&r, payload.data(), sizeof(r));
                                kernel.OnRoster((uint64_t)client, r);
                            }
                            break;
                        }
                        case cross::MsgType_Heartbeat: {
                            if (payload.size() >= sizeof(cross::HeartbeatData)) {
                                cross::HeartbeatData b;
                                std::memcpy(&b, payload.data(), sizeof(b));
                                kernel.OnHeartbeat((uint64_t)client, b, NowMs());
                            }
                            break;
                        }
                        case cross::MsgType_WhoReq:
                            kernel.OnWhoReq((uint64_t)client);
                            break;
                        default:
                            break; // unknown cross message: ignore
                        }
                    }
                }
            }
            kernel.OnDisconnect((uint64_t)client);
            closesocket(client);
            printf("[CROSS] OS connection closed (socket %llu)\n",
                   (unsigned long long)client);
        }).detach();
    }

    g_bRunning.store(false);
    timer.join();
    closesocket(listener);
    WSACleanup();
    printf("[CROSS] shut down\n");
    return 0;
}

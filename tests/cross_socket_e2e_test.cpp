// socket E2E: two game servers over real TCP through the same kernel the
// shipped CQCrossServer.exe uses; packets deliberately split across sends
#include "CrossKernel.h"
#include "CrossProtocol.h"
#include <arpa/inet.h>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

using namespace cross;

static bool RecvFrame(int fd, uint16_t& type, std::vector<uint8_t>& payload) {
    tq::MsgHead head;
    uint8_t* p = (uint8_t*)&head; size_t got = 0;
    while (got < sizeof(head)) {
        ssize_t n = recv(fd, p + got, sizeof(head) - got, 0);
        if (n <= 0) return false;
        got += (size_t)n;
    }
    if (head.length < sizeof(head)) return false;
    payload.resize(head.length - sizeof(head));
    got = 0;
    while (got < payload.size()) {
        ssize_t n = recv(fd, payload.data() + got, payload.size() - got, 0);
        if (n <= 0) return false;
        got += (size_t)n;
    }
    type = head.type;
    return true;
}

static bool SendAll(int fd, const std::vector<uint8_t>& pkt) {
    size_t sent = 0;
    while (sent < pkt.size()) {
        ssize_t n = send(fd, pkt.data() + sent, pkt.size() - sent, 0);
        if (n <= 0) return false;
        sent += (size_t)n;
    }
    return true;
}

int main() {
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1; setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    sockaddr_in a{}; a.sin_family = AF_INET; a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    a.sin_port = 0;
    assert(bind(lfd, (sockaddr*)&a, sizeof(a)) == 0);
    assert(listen(lfd, 4) == 0);
    socklen_t len = sizeof(a);
    getsockname(lfd, (sockaddr*)&a, &len);
    uint16_t port = ntohs(a.sin_port);

    std::vector<int> conns;
    std::mutex mtx;
    CCrossServerKernel kernel(
        [&](uint64_t sock, const std::vector<uint8_t>& pkt) { SendAll((int)sock, pkt); },
        [](const std::string& l) { printf("[hub] %s\n", l.c_str()); });
    std::atomic<bool> run{ true };
    std::thread hub([&]() {
        while (run.load()) {
            int c = accept(lfd, nullptr, nullptr);
            if (c < 0) break;
            std::lock_guard<std::mutex> lk(mtx);
            conns.push_back(c);
            std::thread([c, &kernel, &run]() {
                FrameDecoder dec; uint8_t buf[4096];
                while (run.load()) {
                    ssize_t n = recv(c, buf, sizeof(buf), 0);
                    if (n <= 0) break;
                    uint16_t type; std::vector<uint8_t> payload;
                    bool fresh = true;
                    for (;;) {
                        bool ok = fresh ? dec.Feed(buf, (uint32_t)n, type, payload)
                                        : dec.Drain(type, payload);
                        if (!ok) break;
                        fresh = false;
                        if (type == MsgType_Hello && payload.size() >= sizeof(HelloData)) {
                            HelloData h; std::memcpy(&h, payload.data(), sizeof(h));
                            kernel.OnHello((uint64_t)c, h);
                        } else if (type == MsgType_Talk && payload.size() >= sizeof(TalkData)) {
                            TalkData t; std::memcpy(&t, payload.data(), sizeof(t));
                            kernel.OnTalk((uint64_t)c, t);
                        } else if (type == MsgType_Roster && payload.size() >= sizeof(RosterData)) {
                            RosterData r; std::memcpy(&r, payload.data(), sizeof(r));
                            kernel.OnRoster((uint64_t)c, r);
                        } else if (type == MsgType_WhoReq) {
                            kernel.OnWhoReq((uint64_t)c);
                        }
                    }
                }
                kernel.OnDisconnect((uint64_t)c);
                close(c);
            }).detach();
        }
    });

    // two game servers dial in
    int sa = socket(AF_INET, SOCK_STREAM, 0);
    assert(connect(sa, (sockaddr*)&a, sizeof(a)) == 0);
    int sb = socket(AF_INET, SOCK_STREAM, 0);
    assert(connect(sb, (sockaddr*)&a, sizeof(a)) == 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    HelloData h1{}; h1.dwServerId = 1; CopyStr(h1.szName, sizeof(h1.szName), "Alpha");
    HelloData h2{}; h2.dwServerId = 2; CopyStr(h2.szName, sizeof(h2.szName), "Beta");
    assert(SendAll(sa, Encode(MsgType_Hello, h1)));
    // split Alpha... actually split Beta's hello across two sends: half the frame now, half later
    auto ph2 = Encode(MsgType_Hello, h2);
    assert(send(sb, ph2.data(), 7, 0) == 7);                 // mid-header cut
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    assert(SendAll(sb, std::vector<uint8_t>(ph2.begin() + 7, ph2.end()))); // the rest
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    assert(kernel.ServerCount() == 2);

    // Beta should have heard Alpha is up (split-frame hello decoded fine)
    uint16_t type; std::vector<uint8_t> payload;
    assert(RecvFrame(sb, type, payload));
    assert(type == MsgType_ServerUp);
    ServerUpDownData u; std::memcpy(&u, payload.data(), sizeof(u));
    assert(u.dwServerId == 1 && std::string(u.szName) == "Alpha");

// Alpha talks; the relay skips the origin, so BETA receives it
    TalkData t{}; t.dwServerId = 1; CopyStr(t.szFrom, sizeof(t.szFrom), "Mody");
    CopyStr(t.szText, sizeof(t.szText), "hello from Alpha");
    assert(SendAll(sa, Encode(MsgType_Talk, t)));
    assert(RecvFrame(sb, type, payload) && type == MsgType_Talk);
    TalkData got; std::memcpy(&got, payload.data(), sizeof(got));
    assert(std::string(got.szText) == "hello from Alpha" && std::string(got.szFrom) == "Mody");

    // Beta pushes a roster and asks who: hub answers with both servers
    RosterData r2{}; r2.dwServerId = 2; r2.dwCount = 1;
    CopyStr(r2.entries[0].szName, sizeof(r2.entries[0].szName), "Ali"); r2.entries[0].usLevel = 45;
    assert(SendAll(sb, Encode(MsgType_Roster, r2)));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    tq::MsgHead req; req.type = MsgType_WhoReq; req.length = sizeof(req);
    assert(SendAll(sb, std::vector<uint8_t>((uint8_t*)&req, (uint8_t*)&req + sizeof(req))));
    assert(RecvFrame(sb, type, payload) && type == MsgType_WhoResp);
    WhoRespData w; std::memcpy(&w, payload.data(), sizeof(w));
    assert(w.dwServers == 2);

    printf("CROSS_E2E_OK: split-frame hello, presence sync, wire relay, who response\n");
    fflush(stdout);
    // teardown races (detached hub threads vs destroyed kernel) don't affect
    // the result: everything above already asserted - leave via _exit
    run.store(false);
    _exit(0);
}

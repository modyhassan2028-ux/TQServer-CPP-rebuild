#include "NetCore.h"
#include "MsgTalk.h"
#include "MsgConnect.h"
#include "MsgAction.h"
#include "MsgInteract.h"
#include "UserManager.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

static const uint16_t MAX_PACKET = 8192;

CNetClient::CNetClient(uint64_t ullSocket, uint32_t dwSessionId)
    : m_ullSocket(ullSocket), m_dwSessionId(dwSessionId) {}

CNetClient::~CNetClient() {
    if (m_ullSocket != ~0ull) closesocket(static_cast<SOCKET>(m_ullSocket));
}

bool CNetClient::Send(const void* pData, uint16_t usLen) {
    if (!m_bAlive.load()) return false;
    std::lock_guard<std::mutex> lock(m_mutexSend);
    int nSent = 0;
    const char* p = static_cast<const char*>(pData);
    while (nSent < usLen) {
        int n = send(static_cast<SOCKET>(m_ullSocket), p + nSent, usLen - nSent, 0);
        if (n <= 0) { m_bAlive.store(false); return false; }
        nSent += n;
    }
    return true;
}

void CNetClient::Kick() {
    m_bAlive.store(false);
    if (m_ullSocket != ~0ull) {
        shutdown(static_cast<SOCKET>(m_ullSocket), SD_BOTH);
        closesocket(static_cast<SOCKET>(m_ullSocket));
        m_ullSocket = ~0ull;
    }
}

void CNetClient::RecvLoop() {
    uint8_t buf[4096];
    while (m_bAlive.load()) {
        int n = recv(static_cast<SOCKET>(m_ullSocket), reinterpret_cast<char*>(buf), sizeof(buf), 0);
        if (n <= 0) break;
        m_vecInBuf.insert(m_vecInBuf.end(), buf, buf + n);

        // frame packets: [uint16 length][uint16 type][payload], length includes header
        while (m_vecInBuf.size() >= sizeof(tq::MsgHead)) {
            tq::MsgHead head;
            std::memcpy(&head, m_vecInBuf.data(), sizeof(head));
            if (head.length < sizeof(tq::MsgHead) || head.length > MAX_PACKET) {
                printf("[NET] Session %u: bad frame (len=%u type=%u), kicking.\n",
                       m_dwSessionId, head.length, head.type);
                Kick();
                return;
            }
            if (m_vecInBuf.size() < head.length) break; // wait for more data

            Dispatch(head, m_vecInBuf.data() + sizeof(head), head.length - sizeof(head));
            m_vecInBuf.erase(m_vecInBuf.begin(), m_vecInBuf.begin() + head.length);
        }
    }
    m_bAlive.store(false);
}

void CNetClient::Dispatch(tq::MsgHead head, const uint8_t* pPayload, uint16_t usPayloadLen) {
    (void)usPayloadLen;
    switch (head.type) {
    case 1001: { // MsgConnect - login handshake
        CMsgConnect login;
        login.Clear();
        login.AppendRaw(reinterpret_cast<const uint8_t*>(&head), sizeof(head));
        login.AppendRaw(pPayload, static_cast<uint16_t>(head.length - sizeof(head)));
        login.Process(m_dwSessionId, this);
        break;
    }
    case 1004: { // MsgTalk - chat channels
        CMsgTalk msg;
        msg.Clear();
        msg.AppendRaw(reinterpret_cast<const uint8_t*>(&head), sizeof(head));
        msg.AppendRaw(pPayload, static_cast<uint16_t>(head.length - sizeof(head)));
        auto pUser = CUserManager::Instance().GetUser(m_dwSessionId);
        if (pUser) {
            msg.Process(m_dwSessionId);
        } else {
            CMsgTalk reply;
            if (reply.Create("SYSTEM", "", "Not logged in. Send MsgConnect (1001) first.", CMsgTalk::Channel_Talk))
                Send(reply.GetBuf(), reply.GetSize());
        }
        break;
    }
    case 1010: { // MsgAction - movement / map change
        CMsgAction msg;
        msg.Clear();
        msg.AppendRaw(reinterpret_cast<const uint8_t*>(&head), sizeof(head));
        msg.AppendRaw(pPayload, static_cast<uint16_t>(head.length - sizeof(head)));
        msg.Process(m_dwSessionId);
        break;
    }
    case 1022: { // MsgInteract - attack / interaction
        CMsgInteract msg;
        msg.Clear();
        msg.AppendRaw(reinterpret_cast<const uint8_t*>(&head), sizeof(head));
        msg.AppendRaw(pPayload, static_cast<uint16_t>(head.length - sizeof(head)));
        msg.Process(m_dwSessionId);
        break;
    }
    default:
        printf("[NET] Session %u: packet type=%u len=%u (no handler yet)\n",
               m_dwSessionId, head.type, head.length);
        break;
    }
}

// ---- CNetCore ----

CNetCore& CNetCore::Instance() {
    static CNetCore s_instance;
    return s_instance;
}

bool CNetCore::Start(uint16_t usPort) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("[NET] WSAStartup failed.\n");
        return false;
    }

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock == INVALID_SOCKET) {
        printf("[NET] socket() failed: %d\n", WSAGetLastError());
        return false;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(usPort);

    int opt = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&opt), sizeof(opt));

    if (bind(listenSock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        printf("[NET] bind(%u) failed: %d\n", usPort, WSAGetLastError());
        closesocket(listenSock);
        return false;
    }
    if (listen(listenSock, 64) == SOCKET_ERROR) {
        printf("[NET] listen() failed: %d\n", WSAGetLastError());
        closesocket(listenSock);
        return false;
    }

    m_ullListen = listenSock;
    m_bRunning.store(true);
    printf("[NET] Listening on port %u.\n", usPort);

    std::thread(&CNetCore::AcceptLoop, this).detach();
    return true;
}

void CNetCore::Stop() {
    m_bRunning.store(false);
    if (m_ullListen != ~0ull) {
        closesocket(static_cast<SOCKET>(m_ullListen));
        m_ullListen = ~0ull;
    }
    WSACleanup();
}

void CNetCore::AcceptLoop() {
    while (m_bRunning.load()) {
        sockaddr_in clientAddr{};
        int addrLen = sizeof(clientAddr);
        SOCKET clientSock = accept(static_cast<SOCKET>(m_ullListen),
                                   reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
        if (clientSock == INVALID_SOCKET) {
            if (!m_bRunning.load()) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        char ip[64] = { 0 };
        inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));

        uint32_t dwSession = m_dwNextSession.fetch_add(1);
        uint32_t dwOnline = m_dwOnline.fetch_add(1) + 1;
        printf("[NET] Connect: session=%u ip=%s (online=%u)\n", dwSession, ip, dwOnline);

        auto* pClient = new CNetClient(static_cast<uint64_t>(clientSock), dwSession);
        std::thread([pClient, this]() {
            pClient->RecvLoop();
            printf("[NET] Disconnect: session=%u (online=%u)\n",
                   pClient->SessionId(), m_dwOnline.fetch_sub(1) - 1);
            delete pClient;
        }).detach();
    }
}

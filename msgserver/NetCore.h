#pragma once
#include <cstdint>
#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include "Network/MsgHead.h"

// Real network core for MsgServer: winsock listener, per-client threads,
// 2-byte MsgHead framing (length+type), packet dispatch to handlers.
// v1: connect/recv/dispatch/chat-echo. Port 5816 (game port from ServerGameConfig.ini).

class CNetClient {
public:
    explicit CNetClient(uint64_t ullSocket, uint32_t dwSessionId);
    ~CNetClient();

    uint32_t SessionId() const { return m_dwSessionId; }
    bool IsAlive() const { return m_bAlive.load(); }

    void RecvLoop();          // runs on its own thread
    bool Send(const void* pData, uint16_t usLen);
    void Kick();

private:
    void Dispatch(tq::MsgHead head, const uint8_t* pPayload, uint16_t usPayloadLen);

    uint64_t m_ullSocket;
    uint32_t m_dwSessionId;
    std::vector<uint8_t> m_vecInBuf;
    std::mutex m_mutexSend;
    std::atomic<bool> m_bAlive{ true };
};

class CNetCore {
public:
    static CNetCore& Instance();

    bool Start(uint16_t usPort);
    void Stop();
    uint32_t OnlineCount() const { return m_dwOnline.load(); }

private:
    CNetCore() = default;
    void AcceptLoop();

    uint64_t m_ullListen = ~0ull;
    std::atomic<bool> m_bRunning{ false };
    std::atomic<uint32_t> m_dwOnline{ 0 };
    std::atomic<uint32_t> m_dwNextSession{ 1 };
};

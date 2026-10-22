// MsgServer-side cross-server client (OS = "other server" in the original):
// connects out to the CQCrossServer hub, registers this game server,
// pushes heartbeats + rosters, relays cross chat lines in and out, and
// answers /crosswho with the hub's aggregated snapshot.
#pragma once
#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include "CrossProtocol.h"

namespace cross {

class CCrossClient {
public:
    static CCrossClient& Instance();

    bool Start();          // reads data/cross.ini; no-op when disabled
    void Stop();
    bool IsLinked() const { return m_bLinked.load(); }
    const std::string& ServerName() const { return m_strServerName; }

    // game -> hub
    void SendTalk(const std::string& strFrom, const std::string& strText);
    void RequestWho(uint32_t dwUserId); // /crosswho: reply goes to this user

private:
    CCrossClient() = default;
    void Run();                          // connect + relay loop thread
    void PushRoster();                   // heartbeat + roster snapshot
    void HandlePacket(uint16_t usType, const std::vector<uint8_t>& payload);

    std::atomic<bool> m_bRunning{ false };
    std::atomic<bool> m_bLinked{ false };
    uint64_t m_ullSocket = ~0ull;
    uint32_t m_dwServerId = 1;
    std::string m_strServerName = "Server1";
    std::string m_strHubIp = "127.0.0.1";
    uint16_t m_usHubPort = 5820;
    std::mutex m_mutexSend;
    std::mutex m_mutexPending;          // guards m_dwWhoUser
    uint32_t m_dwWhoUser = 0;           // user awaiting a /crosswho answer
};

} // namespace cross

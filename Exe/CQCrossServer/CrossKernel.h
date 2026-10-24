// CCrossServerKernel (v1 rebuild from the decompiled CQCrossServer.exe):
// pure routing state for the cross-server hub. All socket work lives in
// main.cpp; the kernel only maps server ids -> connections and relays
// messages, which makes the routing rules unit-testable offline.
#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include "CrossProtocol.h"
#include <memory>
#include "CountrySysMgr.h"

namespace cross {

struct CrossServerInfo {
    uint64_t    ullSocket = 0;      // hub-side connection handle
    uint32_t    dwServerId = 0;
    std::string strName;
    uint32_t    dwOnline = 0;
    std::vector<RosterEntry> vecRoster;
    uint64_t    ullLastBeat = 0;    // ms clock for the OnTimer drop rule
};

class CCrossServerKernel {
public:
    // delivery callback: hub shell wires this to socket send
    using SendFn = std::function<void(uint64_t ullSocket, const std::vector<uint8_t>& pkt)>;
    // reason callback: hub shell uses it for logging (CCrossServerKernel::*)
    using LogFn = std::function<void(const std::string&)>;

    explicit CCrossServerKernel(SendFn send, LogFn log = {}) 
        : m_fnSend(std::move(send)), m_fnLog(std::move(log)) {}

    // ---- connection lifecycle (NotifyOSConnect / NotifyOSDisConnect) ----
    void OnHello(uint64_t ullSocket, const HelloData& hello);   // RecordServerSocket
    void OnDisconnect(uint64_t ullSocket);                      // NotifyOSDisConnect
    void OnDropSilent(uint64_t ullNowMs);                       // OnTimer: heartbeat timeout

    // ---- routed messages ----
    void OnTalk(uint64_t ullFromSocket, const TalkData& talk);      // BroadcastOtherServerMsg
    void OnRoster(uint64_t ullFromSocket, const RosterData& roster);
    void OnHeartbeat(uint64_t ullFromSocket, const HeartbeatData& beat, uint64_t ullNowMs);
    void OnWhoReq(uint64_t ullFromSocket);                          // SendMsgToOtherServer

    // ---- country system (m_pCountrySysMgr) ----
    // case 0 of the crossmsg switch: pack league name, leader title
    // and the country date and reply to the requesting socket
    void OnCountryStatusReq(uint64_t ullSocket, const CountryStatusReq& req);
    // case 5: broadcast a system talk to every connected server
    void OnCountryBroadcast(const char* szText);
    // the hub owns the manager (Init'ed from cq_league_info)
    class CCountrySysMgr* CountrySys() { return m_pCountrySys.get(); }
    // test seam (production wiring is the hub shell after Init)
    void SetCountrySysForTest(std::shared_ptr<CCountrySysMgr> p) {
        m_pCountrySys = std::move(p);
    }

    size_t ServerCount();
    uint64_t LastBeat(uint32_t dwServerId);

private:
    void BroadcastAll(const std::vector<uint8_t>& pkt, uint64_t ullSkip = 0);
    std::vector<std::vector<uint8_t>> BuildWhoResponse();

    mutable std::mutex m_mutex;                 // the hub is multi-threaded
    std::map<uint32_t, CrossServerInfo> m_mapServers;  // by server id
    SendFn m_fnSend;
    LogFn m_fnLog;
    std::shared_ptr<class CCountrySysMgr> m_pCountrySys;
};

} // namespace cross

// CCrossServerKernel (v1 rebuild from the decompiled CQCrossServer.exe):
// pure routing state for the cross-server hub. All socket work lives in
// main.cpp; the kernel only maps server ids -> connections and relays
// messages, which makes the routing rules unit-testable offline.
#pragma once
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <set>
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
    // case 1: war score query - members without a country (-1)
    // are silently dropped, exactly like the original gate
    void OnCountryScoreReq(uint64_t ullSocket, const CountryScoreReq& req);
    // case 4: UpdateCountryDate - on success the hub refreshes its
    // country-date state and echoes the request back
    void OnCountryDateUpd(uint64_t ullSocket, const CountryDateUpd& req);
    // case 2: choose a new league for the server
    void OnCountryChoose(uint64_t ullSocket, const CountryChooseReq& req);
    // case 6: produce the first country league
    void OnCountryFirst(uint64_t ullSocket, const CountryFirstReq& req);
    // the hub owns the manager (Init'ed from cq_league_info)
    class CCountrySysMgr* CountrySys() { return m_pCountrySys.get(); }
    // test seam (production wiring is the hub shell after Init).
    // Setting the manager also wires its plunder sinks exactly the
    // way the hub does: FUN_140018870 broadcast / FUN_14000a310
    // (0x961) system talk / FUN_1400143c0 schedule-set insert.
    void SetCountrySysForTest(std::shared_ptr<CCountrySysMgr> p) {
        m_pCountrySys = std::move(p);
        if (m_pCountrySys) WireCountrySinks();
    }

    // ---- plunder war (CCrossMsgPlunderWarInfo, FUN_140023800) ----
    // Action 1 -> CCountrySysMgr::SignUpPlunderWar, action 10 ->
    // PublishSupportToken; anything else logs the original
    // "CCrossMsgPlunderWarInfo::Process wrong action[%u]" (0x140060270).
    // A null country manager hits the original m_pCountrySysMgr null
    // gate (log 0x140058a00) and nothing else happens.
    void OnPlunderWarInfo(uint64_t ullSocket, const PlunderWarInfoData& info);
    // FUN_140018870: broadcast to every ONLINE server that owns a
    // country (FUN_14000d620(server) != -1), skipping dwExclude
    void BroadcastToCountryServers(const std::vector<uint8_t>& pkt,
                                    uint32_t dwExclude);
    // FUN_1400143c0(FUN_140009ed0(kernel), id): the kernel+0x28
    // plunder schedule set (server ids); ProcessServerConnectOK
    // (FUN_14001ade0, a later unit) checks membership
    void AddPlunderScheduleServer(uint32_t dwId);
    bool IsPlunderScheduleServer(uint32_t dwId) const;
    // the country manager's OnTimer (FUN_14001abc0) - the hub
    // shell timer thread drives it every second
    void OnCountryTimer();

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
    std::set<uint32_t> m_setPlunderSchedule; // kernel+0x28 set
    void WireCountrySinks();
};

} // namespace cross

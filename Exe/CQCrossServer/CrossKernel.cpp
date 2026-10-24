// CCrossServerKernel: the routing core of the CQCrossServer rebuild.
#include "CrossKernel.h"
#include <chrono>
#include <algorithm>
#include <cstdio>

namespace cross {

// 90 seconds without a heartbeat = the server is presumed gone
// (original: kernel OnTimer prunes dead OS connections)
static const uint64_t SILENT_DROP_MS = 90'000;

void CCrossServerKernel::OnHello(uint64_t ullSocket, const HelloData& hello) {
    std::vector<std::vector<uint8_t>> toSend;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto& info = m_mapServers[hello.dwServerId];
        bool bWasHere = info.ullSocket != 0;
        info.ullSocket = ullSocket;
        info.dwServerId = hello.dwServerId;
        info.strName = hello.szName;
        info.ullLastBeat = 0; // clocked on the first heartbeat
        if (m_fnLog)
            m_fnLog("RecordServerSocket: server id " + std::to_string(hello.dwServerId) +
                    " '" + info.strName + "' connect ok" +
                    (bWasHere ? " (replacing old socket)" : ""));
        // announce to everyone else (NotifyOSConnect -> CCrossMsgOSConnectInfo)
        ServerUpDownData up;
        up.dwServerId = hello.dwServerId;
        CopyStr(up.szName, sizeof(up.szName), info.strName);
        auto pkt = Encode(MsgType_ServerUp, up);
        toSend.push_back(pkt);
        // also tell the newcomer who is already here
        for (auto& kv : m_mapServers) {
            if (kv.first == hello.dwServerId || kv.second.ullSocket == 0) continue;
            ServerUpDownData other;
            other.dwServerId = kv.second.dwServerId;
            CopyStr(other.szName, sizeof(other.szName), kv.second.strName);
            std::vector<uint8_t> p = Encode(MsgType_ServerUp, other);
            m_fnSend(ullSocket, p);
        }
    }
    for (auto& p : toSend) BroadcastAll(p, ullSocket);
}

void CCrossServerKernel::OnDisconnect(uint64_t ullSocket) {
    std::vector<std::vector<uint8_t>> toSend;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto it = m_mapServers.begin(); it != m_mapServers.end(); ++it) {
            if (it->second.ullSocket != ullSocket) continue;
            if (m_fnLog)
                m_fnLog("NotifyOSDisConnect: server " + it->second.strName +
                        " (id " + std::to_string(it->first) + ") went away");
            ServerUpDownData down;
            down.dwServerId = it->first;
            CopyStr(down.szName, sizeof(down.szName), it->second.strName);
            toSend.push_back(Encode(MsgType_ServerDown, down));
            m_mapServers.erase(it);
            break;
        }
    }
    for (auto& p : toSend) BroadcastAll(p);
}

void CCrossServerKernel::OnDropSilent(uint64_t ullNowMs) {
    std::vector<uint64_t> dead;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& kv : m_mapServers)
            if (kv.second.ullLastBeat != 0 &&
                ullNowMs - kv.second.ullLastBeat > SILENT_DROP_MS)
                dead.push_back(kv.second.ullSocket);
    }
    for (uint64_t s : dead) OnDisconnect(s); // reuses the announce + erase path
}

void CCrossServerKernel::OnTalk(uint64_t ullFromSocket, const TalkData& talk) {
    std::vector<uint8_t> pkt = Encode(MsgType_Talk, talk);
    BroadcastAll(pkt, ullFromSocket); // everyone but the origin
}

void CCrossServerKernel::OnRoster(uint64_t ullFromSocket, const RosterData& roster) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_mapServers.find(roster.dwServerId);
    if (it == m_mapServers.end() || it->second.ullSocket != ullFromSocket) return;
    it->second.vecRoster.clear();
    uint32_t n = std::min(roster.dwCount, MAX_ROSTER);
    for (uint32_t i = 0; i < n; ++i) it->second.vecRoster.push_back(roster.entries[i]);
}

void CCrossServerKernel::OnHeartbeat(uint64_t ullFromSocket, const HeartbeatData& beat,
                                     uint64_t ullNowMs) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_mapServers.find(beat.dwServerId);
    if (it == m_mapServers.end() || it->second.ullSocket != ullFromSocket) return;
    it->second.dwOnline = beat.dwOnline;
    it->second.ullLastBeat = ullNowMs;
}

uint64_t CCrossServerKernel::LastBeat(uint32_t dwServerId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_mapServers.find(dwServerId);
    return it == m_mapServers.end() ? 0 : it->second.ullLastBeat;
}

std::vector<std::vector<uint8_t>> CCrossServerKernel::BuildWhoResponse() {
    // aggregated snapshot of every server + its roster
    std::vector<std::vector<uint8_t>> out;
    std::lock_guard<std::mutex> lock(m_mutex);
    WhoRespData resp;
    resp.dwServers = 0;
    for (auto& kv : m_mapServers) {
        if (resp.dwServers >= 8) break;
        WhoRespServer& s = resp.servers[resp.dwServers];
        CopyStr(s.szServer, sizeof(s.szServer), kv.second.strName);
        s.dwOnline = kv.second.dwOnline;
        uint32_t n = std::min<uint32_t>(kv.second.vecRoster.size(), MAX_ROSTER);
        for (uint32_t i = 0; i < n; ++i) s.entries[i] = kv.second.vecRoster[i];
        ++resp.dwServers;
    }
    out.push_back(Encode(MsgType_WhoResp, resp));
    return out;
}

void CCrossServerKernel::OnWhoReq(uint64_t ullFromSocket) {
    for (auto& p : BuildWhoResponse()) m_fnSend(ullFromSocket, p);
}

void CCrossServerKernel::BroadcastAll(const std::vector<uint8_t>& pkt, uint64_t ullSkip) {
    std::vector<uint64_t> targets;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& kv : m_mapServers) {
            if (kv.second.ullSocket == 0 || kv.second.ullSocket == ullSkip) continue;
            targets.push_back(kv.second.ullSocket);
        }
    }
    for (uint64_t s : targets) m_fnSend(s, pkt);
}

size_t CCrossServerKernel::ServerCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_mapServers.size();
}

// ---------------------------------------------------------------------------
// COUNTRY system handlers (crossmsgserveraction.cpp cases 0 and 5)
// ---------------------------------------------------------------------------
void CCrossServerKernel::OnCountryStatusReq(
        uint64_t ullSocket, const CountryStatusReq& req) {
    // ORIGINAL case 0 (~29462): three m_pCountrySysMgr calls -
    // FUN_14001a6a0 (league name), FUN_14001a6d0 (leader title),
    // FUN_14001bc50 (country date, also written back to msg+8) -
    // each guarded by the "m_pCountrySysMgr" ASSERT, then two
    // CStringPacker::AddString calls carry the strings back.
    CountryStatusResp resp{};
    if (m_pCountrySys) {
        const std::string& name =
            m_pCountrySys->LeagueName(req.dwIdServer, req.dwIdLeague);
        const std::string& title =
            m_pCountrySys->LeaderTitle(req.dwIdServer, req.dwIdLeague);
        std::snprintf(resp.szLeagueName, sizeof(resp.szLeagueName),
                      "%s", name.c_str());
        std::snprintf(resp.szLeaderTitle, sizeof(resp.szLeaderTitle),
                      "%s", title.c_str());
        resp.dwCountryDate =
            m_pCountrySys->CountryDate(req.dwIdServer, req.dwIdLeague);
    }
    auto pkt = Encode(MsgType_CountryStatusResp, resp);
    if (m_fnSend) m_fnSend(ullSocket, pkt);
}

void CCrossServerKernel::OnCountryScoreReq(
        uint64_t ullSocket, const CountryScoreReq& req) {
    // ORIGINAL case 1 (~29507): FUN_14000d620(kernel, uid) must not
    // be -1 or NO reply is sent (the -1 gate, also visible at
    // ~20268); the reply packs the country id (FUN_1400246a0) and
    // the league's country date (FUN_14001bc50 -> FUN_140022ce0)
    // and is sent back with FUN_14000a0b0(kernel, 0, ...).
    if (!m_pCountrySys) return;
    const uint32_t dwCountry =
        m_pCountrySys->GetCountryByUser(req.dwUserId);
    if (dwCountry == 0xffffffff) return; // original gate
    CountryScoreResp resp{};
    resp.dwCountryId = dwCountry;
    resp.dwCountryDate =
        m_pCountrySys->CountryDate(req.dwIdServer, req.dwIdLeague);
    auto pkt = Encode(MsgType_CountryScoreResp, resp);
    if (m_fnSend) m_fnSend(ullSocket, pkt);
}

void CCrossServerKernel::OnCountryDateUpd(
        uint64_t ullSocket, const CountryDateUpd& req) {
    // ORIGINAL case 4 (~29589): FUN_14001a240(countryMgr, idserver,
    // kernelStateDate) must return true; the hub then overwrites
    // its state (kernel+0x430[+8]) with TimeGet(2)/10000 and
    // echoes the original message with FUN_14000a0b0(kernel, 0,
    // msg+0x414, msg+8, msg+0x10, msg+0xc, 1). On false there is
    // NO reply (the league/date pair was not found).
    if (!m_pCountrySys) return;
    if (!m_pCountrySys->UpdateCountryDate(req.dwIdServer, req.dwDate))
        return;
    const uint32_t dwNow =
        (uint32_t)(std::chrono::system_clock::now()
                   .time_since_epoch().count() / 10000000ULL);
    CountryDateAck ack{ req.dwIdServer, dwNow };
    if (m_fnSend) m_fnSend(ullSocket, Encode(MsgType_CountryDateAck, ack));
}

void CCrossServerKernel::OnCountryBroadcast(const char* szText) {
    // ORIGINAL case 5 (~29605): FUN_14000a0b0-style broadcast of a
    // system talk (msg type 0x961) to every server socket.
    if (!szText) return;
    TalkData talk{};
    talk.dwServerId = 0;
    std::snprintf(talk.szText, sizeof(talk.szText), "%s", szText);
    BroadcastAll(Encode(MsgType_CountryBroadcast, talk));
}

} // namespace cross

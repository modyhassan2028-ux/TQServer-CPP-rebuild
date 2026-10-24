#include "CountrySysMgr.h"
#include "MySQLClient.h"
#include <cstdio>
#include <chrono>
#include <cstdlib>

namespace cross {

bool CCountrySysMgr::Init(CMySQLClient* pDB, uint32_t dwCapacityPerServer,
                          uint32_t dwServerCount) {
    // ORIGINAL Init order: LoadLeagueInfo -> LoadPlunderTimeConfig
    // -> LoadPlunderWarInfo (CQCrossServer.exe.decompiled.c ~27030)
    m_dwCapacityPerServer = dwCapacityPerServer;
    m_dwServerCount = dwServerCount;
    if (!LoadLeagueInfo(pDB)) {
        printf("[COUNTRY] CCountrySysMgr::Init LoadLeagueInfo failed.\n");
        return false;
    }
    if (!LoadPlunderTimeConfig()) {
        printf("[COUNTRY] CCountrySysMgr::Init LoadPlunderTimeConfig failed.\n");
        return false;
    }
    if (!LoadPlunderWarInfo()) {
        printf("[COUNTRY] CCountrySysMgr::Init LoadPlunderWarInfo failed.\n");
        return false;
    }
    return true; // ORIGINAL: CONCAT71(...,1) - success
}

bool CCountrySysMgr::LoadLeagueInfo(CMySQLClient* pDB) {
    // ORIGINAL FUN_1400212d0 (~26540): SELECT * FROM cq_league_info
    m_leagues.clear();
    m_nCountryDateTotal = 0;
    if (!pDB) return false;
    if (!pDB->Query("SELECT id,idserver,idleague,country_date,"
                    "amount,league_name,leader_name,title"
                    " FROM cq_league_info")) {
        printf("[COUNTRY] %s\n", pDB->GetError().c_str());
        return false; // ORIGINAL: recordset null -> fail
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 8) continue;
        const uint32_t dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        const uint32_t dwIdServer = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        const uint32_t dwIdLeague = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        // ORIGINAL: (idserver==0 || idserver==0xffffffff ||
        // idleague==0) -> close record, skip (~26620)
        if (dwIdServer == 0 || dwIdServer == 0xffffffff ||
            dwIdLeague == 0) {
            continue;
        }
        // ORIGINAL: duplicate (idserver, idleague) ->
        // "LoadLeagueInfo: server %u league %u is exist" + skip
        const auto key = std::make_pair(dwIdServer, dwIdLeague);
        if (m_leagues.count(key)) {
            printf("[COUNTRY] CCountrySysMgr::LoadLeagueInfo: server %u "
                   "league %u is exist\n", dwIdServer, dwIdLeague);
            continue;
        }
        CountryLeague lg;
        lg.dwId = dwId;
        lg.dwIdServer = dwIdServer;
        lg.dwIdLeague = dwIdLeague;
        lg.dwCountryDate = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        lg.dwAmount = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
        lg.strLeagueName = row[5];
        lg.strLeaderName = row[6];
        lg.strTitle = row[7];
        m_leagues[key] = lg;
        // ORIGINAL: country_date > 0 rows join the date accounting
        // (local_1b8 += FUN_140022ce0) and the map at +0x60;
        // token count > 0 rows go to the map at +0x90 (no token
        // column is read from cq_league_info itself - the token
        // map is populated by the plunder-war flows, so nothing
        // is inserted here)
        if ((int32_t)lg.dwCountryDate > 0)
            m_nCountryDateTotal += lg.dwCountryDate;
    }
    // ORIGINAL tail (~26700): spare capacity distribution
    //   total = m_dwCapacityPerServer * m_dwServerCount
    //   if (m_nCountryDateTotal < total) deficit = (total -
    //   m_nCountryDateTotal) % m_dwServerCount distributed
    //   round-robin over the sorted league map. The exact
    //   round-robin ordering is documented TBD (lines 26700-26760);
    //   the capacity/deficit arithmetic is kept verbatim.
    if (m_dwServerCount >= 1) {
        const uint32_t dwTotal =
            m_dwCapacityPerServer * m_dwServerCount;
        if (m_nCountryDateTotal < dwTotal) {
            const uint32_t dwDeficit =
                (dwTotal - m_nCountryDateTotal) % m_dwServerCount;
            (void)dwDeficit; // assignment loop TBD (see header note)
        }
    }
    return true;
}

bool CCountrySysMgr::LoadPlunderTimeConfig() {
    // ORIGINAL FUN_1400165d0: loads the plunder-war time windows
    // from config (crossshell.ini / pendtime). Config file not
    // shipped in the sample; returns success like the original
    // with defaults pending a real config dump.
    return true;
}

bool CCountrySysMgr::LoadPlunderWarInfo() {
    // ORIGINAL FUN_140019bc0: loads plunder war state. Same
    // situation as LoadPlunderTimeConfig.
    return true;
}

const std::string& CCountrySysMgr::LeagueName(uint32_t dwIdServer,
                                              uint32_t dwIdLeague) const {
    static const std::string s_empty;
    auto it = m_leagues.find({dwIdServer, dwIdLeague});
    return it != m_leagues.end() ? it->second.strLeagueName : s_empty;
}

const std::string& CCountrySysMgr::LeaderTitle(uint32_t dwIdServer,
                                               uint32_t dwIdLeague) const {
    static const std::string s_empty;
    auto it = m_leagues.find({dwIdServer, dwIdLeague});
    return it != m_leagues.end() ? it->second.strTitle : s_empty;
}

uint32_t CCountrySysMgr::CountryDate(uint32_t dwIdServer,
                                     uint32_t dwIdLeague) const {
    auto it = m_leagues.find({dwIdServer, dwIdLeague});
    return it != m_leagues.end() ? it->second.dwCountryDate : 0;
}

bool CCountrySysMgr::HasLeague(uint32_t dwIdServer,
                               uint32_t dwIdLeague) const {
    return m_leagues.count({dwIdServer, dwIdLeague}) != 0;
}

uint32_t CCountrySysMgr::GetCountryByUser(uint32_t dwUserId) const {
    // ORIGINAL FUN_14000d620: lower_bound over the member map;
    // hit only when the found node key == uid, else -1 (0xffffffff)
    auto it = m_mapMemberCountry.lower_bound(dwUserId);
    if (it != m_mapMemberCountry.end() && it->first == dwUserId)
        return it->second;
    return 0xffffffff;
}
const CountryLeague* CCountrySysMgr::TokenLowerBound(
        uint32_t dwIdServer) const {
    // ORIGINAL FUN_14001a240: lower_bound walk over the token map
    // keyed by the server id; end() -> nullptr (checked by the
    // caller, the tree walk merges lower_bound + exact match).
    auto it = m_mapTokens.lower_bound(dwIdServer);
    return it == m_mapTokens.end() ? nullptr : &it->second;
}

const CountryLeague* CCountrySysMgr::CurrentLeagueOf(
        uint32_t dwIdServer) const {
    // ORIGINAL FUN_140019f80: the +0x20 map walk for the server
    // (first league of the (server,*) range wins in our port)
    auto it = m_leagues.lower_bound({dwIdServer, 0});
    if (it != m_leagues.end() && it->first.first == dwIdServer)
        return &it->second;
    return nullptr;
}

uint32_t CCountrySysMgr::CountryDateOf(uint32_t dwIdServer,
                                       uint32_t dwIdLeague) const {
    auto it = m_leagues.find({dwIdServer, dwIdLeague});
    return it == m_leagues.end() ? 0 : it->second.dwCountryDate;
}

bool CCountrySysMgr::OnChooseNewCountryLeague(
        uint32_t dwIdServer, uint32_t dwIdLeague) {
    // ORIGINAL FUN_14001ee50 - see header for the verbatim flow.
    // 1. current league: reset its token touch to 0 + commit
    if (CountryLeague* pCur = const_cast<CountryLeague*>(
            CurrentLeagueOf(dwIdServer))) {
        m_mapTokenTouch.erase(pCur->dwIdLeague); // FUN_140022e40(.., 0, 1)
    }
    // 2. target league must exist
    auto it = m_leagues.find({dwIdServer, dwIdLeague});
    if (it == m_leagues.end()) {
        printf("[COUNTRY] CCountrySysMgr::OnChooseNewCountryLeague:"
               "server %u, league %u is not exsit\n",
               dwIdServer, dwIdLeague);
        return false;
    }
    CountryLeague lg = it->second;
    // 3. erase the old entry, install the target as the server's
    //    league (the +0x20 map erase+insert)
    for (auto jt = m_leagues.begin(); jt != m_leagues.end(); ) {
        if (jt->first.first == dwIdServer && jt->first.second != dwIdLeague)
            jt = m_leagues.erase(jt);
        else ++jt;
    }
    lg.dwIdServer = dwIdServer;
    m_leagues[{dwIdServer, dwIdLeague}] = lg;
    // 4. notify mode-3 processors (FUN_14001c990(mgr, 3, ..))
    printf("[COUNTRY] OnChooseNewCountryLeague: server %u -> "
           "league %u (mode-3 notify)\n", dwIdServer, dwIdLeague);
    // 5. touch = now + commit; country date += league amount
    const uint32_t dwNow = (uint32_t)(std::chrono::system_clock::now()
        .time_since_epoch().count() / 10000000ULL);
    m_mapTokenTouch[lg.dwIdLeague] = dwNow;
    m_leagues[{dwIdServer, dwIdLeague}].dwCountryDate +=
        lg.dwAmount; // FUN_140022d40(league, amount+date, 1)
    // 6. token map: the server slot now points at the new league
    m_mapTokens[dwIdServer] = m_leagues[{dwIdServer, dwIdLeague}];
    return true;
}

bool CCountrySysMgr::OnProduceFirstCountryLeague(
        uint32_t dwIdServer, uint32_t dwKey,
        uint64_t& outPackedId, uint32_t& outTouch) {
    // ORIGINAL FUN_14001d790 - see header for the verbatim flow.
    outPackedId = 0; outTouch = 0;
    // 1. an existing country fails the flow
    if (m_mapTokens.count(dwIdServer)) {
        printf("[COUNTRY] CCountrySysMgr::OnProduceFirstCountryLeague:"
               " server %lu country is exist\n", (unsigned long)dwIdServer);
        return false;
    }
    // 2. the server must already own a league
    const CountryLeague* pCur = CurrentLeagueOf(dwIdServer);
    if (!pCur) {
        printf("[COUNTRY] CCountrySysMgr::OnProduceFirstCountryLeague:"
               " server %lu  has no league\n", (unsigned long)dwIdServer);
        return false;
    }
    CountryLeague lg = *pCur;
    // 3. score write from the manager config (mgr+0x10), no commit
    // 4. touch = now + commit
    const uint32_t dwNow = (uint32_t)(std::chrono::system_clock::now()
        .time_since_epoch().count() / 10000000ULL);
    m_mapTokenTouch[lg.dwIdLeague] = dwNow;
    // 5. token map insert for the server
    m_mapTokens[dwIdServer] = lg;
    // 6. mode-5 processor notify (FUN_14001c990(mgr, 5, ..))
    printf("[COUNTRY] OnProduceFirstCountryLeague: server %u "
           "(mode-5 notify)\n", dwIdServer);
    // 7. packed reply id: server*1000000 + key (FUN_1400243b0)
    outPackedId = (uint64_t)dwIdServer * 1000000ULL + dwKey;
    outTouch = dwNow;
    return true;
}
bool CCountrySysMgr::UpdateCountryDate(uint32_t dwIdServer,
                                       uint32_t dwDate) {
    // ORIGINAL FUN_14001a240: league tree walk for dwIdServer,
    // then the date-map entry whose FUN_140022c80 value == dwDate.
    bool bFound = false;
    for (auto& kv : m_leagues) {
        if (kv.first.first != dwIdServer) continue;
        if (kv.second.dwCountryDate != dwDate) continue;
        // ORIGINAL: FUN_140022e40(league, TimeGet(2)/10000, 1)
        // - write now into record field 4 and commit
        const uint32_t dwNow =
            (uint32_t)(std::chrono::system_clock::now()
                       .time_since_epoch().count() / 10000000ULL);
        m_mapTokenTouch[kv.second.dwIdLeague] = dwNow;
        bFound = true;
        break;
    }
    if (!bFound) {
        // ORIGINAL failure lines (verbatim, best-effort args)
        printf("[COUNTRY] CCountrySysMgr::UpdateCountryDate: "
               "server %u country league is not exist\n", dwIdServer);
    }
    return bFound;
}
uint32_t CCountrySysMgr::LastTokenTouch(uint32_t dwIdServer) const {
    for (auto& kv : m_leagues)
        if (kv.first.first == dwIdServer) {
            auto it = m_mapTokenTouch.find(kv.second.dwIdLeague);
            return it == m_mapTokenTouch.end() ? 0 : it->second;
        }
    return 0;
}
} // namespace cross

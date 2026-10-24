#include "CountrySysMgr.h"
#include "MySQLClient.h"
#include <cstdio>
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
        uint32_t dwCountryDate) const {
    // ORIGINAL FUN_14001a240: lower_bound walk over the token map
    // keyed by the country date; end() -> the original returns the
    // end iterator (checked by the caller).
    auto it = m_mapTokens.lower_bound(dwCountryDate);
    return it == m_mapTokens.end() ? nullptr : &it->second;
}
} // namespace cross

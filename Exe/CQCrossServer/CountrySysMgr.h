// CCountrySysMgr - the cross-server COUNTRY/LEAGUE system manager
// (v1 port from the decompiled CQCrossServer.exe, crossserverkernel).
//
// ORIGINAL Init flow (CQCrossServer.exe.decompiled.c ~line 27030):
//   1. FUN_140016520          - DB/config handle setup
//   2. LoadLeagueInfo (FUN_140020cf0)
//      fail -> "CCountrySysMgr::Init LoadLeagueInfo failed."
//   3. LoadPlunderTimeConfig (FUN_1400165d0)
//      fail -> "CCountrySysMgr::Init LoadPlunderTimeConfig failed."
//   4. LoadPlunderWarInfo (FUN_140019bc0)
//      fail -> "CCountrySysMgr::Init LoadPlunderWarInfo failed."
//   5. Init returns 1 (success)
//
// LoadLeagueInfo (FUN_1400212d0, ~line 26540) is ported faithfully:
//   SELECT * FROM cq_league_info
//   col 1 = id, col 2 = idserver, col 3 = idleague (GetInt); a row
//   with idserver==0 or 0xffffffff, or idleague==0 is skipped
//   (vcall+0x10(rec,1) ... check at ~26620). Duplicate (idserver,
//   idleague) -> "LoadLeagueInfo: server %u league %u is exist"
//   error + FUN_1400232b0 fixup (delete/replace) and the row is
//   skipped. Valid rows insert into the per-server league map
//   (FUN_14001a700 = std::map insert at +0x20). Per-league
//   country_date (FUN_140022ce0 = league->country_date) > 0 rows
//   are also listed in the date map (+0x60); token count
//   (FUN_140022de0 > 0, value FUN_140022c20) goes into the token
//   map (+0x90). The tail (~26620-26760) distributes the spare
//   capacity: m_nCapacityPerServer(+0x10) * m_nServerCount(+200)
//   vs the loaded country_date total, deficit modulo the server
//   count, assigned round-robin over the sorted league map
//   (exact round-robin order documented TBD - lines 26700-26760).
#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class CMySQLClient;

namespace cross {

struct CountryLeague {
    uint32_t dwId = 0;         // cq_league_info.id
    uint32_t dwIdServer = 0;   // cq_league_info.idserver
    uint32_t dwIdLeague = 0;   // cq_league_info.idleague
    uint32_t dwCountryDate = 0; // cq_league_info.country_date
    uint32_t dwAmount = 0;      // cq_league_info.amount
    std::string strLeagueName;  // league_name
    std::string strLeaderName;  // leader_name
    std::string strTitle;       // title
};

class CCountrySysMgr {
public:
    // ORIGINAL Init: the four stages above; returns false and logs
    // the original message if a stage fails.
    bool Init(CMySQLClient* pDB, uint32_t dwCapacityPerServer,
             uint32_t dwServerCount);

    // ---- country status query (kernel msg case 0, ~29462) ----
    // FUN_14001a6a0(countryId, dwA) -> league name ("" if none)
    // FUN_14001a6d0(countryId, dwA) -> leader/title ("" if none)
    // FUN_14001bc50(countryId, dwA) -> country_date read (the same
    //   call also writes back the packed value at msg+8 in case 0)
    const std::string& LeagueName(uint32_t dwIdServer, uint32_t dwIdLeague) const;
    const std::string& LeaderTitle(uint32_t dwIdServer, uint32_t dwIdLeague) const;
    uint32_t CountryDate(uint32_t dwIdServer, uint32_t dwIdLeague) const;

    bool HasLeague(uint32_t dwIdServer, uint32_t dwIdLeague) const;
    size_t LeagueCount() const { return m_leagues.size(); }
    uint32_t TotalCountryDate() const { return m_nCountryDateTotal; }

    // test seam: inject a validated league (LoadLeagueInfo path)
    void InsertLeagueForTest(const CountryLeague& lg) {
        m_leagues[{lg.dwIdServer, lg.dwIdLeague}] = lg;
    }

private:
    bool LoadLeagueInfo(CMySQLClient* pDB);
    bool LoadPlunderTimeConfig();  // FUN_1400165d0: config file load
    bool LoadPlunderWarInfo();     // FUN_140019bc0: war info load

    // key: (idserver, idleague) - the ORIGINAL per-server map at +0x20
    std::map<std::pair<uint32_t, uint32_t>, CountryLeague> m_leagues;
    uint32_t m_nCountryDateTotal = 0;   // local_1b8 in LoadLeagueInfo
    uint32_t m_dwCapacityPerServer = 0; // *(param+0x10)
    uint32_t m_dwServerCount = 0;       // *(param+200)
};

} // namespace cross

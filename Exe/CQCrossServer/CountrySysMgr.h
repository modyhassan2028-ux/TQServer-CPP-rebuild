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

    // ---- case 1 (~29507): member -> country lookup ----
    // ORIGINAL FUN_14000d620: RB-tree lower_bound over the member
    // map (mgr+0xa8, key uid at node+0x18, value country at
    // +0x1c); returns 0xffffffff (-1) when the uid is absent.
    // Usage ~20268: "FUN_14000d620(kernel, uid) != -1" gates the
    // SendMsg reply - a member without a country gets nothing.
    uint32_t GetCountryByUser(uint32_t dwUserId) const;
    // ORIGINAL FUN_14001a240 (case 4, 434 bytes): lower_bound walk
    // over the token map (mgr+0x90) - keyed by the SERVER id (case
    // 2 sets local_528[0] = param_2 = server before the insert);
    // returns the league holding the server's token.
    const CountryLeague* TokenLowerBound(uint32_t dwIdServer) const;

    bool HasLeague(uint32_t dwIdServer, uint32_t dwIdLeague) const;

    // ---- case 4 (~29589): CCountrySysMgr::UpdateCountryDate ----
    // ORIGINAL FUN_14001a240 (the FULL 434 bytes, not just the
    // lookup): find the league of dwIdServer, walk its date map
    // for the entry whose value (FUN_140022c80) equals dwDate,
    // then FUN_140022e40(league, now/10000, 1) - update field 4
    // of the record to now and commit (vcall+0x38 with 0).
    // Failure logs the original lines: "UpdateCountryDate:
    // server %u country league is not exist" / "UpdateCountryDate:
    // country league %u is not exist,server=%u". Returns whether
    // the update landed; the kernel then refreshes its state
    // timestamp and echoes the request back.
    bool UpdateCountryDate(uint32_t dwIdServer, uint32_t dwDate);

    // ---- case 2 (~29579): OnChooseNewCountryLeague ----
    // ORIGINAL FUN_14001ee50 (1743 bytes; the name is verbatim in
    // the failure log). Flow, verbatim:
    //  1. FUN_140019f80(mgr, server) - the current league; if
    //     found, FUN_140022e40(league, 0, 1) resets its token
    //     touch to 0 and commits
    //  2. FUN_140019e20(mgr, server, league) - the target league;
    //     missing -> "OnChooseNewCountryLeague:server %u, league
    //     %u is not exsit" and FAIL
    //  3. erase the old entry from the +0x20 map
    //     (FUN_140018c10), insert the target as the server's new
    //     league (tree insert + FUN_140019910 rebalance)
    //  4. FUN_14001c990(mgr, 3, ...) - notify mode-3 processors
    //  5. now = TimeGet(2)/10000; FUN_140022e40(league, now, 1)
    //     - touch + commit; FUN_140022d40(league, amount +
    //     country_date, 1) - add the league amount into the
    //     country date record and commit
    //  6. FUN_14001a700(mgr+0x90, server) -> the token map slot
    //     receives the new league pointer
    bool OnChooseNewCountryLeague(uint32_t dwIdServer,
                                  uint32_t dwIdLeague);

    // ---- case 6 (~29609): OnProduceFirstCountryLeague ----
    // ORIGINAL FUN_14001d790 (1677 bytes; name verbatim in the
    // failure logs). Flow:
    //  1. the server's country map (+0xc0) walk - an existing
    //     country -> "OnProduceFirstCountryLeague: server %lu
    //     country is exist" and FAIL
    //  2. the +0x20 map lookup - missing -> "server %lu has no
    //     league" and FAIL
    //  3. FUN_140022d40(league, *(uint*)(mgr+0x10), 0) - write
    //     the manager config amount (mgr+0x10) into the score
    //     field, NO commit
    //  4. now = TimeGet(2)/10000; FUN_140022e40(league, now, 1)
    //  5. token map (+0x90) insert for the server
    //  6. FUN_14001c990(mgr, 5, ...) - notify mode-5 processors
    //  7. packer reply: FUN_1400243b0(packer, 3,
    //     server*1000000 + dwKey, now) - the packed id and the
    //     touch timestamp travel back to the caller
    // returns the packed id (server*1000000 + dwKey) and the
    // touch timestamp via the out params; false on failure.
    bool OnProduceFirstCountryLeague(uint32_t dwIdServer,
                                     uint32_t dwKey,
                                     uint64_t& outPackedId,
                                     uint32_t& outTouch);
    // ORIGINAL: score field write target of FUN_140022d40
    // (mgr+0x10 config in case 6, country_date+amount in case 2)
    uint32_t CountryDateOf(uint32_t dwIdServer, uint32_t dwIdLeague) const;
    // ORIGINAL: FUN_140019f80 - the server's CURRENT league
    const CountryLeague* CurrentLeagueOf(uint32_t dwIdServer) const;
    // field 4 of the league record: FUN_140022e40's +0xb0 write
    uint32_t LastTokenTouch(uint32_t dwIdServer) const;
    size_t LeagueCount() const { return m_leagues.size(); }
    uint32_t TotalCountryDate() const { return m_nCountryDateTotal; }

    // test seam: inject a validated league (LoadLeagueInfo path)
    void InsertLeagueForTest(const CountryLeague& lg) {
        m_leagues[{lg.dwIdServer, lg.dwIdLeague}] = lg;
        if ((int32_t)lg.dwCountryDate > 0)
            m_nCountryDateTotal += lg.dwCountryDate;
    }
    // test seam: register a member country (the +0xa8 map)
    void InsertMemberForTest(uint32_t dwUserId, uint32_t dwCountryId) {
        m_mapMemberCountry[dwUserId] = dwCountryId;
    }
    // test seam: token map entry (plunder-war flows own this map)
    void InsertTokenForTest(uint32_t dwCountryDate, const CountryLeague& lg) {
        m_mapTokens[dwCountryDate] = lg;
    }

private:
    bool LoadLeagueInfo(CMySQLClient* pDB);
    bool LoadPlunderTimeConfig();  // FUN_1400165d0: config file load
    bool LoadPlunderWarInfo();     // FUN_140019bc0: war info load

    // key: (idserver, idleague) - the ORIGINAL per-server map at +0x20
    std::map<std::pair<uint32_t, uint32_t>, CountryLeague> m_leagues;
    // ORIGINAL member->country map (mgr+0xa8, FUN_14000d620)
    std::map<uint32_t, uint32_t> m_mapMemberCountry;
    // ORIGINAL token map (mgr+0x90): server id -> league. Filled
    // by OnChooseNewCountryLeague / OnProduceFirstCountryLeague
    // (FUN_14001a700 inserts, local_528[0] = the server id)
    std::map<uint32_t, CountryLeague> m_mapTokens;
    // ORIGINAL field 4 of the country record: FUN_140022e40's
    // +0xb0 vcall writes now (TimeGet(2)/10000) into it
    std::map<uint32_t, uint32_t> m_mapTokenTouch; // key: league id
    uint32_t m_nCountryDateTotal = 0;   // local_1b8 in LoadLeagueInfo
    uint32_t m_dwCapacityPerServer = 0; // *(param+0x10)
    uint32_t m_dwServerCount = 0;       // *(param+200)
};

} // namespace cross

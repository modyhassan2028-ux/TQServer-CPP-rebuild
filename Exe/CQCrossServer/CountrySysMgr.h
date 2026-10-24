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
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "CrossProtocol.h"

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

    // ORIGINAL LoadLeagueInfo tail (LAB_1400211b0): distribute the
    // spare capacity over the leagues - every league gets
    // (total-dateSum)/serverCount, the first (deficit%count) get
    // one extra; public so the tail is testable in isolation.
    void DistributeSpareCapacity();

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

    // ================= CCrossMsgLeagueInfo (40066) =================
    // ORIGINAL Process FUN_140023c60: usAction 0 -> FUN_140021c90
    // (OnProduceNewLeague), 1 -> FUN_14001a0a0, any other value
    // falls through SILENTLY (no wrong-action log, unlike
    // PlunderWarInfo).
    // ---- action 0: FUN_140021c90 OnProduceNewLeague ----
    // Flow, verbatim from the decompile:
    //  1. DB handle null -> log error, FAIL (log text
    //     unrecovered, error branch at 140021d20)
    //  2. INSERT INTO cq_league_info (idserver, idleague,
    //     amount, country_date, league_name, leader_name, title)
    //     - statement fields 1..7 map to the columns in this
    //     order; entry strings cap 0x10
    //  3. duplicate record (the execute "already exists" path)
    //     -> FUN_1400232b0 completion with the error, NO reply,
    //     NO map changes
    //  4. FUN_1400212d0: insert into the (server, league) map
    //  5. amount != 0 -> token map (+0x90) insert
    //     (FUN_14001a700)
    //  6. FUN_14001c990(mgr, 7, {new league}, server) - the
    //     mode-7 brick notify (BuildBrickNotify below)
    //  7. reply: CCrossMsgLeagueInfo action 2, one entry
    //     { id: idleague + idserver*1000000, +4: country_date,
    //     +0xc/+0x1c/+0x2c: the league strings } sent via
    //     FUN_140018870(mgr, msg, dwIdServer) - broadcast to
    //     every country server EXCEPT the source.
    // On success returns the reply entry via outReply.
    bool OnProduceNewLeague(uint32_t dwIdServer,
                            const LeagueInfoEntry& entry,
                            LeagueInfoEntry& outReply);
    // ---- action 1: FUN_14001a0a0 ----
    // Find the server's league in the +0x50 tree (keyed by
    // server), FUN_1400191f0 re-key it by the entry id, then
    // FUN_140022f40(league, 6, entry+0x1c leader_name, 0) - no
    // commit - and FUN_140022f40(league, 5, entry+0xc
    // league_name, 1) - commit. Missing league -> silent FAIL.
    bool OnUpdateLeagueInfo(uint32_t dwIdServer,
                            const LeagueInfoEntry& entry);
    // ================= CCrossMsgLeagueStr (40067) =================
    // ORIGINAL Process FUN_1400243f0: usAction 0 -> FUN_14001bca0,
    // 1 -> FUN_14001c600, 2 -> FUN_14001c030, else silent.
    // All three: empty string -> silent FAIL; find the (server,
    // league) record; write the field with commit:
    //   action 0: field 5 = league_name
    //   action 1: field 6 = leader_name
    //   action 2: field 7 = title (guards server!=0 &&
    //             league!=0 first)
    // then re-encode the SAME action/server/league/string and
    // broadcast it: FUN_140018870(mgr, msg, 0) for actions 0/1,
    // FUN_140018870(mgr, msg, dwIdServer) for action 2 (the
    // source is excluded from its own announce).
    bool OnLeagueStr(uint16_t usAction, uint32_t dwIdServer,
                     uint32_t dwIdLeague, const char* szText);
    // ================= FUN_14001c990 OnBrickChange =================
    // Mode notify used by the league flows (mode 3 in case 2,
    // mode 5 in case 6, mode 7 in OnProduceNewLeague):
    //  1. FUN_14000d620(kernel, server) - the country; -1 logs
    //     "OnBrickChange:socket %u of server %u not exist" and
    //     the notify still runs (the country value only rides
    //     the chunk-flush queue target)
    //  2. FUN_140019f80(mgr, server) - the current league; the
    //     header carries its idleague (field 2) and
    //     country_date (field 4); league missing -> both 0
    //  3. entries: (idleague, amount) per league in the list,
    //     8 bytes each; FUN_140024170 fails past 0x3ff -> flush
    //     the full brick, re-encode the header, re-append
    //  4. the final brick broadcasts with FUN_140018870(mgr,
    //     brick, 0) - every country server, no exclusion.
    // ---- ProcessServerConnectOK (ORIGINAL FUN_14001ade0) ----
    // When a game server finishes registering, the hub queues the
    // full league/plunder state to its COUNTRY (FUN_14000a0b0 ->
    // the country broadcast in the rebuild):
    //  (a) mode-1 brick: header = the server's current league
    //      (FUN_1400240f0(1, idleague, country_date)) + entries
    //      (idleague, amount) of ITS OWN leagues
    //  (b) LeagueRank action 0: a 0x2c entry per league
    //      (idleague, idserver, amount, league_name, leader_name
    //      - FUN_1400230a0 field pulls 2/1/3 + strings 5/6)
    //  (c) LeagueInfo action 2: entries for every league of
    //      EVERY OTHER server (skip node[3] == dwIdServer)
    //  (d) PlunderWarInfo: mode-3 announce (id 0), then a
    //      mode-0 message per today-war with its 10 target
    //      columns (fields 3..12 via the vcall loop)
    //  (e) LeagueList action 0: league ids from
    //      lower_bound(dwIdServer) to the end, chunked
    // Country -1 (FUN_14000d620) -> NOTHING at all.
    void ProcessServerConnectOK(uint32_t dwIdServer);

    // Returns the ready wire packets (one per chunk).
    std::vector<std::vector<uint8_t>> BuildBrickNotify(
            uint16_t usMode, uint32_t dwIdServer,
            const std::vector<const CountryLeague*>& vecLeagues);
    // ORIGINAL: score field write target of FUN_140022d40
    // (mgr+0x10 config in case 6, country_date+amount in case 2)
    uint32_t CountryDateOf(uint32_t dwIdServer, uint32_t dwIdLeague) const;
    // ORIGINAL: FUN_140019f80 - the server's CURRENT league
    const CountryLeague* CurrentLeagueOf(uint32_t dwIdServer) const;
    // field 4 of the league record: FUN_140022e40's +0xb0 write
    uint32_t LastTokenTouch(uint32_t dwIdServer) const;
    size_t LeagueCount() const { return m_leagues.size(); }
    uint32_t TotalCountryDate() const { return m_nCountryDateTotal; }
    // test seam: the config inputs of the distribution tail
    void SetCapacityForTest(uint32_t dwCap, uint32_t dwServers) {
        m_dwCapacityPerServer = dwCap; m_dwServerCount = dwServers;
    }

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

    // ==================== PLUNDER WAR ====================
    // The unit begins here: FUN_1400165d0 (LoadPlunderTimeConfig),
    // FUN_140019bc0 (LoadPlunderWarInfo), FUN_14001abc0 (OnTimer:
    // day change + FUN_14001a400 status machine), FUN_14001de20
    // (SignUpPlunderWar), FUN_14001e700 (PublishSupportToken).
    // Manager state, verbatim offsets:
    //   +0xc   m_dwPlunderDay      - last seen TimeGet(3) snapshot
    //   +0xd0  m_nPlunderStatus     - 0 idle, 1 signup ended, 2 war,
    //                                 3 ended (written by FUN_14001a400
    //                                 and the OnTimer day change)
    //   +0xd4  m_dwPlunderWarStart  - cq_config type 149883 data2 (HHMM)
    //   +0xd8  m_dwPlunderSignupEnd - cq_config type 149883 data1 (HHMM)
    //   +0xdc  m_dwPlunderWarEnd    - cq_config type 149883 data3 (HHMM)
    //   +0xe0/+0x110 m_mapPlunderWarToday - keyed by apply_id
    //   kernel+0x28 set (FUN_140009ed0/FUN_1400143c0) - plunder
    //   schedule server ids, modelled on the kernel (see
    //   CCrossServerKernel::AddPlunderScheduleServer); the manager
    //   pushes into it through the schedule sink.
    enum { PLUNDER_IDLE = 0, PLUNDER_SIGNUP_ENDED = 1,
           PLUNDER_WAR = 2, PLUNDER_ENDED = 3 };

    struct PlunderWarRecord {
        uint32_t dwId = 0;       // cq_plunder_war.id (auto)
        uint32_t dwApplyDate = 0; // col 1 (apply_date, TimeGet(3)%100)
        uint32_t dwApplyId = 0;   // col 2 (apply_id, the packed
                                  // server*1000000+league id)
        uint32_t dwTargets[10] = {0}; // cols 3..12
        uint8_t byCount = 0;     // number of valid targets
    };

    // test seam: inject a today-war (the FUN_14001ade0 +0xe0 map)
    void InsertWarForTest(uint32_t dwKey,
                          const PlunderWarRecord& rec) {
        m_mapPlunderWarToday[dwKey] = rec;
    }

    // ---- sinks wired by the kernel after Init ----
    // FUN_140018870: broadcast a built packet to every online server
    // that owns a country (FUN_14000d620 != -1), skipping dwExclude.
    using PlunderBroadcastFn =
        std::function<void(const std::vector<uint8_t>& pkt,
                           uint32_t dwExclude)>;
    // FUN_14000a310(kernel, text, 0, 0xffffff, 0x961): system talk
    using PlunderTalkFn = std::function<void(const std::string&)>;
    // FUN_1400143c0(FUN_140009ed0(kernel), id): plunder schedule add
    using PlunderScheduleFn = std::function<void(uint32_t)>;
    // FUN_14000d620(kernel, server) sink for OnBrickChange: the
    // country id of a SERVER (0xffffffff = not exist)
    using CountryOfServerFn = std::function<uint32_t(uint32_t)>;
    void SetCountryOfServerFn(CountryOfServerFn fn) {
        m_fnCountryOfServer = std::move(fn);
    }
    void SetPlunderSinks(PlunderBroadcastFn fnBroadcast,
                         PlunderTalkFn fnTalk,
                         PlunderScheduleFn fnSchedule);

    // ---- FUN_1400165d0 (real DB load, verbatim) ----
    // SELECT * FROM cq_config WHERE type = 149883 LIMIT 1;
    // col 2 (data1) -> +0xd8 (signup end, HHMM; the ORIGINAL gate is
    // "data1/100 must be >= 2 and <= 22" - the binary string says
    // "data1 must be greater than 1 and less than 23,type[%d]"),
    // col 3 (data2) -> +0xd4 (war start), col 4 (data3) -> +0xdc
    // (war end). No row -> "table:cq_config, CCountrySysMgr::
    // LoadPlunderTimeConfig no corresponding config found,type[%d]"
    // (0x14005e190, GBK) -> FAIL.
    bool LoadPlunderTimeConfig(CMySQLClient* pDB);

    // ---- FUN_140019bc0 (real DB load, verbatim) ----
    // SELECT * FROM cq_plunder_war; only rows with col 1 ==
    // TimeGet(3)%100 (today) enter the map; col 2 (apply_id) == 0 ->
    // "id[%lu] idPlunder[%lu] is error"; duplicate key ->
    // "id[%lu] Plunder[%lu] is exist"; wrong date ->
    // "id[%lu] date[%lu] is error" (all log, all skip).
    bool LoadPlunderWarInfo(CMySQLClient* pDB);

    // ---- FUN_14001abc0 (OnTimer, verbatim) ----
    // Day change (mgr+0xc != TimeGet(3)):
    //   - non-empty map -> "CCountrySysMgr::OnTimer
    //     m_mapPlunderWarToday is not empty", then every record is
    //     released and the map erased (FUN_1400110a0-style walk)
    //   - +0xd0 = 0 (status reset)
    //   - PlunderWarStatus(action 2, param 0) broadcast
    // Then FUN_14001a400 ALWAYS runs:
    //   status 0: TimeGet(4)/100 >= +0xd8 -> empty map ? status 3
    //             : status 1 + PlunderWarStatus(3,0) broadcast +
    //             STR_PLUNDER_WAR_SIGNUP_END talk
    //   status 1: TimeGet(4)/100 >= +0xd4 -> status 2 +
    //             PlunderWarStatus(0, (((end/100)*60+(start/100)*40)
    //             - start)*60 + (end%100)*60 + TimeGet(1)) broadcast
    //   status 2: TimeGet(4)/100 >= +0xdc -> status 3 +
    //             PlunderWarStatus(1,0) broadcast + the today-map
    //             is cleared (FUN_140018a40)
    void OnTimer();

    // ---- FUN_14001de20 (SignUpPlunderWar, verbatim) ----
    // Action 1 of CCrossMsgPlunderWarInfo. Gates in order:
    //   1. id == 0 || count < 1 -> "id is error idPlunder[%lu]!"
    //   2. status == 2 || 3 -> "status is error idPlunder[%lu]!"
    //   3. duplicate apply_id in the today map ->
    //      "record is exist idPlunder[%lu]!"
    //   4. FUN_140019e20(mgr, id/1000000, id%1000000) == 0 ->
    //      "can not find league idPlunder[%lu]!"
    //   5. target loop (target == 0 or == id skipped; the target
    //      server must have a league - "can not find league
    //      idPlundered[%lu],  idPlunder[%lu]!" (double space, 0x5f1e0);
    //      target%1000000 must equal the target league's country
    //      (FUN_140022c80) - "is not country league idPlundered[%lu],
    //      idPlunder[%lu]!" (0x5f240); bad targets are skipped)
    //   6. no valid target, or count == 0 or > 10 ->
    //      "idPlunder[%lu] target num[%d] !"
    //   7. INSERT cq_plunder_war: col1 = TimeGet(3)%100 (byte),
    //      col2 = id, cols 3.. = targets; commit fail ->
    //      "record insert error, idPlunder[%lu]!" /
    //      "create record error, idPlunder[%lu]!" (no table handle)
    //   8. map insert; PlunderWarInfo(action 2, id, targets)
    //      broadcast (FUN_140018870, exclude 0); the msg build is
    //      capped at 0x3ff -> "msg size error, idPlunder[%lu]!"
    //   9. schedule set: first valid target's league id + the
    //      attacker's league id (FUN_1400143c0 x2)
    //  10. STR_PLUNDER_WAR_TOMORROW_BEGIN talk (0x961) + return true
    bool SignUpPlunderWar(uint32_t dwIdPlunder, uint32_t dwCount,
                          const uint32_t* pTargets);

    // ---- FUN_14001e700 (PublishSupportToken, verbatim) ----
    // Action 10 of CCrossMsgPlunderWarInfo. Gates in order:
    //   1. id == 0 || count < 1 || count > 10 ->
    //      "id is error idServerLeague[%lu], nAmount[%d]!"
    //   2. status == 1 || 2 -> "status is error idServerLeague[%lu]!"
    //   3. target league lookup/gates as SignUp (same strings with
    //      idPlundered); valid targets 0 or > 10 ->
    //      "idServerLeague[%lu] nAmount[%d] !" (target num)
    //   4. PlunderWarInfo(action 11, id, targets) broadcast
    //   5. schedule set: the FIRST VALID TARGET's server id
    //      (param_2/1000000 = the attacker server) - the first target
    //      id is added TWICE verbatim (FUN_140022fe0/c20 called twice),
    //      then the attacker server id (FUN_1400143c0(obj, local_5e0))
    //   6. STR_PUBLISH_SUPPORT_TOKEN_SUCCESS talk + return true
    bool PublishSupportToken(uint32_t dwIdServerLeague, uint32_t dwCount,
                             const uint32_t* pTargets);

    // ---- test/inspection seams ----
    int  PlunderStatus() const { return m_nPlunderStatus; }
    void SetPlunderStatusForTest(int n) { m_nPlunderStatus = n; }
    void SetPlunderTimesForTest(uint32_t dwStart, uint32_t dwSignupEnd,
                                uint32_t dwEnd) {
        m_dwPlunderWarStart = dwStart; m_dwPlunderSignupEnd = dwSignupEnd;
        m_dwPlunderWarEnd = dwEnd;
    }
    // TimeGet modelings used by the unit (conventions consistent with
    // every observed use): TimeGet(3) = local yyyymmdd, TimeGet(4) =
    // local HHMM, TimeGet(1) = local seconds since midnight. The test
    // clock overrides all three.
    void SetClockForTest(uint32_t dwTimeGet1, uint32_t dwTimeGet3,
                         uint32_t dwTimeGet4) {
        m_bClockForTest = true;
        m_dwClock1 = dwTimeGet1; m_dwClock3 = dwTimeGet3;
        m_dwClock4 = dwTimeGet4;
    }
    void ClearClockForTest() { m_bClockForTest = false; }
    uint32_t PlunderDay() const { return m_dwPlunderDay; }
    size_t PlunderWarCount() const { return m_mapPlunderWarToday.size(); }
    bool PlunderScheduleHas(uint32_t dwId) const {
        return m_setSchedulePushed.count(dwId) != 0;
    }
    // the loaded/inserted war record (null when absent)
    const PlunderWarRecord* FindPlunderWar(uint32_t dwApplyId) const;
    void SetPlunderDayForTest(uint32_t d) { m_dwPlunderDay = d; }
    // the DB handle the INSERT path uses (kept from Init, like the
    // original keeps the record-set/table handles of the instance)
    void SetPlunderDBForTest(CMySQLClient* pDB) { m_pDBPlunder = pDB; }

private:
    bool LoadLeagueInfo(CMySQLClient* pDB);

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

    // ---- plunder war state (offsets in the header block above) ----
    uint32_t m_dwPlunderDay = 0;        // mgr+0xc (0 in the ctor - the
                                       // first OnTimer after startup
                                       // always sees a day change)
    int m_nPlunderStatus = 0;           // mgr+0xd0
    uint32_t m_dwPlunderWarStart = 0;    // mgr+0xd4
    uint32_t m_dwPlunderSignupEnd = 0;  // mgr+0xd8
    uint32_t m_dwPlunderWarEnd = 0;     // mgr+0xdc
    std::map<uint32_t, PlunderWarRecord> m_mapPlunderWarToday; // +0xe0
    PlunderBroadcastFn m_fnBroadcast;  // FUN_140018870 sink
    CountryOfServerFn m_fnCountryOfServer; // FUN_14000d620 sink
    PlunderTalkFn m_fnTalk;             // FUN_14000a310 sink
    PlunderScheduleFn m_fnSchedule;     // FUN_1400143c0 sink
    std::set<uint32_t> m_setSchedulePushed; // mirror for inspection
    CMySQLClient* m_pDBPlunder = nullptr; // Init's handle
    bool m_bClockForTest = false;
    uint32_t m_dwClock1 = 0, m_dwClock3 = 0, m_dwClock4 = 0;
    uint32_t TimeGet1() const; // local seconds since midnight
    uint32_t TimeGet3() const; // local yyyymmdd
    uint32_t TimeGet4() const; // local HHMM
};

} // namespace cross

#include "CountrySysMgr.h"
#include "MySQLClient.h"
#include "CrossProtocol.h"
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
    m_pDBPlunder = pDB; // kept for the SignUp INSERT path
    if (!LoadLeagueInfo(pDB)) {
        printf("[COUNTRY] CCountrySysMgr::Init LoadLeagueInfo failed.\n");
        return false;
    }
    if (!LoadPlunderTimeConfig(pDB)) {
        printf("[COUNTRY] CCountrySysMgr::Init LoadPlunderTimeConfig failed.\n");
        return false;
    }
    if (!LoadPlunderWarInfo(pDB)) {
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
    DistributeSpareCapacity();
    return true;
}
void CCountrySysMgr::DistributeSpareCapacity() {
    // ORIGINAL tail (LAB_1400211b0, ~26700-26760): spare capacity
    //   distribution, ported verbatim:
    //   uVar3 = capacity total, local_1b8 = the date sum accumulated
    //   above, iVar14 = server count, uVar7 = deficit % count.
    //   The loop walks the server map (+0xc0, tree order = ascending
    //   server id); per node, plVar6[4] is its league entry:
    //     iVar4 = FUN_140022ce0(league) + (uVar3-local_1b8)/iVar14;
    //     if (0 < uVar7) { iVar4 += 1; uVar7--; }
    //     FUN_140022d40(league, iVar4, 1);   // write + commit
    //   i.e. every league gets its full share, and the FIRST
    //   (deficit % count) leagues get one extra.
    if (m_dwServerCount >= 1) {
        const int32_t nTotal =
            (int32_t)(m_dwCapacityPerServer * m_dwServerCount);
        if ((int32_t)m_nCountryDateTotal < nTotal) {
            const int32_t nShare = (nTotal - (int32_t)m_nCountryDateTotal)
                                   / (int32_t)m_dwServerCount;
            int32_t nRem = (nTotal - (int32_t)m_nCountryDateTotal)
                           % (int32_t)m_dwServerCount;
            // tree order over the servers: our (server, league) map
            // enumerates them ascending
            uint32_t dwLastServer = 0xffffffff;
            for (auto& kv : m_leagues) {
                if (kv.first.first == dwLastServer) continue;
                dwLastServer = kv.first.first;
                int32_t nNew = (int32_t)kv.second.dwCountryDate + nShare;
                if (0 < nRem) { nNew += 1; nRem -= 1; } // uVar7 spread
                kv.second.dwCountryDate = (uint32_t)nNew; // +0xb0 write
            }
        }
    }
}

// ---- FUN_1400165d0 (verbatim) -----------------------------------
// SELECT * FROM cq_config WHERE type = 149883 (0x249fb) LIMIT 1.
// Col 2 (data1) -> +0xd8 signup end; the ORIGINAL gate: data1/100
// must be >= 2 and <= 22, else the binary string (0x14005e130):
// "table:cq_config, CCountrySysMgr::LoadPlunderTimeConfig data1
//  \xb1\xd8\xd0\xeb\xb4\xf3\xd3\xda1\xc7\xd2\xd0\xa1\xd3\xda23,type[%d]"
// ("data1 must be > 1 and < 23") -> FAIL. Cols 3 (data2) -> +0xd4
// war start, 4 (data3) -> +0xdc war end. A missing row logs
// 0x14005e190 ("no matching config found") -> FAIL.
bool CCountrySysMgr::LoadPlunderTimeConfig(CMySQLClient* pDB) {
    if (!pDB) return false;
    if (!pDB->Query("SELECT * FROM cq_config WHERE type = 149883 "
                    "LIMIT 1") || pDB->GetRows().empty()) {
        // ORIGINAL log_InlineLogDBERROR(DAT_14005e190):
        // table:cq_config, CCountrySysMgr::LoadPlunderTimeConfig
        // 未找到对应的配置,type[%d]
        printf("[COUNTRY][DB] table:cq_config, CCountrySysMgr::"
               "LoadPlunderTimeConfig \xce\xb4\xd5\xd2\xb5\xbd\xb6\xd4"
               "\xd3\xa6\xb5\xc4\xc5\xe4\xd6\xc3,type[%d]\n", 149883);
        return false;
    }
    const auto& row = pDB->GetRows()[0];
    if (row.size() < 5) return false;
    m_dwPlunderSignupEnd = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
    if (m_dwPlunderSignupEnd / 100 < 2 || m_dwPlunderSignupEnd / 100 > 22) {
        // ORIGINAL log_InlineLogDBERROR(DAT_14005e130): data1 must be
        // greater than 1 and less than 23
        printf("[COUNTRY][DB] table:cq_config, CCountrySysMgr::"
               "LoadPlunderTimeConfig data1 "
               "\xb1\xd8\xd0\xeb\xb4\xf3\xd3\xda" "1\xc7\xd2\xd0\xa1"
               "\xd3\xda" "23,type[%d]\n", 149883);
        return false;
    }
    m_dwPlunderWarStart = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
    m_dwPlunderWarEnd   = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
    return true; // ORIGINAL: CONCAT71(...,1)
}

// ---- FUN_140019bc0 (verbatim) ----------------------------------
// SELECT * FROM cq_plunder_war. Col 0 is read (statement-level
// GetInt), col 1 (apply_date) must equal TimeGet(3)%100 (today),
// col 2 (apply_id) is the map key (0 -> "id[%lu] idPlunder[%lu] is
// error"; duplicate -> "id[%lu] Plunder[%lu] is exist"; wrong date
// -> "id[%lu] date[%lu] is error" - all three log and SKIP). The
// target columns are NOT read at load time (the record object is
// stored and its columns are read later by the msg builders).
bool CCountrySysMgr::LoadPlunderWarInfo(CMySQLClient* pDB) {
    if (!pDB) return false;
    if (!pDB->Query("SELECT * FROM cq_plunder_war")) {
        printf("[COUNTRY][DB] %s\n", pDB->GetError().c_str());
        return false; // ORIGINAL: null statement -> no error path?
                       // FUN_140019bc0 returns 0 only through this
                       // branch pattern; keep the conservative fail
    }
    const uint32_t dwToday = TimeGet3() % 100;
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 13) continue;
        const uint32_t dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        const uint32_t dwDate = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        if (dwDate != dwToday) {
            // ORIGINAL: "id[%lu] date[%lu] is error"
            printf("[COUNTRY] CCountrySysMgr::LoadPlunderWarInfo "
                   "id[%lu] date[%lu] is error\n",
                   (unsigned long)dwId, (unsigned long)dwDate);
            continue;
        }
        const uint32_t dwApplyId =
            (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        if (dwApplyId == 0) {
            // ORIGINAL: "id[%lu] idPlunder[%lu] is error"
            printf("[COUNTRY] CCountrySysMgr::LoadPlunderWarInfo "
                   "id[%lu] idPlunder[%lu] is error\n",
                   (unsigned long)dwId, (unsigned long)dwApplyId);
            continue;
        }
        if (m_mapPlunderWarToday.count(dwApplyId)) {
            // ORIGINAL: "id[%lu] Plunder[%lu] is exist"
            printf("[COUNTRY] CCountrySysMgr::LoadPlunderWarInfo "
                   "id[%lu] Plunder[%lu] is exist\n",
                   (unsigned long)dwId, (unsigned long)dwApplyId);
            continue;
        }
        PlunderWarRecord rec;
        rec.dwId = dwId;
        rec.dwApplyDate = dwDate;
        rec.dwApplyId = dwApplyId;
        for (int i = 0; i < 10; ++i) {
            const uint32_t t =
                (uint32_t)strtoul(row[3 + i].c_str(), nullptr, 10);
            rec.dwTargets[i] = t;
            if (t != 0) rec.byCount = (uint8_t)(i + 1);
        }
        m_mapPlunderWarToday[dwApplyId] = rec;
    }
    return true; // ORIGINAL: returns 1 on a valid statement
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

// ================= CCrossMsgLeagueInfo (40066) =================
// ORIGINAL Process FUN_140023c60 - see CountrySysMgr.h for the flow.
namespace {
std::string SqlQuote(const char* sz) {
    std::string r = "'";
    if (sz) for (; *sz; ++sz) {
        if (*sz == '\\' || *sz == '\'') r += '\\';
        r += *sz;
    }
    return r + "'";
}
} // namespace

bool CCountrySysMgr::OnProduceNewLeague(uint32_t dwIdServer,
        const LeagueInfoEntry& entry, LeagueInfoEntry& outReply) {
    // ORIGINAL FUN_140021c90 OnProduceNewLeague.
    // 1. DB handle gate (the 140021d20 error branch; log text
    //    unrecovered - DAT reference)
    if (!m_pDBPlunder) {
        printf("[COUNTRY] CCountrySysMgr::OnProduceNewLeague: "
               "no DB handle\n");
        return false;
    }
    // 3. duplicate gate: the original INSERT bounces off an
    //    existing (idserver, idleague) row into the
    //    FUN_1400232b0 completion path - NO reply, NO map
    //    changes. The map-level rule mirrors LoadLeagueInfo.
    const auto key = std::make_pair(dwIdServer, entry.dwIdLeague);
    if (m_leagues.count(key)) {
        printf("[COUNTRY] CCountrySysMgr::OnProduceNewLeague: "
               "server %u league %u is exist\n",
               dwIdServer, entry.dwIdLeague);
        return false;
    }
    // 2. INSERT - statement fields 1..7 =
    //    (idserver, idleague, amount, country_date,
    //    league_name, leader_name, title)
    char sql[640];
    snprintf(sql, sizeof sql,
        "INSERT INTO cq_league_info (idserver,idleague,amount,"
        "country_date,league_name,leader_name,title) VALUES "
        "(%u,%u,%u,%u,%s,%s,%s)",
        dwIdServer, entry.dwIdLeague, entry.dwAmount,
        entry.dwCountryDate, SqlQuote(entry.szName).c_str(),
        SqlQuote(entry.szLeader).c_str(),
        SqlQuote(entry.szTitle).c_str());
    if (!m_pDBPlunder->Query(sql)) {
        printf("[COUNTRY] CCountrySysMgr::OnProduceNewLeague: "
               "record insert error, server %u league %u\n",
               dwIdServer, entry.dwIdLeague);
        return false;
    }
    // 4. FUN_1400212d0: (server, league) map insert
    CountryLeague lg;
    // the original binds the new record object (its id lives in
    // the ORM); we mirror with LAST_INSERT_ID on the same session
    if (m_pDBPlunder->Query("SELECT LAST_INSERT_ID()")) {
        const auto& rowsLid = m_pDBPlunder->GetRows();
        if (!rowsLid.empty() && !rowsLid[0].empty())
            lg.dwId = (uint32_t)strtoul(rowsLid[0][0].c_str(),
                                        nullptr, 10);
    }
    lg.dwIdServer = dwIdServer;
    lg.dwIdLeague = entry.dwIdLeague;
    lg.dwAmount = entry.dwAmount;
    lg.dwCountryDate = entry.dwCountryDate;
    lg.strLeagueName = entry.szName;
    lg.strLeaderName = entry.szLeader;
    lg.strTitle = entry.szTitle;
    m_leagues[key] = lg;
    // 5. amount != 0 -> token map (+0x90) insert (FUN_14001a700)
    if (entry.dwAmount != 0)
        m_mapTokens[dwIdServer] = lg;
    // 6. FUN_14001c990(mgr, 7, {new league}, server): the
    //    mode-7 brick notify broadcasts with NO exclusion
    for (const auto& pkt :
         BuildBrickNotify(7, dwIdServer, {&m_leagues[key]}))
        if (m_fnBroadcast) m_fnBroadcast(pkt, 0);
    // 7. reply entry (usAction 2):
    //    +0  = FUN_140022c80 (field 2 idleague) +
    //           FUN_140022c20 (field 1 idserver)*1000000
    //    +4  = FUN_140022de0 (field 4 country_date)
    //    +0xc/+0x1c/+0x2c = FUN_140022ee0 strings. NOTE: Ghidra
    //    collapsed the register-passed field index of the three
    //    GetString calls; the 5/6/7 mapping follows the
    //    create-path column order at the identical entry
    //    offsets (league_name, leader_name, title).
    const CountryLeague& cur = m_leagues[key];
    outReply = LeagueInfoEntry{};
    outReply.dwIdLeague = (uint32_t)(cur.dwIdLeague +
        (uint64_t)dwIdServer * 1000000ULL);
    outReply.dwAmount = cur.dwCountryDate;
    CopyStr(outReply.szName, sizeof(outReply.szName), cur.strLeagueName);
    CopyStr(outReply.szLeader, sizeof(outReply.szLeader), cur.strLeaderName);
    CopyStr(outReply.szTitle, sizeof(outReply.szTitle), cur.strTitle);
    return true;
}

bool CCountrySysMgr::OnUpdateLeagueInfo(
        uint32_t dwIdServer, const LeagueInfoEntry& entry) {
    // ORIGINAL FUN_14001a0a0.
    // the +0x50 tree walk keyed by the server id
    auto it = m_leagues.lower_bound({dwIdServer, 0});
    if (it == m_leagues.end() || it->first.first != dwIdServer)
        return false; // silent fail in the original
    CountryLeague lg = it->second;
    const uint32_t dwOldLeague = it->first.second;
    // FUN_1400191f0: re-key the league side by the entry id
    m_leagues.erase(it);
    lg.dwIdLeague = entry.dwIdLeague;
    m_leagues[{dwIdServer, entry.dwIdLeague}] = lg;
    // FUN_140022f40(league, 6, entry+0x1c, 0): leader_name,
    // buffer only - NO commit yet
    // FUN_140022f40(league, 5, entry+0xc, 1): league_name +
    // commit (the commit flushes BOTH buffered fields)
    m_leagues[{dwIdServer, entry.dwIdLeague}].strLeaderName =
        entry.szLeader;
    m_leagues[{dwIdServer, entry.dwIdLeague}].strLeagueName =
        entry.szName;
    if (m_pDBPlunder) {
        char sql[640];
        // ORIGINAL: the commit flushes the record buffer via the
        // bound record (vcall+0x38) - the row keeps its OLD
        // idleague column; the re-key is in-memory only. Key the
        // UPDATE by the record pk when known, else by the old
        // (idserver, idleague).
        snprintf(sql, sizeof sql,
            "UPDATE cq_league_info SET league_name=%s,leader_name=%s"
            " WHERE %s",
            SqlQuote(m_leagues[{dwIdServer, entry.dwIdLeague}]
                     .strLeagueName.c_str()).c_str(),
            SqlQuote(m_leagues[{dwIdServer, entry.dwIdLeague}]
                     .strLeaderName.c_str()).c_str(),
            lg.dwId != 0
                ? (std::string("id=") + std::to_string(lg.dwId)).c_str()
                : (std::string("idserver=") + std::to_string(dwIdServer)
                   + " AND idleague=" +
                   std::to_string(dwOldLeague)).c_str());
        m_pDBPlunder->Query(sql);
    }
    return true;
}

// ================= CCrossMsgLeagueStr (40067) =================
bool CCountrySysMgr::OnLeagueStr(uint16_t usAction, uint32_t dwIdServer,
        uint32_t dwIdLeague, const char* szText) {
    // ORIGINAL FUN_14001bca0 (0) / FUN_14001c600 (1) /
    // FUN_14001c030 (2) - one shared shape.
    // ORIGINAL Process FUN_1400243f0: actions 0/1/2 only -
    // anything else never reaches a handler
    if (usAction > 2) return false;
    // empty string -> silent fail (all three handlers)
    if (!szText || !*szText) return false;
    // action 2 guards server!=0 && league!=0 first
    if (usAction == 2 && (dwIdServer == 0 || dwIdLeague == 0))
        return false;
    // the (server, league) record must exist
    auto it = m_leagues.find({dwIdServer, dwIdLeague});
    if (it == m_leagues.end()) return false;
    // field write + commit: 5 = league_name, 6 = leader_name,
    // 7 = title (FUN_140022f40 field ids)
    const char* szColumn = usAction == 0 ? "league_name"
                       : usAction == 1 ? "leader_name" : "title";
    if (usAction == 0) it->second.strLeagueName = szText;
    else if (usAction == 1) it->second.strLeaderName = szText;
    else it->second.strTitle = szText;
    if (m_pDBPlunder) {
        char sql[320];
        // ORIGINAL: FUN_140022f40 commits through the bound
        // record - key by the record pk when known, else by
        // (idserver, idleague)
        snprintf(sql, sizeof sql,
            "UPDATE cq_league_info SET %s=%s WHERE %s",
            szColumn, SqlQuote(szText).c_str(),
            it->second.dwId != 0
                ? (std::string("id=") +
                   std::to_string(it->second.dwId)).c_str()
                : (std::string("idserver=") +
                   std::to_string(dwIdServer) + " AND idleague=" +
                   std::to_string(dwIdLeague)).c_str());
        m_pDBPlunder->Query(sql);
    }
    // re-encode the SAME message and broadcast it:
    // actions 0/1 -> FUN_140018870(mgr, msg, 0) - everybody;
    // action 2 -> FUN_140018870(mgr, msg, dwIdServer) - the
    // source server is excluded from its own announce.
    if (m_fnBroadcast)
        m_fnBroadcast(EncodeLeagueStr(usAction, dwIdServer,
                    dwIdLeague, szText),
            usAction == 2 ? dwIdServer : 0);
    return true;
}

// ================= FUN_14001c990 OnBrickChange =================
std::vector<std::vector<uint8_t>> CCountrySysMgr::BuildBrickNotify(
        uint16_t usMode, uint32_t dwIdServer,
        const std::vector<const CountryLeague*>& vecLeagues) {
    // 1. FUN_14000d620(kernel, server): the country; -1 logs the
    //    "not exist" line but the notify still runs (the value
    //    only rides the chunk-flush queue target).
    if (!m_fnCountryOfServer ||
        m_fnCountryOfServer(dwIdServer) == 0xffffffffu) {
        // ORIGINAL: "OnBrickChange:socket %u of server %u not
        // exist" - the socket handle lives in the kernel; the
        // manager sees only the server id here
        printf("[COUNTRY] CCountrySysMgr::OnBrickChange:socket %u of "
               "server %u not exist\n", 0u, dwIdServer);
    }
    // 2. FUN_140019f80(mgr, server): the current league; header
    //    carries idleague (field 2) and country_date (field 4)
    uint32_t dwIdLeague = 0, dwCountryDate = 0;
    if (const CountryLeague* pCur = CurrentLeagueOf(dwIdServer)) {
        dwIdLeague = pCur->dwIdLeague;
        dwCountryDate = pCur->dwCountryDate;
    }
    // 3. entries: (idleague, amount) 8 bytes each; the 0x3ff
    //    append gate flushes the full brick and re-encodes the
    //    header (FUN_140024170 fail -> FUN_14000a0b0 ->
    //    FUN_1400240f0 again)
    std::vector<std::vector<uint8_t>> out;
    std::vector<LeagueBrickEntry> chunk;
    for (const CountryLeague* pLg : vecLeagues) {
        if (!pLg) {
            // null league -> the DAT_140058a00 error branch,
            // then LAB_14001d10d skips the entry
            printf("[COUNTRY] OnBrickChange: null league entry\n");
            continue;
        }
        if (0x10 + 8u * (chunk.size() + 1) > LEAGUE_INFO_WIRE_CAP) {
            out.push_back(EncodeLeagueBrick(usMode, dwIdLeague,
                dwCountryDate, chunk.data(), (uint16_t)chunk.size()));
            chunk.clear();
        }
        LeagueBrickEntry e;
        e.dwIdLeague = pLg->dwIdLeague;   // FUN_140022c80 field 2
        e.dwAmount = pLg->dwAmount;       // FUN_140022ce0 field 3
        chunk.push_back(e);
    }
    // 4. the final brick: FUN_140018870(mgr, brick, 0) - every
    //    country server, no exclusion
    out.push_back(EncodeLeagueBrick(usMode, dwIdLeague, dwCountryDate,
        chunk.data(), (uint16_t)chunk.size()));
    return out;
}

// ================= PLUNDER WAR: the flow bodies =================

void CCountrySysMgr::SetPlunderSinks(PlunderBroadcastFn fnBroadcast,
                                     PlunderTalkFn fnTalk,
                                     PlunderScheduleFn fnSchedule) {
    m_fnBroadcast = std::move(fnBroadcast);
    m_fnTalk = std::move(fnTalk);
    m_fnSchedule = std::move(fnSchedule);
}

// TimeGet modelings (conventions consistent with every observed
// use in the binary): TimeGet(3) = local yyyymmdd (used as %100 for
// the day-of-month and as the +0xc day snapshot), TimeGet(4) =
// local HHMM (divided by 100 for the hour gates), TimeGet(1) =
// local seconds since midnight (the countdown base).
// ORIGINAL tq::TimeGet (CQBase.dll @ 140b82df0), ported literally:
uint32_t CCountrySysMgr::TimeGet3() const {
    // case 3: (tm_year*100 + 1 + tm_mon)*100 + tm_mday
    // (NOTE: tm_year is year-1900 in the original, so the value is
    // e.g. 1261024 for 2026-10-24 - the quirk is preserved verbatim;
    // only the %100 day tail is consumed by the callers)
    if (m_bClockForTest) return m_dwClock3;
    const time_t t = time(nullptr);
    struct tm lt; localtime_r(&t, &lt);
    return (uint32_t)((lt.tm_year * 100 + 1 + lt.tm_mon) * 100 +
                      lt.tm_mday);
}
uint32_t CCountrySysMgr::TimeGet4() const {
    // case 4: (tm_hour*100 + tm_min)*100 + tm_sec = HHMMSS
    // (the gates divide it by 100 -> HHMM)
    if (m_bClockForTest) return m_dwClock4;
    const time_t t = time(nullptr);
    struct tm lt; localtime_r(&t, &lt);
    return (uint32_t)((lt.tm_hour * 100 + lt.tm_min) * 100 + lt.tm_sec);
}
uint32_t CCountrySysMgr::TimeGet1() const {
    // case 1: _time64(0) = the raw unix epoch seconds
    if (m_bClockForTest) return m_dwClock1;
    return (uint32_t)time(nullptr);
}

const CCountrySysMgr::PlunderWarRecord* CCountrySysMgr::FindPlunderWar(
        uint32_t dwApplyId) const {
    auto it = m_mapPlunderWarToday.find(dwApplyId);
    return it == m_mapPlunderWarToday.end() ? nullptr : &it->second;
}

// ---- FUN_14001abc0 (OnTimer, verbatim) + FUN_14001a400 ----------
void CCountrySysMgr::OnTimer() {
    const uint32_t dwNow3 = TimeGet3();
    if (m_dwPlunderDay != dwNow3) {           // mgr+0xc != TimeGet(3)
        m_dwPlunderDay = dwNow3;              // mgr+0xc = TimeGet(3)
        if (!m_mapPlunderWarToday.empty()) {
            // ORIGINAL log_InlineLogERROR(0x14005eb48):
            // "CCountrySysMgr::OnTimer m_mapPlunderWarToday is not empty"
            printf("[COUNTRY] CCountrySysMgr::OnTimer "
                   "m_mapPlunderWarToday is not empty\n");
        }
        m_mapPlunderWarToday.clear(); // every record released + erased
        m_nPlunderStatus = 0;         // mgr+0xd0 = 0
        // PlunderWarStatus(action 2, param 0) broadcast (Create at
        // 0x14005eb48-region, FUN_140023410 -> FUN_140018870)
        if (m_fnBroadcast)
            m_fnBroadcast(EncodePlunderWarStatus(2, 0), 0);
    }
    // ---- FUN_14001a400 (the status machine, runs every tick) ----
    const uint32_t dwNow4 = TimeGet4();
    const int nStatus = m_nPlunderStatus;     // mgr+0xd0
    if (nStatus == PLUNDER_IDLE) {
        if (m_dwPlunderSignupEnd <= dwNow4 / 100) { // +0xd8 gate
            if (m_mapPlunderWarToday.empty()) {
                m_nPlunderStatus = PLUNDER_ENDED;   // +0xd0 = 3
            } else {
                m_nPlunderStatus = PLUNDER_SIGNUP_ENDED; // = 1
                if (m_fnBroadcast)
                    m_fnBroadcast(EncodePlunderWarStatus(3, 0), 0);
                if (m_fnTalk)
                    m_fnTalk("STR_PLUNDER_WAR_SIGNUP_END");
            }
        }
    } else if (nStatus == PLUNDER_SIGNUP_ENDED) {
        const uint32_t dwStart = m_dwPlunderWarStart; // +0xd4
        if (dwStart <= dwNow4 / 100) {
            m_nPlunderStatus = PLUNDER_WAR;          // = 2
            const uint32_t dwEnd = m_dwPlunderWarEnd; // +0xdc
            // ORIGINAL countdown param (FUN_140023410 action 0):
            // (((end/100)*0x3c + (start/100)*0x28) - start) * 0x3c
            //   + (end % 100) * 0x3c + TimeGet(1)
            const uint32_t dwParam =
                (((dwEnd / 100) * 0x3c + (dwStart / 100) * 0x28) - dwStart)
                    * 0x3c + (dwEnd % 100) * 0x3c + TimeGet1();
            if (m_fnBroadcast)
                m_fnBroadcast(EncodePlunderWarStatus(0, dwParam), 0);
        }
    } else if (nStatus == PLUNDER_WAR) {
        if (m_dwPlunderWarEnd <= dwNow4 / 100) {      // +0xdc gate
            m_nPlunderStatus = PLUNDER_ENDED;         // = 3
            if (m_fnBroadcast)
                m_fnBroadcast(EncodePlunderWarStatus(1, 0), 0);
            // FUN_140018a40: release + erase every today-record
            // (the msg pointer argument only reaches it when the
            // broadcast succeeded; the clear happens regardless)
            m_mapPlunderWarToday.clear();
        }
    }
    // status 3 (PLUNDER_ENDED): no transition - the machine is done
    // for the day (only a day change or a new signup cycle resets it)
}

// ---- FUN_14001de20 (SignUpPlunderWar, verbatim) ------------------
// A helper for the shared target walk of both flows: appends every
// valid target (see the gate strings in the header) and returns the
// first valid target's league via ppFirstTargetLeague.
// The two flows log the SAME shape with flow-specific words
// (verified from the binary):
//   SignUp:   "...SignUpPlunderWar can not find league
//              idPlundered[%lu],  idPlunder[%lu]!"
//   Publish:  "...PublishSupportToken can not find league
//              idTarget[%lu],  idServerLeague[%lu]!"
// (double space before the second id in both, strings 0x14005f240 /
// 0x14005f4f0; the country-league variants are 0x14005f1e0 /
// 0x14005f490)
static bool CollectPlunderTargets(
        CCountrySysMgr& mgr, uint32_t dwSelfId, uint32_t dwCount,
        const uint32_t* pTargets, std::vector<uint32_t>& vecOut,
        const CountryLeague** ppFirstTargetLeague,
        const char* szFn, const char* szTargetLabel,
        const char* szSelfLabel) {
    for (uint32_t i = 0; i < dwCount; ++i) {
        const uint32_t dwTarget = pTargets[i];
        if (dwTarget == 0 || dwTarget == dwSelfId) continue;
        // FUN_140019f80(mgr, target/1000000): the target SERVER's
        // current league; null -> "can not find league ..."
        const CountryLeague* pLeague = mgr.CurrentLeagueOf(dwTarget / 1000000);
        if (!pLeague) {
            printf("[COUNTRY] CCountrySysMgr::%s can not find league "
                   "%s[%lu],  %s[%lu]!\n", szFn, szTargetLabel,
                   (unsigned long)dwTarget, szSelfLabel,
                   (unsigned long)dwSelfId);
            continue;
        }
        // FUN_140022c80(league): the target league's idleague must
        // equal target%1000000, else "is not country league ..."
        if (dwTarget % 1000000 != pLeague->dwIdLeague) {
            printf("[COUNTRY] CCountrySysMgr::%s is not country league "
                   "%s[%lu],  %s[%lu]!\n", szFn, szTargetLabel,
                   (unsigned long)dwTarget, szSelfLabel,
                   (unsigned long)dwSelfId);
            continue;
        }
        if (*ppFirstTargetLeague == nullptr)
            *ppFirstTargetLeague = pLeague;
        vecOut.push_back(dwTarget);
    }
    return true;
}

bool CCountrySysMgr::SignUpPlunderWar(uint32_t dwIdPlunder,
                                      uint32_t dwCount,
                                      const uint32_t* pTargets) {
    // 1. id == 0 || count < 1 -> "id is error idPlunder[%lu]!"
    if (dwIdPlunder == 0 || (int32_t)dwCount < 1) {
        printf("[COUNTRY] CCountrySysMgr::SignUpPlunderWar "
               "id is error idPlunder[%lu]!\n", (unsigned long)dwIdPlunder);
        return false;
    }
    // 2. status == 2 || 3 -> "status is error idPlunder[%lu]!"
    if (m_nPlunderStatus == PLUNDER_WAR ||
        m_nPlunderStatus == PLUNDER_ENDED) {
        printf("[COUNTRY] CCountrySysMgr::SignUpPlunderWar "
               "status is error idPlunder[%lu]!\n",
               (unsigned long)dwIdPlunder);
        return false;
    }
    // 3. duplicate apply_id -> "record is exist idPlunder[%lu]!"
    if (m_mapPlunderWarToday.count(dwIdPlunder)) {
        printf("[COUNTRY] CCountrySysMgr::SignUpPlunderWar "
               "record is exist idPlunder[%lu]!\n",
               (unsigned long)dwIdPlunder);
        return false;
    }
    // 4. FUN_140019e20(mgr, id/1000000, id%1000000): the attacker's
    //    own league must exist -> "can not find league idPlunder[%lu]!"
    if (!HasLeague(dwIdPlunder / 1000000, dwIdPlunder % 1000000)) {
        printf("[COUNTRY] CCountrySysMgr::SignUpPlunderWar "
               "can not find league idPlunder[%lu]!\n",
               (unsigned long)dwIdPlunder);
        return false;
    }
    // 5. the shared target walk
    std::vector<uint32_t> vecTargets;
    const CountryLeague* pFirstTarget = nullptr;
    CollectPlunderTargets(*this, dwIdPlunder, dwCount, pTargets,
                          vecTargets, &pFirstTarget,
                          "SignUpPlunderWar", "idPlundered", "idPlunder");
    // 6. no valid target (plVar14 == 0: silent fail) or an invalid
    //    final count -> "idPlunder[%lu] target num[%d] !"
    if (pFirstTarget == nullptr) return false;
    if (vecTargets.empty() || vecTargets.size() > PLUNDER_MAX_TARGETS) {
        printf("[COUNTRY] CCountrySysMgr::SignUpPlunderWar "
               "idPlunder[%lu] target num[%d] !\n",
               (unsigned long)dwIdPlunder, (int)vecTargets.size());
        return false;
    }
    // 7. INSERT the cq_plunder_war row (col 1 = TimeGet(3)%100 byte,
    //    col 2 = apply id, cols 3.. = targets) and commit
    {
        std::string sql = "INSERT INTO cq_plunder_war (apply_date,"
                          "apply_id";
        for (size_t i = 0; i < vecTargets.size(); ++i)
            sql += ",target_id_" + std::to_string(i + 1);
        sql += ") VALUES (" + std::to_string(TimeGet3() % 100) + "," +
               std::to_string(dwIdPlunder);
        for (uint32_t t : vecTargets) sql += "," + std::to_string(t);
        sql += ")";
        // ORIGINAL: table handle null -> "create record error, ...";
        // commit false -> "record insert error, ..."
        if (!m_pDBPlunder || !m_pDBPlunder->Query(sql)) {
            printf("[COUNTRY] CCountrySysMgr::SignUpPlunderWar "
                   "record insert error, idPlunder[%lu]!\n",
                   (unsigned long)dwIdPlunder);
            return false;
        }
    }
    // 8. map insert + the PlunderWarInfo(action 2) broadcast
    PlunderWarRecord rec;
    rec.dwApplyDate = TimeGet3() % 100;
    rec.dwApplyId = dwIdPlunder;
    rec.byCount = (uint8_t)vecTargets.size();
    for (size_t i = 0; i < vecTargets.size(); ++i)
        rec.dwTargets[i] = vecTargets[i];
    m_mapPlunderWarToday[dwIdPlunder] = rec;
    if (m_fnBroadcast)
        m_fnBroadcast(EncodePlunderWarInfo(2, dwIdPlunder,
                        vecTargets.data(), rec.byCount), 0);
    // 9. schedule set: the first valid target's league SERVER id
    //    (FUN_140022c20 = the record's idserver) then the attacker's
    //    league SERVER id (FUN_1400143c0 x2, verbatim order)
    if (m_fnSchedule) {
        m_fnSchedule(pFirstTarget->dwIdServer);
        m_setSchedulePushed.insert(pFirstTarget->dwIdServer);
        const CountryLeague* pAttacker =
            CurrentLeagueOf(dwIdPlunder / 1000000);
        if (pAttacker) {
            m_fnSchedule(pAttacker->dwIdServer);
            m_setSchedulePushed.insert(pAttacker->dwIdServer);
        }
    }
    // 10. STR_PLUNDER_WAR_TOMORROW_BEGIN system talk (0x961)
    if (m_fnTalk)
        m_fnTalk("STR_PLUNDER_WAR_TOMORROW_BEGIN");
    return true; // ORIGINAL: CONCAT71(...,1)
}

// ---- FUN_14001e700 (PublishSupportToken, verbatim) ---------------
bool CCountrySysMgr::PublishSupportToken(uint32_t dwIdServerLeague,
                                         uint32_t dwCount,
                                         const uint32_t* pTargets) {
    // 1. id == 0 || count < 1 || count > 10 ->
    //    "id is error idServerLeague[%lu], nAmount[%d]!"
    if (dwIdServerLeague == 0 || (int32_t)dwCount < 1 ||
        dwCount > PLUNDER_MAX_TARGETS) {
        printf("[COUNTRY] CCountrySysMgr::PublishSupportToken "
               "id is error idServerLeague[%lu], nAmount[%d]!\n",
               (unsigned long)dwIdServerLeague, (int)dwCount);
        return false;
    }
    // 2. status == 1 || 2 -> "status is error idServerLeague[%lu]!"
    if (m_nPlunderStatus == PLUNDER_SIGNUP_ENDED ||
        m_nPlunderStatus == PLUNDER_WAR) {
        printf("[COUNTRY] CCountrySysMgr::PublishSupportToken "
               "status is error idServerLeague[%lu]!\n",
               (unsigned long)dwIdServerLeague);
        return false;
    }
    // 3. the attacker league must exist (same string family)
    if (!HasLeague(dwIdServerLeague / 1000000,
                   dwIdServerLeague % 1000000)) {
        printf("[COUNTRY] CCountrySysMgr::PublishSupportToken "
               "can not find league idServerLeague[%lu]!\n",
               (unsigned long)dwIdServerLeague);
        return false;
    }
    // 4. the shared target walk
    std::vector<uint32_t> vecTargets;
    const CountryLeague* pFirstTarget = nullptr;
    CollectPlunderTargets(*this, dwIdServerLeague, dwCount, pTargets,
                          vecTargets, &pFirstTarget,
                          "PublishSupportToken", "idTarget",
                          "idServerLeague");
    if (pFirstTarget == nullptr) return false;
    if (vecTargets.empty() || vecTargets.size() > PLUNDER_MAX_TARGETS) {
        printf("[COUNTRY] CCountrySysMgr::PublishSupportToken "
               "idServerLeague[%lu] target num[%d] !\n",
               (unsigned long)dwIdServerLeague, (int)vecTargets.size());
        return false;
    }
    // 5. PlunderWarInfo(action 11) broadcast
    if (m_fnBroadcast)
        m_fnBroadcast(EncodePlunderWarInfo(11, dwIdServerLeague,
                        vecTargets.data(),
                        (uint8_t)vecTargets.size()), 0);
    // 6. schedule set, verbatim order: the first valid target's
    //    league SERVER id TWICE (FUN_140022fe0/FUN_140022c20 called
    //    back-to-back in the original), then the attacker's own
    //    SERVER id (FUN_1400143c0(obj, param_2/1000000))
    if (m_fnSchedule) {
        m_fnSchedule(pFirstTarget->dwIdServer);
        m_fnSchedule(pFirstTarget->dwIdServer);
        m_setSchedulePushed.insert(pFirstTarget->dwIdServer);
        m_fnSchedule(dwIdServerLeague / 1000000);
        m_setSchedulePushed.insert(dwIdServerLeague / 1000000);
    }
    // 7. STR_PUBLISH_SUPPORT_TOKEN_SUCCESS talk (0x961)
    if (m_fnTalk)
        m_fnTalk("STR_PUBLISH_SUPPORT_TOKEN_SUCCESS");
    return true; // ORIGINAL: CONCAT71(...,1)
}


} // namespace cross

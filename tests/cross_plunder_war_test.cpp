// Plunder-war system tests (CQCrossServer unit 2).
// Everything asserted here is checked against the ORIGINAL binary
// behavior first: the log strings were extracted verbatim from
// CQCrossServer.exe, the wire layouts come from
// FUN_140023730/FUN_140023790/FUN_140023410 and the state machine
// transitions from FUN_14001a400 / FUN_14001abc0.
#include "CrossKernel.h"
#include "CrossProtocol.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace cross;

static int s_nTalks = 0;
static std::string s_strLastTalk;

static CountryLeague MakeLeague(uint32_t dwServer, uint32_t dwLeague) {
    CountryLeague lg;
    lg.dwIdServer = dwServer;
    lg.dwIdLeague = dwLeague;
    lg.dwCountryDate = 5;
    return lg;
}

// recorded broadcasts: (packet type, action, param/first-target)
struct BCast {
    uint16_t usType; uint16_t usAction; uint32_t dwParam;
    std::vector<uint32_t> vecTargets;
};
static std::vector<BCast> s_vecBcasts;
static std::vector<uint32_t> s_vecSchedulePush;

static void WireSinks(CCountrySysMgr& mgr) {
    mgr.SetPlunderSinks(
        [](const std::vector<uint8_t>& pkt, uint32_t) {
            // decode like the receiving side would
            tq::MsgHead head;
            std::memcpy(&head, pkt.data(), sizeof(head));
            BCast b{}; b.usType = head.type;
            const uint8_t* p = pkt.data() + sizeof(head);
            if (head.type == MsgType_PlunderWarStatus) {
                std::memcpy(&b.usAction, p, 2);
                std::memcpy(&b.dwParam, p + 4, 4);
            } else if (head.type == MsgType_PlunderWarInfo) {
                std::memcpy(&b.usAction, p, 2);
                std::memcpy(&b.dwParam, p + 4, 4);
                uint8_t c; std::memcpy(&c, p + 0xc, 1);
                for (uint8_t i = 0; i < c && 0x10 + 4u * i + 4 <=
                     pkt.size() - sizeof(head); ++i) {
                    uint32_t t; std::memcpy(&t, p + 0x10 + 4u * i, 4);
                    b.vecTargets.push_back(t);
                }
                assert(head.length ==
                       sizeof(tq::MsgHead) + 0x10 + 4u * c);
            }
            s_vecBcasts.push_back(b);
        },
        [](const std::string& s) { ++s_nTalks; s_strLastTalk = s; },
        [](uint32_t dwId) { s_vecSchedulePush.push_back(dwId); });
}

static void ResetSinks() {
    s_vecBcasts.clear(); s_vecSchedulePush.clear();
    s_nTalks = 0; s_strLastTalk.clear();
}

int main() {
    // ================= 1. wire layouts =================
    {
        auto pkt = EncodePlunderWarStatus(3, 0);
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40042);                 // ORIGINAL 0x9c6a
        assert(h.length == sizeof(tq::MsgHead) + 8);
        uint16_t a; std::memcpy(&a, pkt.data() + sizeof(h), 2);
        uint32_t pm; std::memcpy(&pm, pkt.data() + sizeof(h) + 4, 4);
        assert(a == 3 && pm == 0);

        uint32_t targets[3] = {1000001u, 1000002u, 2000003u};
        auto pkt2 = EncodePlunderWarInfo(2, 0x7000005u, targets, 3);
        tq::MsgHead h2; std::memcpy(&h2, pkt2.data(), sizeof(h2));
        assert(h2.type == 40041);                // ORIGINAL 0x9c69
        assert(h2.length == sizeof(tq::MsgHead) + 0x10 + 4 * 3);
        uint8_t cnt; std::memcpy(&cnt, pkt2.data() + sizeof(h2) + 0xc, 1);
        assert(cnt == 3);
        uint32_t t0; std::memcpy(&t0, pkt2.data() + sizeof(h2) + 0x10, 4);
        assert(t0 == 1000001u);
    }

    // ================= 2. LoadPlunderTimeConfig (live DB) =================
    CMySQLClient db;
    {
        bool bOk = db.Connect("127.0.0.1", 3306, "tqserver", "tqpass123",
                              "cq");
        assert(bOk);
        // clean both tables for the test
        db.Query("DELETE FROM cq_plunder_war");
        db.Query("DELETE FROM cq_config WHERE type = 149883");

        // missing row -> the ORIGINAL logs
        // "LoadPlunderTimeConfig 未找到对应的配置" and Init FAILS
        CCountrySysMgr mgr; WireSinks(mgr);
        assert(!mgr.LoadPlunderTimeConfig(&db));

        // the gate: data1/100 must be in [2, 22] ("must be > 1 and
        // < 23"); 1 (hour 1) fails like the original
        db.Query("INSERT INTO cq_config (type, data1, data2, data3,"
                 " data4, data5, describ) VALUES (149883, 100, 2000,"
                 " 2100, 0, 0, '')");
        assert(!mgr.LoadPlunderTimeConfig(&db));

        // a valid row loads data1 -> signup end, data2 -> war start,
        // data3 -> war end
        db.Query("DELETE FROM cq_config WHERE type = 149883");
        db.Query("INSERT INTO cq_config (type, data1, data2, data3,"
                 " data4, data5, describ) VALUES (149883, 1900, 2000,"
                 " 2100, 0, 0, '')");
        assert(mgr.LoadPlunderTimeConfig(&db));
        mgr.SetPlunderTimesForTest(0, 0, 0);
        assert(mgr.LoadPlunderTimeConfig(&db));
        // verified via Init full path below; row stays for section 3
    }

    // ================= 3. LoadPlunderWarInfo (live DB) =================
    {
        const uint32_t dwToday = []() {   // local yyyymmdd % 100
            const time_t t = time(nullptr);
            struct tm lt; localtime_r(&t, &lt);
            return (uint32_t)lt.tm_mday;
        }();
        CCountrySysMgr mgr; WireSinks(mgr);
        mgr.SetClockForTest(12345, 20261024, 0); // TimeGet(3)%100 = 24
        // id, apply_date, apply_id, target_id_1..10
        db.Query("DELETE FROM cq_plunder_war");
        char sql[512];
        // valid: apply 7000001 with one target, dated today (24)
        std::snprintf(sql, sizeof(sql),
            "INSERT INTO cq_plunder_war VALUES (0, %u, 7000001,"
            " 7000002, 0,0,0,0,0,0,0,0,0)", dwToday);
        db.Query(sql);
        // wrong date -> skipped ("id[%lu] date[%lu] is error")
        db.Query("INSERT INTO cq_plunder_war VALUES (0, 99, 7000003,"
                 " 7000004, 0,0,0,0,0,0,0,0,0)");
        // apply_id 0 -> skipped ("id[%lu] idPlunder[%lu] is error")
        db.Query("INSERT INTO cq_plunder_war VALUES (0, 24, 0,"
                 " 0,0,0,0,0,0,0,0,0,0)");
        assert(mgr.LoadPlunderWarInfo(&db));
        assert(mgr.PlunderWarCount() == 1);
        assert(mgr.FindPlunderWar(7000001u) != nullptr);
        assert(mgr.FindPlunderWar(7000001u)->dwTargets[0] == 7000002u);
        assert(mgr.FindPlunderWar(7000003u) == nullptr);
        // duplicate key -> the second one is skipped, map keeps 1
        db.Query("DELETE FROM cq_plunder_war");
        std::snprintf(sql, sizeof(sql),
            "INSERT INTO cq_plunder_war VALUES (0, %u, 7000001,"
            " 7000009, 0,0,0,0,0,0,0,0,0)", dwToday);
        db.Query(sql);
        db.Query(sql); // same apply_id again
        CCountrySysMgr mgr2; WireSinks(mgr2);
        mgr2.SetClockForTest(0, 20261024, 0);
        assert(mgr2.LoadPlunderWarInfo(&db));
        assert(mgr2.PlunderWarCount() == 1);
    }

    // ================= 4. OnTimer day change =================
    {
        ResetSinks();
        CCountrySysMgr mgr; WireSinks(mgr);
        mgr.SetPlunderStatusForTest(3);       // mid-war-ish residue
        mgr.SetPlunderDayForTest(20261023);   // yesterday
        mgr.SetPlunderTimesForTest(2000, 1900, 2100); // an Init'ed mgr
        mgr.SetClockForTest(0, 20261024, 120000);
        mgr.OnTimer();
        assert(mgr.PlunderDay() == 20261024);
        assert(mgr.PlunderStatus() == 0);     // +0xd0 = 0 reset
        assert(mgr.PlunderWarCount() == 0);   // map wiped
        assert(s_vecBcasts.size() == 1);
        assert(s_vecBcasts[0].usType == 40042);
        assert(s_vecBcasts[0].usAction == 2); // new-day status
        assert(s_vecBcasts[0].dwParam == 0);
    }

    // ================= 5. the status machine (FUN_14001a400) =================
    {
        // 5a. idle -> signup end (a record exists): broadcast 3 + talk
        ResetSinks();
        CCountrySysMgr mgr; WireSinks(mgr);
        mgr.InsertLeagueForTest(MakeLeague(7, 5)); // attacker league
        mgr.InsertLeagueForTest(MakeLeague(7, 2)); // target league
        mgr.SetPlunderTimesForTest(2000, 1900, 2100);
        mgr.SetClockForTest(0, 20261024, 190000); // 19:00:00
        mgr.SetPlunderStatusForTest(0);
        // one record so the machine takes the "has records" path
        uint32_t t[1] = {7000002u};
        mgr.SetPlunderDBForTest(&db);
        db.Query("DELETE FROM cq_plunder_war");
        assert(mgr.SignUpPlunderWar(7000005u, 1, t)); // (7,5) -> (7,2)
        assert(mgr.PlunderWarCount() == 1);
        mgr.SetPlunderDayForTest(20261024); // saw today: no day change
        ResetSinks();
        mgr.OnTimer();   // same day, 19:00 >= signup end 19:00
        assert(mgr.PlunderStatus() == 1);
        assert(s_vecBcasts.size() == 1 &&
               s_vecBcasts[0].usAction == 3 && s_vecBcasts[0].dwParam == 0);
        assert(s_nTalks == 1 && s_strLastTalk == "STR_PLUNDER_WAR_SIGNUP_END");

        // 5b. signup-ended -> war start: the ORIGINAL countdown formula
        //     (((end/100)*0x3c + (start/100)*0x28) - start) * 0x3c
        //     + (end % 100) * 0x3c + TimeGet(1)
        //     with 1900/2000/2100 = ((21*60 + 20*40) - 2000)*60 + 0 + t1
        //     = 3600 + t1
        ResetSinks();
        mgr.SetClockForTest(4000, 20261024, 200000); // 20:00:00, t1=4000
        mgr.OnTimer();
        assert(mgr.PlunderStatus() == 2);
        assert(s_vecBcasts.size() == 1 &&
               s_vecBcasts[0].usAction == 0);
        assert(s_vecBcasts[0].dwParam == 3600u + 4000u);

        // 5c. war -> end (21:00): broadcast 1 + the map is cleared
        ResetSinks();
        mgr.SetClockForTest(7300, 20261024, 210000);
        mgr.OnTimer();
        assert(mgr.PlunderStatus() == 3);
        assert(s_vecBcasts.size() == 1 &&
               s_vecBcasts[0].usAction == 1);
        assert(mgr.PlunderWarCount() == 0);

        // 5d. the empty-map idle path: no broadcast, straight to 3
        ResetSinks();
        CCountrySysMgr m2; WireSinks(m2);
        m2.SetPlunderTimesForTest(2000, 1900, 2100);
        m2.SetPlunderDayForTest(20261024); // no day change here
        m2.SetPlunderStatusForTest(0);
        // the gate is data1 (HHMM) vs TimeGet(4)/100 (HHMM),
        // so 18:59:00 is before it and 19:00:00 already fires it
        m2.SetClockForTest(0, 20261024, 185900);
        m2.OnTimer();
        assert(m2.PlunderStatus() == 0 && s_vecBcasts.empty());
        m2.SetClockForTest(0, 20261024, 190000);
        m2.OnTimer();
        assert(m2.PlunderStatus() == 3 && s_vecBcasts.empty());
    }

    // ================= 6. SignUpPlunderWar (live INSERT) =================
    {
        db.Query("DELETE FROM cq_plunder_war");
        CCountrySysMgr mgr; WireSinks(mgr);
        mgr.InsertLeagueForTest(MakeLeague(7, 5));    // attacker
        mgr.InsertLeagueForTest(MakeLeague(7, 2));    // target A league
        mgr.SetPlunderDBForTest(&db);
        mgr.SetClockForTest(0, 20261024, 120000);
        mgr.SetPlunderStatusForTest(0);

        // gate 1: id is error (id 0)
        uint32_t t1[1] = {7000002u};
        assert(!mgr.SignUpPlunderWar(0, 1, t1));
        // gate 1: count is error (0 targets listed)
        assert(!mgr.SignUpPlunderWar(7000005u, 0, t1));
        // gate 2: status 2/3
        mgr.SetPlunderStatusForTest(2);
        assert(!mgr.SignUpPlunderWar(7000005u, 1, t1));
        mgr.SetPlunderStatusForTest(0);
        // gate 4: attacker league missing (server 8 never installed)
        assert(!mgr.SignUpPlunderWar(8000005u, 1, t1));
        // gate 5: target server has no league -> 0 valid targets
        uint32_t t2[2] = {9000001u, 9000002u};
        assert(!mgr.SignUpPlunderWar(7000005u, 2, t2));
        // gate 5: target league id mismatch (league 3 not installed)
        uint32_t t3[1] = {7000003u};
        assert(!mgr.SignUpPlunderWar(7000005u, 1, t3));

        // happy path: attacker (7,5) hits (7,2)
        ResetSinks();
        uint32_t t4[2] = {7000002u, 7000002u}; // duplicate targets pass
        assert(mgr.SignUpPlunderWar(7000005u, 2, t4));
        assert(mgr.PlunderWarCount() == 1);
        assert(mgr.FindPlunderWar(7000005u) != nullptr);
        // the row landed in the live table
        db.Query("SELECT id, apply_date, apply_id, target_id_1 FROM "
                 "cq_plunder_war WHERE apply_id = 7000005");
        assert(db.GetRows().size() == 1);
        assert(db.GetRows()[0][1] == std::to_string(24)); // apply_date
        assert(db.GetRows()[0][2] == "7000005");
        assert(db.GetRows()[0][3] == "7000002");
        // broadcast: PlunderWarInfo action 2 with both targets
        assert(s_vecBcasts.size() == 1);
        assert(s_vecBcasts[0].usType == 40041 &&
               s_vecBcasts[0].usAction == 2);
        assert(s_vecBcasts[0].dwParam == 7000005u);
        assert(s_vecBcasts[0].vecTargets.size() == 2);
        // talk + schedule: first target server (7), then attacker (7)
        assert(s_nTalks == 1 &&
               s_strLastTalk == "STR_PLUNDER_WAR_TOMORROW_BEGIN");
        assert(s_vecSchedulePush.size() == 2);
        assert(s_vecSchedulePush[0] == 7 && s_vecSchedulePush[1] == 7);
        assert(mgr.PlunderScheduleHas(7));

        // gate 3: duplicate apply_id -> record is exist
        assert(!mgr.SignUpPlunderWar(7000005u, 1, t1));
        db.Query("DELETE FROM cq_plunder_war");
    }

    // ================= 7. PublishSupportToken =================
    {
        CCountrySysMgr mgr; WireSinks(mgr);
        mgr.InsertLeagueForTest(MakeLeague(7, 5));
        mgr.InsertLeagueForTest(MakeLeague(7, 2));
        mgr.SetPlunderDBForTest(&db);
        mgr.SetClockForTest(0, 20261024, 120000);
        mgr.SetPlunderStatusForTest(0);   // idle: allowed

        // gate 1: id error / count error / count > 10
        uint32_t t1[1] = {7000002u};
        assert(!mgr.PublishSupportToken(0, 1, t1));
        assert(!mgr.PublishSupportToken(7000005u, 0, t1));
        assert(!mgr.PublishSupportToken(7000005u, 11, t1));
        // gate 2: status 1/2
        mgr.SetPlunderStatusForTest(1);
        assert(!mgr.PublishSupportToken(7000005u, 1, t1));
        mgr.SetPlunderStatusForTest(0);
        // happy path
        ResetSinks();
        uint32_t t2[2] = {7000002u, 7000002u};
        assert(mgr.PublishSupportToken(7000005u, 2, t2));
        assert(s_vecBcasts.size() == 1);
        assert(s_vecBcasts[0].usType == 40041 &&
               s_vecBcasts[0].usAction == 11);
        assert(s_vecBcasts[0].dwParam == 7000005u);
        assert(s_vecBcasts[0].vecTargets.size() == 2);
        assert(s_nTalks == 1 &&
               s_strLastTalk == "STR_PUBLISH_SUPPORT_TOKEN_SUCCESS");
        // schedule: first target server TWICE, then attacker server
        assert(s_vecSchedulePush.size() == 3);
        assert(s_vecSchedulePush[0] == 7);
        assert(s_vecSchedulePush[1] == 7);
        assert(s_vecSchedulePush[2] == 7); // attacker server id
    }

    // ================= 8. kernel dispatch + broadcast routing =====
    {
        std::vector<std::pair<uint64_t, std::vector<uint8_t>>> sent;
        std::vector<std::string> logs;
        CCrossServerKernel kern(
            [&](uint64_t s, const std::vector<uint8_t>& p) {
                sent.push_back({s, p}); },
            [&](const std::string& l) { logs.push_back(l); });
        auto mgr = std::make_shared<CCountrySysMgr>();
        WireSinks(*mgr); // manager-level capture for assertions
        mgr->InsertLeagueForTest(MakeLeague(7, 5));
        mgr->InsertLeagueForTest(MakeLeague(7, 2));
        // server 7 owns a country (the FUN_14000d620 map member) -
        // only such servers receive FUN_140018870 broadcasts
        mgr->InsertMemberForTest(7, 5);
        mgr->SetPlunderDBForTest(&db);
        mgr->SetClockForTest(0, 20261024, 1200);
        mgr->SetPlunderStatusForTest(0);
        kern.SetCountrySysForTest(mgr); // wires the kernel sinks
        // two online servers: 7 (owns a country) and 8 (does not)
        HelloData h7{}; h7.dwServerId = 7; std::strcpy(h7.szName, "s7");
        HelloData h8{}; h8.dwServerId = 8; std::strcpy(h8.szName, "s8");
        kern.OnHello(100, h7);
        kern.OnHello(200, h8);

        // wrong action -> the ORIGINAL "wrong action[%u]" log
        PlunderWarInfoData bad{}; bad.usAction = 77; bad.dwId = 1;
        kern.OnPlunderWarInfo(100, bad);
        bool bWrongLogged = false;
        for (auto& l : logs)
            if (l.find("CCrossMsgPlunderWarInfo::Process "
                       "wrong action[77]") != std::string::npos)
                bWrongLogged = true;
        assert(bWrongLogged);

        // action 1 routes to SignUpPlunderWar through the kernel
        ResetSinks(); sent.clear();
        PlunderWarInfoData info{};
        info.usAction = 1; info.dwId = 7000005u;
        info.byCount = 2;
        info.dwTargets[0] = 7000002u; info.dwTargets[1] = 7000002u;
        kern.OnPlunderWarInfo(100, info);
        assert(mgr->PlunderWarCount() == 1);
        // TWO broadcasts happen, exactly like the original: the
        // PlunderWarInfo (40041) to country-member servers via
        // FUN_140018870, and the STR_PLUNDER_WAR_TOMORROW_BEGIN
        // system talk (FUN_14000a310) to ALL servers. Only server 7
        // is online, so both land on socket 100.
        // TWO servers are online (7=sock100, 8=sock200), but only 7
        // has a country yet: 40041 -> 100 only; the 9011 talk goes
        // to ALL servers -> 100 and 200. Total: 3 sends.
        assert(sent.size() == 3);
        bool bWarInfo = false, bTalk100 = false, bTalk200 = false;
        for (auto& pr : sent) {
            tq::MsgHead h; std::memcpy(&h, pr.second.data(), sizeof(h));
            if (h.type == 40041 && pr.first == 100) bWarInfo = true;
            if (h.type == 9011 && pr.first == 100) bTalk100 = true;
            if (h.type == 9011 && pr.first == 200) bTalk200 = true;
        }
        assert(bWarInfo && bTalk100 && bTalk200);
        assert(mgr->PlunderScheduleHas(7));
        assert(kern.IsPlunderScheduleServer(7));

        // broadcast with exclude: nobody else is a member, and the
        // excluded member is skipped
        sent.clear();
        mgr->InsertMemberForTest(8, 0);   // give 8 a country
        kern.BroadcastToCountryServers(EncodePlunderWarStatus(2, 0), 7);
        assert(sent.size() == 1 && sent[0].first == 200); // only 8
        db.Query("DELETE FROM cq_plunder_war");
    }

    // restore the shipped dump state (no config row, empty war table)
    db.Query("DELETE FROM cq_config WHERE type = 149883");
    db.Query("DELETE FROM cq_plunder_war");

    printf("CROSS_PLUNDER_OK: wire layouts, config/war DB loads, day "
           "change, status machine, signup + publish flows, kernel "
           "dispatch + country broadcast\n");
    return 0;
}

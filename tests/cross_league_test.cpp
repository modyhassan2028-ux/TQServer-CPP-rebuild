// League message tests (CQCrossServer unit 3) - CCrossMsgLeagueInfo
// (40066, FUN_140023c60/140021c90/14001a0a0), CCrossMsgLeagueStr
// (40067, FUN_1400243f0/14001bca0/c600/c030) and the LeagueBrick
// notify FUN_14001c990. Wire layouts come from FUN_140023a40/a90/b60
// (LeagueInfo), FUN_140024350/3b0 (LeagueStr), FUN_1400240f0/140024170
// (LeagueBrick).
#include "CrossKernel.h"
#include "CrossProtocol.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace cross;

// recorded broadcasts with their exclusion (FUN_140018870 3rd arg)
struct BCast { uint16_t usType; uint16_t usModeOrAction;
               uint32_t dwIdLeague; uint32_t dwDateOrServer;
               uint32_t dwExclude; uint16_t usCount;
               std::vector<uint32_t> vecIds, vecVals;
               std::vector<LeagueInfoEntry> vecInfo; };
static std::vector<BCast> s_vecB;

static void WireSinks(CCountrySysMgr& mgr) {
    mgr.SetPlunderSinks(
        [](const std::vector<uint8_t>& pkt, uint32_t dwEx) {
            tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
            BCast b{}; b.usType = h.type; b.dwExclude = dwEx;
            const uint8_t* p = pkt.data() + sizeof(h);
            if (h.type == MsgType_LeagueBrick) { // 40065
                std::memcpy(&b.usModeOrAction, p, 2);
                std::memcpy(&b.dwIdLeague, p + 4, 4);
                std::memcpy(&b.dwDateOrServer, p + 8, 4);
                std::memcpy(&b.usCount, p + 0xc, 2);
                assert(h.length == sizeof(tq::MsgHead) + 0x10 +
                       8u * b.usCount);
                for (uint16_t i = 0; i < b.usCount; ++i) {
                    uint32_t id, v;
                    std::memcpy(&id, p + 0x10 + 8u * i, 4);
                    std::memcpy(&v, p + 0x14 + 8u * i, 4);
                    b.vecIds.push_back(id); b.vecVals.push_back(v);
                }
            } else if (h.type == MsgType_LeagueStr) { // 40067
                std::memcpy(&b.usModeOrAction, p, 2);
                std::memcpy(&b.dwDateOrServer, p + 4, 4);
                std::memcpy(&b.dwIdLeague, p + 8, 4);
                assert(h.length == sizeof(tq::MsgHead) + 0x1c);
            } else if (h.type == MsgType_LeagueInfo) { // 40066
                std::memcpy(&b.usModeOrAction, p, 2);
                std::memcpy(&b.usCount, p + 2, 2);
                assert(h.length == sizeof(tq::MsgHead) + 4 +
                       0x3cu * b.usCount);
                for (uint16_t i = 0; i < b.usCount; ++i) {
                    LeagueInfoEntry e{};
                    std::memcpy(&e, p + 4 + 0x3cu * i, sizeof(e));
                    b.vecInfo.push_back(e);
                }
            }
            s_vecB.push_back(b);
        }, {}, {});
}

static std::string Q(const char* q) { return q; }

int main() {
    CMySQLClient db;
    assert(db.Connect("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    // clean only the rows this test owns (server 55/56, leagues 77..)
    db.Query("DELETE FROM cq_league_info WHERE idserver IN (55,56)");

    // ============ 1. LeagueInfo wire (FUN_140023a40/a90) ============
    {
        LeagueInfoEntry e{};
        e.dwIdLeague = 77; e.dwAmount = 12; e.dwCountryDate = 345;
        std::strncpy(e.szName, "Pharaohs", 15);
        std::strncpy(e.szLeader, "Mody", 15);
        std::strncpy(e.szTitle, "Kingdom", 15);
        auto pkt = EncodeLeagueInfo(2, &e, 1);
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40066);            // ORIGINAL 0x9c62
        assert(h.length == sizeof(tq::MsgHead) + 4 + 0x3c);
        uint16_t a, c; const uint8_t* p = pkt.data() + sizeof(h);
        std::memcpy(&a, p, 2); std::memcpy(&c, p + 2, 2);
        assert(a == 2 && c == 1);
        uint32_t id, amt, date;
        std::memcpy(&id, p + 4, 4); std::memcpy(&amt, p + 8, 4);
        std::memcpy(&date, p + 0xc, 4);
        assert(id == 77 && amt == 12 && date == 345);
        assert(std::strcmp((const char*)p + 0x10, "Pharaohs") == 0);
        assert(std::strcmp((const char*)p + 0x20, "Mody") == 0);
        assert(std::strcmp((const char*)p + 0x30, "Kingdom") == 0);
    }

    // ============ 2. OnProduceNewLeague (FUN_140021c90) ============
    CCountrySysMgr mgr; WireSinks(mgr);
    mgr.SetPlunderDBForTest(&db);
    {
        LeagueInfoEntry e{};
        e.dwIdLeague = 77; e.dwAmount = 12; e.dwCountryDate = 345;
        std::strncpy(e.szName, "Pharaohs", 15);
        std::strncpy(e.szLeader, "Mody", 15);
        std::strncpy(e.szTitle, "Kingdom", 15);
        LeagueInfoEntry r{};
        assert(mgr.OnProduceNewLeague(55, e, r));
        // reply entry: id = league + server*1000000 (u32 wrap),
        // +4 = country_date, strings per fields 5/6/7
        assert(r.dwIdLeague == 77u + 55u * 1000000u);
        assert(r.dwAmount == 345);
        assert(std::strcmp(r.szName, "Pharaohs") == 0);
        assert(std::strcmp(r.szLeader, "Mody") == 0);
        assert(std::strcmp(r.szTitle, "Kingdom") == 0);
        // the league landed in the manager maps
        assert(mgr.HasLeague(55, 77));
        assert(mgr.TokenLowerBound(55)->dwIdLeague == 77);
        assert(mgr.LeagueName(55, 77) == "Pharaohs");
        // LeaderTitle = the TITLE field (FUN_14001a6d0 port)
        assert(mgr.LeaderTitle(55, 77) == "Kingdom");
        // and in the DB
        db.Query("SELECT idleague,amount,country_date,league_name,"
                 "leader_name,title FROM cq_league_info"
                 " WHERE idserver=55 AND idleague=77");
        auto rows = db.GetRows();
        assert(rows.size() == 1);
        assert(rows[0][0] == "77" && rows[0][1] == "12" &&
               rows[0][2] == "345" && rows[0][3] == "Pharaohs" &&
               rows[0][4] == "Mody" && rows[0][5] == "Kingdom");
        // mode-7 brick notify went out: FUN_14001c990(mgr, 7, ..)
        assert(s_vecB.size() == 1);
        assert(s_vecB[0].usType == 40065);
        assert(s_vecB[0].usModeOrAction == 7);
        assert(s_vecB[0].dwIdLeague == 77);   // current league id
        assert(s_vecB[0].dwDateOrServer == 345); // country_date
        assert(s_vecB[0].usCount == 1);
        assert(s_vecB[0].vecIds == std::vector<uint32_t>{77});
        assert(s_vecB[0].vecVals == std::vector<uint32_t>{12});
        assert(s_vecB[0].dwExclude == 0);     // no exclusion
        s_vecB.clear();
        // duplicate: the original bounces off the existing record
        LeagueInfoEntry r2{};
        assert(!mgr.OnProduceNewLeague(55, e, r2));
        assert(s_vecB.empty());              // NO reply, NO notify
    }

    // ============ 3. OnUpdateLeagueInfo (FUN_14001a0a0) ============
    {
        LeagueInfoEntry e{}; // re-key league 77 -> 78 + new strings
        e.dwIdLeague = 78;
        std::strncpy(e.szName, "NewPharaohs", 15);
        std::strncpy(e.szLeader, "NewMody", 15);
        assert(mgr.OnUpdateLeagueInfo(55, e));
        assert(!mgr.HasLeague(55, 77));
        assert(mgr.HasLeague(55, 78));
        assert(mgr.LeagueName(55, 78) == "NewPharaohs");
        // title rides along unchanged by the re-key
        assert(mgr.LeaderTitle(55, 78) == "Kingdom");
        // DB UPDATE flushed both buffered fields
        // the re-key is IN-MEMORY: the DB row keeps idleague=77
        // (the original commits via the bound record only)
        db.Query("SELECT league_name,leader_name FROM cq_league_info"
                 " WHERE idserver=55 AND idleague=77");
        auto rows = db.GetRows();
        assert(rows.size() == 1);
        assert(rows[0][0] == "NewPharaohs" && rows[0][1] == "NewMody");
        // missing server stays silent
        LeagueInfoEntry e2{}; e2.dwIdLeague = 99;
        assert(!mgr.OnUpdateLeagueInfo(999, e2));
    }

    // ============ 4. OnLeagueStr (FUN_14001bca0/c600/c030) ============
    {
        // empty string -> silent fail
        assert(!mgr.OnLeagueStr(0, 55, 78, ""));
        assert(s_vecB.empty());
        // action 0: league_name; broadcast with NO exclusion
        assert(mgr.OnLeagueStr(0, 55, 78, "RaBand"));
        assert(mgr.LeagueName(55, 78) == "RaBand");
        assert(s_vecB.size() == 1 && s_vecB[0].usType == 40067);
        assert(s_vecB[0].usModeOrAction == 0);
        assert(s_vecB[0].dwExclude == 0);
        // action 1: leader_name
        assert(mgr.OnLeagueStr(1, 55, 78, "RaLeader"));
        assert(s_vecB.size() == 2 && s_vecB[1].usModeOrAction == 1);
        assert(s_vecB[1].dwExclude == 0);
        // action 2: title; guards server!=0 && league!=0, and the
        // rebroadcast EXCLUDES the source server
        assert(!mgr.OnLeagueStr(2, 0, 78, "x"));
        assert(!mgr.OnLeagueStr(2, 55, 0, "x"));
        assert(mgr.OnLeagueStr(2, 55, 78, "RaTitle"));
        assert(s_vecB.size() == 3 && s_vecB[2].usModeOrAction == 2);
        assert(s_vecB[2].dwExclude == 55);
        // title now visible through the accessor
        assert(mgr.LeaderTitle(55, 78) == "RaTitle");
        // unknown action: silent
        assert(!mgr.OnLeagueStr(5, 55, 78, "x"));
        assert(s_vecB.size() == 3);
        s_vecB.clear();
        // DB carries the three fields
        db.Query("SELECT league_name,leader_name,title FROM"
                 " cq_league_info WHERE idserver=55 AND idleague=77");
        auto rows = db.GetRows();
        assert(rows.size() == 1);
        assert(rows[0][0] == "RaBand" && rows[0][1] == "RaLeader"
               && rows[0][2] == "RaTitle");
    }

    // ============ 5. BuildBrickNotify chunking (FUN_14001c990) ====
    {
        std::vector<const CountryLeague*> vec;
        std::vector<CountryLeague> keep(130);
        for (uint32_t i = 0; i < 130; ++i) {
            keep[i].dwIdServer = 56; keep[i].dwIdLeague = 1000 + i;
            keep[i].dwAmount = i * 3;
            vec.push_back(&keep[i]);
        }
        auto pkts = mgr.BuildBrickNotify(3, 56, vec);
        // 125 entries fit one brick; 5 spill into a second one
        assert(pkts.size() == 2);
        LeagueBrickData b1{};
        std::memcpy(&b1, pkts[0].data() + sizeof(tq::MsgHead),
                    sizeof(b1));
        assert(b1.usMode == 3 && b1.usCount == 125);
        assert(b1.dwIdLeague == 0);   // server 56 has no current league
        LeagueBrickData b2{};
        std::memcpy(&b2, pkts[1].data() + sizeof(tq::MsgHead),
                    sizeof(b2));
        assert(b2.usCount == 5);
        assert(b2.entries[0].dwIdLeague == 1125);
        assert(b2.entries[0].dwAmount == 125 * 3);
        // null entry -> skipped, not fatal
        auto pkts2 = mgr.BuildBrickNotify(5, 56, {nullptr});
        assert(pkts2.size() == 1);
    }

    // ============ 6. kernel end-to-end ==============================
    {
        std::vector<std::pair<uint64_t, BCast>> vecSent;
        std::vector<std::pair<uint64_t, std::vector<uint8_t>>> wire;
        CCrossServerKernel kern(
            [&](uint64_t s, const std::vector<uint8_t>& p) {
                wire.push_back({s, p}); });
        auto pmgr = std::make_shared<CCountrySysMgr>();
        WireSinks(*pmgr);
        pmgr->SetPlunderDBForTest(&db);
        kern.SetCountrySysForTest(pmgr);
        // the hub's broadcast rule (FUN_140018870): only servers
        // with a country in the member map receive country
        // traffic - the ORIGINAL registers the game servers as
        // members too
        pmgr->InsertMemberForTest(55, 3);
        // server 55 registers (socket 100), then produces a league
        HelloData hello{}; hello.dwServerId = 55;
        std::strcpy(hello.szName, "EG-Server");
        kern.OnHello(100, hello);
        // a second member of the same country (socket 101) - the
        // reply excludes the SOURCE server, so 101 receives it
        HelloData hello2{}; hello2.dwServerId = 56;
        std::strcpy(hello2.szName, "EG-Server2");
        kern.OnHello(101, hello2);
        pmgr->InsertMemberForTest(56, 3);
        LeagueInfoEntry e{};
        e.dwIdLeague = 88; e.dwAmount = 4; e.dwCountryDate = 21;
        std::strncpy(e.szName, "Kings", 15);
        wire.clear(); // drop the ServerUp from the hello
        kern.OnLeagueInfo(100, 0, e);
        // first the mode-7 brick (exclude 0 -> both members), then
        // the reply (action 2) EXCLUDING the source server 55:
        // only socket 101 (server 56) receives it
        assert(wire.size() == 3);
        tq::MsgHead h;
        std::memcpy(&h, wire[0].second.data(), sizeof(h));
        assert(h.type == 40065);            // brick to member 1
        assert(wire[0].first == 100);
        std::memcpy(&h, wire[1].second.data(), sizeof(h));
        assert(h.type == 40065);            // brick to member 2
        assert(wire[1].first == 101);
        std::memcpy(&h, wire[2].second.data(), sizeof(h));
        assert(h.type == 40066);            // the reply
        assert(wire[2].first == 101);       // NOT the source socket
        const uint8_t* p = wire[2].second.data() + sizeof(h);
        uint16_t a, c;
        std::memcpy(&a, p, 2); std::memcpy(&c, p + 2, 2);
        assert(a == 2 && c == 1);
        LeagueInfoEntry re{};
        std::memcpy(&re, p + 4, sizeof(re));
        assert(re.dwIdLeague == 88u + 55u * 1000000u);
        // LeagueStr through the kernel: action 1 = leader_name,
        // rebroadcast with NO exclusion -> both members
        wire.clear();
        LeagueStrData d{}; d.usAction = 1;
        d.dwIdServer = 55; d.dwIdLeague = 88;
        std::strcpy(d.szText, "KingLeader");
        kern.OnLeagueStr(100, d);
        assert(wire.size() == 2);
        std::memcpy(&h, wire[0].second.data(), sizeof(h));
        assert(h.type == 40067);
        assert(wire[0].first == 100 && wire[1].first == 101);
        // unknown action -> silent
        LeagueStrData bad{}; bad.usAction = 9;
        kern.OnLeagueStr(100, bad);
    }

    db.Query("DELETE FROM cq_league_info WHERE idserver IN (55,56)");
    puts("cross_league_test: ALL OK");
    return 0;
}

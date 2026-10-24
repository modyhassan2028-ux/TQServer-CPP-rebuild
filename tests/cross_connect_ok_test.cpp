// ProcessServerConnectOK test (FUN_14001ade0): when server 55
// (member of country 1) registers, the country gets the 5-part
// state dump. Server 99 is NOT a member -> nothing.
#include "CountrySysMgr.h"
#include "CrossProtocol.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace cross;

static std::vector<std::pair<uint16_t,
    std::vector<uint8_t>>> s_vecSent; // type, pkt
static std::map<uint16_t, size_t> s_nCount;

static void Sink(const std::vector<uint8_t>& p, uint32_t) {
    tq::MsgHead h; std::memcpy(&h, p.data(), sizeof(h));
    s_vecSent.push_back({h.type, p});
    s_nCount[h.type]++;
}

int main() {
    CCountrySysMgr mgr;
    mgr.SetPlunderSinks(Sink, nullptr, nullptr);
    mgr.SetCountryOfServerFn([](uint32_t id) {
        return id == 55 ? 1u : 0xffffffffu; });
    // leagues: server 55 owns two, server 56 owns one
    CountryLeague a; a.dwIdServer = 55; a.dwIdLeague = 77;
    a.dwAmount = 3; a.dwCountryDate = 345;
    a.strLeagueName = "Pharaohs"; a.strLeaderName = "Mody";
    a.strTitle = "Kingdom";
    mgr.InsertLeagueForTest(a);
    CountryLeague b; b.dwIdServer = 55; b.dwIdLeague = 78;
    b.dwAmount = 5; b.dwCountryDate = 345;
    b.strLeagueName = "Nile"; b.strLeaderName = "Ali";
    b.strTitle = "Legion";
    mgr.InsertLeagueForTest(b);
    CountryLeague c; c.dwIdServer = 56; c.dwIdLeague = 88;
    c.dwAmount = 9; c.dwCountryDate = 222;
    c.strLeagueName = "Kings"; c.strLeaderName = "Sara";
    c.strTitle = "Empire";
    mgr.InsertLeagueForTest(c);
    // today-war: id 5, targets
    CCountrySysMgr::PlunderWarRecord war;
    war.dwId = 5; war.dwTargets[0] = 11; war.dwTargets[9] = 22;
    mgr.InsertWarForTest(5, war);

    // NOT a member: FUN_14000d620 == -1 -> NOTHING
    mgr.ProcessServerConnectOK(99);
    assert(s_vecSent.empty());

    // member: the 5-part dump reaches the country
    mgr.ProcessServerConnectOK(55);
    auto Get = [&](uint16_t t) -> const std::vector<uint8_t>* {
        for (auto& pr : s_vecSent) if (pr.first == t) return &pr.second;
        return nullptr; };
    // (a) mode-1 brick 40065
    auto* pBrick = Get(40065);
    assert(pBrick);
    {
        const uint8_t* p = pBrick->data() + sizeof(tq::MsgHead);
        uint16_t usMode; std::memcpy(&usMode, p, 2);
        assert(usMode == 1);
        // header: mode@0, idleague@4, country_date@8, count@0xc;
        // entries (idleague, amount) of server 55 only from +0x10
        uint32_t idlg, cdt;
        std::memcpy(&idlg, p + 4, 4); std::memcpy(&cdt, p + 8, 4);
        // the header league: FUN_140019f80 = the server's
        // CURRENT league = (55,77) in the map order
        assert(idlg == 77 && cdt == 345);
        uint32_t id0, amt0; std::memcpy(&id0, p + 0x10, 4);
        std::memcpy(&amt0, p + 0x14, 4);
        assert(id0 == 77 && amt0 == 3);
        uint32_t id1; std::memcpy(&id1, p + 0x18, 4);
        assert(id1 == 78);
    }
    // (b) LeagueRank 40036: 3 entries {idleague, idserver,
    // amount, name@0x14, leader@0x24}
    auto* pRank = Get(40036);
    assert(pRank);
    {
        const uint8_t* p = pRank->data() + sizeof(tq::MsgHead);
        uint16_t usCount; std::memcpy(&usCount, p + 4, 2);
        assert(usCount == 3);
        uint32_t a0, a1, a2;
        std::memcpy(&a0, p + 8, 4);
        std::memcpy(&a1, p + 8 + 0x2c, 4);
        std::memcpy(&a2, p + 8 + 2 * 0x2c, 4);
        // map order: (55,77), (55,78), (56,88)
        assert(a0 == 77 && a1 == 78 && a2 == 88);
        assert(std::strcmp((const char*)p + 8 + 0x14, "Pharaohs")==0);
        assert(std::strcmp((const char*)p + 8 + 0x24, "Mody")==0);
    }
    // (c) LeagueInfo 40066 action 2: only server 56's league
    auto* pInfo = Get(40066);
    assert(pInfo);
    {
        const uint8_t* p = pInfo->data() + sizeof(tq::MsgHead);
        uint16_t usAction, usCount;
        std::memcpy(&usAction, p, 2);
        std::memcpy(&usCount, p + 2, 2);
        assert(usAction == 2 && usCount == 1);
        auto re = DecodeLeagueInfoEntry(p + 4);
        assert(re.dwIdLeague == 88u + 56u * 1000000u);
        assert(re.dwAmount == 9);
        assert(std::strcmp(re.szName, "Kings") == 0);
        assert(std::strcmp(re.szTitle, "Empire") == 0);
    }
    // (d) plunder: mode-3 announce + per-war mode-0
    assert(s_nCount[40041] == 2);
    auto* pAnn = Get(40041);
    {
        const uint8_t* p = pAnn->data() + sizeof(tq::MsgHead);
        uint16_t usMode; std::memcpy(&usMode, p, 2);
        uint32_t dwId; std::memcpy(&dwId, p + 4, 4);
        assert(usMode == 3 && dwId == 0);
        // the second 40041 is the war: mode 0, id 5, 10 targets
        const std::vector<uint8_t>* pWar = nullptr;
        size_t nSeen = 0;
        for (auto& pr : s_vecSent) if (pr.first == 40041) {
            if (++nSeen == 2) pWar = &pr.second; }
        const uint8_t* q = pWar->data() + sizeof(tq::MsgHead);
        uint16_t m2; std::memcpy(&m2, q, 2);
        uint32_t wid; std::memcpy(&wid, q + 4, 4);
        uint8_t cnt; std::memcpy(&cnt, q + 0xc, 1);
        uint32_t t0, t9; std::memcpy(&t0, q + 0x10, 4);
        std::memcpy(&t9, q + 0x10 + 36, 4);
        assert(m2 == 0 && wid == 5 && cnt == 10);
        assert(t0 == 11 && t9 == 22);
    }
    // (e) LeagueList 40040 action 0: ids from lower_bound(55)
    auto* pList = Get(40040);
    assert(pList);
    {
        const uint8_t* p = pList->data() + sizeof(tq::MsgHead);
        uint16_t usAction; std::memcpy(&usAction, p, 2);
        uint8_t byFlag; std::memcpy(&byFlag, p + 2, 1);
        uint16_t usCount; std::memcpy(&usCount, p + 4, 2);
        assert(usAction == 0 && byFlag == 1 && usCount == 3);
        uint32_t id0; std::memcpy(&id0, p + 8, 4);
        assert(id0 == 77);   // from lower_bound({55,0})
    }
    puts("cross_connect_ok_test: ALL OK");
    return 0;
}

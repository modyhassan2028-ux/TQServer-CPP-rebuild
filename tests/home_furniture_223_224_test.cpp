// cq_action 223/224 (home furniture NPC placement + count check) tests.
// 223 verified against FUN_14013b950 jump idx22 (0x14013cf17): custom int
// parser (>= 4 numbers), gates map/type, per-NPC x,y pair consumption,
// passability check, MoveTo + gmlog/ActionNpcChangePos, always true.
// 224 verified against idx23 (0x14013d604): sscanf "%u %d %d" >= 2,
// count(map,type) >= (v3 ? v3 : 1).
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "MapManager.h"
#include "Npc.h"
#include "MySQLClient.h"
#include "User.h"
#include <cassert>
#include <cstdio>
#include <memory>

static CDialogEngine::Node MkNode(uint32_t id, uint32_t type, uint32_t data,
                                  const char* param) {
    CDialogEngine::Node n;
    n.dwId = id; n.dwType = type; n.dwData = data; n.strParam = param;
    return n;
}

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "root", "", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    CMapManager::Instance().LoadMapsFromDb(pDB);
    auto up = std::make_shared<CUser>(999401); up->SetName("HomeOwner");
    CUser& u = *up;

    // synthetic home map + two furniture npcs of raw type 4
    auto pHome = CMapManager::Instance().GetOrCreate(10001, "Home");
    uint32_t dwN1 = 800001, dwN2 = 800002;
    CNpcManager::Instance().AddNpcForTest(std::make_shared<CNpc>(
        dwN1, "Table", (CNpc::Type)4, 10001, 10, 10));
    CNpcManager::Instance().AddNpcForTest(std::make_shared<CNpc>(
        dwN2, "Chair", (CNpc::Type)4, 10001, 11, 11));
    // a different-type npc on the same map must not be touched
    uint32_t dwN3 = 800003;
    CNpcManager::Instance().AddNpcForTest(std::make_shared<CNpc>(
        dwN3, "Statue", (CNpc::Type)25, 10001, 12, 12));
    auto n1 = CNpcManager::Instance().GetNpc(dwN1);
    auto n2 = CNpcManager::Instance().GetNpc(dwN2);
    auto n3 = CNpcManager::Instance().GetNpc(dwN3);
    assert(n1 && n2 && n3);

    // ---- too few numbers -> false (0xcca) ----
    auto nd1 = MkNode(9500001, 223, 0, "10001 4");
    assert(!CGameAction::ProcessActionUser(up, &nd1));
    printf("[ok] <4 numbers -> false\n");

    // ---- zero map / bad type -> false (0xcd2) ----
    auto nd2 = MkNode(9500002, 223, 0, "0 4 34 39");
    assert(!CGameAction::ProcessActionUser(up, &nd2));
    auto nd3 = MkNode(9500003, 223, 0, "10001 0 34 39");
    assert(!CGameAction::ProcessActionUser(up, &nd3));
    printf("[ok] map 0 / type <= 0 -> false\n");

    // ---- no matching type -> false (0x14070f9f0) ----
    auto nd4 = MkNode(9500004, 223, 0, "10001 99 34 39");
    assert(!CGameAction::ProcessActionUser(up, &nd4));
    printf("[ok] no npc of type -> false\n");

    // ---- real placement: two pairs move two npcs, type 25 untouched ----
    auto nd5 = MkNode(9500005, 223, 0, "10001 4 55 50 55 47");
    assert(CGameAction::ProcessActionUser(up, &nd5));
    assert(n1->GetX() == 55 && n1->GetY() == 50);
    assert(n2->GetX() == 55 && n2->GetY() == 47);
    assert(n3->GetX() == 12 && n3->GetY() == 12); // different type kept
    assert(n1->GetMapId() == 10001 && n2->GetMapId() == 10001);
    printf("[ok] two pairs -> both npcs moved\n");

    // ---- extra npcs stay when pairs run out ----
    n1->MoveTo(10001, 10, 10);
    auto nd6 = MkNode(9500006, 223, 0, "10001 4 20 20");
    assert(CGameAction::ProcessActionUser(up, &nd6));
    assert(n1->GetX() == 20 && n1->GetY() == 20); // first npc, first pair
    assert(n2->GetX() == 55 && n2->GetY() == 47); // no pair left
    printf("[ok] pairs exhausted -> extra npc untouched\n");

    // ---- %user_home_id substitution works through the parser ----
    u.m_dwHomeMapId = 10001;
    auto nd7 = MkNode(9500007, 223, 0, "%user_home_id 4 30 30");
    assert(CGameAction::ProcessActionUser(up, &nd7));
    assert(n1->GetX() == 30 && n1->GetY() == 30);
    printf("[ok] %%user_home_id substituted\n");

    // ---- 224: count >= 1 default, explicit count, and zero-count map ----
    auto nd8 = MkNode(9500008, 224, 0, "%user_home_id 4");
    assert(CGameAction::ProcessActionUser(up, &nd8));  // 2 >= 1
    auto nd9 = MkNode(9500009, 224, 0, "%user_home_id 4 3");
    assert(!CGameAction::ProcessActionUser(up, &nd9)); // 2 < 3
    auto nd10 = MkNode(9500010, 224, 0, "%user_home_id 4 2");
    assert(CGameAction::ProcessActionUser(up, &nd10)); // 2 >= 2
    auto nd11 = MkNode(9500011, 224, 0, "10001 77");
    assert(!CGameAction::ProcessActionUser(up, &nd11)); // no type 77
    printf("[ok] 224 count checks (default/explicit/absent)\n");

    // ---- 224: sscanf needs >= 2 (0xd17) ----
    auto nd12 = MkNode(9500012, 224, 0, "10001");
    assert(!CGameAction::ProcessActionUser(up, &nd12));
    printf("[ok] 224 <2 values -> false\n");

    // ---- invalid point: pair consumed, npc not moved (synthetic map:
    //      CGameMap IsPassable on synthetic grids - verify with whatever
    //      the synthetic grid reports) ----
    printf("ALL 223/224 FURNITURE TESTS PASSED\n");
    return 0;
}

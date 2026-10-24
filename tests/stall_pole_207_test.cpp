// cq_action 207 stall/pole branches test. ORIGINAL FUN_14013c75a:
// record field 4 == 10 -> stall mgr (FUN_140087ed0, class-0x16 record)
// vcall+0x328(npcId) -> bool; == 46 -> root mgr, FUN_14008b330 gate
// ([mapgroup+0x77c]): class-0x25 record vcall+0x78(npcId) (gate on)
// or class-0x1c record vcall+0x40(npcId) (gate off) -> bool.
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "MapManager.h"
#include "Npc.h"
#include "MySQLClient.h"
#include "StallPole.h"
#include "User.h"
#include <cassert>
#include <cstdio>
#include <memory>

static CDialogEngine::Node MkNode(uint32_t id, uint32_t type) {
    CDialogEngine::Node n;
    n.dwId = id; n.dwType = type; n.dwData = 0; n.strParam = "";
    return n;
}

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    CMapManager::Instance().LoadMapsFromDb(pDB);
    auto up = std::make_shared<CUser>(999501); up->SetName("StallOp");

    // dialog stall npc (field 4 = 10) and two pole npcs (field 4 = 46)
    auto spStall = std::make_shared<CNpc>(810001, "Stall",
                                         (CNpc::Type)10, 1000, 50, 50);
    auto spPole = std::make_shared<CNpc>(810002, "Pole",
                                        (CNpc::Type)46, 1000, 60, 60);
    spStall->m_dwNpcType = 10; // record field 4 (raw type)
    spPole->m_dwNpcType = 46;
    CNpcManager::Instance().AddNpcForTest(spStall);
    CNpcManager::Instance().AddNpcForTest(spPole);
    up->m_stDialogCtx.dwId = 810001;

    // ---- type 10: stall removal via vcall+0x328 ----
    auto nd = MkNode(9600001, 207);
    assert(!CGameAction::ProcessActionUser(up, &nd)); // not registered
    CStallManager::Instance().RegisterStall(810001);
    assert(CStallManager::Instance().HasStall(810001));
    assert(CGameAction::ProcessActionUser(up, &nd));  // removed -> true
    assert(!CStallManager::Instance().HasStall(810001));
    assert(!CGameAction::ProcessActionUser(up, &nd)); // already gone
    printf("[ok] 207 type 10 stall remove + second-call false\n");

    // ---- type 46, gate off ([mapgroup+0x77c] = 0): class 0x1c ----
    up->m_stDialogCtx.dwId = 810002;
    CPoleManager::Instance().SetPoleMode(false);
    assert(!CGameAction::ProcessActionUser(up, &nd)); // 0x1c registry empty
    CPoleManager::Instance().RegisterPole(810002, false); // class 0x1c
    assert(CPoleManager::Instance().HasPole(810002, false));
    assert(CGameAction::ProcessActionUser(up, &nd));     // vcall+0x40
    assert(!CPoleManager::Instance().HasPole(810002, false));
    printf("[ok] 207 type 46 gate off -> class-0x1c remove\n");

    // ---- type 46, gate on: class 0x25 registry answers instead ----
    CPoleManager::Instance().SetPoleMode(true);           // +0x77c byte
    CPoleManager::Instance().RegisterPole(810002, true);  // class 0x25
    CPoleManager::Instance().RegisterPole(810002, false); // class 0x1c too
    assert(CPoleManager::Instance().HasPole(810002, true));
    assert(CGameAction::ProcessActionUser(up, &nd));     // vcall+0x78
    assert(!CPoleManager::Instance().HasPole(810002, true));
    // the 0x1c registration is untouched by the gate-on removal
    assert(CPoleManager::Instance().HasPole(810002, false));
    printf("[ok] 207 type 46 gate on -> class-0x25 remove only\n");

    // ---- gate on, only 0x1c registered -> false (wrong class) ----
    auto spPole2 = std::make_shared<CNpc>(810003, "Pole2",
                                         (CNpc::Type)46, 1000, 61, 61);
    spPole2->m_dwNpcType = 46;
    CNpcManager::Instance().AddNpcForTest(spPole2);
    up->m_stDialogCtx.dwId = 810003;
    CPoleManager::Instance().RegisterPole(810003, false);
    assert(!CGameAction::ProcessActionUser(up, &nd)); // gate on, no 0x25
    printf("[ok] 207 type 46 gate/class mismatch -> false\n");

    printf("ALL 207 STALL/POLE TESTS PASSED\n");
    return 0;
}

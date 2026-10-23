// cq_action 205 (delete NPC), 207 (npc-type op), 208 (clone npc)
// fidelity tests. Objdump-verified against the 6159 MsgServer
// FUN_14013b950 subcases 0xcd/0xcf/0xd0.
#include "Account.h"
#include "Npc.h"
#include "Dialog.h"
#include "GameAction.h"
#include "MsgNpcInfo.h"
#include "User.h"
#include "MapManager.h"
#include "MySQLClient.h"
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
    assert(CMapManager::Instance().GetMap(1002));

    auto up = std::make_shared<CUser>(999003); up->SetName("NpcOps");
    CUser& u = *up;

    // ---- spawn a dyna npc via 2007 (real row shape) ----
    auto ndSpawn = MkNode(9100501, 2007, 0,
        "TestDyna 0 0 9999 1 5566 1002 50 60 0 100 0 0 0 0 0 0 0 0 0 0 0 0 0 x");
    assert(CGameAction::ProcessActionUser(up, &ndSpawn));
    auto pNpc = CNpcManager::Instance().GetNpc(5566);
    assert(pNpc && pNpc->m_bDyna);
    u.m_stDialogCtx.dwId = 5566;

    // ---- 205 data=0: delete the dialog npc (real rows all use data=0) ----
    auto nd = MkNode(9100701, 205, 0, "");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(!CNpcManager::Instance().GetNpc(5566)); // erased from registry
    assert(u.m_stDialogCtx.dwId == 0);            // ORIGINAL [pUser+0x10]=0
    printf("[ok] 205 data=0 deletes dialog npc + clears ctx\n");

    // ---- 205 with no dialog npc and data=0: CHECKF false ----
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] 205 without dialog npc -> false\n");

    // ---- 205 data!=0: purge all NPCs of that TYPE ----
    auto ndSpawn2 = MkNode(9100502, 2007, 0,
        "PurgeMe 0 0 7777 7 6677 1002 55 55 0 50 0 0 0 0 0 0 0 0 0 0 0 0 0 x");
    assert(CGameAction::ProcessActionUser(up, &ndSpawn2));
    assert(CNpcManager::Instance().GetNpc(6677));
    u.m_stDialogCtx.dwId = 6677; // dialog points at it too - also purged
    nd = MkNode(9100702, 205, 7, ""); // purge type 7
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(!CNpcManager::Instance().GetNpc(6677));
    printf("[ok] 205 data=7 purged all type-7 npcs\n");

    // ---- 205 data!=0 with no match: exhausted walk -> true ----
    nd = MkNode(9100703, 205, 999, "");
    assert(CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] 205 no-match walk -> true\n");

    // ---- 208: clone the dialog npc to a new id/map/pos ----
    // template: spawn dyna 7788 with a task0 and ownerid
    auto ndSpawn3 = MkNode(9100503, 2007, 0,
        "HouseMan 0 0 4242 3 7788 1002 40 40 0 80 0 0 0 0 0 0 0 0 0 0 0 0 0 x");
    assert(CGameAction::ProcessActionUser(up, &ndSpawn3));
    auto pTmpl = CNpcManager::Instance().GetNpc(7788);
    assert(pTmpl && pTmpl->m_dwOwnerid == 0);
    u.m_stDialogCtx.dwId = 7788;
    nd = MkNode(9100704, 208, 0, "815 1002 44 46");
    assert(!CGameAction::ProcessActionUser(up, &nd)); // ORIGINAL returns false
    auto pClone = CNpcManager::Instance().GetNpc(815);
    assert(pClone);
    assert(pClone->m_bDyna);
    assert(pClone->GetName() == pTmpl->GetName());
    assert(pClone->m_dwLookface == pTmpl->m_dwLookface);
    assert(pClone->m_dwNpcType == pTmpl->m_dwNpcType);
    assert(pClone->GetMapId() == 1002 && pClone->GetX() == 44 && pClone->GetY() == 46);
    printf("[ok] 208 cloned dialog npc -> 815 (dyna, inherited)\n");

    // ---- 208 bad param count: false ----
    nd = MkNode(9100705, 208, 0, "815 1002");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    // ---- 208 without dialog npc: CHECKF false ----
    u.m_stDialogCtx.dwId = 0;
    nd = MkNode(9100706, 208, 0, "816 1002 44 46");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] 208 rejection paths\n");

    // ---- 207: dialog npc required; type dispatch ----
    u.m_stDialogCtx.dwId = 0;
    nd = MkNode(9100707, 207, 0, "");
    assert(!CGameAction::ProcessActionUser(up, &nd)); // pRole QueryObj gate
    u.m_stDialogCtx.dwId = 815; // type 3 npc -> ORIGINAL 0x14013c8b9 false
    nd = MkNode(9100708, 207, 0, "");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] 207 gates + unmatched-type false\n");

    printf("ALL NPC OPS 205/207/208 TESTS PASSED\n");
    return 0;
}

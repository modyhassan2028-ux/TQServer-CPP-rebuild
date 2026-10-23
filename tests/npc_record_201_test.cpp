// cq_action type 201 (FUN_14013ba1e) fidelity test: dyna-npc record ops.
// Semantics objdump-verified against the 6159 MsgServer:
//   sscanf "%s %s %s %u %d" (>=3): field, op, operand, npcId, flag
//   target = npcId ? that npc : dialog npc; must be a DynaNpc record
//   ownerid/ownertype (=/==), lookface (=/== + NpcInfo broadcast),
//   datastr (=/==, 15-char col 0x16), data0..3 (=,+=,==,<,<=,>,>=,
//   "accept" re-parse), life (24 =), maxlife (25 =), npc 820 gmlog.
#include "Account.h"
#include "Npc.h"
#include "Dialog.h"
#include "GameAction.h"
#include "MsgDialog.h"
#include "MsgTalk.h"
#include "User.h"
#include "UserManager.h"
#include "MsgAction.h"
#include "GroupSystem.h"
#include "PlayerMagic.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "Item.h"
#include "UserTask.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <memory>
#include <vector>

static CDialogEngine::Node MkNode(uint32_t id, uint32_t type, const char* param) {
    CDialogEngine::Node n;
    n.dwId = id; n.dwType = type; n.dwData = 0; n.strParam = param;
    return n;
}

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "root", "", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    printf("[ok] cq_action loaded\n");
    CMapManager::Instance().LoadMapsFromDb(pDB);
    assert(CMapManager::Instance().GetMap(1002));

    auto up = std::make_shared<CUser>(999002); up->SetName("Rec201");
    CUser& u = *up;

    // ---- spawn a dynamic npc (type 2007 path sets m_bDyna) ----
    // REAL cq_action 2007 param shape: name f2..f9 ... f13 task0
    const uint32_t NPC_ID = 5566;
    CDialogEngine::Node ndSpawn = MkNode(9100501, 2007,
        "TestDyna 0 0 9999 1 5566 1002 50 60 0 100 0 0 0 0 0 0 0 0 0 0 0 0 0 x");
    assert(CGameAction::ProcessActionUser(up, &ndSpawn));
    auto pNpc = CNpcManager::Instance().GetNpc(NPC_ID);
    assert(pNpc && pNpc->m_bDyna); // ORIGINAL record byte +0x68 set on spawn
    assert(pNpc->m_nMaxLife == 100); // spawn col 0x19 life -> field 25
    printf("[ok] 2007 spawn -> DynaNpc %u on map %u\n", pNpc->GetId(), pNpc->GetMapId());

    // dialog context points at the spawned npc (npcId==0 targets it)
    u.m_stDialogCtx.dwId = NPC_ID;

    // ---- data0: set / equality ----
    auto nd = MkNode(9100601, 201, "data0 = 55");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_dwDynData[0] == 55);
    nd = MkNode(9100602, 201, "data0 == 55");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100603, 201, "data0 == 54");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] data0 = / == semantics\n");

    // ---- data1: += ----
    nd = MkNode(9100604, 201, "data1 = 10");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100605, 201, "data1 += 5");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100606, 201, "data1 == 15");
    assert(CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] data1 += semantics\n");

    // ---- comparisons ----
    nd = MkNode(9100607, 201, "data1 < 16");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100608, 201, "data1 <= 15");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100609, 201, "data1 > 15");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100610, 201, "data1 >= 14");
    assert(CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] data <, <=, >, >= semantics\n");

    // ---- "accept": re-parse value from the player's dialog input ----
    u.m_stDialogCtx.strInput = "77";
    nd = MkNode(9100611, 201, "data2 = accept");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_dwDynData[2] == 77);
    printf("[ok] accept operand re-parses ctx input\n");

    // ---- npcId 4th token targets that npc regardless of dialog ctx ----
    u.m_stDialogCtx.dwId = 1234; // dialog npc no longer the target
    nd = MkNode(9100612, 201, "data0 = 91");
    assert(!CGameAction::ProcessActionUser(up, &nd)); // ctx npc 1234 unknown
    char sz[64]; snprintf(sz, sizeof(sz), "data0 = 91 %u", NPC_ID);
    nd = MkNode(9100613, 201, sz);
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_dwDynData[0] == 91);
    printf("[ok] npcId targeting + unknown-npc false\n");
    u.m_stDialogCtx.dwId = NPC_ID; // restore dialog npc for the rest

    // ---- ownerid / ownertype (fields 1, 2) ----
    nd = MkNode(9100614, 201, "ownerid = 4242");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_dwOwnerid == 4242);
    nd = MkNode(9100615, 201, "ownerid == 4242");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100616, 201, "ownertype = 7");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100617, 201, "ownertype == 7");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100618, 201, "ownertype == 6");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] ownerid / ownertype ops\n");

    // ---- lookface (field 3) ----
    nd = MkNode(9100619, 201, "lookface = 9999");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_dwLookface == 9999);
    nd = MkNode(9100620, 201, "lookface == 9999");
    assert(CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] lookface ops\n");

    // ---- datastr (field 22, 15-char col 0x16) ----
    nd = MkNode(9100621, 201, "datastr = hellonpc");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(strncmp(pNpc->m_strDatastr.c_str(), "hellonpc", 15) == 0);
    nd = MkNode(9100622, 201, "datastr == hellonpc");
    assert(CGameAction::ProcessActionUser(up, &nd));
    nd = MkNode(9100623, 201, "datastr == nope");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] datastr ops\n");

    // ---- life (24) / maxlife (25) ----
    nd = MkNode(9100624, 201, "life = 5000");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_nLife == 5000);
    nd = MkNode(9100625, 201, "maxlife = 9000");
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(pNpc->m_nMaxLife == 9000);
    nd = MkNode(9100626, 201, "life == 5000"); // life only supports "="
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] life / maxlife set + op gate\n");

    // ---- data digit out of 0..3 -> false (ORIGINAL 0xc07f) ----
    nd = MkNode(9100627, 201, "data4 = 1");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    // unknown field -> false
    nd = MkNode(9100628, 201, "nosuchfield = 1");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    // bad op on ownerid -> false
    nd = MkNode(9100629, 201, "ownerid += 1");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] digit/field/op rejection paths\n");

    // ---- non-dyna npc (static spawn) is rejected ----
    auto pStatic = CNpcManager::Instance().SpawnDynamic(7788, "Static",
        12, 0, 1002, 40, 40, 0);
    assert(pStatic);
    pStatic->m_bDyna = false;
    u.m_stDialogCtx.dwId = 7788;
    nd = MkNode(9100630, 201, "data0 = 1");
    assert(!CGameAction::ProcessActionUser(up, &nd)); // "is not DynaNpc"
    printf("[ok] non-dyna rejection\n");

    // ---- bad param count (ORIGINAL log at 0xa9c) ----
    nd = MkNode(9100631, 201, "data0");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] bad param count rejected\n");

    printf("ALL NPC RECORD 201 TESTS PASSED\n");
    return 0;
}

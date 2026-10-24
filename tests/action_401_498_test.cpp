// cq_action 401/402/403/498 test (ORIGINAL FUN_1401199d0 family):
//  401 "<nexttask> <d> <d> <d>" -> [user+0xa34] = nexttask, +0xa38 string
//      reset to "" (FUN_140117b50), pending input set (EVENT_LAYNPC deferral)
//  402 "<what> <arg> <op> <n>" -> count npcs on the user's map
//      (all/furniture=type25/name/type), then "<" / "==" compare
//  403 "<accept coords>" + spec "<name> <sort> <look> <base> <dir> <life>
//      <gate> <owner> <u2> <t0..11> <s>": IsPassable + free cell + type gate
//      (role at the cell; gate 3 = the deed ground drop) + owner select,
//      then SpawnDynamic + [user+0xa30] = npc id
//  498 -> FUN_140340190 consume (ctx.dwData model) + [user+0x14c]=0 +
//      STR_USE_ITEM
// Real rows from the live cq database drive every case (150050 statue
// chain, 150060 Statue spec, 410406 "type 25 < 8", 410412 furniture lay).
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "GroundItems.h"
#include "Item.h"
#include "MapManager.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "MySQLClient.h"
#include "Npc.h"

#include "User.h"
#include <cassert>
#include <cstdio>
#include <memory>

static CDialogEngine::Node MkNode(uint32_t id, uint32_t type, const std::string& s) {
    CDialogEngine::Node n;
    n.dwId = id; n.dwType = type; n.dwData = 0; n.strParam = s;
    return n;
}

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "root", "", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    assert(CItemLibrary::Instance().LoadFromDB(pDB) > 0);
    CMapManager::Instance().LoadMapsFromDb(pDB);

    auto up = std::make_shared<CUser>(999701); up->SetName("HouseOwner");
    up->SetMapId(1000);
    auto& rNpc = CNpcManager::Instance();

    // ---- window gate: outside [401,498] the family is "wrong action type"
    auto nd400 = MkNode(9700001, 400, "");
    assert(!CGameAction::ProcessActionItemOnly(up, &nd400));
    auto nd499 = MkNode(9700002, 499, "");
    assert(!CGameAction::ProcessActionItemOnly(up, &nd499));
    printf("[ok] window gate: 400/499 -> false\n");

    // ---- 401 real row 150050 "150060 9 35 1130 3" (statue chain head)
    auto nd401 = MkNode(150050, 401, "150060 9 35 1130 3");
    assert(CGameAction::ProcessActionItemOnly(up, &nd401));
    assert(up->m_dwLayNpcTask == 150060);          // [user+0xa34]
    assert(up->m_strLayNpcBuf.empty());            // +0xa38 reset
    assert(up->GetPendingInput() == 150060);       // EVENT_LAYNPC deferral
    printf("[ok] 401 row 150050 -> task 150060 registered\n");

    // 401 id_nexttask == 0 -> CHECKF "idNextTask != ID_NONE" -> false
    auto nd401z = MkNode(9700003, 401, "0 9 35 1130 3");
    assert(!CGameAction::ProcessActionItemOnly(up, &nd401z));
    // 401 <= 3 tokens -> DBERR 0x1060 -> false
    auto nd401s = MkNode(9700004, 401, "150060 9 35");
    assert(!CGameAction::ProcessActionItemOnly(up, &nd401s));
    printf("[ok] 401 bad forms -> false\n");

    // ---- 402 real row 410406 "type 25 < 8": empty map -> 0 < 8 -> true
    auto& rMgr = CGroundItemManager::Instance();
    auto nd402 = MkNode(410406, 402, "type 25 < 8");
    assert(CGameAction::ProcessActionItemOnly(up, &nd402));
    // map 1000 already carries the default roster (Twin City), so the
    // absolute "all" counts are asserted relative to the live baseline
    const int iBase = (int)rNpc.GetNpcsOnMap(1000).size();
    // "all == base+2": spawn exactly 2 more npcs
    rNpc.SpawnDynamic(500001, "A", 1, 25, 1000, 50, 50, 0);
    rNpc.SpawnDynamic(500002, "B", 1, 25, 1000, 51, 51, 0);
    // ORIGINAL sscanf "%s %s %s %d" == 4 tokens: the arg slot is a
    // placeholder for all/furniture counters (live rows are "type 25 < 8")
    auto ndAll = MkNode(9700005, 402, "all - == " + std::to_string(iBase + 2));
    assert(CGameAction::ProcessActionItemOnly(up, &ndAll));
    auto ndAll3 = MkNode(9700006, 402, "all - == " + std::to_string(iBase + 3));
    assert(!CGameAction::ProcessActionItemOnly(up, &ndAll3));
    // furniture = type 25: the two above (defaults are not type 25)
    auto ndFurn = MkNode(9700007, 402, "furniture - == 2");
    assert(CGameAction::ProcessActionItemOnly(up, &ndFurn));
    // name count
    auto ndName = MkNode(9700008, 402, "name A == 1");
    assert(CGameAction::ProcessActionItemOnly(up, &ndName));
    // type count (real row on the populated map: 2 type-25 < 8)
    assert(CGameAction::ProcessActionItemOnly(up, &nd402));
    // >= 8 gate: 7 more -> 9 furniture -> "< 8" false
    for (uint32_t i = 0; i < 7; ++i)
        rNpc.SpawnDynamic(500010 + i, "C", 1, 25, 1000, 60 + (uint16_t)i, 60, 0);
    assert(!CGameAction::ProcessActionItemOnly(up, &nd402));
    printf("[ok] 402 counts: all/furniture/name/type + <,== ops\n");
    // unknown counter word -> false
    auto ndBadW = MkNode(9700009, 402, "stuff 25 < 8");
    assert(!CGameAction::ProcessActionItemOnly(up, &ndBadW));

    // ---- 403 real row 150060 "Statue 9 35 1130 2 60000 3 0 0 0"
    // gate 3 requires a ground drop at the picked cell first
    up->m_stDialogCtx.strInput = "80 80 0";
    auto nd403 = MkNode(150060, 403, "Statue 9 35 1130 2 60000 3 0 0 0");
    assert(!CGameAction::ProcessActionItemOnly(up, &nd403)); // no drop -> gate fails
    rMgr.AddItemDrop(1000, 80, 80, 721055, 0);               // the deed drop
    assert(CGameAction::ProcessActionItemOnly(up, &nd403));
    assert(up->m_dwCreatedNpcId != 0);                       // [user+0xa30]
    auto pStatue = rNpc.GetNpc(up->m_dwCreatedNpcId);
    assert(pStatue && pStatue->GetName() == "Statue");
    assert(pStatue->GetX() == 80 && pStatue->GetY() == 80);
    assert(pStatue->GetMapId() == 1000);
    // cell now taken -> second 403 at 80,80 -> false
    assert(!CGameAction::ProcessActionItemOnly(up, &nd403));
    printf("[ok] 403 row 150060 -> Statue at 80,80 (gate 3 = deed drop)\n");

    // ---- 403 real row 150160 GuildTeleporter1: its spec sort is 15 (0xf)
    // -> the ORIGINAL STR_DISABLE_LAY_SYNTRANS gate refuses it (live data:
    // the teleporter furniture is laid through another path, not 403)
    up->m_stDialogCtx.strInput = "82 82 0";
    auto ndGT = MkNode(150160, 403,
        "GuildTeleporter1 15 1 1457 2 0 0 0 815 150100");
    assert(!CGameAction::ProcessActionItemOnly(up, &ndGT));
    printf("[ok] 403 row 150160 sort 15 -> STR_DISABLE_LAY_SYNTRANS -> false\n");
    // gate 0 + owner 0 direct lay (no cell-item requirement)
    auto ndBcn = MkNode(9700013, 403, "Beacon 9 35 1130 2 0 0 0");
    assert(CGameAction::ProcessActionItemOnly(up, &ndBcn));
    printf("[ok] 403 gate 0 owner 0 -> Beacon spawned\n");

    // ---- 403 owner=1 (furniture owned by the placer, WallLamp shape)
    up->m_stDialogCtx.strInput = "84 84 0";
    auto ndWL = MkNode(9700010, 403,
        "WallLamp 25 32 10 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    assert(CGameAction::ProcessActionItemOnly(up, &ndWL));
    printf("[ok] 403 owner=1 furniture spawned\n");

    // ---- 403 failure forms
    up->m_stDialogCtx.strInput = "";                          // CHECKF 0x109d
    assert(!CGameAction::ProcessActionItemOnly(up, &nd403));
    up->m_stDialogCtx.strInput = "80";                         // sscanf < 3
    assert(!CGameAction::ProcessActionItemOnly(up, &nd403));
    up->m_stDialogCtx.strInput = "0 0";                       // impassable
    assert(!CGameAction::ProcessActionItemOnly(up, &nd403));
    up->m_stDialogCtx.strInput = "80 80 0";                     // taken cell
    auto nd403f = MkNode(9700011, 403, "W 1 1 1");            // < 5 parsed
    assert(!CGameAction::ProcessActionItemOnly(up, &nd403f));
    // sort 0xf -> STR_DISABLE_LAY_SYNTRANS -> false
    up->m_stDialogCtx.strInput = "86 86 0";
    auto ndSyn = MkNode(9700012, 403, "S 15 1 1457 2 0 0 0");
    assert(!CGameAction::ProcessActionItemOnly(up, &ndSyn));
    printf("[ok] 403 failure forms all -> false\n");

    // ---- 498: consume the item riding the ctx (FUN_140340190 model)
    ItemInfo deed; deed.dwType = 721055; deed.dwAmount = 1;
    up->AddItem(deed);
    up->m_stDialogCtx.dwData = 721055;
    auto nd498 = MkNode(150061, 498, "");
    assert(CGameAction::ProcessActionItemOnly(up, &nd498));
    assert(up->CountItems(721055, 0) == 0);                   // consumed
    // nothing left -> consume fails -> false
    assert(!CGameAction::ProcessActionItemOnly(up, &nd498));
    printf("[ok] 498 row 150061 -> deed consumed, empty retry -> false\n");

    // ---- full live-chain walk: 150050 (401) registers; the "client
    // reply" jumps 150060 (403) -> spawns -> id_next 150061 (498)
    // consumes the deed riding the ctx
    auto up2 = std::make_shared<CUser>(999702); up2->SetName("Owner2");
    up2->SetMapId(1000);
    ItemInfo deed2; deed2.dwType = 721055; deed2.dwAmount = 1;
    up2->AddItem(deed2);
    up2->m_stDialogCtx.dwData = 721055;
    CGameAction::ProcessAction(up2, 150050);
    assert(up2->m_dwLayNpcTask == 150060);
    up2->m_stDialogCtx.strInput = "90 90 0";
    rMgr.AddItemDrop(1000, 90, 90, 721055, 0);
    CGameAction::ProcessAction(up2, up2->GetPendingInput());
    assert(up2->m_dwCreatedNpcId != 0);
    assert(up2->CountItems(721055, 0) == 0);                  // 498 ran via id_next
    printf("[ok] live chain 150050 -> 150060 -> 150061 (statue + consume)\n");

    printf("ALL FAMILY-401-498 TESTS PASSED\n");
    return 0;
}

// cq_action 801/802 test (ORIGINAL FUN_140127070 family):
//  801 dropitem "<type>" -> FUN_14038a790 floor item drop
//  801 dropmoney "<money> [<bound>]" -> roll = bound + rand(100-bound),
//      final = money*roll/100 -> FUN_14038a560 (level<80 && money<=10
//      skip, LuckyTime, >>3/>>2 bonus, 0 -> silent true)
//  802 "<minlev> <maxlev> <amount>" -> money pile (FUN_1401669f0) next
//      to every same-type monster on the source map in the level range
// Real rows from the live cq database drive every case.
#include "Account.h"
#include "Msg.h"   // tq::RandGet (CQBase)
#include "Dialog.h"
#include "GameAction.h"
#include "GroundItems.h"
#include "Item.h"
#include "MapManager.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "MySQLClient.h"
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

    // ---- unknown type in the window: literal false ----
    auto up = std::make_shared<CUser>(999601); up->SetName("Dropper");
    auto nd803 = MkNode(9600003, 803, "");
    assert(!CGameAction::ProcessActionFamily8xx(up, &nd803)); // window gate

    // ---- no source monster: query fail -> false ----
    auto ndNoSrc = MkNode(51, 801, "dropmoney 49 100");
    assert(!CGameAction::ProcessActionUser(up, &ndNoSrc));

    // source monster on a real map cell (SpawnDynamic registers by map)
    auto spMon = CMonsterManager::Instance().SpawnDynamic(1000, 60, 64, 1, 0, "Pheasant");
    spMon->SetLevel(20);
    up->m_dwSourceMonsterId = spMon->GetId();

    // ---- 801 dropmoney (real row id 51 "dropmoney 49 100") ----
    // 3 tokens -> bound = 100 % 100 = 0 -> roll = tq::RandGet(100),
    // final = 49*roll/100. Pre-read the draw, re-seed so the handler
    // consumes the identical sequence, then compare exactly.
    auto& mgr = CGroundItemManager::Instance();
    size_t nBefore = mgr.AllDrops().size();
    srand(999);
    uint32_t uRoll = (uint32_t)tq::RandGet(100);
    uint32_t uExpect = 49 * uRoll / 100;
    srand(999);
    auto nd51 = MkNode(51, 801, "dropmoney 49 100");
    bool b51 = CGameAction::ProcessActionUser(up, &nd51);
    // ORIGINAL outcomes: final == 0 -> false; level<80 && final <= 10
    // -> true with NO drop (the helper's silent skip); else a floor pile.
    bool bExpectDrop = (uExpect > 10);
    assert(b51 == (uExpect != 0));
    assert(mgr.AllDrops().size() == nBefore + (bExpectDrop ? 1 : 0));
    if (bExpectDrop) {
        assert(mgr.AllDrops().rbegin()->second.qwMoney == uExpect);
        printf("[ok] 801 dropmoney row 51 -> pile %u (roll %u)\n",
               uExpect, uRoll);
    } else if (uExpect != 0) {
        printf("[ok] 801 dropmoney row 51 -> %u <= 10, level<80 -> silent skip\n",
               uExpect);
    } else {
        printf("[ok] 801 dropmoney row 51 -> roll %u -> 0 -> false\n", uRoll);
    }
    // a seeded high roll: bound 2-token form rolls exactly 100 -> final 49
    srand(777);
    auto nd49 = MkNode(9600010, 801, "dropmoney 49");
    size_t nB49 = mgr.AllDrops().size();
    assert(CGameAction::ProcessActionUser(up, &nd49));
    assert(mgr.AllDrops().size() == nB49 + 1);
    assert(mgr.AllDrops().rbegin()->second.qwMoney == 49);
    printf("[ok] 801 dropmoney 49 (2-token) -> exact 49 pile\n");

    // ---- 801 dropmoney small value: level<80 && money<=10 -> silent skip
    auto ndLow = MkNode(9600011, 801, "dropmoney 5");
    srand(1);
    size_t nB2 = mgr.AllDrops().size();
    // 2 tokens -> bound=100 -> roll=100 -> final=5 -> helper skips (<80,<=10)
    assert(CGameAction::ProcessActionUser(up, &ndLow));
    assert(mgr.AllDrops().size() == nB2);
    printf("[ok] 801 dropmoney 5 -> level<80 && <=10 skip\n");

    // ---- 801 dropitem (real rows "dropitem 120005") ----
    auto ndIt = MkNode(9600012, 801, "dropitem 120005");
    assert(CGameAction::ProcessActionUser(up, &ndIt));
    auto& d2 = mgr.AllDrops().rbegin()->second;
    assert(d2.dwItemType == 120005);
    printf("[ok] 801 dropitem 120005 -> %s\n", d2.strName.c_str());

    // unknown itemtype -> false, no drop
    size_t nB3 = mgr.AllDrops().size();
    auto ndBad = MkNode(9600013, 801, "dropitem 999999999");
    assert(!CGameAction::ProcessActionUser(up, &ndBad));
    assert(mgr.AllDrops().size() == nB3);

    // ---- 802 (real row "0 0 20"): every same-type monster gets a pile --
    auto spSame1 = CMonsterManager::Instance().SpawnDynamic(1000, 70, 70, 1, 0, "Pheasant");
    spSame1->SetLevel(10);
    auto spSame2 = CMonsterManager::Instance().SpawnDynamic(1000, 72, 72, 1, 0, "Pheasant");
    spSame2->SetLevel(30);
    auto spOther = CMonsterManager::Instance().SpawnDynamic(1000, 74, 74, 2, 0, "Other");
    spOther->SetLevel(10);
    size_t nB4 = mgr.AllDrops().size();
    auto nd802 = MkNode(9171710, 802, "0 0 20");
    srand(7);
    assert(CGameAction::ProcessActionUser(up, &nd802));
    assert(mgr.AllDrops().size() == nB4 + 3); // 3 same-type on map 1000
    printf("[ok] 802 row 9171710 -> 3 money piles of 20\n");

    // ---- level range "10 10": only level-10 monsters ----
    size_t nB5 = mgr.AllDrops().size();
    auto ndRange = MkNode(9600014, 802, "10 10 30");
    assert(CGameAction::ProcessActionUser(up, &ndRange));
    assert(mgr.AllDrops().size() == nB5 + 1); // levels 20,10,30 -> only the 10
    printf("[ok] 802 level range 10..10 -> 1 pile (only the level-10)\n");

    // ---- bad range gate: min > max with max != 0 -> false ----
    size_t nB6 = mgr.AllDrops().size();
    auto ndBadR = MkNode(9600015, 802, "50 20 5");
    assert(!CGameAction::ProcessActionUser(up, &ndBadR));
    assert(mgr.AllDrops().size() == nB6);

    // ---- FUN_14038a560 literal equations on the monster itself ----
    // LuckyTime: money = base * lucky / 100
    spMon->m_dwLuckyTime = 2; spMon->m_dwDropMoneyBase = 500;
    size_t nB7 = mgr.AllDrops().size();
    assert(spMon->ActionDropMoney(9999, 0));
    assert(mgr.AllDrops().size() == nB7 + 1);
    assert(mgr.AllDrops().rbegin()->second.qwMoney == 10); // 500*2/100
    spMon->m_dwLuckyTime = 0;
    // bonus flag: >>3 (depth<=3) then >>2 (depth 4)
    spMon->m_bDropBonus = true; spMon->m_dwDropBonusLevel = 3;
    assert(spMon->ActionDropMoney(800, 0));
    assert(mgr.AllDrops().rbegin()->second.qwMoney == 100); // 800>>3
    spMon->m_dwDropBonusLevel = 5;
    assert(spMon->ActionDropMoney(800, 0));
    assert(mgr.AllDrops().rbegin()->second.qwMoney == 200); // 800>>2
    spMon->m_bDropBonus = false;
    printf("[ok] FUN_14038a560 LuckyTime + bonus equations literal\n");

    printf("ALL 801/802 TESTS PASSED\n");
    return 0;
}

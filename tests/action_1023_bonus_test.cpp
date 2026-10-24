// cq_action 1023 claim test (ORIGINAL FUN_140172910 TakeBonus via the real
// switch case 0x11): the full literal bonus-claim path against live rows:
//  - real row 17510 (type 1023) drives the case
//  - real grant chain 4010171 (type 501, data 721716 UltraBadge)
//    -> 4010182 (type 1027 spouse check -> false -> chain ends)
//  - cq_bonus bookkeeping: flag 0 -> claimed (flag 1 + time), reclaim -> 0
//  - STR_BAG_FULL gate: 40 slots -> claim refused, flag stays 0
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Item.h"
#include "Item.h"
#include "MapManager.h"
#include "MySQLClient.h"
#include "User.h"
#include <cassert>
#include <cstdio>
#include <memory>

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    assert(CItemLibrary::Instance().LoadFromDB(pDB) > 0);
    CMapManager::Instance().LoadMapsFromDb(pDB);

    // real rows sanity: the 1023 driver and the grant chain exist
    assert(pDB->Query("SELECT type FROM cq_action WHERE id = 17510"));
    assert(pDB->GetRows().size() == 1 && pDB->GetRows()[0][0] == "1023");
    assert(pDB->Query("SELECT type, data FROM cq_action WHERE id = 4010171"));
    assert(pDB->GetRows().size() == 1 && pDB->GetRows()[0][0] == "501" &&
           pDB->GetRows()[0][1] == "721716"); // UltraBadge award

    // isolated test account; clean any leftovers from a previous run
    const uint32_t dwAcct = 991023;
    pDB->Query("DELETE FROM cq_bonus WHERE id_account = " +
               std::to_string(dwAcct));
    pDB->Query("INSERT INTO cq_bonus (action, id_account, flag, time) "
               "VALUES (4010171, " + std::to_string(dwAcct) + ", 0, 0)");
    pDB->Query("SELECT flag, time FROM cq_bonus WHERE id_account = " +
               std::to_string(dwAcct) + " AND flag = 0");
    assert(pDB->GetRows().size() == 1); // seeded

    auto up = std::make_shared<CUser>(999701);
    up->SetName("Claimer");
    up->SetAccountId(dwAcct);

    // ---- claim: row 17510 (type 1023) -> grant 4010171 + flag/time ----
    assert(CGameAction::ProcessAction(up, 17510));
    bool bGotBadge = false;
    for (auto& it : up->GetInventory())
        if (it.dwType == 721716) bGotBadge = true;
    assert(bGotBadge); // UltraBadge awarded by the real 501 handler
    assert(up->GetInventory().size() == 1);
    pDB->Query("SELECT flag, time FROM cq_bonus WHERE id_account = " +
               std::to_string(dwAcct) + " ORDER BY id DESC");
    assert(pDB->GetRows().size() == 1);
    assert(pDB->GetRows()[0][0] == "1");           // flag = 1 (claimed)
    uint32_t dwTime = (uint32_t)strtoul(pDB->GetRows()[0][1].c_str(), nullptr, 10);
    assert(dwTime > 0);                             // time = TimeStampGet()
    printf("[ok] claim 17510 -> UltraBadge 721716 awarded, flag=1, time=%u\n",
           dwTime);

    // ---- reclaim: no flag=0 row left -> the claim case returns false;
    // the ENGINE then follows id_nextfail=0 -> chain end -> literal
    // return 1 (LAB_1401469ca). So the proof of "not claimed" is the
    // effect: inventory unchanged and flag still 1.
    size_t nInvAfter = up->GetInventory().size();
    CGameAction::ProcessAction(up, 17510);
    assert(up->GetInventory().size() == nInvAfter); // no second badge
    pDB->Query("SELECT flag FROM cq_bonus WHERE id_account = " +
               std::to_string(dwAcct) + " AND flag = 0");
    assert(pDB->GetRows().empty());                 // nothing to claim
    printf("[ok] reclaim -> no award, no flag=0 row (chain-end literal 1)\n");

    // ---- bag full gate: 40 slots -> STR_BAG_FULL, flag stays 0 ----
    pDB->Query("INSERT INTO cq_bonus (action, id_account, flag, time) "
               "VALUES (4010171, " + std::to_string(dwAcct) + ", 0, 0)");
    while (up->GetInventory().size() < 0x28) { // ORIGINAL: 40 slots
        ItemInfo it;
        it.dwType = 1000000 + (uint32_t)up->GetInventory().size();
        it.strName = "filler";
        it.dwPosition = 255;
        up->AddItem(it);
    }
    assert(up->GetInventory().size() == 0x28);
    size_t nInvFull = up->GetInventory().size();
    CGameAction::ProcessAction(up, 17510); // ORIGINAL: bag full -> case 0
    assert(up->GetInventory().size() == nInvFull); // nothing granted
    pDB->Query("SELECT flag FROM cq_bonus WHERE id_account = " +
               std::to_string(dwAcct) + " ORDER BY id DESC");
    assert(pDB->GetRows()[0][0] == "0"); // NOT claimed: bonus preserved
    printf("[ok] bag full -> STR_BAG_FULL -> false, flag stays 0\n");

    // cleanup: leave the live cq_bonus table as we found it (empty)
    pDB->Query("DELETE FROM cq_bonus WHERE id_account = " +
               std::to_string(dwAcct));
    printf("ALL 1023 BONUS CLAIM TESTS PASSED\n");
    return 0;
}

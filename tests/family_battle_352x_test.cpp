// cq_action 3523/3524 fidelity tests (battle-domain hold/challenge checks).
// Verified against MsgServer FUN_140140380 subcases idx22 (0x140141a5c) and
// idx23 (0x140141b1b): user syn required; mgr vcall+0x88(data) domain record
// must exist; result = (rec8 vcall+0x1c0(syn) [or +0x1b0] != 0 && == data).
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Guild.h"
#include "FamilyBattle.h"
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
    auto& syn = CGuildManager::Instance();
    auto& fb = CFamilyBattleManager::Instance();
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'BtlTest%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id = 999201");

    // seed domains exactly like the real chains reference (10026, 10027)
    fb.SeedFromDB(pDB);
    assert(fb.Find(10026) && fb.Find(10027) && fb.Find(10035));
    assert(!fb.Find(99999)); // vcall+0x88 unknown -> null -> false
    printf("[ok] domain records seeded from cq_action (10026..10035)\n");

    auto up = std::make_shared<CUser>(999201); up->SetName("BtlChieftain");
    CUser& u = *up;
    auto nd23 = MkNode(9300001, 3523, 10026, ""); // real row shape
    auto nd24 = MkNode(9300002, 3524, 10026, "");

    // no clan -> false for both
    assert(!CGameAction::ProcessActionUser(up, &nd23));
    assert(!CGameAction::ProcessActionUser(up, &nd24));
    printf("[ok] no clan -> false\n");

    // create clan through the real 218 path
    u.m_stDialogCtx.strInput = "BtlTestClan";
    auto nd18 = MkNode(9300003, 218, 0, "");
    assert(CGameAction::ProcessActionUser(up, &nd18));
    uint32_t dwSyn = syn.GetSynIdOfUser(999201);
    assert(dwSyn != 0);
    printf("[ok] clan created (syn %u)\n", dwSyn);

    // clan holds nothing -> both false
    assert(!CGameAction::ProcessActionUser(up, &nd23));
    assert(!CGameAction::ProcessActionUser(up, &nd24));

    // clan holds 10026 -> 3523(data=10026) true, 3523(data=10027) false
    syn.GetSynById(dwSyn)->SetHoldDomain(10026);
    assert(CGameAction::ProcessActionUser(up, &nd23));
    auto nd23b = MkNode(9300004, 3523, 10027, "");
    assert(!CGameAction::ProcessActionUser(up, &nd23b));
    // hold set does not affect the challenge check
    assert(!CGameAction::ProcessActionUser(up, &nd24));
    printf("[ok] 3523 hold-domain check\n");

    // challenge 10027 -> 3524(10027) true, 3524(10026) false, 3523 intact
    syn.GetSynById(dwSyn)->SetChallengeDomain(10027);
    auto nd24b = MkNode(9300005, 3524, 10027, "");
    assert(CGameAction::ProcessActionUser(up, &nd24b));
    assert(!CGameAction::ProcessActionUser(up, &nd24));
    assert(CGameAction::ProcessActionUser(up, &nd23)); // still holds 10026
    printf("[ok] 3524 challenge-domain check\n");

    // unknown domain id -> false even when state matches
    auto nd23c = MkNode(9300006, 3523, 99999, "");
    assert(!CGameAction::ProcessActionUser(up, &nd23c));
    printf("[ok] unknown domain record -> false\n");

    // cleanup
    auto nd19 = MkNode(9300007, 219, 0, "");
    assert(CGameAction::ProcessActionUser(up, &nd19));
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'BtlTest%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id = 999201");

    printf("ALL 3523/3524 TESTS PASSED\n");
    return 0;
}

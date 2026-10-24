// cq_action 3521 (family-battle income distribution) fidelity test.
// Flow verified against MsgServer FUN_140140380 idx20 @ 0x140140d00:
// domain record gate, processed-early-true, holder gate, 15-minute window,
// SUCCESS (income consume+reset, treasury, announcement) and DEFEND
// (challenger income erase, challenge-state swap) outcomes.
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Guild.h"
#include "FamilyBattle.h"
#include "User.h"
#include "UserManager.h"
#include "MapManager.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstdio>
#include <ctime>
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
    assert(acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    CMapManager::Instance().LoadMapsFromDb(pDB);
    auto& syn = CGuildManager::Instance();
    auto& fb = CFamilyBattleManager::Instance();
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'IncTest%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id IN (999301, 999302, 999303)");

    // two clans: Alpha (acting user) and Beta (rival)
    auto upA = std::make_shared<CUser>(999301); upA->SetName("AlphaChief");
    auto upB = std::make_shared<CUser>(999302); upB->SetName("BetaChief");
    CUserManager::Instance().AddUser(upA);
    CUserManager::Instance().AddUser(upB);
    auto nd18 = MkNode(9400001, 218, 0, "");
    upA->m_stDialogCtx.strInput = "IncTestAlpha";
    upB->m_stDialogCtx.strInput = "IncTestBeta";
    assert(CGameAction::ProcessActionUser(upA, &nd18));
    assert(CGameAction::ProcessActionUser(upB, &nd18));
    uint32_t dwA = syn.GetSynIdOfUser(999301);
    uint32_t dwB = syn.GetSynIdOfUser(999302);
    assert(dwA && dwB && dwA != dwB);
    CGuild* pGA = syn.GetSynById(dwA);
    CGuild* pGB = syn.GetSynById(dwB);
    assert(pGA && pGB);

    // domain: Alpha holds 10026, Beta is the registered challenger
    auto& dom = fb.Create(10026);
    dom.dwHolderSyn = dwA;
    dom.dwChallengerSyn = dwB;
    pGA->SetHoldDomain(10026);
    pGA->SetChallengeDomain(0);
    pGB->SetChallengeDomain(10026);

    time_t t = time(nullptr);
    struct tm* pTm = localtime(&t);
    int64_t llCur = pTm->tm_hour * 60 + pTm->tm_min;
    auto nd21 = MkNode(9400002, 3521, 10026, ""); // real row shape

    // ---- unknown domain -> false ----
    auto nd21b = MkNode(9400003, 3521, 99999, "");
    assert(!CGameAction::ProcessActionUser(upA, &nd21b));
    printf("[ok] unknown domain -> false\n");

    // ---- user not of the holder syn -> false (Beta chief acts) ----
    assert(!CGameAction::ProcessActionUser(upB, &nd21));
    printf("[ok] non-holder actor -> false\n");

    // ---- in-window DEFEND: Beta's income erased, paid to Beta,
    //      Alpha becomes the challenger ----
    fb.ResetIncome(10026, dwB, 4);        // battle scheduler created it
    fb.AccumIncome(10026, dwB, 4, 300000); // accumulated during the battle
    fb.SetKernelMinutes((int32_t)llCur);    // kernel snapshot = now
    assert(CGameAction::ProcessActionUser(upA, &nd21));
    assert(pGB->GetTreasury() == 300000);   // vcall+0x190 to the challenger
    assert(fb.FindIncome(10026, dwB, 4) == nullptr); // FUN_1401511e0 erase
    assert(pGA->GetChallengeDomain() == 10026); // +0x1b8(userSyn, domain)
    assert(pGB->GetChallengeDomain() == 0);      // +0x1b8(challenger, 0)
    assert(dom.bProcessed);                  // vcall+0x1a8 mark
    printf("[ok] in-window DEFEND outcome\n");

    // ---- processed flag: second run returns true immediately, no change
    int64_t qwBefore = pGB->GetTreasury();
    assert(CGameAction::ProcessActionUser(upA, &nd21));
    assert(pGB->GetTreasury() == qwBefore);
    printf("[ok] vcall+0x40 processed -> early true\n");

    // ---- SUCCESS outcome: holder == challenger (fresh domain) ----
    dom.bProcessed = false;
    dom.dwHolderSyn = dwB;
    dom.dwChallengerSyn = dwB;
    pGB->SetHoldDomain(10026);
    pGB->SetChallengeDomain(0);
    fb.ResetIncome(10026, dwB, 4);       // start at zero
    fb.AccumIncome(10026, dwB, 4, 750000);
    assert(CGameAction::ProcessActionUser(upB, &nd21));
    assert(pGB->GetTreasury() == 300000 + 750000); // +0x190 add
    auto* pInc = fb.FindIncome(10026, dwB, 4);    // FUN_140151380 reset
    assert(pInc && pInc->qwAmount == 0);
    assert(dom.bProcessed);
    printf("[ok] in-window SUCCESS outcome (income consume+reset)\n");

    // ---- early window: cur < kernel -> false ----
    dom.bProcessed = false;
    fb.SetKernelMinutes((int32_t)(llCur + 20)); // kernel ahead
    assert(!CGameAction::ProcessActionUser(upB, &nd21));
    printf("[ok] cur < kernel -> false\n");

    // ---- late window SUCCESS: the collected vector holds only
    // holder-syn users, so the online-challenger scan (0x140141379)
    // matches only when holder == challenger; the original walk has the
    // same shape ----
    dom.bProcessed = false;
    dom.dwHolderSyn = dwB;
    dom.dwChallengerSyn = dwB;
    pGB->SetHoldDomain(10026);
    pGA->SetChallengeDomain(0);
    fb.ResetIncome(10026, dwB, 4);
    fb.AccumIncome(10026, dwB, 4, 111111);
    int64_t qwB = pGB->GetTreasury();
    fb.SetKernelMinutes((int32_t)(llCur - 20)); // kernel stale 20 min
    assert(CGameAction::ProcessActionUser(upB, &nd21));
    assert(pGB->GetTreasury() == qwB + 111111);
    assert(fb.FindIncome(10026, dwB, 4) != nullptr
           && fb.FindIncome(10026, dwB, 4)->qwAmount == 0); // reset, kept
    printf("[ok] late-window SUCCESS (holder==challenger online)\n");

    // ---- late window offline pick: DEFEND via max battle value ----
    dom.bProcessed = false;
    fb.ResetIncome(10026, dwB, 4);
    dom.dwHolderSyn = dwA;      // Alpha holds it again
    dom.dwChallengerSyn = 0; // no registered challenger
    pGA->SetChallengeDomain(0);
    fb.SetUserBattleValue(999301, 42); // Alpha chief's user battle value
    int64_t qwA = pGA->GetTreasury();
    assert(CGameAction::ProcessActionUser(upA, &nd21));
    assert(pGA->GetChallengeDomain() == 10026); // picked syn gets challenge
    printf("[ok] late-window offline pick DEFEND\n");

    // ---- no clan actor -> false (fresh domain; the original vcall+0x40
    // early-true sits BEFORE the syn gates, so a processed domain returns
    // true even for a clanless actor - checked above already) ----
    dom.bProcessed = false;
    auto upC = std::make_shared<CUser>(999303); upC->SetName("Clanless");
    assert(!CGameAction::ProcessActionUser(upC, &nd21));
    printf("[ok] actor without syn -> false\n");

    // cleanup
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'IncTest%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id IN (999301, 999302, 999303)");

    printf("ALL 3521 INCOME TESTS PASSED\n");
    return 0;
}

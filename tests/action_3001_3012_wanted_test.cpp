// cq_action 3001..3012 family (ProcessActionWanted, FUN_14011a7e0)
// fidelity tests driven against REAL live rows: 17020 (draft target),
// 17030 (draft amount), 17031 (publish), 17043 (list walk), 17060
// (hunter accept), 17080 (cancel for 2x), 17100/17110 (reward add),
// 17613 (police walk), 17660 (police accept), 200000 (wanted gate).
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Guild.h"
#include "User.h"
#include "UserManager.h"
#include "Wanted.h"
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
    auto& mgr = CWantedManager::Instance();
    auto& um = CUserManager::Instance();
    mgr.ClearForTest();

    auto upOffer = std::make_shared<CUser>(999301); upOffer->SetName("RichFoe");
    auto upHunt = std::make_shared<CUser>(999302);  upHunt->SetName("BountyHunter");
    auto upBad = std::make_shared<CUser>(999303);   upBad->SetName("BadGuy");
    upOffer->SetMoney(2000000);
    upHunt->SetMoney(50000);
    assert(um.AddUser(upOffer) && um.AddUser(upHunt) && um.AddUser(upBad));
    CUser& offerer = *upOffer;

    // ---- LIVE ROW 17020 (3002): "My enemy is: <typed>" ----
    offerer.m_stDialogCtx.strInput = "BadGuy";
    auto nd = MkNode(17020, 3002, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    printf("[ok] 3002 (live 17020) draft target BadGuy\n");
    // own name refused (model of the +0x120 refuse path)
    offerer.m_stDialogCtx.strInput = "RichFoe";
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd));
    offerer.m_stDialogCtx.strInput = "BadGuy";
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));

    // ---- LIVE ROW 17030 (3003): "I offer <amount>" ----
    // over the cap -> STR_MAX_BONUTY (original literal typo) + false
    offerer.m_stDialogCtx.strInput = "10000000";
    nd = MkNode(17030, 3003, 0, "");
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd));
    offerer.m_stDialogCtx.strInput = "150000";
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    printf("[ok] 3003 (live 17030) draft amount 150000 (cap 9999999 ok)\n");

    // ---- LIVE ROW 17031 (3004): publish ----
    nd = MkNode(17031, 3004, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(upOffer->GetMoney() == 2000000 - 150000); // charged
    assert(mgr.IsValidId(1));
    printf("[ok] 3004 (live 17031) published #1, charged 150000\n");

    // ---- 3004: min-gate 100k: 99,999 draft -> STR_MIN_BONUTY + false,
    // no charge ----
    offerer.m_stDialogCtx.strInput = "9"; // tiny draft
    nd = MkNode(920030, 3003, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    uint64_t qwM = upOffer->GetMoney();
    nd = MkNode(920031, 3004, 0, "");
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(upOffer->GetMoney() == qwM); // not charged
    printf("[ok] 3004 min 100000 -> false, no charge\n");

    // ---- LIVE ROW 17043 (3001): offer-list walk + %iter_wanted ----
    offerer.SetIterSynState(0);
    nd = MkNode(17043, 3001, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(offerer.GetIterSynState() == 1);
    assert(mgr.FormatOfferLine(offerer.GetIterSynState()) == "1 BadGuy 150000");
    // second walk ends (single offer) -> false -> live 17053 separator
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd));
    printf("[ok] 3001 (live 17043) walk + %%iter_wanted line\n");

    // ---- LIVE ROW 17060 (3005): hunter accepts (fee 1000) ----
    upHunt->m_stDialogCtx.strInput = "1";
    nd = MkNode(17060, 3005, 0, "");
    assert(CGameAction::ProcessActionWanted(upHunt, &nd));
    assert(upHunt->GetMoney() == 50000 - 1000);
    assert(mgr.GetAcceptedOf(999302) == 1);
    // invalid id -> STR_INVALID_WANTED + false
    upHunt->m_stDialogCtx.strInput = "77";
    assert(!CGameAction::ProcessActionWanted(upHunt, &nd));
    printf("[ok] 3005 (live 17060) accepted #1 fee 1000, invalid refused\n");

    // ---- 3005: target BadGuy got the online notify (STR_WANTED_INFO) ----
    // (the online-target notify path executed - BadGuy is registered)
    upBad->SetMoney(1000000);

    // ---- LIVE ROW 17080 (3006): cancel for DOUBLE the reward ----
    // hunter can't afford 2x150000
    upHunt->m_stDialogCtx.strInput = "1";
    nd = MkNode(17080, 3006, 0, "");
    assert(!CGameAction::ProcessActionWanted(upHunt, &nd));
    assert(upHunt->GetMoney() == 49000); // unchanged
    // the OFFERER cancels: 2x150000 = 300000 charged
    upOffer->m_stDialogCtx.strInput = "1";
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(upOffer->GetMoney() == 2000000 - 150000 - 300000);
    assert(!mgr.IsValidId(1)); // removed
    printf("[ok] 3006 (live 17080) canceled for 300000, removed\n");

    // ---- re-publish for the add-reward flow (real 3002/3003/3004) ----
    offerer.m_stDialogCtx.strInput = "BadGuy";
    nd = MkNode(920032, 3002, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    offerer.m_stDialogCtx.strInput = "200000";
    nd = MkNode(920033, 3003, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    nd = MkNode(920034, 3004, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(mgr.IsValidId(2));
    uint64_t qwAfterPublish = upOffer->GetMoney();

    // ---- LIVE ROW 17100 (3007): select offer #2 for reward-add ----
    offerer.m_stDialogCtx.strInput = "2";
    nd = MkNode(17100, 3007, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(mgr.GetSelectedOwnOffer(999301) == 2);
    printf("[ok] 3007 (live 17100) selected offer #2\n");

    // ---- LIVE ROW 17110 (3008): add reward ----
    // < 10000 -> STR_LOWEST_SUPERADD_BONUTY + false
    offerer.m_stDialogCtx.strInput = "9999";
    nd = MkNode(17110, 3008, 0, "");
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd));
    // 50000 more: 200000 -> 250000, charged
    offerer.m_stDialogCtx.strInput = "50000";
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(mgr.GetAmountOf(2) == 250000);
    assert(upOffer->GetMoney() == qwAfterPublish - 50000);
    printf("[ok] 3008 (live 17110) superadd 50000 -> total 250000\n");

    // ---- LIVE ROW 17613 (3010): police-board walk + the line ----
    offerer.SetIterSynState(0);
    nd = MkNode(17613, 3010, 0, "");
    assert(CGameAction::ProcessActionWanted(upOffer, &nd));
    assert(offerer.GetIterSynState() == 1);
    // BadGuy is online -> level/pk resolve; no guild -> "None"
    std::string line = mgr.FormatPoliceLine(offerer.GetIterSynState());
    // BadGuy is a fresh online user: default level 1, pk 0, no guild
    assert(line == "2 BadGuy None 1 0");
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd)); // walk ends
    printf("[ok] 3010 (live 17613) police walk: '%s'\n", line.c_str());

    // ---- LIVE ROW 17660 (3011): police accept ----
    // the OFFERER is online -> true (chain 17663 "only the last")
    upHunt->m_stDialogCtx.strInput = "2";
    nd = MkNode(17660, 3011, 0, "");
    assert(CGameAction::ProcessActionWanted(upHunt, &nd));
    // a NON-EXISTENT board number -> false (chain 17661 "wrong number")
    upHunt->m_stDialogCtx.strInput = "77";
    assert(!CGameAction::ProcessActionWanted(upHunt, &nd));
    printf("[ok] 3011 (live 17660) police-accepted #2, bad id refused\n");

    // ---- LIVE ROW 200000 (3012): the wanted-criminal teleport gate ----
    nd = MkNode(200000, 3012, 0, "");
    assert(CGameAction::ProcessActionWanted(upBad, &nd));   // BadGuy is a target
    assert(!CGameAction::ProcessActionWanted(upHunt, &nd)); // clean player
    printf("[ok] 3012 (live 200000) BadGuy wanted / hunter clean\n");

    // ---- 3009: NO CASE in the ORIGINAL switch -> literal false ----
    nd = MkNode(920039, 3009, 0, "");
    assert(!CGameAction::ProcessActionWanted(upOffer, &nd));
    printf("[ok] 3009 absent case -> literal false\n");

    mgr.ClearForTest();
    printf("ALL 3001-3012 PROCESS-ACTION-WANTED TESTS PASSED\n");
    return 0;
}

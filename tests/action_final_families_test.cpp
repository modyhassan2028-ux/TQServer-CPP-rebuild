// The LAST live-row families: 3907 (FactionMatch), 8007/8011
// (CrossServer), 9001 (OS) - ProcessActionFactionMatch (FUN_14011c610),
// ProcessActionCrossServer (FUN_14011c9e0), ProcessActionOS
// (FUN_140142880). After this suite every live cq_action type has a
// literal port.
#include "Account.h"
#include "CrossServer/CrossClient.h"
#include "Dialog.h"
#include "FactionMatch.h"
#include "GameAction.h"
#include "User.h"
#include "UserManager.h"
#include "Wanted.h"
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
    assert(acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);

    auto& fm = CFactionMatchMgr::Instance();
    auto& ctf = CCrossCtfMgr::Instance();
    auto& cross = cross::CCrossClient::Instance();
    fm.ClearForTest(); ctf.ClearForTest();

    auto up = std::make_shared<CUser>(1001); up->SetName("CtfGuy");
    auto up2 = std::make_shared<CUser>(1002); up2->SetName("TeamGuy");
    auto upOs = std::make_shared<CUser>(0xee69a15f); upOs->SetName("Visitor");
    assert(CUserManager::Instance().AddUser(up));
    assert(CUserManager::Instance().AddUser(up2));
    assert(CUserManager::Instance().AddUser(upOs));
    upOs->SetOsUserFlag(true); // CUser+0x12fc

    // ============ LIVE ROWS 6043911/6043912/6043913 (3907, data 1/2/3) =
    // faction 0 -> row data=1
    fm.SetFactionOf("CtfGuy", 0);
    auto nd = MkNode(6043911, 3907, 1, "");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043912, 3907, 2, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043913, 3907, 3, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    printf("[ok] 3907 faction 0 -> live 6043911 (data 1) only\n");

    // faction 1 -> rows data=2; the walk 6043911 -> 6043912
    fm.SetFactionOf("CtfGuy", 1);
    nd = MkNode(6043911, 3907, 1, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043912, 3907, 2, "");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    printf("[ok] 3907 faction 1 -> live 6043912 (data 2)\n");

    // faction 2 -> only 6043913 (data 3)
    fm.SetFactionOf("CtfGuy", 2);
    nd = MkNode(6043911, 3907, 1, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043912, 3907, 2, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043913, 3907, 3, "");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    printf("[ok] 3907 faction 2 -> live 6043913 (data 3)\n");

    // unknown faction -> all three false -> chain lands on 6043940
    fm.SetFactionOf("CtfGuy", 999); // off-group
    nd = MkNode(6043911, 3907, 1, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043912, 3907, 2, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(6043913, 3907, 3, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    printf("[ok] 3907 unknown faction -> all false\n");

    // 6064021/6064032 (the other NPC's pair, data 1/2)
    fm.SetFactionOf("CtfGuy", 1);
    nd = MkNode(6064032, 3907, 2, "");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    printf("[ok] 3907 live 6064032 (data 2)\n");

    // 3901: open/close (no live rows, literal +0x10 model)
    nd = MkNode(939001, 3901, 1, "");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(939002, 3901, 0, "");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    assert(fm.IsMatchOpen() == false);
    // 3908: score compare (mgr+0x3d8 -> 0): "5 < x" -> 0 < 5 true
    nd = MkNode(939008, 3908, 0, "5 < 3");
    assert(CGameAction::ProcessActionFactionMatch(up, &nd));
    nd = MkNode(939009, 3908, 0, "5 > 3");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    // bad type in range -> DBERR + false, literal
    nd = MkNode(939099, 3997, 0, "");
    assert(!CGameAction::ProcessActionFactionMatch(up, &nd));
    printf("[ok] 3901/3908/unknown-type literal paths\n");

    // ============ LIVE ROWS 6043705/6043725/6043745 (8007, data 1/2/3) =
    ctf.SetGroupOf("CtfGuy", 0);
    nd = MkNode(6043705, 8007, 1, "");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    nd = MkNode(6043725, 8007, 2, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    nd = MkNode(6043745, 8007, 3, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    ctf.SetGroupOf("CtfGuy", 2);
    nd = MkNode(6043705, 8007, 1, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    nd = MkNode(6043745, 8007, 3, "");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    ctf.SetGroupOf("CtfGuy", 999); // off-group -> "only the guild that won"
    nd = MkNode(6043705, 8007, 1, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    printf("[ok] 8007 live 6043705/6043725/6043745 group walk\n");

    // ============ LIVE ROWS 6041180/6041191/6043922/6064096 (8011) ======
    // live rows carry an EMPTY param -> mode 0 -> the scene path
    cross.DebugSetLinked(true);
    nd = MkNode(6041191, 8011, 1, ""); // after 1075 "send 1000 1"
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    assert(cross.m_dwLastTransferUser == 1001 && cross.m_dwLastTransferA == 0 &&
           cross.m_dwLastTransferB == 0); // FUN_1401bd0d0(user, 0, 0)
    nd = MkNode(6041180, 8011, 0, "");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    nd = MkNode(6043922, 8011, 1, "");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    nd = MkNode(6064096, 8011, 1, "");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    printf("[ok] 8011 live rows (empty param) -> scene transfer\n");

    // dead user -> deny
    up->SetAlive(false);
    nd = MkNode(6041191, 8011, 1, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    up->SetAlive(true);
    // in a team -> deny
    ctf.SetTeamIdOf(1001, 7);
    nd = MkNode(6041191, 8011, 1, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    ctf.SetTeamIdOf(1001, 0);
    // hub link down -> disconnect
    cross.DebugSetLinked(false);
    nd = MkNode(6041191, 8011, 1, "");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    cross.DebugSetLinked(true);
    // mode 1 -> literal false (no message)
    nd = MkNode(938011, 8011, 0, "1");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    // mode 5 -> literal false
    nd = MkNode(938012, 8011, 0, "5");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    // mode 2, flag war closed -> STR_CROSS_FALG_WAR_CLOSE (typo) + false
    nd = MkNode(938013, 8011, 0, "2");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    ctf.SetFlagWarOpen(0x809, true);
    nd = MkNode(938013, 8011, 0, "2");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    assert(cross.m_dwLastTransferB == 2);
    // mode 4, no frontier -> deny
    nd = MkNode(938014, 8011, 0, "4");
    assert(!CGameAction::ProcessActionCrossServer(up, &nd));
    ctf.SetFrontierServer(12); // with a frontier -> frontier transfer, flag 1
    nd = MkNode(938014, 8011, 0, "4");
    assert(CGameAction::ProcessActionCrossServer(up, &nd));
    assert(cross.m_dwLastTransferA == 12 && cross.m_dwLastTransferB == 1);
    printf("[ok] 8011 gates: dead/team/disconnect/mode 1,5/flag war/frontier\n");

    // ============ LIVE ROW 6041176 (9001) ===============================
    // normal user -> false (chain -> 94415600)
    nd = MkNode(6041176, 9001, 0, "");
    assert(!CGameAction::ProcessActionOtherServer(up, &nd));
    // OS user (id > 0xee69a15e + the +0x12fc flag) -> true (-> 94415630)
    assert(CGameAction::ProcessActionOtherServer(upOs, &nd));
    printf("[ok] 9001 live 6041176: OS visitor gate\n");

    // 9003: OS user -> scene transfer scene 1
    nd = MkNode(930003, 9003, 0, "");
    assert(CGameAction::ProcessActionOtherServer(upOs, &nd));
    assert(cross.m_dwLastTransferA == 1);
    // 9004: NOT an OS user -> frontier transfer (data, 0)
    nd = MkNode(930004, 9004, 12, "");
    assert(CGameAction::ProcessActionOtherServer(up, &nd));
    assert(cross.m_dwLastTransferA == 12 && cross.m_dwLastTransferB == 0);
    // unknown type in range -> DBERR + false
    nd = MkNode(939998, 9384, 0, "");
    assert(!CGameAction::ProcessActionOtherServer(up, &nd));
    printf("[ok] 9003/9004/unknown-type paths\n");

    fm.ClearForTest(); ctf.ClearForTest();
    printf("ALL FINAL-FAMILY (3907/8007/8011/9001) TESTS PASSED\n");
    return 0;
}

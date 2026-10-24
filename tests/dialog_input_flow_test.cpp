// 6159 input-dialog reply flow test: a 103 (input) dialog registers the
// continuation action (User::SetPendingInput); the typed answer arrives
// as MsgTalk(1004) to the talking NPC, becomes the dialog ctx strInput,
// and the chain continues there (MsgTalk::Process input branch).
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Guild.h"
#include "MapManager.h"
#include "MsgTalk.h"
#include "MySQLClient.h"
#include "Npc.h"
#include "User.h"
#include "UserManager.h"
#include <cassert>
#include <cstdio>
#include <memory>

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    CMapManager::Instance().LoadMapsFromDb(pDB);
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'InpClan%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id = 999601");

    auto up = std::make_shared<CUser>(999601); up->SetName("InputTest");
    CUserManager::Instance().AddUser(up);
    auto spNpc = std::make_shared<CNpc>(4000001, "ClanClerk",
                                       CNpc::Type::Dialog, 1000, 30, 30);
    CNpcManager::Instance().AddNpcForTest(spNpc);
    up->SetTalkingNpc(4000001);

    // real DB row 5021750 is a 218 create-clan action
    assert(CDialogEngine::Instance().HasNode(5021750));
    up->SetPendingInput(5021750);

    // the client's typed answer arrives as a 1004 MsgTalk to the NPC
    CMsgTalk reply;
    assert(reply.Create("InputTest", "ClanClerk", "InpClanOk",
                        CMsgTalk::Channel_Talk, 4000001));
    reply.Process(999601);

    // the input text reached the dialog ctx and the 218 chain consumed it
    assert(up->m_stDialogCtx.strInput == "InpClanOk");
    assert(CGuildManager::Instance().GetSynIdOfUser(999601) != 0);
    assert(up->GetPendingInput() == 0); // consumed

    // no pending input: a plain talk does not touch ctx.strInput
    up->m_stDialogCtx.strInput.clear();
    CMsgTalk plain;
    assert(plain.Create("InputTest", "", "hello there",
                        CMsgTalk::Channel_Talk));
    plain.Process(999601);
    assert(up->m_stDialogCtx.strInput.empty());
    printf("[ok] typed 1004 answer -> ctx.strInput + chain jump\n");

    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'InpClan%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id = 999601");
    printf("ALL INPUT-DIALOG FLOW TESTS PASSED\n");
    return 0;
}

// cq_action 701..722 family (ProcessActionSyn, FUN_140128290) fidelity
// tests, driven against REAL live rows: 10330 (create), 10363 (donate),
// 10373 (announce), 10393 (invite), 10403/10413/10433 (relations),
// 10443 (721 name resolve), 10683/100013 (iterators), 20120/120230/120231
// (717 money ops), 10383 (705: NO CASE in the original switch).
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Guild.h"
#include "User.h"
#include "UserManager.h"
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
    assert(acc.TryMySQL("127.0.0.1", 3306, "tqserver", "tqpass123", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    CMapManager::Instance().LoadMapsFromDb(pDB);
    auto& syn = CGuildManager::Instance();
    auto& um = CUserManager::Instance();
    // clean slate FIRST: previous runs' rows must not reach LoadFromDB
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'SynFam%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id IN (999201, 999202, 999203)");
    assert(syn.LoadFromDB(pDB) > 0); // live cq_syndicate (tester, ...)

    auto up = std::make_shared<CUser>(999201); up->SetName("SynLeader");
    auto up2 = std::make_shared<CUser>(999202); up2->SetName("SynMate");
    auto up3 = std::make_shared<CUser>(999203); up3->SetName("SynRival");
    up->SetMoney(1000000000);
    assert(um.AddUser(up) && um.AddUser(up2));
    CUser& u = *up;

    // ---- LIVE ROW 10330 (701 "90 1000000 500000"): create the guild ----
    u.m_stDialogCtx.strInput = "SynFamTest";
    auto nd = MkNode(10330, 701, 0, "90 1000000 500000");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynIdOfUser(999201) != 0);
    uint32_t dwMySyn = syn.GetSynIdOfUser(999201);
    printf("[ok] 701 (live row 10330) created guild id=%u\n", dwMySyn);

    // ---- 701: duplicate name -> STR_INVALID_GUILD_NAME + false ----
    up2->m_stDialogCtx.strInput = "SynFamTest";
    assert(!CGameAction::ProcessActionSyn(up2, &nd));
    printf("[ok] 701 duplicate name -> false\n");

    // ---- LIVE ROW 10363 (703): donate the typed amount to own guild ----
    uint64_t qwBefore = syn.GetSynTreasuryById(dwMySyn);
    up->m_stDialogCtx.strInput = "50000";
    nd = MkNode(10363, 703, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynTreasuryById(dwMySyn) == (int64_t)qwBefore + 50000);
    assert(up->GetMoney() == 1000000000 - 50000);
    printf("[ok] 703 (live row 10363) donate 50000 -> treasury + user money\n");

    // ---- 703: amount 0 -> false (ORIGINAL < 1 -> 0) ----
    up->m_stDialogCtx.strInput = "0";
    assert(!CGameAction::ProcessActionSyn(up, &nd));
    printf("[ok] 703 amount 0 -> false\n");

    // ---- LIVE ROW 10373 (704): set the announcement ----
    up->m_stDialogCtx.strInput = "Welcome to SynFamTest";
    nd = MkNode(10373, 704, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynOf(999201)->GetAnnouncement() == "Welcome to SynFamTest");
    printf("[ok] 704 (live row 10373) announcement set\n");

    // ---- LIVE ROW 10393 (706): invite the named player ----
    up->m_stDialogCtx.strInput = "SynMate";
    nd = MkNode(10393, 706, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynOf(999202) && syn.GetSynOf(999202)->GetId() == dwMySyn);
    printf("[ok] 706 (live row 10393) invited SynMate\n");

    // ---- 706: unknown name -> false (STR_NOT_HERE path) ----
    up->m_stDialogCtx.strInput = "Ghost";
    assert(!CGameAction::ProcessActionSyn(up, &nd));
    printf("[ok] 706 unknown name -> false\n");

    // ---- LIVE ROW 10403 (711): declare hostile by guild name ----
    // target: a second guild created through 218 (real flow) by a third
    // player - SynMate already joined ours (a member can't create one)
    up3->m_stDialogCtx.strInput = "SynFamRival";
    auto nd218 = MkNode(9200001, 218, 0, "");
    assert(CGameAction::ProcessActionUser(up3, &nd218));
    uint32_t dwRival = syn.GetSynIdOfUser(999203);
    assert(dwRival && dwRival != dwMySyn);
    up->m_stDialogCtx.strInput = "SynFamRival";
    nd = MkNode(10403, 711, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynByIdShared(dwMySyn)->IsHostileTo(dwRival));
    printf("[ok] 711 (live row 10403) hostile declared\n");

    // ---- LIVE ROW 10413 (712): reconcile ----
    nd = MkNode(10413, 712, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(!syn.GetSynByIdShared(dwMySyn)->IsHostileTo(dwRival));
    printf("[ok] 712 (live row 10413) reconciled\n");

    // ---- LIVE ROW 10423 (713): accept the pending ally request ----
    syn.AddAllyRequest(dwRival, dwMySyn);
    nd = MkNode(10423, 713, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynByIdShared(dwMySyn)->IsAlliedTo(dwRival));
    printf("[ok] 713 (live row 10423) allied\n");

    // ---- LIVE ROW 10433 (714): unally ----
    nd = MkNode(10433, 714, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(!syn.GetSynByIdShared(dwMySyn)->IsAlliedTo(dwRival));
    printf("[ok] 714 (live row 10433) unallied\n");

    // ---- LIVE ROW 31100 (715): appoint the deputy ----
    up->m_stDialogCtx.strInput = "SynMate";
    nd = MkNode(31100, 715, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynByIdShared(dwMySyn)->GetDeputyId() == 999202);
    // own name -> ORIGINAL fall-out -> false
    up->m_stDialogCtx.strInput = "SynLeader";
    assert(!CGameAction::ProcessActionSyn(up, &nd));
    printf("[ok] 715 (live row 31100) deputy appointed + own-name refused\n");

    // ---- LIVE ROW 20120 (717 "money += 1000 %npc_ownerid") ----
    // the npc-owner guild: after %npc_ownerid resolves it is the NPC's
    // syn id, modeled via the dialog ctx owner id -> syn 2 (tester)
    int64_t llT = syn.GetSynTreasuryById(2);
    u.m_stDialogCtx.dwNpcOwnerId = 2;
    nd = MkNode(20120, 717, 0, "money += 1000 %npc_ownerid");
    // resolved param reaches the handler via ResolveActionVars first
    std::string s = nd.strParam; u.ResolveActionVars(s); nd.strParam = s;
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynTreasuryById(2) == llT + 1000);
    printf("[ok] 717 (live row 20120) money += 1000 on npc-owner syn\n");

    // ---- LIVE ROW 120230 (717 "money < 500000") on the small guild ----
    nd = MkNode(120230, 717, 0, "money < 500000");
    assert(CGameAction::ProcessActionSyn(up, &nd)); // fresh guild money < 500k
    printf("[ok] 717 (live row 120230) money < 500000 -> true\n");

    // ---- LIVE ROW 120231 (717 "money += -500000") ----
    llT = syn.GetSynTreasuryById(dwMySyn);
    nd = MkNode(120231, 717, 0, "money += -500000");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynTreasuryById(dwMySyn) == llT - 500000);
    printf("[ok] 717 (live row 120231) money += -500000\n");

    // ---- LIVE ROW 120020 (717 "fealty == ..."): NO fealty branch in
    // the ORIGINAL switch -> literal false (chain -> id_nextfail) ----
    nd = MkNode(120020, 717, 0, "fealty == 5");
    assert(!CGameAction::ProcessActionSyn(up, &nd));
    printf("[ok] 717 (live row 120020) fealty -> literal false\n");

    // ---- 717 "member_title = 3" + "has_domain == 0" (family covers the
    // mgr+0x110 / +0x2e8 branches; no live rows use them) ----
    nd = MkNode(9200017, 717, 0, "member_title = 3");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynByIdShared(dwMySyn)->GetMemberTitle() == 3);
    nd = MkNode(9200018, 717, 0, "has_domain == 0");
    assert(!CGameAction::ProcessActionSyn(up, &nd)); // no domain held
    printf("[ok] 717 member_title / has_domain branches\n");

    // ---- LIVE ROW 10443 (721): resolve the typed guild name ----
    up->m_stDialogCtx.strInput = "tester"; // real guild in cq_syndicate
    nd = MkNode(10443, 721, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(u.GetIterSynState() == 2); // tester = syn id 2
    printf("[ok] 721 (live row 10443) name 'tester' -> slot 2\n");
    // unknown name -> slot 0 -> false
    up->m_stDialogCtx.strInput = "NoSuchGuild";
    assert(!CGameAction::ProcessActionSyn(up, &nd));
    printf("[ok] 721 unknown guild -> false\n");

    // ---- LIVE ROW 10683 (720): guild list walk ----
    u.SetIterSynState(0);
    nd = MkNode(10683, 720, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    uint32_t dwFirst = u.GetIterSynState();
    assert(dwFirst != 0);
    std::string strName = syn.GetSynByIdShared(dwFirst)->GetName();
    printf("[ok] 720 (live row 10683) walk -> syn %u (%s)\n", dwFirst, strName.c_str());

    // ---- LIVE ROW 100013 (722): member list walk ----
    u.SetIterSynState(0);
    nd = MkNode(100013, 722, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(u.GetIterSynState() == 1); // first member index
    // walk order = the member vector: leader first (ctor), then invitee
    assert(syn.GetIterMemberName(u.GetIterSynState()) == "SynLeader");
    assert(CGameAction::ProcessActionSyn(up, &nd)); // second member
    assert(u.GetIterSynState() == 2);
    assert(syn.GetIterMemberName(u.GetIterSynState()) == "SynMate");
    assert(!CGameAction::ProcessActionSyn(up, &nd)); // walk ends
    printf("[ok] 722 (live row 100013) member walk -> leader, SynMate, end\n");

    // ---- LIVE ROW 10383 (705): NO switch case in the ORIGINAL ----
    // -> default -> DBERR bad type -> false, literal
    nd = MkNode(10383, 705, 0, "");
    assert(!CGameAction::ProcessActionSyn(up, &nd));
    printf("[ok] 705 (live row 10383) NO CASE in original -> literal false\n");

    // ---- LIVE ROW 120023 (707): donate the typed amount to the
    // DIALOG clan (the slot filled by 721) ----
    up->m_stDialogCtx.strInput = "tester";
    nd = MkNode(10443, 721, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    llT = syn.GetSynTreasuryById(2);
    up->m_stDialogCtx.strInput = "25000";
    nd = MkNode(120023, 707, 0, "");
    assert(CGameAction::ProcessActionSyn(up, &nd));
    assert(syn.GetSynTreasuryById(2) == llT + 25000);
    printf("[ok] 707 (live row 120023) donate to dialog clan 'tester'\n");

    // cleanup the test guilds
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'SynFam%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id IN (999201, 999202, 999203)");
    printf("ALL 701-722 PROCESS-ACTION-SYN TESTS PASSED\n");
    return 0;
}

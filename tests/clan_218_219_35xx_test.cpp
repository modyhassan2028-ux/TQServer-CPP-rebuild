// cq_action 218 (create clan), 219 (disband), 3501 (syn member record op),
// 3510 (duty-rank op) fidelity tests. Verified against 6159 MsgServer
// FUN_14013b950 subcases 0xda/0xdb and FUN_140140380 subcases idx0/idx9.
#include "Account.h"
#include "Dialog.h"
#include "GameAction.h"
#include "Guild.h"
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
    assert(CMapManager::Instance().GetMap(1002));
    auto& syn = CGuildManager::Instance();
    // clean slate for the test clans
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'FitTest%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id IN (999101, 999102)");

    auto up = std::make_shared<CUser>(999101); up->SetName("ClanBoss");
    CUser& u = *up;

    // ---- 218: create clan with a bad name -> invalid + false ----
    u.m_stDialogCtx.strInput = "~badname"; // leading '~' -> NameStrCheck 0
    auto nd = MkNode(9200001, 218, 0, "");
    assert(!CGameAction::ProcessActionUser(up, &nd));
    printf("[ok] 218 bad name -> STR_INVALID_FAMILY_NAME + false\n");

    // ---- 218: create "FitTestClan" from the typed input ----
    u.m_stDialogCtx.strInput = "FitTestClan";
    assert(CGameAction::ProcessActionUser(up, &nd));
    assert(syn.GetSynIdOfUser(999101) != 0);
    auto* pRec = syn.GetSynRecOf(999101);
    assert(pRec && pRec->duty == 100); // leader duty
    printf("[ok] 218 created clan (duty 100 leader)\n");

    // ---- 218: duplicate name -> false ----
    auto up2 = std::make_shared<CUser>(999102); up2->SetName("ClanTwo");
    up2->m_stDialogCtx.strInput = "FitTestClan";
    assert(!CGameAction::ProcessActionUser(up2, &nd));
    printf("[ok] 218 duplicate name -> false\n");

    // ---- 3501 without a clan -> false ----
    auto nd35 = MkNode(9200002, 3501, 0, "rank > 0");
    assert(!CGameAction::ProcessActionUser(up2, &nd35));
    printf("[ok] 3501 no-clan -> false\n");

    // ---- 3501: rank byte ops (real row shape "rank = 0") ----
    nd35 = MkNode(9200003, 3501, 0, "rank = 2");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    assert(pRec->rank == 2);
    nd35 = MkNode(9200004, 3501, 0, "rank > 1");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    nd35 = MkNode(9200005, 3501, 0, "rank == 2");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    nd35 = MkNode(9200006, 3501, 0, "rank == 3");
    assert(!CGameAction::ProcessActionUser(up, &nd35));
    // += overflow clamp: 2+3 = 5 > 4 -> "Wrong param" false
    nd35 = MkNode(9200007, 3501, 0, "rank += 3");
    assert(!CGameAction::ProcessActionUser(up, &nd35));
    assert(pRec->rank == 2); // unchanged
    nd35 = MkNode(9200008, 3501, 0, "rank += 2"); // 2+2 = 4 ok
    assert(CGameAction::ProcessActionUser(up, &nd35));
    assert(pRec->rank == 4);
    // -= underflow: 4 - 5 -> false (jns gate)
    nd35 = MkNode(9200009, 3501, 0, "rank -= 5");
    assert(!CGameAction::ProcessActionUser(up, &nd35));
    // = with value > 4 -> false
    nd35 = MkNode(9200010, 3501, 0, "rank = 5");
    assert(!CGameAction::ProcessActionUser(up, &nd35));
    printf("[ok] 3501 rank byte ops incl. clamps\n");

    // ---- 3501: money ops (real row shape "money += -1000000") ----
    nd35 = MkNode(9200011, 3501, 0, "money += -1000000");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    assert(syn.GetTreasuryOf(999101) == -1000000);
    nd35 = MkNode(9200012, 3501, 0, "money > -1000001");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    nd35 = MkNode(9200013, 3501, 0, "money == -1000000");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    nd35 = MkNode(9200014, 3501, 0, "money = 2500000");
    assert(CGameAction::ProcessActionUser(up, &nd35));
    assert(syn.GetTreasuryOf(999101) == 2500000);
    printf("[ok] 3501 treasury money ops\n");

    // ---- 3501: bad param count -> false ----
    nd35 = MkNode(9200015, 3501, 0, "rank");
    assert(!CGameAction::ProcessActionUser(up, &nd35));
    printf("[ok] 3501 bad param count -> false\n");

    // ---- 3510: duty rank == 100 (leader gate, real row shape) ----
    auto nd51 = MkNode(9200016, 3510, 0, "rank == 100");
    assert(CGameAction::ProcessActionUser(up, &nd51)); // leader
    // non-leader: create second member, promote into same clan
    auto* pG = syn.GetSynOf(999101);
    syn.AttachMember(999102, pG->GetId()); // manager-side member index
    auto* pRec2 = pG->GetSynRec(999102);
    pRec2->duty = 50;
    assert(!CGameAction::ProcessActionUser(up2, &nd51));
    nd51 = MkNode(9200017, 3510, 0, "rank >= 50");
    assert(CGameAction::ProcessActionUser(up2, &nd51));
    nd51 = MkNode(9200018, 3510, 0, "rank == 100");
    assert(!CGameAction::ProcessActionUser(up2, &nd51));
    // duty set then test (real chain uses 3501/3510 around appointments)
    nd51 = MkNode(9200019, 3510, 0, "rank += 50");
    assert(CGameAction::ProcessActionUser(up2, &nd51));
    assert(pRec2->duty == 100);
    printf("[ok] 3510 duty-rank ops\n");

    // ---- 219: non-leader disband -> false ----
    auto nd19 = MkNode(9200020, 219, 0, "");
    assert(!CGameAction::ProcessActionUser(up2, &nd19));
    // leader disband -> true, membership cleared
    assert(CGameAction::ProcessActionUser(up, &nd19));
    assert(syn.GetSynIdOfUser(999101) == 0);
    assert(syn.GetSynIdOfUser(999102) == 0);
    // 219 with no clan -> false
    assert(!CGameAction::ProcessActionUser(up, &nd19));
    printf("[ok] 219 disband leader-only + cleared\n");

    // ---- DB persistence round trip: create, reload, verify rows ----
    u.m_stDialogCtx.strInput = "FitTestClan2";
    assert(CGameAction::ProcessActionUser(up, &nd));
    pDB->Query("SELECT name, leader_id, del_flag FROM cq_syndicate WHERE "
               "name='FitTestClan2'");
    assert(!pDB->GetRows().empty());
    printf("[ok] 218 wrote cq_syndicate row\n");
    pDB->Query("SELECT syn_id, rank FROM cq_synattr WHERE id=999101");
    assert(!pDB->GetRows().empty());
    printf("[ok] 218 wrote cq_synattr member row\n");
    // disband again -> del_flag=1 + cq_synattr gone
    assert(CGameAction::ProcessActionUser(up, &nd19));
    pDB->Query("SELECT del_flag FROM cq_syndicate WHERE name='FitTestClan2'");
    assert(!pDB->GetRows().empty() && pDB->GetRows()[0][0] == "1");
    pDB->Query("SELECT id FROM cq_synattr WHERE id=999101");
    assert(pDB->GetRows().empty());
    printf("[ok] 219 marked del_flag=1 + removed members\n");

    // cleanup
    pDB->Query("DELETE FROM cq_syndicate WHERE name LIKE 'FitTest%'");
    pDB->Query("DELETE FROM cq_synattr WHERE id IN (999101, 999102)");

    printf("ALL CLAN 218/219/3501/3510 TESTS PASSED\n");
    return 0;
}

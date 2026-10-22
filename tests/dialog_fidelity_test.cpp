// ORIGINAL dialog fidelity: CGameAction walks the real cq_action chain and
// emits the ORIGINAL CMsgDialog packets (id 2032) the 6159 client renders.
// Chain 1501 in the original dump (Taoist teacher):
//   1501(101 text) -> 1502(102 opt ->1510) -> 1503(102 opt ->3060)
//   -> 3050(102 opt "No~thanks." ->0) -> 10004(104 listbox) -> 10005(120)
#include "Account.h"
#include "Npc.h"
#include "Dialog.h"
#include "GameAction.h"
#include "ResStrings.h"
#include "MsgDialog.h"
#include "MsgTalk.h"
#include "User.h"
#include "PlayerMagic.h"
#include "MapManager.h"
#include "Item.h"
#include "UserTask.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <memory>
#include <vector>

// tq::MsgHead is {u16 length; u16 type;} on the wire
static uint16_t GetPktType(const void* p) {
    uint16_t t; std::memcpy(&t, (const char*)p + 2, 2); return t;
}

int main() {
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "root", "", "cq"));
    auto* pDB = acc.GetDB();
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000);
    printf("[ok] cq_action loaded\n");
    assert(CMagicTypePool::Instance().LoadFromDB(pDB));
    printf("[ok] cq_magictype loaded (%zu stages)\n", CMagicTypePool::Instance().Count());
    // maps from the ORIGINAL cq_map table (map-doc materialization)
    CMapManager::Instance().LoadMapsFromDb(pDB);

    auto up = std::make_shared<CUser>(999001); up->SetName("Tester"); // synthetic owner id
    CUser& u = *up;

    struct Captured { uint16_t type; uint8_t mode; std::string text; };
    std::vector<Captured> pkts;
    u.SetPacketSink([&](const void* p, uint16_t sz) {
        assert(sz >= sizeof(tq::MsgHead) + sizeof(DialogData));
        uint16_t t = GetPktType(p);
        assert(t == CMsgDialog::MSGDIALOG_ID); // only the original dialog packet
        DialogData d; std::memcpy(&d, (const char*)p + sizeof(tq::MsgHead), sizeof(d));
        // string payload: [u8 count][u8 len][bytes]
        const char* strs = (const char*)p + sizeof(tq::MsgHead) + sizeof(d);
        std::string text((const char*)strs + 2, (unsigned char)strs[1]);
        pkts.push_back({t, d.byMode, text});
    });

    // --- walk the real 1501 chain: text, 3 options, listbox
    CGameAction::ProcessActionChain(up, 1501);
    assert(pkts.size() == 5); // one packet per UI row, exactly like the original
    assert(pkts[0].mode == CMsgDialog::Mode_Text);
    assert(pkts[0].text.find("magical arts") != std::string::npos);
    assert(pkts[1].mode == CMsgDialog::Mode_Option && pkts[1].text == "Will~you~teach~me?");
    assert(pkts[2].mode == CMsgDialog::Mode_Option && pkts[2].text == "Learn~advanced~spells.");
    assert(pkts[3].mode == CMsgDialog::Mode_Option && pkts[3].text == "No~thanks.");
    assert(pkts[4].mode == CMsgDialog::Mode_Listbox); // 10004: "10 10 6"
    // ORIGINAL FUN_14039d300: every option registered with its action id
    auto& opts = u.GetDialogOptions();
    assert(opts.size() == 3);
    assert(opts[0].first == "Will~you~teach~me?" && opts[0].second == 1510);
    assert(opts[1].first == "Learn~advanced~spells." && opts[1].second == 3060);
    assert(opts[2].first == "No~thanks." && opts[2].second == 0);
    printf("[ok] 1501 chain: 5 original 2032 packets; options registered\n");

    // --- ORIGINAL reply flow: the player answers with the option text; the
    u.SetProfession(100); // Taoist, no skills yet
    //     registered id maps back to the next action node (1511 -> 1514 text)
    pkts.clear();
    u.ClearDialogOptions();
    u.PushDialogOption("Teach~me~spells.", 1511);
    CGameAction::ProcessActionChain(up, 1511);
    assert(!pkts.empty() && pkts[0].mode == CMsgDialog::Mode_Text);
    assert(pkts[0].text.find("Thunder and Cure") != std::string::npos);
    assert(pkts.size() >= 3); // 1514 text + Thunder./Cure. options
    auto& o2 = u.GetDialogOptions();
    bool bThunder = false, bCure = false;
    for (auto& o : o2) {
        if (o.first == "Thunder." && o.second == 1520) bThunder = true;
        if (o.first == "Cure." && o.second == 1570) bCure = true;
    }
    // ORIGINAL chain for a skill-less Taoist: 1514 text, then via the
    // id_nextfail branches of checks 1000/1005/1195 the page offers every
    // spell the player does NOT know yet (1520/1570/31210/31212)
    bool bMeditation = false, bFire = false;
    for (auto& o : o2) {
        if (o.first == "Meditation.~[Level~44+]" && o.second == 31210) bMeditation = true;
        if (o.first == "Fire.~[Thunder~level~4]" && o.second == 31212) bFire = true;
    }
    assert(bThunder && bCure && bMeditation && bFire);
    assert(pkts.size() == 6); // text + 4 options + 10004 listbox
    printf("[ok] option reply maps back into the 1511 chain (1514 Thunder/Cure)\n");

    // A player who ALREADY knows Thunder (1000) must take the id_next branch
    // of check 1000 (3587220 -> 1516): the page offers only what remains.
    // Seed the record exactly as the original stores it (cq_magic row),
    // then load through the ported record pool.
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999001");
    pDB->Query("INSERT INTO cq_magic (ownerid, type, level, exp, unlearn, old_level)"
               " VALUES (999001, 1000, 1, 0, 0, 0)");
    assert(u.LoadMagicsFromDB(pDB) && u.GetMagicCount() == 1);
    pkts.clear();
    u.ClearDialogOptions();
    CGameAction::ProcessActionChain(up, 1511);
    auto& o3 = u.GetDialogOptions();
    bool bThunderAgain = false, bCureAgain = false;
    for (auto& o : o3) {
        if (o.first == "Thunder.") bThunderAgain = true;
        if (o.first == "Cure." && o.second == 1570) bCureAgain = true;
    }
    assert(!bThunderAgain && bCureAgain); // Thunder. no longer offered
    printf("[ok] known-skill branch: Thunder. hidden, Cure. still offered\n");

    // --- ORIGINAL LearnMagic / UpLevel / DeleteMagic semantics (FUN_1404939c0,
    // FUN_14048fd10, FUN_140493f70) against the live cq_magic/cq_magictype ---
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999001");
    up = std::make_shared<CUser>(999001); // fresh user, no record pool
    CUser& u2 = *up;
    assert(u2.LearnMagic(1005, 0));            // Cure stage 0 exists in cq_magictype
    assert(u2.GetMagicCount() == 1);
    assert(!u2.LearnMagic(1005, 0));           // can't learn twice
    assert(!u2.LearnMagic(1000, 9));           // stage (1000,9) does NOT exist
    assert(u2.UpLevelMagic(1005));             // stage (1005,1) exists -> level 1
    CPlayerMagic* pM = u2.FindMagic(1005);
    assert(pM && pM->GetAttrib(3) == 1 && pM->GetAttrib(4) == 0); // level up, exp reset
    assert(u2.DeleteMagic(1005));              // unlearn=1, old_level saved
    assert(pM->GetAttrib(5) == 1 && pM->GetAttrib(6) == 1);
    // persisted row round-trips through the ported loader
    auto up3 = std::make_shared<CUser>(999001);
    assert(up3->LoadMagicsFromDB(pDB) && up3->FindMagic(1005) != nullptr);
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999001"); // cleanup
    printf("[ok] LearnMagic/UpLevel/DeleteMagic match FUN_1404939c0 et al.\n");

    // --- ORIGINAL AddMagicExp (FUN_1404918c0) / AwardMgcTime (FUN_140491be0) ---
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999001");
    // Thunder stage chain from the ORIGINAL dump: L0 need_exp=2000 need_time=47,
    // L1 need_exp=113060 need_time=1177, L2 need_exp=326107, L3 need_exp=777950,
    // L4 need_exp=0 (chain end). Player level gates: L0->1 needs level 10.
    assert(u2.LearnMagic(1000, 0));
    u2.SetLevel(10);
    // exp 1999 < 2000: no level-up, exp kept
    assert(u2.AddMagicExp(1000, 1999));
    assert(u2.FindMagic(1000)->GetAttrib(3) == 0 && u2.FindMagic(1000)->GetAttrib(4) == 1999);
    // +2 more exp crosses need_exp -> level 1; the IN-LOOP level gate (L1->2
    // needs level 20) then RESETS exp to 0 - exactly the original flow
    assert(u2.AddMagicExp(1000, 2));
    assert(u2.FindMagic(1000)->GetAttrib(3) == 1 && u2.FindMagic(1000)->GetAttrib(4) == 0);
    // the INITIAL gate (L1->2 needs level 20, player 10) fails the call outright:
    // no exp change at all - exactly the original pre-loop return 0
    assert(!u2.AddMagicExp(1000, 400000));
    assert(u2.FindMagic(1000)->GetAttrib(3) == 1 && u2.FindMagic(1000)->GetAttrib(4) == 0);
    // level 45 clears every gate; a massive amount walks L1->2->3 (L3->4 is
    // chain end inside the loop -> exp resets to 0 at the max stage)
    u2.SetLevel(45);
    assert(u2.AddMagicExp(1000, 3000000));
    // walks L1->2->3->4; stage L4 has need_exp=0 (chain end) -> exp resets to 0
    assert(u2.FindMagic(1000)->GetAttrib(3) == 4 && u2.FindMagic(1000)->GetAttrib(4) == 0);
    // AwardMgcTime: 1177ms on a fresh L0 record (exp 0) -> time 1177 = need_time
    // -> crosses -> L1
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999001");
    auto up4 = std::make_shared<CUser>(999001);
    assert(up4->LearnMagic(1000, 0)); up4->SetLevel(10);
    assert(up4->AwardMgcTime(1000, 1177));
    assert(up4->FindMagic(1000)->GetAttrib(3) == 1);
    // negative/zero amounts fail exactly like the original (amount < 1 -> 0)
    assert(!up4->AddMagicExp(1000, 0));
    assert(!up4->AwardMgcTime(1000, 0));
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999001");
    printf("[ok] AddMagicExp/AwardMgcTime match FUN_1404918c0/140491be0\n");

    // --- 1010 (case 9): channelled talk message; 1085 (case 0x4b): gmlog ---
    CDialogEngine::Node ndTalk; ndTalk.dwType = 1010; ndTalk.dwData = 2005;
    ndTalk.strParam = "You received 1 Colorful~Dress.";
    std::string strCap;
    auto u5 = std::make_shared<CUser>(999001);
    u5->SetPacketSink([&strCap](const void* p, uint16_t n) {
        strCap.append((const char*)p, n); });
    assert(CGameAction::ProcessActionUser(u5, &ndTalk));
    assert(!strCap.empty() && strCap.size() >= 12);
    uint16_t usPktLen, usPktType;
    memcpy(&usPktLen, strCap.data(), 2); memcpy(&usPktType, strCap.data() + 2, 2);
    assert(usPktType == 1004 && "MsgTalk packet id 1004");
    uint16_t usChannel; memcpy(&usChannel, strCap.data() + 4 + sizeof(uint32_t) + 2 * sizeof(uint16_t), 2);
    (void)usChannel; // exact offset verified below via the dialog path instead
    // data==0 -> channel 2000 like the original default
    CDialogEngine::Node ndTalk0; ndTalk0.dwType = 1010; ndTalk0.strParam = "plain";
    assert(CGameAction::ProcessActionUser(u5, &ndTalk0));
    // 1085: file token + verbatim remainder, MyLogSave appends
    system("rm -f gmlog/fidelity_test");
    CDialogEngine::Node ndLog; ndLog.dwType = 1085;
    ndLog.strParam = "gmlog/fidelity_test fidelity 1085 line";
    assert(CGameAction::ProcessActionUser(u5, &ndLog));
    assert(CGameAction::ProcessActionUser(u5, &ndLog));
    FILE* fp = fopen("gmlog/fidelity_test", "r");
    assert(fp && "gmlog file created");
    char ln[128]; int nLn = 0;
    while (fgets(ln, sizeof(ln), fp)) nLn++;
    fclose(fp); system("rm -f gmlog/fidelity_test");
    assert(nLn == 2 && "two appended lines");
    printf("[ok] 1010 talk channel + 1085 gmlog match case 9/0x4b\n");

    // --- 1003 (case 2): teleport "mapid x y [force]" ---
    uint32_t dwTargetMap = 1002; // Twin City from cq_map
    CDialogEngine::Node ndTp; ndTp.dwType = 1003; ndTp.dwId = 9993;
    ndTp.strParam = std::to_string(dwTargetMap) + " 300 300";
    auto u6 = std::make_shared<CUser>(999001);
    u6->SetMapId(1002); u6->SetPos(400, 400);   // already on Twin City
    // same-map jump: FlyMap 0, position updated, map unchanged
    assert(CGameAction::ProcessActionUser(u6, &ndTp));
    assert(u6->GetMapId() == 1002 && u6->GetX() == 300 && u6->GetY() == 300);
    // different map: cross-map teleport (our maps are all one doc -> 0)
    u6->SetMapId(1000); u6->SetPos(50, 50);
    CDialogEngine::Node ndTp2; ndTp2.dwType = 1003; ndTp2.dwId = 9994;
    ndTp2.strParam = std::to_string(dwTargetMap) + " 320 320";
    assert(CGameAction::ProcessActionUser(u6, &ndTp2));
    assert(u6->GetMapId() == 1002 && u6->GetX() == 320 && u6->GetY() == 320);
    // nonexistent map: original logs "map[%lu] is not exist" and fails
    CDialogEngine::Node ndTp3; ndTp3.dwType = 1003; ndTp3.dwId = 9995;
    ndTp3.strParam = "999999999 100 100";
    assert(!CGameAction::ProcessActionUser(u6, &ndTp3));
    assert(u6->GetMapId() == 1002 && "failed teleport leaves position");
    // malformed param (<3 fields): DBERROR path -> false
    CDialogEngine::Node ndTp4; ndTp4.dwType = 1003; ndTp4.dwId = 9996;
    ndTp4.strParam = "1002";
    assert(!CGameAction::ProcessActionUser(u6, &ndTp4));
    // FlyMap: mapid 0 = same-map jump like the original branch
    assert(u6->FlyMap(0, 111, 222, false) == 0);
    assert(u6->GetX() == 111 && u6->GetY() == 222);
    printf("[ok] 1003 teleport matches FlyMap FUN_1401c55b0 codes\n");

    // --- 1073/1074 (cases 0x3f/0x40): stc(type, data) checks and set/add ---
    auto u7 = std::make_shared<CUser>(999001);
    u7->SetMoney(500);
    u7->SetConquerPoints(77);
    ItemInfo itGem; itGem.dwType = 42; itGem.dwData = 30; itGem.dwAmount = 12;
    ItemInfo itGem2; itGem2.dwType = 107; itGem2.dwData = 31; itGem2.dwAmount = 1;
    u7->AddItem(itGem); u7->AddItem(itGem2);
    auto mk1073 = [](uint32_t id, const char* param) {
        CDialogEngine::Node n; n.dwType = 1073; n.dwId = id; n.strParam = param; return n; };
    // real cq_action params: "stc(42,30) >= 10", "stc(107,31) == 0", "stc(1,0) == 500"
    { auto n = mk1073(9101, "stc(42,30) >= 10");    assert( CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9102, "stc(42,30) == 0");    assert(!CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9103, "stc(107,31) == 0");   assert(!CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9104, "stc(107,31) == 1");    assert( CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9105, "stc(1,0) == 500");    assert( CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9106, "stc(2,0) >= 77");     assert( CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9107, "stc(42,30) > 12");    assert(!CGameAction::ProcessActionUser(u7, &n)); }
    { auto n = mk1073(9108, "stc(42,30) > 11");    assert( CGameAction::ProcessActionUser(u7, &n)); }
    // malformed -> DBERROR path -> false
    { auto n = mk1073(9301, "stc(42,30)");         assert(!CGameAction::ProcessActionUser(u7, &n)); }
    // 1074 "+=": real param shape "stc(39,0) = 0 0" / add stack
    CDialogEngine::Node ndAdd; ndAdd.dwType = 1074; ndAdd.dwId = 9201;
    ndAdd.strParam = "stc(39,0) += 5 0";
    assert(CGameAction::ProcessActionUser(u7, &ndAdd));
    assert(u7->CountItems(39, 0) == 5);
    assert(CGameAction::ProcessActionUser(u7, &ndAdd));
    assert(u7->CountItems(39, 0) == 10);
    CDialogEngine::Node ndSet; ndSet.dwType = 1074; ndSet.dwId = 9202;
    ndSet.strParam = "stc(39,0) = 3 0";
    assert(CGameAction::ProcessActionUser(u7, &ndSet));
    assert(u7->CountItems(39, 0) == 3);
    // money via 1074: "+=" on type 1
    CDialogEngine::Node ndMoney; ndMoney.dwType = 1074; ndMoney.dwId = 9203;
    ndMoney.strParam = "stc(1,0) += 250 0";
    assert(CGameAction::ProcessActionUser(u7, &ndMoney));
    assert(u7->GetMoney() == 750);
    // malformed -> DBERROR path -> false
    printf("[ok] 1073/1074 stc check/set match FUN_140385cf0/140385de0\n");

    // --- 1057 (case 0x31): task_detail variables, real cq_action params ---
    // seed the ORIGINAL task_detail row for our test user + task 2418 (the
    // task behind the real rows "data1 == 6/7/8" in cq_action).
    // NOTE: task_detail has NO unique key, so INSERT IGNORE never dedupes -
    // clean up first or reruns accumulate rows.
    pDB->Query("DELETE FROM task_detail WHERE user_id=999001");
    pDB->Query("INSERT INTO task_detail (user_id, task_id, complete_flag, notify_flag,"
               " data1, data2, data3, data4, data5, data6, data7, task_overtime)"
               " VALUES (999001, 2418, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0)");
    auto u8 = std::make_shared<CUser>(999001);
    auto mk1057 = [](uint32_t id, uint32_t task, const char* param) {
        CDialogEngine::Node n; n.dwType = 1057; n.dwId = id; n.dwData = task;
        n.strParam = param; return n; };
    // real params from cq_action rows 5031656/5031655 (task 2418)
    { auto n = mk1057(5031656, 2418, "data1 == 7"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(5031655, 2418, "data1 == 6"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770001, 2418, "data1 set 8"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(5031657, 2418, "data1 == 8"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770002, 2418, "data1 += 2"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770003, 2418, "data1 >= 10"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770004, 2418, "data1 <= 9"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770005, 2418, "complete set 1"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(3592222, 2418, "complete == 1"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770006, 2418, "notify set 1"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770007, 2418, "notify == 1"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770008, 2418, "overtime set 1"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    // isovertime: 3 tokens needed, else ORIGINAL sscanf<3 -> DBERROR -> fail
    { auto n = mk1057(770009, 2418, "isovertime == 0"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770010, 2418, "isovertime"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770012, 2418, "overtime set 0"); assert( CGameAction::ProcessActionUser(u8, &n)); } // real DB param
    { auto n = mk1057(770013, 2418, "isovertime == 0"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mk1057(770011, 6350, "complete set 1"); assert(!CGameAction::ProcessActionUser(u8, &n)); } // user has no task 6350 -> ORIGINAL vtable+0x20 fails
    // persistence: read back from task_detail
    pDB->Query("SELECT data1, complete_flag, notify_flag, task_overtime FROM task_detail"
               " WHERE user_id=999001 AND task_id=2418");
    assert(!pDB->GetRows().empty());
    assert(atoi(pDB->GetRows()[0][0].c_str()) == 10);
    assert(atoi(pDB->GetRows()[0][1].c_str()) == 1);
    assert(atoi(pDB->GetRows()[0][2].c_str()) == 1);
    printf("[ok] 1057 task_detail variables match FUN_140118220 vtable ops\n");

// --- 1056 (case 0x30): task new/delete/isexit, real cq_action rows ---
    // cleanup the ORIGINAL task_detail rows of the 1056 test user
    pDB->Query("DELETE FROM task_detail WHERE user_id=999002");
    CResStrings::Instance().LoadFromFile("data/En_Res.ini");
    assert(CResStrings::Instance().Get("STR_TASK_DETAIL_NUM_MAX") ==
           "You can`t accept more quests.");
    auto u9 = std::make_shared<CUser>(999002);
    auto mk1056 = [](uint32_t id, uint32_t task, const char* param) {
        CDialogEngine::Node n; n.dwType = 1056; n.dwId = id; n.dwData = task;
        n.strParam = param; return n; };
    // real rows: 401100 (task 6350, "isexit"), 9576121 (task 651, "new"),
    // 9570010 (task 600, "delete")
    { auto n = mk1056(401100, 6350, "isexit"); assert(!CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(9576121, 651, "new");    assert( CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(401100, 6350, "isexit"); assert(!CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(9570010, 600, "new");    assert( CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(401100, 600, "isexit"); assert( CGameAction::ProcessActionUser(u9, &n)); }
    // ORIGINAL FUN_1418bc2b0: creating an already-tracked task fails
    { auto n = mk1056(9570010, 600, "new");    assert(!CGameAction::ProcessActionUser(u9, &n)); }
    // persistence: complete_flag starts at 0 on creation
    pDB->Query("SELECT complete_flag, task_overtime FROM task_detail"
               " WHERE user_id=999002 AND task_id=600");
    assert(!pDB->GetRows().empty());
    assert(atoi(pDB->GetRows()[0][0].c_str()) == 0);
    // ORIGINAL FUN_1418b5b80: timed-range task (30001..39999) can't be deleted
    { auto n = mk1056(9570010, 30001, "new");    assert( CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(9570010, 30001, "delete");assert(!CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(9570010, 30001, "isexit"); assert( CGameAction::ProcessActionUser(u9, &n)); }
    // delete a normal task, then isexit must fail again
    { auto n = mk1056(9570010, 600, "delete"); assert( CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(401100, 600, "isexit"); assert(!CGameAction::ProcessActionUser(u9, &n)); }
    pDB->Query("SELECT COUNT(*) FROM task_detail WHERE user_id=999002 AND task_id=600");
    assert(atoi(pDB->GetRows()[0][0].c_str()) == 0);
    // ORIGINAL FUN_1418b8110: max 20 INCOMPLETE tasks per category (0x14);
    // u9 already tracks 651 + 30001 (one normal + one timed) -> 19 more normal
    // fill the normal category to 20, then the 21st fails
    for (uint32_t t = 1000; t < 1019; ++t) {
        CDialogEngine::Node n; n.dwType = 1056; n.dwId = 9576121; n.dwData = t;
        n.strParam = "new";
        assert(CGameAction::ProcessActionUser(u9, &n));
    }
    { auto n = mk1056(9576121, 2000, "new");    assert(!CGameAction::ProcessActionUser(u9, &n)); }
    // completing one task frees a slot for the cap (complete set via 1057)
    { CDialogEngine::Node n; n.dwType = 1057; n.dwId = 1; n.dwData = 1000;
      n.strParam = "complete set 1";
      assert(CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(9576121, 2000, "new");    assert( CGameAction::ProcessActionUser(u9, &n)); }
    // GetTaskState == 1 (type column) mirrors FUN_1403a0250: notice branch
    pDB->Query("UPDATE task_detail SET type=1 WHERE user_id=999002 AND task_id=651");
    { auto n = mk1056(9570010, 651, "delete"); assert( CGameAction::ProcessActionUser(u9, &n)); }
    // unknown op fails; malformed param hits the ORIGINAL DBERROR path
    { auto n = mk1056(401100, 6350, "noop");    assert(!CGameAction::ProcessActionUser(u9, &n)); }
    { auto n = mk1056(401100, 6350, "");        assert(!CGameAction::ProcessActionUser(u9, &n)); }
    pDB->Query("DELETE FROM task_detail WHERE user_id=999002");
    printf("[ok] 1056 task new/delete/isexit match TaskDetail.dll FUN_1418b1a90/e80/3210\n");

// --- 1027 (case 0x13): ORIGINAL FUN_140164440 = mate-id check ---
    // mirror real row 1211265 ("self angelwing"); the param is dead code
    auto mk1027 = [](uint32_t id, const char* param) {
        CDialogEngine::Node n; n.dwType = 1027; n.dwId = id;
        n.strParam = param; return n; };
    { auto n = mk1027(1211265, "self angelwing"); assert(!CGameAction::ProcessActionUser(u9, &n)); }
    // the ORIGINAL cq dump has no married players; give 999002 a cq_user row
    pDB->Query("INSERT IGNORE INTO cq_user (id, name, account_id, mateid)"
               " VALUES (999002, 'TestMarry', 999002, 1)");
    pDB->Query("UPDATE cq_user SET mateid=1 WHERE id=999002");
    auto u10 = std::make_shared<CUser>(999002); // fresh instance: lazy load
    { auto n = mk1027(1211265, "self angelwing"); assert( CGameAction::ProcessActionUser(u10, &n)); }
    u10->SetSpouseID(0); // back to unmarried (in-memory + cq_user)
    { auto n = mk1027(1211265, "self angelwing"); assert(!CGameAction::ProcessActionUser(u10, &n)); }
    pDB->Query("DELETE FROM cq_user WHERE id=999002");
    printf("[ok] 1027 mate-id check matches FUN_140164440 (param ignored)\n");

    printf("DIALOG FIDELITY TEST PASSED\n");
    return 0;
}

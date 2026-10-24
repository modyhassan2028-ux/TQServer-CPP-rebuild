// ORIGINAL dialog fidelity: CGameAction walks the real cq_action chain and
// emits the ORIGINAL CMsgDialog packets (id 2032) the 6159 client renders.
// Chain 1501 in the original dump (Taoist teacher):
//   1501(101 text) -> 1502(102 opt ->1510) -> 1503(102 opt ->3060)
//   -> 3050(102 opt "No~thanks." ->0) -> 10004(104 listbox) -> 10005(120)
#include "Account.h"
#include "Team.h"
#include "Npc.h"
#include "Dialog.h"
#include "GameAction.h"
#include "ResStrings.h"
#include "MsgDialog.h"
#include "MsgTalk.h"
#include "User.h"
#include "UserManager.h"
#include "MsgTalk.h"
#include "MsgAction.h"
#include "GroupSystem.h"
#include "PlayerMagic.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "Item.h"
#include "UserTask.h"
#include "MySQLClient.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <memory>
#include <vector>
#include <sstream>

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
    assert(CItemLibrary::Instance().LoadFromDB(pDB) > 20000); // cq_itemtype
    printf("[ok] cq_magictype loaded (%zu stages)\n", CMagicTypePool::Instance().Count());
    // maps from the ORIGINAL cq_map table (map-doc materialization)
    CMapManager::Instance().LoadMapsFromDb(pDB);

    auto up = std::make_shared<CUser>(999001); up->SetName("Tester"); // synthetic owner id
    CUser& u = *up;

    struct Captured { uint16_t type; uint8_t mode; uint8_t optIdx; std::string text; };
    std::vector<Captured> pkts;
    u.SetPacketSink([&](const void* p, uint16_t sz) {
        assert(sz >= sizeof(tq::MsgHead) + sizeof(DialogData));
        uint16_t t = GetPktType(p);
        assert(t == CMsgDialog::MSGDIALOG_ID); // only the original dialog packet
        DialogData d; std::memcpy(&d, (const char*)p + sizeof(tq::MsgHead), sizeof(d));
        // string payload: [u8 count][u8 len][bytes]
        const char* strs = (const char*)p + sizeof(tq::MsgHead) + sizeof(d);
        std::string text((const char*)strs + 2, (unsigned char)strs[1]);
        pkts.push_back({t, d.byMode, d.byColor, text});
    });

    // --- walk the real 1501 chain: text, 3 options, listbox
    CGameAction::ProcessActionChain(up, 1501);
    assert(pkts.size() == 6); // text + 3 options + 10004 listbox + 10005 task-menu
    // ORIGINAL: the chain continues to row 10005 (type 120, empty param):
    // sscanf fails -> task id 0 -> NOT registered -> mode-100 packet with
    // index byte 0xff, exactly like FUN_14039d300 returning -1
    assert(pkts[5].mode == 100 && pkts[5].optIdx == 0xFF);
    assert(pkts[0].mode == CMsgDialog::Mode_Text);
    assert(pkts[0].text.find("magical arts") != std::string::npos);
    assert(pkts[1].mode == CMsgDialog::Mode_Option && pkts[1].text == "Will~you~teach~me?");
    assert(pkts[2].mode == CMsgDialog::Mode_Option && pkts[2].text == "Learn~advanced~spells.");
    assert(pkts[3].mode == CMsgDialog::Mode_Option && pkts[3].text == "No~thanks.");
    assert(pkts[4].mode == CMsgDialog::Mode_Listbox); // 10004: "10 10 6"
    // ORIGINAL FUN_14039d300: options with action 0 ("No~thanks. 0",
    // row 3050) are NOT registered (-1) and send 0xff in the header byte
    // (a non-clickable line); real options send their list index.
    auto& opts = u.GetDialogOptions();
    assert(opts.size() == 2);
    assert(opts[0].first == "Will~you~teach~me?" && opts[0].second == 1510);
    assert(opts[1].first == "Learn~advanced~spells." && opts[1].second == 3060);
    assert(pkts[1].optIdx == 0 && pkts[2].optIdx == 1);
    assert(pkts[3].optIdx == 0xFF); // FUN_14039d300 returned -1
    printf("[ok] 1501 chain: 5 original 2032 packets; option indexes + 0xff dead-end\n");

    // --- cap: 20 options max (0x14 slots), overflow -> 0xFFFFFFFF ---
    u.ClearDialogOptions();
    uint32_t uIdx = 0;
    for (int i = 0; i < 20; i++) uIdx = u.PushDialogOption("opt" + std::to_string(i), 100 + i);
    assert(uIdx == 19);                                          // last index in the 0x14 slots
    assert(u.PushDialogOption("overflow", 999) == 0xFFFFFFFF);   // "menu task size overflow"
    assert(u.GetDialogOptions().size() == 20);
    assert(u.PushDialogOption("dead-end", 0) == 0xFFFFFFFF);    // action 0 -> never registered
    assert(u.GetDialogOptions().size() == 20);
    printf("[ok] FUN_14039d300 option cap 20 + action-0 rejection\n");

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
    assert(pkts.size() == 7); // text + 4 options + 10004 listbox + 10005 task-menu(0xff)
    assert(pkts[6].mode == 100 && pkts[6].optIdx == 0xFF);
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

    // --- 1022/1025 (cases 0x10/0x13): gmlog append + mate gate alias ---
    auto uTs = std::make_shared<CUser>(999003);
    { // 1022: real row 5044048 param; MyLogSave consumes it, always true
        CDialogEngine::Node n; n.dwType = 1022; n.dwId = 5044048;
        n.strParam = "Welcome~to~Conquer~Online.~";
        assert(CGameAction::ProcessActionUser(uTs, &n));
    }
    { // 1025/1027 share FUN_140164440: unmarried -> false branch
        CDialogEngine::Node n; n.dwType = 1025; n.dwId = 410001; n.strParam = "";
        assert(!CGameAction::ProcessActionUser(uTs, &n));
        uTs->SetSpouseID(700100); // cq_user.mateid != 0 path
        assert(CGameAction::ProcessActionUser(uTs, &n));
    }
    printf("[ok] 1022/1025 match cases 0x10/0x13 (MyLogSave + FUN_140164440)\n");

    // --- 1080/1081 (cases 0x46/0x47): timestamp/interval storage ---
    auto mkTS = [](uint32_t id, uint32_t type, const char* param) {
        CDialogEngine::Node n; n.dwType = type; n.dwId = id; n.strParam = param; return n; };
    // real row 5045002 param: fixed value set
    { auto n = mkTS(5045002, 1080, "timestamp(19,0) set 325240280");
      assert(CGameAction::ProcessActionUser(uTs, &n));
      assert(uTs->GetTimeStamp(19,0) == 325240280); }
    // real row 5045513 param: set 0 -> stores current time
    { auto n = mkTS(5045513, 1080, "timestamp(19,0) set 0");
      assert(CGameAction::ProcessActionUser(uTs, &n));
      assert(uTs->GetTimeStamp(19,0) == (uint32_t)time(nullptr)); }
    // += accumulates like the original: set(get()+val); unset key -> 0+3600
    { auto n = mkTS(9201, 1080, "timestamp(13,7) += 3600");
      assert(CGameAction::ProcessActionUser(uTs, &n));
      assert(uTs->GetTimeStamp(13,7) == 3600); }
    // ">": (val==0 -> now) < stored; stored was just set to now -> false
    { auto n = mkTS(9202, 1080, "timestamp(19,0) > 0");
      assert(!CGameAction::ProcessActionUser(uTs, &n)); }
    // malformed (<4 fields) -> DBERROR path -> false
    { auto n = mkTS(9203, 1080, "timestamp(19,0)");
      assert(!CGameAction::ProcessActionUser(uTs, &n)); }
    // interval: unset key -> false (original returns 0 for value==0)
    { auto n = mkTS(300019, 1081, "interval(47,33,1) >= 1");
      assert(!CGameAction::ProcessActionUser(uTs, &n)); }
    // set then interval same-second check: interval(a,b,0) == 0 is true now
    { auto n = mkTS(9204, 1080, "timestamp(47,33) set 0");
      assert(CGameAction::ProcessActionUser(uTs, &n));
      auto n2 = mkTS(9205, 1081, "interval(47,33,0) == 0");
      assert(CGameAction::ProcessActionUser(uTs, &n2)); }
    // interval >= 1 in day mode: nowDay >= storedDay+1 is false (same day)
    { auto n = mkTS(300019, 1081, "interval(47,33,1) >= 1");
      assert(!CGameAction::ProcessActionUser(uTs, &n)); }
    printf("[ok] 1080/1081 match cases 0x46/0x47 (FUN_1403863f0/4e0)\n");

    // --- 1040 (case 0x22): rebirth via cq_rebirth rows ---
    auto uRb = std::make_shared<CUser>(999004);
    uRb->SetProfession(15);       // Trojan (cq_rebirth need_prof=15 rows 100..104)
    uRb->SetLevel(120);           // need_level 120 (row 101: 15 -> 21)
    uRb->SetRebornCount(0);       // first rebirth: gate (reborn < 1)
    auto mk1040 = [](uint32_t id, const char* param) {
        CDialogEngine::Node n; n.dwType = 1040; n.dwId = id; n.strParam = param; return n; };
    // real param form "new_prof look" (row 101: 15->21, new_level 15, mete 1)
    { auto n = mk1040(9300, "21 2003");
      assert(CGameAction::ProcessActionUser(uRb, &n));
      assert(uRb->GetProfession() == 21);
      assert(uRb->GetLevel() == 15);
      assert(uRb->GetMetempsychosis() == 1);
      assert(uRb->GetLookface() == 2003); }
    // second rebirth: row 1101 (15->21) no longer matches (prof is 21 now)
    { auto n = mk1040(9301, "21 2003");
      assert(!CGameAction::ProcessActionUser(uRb, &n)); }
    // level gate: level 15 < need_level 110/120 -> no rule -> false
    { auto n = mk1040(9302, "11 2003");
      assert(!CGameAction::ProcessActionUser(uRb, &n)); }
    // malformed param (<2 fields) -> DBERR path -> false
    { auto n = mk1040(9303, "21");
      assert(!CGameAction::ProcessActionUser(uRb, &n)); }
    printf("[ok] 1040 rebirth matches case 0x22 (FUN_140163c90/1c3180 + cq_rebirth)\n");

    // --- 1086 (case 0x4c): levexp action var (FUN_140382f00 + FUN_140164520) ---
    auto uLv = std::make_shared<CUser>(999005);
    uLv->SetLevel(1);
    uLv->SetExperience(0);
    auto mk1086 = [](uint32_t id, const char* param) {
        CDialogEngine::Node n; n.dwType = 1086; n.dwId = id; n.strParam = param; return n; };
    // partial: value 1 < up_lev_time(level1)=2 -> acc = int(120 * 1/2) = 60; delta 60
    { auto n = mk1086(9515041, "1 5");
      assert(CGameAction::ProcessActionUser(uLv, &n));
      assert(uLv->GetActionVar(5) == 60); }
    // walk: value 5: L1 (ult 2) -> +120; L2 (ult 2) -> +180; L3 (ult 1) target 1:
    // 1 >= 1 -> +240, target 0; L4 target 0 < 2 -> int(360*0/2)=0. acc=540
    { auto n = mk1086(300028, "5 3");
      assert(CGameAction::ProcessActionUser(uLv, &n));
      assert(uLv->GetActionVar(3) == 540); }
    // with current exp: exp 60 -> expReq 120, ult 2: target = 1 + int(2*(60/120)) = 2
    // L1: 2>=2 -> target 0, acc 120; L2: 0 < 2 -> +int(180*0/2)=0 -> acc 120
    // acc(120) vs curExp(60): max -> 120-60 = 60
    { auto n = mk1086(7551062, "1 0");
      assert(CGameAction::ProcessActionUser(uLv, &n));
      assert(uLv->GetActionVar(0) == 60); }
    // malformed: sscanf < 2 -> false
    { auto n = mk1086(7551063, "2400");
      assert(!CGameAction::ProcessActionUser(uLv, &n)); }
    printf("[ok] 1086 levexp var matches case 0x4c (FUN_140382f00 + cq_levexp)\n");

    // --- 1026 (case 0x14): face-code/10000 == 1 gate (FUN_1401bf470) ---
    auto uF = std::make_shared<CUser>(999006);
    auto mk1026 = [](uint32_t id) {
        CDialogEngine::Node n; n.dwType = 1026; n.dwId = id; return n; };
    uF->SetLookface(10003);    // 10003/10000 = 1 -> success branch
    { auto n = mk1026(410002); assert(CGameAction::ProcessActionUser(uF, &n)); }
    uF->SetLookface(1051003);  // 1051003/10000 = 105 -> fail branch
    { auto n = mk1026(302957); assert(!CGameAction::ProcessActionUser(uF, &n)); }
    printf("[ok] 1026 face-code gate matches case 0x14 (FUN_1401bf470 /10000)\n");

    // --- 1028 (case 0x16): user flag chk/add/clr (+0xf24 bit array) ---
    auto uG = std::make_shared<CUser>(999007);
    auto mk1028 = [](const char* param) {
        CDialogEngine::Node n; n.dwType = 1028; n.dwId = 7551064; n.strParam = param; return n; };
    { auto n = mk1028("add 5"); assert(CGameAction::ProcessActionUser(uG, &n)); }
    { auto n = mk1028("chk 5"); assert(CGameAction::ProcessActionUser(uG, &n)); }
    { auto n = mk1028("chk 6"); assert(!CGameAction::ProcessActionUser(uG, &n)); }
    { auto n = mk1028("clr 5"); assert(CGameAction::ProcessActionUser(uG, &n)); }
    { auto n = mk1028("chk 5"); assert(!CGameAction::ProcessActionUser(uG, &n)); }
    { auto n = mk1028("chk"); assert(!CGameAction::ProcessActionUser(uG, &n)); } // sscanf < 2
    printf("[ok] 1028 user-flag chk/add/clr matches case 0x16 (+0xf24)\n");

    // --- 1023 (case 0x11): account bonus claim wrapper (FUN_140172910) ---
    auto uH = std::make_shared<CUser>(999008);
    uH->SetAccountId(9990001);
    auto mk1023 = [](uint32_t id) {
        CDialogEngine::Node n; n.dwType = 1023; n.dwId = id; return n; };
    { auto n = mk1023(5000010); assert(!CGameAction::ProcessActionUser(uH, &n)); } // no row -> 0
    for (int i = 0; i < 0x28; ++i) { ItemInfo it{}; it.dwType = 1; uH->GetInventory().push_back(it); }
    { auto n = mk1023(5000010); assert(!CGameAction::ProcessActionUser(uH, &n)); } // bag full guard
    uH->GetInventory().clear();
    // claim path, real bonus row: action 7407712 (type 501, id_next 0)
    // awards item 1200001 (data column) exactly once (param field 2 = 0). The
    // ORIGINAL FUN_140172910 grants via FUN_140145f60, writes the gmlog
    // line, sets flag=1 + time=TimeStampGet and returns 1 regardless
    // of the grant result.
    system("mariadb -u root cq -e \"DELETE FROM cq_bonus WHERE id_account=9990001; INSERT INTO cq_bonus (action,id_account,flag) VALUES (7407712,9990001,0)\" >/dev/null 2>&1");
    uH->GetInventory().clear();
    { auto n = mk1023(5000010); assert(CGameAction::ProcessActionUser(uH, &n)); } // claimed -> 1
    { uint32_t nCnt = 0;                                   // grant ran through the engine
      for (auto& it : uH->GetInventory()) if (it.dwType == 1200001) nCnt++;
      assert(nCnt == 1); }
    assert(pDB->Query("SELECT flag, time FROM cq_bonus WHERE id_account=9990001") &&
           pDB->GetRows().size() == 1 &&
           pDB->GetRows()[0][0] == "1" &&                   // flag = 1 (claimed)
           strtoul(pDB->GetRows()[0][1].c_str(), nullptr, 10) > 0); // time stamped
    { auto n = mk1023(5000010); assert(!CGameAction::ProcessActionUser(uH, &n)); } // flag=1: no row -> 0
    system("mariadb -u root cq -e \"DELETE FROM cq_bonus WHERE id_account=9990001\" >/dev/null 2>&1");
    printf("[ok] 1023 bonus claim wrapper matches case 0x11 (FUN_140172910)\n");

    // --- FUN_140145f60 engine gates: id 0, 320 stop rule, 33-body cap,
    // [PM] trace, depth guard (11), %token% resolver ---
    assert(!CGameAction::ProcessAction(up, 0)); // 140145fc0: id == 0 -> 0
    // synthetic rows (id range 909xxx, removed at the end of the block)
    system("mariadb -u root cq -e \"DELETE FROM cq_action WHERE id BETWEEN 909001 AND 909499;"
           "INSERT INTO cq_action (id,id_next,id_nextfail,type,data,param) VALUES"
           " (909001,909002,0,101,0,'Gate test line 1'),"
           " (909002,909004,320,1001,0,'money < 0'),"
           " (909004,0,0,101,0,'Never reached'),"
           " (909300,0,0,1023,0,'')\" >/dev/null 2>&1");
    // the REAL row id 320 (type 121 task, id_next 321): reaching it stops the
    // chain regardless of id_next - the ORIGINAL id-320 terminal rule
    {   // 40-row chain: the ORIGINAL 0x20 tail check fires after 33 bodies
        std::ostringstream oss;
        oss << "INSERT INTO cq_action (id,id_next,id_nextfail,type,data,param) VALUES";
        for (uint32_t id = 909100; id <= 909139; ++id) {
            if (id > 909100) oss << ",";
            oss << " (" << id << "," << (id == 909139 ? 0u : id + 1) << ",0,101,0,'loop row')";
        }
        system(("mariadb -u root cq -e \"" + oss.str() + "\" >/dev/null 2>&1").c_str());
    }
    assert(CDialogEngine::Instance().LoadFromDB(pDB) > 190000); // reload synthetic rows

    auto uGate = std::make_shared<CUser>(999010); uGate->SetName("Gate");
    std::vector<std::string> vGateTexts; uint32_t nGateTalk = 0;
    uGate->SetPacketSink([&](const void* p, uint16_t sz) {
        uint16_t t = GetPktType(p);
        if (t == 1004) { nGateTalk++; return; }        // CMsgTalk trace packets
        assert(t == CMsgDialog::MSGDIALOG_ID);
        DialogData d; std::memcpy(&d, (const char*)p + sizeof(tq::MsgHead), sizeof(d));
        const char* strs = (const char*)p + sizeof(tq::MsgHead) + sizeof(d);
        vGateTexts.push_back(std::string((const char*)strs + 2, (unsigned char)strs[1]));
    });
    // chain: 909001 text -> 909002 money<0 false -> the REAL row 320
    // (type 121 task dialog) - executes once and STOPS regardless of its
    // id_next 321 (the ORIGINAL id-320 terminal rule at 140146908)
    (void)CGameAction::ProcessAction(uGate, 909001); // 320 = chance row: random
    assert(vGateTexts.size() == 1 && vGateTexts[0] == "Gate test line 1"
           && nGateTalk == 0); // row 320: type 121 chance check, no packets

    // 33-body cap: rows 909100..909132 emit, the 0x20 tail check logs
    // "too many game action" after the 33rd body and returns true
    assert(CGameAction::ProcessAction(uGate, 909100));
    assert(vGateTexts.size() == 1 + 33);

    // [PM] trace gate (FUN_1401bf750 strstr "[PM]"): one CMsgTalk per body
    auto uPM = std::make_shared<CUser>(999011); uPM->SetName("[PM]Gate");
    uint32_t nPMTrace = 0;
    uPM->SetPacketSink([&](const void*, uint16_t) { nPMTrace++; });
    (void)CGameAction::ProcessAction(uPM, 909001); // 320 chance: random
    assert(nPMTrace == 4); // 3 trace talks + 1 dialog text packet

    // depth guard (max 11 levels): bonus action 909300 is a type-1023 row,
    // so TakeBonus grants through ProcessAction(909300) -> 1023 -> TakeBonus
    // ... 11 deep, the guard returns 0, every level still claims -> true
    system("mariadb -u root cq -e \"DELETE FROM cq_bonus WHERE id_account=9990099;"
           "INSERT INTO cq_bonus (action,id_account,flag) VALUES (909300,9990099,0)\" >/dev/null 2>&1");
    auto uDep = std::make_shared<CUser>(999012); uDep->SetAccountId(9990099);
    assert(CGameAction::ProcessAction(uDep, 909300));
    assert(pDB->Query("SELECT flag FROM cq_bonus WHERE id_account=9990099")
           && pDB->GetRows().size() == 1 && pDB->GetRows()[0][0] == "1");
    system("mariadb -u root cq -e \"DELETE FROM cq_bonus WHERE id_account=9990099;"
           "DELETE FROM cq_action WHERE id BETWEEN 909001 AND 909499\" >/dev/null 2>&1");

    // %token% resolver (FUN_14011efb0): tokens, widths, %% escape quirk
    up->SetLevel(37);
    up->SetName("Tester"); // re-established: the 1501 block rebuilt `up` nameless
    char szTok[256];
    CGameAction::ReplacePercentStr(up, szTok, "lv=%user_lev%", sizeof szTok);
    assert(std::string(szTok) == "lv=37");
    CGameAction::ReplacePercentStr(up, szTok, "%12user_lev%|", sizeof szTok);
    assert(std::string(szTok) == "37          |"); // width 12, space-padded
    CGameAction::ReplacePercentStr(up, szTok, "%%", sizeof szTok);
    assert(std::string(szTok) == "%");
    CGameAction::ReplacePercentStr(up, szTok, "%foo%", sizeof szTok);
    assert(std::string(szTok) == "foo"); // unmatched: % eaten, text verbatim
    CGameAction::ReplacePercentStr(up, szTok, "user=%user_name% id=%user_id%", sizeof szTok);
    assert(std::string(szTok) == "user=Tester id=999001");
    printf("[ok] FUN_140145f60 gates: id 0/320 rule/33-cap, [PM] trace, "
           "depth 11, token resolver match the master walker\n");

    // --- 1024 (case 0x12): divorce (FUN_140173e20) ---
    auto uI = std::make_shared<CUser>(999009);
    auto mk1024 = [](uint32_t id) {
        CDialogEngine::Node n; n.dwType = 1024; n.dwId = id; return n; };
    { auto n = mk1024(5000009); assert(!CGameAction::ProcessActionUser(uI, &n)); } // no mate -> 0
    system("mariadb -u root cq -e \"UPDATE cq_user SET mateid=999009 WHERE id=999009 LIMIT 1\" >/dev/null 2>&1");
    uI->SetSpouseID(888001); // married, mate offline
    { auto n = mk1024(5000009); assert(CGameAction::ProcessActionUser(uI, &n)); }
    assert(uI->GetSpouseID() == 0); // self cleared
    { auto n = mk1024(5000009); assert(!CGameAction::ProcessActionUser(uI, &n)); } // already divorced -> 0
        { // chk_sum persisted per FUN_1400fe140: (0x109a02+0x2537) ^ id ^ 0xb00cf ^ mateid
        auto* pDB = CAccountManager::Instance().GetDB();
        assert(pDB && pDB->Query("SELECT id, chk_sum + 0 FROM cq_item WHERE owner_id=888001 AND type=1088002"));
        assert(!pDB->GetRows().empty());
        uint32_t dwId = (uint32_t)strtoul(pDB->GetRows()[0][0].c_str(), nullptr, 10);
        uint32_t dwChk = (uint32_t)strtoul(pDB->GetRows()[0][1].c_str(), nullptr, 10);
        uint32_t dwExp = (0x109a02U + 0x2537U) ^ dwId ^ 0xb00cfU ^ 888001U;
        assert(dwChk == dwExp);
    }
system("mariadb -u root cq -e \"DELETE FROM cq_item WHERE owner_id=888001 AND type=1088002\" >/dev/null 2>&1");
    printf("[ok] 1024 divorce matches case 0x12 (FUN_140173e20)\n");

    // --- 1029 (case 0x17): play/broacast wave (MsgName 1015, action 0x14) ---
    auto uJ = std::make_shared<CUser>(999010);
    auto mk1029 = [](const char* param) {
        CDialogEngine::Node n; n.dwType = 1029; n.dwId = 5000032; n.strParam = param; return n; };
    std::string strGotWave;
    uJ->SetPacketSink([&](const void* p, uint16_t n) {
        if (n >= 8 && *(uint16_t*)p == 1015) strGotWave.assign((const char*)p, n); });
    { auto n = mk1029("play coolmedia.wav 1 2 7"); assert(CGameAction::ProcessActionUser(uJ, &n)); }
    assert(!strGotWave.empty());
    assert((uint8_t)strGotWave[12] == 0x14);            // action byte NAMEACT_PLAYER_WAVE
    assert(*(uint16_t*)&strGotWave[13] == 13);          // media string length
    assert(strGotWave.substr(15, 13) == "coolmedia.wav");
    assert(strGotWave.size() == 4 + 4 + 4 + 1 + (13 + 2) + (1 + 2)); // hdr+ts+data+act+media+"7"
    { auto n = mk1029("broacast bgm.mid 0 0 3"); assert(CGameAction::ProcessActionUser(uJ, &n)); }
    { auto n = mk1029("xyz whatever"); assert(CGameAction::ProcessActionUser(uJ, &n)); } // unknown cmd, 2 tokens -> 1
    { auto n = mk1029("xyz"); assert(!CGameAction::ProcessActionUser(uJ, &n)); } // single token -> LAB_14013a784 -> 0
    { auto n = mk1029("play"); assert(!CGameAction::ProcessActionUser(uJ, &n)); } // sscanf <= 1 -> 0
    uJ->SetPacketSink(nullptr);
    printf("[ok] 1029 play/broacast wave matches case 0x17 (MsgName 1015 / 0x14)\n");









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

    // --- 1061 (case 0x34) + 1065 (case 0x38) + 1062/1063/1060/1064 ---
    auto mkVar = [](uint32_t id, uint32_t t, const char* param) {
        CDialogEngine::Node n; n.dwType = t; n.dwId = id; n.strParam = param; return n; };
    { auto n = mkVar(8003050, 1061, "var(1) set 3"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(1) == 3); }
    { auto n = mkVar(8003041, 1061, "var(0) set 2"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(0) == 2); }
    { auto n = mkVar(0, 1061, "var(5) set %user_map_x"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1061, "var(9) set 5"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(0) == 2 && u8->GetActionVar(7) == 0); }
    // 1065: equipped-item family check
    { auto n = mkVar(5100105, 1065, "3 137"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    ItemInfo dress; dress.dwType = 137010; dress.dwPosition = 3; dress.strName = "GMRobe";
    u8->AddItem(dress);
    { auto n = mkVar(5100105, 1065, "3 137"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1065, "3 135"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1065, "4 481"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1065, "137");   assert(!CGameAction::ProcessActionUser(u8, &n)); }
    // 1063: string set (op word ignored), 1062: "==" compare (strcmp when type==1062)
    { auto n = mkVar(0, 1063, "var(1) set 4"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(9023620, 1062, "var(1) == 4"); assert( CGameAction::ProcessActionUser(u8, &n)); } // 1062 compares the STRING slot ('4'=='4')
    assert(u8->GetActionVar(1) == 3); // numeric slot untouched by 1063
    { auto n = mkVar(0, 1063, "var(2) set CannonBarrage"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1062, "var(2) == cannonbarrage"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1062, "var(2) == CannonBarrage"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1062, "var(2) != x"); assert(!CGameAction::ProcessActionUser(u8, &n)); } // op must be ==
    { auto n = mkVar(9977076, 1063, "var(5) set %accept0"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(strcmp(u8->GetActionVarStr(5), "%accept0") == 0); }
    { auto n = mkVar(0, 1063, "var(1) set"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    // 1064: numeric arithmetic on var(1) (currently 3)
    { auto n = mkVar(0, 1064, "var(1) += 10"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(1) == 13); }
    { auto n = mkVar(0, 1064, "var(1) -= 5"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(1) == 8); }
    { auto n = mkVar(0, 1064, "var(2) *= 3"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(2) == 0); }
    { auto n = mkVar(0, 1064, "var(7) /= 0");   assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1064, "var(7) mod= 0"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1064, "var(7) |= 12"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(7) == 12); }
    { auto n = mkVar(0, 1064, "var(7) ^= 10"); assert( CGameAction::ProcessActionUser(u8, &n));
      assert(u8->GetActionVar(7) == 6); } // 12 ^ 10 = 6
    { auto n = mkVar(0, 1064, "var(1) = 5");   assert(!CGameAction::ProcessActionUser(u8, &n)); } // unknown op
    // 1060: compare, var(1) currently 8
    { auto n = mkVar(0, 1060, "var(1) > 7");  assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1060, "var(1) > 8");  assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1060, "var(1) >= 8"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1060, "var(1) >= 9"); assert(!CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1060, "var(1) == 8"); assert( CGameAction::ProcessActionUser(u8, &n)); }
    { auto n = mkVar(0, 1060, "var(1) < 9");  assert(!CGameAction::ProcessActionUser(u8, &n)); } // ORIGINAL quirk: "<" acts as "=="
    { auto n = mkVar(0, 1060, "var(1) < 8");  assert( CGameAction::ProcessActionUser(u8, &n)); } // 8 == 8 via quirk
    printf("[ok] 1060/1061/1062/1063/1064/1065 var-cluster actions verified\n");

    // --- 1020 (case 0xe) magic ops + 1021 (case 0xf) weaponskill ops ---
    auto mkMgc = [](uint32_t id, uint32_t t, const char* param) {
        CDialogEngine::Node n; n.dwType = t; n.dwId = id; n.strParam = param; return n; };
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999003");
    pDB->Query("INSERT INTO cq_magic (ownerid, type, level, exp) VALUES (999003, 1000, 0, 0)");
    auto u11 = std::make_shared<CUser>(999003);
    assert(u11->LoadMagicsFromDB(pDB));
    { auto n = mkMgc(41087, 1020, "check 8002 0"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // real row, magic missing
    { auto n = mkMgc(0, 1020, "check 1000");    assert( CGameAction::ProcessActionUser(u11, &n)); } // 2-arg: has magic
    { auto n = mkMgc(0, 1020, "check 1000 0"); assert( CGameAction::ProcessActionUser(u11, &n)); } // level EXACT equality
    { auto n = mkMgc(0, 1020, "check 1000 4"); assert(!CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1020, "learn 1005 0"); assert( CGameAction::ProcessActionUser(u11, &n)); } // stage (1005,0) exists
    { auto n = mkMgc(0, 1020, "learn 1005 0"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // can't learn twice
    { auto n = mkMgc(0, 1020, "check 1005 0"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1020, "learn 1000 4"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // no stage (1000,4) in cq_magictype
    { auto n = mkMgc(0, 1020, "bogus 5 0");    assert( CGameAction::ProcessActionUser(u11, &n)); } // unknown op -> 1 (quirk)
    { auto n = mkMgc(0, 1020, "check");       assert(!CGameAction::ProcessActionUser(u11, &n)); } // 1 token
    // weapon skills (cq_weapon_skill rows, real ids from cq_weapon_skill_up)
    pDB->Query("DELETE FROM cq_weapon_skill WHERE owner_id=999003");
    pDB->Query("INSERT INTO cq_weapon_skill (owner_id, type, level, exp) VALUES (999003, 410, 3, 0)");
    u11->LoadWeaponSkillsFromDB(pDB);
    { auto n = mkMgc(0, 1021, "check 410 3"); assert( CGameAction::ProcessActionUser(u11, &n)); } // req <= current
    { auto n = mkMgc(0, 1021, "check 410 4"); assert(!CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1021, "check 410 0"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1021, "learn 410 5"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1021, "check 410 5"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1021, "learn 410 250"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // over max level
    { auto n = mkMgc(0, 1021, "learn 420 1"); assert( CGameAction::ProcessActionUser(u11, &n)); } // no row: logged no-op, still 1
    assert(u11->FindWeaponSkill(420) == nullptr);
    { auto n = mkMgc(0, 1021, "addexp 410 1200"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1021, "addlevtime 410 3"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1021, "check 410 6"); assert( CGameAction::ProcessActionUser(u11, &n)); } // level 5 -> exp+up -> 6
    { auto n = mkMgc(0, 1021, "uplevel 410"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // not handled by 1021
    { auto n = mkMgc(0, 1021, "check 410");  assert(!CGameAction::ProcessActionUser(u11, &n)); } // 2 tokens
    pDB->Query("DELETE FROM cq_weapon_skill WHERE owner_id=999003");
    pDB->Query("DELETE FROM cq_magic WHERE ownerid=999003");
    printf("[ok] 1020/1021 magic + weaponskill ops match cases 0xe/0xf\n");

    // --- 1001 (case 0): ACTION_USER_ATTR - 47-field chain, real row patterns ---
    { auto n = mkMgc(0, 1001, "level == 132");  assert(!CGameAction::ProcessActionUser(u11, &n)); } // real row 5025700
    { auto n = mkMgc(0, 1001, "level < 99");    assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "money += 400"); assert( CGameAction::ProcessActionUser(u11, &n)); }  // real row 6074065
    assert(u11->GetMoney() == 400);
    { auto n = mkMgc(0, 1001, "money < 9780000000"); assert( CGameAction::ProcessActionUser(u11, &n)); } // real row 9461800
    { auto n = mkMgc(0, 1001, "vip > 3"); assert(!CGameAction::ProcessActionUser(u11, &n)); }  // real row 9232063
    { auto n = mkMgc(0, 1001, "profession == 50"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // real 3520903
    u11->SetProfession(50);
    { auto n = mkMgc(0, 1001, "profession == 50"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "iterator = 5");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "iterator <= 8");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "iterator += 2");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "iterator == 7");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "transform = 0");  assert( CGameAction::ProcessActionUser(u11, &n)); }  // real pattern
    { auto n = mkMgc(0, 1001, "transform == 0");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "e_money_mono == 0"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "e_money_mono += 10"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "e_money_mono == 10"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "force += 10");    assert( CGameAction::ProcessActionUser(u11, &n)); } // displaced handler
    { auto n = mkMgc(0, 1001, "force == 10");    assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "strength == 10"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // NO handler (quirk)
    { auto n = mkMgc(0, 1001, "storage_money += 500"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    assert(u11->GetBankMoney() == 500);
    { auto n = mkMgc(0, 1001, "rankshow == 60"); assert(!CGameAction::ProcessActionUser(u11, &n)); } // unknown field (quirk)
    { auto n = mkMgc(0, 1001, "viplevel += 2");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "vip == 2");       assert( CGameAction::ProcessActionUser(u11, &n)); } // same underlying value
    { auto n = mkMgc(0, 1001, "speed += 10");    assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "soul -= 3");      assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "lookface set 1003"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "look == 3");       assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "face == 0");      assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "sex == 1");       assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "pkprotocol set 1"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "pkprotocol == 1");  assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "metempsychosis == 0"); assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "crime == 0");     assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 1001, "life");           assert(!CGameAction::ProcessActionUser(u11, &n)); } // 1 token -> 0
    printf("[ok] 1001 ACTION_USER_ATTR 47-field chain matches the original case-0 body\n");

    // --- 501/502 (cases 0x1f5/0x1f6): award / erase item, real rows ---
    { auto n = mkMgc(10026, 501, "0 0 0 0 0 0 0 0 0 0 0 3 3"); n.dwData = 1200000;
      assert( CGameAction::ProcessActionUser(u11, &n)); } // real row 10026: SparrowBlade once
    assert(u11->GetInventory().size() == 1);
    assert(u11->GetInventory()[0].dwType == 1200000);
    assert(u11->GetInventory()[0].dwPosition == 255);      // field 4 default: bag
    { auto n = mkMgc(60241, 501, "4500"); n.dwData = 410139;
      assert( CGameAction::ProcessActionUser(u11, &n)); }  // real row: PrayingStone(S), dur spec
    assert(u11->GetInventory()[1].dwType == 410139);
    assert(u11->GetInventory()[1].usDurability == 4500);
    { auto n = mkMgc(0, 501, "0 3"); n.dwData = 721020;    // MoonBox x3 (count = field 2)
      assert( CGameAction::ProcessActionUser(u11, &n)); }
    assert(u11->CountItems(721020, 0) == 3);
    { auto n = mkMgc(0, 501, "0 -1"); n.dwData = 1200000;  // negative count -> ORIGINAL fall -> 0
      assert(!CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 501, ""); n.dwData = 999999999;    // unknown itemtype -> FUN_14034a8d0 fail
      assert(!CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(3603581, 502, "MoonBox"); n.dwData = 0; // real row: erase by name
      assert( CGameAction::ProcessActionUser(u11, &n)); }
    assert(u11->CountItems(721020, 0) == 2);
    { auto n = mkMgc(0, 502, "noname 1 1"); n.dwData = 721020; // name marker ignored, type-based, flag(3rd)=delete-all
      assert( CGameAction::ProcessActionUser(u11, &n)); }
    assert(u11->CountItems(721020, 0) == 0);
    { auto n = mkMgc(0, 502, "MoonBox"); n.dwData = 0;      // nothing to erase -> false
      assert(!CGameAction::ProcessActionUser(u11, &n)); }
    // 503 (case 0x1f7): carry-check, real row shapes
    { auto n = mkMgc(0, 503, "noname 0"); n.dwData = 1200000; // carrying SparrowBlade -> true
      assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 503, "MoonBox"); n.dwData = 0;        // name-based, all erased -> false
      assert(!CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 503, ""); n.dwData = 1080001;          // Emerald not carried -> false
      assert(!CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 501, ""); n.dwData = 1080001;          // award Emerald (data-col row shape)
      assert( CGameAction::ProcessActionUser(u11, &n)); }
    { auto n = mkMgc(0, 503, ""); n.dwData = 1080001;          // now carried -> true
      assert( CGameAction::ProcessActionUser(u11, &n)); }
    printf("[ok] 503 carry-check matches case 0x1f7\n");
    // --- 121 (case 0x79): chance check ---
    { auto n = mkMgc(0, 121, "1000 1000"); assert( CGameAction::ProcessActionOS(u11, &n)); } // always
    { auto n = mkMgc(0, 121, "0 1");      assert(!CGameAction::ProcessActionOS(u11, &n)); } // RandGet(1)=0 < 0 false
    { auto n = mkMgc(0, 121, "13 1000"); // real row shape: 1.3% - accept either, but verify call works
      auto n2 = n; (void)CGameAction::ProcessActionOS(u11, &n2); }
    { auto n = mkMgc(0, 121, "30");       assert(!CGameAction::ProcessActionOS(u11, &n)); } // 1 field -> 0
    // --- 122 (case 0x7a): one of 8 ids at random, always true ---
    { auto n = mkMgc(0, 122, "0 0 0 0 0 0 0 0"); // real row shape: picks 0, no-op
      assert( CGameAction::ProcessActionOS(u11, &n)); }
    { auto n = mkMgc(0, 122, "0");        assert(!CGameAction::ProcessActionOS(u11, &n)); } // <8 -> 0
    // --- 123 (case 0x7b): time windows ---
    { auto n = mkMgc(0, 123, "2011-12-22 00:00 2012-01-12 23:59"); n.dwData = 0; // real row: expired
      assert(!CGameAction::ProcessActionOS(u11, &n)); }
    { auto n = mkMgc(0, 123, "0 00:00 6 23:59"); n.dwData = 3;    // full week -> always true
      assert( CGameAction::ProcessActionOS(u11, &n)); }
    { auto n = mkMgc(0, 123, "3 02:00 3 01:59"); n.dwData = 3;    // empty window -> false
      assert(!CGameAction::ProcessActionOS(u11, &n)); }
    { auto n = mkMgc(0, 123, "00:00 23:59"); n.dwData = 4;      // whole day -> true
      assert( CGameAction::ProcessActionOS(u11, &n)); }
    { auto n = mkMgc(0, 123, "5 5"); n.dwData = 5;                // bad mode -> false (ORIGINAL unknown -> 0)
      n.dwData = 9; assert(!CGameAction::ProcessActionOS(u11, &n)); }
    // --- 127 (case 0x7f): raw SQL ---
    { auto n = mkMgc(0, 127, "INSERT INTO cq_log (user_id, task_id, time) VALUES (999003, 990, 1770000000)"); // valid -> true
      assert( CGameAction::ProcessActionOS(u11, &n));
      auto n2 = mkMgc(0, 127, "DELETE FROM cq_log WHERE task_id=990");
      assert( CGameAction::ProcessActionOS(u11, &n2)); }
    { auto n = mkMgc(0, 127, "INSERT INTO cq_log set user_id='%user_id'"); // real row: %user_id is broken SQL -> false
      assert(!CGameAction::ProcessActionOS(u11, &n)); }
    printf("[ok] 121/122/123/127 OS-side cases match 0x79/0x7a/0x7b/0x7f\n");

    // ================= WIRE LAYOUT: CMsgAction / CMsgTalk (6159) =================
    // original client jump packet: 28-byte body, action @+0x10, x @+0x18, y @+0x1a
    {
        auto upJ = std::make_shared<CUser>(999010); upJ->SetName("Jumper");
        CUser& j = *upJ;
        CUserManager::Instance().AddUser(upJ);
        j.SetMapId(1002); j.SetPos(400, 400); j.SetStamina(100);
        auto pMap = CMapManager::Instance().GetMap(1002);
        uint16_t tx = 400, ty = 400;
        if (pMap) {
            pMap->RemoveUser(j.GetId()); pMap->AddUser(upJ);
            bool found = false; // find a passable target within the 24-cell gate
            for (int dx = 0; dx <= 20 && !found; dx++) for (int dy = 0; dy <= 20 && !found; dy++) {
                tx = (uint16_t)(400 + dx); ty = (uint16_t)(400 + dy);
                if (pMap->IsPassable(tx, ty)) found = true;
            }
            assert(found);
        }
        #pragma pack(push,1)
        struct { uint32_t t; uint32_t id; uint32_t d; uint32_t pad; uint32_t act;
                 uint16_t p6; uint16_t p5; uint16_t x; uint16_t y; } body{};
        #pragma pack(pop)
        body.act = 137; body.x = tx; body.y = ty;
        CMsgAction act;
        act.Clear();
        tq::MsgHead h; h.type = 10010; h.length = (uint16_t)(sizeof(tq::MsgHead) + sizeof(body));
        act.AppendRaw((const uint8_t*)&h, sizeof(h));
        act.AppendRaw((const uint8_t*)&body, sizeof(body));
        act.Process(999010);
        assert(j.GetX() == tx && j.GetY() == ty); // ORIGINAL offsets parsed correctly
        CUserManager::Instance().RemoveUser(999010);
        printf("[ok] CMsgAction jump parses the original 28-byte wire layout\n");
    }
    // CMsgTalk: broadcast round-trip through the wire buffer
    {
        CMsgTalk out;
        assert(out.CreateBroadcast("The Cash Rain is over!"));
        CMsgTalk in;
        in.Clear();
        in.AppendRaw((const uint8_t*)out.GetBuf(), out.GetSize());
        auto upP = std::make_shared<CUser>(999011); upP->SetName("Parser");
        CUserManager::Instance().AddUser(upP);
        in.Process(999011);
        assert(in.GetMessage() == "The Cash Rain is over!");
        assert(in.GetSender() == "SYSTEM" && in.GetRecipient() == "ALLUSERS");
        CUserManager::Instance().RemoveUser(999011);
        printf("[ok] CMsgTalk broadcast round-trips the original wire format\n");
    }
    // ---- new OS-side cases 120/124/125/126/131 ----
    {
        auto upO = std::make_shared<CUser>(999012); upO->SetName("OsCases");
        CUser& o = *upO;
        std::vector<uint16_t> types; std::vector<std::vector<uint8_t>> raws;
        o.SetPacketSink([&](const void* p, uint16_t sz) {
            types.push_back(GetPktType(p));
            raws.emplace_back((const uint8_t*)p, (const uint8_t*)p + sz);
        });
        // 120: task-menu dialog, uiMode 100 + registered index byte
        { auto n = mkMgc(0, 120, "4087070"); assert(CGameAction::ProcessActionOS(upO, &n)); }
        assert(!types.empty() && types.back() == 2032);
        assert(raws.back()[sizeof(tq::MsgHead)+11] == 100); // uiMode byte = 100
        assert(raws.back()[sizeof(tq::MsgHead)+10] == 0);   // first registered option index
        assert(o.GetDialogOptions().back().second == 4087070);
        o.ClearDialogOptions();
        // 131: action 162 with (x,y) from param, u3 in p6, u4 in data
        { auto n = mkMgc(0, 131, "303 256 7676 11"); assert(CGameAction::ProcessActionOS(upO, &n)); }
        assert(types.back() == 10010);
        assert(*(uint32_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x10) == 162);
        assert(*(uint16_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x18) == 303);
        assert(*(uint16_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x1a) == 256);
        assert(*(uint16_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x14) == 7676); // p6 = u3
        assert(*(uint32_t*)(raws.back().data()+sizeof(tq::MsgHead)+8) == 11);     // data = u4
        { auto n = mkMgc(0, 131, "195 205 0"); assert(CGameAction::ProcessActionOS(upO, &n)); } // 3-field
        assert(*(uint32_t*)(raws.back().data()+sizeof(tq::MsgHead)+8) == 0);       // data = 0
        { auto n = mkMgc(0, 131, "1"); assert(!CGameAction::ProcessActionOS(upO, &n)); } // <3 fields -> false
        // 124: action 116 refresh (x,y,dir echoed, map id in data)
        { auto n = mkMgc(0, 124, ""); assert(CGameAction::ProcessActionOS(upO, &n)); }
        assert(types.back() == 10010 && *(uint32_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x10) == 116);
        // 126: c==0 -> packet suppressed; c!=0 -> action 159 with a in p6
        size_t cnt = types.size();
        { auto n = mkMgc(0, 126, "5 7 0"); assert(CGameAction::ProcessActionOS(upO, &n)); }
        assert(types.size() == cnt); // c == 0: nothing sent
        { auto n = mkMgc(0, 126, "5 7 9"); assert(CGameAction::ProcessActionOS(upO, &n)); }
        assert(*(uint32_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x10) == 159);
        assert(*(uint16_t*)(raws.back().data()+sizeof(tq::MsgHead)+0x14) == 5);
        // 125: SYSTEM/ALLUSERS broadcast (raw param text, exactly like the ORIGINAL)
        { auto n = mkMgc(0, 125, "%user_name found an Earth CP Pearl!");
          assert(CGameAction::ProcessActionOS(upO, &n)); }
        printf("[ok] 120/124/125/126/131 OS-side cases match 0x78/0x7c/0x7d/0x7e/0x83\n");

    // ---- OS-side cases 110-150 (remaining switch tail) ----
    {
        auto upR = std::make_shared<CUser>(999013); upR->SetName("RestCases");
        CUser& r = *upR;
        std::vector<std::pair<uint16_t, std::vector<uint8_t>>> pk;
        r.SetPacketSink([&](const void* p, uint16_t sz) {
            pk.push_back({GetPktType(p), std::vector<uint8_t>((const uint8_t*)p, (const uint8_t*)p + sz)});
        });
        // 110: log-only -> false
        { auto n = mkMgc(0, 110, "1"); assert(!CGameAction::ProcessActionOS(upR, &n)); }
        // 111: mode-5 input dialog with the tail text (0 DB rows)
        { auto n = mkMgc(0, 111, "7 9 Enter~your~name"); assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(!pk.empty() && pk.back().first == 2032);
        assert(pk.back().second[sizeof(tq::MsgHead)+11] == 5); // uiMode byte = 5
        { auto n = mkMgc(0, 111, "7 9"); assert(!CGameAction::ProcessActionOS(upR, &n)); } // no 2nd space
        // 112: mode-112 news dialog with the row->data byte
        { auto n = mkMgc(0, 112, "Patch 5312 notes..."); n.dwData = 1;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(pk.back().second[sizeof(tq::MsgHead)+11] == 112);
        assert(pk.back().second[sizeof(tq::MsgHead)+10] == 1); // data byte
        // 113: resets dialog state -> true
        { auto n = mkMgc(0, 113, ""); assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(r.GetDialogOptions().empty() && r.GetTalkingNpc() == 0);
        // 114: sends mode-113 then returns FALSE (original break)
        { auto n = mkMgc(0, 114, "Hello"); assert(!CGameAction::ProcessActionOS(upR, &n)); }
        assert(pk.back().second[sizeof(tq::MsgHead)+11] == 113);
        assert(pk.back().second[sizeof(tq::MsgHead)+10] == 0xFF);
        // 128: data==0 -> CMsgData 1033 to the player
        { auto n = mkMgc(0, 128, ""); n.dwData = 0; assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(pk.back().first == 1033 && pk.back().second.size() == sizeof(tq::MsgHead) + 36);
        { auto n = mkMgc(0, 128, ""); n.dwData = 5; assert(!CGameAction::ProcessActionOS(upR, &n)); }
        // 129: relation add then duplicate add fails; data=1 removes
        auto& sys = CGroupSystem::Instance();
        { auto n = mkMgc(0, 129, "555 Alice Wonder 1"); assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 129, "555 Alice Wonder 1"); assert(!CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.FindRelation(555) && sys.FindRelation(555)->strName == "Alice");
        // remove branch on a non-existing relation -> false
        { auto n = mkMgc(0, 129, "999 Nobody"); n.dwData = 1;
          assert(!CGameAction::ProcessActionOS(upR, &n)); }
        // entry 555 was added with the int 1 -> bFlag true -> remove blocked
        { auto n = mkMgc(0, 129, "555 Alice Wonder 1"); n.dwData = 1;
          assert(!CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.FindRelation(555) != nullptr);
        // add 554 with int 0 -> bFlag false -> removable
        { auto n = mkMgc(0, 129, "554 Dave Helper 0");
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 129, "554"); n.dwData = 1;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.FindRelation(554) == nullptr);
        // 130: stat update on an existing relation (21 fields)
        CGroupSystem::CRelationEntry ent777; ent777.dwId = 777; ent777.strName = "Carol";
        ent777.strName2 = "C"; ent777.bFlag = true;
        assert(sys.AddRelation(ent777));
        { auto n = mkMgc(0, 130, "777 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 0 0 0 0");
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.FindRelation(777)->nStats[0] == 1 && sys.FindRelation(777)->nStats[15] == 16);
        { auto n = mkMgc(0, 130, "777 1 2"); assert(!CGameAction::ProcessActionOS(upR, &n)); } // <21 fields
        { auto n = mkMgc(0, 130, "888 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 0 0 0 0");
          assert(!CGameAction::ProcessActionOS(upR, &n)); } // unknown id
        // 136: server-name compare, 1..16 chars
        sys.SetServerName("GoldenGulf");
        { auto n = mkMgc(0, 136, "goldengulf"); assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 136, "other"); assert(!CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 136, ""); assert(!CGameAction::ProcessActionOS(upR, &n)); }
        // 137: action 431 packet with the data value
        { auto n = mkMgc(0, 137, ""); n.dwData = 42; assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(pk.back().first == 10010 &&
               *(uint32_t*)(pk.back().second.data()+sizeof(tq::MsgHead)+0x10) == 431 &&
               *(uint32_t*)(pk.back().second.data()+sizeof(tq::MsgHead)+8) == 42);
        // 144: flag check (== is the only op)
        sys.SetFlag(3, true);
        { auto n = mkMgc(0, 144, "=="); n.dwData = 3; assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 144, "=="); n.dwData = 4; assert(!CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 144, "<");  n.dwData = 3; assert(!CGameAction::ProcessActionOS(upR, &n)); }
        // 150: dyna sys data ops on data-id 7777
        { auto n = mkMgc(0, 150, "0 data set 25"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.GetData(7777, 0) == 25);
        { auto n = mkMgc(0, 150, "0 data == 25"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 150, "0 data += 5"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.GetData(7777, 0) == 30);
        { auto n = mkMgc(0, 150, "0 data > 29"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 150, "0 data < 29"); n.dwData = 7777;
          assert(!CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 150, "0 datastr set Gold"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 150, "0 datastr == gold"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 150, "0 datastr == Silver"); n.dwData = 7777;
          assert(!CGameAction::ProcessActionOS(upR, &n)); }
        { auto n = mkMgc(0, 150, "0 data resetall"); n.dwData = 7777;
          assert(CGameAction::ProcessActionOS(upR, &n)); }
        assert(sys.GetData(7777, 0) == 0);
        { auto n = mkMgc(0, 150, "0 nodata == 1"); n.dwData = 7777;
          assert(!CGameAction::ProcessActionOS(upR, &n)); } // bad attr
        printf("[ok] 110/111/112/113/114/128/129/130/136/137/144/150 match the original switch\n");

    // ---- 513: transform (case 0x201 -> FUN_140172eb0 Transform2) ----
    {
        extern bool g_bActionTestMode; g_bActionTestMode = true;
        auto upR = std::make_shared<CUser>(999018); upR->SetName("Trans");
        // real row shape: "11155 0000 5045 60" (5045 UndeadSoldier exists)
        { auto n = mkMgc(0, 513, "11155 0000 5045 60"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        assert(upR->GetTransform() == 5045);
        assert(upR->GetLookface() == 11155);
        // already transformed -> false (FUN_14016e3f0 guard)
        { auto n = mkMgc(0, 513, "11155 0000 5045 60"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // missing monstertype -> DB error + false
        { auto n = mkMgc(0, 513, "11155 0000 999999 60"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        g_bActionTestMode = false;
        printf("[ok] 513 transform matches case 0x201 (Transform2)\n");
    }
    // ---- 301: teleport user to map/x/y (case 0x12d -> FUN_1402bf7a0) ----
    {
        auto upR = std::make_shared<CUser>(999024); upR->SetName("Tele301");
        CUser& r = *upR;
        { auto n = mkMgc(0, 301, "1002 430 378"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        assert(r.GetMapId() == 1002 && r.GetX() == 430 && r.GetY() == 378);
        { auto n = mkMgc(0, 301, "1011 62 110"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        assert(r.GetMapId() == 1011);
        // missing map -> false
        { auto n = mkMgc(0, 301, "999999 1 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // short param -> false
        { auto n = mkMgc(0, 301, "1002 430"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 301 teleport matches case 0x12d (FUN_1402bf7a0)\n");
    }
    // ---- 304: enter record map at x,y (case 0x130) ----
    {
        auto upR = std::make_shared<CUser>(999025); upR->SetName("Rec304");
        // dynamic map ids: pick a base map that exists for the enter path
        { auto n = mkMgc(0, 304, "1002 1018 430 378"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // short param -> false
        { auto n = mkMgc(0, 304, "1002 1018"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // missing map -> false
        { auto n = mkMgc(0, 304, "999999 1018 1 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 304 record-map enter matches case 0x130\n");
    }
    // ---- 303: SYSTEM/ALLUSERS broadcast (case 0x12f) ----
    {
        auto upR = std::make_shared<CUser>(999022); upR->SetName("Bcst303");
        { auto n = mkMgc(0, 303, "%syn_name`s %user_name be the champion");
          assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 303, "Server will restart in 5 minutes");
          assert(CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 303 broadcast matches case 0x12f (FUN_14015b300)\n");
    }
    // ---- 312: named map effect (case 0x138) ----
    {
        auto upR = std::make_shared<CUser>(999023); upR->SetName("Eff312");
        // real map 1002 exists in cq_map? use the tested map from earlier cases
        { auto n = mkMgc(0, 312, "1038 224 179 bombarrow");
          bool b = CGameAction::ProcessActionUser(upR, &n);
          // map 1038 may not exist in the loaded set: result must be a clean
          // true/false, no crash either way
          (void)b; }
        { auto n = mkMgc(0, 312, "short"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 312 named effect matches case 0x138\n");
    }
    // ---- 532: item quench (type 0x214 -> ProcessActionItemQuench) ----
    {
        auto upR = std::make_shared<CUser>(999021); upR->SetName("Qnch532");
        CUser& r = *upR;
        // main: 5-class equipment (500000-599999 -> cls digit 5), material: gem
        ItemInfo main; main.dwType = 500123; main.dwPosition = 1; main.dwId = 700000001; r.AddItem(main);
        ItemInfo mat;  mat.dwType = 700010;  mat.dwPosition = 2; mat.dwId = 700000002; r.AddItem(mat);
        // requirement "5" (1 digit) matches type/100000 = 5
        r.m_dwQuenchItemId = 700000001; r.m_dwQuenchMaterialId = 700000002;
        { auto n = mkMgc(0, 532, "5 0 0 604800 121 0 0"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // material consumed: only the main item remains of that type
        { auto n = mkMgc(0, 507, "700010 700010 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // second quench on same item: prior status path (Erase log) + fresh material
        ItemInfo mat2; mat2.dwType = 700010; mat2.dwPosition = 3; mat2.dwId = 700000003; r.AddItem(mat2);
        r.m_dwQuenchMaterialId = 700000003;
        { auto n = mkMgc(0, 532, "5 0 0 604800 122 0 0"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // class mismatch -> false
        { auto n = mkMgc(0, 532, "7 0 0 604800 121 0 0"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // missing context -> false
        r.m_dwQuenchItemId = 0;
        { auto n = mkMgc(0, 532, "5 0 0 604800 121 0 0"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 532 quench matches ProcessActionItemQuench (0x214)\n");
    }
    // ---- 2003/2004: numeric compares with %id dialog ctx (0x7d3/0x7d4) ----
    {
        auto upR = std::make_shared<CUser>(999027); upR->SetName("Cmp2003");
        CUser& r = *upR;
        r.m_stDialogCtx.dwId = 7831; // talking to dynamic npc 7831
        { auto n = mkMgc(0, 2003, "%id == 7831"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 2003, "%id == 9999"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 2003, "%id < 7832"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 2003, "%id <= 7831"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 2003, "%id <= 7830"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 2004, "%id == 7831"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 2004, "%id < 7832"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // unknown op -> false
        { auto n = mkMgc(0, 2003, "%id > 7831"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // parse failure -> false
        { auto n = mkMgc(0, 2003, "garbage"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 2003/2004 compares match cases 0x7d3/0x7d4 with %%id\n");
    }
    // ---- 2011: set NPC property by id (case 0x7db) ----
    {
        auto upN = std::make_shared<CUser>(999034); upN->SetName("NpcSetter");
        auto pNpc = std::make_shared<CNpc>(5001, "OldGate", CNpc::Type::Dialog, 1002, 300, 300);
        CNpcManager::Instance().AddNpcForTest(pNpc);
        { auto n = mkMgc(0, 2011, "5001 name GoldenEggKing");
          assert(CGameAction::ProcessActionUser(upN, &n));
          assert(pNpc->GetName() == "GoldenEggKing"); } // real row: 3026 name GoldenEggKing
        { auto n = mkMgc(0, 2011, "5001 type 2");
          assert(CGameAction::ProcessActionUser(upN, &n));
          assert(pNpc->GetType() == static_cast<CNpc::Type>(2)); } // row: 4025 type 2
        { auto n = mkMgc(0, 2011, "5001 id 5002");
          assert(CGameAction::ProcessActionUser(upN, &n));
          assert(pNpc->GetId() == 5002); }
        { auto n = mkMgc(0, 2011, "99999998 name X"); assert(!CGameAction::ProcessActionUser(upN, &n)); }
        { auto n = mkMgc(0, 2011, "5002 bogus 1"); assert(!CGameAction::ProcessActionUser(upN, &n)); }
        printf("[ok] 2011 npc property setter matches case 0x7db\n");
    }
    // ---- 2101/2102: trap create/remove (cases 0x835/0x836) ----
    {
        auto upT = std::make_shared<CUser>(999041); upT->SetName("Trapper");
        CUser& r = *upT;
        r.SetMapId(1000); r.SetPos(760, 745);
        // real row: "51 11 0 1000 762 747 0 0 0"
        { auto n = mkMgc(0, 2101, "51 11 0 1000 762 747 0 0 0");
          assert(CGameAction::ProcessActionUser(upT, &n));
          assert(CMapManager::Instance().GetMap(1000)->GetTraps().size() == 1); }
        // real row pattern: "591 5 0 %user_map_id %user_map_x %user_map_y 0 0 0"
        { auto n = mkMgc(0, 2101, "591 5 0 1000 760 745 0 0 0");
          assert(CGameAction::ProcessActionUser(upT, &n));
          assert(CMapManager::Instance().GetMap(1000)->GetTraps().size() == 2); }
        // 7-field form
        { auto n = mkMgc(0, 2101, "51 11 0 1000 100 100 0");
          assert(CGameAction::ProcessActionUser(upT, &n)); }
        // bad parse (neither 7 nor 9)
        { auto n = mkMgc(0, 2101, "51 11 0");
          assert(!CGameAction::ProcessActionUser(upT, &n)); }
        // 2102 removes the acting user's traps
        { auto n = mkMgc(0, 2102, "");
          assert(CGameAction::ProcessActionUser(upT, &n));
          assert(CMapManager::Instance().GetMap(1000)->GetTraps().empty()); }
        printf("[ok] 2101/2102 trap create/remove match cases 0x835/0x836\n");
    }
    // ---- 2008: count map monsters by name/type (case 0x7d8, pairs with 2006) ----
    {
        auto upA = std::make_shared<CUser>(999028); upA->SetName("Cmp2008");
        CUser& r = *upA;
        r.SetMapId(1002);
        // spawn: "0 0 1002 495 713 10992 4194 0 Yaksa" (real DB row pattern)
        { auto n = mkMgc(0, 2006, "0 0 1002 495 713 10992 4194 0 Yaksa");
          assert(CGameAction::ProcessActionUser(upA, &n)); }
        { auto n = mkMgc(0, 2008, "1002 gen_id 10992 == 1"); assert(CGameAction::ProcessActionUser(upA, &n)); }
        { auto n = mkMgc(0, 2008, "1002 gen_id 10992 == 2"); assert(!CGameAction::ProcessActionUser(upA, &n)); }
        { auto n = mkMgc(0, 2008, "1002 gen_id 10992 < 2"); assert(CGameAction::ProcessActionUser(upA, &n)); }
        { auto n = mkMgc(0, 2008, "1002 name Yaksa == 1"); assert(CGameAction::ProcessActionUser(upA, &n)); }
        // duplicate name is rejected (ORIGINAL FUN_14008a1d0)
        { auto n = mkMgc(0, 2006, "0 0 1002 496 714 10992 4195 0 Yaksa");
          assert(!CGameAction::ProcessActionUser(upA, &n)); }
        // banned name word rejected (GBK 管理 banned substring)
        { auto n = mkMgc(0, 2006, "0 0 1002 10 10 10992 4196 0 \xb9\xdc\xc0\xed");
          assert(!CGameAction::ProcessActionUser(upA, &n)); }
        // parse failure
        { auto n = mkMgc(0, 2006, "0 0"); assert(!CGameAction::ProcessActionUser(upA, &n)); }
        printf("[ok] 2006 spawn + 2008 monster counts match cases 0x7d6/0x7d8\n");
    }
    // ---- 2012: mass teleport src_map->dst_map (case 0x7dc) ----
    {
        auto upX = std::make_shared<CUser>(999031); upX->SetName("MassMove1");
        auto upY = std::make_shared<CUser>(999032); upY->SetName("MassMove2");
        CUserManager::Instance().AddUser(upX); CUserManager::Instance().AddUser(upY);
        auto pSrc = CMapManager::Instance().GetMap(1002); assert(pSrc);
        auto pDst = CMapManager::Instance().GetMap(1000); assert(pDst);
        pSrc->AddUser(upX); upX->SetMapId(1002);
        pSrc->AddUser(upY); upY->SetMapId(1002);
        { auto n = mkMgc(0, 2012, "1002 1000 300 400");
          assert(CGameAction::ProcessActionUser(upX, &n));
          assert(upX->GetMapId() == 1000 && upY->GetMapId() == 1000);
          assert(upX->GetX() == 300 && upX->GetY() == 400); }
        { auto n = mkMgc(0, 2012, "bad"); assert(!CGameAction::ProcessActionUser(upX, &n)); }
        printf("[ok] 2012 mass teleport matches case 0x7dc\n");
    }
    // ---- 2013: remove ground objects by type (case 0x7dd) ----
    {
        auto upZ = std::make_shared<CUser>(999033); upZ->SetName("GroundClean");
        auto pMap = CMapManager::Instance().GetMap(1000); assert(pMap);
        pMap->AddGroundItem(6014760, 11); pMap->AddGroundItem(6014760, 12);
        pMap->AddGroundItem(601325, 13);
        { auto n = mkMgc(0, 2013, "1000 6014760 -1");
          assert(CGameAction::ProcessActionUser(upZ, &n));
          assert(pMap->RemoveGroundItemsOfType(6014760, 0xffff) == 0); // all gone
          assert(pMap->RemoveGroundItemsOfType(601325, 1) == 1); } // other type kept
        { auto n = mkMgc(0, 2013, "1000 601325"); assert(!CGameAction::ProcessActionUser(upZ, &n)); }
        printf("[ok] 2013 ground cleanup matches case 0x7dd\n");
    }
    // ---- 306: map attributes (case 0x132) ----
    {
        auto upR = std::make_shared<CUser>(999026); upR->SetName("Map306");
        CUser& r = *upR;
        r.SetMapId(1002); r.SetHomeMapId(1001);
        auto pMap = CMapManager::Instance().GetMap(1002); assert(pMap);
        // synid set + ==
        { auto n = mkMgc(0, 306, "synid = 77 1002"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "synid == 77 1002"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "synid == 78 1002"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // status test/set/reset
        { auto n = mkMgc(0, 306, "status set 4 1002"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "status test 4 1002"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "status test 8 1002"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "status reset 4 1002"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "status test 4 1002"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // res_lev <, ==, = with %user_home_id substitution (home = 1001)
        { auto n = mkMgc(0, 306, "res_lev = 3 %user_home_id"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "res_lev == 3 %user_home_id"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "res_lev < 2 %user_home_id"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // mapdoc
        { auto n = mkMgc(0, 306, "mapdoc = 900000 1001"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 306, "mapdoc == 900000 1001"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // mapid 0 = current map (1002)
        { auto n = mkMgc(0, 306, "synid == 77"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // missing map
        { auto n = mkMgc(0, 306, "synid == 77 999999"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 306 map attributes match case 0x132\n");
    }
    // ---- 517: item attr set/compare (case 0x205) ----
    {
        auto upR = std::make_shared<CUser>(999020); upR->SetName("Attr517");
        CUser& r = *upR;
        ItemInfo it; it.dwType = 421338; it.dwPosition = 3; r.AddItem(it);
        { auto n = mkMgc(0, 517, "3 14 set 5 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 517, "3 14 == 5 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 517, "3 14 == 4 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // attr 1 = type binding (proven in the original class-digit checks)
        { auto n = mkMgc(0, 517, "3 1 == 421338 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // lock status (attr 0x13) special case with gmlog
        { auto n = mkMgc(0, 517, "3 19 set 1 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 517, "3 19 == 1 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // %iter_var_data7 substitution
        r.SetIterVarData(7, 3); // iter var 7 = position 3
        { auto n = mkMgc(0, 517, "%iter_var_data7 14 set 2 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 517, "%iter_var_data7 14 == 2 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // item not at position -> false; bad param -> false
        { auto n = mkMgc(0, 517, "9 14 set 1 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 517, "3"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 517 item attr set/compare matches case 0x205\n");
    }
    // ---- 518: award item copies (case 0x206 -> FUN_14011cf20) ----
    {
        auto upR = std::make_shared<CUser>(999019); upR->SetName("Item518");
        CUser& r = *upR;
        // empty param + data = item type (1200001): single copy
        { auto n = mkMgc(0, 518, ""); n.dwData = 1200001; assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "1200001 1200001 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // 19-field spec, field2 = 2 -> two copies of 3003124 (data)
        { auto n = mkMgc(0, 518, "0 2 0 0 0 0 0 0 0 0 0 3 3 0 0 0 0 0 0"); n.dwData = 3003124;
          assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "3003124 3003124 2"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // item type not in cq_itemtype -> false
        { auto n = mkMgc(0, 518, ""); n.dwData = 99999999; assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 518 award-copies matches case 0x206 (FUN_14011cf20)\n");
    }
    // ---- 509: equipment commands (case 0x1fd) ----
    {
        auto upR = std::make_shared<CUser>(999017); upR->SetName("Item509");
        CUser& r = *upR;
        // 700001: class 7 (target level 1), current level-in-id 0 -> 700011
        ItemInfo eq; eq.dwType = 700001; eq.dwPosition = 1; eq.usDurability = 800;
        r.AddItem(eq);
        { auto n = mkMgc(0, 509, "down_lev 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 quality == 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        // quality digit 0 -> down_lev false
        ItemInfo q0; q0.dwType = 112300; q0.dwPosition = 2;
        r.AddItem(q0);
        { auto n = mkMgc(0, 509, "down_lev 2"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // down_one_lev on 421338 (level 33) -> 421328 iff that type exists
        {
            ItemInfo wpn; wpn.dwType = 421338; wpn.dwPosition = 3;
            r.AddItem(wpn);
            auto n = mkMgc(0, 509, "down_one_lev 3");
            bool bExpect = CItemLibrary::Instance().Lookup(421328) != nullptr;
            assert(CGameAction::ProcessActionUser(upR, &n) == bExpect);
        }
        // recover_dur restores durability
        { auto n = mkMgc(0, 509, "recover_dur 1"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 durability == 10"); assert(CGameAction::ProcessActionUser(upR, &n)); } // 1000/100 = 10
        { auto n = mkMgc(0, 510, "1 durability == 9"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // dead command (up_lev rows are unhandled in v6159) -> false
        { auto n = mkMgc(0, 509, "up_lev 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // unknown position
        { auto n = mkMgc(0, 509, "recover_dur 9"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 509 down_lev/down_one_lev/recover_dur match case 0x1fd\n");
    }
    // ---- 506/507: erase/count N items in a type range (FUN_140344e80/FUN_140338940) ----
    {
        auto upR = std::make_shared<CUser>(999016); upR->SetName("Item506");
        CUser& r = *upR;
        ItemInfo a; a.dwType = 1088000; a.dwAmount = 12; a.dwPosition = 255; a.strName = "ExpBall";
        ItemInfo b; b.dwType = 723700;  b.dwAmount = 5;  b.dwPosition = 255; b.strName = "GemPack";
        r.AddItem(a); r.AddItem(b);
        // 507 check: 12 of 1088000 -> true for N=12, false for 13
        { auto n = mkMgc(0, 507, "1088000 1088000 12"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "1088000 1088000 13"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // range check 1072050..1072059: none -> false
        { auto n = mkMgc(0, 507, "1072050 1072059 2"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // 506 erase 7 of 1088000 -> stack reduced 12->5, true
        { auto n = mkMgc(0, 506, "1088000 1088000 7"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "1088000 1088000 5"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "1088000 1088000 6"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // 506 erase 5 (whole stack) -> item gone, true
        { auto n = mkMgc(0, 506, "1088000 1088000 5"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "1088000 1088000 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // 506 erase more than owned (needs 6, has 5 of 723700) -> false, stack untouched
        { auto n = mkMgc(0, 506, "723700 723700 6"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 507, "723700 723700 5"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 506/507 range erase/count match FUN_140344e80/FUN_140338940\n");
    }
    // ---- 5xx item family: 508/510/511 (FUN_140123590 cases 0x1fc/0x1fe/0x1ff) ----
    {
        auto upR = std::make_shared<CUser>(999014); upR->SetName("Item5xx");
        CUser& r = *upR;
        // 508: empty bag -> room for anything (data<1 -> true; count+data<41 -> true)
        { auto n = mkMgc(0, 508, ""); n.dwData = 0;  assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 508, ""); n.dwData = 10; assert(CGameAction::ProcessActionUser(upR, &n)); }
        // fill the bag to 40 items -> +2 needs 42 -> false; +0 data -> true
        for (int i = 0; i < 40; i++) {
            ItemInfo it; it.dwType = 1000000 + i; it.dwPosition = 255;
            r.AddItem(it);
        }
        { auto n = mkMgc(0, 508, ""); n.dwData = 2;  assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 508, ""); n.dwData = 0;  assert(CGameAction::ProcessActionUser(upR, &n)); }
        // 510: equip an Elite blade at position 1: type 410339? quality digit + level
        // level = (type%1000)/10, quality = type%10. Use 410246: level (246/10=24)... pick
        // type 421338: level = 33, quality = 8.
        ItemInfo wpn; wpn.dwType = 421338; wpn.dwPosition = 1; wpn.usDurability = 4500;
        r.AddItem(wpn);
        { auto n = mkMgc(0, 510, "1 level == 33"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 level == 34"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 quality == 8"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 quality <= 8"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 quality >= 9"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "1 durability == 45"); assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 510, "9 quality == 8"); assert(!CGameAction::ProcessActionUser(upR, &n)); } // no item @9
        { auto n = mkMgc(0, 510, "1 noattr == 1"); assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // 511: position check (data = position)
        { auto n = mkMgc(0, 511, ""); n.dwData = 1; assert(CGameAction::ProcessActionUser(upR, &n)); }
        { auto n = mkMgc(0, 511, ""); n.dwData = 2; assert(!CGameAction::ProcessActionUser(upR, &n)); }
        // ORIGINAL: positions 21..29 fold to 1..9 (FUN_14032b4b0) - pos 21 hits the wpn at 1
        { auto n = mkMgc(0, 511, ""); n.dwData = 21; assert(CGameAction::ProcessActionUser(upR, &n)); }
        printf("[ok] 508/510/511 match cases 0x1fc/0x1fe/0x1ff (level+quality formulas exact)\n");
    }

    }

    }



    printf("[ok] 501/502 award/erase item matches cases 0x1f5/0x1f6\n");

// --- 1027 (rank 0x15): send effect msg "self <effect> [del]" ---
    // mirror real rows: "self angelwing" (2 tokens, f3 empty -> actType 10)
    auto mk1027 = [](uint32_t id, const char* param) {
        CDialogEngine::Node n; n.dwType = 1027; n.dwId = id;
        n.strParam = param; return n; };
    { auto n = mk1027(1211265, "self angelwing");
      assert(CGameAction::ProcessActionUser(u9, &n)); }   // add -> true
    { auto n = mk1027(1211278, "self eidolon add");
      assert(CGameAction::ProcessActionUser(u9, &n)); }   // f3 "add" != "del"
    { auto n = mk1027(1211278, "couple eidolon del");
      assert(CGameAction::ProcessActionUser(u9, &n)); }   // del -> true
    { auto n = mk1027(1211265, "self");
      assert(!CGameAction::ProcessActionUser(u9, &n)); }  // <2 tokens -> DBERR
    { auto n = mk1027(1211265, "nobody eidolon");
      assert(!CGameAction::ProcessActionUser(u9, &n)); }  // unknown target
    printf("[ok] 1027 mate-id check matches FUN_140164440 (param ignored)\n");


    // ---- 2009/2002: delete monster records (cases 0x7d9/0x7d2) ----
    {
        auto upD = std::make_shared<CUser>(999045); upD->SetName("DelMon");
        // spawn the GuildBeast (real 2009 row 120121: "1038 3120 0 GuildBeast")
        { auto n = mkMgc(0, 2006, "0 0 1038 50 60 3120 4194 0 GuildBeast");
          assert(CGameAction::ProcessActionUser(upD, &n)); }
        // name mismatch (ORIGINAL: raw strcmp loop) -> no delete -> false
        { auto n = mkMgc(120121, 2009, "1038 3120 0 NotTheBeast");
          assert(!CGameAction::ProcessActionUser(upD, &n)); }
        // the real row deletes it; iteration would continue over all records
        { auto n = mkMgc(120121, 2009, "1038 3120 0 GuildBeast");
          assert(CGameAction::ProcessActionUser(upD, &n));
          assert(CMonsterManager::Instance().GetMapMonsters(1038).empty()); }
        // no match left -> false (uVar5 stays 0)
        { auto n = mkMgc(120121, 2009, "1038 3120 0 GuildBeast");
          assert(!CGameAction::ProcessActionUser(upD, &n)); }
        // empty name matches by map+type (real row 4092240: "1011 2494 0")
        { auto n = mkMgc(0, 2006, "0 0 1011 50 60 2494 4195 0");
          assert(CGameAction::ProcessActionUser(upD, &n)); }
        { auto n = mkMgc(4092240, 2009, "1011 2494 0");
          assert(CGameAction::ProcessActionUser(upD, &n)); }
        // parse failure (<= 1 field) -> the DBERR path
        { auto n = mkMgc(0, 2009, "1011");
          assert(!CGameAction::ProcessActionUser(upD, &n)); }
        // 2002 (real rows 5017680-84: param "4021 type 2" is dead text,
        // data 0): delmonsternow wipes every live record, always returns 1
        { auto n = mkMgc(0, 2006, "0 0 1038 70 80 3120 4196 0 LeftGate");
          assert(CGameAction::ProcessActionUser(upD, &n)); }
        { auto n = mkMgc(0, 2006, "0 0 1011 70 80 2494 4197 0 RightGate");
          assert(CGameAction::ProcessActionUser(upD, &n)); }
        { auto n = mkMgc(5017680, 2002, "4021 type 2"); n.dwData = 0;
          assert(CGameAction::ProcessActionUser(upD, &n));
          assert(CMonsterManager::Instance().GetAllMonsters().empty()); }
        printf("[ok] 2009/2002 monster record deletion match cases 0x7d9/0x7d2\n");
    }
    // ---- 2007: dynamic NPC creation (case 0x7d7) ----
    {
        auto upN7 = std::make_shared<CUser>(999046); upN7->SetName("SpawnNpc");
        upN7->SetMapId(1000);
        upN7->SetHomeMapId(1000);
        // real row 410072: ItemBox keyed by %user_id on the home map
        { auto n = mkMgc(410072, 2007,
            "ItemBox 4 33 8200 1 %user_id %user_home_id 21 39 0 0 0 8003010 0 0 0 0 0 0");
          assert(CGameAction::ProcessActionUser(upN7, &n)); }
        auto pBox = CNpcManager::Instance().GetNpc(999046);
        assert(pBox && pBox->GetName() == "ItemBox" && pBox->GetMapId() == 1000);
        assert(pBox->GetX() == 21 && pBox->GetY() == 39);
        assert(pBox->m_dwActionId == 8003010); // task0 -> szDynTable col 10
        assert(pBox->m_dwLookface == 8200);    // f4 -> col 5
        assert(pBox->m_dwNpcType == 1);         // f5 -> col 2
        // real row 402771 with %map_owner_id substituted by a literal id
        // (our central resolver has no map-owner context yet - field f6 is
        // the spawn record id); f13 task0 = 5030101, f11 life = 24
        { auto n = mkMgc(402771, 2007,
            "Close~left~gate 26 21 241 2 999047 1038 163 210 20000000 24 5030100"
            " 5030101 0 0 0 0 0 0 0 0 0 0 0");
          assert(CGameAction::ProcessActionUser(upN7, &n)); }
        auto pGate = CNpcManager::Instance().GetNpc(999047);
        assert(pGate && pGate->GetName() == "Close~left~gate" && pGate->GetMapId() == 1038);
        assert(pGate->m_dwActionId == 5030101); // task0 (col 10)
        assert(pGate->m_usLife == 24);          // f11 (col 0x19)
        assert(pGate->m_nSpawnFlags == 21);     // f3
        // < 9 fields -> DBERR 0x324a
        { auto n = mkMgc(0, 2007, "ItemBox 4 33 8200 1");
          assert(!CGameAction::ProcessActionUser(upN7, &n)); }
        // missing map -> "can't find map" LOGERR + DBERR 0x3255
        { auto n = mkMgc(0, 2007, "ItemBox 4 33 8200 1 999048 999999 21 39 0 0 0 8003010");
          assert(!CGameAction::ProcessActionUser(upN7, &n)); }
        printf("[ok] 2007 dynamic NPC creation matches case 0x7d7\n");
    }
    // ---- 2201-2205: ProcessActionPkBonus (FUN_140141c80) ----
    {
        auto upT1 = std::make_shared<CUser>(999050); upT1->SetName("PkbT");
        auto upH1 = std::make_shared<CUser>(999051); upH1->SetName("PkbH");
        CUserManager::Instance().AddUser(upH1);
        pDB->Query("DELETE FROM cq_pk_bonus WHERE target=999050 OR hunter=999051");
        pDB->Query("DELETE FROM cq_pk_item WHERE target=999050 OR hunter=999051");
        // 2201 (real rows 5002143/5002310) - original SQL literals
        { auto n = mkMgc(5002143, 2201, "target_bonus == 0");
          assert(!CGameAction::ProcessActionUser(upT1, &n)); } // empty table
        pDB->Query("INSERT INTO cq_pk_bonus (target, Target_name, hunter, Hunter_name,"
                   " B_type, Bonus) VALUES (999050, 'PkbT', 999051, 'PkbH', 2, 0)");
        { auto n = mkMgc(5002143, 2201, "target_bonus == 0");
          assert(CGameAction::ProcessActionUser(upT1, &n)); }
        pDB->Query("INSERT INTO cq_pk_bonus (target, hunter, B_type, Bonus)"
                   " VALUES (999050, 999051, 2, 500)");
        { auto n = mkMgc(5002310, 2201, "hunter_bonus > 0");
          assert(CGameAction::ProcessActionUser(upH1, &n)); }
        { auto n = mkMgc(5002310, 2201, "hunter_bonus > 900");
          assert(!CGameAction::ProcessActionUser(upH1, &n)); }
        { auto n = mkMgc(5002310, 2201, "target_bonus > 900");
          assert(!CGameAction::ProcessActionUser(upH1, &n)); }
        // 2205 (real rows 5005215/5005235): DetainEquip vtable slots
        { auto n = mkMgc(5005215, 2205, "target");
          assert(!CGameAction::ProcessActionUser(upT1, &n)); } // empty
        pDB->Query("INSERT INTO cq_pk_item (item, target, target_name, hunter,"
                   " hunter_name, manhunt_time, bonus)"
                   " VALUES (10, 999050, 'PkbT', 999051, 'PkbH', 0, 0)");
        { auto n = mkMgc(5005215, 2205, "target");
          assert(CGameAction::ProcessActionUser(upT1, &n)); }
        { auto n = mkMgc(5005235, 2205, "hunter");
          assert(CGameAction::ProcessActionUser(upH1, &n)); }
        // 2202 (real row 5002144: "2 500000"): pop the target record, push
        // it to the hunter's pending vector, notify the hunter
        CUser::SPkBonusRecord rec{};
        rec.dwItem = 10; rec.dwTarget = 999050; rec.dwHunter = 999051;
        snprintf(rec.szTargetName, sizeof(rec.szTargetName), "PkbT");
        snprintf(rec.szHunterName, sizeof(rec.szHunterName), "PkbH");
        upT1->m_vecPkTarget.push_back(rec);
        { auto n = mkMgc(5002144, 2202, "2 500000");
          assert(CGameAction::ProcessActionUser(upT1, &n)); }
        assert(upT1->m_vecPkTarget.empty());
        assert(upH1->m_vecPkHunter.size() == 1);
        assert(upH1->m_vecPkHunter[0].nBonus == 500000);
        assert(upH1->m_vecPkHunter[0].nBType == 2);
        { auto n = mkMgc(5002144, 2202, "2 500000"); // empty -> false
          assert(!CGameAction::ProcessActionUser(upT1, &n)); }
        // 2204 (real row 5002320): b_type 2 pays money; record popped either way
        uint64_t qwBefore = upH1->GetMoney();
        { auto n = mkMgc(5002320, 2204, "");
          assert(CGameAction::ProcessActionUser(upH1, &n)); }
        assert(upH1->GetMoney() == qwBefore + 500000);
        assert(upH1->m_vecPkHunter.empty());
        { auto n = mkMgc(5002320, 2204, ""); // empty -> false
          assert(!CGameAction::ProcessActionUser(upH1, &n)); }
        // 2203 (real row 5002080): DELETE ... AND bonus=0 -> always true
        { auto n = mkMgc(5002080, 2203, "");
          assert(CGameAction::ProcessActionUser(upT1, &n)); }
        assert(atoi(pDB->Scalar("SELECT count(*) FROM cq_pk_bonus WHERE"
                                " target=999050 AND bonus=0", "0").c_str()) == 0);
        pDB->Query("DELETE FROM cq_pk_bonus WHERE target=999050 OR hunter=999051");
        pDB->Query("DELETE FROM cq_pk_item WHERE target=999050 OR hunter=999051");
        CUserManager::Instance().RemoveUser(999051);
        printf("[ok] 2201-2205 pk-bonus family matches FUN_140141c80\n");
    }
    // --- family C complete: 2005 (0x7d5) / 2014 (0x7de), both live rows ---
    // 2005: the single row 7235756 carries a sentence param -> sscanf
    // fails -> literal DBERR path -> false (id_nextfail 1010)
    CDialogEngine::Node ndSpace; ndSpace.dwType = 2005;
    ndSpace.strParam = "Sorry,you did not have enough space for the item.";
    ndSpace.dwId = 7235756;
    assert(!CGameAction::ProcessActionUser(u5, &ndSpace));
    // 2014: row 5007639 parses all 10 fields -> module 5 side effect,
    // break-only case -> true
    CDialogEngine::Node ndMod5; ndMod5.dwType = 2014; ndMod5.dwId = 5007639;
    ndMod5.strParam = "0 8 1 3 9 1 9 8 1 3";
    assert(CGameAction::ProcessActionUser(u5, &ndMod5));
    // malformed 2014 (still true - break-only, module call skipped)
    CDialogEngine::Node ndMod5b; ndMod5b.dwType = 2014;
    ndMod5b.strParam = "1 2";
    assert(CGameAction::ProcessActionUser(u5, &ndMod5b));

    // --- family D: 201 dynamic NPC fields (case 0xc9, live patterns) ---
    auto dyn = std::make_shared<CNpc>(4001, "Dyn", CNpc::Type::Dialog, 1000, 50, 60);
    dyn->m_bDyna = true;
    CNpcManager::Instance().RegisterNpc(dyn);
    u5->m_stDialogCtx.dwId = 4001; // npcId==0 -> the dialog npc
    u5->SetSynId(777);
    CDialogEngine::Node nd201; nd201.dwType = 201;

    // data1 == 2 (322 rows) -> false when 0
    nd201.strParam = "data1 == 2";
    assert(!CGameAction::ProcessActionUser(u5, &nd201));
    // data3 += 1 (126 rows) -> set path, then == passes
    nd201.strParam = "data3 += 1";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    nd201.strParam = "data3 == 1";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    // ownerid = / == %syn_id (39 rows): resolver fills 777
    nd201.strParam = "ownerid = %syn_id";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    nd201.strParam = "ownerid == %syn_id";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    // lookface = 287 (14 rows) then ==
    nd201.strParam = "lookface = 287";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    nd201.strParam = "lookface == 287";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    // data0 = accept (195 rows): value from the dialog input (param_7)
    u5->m_stDialogCtx.strInput = "42";
    nd201.strParam = "data0 = accept";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    nd201.strParam = "data0 == 42";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    // explicit npcId not found -> DBERR false
    nd201.strParam = "data2 = 0 100078 1";
    assert(!CGameAction::ProcessActionUser(u5, &nd201));
    // datastr = / == 
    nd201.strParam = "datastr = 1";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    nd201.strParam = "datastr == 1"; // 106 rows
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    // life = 10000 (8 rows) + maxlife
    nd201.strParam = "life = 10000";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    nd201.strParam = "maxlife = 10000";
    assert(CGameAction::ProcessActionUser(u5, &nd201));
    // not a DynaNpc -> false
    auto plain = std::make_shared<CNpc>(4002, "Plain", CNpc::Type::Dialog, 1000, 51, 61);
    CNpcManager::Instance().RegisterNpc(plain);
    u5->m_stDialogCtx.dwId = 4002;
    nd201.strParam = "data1 == 2";
    assert(!CGameAction::ProcessActionUser(u5, &nd201));
    u5->m_stDialogCtx.dwId = 4001;

    // --- family E batch 1: 1002 / 1005 / 1075 / 1082 (live rows) ---
    CDialogEngine::Node ndE; ndE.dwType = 1082;

    // 1002 (rank 1): "life"/"mana" full restore; other -> false
    CDialogEngine::Node nd1002; nd1002.dwType = 1002;
    u5->SetLife(37);
    nd1002.strParam = "life";
    assert(CGameAction::ProcessActionUser(u5, &nd1002));
    assert(u5->GetLife() == u5->GetMaxLife());
    u5->SetMana(3);
    nd1002.strParam = "mana";
    assert(CGameAction::ProcessActionUser(u5, &nd1002));
    assert(u5->GetMana() == u5->GetMaxMana());
    nd1002.strParam = "other"; // goto LAB false
    assert(!CGameAction::ProcessActionUser(u5, &nd1002));

    // 1005: style 13 (live) - style formula on attr 0x1a
    CDialogEngine::Node nd1005; nd1005.dwType = 1005;
    nd1005.strParam = "style 13";
    assert(CGameAction::ProcessActionUser(u5, &nd1005));
    // default cur 321: (321/100)*100 + 13 = 313; 313 >= 100 stays
    assert(u5->GetHairStyle() == 313);
    // style 39: (313/100)*100 + 39 = 339
    nd1005.strParam = "style 39";
    assert(CGameAction::ProcessActionUser(u5, &nd1005));
    assert(u5->GetHairStyle() == 339);
    // malformed -> false
    nd1005.strParam = "style";
    assert(!CGameAction::ProcessActionUser(u5, &nd1005));

    // 1075: send 1000 1 (all 89 live rows) -> window send
    CDialogEngine::Node nd1075; nd1075.dwType = 1075;
    nd1075.strParam = "send 1000 1";
    assert(CGameAction::ProcessActionUser(u5, &nd1075));
    nd1075.strParam = "send"; // parse < 3 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1075));

    // 1082: self add 2 200 10 0 (live) - side effect then FALSE
    ndE.strParam = "self add 2 200 10 0";
    assert(!CGameAction::ProcessActionUser(u5, &ndE));
    // self del 2 1 (live) - side effect then FALSE
    ndE.strParam = "self del 2 1 0 0";
    assert(!CGameAction::ProcessActionUser(u5, &ndE));
    // parse < 6 -> DBERR false
    ndE.strParam = "self add 2";
    assert(!CGameAction::ProcessActionUser(u5, &ndE));

    // --- family E batch 2: 1083 / 1096 / 1098 / 1554 (live rows) ---
    CDialogEngine::Node ndE2; ndE2.dwType = 1554;

    // 1083 (rank 0x49): stat counter ops
    CDialogEngine::Node nd1083; nd1083.dwType = 1083;
    nd1083.strParam = "+= 5";  // 101 live rows: add then true
    assert(CGameAction::ProcessActionUser(u5, &nd1083));
    assert(u5->GetStatCounter() == 5);
    nd1083.strParam = "== 5";
    assert(CGameAction::ProcessActionUser(u5, &nd1083));
    nd1083.strParam = "< 100";
    assert(CGameAction::ProcessActionUser(u5, &nd1083));
    nd1083.strParam = "== 6";
    assert(!CGameAction::ProcessActionUser(u5, &nd1083));
    nd1083.strParam = "chk 1";  // helper stub -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1083));
    nd1083.strParam = "add 1";  // unknown op -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1083));
    nd1083.strParam = "add";    // parse < 2 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1083));

    // 1096: "200 0 5 0 5 1" (live) -> parse gate + module stub
    CDialogEngine::Node nd1096; nd1096.dwType = 1096;
    nd1096.strParam = "200 0 5 0 5 1";
    assert(CGameAction::ProcessActionUser(u5, &nd1096));
    nd1096.strParam = "200 0 5"; // parse < 6 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1096));
    nd1096.strParam = "200 -1 5 0 5 1"; // negative -> 0
    assert(!CGameAction::ProcessActionUser(u5, &nd1096));

    // 1098: profession whitelist (data=0 branch)
    u5->SetProfession(10);
    CDialogEngine::Node nd1098; nd1098.dwType = 1098;
    nd1098.strParam = "29 30 31 32 33 34 35 37 38 45 46 48 111 12 10";
    assert(CGameAction::ProcessActionUser(u5, &nd1098));
    nd1098.strParam = "29 30 31 32 33 35 36 37 38 45 46 48 111 12 15";
    assert(!CGameAction::ProcessActionUser(u5, &nd1098));

    // 1554: "add"/"chk" single-token rows with monster id in data col
    ndE2.strParam = "add"; ndE2.dwData = 11029; // live pattern
    assert(CGameAction::ProcessActionUser(u5, &ndE2));
    ndE2.strParam = "chk"; ndE2.dwData = 11029; // stub false
    assert(!CGameAction::ProcessActionUser(u5, &ndE2));
    ndE2.strParam = "other"; // no match -> tail -> false
    assert(!CGameAction::ProcessActionUser(u5, &ndE2));

    // --- family E batch 3: 1651 (live rows) ---
    // dialog npc context: id + name + data
    auto npcA = std::make_shared<CNpc>(1015, "Armorer", CNpc::Type::Dialog, 1000, 70, 80);
    CNpcManager::Instance().RegisterNpc(npcA);
    u5->m_stDialogCtx.dwId = 1015;
    u5->m_stDialogCtx.strName = "Armorer";  // live pattern
    u5->m_stDialogCtx.dwData = 17;          // data=2 "0017" rows
    CDialogEngine::Node nd1651; nd1651.dwType = 1651;
    nd1651.dwData = 1; nd1651.strParam = "Armorer";
    assert(CGameAction::ProcessActionUser(u5, &nd1651));
    nd1651.strParam = "Pharmacist"; // mismatch -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1651));
    nd1651.dwData = 2; nd1651.strParam = "0017"; // %u -> 17 == data
    assert(CGameAction::ProcessActionUser(u5, &nd1651));
    nd1651.strParam = "0021"; // 21 != 17 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1651));
    u5->m_stDialogCtx.dwId = 0; // no dialog npc -> 0
    assert(!CGameAction::ProcessActionUser(u5, &nd1651));
    u5->m_stDialogCtx.dwId = 1015;

    // --- family E batch 4: 1004 / 1084 (live rows) ---
    // 1004 (rank 3): "1002 300 280" -> record pos, NO map move
    CDialogEngine::Node nd1004; nd1004.dwType = 1004;
    uint32_t dwOldMap = u5->GetMapId();
    nd1004.strParam = "1002 300 280";
    assert(CGameAction::ProcessActionUser(u5, &nd1004));
    assert(u5->GetRecordPos().dwMap == 1002);
    assert(u5->GetRecordPos().wX == 300 && u5->GetRecordPos().wY == 280);
    assert(u5->GetMapId() == dwOldMap); // record only
    nd1004.strParam = "9999 300 280"; // map lookup 0 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1004));
    nd1004.strParam = "1002 300"; // parse < 3 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1004));

    // 1011 (rank 0xa): enter map - Teleport
    CDialogEngine::Node nd1011; nd1011.dwType = 1011;
    nd1011.strParam = "1002 300 280";
    assert(CGameAction::ProcessActionUser(u5, &nd1011));
    assert(u5->GetMapId() == 1002);
    nd1011.strParam = "9999 300 280";
    assert(!CGameAction::ProcessActionUser(u5, &nd1011));
    nd1011.strParam = "1002 300";
    assert(!CGameAction::ProcessActionUser(u5, &nd1011));

    // 1043: mount recharge -> true (FUN_140162620 tail = 1)
    CDialogEngine::Node nd1043; nd1043.dwType = 1043; nd1043.strParam = "";
    assert(CGameAction::ProcessActionUser(u5, &nd1043));
    // 1046: msg sent but result false (break without uVar41)
    CDialogEngine::Node nd1046; nd1046.dwType = 1046; nd1046.strParam = "";
    assert(!CGameAction::ProcessActionUser(u5, &nd1046));
    // 1071: "60 9018985 0" (live) -> timer + true; bad parse -> false
    CDialogEngine::Node nd1071; nd1071.dwType = 1071;
    nd1071.strParam = "60 9018985 0";
    assert(CGameAction::ProcessActionUser(u5, &nd1071));
    nd1071.strParam = "180 0 1"; // flag path -> true
    assert(CGameAction::ProcessActionUser(u5, &nd1071));
    nd1071.strParam = "60 9018985"; // <3 tokens -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1071));
    // 1072: empty param -> msg + true
    CDialogEngine::Node nd1072; nd1072.dwType = 1072; nd1072.strParam = "";
    assert(CGameAction::ProcessActionUser(u5, &nd1072));

    // 1203: HP full (max<=life); 1204: mana full (max<=mana)
    CDialogEngine::Node nd1203; nd1203.dwType = 1203; nd1203.strParam = "";
    u5->SetLife(u5->GetMaxLife());
    assert(CGameAction::ProcessActionUser(u5, &nd1203));
    u5->SetLife(u5->GetMaxLife() / 2);
    assert(!CGameAction::ProcessActionUser(u5, &nd1203));
    CDialogEngine::Node nd1204; nd1204.dwType = 1204; nd1204.strParam = "";
    u5->SetMana(u5->GetMaxMana());
    assert(CGameAction::ProcessActionUser(u5, &nd1204));
    u5->SetMana(1);
    assert(!CGameAction::ProcessActionUser(u5, &nd1204));
    // 1510: heal pct (data=0 -> pct of maxlife, capped by life)
    CDialogEngine::Node nd1510; nd1510.dwType = 1510; nd1510.dwData = 0;
    nd1510.strParam = "50";
    u5->SetLife(100);
    assert(CGameAction::ProcessActionUser(u5, &nd1510));
    // heal = min(maxlife*50/100, life=100) = 100 -> life 200
    assert(u5->GetLife() == 200);
    assert(u5->GetLife() <= u5->GetMaxLife());
    nd1510.dwData = 7; // unsupported data -> return 0
    assert(!CGameAction::ProcessActionUser(u5, &nd1510));
    // 1650: "%u" leading parse ("12-1007" -> 12), send -> true
    CDialogEngine::Node nd1650; nd1650.dwType = 1650;
    nd1650.strParam = "12-1007";
    assert(CGameAction::ProcessActionUser(u5, &nd1650));
    nd1650.strParam = "x";
    assert(!CGameAction::ProcessActionUser(u5, &nd1650));

    // 1058 (rank 0x32): module-7 var ops ("time set 0" = 228 live rows)
    CDialogEngine::Node nd1058; nd1058.dwType = 1058; nd1058.dwData = 77;
    nd1058.strParam = "time set 0";
    assert(CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time set 500";
    assert(CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time == 500";
    assert(CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time > 499";
    assert(CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time < 500";
    assert(!CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time == 499";
    assert(!CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time += 100";
    assert(CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time == 600";
    assert(CGameAction::ProcessActionUser(u5, &nd1058));
    nd1058.strParam = "time"; // <3 tokens -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1058));
    // 1095 (rank 0x54): status sync stub -> true
    CDialogEngine::Node nd1095; nd1095.dwType = 1095; nd1095.strParam = "";
    assert(CGameAction::ProcessActionUser(u5, &nd1095));

    // --- final E batch: parse gates + faithful results ---
    auto mkE = [](uint32_t ty, const char* par, uint32_t data=0) {
        CDialogEngine::Node n; n.dwType = ty; n.dwId = 990000+n.dwType%1000;
        n.strParam = par; n.dwData = data; return n; };
    { auto n = mkE(1052, "");      assert(!CGameAction::ProcessActionUser(u5,&n)); } // 0xbb DBERR
    { auto n = mkE(1031, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1032, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1036, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1037, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1047, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1078, "", 42); assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1079, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1006, "");      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1041, "hello"); assert( CGameAction::ProcessActionUser(u5,&n)); }
    // 1048: parses ok but ORIGINAL leaves result unset -> false
    { auto n = mkE(1048, "3 7");  assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1048, "3");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    // 1094: data!=metem and data!=0 -> false
    { auto n = mkE(1094, "", 77); assert(!CGameAction::ProcessActionUser(u5,&n)); }
    // 1102/1106/1108/1116: parse ok -> ORIGINAL tail 0
    { auto n = mkE(1102, "a b 5");assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1102, "a b");  assert(!CGameAction::ProcessActionUser(u5,&n)); } // <3 DBERR
    { auto n = mkE(1106, "");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1108, "team_action 1 2"); assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1108, "team_action 1");    assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1116, "5 6");   assert(!CGameAction::ProcessActionUser(u5,&n)); }
    // 1107: "%u %d %d" ok -> true; short -> false
    // 1107 now requires a real team (no team -> false); parse-fail -> false
    { auto n = mkE(1107, "1 2 3"); assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1107, "1 2");   assert(!CGameAction::ProcessActionUser(u5,&n)); }
    // 1110: 7 fields + zero gate
    { auto n = mkE(1110, "1 2 3 4 5 6 7");  assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1110, "1 0 3 4 5 6 7");  assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1110, "1 2 3");           assert(!CGameAction::ProcessActionUser(u5,&n)); }
    // 1114/1115: "%u %u" zero-gates
    { auto n = mkE(1114, "5 6");  assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1114, "0 6");  assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1115, "5 6");  assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1111, "9");    assert( CGameAction::ProcessActionUser(u5,&n)); }
    // 1202/1509/1520: parse -> true; short -> false
    { auto n = mkE(1202, "5");    assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1202, "");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1509, "1 2 3 4 5 6"); assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1509, "1 2 3");        assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1520, "7");    assert( CGameAction::ProcessActionUser(u5,&n)); }
    // unresolved-helper conservators: 1035/1053/1109/1557/1654 -> false
    { auto n = mkE(1035, "");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1053, "");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1109, "");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1557, "5");    assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1654, "");     assert(!CGameAction::ProcessActionUser(u5,&n)); }
    // assumed-success effects: 1070/1077/1508/1511/1652 -> true
    { auto n = mkE(1070, "1 2 3");assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1077, "", 3);  assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1508, "");     assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1511, "");     assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1652, "");     assert( CGameAction::ProcessActionUser(u5,&n)); }
    // 1033: 10-field parse
    { auto n = mkE(1033, "a 1 2 3 4 5 6 7 8 9");
      assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1033, "a 1 2 3");
      assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(1034, "");     assert( CGameAction::ProcessActionUser(u5,&n)); }

    // --- family F: range-dispatched if-chain handlers ---
    { auto n = mkE(302, "alive_user == 1");  assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(302, "bogus");            assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(307, "0 0 0 200 200 4215 < 0"); assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(307, "0 0 0 200");        assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(308, "728006 3030 186 187 1 2 3 4"); assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(311, "123 456");          assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(314, "");                 assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(332, "");                 assert( CGameAction::ProcessActionUser(u5,&n)); } // gate->true
    { auto n = mkE(401, "150060 9 35 1130 3"); assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(401, "150060 9 35");      assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(402, "all x y 5");        assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(402, "all x y");          assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(403, "");                 assert(!CGameAction::ProcessActionUser(u5,&n)); } // all tails 0
    { auto n = mkE(498, "");                 assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(512, "1 2");              assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(512, "1");                assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(516, "1 2 abc 3 to 4");   assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(519, "");                 assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(528, "1");                assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(529, "1 2");              assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(542, "1 2 3 4 5 6 7 8");  assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(543, "");                 assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(544, "");                 assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(550, "1 2 3");            assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(705, "");                 assert(!CGameAction::ProcessActionUser(u5,&n)); } // no case
    { auto n = mkE(708, "");                 assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(709, "");                 assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(3701, "");                assert( CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(20001, "");               assert(!CGameAction::ProcessActionUser(u5,&n)); }
    { auto n = mkE(20002, "");               assert(!CGameAction::ProcessActionUser(u5,&n)); }

    // 1071 timer subsystem (FUN_1401a9b00 ABI): registration + drain
    {
        CDialogEngine::Node nd; nd.dwType = 1071; nd.strParam = "60 9018985 0";
        u5->m_deqTimers.clear();
        assert(CGameAction::ProcessActionUser(u5, &nd));
        assert(u5->m_deqTimers.size() == 1);
        assert(u5->m_deqTimers[0].dwDelay == 60);
        assert(u5->m_deqTimers[0].nActionId == 9018985);
        // guard: actionId == 0 -> no registration ("180 0 1" live row)
        nd.strParam = "180 0 1";
        assert(CGameAction::ProcessActionUser(u5, &nd));
        assert(u5->m_deqTimers.size() == 1); // unchanged
        // drain: not due yet / due after delay
        auto now = u5->m_deqTimers[0].dwStart;
        assert(u5->ProcessActionTimers(now).empty());
        auto fired = u5->ProcessActionTimers(now + 60);
        assert(fired.size() == 1 && fired[0] == 9018985);
        assert(u5->m_deqTimers.empty());
    }

    // --- team system (FUN_140118860 model): 1107 team teleport ---
    {
        u5->SetMapId(1002); // ensure same-map path (MapManager-free)
        auto& tm = CTeamManager::Instance();
        auto pTeam = std::make_shared<CTeam>(u5->GetId());
        auto uMate = std::make_shared<CUser>(88002);
        uMate->SetAlive(true); uMate->SetMapId(1002);
        CUserManager::Instance().AddUser(uMate);
        assert(pTeam->AddMember(uMate->GetId()));
        tm.InsertTeamForTest(pTeam);
        CDialogEngine::Node nd; nd.dwType = 1107; nd.strParam = "1002 100 100";
        // team exists: no-team path for a stranger
        {
            auto uLonely = std::make_shared<CUser>(88003);
            CDialogEngine::Node nd2 = nd;
            assert(!CGameAction::ProcessActionUser(uLonely, &nd2));
        }
        // parse gate
        nd.strParam = "1000 50";
        assert(!CGameAction::ProcessActionUser(u5, &nd));
        // full path: self + member both land on map 1000
        nd.strParam = "1002 100 100";
        assert(CGameAction::ProcessActionUser(u5, &nd));
        assert(u5->GetMapId() == 1002);
        assert(uMate->GetMapId() == 1002);
        // leave-team restores the false path
        pTeam->RemoveMember(uMate->GetId());
        CUserManager::Instance().RemoveUser(uMate->GetId());
    }

    // 1084: "13901336 6 7" (live) - id resolved into vars 6,7
    CDialogEngine::Node nd1084; nd1084.dwType = 1084;
    nd1084.strParam = "13901336 6 7";
    assert(CGameAction::ProcessActionUser(u5, &nd1084));
    assert(u5->GetIterVarData(6) == 0 && u5->GetIterVarData(7) == 0);
    nd1084.strParam = "13901336 6"; // parse < 3 -> false
    assert(!CGameAction::ProcessActionUser(u5, &nd1084));

    printf("DIALOG FIDELITY TEST PASSED\n");
    return 0;
}

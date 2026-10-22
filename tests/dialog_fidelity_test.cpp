// ORIGINAL dialog fidelity: CGameAction walks the real cq_action chain and
// emits the ORIGINAL CMsgDialog packets (id 2032) the 6159 client renders.
// Chain 1501 in the original dump (Taoist teacher):
//   1501(101 text) -> 1502(102 opt ->1510) -> 1503(102 opt ->3060)
//   -> 3050(102 opt "No~thanks." ->0) -> 10004(104 listbox) -> 10005(120)
#include "Account.h"
#include "Npc.h"
#include "Dialog.h"
#include "GameAction.h"
#include "MsgDialog.h"
#include "MsgTalk.h"
#include "User.h"
#include "PlayerMagic.h"
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

    printf("DIALOG FIDELITY TEST PASSED\n");
    return 0;
}

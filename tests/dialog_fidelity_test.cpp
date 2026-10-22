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

    auto up = std::make_shared<CUser>(1); up->SetName("Tester");
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
    // of check 1000 (3587220 -> 1516): the page offers only what remains
    u.LearnMagic(1000, 1);
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

    printf("DIALOG FIDELITY TEST PASSED\n");
    return 0;
}

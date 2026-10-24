// ============================================================================
// magic_effect_packets_test.cpp — byte-level checks of the ported
// CMsgMagicEffect (1105) / CMsgMagicInfo (1103) and the CUser effect-mask
// API (AllowLaunchEffect / AttachEffectType / DropMagicEffect).
//
// Packet layout expectations are the ORIGINAL decompile offsets:
//   1105 payload: attacker@0, target@4, type@8(u16), level@10(u16),
//                dir@14, count@15, flag@16, targets@0x14 stride 0x20,
//                base size 0x34, append cap size+0x20 < 0x400.
//   1103 payload: time@0(u32), magicType@8(u32), mode@14(u16), effect@16(u8),
//                data5@20(u32), data6@24(u32), size 0x1c.
// ============================================================================
#include "MsgMagicEffect.h"
#include "MsgMagicInfo.h"
#include "User.h"
#include "UserManager.h"
#include "Monster.h"
#include "MsgAction.h"
#include "MapManager.h"
#include "Account.h"
#include "Dialog.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

static uint32_t rd32(const char* b, uint32_t off) {
    uint32_t v; std::memcpy(&v, b + off, 4); return v;
}
static uint16_t rd16(const char* b, uint32_t off) {
    uint16_t v; std::memcpy(&v, b + off, 2); return v;
}
static uint8_t rd8(const char* b, uint32_t off) {
    return (uint8_t)b[off];
}

int main() {
    // ---------- 1105 base Create (FUN_140386800) ----------
    CMsgMagicEffect fx;
    assert(!fx.Create(0, 7, 1000, 4, 3, 0));          // attacker 0 -> refuse
    assert(fx.Create(0x1001, 0x2002, 1000, 4, 3, 0));
    assert(fx.GetTotalSize() == 0x34);                 // ORIGINAL base size
    const char* p = fx.GetBuf();
    assert(rd32(p, 0x00) == 0x1001);                   // attacker
    assert(rd32(p, 0x04) == 0x2002);                  // target
    assert(rd16(p, 0x08) == 1000);                    // magic type
    assert(rd16(p, 0x0a) == 4);                       // level
    assert(rd8(p, 0x0e) == 3);                        // dir
    assert(rd8(p, 0x0f) == 0);                        // count starts 0
    assert(rd8(p, 0x10) == 0);                        // flag

    // ---------- AppendTarget (FUN_140386d00) ----------
    assert(fx.AppendTarget(0x2002, 150, 8, 9));
    assert(fx.GetTotalSize() == 0x34 + 0x20);
    p = fx.GetBuf(); // resize may reallocate: re-fetch (test-side only)
    assert(rd8(p, 0x0f) == 1);
    assert(rd32(p, 0x14) == 0x2002);                   // entry id
    assert(rd32(p, 0x18) == 150);                      // damage
    assert(rd32(p, 0x1c) == 8);                        // data2
    assert(rd32(p, 0x30) == 9);                        // data6 at entry+0x1c
    assert(rd32(p, 0x34) == 0);                        // terminator
    for (int i = 0; i < 20; i++)                       // cap: < 0x400
        fx.AppendTarget(0x3000u + i, 10, 0, 0);
    assert(fx.GetTotalSize() < 0x400);
    bool bOverflowRefused = !fx.AppendTarget(1, 1, 1, 1); // depends on cap
    (void)bOverflowRefused;

    // ---------- CreateWithTarget (FUN_1403868f0) ----------
    CMsgMagicEffect fx2;
    assert(!fx2.CreateWithTarget(1, 0, 1000, 1, 0, 5, 6, 7, 0)); // target 0
    assert(fx2.CreateWithTarget(0x1111, 0x2222, 1002, 3, 5, 444, 555, 666, 2));
    assert(fx2.GetTotalSize() == 0x34 + 0x20);
    const char* q = fx2.GetBuf();
    assert(rd8(q, 0x0f) == 1);
    assert(rd32(q, 0x14) == 0x2222);
    assert(rd32(q, 0x18) == 444);
    assert(rd32(q, 0x1c) == 555);
    assert(rd32(q, 0x30) == 666);
    assert(rd32(q, 0x34) == 0);
    assert(rd8(q, 0x10) == 2);                         // flag

    // ---------- CreateFull (FUN_140386e00, literal quirk) ----------
    CMsgMagicEffect fx3;
    assert(fx3.CreateFull(0x1111, 0x2222, 1002, 3, 5, 444, 555, 777, 888, 999, 0xaaa, 1));
    const char* r = fx3.GetBuf();
    assert(rd32(r, 0x14 + 0x00) == 0x2222);
    assert(rd32(r, 0x14 + 0x04) == 444);
    assert(rd32(r, 0x14 + 0x08) == 555);
    assert(rd32(r, 0x14 + 0x20) == 777);   // param_9 at NEXT entry base (quirk)
    assert(rd32(r, 0x14 + 0x10) == 888);   // param_10 @+0x24
    assert(rd32(r, 0x14 + 0x1c) == 999);   // param_11 @+0x30
    assert(rd32(r, 0x14 + 0x18) == 0xaaa); // param_12 @+0x2c
    assert(rd8(r, 0x10) == 1);

    // ---------- 1103 CMsgMagicInfo (FUN_140457240) ----------
    CMsgMagicInfo info;
    assert(!info.Create(6, 0, 0, 0, 0));               // type 0 -> refuse
    assert(info.Create(6, 3000694, 0x0a, 0x12345678, 0x90abcdef));
    assert(info.GetSize() == 0x1c);
    const char* m = info.GetBuf();
    assert(rd32(m, 0x00) != 0);                        // TimeGet
    assert(rd32(m, 0x08) == 3000694);
    assert(rd16(m, 0x0e) == 6);                        // mode
    assert(rd8(m, 0x10) == 0x0a);                      // effect
    assert(rd32(m, 0x14) == 0x12345678);
    assert(rd32(m, 0x18) == 0x90abcdef);

    // ---------- effect-mask API on a user record ----------
    auto& acc = CAccountManager::Instance();
    acc.SetAutoCreate(false);
    assert(acc.TryMySQL("127.0.0.1", 3306, "root", "", "cq"));
    auto* pDB = acc.GetDB();
    assert(CMagicTypePool::Instance().LoadFromDB(pDB));
    assert(CItemLibrary::Instance().LoadFromDB(pDB) > 0);
    CUser u(1);
    u.SetName("Mage");
    // thunder 1000 (level 0 stage) so the record exists in cq_magictype
    assert(u.LearnMagic(1000, 0));
    // unknown magic -> all three refuse
    assert(!u.AllowLaunchEffect(987654, 1));
    assert(!u.AttachEffectType(987654, 1, false, false));
    assert(!u.DropMagicEffect(987654, 1));
    // attach effect 3 with monopoly+exorbitant
    assert(u.AttachEffectType(1000, 3, true, true));
    CPlayerMagic* pRec = u.FindMagic(1000);
    assert(pRec);
    // fresh record: available_effect_type column default = 1 (bit 0)
    assert((uint32_t)pRec->GetAttrib(8) == (1u | (1u << 3))); // available
    assert((uint32_t)pRec->GetAttrib(9) == (1u << 3)); // monopoly
    assert((uint32_t)pRec->GetAttrib(10) == (1u << 3)); // exorbitant
    assert((uint8_t)pRec->GetAttrib(7) == 3);          // current
    // attach again -> refused (already available)
    assert(!u.AttachEffectType(1000, 3, true, true));
    // allow launch flips current and keeps masks
    assert(u.AllowLaunchEffect(1000, 3));
    assert((uint8_t)pRec->GetAttrib(7) == 3);
    // effect not attached -> launch refused
    assert(!u.AllowLaunchEffect(1000, 5));
    // drop: bits cleared, item awarded, masks drained
    assert(u.DropMagicEffect(1000, 3));
    assert((uint32_t)pRec->GetAttrib(8) == 1); // bit 3 drained, column default bit stays
    assert((uint32_t)pRec->GetAttrib(9) == 0);
    assert((uint32_t)pRec->GetAttrib(10) == 0);
    // second drop refused (bit no longer available)
    assert(!u.DropMagicEffect(1000, 3));

    // ---------- SendMagicEffectAfterProcess (FUN_1404851b0 broadcast) ----
    auto upFx = std::make_shared<CUser>(777001); upFx->SetName("FxSender");
    auto upObs = std::make_shared<CUser>(777002); upObs->SetName("FxWatcher");
    upFx->SetMapId(777000); upObs->SetMapId(777000);
    assert(CUserManager::Instance().AddUser(upFx));
    assert(CUserManager::Instance().AddUser(upObs));
    auto pFxMap = CMapManager::Instance().GetOrCreate(777000, "FxMap");
    assert(pFxMap->AddUser(upFx) && pFxMap->AddUser(upObs));
    assert(upFx->LearnMagic(1000, 0));                 // thunder record
    assert(upFx->AttachEffectType(1000, 3, false, true)); // current effect = 3
    // failure paths: unknown magic, target 0 -> CreateFull refuses both
    assert(!upFx->SendMagicEffectAfterProcess(987654, 1, 2, 3, 4, 0x2002));
    assert(!upFx->SendMagicEffectAfterProcess(1000, 1, 2, 3, 4, 0));
    int nSeen = 0;
    upObs->SetPacketSink([&](const void* pv, uint16_t sz) {
        nSeen++;
        const char* b = (const char*)pv;
        assert(sz == 0x54);                            // 0x34 + 0x20 entry
        assert(rd32(b, 0x00) == 777001);               // attacker (proxy id)
        assert(rd32(b, 0x04) == 0x2002);               // target id
        assert(rd16(b, 0x08) == 1000);                 // magic type
        assert(rd16(b, 0x0a) == 0);                    // record level
        assert(rd8(b, 0x0e) == 0);                    // dir
        assert(rd8(b, 0x0f) == 1);                    // one target entry
        assert(rd8(b, 0x10) == 3);                    // flag = current effect
        assert(rd32(b, 0x14) == 0x2002);               // entry id
        assert(rd32(b, 0x18) == 150);                  // damage
        assert(rd32(b, 0x1c) == 0xDD);                 // d2
        assert(rd32(b, 0x24) == 0);                    // d4 (scene diff)
        assert(rd32(b, 0x30) == 0xAABB);               // d5
        assert(rd32(b, 0x2c) == 777001);               // d6 = kernel role id
        assert(rd32(b, 0x34) == 0xCC);                 // d3 NEXT-entry quirk
    });
    assert(upFx->SendMagicEffectAfterProcess(1000, 0xAABB, 0xCC, 0xDD, 150, 0x2002));
    assert(nSeen == 1);                                // observer got the 1105

    // ---------- CreateGroup (FUN_140386a50) / AppendGroup (FUN_140387150) ----
    CMsgMagicEffect grp;
    assert(!grp.CreateGroup(0, 1000, 3, 0, 0, 0, 0, 0, 0, 3));   // zero attacker
    assert(grp.CreateGroup(777001, 1000, 3, 2, 0, 0, 0, 0, 0, 3)); // header only
    {
        const char* b = (const char*)grp.GetBuf();
        assert(grp.GetSize() == 0x34);
        assert(rd32(b, 0x00) == 777001);   // attacker
        assert(rd32(b, 0x04) == 0);        // split u16 target halves = 0
        assert(rd16(b, 0x08) == 1000);     // type
        assert(rd16(b, 0x0a) == 3);        // level
        assert(rd8(b, 0x0e) == 2);         // dir
        assert(rd8(b, 0x0f) == 0);        // count zeroed
        assert(rd8(b, 0x10) == 3);        // flag
    }
    // one append: entry + the param_5 quirk write at the NEXT entry base
    assert(grp.AppendGroup(0x2002, 150, 0xDD, 0xCC, 0x1111, 0x2222, 0x3333, 0x4444));
    {
        const char* b = (const char*)grp.GetBuf();
        assert(grp.GetSize() == 0x54);
        assert(rd8(b, 0x0f) == 1);
        assert(rd32(b, 0x14) == 0x2002);   // id
        assert(rd32(b, 0x18) == 150);      // damage
        assert(rd32(b, 0x1c) == 0xDD);     // data2
        assert(rd32(b, 0x34) == 0xCC);     // dwNext at the NEXT entry base (quirk)
        assert(rd32(b, 0x24) == 0x1111);   // data4 @entry+0x10
        assert(rd32(b, 0x28) == 0x2222);   // data5 @entry+0x14
        assert(rd32(b, 0x2c) == 0x3333);   // data6 @entry+0x18
        assert(rd32(b, 0x30) == 0x4444);   // data7 @entry+0x1c
    }
    // id == 0 still appends (original logs only, no early return)
    assert(grp.AppendGroup(0, 5, 6, 7, 8, 9, 10, 11));
    assert(rd8((const char*)grp.GetBuf(), 0x0f) == 2);
    // first-entry variant: CreateGroup with a non-zero entry id
    CMsgMagicEffect grp2;
    assert(grp2.CreateGroup(777001, 1000, 3, 2, 0, 0, 0x2002, 150, 0xDD, 3));
    {
        const char* b = (const char*)grp2.GetBuf();
        assert(grp2.GetSize() == 0x54);
        assert(rd8(b, 0x0f) == 1);
        assert(rd32(b, 0x14) == 0x2002);
        assert(rd32(b, 0x18) == 150);
        assert(rd32(b, 0x1c) == 0xDD);
        assert(rd32(b, 0x34) == 0);       // next entry base terminator
    }
    // size cap: append until the 0x400 gate refuses
    CMsgMagicEffect big;
    assert(big.CreateGroup(777001, 1000, 3, 2, 0, 0, 0, 0, 0, 3));
    int nApp = 0;
    while (big.AppendGroup(0x2002 + nApp, 1, 2, 3, 4, 5, 6, 7)) nApp++;
    assert(big.GetSize() + 0x20 >= 0x400); // ORIGINAL strict gate held
    // ---------- CMonster::JumpPos (FUN_140388a40) ----
    CMonster mon(555001, 1, "JumpMon");
    mon.SetMapId(777000);
    mon.SetPos(50, 60);
    int nJump = 0;
    upObs->SetPacketSink([&](const void* pv, uint16_t sz) {
        nJump++;
        const char* b = (const char*)pv;
        assert(sz == 14);                     // 4-byte head + MonsterJumpData(10)
        assert(rd16(b, 2) == 20002);          // opcode 0x4e22 in the head
        assert(rd32(b, 4) == 555001);         // id
        assert(rd16(b, 8) == 55);             // x (MonsterJumpData +4)
        assert(rd16(b, 10) == 62);            // y
        assert(rd16(b, 12) == 0);             // data word 0 in the original call
    });
    mon.JumpPos(50, 60);                      // same position: no packet
    assert(nJump == 0);
    mon.JumpPos(55, 62);
    assert(nJump == 1 && mon.GetX() == 55 && mon.GetY() == 62);
    // ---------- CGameMap::IsValidPos (FUN_14015f9d0) ----
    assert(pFxMap->IsValidPos(0, 0) && pFxMap->IsValidPos(500, 500));
    assert(!pFxMap->IsValidPos(-1, 100) && !pFxMap->IsValidPos(100, -1));

    // ---------- SendMagicEffectAfterProcessGroupByPos (FUN_140486fb0) ----
    {
        CMonster monA(555002, 1, "SweepA");
        monA.SetMapId(777000); monA.SetPos(30, 40); monA.SetDir(2);
        CMonster monB(555003, 1, "SweepB");
        monB.SetMapId(777000); monB.SetPos(35, 45); monB.SetDir(5);
        monB.SetBoss(true);
        // (effect 3 already attached at line 156 above)
        std::vector<CUser::SMagicTarget> tg{{nullptr, &monA}, {nullptr, &monB}};
        std::vector<int> dmg{100, -2};
        std::vector<uint32_t> u5{}, u6{};
        std::vector<std::pair<uint32_t, uint32_t>> xy{{60, 61}, {55, 62}};
        struct Cap { uint16_t sz; char buf[0x420]; };
        std::vector<Cap> caps;
        upObs->SetPacketSink([&](const void* pv, uint16_t sz) {
            Cap c; c.sz = sz; memcpy(c.buf, pv, sz); caps.push_back(c);
        });
        assert(upFx->SendMagicEffectAfterProcessGroupByPos(
            1000, 0x1111, 0x2222, tg, dmg, u5, u6, xy));
        // one 1105 (payload 0x74), jump 20002 for each monster, action 10010 for the boss
        assert(caps.size() == 4);
        assert(caps[0].sz == 0x74);               // 1105: 0x34 + 2 * 0x20
        {
            const char* b = caps[0].buf;
            assert(rd32(b, 0x00) == 777001);      // attacker
            assert(rd16(b, 0x08) == 1000);         // type
            assert(rd8(b, 0x0f) == 2);            // count
            assert(rd8(b, 0x10) == 3);            // flag (attr 7)
            assert(rd32(b, 0x14) == 555002);       // entry 1 id
            assert(rd32(b, 0x18) == 100);         // damage code
            assert(rd32(b, 0x1c) == 0);           // d2 = scene diff (single scene)
            assert(rd32(b, 0x24) == 0);           // data4 (leftover slot)
            assert(rd32(b, 0x28) == 0);           // data5
            assert(rd32(b, 0x2c) == 61);          // data6 = y
            assert(rd32(b, 0x30) == 60);          // data7 = x
            assert(rd32(b, 0x34) == 555003);      // entry 2 id
            assert(rd32(b, 0x38) == 0);           // -2: damage zeroed
            assert(rd32(b, 0x3c) == 0);           // d2
            assert(rd32(b, 0x48) == 2);           // -2: data5 = 2
            assert(rd32(b, 0x4c) == 62);          // data6
            assert(rd32(b, 0x50) == 55);          // data7
        }
        assert(caps[1].sz == 14 && caps[2].sz == 14);  // two monster jumps
        assert(rd32(caps[1].buf, 4) == 555002 &&
               rd16(caps[1].buf, 8) == 60 && rd16(caps[1].buf, 10) == 61);
        assert(rd32(caps[2].buf, 4) == 555003 &&
               rd16(caps[2].buf, 8) == 55 && rd16(caps[2].buf, 10) == 62);
        assert(caps[3].sz == 32);                 // CMsgAction (head+ActionData 28)
        {
            const char* b = caps[3].buf;
            assert(rd16(b, 2) == 10010);          // opcode 0x271a
            assert(rd32(b, 8) == 555003);         // id (after the u32 time slot)
            assert(rd32(b, 0xc) == 407);          // data = 0x197
            assert(rd32(b, 0x14) == 5);           // action = monster dir
            assert(rd16(b, 0x18) == 3);          // p6 = 3
            assert(rd16(b, 0x1a) == 0);           // dir = 0
            assert(rd16(b, 0x1c) == 55);          // x post-jump
            assert(rd16(b, 0x1e) == 62);          // y post-jump
        }
        assert(monA.GetX() == 60 && monA.GetY() == 61);
        assert(monB.GetX() == 55 && monB.GetY() == 62);
        // user-target path: reposition via CUser::JumpPos (slot 0x378 model)
        auto upVic = std::make_shared<CUser>(777003); upVic->SetName("SweptUser");
        upVic->SetMapId(777000);
        assert(pFxMap->AddUser(upVic));
        upVic->SetAlive(true);
        upVic->SetPos(10, 10);
        std::vector<CUser::SMagicTarget> tu{{upVic.get(), nullptr}};
        std::vector<int> du{55};
        std::vector<std::pair<uint32_t, uint32_t>> xu{{12, 13}};
        assert(upFx->SendMagicEffectAfterProcessGroupByPos(
            1000, 0, 0, tu, du, u5, u6, xu));
        assert(upVic->GetX() == 12 && upVic->GetY() == 13);
        // dead target: the reposition loop skips it entirely
        upVic->SetAlive(false);
        assert(upFx->SendMagicEffectAfterProcessGroupByPos(
            1000, 0, 0, tu, du, u5, u6, xu));
        assert(upVic->GetX() == 12 && upVic->GetY() == 13); // unchanged
        // -1 damage code: skip (ORIGINAL gate)
        upVic->SetAlive(true);
        du[0] = -1;
        assert(upFx->SendMagicEffectAfterProcessGroupByPos(
            1000, 0, 0, tu, du, u5, u6, xu));
        assert(upVic->GetX() == 12 && upVic->GetY() == 13); // unchanged
        // invalid record: whole call refused (ORIGINAL +0x90 gate)
        assert(!upFx->SendMagicEffectAfterProcessGroupByPos(
            999999, 0, 0, tu, du, u5, u6, xu));
    }

    // ---------- launch gates (FUN_1404864f0 / 1404831f0 / 1403e9290) ----
    {
        // stage-field ABI: GetAttrib(100+N) = cq_magictype column N
        CPlayerMagic* pRec = upFx->FindMagic(1000);
        assert(pRec);
        assert(pRec->GetAttrib(0x66) == 1);    // col 2  sort  (Thunder)
        assert(pRec->GetAttrib(0x68) == 1);    // col 4  crime
        assert(pRec->GetAttrib(0x7a) == 0);    // col 22 weapon_subtype
        assert(pRec->GetAttrib(0x82) == 0);    // col 30 weapon_hit
        assert(pRec->GetAttrib(0x87) == 0 && pRec->GetAttrib(0x88) == 0);

        CMonster monI(555010, 1, "GateMon"); monI.SetMapId(777000);
        std::vector<CUser::SMagicTarget> gt{{nullptr, &monI}};
        // ordinary sort 1 monster hit: gate open (pk count 0, no immunity)
        assert(!upFx->IsTargetProtected(1000, gt[0]));
        // the attacker himself: friendly (FUN_1404864f0 final gate)
        std::vector<CUser::SMagicTarget> gs{{upFx.get(), nullptr}};
        assert(upFx->IsTargetProtected(1000, gs[0]));
        // safe zone (map vtable+0x3d8 refused): skip
        pFxMap->SetSafeZone(true);
        assert(upFx->IsTargetProtected(1000, gt[0]));
        pFxMap->SetSafeZone(false);
        // sort 50 (0x32): gate always open
        assert(upFx->LearnMagic(10430, 0));            // sort 50, crime 0
        assert(!upFx->IsTargetProtected(10430, gs[0]));
        // sort 65 + sort-immune monster: skip via the 30-sort switch
        assert(upFx->LearnMagic(11180, 0));           // sort 65
        assert(!upFx->IsTargetProtected(11180, gt[0]));
        monI.SetSortImmune(true);
        assert(upFx->IsTargetProtected(11180, gt[0]));
        monI.SetSortImmune(false);
        // pk-count > 999 cascade: STR_PK + skip
        pFxMap->SetPkCount(1000);
        assert(upFx->IsTargetProtected(1000, gs[0]));
        pFxMap->SetPkCount(0);
        // missing record: ORIGINAL logs and leaves the gate OPEN
        assert(!upFx->IsTargetProtected(999999, gt[0]));

        // sweep gate (FUN_1404831f0): Thunder crime=1 but no 0xa0 status
        assert(!upFx->SweepTarget(1000, gt[0], false));
        monI.AddStatus(0xa0, 10000);                  // resist 10000: roll always <=
        assert(upFx->SweepTarget(1000, gt[0], false));
        // crime 0 (sort-50 stage 10430) + not type 0x2d46: the gate
        // refuses even though the target carries the status
        assert(!upFx->SweepTarget(10430, gt[0], false));
        monI.AddStatus(0xa0, 0);                       // resist 0: roll never <=
        assert(!upFx->SweepTarget(1000, gt[0], false));
        monI.AddStatus(0xa0, 10000);
        assert(upFx->SweepTarget(1000, gt[0], true)); // type 0x2d46 bypass
        // dead target: refused
        CMonster monDead(555011, 1, "DeadMon"); monDead.SetMapId(777000);
        monDead.SetLife(0);
        std::vector<CUser::SMagicTarget> gd{{nullptr, &monDead}};
        monDead.AddStatus(0xa0, 10000);
        assert(!upFx->SweepTarget(1000, gd[0], true));
        // registry hook stays inert
        upFx->RecordHitPos(gt[0]);
    }

    printf("MAGIC_EFFECT_OK: 1105 base/append/withtarget/full layouts byte-exact, "
           "1103 layout byte-exact, effect masks attach/launch/drop verified, "
           "SendMagicEffectAfterProcess broadcast byte-exact, "
           "CreateGroup/AppendGroup/JumpPos/IsValidPos verified, "
           "SendMagicEffectAfterProcessGroupByPos end-to-end\n");
    return 0;
}

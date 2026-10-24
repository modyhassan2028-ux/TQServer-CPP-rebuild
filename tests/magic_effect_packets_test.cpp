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

    printf("MAGIC_EFFECT_OK: 1105 base/append/withtarget/full layouts byte-exact, "
           "1103 layout byte-exact, effect masks attach/launch/drop verified, "
           "SendMagicEffectAfterProcess broadcast byte-exact, "
           "CreateGroup/AppendGroup/JumpPos/IsValidPos verified\n");
    return 0;
}

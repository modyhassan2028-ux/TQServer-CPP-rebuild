// ---------------------------------------------------------------------------
// ORIGINAL damage roll chain (session-9 decode, PORTING_LOG "جلسة تاسعة،
// تكملة"). This port follows the 14-step literal sequence of
// FUN_1403ec0a0 (LaunchDamage) and its four components:
//   FUN_1403e98e0 (weapon roll, physical)  -> PhysRollWeapon
//   FUN_1403e9e30 (atk - def, physical)     -> PhysRollDiff
//   FUN_1403ea400 (weapon roll, magic)      -> MagicRollWeapon
//   FUN_1403eaad0 (atk - def, magic)        -> MagicRollDiff
//
// The "kernel" objects of the original ABI (att/tgt) map onto CUser here;
// monster kernels land when the monster model gains the slots.
//
// Decoded-but-not-yet-modeled original values are carried by DamageCtx as
// documented stubs so tests can inject them deterministically:
//   FUN_14031caa0  PK adjust      (player-vs-monster, rank < 3000)
//   FUN_1401619e0  PK protection   (status 0xd, non-boss target)
//   FUN_140162250  weapon quality bonus (>12 grade path)
//   FUN_140181080 / FUN_140181280 attacker luck values
//   FUN_140182560  dodge roll value (vs RandGet(10000))
//   FUN_14031d8a0  backstab steering
//   FUN_14031cfb0  crit probe (independent of the crit flag)
//   FUN_1403eb000  final settle (returns false -> floor 2)
//   FUN_1402f2de0 / FUN_1402f2e10 battle aggro registration
//   vtable+800     ApplyDamage on the target
#pragma once
#include <cstdint>
#include "User.h"
#include "Msg.h"

namespace tq {

struct DamageCtx {
    // attacker-side runtime (stub values, test-injectable)
    bool    bAttackerWeapon = false;   // FUN_140178c40: attacker holds a weapon
    int32_t iLuck = 0;                 // FUN_140181080 (luck, >209 -> +50% path)
    int32_t iLuckM = 0;                // FUN_140181280 (diff-component luck %)
    int32_t iWeaponQualityPct = 0;    // FUN_140162250: (grade-12)*base/100 %
    int32_t iPkAdjust = 0;             // FUN_14031caa0 result (signed)
    bool    bPkProtection = false;     // status 0xd PK protection active
    int32_t iPkProtectionVal = 0;     // FUN_1401619e0 prot argument
    // target-side battle defense point (0x1001 via vtable+0x298)
    bool    bTargetDefensePoint = false; // GetPoint(0x1001) != 0
    int32_t iTargetDefPct1 = 0;       // FUN_1401811180: cap 100 percent
    int32_t iTargetDefPct2 = 0;       // FUN_140181380: /100 percent
    // remaining stubs
    int32_t iDodgeVal = 0;             // FUN_140182560 (roll < iDodgeVal -> dodge)
    bool    bCritProbe = false;        // FUN_14031cfb0(att, tgt)
    int32_t iSteerDelta = 0;           // FUN_14031d8a0 backstab delta
    bool    bSettleOk = true;          // FUN_1403eb000 returned true
    // 0x230/0x238 rejection gates on the target (defense point active but
    // battle-defense not engaged) and the 0x27 status gate
    bool    bGate230 = false, bGate238 = false, bGateStatus27 = false;
    // level factor (FUN_1400a76d0) - constant 10000 until the kernel lands
    uint32_t dwLevelFactor = 10000;
};

// ---- component 1: FUN_1403e98e0 (weapon roll, physical) ----
inline uint32_t PhysRollWeapon(CUser* pAtt, const DamageCtx& c) {
    uint32_t dwMin = pAtt->GetHitMin(), dwMax = pAtt->GetHitMax();
    uint32_t dmg = dwMin + (uint32_t)tq::RandGet(dwMax > dwMin ? dwMax - dwMin : 0);
    if (c.bAttackerWeapon) {
        dmg += (uint32_t)((uint64_t)dmg * (uint64_t)c.iLuck / 100);
        if (c.iWeaponQualityPct > 0)  // ORIGINAL: quality > 12 -> (q-12)*base/100
            dmg += (uint32_t)((uint64_t)dmg * (uint64_t)c.iWeaponQualityPct / 100);
    }
    dmg = (uint32_t)((int32_t)dmg + c.iPkAdjust); // FUN_14031caa0 (stub, signed)
    if (c.bPkProtection)  // status 0xd + non-boss target: FUN_1401619e0 (stub)
        dmg = (uint32_t)((int32_t)dmg - c.iPkProtectionVal);
    return dmg;
}

// ---- component 2: FUN_1403e9e30 (atk - def, physical) ----
inline uint32_t PhysRollDiff(CUser* pAtt, CUser* pTgt, const DamageCtx& c) {
    int32_t diff = (int32_t)pAtt->GetKernelAttack() - (int32_t)pTgt->GetKernelDefense();
    if (diff < 0) diff = 0; // ORIGINAL: max(atk-def, 0)
    uint32_t dmg = (uint32_t)diff;
    dmg += (uint32_t)((uint64_t)dmg * (uint64_t)c.iLuckM / 100);
    if (c.bAttackerWeapon && c.iWeaponQualityPct > 0)
        dmg += (uint32_t)((uint64_t)dmg * (uint64_t)c.iWeaponQualityPct / 100);
    dmg = (uint32_t)((int32_t)dmg + c.iPkAdjust);
    if (c.bPkProtection)
        dmg = (uint32_t)((int32_t)dmg - c.iPkProtectionVal);
    return dmg;
}

// ---- components 3/4: FUN_1403ea400 / FUN_1403eaad0 (magic pair) ----
// Same structure as the physical pair (session-9 spec); selected when the
// attacker's 0x260/0x268 states (transformed/mounted) are set.
inline uint32_t MagicRollWeapon(CUser* pAtt, const DamageCtx& c) {
    return PhysRollWeapon(pAtt, c); // 1403ea400 mirrors 1403e98e0
}
inline uint32_t MagicRollDiff(CUser* pAtt, CUser* pTgt, const DamageCtx& c) {
    return PhysRollDiff(pAtt, pTgt, c); // 1403eaad0 mirrors 1403e9e30
}

// ---- FUN_1403ec0a0: LaunchDamage (14-step literal sequence) ----
// Original signature: (kernel* att, kernel* tgt, char type8001,
//   u8 sendFlag, uint power, uint unused, char luckyBoost, i64 power64,
//   char crit). Returns the rolled damage.
inline uint32_t LaunchDamage(CUser* pAtt, CUser* pTgt, bool bType8001,
                             uint8_t /*ucSendFlag*/, uint32_t /*dwPower*/,
                             char cLuckyBoost, uint64_t /*uPower64*/, char cCrit,
                             const DamageCtx& c)
{
    // 1. null guards -> return 1
    if (!pAtt || !pTgt) return 1;
    // 2. aggro registration (FUN_1402f2de0 / FUN_1402f2e10) - documented stub
    // 3. rejection gates -> return 1
    if (c.bTargetDefensePoint && c.bGate230 && !c.bGate238) return 1;
    if (c.bTargetDefensePoint && c.bGateStatus27) return 1;
    if (pTgt->IsDie()) return 1; // vtable+0x290
    // 4. equation select: attacker 0x260/0x268 (transformed/mounted) -> magic
    //    pair, else the physical pair
    uint32_t dmg;
    bool bMagicEquation = false; // attacker 0x260()/0x268() states - stub off
    if (bMagicEquation)
        dmg = MagicRollWeapon(pAtt, c) + MagicRollDiff(pAtt, pTgt, c);
    else
        dmg = PhysRollWeapon(pAtt, c) + PhysRollDiff(pAtt, pTgt, c);
    // 5. luck boost: luckyBoost && attacker weapon && luck > 209 (0xd1)
    //    -> dmg += dmg * 0x32 / 100  (+50%)
    if (cLuckyBoost && c.bAttackerWeapon && c.iLuck > 0xd1)
        dmg += dmg * 0x32 / 100;
    // 6. defense subtract 1: FUN_1401811180 val capped at 100 ->
    //    dmg -= (dmg/2 * val) / 100, floor at 0
    if (c.bTargetDefensePoint) {
        int32_t val = c.iTargetDefPct1 > 100 ? 100 : c.iTargetDefPct1;
        int32_t sub = (int32_t)(((uint64_t)(dmg / 2) * (uint64_t)val) / 100);
        dmg = (uint32_t)((int32_t)dmg - sub);
    }
    // 7. weapon weakening: FUN_14016e4c0(weapon, tgt) -> dmg *= 2
    if (c.bAttackerWeapon) dmg *= 2;
    // 8. backstab steering: FUN_14031d8a0(att, tgt, dmg, power64) - stub delta
    dmg = (uint32_t)((int32_t)dmg + c.iSteerDelta);
    // 9. apply damage: tgt->vtable+800(att, adjusted) - stub (returns actual)
    //    (the original applies the damage here and keeps adjusting below)
    // 10. defense subtract 2: FUN_140181380 val -> dmg = dmg - dmg*val/100
    //     (magic constant 0x51eb851f = /100)
    if (c.bTargetDefensePoint) {
        int32_t sub = (int32_t)(((uint64_t)dmg * (uint64_t)c.iTargetDefPct2) / 100);
        dmg = (uint32_t)((int32_t)dmg - sub);
    }
    // 11. critical: crit flag || FUN_14031cfb0 probe -> MulDiv(dmg, 0x96, 100)
    if (cCrit || c.bCritProbe)
        dmg = (uint32_t)(((uint64_t)dmg * 0x96) / 100); // x1.5
    // 12. dodge: defense point && (attacker defense || tgt 0x1002) ->
    //     RandGet(10000) < FUN_140182560() -> dmg /= 2 (+ FUN_14031cee0 note)
    if (c.bTargetDefensePoint && tq::RandGet(10000) < c.iDodgeVal)
        dmg /= 2;
    // 13. final bonus: empty 0x1002 or vtable+0x38()==10000 && not boss ->
    //     bless (attacker vtable+0x200) minus deduct (target vtable+0x210)
    //     when the attacker is not a boss; type8001 -> cap bonus at 1000;
    //     attacker weapon -> cap bonus at 1000
    int32_t bonus = 0;
    bool bFinalBonus = !pTgt->IsBoss() /* empty 0x1002 / rank 10000 path */;
    if (bFinalBonus) {
        bonus = (int32_t)pAtt->GetBless();
        if (!pAtt->IsBoss())
            bonus -= (int32_t)pTgt->GetDeduct();
        if (bType8001 && bonus > 1000) bonus = 1000;
        if (c.bAttackerWeapon && bonus > 1000) bonus = 1000;
        dmg = (uint32_t)((int32_t)dmg + bonus);
    }
    // 14. final settle FUN_1403eb000(attId, tgtDef, &dmg): true -> the
    //     value stays as-is; false -> floor at 2 (step-13 sum floor is >= 2)
    if (!c.bSettleOk || dmg < 2) dmg = 2;
    return dmg;
}

} // namespace tq

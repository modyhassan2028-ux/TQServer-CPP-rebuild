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
#include <algorithm>
#include <vector>
#include "User.h"
#include "Msg.h"
#include "PlayerMagic.h"

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
    // ---- DamageCalc (FUN_1404847d0) runtime stubs ----
    int32_t iMagicAtkMin = 0, iMagicAtkMax = 0; // FUN_1401805b0/FUN_1401873c0
    int32_t iSlot208 = 0;            // kernel slot 0x208 (physical w/ defense)
    bool    bCasterByte300 = false;  // *(char*)(caster+300) == 1 (0x305c path)
    int32_t iCasterSelector = 0;     // *(caster+0xf8) (FUN_140483100 selector)
    bool    bStatus6c = false;       // status 0x6c on the attacker (x2)
    bool    bStatus78 = false;       // status 0x78 on the attacker (x2)
    bool    bTargetMonster = false;  // target->vtable+0x240 (monster kernel)
    // ---- SkillDamage (FUN_1402f3100) runtime stubs ----
    bool    bAttackerDefensePoint = false; // attacker GetPoint(0x1001) != 0
    int32_t iAttDef98 = 0;         // attacker def-point vtable+0x98 (2nd call)
    bool    bTargetRankBelow3000 = false;  // target 0x1002 vtable+0x50 < 3000
    int32_t iTgtE0 = 0;             // target vtable+0xe0 (percent base)
    int32_t iAttB60 = 0;            // FUN_140180b60 (attacker side)
    int32_t iTgtC70 = 0;            // FUN_140160c70 (target side)
    int32_t iTgt74f0 = 0;           // FUN_1401874f0 (target def subtraction)
    bool    bWeaponWeaken = false;  // FUN_14016e4c0(att, tgt) != 0 -> x2
    bool    bTgt1040Attr10 = false; // 0x1040 point, attr 4 == 10 -> x10
    bool    bCritProbe2 = false;    // FUN_14031d020 (x2 crit, distinct probe)
    bool    bQualityPresent = false; // FUN_140161560() != 0 (bonus cap)
    int32_t iTgtSlot218 = 0;        // target vtable+0x218 (bonus deduction)
    bool    bEcf70Check = false;    // FUN_1402ecf70 -> return dmg unchanged
    bool    bTgtHas1002Rank = false; // target 0x1002 point with rank != 10000
    // ---- launch-chain gate stubs (FUN_1404864f0 / 1404831f0 / map gate) ----
    bool    bGatePkZone = false;    // PK-map branch (STR_PK message) -> reject
    bool    bGatePkSwitch = false;  // attack-sort switch (0x1002 probe) -> reject
    bool    bGateMapFinal = false;  // FUN_140186200 final gate -> reject
    bool    bMapGate398 = false;    // target vtable+0x398 map rejection
    bool    bProbeHit = false;      // FUN_1403e9290 status probe hit
    // ---- fan-loop broadcast gate stubs (FUN_140499830) ----
    bool    bFanLevelUp = false;    // local_558 level-up flag
    bool    bFanLevelProb = false; // local_55c + RandGet(100) < 10 gate
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


// ---- FUN_140481400 / FUN_140481560: hit-kind probes ----
// IsPhysicalHit: weapon_hit==0 -> true; otherwise the attacker must hold a
// weapon (FUN_140178c40 + FUN_14032b4b0(item,5) - stubbed bAttackerWeapon).
inline bool IsPhysicalHit(const CMagicTypeInfo* pType, const DamageCtx& c) {
    uint32_t wh = pType->dwWeaponHit;
    return wh == 0 || (wh != 1 && c.bAttackerWeapon);
}
// IsMagicHit: the mirrored probe (weapon_hit==1 -> true; no weapon -> magic)
inline bool IsMagicHit(const CMagicTypeInfo* pType, const DamageCtx& c) {
    uint32_t wh = pType->dwWeaponHit;
    return wh == 1 || (wh != 0 && !c.bAttackerWeapon);
}

// ---- FUN_1402f3100: SkillDamage - read COMPLETE (def 600555-600873).
// Original signature: (battleCtx, att, tgt, baseDmg, power64). Literal
// sequence after the rejection gates (same 0x230/0x238 + 0x27 gates as
// FUN_1403ec0a0, with extra FUN_14016cfc0/14016cff0 sub-checks on the 0x27
// path - not modeled yet, gated via bGateStatus27):
inline uint32_t SkillDamage(CUser* pAtt, CUser* pTgt, uint32_t dwBase,
                            uint64_t uPower64, const DamageCtx& c)
{
    // gates -> return 1
    if (c.bTargetDefensePoint && c.bGate230 && !c.bGate238) return 1;
    if (c.bTargetDefensePoint && c.bGateStatus27) return 1;
    if (pTgt->IsDie()) return 1;
    int32_t dmg = (int32_t)dwBase;
    // attacker defense point (local_40): vtable+0x98 called twice, the
    // second value is added (decompile artifact kept as iAttDef98)
    if (c.bAttackerDefensePoint)
        dmg += c.iAttDef98;
    if (!c.bTargetDefensePoint) {
        // no target defense point: target 0x1002 rank < 3000 -> PK adjust
        if (c.bTargetRankBelow3000)
            dmg += c.iPkAdjust; // FUN_14031caa0(att, tgt, dmg) - value stub
    } else {
        // target defense point: dmg -= floor(dmg/4)
        // ORIGINAL: dmg - (dmg + (dmg>>31 & 3)) >> 2 (signed floor trick)
        dmg = dmg - ((dmg + ((dmg >> 31) & 3)) >> 2);
    }
    // percent bonus: p = tgtE0 + (tgtC70 - attB60), only if >= 0, cap 90
    int32_t pct = 0;
    if (c.iTgtE0 + (c.iTgtC70 - c.iAttB60) >= 0) {
        pct = c.iTgtE0 + (c.iTgtC70 - c.iAttB60);
        if (pct > 0x5a) pct = 0x5a; // cap 90
    }
    // ORIGINAL: (pct*dmg * -0x51eb851f)>>32>>5 = dmg*pct/100 (magic /100)
    dmg += (int32_t)(((int64_t)pct * dmg) / 100);
    if (c.bAttackerDefensePoint) {
        int32_t luckM = c.iLuckM; // FUN_140181280
        dmg += (int32_t)(((int64_t)luckM * dmg) / 100);
        dmg += c.iMagicAtkMax;    // FUN_1401873c0(attacker def point)
        if (luckM > 0xb3)        // > 179 -> +5%
            dmg += dmg / 0x14;
        // FUN_1401631c0(attDefPoint, &dmg, tgt) settle - stub passthrough
    }
    if (c.bTargetDefensePoint) {
        dmg -= c.iTgt74f0;       // FUN_1401874f0 (target def point)
        int32_t val = c.iTargetDefPct1; // FUN_140181180
        if (val >= 0x65) val = 100;
        // dmg += (-(dmg/2) * val)/100  (defense subtract 1, cap 100)
        dmg += (int32_t)((-(int64_t)(dmg / 2) * val) / 100);
    }
    // weapon weakening: attacker def point && FUN_14016e4c0 -> x2
    if (c.bAttackerDefensePoint && c.bWeaponWeaken) dmg *= 2;
    if (dmg < 0) dmg = 0;
    // target 0x1040 point: attr 4 == 10 && FUN_1402bc2c0 -> x10
    if (c.bTgt1040Attr10) dmg *= 10;
    // backstab steering: FUN_14031d8a0(att, tgt, dmg, power64) - stub delta
    dmg += c.iSteerDelta;
    // apply: tgt->vtable+0x328(tgt, att, dmg) - stub passthrough
    if (c.bTargetDefensePoint) {
        int32_t val = c.iTargetDefPct2; // FUN_140181380
        if (val < 0x65) { if (val < 1) goto skip_sub2; }
        else val = 100;
        { // dmg -= dmg*val/100 (magic /100 constant)
            dmg -= (int32_t)(((int64_t)val * dmg) / 100);
        }
    }
skip_sub2:
    // crit probe FUN_14031d020 -> MulDiv(dmg, 200, 100) = x2 (!), and
    // FUN_14031cee0(power64, 4) break-notify (stub)
    if (c.bCritProbe2)
        dmg = (int32_t)(((int64_t)dmg * 200) / 100);
    // final bonus: (no 0x1002 or rank 10000) && target not boss:
    //   bonus = att slot 0x208; attacker not boss: -= tgt slot 0x218;
    //   attacker def point && quality present -> cap 1000
    int32_t bonus = 0;
    bool bFinalBonus = !c.bTgtHas1002Rank /* or vtable+0x38()==10000 */
                       && !pTgt->IsBoss();
    if (bFinalBonus) {
        bonus = c.iSlot208;
        if (!pAtt->IsBoss())
            bonus -= c.iTgtSlot218;
        if (c.bAttackerDefensePoint && c.bQualityPresent && bonus > 1000)
            bonus = 1000;
        dmg += bonus;
    }
    // target defense point && FUN_1402ecf70(battle, attId, tgtId, &dmg)
    // -> return the value as-is (stub flag)
    if (c.bTargetDefensePoint && c.bEcf70Check)
        return (uint32_t)dmg;
    if (dmg < 2) dmg = 1; // ORIGINAL floors at 1 here (not 2)
    return (uint32_t)dmg;
}

// ---- FUN_1404847d0: total damage calculation (session-9 literal spec) ----
// ORIGINAL signature: uint DamageCalc(caster, target, power64, skillPower)
// with caster+0x90 = the CPlayerMagic record (null -> log -> return 0) and
// the magic TYPE record supplying sort (attr 0x66 -> col 2), type
// (cq_magic col 2), power (attr 0x6e -> col 10), status_data0 (col 35),
// status_data2 (col 37), attr_power (col 39) and data (col 44).
inline uint32_t DamageCalc(CUser* pCaster, CUser* pTarget,
                           const CPlayerMagic* pRec, const CMagicTypeInfo* pType,
                           uint64_t uPower64, int32_t iSkillPower,
                           const DamageCtx& c)
{
    if (!pRec) { // caster+0x90 null -> log -> return 0
        printf("[MAGIC] DamageCalc: no magic record (caster id %u)\n",
               pCaster ? pCaster->GetId() : 0);
        return 0;
    }
    if (!pCaster || !pType) return 0;
    if (pTarget->IsDie()) return 1; // vtable+0x290 nonzero -> no damage

    const uint32_t res8 = c.dwLevelFactor; // FUN_1400a76d0 (10000 for now)
    const bool bHasDef = c.bTargetDefensePoint; // GetPoint(0x1001) != 0
    const uint32_t dwSort = (uint32_t)pType->Field(2);   // attr 0x66
    // ORIGINAL reads the type from the PLAYER MAGIC record
    // (FUN_140418c50(rec, 2) = cq_magic col 2) - verified at the 0x3070/
    // 0x305c tail; same value as the stage's dwType
    const uint32_t dwType = (uint32_t)pRec->GetAttrib(2);
    const bool bPhys  = IsPhysicalHit(pType, c);
    const bool bMagic = IsMagicHit(pType, c);

    // the shared min/max defense formula (slots 0x88/0x90 + luck + 0x200):
    //   ((min + RandGet(max-min) + luck*(min+rand)/100 + slot0x200) * res8)/10000
    auto fnMinMaxFormula = [&](void) -> uint32_t {
        uint32_t dwMin = pCaster->GetHitMin(), dwMax = pCaster->GetHitMax();
        uint32_t roll = dwMin + (uint32_t)tq::RandGet(dwMax > dwMin ? dwMax - dwMin : 0);
        uint64_t sum = roll + (uint64_t)((uint64_t)roll * (uint64_t)c.iLuck / 100)
                     + pCaster->GetBless();
        return (uint32_t)((sum * res8) / 10000);
    };

    // ---- poison branch (sort 13, via IsMagicHit) - early return ----
    if (bMagic && dwSort == 13) {
        uint32_t dwPower = (uint32_t)pType->Field(10); // attr 0x6e
        uint32_t uVar6 = LaunchDamage(pCaster, pTarget, false, 1,
                                      dwPower, 0, uPower64, 0, c);
        uint32_t dmg = 0;
        if (bHasDef)
            dmg = fnMinMaxFormula();
        // status 0x6c on the attacker && target monster && not boss -> x2
        if (c.bStatus6c && c.bTargetMonster && !pTarget->IsBoss()) dmg *= 2;
        return uVar6 > dmg ? uVar6 : dmg;
    }

    uint32_t uVar10 = 0, uVar17 = 0;

    // ---- non-poison branch 1: physical (FUN_140481400) ----
    if (bPhys) {
        if (dwSort == 37 && iSkillPower) { // sort 0x25 with skill power
            uVar10 = SkillDamage(pCaster, pTarget, (uint32_t)iSkillPower,
                                 uPower64, c);
            if (bHasDef) {
                // (atkMin + atkMax + luckM*sum/100 + slot0x208 + skillPower)
                //   * res8 / 10000   (sum = atkMin + atkMax, literal)
                int64_t sum = (int64_t)c.iMagicAtkMin + c.iMagicAtkMax;
                sum += (int64_t)((uint64_t)sum * (uint64_t)c.iLuckM / 100);
                sum += c.iSlot208 + iSkillPower;
                uVar17 = (uint32_t)(((uint64_t)sum * res8) / 10000);
            }
        } else {
            uint32_t dwPower = (uint32_t)pType->Field(10); // attr 0x6e
            // type 0x305c (12380) && *(char*)(caster+300)==1 -> status_data0
            if (dwType == 0x305c && c.bCasterByte300)
                dwPower = (uint32_t)pType->Field(35);
            uVar10 = SkillDamage(pCaster, pTarget, dwPower, uPower64, c);
            if (bHasDef) {
                // (sum + luckM*sum/100 + slot0x208 + power + atkMin + atkMax)
                //   * res8 / 10000   (sum = atkMin + atkMax, literal reading)
                int64_t sum = (int64_t)c.iMagicAtkMin + c.iMagicAtkMax;
                sum += (int64_t)((uint64_t)sum * (uint64_t)c.iLuckM / 100);
                sum += c.iSlot208 + dwPower + c.iMagicAtkMin + c.iMagicAtkMax;
                uVar17 = (uint32_t)(((uint64_t)sum * res8) / 10000);
            }
        }
    }

    // ---- non-poison branch 2: magic (FUN_140481560) - ACCUMULATES ----
    if (bMagic) {
        uint8_t ucSendFlag = 1;
        uint32_t dwPower = (uint32_t)pType->Field(10); // default: attr 0x6e
        if (dwSort == 57 || dwType == 0x2d5a) { // sort 0x39 / type 11610
            // boss -> 30100; else max(30010, status_data0)
            dwPower = pTarget->IsBoss() ? 30100u
                : (uint32_t)std::max(30010, pType->Field(35));
        } else if (dwType == 0x2f30) { // 12080: distance < 4 -> data + 30000
            int32_t dx = (int32_t)pCaster->GetX() - (int32_t)pTarget->GetX();
            int32_t dy = (int32_t)pCaster->GetY() - (int32_t)pTarget->GetY();
            if (std::max(dx < 0 ? -dx : dx, dy < 0 ? -dy : dy) < 4)
                dwPower = (uint32_t)pType->Field(44) + 30000; // data + 30000
        } else if (dwType == 0x3002) { // 12290: same as sort 0x39 logic
            dwPower = pTarget->IsBoss() ? 30100u
                : (uint32_t)std::max(30010, pType->Field(35));
        } else if (dwType == 0x2f26) { // 12070: FUN_140483100 selector
            switch (c.iCasterSelector) { // *(caster+0xf8)
            case 1: dwPower = (uint32_t)pType->Field(37); break; // status_data2
            case 2: dwPower = (uint32_t)pType->Field(45); break; // runtime col 45
            case 3: dwPower = (uint32_t)pType->Field(46); break; // runtime col 46
            default: break; // keep attr 0x6e
            }
        } else if ((dwType == 0x2ed6 || dwType == 0x2f4e || dwType == 0x2fd0)
                   && !bHasDef) { // 11926/12110/12240 without defense
            ucSendFlag = 0;
            dwPower = (uint32_t)pType->Field(35); // status_data0
        } else if ((dwType == 0x3020 || dwType == 0x302a || dwType == 0x3034)
                   && !bHasDef) { // 12320/12298/12340 without defense
            dwPower = (uint32_t)pType->Field(35);
        } else if ((dwType == 0x2f58 || dwType == 0x2f62 || dwType == 0x2f6c)
                   && !bHasDef) { // heal types 12120/12130/12140
            dwPower = (uint32_t)pType->Field(35);
        }
        // physical and magic ACCUMULATE (+=)
        uVar10 += LaunchDamage(pCaster, pTarget, dwType == 0x1f41, ucSendFlag,
                               dwPower, 0, uPower64, 0, c);
        if (bHasDef)
            uVar17 = fnMinMaxFormula(); // backup uVar17 (slots 0x88/0x90)
    }

    // ---- step 3: doubling statuses ----
    if (c.bStatus6c && c.bTargetMonster && !pTarget->IsBoss()) uVar10 *= 2;
    if (c.bStatus78 && c.bTargetMonster) uVar10 *= 2;
    // ---- step 4: final = max(uVar10, uVar17) ----
    uint32_t result = uVar10 > uVar17 ? uVar10 : uVar17;
    // ---- step 5: type 0x3070 (12400) leaves the target at 1 HP ----
    if (dwType == 0x3070 && bHasDef && pTarget->GetLife() <= result)
        result = pTarget->GetLife() - 1;
    // ---- step 6: type 0x305c damage cap (attr_power) ----
    if (dwType == 0x305c && bHasDef
        && (uint32_t)pType->Field(39) <= result)
        result = (uint32_t)pType->Field(39);
    return result;
}

// ===========================================================================
// Launch chain (session "Fan Loop" step 6) - FUN_1404a1f70 and its helpers.
// ORIGINAL: uint LaunchOnTarget(caster, target, p3, p4, p5, p6, skillPower)
// where p3/p4/p5/p6 are collector lists (written via FUN_1401af440 /
// FUN_14000f0a0 / FUN_1402751c0) that the fan loop (FUN_140499830) later
// broadcasts as MsgMagicEffect. Modeled here as a LaunchOut struct.
//
// ABI note: FUN_1404847d0's "power64" (param_3) is actually a POINTER to a
// stack slot holding the launched effect record (&local_34 in the caller,
// initialized to 0): null-checked (param_3 == 0), then handed down to
// FUN_14031cee0(ptr, 4/8) notify calls and FUN_14031d8a0 steering. Our
// uPower64 param carries that pointer opaquely.
// ===========================================================================
struct LaunchOut {
    int32_t dwDamage = 0;    // param_4 list: the rolled damage
    uint32_t dwEffectSlot = 0; // param_5 list: the effect-record slot (local_34)
    uint32_t dwPost = 0;      // param_6 list: FUN_140484670 result (local_30)
};

// record attr helper: ORIGINAL FUN_140418c50(rec, idx) - idx >= 0x64
// resolves through the magic TYPE record (attr - 100 = column), smaller
// indices are the record's own columns (2 = type).
inline int32_t RecAttrib(const CPlayerMagic* pRec, const CMagicTypeInfo* pType,
                         uint32_t dwIdx) {
    return dwIdx >= 100 ? pType->Field(dwIdx - 100)
                        : pRec->GetAttrib(dwIdx);
}

// ---- FUN_1404864f0: the PK-zone launch gate. Returns true = REJECT. ----
// Structure literal; the deep PK checks (FUN_14017ef50/14011dbb0/14016cc30,
// PK level 0xef4, STR_PK message, FUN_140186200 and the target 0x1002 probe)
// need the map/battle kernel and are stubbed via ctx flags (neutral = pass).
inline bool LaunchGate(const DamageCtx& c) {
    if (c.bGatePkZone) return true;      // the PK-map branch (STR_PK message)
    if (c.bGatePkSwitch) return true;   // the attack-sort switch (0x1002 probe)
    return c.bGateMapFinal;              // FUN_140186200 result (false = pass)
}

// ---- FUN_140483270: pre-register the target's 0x1001 defense point with
// the battle module (6-arg 0x2d8 call). Documented stub - needs the
// battle-module kernel. ----
inline void PreRegisterDefensePoint(CUser*, CUser*) {}

// ---- FUN_1404831f0: status-probe gate. Returns true -> caller returns -2.
inline bool StatusProbeGate(const CMagicTypeInfo* pType, const CPlayerMagic* pRec,
                            uint32_t dwType, bool bType2d46, const DamageCtx& c) {
    // ORIGINAL: (rec null || GetAttrib(rec, 0x68) == 0) && !type2d46 -> 0;
    // else FUN_1403e9290(target) decides (stubbed: ctx.bProbeHit)
    bool bAttr68 = pRec == nullptr || pType->Field(4) != 0; // attr 0x68 = col 4
    if (!bAttr68 && !bType2d46) return false;
    return c.bProbeHit; // FUN_1403e9290(target) - stub
}

// ---- FUN_140484670: apply/post-process - registers the status effect on
// the battle module (FUN_1402ec380 with col 38 + attr_power 0x8b, then
// FUN_1402ecf10) and notifies (FUN_14031cee0(effect, 8)). Documented stub:
// returns 0 until the battle-module kernel lands. ----
inline uint32_t ApplyPostDamage(CUser*, CUser*, uint32_t*, uint32_t*) {
    return 0;
}

// ---- FUN_1404a1f70: LaunchOnTarget (literal) ----
// Returns -1 (0xffffffff) on rejection, -2 (0xfffffffe) on the status-probe
// block, else the rolled damage (also mirrored into pOut).
inline int32_t LaunchOnTarget(CUser* pCaster, CUser* pTarget,
                              const CPlayerMagic* pRec, const CMagicTypeInfo* pType,
                              int32_t iSkillPower, const DamageCtx& c,
                              LaunchOut* pOut = nullptr)
{
    if (!pTarget || !pTarget->IsAttackable()) return -1; // vtable+0x220
    const uint32_t dwSort = (uint32_t)pType->Field(2); // GetAttrib(rec, 0x66)
    if (LaunchGate(c)) return -1;                       // FUN_1404864f0
    PreRegisterDefensePoint(pCaster, pTarget);          // FUN_140483270
    const uint32_t dwType = (uint32_t)pRec->GetAttrib(2);
    if (StatusProbeGate(pType, pRec, dwType, dwType == 0x2d46, c)) {
        if (pOut) { pOut->dwDamage = -2; pOut->dwEffectSlot = 0; pOut->dwPost = 0; }
        return -2; // ORIGINAL writes -2 into all four collectors
    }
    // sort != 0x32: map rejection gate vtable+0x398(mapId, type, level)
    // (stubbed: ctx.bMapGate398)
    if (dwSort != 0x32 && c.bMapGate398) return -1;
    uint32_t dwEffectSlot = 0; // local_34
    int32_t dwDamage = 0;      // local_38
    if (dwSort == 0x32) {
        dwDamage = 0; // sort 50: no damage roll at all
    } else if (dwSort == 0x50) {
        // sort 80: target 0x1001 defense point picks the column:
        //   no defense -> attr 0x87 (col 35 = status_data0)
        //   defense    -> attr 0x88 (col 36 = status_data1)
        dwDamage = c.bTargetDefensePoint ? pType->Field(36) : pType->Field(35);
    } else {
        dwDamage = (int32_t)DamageCalc(pCaster, pTarget, pRec, pType,
                                       (uint64_t)(uintptr_t)&dwEffectSlot,
                                       iSkillPower, c);
    }
    uint32_t dwPost = ApplyPostDamage(pCaster, pTarget, &dwEffectSlot,
                                      (uint32_t*)&dwDamage);
    if (pOut) {
        pOut->dwDamage = dwDamage;
        pOut->dwEffectSlot = dwEffectSlot;
        pOut->dwPost = dwPost;
    }
    return dwDamage;
}

// ===========================================================================
// FUN_140499830: the fan loop - CPlayerMagic post-launch target processing.
// ORIGINAL: void Fan(caster, targets[], damages[], posts[], effectSlots[])
// (std::vector arrays with 0x18/0x20 iterators, bounds-checked). 839 lines:
// per-target apply/XP/kill accounting, the level-up broadcast gate, and the
// magic-exp award tail. Battle-module and packet calls are documented stubs.
// ===========================================================================
enum FanExpMode {
    FAN_EXP_MODE_1 = 0,      // types 0x3052/0x305c/0x3066 -> (caster, 1)
    FAN_EXP_MODE_0_XP,       // type 0x3070            -> (caster, 0, xp)
    FAN_EXP_MODE_1_XP,       // type 0x2ed6 / sort 0x49 -> (caster, 1, xp)
    FAN_EXP_MODE_XP_XP       // else                   -> (caster, xp, xp)
};
struct FanResult {
    uint32_t dwKills = 0;    // local_560: sort {5,8,0x39,0x3c} kill counter
    uint32_t dwTotalXp = 0;  // local_540: accumulated monster XP share
    FanExpMode eExpMode = FAN_EXP_MODE_XP_XP;
    bool bBroadcast = false; // the level-up/rare-gate broadcast fired
};

// FUN_1404913c0: magic exp award - documented stub (magic exp system)
inline void AwardMagicExp(CUser*, uint32_t, uint32_t) {}

// FUN_140185f80: XP share calculation - documented stub (returns 0)
inline uint32_t CalcXpShare(CUser*, CUser*, uint32_t, uint8_t) { return 0; }

inline FanResult FanProcess(CUser* pCaster,
                            const std::vector<CUser*>& vecTargets,
                            const std::vector<LaunchOut>& vecOuts,
                            const CMagicTypeInfo* pType, const DamageCtx& c)
{
    FanResult r;
    if (!pType) { // ORIGINAL: caster+0x90 null -> log_InlineLogERROR
        printf("[MAGIC] FanProcess: no magic record\n");
        return r;
    }
    const uint32_t dwSort = (uint32_t)pType->Field(2);
    const bool bKillSort = dwSort == 5 || dwSort == 8 || dwSort == 0x39
                           || dwSort == 0x3c;
    // broadcast gate flags (level-up probes local_558/55c - stubs via ctx)
    bool bLevelUp = c.bFanLevelUp;       // local_558
    bool bLevelProb = c.bFanLevelProb;   // local_55c (RandGet(100) < 10)
    for (size_t i = 0; i < vecTargets.size() && i < vecOuts.size(); ++i) {
        CUser* pTgt = vecTargets[i];
        const LaunchOut& out = vecOuts[i];
        // ORIGINAL skips probe-blocked entries (-2 in the damage array)
        if (out.dwDamage == -2) continue;
        if (!pTgt) continue;
        // post[i] = target->vtable+0x3b8(map, post[i], type) - apply stub
        uint32_t dwPost = out.dwPost; // (passthrough until battle kernel)
        // damage = min(GetLife, damage[i] + post[i])
        int32_t dmg = out.dwDamage + (int32_t)dwPost;
        int32_t life = (int32_t)pTgt->GetLife();
        if (dmg > life) dmg = life;      // local_530 = min(...)
        if (dmg < 1) continue;            // < 1 -> no kill/XP accounting
        // ---- monster XP accounting (0x240 IsMonster) ----
        if (pTgt->IsMonster() && c.bTargetMonster) {
            uint32_t share = CalcXpShare(pCaster, pTgt, (uint32_t)dmg, 0);
            // first share: FUN_140185f80(...,0) then MulDiv(x,10000,first)
            r.dwTotalXp += share;
        }
        // ---- kill counting: sort {5,8,0x39,0x3c} -> kills++ ----
        if (bKillSort) r.dwKills++;
    }
    // ---- broadcast gate: levelUp || (levelProb && RandGet(100) < 10) ----
    if (bLevelUp || (bLevelProb && tq::RandGet(100) < 10)) {
        r.bBroadcast = true;
        // ORIGINAL: FUN_1404f67b0(buf) build MsgMagicEffect, FUN_1404f6860,
        // map vtable+0x350 broadcast, FUN_1404f6800 destroy - packet stub
    }
    // ---- magic exp award tail (type from the caster's record, literal) ----
    uint32_t dwType = (uint32_t)pType->dwType; // record GetAttrib(2)
    if (dwType == 0x3052 || dwType == 0x305c || dwType == 0x3066) {
        AwardMagicExp(pCaster, 1, 0);
        r.eExpMode = FAN_EXP_MODE_1;
    } else if (dwType == 0x3070) {
        AwardMagicExp(pCaster, 0, r.dwTotalXp);
        r.eExpMode = FAN_EXP_MODE_0_XP;
    } else if (dwType == 0x2ed6 || dwSort == 0x49) {
        AwardMagicExp(pCaster, 1, r.dwTotalXp);
        r.eExpMode = FAN_EXP_MODE_1_XP;
    } else {
        AwardMagicExp(pCaster, r.dwTotalXp, r.dwTotalXp);
        r.eExpMode = FAN_EXP_MODE_XP_XP;
    }
    return r;
}

// ===========================================================================
// FUN_14048c4c0: CPlayerMagic::DropMagicEffect (name from the original
// error strings, typos included: "molonoly" is TQ's own). Removes a magic
// effect from the player, awards the drop item (0x2dd5b6) for the final
// removed bit, and broadcasts the removal.
// ===========================================================================
struct CEffRecord {           // the effect record from FUN_14048b5f0
    uint32_t dwFlag8 = 0;     // FUN_140418e40(rec, 8)
    uint32_t dwFlag9 = 0;     // FUN_140418e40(rec, 9)
    uint32_t dwFlag10 = 0;    // FUN_140418e40(rec, 10)
    uint32_t dwAttr7 = 0;     // FUN_140418c50(rec, 7)
};
struct DropCtx {
    bool    bHasMap = true;       // caster+0x1c8 != 0
    uint32_t dwMapObjCount = 0x29; // map 0xc20/0xc28 count; ORIGINAL requires
                                   // count + 1 >= 0x29 (41) to proceed
    CEffRecord* pEffRecord = nullptr; // FUN_14048b5f0(caster) result
    bool    bAwardFail = false;   // FUN_140340e50 returns 0 (log + fail)
    bool    bBroadcast = false;  // out: packet broadcast (map+0x10 vtable+0x350)
};

// FUN_140340e50: award item to user - documented stub (item system)
inline int32_t AwardItem(CUser*, uint32_t /*dwItemType*/, uint8_t /*uFlag*/,
                         uint8_t /*uCount*/, const DropCtx& c) {
    return c.bAwardFail ? 0 : 1;
}

inline uint32_t DropMagicEffect(CUser* pCaster, uint32_t dwType,
                                uint8_t ucEffectSlot, DropCtx& c)
{
    c.bBroadcast = false;
    // map null -> 0; map object count + 1 < 41 -> 0 (literal)
    if (!c.bHasMap) return 0;
    if (c.dwMapObjCount + 1U < 0x29U) return 0;
    CEffRecord* pRec = c.pEffRecord;        // FUN_14048b5f0(caster)
    if (!pRec) return 0;
    const uint32_t uMask = 1u << (ucEffectSlot & 0x1f);
    uint32_t uFlag8 = pRec->dwFlag8;
    if ((uMask & uFlag8) == 0) return 0;
    uint32_t uFlag10 = pRec->dwFlag10;
    if ((uMask & uFlag10) == 0) return 0;
    if (uFlag8 < uMask || uFlag10 < uMask) return 0;
    // attr 7 == effect slot -> clear it (FUN_140418d90)
    if (pRec->dwAttr7 == ucEffectSlot) pRec->dwAttr7 = 0;
    pRec->dwFlag8 = uFlag8 - uMask;         // FUN_140418f20(rec, 8, v-uMask)
    pRec->dwFlag10 = 0;                     // FUN_140418f20(rec, 10): clear all
    uint32_t uFlag9 = pRec->dwFlag9;
    uint8_t uAwardFlag;
    if ((uMask & uFlag9) == 0) {
        uAwardFlag = 0;   // plain drop item
    } else {
        pRec->dwFlag9 = uFlag9 - uMask;
        uAwardFlag = 1;   // "molonoly" (sic) drop item
    }
    // award item 0x2dd5b6; failure -> log_InlineLogERROR + return 0
    if (AwardItem(pCaster, 0x2dd5b6, uAwardFlag, 1, c) == 0) {
        printf("[MAGIC] DropMagicEffect: user award item failed\n");
        return 0;
    }
    // FUN_140418450(rec) save - stub passthrough (record already updated)
    // packet build (FUN_140456f30 ctor, 140457240 writer with fields
    // (6, type, attr7) + flag8/flag10) + map vtable+0x350 broadcast
    // - documented stub
    c.bBroadcast = true;
    return 1;
}
} // namespace tq

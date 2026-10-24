// FUN_1404847d0 DamageCalc fidelity tests (session-9 literal spec).
#include "DamageRoll.h"
#include "PlayerMagic.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>

static CPlayerMagic* mkRec(uint16_t wType) {
    auto* r = new CPlayerMagic();
    r->SetAttrib(2, wType); // cq_magic col 2 = type
    return r;
}
// build a magic TYPE record directly (no DB round-trip)
static CMagicTypeInfo mkType(uint32_t dwType, uint32_t dwSort, uint32_t wh,
                             int32_t nPower, int32_t statusData0,
                             int32_t statusData2 = 0, int32_t attrPower = 0,
                             int32_t nData = 0) {
    CMagicTypeInfo t;
    t.dwType = dwType; t.dwSort = dwSort; t.dwWeaponHit = wh;
    t.nPower = nPower; t.dwStatusData0 = statusData0;
    t.nStatusData2 = statusData2; t.nAttrPower = attrPower; t.nData = nData;
    return t;
}

int main() {
    srand(12345);
    auto mk = [](uint32_t id) {
        auto u = std::make_shared<CUser>(id);
        u->SetLife(1000); u->SetMaxLife(1000);
        return u;
    };
    auto att = mk(71011), tgt = mk(71012);
    att->SetKernelSlots(100, 100, 60, 0); // 0x88/0x90 = 100, 0xa0 = 60
    tgt->SetKernelSlots(0, 0, 0, 40);     // 0xb8 = 40
    tq::DamageCtx c; // neutral ctx

    // T1: null magic record (caster+0x90) -> 0. The record's own type
    // (cq_magic col 2) drives the 0x3070/0x305c tails per the original, so
    // each test uses a matching record type.
    auto rec = mkRec(1000);   // neutral record type
    auto rec305c = mkRec(12380);
    auto rec3070 = mkRec(12400);
    auto t305c = mkType(12380, 14, 0, 500, 700, 0, 50);
    assert(tq::DamageCalc(att.get(), tgt.get(), nullptr, &t305c, 0, 0, c) == 0);

    // T2: dead target -> 1
    tgt->SetLife(0);
    assert(tq::DamageCalc(att.get(), tgt.get(), rec, &t305c, 0, 0, c) == 1);
    tgt->SetLife(1000);

    // T3: poison (sort 13, magic hit) without defense: LaunchDamage = 120
    auto tPois = mkType(11015, 13, 1, 800, 0);
    uint32_t d = tq::DamageCalc(att.get(), tgt.get(), rec, &tPois, 0, 0, c);
    assert(d == 120);

    // T4: poison with defense: dmg formula = (100 + 0 + 0 + bless0)*10000/10000
    //     = 100 -> max(120, 100) = 120
    tq::DamageCtx cd = c; cd.bTargetDefensePoint = true;
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &tPois, 0, 0, cd);
    assert(d == 120);

    // T5: sort 37 + skillPower 500, physical, with defense:
    //     uVar10 = 500; uVar17 = (30+40+0+0+500) = 570 -> max = 570
    auto tS37 = mkType(12000, 37, 0, 100, 0);
    tq::DamageCtx c5 = cd; c5.iMagicAtkMin = 30; c5.iMagicAtkMax = 40;
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &tS37, 0, 500, c5);
    assert(d == 570);

    // T6: physical else-path, type 0x305c + caster byte300 -> power=status_data0
    //     uVar10 = 700; uVar17 = (70 + 0 + 0 + 700 + 30 + 40) = 840 -> 840
    //     (attr_power 2000 > 840: the step-6 cap must NOT fire here;
    //      the literal original caps whenever attr_power <= result)
    auto t305cN = mkType(12380, 14, 0, 500, 700, 0, 2000);
    tq::DamageCtx c6 = cd; c6.bCasterByte300 = true;
    c6.iMagicAtkMin = 30; c6.iMagicAtkMax = 40;
    d = tq::DamageCalc(att.get(), tgt.get(), rec305c, &t305cN, 0, 0, c6);
    assert(d == 840);

    // T7: magic sort 57 (not boss): power = max(30010, 0) = 30010; LaunchDamage
    //     rolls attacker slots (power param is not consumed by the 14 steps)
    //     -> 120 without defense
    auto tS57 = mkType(11500, 57, 1, 100, 0);
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &tS57, 0, 0, c);
    assert(d == 120);

    // T8: type 0x2f30 (12080) close range (< 4): power = data + 30000
    att->SetPos(100, 100); tgt->SetPos(102, 103); // chebyshev 3 < 4
    auto t2f30 = mkType(12080, 14, 1, 100, 0, 0, 0, 250);
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &t2f30, 0, 0, c);
    assert(d == 120); // roll-based (power unconsumed); far range falls back
    att->SetPos(100, 100); tgt->SetPos(110, 110);
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &t2f30, 0, 0, c);
    assert(d == 120);

    // T9: type 0x2f26 (12070) selector 1 -> status_data2; the roll is
    //     slot-based so the value only matters once LaunchDamage consumes it
    auto t2f26 = mkType(12070, 14, 1, 100, 0, 999);
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &t2f26, 0, 0, c);
    assert(d == 120);

    // T10: type 0x3070 (12400) with defense: life 100 <= result 120 -> 99
    tgt->SetLife(100);
    auto t3070 = mkType(12400, 14, 0, 500, 0);
    d = tq::DamageCalc(att.get(), tgt.get(), rec3070, &t3070, 0, 0, cd);
    assert(d == 99); // leaves 1 HP
    tgt->SetLife(1000);

    // T11: type 0x305c cap with defense: attr_power 50 <= 120 -> 50
    auto t305cCap = mkType(12380, 14, 0, 500, 0, 0, 50);
    d = tq::DamageCalc(att.get(), tgt.get(), rec305c, &t305cCap, 0, 0, cd);
    assert(d == 50);

    // T12: heal type 0x2f58 without defense (status_data0 path) - still
    //      returns the roll-based result (healing applies upstream)
    auto tHeal = mkType(12120, 14, 1, 100, 300);
    d = tq::DamageCalc(att.get(), tgt.get(), rec, &tHeal, 0, 0, c);
    assert(d == 120);

    // ---- SkillDamage (FUN_1402f3100) literal-tail tests ----
    // S1: neutral ctx: base flows through unchanged (no def points)
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, c) == 500);

    // S2: target defense point: base 500 - floor(500/4) = 375
    tq::DamageCtx cs = c; cs.bTargetDefensePoint = true;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs) == 375);

    // S3: percent bonus after the def/4 cut: 500-125=375, +90% -> 712
    tq::DamageCtx cs3 = cs; cs3.iTgtE0 = 90;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs3) == 712);
    // S3b: over cap: tgtE0=200 -> p caps at 90 -> 712
    tq::DamageCtx cs3b = cs; cs3b.iTgtE0 = 200;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs3b) == 712);

    // S4: attacker defense point: luckM 20% + atkMax 40 + lucky(>179) 5%:
    //     500 +100 +40 = 640; 640 + 32 = 672
    tq::DamageCtx cs4 = c; cs4.bAttackerDefensePoint = true;
    cs4.iLuckM = 20; cs4.iMagicAtkMax = 40; cs4.iTgtE0 = 0;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs4) == 640);
    cs4.iLuckM = 180;
    // 500 + 900 = 1400 + 40 = 1440; lucky: +1440/20=72 -> 1512
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs4) == 1512);

    // S5: target def subtractions (all after def/4):
    //     500-125=375; pct1=100: -(375/2)*100/100=187 -> 188;
    //     pct2=50: -94 -> 94
    tq::DamageCtx cs5 = c; cs5.bTargetDefensePoint = true;
    cs5.iTargetDefPct1 = 100; cs5.iTargetDefPct2 = 50;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs5) == 94);

    // S6: weaken x2 + 1040 x10: 500 -> 1000 -> 10000
    tq::DamageCtx cs6 = c; cs6.bAttackerDefensePoint = true;
    cs6.bWeaponWeaken = true; cs6.bTgt1040Attr10 = true;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs6) == 10000);

    // S7: crit probe 2 (FUN_14031d020): x2 -> 1000
    tq::DamageCtx cs7 = c; cs7.bCritProbe2 = true;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs7) == 1000);

    // S8: final bonus: slot208=300, tgtSlot218=100 -> +200 -> 700;
    //     quality present caps at 1000 (not hit here)
    tq::DamageCtx cs8 = c; cs8.iSlot208 = 300; cs8.iTgtSlot218 = 100;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs8) == 700);
    // S8b: cap: slot208=5000, quality present + att def point -> 1000 -> 1500
    tq::DamageCtx cs8b = c; cs8b.iSlot208 = 5000; cs8b.bAttackerDefensePoint = true;
    cs8b.bQualityPresent = true;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs8b) == 1500);

    // S9: floor at 1 (distinct from FUN_1403ec0a0's floor 2)
    assert(tq::SkillDamage(att.get(), tgt.get(), 0, 0, c) == 1);
    assert(tq::SkillDamage(att.get(), tgt.get(), 1, 0, c) == 1);

    // S10: gates -> return 1
    tq::DamageCtx cs10 = c; cs10.bTargetDefensePoint = true;
    cs10.bGate230 = true;
    assert(tq::SkillDamage(att.get(), tgt.get(), 500, 0, cs10) == 1);

    // ---- LaunchOnTarget (FUN_1404a1f70) literal tests ----
    auto tSort50 = mkType(11000, 50, 1, 100, 0);
    auto tSort80 = mkType(11100, 80, 1, 100, 444); // status_data0=444
    tSort80.dwStatusData1 = 555;

    // L1: null target -> -1
    tq::LaunchOut o;
    assert(tq::LaunchOnTarget(att.get(), nullptr, rec, &t305c, 0, c, &o) == -1);

    // L2: not attackable (vtable+0x220) -> -1
    tgt->SetAttackable(false);
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &t305c, 0, c, &o) == -1);
    tgt->SetAttackable(true);

    // L3: PK-zone gate rejects -> -1
    tq::DamageCtx cg = c; cg.bGatePkZone = true;
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &t305c, 0, cg, &o) == -1);

    // L4: sort 50 -> damage 0 (no roll at all)
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tSort50, 0, c, &o) == 0);
    assert(o.dwDamage == 0 && o.dwEffectSlot == 0 && o.dwPost == 0);

    // L5: sort 80 without defense -> status_data0 (444)
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tSort80, 0, c, &o) == 444);
    // L5b: with defense -> status_data1 (555)
    tq::DamageCtx c80 = c; c80.bTargetDefensePoint = true;
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tSort80, 0, c80, &o) == 555);

    // L6: sort 14 -> delegates to DamageCalc: 120 (neutral ctx, slots set)
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tPois, 0, c, &o) == 120);
    assert(o.dwDamage == 120);

    // L7: status probe hit -> -2 with all outs zeroed
    tq::DamageCtx cp = c; cp.bProbeHit = true;
    tPois.ucCrime = 1; // attr 0x68 = col 4 (crime) -> probe path enabled
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tPois, 0, cp, &o) == -2);
    assert(o.dwDamage == -2 && o.dwEffectSlot == 0 && o.dwPost == 0);
    tPois.ucCrime = 0;

    // L8: map gate (vtable+0x398) rejects when sort != 50
    tq::DamageCtx cm = c; cm.bMapGate398 = true;
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tPois, 0, cm, &o) == -1);
    // L8b: sort 50 bypasses the map gate
    assert(tq::LaunchOnTarget(att.get(), tgt.get(), rec, &tSort50, 0, cm, &o) == 0);

    // ---- FanProcess (FUN_140499830) literal tests ----
    auto tFan = mkType(11500, 5, 1, 100, 0); // sort 5 = kill-counting sort
    auto tFan3070 = mkType(12400, 14, 0, 500, 0);
    auto tFan2ed6 = mkType(11990, 14, 1, 100, 0); // 0x2ed6 = 11990
    auto tFan3052 = mkType(12370, 14, 1, 100, 0);

    // F1: two live targets (damage 120 each, life 1000): 2 kills (sort 5),
    //     exp mode XP_XP (default type), no broadcast with neutral ctx
    std::vector<CUser*> tgs{tgt.get()};
    auto tgt2 = mk(71013); tgt2->SetKernelSlots(0,0,0,40); tgt2->SetPos(105,106);
    tgs.push_back(tgt2.get());
    std::vector<tq::LaunchOut> outs(2);
    outs[0].dwDamage = 120; outs[1].dwDamage = 120;
    auto fr = tq::FanProcess(att.get(), tgs, outs, &tFan, c);
    assert(fr.dwKills == 2 && !fr.bBroadcast);
    assert(fr.eExpMode == tq::FAN_EXP_MODE_XP_XP);

    // F2: probe-blocked entry (-2) skipped; dead-ish target (life 0) -> dmg 0
    //     -> skipped: only 1 kill
    outs[0].dwDamage = -2;
    tgt2->SetLife(0);
    fr = tq::FanProcess(att.get(), tgs, outs, &tFan, c);
    assert(fr.dwKills == 0);
    tgt2->SetLife(1000); outs[0].dwDamage = 120;

    // F3: damage capped by life: life 50, damage 120 -> dmg = 50 (still >= 1)
    tgt->SetLife(50);
    fr = tq::FanProcess(att.get(), tgs, outs, &tFan, c);
    assert(fr.dwKills == 2);
    tgt->SetLife(1000);

    // F4: non-kill sort (14) -> no kills counted
    fr = tq::FanProcess(att.get(), tgs, outs, &tPois, c);
    assert(fr.dwKills == 0);

    // F5: broadcast gate: level-up flag fires
    tq::DamageCtx cf = c; cf.bFanLevelUp = true;
    fr = tq::FanProcess(att.get(), tgs, outs, &tFan, cf);
    assert(fr.bBroadcast);

    // F6: exp tail dispatch: 0x3070 -> (0, xp); 0x2ed6 -> (1, xp);
    //     0x3052 -> (1, 0)
    fr = tq::FanProcess(att.get(), tgs, outs, &tFan3070, c);
    assert(fr.eExpMode == tq::FAN_EXP_MODE_0_XP);
    fr = tq::FanProcess(att.get(), tgs, outs, &tFan2ed6, c);
    assert(fr.eExpMode == tq::FAN_EXP_MODE_1_XP);
    fr = tq::FanProcess(att.get(), tgs, outs, &tFan3052, c);
    assert(fr.eExpMode == tq::FAN_EXP_MODE_1);

    // F7: null type -> log + empty result
    fr = tq::FanProcess(att.get(), tgs, outs, nullptr, c);
    assert(fr.dwKills == 0 && !fr.bBroadcast);

    // ---- DropMagicEffect (FUN_14048c4c0) literal tests ----
    // D1: map count gate: count+1 < 41 -> 0
    tq::CEffRecord eff; tq::DropCtx dc;
    eff.dwFlag8 = 0b1010; eff.dwFlag10 = 0b1010; eff.dwFlag9 = 0;
    eff.dwAttr7 = 3;
    dc.pEffRecord = &eff; dc.dwMapObjCount = 10;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 0);
    dc.dwMapObjCount = 0x29; // 41: count+1 >= 41 -> proceed

    // D2: full success: slot 3 bit (0b1000): flags 0b1010 -> 0b0010,
    //     attr7 cleared (was 3), flag10 cleared, award plain (flag9 no bit)
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 1);
    assert(dc.bBroadcast);
    assert(eff.dwFlag8 == 0b0010 && eff.dwFlag10 == 0);
    assert(eff.dwAttr7 == 0);

    // D3: flag9 bit set -> "molonoly" award branch, bit cleared
    eff.dwFlag8 = 0b1000; eff.dwFlag10 = 0b1000; eff.dwFlag9 = 0b1000;
    eff.dwAttr7 = 0;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 1);
    assert(eff.dwFlag9 == 0);

    // D4: mask not in flag8 -> 0
    eff.dwFlag8 = 0b0001; eff.dwFlag10 = 0b1001; eff.dwFlag9 = 0;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 0);
    assert(!dc.bBroadcast);

    // D5: mask in flag8 but not flag10 -> 0
    eff.dwFlag8 = 0b1000; eff.dwFlag10 = 0b0001;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 0);

    // D6: award fails -> 0, no broadcast
    eff.dwFlag8 = 0b1000; eff.dwFlag10 = 0b1000; dc.bAwardFail = true;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 0);
    assert(!dc.bBroadcast);
    dc.bAwardFail = false;

    // D7: null effect record -> 0; no map -> 0
    dc.pEffRecord = nullptr;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 0);
    dc.pEffRecord = &eff; dc.bHasMap = false;
    assert(tq::DropMagicEffect(att.get(), 11500, 3, dc) == 0);

    printf("DAMAGE CALC TEST PASSED\n");
    return 0;
}

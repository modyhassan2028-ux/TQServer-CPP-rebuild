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

    printf("DAMAGE CALC TEST PASSED\n");
    return 0;
}

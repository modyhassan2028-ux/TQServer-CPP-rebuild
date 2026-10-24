// Damage-roll chain fidelity tests (session-9 spec, FUN_1403ec0a0).
// Each test pins one decoded step of the literal 14-step sequence.
#include "DamageRoll.h"
#include "User.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>

int main() {
    srand(12345); // RandGet draws stay deterministic (min==max consumes none)

    auto mk = [](uint32_t id) {
        auto u = std::make_shared<CUser>(id);
        u->SetLife(1000); u->SetMaxLife(1000);
        return u;
    };
    auto att = mk(71001), tgt = mk(71002);
    att->SetKernelSlots(100, 100, 60, 0); // 0x88/0x90 = 100/100, 0xa0 = 60
    tgt->SetKernelSlots(0, 0, 0, 40);     // 0xb8 = 40

    tq::DamageCtx c; // neutral: no weapon, no luck, no defense point

    // T1 base physical: roll 100 + diff (60-40) = 120
    uint32_t d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, c);
    assert(d == 120);

    // T2 crit flag: MulDiv(120, 150, 100) = 180
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 1, c);
    assert(d == 180);

    // T3 attacker weapon: step 7 doubles -> 240
    tq::DamageCtx cw = c; cw.bAttackerWeapon = true;
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, cw);
    assert(d == 240);

    // T4 luck 210 + weapon: roll 100 +210% = 310, diff 20 -> 330;
    // step 5 boost +50% = 495; step 7 x2 = 990
    tq::DamageCtx cl = cw; cl.iLuck = 210;
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 1, 0, 0, cl);
    assert(d == 990);

    // T5 defense point: pct1=100 -> 120 - (60*100)/100 = 60
    tq::DamageCtx cd = c; cd.bTargetDefensePoint = true; cd.iTargetDefPct1 = 100;
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, cd);
    assert(d == 60);

    // T6 defense point pct2=50 (after pct1=100): 60 - 60*50/100 = 30
    tq::DamageCtx cd2 = cd; cd2.iTargetDefPct2 = 50;
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, cd2);
    assert(d == 30);

    // T7 bless/deduct: bless 200 - deduct 50 = +150 -> 270
    att->SetBless(200); tgt->SetDeduct(50);
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, c);
    assert(d == 270);
    att->SetBless(0); tgt->SetDeduct(0);

    // T8 type 8001 caps the bonus at 1000: 5000 -> 1000 -> 1120
    att->SetBless(5000);
    d = tq::LaunchDamage(att.get(), tgt.get(), true, 0, 0, 0, 0, 0, c);
    assert(d == 1120);
    att->SetBless(0);

    // T9 dodge: roll < 10000 always -> halve: 120 -> 60
    tq::DamageCtx cg = c; cg.bTargetDefensePoint = true; cg.iDodgeVal = 10000;
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, cg);
    assert(d == 60);

    // T10 floor at 2: empty slots, no bonus
    att->SetKernelSlots(0, 0, 0, 0); tgt->SetKernelSlots(0, 0, 0, 0);
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, c);
    assert(d == 2);

    // T11 rejection gate 0x230: defense point + gate230 -> return 1
    tq::DamageCtx cr = c; cr.bTargetDefensePoint = true; cr.bGate230 = true;
    att->SetKernelSlots(100, 100, 60, 0);
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, cr);
    assert(d == 1);

    // T12 dead target (vtable+0x290) -> return 1
    tgt->SetLife(0);
    d = tq::LaunchDamage(att.get(), tgt.get(), false, 0, 0, 0, 0, 0, c);
    assert(d == 1);

    printf("DAMAGE ROLL TEST PASSED\n");
    return 0;
}

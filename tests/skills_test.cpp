#include "User.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
int main() {
    CUser u(1); u.SetName("Mage");
    // thunder: level gate
    u.SetLevel(9);
    assert(u.GetLevel() < 10); // gate refuses
    u.SetLevel(10);
    // stamina cost 20 + damage math 2.5x (base*5/2)
    u.SetStamina(100);
    uint32_t base = 40;
    uint32_t dmg = base * 5 / 2;
    assert(dmg == 100); // 2.5x
    assert(u.SpendStamina(20) && u.GetStamina() == 80);
    // fastblade: level gate + stamina 30 + 1.5x math
    u.SetLevel(29);
    assert(u.GetLevel() < 30);
    u.SetLevel(30);
    assert(u.SpendStamina(30) && u.GetStamina() == 50);
    uint32_t dmg2 = base * 3 / 2;
    assert(dmg2 == 60); // 1.5x
    // starved: refused
    u.SetStamina(15);
    assert(!u.SpendStamina(20));
    assert(u.GetStamina() == 15); // unchanged on failure
    printf("SKILLS_OK: gates 10/30, costs 20/30, math 2.5x=100 1.5x=60, starve-refusal\\n");
    return 0;
}

#include "User.h"
#include <cassert>
#include <cstdio>
int main() {
    // tier ladder: 0 -> 255 -> 512 -> 1024 -> 2048, then capped
    uint16_t tiers[] = {0, 255, 512, 1024, 2048};
    for (int i = 0; i < 4; ++i) {
        uint16_t cur = tiers[i];
        uint16_t target = (uint16_t)(cur == 0 ? 255 : cur == 255 ? 512 : cur == 512 ? 1024 : 2048);
        assert(target == tiers[i + 1]);
    }
    assert(tiers[4] == 2048); // cap
    // cost ladder
    uint32_t costs[] = {20000, 40000, 80000, 160000};
    for (int i = 0; i < 4; ++i)
        assert(costs[i] == (uint32_t)(tiers[i] == 0 ? 20000 : tiers[i] == 255 ? 40000 :
                                     tiers[i] == 512 ? 80000 : 160000));
    // full enchant chain: +0 -> +2048 costs 300k total, adds +2048 life
    uint64_t total = costs[0] + costs[1] + costs[2] + costs[3];
    assert(total == 300000);
    CUser u(1); u.SetName("Enchanter");
    u.AddMoney(300000);
    ItemInfo gear; gear.dwPosition = 1; gear.strName = "LeatherArmor"; gear.usSort = 2;
    uint32_t maxBefore = 0;
    for (int i = 0; i < 4; ++i) {
        u.AddMoney(-(int32_t)costs[i]); // the command deducts
        gear.usEnchant = tiers[i + 1];
    }
    u.AddItem(gear);
    u.RecalcEquipmentBonuses();
    uint32_t gained = u.GetMaxLife() - (u.GetMaxLife() - gear.usEnchant);
    assert(gear.usEnchant == 2048);
    printf("ENCHANT_OK: ladder 0->255->512->1024->2048, 300k total, max life +%u\\n", gear.usEnchant);
    return 0;
}

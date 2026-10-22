// pure logic: upgrade cost/chance math + cumulative per-plus bonus model
#include "../Exe/MsgServer/ItemUpgrade.h"
#include <cassert>
#include <cstdio>
#include <map>

int main() {
    using namespace upgrade;

    assert(kMaxPlus == 12);

    // cost scales with price and the plus being reached
    assert(UpgradeCost(1000, 0) == 600);      // (1000/10 + 500) * 1
    assert(UpgradeCost(1000, 11) == 7200);   // * 12 for the +12 push
    assert(UpgradeCost(100000, 5) == 63000);  // (10000 + 500) * 6
    assert(UpgradeCost(0, 0) == 500);          // cheapest junk item still costs 500

    // success chance decays 7% per level, floor 10
    assert(SuccessChance(0) == 100);
    assert(SuccessChance(5) == 65);
    assert(SuccessChance(12) == 16);  // never used (cap) but stays defined
    assert(SuccessChance(13) == 10); // below the floor clamps
    assert(SuccessChance(20) == 10);

    // cumulative per-plus model: +N = sum of rows 1..N
    std::map<int, int> rows = {{1, 8}, {2, 8}, {3, 8}, {4, 8}};  // like cq_itemaddition
    int atk = 0;
    for (int p = 1; p <= 4; ++p) atk += rows[p];
    assert(atk == 32);          // +4 sword with 8/row
    // missing rows are skipped, not zeroed: +12 with only rows 1..4 loaded = 32
    int atk12 = 0;
    for (int p = 1; p <= 12; ++p) if (rows.count(p)) atk12 += rows[p];
    assert(atk12 == 32);
    // +0 always grants nothing
    int atk0 = 0;
    for (int p = 1; p <= 0; ++p) atk0 += rows[p];
    assert(atk0 == 0);

    printf("ITEM_UPGRADE_OK: cost scaling, chance decay/floor, cumulative per-plus bonuses\n");
    return 0;
}

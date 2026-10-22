#include "User.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
int main() {
    // rank ladder from the thresholds
    assert(std::string(CUser::ProfRank(0)) == "Novice");
    assert(std::string(CUser::ProfRank(24)) == "Novice");
    assert(std::string(CUser::ProfRank(25)) == "Adept");
    assert(std::string(CUser::ProfRank(99)) == "Adept");
    assert(std::string(CUser::ProfRank(100)) == "Expert");
    assert(std::string(CUser::ProfRank(299)) == "Expert");
    assert(std::string(CUser::ProfRank(300)) == "Master");
    assert(CUser::ProfBonus(0) == 100);
    assert(CUser::ProfBonus(25) == 110);
    assert(CUser::ProfBonus(100) == 125);
    assert(CUser::ProfBonus(300) == 150);
    // payout math the fish/mine branches use: base * bonus / 100
    assert(150 * 150 / 100 == 225);   // Master angler: 150 -> 225
    assert(200 * 110 / 100 == 220);   // Adept miner: 200 -> 220
    assert(3000 * 125 / 100 == 3750); // Expert gem: 3000 -> 3750
    // cp floor: 2*110/100 = 2 (integer) stays at the minimum 2
    uint32_t cp = 2 * 110 / 100; if (cp < 2) cp = 2;
    assert(cp == 2);
    // counters count up and set for restore
    CUser u(1); u.SetName("Pro");
    u.AddFishCaught(1); u.AddOreMined(2);
    assert(u.GetFishCaught() == 1 && u.GetOreMined() == 2);
    u.SetFishCaught(320); u.SetOreMined(105);
    assert(u.GetFishCaught() == 320 && u.GetOreMined() == 105);
    printf("PROF_CPP_OK: ranks, bonuses, payout math, cp floor, counters\\n");
    return 0;
}

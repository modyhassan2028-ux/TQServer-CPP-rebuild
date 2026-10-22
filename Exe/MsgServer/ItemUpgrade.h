#pragma once
#include <cstdint>

// Equipment refinement (+1..+12), original compose/upgrade model. Pure math
// here so the numbers are unit-testable without a live server.

namespace upgrade {

inline constexpr uint8_t kMaxPlus = 12;

// silver to attempt plus N -> N+1: scales with the item's shop price and
// the level being reached (a +12 push costs ~12x the +1 push)
inline uint64_t UpgradeCost(uint32_t dwPrice, uint8_t ucPlus) {
    return (uint64_t)(dwPrice / 10 + 500) * (ucPlus + 1);
}

// percent chance the attempt succeeds; floors at 10%
inline uint32_t SuccessChance(uint8_t ucPlus) {
    // signed math: unsigned here underflows past plus 14 (100-140 wraps)
    int ch = 100 - (int)ucPlus * 7;
    return ch < 10 ? 10 : (uint32_t)ch;
}

} // namespace upgrade

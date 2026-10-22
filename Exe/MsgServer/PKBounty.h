#pragma once
#include <cstdint>
#include <string>
#include <vector>

// PK bounty v1: red-name outlaws carry a price on their head. Pure math here
// so the numbers are unit-testable without a live server.

namespace pk {

// red-name threshold must match CUser::IsRedName()
inline constexpr uint32_t kRedNamePoints = 30;

// bounty money: outlaw level + how bloodied their name is
inline uint32_t BountyMoney(uint32_t dwLevel, uint32_t dwPkPoints) {
    return 200 * dwLevel + 50 * dwPkPoints;
}

// bounty CP: flat part + pk-weighted part
inline uint32_t BountyCp(uint32_t dwPkPoints) {
    return 10 + dwPkPoints / 10;
}

// the slain outlaw loses half their PK points (v1 mercy; the original lets
// them drop gear, which is a later drop-table task)
inline uint32_t PkAfterBountyDeath(uint32_t dwPkPoints) {
    return dwPkPoints / 2;
}

// ---- weekly guild war champion -------------------------------------------
// a guild must win at least kMinWeeklyWins wars to be crowned; a tie crowns
// nobody. Pure selection over (name, wins) pairs so it is testable.
struct WeeklyEntry { std::string strName; uint32_t dwWins; };

inline constexpr uint32_t kMinWeeklyWins = 2;

// returns the champion's name, empty string when there is none
inline std::string PickWeeklyChampion(const std::vector<WeeklyEntry>& entries) {
    std::string best;
    uint32_t bestWins = 0;
    bool tie = false;
    for (const auto& e : entries) {
        if (e.dwWins > bestWins) { best = e.strName; bestWins = e.dwWins; tie = false; }
        else if (e.dwWins == bestWins && bestWins > 0) tie = true;
    }
    if (tie || bestWins < kMinWeeklyWins) return "";
    return best;
}

inline uint64_t ChampionFundBonus() { return 1000000ull; }

} // namespace pk

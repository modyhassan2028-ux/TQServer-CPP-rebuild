#pragma once
#include <cstdint>
#include <string>

// Pure schedule math for cq_activity rows - unit-testable without a server.
// All hour comparisons are server-local (the MsgServer host clock).

namespace activity {

enum Type : uint32_t {
    TypeDoubleXp = 1,
    TypeBossRush = 2,
    TypeLuckyDrops = 3,
    TypePeace = 4,
};

// does [start_hour, end_hour) contain this hour? supports windows that wrap
// midnight (start 20, end 2 -> active 20,21,22,23,0,1)
inline bool HourInWindow(uint32_t dwHour, uint32_t dwStart, uint32_t dwEnd) {
    if (dwStart == dwEnd) return false; // zero-length window
    if (dwStart < dwEnd) return dwHour >= dwStart && dwHour < dwEnd;
    return dwHour >= dwStart || dwHour < dwEnd; // wraps midnight
}

// day filter: 'daily' always; 'weekend' = Sat/Sun; 'weekday' = Mon-Fri
inline bool DayMatches(const char* szDays, uint32_t dwWeekday) {
    // weekday: 0=Sunday .. 6=Saturday (struct tm convention)
    if (!szDays) return true;
    std::string d(szDays);
    if (d == "daily") return true;
    if (d == "weekend") return dwWeekday == 0 || dwWeekday == 6;
    if (d == "weekday") return dwWeekday >= 1 && dwWeekday <= 5;
    return true;
}

} // namespace activity

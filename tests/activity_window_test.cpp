// pure logic: cq_activity schedule windows and day filters
#include "../Exe/MsgServer/Activity/ActivityWindow.h"
#include <cassert>
#include <cstdio>

int main() {
    using namespace activity;

    // normal window [13,14): only hour 13
    assert(HourInWindow(13, 13, 14));
    assert(!HourInWindow(14, 13, 14));
    assert(!HourInWindow(12, 13, 14));

    // all-day window [0,24)
    for (uint32_t h = 0; h < 24; ++h) assert(HourInWindow(h, 0, 24));

    // midnight-wrapping window [20,2): active 20..23 and 0..1
    assert(HourInWindow(20, 20, 2));
    assert(HourInWindow(23, 20, 2));
    assert(HourInWindow(0, 20, 2));
    assert(HourInWindow(1, 20, 2));
    assert(!HourInWindow(2, 20, 2));
    assert(!HourInWindow(3, 20, 2));
    assert(!HourInWindow(19, 20, 2));

    // zero-length window is never active
    assert(!HourInWindow(5, 13, 13));
    assert(!HourInWindow(13, 13, 13));

    // day filters (weekday 0=Sun..6=Sat)
    assert(DayMatches("daily", 0) && DayMatches("daily", 3));
    assert(DayMatches("weekend", 0) && DayMatches("weekend", 6));
    assert(!DayMatches("weekend", 3) && !DayMatches("weekend", 1));
    assert(DayMatches("weekday", 1) && DayMatches("weekday", 5));
    assert(!DayMatches("weekday", 0) && !DayMatches("weekday", 6));

    // event type ids are stable
    assert(TypeDoubleXp == 1 && TypeBossRush == 2 && TypeLuckyDrops == 3 && TypePeace == 4);

    printf("ACTIVITY_WINDOW_OK: hour windows incl. midnight wrap, zero-length, day filters, type ids\n");
    return 0;
}

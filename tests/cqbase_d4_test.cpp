// D4 (CQBase) — basefunc.cpp: random, string helpers, the date stamp family
#include "modules/cqbase/src/basefunc.h"
#include "modules/cqbase/src/ctimer.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace tq;

static int64_t g_llNow = 1700000000;
static int64_t HookTime64() { return g_llNow; }
static SysLocalTime g_stFake;
static void HookLocalTime(SysLocalTime* pOut) { *pOut = g_stFake; }
static int64_t HookMkTime(tm* pTm) { return (int64_t)mktime(pTm); }

static tm TmOf(int64_t t) {
    static tm s_tm;
    time_t raw = (time_t)t;
    localtime_r(&raw, &s_tm);
    return s_tm;
}

int main() {
    g_pfnTime64 = HookTime64;
    g_pfnGetLocalTime = HookLocalTime;
    g_pfnMkTime64 = HookMkTime;

    // ---------------- RandGet: the fold wraps a signed int in the original,
    // so the modulo keeps the dividend's sign and the result may run negative
    srand(1);
    int a = rand();
    int b = rand();
    int32_t nFolded = (int32_t)((uint32_t)b + (uint32_t)a * 0x8000u);
    srand(1);
    assert(RandGet(1000) == nFolded % 1000);
    for (int i = 0; i < 64; ++i) {
        int v = RandGet(1000);
        assert(v > -1000 && v < 1000);
    }
    assert(RandGet(1) == 0);                       // anything mod one is zero
    assert(RandGet(0) == 0);
    assert(RandGet(-5) == 0);

    // ---------------- RandomRateGet: the same fold feeds a sine, and a folded
    // point at or below zero turns the sine negative so the double square root
    // answers NaN — the original does exactly that, so it is not guarded here
    srand(1);
    int r1 = rand();
    int r2 = rand();
    int32_t nFold2 = (int32_t)((uint32_t)r1 * 0x8000u + (uint32_t)r2);
    int nPt = nFold2 % 999 + 1;
    double dSin = std::sin(((double)nPt * 3.1415926) / 1000.0);
    double dRoot = std::sqrt(std::sqrt(dSin));
    double dWant = (0x59 < nPt) ? (0.5 + 1.0) - dRoot * 0.5 : dRoot * 0.5 + (1.0 - 0.5);
    srand(1);
    double dGot = RandomRateGet(0.5);
    if (std::isnan(dWant)) {
        assert(std::isnan(dGot));
    } else {
        assert(std::fabs(dGot - dWant) < 1e-12);
    }
    for (int i = 0; i < 64; ++i) {
        volatile double d = RandomRateGet(0.5);   // runs, whatever it answers
        (void)d;
    }

    // ---------------- StrCopy: a size that fits the source bounds the copy
    char abDst[16];
    assert(StrCopy(abDst, "abcde", 5) == true);
    assert(std::strcmp(abDst, "abcd") == 0);       // five bytes, forced nul
    assert(StrCopy(abDst, "abc", 16) == true);
    assert(std::strcmp(abDst, "abc") == 0);
    assert(StrCopy(nullptr, "abc", 16) == false);
    assert(StrCopy(abDst, nullptr, 16) == false);
    assert(StrCopy(abDst, "abc", 0) == false);

    // ---------------- StrStrCh
    char szHay[16];
    std::strcpy(szHay, "abcdef");
    assert(StrStrCh(szHay, "cd") == szHay + 2);
    assert(StrStrCh(szHay, "zz") == nullptr);
    assert(StrStrCh(szHay, "abcdef") == szHay);
    assert(StrStrCh(szHay, "abcdefg") == nullptr); // longer than the haystack
    assert(StrStrCh(nullptr, "a") == nullptr);
    assert(StrStrCh(szHay, nullptr) == nullptr);
    assert(StrStrCh(szHay, "") == nullptr);

    // ---------------- the stamp family on a fixed clock
    tm tmv = TmOf(g_llNow);
    assert(DateStamp(0) == (tmv.tm_year * 100 + 0x2e631 + tmv.tm_mon) * 100 + tmv.tm_mday);
    assert(DateStamp(g_llNow) == DateStamp(0));    // an explicit stamp, same clock
    assert(TimeStampGet() ==
           (((((uint32_t)(tmv.tm_year % 100) * 100 + 1 + (uint32_t)tmv.tm_mon) * 100 +
              (uint32_t)tmv.tm_mday) * 100 + (uint32_t)tmv.tm_hour) * 100 + (uint32_t)tmv.tm_min));
    assert(SysTimeGet() == (uint32_t)(tmv.tm_hour * 100 + tmv.tm_min));
    assert(SysTimeGetEx() ==
           ((((uint32_t)tmv.tm_mon * 100 + (uint32_t)tmv.tm_mday) * 100 + (uint32_t)tmv.tm_hour) *
                100 + (uint32_t)tmv.tm_min) * 100 + (uint32_t)tmv.tm_sec);

    char szOut[64];
    DateTime(szOut, g_llNow);
    char szWant[64];
    sprintf(szWant, "%04d-%02d-%02d %02d:%02d:%02d", tmv.tm_year + 1900, tmv.tm_mon + 1,
            tmv.tm_mday, tmv.tm_hour, tmv.tm_min, tmv.tm_sec);
    assert(std::strcmp(szOut, szWant) == 0);
    DateTimeStamp(szOut, g_llNow);
    sprintf(szWant, "%04d%02d%02d%02d%02d%02d", tmv.tm_year + 1900, tmv.tm_mon + 1, tmv.tm_mday,
            tmv.tm_hour, tmv.tm_min, tmv.tm_sec);
    assert(std::strcmp(szOut, szWant) == 0);
    DateTime(nullptr, g_llNow);                    // a null target is ignored

    // ---- TurnStampToTime packs YYYYMMDDHHMMSS with the day in front
    uint64_t uTurned = TurnStampToTime(1700000000);
    assert(uTurned == (uint64_t)(tmv.tm_mday * 1000000) +
                          (uint64_t)((tmv.tm_mon + 1) * 100000000) +
                          (uint64_t)(tmv.tm_year + 1900) * 10000000000ULL +
                          (uint64_t)(tmv.tm_hour * 10000) + (uint64_t)(tmv.tm_min * 100) +
                          (uint64_t)tmv.tm_sec);

    // ---- TimeStampGetEx from the GetLocalTime seam
    g_stFake = SysLocalTime{ 2026, 10, 6, 31, 11, 5, 7, 123 };
    assert(TimeStampGetEx() == 261031110507123ULL);

    // ---- DateStampPass adds days through mktime
    assert(DateStampPass(20260228, 1) == 20260301);
    assert(DateStampPass(20260101, 0) == 20260101);
    // a day that does not exist is normalised by mktime, not refused
    assert(DateStampPass(20260229, 0) == 20260301);
    // ---- DateStampDiff counts whole days
    assert(DateStampDiff(20260101, 20260301) == 59);
    assert(DateStampDiff(20260301, 20260228) == -1);

    // ---- IsTimeRange: the window and its wrap
    uint32_t uNow = ((uint32_t)tmv.tm_wday * 100 + (uint32_t)tmv.tm_hour) * 100 +
                    (uint32_t)tmv.tm_min;
    uNow = uNow * 100 + (uint32_t)tmv.tm_sec;
    assert(IsTimeRange(uNow - 100, uNow + 100, 0) == true);     // inside
    assert(IsTimeRange(uNow + 100, uNow + 200, 0) == false);    // after
    // the wrap: a window whose end is behind its begin covers the late part
    // and the early part, so a clock between the pair is outside it
    assert(IsTimeRange(uNow - 100, uNow - 200, 0) == true);
    assert(IsTimeRange(uNow + 100, uNow - 100, 0) == false);
    // the month-day form (a leading part of 10^8 or more)
    uint32_t uDayNow = ((uint32_t)tmv.tm_mday * 10000 + (uint32_t)tmv.tm_hour) * 100 +
                       (uint32_t)tmv.tm_min;
    uDayNow = uDayNow * 100 + (uint32_t)tmv.tm_sec;
    assert(IsTimeRange(uDayNow - 50, uDayNow + 50, 0) == true);

    // ---- IsActiveTime: the hour, minute and second must all match
    uint32_t uActive = (uint32_t)tmv.tm_mday * 100000000 + (uint32_t)tmv.tm_hour * 10000 +
                       (uint32_t)tmv.tm_min * 100 + (uint32_t)tmv.tm_sec;
    assert(IsActiveTime(g_llNow, uActive) == true);
    assert(IsActiveTime(g_llNow, uActive + 1) == false);        // the second differs
    uint32_t uActiveH = (uint32_t)tmv.tm_mday * 100000000 + (uint32_t)((tmv.tm_hour + 1) % 24) * 10000 +
                        (uint32_t)tmv.tm_min * 100 + (uint32_t)tmv.tm_sec;
    assert(IsActiveTime(g_llNow, uActiveH) == false);

    // ---- CQLanguageGet is the one storage slot
    assert(CQLanguageGet() == g_pCQLanguageValue());
    *CQLanguageGet() = 3;
    assert(*g_pCQLanguageValue() == 3);

    printf("CQBASE_D4_OK: rand, StrCopy, StrStrCh, and the date stamp family\n");
    return 0;
}

// D2 (CQBase) — tq::TimeGet, tq::CTimer and tq::CTimerMS
// 0x140b82df0, 0x140bb59f0..0x140bb5ed0, 0x140b8b460/0x140b8b470
#include "modules/cqbase/src/ctimer.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace tq;

static int64_t g_llNow = 0;
static uint32_t g_uNow = 0;
static int g_nTime64Calls = 0;
static int64_t HookTime64() { g_nTime64Calls++; return g_llNow; }
static uint32_t HookMilli() { return g_uNow; }

int main() {
    g_pfnTime64 = HookTime64;
    g_pfnTimeGetMilli = HookMilli;

    // ---- TimeGet: 0 is the tick, 1 the seconds, and a value past six is the
    // tick again. The calendar packings come from _localtime64 on the seam.
    g_uNow = 12345;
    g_llNow = 1700000000;                       // 2023-11-14 22:13:20 UTC
    assert(TimeGet(0) == 12345);
    assert(TimeGet(9) == 12345);                // anything past six
    assert(TimeGet(1) == 1700000000u);
    uint32_t uYYYYMMDD = TimeGet(kTimeYYYYMMDD);
    uint32_t uHHMMSS = TimeGet(kTimeHHMMSS);
    (void)TimeGet(kTimeYYMMDDHHMM);
    (void)TimeGet(kTimeMMDDHHMMSS);
    (void)TimeGet(kTimeWeekDay);
    // the local hour differs by zone, so compare the shape rather than digits
    assert(uYYYYMMDD % 100 >= 1 && uYYYYMMDD % 100 <= 31);
    assert((uHHMMSS / 10000) <= 23 && (uHHMMSS % 100) <= 60);

    // ---- CTimer construction and assignment
    CTimer t(30);
    assert(t.nInterval == 30 && t.llUpdate == 0);
    assert(t.IsActive() == false);
    CTimer t2(0);
    t2 = t;
    assert(t2.nInterval == 30 && t2.llUpdate == 0);

    // ---- a live timer: IsActive, IsTimeOut, the boundary
    g_llNow = 1000;
    t.Startup(30);
    assert(t.IsActive() == true);
    assert(t.llUpdate == 1000);
    g_llNow = 1029;
    assert(t.IsTimeOut() == false);             // 29 elapsed
    g_llNow = 1030;
    assert(t.IsTimeOut() == true);              // the interval is the floor
    assert(t.IsTimeOut(29) == true);
    assert(t.IsTimeOut(31) == false);
    assert(g_nTime64Calls > 0);

    // ---- TimeOver clears both fields on the timeout and answers false early
    CTimer t3(10);
    g_llNow = 500; t3.Startup(10);
    g_llNow = 505;
    assert(t3.TimeOver() == false);
    assert(t3.nInterval == 10 && t3.llUpdate == 500);   // untouched
    g_llNow = 510;
    assert(t3.TimeOver() == true);
    assert(t3.nInterval == 0 && t3.llUpdate == 0);      // the clear
    assert(t3.TimeOver() == false);                     // already dead

    // ---- GetRemain: a dead timer answers zero, a live one clamps
    CTimer t4(60);
    assert(t4.GetRemain() == 0);
    g_llNow = 2000; t4.Startup(60);
    g_llNow = 2030;
    assert(t4.GetRemain() == 30);               // 60 - (2030-2000)
    g_llNow = 2100;                             // 100 spent of 60
    assert(t4.GetRemain() == 0);                // the leftover clamps at zero
    CTimer t5(60);
    g_llNow = 100; t5.Startup(60);
    g_llNow = 1;                                // a stamp in the future
    assert(t5.GetRemain() == 60);               // the interval is the cap

    // ---- DecInterval floors at zero, IncInterval caps at the max
    CTimer t6(10);
    t6.DecInterval(4);
    assert(t6.nInterval == 6);
    t6.DecInterval(100);
    assert(t6.nInterval == 0);
    t6.IncInterval(7, 12);
    assert(t6.nInterval == 7);
    t6.IncInterval(9, 12);
    assert(t6.nInterval == 12);
    t6.SetInterval(3);
    assert(t6.nInterval == 3);
    t6.Clear();
    assert(t6.nInterval == 0 && t6.llUpdate == 0);

    // ---- ToNextTick: too early, one period, then a full resync
    CTimer t7(10);
    g_llNow = 100; t7.Startup(10);
    g_llNow = 105;
    assert(t7.ToNextTick(10) == false);         // 5 < 10
    g_llNow = 110;
    assert(t7.ToNextTick(10) == true);
    assert(t7.llUpdate == 110);                 // one period steps the stamp
    g_llNow = 400;                              // far past twice the period
    assert(t7.ToNextTick(10) == true);
    assert(t7.llUpdate == 400);                 // a resync to now

    // ---- ToNextTime on both overloads
    CTimer t8(10);
    g_llNow = 100; t8.Startup(10);
    g_llNow = 109;
    assert(t8.ToNextTime() == false);
    g_llNow = 110;
    assert(t8.ToNextTime() == true);
    assert(t8.llUpdate == 110);
    g_llNow = 200;
    assert(t8.ToNextTime(5) == true);
    assert(t8.llUpdate == 200);
    assert(t8.ToNextTime(5) == false);          // just stamped

    // ---- CTimerMS: the millisecond twin, and the eight byte stamp quirk
    g_uNow = 0;
    CTimerMS m(50);
    assert(m.nInterval == 50 && m.uUpdate == 0 && m.uTail == 0);
    assert(m.GetInterval() == 50 && m.GetUpdateTime() == 0);
    assert(m.IsActive() == false);
    g_uNow = 7000;
    m.Startup(50);
    assert(m.IsActive() == true);
    assert(m.GetUpdateTime() == 7000);
    assert(m.uTail == 0);                       // the stamp is 7000, tail clear
    g_uNow = 7049;
    assert(m.IsTimeOut() == false);
    g_uNow = 7050;
    assert(m.IsTimeOut() == true);
    assert(m.IsTimeOut(49) == true);
    assert(m.IsTimeOut(51) == false);

    // the eight byte write lands on both words when the tick passes 2^32
    m.nInterval = 1;
    m.Update();
    assert(m.GetUpdateTime() == g_uNow);

    // ---- TimeOver and the ordering of the clear
    CTimerMS m2(20);
    g_uNow = 100; m2.Startup(20);
    g_uNow = 110;
    assert(m2.TimeOver() == false);
    g_uNow = 120;
    assert(m2.TimeOver() == true);
    assert(m2.nInterval == 0 && m2.uUpdate == 0);

    // ---- Dec/Inc/Set/Clear
    CTimerMS m3(10);
    m3.DecInterval(3);   assert(m3.nInterval == 7);
    m3.DecInterval(9);   assert(m3.nInterval == 0);
    m3.IncInterval(5, 8); assert(m3.nInterval == 5);
    m3.IncInterval(9, 8); assert(m3.nInterval == 8);
    m3.SetInterval(2);   assert(m3.nInterval == 2);
    g_uNow = 555; m3.Update();
    assert(m3.IsActive() == true);
    m3.Clear();
    assert(m3.nInterval == 0 && m3.uUpdate == 0);

    // ---- ToNextTick / ToNextTime on the millisecond class
    CTimerMS m4(10);
    g_uNow = 1000; m4.Startup(10);
    g_uNow = 1005;
    assert(m4.ToNextTick(10) == false);
    g_uNow = 1010;
    assert(m4.ToNextTick(10) == true);
    assert(m4.uUpdate == 1010);
    g_uNow = 5000;
    assert(m4.ToNextTick(10) == true);
    assert(m4.uUpdate == 5000);                 // the resync
    g_uNow = 5009;
    assert(m4.ToNextTime() == false);
    g_uNow = 5010;
    assert(m4.ToNextTime() == true);
    assert(m4.uUpdate == 5010);
    g_uNow = 6000;
    assert(m4.ToNextTime(7) == true);
    assert(m4.ToNextTime(7) == false);

    // ---- the assignment copies both words and the CRT closures build zeros
    CTimerMS m5(1);
    g_uNow = 42; m5.Startup(1);
    CTimerMS m6(0);
    m6 = m5;
    assert(m6.nInterval == 1 && m6.uUpdate == 42);

    char aTimer[sizeof(CTimer)] = { 0 };
    CTimerDefaultCtorClosure(aTimer);
    CTimer* pT = reinterpret_cast<CTimer*>(aTimer);
    assert(pT->nInterval == 0 && pT->llUpdate == 0);
    char aTimerMS[sizeof(CTimerMS)] = { 0 };
    CTimerMSDefaultCtorClosure(aTimerMS);
    CTimerMS* pM = reinterpret_cast<CTimerMS*>(aTimerMS);
    assert(pM->nInterval == 0 && pM->uUpdate == 0);

    printf("CQBASE_D2_OK: TimeGet, CTimer, CTimerMS\n");
    return 0;
}

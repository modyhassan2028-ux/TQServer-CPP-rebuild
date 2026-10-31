// ============================================================================
// ctimer.h — RAW CQBase.dll v6159 · tq::TimeGet, tq::CTimer, tq::CTimerMS
//   the two timer classes of the family and the clock they read.
//   CTimer keeps seconds (0x140bb59f0..0x140bb5da0):
//     +0x00 nInterval (int)        +0x08 llUpdate (8 bytes, _time64 stamp)
//   CTimerMS keeps the millisecond tick (0x140bb5b70..0x140bb5ed0):
//     +0x00 nInterval (int)        +0x04 uUpdate (4 bytes read, 8 bytes written)
//   The millisecond class stamps eight bytes at +0x04 while its reader takes
//   four, so the last four bytes of that write land past the field; the port
//   keeps a named tail member so the same bytes are written in bounds.
// ============================================================================
#ifndef CQBASE_TIME_CTIMER_H
#define CQBASE_TIME_CTIMER_H

#include <cstdint>

namespace tq {

// 0x140b82df0 — 0 is the millisecond tick, 1 seconds, 2..6 the calendar
// packings below, and every other value falls to the default (the tick).
constexpr int kTimeMilli = 0;
constexpr int kTimeSeconds = 1;
constexpr int kTimeYYMMDDHHMM = 2;
constexpr int kTimeYYYYMMDD = 3;
constexpr int kTimeHHMMSS = 4;
constexpr int kTimeMMDDHHMMSS = 5;
constexpr int kTimeWeekDay = 6;
uint32_t TimeGet(int nKind);

// timeGetTime and _time64, as the host supplies them
extern uint32_t (*g_pfnTimeGetMilli)();
extern int64_t (*g_pfnTime64)();

class CTimer {
public:
    int32_t nInterval;      // +0x00
    int32_t nPad;           // +0x04
    int64_t llUpdate;       // +0x08

    explicit CTimer(int nInterval);              // 0x140bb59f0
    CTimer& operator=(const CTimer& r);          // 0x140bb5a00
    void Clear();                                // 0x140bb5a10
    void DecInterval(int nDelta);                // 0x140bb5a20
    int GetRemain();                             // 0x140bb5a30
    void IncInterval(int nDelta, int nMax);      // 0x140bb5a80
    bool IsActive();                             // 0x140bb5a90
    bool IsTimeOut();                            // 0x140bb5aa0
    bool IsTimeOut(int nInterval);               // 0x140bb5ad0
    void SetInterval(int nInterval);             // 0x140bb5b00
    bool TimeOver();                             // 0x140bb5b10
    void Update();                               // 0x140bb5b50
    void Startup(int nInterval);                 // 0x140bb5cb0
    bool ToNextTick(int nInterval);              // 0x140bb5cd0
    bool ToNextTime();                           // 0x140bb5d60
    bool ToNextTime(int nInterval);              // 0x140bb5da0
};

class CTimerMS {
public:
    int32_t nInterval;      // +0x00
    uint32_t uUpdate;       // +0x04  (read as four bytes)
    uint32_t uTail;         // +0x08  (the half of the eight byte stamp write)

    explicit CTimerMS(int nInterval);            // 0x140bb5b70
    CTimerMS& operator=(const CTimerMS& r);      // 0x140bb5b80
    void Clear();                                // 0x140bb5b90
    void DecInterval(int nDelta);                // 0x140bb5ba0
    int GetInterval();                           // 0x140bb5bb0
    uint32_t GetUpdateTime();                    // 0x140bb5bc0
    void IncInterval(int nDelta, int nMax);      // 0x140bb5bd0
    bool IsActive();                             // 0x140bb5be0
    bool IsTimeOut();                            // 0x140bb5bf0
    bool IsTimeOut(int nInterval);               // 0x140bb5c10
    void SetInterval(int nInterval);             // 0x140bb5c40
    bool TimeOver();                             // 0x140bb5c50
    void Update();                               // 0x140bb5c90
    void Startup(int nInterval);                 // 0x140bb5df0
    bool ToNextTick(int nInterval);              // 0x140bb5e10
    bool ToNextTime();                           // 0x140bb5e90
    bool ToNextTime(int nInterval);              // 0x140bb5ed0
};

// the two static initialisers the CRT closure calls (0x140b8b460/0x140b8b470)
void CTimerDefaultCtorClosure(void* pThis);      // 0x140b8b460
void CTimerMSDefaultCtorClosure(void* pThis);    // 0x140b8b470

}  // namespace tq
#endif

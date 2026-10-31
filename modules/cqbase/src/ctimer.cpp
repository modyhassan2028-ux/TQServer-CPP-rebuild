// CQBase.dll v6159 — TimeGet, CTimer and CTimerMS (0x140b82df0, 0x140bb59f0..)
#include "modules/cqbase/src/ctimer.h"

#include <ctime>
#include <new>

namespace tq {

static uint32_t DefTimeGetMilli() { return 0; }
static int64_t DefTime64() { return 0; }
uint32_t (*g_pfnTimeGetMilli)() = DefTimeGetMilli;
int64_t (*g_pfnTime64)() = DefTime64;

// _localtime64 is MSVC's; the port keeps one shape and routes it here.
static tm* LocalTime64(int64_t tValue) {
#if defined(_WIN32)
    return _localtime64(&tValue);
#else
    static thread_local tm s_tm;
    time_t tRaw = (time_t)tValue;
    return localtime_r(&tRaw, &s_tm) ? &s_tm : nullptr;
#endif
}

// 0x140b82df0 — every calendar case builds the same packed decimal from
// _localtime64, and a null tm answers zero. Anything outside 1..6, including
// the zero the timers pass, is the millisecond tick.
uint32_t TimeGet(int nKind) {
    switch (nKind) {
    case kTimeSeconds: {
        return (uint32_t)g_pfnTime64();
    }
    case kTimeYYMMDDHHMM: {
        int64_t t = g_pfnTime64();
        tm* p = LocalTime64(t);
        if (p != nullptr) {
            return ((((uint32_t)(p->tm_year % 100) * 100 + 1 + (uint32_t)p->tm_mon) * 100 +
                     (uint32_t)p->tm_mday) * 100 + (uint32_t)p->tm_hour) * 100 +
                   (uint32_t)p->tm_min;
        }
        return 0;
    }
    case kTimeYYYYMMDD: {
        int64_t t = g_pfnTime64();
        tm* p = LocalTime64(t);
        if (p != nullptr) {
            return ((uint32_t)p->tm_year * 100 + 1 + (uint32_t)p->tm_mon) * 100 +
                   (uint32_t)p->tm_mday;
        }
        return 0;
    }
    case kTimeHHMMSS: {
        int64_t t = g_pfnTime64();
        tm* p = LocalTime64(t);
        if (p != nullptr) {
            return ((uint32_t)p->tm_hour * 100 + (uint32_t)p->tm_min) * 100 +
                   (uint32_t)p->tm_sec;
        }
        return 0;
    }
    case kTimeMMDDHHMMSS: {
        int64_t t = g_pfnTime64();
        tm* p = LocalTime64(t);
        if (p != nullptr) {
            return (((((uint32_t)p->tm_mon + 1) * 100 + (uint32_t)p->tm_mday) * 100 +
                     (uint32_t)p->tm_hour) * 100 + (uint32_t)p->tm_min) * 100 +
                   (uint32_t)p->tm_sec;
        }
        return 0;
    }
    case kTimeWeekDay: {
        int64_t t = g_pfnTime64();
        tm* p = LocalTime64(t);
        if (p != nullptr) return (uint32_t)p->tm_wday;
        return 0;
    }
    default:
        return g_pfnTimeGetMilli();
    }
}

// ---------------------------------------------------------------- CTimer
CTimer::CTimer(int nInterval_) {
    nInterval = nInterval_;
    llUpdate = 0;
}

CTimer& CTimer::operator=(const CTimer& r) {
    nInterval = r.nInterval;
    llUpdate = r.llUpdate;
    return *this;
}

void CTimer::Clear() {
    nInterval = 0;
    llUpdate = 0;
}

void CTimer::DecInterval(int nDelta) {
    nInterval = nInterval - nDelta;
    if (nInterval < 0) nInterval = 0;
}

// 0x140bb5a30 — a cleared stamp answers zero outright; otherwise the leftover
// is interval minus the seconds already spent, clamped into 0..interval. The
// stamp's low dword is what the original adds.
int CTimer::GetRemain() {
    if (llUpdate == 0) return 0;
    int64_t tNow = g_pfnTime64();
    int nInt = nInterval;
    int nRemain = (nInt - (int)tNow) + (int)(int32_t)(uint32_t)llUpdate;
    if (nInt <= nRemain) return nInt;
    if (nRemain < 0) nRemain = 0;
    return nRemain;
}

void CTimer::IncInterval(int nDelta, int nMax) {
    nInterval = nInterval + nDelta;
    if (nMax < nInterval) nInterval = nMax;
}

bool CTimer::IsActive() { return llUpdate != 0; }

bool CTimer::IsTimeOut() {
    int64_t tNow = g_pfnTime64();
    return (int64_t)nInterval <= tNow - llUpdate;
}

bool CTimer::IsTimeOut(int nInterval_) {
    int64_t tNow = g_pfnTime64();
    return (int64_t)nInterval_ <= tNow - llUpdate;
}

void CTimer::SetInterval(int nInterval_) { nInterval = nInterval_; }

// 0x140bb5b10 — a live timeout clears both fields and answers true.
bool CTimer::TimeOver() {
    if (llUpdate != 0) {
        int64_t tNow = g_pfnTime64();
        if ((int64_t)nInterval <= tNow - llUpdate) {
            nInterval = 0;
            llUpdate = 0;
            return true;
        }
    }
    return false;
}

void CTimer::Update() { llUpdate = g_pfnTime64(); }

void CTimer::Startup(int nInterval_) {
    nInterval = nInterval_;
    llUpdate = g_pfnTime64();
}

// 0x140bb5cd0 — the three arm shape: too early answers false, a full double
// period re-stamps from now, otherwise the stamp steps by exactly one period.
bool CTimer::ToNextTick(int nInterval_) {
    int64_t tNow = g_pfnTime64();
    if (tNow - llUpdate < (int64_t)nInterval_) return false;
    tNow = g_pfnTime64();
    if ((int64_t)(nInterval_ * 2) <= tNow - llUpdate) {
        llUpdate = g_pfnTime64();
        return true;
    }
    llUpdate = (int64_t)nInterval_ + llUpdate;
    return true;
}

bool CTimer::ToNextTime() {
    int64_t tNow = g_pfnTime64();
    if ((int64_t)nInterval <= tNow - llUpdate) {
        llUpdate = g_pfnTime64();
        return true;
    }
    return false;
}

bool CTimer::ToNextTime(int nInterval_) {
    int64_t tNow = g_pfnTime64();
    if ((int64_t)nInterval_ <= tNow - llUpdate) {
        llUpdate = g_pfnTime64();
        return true;
    }
    return false;
}

// -------------------------------------------------------------- CTimerMS
CTimerMS::CTimerMS(int nInterval_) {
    nInterval = nInterval_;
    uUpdate = 0;
    uTail = 0;
}

CTimerMS& CTimerMS::operator=(const CTimerMS& r) {
    nInterval = r.nInterval;
    uUpdate = r.uUpdate;
    return *this;
}

// the two words are cleared in this order in the original: +4 first
void CTimerMS::Clear() {
    uUpdate = 0;
    nInterval = 0;
}

void CTimerMS::DecInterval(int nDelta) {
    nInterval = nInterval - nDelta;
    if (nInterval < 0) nInterval = 0;
}

int CTimerMS::GetInterval() { return nInterval; }
uint32_t CTimerMS::GetUpdateTime() { return uUpdate; }

void CTimerMS::IncInterval(int nDelta, int nMax) {
    nInterval = nInterval + nDelta;
    if (nMax < nInterval) nInterval = nMax;
}

bool CTimerMS::IsActive() { return uUpdate != 0; }

bool CTimerMS::IsTimeOut() {
    uint32_t uNow = g_pfnTimeGetMilli();
    return (uint32_t)nInterval <= uNow - (uint32_t)uUpdate;
}

bool CTimerMS::IsTimeOut(int nInterval_) {
    uint32_t uNow = g_pfnTimeGetMilli();
    return (uint32_t)nInterval_ <= uNow - (uint32_t)uUpdate;
}

void CTimerMS::SetInterval(int nInterval_) { nInterval = nInterval_; }

bool CTimerMS::TimeOver() {
    if (uUpdate != 0) {
        uint32_t uNow = g_pfnTimeGetMilli();
        if ((uint32_t)nInterval <= uNow - (uint32_t)uUpdate) {
            uUpdate = 0;
            nInterval = 0;
            return true;
        }
    }
    return false;
}

// 0x140bb5c90 — the original stores an eight byte value at +0x04, so the two
// words +0x04 and +0x08 take the stamp while the reader only ever sees the
// first. Kept as the same eight byte write.
void CTimerMS::Update() {
    uint32_t uNow = g_pfnTimeGetMilli();
    *reinterpret_cast<uint64_t*>(&uUpdate) = (uint64_t)uNow;
}

void CTimerMS::Startup(int nInterval_) {
    nInterval = nInterval_;
    uint32_t uNow = g_pfnTimeGetMilli();
    *reinterpret_cast<uint64_t*>(&uUpdate) = (uint64_t)uNow;
}

// 0x140bb5e10 — the stored stamp is read into a local before the second call,
// exactly as the original does.
bool CTimerMS::ToNextTick(int nInterval_) {
    uint32_t uNow = g_pfnTimeGetMilli();
    if (uNow - (uint32_t)uUpdate < (uint32_t)nInterval_) return false;
    int nStored = (int)uUpdate;
    uNow = g_pfnTimeGetMilli();
    if ((uint32_t)(nInterval_ * 2) <= uNow - (uint32_t)nStored) {
        uint32_t uFresh = g_pfnTimeGetMilli();
        *reinterpret_cast<uint64_t*>(&uUpdate) = (uint64_t)uFresh;
        return true;
    }
    uUpdate = (uint32_t)(nStored + nInterval_);
    return true;
}

bool CTimerMS::ToNextTime() {
    uint32_t uNow = g_pfnTimeGetMilli();
    if ((uint32_t)nInterval <= uNow - (uint32_t)uUpdate) {
        uint32_t uFresh = g_pfnTimeGetMilli();
        *reinterpret_cast<uint64_t*>(&uUpdate) = (uint64_t)uFresh;
        return true;
    }
    return false;
}

bool CTimerMS::ToNextTime(int nInterval_) {
    uint32_t uNow = g_pfnTimeGetMilli();
    if ((uint32_t)nInterval_ <= uNow - (uint32_t)uUpdate) {
        uint32_t uFresh = g_pfnTimeGetMilli();
        *reinterpret_cast<uint64_t*>(&uUpdate) = (uint64_t)uFresh;
        return true;
    }
    return false;
}

// 0x140b8b460 / 0x140b8b470 — the CRT closures that build the timer with a
// zero interval.
void CTimerDefaultCtorClosure(void* pThis) {
    new (pThis) CTimer(0);
}
void CTimerMSDefaultCtorClosure(void* pThis) {
    new (pThis) CTimerMS(0);
}

}  // namespace tq

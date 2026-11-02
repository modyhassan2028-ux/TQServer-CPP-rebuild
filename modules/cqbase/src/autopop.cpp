// ============================================================================
// autopop.cpp — RAW CQBase.dll v6159 · CAutoPop
//   0x140b8b490 (DeadLoopDump) and 0x140b8d7e0 (the destructor).
//   What the two keep between them: a count of every trip, a decaying counter that is
//   reset to ten when its own sixty millisecond timer fires, and one report per trip
//   unless that counter has just run down to zero.
// ============================================================================
#include "modules/cqbase/src/autopop.h"
#include "modules/cqbase/src/logkernel.h"

namespace tq {

CMyCriticalSection g_AutoPopCtrl(2000);    // m_xCtrl
CMyCriticalSection g_AutoPopDump(2000);    // m_xDump
int32_t g_nAutoPopAllCount = 0;            // m_nAllCount
int32_t g_nAutoPopDecCount = 0;            // m_nDecCount
CTimer g_AutoPopDelay(0);                  // m_tDelay, its interval is what ToNextTime takes

static const char* DefaultAutoPopName(void*) { return ""; }
const char* (*g_pfnAutoPopName)(void* pGuard) = DefaultAutoPopName;

// 0x140b8b490 — the guard is taken for the whole of it: the trip is counted, the timer is
// asked whether its sixty milliseconds have passed (ten more reports if they have), the
// counter comes down by one whatever happened, and the trip is reported unless the counter
// stood at zero when it was read.
void CAutoPop::DeadLoopDump(const char* pszWhere, int nMs) {
    CMySingleLock lock(&g_AutoPopCtrl);
    ++g_nAutoPopAllCount;
    const bool bElapsed = g_AutoPopDelay.ToNextTime(0x3c);
    int nRemaining = g_nAutoPopDecCount;
    if (bElapsed) nRemaining = 10;
    g_nAutoPopDecCount = nRemaining - 1;
    if (nRemaining != 0) {
        log_InlineLogERROR("DeadLoopDump[%s], ms[%d], count[%d]", pszWhere, nMs,
                           g_nAutoPopAllCount);
    }
}

// 0x140b8d7e0 — the destructor looks at the list its guard holds: a list with nothing in
// it says nothing at all, and one that is still holding something is named and reported
// when more than a second has gone by since the last time.
CAutoPop::~CAutoPop() {
    int64_t* pList = nullptr;
    const char* pszName = nullptr;
    uint32_t uNow = 0;
    int32_t nPassed = 0;
    {
        CMySingleLock lock(&g_AutoPopDump);
        pList = *(int64_t**)m_pGuard;
        // the emptiness test the raw makes: the two pointers at +0x18 and +0x20, their
        // difference with the low three bits dropped
        if (((pList[4] - pList[3]) & 0xfffffffffffffff8ULL) == 0) {
            return;   // the lock releases with the scope
        }
        pszName = g_pfnAutoPopName(pList);
    }
    uNow = TimeGet(0);
    nPassed = (int32_t)(uNow - (uint32_t)m_nLastMs);
    if (nPassed > 1000) {
        DeadLoopDump(pszName, nPassed);
    }
}

}  // namespace tq

// CQBase.dll v6159 — the tq locking primitives (0x140ba0060..0x140ba0390)
#include "modules/cqbase/src/csync.h"

#if defined(_WIN32)
#include <windows.h>
#endif

namespace tq {

#if defined(_WIN32)
static void CsEnter(void* p) { EnterCriticalSection((CRITICAL_SECTION*)p); }
static void CsLeave(void* p) { LeaveCriticalSection((CRITICAL_SECTION*)p); }
static uint32_t WaitOne(void* h, uint32_t nMs) { return WaitForSingleObject((HANDLE)h, nMs); }
static bool RelMutex(void* h) { return ReleaseMutex((HANDLE)h) != 0; }
static bool SetEv(void* h) { return SetEvent((HANDLE)h) != 0; }
static uint32_t WaitMany(uint32_t n, void** ph, bool bAll, uint32_t nMs) {
    return WaitForMultipleObjects(n, (const HANDLE*)ph, bAll ? TRUE : FALSE, nMs);
}
SyncApi g_SyncApi = { CsEnter, CsLeave, WaitOne, RelMutex, SetEv, WaitMany };
#else
static void CsEnter(void*) {}
static void CsLeave(void*) {}
static uint32_t WaitOne(void*, uint32_t) { return kWaitTimeout; }
static bool RelMutex(void*) { return false; }
static bool SetEv(void*) { return false; }
static uint32_t WaitMany(uint32_t, void**, bool, uint32_t) { return kWaitTimeout; }
SyncApi g_SyncApi = { CsEnter, CsLeave, WaitOne, RelMutex, SetEv, WaitMany };
#endif

// 0x140ba0060 / 0x140ba0070 — straight into the critical section at +0x08.
void CMyCriticalSection::Lock() { g_SyncApi.pfnEnterCS(abCs); }
void CMyCriticalSection::Unlock() { g_SyncApi.pfnLeaveCS(abCs); }

// 0x140ba0110 / 0x140ba0130 — a null handle is skipped, not an error.
void CMutexLock::Lock() {
    if (hMutex != nullptr) g_SyncApi.pfnWaitSingle(hMutex, 0xffffffff);
}
void CMutexLock::Unlock() {
    if (hMutex != nullptr) g_SyncApi.pfnReleaseMutex(hMutex);
}

// 0x140ba0190 — Signal answers zero no matter what SetEvent returned.
int CMyEvent::Signal() {
    g_SyncApi.pfnSetEvent(hEvent);
    return 0;
}

// 0x140ba01b0 — object zero is success, a timeout is the marker, anything else
// is the failure code.
int CMyEvent::Wait(int nMs) {
    uint32_t uRet = g_SyncApi.pfnWaitSingle(hEvent, (uint32_t)nMs);
    if (uRet == kWaitObject0) return 0;
    int nRet = kWaitFailCode;
    if (uRet == kWaitTimeout) nRet = kWaitTimeoutCode;
    return nRet;
}

// 0x140ba02e0 — a null array, a negative index, an index past the count or a
// null handle all answer -1 without touching anything.
int CMyMultiEvent::Signal(int nIndex) {
    void** ph = phEvents;
    if (((ph != nullptr) && (-1 < nIndex)) && (nIndex < nCount) &&
        (ph[(int64_t)nIndex] != nullptr)) {
        g_SyncApi.pfnSetEvent(ph[(int64_t)nIndex]);
        return 0;
    }
    return -1;
}

// 0x140ba0320 — a return at or past the count is a failure, and only the
// timeout value past the count turns into the timeout marker.
int CMyMultiEvent::Wait(int nMs) {
    uint32_t uRet = g_SyncApi.pfnWaitMulti((uint32_t)nCount, phEvents, false, (uint32_t)nMs);
    uint32_t uOut = uRet;
    if (((uint32_t)nCount <= uRet) && (uOut = 0xffffffff, uRet == kWaitTimeout)) {
        uOut = 0x7fffffff;
    }
    return (int)uOut;
}

// 0x140ba0390 — the virtual at +0x10 of the object it holds.
void CMySingleLock::Unlock() {
    pLock->Unlock();
}

}  // namespace tq

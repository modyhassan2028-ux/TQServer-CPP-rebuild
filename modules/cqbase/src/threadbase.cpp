// CQBase.dll v6159 — CThreadBase (0x140bb30a0..0x140bb3680)
#include "modules/cqbase/src/threadbase.h"
#include "modules/cqbase/src/logkernel.h"

#include <cstdint>

namespace tq {

static uint32_t DefaultGetCurrentThreadId() { return 1; }
static uint32_t DefaultGetThreadId(void*) { return 0; }
static bool DefaultCloseHandle(void*) { return true; }
static void* DefaultCreateEvent() { return nullptr; }
static bool DefaultSetEvent(void*) { return false; }
static uint32_t DefaultWaitForSingleObject(void*, uint32_t) { return kThreadWaitFailed; }
static uint32_t DefaultResumeThread(void*) { return 0; }
static uint32_t DefaultGetLastError() { return 0; }
static uintptr_t DefaultBeginThreadEx(uint32_t (*)(void*), void*, unsigned, unsigned*) { return 0; }
static int DefaultGetErrno() { return 0; }

ThreadApi g_ThreadApi = {
    DefaultGetCurrentThreadId, DefaultGetThreadId, DefaultCloseHandle, DefaultCreateEvent,
    DefaultSetEvent, DefaultWaitForSingleObject, DefaultResumeThread, DefaultGetLastError,
    DefaultBeginThreadEx, DefaultGetErrno,
};

// 0x140bb3660 / 0x140bb3670 — both hooks are empty in the raw
void CThreadBaseOnDestroy(CThreadBase*) {}
void CThreadBaseOnInit(CThreadBase*) {}

const CThreadVt g_CThreadBaseVt = {
    nullptr,                 // +0x00  _purecall in the raw
    CThreadBaseOnDestroy,    // +0x08
    CThreadBaseOnInit,       // +0x10
    nullptr,                 // +0x18  _purecall, the run hook the loop calls
};

// 0x140bb30a0
CThreadBase::CThreadBase()
    : pVt(&g_CThreadBaseVt), hCloseEvent(nullptr), hThread(nullptr), strName() {}

// 0x140bb30e0 — waits for the thread without a bound, reports both ends, closes both
// handles. The handles are not cleared, the object is going away.
CThreadBase::~CThreadBase() {
    if (hThread != nullptr) {
        log_InlineLogERROR("thread %u is waiting for thread %u \"%s\" to finish ...",
                           g_ThreadApi.pfnGetCurrentThreadId(),
                           g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
        uint32_t uWait = g_ThreadApi.pfnWaitForSingleObject(hThread, kThreadWaitInfinite);
        if (uWait == kThreadWaitObject) {
            log_InlineLogMessage("thread %u continues after thread %u \"%s\" finished",
                                 g_ThreadApi.pfnGetCurrentThreadId(),
                                 g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
        } else {
            uint32_t uError = g_ThreadApi.pfnGetLastError();
            log_InlineLogERROR(
                "thread %u cannot wait for thread %u \"%s\" to finish with error %u",
                g_ThreadApi.pfnGetCurrentThreadId(), g_ThreadApi.pfnGetThreadId(hThread),
                strName.c_str(), uError);
        }
        g_ThreadApi.pfnCloseHandle(hThread);
    }
    if (hCloseEvent != nullptr) g_ThreadApi.pfnCloseHandle(hCloseEvent);
}

// 0x140bb3220
bool CThreadBase::CloseThread(uint32_t uTimeoutMs) {
    if (hThread == nullptr) return true;
    if (g_ThreadApi.pfnGetCurrentThreadId() == g_ThreadApi.pfnGetThreadId(hThread)) {
        log_InlineLogMessage("thread %u \"%s\" set close event for itself ...",
                             g_ThreadApi.pfnGetCurrentThreadId(), strName.c_str());
        g_ThreadApi.pfnSetEvent(hCloseEvent);
        return true;
    }
    log_InlineLogMessage("thread %u is trying to close thread %u \"%s\" in %u ms ...",
                         g_ThreadApi.pfnGetCurrentThreadId(),
                         g_ThreadApi.pfnGetThreadId(hThread), strName.c_str(), uTimeoutMs);
    g_ThreadApi.pfnResumeThread(hThread);
    g_ThreadApi.pfnSetEvent(hCloseEvent);
    uint32_t uWait = g_ThreadApi.pfnWaitForSingleObject(hThread, uTimeoutMs);
    if (uWait == kThreadWaitObject) {
        log_InlineLogMessage("thread %u successfully closed thread %u \"%s\" in %u ms",
                             g_ThreadApi.pfnGetCurrentThreadId(),
                             g_ThreadApi.pfnGetThreadId(hThread), strName.c_str(), uTimeoutMs);
        g_ThreadApi.pfnCloseHandle(hThread);
        hThread = nullptr;
        strName = "";
        if (hCloseEvent != nullptr) {
            g_ThreadApi.pfnCloseHandle(hCloseEvent);
            hCloseEvent = nullptr;
        }
        return true;
    }
    if (uWait == kThreadWaitTimeout) {
        log_InlineLogERROR("thread %u cannot close thread %u \"%s\"",
                           g_ThreadApi.pfnGetCurrentThreadId(),
                           g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
        return false;
    }
    uint32_t uError = g_ThreadApi.pfnGetLastError();
    log_InlineLogERROR("thread %u cannot close thread %u \"%s\" with error %u",
                       g_ThreadApi.pfnGetCurrentThreadId(),
                       g_ThreadApi.pfnGetThreadId(hThread), strName.c_str(), uError);
    return false;
}

// 0x140bb3430
void* CThreadBase::GetThreadHandle() const { return hThread; }

// 0x140bb3440
bool CThreadBase::ResumeThread() {
    if (hThread == nullptr) return false;
    uint32_t uRet = g_ThreadApi.pfnResumeThread(hThread);
    if (uRet == 0) {
        log_InlineLogWARNING("thread %u resumed thread %u \"%s\" but it was not suspended",
                             g_ThreadApi.pfnGetCurrentThreadId(),
                             g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
    } else if (uRet == 1) {
        log_InlineLogMessage("thread %u resumed thread %u \"%s\" and it was restarted",
                             g_ThreadApi.pfnGetCurrentThreadId(),
                             g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
        return true;
    } else if (uRet == 0xffffffff) {
        log_InlineLogERROR("thread %u cannot resume thread %u \"%s\"",
                           g_ThreadApi.pfnGetCurrentThreadId(),
                           g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
        return false;
    }
    return true;
}

// 0x140bb3550 — up, OnInit, then the close event is polled with no wait at all;
// anything other than a timeout leaves with code 0, a run hook that answers false
// leaves with code 2.
uint32_t CThreadBase::ThreadProc() {
    uint32_t uExitCode = 0;
    log_InlineLogMessage("thread %u \"%s\" is up and running",
                         g_ThreadApi.pfnGetCurrentThreadId(), strName.c_str());
    if (pVt != nullptr && pVt->pfnOnInit != nullptr) pVt->pfnOnInit(this);
    for (;;) {
        if (g_ThreadApi.pfnWaitForSingleObject(hCloseEvent, 0) != kThreadWaitTimeout) break;
        bool bKeepGoing = (pVt != nullptr && pVt->pfnRun != nullptr) ? pVt->pfnRun(this) : false;
        if (!bKeepGoing) {
            uExitCode = 2;
            break;
        }
    }
    // the raw hands the format one number and passes it twice
    log_InlineLogMessage("thread %u \"%s\" is exiting with code %u",
                         g_ThreadApi.pfnGetCurrentThreadId(), strName.c_str(), uExitCode,
                         uExitCode);
    if (pVt != nullptr && pVt->pfnOnDestroy != nullptr) pVt->pfnOnDestroy(this);
    log_InlineLogMessage("thread %u \"%s\" exited with code %u",
                         g_ThreadApi.pfnGetCurrentThreadId(), strName.c_str(), uExitCode);
    return uExitCode;
}

// 0x140bb3650 — the same body reached from the thread entry point
uint32_t CThreadBase::TrueThreadProc(void* pParam) {
    return static_cast<CThreadBase*>(pParam)->ThreadProc();
}

// 0x140bb3680 — a name is required, an existing thread is refused, the event comes
// first, then the name, then the thread itself. A thread that fails to start takes
// the event back down with it.
bool CThreadBase::CreateThread(const char* pszName, bool bRun) {
    if (pszName == nullptr) {
        log_InlineLogERROR("thread %u cannot create thread without a name",
                           g_ThreadApi.pfnGetCurrentThreadId());
        return false;
    }
    if (hThread != nullptr) {
        log_InlineLogERROR("thread %u cannot create thread \"%s\" over thread %u \"%s\"",
                           g_ThreadApi.pfnGetCurrentThreadId(), pszName,
                           g_ThreadApi.pfnGetThreadId(hThread), strName.c_str());
        return false;
    }
    hCloseEvent = g_ThreadApi.pfnCreateEvent();
    if (hCloseEvent == nullptr) {
        uint32_t uError = g_ThreadApi.pfnGetLastError();
        log_InlineLogERROR("thread %u cannot create event for thread \"%s\" with error %u",
                           g_ThreadApi.pfnGetCurrentThreadId(), pszName, uError);
        return false;
    }
    strName = pszName;
    unsigned uFlags = bRun ? 0u : kThreadCreateSuspended;
    unsigned uThreadId = 0;
    uintptr_t uHandle = g_ThreadApi.pfnBeginThreadEx(&CThreadBase::TrueThreadProc, this, uFlags,
                                                     &uThreadId);
    hThread = (void*)uHandle;
    if (uHandle == 0) {
        int nErrno = g_ThreadApi.pfnGetErrno();
        log_InlineLogERROR("thread %u cannot create thread \"%s\" with error %d",
                           g_ThreadApi.pfnGetCurrentThreadId(), pszName, nErrno);
        g_ThreadApi.pfnCloseHandle(hCloseEvent);
        hCloseEvent = nullptr;
        return false;
    }
    if (bRun) {
        log_InlineLogMessage("thread %u created running thread %u \"%s\"",
                             g_ThreadApi.pfnGetCurrentThreadId(), uThreadId, pszName);
    } else {
        log_InlineLogMessage("thread %u created suspended thread %u \"%s\"",
                             g_ThreadApi.pfnGetCurrentThreadId(), uThreadId, pszName);
    }
    return true;
}

}  // namespace tq

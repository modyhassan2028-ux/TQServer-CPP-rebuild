// CQBase.dll v6159 — CThreadTimesInfo handle (0x140bb3850..0x140bb3960, 0x140bb5670)
// and the process half of CThreadTimesInfoBase::Init (0x140bb4750)
#include "modules/cqbase/src/threadtimesinfo.h"
#include "modules/cqbase/src/logkernel.h"

#include <cstdarg>
#include <cstdio>

namespace tq {

// 0x140bce3c8 — slot 0 is the deleting destructor, nothing else is called through
// this table by the handle.
static const void* const kCThreadTimesInfoBaseVt[1] = {
    (const void*)&CThreadTimesInfoBaseDeletingDtor,
};

const void* const* CThreadTimesInfoBase::Table() { return kCThreadTimesInfoBaseVt; }

// 0x140bb3880 — the file's own reporter: format into a 0x740 buffer and hand it to
// log_Save for "syslog/thread" at level 0. The original zeroes the buffer and leaves a
// terminator at its end before formatting; formatting over a cleared buffer keeps the
// same bytes in the same place.
static void ThreadTimesLog(const char* pszFormat, ...) {
    if (pszFormat == nullptr) return;
    char szBuf[0x740];
    szBuf[0] = '\0';
    szBuf[0x73f] = '\0';
    va_list vaArgs;
    va_start(vaArgs, pszFormat);
    vsnprintf(szBuf, 0x740, pszFormat, vaArgs);
    va_end(vaArgs);
    szBuf[0x73f] = '\0';
    log_Save((char*)"syslog/thread", szBuf, 0);
}

static void* DefaultGetCurrentProcess() { return nullptr; }
static bool DefaultGetProcessTimes(void*, uint64_t*, uint64_t*, uint64_t*, uint64_t*) {
    return false;
}
static uint32_t DefaultGetTickCount() { return 0; }
static uint32_t DefaultGetThreadIdTimes(void*) { return 0; }
static bool DefaultGetThreadTimes(void*, uint64_t*, uint64_t*, uint64_t*, uint64_t*) {
    return false;
}

ThreadTimesApi g_ThreadTimesApi = {
    DefaultGetCurrentProcess, DefaultGetProcessTimes, DefaultGetTickCount,
    DefaultGetThreadIdTimes,  DefaultGetThreadTimes,
};

// 0x140bb4750 — the process is sampled once, then every thread in the list is asked
// for its own times. A thread whose handle is empty or -1 is skipped without a word,
// a thread id of zero is skipped too, and a failed ask for times only reports.
bool CThreadTimesInfoBase::Init() {
    uint64_t uCreation = 0, uExit = 0, uKernel = 0, uUser = 0;
    hProcess = g_ThreadTimesApi.pfnGetCurrentProcess();
    if (!g_ThreadTimesApi.pfnGetProcessTimes(hProcess, &uCreation, &uExit, &uKernel, &uUser)) {
        ThreadTimesLog("CThreadTimesInfoBase::Init GetProcessTimes failed.");
    }
    // the raw stores these two no matter what the ask answered: on failure the values
    // come from the out parameters as the call left them, which in the original means
    // uninitialised stack. The numbers below are the ones the call produced, not zeros.
    uProcessKernelMs = (uint32_t)(int32_t)((int64_t)uKernel / 10000);
    uProcessUserMs = (uint32_t)(int32_t)((int64_t)uUser / 10000);
    uTickCount = g_ThreadTimesApi.pfnGetTickCount();
    for (size_t i = 0; i < vSamples.size(); ++i) {
        CThreadTimesSample& rSample = vSamples[i];
        void* hThread = rSample.hThread;
        if (hThread == nullptr || hThread == (void*)(intptr_t)-1) continue;
        uint32_t uThreadId = g_ThreadTimesApi.pfnGetThreadId(hThread);
        if (uThreadId == 0) continue;
        uint64_t uThreadCreation = 0, uThreadExit = 0, uThreadKernel = 0, uThreadUser = 0;
        if (!g_ThreadTimesApi.pfnGetThreadTimes(hThread, &uThreadCreation, &uThreadExit,
                                                &uThreadKernel, &uThreadUser)) {
            ThreadTimesLog("CThreadTimesInfoBase::Start GetThreadTimes failed.Thread id %u",
                           uThreadId);
            continue;
        }
        rSample.uKernelMs = (uint32_t)(int32_t)((int64_t)uThreadKernel / 10000);
        rSample.uUserMs = (uint32_t)(int32_t)((int64_t)uThreadUser / 10000);
    }
    ThreadTimesLog("ThreadTimesInfo Init ok.");
    uInited = 1;
    return true;
}

// 0x140bb5590 — the table, an empty sample list, then every measuring field zeroed.
// The list is a debug level STL vector, which is why the raw builds a proxy object
// with operator new(8) at the container's start and links it before returning.
CThreadTimesInfoBase::CThreadTimesInfoBase()
    : pVt(kCThreadTimesInfoBaseVt),
      vSamples(),
      uField28(0),
      uField30(0),
      hProcess(nullptr),
      uProcessUserMs(0),
      uProcessKernelMs(0),
      uTickCount(0),
      uInited(0) {}

// 0x140bb5800
CThreadTimesInfoBase::~CThreadTimesInfoBase() { pVt = kCThreadTimesInfoBaseVt; }

void* CThreadTimesInfoBaseNew() { return new CThreadTimesInfoBase(); }

void* CThreadTimesInfoBaseDeletingDtor(void* pBase, int nFlag) {
    CThreadTimesInfoBase* pObj = (CThreadTimesInfoBase*)pBase;
    pObj->~CThreadTimesInfoBase();
    if ((nFlag & 1) != 0) operator delete(pBase);
    return pBase;
}

PfnNewThreadTimesInfoBase g_pfnNewThreadTimesInfoBase = CThreadTimesInfoBaseNew;

// The handle's own table. Nothing in the binary calls through it, the wrapper's
// destructor is not virtual, but the original stores a table at +0x00, so the
// member exists and points at a table of this object's own.
static const void* const kCThreadTimesInfoVt[1] = { nullptr };

// 0x140bb5670
CThreadTimesInfo::CThreadTimesInfo() : pVt(kCThreadTimesInfoVt), pBase(nullptr) {
    pBase = g_pfnNewThreadTimesInfoBase();
}

// 0x140bb3850 — shares the measuring object with the one it copies
CThreadTimesInfo::CThreadTimesInfo(const CThreadTimesInfo& rOther)
    : pVt(kCThreadTimesInfoVt), pBase(rOther.pBase) {}

// 0x140bb3870 — overwrites the pointer, the old object is not released
CThreadTimesInfo& CThreadTimesInfo::operator=(const CThreadTimesInfo& rOther) {
    pBase = rOther.pBase;
    return *this;
}

// 0x140bb3960 — the object goes through its own first table slot with (this, 1)
CThreadTimesInfo::~CThreadTimesInfo() {
    if (pBase != nullptr) {
        typedef void (*PfnDeletingDtor)(void*, int);
        void** ppVt = *(void***)pBase;
        ((PfnDeletingDtor)ppVt[0])(pBase, 1);
    }
    pBase = nullptr;
}

}  // namespace tq

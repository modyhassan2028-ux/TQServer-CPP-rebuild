// ============================================================================
// threadbase.h — RAW CQBase.dll v6159 · CThreadBase
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// The vtable is modelled as an explicit table instead of C++ virtuals, because
// the raw table at 0x140bca0d0 does not follow a declaration order that can be
// written down without guessing:
//     +0x00  _purecall                       (0x140bb6a9c, never called here)
//     +0x08  OnDestroy                       (0x140bb3660, empty)
//     +0x10  OnInit                          (0x140bb3670, empty)
//     +0x18  _purecall, overridden by the run hook the raw loop calls
// Storing the table pointer at +0x00 and calling through the fixed offsets keeps
// the object layout and the call order identical to the original.
//
// MODELLING NOTE (declared, not guessed):
//   1. The original's file name for this class leaves no path string in the
//      binary, so it is placed beside threadtimesinfo.cpp, which does. The class
//      name and every address here are the original's.
//   2. The name member is a std::string at +0x18. In this binary that is a debug
//      level STL string, whose buffer sits at +0x20 and capacity at +0x38, which
//      is why the raw keeps comparing 0x38 and reading 0x20 for the small string
//      form. std::string and c_str() give the same text.
//   3. The Win32 thread calls and _beginthreadex are seams. The defaults below
//      are inert, and every test injects its own so the call order, the return
//      values and the log lines can be pinned.
// ============================================================================
#ifndef CQBASE_THREADBASE_H
#define CQBASE_THREADBASE_H

#include <cstdint>
#include <string>

namespace tq {

constexpr uint32_t kThreadWaitObject = 0;         // WAIT_OBJECT_0
constexpr uint32_t kThreadWaitTimeout = 0x102;    // WAIT_TIMEOUT
constexpr uint32_t kThreadWaitFailed = 0xffffffff;  // WAIT_FAILED
constexpr uint32_t kThreadWaitInfinite = 0xffffffff;
constexpr unsigned kThreadCreateSuspended = 4;    // CREATE_SUSPENDED

class CThreadBase;
typedef void (*PfnThreadSlot00)(CThreadBase*);
typedef void (*PfnThreadOnDestroy)(CThreadBase*);
typedef void (*PfnThreadOnInit)(CThreadBase*);
typedef bool (*PfnThreadRun)(CThreadBase*);

struct CThreadVt {
    PfnThreadSlot00 pfnSlot00;   // +0x00
    PfnThreadOnDestroy pfnOnDestroy;  // +0x08
    PfnThreadOnInit pfnOnInit;        // +0x10
    PfnThreadRun pfnRun;              // +0x18
};

struct ThreadApi {
    uint32_t (*pfnGetCurrentThreadId)();
    uint32_t (*pfnGetThreadId)(void* hThread);
    bool (*pfnCloseHandle)(void* hHandle);
    void* (*pfnCreateEvent)();                                  // CreateEventA(NULL,0,0,NULL)
    bool (*pfnSetEvent)(void* hEvent);
    uint32_t (*pfnWaitForSingleObject)(void* hHandle, uint32_t uMilliseconds);
    uint32_t (*pfnResumeThread)(void* hThread);
    uint32_t (*pfnGetLastError)();
    uintptr_t (*pfnBeginThreadEx)(uint32_t (*pfnStart)(void*), void* pArg, unsigned uFlags,
                                  unsigned* puThreadId);        // _beginthreadex
    int (*pfnGetErrno)();
};
extern ThreadApi g_ThreadApi;
extern const CThreadVt g_CThreadBaseVt;

class CThreadBase {
public:
    CThreadBase();                     // 0x140bb30a0
    ~CThreadBase();                    // 0x140bb30e0
    bool CloseThread(uint32_t uTimeoutMs);   // 0x140bb3220
    void* GetThreadHandle() const;           // 0x140bb3430
    bool ResumeThread();                     // 0x140bb3440
    uint32_t ThreadProc();                   // 0x140bb3550
    static uint32_t TrueThreadProc(void* pParam);   // 0x140bb3650
    bool CreateThread(const char* pszName, bool bRun);  // 0x140bb3680

    const CThreadVt* pVt;   // +0x00
    void* hCloseEvent;      // +0x08
    void* hThread;          // +0x10
    std::string strName;    // +0x18
};

void CThreadBaseOnDestroy(CThreadBase* pThis);   // 0x140bb3660, empty in the raw
void CThreadBaseOnInit(CThreadBase* pThis);      // 0x140bb3670, empty in the raw

}  // namespace tq
#endif

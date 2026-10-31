// D14 (CQBase) — CThreadBase: create, run, close, wait
#include "modules/cqbase/src/threadbase.h"
#include "modules/cqbase/src/logkernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace tq;

static std::vector<std::string> g_vTexts;
static std::vector<std::string> g_vFiles;
static bool FakeRunning() { return false; }
static void FakeWrite(const char* pszFile, const char* pszText, int) {
    g_vFiles.push_back(pszFile ? pszFile : "<null>");
    g_vTexts.push_back(pszText ? pszText : "<null>");
}
static void FakePost(void*, const char*, const char*, int) {}
static uint32_t FakeLogThreadId() { return 1; }

static uint32_t g_uCurrent = 1;      // current thread
static uint32_t g_uOther = 7;        // what GetThreadId answers
static uint32_t g_uWait = kThreadWaitTimeout;
static uint32_t g_uResume = 1;
static uint32_t g_uLastError = 0;
static uintptr_t g_uBeginRet = 0x500;
static unsigned g_uBeginId = 55;
static unsigned g_uBeginFlags = 999;
static int g_nErrno = 0;
static int g_nCreateEventFail = 0;
static int g_nEvents = 0, g_nSetEvents = 0, g_nCloses = 0, g_nResumes = 0, g_nWaits = 0;
static uint32_t g_uWaitArg = 0;
static std::vector<void*> g_vClosed;

static uint32_t FGetCurrent() { return g_uCurrent; }
static uint32_t FGetThreadId(void* h) { return h == (void*)0x500 ? g_uOther : 0; }
static bool FClose(void* h) { ++g_nCloses; g_vClosed.push_back(h); return true; }
static void* FCreateEvent() {
    ++g_nEvents;
    return g_nCreateEventFail ? nullptr : (void*)0x900;
}
static bool FSetEvent(void*) { ++g_nSetEvents; return true; }
static uint32_t FWait(void*, uint32_t uMs) { ++g_nWaits; g_uWaitArg = uMs; return g_uWait; }
static uint32_t FResume(void*) { ++g_nResumes; return g_uResume; }
static uint32_t FLastError() { return g_uLastError; }
static uintptr_t FBegin(uint32_t (*)(void*), void*, unsigned uFlags, unsigned* puId) {
    g_uBeginFlags = uFlags;
    if (puId) *puId = g_uBeginId;
    return g_uBeginRet;
}
static int FErrno() { return g_nErrno; }

// the run hooks a subclass would give
static int g_nOnInit = 0, g_nOnDestroy = 0, g_nRun = 0;
static bool g_bRunAnswer = true;
static void* g_pOnInitThis = nullptr;
static void HookOnInit(CThreadBase* p) { ++g_nOnInit; g_pOnInitThis = p; }
static void HookOnDestroy(CThreadBase* p) { ++g_nOnDestroy; (void)p; }
static bool HookRun(CThreadBase*) { ++g_nRun; return g_bRunAnswer; }
static const CThreadVt g_TestVt = { nullptr, HookOnDestroy, HookOnInit, HookRun };

static void Reset() {
    g_vTexts.clear(); g_vFiles.clear();
    g_nEvents = g_nSetEvents = g_nCloses = g_nResumes = g_nWaits = 0;
    g_nCreateEventFail = 0; g_uWait = kThreadWaitTimeout; g_uResume = 1;
    g_uBeginRet = 0x500; g_uBeginId = 55; g_uBeginFlags = 999;
    g_uLastError = 0; g_nErrno = 0; g_uWaitArg = 0; g_vClosed.clear();
    g_nOnInit = g_nOnDestroy = g_nRun = 0; g_bRunAnswer = true; g_pOnInitThis = nullptr;
}
static bool SawText(const char* psz) {
    for (auto& s : g_vTexts) if (s.find(psz) != std::string::npos) return true;
    return false;
}

int main() {
    g_LogApi.pfnIsThreadRunning = FakeRunning;
    g_LogApi.pfnWriteDirect = FakeWrite;
    g_LogApi.pfnPostToThread = FakePost;
    g_LogApi.pfnGetCurrentThreadId = FakeLogThreadId;
    g_pszSysLogFile = (char*)"syslog/syslog";
    g_ThreadApi.pfnGetCurrentThreadId = FGetCurrent;
    g_ThreadApi.pfnGetThreadId = FGetThreadId;
    g_ThreadApi.pfnCloseHandle = FClose;
    g_ThreadApi.pfnCreateEvent = FCreateEvent;
    g_ThreadApi.pfnSetEvent = FSetEvent;
    g_ThreadApi.pfnWaitForSingleObject = FWait;
    g_ThreadApi.pfnResumeThread = FResume;
    g_ThreadApi.pfnGetLastError = FLastError;
    g_ThreadApi.pfnBeginThreadEx = FBegin;
    g_ThreadApi.pfnGetErrno = FErrno;

    // ---- the object as built
    {
        CThreadBase obj;
        assert(obj.pVt == &g_CThreadBaseVt);
        assert(obj.hThread == nullptr && obj.hCloseEvent == nullptr);
        assert(obj.strName.empty());
        assert(g_CThreadBaseVt.pfnOnDestroy == CThreadBaseOnDestroy);
        assert(g_CThreadBaseVt.pfnOnInit == CThreadBaseOnInit);
        assert(g_CThreadBaseVt.pfnSlot00 == nullptr && g_CThreadBaseVt.pfnRun == nullptr);
        // the base hooks answer nothing at all
        CThreadBaseOnInit(&obj);
        CThreadBaseOnDestroy(&obj);
        assert(obj.GetThreadHandle() == nullptr);
        Reset();
        assert(obj.ResumeThread() == false && g_nResumes == 0);
        assert(obj.CloseThread(1000) == true);      // nothing to close, no log
        assert(g_vTexts.empty() && g_nCloses == 0);
    }
    // the destructor of a bare object does nothing either
    {
        Reset();
        { CThreadBase obj; }
        assert(g_vTexts.empty() && g_nCloses == 0 && g_nWaits == 0);
    }

    // ---- CreateThread: a name is required
    {
        Reset();
        CThreadBase obj;
        assert(obj.CreateThread(nullptr, true) == false);
        assert(g_vTexts.size() == 1);
        assert(g_vTexts[0] == "   1 ERROR: thread 1 cannot create thread without a name");
        assert(g_nEvents == 0 && obj.hThread == nullptr);
    }
    // ---- CreateThread: over an existing thread, both names in the line
    {
        Reset();
        CThreadBase obj;
        obj.hThread = (void*)0x500;
        obj.strName = "old";
        assert(obj.CreateThread("new", true) == false);
        assert(g_vTexts[0] ==
               "   1 ERROR: thread 1 cannot create thread \"new\" over thread 7 \"old\"");
        assert(g_nEvents == 0);
    }
    // ---- CreateThread: the event fails, and no name is taken before it works
    {
        Reset();
        CThreadBase obj;
        g_nCreateEventFail = 1; g_uLastError = 1234;
        assert(obj.CreateThread("worker", true) == false);
        assert(g_vTexts[0] ==
               "   1 ERROR: thread 1 cannot create event for thread \"worker\" with error 1234");
        assert(obj.strName.empty() && obj.hThread == nullptr);
        assert(g_nCloses == 0);
    }
    // ---- CreateThread: running, then suspended
    {
        Reset();
        CThreadBase obj;
        assert(obj.CreateThread("worker", true) == true);
        assert(g_uBeginFlags == 0);                 // running hands no CREATE_SUSPENDED
        assert(obj.hThread == (void*)0x500 && obj.hCloseEvent == (void*)0x900);
        assert(obj.strName == "worker");
        assert(g_vTexts[0] == "   1 Message: thread 1 created running thread 55 \"worker\"");

        Reset();
        CThreadBase obj2;
        assert(obj2.CreateThread("sleeper", false) == true);
        assert(g_uBeginFlags == kThreadCreateSuspended);
        assert(g_vTexts[0] == "   1 Message: thread 1 created suspended thread 55 \"sleeper\"");
    }
    // ---- CreateThread: the thread itself fails, the event is taken back down
    {
        Reset();
        CThreadBase obj;
        g_uBeginRet = 0; g_nErrno = 22;
        assert(obj.CreateThread("doomed", true) == false);
        assert(obj.hThread == nullptr && obj.hCloseEvent == nullptr);
        assert(obj.strName == "doomed");            // the name was already taken
        assert(g_vTexts[0] ==
               "   1 ERROR: thread 1 cannot create thread \"doomed\" with error 22");
        assert(g_nCloses == 1 && g_vClosed[0] == (void*)0x900);
    }

    // ---- ThreadProc: the close event stays quiet, the run hook says stop
    {
        Reset();
        CThreadBase obj;
        obj.pVt = &g_TestVt;
        obj.strName = "runner";
        g_bRunAnswer = false;                       // stops on the first ask
        uint32_t uCode = obj.ThreadProc();
        assert(uCode == 2);
        assert(g_nOnInit == 1 && g_pOnInitThis == &obj);   // OnInit first, on this object
        assert(g_nRun == 1 && g_nOnDestroy == 1);
        assert(g_nWaits == 1 && g_uWaitArg == 0);   // polled, never waited on
        assert(g_vTexts.size() == 3);
        assert(g_vTexts[0] == "   1 Message: thread 1 \"runner\" is up and running");
        assert(g_vTexts[1] == "   1 Message: thread 1 \"runner\" is exiting with code 2");
        assert(g_vTexts[2] == "   1 Message: thread 1 \"runner\" exited with code 2");
        // the same body through the thread entry point
        Reset();
        g_bRunAnswer = false;      // the same loop, so it must be told to stop
        obj.strName = "entry";
        assert(CThreadBase::TrueThreadProc(&obj) == 2);
        assert(g_nOnInit == 1 && g_nOnDestroy == 1);
    }
    // ---- ThreadProc: the exit event was raised, so nothing runs and code is 0
    {
        Reset();
        CThreadBase obj;
        obj.pVt = &g_TestVt;
        obj.strName = "leaving";
        g_uWait = kThreadWaitObject;                // the event is already signalled
        assert(obj.ThreadProc() == 0);
        assert(g_nOnInit == 1 && g_nRun == 0 && g_nOnDestroy == 1);
        assert(g_vTexts[1] == "   1 Message: thread 1 \"leaving\" is exiting with code 0");
    }
    // ---- ThreadProc: the hook says go twice, then stop
    {
        Reset();
        CThreadBase obj;
        obj.pVt = &g_TestVt;
        obj.strName = "looper";
        g_uWait = kThreadWaitTimeout;
        static int s_nCalls = 0;
        s_nCalls = 0;
        struct Local {
            static bool RunTwice(CThreadBase*) { return ++s_nCalls < 3; }
        };
        const CThreadVt vt = { nullptr, HookOnDestroy, HookOnInit, &Local::RunTwice };
        obj.pVt = &vt;
        assert(obj.ThreadProc() == 2);
        assert(s_nCalls == 3 && g_nWaits == 3);
    }

    // ---- CloseThread: a thread that is this very thread just raises the event
    {
        Reset();
        CThreadBase obj;
        obj.hThread = (void*)0x500;
        obj.hCloseEvent = (void*)0x900;
        obj.strName = "self";
        g_uCurrent = g_uOther;                      // we are that thread
        assert(obj.CloseThread(1000) == true);
        assert(g_nSetEvents == 1 && g_nResumes == 0 && g_nCloses == 0 && g_nWaits == 0);
        assert(obj.hThread == (void*)0x500);        // nothing cleared
        assert(g_vTexts[0] == "   1 Message: thread 7 \"self\" set close event for itself ...");
        g_uCurrent = 1;
    }
    // ---- CloseThread: another thread that answers in time
    {
        Reset();
        CThreadBase obj;
        obj.hThread = (void*)0x500;
        obj.hCloseEvent = (void*)0x900;
        obj.strName = "worker";
        g_uWait = kThreadWaitObject;
        assert(obj.CloseThread(2500) == true);
        assert(g_nResumes == 1 && g_nSetEvents == 1 && g_uWaitArg == 2500);
        assert(obj.hThread == nullptr && obj.hCloseEvent == nullptr && obj.strName.empty());
        assert(g_nCloses == 2);                     // the thread, then the event
        assert(g_vTexts.size() == 2);
        assert(SawText("is trying to close thread 7 \"worker\" in 2500 ms ..."));
        assert(SawText("successfully closed thread 7 \"worker\" in 2500 ms"));
    }
    // ---- CloseThread: a timeout reports and keeps both handles
    {
        Reset();
        CThreadBase obj;
        obj.hThread = (void*)0x500;
        obj.hCloseEvent = (void*)0x900;
        obj.strName = "stuck";
        g_uWait = kThreadWaitTimeout;
        assert(obj.CloseThread(1000) == false);
        assert(obj.hThread == (void*)0x500 && obj.hCloseEvent == (void*)0x900);
        assert(g_nCloses == 0 && obj.strName == "stuck");
        assert(g_vTexts[1] == "   1 ERROR: thread 1 cannot close thread 7 \"stuck\"");
    }
    // ---- CloseThread: a real failure reports the error
    {
        Reset();
        CThreadBase obj;
        obj.hThread = (void*)0x500;
        obj.hCloseEvent = (void*)0x900;
        obj.strName = "broken";
        g_uWait = kThreadWaitFailed; g_uLastError = 6;
        assert(obj.CloseThread(1000) == false);
        assert(g_vTexts[1] ==
               "   1 ERROR: thread 1 cannot close thread 7 \"broken\" with error 6");
        assert(g_nCloses == 0);
    }

    // ---- ResumeThread: the four answers
    {
        Reset();
        CThreadBase obj;
        obj.hThread = (void*)0x500;
        obj.strName = "w";
        g_uResume = 0;
        assert(obj.ResumeThread() == true);         // not suspended is still true
        assert(SawText("but it was not suspended"));
        Reset(); obj.strName = "w";
        g_uResume = 1;
        assert(obj.ResumeThread() == true);
        assert(SawText("and it was restarted"));
        Reset(); obj.strName = "w";
        g_uResume = 0xffffffff;
        assert(obj.ResumeThread() == false);
        assert(SawText("cannot resume thread 7 \"w\""));
        Reset(); obj.strName = "w";
        g_uResume = 3;                              // anything else is quiet
        assert(obj.ResumeThread() == true);
        assert(g_vTexts.empty());
    }

    // ---- the destructor: it waits without a bound and closes both handles
    {
        Reset();
        g_uWait = kThreadWaitObject;
        {
            CThreadBase obj;
            obj.hThread = (void*)0x500;
            obj.hCloseEvent = (void*)0x900;
            obj.strName = "dying";
        }
        assert(g_uWaitArg == kThreadWaitInfinite);
        assert(g_nCloses == 2);
        assert(g_vTexts.size() == 2);
        assert(g_vTexts[0] ==
               "   1 ERROR: thread 1 is waiting for thread 7 \"dying\" to finish ...");
        assert(g_vTexts[1] ==
               "   1 Message: thread 1 continues after thread 7 \"dying\" finished");
    }
    // ---- the destructor: a wait that fails reports the error and still closes
    {
        Reset();
        g_uWait = kThreadWaitFailed; g_uLastError = 9;
        {
            CThreadBase obj;
            obj.hThread = (void*)0x500;
            obj.hCloseEvent = (void*)0x900;
            obj.strName = "dying2";
        }
        assert(g_vTexts[1] ==
               "   1 ERROR: thread 1 cannot wait for thread 7 \"dying2\" to finish with error 9");
        assert(g_nCloses == 2);
    }

    g_pszSysLogFile = nullptr;
    printf("CQBASE_D14_OK: CThreadBase create/run/close/wait, 20 checks\n");
    return 0;
}

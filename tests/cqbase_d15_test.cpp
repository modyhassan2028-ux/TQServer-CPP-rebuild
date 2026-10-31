// D15 (CQBase) — CThreadTimesInfo: the two word handle and its pimpl contract
#include "modules/cqbase/src/threadtimesinfo.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include "modules/cqbase/src/logkernel.h"
using namespace tq;

static std::vector<std::string> g_vLogged;
static std::vector<std::string> g_vLogFiles;
static bool FakeRunning() { return false; }
static void FakeWrite(const char* pszFile, const char* pszText, int) {
    g_vLogFiles.push_back(pszFile ? pszFile : "<null>");
    g_vLogged.push_back(pszText ? pszText : "<null>");
}
static void FakePost(void*, const char*, const char*, int) {}
static uint32_t FakeLogThreadId() { return 1; }
static bool SawLog(const char* psz) {
    for (auto& t : g_vLogged) if (t.find(psz) != std::string::npos) return true;
    return false;
}

static int g_nNews = 0;
static int g_nDeletes = 0;
static void* g_pDeleted = nullptr;
static int g_nDeletedArg = 0;
static char g_Base[64];                 // stands in for the 0x50 byte object

static void DeletingDtor(void* p, int nFlag) {
    ++g_nDeletes; g_pDeleted = p; g_nDeletedArg = nFlag;
}
static void* const* BaseTable() {
    static void* s_table[1] = {(void*)DeletingDtor};
    return s_table;
}
static void* FakeNew() {
    ++g_nNews;
    *(void**)g_Base = (void*)BaseTable();
    return g_Base;
}
static void* FakeNewFails() { ++g_nNews; return nullptr; }

// ---- the clock seams
static uint64_t g_uProcKernel = 20000, g_uProcUser = 10000;
static int g_nProcFail = 0;
static uint32_t g_uTick = 777;
static uint32_t g_uThreadIdAnswer = 42;
static uint64_t g_uThreadKernel = 90000, g_uThreadUser = 30000;
static int g_nThreadTimesFail = 0;
static int g_nGetThreadIdCalls = 0, g_nGetThreadTimesCalls = 0;
static void* g_pProcess = (void*)0xBEEF;
static void* FGetCurrentProcess() { return g_pProcess; }
static bool FGetProcessTimes(void*, uint64_t* c, uint64_t* e, uint64_t* k, uint64_t* u) {
    *c = 1; *e = 2;
    if (g_nProcFail) { *k = 12345; *u = 67890; return false; }   // whatever the ask leaves
    *k = g_uProcKernel; *u = g_uProcUser;
    return true;
}
static uint32_t FGetTickCount() { return g_uTick; }
static uint32_t FGetThreadIdTimes(void* h) {
    ++g_nGetThreadIdCalls;
    if (h == (void*)0x2222) return 0;      // the handle that has no thread id
    return g_uThreadIdAnswer;
}
static bool FGetThreadTimes(void*, uint64_t* c, uint64_t* e, uint64_t* k, uint64_t* u) {
    ++g_nGetThreadTimesCalls;
    *c = 3; *e = 4; *k = g_uThreadKernel; *u = g_uThreadUser;
    return g_nThreadTimesFail == 0;
}

int main() {
    g_LogApi.pfnIsThreadRunning = FakeRunning;
    g_LogApi.pfnWriteDirect = FakeWrite;
    g_LogApi.pfnPostToThread = FakePost;
    g_LogApi.pfnGetCurrentThreadId = FakeLogThreadId;
    g_pszSysLogFile = (char*)"syslog/syslog";
    g_ThreadTimesApi.pfnGetCurrentProcess = FGetCurrentProcess;
    g_ThreadTimesApi.pfnGetProcessTimes = FGetProcessTimes;
    g_ThreadTimesApi.pfnGetTickCount = FGetTickCount;
    g_ThreadTimesApi.pfnGetThreadId = FGetThreadIdTimes;
    g_ThreadTimesApi.pfnGetThreadTimes = FGetThreadTimes;

    // ---- Init: the process sample, the tick, then every thread in the list
    {
        g_vLogged.clear(); g_nProcFail = 0; g_nThreadTimesFail = 0;
        g_nGetThreadIdCalls = 0; g_nGetThreadTimesCalls = 0;
        CThreadTimesInfoBase base;
        // an empty handle and -1 are skipped without even asking for an id
        base.vSamples.push_back(CThreadTimesSample{nullptr, 7, 8});
        base.vSamples.push_back(CThreadTimesSample{(void*)(intptr_t)-1, 9, 10});
        // a handle with no thread id is skipped after the id ask
        g_uThreadIdAnswer = 0;
        base.vSamples.push_back(CThreadTimesSample{(void*)0x2222, 1, 2});
        // the id comes back, so the times are asked for
        g_uThreadIdAnswer = 42;
        base.vSamples.push_back(CThreadTimesSample{(void*)0x3333, 0, 0});
        assert(base.Init() == true);
        assert(base.hProcess == g_pProcess);
        assert(base.uProcessKernelMs == 2 && base.uProcessUserMs == 1);   // 20000/10000, 10000/10000
        assert(base.uTickCount == 777 && base.uInited == 1);
        assert(g_nGetThreadIdCalls == 2);          // only the two real handles
        assert(g_nGetThreadTimesCalls == 1);
        assert(base.vSamples[0].uKernelMs == 7 && base.vSamples[0].uUserMs == 8);   // untouched
        assert(base.vSamples[1].uKernelMs == 9 && base.vSamples[1].uUserMs == 10);
        assert(base.vSamples[2].uKernelMs == 1 && base.vSamples[2].uUserMs == 2);
        assert(base.vSamples[3].uKernelMs == 9 && base.vSamples[3].uUserMs == 3);   // 90000, 30000
        assert(SawLog("ThreadTimesInfo Init ok."));
        assert(g_vLogFiles.back() == "syslog/thread");
    }
    // ---- Init: a refused process ask reports and still leaves zeroed numbers
    {
        g_vLogged.clear(); g_nProcFail = 1; g_nThreadTimesFail = 1;
        g_nGetThreadTimesCalls = 0;
        CThreadTimesInfoBase base;
        base.vSamples.push_back(CThreadTimesSample{(void*)0x3333, 5, 6});
        assert(base.Init() == true);
        // a refused ask still stores whatever the out parameters hold, exactly as the
        // original does with its uninitialised stack pair
        assert(base.uProcessKernelMs == 1 && base.uProcessUserMs == 6);
        assert(base.uTickCount == 777 && base.uInited == 1);
        assert(SawLog("CThreadTimesInfoBase::Init GetProcessTimes failed."));
        // the thread ask failed too: the sample keeps what it had and the id is named
        assert(base.vSamples[0].uKernelMs == 5 && base.vSamples[0].uUserMs == 6);
        assert(SawLog("CThreadTimesInfoBase::Start GetThreadTimes failed.Thread id 42"));
        assert(g_nGetThreadTimesCalls == 1);
        g_nProcFail = 0; g_nThreadTimesFail = 0;
    }
    // ---- the real measuring object: table, zeroed fields, 16 byte samples
    {
        g_pfnNewThreadTimesInfoBase = CThreadTimesInfoBaseNew;
        assert(sizeof(CThreadTimesSample) == 16);
        assert(CThreadTimesInfoBase::Table()[0] ==
               (const void*)&CThreadTimesInfoBaseDeletingDtor);
        CThreadTimesInfo obj;
        assert(obj.pBase != nullptr);
        CThreadTimesInfoBase* pB = (CThreadTimesInfoBase*)obj.pBase;
        assert(pB->pVt == (const void*)CThreadTimesInfoBase::Table());
        assert(pB->vSamples.empty());
        assert(pB->uField28 == 0 && pB->uField30 == 0 && pB->hProcess == nullptr);
        assert(pB->uProcessUserMs == 0 && pB->uProcessKernelMs == 0);
        assert(pB->uTickCount == 0 && pB->uInited == 0);
        pB->vSamples.push_back(CThreadTimesSample{(void*)0x1234, 11, 22});
        assert(pB->vSamples.size() == 1 && pB->vSamples[0].uKernelMs == 11);
        assert(pB->vSamples[0].uUserMs == 22 && pB->vSamples[0].hThread == (void*)0x1234);
        // flag 0 destroys without freeing, so the table can be read back
        void* pRaw = obj.pBase;
        assert(CThreadTimesInfoBaseDeletingDtor(pRaw, 0) == pRaw);
        assert(((CThreadTimesInfoBase*)pRaw)->pVt ==
               (const void*)CThreadTimesInfoBase::Table());
        obj.pBase = nullptr;            // the handle must not destroy it a second time
        operator delete(pRaw);          // the caller frees what flag 0 left behind
        // flag 1 frees as well, and the pointer is not touched afterwards
        CThreadTimesInfoBaseDeletingDtor(CThreadTimesInfoBaseNew(), 1);
    }
    // ---- an empty seam behaves like a failed allocation
    {
        g_pfnNewThreadTimesInfoBase = FakeNewFails;
        CThreadTimesInfo obj;
        assert(obj.pVt != nullptr);
        assert(obj.pBase == nullptr);
        assert(g_nNews == 1);
        // the destructor of an empty handle calls nothing
        g_nDeletes = 0; g_pDeleted = nullptr;
        { CThreadTimesInfo inner; }
        assert(g_nDeletes == 0);
    }
    // ---- a real handle builds a measuring object and releases it with (this, 1)
    {
        g_pfnNewThreadTimesInfoBase = FakeNew;
        g_nNews = 0; g_nDeletes = 0; g_pDeleted = nullptr; g_nDeletedArg = 0;
        {
            CThreadTimesInfo obj;
            assert(g_nNews == 1);
            assert(obj.pBase == (void*)g_Base);
            assert(obj.pVt != nullptr);   // the handle carries its own table
        }
        assert(g_nDeletes == 1);
        assert(g_pDeleted == (void*)g_Base);
        assert(g_nDeletedArg == 1);
    }
    // ---- the handle is cleared by its own destructor
    {
        g_pfnNewThreadTimesInfoBase = FakeNew;
        CThreadTimesInfo obj;
        void* pKeep = obj.pBase;
        g_nDeletes = 0;
        obj.~CThreadTimesInfo();
        assert(g_nDeletes == 1 && g_pDeleted == pKeep);
        assert(obj.pBase == nullptr);
        // a second destruction of the cleared handle calls nothing
        obj.~CThreadTimesInfo();
        assert(g_nDeletes == 1);
    }
    // ---- the copy shares the measuring object (quirk: both would delete it)
    {
        g_pfnNewThreadTimesInfoBase = FakeNew;
        g_nNews = 0;
        CThreadTimesInfo a;
        assert(g_nNews == 1);
        g_nDeletes = 0;
        {
            CThreadTimesInfo b(a);          // copy constructor
            assert(b.pBase == a.pBase);     // the same 0x50 bytes, not a new object
            assert(g_nNews == 1);
            b.pBase = nullptr;              // disown the share so both do not delete it
        }
        assert(g_nDeletes == 0);
        assert(a.pBase == (void*)g_Base);
        a.pBase = nullptr;
    }
    // ---- operator= overwrites without releasing what was there (quirk: a leak)
    {
        static char s_Other[64];
        struct Local {
            static void* New() { *(void**)s_Other = (void*)BaseTable(); return s_Other; }
        };
        g_pfnNewThreadTimesInfoBase = FakeNew;
        CThreadTimesInfo a;
        void* pFirst = a.pBase;
        assert(pFirst == (void*)g_Base);
        g_pfnNewThreadTimesInfoBase = &Local::New;
        CThreadTimesInfo b;
        assert(b.pBase == (void*)s_Other);
        g_nDeletes = 0;
        a = b;                              // no delete of the first object
        assert(g_nDeletes == 0);
        assert(a.pBase == (void*)s_Other);
        a.pBase = nullptr;
        b.pBase = nullptr;
    }
    // ---- RecordThreadTimesInfo: it stays silent until initialised, then reports
    {
        CThreadTimesInfoBase base;
        base.vSamples.push_back(CThreadTimesSample{(void*)0x3333, 40, 50});
        g_vLogged.clear();
        base.RecordThreadTimesInfo(true);          // not initialised yet
        assert(g_vLogged.empty());

        g_uTick = 1500; g_uProcKernel = 20000; g_uProcUser = 10000;
        g_uThreadKernel = 90000; g_uThreadUser = 30000;
        g_nThreadTimesFail = 0; g_nProcFail = 0;
        g_nGetThreadTimesCalls = 0;
        base.uInited = 1;
        base.uTickCount = 1000;
        base.uProcessKernelMs = 0;
        base.uProcessUserMs = 0;
        base.RecordThreadTimesInfo(true);
        // the banner names the moment, so it must carry a date and a time
        bool bBanner = false;
        for (auto& t : g_vLogged) {
            if (t.find("ThreadTimesInfo [") == std::string::npos) continue;
            bBanner = t.find('-') != std::string::npos && t.find(':') != std::string::npos;
            break;
        }
        assert(bBanner);
        assert(SawLog("Number of Thread: 1"));
        assert(SawLog("Process kernel:"));
        assert(SawLog("thread   42 kernel:"));
        assert(base.uTickCount == 1500);                    // updated
        assert(base.uProcessKernelMs == 2 && base.uProcessUserMs == 1);
        assert(base.vSamples[0].uKernelMs == 9 && base.vSamples[0].uUserMs == 3);
        assert(g_vLogFiles.back() == "syslog/thread");

        // ---- without the update flag nothing is stored, the delta is still reported
        g_vLogged.clear();
        g_uTick = 2500;
        base.RecordThreadTimesInfo(false);
        assert(base.uTickCount == 1500);
        assert(base.uProcessKernelMs == 2 && base.uProcessUserMs == 1);
        assert(base.vSamples[0].uKernelMs == 9 && base.vSamples[0].uUserMs == 3);
        assert(SawLog("Number of Thread: 1"));

        // ---- a clock that did not move forward is reported and becomes the base
        g_vLogged.clear();
        g_uTick = 1200;                                     // less than the stored 1500
        base.RecordThreadTimesInfo(true);
        assert(SawLog("GetTickCount err, new count: 1200, old count: 1500"));
        assert(base.uTickCount == 1200);
        assert(!SawLog("Number of Thread:"));               // the report stops there

        // ---- an empty list is silent even when initialised
        CThreadTimesInfoBase empty;
        empty.uInited = 1;
        g_vLogged.clear();
        empty.RecordThreadTimesInfo(true);
        assert(g_vLogged.empty());
    }

    printf("CQBASE_D15_OK: CThreadTimesInfo handle, measuring object, Init and the report, 8 units, 70 checks\n");
    return 0;
}

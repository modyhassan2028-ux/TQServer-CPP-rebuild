// D16 (CQBase) — CPerformanceInfo: the handle, its quirks and its one forwarder
#include "modules/cqbase/src/performanceinfo.h"
#include <cassert>
#include <cstdio>

using namespace tq;

static int g_nNews = 0;
static int g_nDeletes = 0;
static void* g_pDeleted = nullptr;
static int g_nDeletedFlag = -1;
static char g_Base[64];

static void DeletingDtor(void* p, int nFlag) { ++g_nDeletes; g_pDeleted = p; g_nDeletedFlag = nFlag; }
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
static int g_nRecorded = 0;
static void* g_pRecorded = nullptr;
static void FakeRecord(void* p) { ++g_nRecorded; g_pRecorded = p; }

int main() {
    g_pfnPerformanceInfoBaseRecord = FakeRecord;

    // ---- a null seam behaves like a failed allocation
    {
        g_pfnNewPerformanceInfoBase = FakeNewFails;
        g_nNews = 0;
        CPerformanceInfo obj;
        assert(obj.pVt != nullptr);
        assert(obj.pBase == nullptr);
        assert(g_nNews == 1);
        // the recording call has nothing to forward to
        g_nRecorded = 0;
        obj.RecrodPerformanceInfo();
        assert(g_nRecorded == 0);
    }
    // ---- a real handle builds a measuring object and frees it with (this, 1)
    {
        g_pfnNewPerformanceInfoBase = FakeNew;
        g_nNews = 0; g_nDeletes = 0; g_pDeleted = nullptr; g_nDeletedFlag = -1;
        {
            CPerformanceInfo obj;
            assert(g_nNews == 1 && obj.pBase == (void*)g_Base);
            g_nRecorded = 0;
            obj.RecrodPerformanceInfo();
            assert(g_nRecorded == 1 && g_pRecorded == (void*)g_Base);
        }
        assert(g_nDeletes == 1 && g_pDeleted == (void*)g_Base && g_nDeletedFlag == 1);
    }
    // ---- the destructor leaves its pointer alone, unlike the thread times handle
    {
        g_pfnNewPerformanceInfoBase = FakeNew;
        CPerformanceInfo obj;
        void* pKeep = obj.pBase;
        g_nDeletes = 0;
        obj.~CPerformanceInfo();
        assert(g_nDeletes == 1 && g_pDeleted == pKeep);
        assert(obj.pBase == pKeep);          // NOT cleared: the raw does not touch it
    }
    // ---- the copy shares the measuring object
    {
        g_pfnNewPerformanceInfoBase = FakeNew;
        g_nNews = 0;
        CPerformanceInfo a;
        assert(g_nNews == 1);
        g_nDeletes = 0;
        {
            CPerformanceInfo b(a);
            assert(b.pBase == a.pBase && g_nNews == 1);
            b.pBase = nullptr;               // disown the share
        }
        assert(g_nDeletes == 0 && a.pBase == (void*)g_Base);
        a.pBase = nullptr;
    }
    // ---- operator= overwrites without releasing what was there
    {
        static char s_Other[64];
        struct Local { static void* New() { *(void**)s_Other = (void*)BaseTable(); return s_Other; } };
        g_pfnNewPerformanceInfoBase = FakeNew;
        CPerformanceInfo a;
        assert(a.pBase == (void*)g_Base);
        g_pfnNewPerformanceInfoBase = &Local::New;
        CPerformanceInfo b;
        assert(b.pBase == (void*)s_Other);
        g_nDeletes = 0;
        a = b;
        assert(g_nDeletes == 0 && a.pBase == (void*)s_Other);
        a.pBase = nullptr;
        b.pBase = nullptr;
    }
    printf("CQBASE_D16_OK: CPerformanceInfo handle, 5 units, 16 checks\n");
    return 0;
}

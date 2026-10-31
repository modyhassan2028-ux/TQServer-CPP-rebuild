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

    // ---- the measuring object builds, links its two lists, and frees in order
    {
        static int nFreedLibrary = 0, nClosed = 0, nClear = 0, nFinal = 0, nFreeCalls = 0;
        static void* pFreedList = nullptr;
        struct Api {
            static void* Alloc(size_t n) { return ::operator new(n); }
            static void Free(void* p) { ++nFreeCalls; ::operator delete(p); }
            static int FreeLibrary(void*) { ++nFreedLibrary; return 1; }
            static int CloseQuery(void*) { ++nClosed; return 0; }
            static void Clear(void* p) {
                ++nClear;
                pFreedList = p;
                // stands in for the unported teardown: release the sentinel node
                CPerformanceList* pL = (CPerformanceList*)p;
                if (pL->pHead != nullptr) { Free(pL->pHead); pL->pHead = nullptr; }
            }
            static void Final(void* p) { ++nFinal; pFreedList = p; }
        };
        PerformanceInfoApi saved = g_PerformanceInfoApi;
        g_PerformanceInfoApi = {&Api::Alloc, &Api::Free, &Api::FreeLibrary, &Api::CloseQuery,
                                &Api::Clear, &Api::Final};
        {
            CPerformanceInfoBase base;
            assert(base.pVt == (const void*)CPerformanceInfoBase::Table());
            assert(CPerformanceInfoBase::Table()[0] ==
                   (const void*)&CPerformanceInfoBaseDeletingDtor);
            assert(base.hQuery == nullptr && base.pA0 == nullptr && base.pA8 == nullptr);
            assert(base.uC0 == 1);                 // the dword after it is never written
            assert(base.u148 == 0);
            // both lists got a proxy and a self linked sentinel
            CPerformanceList* pA = base.ListA();
            CPerformanceList* pB = base.ListB();
            assert(pA->pProxy != nullptr && pB->pProxy != nullptr);
            assert(*(void**)pA->pProxy == (void*)pA && *(void**)pB->pProxy == (void*)pB);
            assert(pA->nCount == 0 && pB->nCount == 0);
            assert(((CPerformanceNode50*)pA->pHead)->uFlag49 == 1);
            assert(((CPerformanceNode50*)pA->pHead)->p0 == pA->pHead);
            assert(((CPerformanceNode278*)pB->pHead)->uFlag271 == 1);
            assert(((CPerformanceNode278*)pB->pHead)->p2 == pB->pHead);
            base.hModule1 = (void*)0x1;
            base.hModule2 = (void*)0x2;
            base.hQuery = (void*)0x3;
            nFreedLibrary = nClosed = nClear = nFinal = nFreeCalls = 0;
        }
        // FreeLibrary twice, then the query, then B before A, two steps each
        assert(nFreedLibrary == 2 && nClosed == 1);
        assert(nClear == 2 && nFinal == 2);
        assert(nFreeCalls == 4);        // two sentinel nodes then two proxies
        // the object's table slot frees only when the flag asks
        {
            void* pRaw = CPerformanceInfoBaseNew();
            assert(pRaw != nullptr);
            nClear = nFinal = nFreeCalls = 0;
            assert(CPerformanceInfoBaseDeletingDtor(pRaw, 0) == pRaw);
            assert(nClear == 2 && nFinal == 2);
        assert(nFreeCalls == 4);        // two sentinel nodes then two proxies   // proxies only
            operator delete(pRaw);                                    // flag 0 left it alive
            nFreeCalls = 0;
            CPerformanceInfoBaseDeletingDtor(CPerformanceInfoBaseNew(), 1);
            // the two proxies go through the seam; the object itself is released with the
            // plain operator delete the raw calls directly
            assert(nFreeCalls == 4);
        }
        g_PerformanceInfoApi = saved;
    }
    // ---- the handle's default seam now builds the real measuring object
    {
        g_pfnNewPerformanceInfoBase = CPerformanceInfoBaseNew;
        CPerformanceInfo obj;
        assert(obj.pBase != nullptr);
        CPerformanceInfoBase* pB = (CPerformanceInfoBase*)obj.pBase;
        assert(pB->pVt == (const void*)CPerformanceInfoBase::Table());
        assert(pB->ListA()->nCount == 0 && pB->ListB()->nCount == 0);
    }

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
    printf("CQBASE_D16_OK: CPerformanceInfo handle and measuring object, 12 units, 38 checks\n");
    return 0;
}

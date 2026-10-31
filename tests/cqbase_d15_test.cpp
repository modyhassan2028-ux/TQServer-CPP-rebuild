// D15 (CQBase) — CThreadTimesInfo: the two word handle and its pimpl contract
#include "modules/cqbase/src/threadtimesinfo.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace tq;

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

int main() {
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
        assert(pB->uField28 == 0 && pB->uField30 == 0 && pB->uField38 == 0);
        assert(pB->uField40 == 0 && pB->uField44 == 0 && pB->uField48 == 0);
        assert(pB->uField4C == 0);
        pB->vSamples.push_back(CThreadTimesSample{11, 22});
        assert(pB->vSamples.size() == 1 && pB->vSamples[0].uField08 == 22);
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
    printf("CQBASE_D15_OK: CThreadTimesInfo handle and measuring object, 6 units, 33 checks\n");
    return 0;
}

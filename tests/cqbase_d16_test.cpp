// D16 (CQBase) — CPerformanceInfo: the handle, its quirks and its one forwarder
#include "modules/cqbase/src/performanceinfo.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <string>

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

    // ---- the layout the binary has: 0x150 bytes, every named field where it belongs
    {
        static_assert(sizeof(CPerformanceInfoBase) == 0x150, "measuring object is 0x150");
        static_assert(sizeof(CPerformanceList) == 0x40, "a list is 0x40");
        static_assert(sizeof(CPerformanceNode50) == 0x50, "node A is 0x50");
        static_assert(sizeof(CPerformanceNode278) == 0x278, "node B is 0x278");
        static_assert(offsetof(CPerformanceInfoBase, hQuery) == 0x08, "query handle at 0x08");
        static_assert(offsetof(CPerformanceInfoBase, pA0) == 0xA0, "export A at 0xA0");
        static_assert(offsetof(CPerformanceInfoBase, pA8) == 0xA8, "export B at 0xA8");
        static_assert(offsetof(CPerformanceInfoBase, hModule1) == 0xB0, "module 1 at 0xB0");
        static_assert(offsetof(CPerformanceInfoBase, uC0) == 0xC0, "count at 0xC0");
        static_assert(offsetof(CPerformanceInfoBase, listA) == 0xC8, "list A at 0xC8");
        static_assert(offsetof(CPerformanceInfoBase, listB) == 0x108, "list B at 0x108");
        static_assert(offsetof(CPerformanceInfoBase, u148) == 0x148, "last field at 0x148");
        static_assert(offsetof(CPerformanceList, pHead) == 0x30, "sentinel at 0x30");
        static_assert(offsetof(CPerformanceList, nCount) == 0x38, "count at 0x38");
        assert(sizeof(CPerformanceInfo) == 16);
    }
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
    // ---- Init: the name is borrowed, the two libraries are asked by name, and only a
    //      library that loaded hands over its export
    {
        static std::string g_sLibs, g_sProcs, g_sLogs;
        static void* g_pSetup = nullptr;
        static void* const hNtdll = (void*)0xAA;
        static void* const hKernel = (void*)0xBB;
        static int nLoadFails = 0;
        struct Api {
            static void* Alloc(size_t n) { return ::operator new(n); }
            static void Free(void* p) { ::operator delete(p); }
            static int FreeLibrary(void*) { return 1; }
            static int CloseQuery(void*) { return 0; }
            static void Clear(void* p) {
                CPerformanceList* pL = (CPerformanceList*)p;
                if (pL->pHead) { Free(pL->pHead); pL->pHead = nullptr; }
            }
            static void Final(void*) {}
            static void* LoadLibraryA(const char* psz) {
                g_sLibs += psz; g_sLibs += '|';
                if (nLoadFails && std::string(psz) == "Ntdll.dll") return nullptr;
                if (std::string(psz) == "Ntdll.dll") return hNtdll;
                if (std::string(psz) == "Kernel32.dll") return hKernel;
                return nullptr;
            }
            static void* GetProcAddress(void* h, const char* psz) {
                g_sProcs += psz; g_sProcs += '|';
                if (h == hNtdll && std::string(psz) == "NtQuerySystemInformation") return (void*)0x101;
                if (h == hKernel && std::string(psz) == "GlobalMemoryStatusEx") return (void*)0x202;
                return nullptr;
            }
            static void GetSystemInfo(uint32_t* pCount) { *pCount = 8; }
            static void Setup(void* p) { g_pSetup = p; }
            static void Log(void*, const char* psz) { g_sLogs += psz; }
        };
        PerformanceInfoApi saved = g_PerformanceInfoApi;
        g_PerformanceInfoApi = {&Api::Alloc, &Api::Free, &Api::FreeLibrary, &Api::CloseQuery,
                                &Api::Clear, &Api::Final, &Api::LoadLibraryA,
                                &Api::GetProcAddress, &Api::GetSystemInfo, &Api::Setup,
                                &Api::Log};
        const char szName[] = "server";
        CPerformanceInfoBase base;
        nLoadFails = 0; g_sLibs.clear(); g_sProcs.clear(); g_sLogs.clear();
        g_pSetup = nullptr;
        base.Init(szName);
        assert(g_sLibs == "Ntdll.dll|Kernel32.dll|");
        assert(g_sProcs == "NtQuerySystemInformation|GlobalMemoryStatusEx|");
        assert(base.hModule1 == hNtdll && base.hModule2 == hKernel);
        assert(base.pA0 == (void*)0x101 && base.pA8 == (void*)0x202);
        assert(base.u148 == (uint64_t)(uintptr_t)szName);      // borrowed, not copied
        assert(base.uC0 == 8);                                 // replaces the constructor's one
        assert(g_pSetup == (void*)&base);
        assert(g_sLogs == "Performance initialize success !");
        // a library that refuses to load leaves the export exactly as it was
        base.pA0 = (void*)0x77;
        nLoadFails = 1;
        g_sProcs.clear();
        base.Init(szName);
        assert(base.pA0 == (void*)0x77);
        assert(g_sProcs == "GlobalMemoryStatusEx|");           // only Kernel32 was asked
        nLoadFails = 0;
        g_PerformanceInfoApi = saved;
    }
    // ---- the handle's Init forwards only when it has a measuring object
    {
        CPerformanceInfoBase* pReal = (CPerformanceInfoBase*)CPerformanceInfoBaseNew();
        static std::string g_sName;
        struct Api {
            static void* Alloc(size_t n) { return ::operator new(n); }
            static void Free(void* p) { ::operator delete(p); }
            static int FreeLibrary(void*) { return 1; }
            static int CloseQuery(void*) { return 0; }
            static void Clear(void* p) {
                CPerformanceList* pL = (CPerformanceList*)p;
                if (pL->pHead) { Free(pL->pHead); pL->pHead = nullptr; }
            }
            static void Final(void*) {}
            static void* LoadLibraryA(const char*) { return nullptr; }
            static void* GetProcAddress(void*, const char*) { return nullptr; }
            static void GetSystemInfo(uint32_t*) {}
            static void Setup(void*) {}
            static void Log(void*, const char* psz) { g_sName = psz; }
        };
        PerformanceInfoApi saved = g_PerformanceInfoApi;
        g_PerformanceInfoApi = {&Api::Alloc, &Api::Free, &Api::FreeLibrary, &Api::CloseQuery,
                                &Api::Clear, &Api::Final, &Api::LoadLibraryA,
                                &Api::GetProcAddress, &Api::GetSystemInfo, &Api::Setup,
                                &Api::Log};
        // a handle that never got an object stays silent
        g_pfnNewPerformanceInfoBase = FakeNewFails;
        CPerformanceInfo none;
        assert(none.pBase == nullptr);
        g_sName.clear();
        none.Init("cfg");
        assert(g_sName.empty());
        // a real handle forwards
        g_pfnNewPerformanceInfoBase = CPerformanceInfoBaseNew;
        CPerformanceInfo obj;
        assert(obj.pBase != nullptr);
        obj.Init("cfg");
        assert(g_sName == "Performance initialize success !");
        g_PerformanceInfoApi = saved;
        CPerformanceInfoBaseDeletingDtor(pReal, 1);
    }

    printf("CQBASE_D16_OK: CPerformanceInfo handle, measuring object and Init, 14 units, 53 checks + 14 layout\n");
    return 0;
}

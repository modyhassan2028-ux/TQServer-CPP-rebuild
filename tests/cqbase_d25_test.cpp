// ============================================================================
// cqbase_d25 — the two initialisers, their teardowns and their frees, checked value by
//   value against the binary's own writes: child order, slots, constants and the raw 64 bit
//   answer the closing tail jump returns.
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"
#include "modules/syndicate/src/synobjects.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

using namespace tq;

// ---- the fake data object model the initialisers talk to through vtable offsets
struct FakeObj {
    void** ppVft;
    int32_t nIndex;
};

static FakeObj g_aChild[16];
static FakeObj g_Root;
static FakeObj g_Manager;
static void* g_aRootVft[24];
static void* g_aChildVft[24];
static void* g_aMgrVft[24];

static std::string g_strCreatedName;
static std::vector<int32_t> g_vChildOrder;
static std::vector<std::pair<int32_t, int32_t> > g_vB0;
static std::vector<std::pair<int32_t, int32_t> > g_vB8;
static std::vector<std::pair<int32_t, void*> > g_vPtr;
static int g_nFinishCalls = 0;
static uint64_t g_uFinishArg = 0;
static uint64_t g_uFinishRet = 0x1122334455667788ull;
static int g_nDestroyCalls = 0;
static uint64_t g_uDestroyA1 = 0, g_uDestroyA4 = 0;
static void* g_pDestroyA2 = nullptr;
static void* g_pDestroyA3 = nullptr;
static int g_nDeleteCalls = 0;
static uint64_t g_uDeleteFlag = 0;
static int g_nHeapFree = 0;
static void* g_pHeapFreed = nullptr;

static void Reset() {
    g_strCreatedName.clear();
    g_vChildOrder.clear();
    g_vB0.clear();
    g_vB8.clear();
    g_vPtr.clear();
    g_nFinishCalls = 0;
    g_uFinishArg = 0;
    g_nDestroyCalls = 0;
    g_uDeleteFlag = 0;
    g_nDeleteCalls = 0;
    g_nHeapFree = 0;
    g_pHeapFreed = nullptr;
}

static void* SlotCreate(void*, const char* pszName) {
    g_strCreatedName = pszName;
    return &g_Root;
}
static void* SlotGetChild(void*, int32_t nIndex) {
    g_vChildOrder.push_back(nIndex);
    return &g_aChild[nIndex];
}
static uint64_t SlotFinish(void*, uint64_t uFlag) {
    ++g_nFinishCalls;
    g_uFinishArg = uFlag;
    return g_uFinishRet;
}
static void SlotSetPtr(void* pSelf, void* pValue) {
    g_vPtr.push_back(std::make_pair(((FakeObj*)pSelf)->nIndex, pValue));
}
static void SlotSetB0(void* pSelf, int32_t nValue) {
    g_vB0.push_back(std::make_pair(((FakeObj*)pSelf)->nIndex, nValue));
}
static void SlotSetB8(void* pSelf, int32_t nValue) {
    g_vB8.push_back(std::make_pair(((FakeObj*)pSelf)->nIndex, nValue));
}
static uint64_t SlotDestroy(void* pSelf, uint64_t uA1, void* pA2, void* pA3, uint64_t uA4) {
    (void)pSelf;
    ++g_nDestroyCalls;
    g_uDestroyA1 = uA1;
    g_pDestroyA2 = pA2;
    g_pDestroyA3 = pA3;
    g_uDestroyA4 = uA4;
    return 0;
}
static uint64_t SlotDelete(void* pSelf, uint64_t uFlag) {
    if (pSelf == (void*)&g_Root) {
        ++g_nDeleteCalls;
        g_uDeleteFlag = uFlag;
    }
    return 0;
}

// the heap the frees go through
static void* HeapCreate(uint32_t, size_t, size_t) { return (void*)1; }
static void* HeapAlloc(void*, uint32_t, size_t uBytes) { return std::calloc(1, uBytes); }
static bool HeapFree(void*, uint32_t, void* pMem) {
    ++g_nHeapFree;
    g_pHeapFreed = pMem;
    std::free(pMem);
    return true;
}
static void LogWrite(const char*, const char*, int) {}
static void LogPost(void*, const char*, const char*, int) {}
static uint32_t LogTid() { return 0x25; }
static bool LogRunning() { return true; }
static bool HeapValid(void*, uint32_t, const void*) { return true; }
static bool HeapDestroy(void*) { return true; }

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    // the reporting seams: a Free on a heap nothing was taken from still logs,
    // straight through to the heap check the way the original does
    tq::g_LogApi.pfnIsThreadRunning = &LogRunning;
    tq::g_LogApi.pfnWriteDirect = &LogWrite;
    tq::g_LogApi.pfnPostToThread = &LogPost;
    tq::g_LogApi.pfnGetCurrentThreadId = &LogTid;
    HeapApi savedHeap = tq::g_HeapApi;
    tq::g_HeapApi = {&HeapCreate, &HeapAlloc, &HeapFree, &HeapValid, &HeapDestroy};

    // ---- the vtable tables at the offsets the binary reads
    g_aRootVft[0x00 / 8] = (void*)&SlotDelete;
    g_aRootVft[0x10 / 8] = (void*)&SlotGetChild;
    g_aRootVft[0x38 / 8] = (void*)&SlotDestroy;
    g_aRootVft[0x50 / 8] = (void*)&SlotFinish;
    g_aRootVft[0x80 / 8] = (void*)&SlotSetPtr;
    g_aRootVft[0xb0 / 8] = (void*)&SlotSetB0;
    g_aRootVft[0xb8 / 8] = (void*)&SlotSetB8;
    for (int i = 0; i < 16; ++i) {
        g_aChildVft[0x00 / 8] = (void*)&SlotDelete;
        g_aChildVft[0xb0 / 8] = (void*)&SlotSetB0;
        g_aChildVft[0xb8 / 8] = (void*)&SlotSetB8;
        g_aChildVft[0x80 / 8] = (void*)&SlotSetPtr;
        g_aChild[i].ppVft = g_aChildVft;
        g_aChild[i].nIndex = i;
    }
    g_aMgrVft[0x20 / 8] = (void*)&SlotCreate;
    g_Root.ppVft = g_aRootVft;
    g_Root.nIndex = -1;
    g_Manager.ppVft = g_aMgrVft;
    g_pfnDbInstanceGet = []() -> void* { return (void*)&g_Manager; };

    static const char kName[] = "HOSTILE";

    // ---- the domain: seven children, in order, with the binary's own constants
    {
        CSynDomain dom;
        std::memset(&dom, 0, sizeof(dom));
        Reset();
        const uint64_t uRet = dom.Init(0x31, kName);

        assert(uRet == 0x1122334455667788ull);          // the tail jump's answer, whole
        assert(g_strCreatedName == "cq_syndomain");
        assert(dom.pInner == (void*)&g_Root);
        assert(g_nFinishCalls == 1 && g_uFinishArg == 1);  // cl(1) closes it

        const int32_t aWant[] = {0, 1, 2, 3, 4, 5, 6};
        assert(g_vChildOrder.size() == 7);
        for (int i = 0; i < 7; ++i) assert(g_vChildOrder[i] == aWant[i]);

        assert(g_vB8.size() == 2);
        assert(g_vB8[0].first == 0 && g_vB8[0].second == 0x31);       // the id
        assert(g_vB8[1].first == 2 && g_vB8[1].second == 930000);

        assert(g_vPtr.size() == 1);
        assert(g_vPtr[0].first == 1 && g_vPtr[0].second == (void*)kName);

        assert(g_vB0.size() == 4);
        assert(g_vB0[0].first == 3 && g_vB0[0].second == 0x100);
        assert(g_vB0[1].first == 4 && g_vB0[1].second == 0xad);
        assert(g_vB0[2].first == 5 && g_vB0[2].second == 5);
        assert(g_vB0[3].first == 6 && g_vB0[3].second == 5);
    }

    // ---- a zero id or a null name answers zero before anything is asked for
    {
        CSynDomain dom;
        std::memset(&dom, 0, sizeof(dom));
        Reset();
        assert(dom.Init(0, kName) == 0);
        assert(dom.Init(5, nullptr) == 0);
        assert(g_vChildOrder.empty() && g_strCreatedName.empty() && g_nFinishCalls == 0);
        assert(dom.pInner == nullptr);
    }

    // ---- the facility: the fixed six, then the pair the type picks, then 100
    {
        struct Case { int32_t nType, n3, n4; };
        static const Case kCases[] = {
            {1, 0xd9, 0xb7}, {2, 0xee, 0xb7}, {3, 0xea, 0x7d},
            {4, 0xc9, 0x84}, {5, 0xb5, 0x94}, {6, 0x10b, 0x88},
            {7, 0x79, 0xe2}, {8, 0x6b, 0xcf}, {9, 0x84, 0xcf},
            {10, 0, 0},      // the default arm
        };
        for (size_t i = 0; i < sizeof(kCases) / sizeof(kCases[0]); ++i) {
            CSynFacility fac;
            std::memset(&fac, 0, sizeof(fac));
            Reset();
            const uint64_t uRet = fac.Init(0x41, kCases[i].nType);

            assert(uRet == 0x1122334455667788ull);
            assert(g_strCreatedName == "cq_synfacility");
            assert(fac.pInner == (void*)&g_Root);

            const int32_t aWantOrder[] = {0, 1, 2, 5, 7, 8, 3, 4, 6};
            assert(g_vChildOrder.size() == 9);
            for (int k = 0; k < 9; ++k) assert(g_vChildOrder[k] == aWantOrder[k]);

            assert(g_vB8.size() == 2);
            assert(g_vB8[0].first == 1 && g_vB8[0].second == 0x41);
            assert(g_vB8[1].first == 2 && g_vB8[1].second == kCases[i].nType);

            // children 0, 5, 7, 8 get zero; 3 and 4 get the pair; 6 gets 100
            assert(g_vB0.size() == 7);
            assert(g_vB0[0].first == 0 && g_vB0[0].second == 0);
            assert(g_vB0[1].first == 5 && g_vB0[1].second == 0);
            assert(g_vB0[2].first == 7 && g_vB0[2].second == 0);
            assert(g_vB0[3].first == 8 && g_vB0[3].second == 0);
            assert(g_vB0[4].first == 3 && g_vB0[4].second == kCases[i].n3);
            assert(g_vB0[5].first == 4 && g_vB0[5].second == kCases[i].n4);
            assert(g_vB0[6].first == 6 && g_vB0[6].second == 100);
            assert(g_nFinishCalls == 1 && g_uFinishArg == 1);
        }

        // a zero id or a zero type is refused before the object is even asked for
        CSynFacility fac;
        std::memset(&fac, 0, sizeof(fac));
        Reset();
        assert(fac.Init(0, 3) == 0);
        assert(fac.Init(7, 0) == 0);
        assert(fac.pInner == nullptr && g_vChildOrder.empty() && g_strCreatedName.empty());
    }

    // ---- the teardown: close through +0x38, delete through slot zero, clear twice
    {
        CSynDomain dom;
        std::memset(&dom, 0, sizeof(dom));
        dom.pInner = &g_Root;
        Reset();
        dom.Destroy((void*)0x11, (void*)0x22);
        assert(g_nDestroyCalls == 1);
        assert(g_uDestroyA1 == 0);                        // the second argument is zeroed
        assert(g_pDestroyA2 == (void*)0x11);              // the caller's third travels through
        assert(g_pDestroyA3 == (void*)0x22);
        assert(g_uDestroyA4 == 0xfffffffffffffffeull);    // the fifth is minus two
        assert(g_nDeleteCalls == 1 && g_uDeleteFlag == 1);
        assert(dom.pInner == nullptr);

        Reset();
        dom.Destroy((void*)0x11, (void*)0x22);            // already empty: nothing at all
        assert(g_nDestroyCalls == 0 && g_nDeleteCalls == 0);
    }

    // ---- the same three steps for a facility
    {
        CSynFacility fac;
        std::memset(&fac, 0, sizeof(fac));
        fac.pInner = &g_Root;
        Reset();
        fac.Destroy((void*)0x33, (void*)0x44);
        assert(g_nDestroyCalls == 1 && g_uDestroyA1 == 0);
        assert(g_pDestroyA2 == (void*)0x33 && g_pDestroyA3 == (void*)0x44);
        assert(g_nDeleteCalls == 1 && g_uDeleteFlag == 1);
        assert(fac.pInner == nullptr);
    }

    // ---- and the frees go through the named heaps, one per object kind
    {
        void* pBlock = std::calloc(1, 0x40);
        Reset();
        CSynDomain::FreeAlloc(pBlock);
        assert(g_nHeapFree == 1 && g_pHeapFreed == pBlock);

        pBlock = std::calloc(1, 0x40);
        Reset();
        CSynFacility::FreeAlloc(pBlock);
        assert(g_nHeapFree == 1 && g_pHeapFreed == pBlock);
    }

    // ---- a release on a live domain takes both steps, in order
    {
        CSynDomain* pDom = (CSynDomain*)std::calloc(1, sizeof(CSynDomain));
        pDom->pInner = &g_Root;
        Reset();
        CSynDomain::Release(pDom);
        assert(g_nDestroyCalls == 1 && g_nDeleteCalls == 1);
        assert(g_nHeapFree == 1 && g_pHeapFreed == pDom);   // pDom is gone now

        Reset();
        CSynDomain::Release(nullptr);
        CSynFacility::Release(nullptr);
        assert(g_nDestroyCalls == 0 && g_nHeapFree == 0);
    }

    tq::g_HeapApi = savedHeap;
    tq::g_LogApi = savedLog;
    std::printf("SYNDICATE_D25_OK: both initialisers, both teardowns and both frees, 6 units, 57 checks\n");
    return 0;
}

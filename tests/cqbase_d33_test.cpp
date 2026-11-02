// ============================================================================
// cqbase_d33 — the two class heaps and their allocation wrappers: one heap per class shared by
//   the allocator, the validity test, the free and the scalar deleting destructor
// ============================================================================
#include "modules/cqbase/src/myheap.h"
#include "modules/syndicate/src/synobjects.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>

using namespace tq;

static int g_nSlot38 = 0;
static int g_nSlot0 = 0;
static int g_nDestroy = 0;
static int g_nFree = 0;

static void FakeSlot38(void* p, void* a, void* b, void* c, void* d) {
    (void)p; (void)a; (void)b; (void)c; (void)d;
    g_nSlot38++;
}
static void FakeSlot0(void* p, void* uFlag) {
    (void)p; (void)uFlag;
    g_nSlot0++;
}
static void FakeDestroy(void* p, void* a, void* b) {
    (void)p; (void)a; (void)b;
    g_nDestroy++;
}
static void FakeFree(void* p) {
    (void)p;
    g_nFree++;
}

static void* g_aFakeVft[0x40];

// the validity test forwards to the heap api, so it is faked here to observe the call
static int g_nValidCalls = 0;
static void* g_pValidHeap = nullptr;
static uint32_t g_uValidFlags = 0xFFFFFFFF;
static void* g_pValidPtr = nullptr;
static bool g_bValidAnswer = true;
static bool FakeValidate(void* h, uint32_t f, const void* p) {
    g_nValidCalls++;
    g_pValidHeap = h;
    g_uValidFlags = f;
    g_pValidPtr = (void*)p;
    return g_bValidAnswer;
}

// the member teardown behind the free hook's signature
static void DestroyDomainThunk(void* p, void* a, void* b) {
    ((CSynDomain*)p)->Destroy(a, b);
}

int main() {
    std::memset(g_aFakeVft, 0, sizeof(g_aFakeVft));
    g_aFakeVft[0x00 / 8] = (void*)&FakeSlot0;
    g_aFakeVft[0x38 / 8] = (void*)&FakeSlot38;

    // ---- one heap per class, and the two classes do not share it
    {
        CMyHeap& domainHeap = CSynDomain::Heap();
        assert(&domainHeap == &CSynDomain::Heap());          // the same object every time
        CMyHeap& facilityHeap = CSynFacility::Heap();
        assert(&facilityHeap == &CSynFacility::Heap());
        assert((void*)&domainHeap != (void*)&facilityHeap);
    }

    // ---- the validity test forwards the pointer, the heap handle and flags zero, and answers
    //      with whatever the api says
    {
        g_HeapApi.pfnValidate = &FakeValidate;

        void* pBlock = CSynDomain::Alloc(0x40);
        assert(pBlock != nullptr);
        std::memset(pBlock, 0x5A, 0x40);                      // the block is writable

        g_bValidAnswer = true;
        g_nValidCalls = 0;
        assert(CSynDomain::IsValidPt(pBlock) == true);
        assert(g_nValidCalls == 1);
        assert(g_pValidPtr == pBlock);
        assert(g_uValidFlags == 0);
        assert(g_pValidHeap != nullptr);

        g_bValidAnswer = false;
        assert(CSynDomain::IsValidPt(pBlock) == false);
        assert(g_nValidCalls == 2);

        void* pFacilityBlock = CSynFacility::Alloc(0x18);
        assert(pFacilityBlock != nullptr);
        g_bValidAnswer = true;
        assert(CSynFacility::IsValidPt(pFacilityBlock) == true);
        assert(g_pValidPtr == pFacilityBlock);

        CSynDomain::FreeAlloc(pBlock);
        CSynFacility::FreeAlloc(pFacilityBlock);
    }

    // ---- the domain's scalar deleting destructor: tear down always, free only with bit zero
    {
        g_pfnDestroyDomain = &FakeDestroy;
        g_pfnFreeDomainAlloc = &FakeFree;

        CSynDomain* pDomain = (CSynDomain*)CSynDomain::Alloc(sizeof(CSynDomain));
        assert(pDomain != nullptr);
        std::memset(pDomain, 0, sizeof(CSynDomain));

        g_nDestroy = g_nFree = 0;
        assert(pDomain->DeleteScalar(0) == pDomain);
        assert(g_nDestroy == 1);
        assert(g_nFree == 0);                                  // flags without bit zero: no free

        assert(pDomain->DeleteScalar(1) == pDomain);
        assert(g_nDestroy == 2);
        assert(g_nFree == 1);
        CSynDomain::FreeAlloc(pDomain);
    }

    // ---- and the facility's, which ends in its own free hook
    {
        g_pfnDestroyFacility = &FakeDestroy;
        g_pfnFreeFacilityAlloc = &FakeFree;

        g_nSlot38 = g_nSlot0 = 0;
        CSynFacility* pFacility = (CSynFacility*)CSynFacility::Alloc(sizeof(CSynFacility));
        assert(pFacility != nullptr);
        std::memset(pFacility, 0, sizeof(CSynFacility));

        g_nDestroy = g_nFree = 0;
        assert(pFacility->DeleteScalar(0) == pFacility);
        assert(g_nDestroy == 1 && g_nFree == 0);
        assert(pFacility->DeleteScalar(1) == pFacility);
        assert(g_nDestroy == 2 && g_nFree == 1);
        CSynFacility::FreeAlloc(pFacility);
    }

    // ---- with the real teardown hooked in, the object's own slots are the ones called
    {
        g_pfnDestroyDomain = &DestroyDomainThunk;
        g_pfnFreeDomainAlloc = &CSynDomain::FreeAlloc;

        CSynDomain* pDomain = (CSynDomain*)CSynDomain::Alloc(sizeof(CSynDomain));
        assert(pDomain != nullptr);
        std::memset(pDomain, 0, sizeof(CSynDomain));
        static void* aFakeObj[1];
        aFakeObj[0] = g_aFakeVft;          // an object whose first word is its vtable
        pDomain->pInner = aFakeObj;

        g_nSlot38 = g_nSlot0 = 0;
        pDomain->DeleteScalar(0);                  // no free here, so the fields stay readable
        assert(g_nSlot38 == 1);                    // slot 0x38 asked the inner object to close
        assert(g_nSlot0 == 1);                     // slot zero asked it to go away
        assert(pDomain->pInner == nullptr);
        CSynDomain::FreeAlloc(pDomain);
    }

    // ---- domain construction goes through the class heap, so the block is the class's own
    {
        CSynDomain* pDomain = CSynDomain::Create((void*)1, (void*)2, (void*)3);
        assert(pDomain != nullptr);
        assert(CSynDomain::IsValidPt(pDomain) == true);
        assert(pDomain->pInner == nullptr);
        assert(pDomain->u8 == 0);
        assert(pDomain->p1 == (void*)1);
        assert(pDomain->p2 == (void*)2);
        assert(pDomain->p3 == (void*)3);
        g_pfnFreeDomainAlloc(pDomain);

        CSynFacility* pFacility = CSynFacility::Create((void*)4, (void*)5, (void*)6);
        assert(pFacility != nullptr);
        assert(CSynFacility::IsValidPt(pFacility) == true);
        assert(pFacility->pInner == nullptr);
        assert(pFacility->p1 == (void*)4);
        CSynFacility::FreeAlloc(pFacility);
    }

    std::printf("SYNDICATE_D33_OK: the class heaps and the scalar deleting destructors, 8 units, 41 checks\n");
    return 0;
}

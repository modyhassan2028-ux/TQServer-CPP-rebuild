// ============================================================================
// synobjects.cpp — RAW Syndicate.dll v6159 · the two data objects, their initialisers and
//   the two releases. Every vtable call is made through the slot offset the binary uses;
//   the slot names below are neutral on purpose, because the binary only tells us the
//   offset and the arguments, never a name.
// ============================================================================
#include "modules/syndicate/src/synobjects.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"

#include <cstring>

namespace tq {

// ---- slots read by offset, exactly as the binary reads them
typedef void* (*pfnSlotGetChild)(void* pSelf, int32_t nIndex);        // +0x10
typedef void* (*pfnSlotCreate)(void* pSelf, const char* pszName);     // +0x20
typedef uint64_t (*pfnSlotFinish)(void* pSelf, uint64_t uFlag);       // +0x50
typedef void (*pfnSlotSetPtr)(void* pSelf, void* pValue);             // +0x80
typedef void (*pfnSlotSetIntB0)(void* pSelf, int32_t nValue);         // +0xb0
typedef void (*pfnSlotSetIntB8)(void* pSelf, int32_t nValue);         // +0xb8
typedef uint64_t (*pfnSlotDestroy)(void* pSelf, uint64_t u0, void* u1, void* u2,
                                   uint64_t u3);                      // +0x38
typedef uint64_t (*pfnSlotDelete)(void* pSelf, uint64_t uFlag);       // +0x00

static void** SynVft(void* pSelf) { return *(void***)pSelf; }

static void* SynGetChild(void* pSelf, int32_t nIndex) {
    return ((pfnSlotGetChild)SynVft(pSelf)[0x10 / 8])(pSelf, nIndex);
}
static void SynSetPtr(void* pSelf, void* pValue) {
    ((pfnSlotSetPtr)SynVft(pSelf)[0x80 / 8])(pSelf, pValue);
}
static void SynSetIntB0(void* pSelf, int32_t nValue) {
    ((pfnSlotSetIntB0)SynVft(pSelf)[0xb0 / 8])(pSelf, nValue);
}
static void SynSetIntB8(void* pSelf, int32_t nValue) {
    ((pfnSlotSetIntB8)SynVft(pSelf)[0xb8 / 8])(pSelf, nValue);
}
static uint64_t SynFinish(void* pSelf, uint64_t uFlag) {
    return ((pfnSlotFinish)SynVft(pSelf)[0x50 / 8])(pSelf, uFlag);
}

// ---- DB.dll!InstanceGet, the module instance the initialisers build through
static void* DefaultDbInstanceGet() { return nullptr; }
void* (*g_pfnDbInstanceGet)() = DefaultDbInstanceGet;


// ---- the creators ---------------------------------------------------------------
// each one takes the class's own heap, a guarded CMyHeap whose lifetime is the function's
static void DefaultConstructSyndicate(void*, void*, void*, void*) {}
void (*g_pfnConstructSyndicate)(void* pMem, void* pOwner, void* p2, void* p3) =
    DefaultConstructSyndicate;

// 0x141788b60 — the fields in the binary's order, the byte at +0x48 set to one
CSynAttr* CSynAttr::Create(void* p1_, void* p2_, void* p3_) {
    static CMyHeap sHeap("CSynAttr");
    CSynAttr* p = (CSynAttr*)sHeap.Alloc(0x50);
    if (p == nullptr) return nullptr;
    p->u0 = 0;
    p->p1 = p1_;
    p->p2 = p2_;
    p->p3 = p3_;
    p->u30 = 0;
    p->u34 = 0;
    p->u3C = 0;
    p->u40 = 0;
    p->u44 = 0;
    p->u48 = 1;
    p->u4C = 0;
    p->u20 = 0;
    p->u28 = 0;
    return p;
}

// 0x1417a28c0 — the creator hands the whole thing to the constructor
CSyndicate* CSyndicate::Create(void* pOwner, void* p2, void* p3) {
    static CMyHeap sHeap("CSyndicate");
    CSyndicate* p = (CSyndicate*)sHeap.Alloc(0x450);
    if (p == nullptr) return nullptr;
    g_pfnConstructSyndicate(p, pOwner, p2, p3);
    return p;
}

// 0x1417c4b60 — a zero qword, a zero dword at +0x08, then the three arguments
CSynDomain* CSynDomain::Create(void* p1_, void* p2_, void* p3_) {
    static CMyHeap sHeap("CSynDomain");
    CSynDomain* p = (CSynDomain*)sHeap.Alloc(0x28);
    if (p == nullptr) return nullptr;
    p->pInner = nullptr;
    p->u8 = 0;
    p->p1 = p1_;
    p->p2 = p2_;
    p->p3 = p3_;
    return p;
}

// 0x1417c5320 — a zero qword and the three arguments
CSynFacility* CSynFacility::Create(void* p1_, void* p2_, void* p3_) {
    static CMyHeap sHeap("CSynFacility");
    CSynFacility* p = (CSynFacility*)sHeap.Alloc(0x20);
    if (p == nullptr) return nullptr;
    p->pInner = nullptr;
    p->p1 = p1_;
    p->p2 = p2_;
    p->p3 = p3_;
    return p;
}

// ---- CSynDomain ----------------------------------------------------------------
// 0x1417c45c0 — a zero id or a null name answers zero before anything else happens. The
// object is created by name, stored into +0x00 of the domain, and then seven children are
// filled: the id, the name, 930000, 0x100, 0xad and 5 twice. The call that closes it is a
// tail jump, so its full 64 bit answer is what the caller gets back.
uint64_t CSynDomain::Init(uint32_t uId, const char* pszName) {
    if (uId == 0) return 0;
    if (pszName == nullptr) return 0;

    void* pMgr = g_pfnDbInstanceGet();
    void* pObj = ((pfnSlotCreate)SynVft(pMgr)[0x20 / 8])(pMgr, "cq_syndomain");
    pInner = pObj;
    if (pObj == nullptr) return 0;

    SynSetIntB8(SynGetChild(pObj, 0), (int32_t)uId);
    SynSetPtr(SynGetChild(pObj, 1), (void*)pszName);
    SynSetIntB8(SynGetChild(pObj, 2), 930000);
    SynSetIntB0(SynGetChild(pObj, 3), 0x100);
    SynSetIntB0(SynGetChild(pObj, 4), 0xad);
    SynSetIntB0(SynGetChild(pObj, 5), 5);
    SynSetIntB0(SynGetChild(pObj, 6), 5);
    return SynFinish(pObj, 1);
}

// 0x1417c4550 — the inner object is asked to close itself through +0x38 with a zero second
// argument and 0xfffffffffffffffe as the fifth, then deleted through slot zero with flags
// set to one. The null store into +0x00 is performed twice, and both are kept.
void CSynDomain::Destroy(void* u1, void* u2) {
    void* pObj = pInner;
    if (pObj == nullptr) return;
    ((pfnSlotDestroy)SynVft(pObj)[0x38 / 8])(pObj, 0, u1, u2, 0xfffffffffffffffeull);
    if (pInner == nullptr) return;
    void* pAgain = pInner;
    ((pfnSlotDelete)SynVft(pAgain)[0x00 / 8])(pAgain, 1);
    pInner = nullptr;
    pInner = nullptr;
}

// 0x1417c4a70 — the domain's own heap, made on first use and freed through after that
void CSynDomain::FreeAlloc(void* pMem) {
    static CMyHeap sHeap("CSynDomain");
    sHeap.Free(pMem);
}

// ---- CSynFacility --------------------------------------------------------------
// 0x1417c4cc0 — the guard is the same pair, checked together. Nine children are always
// filled the same way (0, id, type, 0 at 5, 0 at 7, 0 at 8), then a jump table on the type
// picks the pair written to children 3 and 4, then child 6 is set to 100.
uint64_t CSynFacility::Init(uint32_t uId, int32_t nFacilityType) {
    if (uId == 0 || nFacilityType == 0) return 0;

    void* pMgr = g_pfnDbInstanceGet();
    void* pObj = ((pfnSlotCreate)SynVft(pMgr)[0x20 / 8])(pMgr, "cq_synfacility");
    pInner = pObj;
    if (pObj == nullptr) return 0;

    SynSetIntB0(SynGetChild(pObj, 0), 0);
    SynSetIntB8(SynGetChild(pObj, 1), (int32_t)uId);
    SynSetIntB8(SynGetChild(pObj, 2), nFacilityType);
    SynSetIntB0(SynGetChild(pObj, 5), 0);
    SynSetIntB0(SynGetChild(pObj, 7), 0);
    SynSetIntB0(SynGetChild(pObj, 8), 0);

    // the jump table at .text:0x1417c5008, nine entries relative to 0x141720000
    int32_t nChild3 = 0;
    int32_t nChild4 = 0;
    switch (nFacilityType) {
        case 1: nChild3 = 0xd9;  nChild4 = 0xb7; break;
        case 2: nChild3 = 0xee;  nChild4 = 0xb7; break;
        case 3: nChild3 = 0xea;  nChild4 = 0x7d; break;
        case 4: nChild3 = 0xc9;  nChild4 = 0x84; break;
        case 5: nChild3 = 0xb5;  nChild4 = 0x94; break;
        case 6: nChild3 = 0x10b; nChild4 = 0x88; break;
        case 7: nChild3 = 0x79;  nChild4 = 0xe2; break;
        case 8: nChild3 = 0x6b;  nChild4 = 0xcf; break;
        case 9: nChild3 = 0x84;  nChild4 = 0xcf; break;
        default: nChild3 = 0;    nChild4 = 0;    break;
    }
    SynSetIntB0(SynGetChild(pObj, 3), nChild3);
    SynSetIntB0(SynGetChild(pObj, 4), nChild4);

    SynSetIntB0(SynGetChild(pObj, 6), 100);
    return SynFinish(pObj, 1);
}

// 0x1417c4c50 — identical to the domain's teardown, including the doubled null store
void CSynFacility::Destroy(void* u1, void* u2) {
    void* pObj = pInner;
    if (pObj == nullptr) return;
    ((pfnSlotDestroy)SynVft(pObj)[0x38 / 8])(pObj, 0, u1, u2, 0xfffffffffffffffeull);
    if (pInner == nullptr) return;
    void* pAgain = pInner;
    ((pfnSlotDelete)SynVft(pAgain)[0x00 / 8])(pAgain, 1);
    pInner = nullptr;
    pInner = nullptr;
}

// 0x1417c5230 — the facility's own heap
void CSynFacility::FreeAlloc(void* pMem) {
    static CMyHeap sHeap("CSynFacility");
    sHeap.Free(pMem);
}

// ---- the release wrappers -----------------------------------------------------
static void DefaultDestroyDomain(void* pDomain, void* u1, void* u2) {
    ((CSynDomain*)pDomain)->Destroy(u1, u2);
}
static void DefaultFreeDomainAlloc(void* pDomain) { CSynDomain::FreeAlloc(pDomain); }
static void DefaultDestroyFacility(void* pFacility, void* u1, void* u2) {
    ((CSynFacility*)pFacility)->Destroy(u1, u2);
}
static void DefaultFreeFacilityAlloc(void* pFacility) { CSynFacility::FreeAlloc(pFacility); }

void (*g_pfnDestroyDomain)(void*, void*, void*) = DefaultDestroyDomain;
void (*g_pfnFreeDomainAlloc)(void*) = DefaultFreeDomainAlloc;
void (*g_pfnDestroyFacility)(void*, void*, void*) = DefaultDestroyFacility;
void (*g_pfnFreeFacilityAlloc)(void*) = DefaultFreeFacilityAlloc;

// 0x1417c4c00 — a null domain is not touched at all; anything else is taken apart and
// then handed back, in that order. The raw hands the teardown two unnamed values that it
// never sets, so they travel through as they came in.
void CSynDomain::Release(CSynDomain* pDomain) {
    if (pDomain != nullptr) {
        g_pfnDestroyDomain(pDomain, nullptr, nullptr);
        g_pfnFreeDomainAlloc(pDomain);
    }
}

// 0x1417c53c0 — the same two steps for a facility
void CSynFacility::Release(CSynFacility* pFacility) {
    if (pFacility != nullptr) {
        g_pfnDestroyFacility(pFacility, nullptr, nullptr);
        g_pfnFreeFacilityAlloc(pFacility);
    }
}

}  // namespace tq

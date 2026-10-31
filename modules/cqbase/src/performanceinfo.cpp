// CQBase.dll v6159 — CPerformanceInfo handle (0x140ba03b0..0x140ba5ef0)
#include "modules/cqbase/src/performanceinfo.h"

namespace tq {

static const void* const kCPerformanceInfoVt[1] = { nullptr };

// 0x140bcbb30 — slot 0 is the deleting destructor
static const void* const kCPerformanceInfoBaseVt[1] = {
    (const void*)&CPerformanceInfoBaseDeletingDtor,
};

static void* DefaultAlloc(size_t nBytes) { return ::operator new(nBytes); }
static void DefaultFree(void* p) { ::operator delete(p); }
static int DefaultFreeLibrary(void*) { return 0; }
static int DefaultPdhCloseQuery(void*) { return 0; }
// The two teardown bodies a list goes through are part of the half of the file that is
// still unported (0x140ba2d50 and 0x140ba42d0 for A, 0x140ba1f20 and 0x140ba4340 for B).
// Until they are here the clear step releases the list's sentinel node, which is the only
// allocation a list holds at this point, so the object can be destroyed without leaving
// memory behind; the final step has nothing to do yet.
static void DefaultListClear(void* pList) {
    CPerformanceList* pL = (CPerformanceList*)pList;
    if (pL->pHead != nullptr) {
        g_PerformanceInfoApi.pfnFree(pL->pHead);
        pL->pHead = nullptr;
    }
}
static void DefaultListFinal(void*) {}

PerformanceInfoApi g_PerformanceInfoApi = {
    DefaultAlloc, DefaultFree, DefaultFreeLibrary, DefaultPdhCloseQuery, DefaultListClear,
    DefaultListFinal,
};

const void* const* CPerformanceInfoBase::Table() { return kCPerformanceInfoBaseVt; }

// 0x140ba1c20 — the first three qwords are cleared, then the two flag bytes are written
// in the order the raw writes them: one at 0x48 and zero at 0x49.
static int CPerformanceNode50Init(void* pNode) {
    CPerformanceNode50* pN = (CPerformanceNode50*)pNode;
    pN->p0 = nullptr;
    pN->p1 = nullptr;
    pN->p2 = nullptr;
    pN->uFlag48 = 1;
    pN->uFlag49 = 0;
    return 0;
}

// 0x140ba1d20
static int CPerformanceNode278Init(void* pNode) {
    CPerformanceNode278* pN = (CPerformanceNode278*)pNode;
    pN->p0 = nullptr;
    pN->p1 = nullptr;
    pN->p2 = nullptr;
    pN->uFlag270 = 1;
    pN->uFlag271 = 0;
    return 0;
}

// 0x140ba5cf0 — a proxy of eight bytes, a node, then the node linked to itself and the
// count cleared. The node's zero byte at 0x49 becomes a one afterwards.
void CPerformanceListInitA(CPerformanceList* pList) {
    void** ppProxy = (void**)g_PerformanceInfoApi.pfnAlloc(8);
    if (ppProxy != nullptr) *ppProxy = pList;
    pList->pProxy = ppProxy;
    CPerformanceNode50* pNode = (CPerformanceNode50*)g_PerformanceInfoApi.pfnAlloc(0x50);
    CPerformanceNode50Init(pNode);
    pList->pHead = pNode;
    pNode->uFlag49 = 1;
    pNode->p1 = pNode;
    pNode->p0 = pNode;
    pNode->p2 = pNode;
    pList->nCount = 0;
}

// 0x140ba5d70 — the same with the larger node and its byte at 0x271
void CPerformanceListInitB(CPerformanceList* pList) {
    void** ppProxy = (void**)g_PerformanceInfoApi.pfnAlloc(8);
    if (ppProxy != nullptr) *ppProxy = pList;
    pList->pProxy = ppProxy;
    CPerformanceNode278* pNode = (CPerformanceNode278*)g_PerformanceInfoApi.pfnAlloc(0x278);
    CPerformanceNode278Init(pNode);
    pList->pHead = pNode;
    pNode->uFlag271 = 1;
    pNode->p1 = pNode;
    pNode->p0 = pNode;
    pNode->p2 = pNode;
    pList->nCount = 0;
}

// 0x140ba5df0 — the table, both lists, then every field in the order the raw writes
// them. Note the dword at 0xC4 is never written, and 0x148 is cleared last of all.
CPerformanceInfoBase::CPerformanceInfoBase() : pVt(kCPerformanceInfoBaseVt) {
    CPerformanceListInitA(&listA);
    CPerformanceListInitB(&listB);
    hModule1 = nullptr;      // 0xB0
    hModule2 = nullptr;      // 0xB8
    uC0 = 1;                 // 0xC0, a dword
    pA0 = nullptr;           // 0xA0
    pA8 = nullptr;           // 0xA8
    for (size_t i = 0; i < sizeof(unknown10); ++i) unknown10[i] = 0;
    hQuery = nullptr;        // 0x08, the rest of the zeroed run
    u148 = 0;
}

// 0x140ba50b0 — frees both modules, closes the query, then empties list B before list A,
// deleting each list's proxy after its two teardown steps.
CPerformanceInfoBase::~CPerformanceInfoBase() {
    pVt = kCPerformanceInfoBaseVt;
    if (hModule1 != nullptr) {
        g_PerformanceInfoApi.pfnFreeLibrary(hModule1);
        hModule1 = nullptr;
    }
    if (hModule2 != nullptr) {
        g_PerformanceInfoApi.pfnFreeLibrary(hModule2);
        hModule2 = nullptr;
    }
    g_PerformanceInfoApi.pfnPdhCloseQuery(hQuery);
    g_PerformanceInfoApi.pfnListClear(&listB);
    g_PerformanceInfoApi.pfnListFinal(&listB);
    g_PerformanceInfoApi.pfnFree(listB.pProxy);
    g_PerformanceInfoApi.pfnListClear(&listA);
    g_PerformanceInfoApi.pfnListFinal(&listA);
    g_PerformanceInfoApi.pfnFree(listA.pProxy);
}

void* CPerformanceInfoBaseNew() { return new CPerformanceInfoBase(); }

// 0x140ba5ec0
void* CPerformanceInfoBaseDeletingDtor(void* pBase, int nFlag) {
    CPerformanceInfoBase* pObj = (CPerformanceInfoBase*)pBase;
    pObj->~CPerformanceInfoBase();
    if ((nFlag & 1) != 0) operator delete(pBase);
    return pBase;
}

// the measuring object exists now, so the handle builds the real one
static void* DefaultNewPerformanceInfoBase() { return CPerformanceInfoBaseNew(); }
static void DefaultPerformanceInfoRecord(void*) {}

// the allocation seam stands where the other half of the file builds its object
PfnNewPerformanceInfoBase g_pfnNewPerformanceInfoBase = DefaultNewPerformanceInfoBase;
PfnPerformanceInfoBaseRecord g_pfnPerformanceInfoBaseRecord = DefaultPerformanceInfoRecord;

// 0x140ba5ef0 — operator new(0x150) then its constructor
CPerformanceInfo::CPerformanceInfo() : pVt(kCPerformanceInfoVt), pBase(nullptr) {
    pBase = g_pfnNewPerformanceInfoBase();
}

// 0x140ba03b0 — shares the measuring object with the one it copies
CPerformanceInfo::CPerformanceInfo(const CPerformanceInfo& rOther)
    : pVt(kCPerformanceInfoVt), pBase(rOther.pBase) {}

// 0x140ba03d0 — overwrites the pointer, the old object is not released
CPerformanceInfo& CPerformanceInfo::operator=(const CPerformanceInfo& rOther) {
    pBase = rOther.pBase;
    return *this;
}

// 0x140ba07e0 — the object goes through its own first table slot with (this, 1) and,
// unlike the thread times handle, the pointer is left pointing at what was deleted.
CPerformanceInfo::~CPerformanceInfo() {
    if (pBase != nullptr) {
        typedef void (*PfnDeletingDtor)(void*, int);
        void** ppVt = *(void***)pBase;
        ((PfnDeletingDtor)ppVt[0])(pBase, 1);
    }
}

// 0x140ba5cd0 — the name is spelled this way in the original
void CPerformanceInfo::RecrodPerformanceInfo() {
    if (pBase != nullptr) g_pfnPerformanceInfoBaseRecord(pBase);
}

}  // namespace tq

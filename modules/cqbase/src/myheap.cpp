// CQBase.dll v6159 — myheap.cpp (0x140b9d6e0..0x140b9e0f0)
#include "modules/cqbase/src/myheap.h"
#include "modules/cqbase/src/cini.h"   // LogPrintf

#include <cstdlib>
#include <cstring>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace tq {

#if defined(_WIN32)
static void* HCreate(uint32_t o, size_t i, size_t m) { return HeapCreate(o, i, m); }
static void* HAlloc(void* h, uint32_t f, size_t n) { return HeapAlloc((HANDLE)h, f, n); }
static bool HFree(void* h, uint32_t f, void* p) { return HeapFree((HANDLE)h, f, p) != 0; }
static bool HValid(void* h, uint32_t f, const void* p) {
    return HeapValidate((HANDLE)h, f, p) != 0;
}
static bool HDestroy(void* h) { return HeapDestroy((HANDLE)h) != 0; }
HeapApi g_HeapApi = { HCreate, HAlloc, HFree, HValid, HDestroy };
#else
// off Windows the heap is the process heap, which is what HeapCreate(0,0,0) means
static void* HCreate(uint32_t, size_t, size_t) { return (void*)1; }
static void* HAlloc(void*, uint32_t, size_t n) { return std::malloc(n); }
static bool HFree(void*, uint32_t, void* p) { std::free(p); return true; }
static bool HValid(void*, uint32_t, const void* p) { return p != nullptr; }
static bool HDestroy(void*) { return true; }
HeapApi g_HeapApi = { HCreate, HAlloc, HFree, HValid, HDestroy };
#endif

CMyHeapMgr g_MyHeapMgr;

static std::vector<CMyBaseHeap*>* g_pHeapList = nullptr;

// 0x140b9d700 — the name goes in, the count starts at zero, the heap is created
// with no options at all.
CMyBaseHeap::CMyBaseHeap(const char* pszName)
    : m_nNumAlloc(0), m_strName(pszName), m_hHeap(nullptr) {
    m_hHeap = g_HeapApi.pfnCreate(0, 0, 0);
}

CMyBaseHeap::~CMyBaseHeap() {}

// 0x140b9d7d0 — a zero size and a missing heap both answer null; the heap handle
// being missing is reported, a zero size is not. The count only goes up when the
// allocation really happened.
void* CMyBaseHeap::Alloc(size_t uBytes) {
    if (uBytes == 0) return nullptr;
    if (m_hHeap == nullptr) {
        LogPrintf("%s", "CHECKF m_hHeap myheap.cpp:0x34");
        return nullptr;
    }
    void* pMem = g_HeapApi.pfnAlloc(m_hHeap, 8, uBytes);   // flag 8, zeroed memory
    if (pMem != nullptr) {
        __atomic_fetch_add(&m_nNumAlloc, 1, __ATOMIC_SEQ_CST);
    }
    return pMem;
}

// 0x140b9d840 — a null pointer is ignored; a count that has already reached zero is
// reported and the free still goes ahead, because the report falls through to the
// heap check rather than returning. A missing handle is reported and answers at
// once. The count only goes down when the free really happened.
void CMyBaseHeap::Free(void* pMem) {
    if (pMem == nullptr) return;
    if (m_nNumAlloc < 1) {
        LogPrintf("%s", "IF_NOT m_lNumAlloc > 0 myheap.cpp:0x53");
        // the original reads the name here and then falls straight through to the
        // heap handle check, it does not return
        (void)m_strName.c_str();
    }
    if (m_hHeap == nullptr) {
        LogPrintf("%s", "CHECK m_hHeap myheap.cpp:0x58");
        return;
    }
    if (g_HeapApi.pfnFree(m_hHeap, 0, pMem)) {
        __atomic_fetch_sub(&m_nNumAlloc, 1, __ATOMIC_SEQ_CST);
    }
}

// 0x140b9dac0 — a null base is reported, otherwise the heap files itself with the
// manager under its own name.
CMyHeap::CMyHeap(const char* pszName) {
    m_pBaseHeap = new CMyBaseHeap(pszName);
    if (m_pBaseHeap == nullptr) {
        LogPrintf("%s", "IF_NOT m_pBaseHeap myheap.cpp:0x8a");
    } else {
        g_MyHeapMgr.AddMyHeap(pszName, m_pBaseHeap);
    }
}

// 0x140b9e0f0 — the heap is destroyed, the name goes, the base is freed
CMyHeap::~CMyHeap() {
    if (m_pBaseHeap == nullptr) return;
    if (m_pBaseHeap->m_hHeap != nullptr) {
        g_HeapApi.pfnDestroy(m_pBaseHeap->m_hHeap);
    }
    delete m_pBaseHeap;
    m_pBaseHeap = nullptr;
}

// 0x140b9d980 — no base means no allocation, and it says so
void* CMyHeap::Alloc(size_t uBytes) {
    if (m_pBaseHeap == nullptr) {
        LogPrintf("%s", "IF_OK m_pBaseHeap myheap.cpp:0x9c");
        return nullptr;
    }
    return m_pBaseHeap->Alloc(uBytes);
}

// 0x140b9d9b0
void CMyHeap::Free(void* pMem) {
    if (m_pBaseHeap == nullptr) {
        LogPrintf("%s", "IF_OK m_pBaseHeap myheap.cpp:0xa8");
        return;
    }
    m_pBaseHeap->Free(pMem);
}

// 0x140b9da00 — a null base is reported and answers false, a base without a heap
// answers false without a word
bool CMyHeap::IsValidPt(const void* pMem) {
    if (m_pBaseHeap == nullptr) {
        LogPrintf("%s", "IF_OK m_pBaseHeap myheap.cpp:0xb2");
        return false;
    }
    if (m_pBaseHeap->m_hHeap == nullptr) return false;
    return g_HeapApi.pfnValidate(m_pBaseHeap->m_hHeap, 0, pMem);
}

// 0x140b9d6f0 — the assignment shares the base, it does not copy it
CMyHeap& CMyHeap::operator=(const CMyHeap& rOther) {
    m_pBaseHeap = rOther.m_pBaseHeap;
    return *this;
}

// 0x140b9d6e0
CMyHeapMgr& CMyHeapMgr::operator=(const CMyHeapMgr&) {
    return *this;
}

// 0x140b9f760 — the base is filed under its name for the later reports
void CMyHeapMgr::AddMyHeap(const char* pszName, CMyBaseHeap* pBase) {
    if (g_pHeapList == nullptr) g_pHeapList = new std::vector<CMyBaseHeap*>();
    g_pHeapList->push_back(pBase);
    (void)pszName;
}

}  // namespace tq

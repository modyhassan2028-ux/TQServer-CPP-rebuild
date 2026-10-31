// CQBase.dll v6159 — CPerformanceInfo handle (0x140ba03b0..0x140ba5ef0)
#include "modules/cqbase/src/performanceinfo.h"

#include <cstdarg>
#include <cstdio>
#include <string>

#include "modules/cqbase/src/logkernel.h"

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

static void* DefaultLoadLibraryA(const char*) { return nullptr; }
static void* DefaultGetProcAddress(void*, const char*) { return nullptr; }
static void DefaultGetSystemInfo(uint32_t* pCount) { *pCount = 1; }
static void DefaultSetupCounters(void* pBase);


PerformanceInfoApi g_PerformanceInfoApi = {
    DefaultAlloc, DefaultFree, DefaultFreeLibrary, DefaultPdhCloseQuery,
    DefaultLoadLibraryA, DefaultGetProcAddress, DefaultGetSystemInfo,
    DefaultSetupCounters, CPerformanceInfoLog,
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
    // the raw clears these field by field from 0x08 to 0x9F; a run of bytes does the same
    for (size_t i = 0; i < (0xA0 - 0x08); ++i) ((uint8_t*)&hQuery)[i] = 0;
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
    CPerformanceInfoListClearB(&listB);
    CPerformanceInfoListFinalB(&listB);
    g_PerformanceInfoApi.pfnFree(listB.pProxy);
    CPerformanceInfoListClearA(&listA);
    CPerformanceInfoListFinalA(&listA);
    g_PerformanceInfoApi.pfnFree(listA.pProxy);
}

void* CPerformanceInfoBaseNew() { return new CPerformanceInfoBase(); }

// 0x140ba2d50 — the smaller list goes down the right side first, then destroys the name a
// node keeps at +0x18, then releases the node, and only then takes the next one.
static void CPerformanceInfoNodeClearA(CPerformanceNode50* pNode) {
    while (pNode->uFlag49 == 0) {
        CPerformanceInfoNodeClearA((CPerformanceNode50*)pNode->p2);   // right side first
        CPerformanceNode50* pNext = (CPerformanceNode50*)pNode->p0;
        CPerformanceNode50DestroyName(pNode);
        g_PerformanceInfoApi.pfnFree(pNode);
        pNode = pNext;
    }
}

// the destructor hands this the sentinel's first node, not the sentinel itself
void CPerformanceInfoListClearA(CPerformanceList* pList) {
    CPerformanceInfoNodeClearA((CPerformanceNode50*)((CPerformanceNode50*)pList->pHead)->p1);
}

// 0x140ba1f20 — the larger list walks from the sentinel's first node, tells the list to
// let go of the node, releases it, and moves to the next. The sentinel's three links are
// then pointed back at itself and the count cleared.
void CPerformanceInfoListClearB(CPerformanceList* pList) {
    CPerformanceNode278* pSentinel = (CPerformanceNode278*)pList->pHead;
    CPerformanceNode278* pNode = (CPerformanceNode278*)pSentinel->p1;
    while (pNode->uFlag271 == 0) {
        g_PerformanceInfoApi.pfnNodeDetachB(pList, pNode);
        CPerformanceNode278* pNext = (CPerformanceNode278*)pNode->p0;
        g_PerformanceInfoApi.pfnFree(pNode);
        pNode = pNext;
    }
    pSentinel->p1 = pSentinel;
    pList->nCount = 0;
    pSentinel->p0 = pSentinel;
    pSentinel->p2 = pSentinel;
}

// 0x140ba42d0 — one erase step for the smaller list, then the sentinel itself goes and
// the head and count are cleared.
void CPerformanceInfoListFinalA(CPerformanceList* pList) {
    g_PerformanceInfoApi.pfnTreeEraseA(pList, pList->pHead);
    g_PerformanceInfoApi.pfnFree(pList->pHead);
    pList->pHead = nullptr;
    pList->nCount = 0;
}

// 0x140ba4340 — the larger list's last step ends the same way. Its rebalancing loop runs
// over the tree the clear step has already emptied, and is not ported yet.
void CPerformanceInfoListFinalB(CPerformanceList* pList) {
    g_PerformanceInfoApi.pfnFree(pList->pHead);
    pList->pHead = nullptr;
    pList->nCount = 0;
}

// 0x140ba04e0 — a line is only saved when the object was given a name and a name that
// holds a slash: the slash is looked for and an absent one skips the save entirely.
void CPerformanceInfoLog(void* pBase, const char* pszFormat, ...) {
    CPerformanceInfoBase* pThis = (CPerformanceInfoBase*)pBase;
    if (pThis == nullptr || pThis->u148 == 0 || pszFormat == nullptr) return;
    char szLine[0x740];
    for (size_t i = 0; i < sizeof(szLine); ++i) szLine[i] = 0;
    va_list args;
    va_start(args, pszFormat);
    vsnprintf(szLine, 0x740, pszFormat, args);   // the raw calls the same MSVC entry
    va_end(args);
    std::string strName((const char*)(uintptr_t)pThis->u148);
    if (strName.find('/') != std::string::npos) {
        log_Save((char*)(uintptr_t)pThis->u148, szLine, 0);
    }
}

// 0x140ba0600 — one query, sixteen counters. Two slots on the way, 0x68 and 0x78, are
// left alone: no counter is ever added to them.
void CPerformanceInfoBase::SetupCounters() {
    uint32_t uStatus = g_PerformanceInfoApi.pfnPdhOpenQueryA(nullptr, nullptr, &hQuery);
    if (uStatus == 0) {
        void** ppSlots[16] = {
            &hCommittedBytes, &hCommitLimit, &hPoolPaged, &hPoolNonpaged, &hHandleCount,
            &hProcesses, &hThreads, &hCacheBytes, &hCacheBytesPeak, &hPageFaults, &hPageReads,
            &hPageWrites, &hContextSwitches, &hIoRead, &hIoWrite, &hIoOther,
        };
        static const char* const s_pszPaths[16] = {
            "\\Memory\\Committed Bytes",
            "\\Memory\\Commit Limit",
            "\\Memory\\Pool Paged Bytes",
            "\\Memory\\Pool Nonpaged Bytes",
            "\\Process(_Total)\\Handle Count",
            "\\System\\Processes",
            "\\System\\Threads",
            "\\Memory\\Cache Bytes",
            "\\Memory\\Cache Bytes Peak",
            "\\Memory\\Page Faults/sec",
            "\\Memory\\Page Reads/sec",
            "\\Memory\\Page Writes/sec",
            "\\System\\Context Switches/sec",
            "\\Process(_Total)\\IO Read Operations/sec",
            "\\Process(_Total)\\IO Write Operations/sec",
            "\\Process(_Total)\\IO Other Operations/sec",
        };
        for (int i = 0; i < 16; ++i) {
            g_PerformanceInfoApi.pfnPdhAddCounterA(hQuery, s_pszPaths[i], 0, ppSlots[i]);
        }
        return;
    }
    g_PerformanceInfoApi.pfnLog(this, "PdhOpenQuery fail. status: %ld", (long)uStatus);
}

static void DefaultSetupCounters(void* pBase) {
    ((CPerformanceInfoBase*)pBase)->SetupCounters();
}

// 0x140ba10b0 — the node's string is destroyed before the node itself is released
void CPerformanceNode50DestroyName(void* pNode) {
    ((CPerformanceNode50*)pNode)->strName.~basic_string();
}

// 0x140ba10e0 — the handle's single object slot
void* CPerformanceInfoDeletingDtor(void* pObject, unsigned uFlags) {
    CPerformanceInfo* pThis = (CPerformanceInfo*)pObject;
    pThis->pVt = kCPerformanceInfoVt;
    if (pThis->pBase != nullptr) {
        typedef void (*PfnDeletingDtor)(void*, int);
        void** ppVt = *(void***)pThis->pBase;
        ((PfnDeletingDtor)ppVt[0])(pThis->pBase, 1);
    }
    if ((uFlags & 1) != 0) operator delete(pObject);
    return pObject;
}

// 0x140ba1130 — the array form: the count sits in front of the block, the elements are
// destroyed in order, and only then does the block go
void* CPerformanceInfoArrayDeletingDtor(void* pObjects, unsigned uFlags) {
    CPerformanceInfo* pThis = (CPerformanceInfo*)pObjects;
    if ((uFlags & 2) != 0) {
        int nCount = ((int*)pObjects)[-1];
        for (int i = 0; i < nCount; ++i) pThis[i].~CPerformanceInfo();
        if ((uFlags & 1) != 0) {
            // the raw releases block minus one element, the cookie the count lives in
        }
        return pObjects;
    }
    pThis->~CPerformanceInfo();
    if ((uFlags & 1) != 0) operator delete(pObjects);
    return pObjects;
}

// 0x140ba11c0 — the name is stored as the caller's pointer, never copied, and it goes in
// before any of the loading. Ntdll is asked for the system information call, Kernel32 for
// the memory status call, and each export is kept only when its library loaded. The
// processor count replaces the one the constructor wrote. The counter setup at
// 0x140ba0600 and the reporter at 0x140ba04e0 follow, both still unported.
void CPerformanceInfoBase::Init(const char* pszName) {
    u148 = (uint64_t)(uintptr_t)pszName;
    hModule1 = g_PerformanceInfoApi.pfnLoadLibraryA("Ntdll.dll");
    if (hModule1 != nullptr) {
        pA0 = g_PerformanceInfoApi.pfnGetProcAddress(hModule1, "NtQuerySystemInformation");
    }
    hModule2 = g_PerformanceInfoApi.pfnLoadLibraryA("Kernel32.dll");
    if (hModule2 != nullptr) {
        pA8 = g_PerformanceInfoApi.pfnGetProcAddress(hModule2, "GlobalMemoryStatusEx");
    }
    uint32_t uProcessors = 0;
    g_PerformanceInfoApi.pfnGetSystemInfo(&uProcessors);
    uC0 = uProcessors;
    g_PerformanceInfoApi.pfnSetupCounters(this);
    g_PerformanceInfoApi.pfnLog(this, "Performance initialize success !");
}

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

// 0x140ba1270 — the name is spelled this way in the original
void CPerformanceInfo::Init(const char* pszName) {
    if (pBase != nullptr) ((CPerformanceInfoBase*)pBase)->Init(pszName);
}

// 0x140ba5cd0 — the name is spelled this way in the original
void CPerformanceInfo::RecrodPerformanceInfo() {
    if (pBase != nullptr) g_pfnPerformanceInfoBaseRecord(pBase);
}

}  // namespace tq

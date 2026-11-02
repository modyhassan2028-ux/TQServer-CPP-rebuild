// CQBase.dll v6159 — CPerformanceInfo handle (0x140ba03b0..0x140ba5ef0)
#include "modules/cqbase/src/performanceinfo.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
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

// 0x140ba51c0 — the system half of the report. The raw divides every byte count by one
// thousand and twenty four, rounding toward zero, which it does by adding 1023 to a
// negative value before the arithmetic shift.
static int64_t KbFromBytes(int64_t nValue) {
    return (int64_t)((uint64_t)nValue + (((uint64_t)nValue >> 63) & 1023)) >> 10;
}

// 0x140ba51c0 — four pointers have to be in place before anything is read, and the count
// of processes has to be positive, because every per process figure is divided by it
void CPerformanceInfoBase::RecordSystemCounters() {
    if (hModule1 == nullptr || hModule2 == nullptr || (int32_t)uC0 <= 0 || hQuery == nullptr) {
        return;
    }
    int32_t tNow = 0;
    g_PerformanceInfoApi.pfnTime(&tNow);
    struct tm* pTm = g_PerformanceInfoApi.pfnLocaltime(&tNow);
    // no stamp, no report: everything past this point is inside the timestamp check
    if (pTm == nullptr) return;
    char szStamp[100];
    strftime(szStamp, sizeof(szStamp), "%Y-%m-%d %H:%M:%S", pTm);
    g_PerformanceInfoApi.pfnLog(this,
        "*********************************PerformanceInfo [%s]*********************************",
        szStamp);
    g_PerformanceInfoApi.pfnLogSecond(this,
        "*********************************PerformanceInfo [%s]*********************************",
        szStamp);

    // the memory status block is cleared first, its length set second, then it is asked for
    uint8_t abMemStatus[0x40] = {0};
    if (pA8 != nullptr) {
        *(uint32_t*)abMemStatus = 0x40;
        ((void (*)(void*))pA8)(abMemStatus);
    }
    // the system information buffer is not cleared: a failed query leaves whatever was there
    uint8_t abSysPerf[0x138];
    if (pA0 != nullptr) {
        ((uint32_t (*)(int32_t, void*, uint32_t, uint32_t*))pA0)(2, abSysPerf, 0x138, nullptr);
    }

    // the first collect must report success or the whole report stops with its status; the
    // second one is asked again after a hundred milliseconds and a failure there is silent
    uint32_t uStatus = g_PerformanceInfoApi.pfnPdhCollectQueryData(hQuery);
    if (uStatus != 0) {
        g_PerformanceInfoApi.pfnLog(this, "PdhCollectQueryData fail. status: %ld", (long)uStatus);
        return;
    }
    g_PerformanceInfoApi.pfnSleepMs(100);
    if (g_PerformanceInfoApi.pfnPdhCollectQueryData(hQuery) != 0) return;

    auto ReadLong = [](void* hCounter) -> int64_t {
        PdhCounterValue value = {};
        if (g_PerformanceInfoApi.pfnPdhGetFormattedCounterValue(hCounter, 0x100, nullptr,
                                                                &value) != 0) {
            return 0;
        }
        return (int64_t)value.nLong;
    };
    auto ReadLarge = [](void* hCounter) -> int64_t {
        PdhCounterValue value = {};
        if (g_PerformanceInfoApi.pfnPdhGetFormattedCounterValue(hCounter, 0x400, nullptr,
                                                                &value) != 0) {
            return 0;
        }
        return value.nLarge;
    };

    int64_t nHandleCount = ReadLong(hHandleCount);
    int64_t nThreadCount = ReadLong(hThreads);
    int64_t nProcessCount = ReadLong(hProcesses);
    g_PerformanceInfoApi.pfnLog(this,
        "Handle Count:    %10ld     Thread Count:       %10ld     Process Count:           %6ld",
        (long)nHandleCount, (long)nThreadCount, (long)nProcessCount);

    int64_t nCache = KbFromBytes(ReadLarge(hCacheBytes));
    int64_t nCachePeak = KbFromBytes(ReadLarge(hCacheBytesPeak));
    int64_t nTotalPhys = *(int64_t*)(abMemStatus + 0x08);
    int64_t nAvailPhys = *(int64_t*)(abMemStatus + 0x10);
    g_PerformanceInfoApi.pfnLog(this,
        "Physical Total:  %10I64d K   Physical Available: %10I64d K   System Cache(Physical):%8I64d K   System Cache Peak(Physical):   %10I64d K",
        (long long)KbFromBytes(nTotalPhys), (long long)KbFromBytes(nAvailPhys),
        (long long)nCache, (long long)nCachePeak);

    int64_t nPoolPaged = KbFromBytes(ReadLarge(hPoolPaged));
    int64_t nPoolNonpaged = KbFromBytes(ReadLarge(hPoolNonpaged));
    g_PerformanceInfoApi.pfnLog(this,
        "Kernel Total:    %10I64d K   Kernel Paged:       %10I64d K   Kernel Nonpaged:     %10I64d K",
        (long long)(nPoolNonpaged + nPoolPaged), (long long)nPoolPaged,
        (long long)nPoolNonpaged);

    int64_t nCommitted = KbFromBytes(ReadLarge(hCommittedBytes));
    int64_t nCommitLimit = KbFromBytes(ReadLarge(hCommitLimit));
    // the peak comes out of the system information buffer, not from a counter: twenty bits,
    // in pages, four kilobytes each
    uint32_t uPeakCommit = *(uint32_t*)(abSysPerf + 0x38);
    int64_t nCommitPeak = (int64_t)(uint32_t)((uPeakCommit & 0xfffff) << 2);
    g_PerformanceInfoApi.pfnLog(this,
        "Commit Total:    %10I64d K   Commit Limit:       %10I64d K   Commit Peak:         %10ld K",
        (long long)nCommitted, (long long)nCommitLimit, (long)nCommitPeak);

    int64_t nPageFaults = ReadLong(hPageFaults);
    int64_t nPageReads = ReadLong(hPageReads);
    int64_t nPageWrites = ReadLong(hPageWrites);
    g_PerformanceInfoApi.pfnLog(this,
        "Page Fault(s):   %10ld     Page Reads(s):      %10ld     Page Writes(s):      %10ld",
        (long)nPageFaults, (long)nPageReads, (long)nPageWrites);

    int64_t nContextSwitches = ReadLong(hContextSwitches);
    int64_t nIoRead = ReadLong(hIoRead);
    int64_t nIoWrite = ReadLong(hIoWrite);
    int64_t nIoOther = ReadLong(hIoOther);
    g_PerformanceInfoApi.pfnLog(this,
        "Context Switch(s):%9ld     IO Read Operations(s):%8ld     IO Write Operations(s):%8ld     IO Other Operations(s):    %10ld",
        (long)nContextSwitches, (long)nIoRead, (long)nIoWrite, (long)nIoOther);
    // the raw hands the last two values it read to a call with an empty format, where they
    // are never formatted; kept because it is what the binary does
    g_PerformanceInfoApi.pfnLog(this, "", (long)nContextSwitches, (long)nIoRead);

    RecordProcessTable();   // the raw carries on into the table on the same path
}

// 0x140ba51c0 — the per process table: eleven label pointers, a header, then a row per node
// from the larger list. Not ported yet; the seam keeps the ordering of the raw visible.

// 0x140ba0a80 — the string comes first, then the dword the caller points at
void CPerformanceKeyNodeBuild(CPerformanceKeyNode* pNode, const std::string& strKey,
                              const uint32_t* pValue) {
    new (&pNode->strKey) std::string(strKey);
    pNode->uValue = *pValue;
}

// 0x140ba0ee0 — the copy takes the string from the source and then its dword
void CPerformanceKeyNodeCopy(CPerformanceKeyNode* pDst, const CPerformanceKeyNode* pSrc) {
    new (&pDst->strKey) std::string(pSrc->strKey);
    pDst->uValue = pSrc->uValue;
}

// 0x140ba0e90 — three links, six hundred bytes of payload at 0x18, then the flag pair in
// the order the raw writes them: the byte after the flag is cleared first.
void CPerformanceNode278Build(CPerformanceNode278* pNode, void* p0, void* p1, void* p2,
                              const void* pPayload, uint8_t uFlag270) {
    pNode->p0 = p0;
    pNode->p1 = p1;
    pNode->p2 = p2;
    memcpy((uint8_t*)pNode + 0x18, pPayload, 600);
    pNode->uFlag271 = 0;
    pNode->uFlag270 = uFlag270;
}

// 0x140ba5cd0 — the name is spelled this way in the original
void CPerformanceInfo::RecrodPerformanceInfo() {
    if (pBase != nullptr) g_pfnPerformanceInfoBaseRecord(pBase);
}


// 0x140ba51c0 (second half) — the per process table. The twelve column labels and the
// twelve values of every row come from the binary:
//   "%8s %25s %7s %12s %12s %13s %11s %11s %13s %10s %10s %10s"  (labels 0x140bcbc1c)
//   "%8d %25s %6.3f%% %10ld K %10ld K %11ld K %11ld %11ld %13ld %10ld %10ld %10ld"
// The cpu column divides the 0x8200 read of the payload's counter at +0x20 by the
// processor count at +0xC0, and leaves zero when the read is refused.
namespace {
struct RowWalk {
    CPerformanceInfoBase* pBase;
    uint32_t nRows;
};

int64_t KbFromCounter(CPerformanceInfoBase* pBase, const CPerformanceNode278* pNode,
                      size_t nOffset) {
    PdhCounterValue v = {};
    if (g_PerformanceInfoApi.pfnPdhGetFormattedCounterValue(
            pNode->CounterAt(nOffset), 0x400, nullptr, &v) != 0) {
        return 0;
    }
    return KbFromBytes(v.nLarge);
}

int64_t LongFromCounter(const CPerformanceNode278* pNode, size_t nOffset) {
    PdhCounterValue v = {};
    if (g_PerformanceInfoApi.pfnPdhGetFormattedCounterValue(
            pNode->CounterAt(nOffset), 0x100, nullptr, &v) != 0) {
        return 0;
    }
    return (int64_t)v.nLong;
}

// The row itself: every column in the order the format asks for them.
void RecordOneRow(void* pCtx, CPerformanceNode278* pNode) {
    RowWalk* pWalk = (RowWalk*)pCtx;
    CPerformanceInfoBase* pBase = pWalk->pBase;

    double dCpu = 0.0;
    {
        PdhCounterValue v = {};
        if (g_PerformanceInfoApi.pfnPdhGetFormattedCounterValue(
                pNode->CounterAt(0x20), 0x8200, nullptr, &v) == 0) {
            int32_t nDivisor = (int32_t)pBase->uC0;
            if (nDivisor < 1) nDivisor = 0;
            dCpu = v.dDouble / (double)nDivisor;
        }
    }
    long nMemory = (long)KbFromCounter(pBase, pNode, 0x58);
    long nPeak = (long)KbFromCounter(pBase, pNode, 0x60);
    long nPageFile = (long)KbFromCounter(pBase, pNode, 0x68);
    long nThreads = (long)LongFromCounter(pNode, 0x30);
    long nHandles = (long)LongFromCounter(pNode, 0x28);
    long nFaults = (long)LongFromCounter(pNode, 0x50);
    long nIoRead = (long)LongFromCounter(pNode, 0x40);
    long nIoWrite = (long)LongFromCounter(pNode, 0x48);
    long nIoOther = (long)LongFromCounter(pNode, 0x38);

    g_PerformanceInfoApi.pfnLog(pBase,
        "%8d %25s %6.3f%% %10ld K %10ld K %11ld K %11ld %11ld %13ld %10ld %10ld %10ld",
        pNode->ProcessId(), pNode->ProcessName(), dCpu, nMemory, nPeak, nPageFile,
        nThreads, nHandles, nFaults, nIoRead, nIoWrite, nIoOther);
}
}  // namespace

void CPerformanceInfoBase::RecordProcessTable() {
    if (hModule1 == nullptr || hModule2 == nullptr || (int32_t)uC0 <= 0 || hQuery == nullptr) {
        return;
    }
    g_PerformanceInfoApi.pfnLog(this,
        "%8s %25s %7s %12s %12s %13s %11s %11s %13s %10s %10s %10s",
        "PID", "Process", "CPU", "Memory", "MemoryPeak", "PageFileBytes",
        "ThreadCount", "HandleCount", "PageFaults(s)", "IO Read", "IO Write", "IO Other");

    RowWalk walk = { this, 0 };
    g_PerformanceInfoApi.pfnWalkListB(ListB(), &RecordOneRow, &walk);
}

}  // namespace tq

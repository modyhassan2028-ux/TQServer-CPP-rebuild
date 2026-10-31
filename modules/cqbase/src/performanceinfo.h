// ============================================================================
// performanceinfo.h — RAW CQBase.dll v6159 · CPerformanceInfo (the handle half)
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// The binary carries the file's own path inside two catch handlers:
//   f:\version\cqserver-78.0.11-1204\modules\cqbase\src\performanceinfo.cpp
//
// CPerformanceInfo is built exactly like CThreadTimesInfo next door: a table at
// +0x00 and a heap object of 0x150 bytes at +0x08 that does the measuring. Only
// the handle is here; the measuring object's Init, RecrodPerformanceInfo and
// RefreshPerformanceInfo belong to the rest of the same original file and are
// not ported yet.
//
// RAW QUIRKS KEPT:
//   1. The copy constructor and operator= copy the raw pointer, so two handles
//      own one measuring object and both destructors delete it.
//   2. operator= overwrites the pointer without deleting what it pointed at.
//   3. The destructor does NOT clear its pointer afterwards, unlike the thread
//      times handle next door which does.
// ============================================================================
#ifndef CQBASE_PERFORMANCEINFO_H
#define CQBASE_PERFORMANCEINFO_H

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <string>

namespace tq {

constexpr uint32_t kPerformanceInfoBaseSize = 0x150;

// The measuring object is built by the other half of performanceinfo.cpp, which is
// not ported yet. A null seam behaves exactly like a failed allocation.
typedef void* (*PfnNewPerformanceInfoBase)();
extern PfnNewPerformanceInfoBase g_pfnNewPerformanceInfoBase;

// The record body of the measuring object (0x140ba51c0) is that other half too.
typedef void (*PfnPerformanceInfoBaseRecord)(void* pBase);
extern PfnPerformanceInfoBaseRecord g_pfnPerformanceInfoBaseRecord;

// ---- the measuring object (the rest of performanceinfo.cpp) -------------------
// RAW QUIRKS KEPT:
//   * The constructor writes its fields in a fixed order that leaves a gap: the
//     dword at +0xC4 is never written, only the one at +0xC0.
//   * The destructor frees two loaded modules before it closes the query handle.
//   * A list node is created with a one at +0x48 (or +0x270) and a zero at the byte
//     after it, and the constructor then turns that zero into a one.

// 0x140ba1c20 — a fifty byte node, first three qwords cleared
struct CPerformanceNode50 {
    void* p0;              // +0x00
    void* p1;              // +0x08
    void* p2;              // +0x10
    std::string strName;   // +0x18  a 0x28 byte string in the original, destroyed on clear
    uint8_t padName[0x48 - 0x18 - sizeof(std::string)];
    uint8_t uFlag48;       // +0x48
    uint8_t uFlag49;       // +0x49
    uint8_t tail[0x06];
};

// 0x140ba1d20 — a six hundred and thirty two byte node, same shape
struct CPerformanceNode278 {
    void* p0;              // +0x00
    void* p1;              // +0x08
    void* p2;              // +0x10
    uint8_t unknown18[0x258];
    uint8_t uFlag270;      // +0x270
    uint8_t uFlag271;      // +0x271
    uint8_t tail[0x06];
};

// The two intrusive lists the measuring object keeps. Only what the ported half of the
// file touches is named; the middle is untouched by these units and left as it is.
struct CPerformanceList {
    void* pProxy;          // +0x00
    uint8_t unknown08[0x28];
    void* pHead;           // +0x30
    uint64_t nCount;       // +0x38
};

// What PdhGetFormattedCounterValue leaves behind: the status word, then the value. The
// 32 bits of padding keep the value's low dword where the raw reads it.
struct PdhCounterValue {
    uint32_t uStatus;   // +0
    uint32_t uPad;      // +4
    union {
        int32_t  nLong;     // +8   the type 0x100 reads
        int64_t  nLarge;    // +8   the type 0x400 reads
        double   dDouble;   // +8
    };
};
static_assert(offsetof(PdhCounterValue, nLong) == 8, "the value sits eight bytes in");

struct PerformanceInfoApi {
    void* (*pfnAlloc)(size_t);              // operator new
    void (*pfnFree)(void*);                 // operator delete
    int (*pfnFreeLibrary)(void* hModule);
    int (*pfnPdhCloseQuery)(void* hQuery);
    void* (*pfnLoadLibraryA)(const char*);  // LoadLibraryA
    void* (*pfnGetProcAddress)(void* hModule, const char* pszName);
    void (*pfnGetSystemInfo)(uint32_t* pNumberOfProcessors);
    void (*pfnSetupCounters)(void* pBase);  // 0x140ba0600, the PDH setup, not ported
    void (*pfnLog)(void* pBase, const char* pszFormat, ...);  // 0x140ba04e0
    // PdhOpenQueryA and PdhAddCounterA
    uint32_t (*pfnPdhOpenQueryA)(const char* pszSource, void* pUserData, void** ppQuery) =
        DefaultPdhOpenQueryA;
    uint32_t (*pfnPdhAddCounterA)(void* hQuery, const char* pszPath, uintptr_t uUserData,
                                 void** ppCounter) = DefaultPdhAddCounterA;
    uint32_t (*pfnPdhCollectQueryData)(void* hQuery) = DefaultPdhCollectQueryData;
    uint32_t (*pfnPdhGetFormattedCounterValue)(void* hCounter, uint32_t uType, void* pType,
                                               PdhCounterValue* pValue) =
        DefaultPdhGetFormattedCounterValue;
    void (*pfnSleepMs)(uint32_t uMs) = DefaultSleepMs;
    void (*pfnTime)(int32_t* pTime) = DefaultTime;
    struct tm* (*pfnLocaltime)(const int32_t* pTime) = DefaultLocaltime;
    void (*pfnLogSecond)(void* pBase, const char* pszFormat, const char* pszStamp) =
        DefaultLogSecond;               // 0x140ba4560, the second reporter
    // 0x140ba3c90 erases one node from the smaller list's tree and 0x140ba1a90 is what
    // the larger list calls before it deletes a node; both belong to the counter setup
    // that is still unported, so their hooks start empty.
    void (*pfnTreeEraseA)(void* pList, void* pNode) = DefaultTreeSteps;
    void (*pfnNodeDetachB)(void* pList, void* pNode) = DefaultTreeSteps;

    static void DefaultTreeSteps(void*, void*) {}
    static uint32_t DefaultPdhOpenQueryA(const char*, void*, void**) { return 1; }
    static uint32_t DefaultPdhAddCounterA(void*, const char*, uintptr_t, void**) { return 1; }
    static uint32_t DefaultPdhCollectQueryData(void*) { return 1; }
    static uint32_t DefaultPdhGetFormattedCounterValue(void*, uint32_t, void*,
                                                       PdhCounterValue* pValue) {
        if (pValue != nullptr) { pValue->uStatus = 1; pValue->uPad = 0; pValue->nLarge = 0; }
        return 1;
    }
    static void DefaultSleepMs(uint32_t) {}
    static void DefaultTime(int32_t* pTime) { if (pTime) *pTime = (int32_t)::time(nullptr); }
    static struct tm* DefaultLocaltime(const int32_t* pTime) {
        return ::localtime((const time_t*)pTime);
    }
    static void DefaultLogSecond(void*, const char*, const char*) {}
};
extern PerformanceInfoApi g_PerformanceInfoApi;

class CPerformanceInfoBase {
public:
    CPerformanceInfoBase();       // 0x140ba5df0
    void Init(const char* pszName);    // 0x140ba11c0
    void SetupCounters();              // 0x140ba0600, sixteen counter paths on one query
    void RecordSystemCounters();       // 0x140ba51c0 up to the process table
    void RecordProcessTable();         // 0x140ba51c0 from the table header on, not ported
    ~CPerformanceInfoBase();      // 0x140ba50b0
    static const void* const* Table();   // 0x140bcbb30, slot 0 is the deleting dtor

    CPerformanceList* ListA() { return &listA; }   // 0xC8, nodes of 0x50
    CPerformanceList* ListB() { return &listB; }   // 0x108, nodes of 0x278

    const void* pVt;              // +0x00
    void* hQuery;                 // +0x08  PdhCloseQuery takes it
    void* hCommittedBytes;        // +0x10  \Memory\Committed Bytes
    void* hCommitLimit;           // +0x18  \Memory\Commit Limit
    void* hPoolPaged;             // +0x20  \Memory\Pool Paged Bytes
    void* hPoolNonpaged;          // +0x28  \Memory\Pool Nonpaged Bytes
    void* hHandleCount;           // +0x30  \Process(_Total)\Handle Count
    void* hProcesses;             // +0x38  \System\Processes
    void* hThreads;               // +0x40  \System\Threads
    void* hCacheBytes;            // +0x48  \Memory\Cache Bytes
    void* hCacheBytesPeak;        // +0x50  \Memory\Cache Bytes Peak
    void* hPageFaults;            // +0x58  \Memory\Page Faults/sec
    void* hPageReads;             // +0x60  \Memory\Page Reads/sec
    void* hUnused68;              // +0x68  no counter is added here
    void* hPageWrites;            // +0x70  \Memory\Page Writes/sec
    void* hUnused78;              // +0x78  no counter is added here either
    void* hContextSwitches;       // +0x80  \System\Context Switches/sec
    void* hIoRead;                // +0x88  \Process(_Total)\IO Read Operations/sec
    void* hIoWrite;               // +0x90  \Process(_Total)\IO Write Operations/sec
    void* hIoOther;               // +0x98  \Process(_Total)\IO Other Operations/sec
    void* pA0;                    // +0xA0
    void* pA8;                    // +0xA8
    void* hModule1;               // +0xB0  FreeLibrary
    void* hModule2;               // +0xB8  FreeLibrary
    uint32_t uC0;                 // +0xC0  set to one, the dword after it is not written
    uint32_t uC4;                 // +0xC4
    CPerformanceList listA;       // +0xC8
    CPerformanceList listB;       // +0x108
    uint64_t u148;                // +0x148  cleared last, then Init stores a borrowed name
};

// A key node from the other container: a string at the front and one dword at 0x140.
struct CPerformanceKeyNode {
    std::string strKey;                              // +0x00
    uint8_t padKey[0x140 - sizeof(std::string)];      // up to the value
    uint32_t uValue;                                 // +0x140
};

// 0x140ba0a80 — a key node built from a string and a dword
void CPerformanceKeyNodeBuild(CPerformanceKeyNode* pNode, const std::string& strKey,
                              const uint32_t* pValue);
// 0x140ba0ee0 — and the pair copied from another node
void CPerformanceKeyNodeCopy(CPerformanceKeyNode* pDst, const CPerformanceKeyNode* pSrc);

// 0x140ba0e90 — the larger node is built from three links, a six hundred byte payload
// and one flag byte, with the byte after it cleared
void CPerformanceNode278Build(CPerformanceNode278* pNode, void* p0, void* p1, void* p2,
                              const void* pPayload, uint8_t uFlag270);

// 0x140ba2d50 — the smaller list is emptied from the top down
void CPerformanceInfoListClearA(CPerformanceList* pList);
// 0x140ba1f20 — the larger list is walked from its first node
void CPerformanceInfoListClearB(CPerformanceList* pList);
// 0x140ba42d0 — the smaller list's last step
void CPerformanceInfoListFinalA(CPerformanceList* pList);
// 0x140ba4340 — the larger list's last step (its rebalancing loop is not ported)
void CPerformanceInfoListFinalB(CPerformanceList* pList);
// 0x140ba04e0 — this file's reporter: a formatted line saved under the name it was given
void CPerformanceInfoLog(void* pBase, const char* pszFormat, ...);

// 0x140ba5cf0 and 0x140ba5d70 — a list's proxy plus its circular sentinel
void CPerformanceListInitA(CPerformanceList* pList);   // nodes of 0x50
void CPerformanceListInitB(CPerformanceList* pList);   // nodes of 0x278
// 0x140ba5ec0 — the object's first table slot
void* CPerformanceInfoBaseDeletingDtor(void* pBase, int nFlag);
void* CPerformanceInfoBaseNew();

// 0x140ba10b0 — the string a fifty byte node keeps at +0x18
void CPerformanceNode50DestroyName(void* pNode);

// 0x140ba10e0 and 0x140ba1130 — the handle's table slots for one object and for an array
void* CPerformanceInfoDeletingDtor(void* pObject, unsigned uFlags);
void* CPerformanceInfoArrayDeletingDtor(void* pObjects, unsigned uFlags);

class CPerformanceInfo {
public:
    CPerformanceInfo();                                    // 0x140ba5ef0
    void Init(const char* pszName);                        // 0x140ba1270 (forwards)
    CPerformanceInfo(const CPerformanceInfo& rOther);      // 0x140ba03b0
    CPerformanceInfo& operator=(const CPerformanceInfo&);  // 0x140ba03d0
    ~CPerformanceInfo();                                   // 0x140ba07e0

    void RecrodPerformanceInfo();                          // 0x140ba5cd0 (sic)

    const void* pVt;   // +0x00  0x140bcb008
    void* pBase;       // +0x08  the 0x150 byte measuring object
};

}  // namespace tq
#endif

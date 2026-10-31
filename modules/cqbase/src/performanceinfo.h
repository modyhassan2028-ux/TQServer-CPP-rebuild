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
    uint8_t unknown18[0x30];
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

struct PerformanceInfoApi {
    void* (*pfnAlloc)(size_t);              // operator new
    void (*pfnFree)(void*);                 // operator delete
    int (*pfnFreeLibrary)(void* hModule);
    int (*pfnPdhCloseQuery)(void* hQuery);
    void (*pfnListClear)(void* pList);      // 0x140ba2d50 for A, 0x140ba1f20 for B
    void (*pfnListFinal)(void* pList);      // 0x140ba42d0 for A, 0x140ba4340 for B
    void* (*pfnLoadLibraryA)(const char*);  // LoadLibraryA
    void* (*pfnGetProcAddress)(void* hModule, const char* pszName);
    void (*pfnGetSystemInfo)(uint32_t* pNumberOfProcessors);
    void (*pfnSetupCounters)(void* pBase);  // 0x140ba0600, the PDH setup, not ported
    void (*pfnLog)(void* pBase, const char* pszText);   // 0x140ba04e0, this file's reporter
};
extern PerformanceInfoApi g_PerformanceInfoApi;

class CPerformanceInfoBase {
public:
    CPerformanceInfoBase();       // 0x140ba5df0
    void Init(const char* pszName);   // 0x140ba11c0
    ~CPerformanceInfoBase();      // 0x140ba50b0
    static const void* const* Table();   // 0x140bcbb30, slot 0 is the deleting dtor

    CPerformanceList* ListA() { return &listA; }   // 0xC8, nodes of 0x50
    CPerformanceList* ListB() { return &listB; }   // 0x108, nodes of 0x278

    const void* pVt;              // +0x00
    void* hQuery;                 // +0x08  PdhCloseQuery takes it
    uint8_t unknown10[0x90];      // +0x10
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

// 0x140ba5cf0 and 0x140ba5d70 — a list's proxy plus its circular sentinel
void CPerformanceListInitA(CPerformanceList* pList);   // nodes of 0x50
void CPerformanceListInitB(CPerformanceList* pList);   // nodes of 0x278
// 0x140ba5ec0 — the object's first table slot
void* CPerformanceInfoBaseDeletingDtor(void* pBase, int nFlag);
void* CPerformanceInfoBaseNew();

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

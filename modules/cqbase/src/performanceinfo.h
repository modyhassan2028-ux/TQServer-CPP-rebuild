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

class CPerformanceInfo {
public:
    CPerformanceInfo();                                    // 0x140ba5ef0
    CPerformanceInfo(const CPerformanceInfo& rOther);      // 0x140ba03b0
    CPerformanceInfo& operator=(const CPerformanceInfo&);  // 0x140ba03d0
    ~CPerformanceInfo();                                   // 0x140ba07e0

    void RecrodPerformanceInfo();                          // 0x140ba5cd0 (sic)

    const void* pVt;   // +0x00  0x140bcb008
    void* pBase;       // +0x08  the 0x150 byte measuring object
};

}  // namespace tq
#endif

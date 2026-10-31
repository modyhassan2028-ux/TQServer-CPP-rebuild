// ============================================================================
// threadtimesinfo.h — RAW CQBase.dll v6159 · CThreadTimesInfo (the wrapper half)
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// The file name is the original's own: "modules\cqbase\src\threadtimesinfo.cpp"
// is one of the path strings the binary carries.
//
// CThreadTimesInfo is a two word handle: a table at +0x00 and a heap object of
// 0x50 bytes at +0x08 that does the measuring (CThreadTimesInfoBase). Only the
// handle is here; the measuring object's Init, Start and RecordThreadTimesInfo
// are the rest of the same original file and are not ported yet.
//
// RAW QUIRKS KEPT (all three are in the original, none are wanted behaviour):
//   1. The copy constructor and operator= copy the raw pointer, so two handles
//      share one measuring object and both destructors delete it.
//   2. operator= overwrites the pointer without deleting what it pointed at, so
//      the previous object leaks.
//   3. The destructor calls the object's first table slot with (this, 1), the
//      deleting destructor, and only then clears its own pointer.
// ============================================================================
#ifndef CQBASE_THREADTIMESINFO_H
#define CQBASE_THREADTIMESINFO_H

#include <cstdint>

namespace tq {

constexpr uint32_t kThreadTimesInfoBaseSize = 0x50;

// The measuring object is built by the other half of threadtimesinfo.cpp, which
// is not ported yet. Until it is, this seam stands in for "new 0x50 bytes and
// construct them"; a null seam behaves exactly like a failed allocation.
typedef void* (*PfnNewThreadTimesInfoBase)();
extern PfnNewThreadTimesInfoBase g_pfnNewThreadTimesInfoBase;

class CThreadTimesInfo {
public:
    CThreadTimesInfo();                                       // 0x140bb5670
    CThreadTimesInfo(const CThreadTimesInfo& rOther);         // 0x140bb3850
    CThreadTimesInfo& operator=(const CThreadTimesInfo&);     // 0x140bb3870
    ~CThreadTimesInfo();                                      // 0x140bb3960

    const void* pVt;   // +0x00  0x140bcde50
    void* pBase;       // +0x08  the 0x50 byte measuring object
};

}  // namespace tq
#endif

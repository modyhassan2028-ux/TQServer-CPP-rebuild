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
#include <vector>

namespace tq {

constexpr uint32_t kThreadTimesInfoBaseSize = 0x50;

// One sample in the list the measuring object keeps. Evidence from the binary:
// the element stride is 0x10 (`>> 4` in the iterator distance at 0x140bb3b30) and
// an element copy moves exactly two qwords (0x140bb51c0). What each qword holds is
// settled by Init, Start and RecordThreadTimesInfo, which are not ported yet, so
// they are positional names rather than invented meanings.
struct CThreadTimesSample {
    uint64_t uField00;
    uint64_t uField08;
};

class CThreadTimesInfoBase {
public:
    CThreadTimesInfoBase();     // 0x140bb5590
    ~CThreadTimesInfoBase();    // 0x140bb5800

    static const void* const* Table();   // 0x140bce3c8, slot 0 is the deleting dtor

    const void* pVt;                           // +0x00
    std::vector<CThreadTimesSample> vSamples;  // +0x08, a debug level STL vector
    uint64_t uField28;                         // +0x28
    uint64_t uField30;                         // +0x30
    uint64_t uField38;                         // +0x38
    uint32_t uField40;                         // +0x40
    uint32_t uField44;                         // +0x44
    uint32_t uField48;                         // +0x48
    uint8_t uField4C;                          // +0x4c
};

// 0x140bb5800 — the object's first table slot: it destroys, and frees only when the
// flag asks. It returns the pointer it was handed either way.
void* CThreadTimesInfoBaseDeletingDtor(void* pBase, int nFlag);
// operator new(0x50) then the constructor
void* CThreadTimesInfoBaseNew();

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

// CQBase.dll v6159 — CPerformanceInfo handle (0x140ba03b0..0x140ba5ef0)
#include "modules/cqbase/src/performanceinfo.h"

namespace tq {

static const void* const kCPerformanceInfoVt[1] = { nullptr };

static void* DefaultNewPerformanceInfoBase() { return nullptr; }
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

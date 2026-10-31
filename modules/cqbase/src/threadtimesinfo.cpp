// CQBase.dll v6159 — CThreadTimesInfo handle (0x140bb3850..0x140bb3960, 0x140bb5670)
#include "modules/cqbase/src/threadtimesinfo.h"

namespace tq {

static void* DefaultNewThreadTimesInfoBase() { return nullptr; }
PfnNewThreadTimesInfoBase g_pfnNewThreadTimesInfoBase = DefaultNewThreadTimesInfoBase;

// The handle's own table. Nothing in the binary calls through it, the wrapper's
// destructor is not virtual, but the original stores a table at +0x00, so the
// member exists and points at a table of this object's own.
static const void* const kCThreadTimesInfoVt[1] = { nullptr };

// 0x140bb5670
CThreadTimesInfo::CThreadTimesInfo() : pVt(kCThreadTimesInfoVt), pBase(nullptr) {
    pBase = g_pfnNewThreadTimesInfoBase();
}

// 0x140bb3850 — shares the measuring object with the one it copies
CThreadTimesInfo::CThreadTimesInfo(const CThreadTimesInfo& rOther)
    : pVt(kCThreadTimesInfoVt), pBase(rOther.pBase) {}

// 0x140bb3870 — overwrites the pointer, the old object is not released
CThreadTimesInfo& CThreadTimesInfo::operator=(const CThreadTimesInfo& rOther) {
    pBase = rOther.pBase;
    return *this;
}

// 0x140bb3960 — the object goes through its own first table slot with (this, 1)
CThreadTimesInfo::~CThreadTimesInfo() {
    if (pBase != nullptr) {
        typedef void (*PfnDeletingDtor)(void*, int);
        void** ppVt = *(void***)pBase;
        ((PfnDeletingDtor)ppVt[0])(pBase, 1);
    }
    pBase = nullptr;
}

}  // namespace tq

// CQBase.dll v6159 — CThreadTimesInfo handle (0x140bb3850..0x140bb3960, 0x140bb5670)
#include "modules/cqbase/src/threadtimesinfo.h"

namespace tq {

// 0x140bce3c8 — slot 0 is the deleting destructor, nothing else is called through
// this table by the handle.
static const void* const kCThreadTimesInfoBaseVt[1] = {
    (const void*)&CThreadTimesInfoBaseDeletingDtor,
};

const void* const* CThreadTimesInfoBase::Table() { return kCThreadTimesInfoBaseVt; }

// 0x140bb5590 — the table, an empty sample list, then every measuring field zeroed.
// The list is a debug level STL vector, which is why the raw builds a proxy object
// with operator new(8) at the container's start and links it before returning.
CThreadTimesInfoBase::CThreadTimesInfoBase()
    : pVt(kCThreadTimesInfoBaseVt),
      vSamples(),
      uField28(0),
      uField30(0),
      uField38(0),
      uField40(0),
      uField44(0),
      uField48(0),
      uField4C(0) {}

// 0x140bb5800
CThreadTimesInfoBase::~CThreadTimesInfoBase() { pVt = kCThreadTimesInfoBaseVt; }

void* CThreadTimesInfoBaseNew() { return new CThreadTimesInfoBase(); }

void* CThreadTimesInfoBaseDeletingDtor(void* pBase, int nFlag) {
    CThreadTimesInfoBase* pObj = (CThreadTimesInfoBase*)pBase;
    pObj->~CThreadTimesInfoBase();
    if ((nFlag & 1) != 0) operator delete(pBase);
    return pBase;
}

PfnNewThreadTimesInfoBase g_pfnNewThreadTimesInfoBase = CThreadTimesInfoBaseNew;

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

// ============================================================================
// synarenicmeed.cpp — RAW Syndicate.dll v6159 · CSynArenicMeed::InstanceGet
// ============================================================================
#include "modules/syndicate/src/synarenicmeed.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"

namespace tq {

static const char kSynArenicMeedSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synarenicmeed.cpp";

// 0x141781b60
CSynArenicMeed* CSynArenicMeed::InstanceGet() {
    static CSynArenicMeed* spSelf = nullptr;
    if (spSelf == nullptr) {
        static CMyHeap sHeap("CSynArenicMeed");
        CSynArenicMeed* pMem = (CSynArenicMeed*)sHeap.Alloc(8);
        if (pMem == nullptr) {
            spSelf = nullptr;
        } else {
            pMem->u0 = 0;      // the whole object, eight bytes of zero
            spSelf = pMem;
        }
        if (spSelf == nullptr) {
            log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "MYASSERT", "m_pSelf",
                               kSynArenicMeedSource, 0x5bd);
        }
    }
    return spSelf;
}

}  // namespace tq

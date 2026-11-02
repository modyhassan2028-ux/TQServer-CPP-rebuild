// ============================================================================
// crossvlmresult.cpp — RAW Syndicate.dll v6159 · CCrossVlmResult::InstanceGet
// ============================================================================
#include "modules/syndicate/src/crossvlmresult.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"

namespace tq {

static const char kCrossVlmResultSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\crossvlmresult.cpp";

static CCrossVlmResult* DefaultConstructCrossVlmResult(void* pMem) {
    return (CCrossVlmResult*)pMem;
}
CCrossVlmResult* (*g_pfnConstructCrossVlmResult)(void* pMem) =
    DefaultConstructCrossVlmResult;

// 0x141741a30 — the member is only built once; a build that comes back empty is reported
// and answered as it is, so the next call tries again.
CCrossVlmResult* CCrossVlmResult::InstanceGet() {
    static CCrossVlmResult* spSelf = nullptr;
    if (spSelf == nullptr) {
        static CMyHeap sHeap("CCrossVlmResult");
        void* pMem = sHeap.Alloc(0x38);
        spSelf = (pMem == nullptr) ? nullptr : g_pfnConstructCrossVlmResult(pMem);
        if (spSelf == nullptr) {
            log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "MYASSERT", "m_pSelf",
                               kCrossVlmResultSource, 0x32);
        }
    }
    return spSelf;
}

}  // namespace tq

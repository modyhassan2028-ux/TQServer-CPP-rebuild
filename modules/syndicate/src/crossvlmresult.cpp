// ============================================================================
// crossvlmresult.cpp — RAW Syndicate.dll v6159 · the constructor and the one place the
//   class is ever made. The order of the stores is the order of the binary and it matters:
//   the node is linked first, the three qwords are cleared, the list hook runs, and only
//   then is +0x00 written.
// ============================================================================
#include "modules/syndicate/src/crossvlmresult.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"

namespace tq {

static const char kCrossVlmResultSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\crossvlmresult.cpp";

static void DefaultInitCrossVlmList(void**) {}
void (*g_pfnInitCrossVlmList)(void** ppListHead) = DefaultInitCrossVlmList;

// 0x141741840 — operator new(8) makes the node, the node points back at the head, and a
// failed allocation leaves the head null rather than making one up.
CCrossVlmResult* CCrossVlmResult::Construct() {
    SynListNode** ppHead = (SynListNode**)((char*)this + 0x08);
    SynListNode* pNode = (SynListNode*)::operator new(8);
    SynListNode* pLink = nullptr;
    if (pNode != nullptr) {
        pNode->pNext = (SynListNode*)ppHead;
        pLink = pNode;
    }
    *ppHead = pLink;
    *(uint64_t*)((char*)this + 0x20) = 0;
    *(uint64_t*)((char*)this + 0x28) = 0;
    *(uint64_t*)((char*)this + 0x30) = 0;
    g_pfnInitCrossVlmList((void**)ppHead);
    *(uint64_t*)((char*)this + 0x00) = 0;
    return this;
}

static CCrossVlmResult* DefaultConstructCrossVlmResult(void* pMem) {
    return ((CCrossVlmResult*)pMem)->Construct();
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

// ============================================================================
// syncountry.cpp — RAW Syndicate.dll v6159 · the sweeps as the binary runs them: walk the
//   map in order, deal with each record, then erase the tree from the head's own parent
//   pointer, deleting every node, and finally point the head's three links at itself and
//   zero the count. The neighbouring map is only torn down, its records are never touched.
// ============================================================================
#include "modules/syndicate/src/syncountry.h"
#include "modules/cqbase/src/logkernel.h"

#include <new>

namespace tq {

static_assert(sizeof(SynCountryNode) == 0x38, "the swept node is 0x38 bytes");
static_assert(offsetof(SynCountryNode, pRecord) == 0x20, "the record sits at +0x20");
static_assert(offsetof(SynCountryNode, uNil) == 0x29, "the nil byte sits at +0x29");
static_assert(sizeof(SynMapHolder) == 0x40, "the holder is 0x40 bytes");
static_assert(offsetof(SynMapHolder, pHead) == 0x30, "the head sits at +0x30");
static_assert(offsetof(SynMapHolder, uCount) == 0x38, "the count sits at +0x38");

static const char kCountrySource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\country.cpp";

// ---- the callback the sweeps call for a record they want to keep
static void DefaultMoveRecord(void*, void*, void*, void*) {}
void (*g_pfnCountryMoveRecord)(void* pSelf, void* pRecord, void* a3, void* a4) =
    DefaultMoveRecord;

// ---- 0x1417262c0 / 0x141726310 / 0x141726360: right subtree first, then the node itself,
//      walking down the left links
static void SynNodeEraseAt(void* pCtx, void* pNode, size_t uNilOff) {
    uint8_t uNil = *(uint8_t*)((char*)pNode + uNilOff);
    while (uNil == 0) {
        void* pRight = *(void**)((char*)pNode + 0x10);
        SynNodeEraseAt(pCtx, pRight, uNilOff);
        void* pNext = *(void**)((char*)pNode + 0x00);
        ::operator delete(pNode);
        pNode = pNext;
        uNil = *(uint8_t*)((char*)pNode + uNilOff);
    }
}

void SynNodeErase29(void* pCtx, void* pNode) { SynNodeEraseAt(pCtx, pNode, 0x29); }
void SynNodeErase49(void* pCtx, void* pNode) { SynNodeEraseAt(pCtx, pNode, 0x49); }
void SynNodeErase1d(void* pCtx, void* pNode) { SynNodeEraseAt(pCtx, pNode, 0x1d); }

// ---- the successor the sweeps step with, inlined there exactly as it is here
static SynCountryNode* SynSuccessor(SynCountryNode* pNode, SynCountryNode* pHead) {
    // a nil node here is where the raw trips its debug assert; this port ends the walk
    // instead of spinning on the same node, and says so rather than inventing new work
    if (*(uint8_t*)((char*)pNode + 0x29) != 0) return pHead;
    void* pRight = *(void**)((char*)pNode + 0x10);
    if (*(uint8_t*)((char*)pRight + 0x29) == 0) {
        pNode = (SynCountryNode*)pRight;
        void* pLeft = *(void**)pRight;
        while (*(uint8_t*)((char*)pLeft + 0x29) == 0) {
            pNode = (SynCountryNode*)pLeft;
            pLeft = *(void**)pLeft;
        }
        return pNode;
    }
    void* pParent = *(void**)((char*)pNode + 0x08);
    if (*(uint8_t*)((char*)pParent + 0x29) != 0) return (SynCountryNode*)pParent;
    while (pNode == (SynCountryNode*)*(void**)((char*)pParent + 0x10)) {
        pNode = (SynCountryNode*)pParent;
        pParent = *(void**)((char*)pParent + 0x08);
        if (*(uint8_t*)((char*)pParent + 0x29) != 0) break;
    }
    return (SynCountryNode*)pParent;
}

// ---- the tree teardown: from the head's parent, erase every node and delete it, then
//      point the head's three links at itself and zero the count. The head itself survives.
static void SynCountryTeardown(void* pSelf, size_t uHolderOff, size_t uHeadOff,
                               size_t uCountOff, size_t uNilOff,
                               void (*pfnErase)(void*, void*)) {
    uint8_t* p = (uint8_t*)pSelf;
    void* pHead = *(void**)(p + uHeadOff);
    void* pNode = *(void**)((char*)pHead + 0x08);
    uint8_t uNil = *(uint8_t*)((char*)pNode + uNilOff);
    while (uNil == 0) {
        pfnErase(p + uHolderOff, *(void**)((char*)pNode + 0x10));
        void* pNext = *(void**)pNode;
        ::operator delete(pNode);
        pNode = pNext;
        uNil = *(uint8_t*)((char*)pNode + uNilOff);
    }
    pHead = *(void**)(p + uHeadOff);                        // the raw reloads it every store
    *(void**)((char*)pHead + 0x08) = pHead;
    *(uint64_t*)(p + uCountOff) = 0;
    pHead = *(void**)(p + uHeadOff);
    *(void**)pHead = pHead;
    pHead = *(void**)(p + uHeadOff);
    *(void**)((char*)pHead + 0x10) = pHead;
}

// ---- one sweep: the walk, then the teardown of the same map, then the neighbour's
static void SynCountrySweep(void* pSelf, uint8_t uDestroy, void* a3, void* a4,
                            size_t uHolderOff, size_t uHeadOff, size_t uCountOff,
                            size_t uTailHolderOff, size_t uTailHeadOff, size_t uTailCountOff,
                            uint32_t uLogLine) {
    uint8_t* p = (uint8_t*)pSelf;
    void* pHead = *(void**)(p + uHeadOff);
    SynCountryNode* pNode = (SynCountryNode*)*(void**)pHead;    // the head's first link
    while ((void*)pNode != pHead) {
        void* pRecord = *(void**)((char*)pNode + 0x20);
        if (pRecord == nullptr) {
            log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECK", "NULL != pRec",
                               kCountrySource, uLogLine);
        } else if (uDestroy == 0) {
            (*(void (**)(void*, uint64_t)) * (void**)pRecord)(pRecord, 1);   // slot zero, flag 1
        } else {
            g_pfnCountryMoveRecord(pSelf, pRecord, a3, a4);
        }
        pNode = SynSuccessor(pNode, (SynCountryNode*)pHead);
    }
    SynCountryTeardown(pSelf, uHolderOff, uHeadOff, uCountOff, 0x29, &SynNodeErase29);
    SynCountryTeardown(pSelf, uTailHolderOff, uTailHeadOff, uTailCountOff, 0x49,
                       &SynNodeErase49);
}

// 0x1417364e0 — the holders at +0x90 and +0x150
void SynCountrySweepA(void* pSelf, uint8_t uDestroy, void* a3, void* a4) {
    SynCountrySweep(pSelf, uDestroy, a3, a4, 0x90, 0xc0, 0xc8, 0x150, 0x180, 0x188, 0xdf);
}

// 0x141736750 — the same body one holder over: +0xd0 and +0x190
void SynCountrySweepB(void* pSelf, uint8_t uDestroy, void* a3, void* a4) {
    SynCountrySweep(pSelf, uDestroy, a3, a4, 0xd0, 0x100, 0x108, 0x190, 0x1c0, 0x1c8, 0xf5);
}

}  // namespace tq

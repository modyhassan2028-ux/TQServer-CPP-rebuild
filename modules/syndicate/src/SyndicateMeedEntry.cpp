// SyndicateMeedEntry.cpp — D55a/T16: verbatim
// from Syndicate.dll.decompiled.c. See the .h
// for the address map. NO guessed logic: every
// statement follows the decompile text.
#include "modules/syndicate/src/SyndicateMeedEntry.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"  // the op new/delete seams
#include <new>          // std::bad_alloc
#include <cstring>

namespace syndicate {

// ---- the seams ----
char (*g_fnMeedEntryCmp)(const MeedEntry5*,
                         const MeedEntry5*) = nullptr;

// ---------- FUN_141780750: the entry swap ----------
void MeedEntrySwap5(MeedEntry5* a, MeedEntry5* b) {
    if (a == (MeedEntry5*)b) {
        return;                     // (param_1 != param_2)
    }
    MeedEntry5 t;
    t.v[0] = a->v[0];
    t.v[1] = a->v[1];
    t.v[2] = a->v[2];
    t.v[3] = a->v[3];
    t.v[4] = a->v[4];
    a->v[0] = b->v[0];
    a->v[1] = b->v[1];
    a->v[2] = b->v[2];
    a->v[3] = b->v[3];
    a->v[4] = b->v[4];
    b->v[0] = t.v[0];
    b->v[1] = t.v[1];
    b->v[2] = t.v[2];
    b->v[3] = t.v[3];
    b->v[4] = t.v[4];
}

// ---------- FUN_1417820e0: the fwd copy ----------
MeedEntry5* MeedEntryCopyFwd(MeedEntry5* p1,
                             MeedEntry5* p2,
                             MeedEntry5* p3) {
    for (; p1 != p2; p1 = p1 + 1) {
        if (p3 != nullptr) {
            p3->v[0] = p1->v[0];
            p3->v[1] = p1->v[1];
            p3->v[2] = p1->v[2];
            p3->v[3] = p1->v[3];
            p3->v[4] = p1->v[4];
        }
        p3 = p3 + 1;
    }
    return p3;
}

// ---------- FUN_141782c20: the bwd copy ----------
int64_t MeedEntryCopyBwd(int64_t p1, int64_t p2,
                         int64_t p3) {
    int64_t lVar1;
    if (p1 != p2) {
        lVar1 = p3 - p2;
        int64_t lVar2 = p2;
        int64_t lVar3;
        do {
            lVar3 = lVar2 - 0x14;
            *(int32_t*)(lVar1 + lVar3) =
                *(int32_t*)(lVar2 - 0x14);
            *(int32_t*)(lVar1 + 4 + lVar3) =
                *(int32_t*)(lVar2 - 0x10);
            *(int32_t*)(lVar1 + 8 + lVar3) =
                *(int32_t*)(lVar2 - 0xc);
            *(int32_t*)(lVar1 + 0xc + lVar3) =
                *(int32_t*)(lVar2 - 8);
            *(int32_t*)(lVar1 + 0x10 + lVar3) =
                *(int32_t*)(lVar2 - 4);
            lVar2 = lVar3;
        } while (lVar3 != p1);
    }
    return p3 + ((p2 - p1) / 0x14) * -0x14;
}

// ---------- FUN_141782480: the copy-backward
// variant ----------
int64_t MeedEntryCopyTo(MeedEntry5* p1,
                        MeedEntry5* p2,
                        int64_t p3) {
    if (p1 != p2) {
        int64_t lVar1 = p3 - (int64_t)p1;
        MeedEntry5* puVar2 = p1;
        MeedEntry5* puVar3;
        do {
            puVar3 = puVar2 + 1;
            *(int32_t*)(lVar1 + -0x14 +
                        (int64_t)puVar3) = puVar2->v[0];
            *(int32_t*)(lVar1 + -0x10 +
                        (int64_t)puVar3) = puVar2->v[1];
            *(int32_t*)(lVar1 + -0xc +
                        (int64_t)puVar3) = puVar2->v[2];
            *(int32_t*)(lVar1 + -8 +
                        (int64_t)puVar3) = puVar2->v[3];
            *(int32_t*)(lVar1 + -4 +
                        (int64_t)puVar3) = puVar2->v[4];
            puVar2 = puVar3;
        } while (puVar3 != p2);
    }
    return p3 +
        (((int64_t)p2 - (int64_t)p1) / 0x14) * 0x14;
}

// ---------- FUN_141782550: the fill-copy ----------
void MeedEntryFillCopy(MeedEntry5* p1, int64_t n,
                       const MeedEntry5* pSrc) {
    for (; n != 0; n = n + -1) {
        if (p1 != nullptr) {
            p1->v[0] = pSrc->v[0];
            p1->v[1] = pSrc->v[1];
            p1->v[2] = pSrc->v[2];
            p1->v[3] = pSrc->v[3];
            p1->v[4] = pSrc->v[4];
        }
        p1 = p1 + 1;
    }
}

// ---------- FUN_141782060: the rotate-backward ----------
int64_t MeedEntryRotBwd(int64_t p1, int64_t p2,
                        int64_t p3) {
    if (p1 != p2) {
        int64_t lVar1 = p3 - p2;
        int64_t lVar2 = p2;
        int64_t lVar3;
        do {
            lVar3 = lVar2 - 0x14;
            *(int32_t*)(lVar1 + lVar3) =
                *(int32_t*)(lVar2 - 0x14);
            *(int32_t*)(lVar1 + 4 + lVar3) =
                *(int32_t*)(lVar2 - 0x10);
            *(int32_t*)(lVar1 + 8 + lVar3) =
                *(int32_t*)(lVar2 - 0xc);
            *(int32_t*)(lVar1 + 0xc + lVar3) =
                *(int32_t*)(lVar2 - 8);
            *(int32_t*)(lVar1 + 0x10 + lVar3) =
                *(int32_t*)(lVar2 - 4);
            lVar2 = lVar3;
        } while (lVar3 != p1);
    }
    return p3 + ((p2 - p1) / 0x14) * -0x14;
}

// ---------- FUN_141781ca0: the alloc ----------
void* MeedEntryAlloc(void* /*pCookie*/, uint64_t n) {
    if (n != 0 &&
        (0xffffffffffffffffULL / n) < 0x14) {
        throw std::bad_alloc();
    }
    return g_fnMeritOpNew(n * 0x14);
}

// ---------- FUN_141783b70: the generic insert ----------
// vec layout: {proxy@0, .., begin@0x18,
// end@0x20, cap@0x28}
void MeedEntryVecInsert(
    void* pVec, void* pPair[2], uint64_t n,
    const MeedEntry5* pSrc) {
    char* vc = (char*)pVec;
    MeedEntry5** ppBegin =
        (MeedEntry5**)(vc + 0x18);
    MeedEntry5** ppEnd =
        (MeedEntry5**)(vc + 0x20);
    MeedEntry5** ppCap =
        (MeedEntry5**)(vc + 0x28);
    MeedEntry5** ppProxy = (MeedEntry5**)pVec;
    MeedEntry5* pPos =
        (MeedEntry5*)pPair[1];

    MeedEntry5* pBegin = *ppBegin;
    uint64_t uVar6;
    if (pBegin == nullptr) {
        uVar6 = 0;
    } else {
        uVar6 = *ppCap - pBegin;
    }
    if (n == 0) {
        return;
    }
    MeedEntry5* pEnd = *ppEnd;
    int64_t lVar2 = ((int64_t)pEnd -
                     (int64_t)pBegin) / 0x14;
    if (0xcccccccccccccccU - lVar2 < n) {
        // FUN_141780330: the length_error abort
        // (noreturn in the original)
        __builtin_unreachable();
    }
    uint64_t uVar1 = lVar2 + n;
    if (uVar6 < uVar1) {
        // the grow path
        if (0xcccccccccccccccU -
                (uVar6 >> 1) < uVar6) {
            uVar6 = 0;
        } else {
            uVar6 = uVar6 + (uVar6 >> 1);
        }
        if (uVar6 < uVar1) {
            uVar6 = uVar1;
        }
        MeedEntry5* puVar4 =
            (MeedEntry5*)MeedEntryAlloc(
                vc + 0x10, uVar6);
        lVar2 = ((int64_t)pPos -
                 (int64_t)pBegin) / 0x14;
        MeedEntryFillCopy(puVar4 + lVar2, n,
                          pSrc);
        MeedEntryCopyFwd(pBegin, pPos, puVar4);
        MeedEntryCopyFwd(pPos, pEnd,
                         puVar4 + lVar2 + n);
        void* pvVar3 = pBegin;
        int64_t lEnd =
            (int64_t)*ppEnd - (int64_t)pBegin;
        if (pvVar3 != nullptr) {
            g_fnMeritOpDelete(pvVar3);
        }
        *ppCap = puVar4 + uVar6;
        *ppEnd = puVar4 +
                 (n + lEnd / 0x14);
        *ppBegin = puVar4;
    } else if ((uint64_t)(((int64_t)pEnd -
                 (int64_t)pPos) / 0x14) < n) {
        // the move-forward path
        MeedEntry5 local;
        local.v[0] = pSrc->v[0];
        local.v[1] = pSrc->v[1];
        local.v[2] = pSrc->v[2];
        local.v[3] = pSrc->v[3];
        local.v[4] = pSrc->v[4];
        MeedEntryCopyFwd(pPos, pEnd, pPos + n);
        MeedEntryFillCopy(
            *ppEnd,
            n - ((int64_t)*ppEnd -
                 (int64_t)pPos) / 0x14,
            &local);
        *ppEnd =
            (MeedEntry5*)((int64_t)*ppEnd +
                         n * 0x14);
        int64_t lVar2b = (int64_t)*ppEnd;
        for (MeedEntry5* puVar4b = pPos;
             puVar4b !=
             (MeedEntry5*)(lVar2b +
                           (int64_t)n * -0x14);
             puVar4b = puVar4b + 1) {
            puVar4b->v[0] = local.v[0];
            puVar4b->v[1] = local.v[1];
            puVar4b->v[2] = local.v[2];
            puVar4b->v[3] = local.v[3];
            puVar4b->v[4] = local.v[4];
        }
    } else {
        // the tail-insert path
        MeedEntry5 local;
        local.v[0] = pSrc->v[0];
        local.v[1] = pSrc->v[1];
        local.v[2] = pSrc->v[2];
        local.v[3] = pSrc->v[3];
        local.v[4] = pSrc->v[4];
        MeedEntry5* puVar5 = MeedEntryCopyFwd(
            pEnd - n, pEnd, pEnd);
        *ppEnd = puVar5;
        MeedEntryCopyBwd((int64_t)pPos,
                         (int64_t)(pEnd - n),
                         (int64_t)pEnd);
        for (MeedEntry5* puVar5b = pPos;
             puVar5b != pPos + n;
             puVar5b = puVar5b + 1) {
            puVar5b->v[0] = local.v[0];
            puVar5b->v[1] = local.v[1];
            puVar5b->v[2] = local.v[2];
            puVar5b->v[3] = local.v[3];
            puVar5b->v[4] = local.v[4];
        }
    }
}

// ---------- FUN_141784100: the push-grow ----------
void MeedEntryVecGrow(void* pVec, void* pPair[2],
                      const MeedEntry5* pSrc) {
    char* vc = (char*)pVec;
    MeedEntry5** ppBegin =
        (MeedEntry5**)(vc + 0x18);
    MeedEntry5** ppEnd =
        (MeedEntry5**)(vc + 0x20);
    MeedEntry5* pBegin = *ppBegin;
    int64_t lVar4 = 0;
    int64_t lVar5 =
        (int64_t)*ppEnd - (int64_t)pBegin;
    int64_t lVar6 = lVar5 >> 0x3f;
    if (lVar5 / 0x14 + lVar6 != lVar6) {
        lVar4 = ((int64_t)pPair[1] -
                 (int64_t)pBegin) / 0x14;
    }
    void* local_28[2];
    local_28[0] = pPair[0];
    local_28[1] = pPair[1];
    MeedEntryVecInsert(pVec, local_28, 1, pSrc);
    pBegin = *ppBegin;
    void* plVar2 = *(void**)pVec;   // the proxy
    uint64_t uVar1 =
        (uint64_t)((int64_t)pBegin + lVar4 * 0x14);
    // (the iterator fix-up bounds gates: the
    //  proxy dereference checks — elided in
    //  the port build, they only trap in
    //  _ITERATOR_DEBUG builds)
    (void)plVar2;
    (void)uVar1;
    // *param_2 = the recomputed pair
    void** pOut = (void**)pPair;
    pOut[0] = *(void**)pVec;
    pOut[1] = (void*)((int64_t)*ppBegin +
                      lVar4 * 0x14);
}

// ---------- FUN_1417848f0: the push ----------
void MeedEntryVecPush(void* pVec,
                      const MeedEntry5* pEntry) {
    char* vc = (char*)pVec;
    MeedEntry5** ppBegin =
        (MeedEntry5**)(vc + 0x18);
    MeedEntry5** ppEnd =
        (MeedEntry5**)(vc + 0x20);
    MeedEntry5** ppCap =
        (MeedEntry5**)(vc + 0x28);
    MeedEntry5* pBegin = *ppBegin;
    uint64_t uVar3;
    if (pBegin == nullptr) {
        uVar3 = 0;
    } else {
        uVar3 = *ppCap - pBegin;
    }
    MeedEntry5* pEnd = *ppEnd;
    if ((uint64_t)(((int64_t)pEnd -
                    (int64_t)pBegin) / 0x14) <
        uVar3) {
        // the direct store
        MeedEntryFillCopy(pEnd, 1, pEntry);
        *ppEnd = pEnd + 1;
        return;
    }
    // the grow path
    void* local_28[2];
    local_28[0] = *(void**)pVec;
    local_28[1] = pEnd;
    MeedEntryVecGrow(pVec, local_28, pEntry);
}

// ---------- FUN_141783ad0: the erase-tail ----------
void MeedEntryVecEraseTail(void* pVec) {
    char* vc = (char*)pVec;
    MeedEntry5** ppBegin =
        (MeedEntry5**)(vc + 0x18);
    MeedEntry5** ppEnd =
        (MeedEntry5**)(vc + 0x20);
    MeedEntry5* pEnd = *ppEnd;
    MeedEntry5* pBegin = *ppBegin;
    if (pBegin != pEnd) {
        // FUN_141782480(end, end, begin):
        // the self no-op move; the return
        // recomputes the position
        int64_t lVar3 = MeedEntryCopyTo(
            pEnd, (MeedEntry5*)*ppEnd,
            (int64_t)pBegin);
        *ppEnd = (MeedEntry5*)lVar3;
    }
}

// ---------- FUN_141781eb0: the median-of-3 ----------
static void MeedEntryMedian3(MeedEntry5* p1,
                             MeedEntry5* p2,
                             MeedEntry5* p3,
                             char (*pCmp)(
                                 const MeedEntry5*,
                                 const MeedEntry5*)) {
    if (pCmp(p2, p1)) {
        MeedEntrySwap5(p2, p1);
    }
    if (pCmp(p3, p2)) {
        MeedEntrySwap5(p3, p2);
    }
    if (pCmp(p2, p1)) {
        MeedEntrySwap5(p2, p1);
    }
}

// ---------- FUN_141782640: the median-of-9 ----------
static void MeedEntryMedian9(MeedEntry5* p1,
                             MeedEntry5* p2,
                             MeedEntry5* p3,
                             char (*pCmp)(
                                 const MeedEntry5*,
                                 const MeedEntry5*)) {
    int64_t lVar1 =
        ((int64_t)p3 - (int64_t)p1) / 0x14;
    if (0x28 < lVar1) {
        lVar1 = lVar1 + 1;
        lVar1 = (lVar1 +
                 (int64_t)((uint64_t)(
                               lVar1 >> 0x3f) &
                           7)) >> 3;
        MeedEntryMedian3(p1, p1 + lVar1,
                         p1 + lVar1 * 2, pCmp);
        MeedEntryMedian3(p2 - lVar1, p2,
                         p2 + lVar1, pCmp);
        MeedEntryMedian3(p3 - lVar1 * 2,
                         p3 - lVar1, p3, pCmp);
        MeedEntryMedian3(p1 + lVar1, p2,
                         p3 - lVar1, pCmp);
        return;
    }
    MeedEntryMedian3(p1, p2, p3, pCmp);
}

// ---------- FUN_1417807c0: the sift-up ----------
static void MeedEntrySiftUp(
    char* pBase, int64_t pHole, int64_t pTop,
    const MeedEntry5* pVal,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    while (pTop < pHole) {
        int64_t lVar3 = (pHole - 1) / 2;
        MeedEntry5* puVar1 =
            (MeedEntry5*)(pBase + lVar3 * 0x14);
        if (!pCmp(puVar1, pVal)) {
            break;
        }
        *(MeedEntry5*)(pBase + pHole * 0x14) =
            *puVar1;
        pHole = lVar3;
    }
    *(MeedEntry5*)(pBase + pHole * 0x14) = *pVal;
}

// ---------- FUN_141781f30: the sift-down ----------
static void MeedEntrySiftDown(
    char* pBase, int64_t pHole, int64_t pLen,
    const MeedEntry5* pVal,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    int64_t lVar1 = pHole;
    int64_t lVar3;
    while (true) {
        lVar3 = lVar1 * 2 + 2;
        if (pLen <= lVar3) {
            break;
        }
        MeedEntry5* lVar4 =
            (MeedEntry5*)(pBase + lVar3 * 0x14);
        if (pCmp(lVar4,
                 (MeedEntry5*)(pBase +
                               (lVar3 - 1) *
                                   0x14))) {
            lVar3 = lVar1 * 2 + 1;
        }
        *(MeedEntry5*)(pBase + lVar1 * 0x14) =
            *(MeedEntry5*)(pBase + lVar3 * 0x14);
        lVar1 = lVar3;
    }
    int64_t lVar4b = lVar1;
    if (lVar3 == pLen) {
        lVar4b = pLen - 1;
        *(MeedEntry5*)(pBase + lVar1 * 0x14) =
            *(MeedEntry5*)(pBase - 0x14 +
                           pLen * 0x14);
    }
    MeedEntrySiftUp(pBase, lVar4b, pHole, pVal,
                    pCmp);
}

// ---------- FUN_141782740: the make-heap ----------
static void MeedEntryHeapMake(
    MeedEntry5* p1, MeedEntry5* p2,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    int64_t lVar1 =
        ((int64_t)p2 - (int64_t)p1) / 0x14;
    int64_t lVar2 = lVar1 / 2;
    if (0 < lVar2) {
        int64_t lVar3 =
            (int64_t)p1 + lVar2 * 0x14;
        do {
            MeedEntry5 local;
            local = *(MeedEntry5*)(lVar3 - 0x14);
            lVar2 = lVar2 - 1;
            MeedEntrySiftDown((char*)p1, lVar2,
                              lVar1, &local, pCmp);
            lVar3 = lVar3 - 0x14;
        } while (0 < lVar2);
    }
}

// ---------- FUN_141782990: the pop-one ----------
static void MeedEntryPopOne(
    MeedEntry5* p1, MeedEntry5* p2,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    MeedEntry5 local;
    local.v[0] =
        *(int32_t*)((int64_t)p2 - 0x14);
    local.v[1] =
        *(int32_t*)((int64_t)p2 - 0x10);
    local.v[2] =
        *(int32_t*)((int64_t)p2 - 0xc);
    local.v[3] =
        *(int32_t*)((int64_t)p2 - 8);
    local.v[4] =
        *(int32_t*)((int64_t)p2 - 4);
    *(int32_t*)((int64_t)p2 - 0x14) = p1->v[0];
    *(int32_t*)((int64_t)p2 - 0x10) = p1->v[1];
    *(int32_t*)((int64_t)p2 - 0xc) = p1->v[2];
    *(int32_t*)((int64_t)p2 - 8) = p1->v[3];
    *(int32_t*)((int64_t)p2 - 4) = p1->v[4];
    MeedEntrySiftDown(
        (char*)p1, 0,
        (((int64_t)p2 - (int64_t)p1) - 0x14) /
            0x14,
        &local, pCmp);
}

// ---------- FUN_1417833d0: the sort-down loop --
static void MeedEntryHeapPopLoop(
    MeedEntry5* p1, MeedEntry5* p2,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    for (int64_t lVar1 = (int64_t)p2 -
             (int64_t)p1;
         1 < lVar1 / 0x14;
         lVar1 = lVar1 + -0x14) {
        MeedEntryPopOne(p1, p2, pCmp);
        p2 = (MeedEntry5*)((int64_t)p2 -
                           0x14);
    }
}

// ---------- FUN_141782810: the guarded
// insertion sort ----------
static void MeedEntryInsertionGuarded(
    MeedEntry5* p1, MeedEntry5* p2,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    MeedEntry5* puVar1 = p1;
    MeedEntry5* puVar4 = p1;
    if (p1 == p2) {
        return;
    }
    while (true) {
        puVar4 = puVar4 + 1;
        if (puVar4 == p2) {
            break;
        }
        MeedEntry5 local;
        local.v[0] = puVar4->v[0];
        local.v[1] = puVar4->v[1];
        local.v[2] = puVar4->v[2];
        local.v[3] = puVar4->v[3];
        local.v[4] = puVar4->v[4];
        if (pCmp(&local, p1)) {
            // less than first: the rotate
            MeedEntryRotBwd((int64_t)p1,
                            (int64_t)puVar4,
                            (int64_t)puVar1 +
                                10 * 4);
            p1->v[0] = local.v[0];
            p1->v[1] = local.v[1];
            p1->v[2] = local.v[2];
            p1->v[3] = local.v[3];
            p1->v[4] = local.v[4];
        } else {
            char cVar5 =
                pCmp(&local, puVar1);
            MeedEntry5* puVar2 = puVar4;
            MeedEntry5* puVar3 = puVar1;
            while (cVar5 != '\0') {
                puVar2->v[0] = puVar3->v[0];
                puVar2->v[1] = puVar3->v[1];
                puVar2->v[2] = puVar3->v[2];
                puVar2->v[3] = puVar3->v[3];
                puVar2->v[4] = puVar3->v[4];
                cVar5 = pCmp(&local, puVar3 - 1);
                puVar2 = puVar3;
                puVar3 = puVar3 - 1;
            }
            puVar2->v[0] = local.v[0];
            puVar2->v[1] = local.v[1];
            puVar2->v[2] = local.v[2];
            puVar2->v[3] = local.v[3];
            puVar2->v[4] = local.v[4];
        }
        puVar1 = puVar1 + 1;
    }
}

// ---------- FUN_141782ca0: the partition ----------
static void MeedEntryPartition(
    MeedEntry5* pOut[2], MeedEntry5* pFirst,
    MeedEntry5* pLast,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    // the original: param_2 + (bytes/0x28)*5
    // in 4-byte units = + count/2 entries on
    // the typed pointer
    MeedEntry5* puVar13 =
        pFirst + (((int64_t)pLast -
                   (int64_t)pFirst) / 0x28);
    MeedEntryMedian9(pFirst, puVar13, pLast - 1,
                     pCmp);
    MeedEntry5* puVar12 = puVar13;
    MeedEntry5* puVar14;
    MeedEntry5* puVar11 = nullptr;
    while (true) {
        puVar14 = puVar12;
        if (!(pFirst < puVar14)) {
            break;
        }
        puVar12 = puVar14 - 1;
        char cVar10 = pCmp(puVar12, puVar14);
        if (cVar10 != '\0' ||
            (cVar10 = pCmp(puVar14, puVar12),
             cVar10 != '\0')) {
            break;
        }
    }
    do {
        puVar13 = puVar13 + 1;
        puVar12 = puVar13;
        puVar11 = puVar14;
        if (pLast <= puVar13) {
            break;
        }
        char cVar10 = pCmp(puVar13, puVar14);
        if (cVar10 != '\0' ||
            (cVar10 = pCmp(puVar14, puVar13),
             cVar10 != '\0')) {
            break;
        }
    } while (true);
joined_r0x000141782d83:
    MeedEntry5* puVar7 = puVar12;
    MeedEntry5* puVar6 = puVar13;
    MeedEntry5* puVar8 = puVar14;
    MeedEntry5* puVar9 = puVar11;
    puVar13 = puVar6;
    if (puVar7 < pLast) {
        char cVar10 = pCmp(puVar11, puVar7);
        if (cVar10 == '\0') {
            cVar10 = pCmp(puVar7, puVar11);
            if (cVar10 != '\0') {
                goto joined_r0x000141782e24;
            }
            puVar13 = puVar6 + 1;
            if (puVar6 != puVar7) {
                MeedEntrySwap5(puVar6, puVar7);
            }
        }
        puVar12 = puVar7 + 1;
        goto joined_r0x000141782d83;
    }
joined_r0x000141782e24:
    for (; pFirst < puVar8;
         puVar8 = puVar8 - 1) {
        MeedEntry5* puVar11b = puVar14 - 1;
        char cVar10 =
            pCmp(puVar11b, puVar9);
        MeedEntry5* puVar12b = puVar9;
        if (cVar10 == '\0') {
            cVar10 = pCmp(puVar9, puVar11b);
            if (cVar10 != '\0') {
                break;
            }
            puVar12b = puVar9 - 1;
            if (puVar12b != puVar11b) {
                MeedEntrySwap5(puVar12b,
                               puVar11b);
            }
        }
        puVar14 = puVar11b;
        puVar9 = puVar12b;
    }
    if (puVar8 == pFirst) {
        if (puVar7 == pLast) {
            *pOut = puVar9;
            pOut[1] = puVar6;
            return;
        }
        if (puVar6 != puVar7 &&
            puVar9 != puVar6) {
            MeedEntrySwap5(puVar9, puVar6);
        }
        puVar13 = puVar6 + 1;
        puVar12 = puVar7 + 1;
        puVar14 = puVar8;
        puVar11 = puVar9 + 1;
        if (puVar9 != puVar7) {
            MeedEntrySwap5(puVar9, puVar7);
        }
    } else {
        puVar14 = puVar8 - 1;
        if (puVar7 == pLast) {
            MeedEntry5* puVar11b = puVar9 - 1;
            puVar11 = puVar11b;   // stays puVar9-1
            if (puVar14 != puVar11b) {
                MeedEntrySwap5(puVar14,
                               puVar11b);
            }
            puVar13 = puVar6 - 1;
            puVar12 = puVar7;
            if (puVar11b != puVar13) {
                MeedEntrySwap5(puVar11b,
                               puVar13);
            }
        } else {
            if (puVar7 != puVar14) {
                MeedEntrySwap5(puVar7,
                               puVar14);
            }
            puVar12 = puVar7 + 1;
            puVar11 = puVar9;
        }
    }
    goto joined_r0x000141782d83;
}

// ---------- FUN_141783f50: the introsort core --
static void MeedEntryIntro(
    MeedEntry5* p1, MeedEntry5* p2,
    int64_t pDepth,
    char (*pCmp)(const MeedEntry5*,
                 const MeedEntry5*)) {
    int64_t lVar1 = (int64_t)p2 - (int64_t)p1;
    do {
        lVar1 = lVar1 / 0x14;
        if (lVar1 < 0x21) {
            if (1 < lVar1) {
                MeedEntryInsertionGuarded(p1, p2,
                                          pCmp);
            }
            return;
        }
        if (pDepth < 1) {
            if (0x20 < lVar1) {
                MeedEntryHeapMake(p1, p2, pCmp);
                MeedEntryHeapPopLoop(p1, p2,
                                     pCmp);
            }
            return;
        }
        MeedEntry5* local_18[2];
        MeedEntry5* local_10;
        MeedEntryPartition(
            (MeedEntry5**)local_18, p1, p2,
            pCmp);
        local_10 = local_18[1];
        pDepth = pDepth / 2 + (pDepth / 2) / 2;
        if (((int64_t)local_18[0] -
             (int64_t)p1) / 0x14 <
            ((int64_t)p2 -
             (int64_t)local_10) / 0x14) {
            MeedEntryIntro(p1, local_18[0],
                           pDepth, pCmp);
            p1 = local_10;
        } else {
            MeedEntryIntro(local_10, p2,
                           pDepth, pCmp);
            p2 = local_18[0];
        }
        lVar1 = (int64_t)p2 - (int64_t)p1;
    } while (true);
}

// ---------- FUN_141784260: the sort entry ------
void MeedEntrySort(void* pPairFirst[2],
                   void* pPairLast[2],
                   char (*pCmp)(const MeedEntry5*,
                                const MeedEntry5*)) {
    // (the proxy gates: if (*pPairLast == 0 ||
    //  *pPairLast != *pPairFirst) trap — only
    //  under _ITERATOR_DEBUG; elided like D52)
    MeedEntryIntro(
        (MeedEntry5*)pPairFirst[1],
        (MeedEntry5*)pPairLast[1],
        ((int64_t)pPairLast[1] -
         (int64_t)pPairFirst[1]) / 0x14,
        pCmp);
}

}  // namespace syndicate

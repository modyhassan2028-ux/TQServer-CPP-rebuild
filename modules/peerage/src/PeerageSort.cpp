// ============================================================
// Peerage.dll port — unit T3/D19. VERBATIM from the
// Ghidra listing (the addresses in the header).
// ============================================================
#include "PeerageSort.h"
#include "PeerageSortMgr.h"
#include <cstdlib>
#include <cstring>

namespace peerage {

// ---- the seam defaults ----
static void* defRowQ(void*, int) { return nullptr; }
static int64_t defRowV(void*) { return 0; }
static uint32_t defRowI(void*) { return 0; }
void* (*g_fnRowQuery2)(void*, int) = defRowQ;
int64_t (*g_fnRowGetValue)(void*) = defRowV;
uint32_t (*g_fnRowGetId)(void*) = defRowI;
void (*g_fnSortLogError2)() = []() {};
void (*g_fnInvalidParameter2)() = []() { abort(); };

// ---- FUN_141552180: the key ----
uint32_t PeerageSortKey(void* pElem) {
    return *(uint32_t*)((char*)pElem + 0x18);
}

// ---- FUN_141552810: the comparator ----
bool PeerageSortPred(void* pA, void* pB) {
    if (pA == nullptr || pB == nullptr) {
        g_fnSortLogError2();
        return false;
    }
    // the values (elem+8 -> vt+0x10(2) -> vt+0x58)
    void* pRecA = g_fnRowQuery2(
        *(void**)((char*)pA + 8), 2);
    int64_t vA = g_fnRowGetValue(pRecA);
    void* pRecB = g_fnRowQuery2(
        *(void**)((char*)pB + 8), 2);
    int64_t vB = g_fnRowGetValue(pRecB);
    if (vA != vB) {
        // recompute both (verbatim double query)
        pRecA = g_fnRowQuery2(
            *(void**)((char*)pA + 8), 2);
        vA = g_fnRowGetValue(pRecA);
        pRecB = g_fnRowQuery2(
            *(void**)((char*)pB + 8), 2);
        vB = g_fnRowGetValue(pRecB);
        return vB < vA;   // DESCENDING
    }
    // the keys (+0x18)
    uint32_t kA = PeerageSortKey(pA);
    uint32_t kB = PeerageSortKey(pB);
    if (kA != kB) {
        kA = PeerageSortKey(pA);
        kB = PeerageSortKey(pB);
        return kB < kA;    // DESCENDING
    }
    // the ids (elem+8 -> vt+0x10(0) -> vt+0x40)
    void* pRecA0 = g_fnRowQuery2(
        *(void**)((char*)pA + 8), 0);
    uint32_t iA = g_fnRowGetId(pRecA0);
    void* pRecB0 = g_fnRowQuery2(
        *(void**)((char*)pB + 8), 0);
    uint32_t iB = g_fnRowGetId(pRecB0);
    return iA < iB;        // ASCENDING
}

// ---- FUN_141553aa0: the 3-comparison median ----
void SortMedian3(void** ppA, void** ppB, void** ppC,
                 bool (*pPred)(void*, void*)) {
    if (pPred(*ppB, *ppA) && ppB != ppA) {
        void* t = *ppB; *ppB = *ppA; *ppA = t;
    }
    if (pPred(*ppC, *ppB) && ppC != ppB) {
        void* t = *ppC; *ppC = *ppB; *ppB = t;
    }
    if (pPred(*ppB, *ppA) && ppB != ppA) {
        void* t = *ppB; *ppB = *ppA; *ppA = t;
    }
}

// ---- FUN_141554000: med3 / the 9-sample med ----
void SortMedian3or9(void** ppA, void** ppB,
                    void** ppC,
                    bool (*pPred)(void*, void*)) {
    int64_t n = ((int64_t)ppC - (int64_t)ppA) >> 3;
    if (0x28 < n) {
        int64_t k = n + 1;
        k = (int64_t)
            ((uint64_t)k
             + ((uint32_t)((int64_t)k >> 0x3f) & 7))
            >> 3;
        SortMedian3(ppA, ppA + k, ppA + k * 2, pPred);
        SortMedian3(ppB - k, ppB, ppB + k, pPred);
        SortMedian3(ppC - k * 2, ppC - k, ppC, pPred);
        SortMedian3(ppA + k, ppB, ppC - k, pPred);
        return;
    }
    SortMedian3(ppA, ppB, ppC, pPred);
}

// ---- FUN_141553b30: the heap sift ----
void SortSiftDown(void** ppBase, int64_t nHole,
                  int64_t nLen, void* pVal,
                  bool (*pPred)(void*, void*)) {
    int64_t i = nHole;
    int64_t nChild;
    while (true) {
        nChild = i * 2 + 2;
        if (nLen <= nChild) break;
        if (pPred(ppBase[nChild],
                  ppBase[nChild - 1])) {
            nChild = i * 2 + 1;
        }
        ppBase[i] = ppBase[nChild];
        i = nChild;
    }
    if (nChild == nLen) {
        ppBase[i] = ppBase[nLen - 1];
        i = nLen - 1;
    }
    while (nHole < i) {
        int64_t nPar = (i - 1) / 2;
        if (!pPred(ppBase[nPar], pVal)) break;
        ppBase[i] = ppBase[nPar];
        i = nPar;
    }
    ppBase[i] = pVal;
}

// ---- FUN_1415547e0: make_heap ----
void SortMakeHeap(void** ppFirst, void** ppLast,
                  bool (*pPred)(void*, void*)) {
    int64_t nLen = ((int64_t)ppLast
                    - (int64_t)ppFirst) >> 3;
    if (1 < nLen) {
        int64_t nPar = (nLen
            - (((int64_t)ppLast - (int64_t)ppFirst)
               >> 0x3f)) >> 1;
        while (0 < nPar) {
            void* pVal = ppFirst[nPar - 1];
            nPar = nPar - 1;
            SortSiftDown(ppFirst, nPar, nLen,
                         pVal, pPred);
        }
    }
}

// ---- FUN_141554f80: sort_heap ----
void SortHeapSort(void** ppFirst, void** ppLast,
                  bool (*pPred)(void*, void*)) {
    for (int64_t nSpan = (int64_t)ppLast
             - (int64_t)ppFirst;
         1 < (nSpan >> 3); nSpan = nSpan - 8) {
        void* pVal =
            *(void**)((int64_t)ppFirst + nSpan - 8);
        *(void**)((int64_t)ppFirst + nSpan - 8)
            = *ppFirst;
        SortSiftDown(ppFirst, 0, (nSpan - 8) >> 3,
                     pVal, pPred);
    }
}

// ---- FUN_141554160: the insertion sort ----
void SortInsertion(void** ppFirst, void** ppLast,
                    bool (*pPred)(void*, void*)) {
    if (ppFirst == ppLast) return;
    void** ppIt = ppFirst + 1;
    if (ppIt == ppLast) return;
    do {
        void* pVal = *ppIt;
        if (!pPred(pVal, *ppFirst)) {
            // the inner shift loop
            bool c = pPred(pVal, ppIt[-1]);
            void** ppJ = ppIt;
            while (c) {
                *ppJ = ppJ[-1];
                c = pPred(pVal, ppJ[-2]);
                ppJ = ppJ - 1;
            }
            *ppJ = pVal;
        } else {
            // rotate right by (it - first)
            int64_t n = ((int64_t)ppIt
                         - (int64_t)ppFirst) >> 3;
            if (0 < n) {
                size_t uS = (size_t)(n * 8);
                memmove(ppIt + 1 - n, ppFirst, uS);
            }
            *ppFirst = pVal;
        }
        ppIt = ppIt + 1;
    } while (ppIt != ppLast);
}

// ---- FUN_1415545b0: the partition ----
void SortPartition(void* itOut[2], void** ppFirst,
                   void** ppLast,
                   bool (*pPred)(void*, void*)) {
    void** ppA;   // puVar7 (the mid walk)
    void** ppB;   // puVar8 (the right scan)
    void** ppC;   // puVar9 (the pivot walk back)
    void** ppD;   // puVar4 (the left scan)
    void** ppE;   // puVar5 (the swap walker)
    void** ppF;   // puVar2 (the right bound)
    void** ppG;   // puVar6
    void* uVar1;

    ppA = ppFirst
        + ((((int64_t)ppLast - (int64_t)ppFirst) >> 3)
            - (((int64_t)ppLast
                - (int64_t)ppFirst) >> 0x3f)) / 2;
    SortMedian3or9(ppFirst, ppA, ppLast - 1, pPred);
    ppB = ppA;
    while (ppC = ppB, ppFirst < ppC) {
        if (pPred(ppC[-1], *ppC)) break;
        // (the comma side-effect: assigned either way)
        ppB = ppC - 1;
        if (pPred(*ppC, ppC[-1])) break;
    }
    do {
        ppA = ppA + 1;
        ppB = ppA;
        ppD = ppC;
        if (ppLast <= ppA) break;
        if (pPred(*ppA, *ppC)) break;
        if (pPred(*ppC, *ppA)) break;
    } while (true);
joined_673:
    ppF = ppB;
    ppB = ppC;
    ppE = ppD;
    if (ppLast <= ppF) {
joined_6b3:
        for (; ppFirst < ppC; ppC = ppC - 1) {
            ppB = ppB - 1;
            // (cVar3 == 0: the second pred + the
            // walk/swap; cVar3 != 0: NOTHING — the
            // loop just continues)
            if (!pPred(*ppB, *ppE)) {
                if (pPred(*ppE, *ppB)) break;
                ppE = ppE - 1;
                if (ppE != ppB) {
                    uVar1 = *ppE; *ppE = *ppB;
                    *ppB = uVar1;
                }
            }
        }
        if (ppC == ppFirst) {
            if (ppF == ppLast) {
                void*** pMid = (void***)itOut;
                pMid[0] = ppE;
                pMid[1] = ppA;
                return;
            }
            if (ppA != ppF && ppE != ppA) {
                uVar1 = *ppE; *ppE = *ppA;
                *ppA = uVar1;
            }
            ppA = ppA + 1;
            ppB = ppF + 1;
            ppD = ppE + 1;
            if (ppE != ppF) {
                uVar1 = *ppE; *ppE = *ppF;
                *ppF = uVar1;
            }
        } else {
            ppC = ppC - 1;
            if (ppF == ppLast) {
                ppD = ppE - 1;
                if (ppC != ppD) {
                    uVar1 = *ppC; *ppC = *ppD;
                    *ppD = uVar1;
                }
                ppA = ppA - 1;
                ppB = ppF;
                if (ppD != ppA) {
                    uVar1 = *ppD; *ppD = *ppA;
                    *ppA = uVar1;
                }
            } else {
                if (ppF != ppC) {
                    uVar1 = *ppF; *ppF = *ppC;
                    *ppC = uVar1;
                }
                ppB = ppF + 1;
                ppD = ppE;
            }
        }
        goto joined_673;
    }
    if (!pPred(*ppD, *ppF)) {
        if (pPred(*ppF, *ppD)) goto joined_6b3;
        ppG = ppA + 1;
        if (ppA != ppF) {
            uVar1 = *ppA; *ppA = *ppF;
            *ppF = uVar1;
        }
    } else {
        ppG = ppA;
    }
    ppA = ppG;
    ppB = ppF + 1;
    goto joined_673;
}

// ---- FUN_141555b60: the introsort loop ----
void SortIntrosort(void** ppFirst, void** ppLast,
                   int64_t nDepth,
                   bool (*pPred)(void*, void*)) {
    int64_t nSpan = (int64_t)ppLast
                    - (int64_t)ppFirst;
    do {
        int64_t nCount = nSpan >> 3;
        if (nCount < 0x21) {
            // LAB_141555c25
            if (1 < nCount) {
                SortInsertion(ppFirst, ppLast, pPred);
            }
            return;
        }
        if (nDepth < 1) {
            if (0x20 < nCount) {
                SortMakeHeap(ppFirst, ppLast, pPred);
                SortHeapSort(ppFirst, ppLast, pPred);
                return;
            }
            // (LAB_141555c25)
            if (1 < nCount) {
                SortInsertion(ppFirst, ppLast, pPred);
            }
            return;
        }
        void* itMid[2];
        SortPartition(itMid, ppFirst, ppLast, pPred);
        void** ppMidFirst = (void**)itMid[0];
        void** ppMidSecond = (void**)itMid[1];
        nDepth = nDepth / 2 + (nDepth / 2) / 2;
        if ((((int64_t)ppMidFirst - (int64_t)ppFirst)
             & 0xfffffffffffffff8ULL)
            < (((int64_t)ppLast
                - (int64_t)ppMidSecond)
               & 0xfffffffffffffff8ULL)) {
            SortIntrosort(ppFirst, ppMidFirst,
                          nDepth, pPred);
            ppFirst = ppMidSecond;
        } else {
            SortIntrosort(ppMidSecond, ppLast,
                          nDepth, pPred);
            ppLast = ppMidFirst;
        }
        nSpan = (int64_t)ppLast - (int64_t)ppFirst;
    } while (true);
}

// ---- FUN_141555f80's sort-call wrapper ----
// (the part before the promotion walk)
void SortPeerageVector(CPeerageSortMgr* pMgr) {
    // if (param_3 != 0) FindById(...);  — (the D20
    // walk owns the param_3 call; the sort itself:)
    void** ppEnd = pMgr->m_vec.m_ppEnd;
    if ((void*)ppEnd < (void*)pMgr->m_vec.m_ppBegin) {
        g_fnInvalidParameter2();
    }
    void* pProxy = *(void**)((char*)pMgr + 8);
    void** ppBegin = pMgr->m_vec.m_ppBegin;
    if ((void*)pMgr->m_vec.m_ppEnd < (void*)ppBegin) {
        g_fnInvalidParameter2();
    }
    if (pProxy == nullptr
        || pProxy != *(void**)((char*)pMgr + 8)) {
        g_fnInvalidParameter2();
    }
    SortIntrosort(ppBegin, ppEnd,
        ((int64_t)ppEnd - (int64_t)ppBegin) >> 3,
        PeerageSortPred);
}

} // namespace peerage

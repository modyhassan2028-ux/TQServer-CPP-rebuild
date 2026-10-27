// ============================================================
// Peerage.dll port — unit T2/D18. VERBATIM from the
// Ghidra listing (addresses in the header).
// ============================================================
#include "PeerageSortMgr.h"
#include <cstdlib>
#include <cstring>

namespace peerage {

// ---- the seam defaults ----
std::function<void*(size_t)> g_fnSortAlloc =
    [](size_t n) { return calloc(1, n); };
std::function<void*(size_t)> g_fnVecAlloc =
    [](size_t n) { return malloc(n); };
std::function<void(void*)> g_fnVecDelete =
    [](void* p) { free(p); };
std::function<void*(size_t)> g_fnProxyAlloc =
    [](size_t n) { return calloc(1, n); };
std::function<void(void*)> g_fnProxyDelete =
    [](void* p) { free(p); };
void (*g_fnInvalidParameter)() = []() { abort(); };
void (*g_fnThrowLengthError)() = []() { abort(); };
void (*g_fnThrowBadAlloc)() = []() { abort(); };
void (*g_fnSortLogError)() = []() {};
std::function<void*(void*, int)> g_fnRowQuery =
    [](void*, int) { return nullptr; };
std::function<int(void*)> g_fnRowGetInt =
    [](void*) { return 0; };

// ---- FUN_141554f40: the forward move helper ----
// (memmove(dst, src, (end-src)/8*8) then dst+size)
static void* MoveFwd(void* pDst, void* pSrc,
                     int64_t nEnd) {
    int64_t n = ((int64_t)pSrc - (int64_t)pDst) >> 3;
    size_t uSize = (size_t)(n * 8);
    void* pRet = (void*)((int64_t)pDst + uSize);
    if (n != 0) {
        memmove(pRet, pSrc, uSize);   // memmove_s
    }
    return pRet;
}

// ---- FUN_141553ef0: the backward move helper ----
static void* MoveBack(void* pSrc, int64_t nB,
                      int64_t nEnd) {
    int64_t n = (nB - (int64_t)pSrc) >> 3;
    void* pDst = (void*)(nEnd - n * 8);
    if (0 < n) {
        memmove(pDst, pSrc, (size_t)(n * 8));
    }
    return pDst;
}

// ---- FUN_141553850: the buffer alloc ----
// (if count > (2^64-1)/8 -> bad_alloc; new(count*8))
static void* VecAllocBuf(void* pAlloc, uint64_t uCount) {
    (void)pAlloc;   // (param_1: the allocator @ vec+0x10)
    if (uCount != 0) {
        // SUB168((0<<64 | -1) / count) < 8 -> throw
        if (((~0ull) / uCount) < 8) {
            g_fnThrowBadAlloc();   // no return
        }
    }
    return g_fnVecAlloc((size_t)(uCount * 8));
}

// ---- FUN_1415553d0: _Insert_n ----
void VecInsertN(SPtrVec* pVec, void* itPair[2],
                uint64_t uCount,
                void* pValueQword) {
    int64_t nBegin = (int64_t)pVec->m_ppBegin;
    uint64_t uSize;
    if (nBegin == 0) {
        uSize = 0;
    } else {
        uSize = (uint64_t)((int64_t)pVec->m_ppEnd
                     - nBegin) >> 3;
    }
    uint64_t uNewCap = 0;
    if (uCount != 0) {
        int64_t nEnd = (int64_t)pVec->m_ppEnd;
        int64_t nOldSize = (nEnd - nBegin) >> 3;
        // 0x1fffffffffffffff - old < count -> throw
        if (0x1fffffffffffffffULL - (uint64_t)nOldSize
                < uCount) {
            g_fnThrowLengthError();   // no return
        }
        uint64_t uNeed = uCount + (uint64_t)nOldSize;
        if (uSize < uNeed) {
            // cap = max(size + size/2, need)
            if (uSize <= 0x1fffffffffffffffULL
                    - (uSize >> 1)) {
                uNewCap = uSize + (uSize >> 1);
            }
            if (uNewCap < uNeed) {
                uNewCap = uNeed;
            }
            void* pNew = VecAllocBuf(
                (char*)pVec + 0x10, uNewCap);
            // the insertion index (from itPair+8)
            int64_t nIdx = ((int64_t)itPair[1]
                     - (int64_t)pVec->m_ppBegin) >> 3;
            void** ppDst = (void**)((int64_t)pNew
                                     + nIdx * 8);
            for (uint64_t i = uCount; i != 0; --i) {
                *ppDst = *(void**)pValueQword;
                ++ppDst;
            }
            // move [begin, it) forward
            int64_t nHead = ((int64_t)itPair[1]
                     - (int64_t)pVec->m_ppBegin) >> 3;
            if (nHead != 0) {
                size_t uS = (size_t)(nHead << 3);
                memmove(pNew, pVec->m_ppBegin, uS);
            }
            // move [it, end) after the hole
            int64_t nTail = ((int64_t)pVec->m_ppEnd
                     - (int64_t)itPair[1]) >> 3;
            if (nTail != 0) {
                size_t uS = (size_t)(nTail << 3);
                memmove((void*)((int64_t)pNew
                    + (nIdx + (int64_t)uCount) * 8),
                    itPair[1], uS);
            }
            // free the old buf + fix the pointers
            void* pOld = pVec->m_ppBegin;
            int64_t nOldEnd = (int64_t)pVec->m_ppEnd;
            if (pOld != nullptr) {
                g_fnVecDelete(pOld);
            }
            pVec->m_ppCap = (void**)((int64_t)pNew
                              + uNewCap * 8);
            pVec->m_ppEnd = (void**)((int64_t)pNew
                + ((int64_t)uCount
                   + ((nOldEnd
                       - (int64_t)pOld) >> 3)) * 8);
            pVec->m_ppBegin = (void**)pNew;
        } else if ((uint64_t)(((int64_t)nEnd
                    - (int64_t)itPair[1]) >> 3)
                   < uCount) {
            // shift the tail right by count
            uint64_t uVal = *(uint64_t*)pValueQword;
            int64_t nEnd2 = (int64_t)pVec->m_ppEnd;
            MoveFwd(itPair[1], (void*)(int64_t)nEnd2,
                    nEnd2);
            // (the MoveFwd contract: dst = itPair+8)
            // fill [it+count .. end+count)
            void** ppE = pVec->m_ppEnd;
            int64_t nFill = (int64_t)uCount
                - (((int64_t)ppE
                    - (int64_t)itPair[1]) >> 3);
            for (; nFill != 0; --nFill) {
                *(uint64_t*)ppE = uVal;
                ++ppE;
            }
            pVec->m_ppEnd = (void**)((int64_t)
                pVec->m_ppEnd + (int64_t)uCount * 8);
            // fill [it, it+count)
            int64_t nE = (int64_t)pVec->m_ppEnd;
            for (void** pp = (void**)itPair[1];
                 pp != (void**)(nE
                     - (int64_t)uCount * 8); ++pp) {
                *(uint64_t*)pp = uVal;
            }
        } else {
            // no realloc: move [it,end) right, fill
            uint64_t uVal = *(uint64_t*)pValueQword;
            int64_t nEnd3 = (int64_t)pVec->m_ppEnd;
            void* pSrcBack = (void*)(nEnd3
                - (int64_t)uCount * 8);
            void* pRet = MoveFwd(pSrcBack,
                (void*)nEnd3, nEnd3);
            pVec->m_ppEnd = (void**)pRet;
            MoveBack(itPair[1],
                     (int64_t)pSrcBack, nEnd3);
            void** ppS = (void**)itPair[1];
            void** ppD = ppS + uCount;
            for (; ppS != ppD; ++ppS) {
                *(uint64_t*)ppS = uVal;
            }
        }
    }
}

// ---- FUN_141555a30: the insert-at-end grow ----
void VecGrowForPush(SPtrVec* pVec, void* itOut[2],
                    void* pProxyPair[2],
                    void* pValueQword) {
    // lVar4: the index of the vector's end (or 0)
    int64_t lIdx = 0;
    uint64_t uBegin = (uint64_t)(uintptr_t)
        pVec->m_ppBegin;
    if (((uint64_t)(uintptr_t)pVec->m_ppEnd
         - uBegin) & 0xfffffffffffffff8ULL) {
        if ((uint64_t)(uintptr_t)pVec->m_ppEnd
                < uBegin) {
            g_fnInvalidParameter();
        }
        if (*(void**)pProxyPair == nullptr
            || *(void**)pProxyPair != pVec->m_pProxy) {
            g_fnInvalidParameter();
        }
        lIdx = ((int64_t)(uintptr_t)
                ((void**)pProxyPair)[1]
                - (int64_t)uBegin) >> 3;
    }
    // local_28/uStack_20 = the proxy iterator pair
    void* itPair[2] = { *(void**)pProxyPair,
                        ((void**)pProxyPair)[1] };
    VecInsertN(pVec, itPair, 1, pValueQword);
    // recompute: uVar1 = the new begin
    uint64_t uNewBegin = (uint64_t)(uintptr_t)
        pVec->m_ppBegin;
    if ((uint64_t)(uintptr_t)pVec->m_ppEnd
            < uNewBegin) {
        g_fnInvalidParameter();
    }
    void* pProxy = pVec->m_pProxy;
    // the proxy's deref (lVar5 = *proxy = the vec)
    int64_t lVec = 0;
    if (pProxy == nullptr) {
        g_fnInvalidParameter();
        // (lVar5 = 0 in the listing)
    } else {
        lVec = *(int64_t*)pProxy;
    }
    uint64_t uIt = uNewBegin
        + (uint64_t)(lIdx * 8);
    // the debug checks: begin <= it (twice: via the
    // proxy's vec +0x20 and +0x18)
    if (uIt <= *(uint64_t*)(lVec + 0x20)) {
        if (pProxy != nullptr) {
            lVec = *(int64_t*)pProxy;
        }
        if (*(uint64_t*)(lVec + 0x18) <= uIt) {
            // LAB_141555b24
            itOut[0] = (void*)pProxy;
            itOut[1] = (void*)uIt;
            return;
        }
    }
    g_fnInvalidParameter();
    // (unreachable in the original; mirror the fall)
    itOut[0] = (void*)pProxy;
    itOut[1] = (void*)uIt;
}

// ---- FUN_141555cb0: push_back ----
void VecPushBack(CPeerageSortMgr* p, void** ppObj) {
    SPtrVec* pVec = (SPtrVec*)((char*)p + 8);
    void* pBegin = pVec->m_ppBegin;
    uint64_t uSize;
    if (pBegin == nullptr) {
        uSize = 0;
    } else {
        uSize = (uint64_t)((int64_t)pVec->m_ppCap
                     - (int64_t)pBegin) >> 3;
    }
    void* pEnd = pVec->m_ppEnd;
    if ((uint64_t)(((int64_t)pEnd
            - (int64_t)pBegin) >> 3) < uSize) {
        *(void**)pEnd = *ppObj;
        pVec->m_ppEnd = (void**)((int64_t)pEnd + 8);
        return;
    }
    if (pEnd < pBegin) {
        g_fnInvalidParameter();
    }
    // local_28/puStack_20 = (*vec, end)
    void* itPair[2] = { pEnd, nullptr };
    void* proxyPair[2] = { (void*)pVec->m_pProxy,
                           (void*)pEnd };
    // (the call: a30(vec, &local_18, &local_28, obj))
    void* itOut[2];
    VecGrowForPush(pVec, itOut, proxyPair, ppObj);
    (void)itPair;
}

// ---- FUN_141552340: CtorPeerageSort ----
CPeerageSort* CtorPeerageSort(void* pRow,
                              uint64_t* puPair) {
    if (pRow == nullptr || puPair == nullptr) {
        return nullptr;
    }
    CPeerageSort* p = (CPeerageSort*)
        g_fnSortAlloc(sizeof(CPeerageSort));
    if (p == nullptr) {
        return nullptr;
    }
    p->SetVft((void*)1);   // CPeerageSort::vftable
    p->SetRow(pRow);
    p->SetN14(0);
    p->SetN18(0);
    p->SetField1c(puPair[0]);
    p->SetField24(puPair[1]);
    p->SetB2b(0);
    return p;
}

// ---- FUN_141552170: SetSortField18 ----
void SetSortField18(CPeerageSort* p, uint32_t uVal) {
    p->SetN18(uVal);
}

// ---- FUN_141554ff0: CtorPeerageSortMgr ----
CPeerageSortMgr* CtorPeerageSortMgr(
    CPeerageSortMgr* p) {
    p->m_pVftable = (void*)2;  // CPeerageSortMgr vt
    // the proxy: operator_new(8), *proxy = &vec
    void* pProxy = g_fnProxyAlloc(8);
    void* pProxyOut = nullptr;
    if (pProxy != nullptr) {
        *(void**)pProxy = (char*)p + 8;
        pProxyOut = pProxy;
    }
    p->m_vec.m_pProxy = pProxyOut;
    p->m_vec.m_ppBegin = nullptr;
    p->m_vec.m_ppEnd = nullptr;
    p->m_vec.m_ppCap = nullptr;
    p->m_uSpare38 = 0;
    p->m_pDb = nullptr;
    p->m_nRankNum48 = 0;
    return p;
}

// ---- FUN_141555690: MakePeerageSortMgr ----
CPeerageSortMgr* MakePeerageSortMgr() {
    CPeerageSortMgr* p = (CPeerageSortMgr*)
        g_fnSortAlloc(sizeof(CPeerageSortMgr));
    if (p != nullptr) {
        p = CtorPeerageSortMgr(p);
    }
    if (p == nullptr) {
        g_fnSortLogError();
        return nullptr;
    }
    return p;
}

// ---- FUN_1415548b0: FindSortById ----
void* FindSortById(CPeerageSortMgr* p, int n) {
    void** pp = p->m_vec.m_ppBegin;
    if (p->m_vec.m_ppEnd < pp) {
        g_fnInvalidParameter();
    }
    void* pProxy = p->m_vec.m_pProxy;
    while (true) {
        void** ppEnd = p->m_vec.m_ppEnd;
        if (ppEnd < p->m_vec.m_ppBegin) {
            g_fnInvalidParameter();
        }
        if (pProxy == nullptr
            || pProxy != p->m_vec.m_pProxy) {
            g_fnInvalidParameter();
        }
        if (pp == ppEnd) {
            break;
        }
        // the debug range check (via *proxy)
        int64_t lVec = (pProxy != nullptr)
            ? *(int64_t*)pProxy : 0;
        if ((void*)*(void**)(lVec + 0x20)
                <= (void*)pp) {
            g_fnInvalidParameter();
        }
        void* pElem = *pp;
        if (pElem == nullptr) {
            g_fnSortLogError();
        } else {
            void* pRow = *(void**)((char*)pElem + 8);
            void* pRec = g_fnRowQuery(pRow, 3);
            int nId = g_fnRowGetInt(pRec);
            if (nId == n) {
                return pElem;
            }
        }
        // the second debug range check
        int64_t lVec2 = (pProxy != nullptr)
            ? *(int64_t*)pProxy : 0;
        if ((void*)*(void**)(lVec2 + 0x20)
                <= (void*)pp) {
            g_fnInvalidParameter();
        }
        ++pp;
    }
    return nullptr;
}

} // namespace peerage

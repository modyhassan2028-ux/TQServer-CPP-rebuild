#include "MsgVectorFamily.h"
#include <new>
#include <stdexcept>

namespace msg {

// ===== M70: ORIGINAL FUN_1400092d0 VERBATIM =====
// the guard: n != 0 and (max / n) < 0x10 ->
// std::bad_alloc; else operator new(n << 4)
// (the ORIGINAL returns the operator_new result -
// Ghidra dropped the tail return)
void* VecAlloc(void* /*pVec*/, uint64_t qElems) {
    if (qElems != 0 &&
        0xffffffffffffffffULL / qElems < 0x10)
        throw std::bad_alloc();
    return operator new(qElems << 4);
}

// ===== M70: ORIGINAL FUN_14000a6e0 VERBATIM =====
void VecFill(void* pDst, int64_t qN,
             const void* pVal) {
    const uint64_t* pS = (const uint64_t*)pVal;
    uint64_t* pD = (uint64_t*)pDst;
    for (; qN != 0; qN--) {
        pD[0] = pS[0];
        pD[1] = pS[1];
        pD += 2;
    }
}

// ===== M70: ORIGINAL FUN_140009710 VERBATIM =====
void* VecCopy(const void* pFrom, const void* pTo,
              void* pDst) {
    const uint64_t* pS = (const uint64_t*)pFrom;
    uint64_t* pD = (uint64_t*)pDst;
    for (; (const void*)pS != pTo; pS += 2) {
        pD[0] = pS[0];
        pD[1] = pS[1];
        pD += 2;
    }
    return pD;
}

// ===== M70: ORIGINAL FUN_14000bac0 VERBATIM =====
// the backward-walking copy: each element at src-0x10
// goes to (pEnd - pTo) + src-0x10 (moves UP)
void* VecMoveBack(const void* pFrom, const void* pTo,
                  const void* pEnd) {
    int64_t lOff = (int64_t)((const char*)pEnd -
                             (const char*)pTo);
    int64_t lA = (int64_t)pTo;
    if (pFrom != pTo) {
        int64_t lSrc = lA;
        int64_t lDst = 0;
        do {
            lDst = lSrc - 0x10;
            *(uint64_t*)(lOff + lDst) =
                *(uint64_t*)(lSrc - 0x10);
            *(uint64_t*)(lOff + lDst + 8) =
                *(uint64_t*)(lSrc - 8);
            lSrc = lDst;
        } while (lDst != (int64_t)pFrom);
    }
    return (void*)((int64_t)pEnd -
        (((int64_t)pTo - (int64_t)pFrom) &
         0xfffffffffffffff0ULL));
}

// ===== M70: ORIGINAL FUN_14000eab0 VERBATIM =====
// insert n value-pairs AT THE FRONT. pBasePair =
// param_2 of the ORIGINAL: a stack pair whose +8
// holds the FIRST pointer (every read of param_2+8
// equals vector+0x18 - kept VERBATIM as passed).
// (empty-body checks = release iterator guards)
void VecInsertFront(SVec* pV, void* pBasePair,
                    uint64_t qN, const void* pVal) {
    int64_t lFirst = (int64_t)pV->m_pFirst;
    uint64_t qCapE;
    if (lFirst == 0)
        qCapE = 0;
    else
        qCapE = ((uint64_t)pV->m_pCap - lFirst) >> 4;
    if (qN != 0) {
        int64_t lLast = (int64_t)pV->m_pLast;
        int64_t lOldN = (lLast - lFirst) >> 4;
        if (0xfffffffffffffffULL - lOldN < qN) {
            // FUN_140007aa0 VERBATIM:
            throw std::length_error(
                "vector<T> too long");
        }
        uint64_t qNeed = qN + lOldN;
        if (qCapE < qNeed) {
            // ===== the GROW branch =====
            uint64_t qNewCap = qCapE;
            if (0xfffffffffffffffULL - (qCapE >> 1) <
                qCapE)
                qNewCap = 0;
            else
                qNewCap = qCapE + (qCapE >> 1);
            if (qNewCap < qNeed)
                qNewCap = qNeed;
            void* pNew = VecAlloc(
                (char*)pV + 0x10, qNewCap);
            int64_t lPre =
                ((int64_t)*(void**)((char*)pBasePair+8)
                 - lFirst) >> 4;   // = 0 VERBATIM
            VecFill((char*)pNew + lPre * 0x10,
                    qN, pVal);
            VecCopy((void*)lFirst,
                    *(void**)((char*)pBasePair + 8),
                    pNew);       // prefix (empty)
            VecCopy(
                *(void**)((char*)pBasePair + 8),
                (void*)lLast,
                (char*)pNew + (lPre + qN) * 0x10);
            int64_t lOldFirst = lFirst;
            int64_t lOldLast = lLast;
            if ((void*)lOldFirst)
                operator delete((void*)lOldFirst);
            pV->m_pCap =
                (char*)pNew + qNewCap * 0x10;
            pV->m_pLast = (char*)pNew +
                (qN + ((lOldLast - lOldFirst) >> 4))
                * 0x10;
            pV->m_pFirst = pNew;
        } else if ((uint64_t)lOldN < qN) {
            // ===== the SHIFT branch (n > old size,
            // capacity fits): move forward, fill the
            // vacated front + the gap =====
            uint64_t qV[2];
            qV[0] = ((const uint64_t*)pVal)[0];
            qV[1] = ((const uint64_t*)pVal)[1];
            VecCopy(*(void**)((char*)pBasePair + 8),
                     (void*)lLast,
                     (char*)lFirst + qN * 0x10);
            VecFill((void*)lLast,
                    qN - ((lLast - lFirst) >> 4),
                    qV);
            pV->m_pLast =
                (char*)lLast + qN * 0x10;
            int64_t lNewLast =
                (int64_t)pV->m_pLast;
            for (uint64_t* p =
                     (uint64_t*)lFirst;
                 p != (uint64_t*)(lNewLast -
                     (int64_t)qN * 0x10); p += 2) {
                p[0] = qV[0];
                p[1] = qV[1];
            }
        } else {
            // ===== the MOVE-BACK branch (n <= old
            // size): duplicate the last n at the
            // end, move the head up, fill =====
            uint64_t qV[2];
            qV[0] = ((const uint64_t*)pVal)[0];
            qV[1] = ((const uint64_t*)pVal)[1];
            int64_t lTail = lLast - qN * 0x10;
            pV->m_pLast = VecCopy((void*)lTail,
                (void*)lLast, (void*)lLast);
            VecMoveBack((void*)lFirst, (void*)lTail,
                        (void*)lLast);
            uint64_t* pEnd =
                (uint64_t*)lFirst + qN * 2;
            for (uint64_t* p = (uint64_t*)lFirst;
                 p != pEnd; p += 2) {
                p[0] = qV[0];
                p[1] = qV[1];
            }
        }
    }
}

// ===== M70: ORIGINAL FUN_14000f4a0 VERBATIM =====
// clear (LAST = FIRST - the element-destroy loop is
// a no-op for the 0x10 POD pairs in the ORIGINAL:
// zero iterations by construction, documented) then
// refill via eab0 (the pBasePair stack pair = the
// vector's own {+0, FIRST})
void VecClearRefill(SVec* pV, uint64_t qN,
                    const void* pVal) {
    void* pFirst = pV->m_pFirst;
    void* pLast = pV->m_pLast;
    if (pFirst != pLast) {
        // the ORIGINAL's copy loop skeleton is dead
        // (src == dst range) - the literal effect:
        pV->m_pLast = pV->m_pFirst;
    }
    // local_28 = *vec; uStack_20 = FIRST:
    uint64_t qPair[2];
    qPair[0] = pV->m_q0;
    qPair[1] = (uint64_t)pV->m_pFirst;
    VecInsertFront(pV, qPair, qN, pVal);
}

} // namespace msg

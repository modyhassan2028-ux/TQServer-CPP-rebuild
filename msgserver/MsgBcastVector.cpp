#include "MsgBcastVector.h"
#include <new>
#include <stdexcept>
#include <cstdlib>

namespace msg {

// the seam (default = the CRT abort)
void (*g_fnBcastInvalidParam)() = []() {
    std::abort();
};

// ===== M67a: ORIGINAL FUN_140096be0 VERBATIM =====
void* BcastVecAlloc(void* /*pProxy*/, uint64_t qElems) {
    if (qElems != 0 &&
        0xffffffffffffffffULL / qElems < 0x10)
        throw std::bad_alloc();
    return operator new(qElems << 4);
}

// ===== M67a: ORIGINAL FUN_140098660 VERBATIM =====
uint64_t* BcastVecCopy(const uint64_t* pFrom,
                       const uint64_t* pTo,
                       uint64_t* pDst) {
    for (; pFrom != pTo; pFrom += 2) {
        if (pDst != nullptr) {
            pDst[0] = pFrom[0];
            pDst[1] = pFrom[1];
        }
        pDst += 2;
    }
    return pDst;
}

// ===== M67a: ORIGINAL FUN_14009cc60 VERBATIM =====
void BcastVecFill(uint64_t* pDst, uint64_t qN,
                  const uint64_t* pVal) {
    for (; qN != 0; qN--) {
        if (pDst != nullptr) {
            pDst[0] = pVal[0];
            pDst[1] = pVal[1];
        }
        pDst += 2;
    }
}

// ===== M67a: ORIGINAL FUN_1400a17a0 VERBATIM =====
void* BcastVecMoveBack(const void* pFrom,
                       const void* pTo,
                       const void* pEnd) {
    int64_t lOff = (int64_t)((const char*)pEnd -
                             (const char*)pTo);
    if (pFrom != pTo) {
        int64_t lSrc = (int64_t)pTo;
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

// ===== M67a: ORIGINAL FUN_14008e820 VERBATIM =====
// std::length_error("vector<T> too long")
[[noreturn]] void BcastVecTooLong() {
    throw std::length_error("vector<T> too long");
}

// ===== M67a: ORIGINAL FUN_1400b6290 VERBATIM =====
// the generic _Insert_n: qN pairs of pVal at the
// position carried by pPair+8.
void BcastVecInsert(SBVec* pV, void* pPair,
                    uint64_t qN, const void* pVal) {
    int64_t lFirst = (int64_t)pV->m_pFirst;
    uint64_t qCapE;
    if (lFirst == 0)
        qCapE = 0;
    else
        qCapE = ((uint64_t)pV->m_pCap - lFirst) >> 4;
    if (qN != 0) {
        int64_t lLast = (int64_t)pV->m_pLast;
        int64_t lPos =
            *(int64_t*)((char*)pPair + 8);
        int64_t lOldN = (lLast - lFirst) >> 4;
        if (0xfffffffffffffffULL - lOldN < qN) {
            BcastVecTooLong();     // FUN_14008e820
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
            void* pNew = BcastVecAlloc(
                (char*)pV + 0x10, qNewCap);
            int64_t lPre = (lPos - lFirst) >> 4;
            BcastVecFill((uint64_t*)pNew + lPre*2,
                         qN, (const uint64_t*)pVal);
            BcastVecCopy((uint64_t*)lFirst,
                         (uint64_t*)lPos,
                         (uint64_t*)pNew);
            BcastVecCopy((uint64_t*)lPos,
                         (uint64_t*)lLast,
                         (uint64_t*)pNew +
                             (lPre + qN) * 2);
            void* pOldFirst = pV->m_pFirst;
            int64_t lOldLast = lLast;
            if (pOldFirst != nullptr)
                operator delete(pOldFirst);
            pV->m_pCap =
                (char*)pNew + qNewCap * 0x10;
            pV->m_pLast = (char*)pNew +
                (qN + ((lOldLast - lFirst) >> 4))
                * 0x10;
            pV->m_pFirst = pNew;
        } else if ((uint64_t)((lLast - lPos) >> 4)
                   < qN) {
            // ===== the SHIFT branch (tail < qN):
            // move [pos, LAST) up by qN, fill the
            // vacated slots + the rest =====
            uint64_t qV[2];
            qV[0] = ((const uint64_t*)pVal)[0];
            qV[1] = ((const uint64_t*)pVal)[1];
            BcastVecCopy((uint64_t*)lPos,
                         (uint64_t*)lLast,
                         (uint64_t*)(lPos +
                                     (int64_t)qN*0x10));
            BcastVecFill((uint64_t*)lLast,
                         qN - ((uint64_t)(lLast - lPos) >> 4),
                         qV);
            pV->m_pLast =
                (char*)lLast + (int64_t)qN * 0x10;
            int64_t lNewLast =
                (int64_t)pV->m_pLast;
            for (uint64_t* p = (uint64_t*)lPos;
                 p != (uint64_t*)(lNewLast -
                     (int64_t)qN * 0x10);
                 p += 2) {
                p[0] = qV[0];
                p[1] = qV[1];
            }
        } else {
            // ===== the MOVE-BACK branch (tail >= qN):
            // dupe the tail at the end, move the head
            // up, fill [pos, pos+qN) =====
            uint64_t qV[2];
            qV[0] = ((const uint64_t*)pVal)[0];
            qV[1] = ((const uint64_t*)pVal)[1];
            int64_t lTail = lLast -
                (int64_t)qN * 0x10;
            pV->m_pLast = BcastVecCopy(
                (uint64_t*)lTail, (uint64_t*)lLast,
                (uint64_t*)lLast);
            BcastVecMoveBack((void*)lFirst,
                             (void*)lTail,
                             (void*)lLast);
            uint64_t* pEnd =
                (uint64_t*)lPos + qN * 2;
            for (uint64_t* p = (uint64_t*)lPos;
                 p != pEnd; p += 2) {
                p[0] = qV[0];
                p[1] = qV[1];
            }
        }
    }
}

// ===== M67a: ORIGINAL FUN_1400ec4f0 VERBATIM =====
void BcastVecResize(SBVec* pV, uint64_t qN,
                    const void* pVal) {
    uint64_t* pLast = (uint64_t*)pV->m_pLast;
    uint64_t* pFirst = (uint64_t*)pV->m_pFirst;
    uint64_t qSize =
        (uint64_t)(pLast - pFirst) >> 1; // >>4 /16
    if (qSize < qN) {
        if (pLast < pFirst) {
            // _invalid_parameter_noinfo()
            g_fnBcastInvalidParam();   // _invalid_parameter_noinfo
            return;
        }
        // local pair: { *pV, LAST } -> append at END
        uint64_t aPair[2];
        aPair[0] = pV->m_q0;
        aPair[1] = (uint64_t)pV->m_pLast;
        BcastVecInsert(pV, aPair, qN - qSize, pVal);
        return;
    }
    if (qSize <= qN)
        return;   // == n: no-op
    // ===== the SHRINK branch =====
    if (pLast < pFirst) { g_fnBcastInvalidParam(); return; }
    uint64_t qF = (uint64_t)pV->m_pFirst;
    if ((uint64_t)pV->m_pLast < qF) {
        g_fnBcastInvalidParam(); return;
    }
    int64_t lProxy = *(int64_t*)pV;   // *param_1
    if (lProxy == 0) { g_fnBcastInvalidParam(); return; }
    int64_t lCont = *(int64_t*)lProxy;
    uint64_t* pNewLast =
        (uint64_t*)(qF + qN * 0x10);
    if (pNewLast <= *(uint64_t**)(lCont + 0x20)) {
        if (*(uint64_t**)(lCont + 0x18) <= pNewLast)
            goto InRange;
    }
    g_fnBcastInvalidParam(); return;
InRange:
    if (pNewLast < (uint64_t*)pV->m_pFirst ||
        (uint64_t*)pV->m_pLast < pNewLast) {
        g_fnBcastInvalidParam(); return;
    }
    int64_t lProxy2 = *(int64_t*)pV;
    if (pLast < (uint64_t*)pV->m_pFirst ||
        (uint64_t*)pV->m_pLast < pLast) {
        g_fnBcastInvalidParam(); return;
    }
    if (lProxy2 == 0 || lProxy2 != *(int64_t*)pV) {
        g_fnBcastInvalidParam(); return;
    }
    if (pNewLast != pLast) {
        // the raw's element-move loop skeleton:
        // iterates [oldLast, LAST) - ZERO elements
        // by construction (release-dead destroy loop
        // for the 0x10 POD pairs) - kept literal
        uint64_t* pEnd = (uint64_t*)pV->m_pLast;
        uint64_t* pIt = pLast;
        while (pIt != pEnd) {
            uint64_t* pNext = pIt + 2;
            *(uint64_t*)((char*)pNewLast +
                (-0x10 - (int64_t)pLast) +
                (int64_t)pNext) = pIt[0];
            *(uint64_t*)((char*)pNewLast +
                (-8 - (int64_t)pLast) +
                (int64_t)pNext) = pIt[1];
            pIt = pNext;
        }
        pV->m_pLast = (void*)(
            ((char*)pEnd - (char*)pLast &
             0xfffffffffffffff0ULL) +
            (char*)pNewLast);
    }
}

} // namespace msg

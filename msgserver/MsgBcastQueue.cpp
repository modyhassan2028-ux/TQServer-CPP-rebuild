#include "MsgBcastQueue.h"
#include "MsgBcastVector.h"
#include <new>
#include <stdexcept>
#include <cstring>

namespace msg {

// the invalid-parameter seam (shared with M67a -
// the raw calls _invalid_parameter_noinfo, a CRT
// abort; the port returns after the seam call,
// which the noreturn original never reaches)
extern void (*g_fnBcastInvalidParam)();

// ===== M67b: ORIGINAL FUN_14009a2a0 VERBATIM =====
void* BcastSentNew() {
    void* pv = operator new(0x40);
    if (pv != nullptr) {
        *(void**)pv = pv;              // next = self
    }
    if ((char*)pv + 8 != nullptr) {    // tautology
        *(void**)((char*)pv + 8) = pv; // prev = self
    }
    return pv;
}

// ===== M67b: ORIGINAL FUN_14009ad30 VERBATIM =====
void* BcastListNodeNew(void* pNext, void* pPrev,
                       const void* pData) {
    uint64_t* pn = (uint64_t*)operator new(0x40);
    if (pn != nullptr) {
        pn[0] = (uint64_t)pNext;
    }
    if (pn + 1 != nullptr) {           // tautology
        pn[1] = (uint64_t)pPrev;
    }
    if (pn + 2 != nullptr) {           // tautology
        const uint64_t* pd =
            (const uint64_t*)pData;
        pn[2] = pd[0]; pn[3] = pd[1];
        pn[4] = pd[2]; pn[5] = pd[3];
        pn[6] = pd[4]; pn[7] = pd[5];
    }
    return pn;
}

// ===== M67b: ORIGINAL FUN_1400a5f80 VERBATIM =====
void BcastListAppend(void* pList, uint64_t* pPos,
                     uint64_t* pItFirst,
                     uint64_t* pItLast) {
    for (;;) {
        // the _Compat check: begin/end share the
        // anchor chain (raw: 0 or mismatch ->
        // CRT abort)
        if (pItFirst[0] == 0 ||
            pItFirst[0] != pItLast[0]) {
            g_fnBcastInvalidParam(); return;
        }
        // reached the end sentinel -> done
        if (pItFirst[1] == pItLast[1])
            return;
        uint64_t qSent = pPos[1];   // dest sentinel
        // the src container through the anchor
        void* pAnchor =
            (void*)pItFirst[0];
        void* pCont = nullptr;
        if (pAnchor == nullptr) {
            g_fnBcastInvalidParam(); return;
        }
        pCont = *(void**)pAnchor;
        if (pItFirst[1] ==
            *(uint64_t*)((char*)pCont + 0x28)) {
            g_fnBcastInvalidParam(); return;
        }
        // the node copy {next=sent, prev=sent->prev,
        // data = 48 bytes at src walker + 0x10}
        void* pNew = BcastListNodeNew(
            (void*)qSent,
            *(void**)((char*)qSent + 8),
            (const void*)(pItFirst[1] + 0x10));
        // "list<T> too long" (FUN_14008e820 twin
        // check on the count at list+0x30)
        if (*(uint64_t*)((char*)pList + 0x30) ==
            0x555555555555555ULL) {
            throw std::length_error(
                "list<T> too long");
        }
        (*(uint64_t*)((char*)pList + 0x30))++;
        // relink: sentinel->prev = new;
        // new->prev->next = new
        *(void**)((char*)qSent + 8) = pNew;
        *(void**)(*(void**)((char*)pNew + 8)) =
            pNew;
        // the advance-guard (release-dead _Compat
        // re-check on the src container)
        void* pA2 = (void*)pItFirst[0];
        if (pA2 == nullptr) {
            g_fnBcastInvalidParam(); return;
        }
        void* pC2 = *(void**)pA2;
        if (pItFirst[1] ==
            *(uint64_t*)((char*)pC2 + 0x28)) {
            g_fnBcastInvalidParam(); return;
        }
        // advance: walker = walker->next
        pItFirst[1] = *(uint64_t*)pItFirst[1];
    }
}

// ===== M67b: ORIGINAL FUN_1400ef8d0 VERBATIM =====
void BcastQueueUpdate(SBcastQ* pQ, SBcastQ* pSrc) {
    // 1) the resize fill pair = {**anchor-chain,
    //    dest sentinel}: anchor -> &list -> anchor
    //    VALUE (three raw derefs at ef906..ef923)
    uint64_t aFill[2];
    void* pSent = pQ->m_pSent;
    uint64_t qL3;
    {
        uint64_t qL1 = *(uint64_t*)((char*)pQ + 0x10);
        uint64_t qL2;
        if (qL1 == 0)
            qL2 = 0;               // (ef916)
        else
            qL2 = *(uint64_t*)qL1; // (ef90f)
        qL3 = *(uint64_t*)qL2;     // (ef920)
    }
    aFill[0] = qL3;
    aFill[1] = (uint64_t)pSent;
    // src vector count = (*(src+0x68) -
    // *(src+0x60)) >> 4
    uint64_t qSrcN =
        ((char*)pSrc->m_vLast -
         (char*)pSrc->m_vFirst) >> 4;
    BcastVecResize(
        (SBVec*)((char*)pQ + 0x48),
        qSrcN, aFill);
    // 2) the field copies
    pQ->m_q78 = pSrc->m_q78;
    pQ->m_q80 = pSrc->m_q80;
    pQ->m_dw88 = pSrc->m_dw88;
    // 3) clear the dest list (delete the nodes)
    {
        void* s = pQ->m_pSent;
        void* first = *(void**)s;
        *(void**)s = s;             // next = self
        *(void**)((char*)s + 8) = s; // prev = self
        pQ->m_qSize = 0;
        for (void* n = first; n != s; ) {
            void* nx = *(void**)n;
            operator delete(n);
            n = nx;
        }
    }
    // 4) append-COPY the src list (the three
    //    iterator pairs built at ef9a9..efa3d)
    {
        uint64_t aPos[2]  =
            { *(uint64_t*)((char*)pQ + 0x10),
              (uint64_t)pQ->m_pSent };
        uint64_t aBeg[2]  =
            { *(uint64_t*)((char*)pSrc + 0x10),
              *(uint64_t*)pSrc->m_pSent };
        uint64_t aEnd[2]  =
            { *(uint64_t*)((char*)pSrc + 0x10),
              (uint64_t)pSrc->m_pSent };
        BcastListAppend((char*)pQ + 0x10, aPos,
                        aBeg, aEnd);
    }
    // 5) the byte copy
    *(uint8_t*)((char*)pQ + 8) =
        *(uint8_t*)((char*)pSrc + 8);
    // 6) the sync walk
    {
        void* walkerD = *(void**)pQ->m_pSent;
        void* anchorD =
            *(void**)((char*)pQ + 0x10);
        void* walkerS = *(void**)pSrc->m_pSent;
        void* anchorS =
            *(void**)((char*)pSrc + 0x10);
        uint64_t i = 0;
        uint64_t qDestN =
            ((char*)pQ->m_vLast -
             (char*)pQ->m_vFirst) >> 4;
        if (qDestN == 0)
            return;
        for (;;) {
            // src bounds: i < src count (raw:
            // noreturn CRT abort)
            uint64_t qSrcN2 =
                ((char*)pSrc->m_vLast -
                 (char*)pSrc->m_vFirst) >> 4;
            if (i >= qSrcN2) {
                g_fnBcastInvalidParam();
                return;
            }
            if (*(void**)((char*)pSrc->m_vFirst
                    + 8 + i * 0x10) == walkerS) {
                // MATCH: write {anchor value,
                // dest walker} into slot i
                uint64_t qVal = 0;
                if (anchorD != nullptr)
                    qVal = *(uint64_t*)anchorD;
                // (raw efac4: the second deref)
                qVal = *(uint64_t*)qVal;
                uint64_t aPair[2];
                aPair[0] = qVal;
                aPair[1] = (uint64_t)walkerD;
                // dest bounds: i < dest count
                uint64_t qDestN2 =
                    ((char*)pQ->m_vLast -
                     (char*)pQ->m_vFirst) >> 4;
                if (i >= qDestN2) {
                    g_fnBcastInvalidParam();
                    return;
                }
                ((uint64_t*)pQ->m_vFirst)[i*2] =
                    aPair[0];
                ((uint64_t*)pQ->m_vFirst)[i*2+1] =
                    aPair[1];
                i++;
            } else {
                // ADVANCE both walkers (the
                // end-guards: walker == sentinel
                // -> CRT abort)
                if (anchorD == nullptr) {
                    g_fnBcastInvalidParam();
                    return;
                }
                void* contD = *(void**)anchorD;
                if (walkerD ==
                    *(void**)((char*)contD + 0x28)) {
                    g_fnBcastInvalidParam();
                    return;
                }
                walkerD = *(void**)walkerD;
                if (anchorS == nullptr) {
                    g_fnBcastInvalidParam();
                    return;
                }
                void* contS = *(void**)anchorS;
                if (walkerS ==
                    *(void**)((char*)contS + 0x28)) {
                    g_fnBcastInvalidParam();
                    return;
                }
                walkerS = *(void**)walkerS;
            }
            // loop while i < dest count
            qDestN =
                ((char*)pQ->m_vLast -
                 (char*)pQ->m_vFirst) >> 4;
            if (i >= qDestN)
                return;
        }
    }
}

// ===== M67b: ORIGINAL FUN_1400f03b0 VERBATIM =====
SBcastQ* BcastQCreate(SBcastQ* pQ, SBcastQ* pSrc) {
    *(uint8_t*)((char*)pQ + 8) =
        *(uint8_t*)((char*)pSrc + 8);
    // the list anchor cell {->list at +0x10}
    {
        void** pa = (void**)operator new(8);
        if (pa != nullptr)
            *pa = (char*)pQ + 0x10;
        *(void***)((char*)pQ + 0x10) = pa;
    }
    // sentinel + size
    pQ->m_pSent = BcastSentNew();
    pQ->m_qSize = 0;
    // the vector anchor cell {->vector at +0x48}
    {
        void** pb = (void**)operator new(8);
        if (pb != nullptr)
            *pb = (char*)pQ + 0x48;
        *(void***)((char*)pQ + 0x48) = pb;
    }
    pQ->m_vFirst = nullptr;
    pQ->m_vLast = nullptr;
    pQ->m_vCap = nullptr;
    BcastQueueUpdate(pQ, pSrc);
    return pQ;
}

} // namespace msg

namespace msg {

// ===== M67c: ORIGINAL FUN_1400a3410 VERBATIM =====
uint64_t* BcastQueueFind(SBcastQ* pQ, uint32_t dwKey,
                         uint64_t* pOut) {
    // the Park-Miller hash (16807/2836 minimal
    // standard) of the obfuscated key
    uint32_t q = ((dwKey ^ 0xdeadbeefU) &
                  0x7fffffffU) / 0x1f31dU;
    int32_t n = ((int32_t)(((dwKey ^ 0xdeadbeefU) &
                  0x7fffffffU) % 0x1f31dU) * 0x41a7) -
                (int32_t)q * 0xb14;
    if (n < 0)
        n += 0x7fffffff;
    uint64_t mask = pQ->m_q78;
    uint64_t idx = (uint64_t)n & mask;
    if (pQ->m_q80 <= idx)
        idx = idx + (-1ULL - (mask >> 1));
    uint64_t qVecSize =
        ((char*)pQ->m_vLast - (char*)pQ->m_vFirst)
        >> 4;
    if (qVecSize <= idx) {
        g_fnBcastInvalidParam(); return pOut;
    }
    void* pAnchorCell =
        *(void**)((char*)pQ + 0x10);   // plVar2
    void* pBucket =
        *(void**)((char*)pQ->m_vFirst + 8 +
                  idx * 0x10);
    if (pAnchorCell == nullptr) {
        g_fnBcastInvalidParam(); return pOut;
    }
    void* pListObj =
        *(void**)pAnchorCell;          // lVar7
    void* node = pBucket;
    for (;;) {
        if (qVecSize <= idx + 1) {
            g_fnBcastInvalidParam(); return pOut;
        }
        // the empty bucket: next bucket shares node
        if (*(void**)((char*)pQ->m_vFirst + 8 +
                (idx + 1) * 0x10) == pBucket) {
            pOut[1] = (uint64_t)pQ->m_pSent;
            pOut[0] = (uint64_t)pAnchorCell;
            return pOut;
        }
        if (pListObj == nullptr) {
            g_fnBcastInvalidParam(); return pOut;
        }
        if (node == *(void**)((char*)pListObj + 0x28)) {
            g_fnBcastInvalidParam(); return pOut;
        }
        // the key at data[0].u32 (node+0x10)
        if (dwKey <= *(uint32_t*)((char*)node + 0x10))
            break;
        if (node == *(void**)((char*)pListObj + 0x28)) {
            g_fnBcastInvalidParam(); return pOut;
        }
        node = *(void**)node;   // next chain node
    }
    // node.key >= key: found or END
    if (node == *(void**)((char*)pListObj + 0x28)) {
        g_fnBcastInvalidParam(); return pOut;
    }
    if (dwKey < *(uint32_t*)((char*)node + 0x10)) {
        // lower_bound overshoot -> END pair
        pOut[0] = (uint64_t)pAnchorCell;
        pOut[1] = (uint64_t)pQ->m_pSent;
    } else {
        pOut[0] = (uint64_t)pAnchorCell;
        pOut[1] = (uint64_t)node;
    }
    return pOut;
}

// ===== M67c: ORIGINAL FUN_1400b29c0 VERBATIM =====
void* BcastQueueLookupData(void* pMapGroup,
                           uint32_t dwKey) {
    SBcastQ* pQ =
        (SBcastQ*)((char*)pMapGroup + 0x4b8);
    uint64_t aIt[2] = {0, 0};
    BcastQueueFind(pQ, dwKey, aIt);
    void* pSent = *(void**)((char*)pMapGroup + 0x4f0);
    if (aIt[0] == 0 ||
        aIt[0] != *(uint64_t*)((char*)pMapGroup + 0x4c8)) {
        g_fnBcastInvalidParam(); return nullptr;
    }
    if (aIt[1] != (uint64_t)pSent) {
        // found: re-find + the sentinel guard
        uint64_t aIt2[2] = {0, 0};
        BcastQueueFind(pQ, dwKey, aIt2);
        void* pObj = nullptr;
        if (aIt2[0] == 0) {
            g_fnBcastInvalidParam(); return nullptr;
        }
        pObj = *(void**)aIt2[0];
        if (aIt[1] == (uint64_t)
                *(void**)((char*)pObj + 0x28)) {
            g_fnBcastInvalidParam(); return nullptr;
        }
        return (void*)(aIt[1] + 0x18);
    }
    return nullptr;
}

} // namespace msg

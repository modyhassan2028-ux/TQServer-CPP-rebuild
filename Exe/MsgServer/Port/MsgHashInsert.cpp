#include "MsgHashInsert.h"
#include "MsgHashList.h"
#include "MsgHashProbe.h"
#include "MsgVectorFamily.h"
#include <cstdlib>

namespace msg {

// ===== M71: ORIGINAL FUN_14000f880 VERBATIM =====
// (the release-empty MSVC iterator formality guards
// documented as skipped; the two live data reads
// kept literally)
void* HashInsert(SHashContainer* pC, void* pOut,
                 int32_t* pKey, void* pHint) {
    uint8_t* pB = (uint8_t*)pC;
    void** pHintQ = (void**)pHint;
    void** pOutQ = (void**)pOut;
    // the VERBATIM hash: ldiv(key, 0x1f31d)
    ldiv_t d = ldiv(*pKey, 0x1f31d);
    int iVar3 = d.rem * 0x41a7 + d.quot * -0xb14;
    if (iVar3 < 0) iVar3 += 0x7fffffff;
    uint64_t uVar7 = (uint64_t)(int64_t)iVar3 &
                     pC->m_qMask;
    if (pC->m_qBuckets <= uVar7)
        uVar7 = uVar7 + (-1 - (pC->m_qMask >> 1));
    uint8_t* pList = pB + 0x10;    // plVar6
    uint64_t qBuck = (uint64_t)pC->m_vec.m_pFirst;
    void* lVar8 = *(void**)(qBuck + 8 +
                            (uVar7 + 1) * 0x10);
    void* lStack_60 = lVar8;
    void* lVar1 = *(void**)pList;  // the proxy
    void* local_68 = lVar1;
    uint64_t lVar10 = uVar7 * 0x10;
    // the backward probe walk of the bucket
    do {
        void* lVar2 = *(void**)(qBuck + 8 + lVar10);
        if (lVar8 == lVar2) goto INSERT;
        lVar8 = *(void**)((char*)lVar8 + 8); // prev
        lStack_60 = lVar8;
    } while (*pKey !=
             *(int32_t*)((char*)lVar8 + 0x10));
    // ===== the DUPLICATE path =====
    if (*(int32_t*)((char*)lVar8 + 0x10) == *pKey) {
        if (pHintQ[1] != pC->m_pEnd) {
            uint64_t it[2] = {(uint64_t)pHintQ[0],
                              (uint64_t)pHintQ[1]};
            uint64_t o[2];
            HashListErase(pList, (void**)o,
                          (void**)it);
        }
        *(uint8_t*)((char*)pOut + 0x10) = 0;
        pOutQ[0] = local_68;
    } else {
        lVar8 = *(void**)lVar8;   // step next
        lStack_60 = lVar8;
INSERT:
        // ===== the INSERT path =====
        if (pHintQ[1] == pC->m_pEnd) {
            // no valid hint: emplace before the
            // position, hint = the new node
            uint64_t it[2] = {(uint64_t)local_68,
                              (uint64_t)lStack_60};
            uint64_t o[2];
            HashListEmplace(pList, (void**)o,
                            (void**)it, pKey);
            pHintQ[0] = *(void**)o;
            pHintQ[1] = *((void**)o + 1);
        } else {
            // valid hint: TRANSFER the hint node
            uint64_t it1[2] = {(uint64_t)local_68,
                               (uint64_t)lStack_60};
            uint64_t it2[2] = {(uint64_t)pHintQ[0],
                              (uint64_t)pHintQ[1]};
            HashListTransfer(pList, (void**)it1,
                             pList, (void**)it2);
        }
        // ===== the boundary propagation loop
        // (the linchpin line: position = the NEW
        // node from hint[1], NOT the stale one)
        while (true) {
            void* lVar2 = *(void**)(qBuck + 8 + lVar10);
            if (lVar8 != lVar2) break;
            local_68 = pHintQ[0];
            lStack_60 = pHintQ[1];   // the NEW node
            void* plVar5 = (local_68 != nullptr) ?
                *(void**)local_68 : nullptr;
            void* local_58 = *(void**)plVar5;
            void* lStack_50 = lStack_60;
            *(void**)(qBuck + lVar10) = local_58;
            *(void**)(qBuck + lVar10 + 8) =
                lStack_50;
            if (uVar7 == 0) break;
            uVar7--;
            lVar10 -= 0x10;
        }
        // ===== the rehash trigger (max_load) =====
        uint64_t uVarCnt = pC->m_qBuckets;
        float fVar11 = (float)(int64_t)pC->m_qSize;
        if ((int64_t)pC->m_qSize < 0)
            fVar11 = fVar11 +
                18446744073709551616.0f; // 2^64
        float fVar12 = (float)(int64_t)uVarCnt;
        if ((int64_t)uVarCnt < 0)
            fVar12 = fVar12 +
                18446744073709551616.0f;
        if (pC->m_fMaxLoad <= fVar11 / fVar12 &&
            fVar11 / fVar12 != pC->m_fMaxLoad) {
            int iVar3b = 0;
            do {
                if (0x7fffffffffffffeULL < uVarCnt)
                    break;
                iVar3b++;
                uVarCnt *= 2;
            } while (iVar3b < 3);   // x8 VERBATIM
            // the fill pair {proxy, END}
            void* plVar6b = (*(void**)pList != nullptr)
                ? *(void**)*(void**)pList : nullptr;
            uint64_t pair[2];
            pair[0] = *(uint64_t*)plVar6b;
            pair[1] = (uint64_t)pC->m_pEnd;
            VecClearRefill(&pC->m_vec, uVarCnt + 1,
                           pair);
            pC->m_qMask = uVarCnt - 1;
            pC->m_qBuckets = uVarCnt;
            HashRebuild(pC);
        }
        pOutQ[0] = pHintQ[0];
        lStack_60 = pHintQ[1];
        *(uint8_t*)((char*)pOut + 0x10) = 1;
    }
    pOutQ[1] = lStack_60;
    return pOut;
}

// ===== M71: ORIGINAL FUN_14000fd50 VERBATIM =====
void HashRebuild(SHashContainer* pC) {
    uint8_t* pB = (uint8_t*)pC;
    uint8_t* pList = pB + 0x10;
    while (true) {
        void* plVar2 = *(void**)pList;  // the proxy
        void* lVar3 = *(void**)*(void**)(pB + 0x38);
                   // END->next = the front element
        void* lVar4 = *(void**)
            ((char*)pC->m_vec.m_pFirst + 8); // head0
        if (lVar3 == lVar4) break;
        // the hint pair {proxy, front-node} and the
        // key at front+0x10 (the 0x10 key block copy
        // in the ORIGINAL starts with *key - the
        // insert reads only the int key)
        uint64_t hint[2] = {(uint64_t)plVar2,
                            (uint64_t)lVar3};
        uint64_t out[6];
        HashInsert(pC, out,
                   (int32_t*)((char*)lVar3 + 0x10),
                   hint);
    }
}

// ===== M71: ORIGINAL FUN_140010970 VERBATIM =====
void* HashValueAt(SHashContainer* pC, int32_t* pKey) {
    uint8_t* pB = (uint8_t*)pC;
    uint64_t it[2] = {0, 0};
    HashProbeFind(pB, (void**)it, pKey);
    void* lVar1 = *(void**)(pB + 0x38);   // END
    if ((void*)it[1] == lVar1) {
        // MISS: insert with the END hint; the key
        // block copy starts with *pKey (VERBATIM)
        uint32_t keyBlk[4] = {(uint32_t)*pKey,
                              0, 0, 0};
        uint64_t hint[2];
        hint[0] = *(uint64_t*)(pB + 0x10);
        hint[1] = *(uint64_t*)(pB + 0x38);
        uint64_t out[6];
        HashInsert(pC, out, (int32_t*)keyBlk,
                   hint);
        it[0] = out[0]; it[1] = out[1];
    }
    return (char*)it[1] + 0x14;   // the value slot
}

} // namespace msg

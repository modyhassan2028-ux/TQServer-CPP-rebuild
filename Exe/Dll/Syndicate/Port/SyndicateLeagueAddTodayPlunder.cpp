// ============================================================================
// SyndicateLeagueAddTodayPlunder.cpp — unit D74, verbatim
// port of FUN_1417715f0 (v6159 Syndicate.dll).
// ============================================================================
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueAddTodayPlunder.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include <cstring>

namespace syndicate {

void  (*g_fnAtpMsgCtor)(void*);
char  (*g_fnAtpMsgCreate)(void*, int32_t, int32_t);
void  (*g_fnAtpMsgSerialize)(void*);
void  (*g_fnAtpMsgDtor)(void*);
void  (*g_fnAtpSendOptText)(void*, uint32_t, void*, void*, int32_t);

static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}

void AddTodayPlunderWarInfo(void* pMgr, uint32_t uIdPlunder,
                            int32_t nCount, uint32_t* aTargets) {
    char* pc = (char*)pMgr;
    if (uIdPlunder == 0) return;
    if (nCount <= 0) return;
    void* pLogic = RdP(pc, 8);

    // the repeat check — lower_bound into mgr+0x370
    uint32_t uKey = uIdPlunder;
    uint64_t aIter[2] = { 0, 0 };
    g_fnLbrMapLowerBound(pc + 0x370, aIter, &uKey);
    if (RdP(pc, 0x370) == nullptr ||
        RdP(pc, 0x370) != (void*)(uintptr_t)aIter[0])
        g_fnLbrInvalid();
    if (RdP(pc, 0x3a0) != (void*)(uintptr_t)aIter[1])
        g_fnPwsLogErr(
            "CLeagueMgr::AddTodayPlunderWarInfo data repeat idPlunder",
            (uint64_t)uIdPlunder);            // RAW lu%

    // the outer value map — the RAW stack container
    uint64_t aOuter[8] = { 0,0,0,0,0,0,0,0 };
    void* pWrap = g_fnLbrOpNew(8);
    if (pWrap == nullptr) aOuter[0] = 0;
    else { *(void**)pWrap = aOuter;
           aOuter[0] = (uint64_t)(uintptr_t)pWrap; }
    char* pTree = (char*)g_fnLbrHeadAlloc();
    *(unsigned char*)(pTree + 0x1d) = 1;
    ((void**)pTree)[1] = pTree;
    ((void**)pTree)[0] = pTree;
    ((void**)pTree)[2] = pTree;
    aOuter[6] = (uint64_t)(uintptr_t)pTree;    // +0x30
    // aOuter[7] (+0x38) = the size, starts 0

    alignas(8) unsigned char aMsg[0x2300];     // local_4a8[1120]

    // the teardown block (RAW: 14172a410 + the two deletes)
    auto Teardown = [&]() {
        uint64_t aD1[2] = { 0, 0 }, aD2[2] = { 0, 0 },
                 aD3[2] = { 0, 0 };
        g_fnLbrMapEraseRange(aOuter, aD1, aD2, aD3);
        g_fnLbrOpDelete(pTree);
        pTree = nullptr;
        aOuter[7] = 0;
        g_fnLbrOpDelete((void*)(uintptr_t)aOuter[0]);
    };

    for (int32_t i = 0; i < nCount; i++) {
        if (9 < i) break;                      // RAW cap
        uint32_t uT = aTargets[i];
        uint32_t uKeyOuter = uT;               // local_640 lo
        if (uT == 0) continue;
        // the inline lower_bound walk over mgr+0x3b0
        char* pHeadB = (char*)RdP(pc, 0x3e0);
        char* pCur = (char*)RdP(pHeadB, 8);     // head[1] = root
        char* pBest = pHeadB;
        while (*(unsigned char*)(pCur + 0x61) == 0) {
            char* pNext;
            if (*(uint32_t*)(pCur + 0x18) < uT) {
                pNext = (char*)RdP(pCur, 0x10);
            } else {
                pBest = pCur;
                pNext = (char*)RdP(pCur, 0);
            }
            pCur = pNext;
        }
        void* pProxyB = RdP(pc, 0x3b0);
        void* pItNode;
        if (pBest == pHeadB ||
            uT < *(uint32_t*)(pBest + 0x18))
            pItNode = pHeadB;                   // end
        else
            pItNode = pBest;                   // found
        if (RdP(pc, 0x3b0) == nullptr ||
            RdP(pc, 0x3b0) != pProxyB)
            g_fnLbrInvalid();
        if (pItNode == pHeadB) {
            // ABSENT: the new inner map + insert into mgr+0x3b0
            uint64_t aInner[8] = { 0,0,0,0,0,0,0,0 };
            void* pWrap2 = g_fnLbrOpNew(8);
            if (pWrap2 == nullptr) aInner[0] = 0;
            else { *(void**)pWrap2 = aInner;
                   aInner[0] = (uint64_t)(uintptr_t)pWrap2; }
            char* pTree2 = (char*)g_fnLbrHeadAlloc();
            *(unsigned char*)(pTree2 + 0x1d) = 1;
            ((void**)pTree2)[1] = pTree2;
            ((void**)pTree2)[0] = pTree2;
            ((void**)pTree2)[2] = pTree2;
            aInner[6] = (uint64_t)(uintptr_t)pTree2;
            g_fnLbrMapInsertKey(aInner, aIter, &uKey);
            // the pair/move dance (RAW order preserved)
            uint64_t aTmpFirst[9] = { 0 };
            g_fnLbrMapMoveCtor(aTmpFirst, aInner);
            uint64_t aPair[10] = { 0 };
            g_fnLbrPairMake(aPair, uT, aTmpFirst);
            uint64_t aFinal[10] = { 0 };
            aFinal[0] = *(uint32_t*)aPair;
            g_fnLbrMapMoveCtor(aFinal + 1, aPair + 1);
            g_fnLbrMapInsertPair(pc + 0x3b0, aIter, aFinal);
            g_fnLbrMapTreeDtor(aFinal + 1);
            g_fnLbrOpDelete(*(void**)(aFinal + 1));
            g_fnLbrMapTreeDtor(aPair + 1);
            g_fnLbrOpDelete(*(void**)(aPair + 1));
            // clear + free the moved-from original
            uint64_t aE1[2] = { 0, 0 }, aE2[2] = { 0, 0 },
                    aE3[2] = { 0, 0 };
            g_fnLbrMapEraseRange(aInner, aE1, aE2, aE3);
            g_fnLbrOpDelete(pTree2);
            g_fnLbrOpDelete((void*)(uintptr_t)aInner[0]);
        } else {
            // FOUND: the deref checks + insert into node+0x20
            if (pProxyB == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pCont = *(void**)pProxyB;
                if (pItNode == RdP(pCont, 0x30))
                    g_fnLbrInvalid();
            }
            g_fnLbrMapInsertKey((char*)pItNode + 0x20,
                                aIter, &uKey);
        }
        // the outer map insert (always, RAW order)
        g_fnLbrMapInsertKey(aOuter, aIter, &uKeyOuter);
        uint64_t uMy = g_fnLbrGetMyLeague(pLogic);
        if (uT / 1000000 == uMy) {
            g_fnAtpMsgCtor(aMsg);
            if (g_fnAtpMsgCreate(aMsg, 4, 0) == 0) {
                g_fnAtpMsgDtor(aMsg);
                Teardown();
                return;                 // RAW: partial state
            }
            g_fnAtpMsgSerialize(aMsg);
            g_fnAtpSendOptText(pLogic, uT % 1000000, aMsg,
                              nullptr, 1);
            g_fnAtpMsgDtor(aMsg);
        }
    }

    if (aOuter[7] == 0) {              // the size gate
        Teardown();
        return;
    }
    // the final {id, map} pair into mgr+0x370
    uint64_t aTmpFirst[9] = { 0 };
    g_fnLbrMapMoveCtor(aTmpFirst, aOuter);
    uint64_t aPair[10] = { 0 };
    g_fnLbrPairMake(aPair, uIdPlunder, aTmpFirst);
    uint64_t aFinal[10] = { 0 };
    aFinal[0] = *(uint32_t*)aPair;
    g_fnLbrMapMoveCtor(aFinal + 1, aPair + 1);
    g_fnLbrMapInsertPair(pc + 0x370, aIter, aFinal);
    g_fnLbrMapTreeDtor(aFinal + 1);
    g_fnLbrOpDelete(*(void**)(aFinal + 1));
    g_fnLbrMapTreeDtor(aPair + 1);
    g_fnLbrOpDelete(*(void**)(aPair + 1));

    uint64_t uMy2 = g_fnLbrGetMyLeague(pLogic);
    if (uIdPlunder / 1000000 == uMy2) {
        g_fnAtpMsgCtor(aMsg);
        if (g_fnAtpMsgCreate(aMsg, 4, 0) == 0) {
            g_fnAtpMsgDtor(aMsg);
            Teardown();
            return;
        }
        g_fnAtpMsgSerialize(aMsg);
        g_fnAtpSendOptText(pLogic, uIdPlunder % 1000000, aMsg,
                          nullptr, 0);
        g_fnAtpMsgDtor(aMsg);
    }
    Teardown();
}

}  // namespace syndicate

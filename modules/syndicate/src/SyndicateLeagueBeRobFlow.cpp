// ============================================================
// Syndicate.dll port — unit D70: FUN_141771f90 (the league
// BeRob broadcast). See the .h for the full map of the
// function. Everything below is the raw control flow in
// order; the container kit + name getters + the logic vt
// are seams (bound to their raw addresses); the D69
// CMsgLeagueBeRob family is the real linked port.
//
// Stack object sizes: CMsg = 0x470 (1136 bytes, matches the
// decompile's CMsg local_db8[1136] arrays); the stack maps
// = 0x40-byte containers {proxy@0, head@+0x30, size@+0x38}.
// The name buffers = 16 bytes, cap 0x10.
// ============================================================
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"
#include "modules/syndicate/src/SyndicateLeagueBeRob.h"
#include <cstring>
#include <cstdio>

namespace syndicate {

// ---- the seam storage ----
void* (*g_fnLbrOpNew)(size_t) = nullptr;
void (*g_fnLbrOpDelete)(void*) = nullptr;
void (*g_fnLbrInvalid)() = nullptr;
void* (*g_fnLbrHeadAlloc)() = nullptr;
void* (*g_fnLbrMapCtor)(void*) = nullptr;
void* (*g_fnLbrMapInsertKey)(void*, void*, uint32_t*) = nullptr;
void* (*g_fnLbrMapMoveCtor)(void*, void*) = nullptr;
void* (*g_fnLbrPairMake)(void*, uint32_t, void*) = nullptr;
void* (*g_fnLbrMapLowerBound)(void*, void*, uint32_t*) = nullptr;
void* (*g_fnLbrMapInsertPair)(void*, void*, void*) = nullptr;
void (*g_fnLbrMapTreeDtor)(void*) = nullptr;
void* (*g_fnLbrMapEraseRange)(void*, void*, void*, void*) = nullptr;
void (*g_fnLbrIterAdvance)(void*) = nullptr;
void (*g_fnLbrMapInsertKeyRange)(void*, void*, void*) = nullptr;
int (*g_fnLbrGetNameById)(void*, uint32_t, char*, int) = nullptr;
int (*g_fnLbrGetLeagueName)(void*, uint32_t, char*, int) = nullptr;
uint64_t (*g_fnLbrGetMyLeague)(void*) = nullptr;
void (*g_fnLbrSendMsg)(void*, uint64_t, void*, uint64_t) = nullptr;

// ---- the raw-offset readers (container/kit layouts) ----
static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}
static inline void WrP(void* p, size_t off, void* v) {
    *(void**)((char*)p + off) = v;
}
static inline uint64_t RdQ(void* p, size_t off) {
    return *(uint64_t*)((char*)p + off);
}
static inline void WrQ(void* p, size_t off, uint64_t v) {
    *(uint64_t*)((char*)p + off) = v;
}

// the inline FUN_141731fc0 body (as at the function top and
// the (A)/(B)/(D) insert branches): a 0x40-byte container
// {proxy@0, head@+0x30, size@+0x38}. Verbatim order: the
// proxy field is nulled FIRST, then operator_new(8) +
// back-link, then the head (FUN_141726c30) self-linked with
// isnil@+0x1d = 1, then size = 0.
static void LbrStackMapCtor(char* pMap) {
    WrP(pMap, 0, nullptr);
    void* pProxy = g_fnLbrOpNew(8);
    if (pProxy != nullptr) {
        WrP(pProxy, 0, pMap);
        WrP(pMap, 0, pProxy);
    }
    void* pHead = g_fnLbrHeadAlloc();
    *(unsigned char*)((char*)pHead + 0x1d) = 1;
    WrP(pHead, 0x08, pHead);   // [1] parent self
    WrP(pHead, 0x00, pHead);   // [0] left self
    WrP(pHead, 0x10, pHead);   // [2] right self
    WrP(pMap, 0x30, pHead);    // container[6] = the head
    WrQ(pMap, 0x38, 0);        // size (container[7])
}

// the stack-map teardown used by the inline-constructed
// maps: erase [head->left, head) via FUN_14172a410, then
// delete the head, then delete the proxy (verbatim order).
static void LbrStackMapDtor(char* pMap) {
    // the head is read FRESH: the move-ctor husk dance may have
    // replaced it since the map was built (the raw's local head
    // var IS the container's +0x30 slot, so it tracks too)
    void* pHead = RdP(pMap, 0x30);
    void* pProxy = RdP(pMap, 0);
    uint64_t aFirst[2]  = { (uint64_t)(uintptr_t)pProxy,
                            (uint64_t)(uintptr_t)RdP(pHead, 0) };
    uint64_t aLast[2]   = { (uint64_t)(uintptr_t)pProxy,
                            (uint64_t)(uintptr_t)pHead };
    uint64_t aOut[2] = { 0, 0 };
    g_fnLbrMapEraseRange(pMap, aOut, aFirst, aLast);
    g_fnLbrOpDelete(pHead);
    WrP(pMap, 0x30, nullptr);   // the raw: local_1518 = 0 (the slot)
    WrQ(pMap, 0x38, 0);         // the raw: local_1510 = 0
    g_fnLbrOpDelete(pProxy);
}

// the pair/insert dance shared by all five sites (verbatim
// per-site values are passed by the caller): temp := move(X)
// [FUN_1417695b0], pair {uPairKey, temp} [FUN_14176f690,
// which dtors the temp], the insert-arg's key dword := the
// pair's key, D := move(pair.second) [FUN_1417695b0 on the
// pair's +8], insert via FUN_141770ea0, then the two husk
// dtors [FUN_14172c560 + proxy delete] for D and the pair's
// second. pInsArg = the raw {key@0, D-map@+8} insert arg.
static void LbrPairInsert(char* pInsArg, uint32_t uPairKey,
                          char* pX, void* pOuterMap) {
    char* pD = pInsArg + 8;
    char aTemp[0x40];
    char aPair[0x48];   // {key@0, map@+8 (0x40)}
    uint64_t aOutIter[2] = { 0, 0 };
    g_fnLbrMapMoveCtor(aTemp, pX);                       // temp := move(X)
    g_fnLbrPairMake(aPair, uPairKey, aTemp);             // {key, move(temp)}
    *(uint32_t*)pInsArg = *(uint32_t*)aPair;   // the insert-arg key dword
    g_fnLbrMapMoveCtor(pD, aPair + 8);          // D := move(pair.second)
    g_fnLbrMapInsertPair(pOuterMap, aOutIter, pInsArg);
    g_fnLbrMapTreeDtor(pD);                     // dtor the inserted copy D
    g_fnLbrOpDelete(RdP(pD, 0));
    g_fnLbrMapTreeDtor(aPair + 8);              // dtor the moved-from second
    g_fnLbrOpDelete(RdP(aPair + 8, 0));
}

void LeagueBeRobBroadcast(void* pMgr, uint32_t uKey, int nCount,
                          uint32_t* pIds) {
    char* pc = (char*)pMgr;
    if (uKey == 0) return;                        // if (param_2 != 0)
    if (nCount <= 0) return;                      // if (0 < param_3)

    void* pLogic = RdP(pc, 8);                    // *(mgr+8)
    uint32_t uLeagueKeyOp = uKey;                 // local_1694
    uint32_t uKeyCopy     = uKey;                 // local_1690
    uint32_t* pIdsSaved   = pIds;                 // local_1658
    uint64_t uMyLeague = g_fnLbrGetMyLeague(pLogic);   // local_168c

    // the RESULT SET: the inline FUN_141731fc0 body
    char aResult[0x40];
    LbrStackMapCtor(aResult);
    void* pResultHead = RdP(aResult, 0x30);       // local_1608
    void* pResultProxy = RdP(aResult, 0);         // local_1638[0]

    int64_t nProcessed = 0;                       // local_1688 (the 9 < gate)
    for (int64_t i = 0; i < (int64_t)nCount; i++, nProcessed++) {
        if (9 < nProcessed) break;                // the 10-entry cap
        uint32_t uMember = pIds[i];               // uVar18
        if (uMember == 0) continue;
        uint32_t uMemberKey = uMember;            // local_1698 (by-address key)

        // ---------------- (A) mgr+0x3f0 [league][member] ----------------
        {
            uint64_t aIter[2] = { 0, 0 };
            g_fnLbrMapLowerBound(pc + 0x3f0, aIter, &uLeagueKeyOp);
            void* pItProxy = (void*)(uintptr_t)aIter[0];   // local_13d8
            void* pItNode  = (void*)(uintptr_t)aIter[1];   // local_13d0
            void* pMapHead = RdP(pc, 0x420);              // the +0x3f0 map's head
            if (RdP(pc, 0x3f0) == nullptr ||
                RdP(pc, 0x3f0) != pItProxy)
                g_fnLbrInvalid();
            if (pMapHead == pItNode) {
                // absent: build the inner map, insert the member,
                // pair {uKey, map}, insert into mgr+0x3f0
                char aX[0x40];
                LbrStackMapCtor(aX);
                uint64_t aOut[2] = { 0, 0 };
                g_fnLbrMapInsertKey(aX, aOut, &uMemberKey);
                char aIns[0x48];
                LbrPairInsert(aIns, uKey, aX, pc + 0x3f0);
                LbrStackMapDtor(aX);
            } else {
                // present: proxy → container; the end-check; the
                // value map insert (node+0x20)
                if (pItProxy == nullptr) g_fnLbrInvalid();
                void* pCont = RdP(pItProxy, 0);
                if (pItNode == RdP(pCont, 0x30)) g_fnLbrInvalid();
                uint64_t aOut[2] = { 0, 0 };
                g_fnLbrMapInsertKey((char*)pItNode + 0x20, aOut,
                                    &uMemberKey);
            }
        }

        // ---------------- (B) mgr+0x430 [member][league] ----------------
        {
            // the INLINE lower bound (isnil@+0x61, key@+0x18):
            // start at the head's parent (head[1], head @mgr+0x460)
            void* pHeadB = RdP(pc, 0x460);
            void* pCur = RdP(pHeadB, 8);           // head[1] = the root
            void* pBest = pHeadB;                  // puVar5 starts at head
            while (*(unsigned char*)((char*)pCur + 0x61) == 0) {
                if (*(uint32_t*)((char*)pCur + 0x18) < uMember)
                    pCur = RdP(pCur, 0x10);        // [2] right
                else {
                    pBest = pCur;
                    pCur = RdP(pCur, 0);           // [0] left
                }
            }
            if (RdP(pc, 0x430) == nullptr) g_fnLbrInvalid();
            void* pProxyB = RdP(pc, 0x430);
            uint64_t aIter[2];
            if ((pBest == pHeadB) ||
                (uMember < *(uint32_t*)((char*)pBest + 0x18))) {
                aIter[0] = (uint64_t)(uintptr_t)RdP(pc, 0x460); // end: the head
                aIter[1] = (uint64_t)(uintptr_t)pProxyB;
            } else {
                aIter[0] = (uint64_t)(uintptr_t)pBest;          // the found node
                aIter[1] = (uint64_t)(uintptr_t)pProxyB;
            }
            // hmm — the raw stores the iter as {proxy, node}: the
            // decompile's local_1328/local_1300 = the NODE and
            // local_1308/*(mgr+0x430) = the PROXY. Keep raw order.
            void* pItProxyB = (void*)(uintptr_t)aIter[1];
            void* pItNodeB  = (void*)(uintptr_t)aIter[0];
            if (RdP(pc, 0x430) == nullptr ||
                RdP(pc, 0x430) != pItProxyB)
                g_fnLbrInvalid();
            if (pHeadB == pItNodeB) {
                char aX[0x40];
                LbrStackMapCtor(aX);
                uint64_t aOut[2] = { 0, 0 };
                g_fnLbrMapInsertKey(aX, aOut, &uLeagueKeyOp);
                char aIns[0x48];
                LbrPairInsert(aIns, uMember, aX, pc + 0x430);
                LbrStackMapDtor(aX);
            } else {
                if (pItProxyB == nullptr) g_fnLbrInvalid();
                void* pCont = RdP(pItProxyB, 0);
                if (pItNodeB == RdP(pCont, 0x30)) g_fnLbrInvalid();
                uint64_t aOut[2] = { 0, 0 };
                g_fnLbrMapInsertKey((char*)pItNodeB + 0x20, aOut,
                                    &uLeagueKeyOp);
            }
        }

        // ---------------- (C) the per-member message ----------------
        if (*(int32_t*)(pc + 0x35c) == 2 &&
            uMyLeague == (uint64_t)uMember / 1000000) {
            char aName[16];
            memset(aName, 0, 16);
            if (!g_fnLbrGetLeagueName(pMgr, uKey, aName, 0x10))
                continue;                       // goto the loop bottom
            char abMsg[0x470];
            CtorCMsgLeagueBeRob(abMsg);
            uint64_t uTail2 = *(uint32_t*)(pc + 0x358);
            uint64_t uTail1 = 3;
            uint64_t uTailMsg = (uint64_t)uKey / 1000000;
            bool bOk = CreateLeagueBeRob(abMsg, 3,
                                         (uint32_t)(uKey / 1000000),
                                         *(uint32_t*)(pc + 0x358), aName);
            if (bOk) {
                uTail1 = uKey;
                uint64_t uApp = AppendDwordLeagueBeRob(abMsg, uKey);
                if ((char)uApp != 0) {
                    SerializeLeagueBeRob(abMsg);
                    uTail2 = 0;
                    uTailMsg = (uint64_t)(uintptr_t)abMsg;
                    uTail1 = (uint64_t)uMember % 1000000;
                    g_fnLbrSendMsg(pLogic, (uint64_t)uMember % 1000000,
                                   abMsg, 0);
                }
            }
            DtorCMsgLeagueBeRob(abMsg, uTail1, uTailMsg, uTail2);
        }

        // ---------------- (D) mgr+0x470 [league] keys union ----------------
        {
            uint64_t aIter[2] = { 0, 0 };
            g_fnLbrMapLowerBound(pc + 0x470, aIter, &uLeagueKeyOp);
            void* pItProxy = (void*)(uintptr_t)aIter[0];
            void* pItNode  = (void*)(uintptr_t)aIter[1];
            void* pHeadD = RdP(pc, 0x4a0);       // the +0x470 map's head
            if (RdP(pc, 0x470) == nullptr ||
                RdP(pc, 0x470) != pItProxy)
                g_fnLbrInvalid();
            char* pDstInner = nullptr;           // the range-copy target
            char aX[0x40];    // must outlive the whole (D) block
            if (pHeadD == pItNode) {
                LbrStackMapCtor(aX);
                pDstInner = aX;
            } else {
                pDstInner = (char*)pItNode + 0x20;
            }
            // the two source lookups (mgr+0x370, mgr+0x3b0) by
            // the MEMBER id; each FOUND node's value map has its
            // whole key range copied into pDstInner AND aResult
            for (int iSrc = 0; iSrc < 2; iSrc++) {
                size_t offMap = (iSrc == 0) ? 0x370 : 0x3b0;
                size_t offHead = (iSrc == 0) ? 0x3a0 : 0x3e0;
                uint64_t aIterS[2] = { 0, 0 };
                g_fnLbrMapLowerBound(pc + offMap, aIterS, &uMemberKey);
                void* pItProxyS = (void*)(uintptr_t)aIterS[0];
                void* pItNodeS  = (void*)(uintptr_t)aIterS[1];
                if (RdP(pc, offMap) == nullptr ||
                    RdP(pc, offMap) != pItProxyS)
                    g_fnLbrInvalid();
                if (RdP(pc, offHead) == pItNodeS)
                    continue;                     // absent: nothing to copy
                // present: proxy → container; end-check
                if (pItProxyS == nullptr) g_fnLbrInvalid();
                void* pContS = RdP(pItProxyS, 0);
                if (pItNodeS == RdP(pContS, 0x30)) g_fnLbrInvalid();
                char* pVal = (char*)pItNodeS + 0x20;   // the value map
                // the raw builds FRESH iter pairs per call (the
                // kit CONSUMES the first iterator as it walks)
                uint64_t aF1[2] = {
                    (uint64_t)(uintptr_t)RdP(pVal, 0),
                    (uint64_t)(uintptr_t)RdP(RdP(pVal, 0x30), 0) };
                uint64_t aL1[2] = {
                    (uint64_t)(uintptr_t)RdP(pVal, 0),
                    (uint64_t)(uintptr_t)RdP(pVal, 0x30) };
                g_fnLbrMapInsertKeyRange(pDstInner, aF1, aL1);
                uint64_t aF2[2] = {
                    (uint64_t)(uintptr_t)RdP(pVal, 0),
                    (uint64_t)(uintptr_t)RdP(RdP(pVal, 0x30), 0) };
                uint64_t aL2[2] = {
                    (uint64_t)(uintptr_t)RdP(pVal, 0),
                    (uint64_t)(uintptr_t)RdP(pVal, 0x30) };
                g_fnLbrMapInsertKeyRange(aResult, aF2, aL2);
            }
            if (pHeadD == pItNode) {
                // the absent case finishes with the pair/insert
                char* aX = pDstInner;
                char aIns[0x48];
                LbrPairInsert(aIns, uKeyCopy, aX, pc + 0x470);
                LbrStackMapDtor(aX);
            }
        }

        // ---------------- (E) the walks over mgr+0x370 and
        // ----------------      mgr+0x3b0's value maps
        for (int iWalk = 0; iWalk < 2; iWalk++) {
            size_t offMap  = (iWalk == 0) ? 0x370 : 0x3b0;
            size_t offHead = (iWalk == 0) ? 0x3a0 : 0x3e0;
            uint64_t aIterW[2] = { 0, 0 };
            g_fnLbrMapLowerBound(pc + offMap, aIterW, &uMemberKey);
            void* pItProxyW = (void*)(uintptr_t)aIterW[0];
            void* pItNodeW  = (void*)(uintptr_t)aIterW[1];
            if (RdP(pc, offMap) == nullptr ||
                RdP(pc, offMap) != pItProxyW)
                g_fnLbrInvalid();
            if (RdP(pc, offHead) == pItNodeW)
                continue;                          // absent member entry
            if (pItProxyW == nullptr) g_fnLbrInvalid();
            void* pContW = RdP(pItProxyW, 0);
            if (pItNodeW == RdP(pContW, 0x30)) g_fnLbrInvalid();
            char* pVal = (char*)pItNodeW + 0x20;
            void* pValHead = RdP(pVal, 0x30);      // *(node+0x50)
            // the walk iter: {proxy = val proxy, node = head->left}
            uint64_t aWalk[2] = {
                (uint64_t)(uintptr_t)RdP(pVal, 0),
                (uint64_t)(uintptr_t)RdP(pValHead, 0) };
            for (;;) {
                uint64_t uNode = aWalk[1];
                if (RdP(pVal, 0) == nullptr ||
                    RdP(pVal, 0) != (void*)(uintptr_t)aWalk[0])
                    g_fnLbrInvalid();
                if (pValHead == (void*)(uintptr_t)uNode)
                    break;                          // end
                if ((void*)(uintptr_t)aWalk[0] == nullptr)
                    g_fnLbrInvalid();
                uint64_t uWrapping = *(uint64_t*)(void*)(uintptr_t)aWalk[0];
                if ((void*)(uintptr_t)uNode ==
                    RdP((void*)(uintptr_t)uWrapping, 0x30))
                    g_fnLbrInvalid();
                uint32_t uWalkKey = *(uint32_t*)((char*)(uintptr_t)uNode
                                                + 0x18);
                uint32_t uWalkKeyOp = uWalkKey;
                if (uWalkKey != 0) {
                    // lower bound mgr+0x470 by the walked key
                    uint64_t aIterK[2] = { 0, 0 };
                    g_fnLbrMapLowerBound(pc + 0x470, aIterK,
                                         &uWalkKeyOp);
                    void* pItProxyK = (void*)(uintptr_t)aIterK[0];
                    void* pItNodeK  = (void*)(uintptr_t)aIterK[1];
                    void* pHeadK = RdP(pc, 0x4a0);
                    if (RdP(pc, 0x470) == nullptr ||
                        RdP(pc, 0x470) != pItProxyK)
                        g_fnLbrInvalid();
                    if (pHeadK == pItNodeK) {
                        // absent: real FUN_141731fc0 + league-key
                        // insert + pair/insert (walked key, map)
                        char aX[0x40];
                        g_fnLbrMapCtor(aX);
                        uint64_t aOutK[2] = { 0, 0 };
                        g_fnLbrMapInsertKey(aX, aOutK, &uLeagueKeyOp);
                        char aIns[0x48];
                        LbrPairInsert(aIns, uWalkKey, aX, pc + 0x470);
                        // the moved-from X teardown (the REAL ctor
                        // version): tree dtor + proxy delete
                        g_fnLbrMapTreeDtor(aX);
                        g_fnLbrOpDelete(RdP(aX, 0));
                    } else {
                        if (pItProxyK == nullptr) g_fnLbrInvalid();
                        void* pContK = RdP(pItProxyK, 0);
                        if (pItNodeK == RdP(pContK, 0x30))
                            g_fnLbrInvalid();
                        uint64_t aOutK[2] = { 0, 0 };
                        g_fnLbrMapInsertKey((char*)pItNodeK + 0x20,
                                            aOutK, &uLeagueKeyOp);
                    }
                    // the per-entry message (the SECOND/THIRD CMsg)
                    if (*(int32_t*)(pc + 0x35c) == 2 &&
                        uMyLeague == (uint64_t)uWalkKey / 1000000) {
                        char abMsgE[0x470];
                        CtorCMsgLeagueBeRob(abMsgE);
                        uint64_t uTail2 = *(uint32_t*)(pc + 0x358);
                        uint64_t uTail1 = 4;
                        uint64_t uTailMsg = 0;
                        bool bOk = CreateLeagueBeRob(abMsgE, 4, 0,
                                *(uint32_t*)(pc + 0x358), "");
                        if (bOk) {
                            uTail1 = uKeyCopy;
                            uint64_t uApp = AppendDwordLeagueBeRob(
                                abMsgE, uKeyCopy);
                            if ((char)uApp != 0) {
                                SerializeLeagueBeRob(abMsgE);
                                uTail2 = 0;
                                uTailMsg = (uint64_t)(uintptr_t)abMsgE;
                                uTail1 = (uint64_t)uWalkKey % 1000000;
                                g_fnLbrSendMsg(pLogic,
                                    (uint64_t)uWalkKey % 1000000,
                                    abMsgE, 0);
                            }
                        }
                        DtorCMsgLeagueBeRob(abMsgE, uTail1, uTailMsg,
                                            uTail2);
                    }
                }
                g_fnLbrIterAdvance(aWalk);
            }
        }
        (void)pIdsSaved; (void)pResultProxy;
    }

    // ---------------- the AGGREGATE block ----------------
    if (*(int32_t*)(pc + 0x35c) == 2 &&
        uMyLeague == (uint64_t)uKey / 1000000) {
        uint32_t uAnchor = pIds[0];               // *param_4
        if (uAnchor == 0) {
            LbrStackMapDtor(aResult);
            return;
        }
        char aName[16];
        memset(aName, 0, 16);
        if (!g_fnLbrGetNameById(pMgr, uAnchor, aName, 0x10)) {
            LbrStackMapDtor(aResult);
            return;
        }
        // the verbatim byte walk (lVar19 from -1; exits on the
        // NUL byte; == -2 ⟺ the FIRST byte was NUL)
        int64_t nScan = -1;
        char* pScan = aName;
        for (;;) {
            if (nScan == 0) break;
            nScan--;
            char c = *pScan;
            pScan++;
            if (c == 0) break;
        }
        if (nScan == -2 &&
            !g_fnLbrGetLeagueName(pMgr, uAnchor, aName, 0x10)) {
            LbrStackMapDtor(aResult);
            return;
        }
        // the type-2 message over ALL the ids (the 10-cap again)
        {
            char abMsg2[0x470];
            CtorCMsgLeagueBeRob(abMsg2);
            bool bOk = CreateLeagueBeRob(abMsg2, 2,
                    (uint32_t)((uint64_t)uAnchor / 1000000),
                    *(uint32_t*)(pc + 0x358), aName);
            if (bOk) {
                uint32_t uGate = 0;
                int64_t j = 0;
                if (nCount > 0) {
                    do {
                        if (9 < uGate) break;
                        uint32_t uId = pIds[j];
                        if (uId != 0) {
                            uint64_t uApp = AppendDwordLeagueBeRob(
                                abMsg2, uId);
                            if ((char)uApp == 0) {
                                SerializeLeagueBeRob(abMsg2);
                                g_fnLbrSendMsg(pLogic,
                                    (uint64_t)uKey % 1000000,
                                    abMsg2, 0);
                                ClearLeagueBeRob(abMsg2);
                                CreateLeagueBeRob(abMsg2, 2,
                                    (uint32_t)((uint64_t)uAnchor / 1000000),
                                    *(uint32_t*)(pc + 0x358), aName);
                                AppendDwordLeagueBeRob(abMsg2, uId);
                            }
                        }
                        uGate++;
                        j++;
                    } while (j < (int64_t)nCount);
                }
                if (GetCountLeagueBeRob(abMsg2) != 0) {
                    SerializeLeagueBeRob(abMsg2);
                    g_fnLbrSendMsg(pLogic, (uint64_t)uKey % 1000000,
                                   abMsg2, 0);
                }
            }
            // the FOURTH CMsg: the result set's keys (type 4)
            char abMsg4[0x470];
            CtorCMsgLeagueBeRob(abMsg4);
            uint64_t uTail2 = *(uint32_t*)(pc + 0x358);
            uint64_t uTail1 = 4;
            uint64_t uTailMsg = 0;
            bool bOk4 = CreateLeagueBeRob(abMsg4, 4, 0,
                    *(uint32_t*)(pc + 0x358), "");
            if (bOk4) {
                // walk the result set: first = head->left
                uint64_t aWalk[2] = {
                    (uint64_t)(uintptr_t)pResultProxy,
                    (uint64_t)(uintptr_t)RdP(pResultHead, 0) };
                for (;;) {
                    uint64_t uNode = aWalk[1];
                    if (RdP(aResult, 0) == nullptr ||
                        RdP(aResult, 0) != (void*)(uintptr_t)aWalk[0])
                        g_fnLbrInvalid();
                    if (pResultHead == (void*)(uintptr_t)uNode)
                        break;
                    if ((void*)(uintptr_t)aWalk[0] == nullptr)
                        g_fnLbrInvalid();
                    uint64_t uWrapping =
                        *(uint64_t*)(void*)(uintptr_t)aWalk[0];
                    if ((void*)(uintptr_t)uNode ==
                        RdP((void*)(uintptr_t)uWrapping, 0x30))
                        g_fnLbrInvalid();
                    uint32_t uRK = *(uint32_t*)((char*)(uintptr_t)uNode
                                               + 0x18);
                    if (uRK != 0) {
                        uTail1 = uRK;
                        uint64_t uApp = AppendDwordLeagueBeRob(
                            abMsg4, uRK);
                        if ((char)uApp == 0) {
                            SerializeLeagueBeRob(abMsg4);
                            g_fnLbrSendMsg(pLogic,
                                (uint64_t)uKey % 1000000,
                                abMsg4, 0);
                            ClearLeagueBeRob(abMsg4);
                            uTail2 = *(uint32_t*)(pc + 0x358);
                            uTailMsg = 0;
                            CreateLeagueBeRob(abMsg4, 4, 0,
                                *(uint32_t*)(pc + 0x358), "");
                            uTail1 = uRK;
                            AppendDwordLeagueBeRob(abMsg4, uRK);
                        }
                    }
                    g_fnLbrIterAdvance(aWalk);
                }
                if (GetCountLeagueBeRob(abMsg4) != 0) {
                    SerializeLeagueBeRob(abMsg4);
                    uTail2 = 0;
                    uTailMsg = (uint64_t)(uintptr_t)abMsg4;
                    uTail1 = (uint64_t)uKey % 1000000;
                    g_fnLbrSendMsg(pLogic, (uint64_t)uKey % 1000000,
                                   abMsg4, 0);
                }
            }
            DtorCMsgLeagueBeRob(abMsg4, uTail1, uTailMsg, uTail2);
            DtorCMsgLeagueBeRob(abMsg2, uTail1, uTailMsg, uTail2);
        }
    }

    // ---------------- the result set teardown ----------------
    LbrStackMapDtor(aResult);
}

}  // namespace syndicate

// ============================================================================
// SyndicateLeaguePlunderClose.cpp — unit D79: RAW-verbatim
// port of FUN_141774c70. Both walks carry the SAME gate
// chain (key!=0, proxy derefs, size@+0x58!=0, leftmost
// via **(node+0x50), first-member id@+0x18, myLeague ==
// key/1e6) — verified at 0x141774dc6ff (0x43) and the
// 0x44 body: they differ ONLY in the name fetch (170 +
// the -2 fallback for 0x43, 250 direct for 0x44), the
// LeagueOpt type, and the log literal (the RAW keeps
// 'PlunderWarStart' in the 0x43 logs and
// 'SendUserPlunderWarStatus' in the 0x44 log — preserved
// verbatim, NOT normalized).
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderClose.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueAddTodayPlunder.h"
#include "Exe/Dll/Syndicate/Port/SyndicateInviteNotify.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"
#include <cstring>
#include <cstdint>

namespace syndicate {

void (*g_fnPwcTreeDestroy)(void*, void*);
void (*g_fnPwcWarUiState)(void*, int32_t, int32_t);

static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}
// the RAW -2 name-length walk (empty at the first char)
static inline bool PwcEmptyName(const char* pName) {
    int64_t n = -1;
    char c;
    do {
        if (n == 0) break;
        n--;
        c = *pName++;
    } while (c != '\0');
    return n == -2;
}
// the +0x61 in-order advance (the Mgr-tree walk,
// leftmost-of-right then the climb) — RAW-verbatim
static inline char* PwcNext61(char* pCur) {
    char* pR = *(char**)(pCur + 0x10);
    if (*(unsigned char*)(pR + 0x61) == 0) {
        char* pW = pR;
        do {
            pCur = pW;
            pW = *(char**)pCur;
        } while (*(unsigned char*)(*(char**)pCur + 0x61) == 0);
        return pCur;
    }
    char* pPrev = pCur;
    char* pPar = *(char**)(pCur + 8);
    char c2 = *(unsigned char*)(pPar + 0x61);
    for (;;) {
        pCur = pPar;
        if (!(c2 == 0 && pPrev == *(char**)(pCur + 0x10)))
            return pCur;
        c2 = *(unsigned char*)(*(char**)(pCur + 8) + 0x61);
        pPar = *(char**)(pCur + 8);
        pPrev = pCur;
    }
}

void PlunderWarClose(void* pMgr) {
    char* pc = (char*)pMgr;
    void* pLogic = RdP(pc, 8);
    alignas(8) unsigned char aMsg[0x2180];   // local_8a8[1072]

    // ---- the outer walk over mgr+0x370 (the 0x43 body)
    void* pPrA = RdP(pc, 0x370);
    char* pCur = *(char**)((char*)RdP(pc, 0x3a0));  // **(0x3a0)
    for (;;) {
        char* pHdA = (char*)RdP(pc, 0x3a0);
        if (RdP(pc, 0x370) == nullptr ||
            RdP(pc, 0x370) != pPrA)
            g_fnLbrInvalid();
        if (pHdA == pCur) {
            // ---- the 0x3b0 phase (the 0x44 body)
            void* pPrB = RdP(pc, 0x3b0);
            char* pCurB = *(char**)((char*)RdP(pc, 0x3e0));
            for (;;) {
                char* pHdB = (char*)RdP(pc, 0x3e0);
                if (RdP(pc, 0x3b0) == nullptr ||
                    RdP(pc, 0x3b0) != pPrB)
                    g_fnLbrInvalid();
                if (pHdB == pCurB) break;   // -> the teardown
                if (pPrB == nullptr) g_fnLbrInvalid();
                else { void* pC = *(void**)pPrB;
                       if (pCurB == RdP(pC, 0x30)) g_fnLbrInvalid(); }
                uint32_t uKeyB = *(uint32_t*)(pCurB + 0x18);
                if (uKeyB != 0) {
                    if (pPrB == nullptr) g_fnLbrInvalid();
                    else { void* pC = *(void**)pPrB;
                           if (pCurB == RdP(pC, 0x30)) g_fnLbrInvalid(); }
                    if (*(int64_t*)(pCurB + 0x58) != 0) {
                        char* pLeftB =
                            *(char**)*(char**)(pCurB + 0x50);
                        void* pWrapB = *(void**)(pCurB + 0x20);
                        void* pCellB = *(void**)pWrapB;
                        if (pLeftB == RdP(pCellB, 0x30))
                            g_fnLbrInvalid();
                        uint32_t uFirstB =
                            *(uint32_t*)(pLeftB + 0x18);
                        if (uFirstB != 0 &&
                            (uint32_t)g_fnLbrGetMyLeague(pLogic)
                                == uKeyB / 1000000) {
                            char aName[16]; memset(aName, 0, 16);
                            if (g_fnLbrGetLeagueName(pMgr, uFirstB,
                                                     aName, 16) == 0) {
                                g_fnPwsLogErr(
                                    "CLeagueMgr::SendUserPlunderWarStatus cannot find the plundered league[%lu]",
                                    (uint64_t)uFirstB);
                                return;   // RAW: aborts ALL
                            }
                            CtorCMsgLeagueOpt(aMsg);
                            if (g_fn1417d6820(aMsg, 0x44, aName,
                                              0, uFirstB / 1000000,
                                              0) != 0) {
                                g_fnAtpSendOptText(pLogic,
                                    uKeyB % 1000000, aMsg,
                                    nullptr, 0);
                            }
                            g_fn1417d66c0(aMsg);
                        }
                    }
                }
                if (pPrB == nullptr) g_fnLbrInvalid();
                pCurB = PwcNext61(pCurB);
            }
            // ---- the teardown: the war ends (mgr+0x35c = 3)
            *(int32_t*)(pc + 0x35c) = 3;
            const size_t aOffs[5][3] = {
                { 0x370, 0x3a0, 0x3a8 },
                { 0x3b0, 0x3e0, 0x3e8 },
                { 0x3f0, 0x420, 0x428 },
                { 0x430, 0x460, 0x468 },
                { 0x470, 0x4a0, 0x4a8 },
            };
            for (int i = 0; i < 5; i++) {
                size_t oM = aOffs[i][0], oH = aOffs[i][1],
                       oS = aOffs[i][2];
                char* pHead = (char*)RdP(pc, oH);
                g_fnPwcTreeDestroy(pc + oM,
                    *(void**)(pHead + 8));      // the root
                *(void**)(pHead + 8) = pHead;   // root = head
                *(uint64_t*)(pc + oS) = 0;      // size = 0
                *(void**)pHead = pHead;         // leftmost
                *(void**)(pHead + 0x10) = pHead; // rightmost
            }
            g_fnPwcWarUiState(pLogic, 3, 0);    // vt+0x528(3)
            g_fnPwcWarUiState(pLogic, 10, 1);   // vt+0x528(10,1)
            // the closing 0x46 broadcast
            CtorCMsgLeagueOpt(aMsg);
            if (CreateMsgLeagueOptText(aMsg, 0x46) != 0) {
                g_fnPwsBroadcast45(pLogic, aMsg);  // vt+0x98
            }
            g_fn1417d66c0(aMsg);
            return;
        }
        // the per-node 0x43 body
        uint32_t uKey = *(uint32_t*)(pCur + 0x18);
        if (uKey != 0) {
            if (pPrA == nullptr) g_fnLbrInvalid();
            else { void* pC = *(void**)pPrA;
                   if (pCur == RdP(pC, 0x30)) g_fnLbrInvalid(); }
            if (*(int64_t*)(pCur + 0x58) != 0) {
                char* pLeft = *(char**)*(char**)(pCur + 0x50);
                void* pWrap = *(void**)(pCur + 0x20);
                void* pCell = *(void**)pWrap;
                if (pLeft == RdP(pCell, 0x30)) g_fnLbrInvalid();
                uint32_t uFirst = *(uint32_t*)(pLeft + 0x18);
                if (uFirst != 0 &&
                    (uint32_t)g_fnLbrGetMyLeague(pLogic)
                        == uKey / 1000000) {
                    char aName[16]; memset(aName, 0, 16);
                    if (g_fnLbrGetNameById(pMgr, uFirst, aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::PlunderWarStart cannot find the plundered league[%lu]",
                            (uint64_t)uFirst);
                        return;
                    }
                    if (PwcEmptyName(aName) &&
                        g_fnLbrGetLeagueName(pMgr, uFirst,
                                             aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::PlunderWarStart cannot find the plundered league[%lu]",
                            (uint64_t)uFirst);
                        return;
                    }
                    CtorCMsgLeagueOpt(aMsg);
                    if (g_fn1417d6820(aMsg, 0x43, aName, 0,
                                      uFirst / 1000000, 0) != 0) {
                        g_fnAtpSendOptText(pLogic,
                            uKey % 1000000, aMsg, nullptr, 0);
                    }
                    g_fn1417d66c0(aMsg);
                }
            }
        }
        if (pPrA == nullptr) g_fnLbrInvalid();
        pCur = PwcNext61(pCur);
    }
}

}   // namespace syndicate

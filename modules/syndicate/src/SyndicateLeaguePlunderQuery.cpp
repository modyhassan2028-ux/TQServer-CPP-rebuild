// ============================================================================
// SyndicateLeaguePlunderQuery.cpp — unit D76, verbatim
// port of FUN_141766e90 (v6159 Syndicate.dll).
// ============================================================================
#include "modules/syndicate/src/SyndicateLeaguePlunderQuery.h"
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"
#include "modules/syndicate/src/SyndicateLeagueRobOptFlow.h"
#include "modules/syndicate/src/SyndicateLeagueAddTodayPlunder.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderList.h"
#include <cstring>

namespace syndicate {

uint32_t (*g_fnCqpMemberKey)(void*, uint32_t, int32_t);
uint16_t (*g_fnCqpMsgCount)(void*);
char     (*g_fnCqpMsgAppend)(void*, int32_t, const char*,
                             const char*);

static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}

int32_t ClientQueryPlunderWarInfo(void* pMgr, uint32_t uUser,
                                  int32_t nType, int32_t nPage,
                                  int32_t nPageSize) {
    char* pc = (char*)pMgr;
    if (uUser == 0 || nPage < 1 || nPageSize < 1) return 0;
    void* pLogic = RdP(pc, 8);
    uint32_t uLeague = g_fnSplUserLeague(pLogic);
    if (uLeague == 0) return 0;
    uint32_t uKey = g_fnCqpMemberKey(pLogic, uUser,
                                     (int32_t)uLeague);
    if (uKey == 0) return 0;

    alignas(8) unsigned char aMsg[0x2300];  // local_4d8[1120]

    if (nType != 2) {
        // ============ the PLUNDERED branch (mgr+0x3b0) ============
        uint64_t aIt[2] = { 0, 0 };
        g_fnLbrMapLowerBound(pc + 0x3b0, aIt, &uKey);
        char* pHead = (char*)RdP(pc, 0x3e0);
        void* pProxy = RdP(pc, 0x3b0);
        if (pProxy == nullptr ||
            pProxy != (void*)(uintptr_t)aIt[0])
            g_fnLbrInvalid();
        char* pNode = (char*)(uintptr_t)aIt[1];
        if (pHead == pNode) return 0;              // absent
        if ((void*)(uintptr_t)aIt[0] == nullptr) {
            g_fnLbrInvalid();
        } else {
            void* pCont = *(void**)(uintptr_t)aIt[0];
            if (pNode == RdP(pCont, 0x30))
                g_fnLbrInvalid();
        }
        int32_t nTotal = (int32_t)*(int64_t*)(pNode + 0x58);
        if (nTotal < 1) return 0;
        int32_t nSkip = (nPage - 1) * nPageSize;
        if (nSkip < 0 || nTotal <= nSkip) return 0;

        g_fnAtpMsgCtor(aMsg);
        uint32_t uAddr = (uint32_t)nPage +
                         (uint32_t)nTotal * 1000;
        if (g_fnAtpMsgCreate(aMsg, nType, uAddr) == 0) {
            g_fnAtpMsgDtor(aMsg);
            return 0;
        }
        void* pMy = *(void**)(pNode + 0x20);
        char* pCur =
            *(char**)*(char**)(pNode + 0x50);  // leftmost
        uint64_t uIdx = 0;
        bool bOver = false;
        for (;;) {
            char* pHd = *(char**)(pNode + 0x50);
            void* pPr = *(void**)(pNode + 0x20);
            if (pPr == nullptr || pPr != pMy)
                g_fnLbrInvalid();
            if (pHd == pCur) break;                    // end
            if (nPageSize <= (int32_t)g_fnCqpMsgCount(aMsg))
                break;                                 // full
            if (nSkip <= (int32_t)uIdx) {
                if (pMy == nullptr) {
                    g_fnLbrInvalid();
                } else {
                    void* pC = *(void**)pMy;
                    if (pCur == RdP(pC, 0x30))
                        g_fnLbrInvalid();
                }
                uint32_t uId = *(uint32_t*)(pCur + 0x18);
                if (uId != 0) {
                    char aName1[16];
                    memset(aName1, 0, sizeof(aName1));
                    g_fnLbrGetLeagueName(pMgr, uId, aName1,
                                         16);       // 141766250
                    if (g_fnCqpMsgAppend(
                            aMsg, (int32_t)(uId / 1000000),
                            aName1, nullptr) == 0) {
                        bOver = true;
                        break;
                    }
                }
            }
            // the RAW kit advance (isnil@+0x1d)
            if (pMy == nullptr) g_fnLbrInvalid();
            if (*(unsigned char*)(pCur + 0x1d) == 0) {
                char* pR = *(char**)(pCur + 0x10);
                if (*(unsigned char*)(pR + 0x1d) == 0) {
                    char* pW = pR;
                    do {
                        pCur = pW;
                        pW = *(char**)pCur;
                    } while (*(unsigned char*)(
                                 *(char**)pCur + 0x1d) == 0);
                } else {
                    char* pPrev = pCur;
                    for (;;) {
                        char* pPar = *(char**)(pPrev + 8);
                        pCur = pPar;
                        if (*(unsigned char*)(pPar + 0x1d)
                                != 0)
                            break;          // the head
                        bool bR = pPrev ==
                            *(char**)(pPar + 0x10);
                        pPrev = pPar;
                        if (!bR) break;
                    }
                }
            } else {
                g_fnLbrInvalid();
            }
            uIdx++;
        }
        if (bOver)
            g_fnPwsLogErr("CLeagueMgr::ClientQueryPlunderWar"
                          "Info msg over size", 0);
        if (g_fnCqpMsgCount(aMsg) != 0) {
            g_fnAtpMsgSerialize(aMsg);
            g_fnSplSendMsg(pLogic, uUser, aMsg);
        }
        g_fnAtpMsgDtor(aMsg);
        return 1;
    }

    // ============ the PLUNDERING branch (mgr+0x370) ============
    uint64_t aIt[2] = { 0, 0 };
    g_fnLbrMapLowerBound(pc + 0x370, aIt, &uKey);
    char* pHead = (char*)RdP(pc, 0x3a0);
    void* pProxy = RdP(pc, 0x370);
    if (pProxy == nullptr ||
        pProxy != (void*)(uintptr_t)aIt[0])
        g_fnLbrInvalid();
    char* pNode = (char*)(uintptr_t)aIt[1];
    if (pHead == pNode) return 0;                  // absent
    if ((void*)(uintptr_t)aIt[0] == nullptr) {
        g_fnLbrInvalid();
    } else {
        void* pCont = *(void**)(uintptr_t)aIt[0];
        if (pNode == RdP(pCont, 0x30))
            g_fnLbrInvalid();
    }
    int32_t nTotal = (int32_t)*(int64_t*)(pNode + 0x58);
    if (nTotal < 1) return 0;
    int32_t nSkip = (nPage - 1) * nPageSize;
    if (nSkip < 0 || nTotal <= nSkip) return 0;

    g_fnAtpMsgCtor(aMsg);
    uint32_t uAddr = (uint32_t)nPage + (uint32_t)nTotal * 1000;
    if (g_fnAtpMsgCreate(aMsg, 2, uAddr) == 0) {
        g_fnAtpMsgDtor(aMsg);
        return 0;
    }
    void* pMy = *(void**)(pNode + 0x20);
    char* pCur = *(char**)*(char**)(pNode + 0x50);   // leftmost
    uint64_t uIdx = 0;
    bool bOver = false;
    for (;;) {
        char* pHd = *(char**)(pNode + 0x50);
        void* pPr = *(void**)(pNode + 0x20);
        if (pPr == nullptr || pPr != pMy)
            g_fnLbrInvalid();
        if (pHd == pCur) break;
        if (nPageSize <= (int32_t)g_fnCqpMsgCount(aMsg))
            break;
        if (nSkip <= (int32_t)uIdx) {
            if (pMy == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pC = *(void**)pMy;
                if (pCur == RdP(pC, 0x30))
                    g_fnLbrInvalid();
            }
            uint32_t uId = *(uint32_t*)(pCur + 0x18);
            if (uId != 0) {
                char aName1[16];
                char aName2[16];
                memset(aName1, 0, sizeof(aName1));
                memset(aName2, 0, sizeof(aName2));
                g_fnLbrGetLeagueName(pMgr, uId, aName1,
                                     16);          // 141766250
                g_fnLbrGetNameById(pMgr, uId, aName2,
                                   16);            // 141766170
                if (g_fnCqpMsgAppend(
                        aMsg, (int32_t)(uId / 1000000),
                        aName1, aName2) == 0) {
                    bOver = true;
                    break;
                }
            }
        }
        if (pMy == nullptr) g_fnLbrInvalid();
        if (*(unsigned char*)(pCur + 0x1d) == 0) {
            char* pR = *(char**)(pCur + 0x10);
            if (*(unsigned char*)(pR + 0x1d) == 0) {
                char* pW = pR;
                do {
                    pCur = pW;
                    pW = *(char**)pCur;
                } while (*(unsigned char*)(
                             *(char**)pCur + 0x1d) == 0);
            } else {
                char* pPrev = pCur;
                for (;;) {
                    char* pPar = *(char**)(pPrev + 8);
                    pCur = pPar;
                    if (*(unsigned char*)(pPar + 0x1d) != 0)
                        break;
                    bool bR = pPrev == *(char**)(pPar + 0x10);
                    pPrev = pPar;
                    if (!bR) break;
                }
            }
        } else {
            g_fnLbrInvalid();
        }
        uIdx++;
    }
    if (bOver)
        g_fnPwsLogErr("CLeagueMgr::ClientQueryPlunderWar"
                      "Info msg over size", 0);
    if (g_fnCqpMsgCount(aMsg) != 0) {
        g_fnAtpMsgSerialize(aMsg);
        g_fnSplSendMsg(pLogic, uUser, aMsg);
    }
    g_fnAtpMsgDtor(aMsg);
    return 1;
}

}  // namespace syndicate

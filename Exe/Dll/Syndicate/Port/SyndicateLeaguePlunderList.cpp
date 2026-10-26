// ============================================================================
// SyndicateLeaguePlunderList.cpp — unit D75, verbatim
// port of FUN_141766500 (v6159 Syndicate.dll).
// ============================================================================
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderList.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include <cstring>

namespace syndicate {

char     (*g_fnSplWarState)(void*);
uint32_t (*g_fnSplUserLeague)(void*);
void     (*g_fnSplSendMsg)(void*, uint32_t, void*);
void     (*g_fnSplMsgCtor)(void*);
char     (*g_fnSplMsgCreate)(void*, int);
char     (*g_fnSplMsgAppend)(void*, uint32_t, const char*);
void     (*g_fnSplMsgFlush)(void*);
void     (*g_fnSplMsgClear)(void*);
int16_t  (*g_fnSplMsgCount)(void*);
void     (*g_fnSplMsgDtor)(void*);
void*    (*g_fnSplFindLeague)(void*, uint32_t);
void*    (*g_fnSplName48)(void*);
void*    (*g_fnSplName28)(void*);
void*    (*g_fnSplLookup)(void*, void*, uint32_t*);

static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}

// the RAW name-length walk: count down from -1 until the
// terminator; -2 means the FIRST char was 0 (empty name)
static inline bool SplEmptyName(const char* pName) {
    int64_t n = -1;
    char c;
    do {
        if (n == 0) break;
        n--;
        c = *pName++;
    } while (c != '\0');
    return n == -2;
}

void SendPlunderWarListToClient(void* pMgr, uint32_t uUser) {
    char* pc = (char*)pMgr;
    if (uUser == 0) return;
    void* pLogic = RdP(pc, 8);

    if (g_fnSplWarState(pLogic) != 0) return;   // vt+0x278
    uint32_t uUserLeague = g_fnSplUserLeague(pLogic);
    if (uUserLeague == 0) return;               // vt+0x4a8

    alignas(8) unsigned char aMsg[0x2300];      // local_4a8[1120]
    g_fnSplMsgCtor(aMsg);
    if (g_fnSplMsgCreate(aMsg, 0) != 0) {
        // the first entry
        uint32_t uFirst = *(uint32_t*)(pc + 0x18);
        if (uFirst != 0 && uFirst != uUserLeague) {
            void* pLeague = g_fnSplFindLeague(pMgr, uFirst);
            if (pLeague != nullptr) {
                const char* pName =
                    (const char*)g_fnSplName48(pLeague);
                if (SplEmptyName(pName))
                    pName = (const char*)g_fnSplName28(pLeague);
                uint32_t uMy =
                    (uint32_t)g_fnLbrGetMyLeague(pLogic);
                if (g_fnSplMsgAppend(aMsg, uMy, pName) == 0)
                    g_fnPwsLogErr(
                        "CLeagueMgr::SendPlunderWarListToClient"
                        " msg Append Error!", (uint64_t)uMy);
            }
        }
        // the main loop over mgr+0x148/0x178
        void* pProxyL = RdP(pc, 0x148);
        char* pHeadL = (char*)RdP(pc, 0x178);
        char* pCur = (char*)RdP(pHeadL, 0);     // leftmost
        while (true) {
            char* pHeadChk = (char*)RdP(pc, 0x178);
            if (RdP(pc, 0x148) == nullptr ||
                RdP(pc, 0x148) != pProxyL)
                g_fnLbrInvalid();
            if (pCur == pHeadChk) break;        // end
            // the iterator deref checks
            if (pProxyL == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pCont = *(void**)pProxyL;
                if (pCur == RdP(pCont, 0x30))
                    g_fnLbrInvalid();
            }
            uint32_t uId = *(uint32_t*)(pCur + 0x18);
            int32_t nKey = *(int32_t*)(pCur + 0x1c);
            if (uId != 0 && nKey != 0) {
                uint64_t aIter2[2] = { 0, 0 };
                uint32_t uKey2 = (uint32_t)nKey;
                g_fnSplLookup(pc + 0x108, aIter2, &uKey2);
                char* pHead2 = (char*)RdP(pc, 0x138);
                if (RdP(pc, 0x108) == nullptr ||
                    RdP(pc, 0x108) !=
                        (void*)(uintptr_t)aIter2[0])
                    g_fnLbrInvalid();
                char* pVal = (char*)(uintptr_t)aIter2[1];
                if (pHead2 != pVal) {          // found
                    if ((void*)(uintptr_t)aIter2[0] == nullptr) {
                        g_fnLbrInvalid();
                    } else {
                        void* pC2 =
                            *(void**)(uintptr_t)aIter2[0];
                        if (pVal == RdP(pC2, 0x30))
                            g_fnLbrInvalid();
                    }
                    const char* pName =
                        (const char*)(pVal + 0x48);
                    if (SplEmptyName(pName)) {
                        if (g_fnSplMsgAppend(
                                aMsg, uId,
                                (const char*)(pVal + 0x28))
                            == 0) {
                            g_fnSplMsgFlush(aMsg);
                            g_fnSplSendMsg(pLogic, uUser, aMsg);
                            g_fnSplMsgClear(aMsg);
                            if ((void*)(uintptr_t)aIter2[0]
                                    == nullptr) {
                                g_fnLbrInvalid();
                            } else {
                                void* pC3 = *(void**)(uintptr_t)
                                    aIter2[0];
                                if (pVal == RdP(pC3, 0x30))
                                    g_fnLbrInvalid();
                            }
                            g_fnSplMsgAppend(
                                aMsg, uId,
                                (const char*)(pVal + 0x28));
                        }
                    } else {
                        if (g_fnSplMsgAppend(
                                aMsg, uId, pName) == 0) {
                            g_fnSplMsgFlush(aMsg);
                            g_fnSplSendMsg(pLogic, uUser, aMsg);
                            g_fnSplMsgClear(aMsg);
                            if ((void*)(uintptr_t)aIter2[0]
                                    == nullptr) {
                                g_fnLbrInvalid();
                            } else {
                                void* pC3 = *(void**)(uintptr_t)
                                    aIter2[0];
                                if (pVal == RdP(pC3, 0x30))
                                    g_fnLbrInvalid();
                            }
                            g_fnSplMsgAppend(aMsg, uId,
                                             pName);
                        }
                    }
                }
            }
            // the RAW in-order advance (isnil@+0x21)
            if (*(unsigned char*)(pCur + 0x21) == 0) {
                char* pR = *(char**)(pCur + 0x10);
                if (*(unsigned char*)(pR + 0x21) == 0) {
                    // leftmost of the right subtree
                    char* pWalk = pR;
                    char c = *(unsigned char*)(*(char**)pWalk
                                              + 0x21);
                    pCur = pWalk;
                    pWalk = *(char**)pWalk;
                    while (c == 0) {
                        c = *(unsigned char*)(*(char**)pWalk
                                              + 0x21);
                        pCur = pWalk;
                        pWalk = *(char**)pWalk;
                    }
                } else {
                    // climb while we are the parent's right
                    char* pPrev = pCur;
                    char* pPar = *(char**)(pCur + 8);
                    char c = *(unsigned char*)(pPar + 0x21);
                    for (;;) {
                        pCur = pPar;
                        if (!(c == 0 &&
                              pPrev ==
                                  *(char**)(pCur + 0x10)))
                            break;
                        c = *(unsigned char*)(*(char**)(pCur + 8)
                                              + 0x21);
                        pPar = *(char**)(pCur + 8);
                        pPrev = pCur;
                    }
                }
            } else {
                g_fnLbrInvalid();   // advance past the head
            }
        }
        int16_t nCount = g_fnSplMsgCount(aMsg);
        if (nCount != 0) {
            g_fnSplMsgFlush(aMsg);
            g_fnSplSendMsg(pLogic, uUser, aMsg);
        }
    }
    g_fnSplMsgDtor(aMsg);
}

}  // namespace syndicate

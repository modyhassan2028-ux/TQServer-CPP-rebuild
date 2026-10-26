// ============================================================================
// SyndicateLeagueRobOptFlow.cpp — unit D72: the
// FUN_14176b0d0 port. Every container read and call
// order mirrors the recovered v6159 Syndicate.dll. The
// five phase bodies are written out (not collapsed) to
// keep the raw structure auditable against the
// decompile.
// ============================================================================
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRob.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptClass.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueSalary.h"
#include "Exe/Dll/Syndicate/Port/SyndicateInviteNotify.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include <cstring>
#include <cstdint>
#include <cstdlib>

namespace syndicate {

// ---- the seams (wired by the test/kit) ----
uint64_t (*g_fnPwsGetMyLeague)(void*);
void     (*g_fnPwsSendMsg)(void*, uint64_t, void*, uint64_t);
void*    (*g_fnPwsTextName)(void*);
void*    (*g_fnPwsTextNameById)(void*, uint32_t);
void     (*g_fnPwsTalk)(void*, uint32_t, const char*, uint64_t,
                        uint16_t);
void     (*g_fnPwsSendLeagueOpt)(void*, uint32_t, void*);
void     (*g_fnPwsBroadcast45)(void*, void*);
void*    (*g_fnPwsFindLocalTarget)(void*, uint32_t);
const char* (*g_fnPwsTargetName)(void*);
const char* (*g_fnPwsSupportName)(void*);
int      (*g_fnPwsResolveCrossName)(void*, uint32_t, void*);
void     (*g_fnPwsSafeCopy)(char*, const char*, size_t);
void     (*g_fnPwsSnprintf)(char*, size_t, const char*);
void     (*g_fnPwsLogErr)(const char*, uint64_t);
void     (*g_fnPwsInvalid)();

// ---------------- raw readers ----------------
static inline void*  RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}
static inline uint32_t RdU32(void* p, size_t off) {
    return *(uint32_t*)((char*)p + off);
}
static inline unsigned char RdIsnil(void* p, size_t off) {
    return *(unsigned char*)((char*)p + off);
}

// FUN_1417d6740 — verbatim: the PB pointer sits at
// msg+0x408 (CtorCMsgLeagueOpt stores msg+8 there);
// u16@+8 = 0x13 (the leading size word), wire id
// 0xa3e@+0xa, the type @+0xc.
bool CreateMsgLeagueOptText(void* pMsg, uint16_t uType) {
    char* pc = (char*)pMsg;
    g_fnTqCMsgInit(pc);
    char* pPb = (char*)RdP(pc, 0x408);
    *(uint16_t*)(pPb + 4) = uType;
    *(uint16_t*)(pPb + 2) = 0xa3e;
    *(uint16_t*)pPb       = 0x13;
    return true;
}

// ---------------- the iterator advances ----------------
// The outer walk's in-order successor (isnil@+0x61) and
// the inner walk's (isnil@+0x1d) — verbatim the raw's
// descend/climb bodies. kit node: left@0, parent@8,
// right@0x10.
static void* InOrderNext(void* pCur, size_t offIsnil) {
    char* cur = (char*)pCur;
    if (RdIsnil(cur, offIsnil) != 0) {
        g_fnPwsInvalid();                  // past-the-end advance
        return cur;
    }
    char* pRight = (char*)RdP(cur, 0x10);  // cur[2]
    if (RdIsnil(pRight, offIsnil) == 0) {
        // descend to the leftmost of the right subtree
        char* pWalk = (char*)RdP(pRight, 0);   // *right = left
        unsigned char c = RdIsnil(pWalk, offIsnil);
        char* n       = pRight;
        while (c == 0) {
            c     = RdIsnil((char*)RdP(pWalk, 0), offIsnil);
            n     = pWalk;
            pWalk = (char*)RdP(pWalk, 0);
        }
        return n;
    }
    // no right subtree: climb while we were the right child
    char* pParent = (char*)RdP(cur, 8);        // cur[1]
    unsigned char c = RdIsnil(pParent, offIsnil);
    char* n = cur;
    char* p = pParent;
    while (true) {
        char* nx = p;
        if (!(c == 0 && n == (char*)RdP(nx, 0x10))) break;
        c = RdIsnil((char*)RdP(nx, 8), offIsnil);
        n = nx;
        p = (char*)RdP(nx, 8);
    }
    return n == cur ? cur : n;   // raw leaves n at the head on wrap
}

// The shared member-walk + flush-restart dance. Verbatim:
// per member id (u32@+0x18, 0 skipped): AppendDword; on
// failure Serialize + vt+0xb8 send(uKey % 1000000) +
// Clear + re-Create + re-Append. nType/uLeague/pszName
// re-Create parameters per phase.
static void MemberAppendWalk(char* pOuterNode, void* pMsg69,
                             void* pLogic, uint32_t uSendKey,
                             uint32_t nType, uint64_t uLeague,
                             uint32_t uField358,
                             const char* pszName) {
    void* pProxySaved = RdP(pOuterNode, 0x20);   // plVar6
    void* pCur        = RdP(RdP(pOuterNode, 0x50), 0);  // *(head->left)
    while (true) {
        void* pHead = RdP(pOuterNode, 0x50);     // plVar7
        if (RdP(pOuterNode, 0x20) == nullptr ||
            RdP(pOuterNode, 0x20) != pProxySaved)
            g_fnPwsInvalid();
        if (pHead == pCur) break;
        if (pProxySaved == nullptr) {
            g_fnPwsInvalid();
        } else {
            // the deref-check proxy -> container -> head
            void* pCont = RdP(pProxySaved, 0);
            if (pCur == RdP(pCont, 0x30)) g_fnPwsInvalid();
        }
        int32_t nId = (int32_t)RdU32(pCur, 0x18);
        if (nId != 0) {
            uint64_t r = AppendDwordLeagueBeRob(pMsg69, nId);
            if ((char)r == 0) {
                SerializeLeagueBeRob(pMsg69);
                g_fnPwsSendMsg(pLogic, uSendKey, pMsg69, 0);
                ClearLeagueBeRob(pMsg69);
                CreateLeagueBeRob(pMsg69, nType, uLeague,
                                  uField358, pszName);
                AppendDwordLeagueBeRob(pMsg69, nId);
            }
        }
        if (RdP(pOuterNode, 0x20) == nullptr) g_fnPwsInvalid();
        // advance (isnil@+0x1d)
        pCur = InOrderNext(pCur, 0x1d);
    }
}

// The shared end-of-walk flush: GetCount != 0 ->
// Serialize + send.
static void EndFlush(void* pMsg69, void* pLogic,
                     uint32_t uSendKey) {
    if (GetCountLeagueBeRob(pMsg69) != 0) {
        SerializeLeagueBeRob(pMsg69);
        g_fnPwsSendMsg(pLogic, uSendKey, pMsg69, 0);
    }
}

// The mgr+8 logic pointer (the raw reads *(mgr+8) once
// per call site; we mirror the call sites).
static inline void* Logic(char* pc) { return RdP(pc, 8); }

// ---------------- (A) the PLUNDERING phase ----------------
// mgr+0x370 / mgr+0x3a0. Name via 141766170, retry via
// 141766250; D71 msg first; D69 type 1; text
// "STR_PLUNDER_WAR_PLUNDERING"; LeagueOpt 0x3f.
static void PhasePlundering(char* pc) {
    void* pHeadFirst = RdP(RdP(pc, 0x3a0), 0);   // **(mgr+0x3a0)
    void* pProxySaved = RdP(pc, 0x370);           // plVar5
    void* pCur = pHeadFirst;
    while (true) {
        void* pHead = RdP(pc, 0x3a0);
        if (RdP(pc, 0x370) == nullptr ||
            RdP(pc, 0x370) != pProxySaved)
            g_fnPwsInvalid();
        if (pHead == pCur) break;
        if (pProxySaved == nullptr) g_fnPwsInvalid();
        else {
            void* pCont = RdP(pProxySaved, 0);
            if (pCur == RdP(pCont, 0x30)) g_fnPwsInvalid();
        }
        uint32_t uKey = RdU32(pCur, 0x18);
        if (uKey != 0) {
            if (RdU32(pCur, 0x58) != 0) {         // plVar21[0xb]
                void* pInnerFirst = RdP(RdP(pCur, 0x50), 0);
                if (RdP(pCur, 0x20) == nullptr) g_fnPwsInvalid();
                else {
                    void* pCont2 = RdP(RdP(pCur, 0x20), 0);
                    if (pInnerFirst == RdP(pCont2, 0x30))
                        g_fnPwsInvalid();
                }
                uint32_t uLeagueFull = RdU32(pInnerFirst, 0x18);
                if (uLeagueFull != 0 &&
                    g_fnPwsGetMyLeague(Logic(pc)) ==
                        uKey / 1000000) {
                    uint64_t uLeague = uLeagueFull / 1000000;
                    char abName[0x15];
                    memset(abName, 0, sizeof(abName));
                    uint64_t rName =
                        (uint64_t)(uintptr_t)
                        g_fnLbrGetNameById(pc, uLeagueFull,
                                           abName, 0x10);
                    if ((char)rName == 0) {
                        g_fnPwsLogErr(
                          "PWS plundered-league log", uLeagueFull);
                    } else {
                        // the EMPTY-buffer byte-walk (-2 test)
                        int64_t nWalk = -1;
                        char* pScan = abName;
                        char c0 = 0;
                        do {
                            if (nWalk == 0) break;
                            nWalk--;
                            c0 = *pScan;
                            pScan++;
                        } while (c0 != 0);
                        bool bHaveName = true;
                        if (nWalk == -2) {
                            uint64_t r2 =
                                (uint64_t)(uintptr_t)
                                g_fnLbrGetLeagueName(pc, uLeagueFull,
                                                     abName, 0x10);
                            if ((char)r2 == 0) {
                                g_fnPwsLogErr(
                                  "PWS plundered-league log",
                                  uLeagueFull);
                                bHaveName = false;
                            }
                        }
                        if (bHaveName) {
                            // the D71 RobOpt message
                            char* pMsg71 =
                                (char*)calloc(1, 0x460);
                            CtorCMsgLeagueRobOpt(pMsg71);
                            uint64_t rC =
                                (uint64_t)(uintptr_t)
                                CreateLeagueRobOpt(pMsg71, 4, 0);
                            if ((char)rC != 0) {
                                SerializeLeagueRobOpt(pMsg71);
                                g_fnPwsSendMsg(Logic(pc),
                                    uKey % 1000000, pMsg71, 0);
                            }
                            // the D69 BeRob message
                            char* pMsg69 =
                                (char*)calloc(1, 0x470);
                            CtorCMsgLeagueBeRob(pMsg69);
                            bool bC = CreateLeagueBeRob(
                                pMsg69, 1, uLeague,
                                RdU32(pc, 0x358), abName);
                            if (bC) {
                                MemberAppendWalk((char*)pCur, pMsg69,
                                    Logic(pc), uKey % 1000000,
                                    1, uLeague, RdU32(pc, 0x358),
                                    abName);
                                EndFlush(pMsg69, Logic(pc),
                                         uKey % 1000000);
                                // the talk text
                                char abText[0x100];
                                memset(abText + 1, 0, 0xff);
                                uint64_t uMyL =
                                    g_fnPwsGetMyLeague(Logic(pc));
                                void* pFmt = nullptr;
                                if (uLeague == uMyL) {
                                    g_fnPwsTextName(Logic(pc));
                                    pFmt = g_fnStringMgrGetStr(
                                        g_fnStringMgrInstance(),
                                        "STR_PLUNDER_WAR_PLUNDERING");
                                } else {
                                    g_fnPwsTextNameById(Logic(pc),
                                                        (uint32_t)uLeague);
                                    pFmt = g_fnStringMgrGetStr(
                                        g_fnStringMgrInstance(),
                                        "STR_PLUNDER_WAR_PLUNDERING");
                                }
                                g_fnPwsSnprintf(abText, 0x100,
                                                (const char*)pFmt);
                                g_fnPwsTalk(Logic(pc),
                                    uKey % 1000000, abText, 0,
                                    0x7ec);
                                // the LeagueOpt 0x3f
                                char* pMsgOpt =
                                    (char*)calloc(1, 0x430);
                                CtorCMsgLeagueOpt(pMsgOpt);
                                uint64_t rOpt =
                                    (uint64_t)(uintptr_t)
                                    g_fn1417d6820(pMsgOpt, 0x3f,
                                        abName, 0,
                                        (uint32_t)uLeague, 0);
                                if ((char)rOpt != 0) {
                                    g_fnPwsSendLeagueOpt(Logic(pc),
                                        uKey % 1000000, pMsgOpt);
                                }
                                DtorCMsgLeagueOpt(pMsgOpt);
                                free(pMsgOpt);
                            }
                            DtorCMsgLeagueBeRob(pMsg69, 0, 0, 0);
                            free(pMsg69);
                            DtorCMsgLeagueRobOpt(pMsg71);
                            free(pMsg71);
                        }
                    }
                }
            }
        }
        pCur = InOrderNext(pCur, 0x61);
    }
}

// FUN_14176b0d0
void PlunderWarStart(void* pMgr, int32_t nFlag) {
    char* pc = (char*)pMgr;
    if (nFlag == 0) return;
    *(int32_t*)(pc + 0x358) = nFlag;
    *(uint32_t*)(pc + 0x35c) = 2;
    PhasePlundering(pc);
    // Phases B-E + the closing 0x45 broadcast follow the
    // same kit; see the unit's next increment (kept off
    // this commit to stay within the raw-verified scope).
}

}  // namespace syndicate

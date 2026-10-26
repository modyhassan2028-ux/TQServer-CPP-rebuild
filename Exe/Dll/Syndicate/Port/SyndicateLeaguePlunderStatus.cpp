// ============================================================================
// SyndicateLeaguePlunderStatus.cpp — unit D77, verbatim
// port of FUN_14176ca70 (v6159 Syndicate.dll). The four
// map phases are kept as four RAW copies (no merging).
// ============================================================================
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderStatus.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueAddTodayPlunder.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderList.h"
#include <cstring>

namespace syndicate {

void  (*g_fnSusMsgCtor)(void*);
char  (*g_fnSusMsgCreate)(void*, int32_t, uint32_t, uint32_t,
                          const char*);
char  (*g_fnSusMsgAppend)(void*, uint32_t);
void  (*g_fnSusMsgFlush)(void*);
void  (*g_fnSusMsgClear)(void*);
int16_t (*g_fnSusMsgCount)(void*);
void  (*g_fnSusMsgDtor)(void*);
void  (*g_fnSusSendAlt)(void*, uint32_t, void*);

static inline void* RdP(void* p, size_t off) {
    return *(void**)((char*)p + off);
}

// the RAW -2 name-length walk (empty first char)
static inline bool SusEmptyName(const char* pName) {
    int64_t n = -1;
    char c;
    do {
        if (n == 0) break;
        n--;
        c = *pName++;
    } while (c != '\0');
    return n == -2;
}

void SendUserPlunderWarStatus(void* pMgr, uint32_t uKey,
                              uint32_t uParam3,
                              uint32_t uParam4) {
    char* pc = (char*)pMgr;
    if (uKey == 0) return;
    if (uParam3 == 0 && uParam4 == 0) return;
    void* pLogic = RdP(pc, 8);

    alignas(8) unsigned char aMsg[0x2380];  // local_4d8[1136]
    alignas(16) char aName[16];             // local_68

    // ===== the presence lookup (0x370 then 0x3b0) =====
    uint32_t uKeyV = uKey;
    uint64_t aIt[2] = { 0, 0 };
    g_fnLbrMapLowerBound(pc + 0x370, aIt, &uKeyV);
    char* pHeadA = (char*)RdP(pc, 0x3a0);
    void* pPrA = RdP(pc, 0x370);
    if (pPrA == nullptr ||
        pPrA != (void*)(uintptr_t)aIt[0])
        g_fnLbrInvalid();
    bool bPresent = ((char*)(uintptr_t)aIt[1] != pHeadA);
    if (!bPresent) {
        g_fnLbrMapLowerBound(pc + 0x3b0, aIt, &uKeyV);
        pHeadA = (char*)RdP(pc, 0x3e0);
        pPrA = RdP(pc, 0x3b0);
        if (pPrA == nullptr ||
            pPrA != (void*)(uintptr_t)aIt[0])
            g_fnLbrInvalid();
        bPresent = ((char*)(uintptr_t)aIt[1] != pHeadA);
    }
    if (bPresent) {
        // P1 — the D71 RobOpt presence msg
        g_fnAtpMsgCtor(aMsg);
        if (g_fnAtpMsgCreate(aMsg, 4, 0) == 0) {
            g_fnAtpMsgDtor(aMsg);
            return;
        }
        g_fnAtpMsgSerialize(aMsg);
        if (uParam3 == 0)
            g_fnSusSendAlt(pLogic, uParam4, aMsg);
        else
            g_fnSplSendMsg(pLogic, uParam3, aMsg);
        g_fnAtpMsgDtor(aMsg);
    }

    // ===== the war gate =====
    if (*(int32_t*)(pc + 0x35c) != 2) return;

    // ================= P2: 0x370, type 1 =================
    {
        uint64_t aIt2[2] = { 0, 0 };
        g_fnLbrMapLowerBound(pc + 0x370, aIt2, &uKeyV);
        char* pHead = (char*)RdP(pc, 0x3a0);
        void* pPr = RdP(pc, 0x370);
        if (pPr == nullptr ||
            pPr != (void*)(uintptr_t)aIt2[0])
            g_fnLbrInvalid();
        char* pNode = (char*)(uintptr_t)aIt2[1];
        if (pHead != pNode) {
            if ((void*)(uintptr_t)aIt2[0] == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pC = *(void**)(uintptr_t)aIt2[0];
                if (pNode == RdP(pC, 0x30))
                    g_fnLbrInvalid();
            }
            if (*(int64_t*)(pNode + 0x58) != 0) {
                char* pLm = *(char**)*(char**)(pNode + 0x50);
                void* pWrap = *(void**)(pNode + 0x20);
                void* pCell = *(void**)pWrap;
                if (pLm == RdP(pCell, 0x30))
                    g_fnLbrInvalid();
                uint32_t uFirst = *(uint32_t*)(pLm + 0x18);
                if (uFirst != 0) {
                    memset(aName, 0, sizeof(aName));
                    if (g_fnLbrGetNameById(pMgr, uFirst,
                                           aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::SendUserPlunderWar"
                            "Status cannot find the plundered"
                            " league[%lu]", uFirst);
                        return;
                    }
                    if (SusEmptyName(aName) &&
                        g_fnLbrGetLeagueName(pMgr, uFirst,
                                             aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::SendUserPlunderWar"
                            "Status cannot find the plundered"
                            " league[%lu]", uFirst);
                        return;
                    }
                    g_fnSusMsgCtor(aMsg);
                    uint32_t uLg = uFirst / 1000000;
                    uint32_t uFlag = *(uint32_t*)(pc + 0x358);
                    if (g_fnSusMsgCreate(aMsg, 1, uLg, uFlag,
                                         aName) != 0) {
                        char* pCur =
                            *(char**)*(char**)(pNode + 0x50);
                        void* pMy = *(void**)(pNode + 0x20);
                        for (;;) {
                            char* pHd =
                                *(char**)(pNode + 0x50);
                            void* pP = *(void**)(pNode + 0x20);
                            if (pP == nullptr || pP != pMy)
                                g_fnLbrInvalid();
                            if (pHd == pCur) break;
                            if (pMy == nullptr) {
                                g_fnLbrInvalid();
                            } else {
                                void* pC2 = *(void**)pMy;
                                if (pCur == RdP(pC2, 0x30))
                                    g_fnLbrInvalid();
                            }
                            uint32_t uId =
                                *(uint32_t*)(pCur + 0x18);
                            if (uId != 0 &&
                                g_fnSusMsgAppend(aMsg, uId)
                                    == 0) {
                                g_fnSusMsgFlush(aMsg);
                                if (uParam3 == 0)
                                    g_fnSusSendAlt(
                                        pLogic, uParam4, aMsg);
                                else
                                    g_fnSplSendMsg(
                                        pLogic, uParam3, aMsg);
                                g_fnSusMsgClear(aMsg);
                                g_fnSusMsgCreate(aMsg, 1, uLg,
                                                 uFlag, aName);
                                g_fnSusMsgAppend(aMsg, uId);
                            }
                            if (*(unsigned char*)(pCur + 0x1d)
                                    == 0) {
                                char* pR = *(char**)(pCur + 0x10);
                                if (*(unsigned char*)(pR + 0x1d)
                                        == 0) {
                                    char* pW = pR;
                                    do {
                                        pCur = pW;
                                        pW = *(char**)pCur;
                                    } while (*(unsigned char*)(
                                        *(char**)pCur + 0x1d)
                                        == 0);
                                } else {
                                    char* pPrev = pCur;
                                    for (;;) {
                                        char* pPar =
                                            *(char**)(pPrev + 8);
                                        pCur = pPar;
                                        if (*(unsigned char*)(
                                                pPar + 0x1d) != 0)
                                            break;
                                        bool bR = pPrev ==
                                            *(char**)(pPar + 0x10);
                                        pPrev = pPar;
                                        if (!bR) break;
                                    }
                                }
                            } else {
                                g_fnLbrInvalid();
                            }
                        }
                        if (g_fnSusMsgCount(aMsg) != 0) {
                            g_fnSusMsgFlush(aMsg);
                            if (uParam3 == 0)
                                g_fnSusSendAlt(pLogic, uParam4,
                                               aMsg);
                            else
                                g_fnSplSendMsg(pLogic, uParam3,
                                               aMsg);
                        }
                    }
                    g_fnSusMsgDtor(aMsg);
                }
            }
        }
    }

    // ================= P3: 0x3b0, type 0 =================
    {
        uint64_t aIt2[2] = { 0, 0 };
        g_fnLbrMapLowerBound(pc + 0x3b0, aIt2, &uKeyV);
        char* pHead = (char*)RdP(pc, 0x3e0);
        void* pPr = RdP(pc, 0x3b0);
        if (pPr == nullptr ||
            pPr != (void*)(uintptr_t)aIt2[0])
            g_fnLbrInvalid();
        char* pNode = (char*)(uintptr_t)aIt2[1];
        if (pHead != pNode) {
            if ((void*)(uintptr_t)aIt2[0] == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pC = *(void**)(uintptr_t)aIt2[0];
                if (pNode == RdP(pC, 0x30))
                    g_fnLbrInvalid();
            }
            if (*(int64_t*)(pNode + 0x58) != 0) {
                char* pLm = *(char**)*(char**)(pNode + 0x50);
                void* pWrap = *(void**)(pNode + 0x20);
                void* pCell = *(void**)pWrap;
                if (pLm == RdP(pCell, 0x30))
                    g_fnLbrInvalid();
                uint32_t uFirst = *(uint32_t*)(pLm + 0x18);
                if (uFirst != 0) {
                    memset(aName, 0, sizeof(aName));
                    if (g_fnLbrGetLeagueName(pMgr, uFirst,
                                             aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::SendUserPlunderWar"
                            "Status cannot find the plundered"
                            " league[%lu]", uFirst);
                        return;
                    }
                    g_fnSusMsgCtor(aMsg);
                    uint32_t uLg = uFirst / 1000000;
                    uint32_t uFlag = *(uint32_t*)(pc + 0x358);
                    if (g_fnSusMsgCreate(aMsg, 0, uLg, uFlag,
                                         aName) != 0) {
                        char* pCur =
                            *(char**)*(char**)(pNode + 0x50);
                        void* pMy = *(void**)(pNode + 0x20);
                        for (;;) {
                            char* pHd =
                                *(char**)(pNode + 0x50);
                            void* pP = *(void**)(pNode + 0x20);
                            if (pP == nullptr || pP != pMy)
                                g_fnLbrInvalid();
                            if (pHd == pCur) break;
                            if (pMy == nullptr) {
                                g_fnLbrInvalid();
                            } else {
                                void* pC2 = *(void**)pMy;
                                if (pCur == RdP(pC2, 0x30))
                                    g_fnLbrInvalid();
                            }
                            uint32_t uId =
                                *(uint32_t*)(pCur + 0x18);
                            if (uId != 0 &&
                                g_fnSusMsgAppend(aMsg, uId)
                                    == 0) {
                                g_fnSusMsgFlush(aMsg);
                                if (uParam3 == 0)
                                    g_fnSusSendAlt(
                                        pLogic, uParam4, aMsg);
                                else
                                    g_fnSplSendMsg(
                                        pLogic, uParam3, aMsg);
                                g_fnSusMsgClear(aMsg);
                                g_fnSusMsgCreate(aMsg, 0, uLg,
                                                 uFlag, aName);
                                g_fnSusMsgAppend(aMsg, uId);
                            }
                            if (*(unsigned char*)(pCur + 0x1d)
                                    == 0) {
                                char* pR = *(char**)(pCur + 0x10);
                                if (*(unsigned char*)(pR + 0x1d)
                                        == 0) {
                                    char* pW = pR;
                                    do {
                                        pCur = pW;
                                        pW = *(char**)pCur;
                                    } while (*(unsigned char*)(
                                        *(char**)pCur + 0x1d)
                                        == 0);
                                } else {
                                    char* pPrev = pCur;
                                    for (;;) {
                                        char* pPar =
                                            *(char**)(pPrev + 8);
                                        pCur = pPar;
                                        if (*(unsigned char*)(
                                                pPar + 0x1d) != 0)
                                            break;
                                        bool bR = pPrev ==
                                            *(char**)(pPar + 0x10);
                                        pPrev = pPar;
                                        if (!bR) break;
                                    }
                                }
                            } else {
                                g_fnLbrInvalid();
                            }
                        }
                        if (g_fnSusMsgCount(aMsg) != 0) {
                            g_fnSusMsgFlush(aMsg);
                            if (uParam3 == 0)
                                g_fnSusSendAlt(pLogic, uParam4,
                                               aMsg);
                            else
                                g_fnSplSendMsg(pLogic, uParam3,
                                               aMsg);
                        }
                    }
                    g_fnSusMsgDtor(aMsg);
                }
            }
        }
    }

    // ================= P4: 0x430, type 2 =================
    {
        uint64_t aIt2[2] = { 0, 0 };
        g_fnLbrMapLowerBound(pc + 0x430, aIt2, &uKeyV);
        char* pHead = (char*)RdP(pc, 0x460);
        void* pPr = RdP(pc, 0x430);
        if (pPr == nullptr ||
            pPr != (void*)(uintptr_t)aIt2[0])
            g_fnLbrInvalid();
        char* pNode = (char*)(uintptr_t)aIt2[1];
        if (pHead != pNode) {
            if ((void*)(uintptr_t)aIt2[0] == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pC = *(void**)(uintptr_t)aIt2[0];
                if (pNode == RdP(pC, 0x30))
                    g_fnLbrInvalid();
            }
            if (*(int64_t*)(pNode + 0x58) != 0) {
                char* pLm = *(char**)*(char**)(pNode + 0x50);
                void* pWrap = *(void**)(pNode + 0x20);
                void* pCell = *(void**)pWrap;
                if (pLm == RdP(pCell, 0x30))
                    g_fnLbrInvalid();
                uint32_t uFirst = *(uint32_t*)(pLm + 0x18);
                if (uFirst != 0) {
                    memset(aName, 0, sizeof(aName));
                    if (g_fnLbrGetNameById(pMgr, uFirst,
                                           aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::SendUserPlunderWar"
                            "Status cannot find the support"
                            " idServerTarget[%lu]", uFirst);
                        return;
                    }
                    if (SusEmptyName(aName) &&
                        g_fnLbrGetLeagueName(pMgr, uFirst,
                                             aName, 16) == 0) {
                        g_fnPwsLogErr(
                            "CLeagueMgr::SendUserPlunderWar"
                            "Status cannot find the support"
                            " idServerTarget[%lu]", uFirst);
                        return;
                    }
                    g_fnSusMsgCtor(aMsg);
                    uint32_t uLg = uFirst / 1000000;
                    uint32_t uFlag = *(uint32_t*)(pc + 0x358);
                    if (g_fnSusMsgCreate(aMsg, 2, uLg, uFlag,
                                         aName) != 0) {
                        char* pCur =
                            *(char**)*(char**)(pNode + 0x50);
                        void* pMy = *(void**)(pNode + 0x20);
                        for (;;) {
                            char* pHd =
                                *(char**)(pNode + 0x50);
                            void* pP = *(void**)(pNode + 0x20);
                            if (pP == nullptr || pP != pMy)
                                g_fnLbrInvalid();
                            if (pHd == pCur) break;
                            if (pMy == nullptr) {
                                g_fnLbrInvalid();
                            } else {
                                void* pC2 = *(void**)pMy;
                                if (pCur == RdP(pC2, 0x30))
                                    g_fnLbrInvalid();
                            }
                            uint32_t uId =
                                *(uint32_t*)(pCur + 0x18);
                            if (uId != 0 &&
                                g_fnSusMsgAppend(aMsg, uId)
                                    == 0) {
                                g_fnSusMsgFlush(aMsg);
                                if (uParam3 == 0)
                                    g_fnSusSendAlt(
                                        pLogic, uParam4, aMsg);
                                else
                                    g_fnSplSendMsg(
                                        pLogic, uParam3, aMsg);
                                g_fnSusMsgClear(aMsg);
                                g_fnSusMsgCreate(aMsg, 2, uLg,
                                                 uFlag, aName);
                                g_fnSusMsgAppend(aMsg, uId);
                            }
                            if (*(unsigned char*)(pCur + 0x1d)
                                    == 0) {
                                char* pR = *(char**)(pCur + 0x10);
                                if (*(unsigned char*)(pR + 0x1d)
                                        == 0) {
                                    char* pW = pR;
                                    do {
                                        pCur = pW;
                                        pW = *(char**)pCur;
                                    } while (*(unsigned char*)(
                                        *(char**)pCur + 0x1d)
                                        == 0);
                                } else {
                                    char* pPrev = pCur;
                                    for (;;) {
                                        char* pPar =
                                            *(char**)(pPrev + 8);
                                        pCur = pPar;
                                        if (*(unsigned char*)(
                                                pPar + 0x1d) != 0)
                                            break;
                                        bool bR = pPrev ==
                                            *(char**)(pPar + 0x10);
                                        pPrev = pPar;
                                        if (!bR) break;
                                    }
                                }
                            } else {
                                g_fnLbrInvalid();
                            }
                        }
                        if (g_fnSusMsgCount(aMsg) != 0) {
                            g_fnSusMsgFlush(aMsg);
                            if (uParam3 == 0)
                                g_fnSusSendAlt(pLogic, uParam4,
                                               aMsg);
                            else
                                g_fnSplSendMsg(pLogic, uParam3,
                                               aMsg);
                        }
                    }
                    g_fnSusMsgDtor(aMsg);
                }
            }
        }
    }

    // ================= P5: 0x470, type 4 =================
    {
        uint64_t aIt2[2] = { 0, 0 };
        g_fnLbrMapLowerBound(pc + 0x470, aIt2, &uKeyV);
        char* pHead = (char*)RdP(pc, 0x4a0);
        void* pPr = RdP(pc, 0x470);
        if (pPr == nullptr ||
            pPr != (void*)(uintptr_t)aIt2[0])
            g_fnLbrInvalid();
        char* pNode = (char*)(uintptr_t)aIt2[1];
        if (pHead != pNode) {
            if ((void*)(uintptr_t)aIt2[0] == nullptr) {
                g_fnLbrInvalid();
            } else {
                void* pC = *(void**)(uintptr_t)aIt2[0];
                if (pNode == RdP(pC, 0x30))
                    g_fnLbrInvalid();
            }
            if (*(int64_t*)(pNode + 0x58) != 0) {
                g_fnSusMsgCtor(aMsg);
                uint32_t uFlag = *(uint32_t*)(pc + 0x358);
                if (g_fnSusMsgCreate(aMsg, 4, 0, uFlag, "")
                        != 0) {
                    char* pCur =
                        *(char**)*(char**)(pNode + 0x50);
                    void* pMy = *(void**)(pNode + 0x20);
                    for (;;) {
                        char* pHd = *(char**)(pNode + 0x50);
                        void* pP = *(void**)(pNode + 0x20);
                        if (pP == nullptr || pP != pMy)
                            g_fnLbrInvalid();
                        if (pHd == pCur) break;
                        if (pMy == nullptr) {
                            g_fnLbrInvalid();
                        } else {
                            void* pC2 = *(void**)pMy;
                            if (pCur == RdP(pC2, 0x30))
                                g_fnLbrInvalid();
                        }
                        int32_t nId =
                            *(int32_t*)(pCur + 0x18);
                        if (nId != 0 &&
                            g_fnSusMsgAppend(aMsg,
                                             (uint32_t)nId)
                                == 0) {
                            g_fnSusMsgFlush(aMsg);
                            if (uParam3 == 0)
                                g_fnSusSendAlt(pLogic,
                                               uParam4, aMsg);
                            else
                                g_fnSplSendMsg(pLogic,
                                               uParam3, aMsg);
                            g_fnSusMsgClear(aMsg);
                            g_fnSusMsgCreate(aMsg, 4, 0,
                                             uFlag, "");
                            g_fnSusMsgAppend(aMsg,
                                             (uint32_t)nId);
                        }
                        if (*(unsigned char*)(pCur + 0x1d)
                                == 0) {
                            char* pR = *(char**)(pCur + 0x10);
                            if (*(unsigned char*)(pR + 0x1d)
                                    == 0) {
                                char* pW = pR;
                                do {
                                    pCur = pW;
                                    pW = *(char**)pCur;
                                } while (*(unsigned char*)(
                                    *(char**)pCur + 0x1d)
                                    == 0);
                            } else {
                                char* pPrev = pCur;
                                for (;;) {
                                    char* pPar =
                                        *(char**)(pPrev + 8);
                                    pCur = pPar;
                                    if (*(unsigned char*)(
                                            pPar + 0x1d) != 0)
                                        break;
                                    bool bR = pPrev ==
                                        *(char**)(pPar + 0x10);
                                    pPrev = pPar;
                                    if (!bR) break;
                                }
                            }
                        } else {
                            g_fnLbrInvalid();
                        }
                    }
                    if (g_fnSusMsgCount(aMsg) != 0) {
                        g_fnSusMsgFlush(aMsg);
                        if (uParam3 == 0)
                            g_fnSusSendAlt(pLogic, uParam4,
                                           aMsg);
                        else
                            g_fnSplSendMsg(pLogic, uParam3,
                                           aMsg);
                    }
                }
                g_fnSusMsgDtor(aMsg);
            }
        }
    }
}

}  // namespace syndicate

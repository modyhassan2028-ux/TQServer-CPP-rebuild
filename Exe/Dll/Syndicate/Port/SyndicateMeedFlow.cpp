// ============================================================
// Syndicate.dll port — D47/T16: the meed CMsg flow
// (see SyndicateMeedFlow.h for the address map).
// ============================================================
#include "SyndicateMeedFlow.h"
#include "SyndicateSynMeed.h"     // the meed core
#include "SyndicateModule.h"       // g_fnGetServiceInst
#include "SyndicateCrossMerit.h"  // op-new seams
#include "SyndicateModule.h"       // g_pTqCMsgVft
#include <cstring>

namespace syndicate {

int MeedGetRecord(void*, uint64_t, int32_t*,
                int, int, int);  // D49 real

// ---- the defaults ----
static void DefTqCMsgInit(void*) {}
static void* DefMeedPoolCtor(void* p) {
    (void)p; return nullptr;
}
static char* DefMgrNameOf(void*, uint32_t) {
    return nullptr;
}
static void DefMeedSend(void*, void*, void*) {}

void* g_pMsgMemAwardRankVft = (void*)0x1234;
void (*g_fnTqCMsgInit)(void*) = DefTqCMsgInit;

void* g_pMeedPool = nullptr;      // DAT_141886d40
void* (*g_fnMeedPoolCtor)(void*) = DefMeedPoolCtor;
// (the original flow calls 14177cdc0 directly —
//  the seam now defaults to the REAL function)
void (*g_fnMeedListFill)(void*, int*, int*,
                         uint32_t, int)
    = &MeedPoolGetSynMeed;
int (*g_fnMeedGradePage)(void*, uint64_t, int32_t*,
                         int, int, int)
    = &MeedGetRecord;
char* (*g_fnMgrNameOf)(void*, uint32_t)
    = DefMgrNameOf;
void (*g_fnMeedSend)(void*, void*, void*)
    = DefMeedSend;

void MeedPoolReset() { g_pMeedPool = nullptr; }

// ---- FUN_14177d350: the pool lazy get ----
void* MeedPoolGet() {
    if (g_pMeedPool == nullptr) {
        void* pv = g_fnMeritOpNew(0xd0);
        if (pv == nullptr) {
            g_pMeedPool = nullptr;
        } else {
            g_pMeedPool = g_fnMeedPoolCtor(pv);
        }
        if (g_pMeedPool == nullptr) {
            g_fnMeedLog();
        }
    }
    return g_pMeedPool;
}

// ---- FUN_141778e60: count the entries of a type --
// (the members-vector walk, the vt+8 sub(3) protocol,
//  the debug-iterator gates verbatim)
int MeedGradeTypeCount(void* pLeague, int nType) {
    char* pc = (char*)pLeague;
    int iVar6 = 0;
    int64_t* plVar4 =
        *(int64_t**)(pc + 0x20);          // begin
    if (*(int64_t**)(pc + 0x28) < plVar4) {
        g_fnMeritInvalid();
    }
    int64_t* plVar1 =
        *(int64_t**)(pc + 8);             // the proxy
    while (true) {
        int64_t* plVar3 =
            *(int64_t**)(pc + 0x28);      // end
        if (plVar3 < *(int64_t**)(pc + 0x20)) {
            g_fnMeritInvalid();
        }
        if (*(int64_t**)(pc + 8) == nullptr
            || *(int64_t**)(pc + 8) != plVar1) {
            g_fnMeritInvalid();
        }
        if (plVar3 == plVar4) break;
        // the debug deref gate (verbatim)
        int64_t lVar5 = (plVar1 == nullptr) ? 0
            : *(int64_t*)plVar1;
        if (*(int64_t**)(lVar5 + 0x20) <= plVar4) {
            g_fnMeritInvalid();
        }
        int64_t* plMem = *(int64_t**)plVar4;
        if (plMem != nullptr) {
            void* pSub3 = g_fnMeedMemSub(plMem, 3);
            int iVar2 = g_fnMeedSubNType(pSub3);
            if (iVar2 == nType) {
                iVar6 = iVar6 + 1;
            }
        }
        // the debug advance (verbatim)
        lVar5 = (plVar1 == nullptr) ? 0
            : *(int64_t*)plVar1;
        if (*(int64_t**)(lVar5 + 0x20) <= plVar4) {
            g_fnMeritInvalid();
        }
        plVar4 = plVar4 + 1;
    }
    return iVar6;
}

// ---- FUN_1417d9e60: the CMsg ctor (verbatim) ----
void* CMsgMemAwardRankCtor(void* pMsg) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pMsgMemAwardRankVft;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return pMsg;
}

// ---- FUN_1417d9eb0: the CMsg dtor (verbatim) ----
void CMsgMemAwardRankDtor(void* pMsg) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pMsgMemAwardRankVft;
    *(void**)pc = g_pTqCMsgVft;
}

// ---- FUN_1417da020: the header encode ----
int CMsgMemAwardRankHead(void* pMsg, int nType,
                         int nCount, uint64_t uA,
                         int nB) {
    char* pc = (char*)pMsg;
    g_fnTqCMsgInit(pc);
    char* pHdr = *(char**)(pc + 0x408);
    *(uint16_t*)(pHdr + 2) = 0x427;   // the msg id
    *(uint16_t*)pHdr = 0x20;         // the size
    *(uint16_t*)(pHdr + 4) = 1;
    *(uint32_t*)(pHdr + 6) = nType;
    *(uint32_t*)(pHdr + 0xa) = nCount; // "+10" DEC
    *(uint32_t*)(pHdr + 0xe) = 0;    // entry count
    *(uint64_t*)(pHdr + 0x16) = uA;
    *(uint32_t*)(pHdr + 0x12) = nB;
    return 1;
}

// ---- FUN_1417da310: the entry append (0x3c) ----
int CMsgMemAwardRankAppend(void* pMsg, int32_t* pE,
                           const char* pName) {
    char* pc = (char*)pMsg;
    uint16_t* puVar2 = *(uint16_t**)(pc + 0x408);
    if (0x3ff < (uint32_t)*puVar2 + 0x3c) {
        g_fnMeedLog();
        return 0;
    }
    *puVar2 = *puVar2 + 0x3c;        // the size grow
    char* lVar3 = *(char**)(pc + 0x408);
    int64_t lVar4 =
        (int64_t)*(int32_t*)(lVar3 + 0xe) * 0x3c;
    // the entry zeroing (verbatim)
    *(uint64_t*)(lVar4 + 0x1e + lVar3) = 0;
    *(uint64_t*)(lVar4 + 0x26 + lVar3) = 0;
    *(uint64_t*)(lVar4 + 0x2e + lVar3) = 0;
    *(uint64_t*)(lVar4 + 0x36 + lVar3) = 0;
    *(uint64_t*)(lVar4 + 0x46 + lVar3) = 0;
    *(uint64_t*)(lVar4 + 0x4e + lVar3) = 0;
    *(uint32_t*)(lVar4 + 0x56 + lVar3) = 0;
    if (pName != nullptr) {
        strncpy((char*)(lVar4 + 0x36 + lVar3),
               pName, 0x24);
    }
    *(uint32_t*)(lVar4 + 0x1e + lVar3) = pE[0];
    *(uint32_t*)(lVar4 + 0x32 + lVar3) = pE[1];
    *(uint64_t*)(lVar4 + 0x2a + lVar3)
        = (uint64_t)(int64_t)pE[3];
    *(uint32_t*)(lVar4 + 0x22 + lVar3) = pE[2];
    *(uint32_t*)(lVar4 + 0x26 + lVar3) = pE[4];
    lVar3 = *(char**)(pc + 0x408);
    int32_t* piVar1 = (int32_t*)(lVar3 + 0xe);
    *piVar1 = *piVar1 + 1;           // the count
    return 1;
}


// ---- D48: the pool list fill (14177cdc0) ------
static void* DefMeedMemSubV(void* p) { return p; }
static uint32_t DefMeedSubVVal(void*) { return 0; }

void* (*g_fnMeedMemSubV)(void*) = DefMeedMemSubV;
uint32_t (*g_fnMeedSubVVal)(void*) = DefMeedSubVVal;

// ---- FUN_14177cb40: GetVecByMeedType (verbatim) --
void* MeedPoolVecByType(void* pPool, int nType) {
    char* pc = (char*)pPool;
    if ((uint32_t)(nType - 1) < 3) {
        return pc + (uint64_t)(nType - 1) * 0x30;
    }
    g_fnMeedLog();
    return pc + 0x98;
}

// ---- FUN_14177cad0: IsMemberUser (verbatim) ----
bool MeedIsMemberUser(void* pMember,
                      uint32_t uUser) {
    if (pMember == nullptr) {
        g_fnMeedLog();
        return false;
    }
    void* pSub2 = g_fnMeedMemSub(pMember, 2);
    int iVar1 = g_fnMeedSubNId(pSub2);
    return (uint32_t)iVar1 == uUser;
}

// ---- FUN_14177cdc0: GetSynMeed (verbatim) -----
void MeedPoolGetSynMeed(void* pPool, int* pnA,
                        int* pnB, uint32_t uUser,
                        int nType) {
    if (2 < (uint32_t)(nType - 1)) {  // verbatim
        g_fnMeedLog();
        return;
    }
    if (pnA == nullptr || pnB == nullptr) {
        g_fnMeedLog();
        return;
    }
    uint32_t uVar5 = 0, uVar6 = 0;
    char* pv = (char*)MeedPoolVecByType(pPool,
                                        nType);
    char** ppProxy = (char**)pv;
    char** puVar8 = *(char***)(pv + 0x18); // begin
    if (*(char***)(pv + 0x20) < puVar8) {   // end
        g_fnMeritInvalid();
    }
    char* plVar1 = *(char**)pv;             // proxy
    while (true) {
        char** puVar2 = *(char***)(pv + 0x20);
        if (puVar2 < *(char***)(pv + 0x18)) {
            g_fnMeritInvalid();
        }
        if (*ppProxy == nullptr
            || *ppProxy != plVar1) {
            g_fnMeritInvalid();
        }
        if (puVar2 == puVar8) break;   // the end
        // the debug deref gate (verbatim)
        int64_t lVar9 = (plVar1 == nullptr) ? 0
            : *(int64_t*)plVar1;
        if (*(char**)(lVar9 + 0x20)
            <= (char*)puVar8) {
            g_fnMeritInvalid();
        }
        char* pMem = *puVar8;
        if (pMem != nullptr
            && MeedIsMemberUser(pMem, uUser)) {
            // the member sub(3)/sub(4) outs
            void* pSub3 = g_fnMeedMemSub(pMem, 3);
            uVar5 = (uint32_t)
                g_fnMeedSubNType(pSub3);
            void* pSub4 = g_fnMeedMemSubV(pMem);
            uVar6 = g_fnMeedSubVVal(pSub4);
            break;
        }
        lVar9 = (plVar1 == nullptr) ? 0
            : *(int64_t*)plVar1;
        if (*(char**)(lVar9 + 0x20)
            <= (char*)puVar8) {
            g_fnMeritInvalid();
        }
        puVar8 = puVar8 + 1;           // the stride
    }
    *pnA = (int)uVar5;
    *pnB = (int)uVar6;
}


// ---- D49: the grade page query (141779f40) ----
static void DefMeedSortRaw(void**, void**, int) {}
void (*g_fnMeedSortRaw)(void**, void**, int)
    = DefMeedSortRaw;   // (D50: the real introsort)

// the sub reads: vt+0x48 (the value slots) and
// the vt+0x40 id (via the D46 seams)
static int Sub48(void* pM, int n) {
    void* pSub = g_fnMeedMemSub(pM, n);
    return g_fnMeedSubNType(pSub);
}
static int SubId(void* pM) {
    void* pSub = g_fnMeedMemSub(pM, 2);
    return g_fnMeedSubNId(pSub);
}

// ---- FUN_1417782c0: the entry type match ------
bool MeedRecMatchType(void* pL, void* pM,
                      int nType) {
    (void)pL;
    if (pM == nullptr) {
        g_fnMeedLog();
        return false;
    }
    void* pSub = g_fnMeedMemSub(pM, 3);
    return g_fnMeedSubNType(pSub) == nType;
}

// ---- FUN_141779eb0: the lazy sort (verbatim) --
void MeedSortIfNeeded(void* pL) {
    char* pc = (char*)pL;
    if (*(void***)(pc + 0x28)
        < *(void***)(pc + 0x20)) {
        g_fnMeritInvalid();
    }
    void** ppBegin = *(void***)(pc + 0x20);
    void** ppEnd = *(void***)(pc + 0x28);
    if (*(void***)(pc + 0x28) < ppBegin) {
        g_fnMeritInvalid();
    }
    int64_t lVar3 = *(int64_t*)(pc + 8);
    if (*(void***)(pc + 0x28) < ppBegin) {
        g_fnMeritInvalid();
    }
    if ((lVar3 == 0)
        || (lVar3 != *(int64_t*)(pc + 8))) {
        g_fnMeritInvalid();
    }
    g_fnMeedSortRaw(ppBegin, ppEnd,
        (int)(((int64_t)ppEnd - (int64_t)ppBegin)
              >> 3));
    *(uint8_t*)(pc + 0x38) = 1;
}

// ---- FUN_141779f40: GetMeedRecord (verbatim) --
int MeedGetRecord(void* pL, uint64_t uUser,
                  int32_t* pOut, int nType,
                  int nLimit, int nPage) {
    char* pc = (char*)pL;
    if (2 < (uint32_t)(nType - 1)) {  // verbatim
        g_fnMeedLog();
        return 0;
    }
    if (*(uint8_t*)(pc + 0x38) == 0) {
        MeedSortIfNeeded(pL);
    }
    int ret = 0;        // r13d
    int matches = 0;    // edi (the window count)
    if (nType == 2) {
        if (0 < nPage) {
            int32_t* cursor = pOut + 3;
            int64_t visited = 0;
            int64_t cellIdx = 0;
            int written = 0;
            do {
                int64_t count =
                    ((int64_t)*(void***)(pc + 0x28)
                    - (int64_t)*(void***)(pc
                        + 0x20)) >> 3;
                if (count <= visited) {
                    return ret;
                }
                if (count <= cellIdx) {
                    g_fnMeritInvalid();
                }
                int64_t* cell =
                    *(int64_t**)(*(char**)(pc
                        + 0x20) + cellIdx * 8);
                if (cell != nullptr
                    && MeedRecMatchType(pL, cell, 2)
                    && matches < nLimit) {
                    matches = matches + 1; // skip
                } else {
                    // the write (verbatim —
                    // matches stays frozen)
                    cursor[-3] = matches + 1;
                    cursor[1] = Sub48(cell, 6);
                    *cursor = Sub48(cell, 5);
                    cursor[-1] = Sub48(cell, 4);
                    cursor[-2] = SubId(cell);
                    ret = ret + 1;
                    written = written + 1;
                    cursor = cursor + 5;
                }
                visited = visited + 1;
                cellIdx = cellIdx + 1;
            } while (written < nPage);
        }
    } else if (nType == 1 || nType == 3) {
        // r12 = cellIdx, r14d = visited, ebp = rank
        int rank = 1;
        int64_t selfWritten = 0;   // local_40
        int32_t* cursorB = pOut + 8;  // slot 1
        int64_t cellIdx = 0;
        int64_t visited = 0;
        bool exited = false;
        int64_t count =
            ((int64_t)*(void***)(pc + 0x28)
            - (int64_t)*(void***)(pc + 0x20)) >> 3;
        if (count != 0) {
            do {
                if (count <= cellIdx) {
                    g_fnMeritInvalid();
                }
                int64_t* cell =
                    *(int64_t**)(*(char**)(pc
                        + 0x20) + cellIdx * 8);
                if (cell != nullptr
                    && MeedRecMatchType(pL, cell,
                                        nType)) {
                    bool bSelf =
                        MeedIsMemberUser(cell,
                                         (uint32_t)
                                         uUser);
                    if (bSelf) {
                        // the SELF path: slot 0
                        pOut[0] = rank;
                        pOut[4] = Sub48(cell, 6);
                        pOut[3] = Sub48(cell, 5);
                        pOut[2] = Sub48(cell, 4);
                        pOut[1] = SubId(cell);
                        if ((int64_t)nPage
                            <= selfWritten) {
                            ret = ret + 1;
                            exited = true;
                            break;  // a300
                        }
                    }
                    // a22d (both paths reach)
                    if (matches < nLimit) {
                        matches = matches + 1;
                        rank = rank + 1;
                    } else if (selfWritten
                               < nPage) {
                        cursorB[-3] = rank;
                        cursorB[1] =
                            Sub48(cell, 6);
                        *cursorB =
                            Sub48(cell, 5);
                        cursorB[-1] =
                            Sub48(cell, 4);
                        cursorB[-2] =
                            SubId(cell);
                        selfWritten
                            = selfWritten + 1;
                        rank = rank + 1;
                        ret = ret + 1;
                        cursorB = cursorB + 5;
                    } else {
                        rank = rank + 1;
                    }
                }
                visited = visited + 1;
                cellIdx = cellIdx + 1;
            } while (visited < count);
        } else {
            ret = ret + 1;  // a300 (the empty
        }                   //  vector → 1!)
        if (!exited && count == 0) {
            // (handled above)
        }
    }
    return ret;
}

// ---- FUN_14177f700: SendMemberGrade (verbatim) --
uint64_t MeedSendMemberGrade(void* pUserProxy,
                             uint64_t uUser,
                             int nType, int nPage) {
    uint64_t uVar7 = 0;
    if ((uint32_t)(nType - 1) < 3) {
        if (nPage < 1) {
            // verbatim: (type-1)>>8 is 0 inside the
            // 1-3 gate — uVar7 = 0
            uVar7 = ((uint64_t)(
                (uint32_t)(nType - 1) >> 8)) << 8;
        } else {
            int64_t* plVar3 =
                (int64_t*)g_fnGetServiceInst();
            uint32_t uId =
                (uint32_t)g_fnMgrUserId(plVar3);
            void* plVar4 = MeedSingletonGet();
            void* pLeague =
                MeedUserLeague(plVar4, uId);
            if (pLeague != nullptr) {
                int iVar2 = MeedGradeTypeCount(
                    pLeague, nType);
                int local_514 = 0;
                int local_518 = 0;
                void* pvPool = MeedPoolGet();
                g_fnMeedListFill(pvPool, &local_514,
                                 &local_518, uId,
                                 nType);
                // the CMsg buffer (the stack
                // alloc of the original: CMsg[1040])
                char msgBuf[8320];
                CMsgMemAwardRankCtor(msgBuf);
                uint64_t uVar6 = (uint64_t)
                    CMsgMemAwardRankHead(
                        msgBuf, nType, iVar2,
                        (uint64_t)(int64_t)local_514,
                        local_518);
                if ((char)uVar6 == '\0') {
                    g_fnMeedLog();
                    CMsgMemAwardRankDtor(msgBuf);
                    return 0;
                }
                // the 40-entry zeroing (8×5 ints)
                int32_t entries[40];
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 5; ++j) {
                        entries[i * 5 + j] = 0;
                    }
                }
                int iVar2b = 0;   // the limit
                int iVar10 = 0;   // the stride
                if (nType == 1 || nType == 3) {
                    iVar2b = nPage * 4 - 4;
                    iVar10 = 4;
                } else if (nType == 2) {
                    iVar2b = nPage * 8 - 8;
                    iVar10 = 8;
                }
                uVar7 = (uint64_t)g_fnMeedGradePage(
                    pLeague, uUser, entries, nType,
                    iVar2b, iVar10);
                int iVar11 = 0;
                while (iVar11 < (int)uVar7) {
                    char* pcVar8 = g_fnMgrNameOf(
                        plVar3,
                        (uint32_t)entries[iVar11 * 5
                                           + 1]);
                    uint64_t uVar9 =
                        (uint64_t)CMsgMemAwardRankAppend(
                            msgBuf,
                            entries + iVar11 * 5,
                            pcVar8);
                    if ((char)uVar9 == '\0') {
                        g_fnMeedLog();
                        CMsgMemAwardRankDtor(msgBuf);
                        return 0;
                    }
                    iVar11 = iVar11 + 1;
                }
                g_fnMeedSend(
                    *(void**)pUserProxy, (void*)uUser,
                    msgBuf);
                CMsgMemAwardRankDtor(msgBuf);
                return 1;
            }
        }
    } else {
        g_fnMeedLog();
        uVar7 = 0;
    }
    return uVar7 & 0xffffffffffffff00ULL;
}

} // namespace syndicate

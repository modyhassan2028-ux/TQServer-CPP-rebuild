#include "SyndicateMeedInfo.h"
#include "SyndicateMeedFlow.h"
#include "SyndicateMeedSort.h"
#include "SyndicateSynMeed.h"
#include "SyndicateCrossMerit.h"
#include "SyndicateModule.h"
#include <cstring>

namespace syndicate {

int (*g_fnMeedSubNScore)(void*) = nullptr;
int (*g_fnMeedReqId)(void*) = nullptr;
static char* DefMgrNameOfSvc(void*, uint32_t) {
    return nullptr;
}
char* (*g_fnMgrNameOfSvc)(void*, uint32_t)
    = DefMgrNameOfSvc;
static void DefSendTarget(void*, void*, void*) {}
void (*g_fnMeedSendTarget)(void*, void*, void*)
    = DefSendTarget;

// ---- FUN_14177c970: the score comparator -----
bool MeedCmpScore(void* a, void* b) {
    if (a == nullptr) {
        return false;
    }
    if (b == nullptr) {
        return true;
    }
    void* s = g_fnMeedMemSub(a, 4);
    int64_t k1a = g_fnMeedSubNScore(s);
    s = g_fnMeedMemSub(a, 3);
    int64_t k1b = g_fnMeedSubNScore(s);
    int64_t k1 = k1a * 50000 + k1b;
    s = g_fnMeedMemSub(b, 4);
    int64_t k2a = g_fnMeedSubNScore(s);
    s = g_fnMeedMemSub(b, 3);
    int64_t k2b = g_fnMeedSubNScore(s);
    int64_t k2 = k2a * 50000 + k2b;
    if (k1 == k2) {
        s = g_fnMeedMemSub(a, 2);
        uint32_t ida =
            (uint32_t)g_fnMeedSubNId(s);
        s = g_fnMeedMemSub(b, 2);
        uint32_t idb =
            (uint32_t)g_fnMeedSubNId(s);
        return ida < idb;
    }
    return k2 < k1;
}

// ---- FUN_14177c870: the grade comparator -----
bool MeedCmpGrade(void* a, void* b) {
    if (a == nullptr) {
        return false;
    }
    if (b == nullptr) {
        return true;
    }
    void* s = g_fnMeedMemSub(a, 4);
    int ga = g_fnMeedSubNType(s);
    s = g_fnMeedMemSub(b, 4);
    int gb = g_fnMeedSubNType(s);
    if (ga == gb) {
        s = g_fnMeedMemSub(a, 3);
        int ta = g_fnMeedSubNType(s);
        s = g_fnMeedMemSub(b, 3);
        int tb = g_fnMeedSubNType(s);
        if (ta == tb) {
            s = g_fnMeedMemSub(a, 2);
            uint32_t ida =
                (uint32_t)g_fnMeedSubNId(s);
            s = g_fnMeedMemSub(b, 2);
            uint32_t idb =
                (uint32_t)g_fnMeedSubNId(s);
            return ida < idb;
        }
        return tb < ta;
    }
    return gb < ga;
}

// ---- the debug-iterator gates (the vector
//      pattern of the family) -----------------
static void MeedVecGates(void** v) {
    if ((void*)v[4] < (void*)v[3]) {
        g_fnMeritInvalid();
    }
    if ((void*)v[4] < (void*)v[3]) {
        g_fnMeritInvalid();
    }
    int64_t lVar3 = (int64_t)v[0];
    if ((void*)v[4] < (void*)v[3]) {
        g_fnMeritInvalid();
    }
    if ((lVar3 == 0)
        || (lVar3 != (int64_t)v[0])) {
        g_fnMeritInvalid();
    }
}

// ---- FUN_14177d9b0: SortByMeed --------------
void MeedSortByType(void* pPool, int nType) {
    char* pc = (char*)pPool;
    void** v = nullptr;
    if (2 < (uint32_t)(nType - 1)) {
        g_fnMeedLog();   // SortByMeed Type log
        return;
    }
    if ((uint32_t)(nType - 1) < 3) {
        v = (void**)(pc + (nType - 1) * 0x30);
    } else {
        v = (void**)(pc + 0x98);
    }
    MeedSortCmpFn cmp = (nType == 2)
        ? &MeedCmpGrade : &MeedCmpScore;
    MeedVecGates(v);
    MeedSortDriver(
        (void**)v[3], (void**)v[4],
        ((int64_t)v[4] - (int64_t)v[3]) / 8,
        cmp);
    if (nType < 1) {
        // the dead error branch (inlined from
        // GetSortFlagByMeedType) — verbatim
        *(uint8_t*)(pc + 200) = 1; // 0xc8!
        return;
    }
    uint8_t* pf =
        (uint8_t*)(pc + 0x90 + (nType - 1));
    *pf = 1;
}

// ---- FUN_14177cd40: GetCount ----------------
int MeedGetCount(void* pPool, int nType) {
    char* pc = (char*)pPool;
    if (2 < (uint32_t)(nType - 1)) {
        g_fnMeedLog();   // GetCount Type log
        return 0;
    }
    if ((uint32_t)(nType - 1) < 3) {
        char* e = pc + (nType - 1) * 0x30;
        return (int)((*(int64_t*)(e + 0x20)
                      - *(int64_t*)(e + 0x18))
                     / 8);
    }
    g_fnMeedLog();   // GetVecByMeedType log
    return (int)((*(int64_t*)(pc + 0xb8)
                  - *(int64_t*)(pc + 0xb0))
                 / 8);
}

// ---- FUN_14177dfe0: GetMeedList -------------
int MeedGetList(void* pPool, int nReqId,
                int32_t* pnOut, int nType,
                int nOffset, int nSpan,
                int32_t* pnSelfA,
                int32_t* pnSelfB) {
    char* pc = (char*)pPool;
    uint32_t uT = (uint32_t)(nType - 1);
    if (2 < uT) {
        g_fnMeedLog();   // GetMeedList log
        return 0;
    }
    char* e = pc + (int)uT * 0x30;
    if (*(uint8_t*)(pc + 0x90 + (int)uT)
        == 0) {
        MeedSortByType(pPool, nType);
    }
    int64_t uOff = (int64_t)(uint32_t)nOffset;
    int nWritten = 0;
    bool bSelf = false;
    int32_t* pOut = pnOut;
    if (0 < nSpan) {
        uint32_t uCur = (uint32_t)nOffset;
        int64_t n = 0;
        do {
            int64_t cnt =
                (*(int64_t*)(e + 0x20)
                 - *(int64_t*)(e + 0x18)) / 8;
            if (cnt <= (int64_t)(uCur
                                 & 0xffffffff)) {
                break;
            }
            if (cnt <= uOff) {
                g_fnMeritInvalid();
            }
            void** pm =
                *(void***)(*(int64_t*)(e + 0x18)
                           + uOff * 8);
            if (pm != nullptr) {
                void* s = g_fnMeedMemSub(pm, 2);
                pOut[0] = g_fnMeedSubNId(s);
                s = g_fnMeedMemSub(pm, 4);
                pOut[2] = g_fnMeedSubNType(s);
                s = g_fnMeedMemSub(pm, 3);
                pOut[1] = g_fnMeedSubNType(s);
                if (!bSelf && nReqId != 0
                    && pOut[0] == nReqId) {
                    bSelf = true;
                    s = g_fnMeedMemSub(pm, 3);
                    *pnSelfA =
                        g_fnMeedSubNType(s);
                    s = g_fnMeedMemSub(pm, 4);
                    *pnSelfB =
                        g_fnMeedSubNType(s);
                }
                nWritten++;
                n++;
                pOut = pOut + 3;
            }
            uCur = uCur + 1;
            uOff = uOff + 1;
        } while (n < nSpan);
        if (bSelf) {
            return nWritten;
        }
    }
    // the self scan (types 1/3 only)
    if (nReqId != 0
        && (nType == 1 || nType == 3)) {
        int64_t cnt =
            (*(int64_t*)(e + 0x20)
             - *(int64_t*)(e + 0x18)) / 8;
        int64_t i = 0;
        if (cnt != 0) {
            do {
                if (cnt <= i) {
                    g_fnMeritInvalid();
                }
                void** pm =
                    *(void***)(*(int64_t*)(e + 0x18)
                               + i * 8);
                if (pm != nullptr) {
                    void* s =
                        g_fnMeedMemSub(pm, 2);
                    if (g_fnMeedSubNId(s)
                        == nReqId) {
                        s = g_fnMeedMemSub(pm, 3);
                        *pnSelfA =
                            g_fnMeedSubNType(s);
                        s = g_fnMeedMemSub(pm, 4);
                        *pnSelfB =
                            g_fnMeedSubNType(s);
                        return nWritten;
                    }
                }
                i++;
            } while (i < cnt);
        }
    }
    return nWritten;
}

// ---- FUN_1417d9f90: the self-rank create ----
int CMsgSelfRankCreate(void* pMsg, int nType,
                       int nCount) {
    char* pc = (char*)pMsg;
    g_fnTqCMsgInit(pc);
    char* pHdr = *(char**)(pc + 0x408);
    *(uint16_t*)(pHdr + 2) = 0x427;
    *(uint16_t*)pHdr = 0x20;
    *(uint16_t*)(pHdr + 4) = 0;
    *(uint32_t*)(pHdr + 6) = (uint32_t)nType;
    *(uint32_t*)(pHdr + 0xe) = 0;
    *(uint32_t*)(pHdr + 10) = (uint32_t)nCount;
    *(uint64_t*)(pHdr + 0x16) = 0;
    *(uint32_t*)(pHdr + 0x12) = 0;
    return 1;
}

// ---- FUN_1417da420: the counts write ---------
int CMsgSelfRankCounts(void* pMsg, int64_t uA,
                       int nB) {
    char* pc = (char*)pMsg;
    char* pHdr = *(char**)(pc + 0x408);
    *(int64_t*)(pHdr + 0x16) = uA;
    *(int32_t*)(pHdr + 0x12) = nB;
    return 0;
}

// ---- FUN_1417da210: the self-rank append -----
int CMsgSelfRankAppend(void* pMsg, int32_t* pnE,
                       const char* pName) {
    char* pc = (char*)pMsg;
    uint16_t* puVar2 = *(uint16_t**)(pc + 0x408);
    if (0x3ff < (uint32_t)*puVar2 + 0x34) {
        g_fnMeedLog();
        return 0;
    }
    *puVar2 = (uint16_t)(*puVar2 + 0x34);
    char* lVar3 = *(char**)(pc + 0x408);
    int64_t lVar4 =
        (int64_t)*(int32_t*)(lVar3 + 0xe)
        * 0x34;
    *(int64_t*)(lVar4 + 0x1e + (int64_t)lVar3)
        = 0;
    *(int64_t*)(lVar4 + 0x26 + (int64_t)lVar3)
        = 0;
    *(int64_t*)(lVar4 + 0x2e + (int64_t)lVar3)
        = 0;
    *(int64_t*)(lVar4 + 0x36 + (int64_t)lVar3)
        = 0;
    *(int64_t*)(lVar4 + 0x3e + (int64_t)lVar3)
        = 0;
    *(int64_t*)(lVar4 + 0x46 + (int64_t)lVar3)
        = 0;
    *(int32_t*)(lVar4 + 0x4e + (int64_t)lVar3)
        = 0;
    if (pName != nullptr) {
        strncpy(lVar4 + 0x2a + lVar3, pName,
                0x24);
    }
    *(int32_t*)(lVar4 + 0x4e + (int64_t)lVar3)
        = pnE[0];
    *(int64_t*)(lVar4 + 0x22 + (int64_t)lVar3)
        = (int64_t)pnE[1];
    *(int32_t*)(lVar4 + 0x1e + (int64_t)lVar3)
        = pnE[2];
    lVar3 = *(char**)(pc + 0x408);
    *(int32_t*)(lVar3 + 0xe) =
        *(int32_t*)(lVar3 + 0xe) + 1;
    return 1;
}

// ---- FUN_141780a30: SendMeedInfo (the flow) --
bool MeedSendInfo(void* pThis, void* p2,
                  int nType, int nPage) {
    if ((uint32_t)(nType - 1) >= 3) {
        g_fnMeedLog();   // SendMeedInfo Type log
        return false;
    }
    if (nPage < 1) {
        return false;
    }
    void* pSvc = g_fnGetServiceInst();
    int nReqId = g_fnMeedReqId(pSvc);
    void* pPool = MeedPoolGet();
    int64_t nTotal = MeedGetCount(pPool, nType);
    // the stack CMsg (0x820, zeroed)
    static __thread char msg[0x820];
    memset(msg, 0, sizeof(msg));
    CMsgMemAwardRankCtor(msg);
    if (CMsgSelfRankCreate(msg, nType,
                           (int)nTotal) == 0) {
        g_fnMeedLog();
        CMsgMemAwardRankDtor(msg);
        return false;
    }
    // the ids buffer: 8 entries x 3 ints
    int32_t ids[24];
    memset(ids, 0, sizeof(ids));
    int nSpan;
    int nOffset;
    if (nType == 1 || nType == 3) {
        nOffset = nPage * 5 - 5;
        nSpan = 5;
    } else {
        nOffset = nPage * 8 - 8;
        nSpan = 8;
    }
    int32_t selfA = 0;
    int32_t selfB = 0;
    int nWritten = MeedGetList(pPool, nReqId,
                               ids, nType,
                               nOffset, nSpan,
                               &selfA, &selfB);
    if (nType == 1 || nType == 3) {
        CMsgSelfRankCounts(msg, selfA, selfB);
    }
    for (int i = 0; i < nSpan; ++i) {
        char* pName =
            g_fnMgrNameOfSvc(pSvc,
                             (uint32_t)ids[i * 3]);
        if (CMsgSelfRankAppend(msg,
                               &ids[i * 3],
                               pName) == 0) {
            g_fnMeedLog();
            CMsgMemAwardRankDtor(msg);
            return false;
        }
    }
    // the send: (*pThis)->vt[1](obj, p2, msg)
    void* pObj = *(void**)pThis;
    g_fnMeedSendTarget(pObj, p2, msg);
    CMsgMemAwardRankDtor(msg);
    return true;
}

} // namespace syndicate

// SyndicateMeedApply — D53/T16: the SetArenicMeed
// flow + the CMeedSetMgr apply family, verbatim
// from Syndicate.dll.decompiled.c.
// The logic singleton (1417b6210), the user object
// and the DB instance are opaque: every call is the
// ORIGINAL vtable-offset call via an explicit slot
// cast (the D21/D51 style).
#include "SyndicateMeedApply.h"
#include "SyndicateLeagueCmp.h"    // LeagueSingleton
#include "SyndicateMeedFlow.h"     // pool + msg
#include "SyndicateMeedSort.h"     // the sort family
#include "SyndicateMeedInfo.h"     // MeedSortByType, g_fnMeedReqId
#include "SyndicateSynMeed.h"      // g_fnMeedLog
#include "SyndicateCrossMerit.h"   // g_fnMeritInvalid

#include <cstdio>
#include <cstring>

namespace syndicate {

// ---------- the seam defaults ----------
int32_t g_nMeedMoneyCap = 0;
void* (*g_fnMeedInstGet)() =
    []() -> void* { return nullptr; };
void* (*g_fnMeedStrInst)() =
    []() -> void* { return nullptr; };
char* (*g_fnMeedStrGet)(void*, const char*) =
    [](void*, const char*) -> char* {
        return nullptr; };
void (*g_fnMeedSnprintf)(char*, size_t,
                        const char*) =
    [](char* d, size_t, const char* f) {
        snprintf(d, 0x400, "%s", f ? f : ""); };
void (*g_fnMeedLogSave)(const char*, const char*,
                       uint32_t) =
    [](const char*, const char*, uint32_t) {};
void (*g_fnMeedVecInsert)(void*, void**,
                          void**, void*) =
    [](void*, void**, void**, void*) {};
const char* g_szMeedLogFmtFresh = "FMT-FRESH";
const char* g_szMeedLogFmtMore = "FMT-MORE";

namespace {
inline void* VtSlot(void* pObj, size_t uOff) {
    void* pVt = *(void**)pObj;
    return *(void**)((char*)pVt + uOff);
}
inline char* StrOf(const char* pKey) {
    return g_fnMeedStrGet(g_fnMeedStrInst(),
                          pKey);
}
} // namespace

// ---------- FUN_14177caa0: the bounds ----------
uint64_t MeedApplyBounds(int nMoney, int nEmoney) {
    if (-1 < nMoney) {
        if (((nMoney < g_nMeedMoneyCap)
             && (-1 < nEmoney))
            && (nEmoney < g_nMeedMoneyCap)
            && ((0 < nEmoney || (0 < nMoney)))) {
            return 1;
        }
    }
    return 0;   // RAX & ~0xff
}

// ---------- FUN_14177cb90: the flag addr --------
uint8_t* MeedSortFlagGet(void* pPool, int nType) {
    char* pc = (char*)pPool;
    if ((uint32_t)(nType - 1) < 3) {
        return (uint8_t*)(pc + 0x90
                          + (nType - 1));
    }
    g_fnMeedLog();   // GetSortFlagByMeedType log
    return (uint8_t*)(pc + 200);   // 0xc8!
}

// ---------- FUN_14177ff70: GetEmonyType ---------
uint64_t MeedEmonyType(void* pUser, int nType,
                       int nMoneyType) {
    (void)pUser;   // (not used in the body)
    uint64_t uVar1 = 0;
    if (((uint32_t)(nType - 1) < 3)
        && ((uint32_t)nMoneyType < 5)) {
        if (nType == 2) {
            if (nMoneyType == 4) {
                goto LAB_NotFound;
            }
            if (nMoneyType == 0) return 0x15;
            if (nMoneyType == 1) return 0x16;
            if (nMoneyType == 2) return 0x17;
            if (nMoneyType == 3) return 0x18;
        } else if (nType == 1) {
            if (nMoneyType == 0) return 0x1a;
            if (nMoneyType == 1) return 0x1b;
            if (nMoneyType == 2) return 0x1c;
            if (nMoneyType == 3) return 0x1d;
            if (nMoneyType == 4) return 0x29;
        } else if (nType == 3) {
            if (nMoneyType == 0) {
                uVar1 = 0x25;   // fallthrough
            } else {
                if (nMoneyType == 1) return 0x26;
                if (nMoneyType == 2) return 0x27;
                if (nMoneyType == 3) return 0x28;
                uVar1 = 0;
                if (nMoneyType == 4) return 0x2a;
            }
        }
        return uVar1;
    }
LAB_NotFound:
    g_fnMeedLog();   // GetEmonyType log
    return 0;
}

// ---------- FUN_14177fbc0: GetStrObject ---------
char* MeedPromptGet(void* pUser, int nType,
                    int nStrType) {
    char* uVar3 = nullptr;
    if (((uint32_t)(nType - 1) < 3)
        && ((uint32_t)(nStrType - 1) < 7)) {
        if (nType == 1) {
            switch (nStrType) {
            case 1: {
                // the vt+0x360 gate (the args were
                // dropped by Ghidra; the object is
                // passed)
                void* pObj = *(void**)pUser;
                auto fn = (char (*)(void*))
                    VtSlot(pObj, 0x360);
                if (fn(pObj) != '\0') {
                    return StrOf(
                        "STR_VLM_ARENIC_MEED1_1");
                }
                return StrOf(
                    "STR_VLM_ARENIC_MEED1_2"); }
            case 2: {
                void* pObj = *(void**)pUser;
                auto fn = (char (*)(void*))
                    VtSlot(pObj, 0x360);
                if (fn(pObj) != '\0') {
                    return StrOf(
                        "STR_VLM_ARENIC_MEED2_1");
                }
                return StrOf(
                    "STR_VLM_ARENIC_MEED2_2"); }
            case 3:
                return StrOf(
                    "STR_VLM_ARENIC_DISTRIBUTEMEED1");
            case 4:
                return StrOf(
                    "STR_VLM_ARENIC_DISTRIBUTEMEED2");
            case 5:
                return StrOf(
                    "STR_VLM_ARENIC_OVER");
            case 6:
                return StrOf(
                    "STR_VLM_ARENIC_FIRST");
            case 7:
                return StrOf(
                    "STR_VLM_ARENIC_END_PROCESS");
            }
        } else if (nType == 2) {
            switch (nStrType) {
            case 1:
                return StrOf("STR_SYN_ARENIC_MEED1");
            case 2:
                return StrOf("STR_SYN_ARENIC_MEED2");
            case 3:
                return StrOf(
                    "STR_SYN_ARENIC_DISTRIBUTEMEED1");
            case 4:
                return StrOf(
                    "STR_SYN_ARENIC_DISTRIBUTEMEED2");
            case 5:
                return StrOf(
                    "STR_SYN_ARENIC_OVER");
            }
        } else if (nType == 3) {
            switch (nStrType) {
            case 1:
                return StrOf(
                    "STR_CROSS_VLM_ARENIC_MEED1");
            case 2:
                return StrOf(
                    "STR_CROSS_VLM_ARENIC_MEED2");
            case 3:
                return StrOf(
                    "STR_CROSS_VLM_ARENIC_DISTRIBUTEMEED1");
            case 4:
                return StrOf(
                    "STR_CROSS_VLM_ARENIC_DISTRIBUTEMEED2");
            case 5:
                return StrOf(
                    "STR_CROSS_VLM_ARENIC_OVER");
            case 6:
                return StrOf(
                    "STR_CROSS_VLM_ARENIC_FIRST");
            case 7:
                uVar3 = StrOf(
                    "STR_CROSS_VLM_ARENIC_END_PROCESS");
                break;   // fallthrough
            }
        }
        return uVar3;
    }
    g_fnMeedLog();   // GetStrObject log
    return nullptr;
}

// ---------- FUN_14177fad0: the gmlog names ------
const char* MeedGmLogName(int nType, int nIdx) {
    if (((uint32_t)(nType - 1) < 3)
        && ((uint32_t)(nIdx - 1) < 3)) {
        if (nType == 1) {
            if (nIdx == 1) return "gmlog/money_vlmarenic";
            if (nIdx == 2) return "gmlog/vlm_meed_award";
            if (nIdx == 3) return "gmlog/vlm_meed_overflow";
        } else if (nType == 2) {
            if (nIdx == 1) return "gmlog/money_synarenic";
            if (nIdx == 2) return "gmlog/syn_meed_award";
            if (nIdx == 3) return "gmlog/syn_meed_overflow";
        } else if (nType == 3) {
            if (nIdx == 1) return "gmlog/cross_money_vlmarenic";
            if (nIdx == 2) return "gmlog/cross_vlm_meed_award";
            if (nIdx == 3) return "gmlog/cross_vlm_meed_overflow";
        }
    } else {
        g_fnMeedLog();   // GetGMFileName log
    }
    return "gmlog/meed_error";
}

// ---------- FUN_1417da0d0: the 0x427 encode ------
uint64_t CMsgAwardRankEncode(void* pMsg,
                            uint16_t uA,
                            uint32_t uType,
                            uint64_t uMoney,
                            uint32_t uB) {
    g_fnTqCMsgInit(pMsg);
    char* pc = *(char**)((char*)pMsg + 0x408);
    *(uint16_t*)(pc + 2) = 0x427;
    *(uint16_t*)(pc + 0) = 0x20;
    *(uint16_t*)(pc + 4) = uA;
    *(uint32_t*)(pc + 6) = uType;
    *(uint32_t*)(pc + 0xe) = 0;
    *(uint64_t*)(pc + 0x16) = uMoney;
    *(uint32_t*)(pc + 0x12) = uB;
    return 1;
}

// ---------- FUN_141732200: the vec push ---------
void MeedVecPush(void* pVec, void** ppVal) {
    void** puVar1 = *(void***)((char*)pVec + 0x18);
    uint64_t uVar3 = 0;
    if (puVar1 != (void**)0) {
        // the capacity qword at vec+0x28
        uVar3 = (uint64_t)(
            (*(char**)((char*)pVec + 0x28))
            - (char*)puVar1)
            >> 3;
    }
    void** puVar2 = *(void***)((char*)pVec + 0x20);
    if ((uint64_t)(((char*)puVar2
                    - (char*)puVar1) >> 3) < uVar3) {
        *puVar2 = *ppVal;
        *(void***)((char*)pVec + 0x20) = puVar2 + 1;
        return;
    }
    if (puVar2 < puVar1) {
        g_fnMeritInvalid();
    }
    // local_28 = *vec (the proxy deref pair) +
    // puStack_20 = end — then 1417311d0
    void* local_28[2] = { *(void**)pVec, nullptr };
    void* puStack_20 = puVar2;
    g_fnMeedVecInsert(pVec, local_28,
                      &puStack_20, ppVal);
}

// ---------- FUN_14177d5f0: Insert ---------------
uint8_t MeedSetMgrInsert(void* pPool,
                         int32_t* pnEntry,
                         int nType) {
    if ((uint32_t)(nType - 1) < 3) {
        int iVar1 = pnEntry[1];
        int iVar2 = pnEntry[2];
        if (-1 < iVar1) {
            if (((iVar1 < g_nMeedMoneyCap)
                 && (-1 < iVar2))
                && (iVar2 < g_nMeedMoneyCap)
                && ((0 < iVar2
                     || (0 < iVar1)))) {
                // the query chain (opaque vtables)
                void* plVar4 = g_fnMeedInstGet();
                {
                    auto fn = (void* (*)(
                        void*, const char*))
                        VtSlot(plVar4, 0x20);
                    plVar4 = fn(plVar4, "cq_setmeed");
                }
                void* local_res20 = plVar4;
                if (plVar4 == (void*)0) {
                    g_fnMeedLog();
                    return 0;
                }
                {
                    auto fnF = (void* (*)(
                        void*, int64_t))
                        VtSlot(plVar4, 0x10);
                    auto fnB0 = (void (*)(void*,
                                          int64_t))
                        nullptr;
                    void* plVar5 = fnF(plVar4, 1);
                    fnB0 = (void (*)(void*, int64_t))
                        VtSlot(plVar5, 0xb0);
                    fnB0(plVar5, nType);
                    plVar5 = fnF(plVar4, 2);
                    auto fnB8 = (void (*)(void*,
                                          int64_t))
                        VtSlot(plVar5, 0xb8);
                    fnB8(plVar5, (int64_t)pnEntry[0]);
                    plVar5 = fnF(plVar4, 3);
                    fnB0 = (void (*)(void*, int64_t))
                        VtSlot(plVar5, 0xb0);
                    fnB0(plVar5, pnEntry[1]);
                    plVar5 = fnF(plVar4, 4);
                    fnB0 = (void (*)(void*, int64_t))
                        VtSlot(plVar5, 0xb0);
                    fnB0(plVar5, pnEntry[2]);
                }
                void* plVar5 =
                    MeedPoolVecByType(pPool, nType);
                MeedVecPush(plVar5, &local_res20);
                uint8_t uVar3;
                {
                    auto fn = (uint8_t (*)(void*,
                                           int64_t))
                        VtSlot(plVar4, 0x50);
                    uVar3 = fn(plVar4, 1);
                }
                uint8_t* puVar6 =
                    MeedSortFlagGet(pPool, nType);
                *puVar6 = 0;
                return uVar3;
            }
        }
    } else {
        g_fnMeedLog();   // Insert Type log
    }
    return 0;
}

// ---------- FUN_14177cbd0: AddMore -------------
bool MeedSetMgrAddMore(void* pPool, void* pMember,
                       int32_t* pnEntry,
                       int nType) {
    if (2 < (uint32_t)(nType - 1)) {
        g_fnMeedLog();   // AddMore Type log
        return false;
    }
    if (pMember == (void*)0) {
        g_fnMeedLog();
        return false;
    }
    // vt+0x10(member, 3) -> field; vt+0x48() -> val
    int iVar2;
    {
        auto fnF = (void* (*)(void*, int64_t))
            VtSlot(pMember, 0x10);
        void* plVar4 = fnF(pMember, 3);
        auto fnV = (int (*)(void*))
            VtSlot(plVar4, 0x48);
        iVar2 = fnV(plVar4) + pnEntry[1];
    }
    int iVar3;
    {
        auto fnF = (void* (*)(void*, int64_t))
            VtSlot(pMember, 0x10);
        void* plVar4 = fnF(pMember, 4);
        auto fnV = (int (*)(void*))
            VtSlot(plVar4, 0x48);
        iVar3 = fnV(plVar4) + pnEntry[2];
    }
    if ((((iVar2 < 0)
          || (g_nMeedMoneyCap <= iVar2))
         || (iVar3 < 0))
        || ((g_nMeedMoneyCap <= iVar3)
            || ((iVar3 < 1 && (iVar2 < 1))))) {
        return false;
    }
    {
        auto fnF = (void* (*)(void*, int64_t))
            VtSlot(pMember, 0x10);
        void* plVar4 = fnF(pMember, 3);
        auto fnS = (void (*)(void*, int64_t))
            VtSlot(plVar4, 0xb0);
        fnS(plVar4, iVar2);
        plVar4 = fnF(pMember, 4);
        fnS = (void (*)(void*, int64_t))
            VtSlot(plVar4, 0xb0);
        fnS(plVar4, iVar3);
    }
    uint8_t* puVar5 = MeedSortFlagGet(pPool, nType);
    *puVar5 = 0;
    char cVar1;
    {
        auto fn = (char (*)(void*, uint64_t))
            VtSlot(pMember, 0x38);
        cVar1 = fn(pMember, 0);
    }
    return cVar1 != '\0';
}

// ---------- FUN_14177db90: SetSynMeed ----------
uint64_t MeedSetMgrSetSynMeed(void* pPool,
                             int32_t* pnEntry,
                             int nType,
                             uint8_t* pOut) {
    if (2 < (uint32_t)(nType - 1)) {
        g_fnMeedLog();   // SetSynMeed Type log
        return 0;
    }
    if ((pnEntry[2] < 1) && (pnEntry[1] < 1)) {
        g_fnMeedLog();   // the 141824ca8 datum
        return 0;
    }
    int iVar1 = pnEntry[0];
    void** plVar7 = (void**)MeedPoolVecByType(
        pPool, nType);
    // (lVar17 = 0 — the "zero" for the null-proxy
    // paths)
    if ((uintptr_t)plVar7[4]
        < (uintptr_t)plVar7[3]) {
        g_fnMeritInvalid();
    }
    if ((nType == 1) || (nType == 3)) {
        // the lazy sort (flag +0x90)
        uint8_t* pf = MeedSortFlagGet(pPool,
                                      nType);
        if (*pf == '\0') {
            MeedSortByType(pPool, nType);
            uint8_t* pf2 = MeedSortFlagGet(pPool,
                                           nType);
            *pf2 = 1;
        }
        void** puVar16 = (void**)plVar7[3];
        if ((void**)plVar7[4] < puVar16) {
            g_fnMeritInvalid();
        }
        void** plVar12 = (void**)*plVar7;
        void** puVar4 = (void**)plVar7[4];
        // the ORIGINAL checks the TOP element only
        // (the vector is sorted desc): if the top
        // IS the user (or the vector is EMPTY) ->
        // *param_4 = 1; if not -> the overflow
        // comparison decides, then goto LAB.
        // (The debug iterator dance collapses in
        // the port.)
        if (puVar16 != puVar4) {
            bool bVar5 = MeedIsMemberUser(
                (void*)*puVar16,
                (uint32_t)iVar1);
            if (!bVar5) {
                // not the user: GetSynMeed for the
                // sums + the overflow check
                int local_b4 = 0;
                int64_t local_b0 = 0;
                MeedPoolGetSynMeed(
                    pPool, (int*)&local_b0,
                    &local_b4, (uint32_t)iVar1,
                    nType);
                int iVar2 = pnEntry[2];
                int64_t lVar10 = local_b4;
                int iVar3 = pnEntry[1];
                int64_t lVar11 =
                    (int64_t)(int32_t)
                        local_b0;
                // the top member's score:
                // sub4@0x58*50000 + sub3@0x58
                void* pM = (void*)*puVar16;
                void* local_b0f;
                {
                    auto fnF = (void* (*)(
                        void*, int64_t))
                        VtSlot(pM, 0x10);
                    local_b0f = fnF(pM, 4);
                }
                void* plVar12b;
                {
                    auto fnF = (void* (*)(
                        void*, int64_t))
                        VtSlot(pM, 0x10);
                    plVar12b = fnF(pM, 3);
                }
                int64_t lVar13;
                {
                    auto fn = (int64_t (*)(void*))
                        VtSlot(local_b0f, 0x58);
                    lVar13 = fn(local_b0f);
                }
                int64_t lVar14;
                {
                    auto fn = (int64_t (*)(void*))
                        VtSlot(plVar12b, 0x58);
                    lVar14 = fn(plVar12b);
                }
                if (lVar14 + lVar13 * 50000
                    < (iVar2 + lVar10) * 50000
                          + (int64_t)iVar3
                          + lVar11) {
                    *pOut = 1;
                }
                goto LAB_14177de1e;
            }
        }
        *pOut = 1;
    }
LAB_14177de1e:;
    // the rescan walk: find the member by id
    void** puVar16 = (void**)plVar7[3];
    void** plVar12 = (void**)*plVar7;
    while (true) {
        void** puVar4 = (void**)plVar7[4];
        if (puVar4 < (void**)plVar7[3]) {
            g_fnMeritInvalid();
        }
        if (puVar4 == puVar16) break;
        if (*(void**)puVar16 != (void*)0
            && MeedIsMemberUser(
                    *(void**)puVar16,
                    (uint32_t)iVar1)) {
            break;
        }
        puVar16 = puVar16 + 1;
    }
    uint8_t uVar6;
    void** puVar4 = (void**)plVar7[4];
    if (puVar4 == puVar16) {
        // no member found: Insert
        uVar6 = MeedSetMgrInsert(pPool, pnEntry,
                                 nType);
    } else {
        if (*(void**)puVar16 == (void*)0) {
            g_fnMeedLog();   // SetSynMeed idSyn log
            return 0;
        }
        uVar6 = (uint8_t)MeedSetMgrAddMore(
            pPool, *(void**)puVar16, pnEntry,
            nType);
    }
    return uVar6;   // CONCAT71(uVar15, uVar6)
}

// ---------- FUN_141780cb0: SetArenicMeed --------
uint64_t MeedSetArenic(void* pUser, uint32_t uId,
                      int nType, int nMoney,
                      int nEmoney, uint16_t uP6) {
    uint32_t local_c98 = uId;   // the saved id
    void* local_c90 = pUser;    // the saved user
    uint8_t local_ca8 = 0;      // the success flag
    uint64_t uVar10 = 0;

    if (2 < (uint32_t)(nType - 1)) {
        g_fnMeedLog();   // SetArenicMeed Type log
        return 0;
    }
    void* plVar5 = LeagueSingleton();
    // vt+0x78(mgr, id) — the gate
    uint64_t uVar6;
    {
        auto fn = (uint64_t (*)(void*, uint32_t))
            VtSlot(plVar5, 0x78);
        uVar6 = fn(plVar5, uId);
    }
    if ((char)uVar6 == '\0') {
        return uVar6;
    }
    int local_ca0 = 0;
    int iVar4 = 0;
    if (nType == 3) {
        // the type-3 gates
        void* pObj = *(void**)pUser;
        int uVar3 = g_fnMeedReqId(plVar5);
        {
            auto fn = (int (*)(void*, int,
                              int*))
                VtSlot(pObj, 0x388);
            iVar4 = fn(pObj, uVar3, &local_ca0);
        }
        char buf1[0x400];
        if (local_ca0 == 1) {
            char* pcVar8 = MeedPromptGet(
                local_c90, 3, -1);
            // (the ERROR1 key comes from the
            // GetStrObject 0 path — the original
            // looks it up directly; verbatim via
            // the seam)
            pcVar8 = StrOf(
                "STR_VLM_ARENIC_MEED_ERROR1");
            g_fnMeedSnprintf(buf1, 0x400, pcVar8);
            void* pU = *(void**)local_c90;
            auto fn = (uint64_t (*)(void*,
                                    uint32_t,
                                    char*))
                VtSlot(pU, 0x18);
            uint64_t r = fn(pU, uId, buf1);
            return r & 0xffffffffffffff00ULL;
        }
        if (local_ca0 == 2) {
            char* pcVar8 = StrOf(
                "STR_VLM_ARENIC_MEED_ERROR2");
            g_fnMeedSnprintf(buf1, 0x400, pcVar8);
            void* pU = *(void**)local_c90;
            auto fn = (uint64_t (*)(void*,
                                    uint32_t,
                                    char*))
                VtSlot(pU, 0x18);
            uint64_t r = fn(pU, uId, buf1);
            return r & 0xffffffffffffff00ULL;
        }
        // vt+0x390 (the args dropped by Ghidra)
        {
            void* pU = *(void**)local_c90;
            auto fn = (char (*)(void*))
                VtSlot(pU, 0x390);
            uVar6 = (uint64_t)(uint8_t)fn(pU);
        }
        if ((char)uVar6 != '\0') {
            char* pcVar8 = StrOf(
                "STR_CROSS_VLM_ARENIC_MEED_ERROR");
            g_fnMeedSnprintf(buf1, 0x400, pcVar8);
            void* pU = *(void**)local_c90;
            auto fn = (uint64_t (*)(void*,
                                    uint32_t,
                                    char*))
                VtSlot(pU, 0x18);
            uint64_t r = fn(pU, uId, buf1);
            return r & 0xffffffffffffff00ULL;
        }
        if (((local_ca0 != 0) || (iVar4 < 0))
            || (2 < iVar4)) {
            return uVar6 & 0xffffffffffffff00ULL;
        }
    }
    // the money gates
    if (((nMoney < 0) || (nEmoney < 0))
        || ((nMoney == 0 && (nEmoney == 0)))) {
        return uVar6 & 0xffffffffffffff00ULL;
    }
    iVar4 = g_fnMeedReqId(plVar5);
    local_ca0 = iVar4;
    {
        auto fn = (uint64_t (*)(void*, int))
            VtSlot(plVar5, 0x268);
        uVar6 = fn(plVar5, iVar4);
    }
    if ((int64_t)uVar6 < (int64_t)nMoney) {
        return uVar6 & 0xffffffffffffff00ULL;
    }
    {
        auto fn = (uint64_t (*)(void*, int))
            VtSlot(plVar5, 0x278);
        uVar6 = fn(plVar5, iVar4);
    }
    if ((int)uVar6 < nEmoney) {
        return uVar6 & 0xffffffffffffff00ULL;
    }
    void* pvVar9 = MeedPoolGet();
    int local_c9c = 0;
    int local_ca4 = 0;
    void* local_c78 = pvVar9;
    MeedPoolGetSynMeed(pvVar9, &local_c9c,
                       &local_ca4, (uint32_t)iVar4,
                       nType);
    uVar6 = MeedApplyBounds(
        nMoney + local_c9c, local_ca4 + nEmoney);
    if ((char)uVar6 == '\0') {
        return uVar6;
    }
    local_ca8 = 0;
    if ((local_ca4 == 0) && (local_c9c == 0)) {
        // ---- the fresh path ----
        if (((0 < nMoney) && (nMoney < 100))
            || ((uint32_t)(nEmoney - 1) < 99)) {
            return ((uint64_t)(uint32_t)
                        (nEmoney - 1))
                   & 0xffffffffffffff00ULL;
        }
        char buf2[0x400];
        memset(buf2, 0, 0x3ff);
        buf2[0] = '\0';
        char cVar2;
        {
            auto fn = (char (*)(void*, int,
                                int64_t))
                VtSlot(plVar5, 0x1f0);
            cVar2 = fn(plVar5, iVar4,
                       -(int64_t)nMoney);
        }
        if (cVar2 == '\0') {
            cVar2 = 0;
        }
        if (cVar2 == '\0') {
            {
                auto fn = (char (*)(void*, int))
                    VtSlot(plVar5, 0x1f8);
                cVar2 = fn(plVar5, iVar4);
            }
        }
        if (cVar2 == '\0') {
            g_fnMeedLog();   // OnSynMoneyChange err
            uVar10 = 0;
            goto LAB_141781475;
        }
        if (0 < nEmoney) {
            void* pObj = *(void**)local_c90;
            uint64_t uE = MeedEmonyType(
                local_c90, nType, 0);
            auto fn = (void (*)(void*, uint64_t,
                               int, int))
                VtSlot(pObj, 0x350);
            fn(pObj, (uint32_t)uE, iVar4, 0);
            pvVar9 = local_c78;
        }
        // the entry {id, money, emoney} — CONTIGUOUS
        // in the original stack (local_c90/c88);
        // an array guarantees it
        int local_c90e[3] = { iVar4, nMoney,
                              nEmoney };
        uint8_t local_ca7 = 0;
        uVar6 = MeedSetMgrSetSynMeed(
            pvVar9, local_c90e, nType,
            &local_ca7);
        if ((char)uVar6 == '\0') {
            g_fnMeedLog();   // the 141824ca8 datum
        }
        if (((nType == 1) || (nType == 3))
            && (local_ca7 != '\0')) {
            {
                auto fn = (void (*)(void*, int))
                    VtSlot(plVar5, 0x290);
                fn(plVar5, iVar4);
            }
            char* pcVar8 = MeedPromptGet(
                local_c90, nType, 6);
            g_fnMeedSnprintf(buf2, 0x400, pcVar8);
            void* pU = *(void**)local_c90;
            auto fn = (void (*)(void*, char*))
                VtSlot(pU, 200);   // 0xc8!
            fn(pU, buf2);
        }
        {
            const char* pcVar8 = MeedGmLogName(
                nType, 1);
            g_fnMeedLogSave(pcVar8,
                            g_szMeedLogFmtFresh,
                            local_c98);
        }
        char* pcVar8 = MeedPromptGet(
            local_c90, nType, 1);
        g_fnMeedSnprintf(buf2, 0x400, pcVar8);
        {
            auto fn = (void (*)(void*, int,
                                char*, int))
                VtSlot(plVar5, 0x40);
            fn(plVar5, iVar4, buf2, 0);
        }
    } else {
        // ---- the existing path ----
        uint64_t msg[0x86];   // the CMsg buffer
        memset(msg, 0, sizeof msg);
        char cVar2;
        {
            auto fn = (char (*)(void*, int,
                                int64_t))
                VtSlot(plVar5, 0x1f0);
            cVar2 = fn(plVar5, iVar4,
                       -(int64_t)nMoney);
        }
        if (cVar2 == '\0') {
            {
                auto fn = (char (*)(void*, int))
                    VtSlot(plVar5, 0x1f8);
                cVar2 = fn(plVar5, iVar4);
            }
        }
        if (cVar2 == '\0') {
            g_fnMeedLog();
            uVar10 = 0;
            goto LAB_141781475;
        }
        if (0 < nEmoney) {
            void* pObj = *(void**)local_c90;
            uint64_t uE = MeedEmonyType(
                local_c90, nType, 0);
            auto fn = (void (*)(void*, uint64_t,
                               int, int))
                VtSlot(pObj, 0x350);
            fn(pObj, (uint32_t)uE, iVar4, 0);
            pvVar9 = local_c78;
        }
        // the entry at local_c70: {id, money,
        // emoney} — CONTIGUOUS in the original stack
        // (local_c70/c6c/c68); an array guarantees it
        int local_c70[3] = { iVar4, nMoney,
                             nEmoney };
        int local_ca6 = 0;
        uVar6 = MeedSetMgrSetSynMeed(
            pvVar9, local_c70, nType,
            (uint8_t*)&local_ca6);
        if ((char)uVar6 == '\0') {
            g_fnMeedLog();
        }
        if (((nType == 1) || (nType == 3))
            && (local_ca6 != 0)) {
            {
                auto fn = (void (*)(void*, int))
                    VtSlot(plVar5, 0x290);
                fn(plVar5, local_ca0);
            }
            char* pcVar8 = MeedPromptGet(
                local_c90, nType, 6);
            g_fnMeedSnprintf((char*)msg, 0x400,
                            pcVar8);
            void* pU = *(void**)local_c90;
            auto fn = (void (*)(void*, char*))
                VtSlot(pU, 200);
            fn(pU, (char*)msg);
            iVar4 = local_ca0;
        }
        {
            const char* pcVar8 = MeedGmLogName(
                nType, 1);
            g_fnMeedLogSave(pcVar8,
                            g_szMeedLogFmtMore,
                            local_c98);
        }
        char* pcVar8 = MeedPromptGet(
            local_c90, nType, 2);
        g_fnMeedSnprintf((char*)msg, 0x400,
                         pcVar8);
        {
            auto fn = (void (*)(void*, int,
                                char*, int))
                VtSlot(plVar5, 0x40);
            fn(plVar5, iVar4, (char*)msg, 0);
        }
        // (the CMsg buffer doubles as the final
        // award-rank msg — see the tail)
        local_ca8 = 1;
        CMsgMemAwardRankCtor(msg);
        uVar10 = CMsgAwardRankEncode(
            msg, uP6, (uint32_t)nType,
            (int64_t)(nMoney + local_c9c),
            (uint32_t)(local_ca4 + nEmoney));
        if ((char)uVar10 == '\0') {
            g_fnMeedLog();
            CMsgMemAwardRankDtor(msg);
            return uVar10 & 0xffffffffffffff00ULL;
        }
        {
            void* pU = *(void**)local_c90;
            auto fn = (void (*)(void*, uint32_t,
                                void*))
                VtSlot(pU, 0x08);
            fn(pU, local_c98, msg);
        }
        if (nType == 3) {
            void* pU = *(void**)local_c90;
            auto fn = (void (*)(void*, int,
                                int, int))
                VtSlot(pU, 0x398);
            fn(pU, iVar4, nMoney + local_c9c,
               local_ca4 + nEmoney);
        }
        CMsgMemAwardRankDtor(msg);
        goto LAB_141781475_v2;
    }
    // (the fresh path shares the tail — the CMsg
    // buffer was NOT zeroed there; the ctor does it)
    {
        uint64_t msg[0x86];
        local_ca8 = 1;
        CMsgMemAwardRankCtor(msg);
        uVar10 = CMsgAwardRankEncode(
            msg, uP6, (uint32_t)nType,
            (int64_t)(nMoney + local_c9c),
            (uint32_t)(local_ca4 + nEmoney));
        if ((char)uVar10 == '\0') {
            g_fnMeedLog();
            CMsgMemAwardRankDtor(msg);
            return uVar10 & 0xffffffffffffff00ULL;
        }
        {
            void* pU = *(void**)local_c90;
            auto fn = (void (*)(void*, uint32_t,
                                void*))
                VtSlot(pU, 0x08);
            fn(pU, local_c98, msg);
        }
        if (nType == 3) {
            void* pU = *(void**)local_c90;
            auto fn = (void (*)(void*, int,
                                int, int))
                VtSlot(pU, 0x398);
            fn(pU, iVar4, nMoney + local_c9c,
               local_ca4 + nEmoney);
        }
        CMsgMemAwardRankDtor(msg);
    }
LAB_141781475_v2:
LAB_141781475:
    return (uVar10 & 0xffffffffffffff00ULL)
           | local_ca8;
}

}  // namespace syndicate

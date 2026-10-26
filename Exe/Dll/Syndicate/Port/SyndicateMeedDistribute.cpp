// SyndicateMeedDistribute — D55b/T16 port.
// Verbatim from Syndicate.dll.decompiled.c
// (v6159). Every address is kept in a comment at
// the function it came from.
#include "Exe/Dll/Syndicate/Port/SyndicateMeedDistribute.h"

#include <cstring>
#include <cmath>

#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"   // g_fnGetGameMgr, g_fnMeritOpNew, g_fnMeritOpDelete, g_fnMeritInvalid, g_fnMeedLog, MeritSingleton
#include "Exe/Dll/Syndicate/Port/SyndicateMeedEntry.h"    // D55a
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"     // MeedPoolGet, g_fnMeedListFill
#include "Exe/Dll/Syndicate/Port/SyndicateMeedEnd.h"      // MeedDeleteSynMeed
#include "Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"       // MeedSingletonGet, MeedUserLeague, g_fnMeedLog, MeedPostGrade
#include "Exe/Dll/Syndicate/Port/SyndicateMeedApply.h"     // MeedGmLogName, MeedPromptGet, g_fnMeedLogSave, g_fnMeedSnprintf, g_fnMeedInstGet, g_fnMeedStrInst, g_fnMeedStrGet, MeedVecPush
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"     // LeagueMemberLookup

namespace syndicate {

// ---------- the seams ----------
int (*g_fnMeedScorer0)(void* pThis, uint64_t uSyn,
                       uint32_t uUser);
int (*g_fnMeedScorer2)(void* pThis, uint64_t uSyn,
                       uint32_t uUser);
int (*g_fnMeedCrossPoint)(void* pCross, uint64_t uSyn,
                          uint32_t uUser);
uint32_t (*g_fnMeedRandGet)(int n);
uint64_t (*g_fnMeedTimeGet)(int n);
void (*g_fnMeedAwardOnline)(void* pThis,
    uint32_t uUser, int nType, int nPoint,
    int nMoney, int nEmoney);

static inline void* VtSlot(void* pObj, size_t uOff) {
    return *(void**)(*(char**)pObj + uOff);
}

// ---------- FUN_1417800b0 @ 1417800b0 ----------
uint64_t MeedTypeByCompeteGet(void* pThis,
                              uint32_t uType) {
    (void)pThis;
    if (uType < 4) {
        if ((int)uType < 2) {
            return 2;
        }
        if (uType == 2) {
            return 1;
        }
        if (uType == 3) {
            return 3;
        }
    } else {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::GetMeedTypeByCompeteType,
        //  Type[%d] is not found!"
        g_fnMeedLog();
    }
    return 0;
}

// ---------- FUN_1417ae630 @ 1417ae630 ----------
int64_t SynMemberFind(void* pMgr, uint32_t uId) {
    // FUN_1417cad00(*(mgr+0x10), id)
    void* pInner =
        *(void**)((char*)pMgr + 0x10);
    return LeagueMemberLookup(pInner, uId);
}

// ---------- FUN_141781b10 @ 141781b10 ----------
uint32_t MeedRandomMemberPick(
    void* pThis, void* pVecIds) {
    (void)pThis;
    char* pcVec = (char*)pVecIds;
    int64_t lBegin =
        *(int64_t*)(pcVec + 0x18);
    int64_t lEnd =
        *(int64_t*)(pcVec + 0x20);
    // tq::RandGet(count - 1) with count =
    // (end - begin) >> 2
    uint32_t uVar1 = g_fnMeedRandGet(
        (int)((lEnd - lBegin) >> 2) - 1);
    if ((uint64_t)uVar1
        < (uint64_t)((lEnd - lBegin) >> 2)) {
        return *(uint32_t*)(
            lBegin + (uint64_t)uVar1 * 4);
    }
    return 0;
}

// ---------- FUN_14177f250 @ 14177f250 ----------
// the DAT_141886d50 lazy singleton
static void* s_pUserMgr;  // DAT_141886d50

void MeedUserMgrReset() { s_pUserMgr = nullptr; }

void* MeedUserMgrGet() {
    if (s_pUserMgr == (void*)0) {
        s_pUserMgr = g_fnMeritOpNew(8);
        if (s_pUserMgr == (void*)0) {
            s_pUserMgr = (void*)0;
        } else {
            *(uint64_t*)s_pUserMgr = 0;
        }
        if (s_pUserMgr == (void*)0) {
            g_fnMeedLog();  // datum 141824ca8
        }
    }
    return s_pUserMgr;
}

// ---------- FUN_14177fa90 @ 14177fa90 ----------
void* MeedPointScorerGet(void* pThis, int nType) {
    (void)pThis;
    // the table: 0 -> LAB_14177fa40 (a thunk —
    // seam), 1 -> FUN_14177fa10 (MeedPostGrade),
    // 2 -> LAB_14177fa50 (a thunk — seam),
    // 3 -> FUN_14177fa60 (MeedCrossScorer)
    if (nType == 0) {
        return (void*)g_fnMeedScorer0;
    }
    if (nType == 1) {
        return (void*)&MeedPostGrade;
    }
    if (nType == 2) {
        return (void*)g_fnMeedScorer2;
    }
    if (nType == 3) {
        return (void*)&MeedCrossScorer;
    }
    return (void*)0;
}

// ---------- FUN_14177fa60 @ 14177fa60 ----------
int MeedCrossScorer(void* pThis, uint64_t uSyn,
                    uint32_t uUser) {
    (void)pThis;
    // FUN_14173f9c0() (MeriSingleton — ported)
    // then FUN_14173d820(cross, uSyn, uUser)
    void* puVar1 = MeritSingleton();
    // fa10's upgraded signature RETURNS the point
    // (Ghidra dropped it; the 49f0 call site reads
    // the scorer's return as the user's points)
    return g_fnMeedCrossPoint(puVar1, uSyn,
                             uUser);
}

// ---------- FUN_141779b60 @ 141779b60 ----------
// (the league, the meed type, the 5-int entry)
uint64_t MeedRecordInsert(void* pLeague,
                          int nType, void* pEntry) {
    if ((uint32_t)(nType - 1) < 3) {
        void* plVar1 = g_fnMeedInstGet();
        {
            auto fn = (void* (*)(
                void*, const char*))
                VtSlot(plVar1, 0x20);
            plVar1 = fn(plVar1,
                        "cq_meedrecord");
        }
        void* local_res20 = plVar1;
        if (plVar1 != (void*)0) {
            // field 1 = entry[0] (vt+0xb8)
            {
                auto fnF = (void* (*)(
                    void*, int64_t))
                    VtSlot(plVar1, 0x10);
                void* plVar2 = fnF(plVar1, 1);
                auto fnW = (void (*)(void*,
                    uint32_t))
                    VtSlot(plVar2, 0xb8);
                fnW(plVar2,
                    *(uint32_t*)pEntry);
            }
            // field 3 = the type (vt+0xb0)
            {
                auto fnF = (void* (*)(
                    void*, int64_t))
                    VtSlot(plVar1, 0x10);
                void* plVar2 = fnF(plVar1, 3);
                auto fnW = (void (*)(void*,
                    int))
                    VtSlot(plVar2, 0xb0);
                fnW(plVar2, nType);
            }
            // field 2 = entry[1] (the user)
            {
                auto fnF = (void* (*)(
                    void*, int64_t))
                    VtSlot(plVar1, 0x10);
                void* plVar2 = fnF(plVar1, 2);
                auto fnW = (void (*)(void*,
                    uint32_t))
                    VtSlot(plVar2, 0xb8);
                fnW(plVar2,
                    *(uint32_t*)((char*)
                        pEntry + 4));
            }
            // field 4 = entry[2] (the point)
            {
                auto fnF = (void* (*)(
                    void*, int64_t))
                    VtSlot(plVar1, 0x10);
                void* plVar2 = fnF(plVar1, 4);
                auto fnW = (void (*)(void*,
                    int))
                    VtSlot(plVar2, 0xb0);
                fnW(plVar2,
                    *(uint32_t*)((char*)
                        pEntry + 8));
            }
            // field 5 = entry[3] (the money)
            {
                auto fnF = (void* (*)(
                    void*, int64_t))
                    VtSlot(plVar1, 0x10);
                void* plVar2 = fnF(plVar1, 5);
                auto fnW = (void (*)(void*,
                    int))
                    VtSlot(plVar2, 0xb0);
                fnW(plVar2,
                    *(uint32_t*)((char*)
                        pEntry + 0xc));
            }
            // field 6 = entry[4] (the emoney)
            {
                auto fnF = (void* (*)(
                    void*, int64_t))
                    VtSlot(plVar1, 0x10);
                void* plVar2 = fnF(plVar1, 6);
                auto fnW = (void (*)(void*,
                    int))
                    VtSlot(plVar2, 0xb0);
                fnW(plVar2,
                    *(uint32_t*)((char*)
                        pEntry + 0x10));
            }
            // vt+0x50(table, 0)
            {
                auto fn = (void (*)(void*,
                    int))
                    VtSlot(plVar1, 0x50);
                fn(plVar1, 0);
            }
            // FUN_141732200(league+8, &the-record)
            MeedVecPush((char*)pLeague + 8,
                        &local_res20);
            // the byte at league+0x38 = 0
            *(uint8_t*)((char*)pLeague + 0x38)
                = 0;
        } else {
            g_fnMeedLog();  // datum 141824ca8
        }
        return (uint64_t)(plVar1 != (void*)0);
    }
    // log_InlineLogERROR(literal):
    // "CMeedRecord::Insert(), Type[%d] is not
    //  found!"
    g_fnMeedLog();
    return 0;
}

// ---------- FUN_14177f0d0 @ 14177f0d0 ----------
uint8_t MeedRecordUserPoint(void* pMgr,
    uint32_t uUser, int nType, int nMoney,
    int nEmoney) {
    if ((uint32_t)(nType - 1) < 3) {
        if ((nEmoney < 0) || (nMoney < 0)) {
            return 0;
        }
        if ((nEmoney == 0) && (nMoney == 0)) {
            return 1;
        }
        void* plVar2 = g_fnMeedInstGet();
        {
            auto fn = (void* (*)(
                void*, const char*))
                VtSlot(plVar2, 0x20);
            plVar2 = fn(plVar2,
                        "cq_pointrecord");
        }
        if (plVar2 == (void*)0) {
            g_fnMeedLog();  // datum 141824ca8
            return 0;
        }
        // field 1 = the user (vt+0xb8)
        {
            auto fnF = (void* (*)(
                void*, int64_t))
                VtSlot(plVar2, 0x10);
            void* plVar3 = fnF(plVar2, 1);
            auto fnW = (void (*)(void*,
                uint32_t))
                VtSlot(plVar3, 0xb8);
            fnW(plVar3, uUser);
        }
        // field 4 = the type (vt+0xb0)
        {
            auto fnF = (void* (*)(
                void*, int64_t))
                VtSlot(plVar2, 0x10);
            void* plVar3 = fnF(plVar2, 4);
            auto fnW = (void (*)(void*,
                int))
                VtSlot(plVar3, 0xb0);
            fnW(plVar3, nType);
        }
        // field 2 = the money (vt+0xb0)
        {
            auto fnF = (void* (*)(
                void*, int64_t))
                VtSlot(plVar2, 0x10);
            void* plVar3 = fnF(plVar2, 2);
            auto fnW = (void (*)(void*,
                int))
                VtSlot(plVar3, 0xb0);
            fnW(plVar3, nMoney);
        }
        // field 3 = the emoney (vt+0xb0)
        {
            auto fnF = (void* (*)(
                void*, int64_t))
                VtSlot(plVar2, 0x10);
            void* plVar3 = fnF(plVar2, 3);
            auto fnW = (void (*)(void*,
                int))
                VtSlot(plVar3, 0xb0);
            fnW(plVar3, nEmoney);
        }
        // vt+0x50(table, emoney != 0)
        uint8_t uVar1;
        {
            auto fn = (uint8_t (*)(void*,
                int))
                VtSlot(plVar2, 0x50);
            uVar1 = fn(plVar2, nEmoney != 0);
        }
        // vt+0(table, 1) — the FIRST vtable slot
        {
            auto fn = (void (*)(void*,
                int))
                VtSlot(plVar2, 0x0);
            fn(plVar2, 1);
        }
        return uVar1;
    }
    // log_InlineLogERROR(literal):
    // "CPointRecordMgr::RecordUserPoint,
    //  Type[%d] is not found!"
    g_fnMeedLog();
    return 0;
}

// ---------- FUN_1417849f0 @ 1417849f0 ----------
uint64_t MeedCollectPoint(void* pThis,
    uint32_t uIdSyn, void* pVecEntries,
    int* pnTotal, int* pnMaxUser, int* pnMaxPoint,
    uint32_t uType, void* pVecIds) {
    if (3 < uType) {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::CollectPoint, Type[%d]
        //  is not found!"
        g_fnMeedLog();
        return 0;  // & 0xff..00
    }
    if (((pnTotal != (int*)0)
            && (pnMaxPoint != (int*)0))
        && (pnMaxUser != (int*)0)) {
        char* pcIds = (char*)pVecIds;
        void* pcVar4 = MeedPointScorerGet(
            pThis, (int)uType);
        if (pcVar4 == (void*)0) {
            g_fnMeedLog();  // datum 141824ca8
            return 0;
        }
        int iVar9 = 0;
        uint32_t uVar10 = 0;
        int iVar8 = 0;
        MeedEntryVecEraseTail(pVecEntries);
        char* pcEntries = (char*)pVecEntries;
        uint32_t* puVar5 = *(uint32_t**)(
            pcIds + 0x18);
        void* plVar6 = *(void**)pcIds;  // proxy
        while (true) {
            uint32_t* puVar2 = *(uint32_t**)(
                pcIds + 0x20);
            if (puVar2 < puVar5) {
                g_fnMeritInvalid();
            }
            if ((*(void**)pcIds == (void*)0)
                || (*(void**)pcIds != plVar6)) {
                g_fnMeritInvalid();
            }
            if (puVar2 == puVar5) break;
            if (plVar6 == (void*)0) {
                g_fnMeritInvalid();
            }
            // (the debug gate: the proxy's
            //  last >= the iterator)
            {
                int64_t lVar7 =
                    *(int64_t*)plVar6;
                if (*(void**)(lVar7 + 0x20)
                        <= (void*)puVar5) {
                    g_fnMeritInvalid();
                }
            }
            uint32_t uVar1 = *puVar5;
            // the scorer: (this, syn, user)
            int iVar3 =
                ((int (*)(void*, uint64_t,
                    uint32_t))pcVar4)(
                        pThis, uIdSyn, uVar1);
            if (0 < iVar3) {
                iVar9 = iVar9 + iVar3;
                // the entry at &local_60:
                // {0, id, point, 0, 0}
                int local_60[5];
                local_60[0] = 0;
                local_60[3] = 0;
                local_60[4] = 0;
                local_60[1] = (int)uVar1;
                local_60[2] = iVar3;
                MeedEntryVecPush(pVecEntries,
                    (const MeedEntry5*)local_60);
                if (iVar8 < iVar3) {
                    uVar10 = uVar1;
                    iVar8 = iVar3;
                }
            }
            {
                int64_t lVar7 =
                    *(int64_t*)plVar6;
                if (*(void**)(lVar7 + 0x20)
                        <= (void*)puVar5) {
                    g_fnMeritInvalid();
                }
            }
            puVar5 = puVar5 + 1;
        }
        *pnMaxUser = (int)uVar10;
        *pnMaxPoint = iVar8;
        *pnTotal = iVar9;
        (void)pcEntries;
        return 1;
    }
    g_fnMeedLog();  // datum 141824ca8
    return 0;
}

// ---------- FUN_141784c50 @ 141784c50 ----------
uint64_t MeedCollectAward(void* pThis,
    int nMeedType, void* pVecEntries, int nTotal,
    int nMoneyPot, int nEmoneyPot) {
    if (2 < (uint32_t)(nMeedType - 1)) {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::CollectAward, Type[%d]
        //  is not found!"
        g_fnMeedLog();
        return 0;  // & 0xff..00
    }
    if (nMeedType == 1) {
        // LAB_141784c87: FUN_1417846e0
        return MeedCollectAward13(
            pThis, pVecEntries, nTotal,
            nMoneyPot, nEmoneyPot);
    }
    if (nMeedType != 2) {
        if (nMeedType != 3) {
            // LAB_141784cbe — the unreachable
            // truncation fall-through (Ghidra
            // noise for the 0 return)
            return 0;
        }
        // LAB_141784c87: FUN_1417846e0
        return MeedCollectAward13(
            pThis, pVecEntries, nTotal,
            nMoneyPot, nEmoneyPot);
    }
    return MeedCollectAward2(
        pThis, pVecEntries, nTotal, nMoneyPot,
        nEmoneyPot);
}

// ---------- FUN_1417846e0 @ 1417846e0 ----------
uint64_t MeedCollectAward13(void* pThis,
    void* pVec, int nTotal, int nMoneyPot,
    int nEmoneyPot) {
    (void)pThis;
    char* pcVec = (char*)pVec;
    void* pProxy = *(void**)pcVec;
    // param_2[4] = the END (+0x20) — the decompile
    // read param_2[4], not the cap
    uint64_t uVar4 = *(uint64_t*)(pcVec + 0x20);
    if (uVar4
        < (uint64_t)*(uint64_t*)(pcVec + 0x18)) {
        g_fnMeritInvalid();
    }
    // the sort pair: first = {proxy, begin},
    // last = {proxy, end} (the decompile's
    // local_78/local_88 slots)
    int64_t local_78[2] = {
        (int64_t)pProxy,
        *(int64_t*)(pcVec + 0x18)};
    int64_t local_88[2] = {
        (int64_t)pProxy, (int64_t)uVar4};
    MeedEntrySort(
        (void**)local_78, (void**)local_88,
        g_fnMeedEntryCmp);
    uint64_t uVar4c =
        *(uint64_t*)(pcVec + 0x18);
    void* plVar2 = *(void**)pcVec;
    int iVar5 = nEmoneyPot;
    while (true) {
        uint64_t uVar1 = *(uint64_t*)(
            pcVec + 0x20);
        if (uVar1 < uVar4c) {
            g_fnMeritInvalid();
        }
        if ((*(void**)pcVec == (void*)0)
            || (*(void**)pcVec != plVar2)) {
            g_fnMeritInvalid();
        }
        if (uVar1 == uVar4c) break;
        {
            int64_t lVar6 = *(int64_t*)plVar2;
            if (*(uint64_t*)(lVar6 + 0x20)
                    <= uVar4c) {
                g_fnMeritInvalid();
            }
        }
        char* pcEntry = (char*)uVar4c;
        int iVar7 = *(int*)(pcEntry + 8);
        // ceil((double)(emoneyPot * point)
        //      / (double)total)
        double dVar8 = std::ceil(
            (double)((int64_t)nEmoneyPot
                * (int64_t)iVar7)
            / (double)nTotal);
        int iVar3 = (int)dVar8;
        iVar7 = (int)(((int64_t)nMoneyPot
            * (int64_t)iVar7) / (int64_t)nTotal);
        int local_b8;
        if ((0 < iVar7) || (0 < iVar3)) {
            if (iVar5 < iVar3) {
                local_b8 = 0;
            } else {
                local_b8 = iVar5 - iVar3;
                iVar5 = iVar3;
            }
            *(int*)(pcEntry + 0xc) = iVar7;
            *(int*)(pcEntry + 0x10) = iVar5;
            iVar5 = local_b8;
        }
        {
            int64_t lVar6 = *(int64_t*)plVar2;
            if (*(uint64_t*)(lVar6 + 0x20)
                    <= uVar4c) {
                g_fnMeritInvalid();
            }
        }
        uVar4c = uVar4c + 0x14;
    }
    return (uint64_t)(iVar5 < 1);
}

// ---------- FUN_1417842d0 @ 1417842d0 ----------
uint64_t MeedCollectAward2(void* pThis,
    void* pVec, int nTotal, int nMoneyPot,
    int nEmoneyPot) {
    (void)pThis;
    char* pcVec = (char*)pVec;
    uint64_t uVar6 = *(uint64_t*)(pcVec + 0x18);
    if (*(uint64_t*)(pcVec + 0x20) < uVar6) {
        g_fnMeritInvalid();
    }
    void* plVar1 = *(void**)pcVec;
    int iVar9 = nEmoneyPot;
    // ---- pass 1: the floor shares ----
    while (true) {
        uint64_t uVar2 = *(uint64_t*)(
            pcVec + 0x20);
        if (uVar2 < uVar6) {
            g_fnMeritInvalid();
        }
        void* plVar5 = *(void**)pcVec;
        if ((plVar5 == (void*)0)
            || (plVar5 != plVar1)) {
            g_fnMeritInvalid();
        }
        if (uVar2 == uVar6) break;
        {
            int64_t lVar8 = *(int64_t*)plVar1;
            if (*(uint64_t*)(lVar8 + 0x20)
                    <= uVar6) {
                g_fnMeritInvalid();
            }
        }
        char* pcEntry = (char*)uVar6;
        int iVar7 = (int)(((int64_t)nMoneyPot
            * (int64_t)*(int*)(pcEntry + 8))
            / (int64_t)nTotal);
        int iVar4 = (int)(((int64_t)nEmoneyPot
            * (int64_t)*(int*)(pcEntry + 8))
            / (int64_t)nTotal);
        if ((0 < iVar7) || (0 < iVar4)) {
            iVar9 = iVar9 - iVar4;
            *(int*)(pcEntry + 0xc) = iVar7;
            *(int*)(pcEntry + 0x10) = iVar4;
        }
        {
            int64_t lVar8 = *(int64_t*)plVar1;
            if (*(uint64_t*)(lVar8 + 0x20)
                    <= uVar6) {
                g_fnMeritInvalid();
            }
        }
        uVar6 = uVar6 + 0x14;
    }
    if (iVar9 < 1) {
        return 1;
    }
    // ---- pass 2: the per-entry spread ----
    uint64_t uVar6b = *(uint64_t*)(pcVec + 0x20);
    uint64_t uVar2 = ((uint64_t)uVar6b
        - *(uint64_t*)(pcVec + 0x18)) / 0x14;
    if (uVar2 == 0) {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::CollectAwardSyn.
        //  rVecAward.size() <= 0"
        g_fnMeedLog();
        return 0;
    }
    int iVar4 = (int)((uint64_t)(int64_t)iVar9
        / uVar2);
    if (0 < iVar4) {
        uint64_t uVar6c =
            *(uint64_t*)(pcVec + 0x18);
        if (*(uint64_t*)(pcVec + 0x20)
            < uVar6c) {
            g_fnMeritInvalid();
        }
        void* plVar1b = *(void**)pcVec;
        while (true) {
            uint64_t uVar2b = *(uint64_t*)(
                pcVec + 0x20);
            if (uVar2b < uVar6c) {
                g_fnMeritInvalid();
            }
            void* local_48 = *(void**)pcVec;
            if ((local_48 == (void*)0)
                || (local_48 != plVar1b)) {
                g_fnMeritInvalid();
            }
            if (uVar2b == uVar6c) break;
            {
                int64_t lVar8 =
                    *(int64_t*)plVar1b;
                if (*(uint64_t*)(lVar8 + 0x20)
                        <= uVar6c) {
                    g_fnMeritInvalid();
                }
            }
            char* pcEntry = (char*)uVar6c;
            *(int*)(pcEntry + 0x10)
                = *(int*)(pcEntry + 0x10) + iVar4;
            {
                int64_t lVar8 =
                    *(int64_t*)plVar1b;
                if (*(uint64_t*)(lVar8 + 0x20)
                        <= uVar6c) {
                    g_fnMeritInvalid();
                }
            }
            uVar6c = uVar6c + 0x14;
        }
    }
    // ---- the remainder re-sync ----
    // The Ghidra rendering is the compiler's
    // negated-magic division of the BYTE size
    // by 0x14 (the entry stride):
    //   iVar9 += (-(end - begin) / 0x14) * iVar4
    // i.e. iVar9 -= count * iVar4. The Ghidra
    // slice-sign correction ((auVar3._12_4_ >>
    // 0x1f)) is the rendering artifact of the
    // MSVC idiom (hi >> 3 + the sign fix); the
    // game semantics is exactly the count.
    iVar9 = iVar9
        - (int)((((int64_t)uVar6b
            - *(int64_t*)(pcVec + 0x18))
            / 0x14) * (int64_t)iVar4);
    if (iVar9 < 1) {
        return 1;
    }
    // ---- pass 3: +1 each, sorted ----
    if (uVar6b
        < *(uint64_t*)(pcVec + 0x18)) {
        g_fnMeritInvalid();
    }
    int64_t local_b8[2] = {
        *(int64_t*)pcVec,
        *(int64_t*)(pcVec + 0x18)};   // first
    int64_t local_78[2] = {
        *(int64_t*)pcVec,
        (int64_t)uVar6b};               // last
    MeedEntrySort(
        (void**)local_b8, (void**)local_78,
        g_fnMeedEntryCmp);
    uint64_t uVar6d = *(uint64_t*)(pcVec + 0x18);
    if (*(uint64_t*)(pcVec + 0x20) < uVar6d) {
        g_fnMeritInvalid();
    }
    void* plVar1c = *(void**)pcVec;
    void* plVar5c = plVar1c;
    for (; 0 < iVar9; iVar9 = iVar9 + -1) {
        uint64_t uVar2c = *(uint64_t*)(
            pcVec + 0x20);
        void* local_38 = *(void**)pcVec;
        if (uVar2c < uVar6d) {
            g_fnMeritInvalid();
        }
        plVar5c = *(void**)pcVec;
        local_38 = plVar5c;
        if ((plVar5c == (void*)0)
            || (plVar5c != plVar1c)) {
            g_fnMeritInvalid();
        }
        if (uVar2c == uVar6d) break;
        {
            int64_t lVar8 = *(int64_t*)plVar1c;
            if (*(uint64_t*)(lVar8 + 0x20)
                    <= uVar6d) {
                g_fnMeritInvalid();
            }
        }
        char* pcEntry = (char*)uVar6d;
        *(int*)(pcEntry + 0x10)
            = *(int*)(pcEntry + 0x10) + 1;
        {
            int64_t lVar8 = *(int64_t*)plVar1c;
            if (*(uint64_t*)(lVar8 + 0x20)
                    <= uVar6d) {
                g_fnMeritInvalid();
            }
        }
        uVar6d = uVar6d + 0x14;
    }
    (void)plVar5c;
    return 1;
}

// ---------- FUN_1417821d0 @ 1417821d0 ----------
void MeedAwardUser(void* pThis, uint32_t uUser,
    int nType, int nPoint, int nMoney,
    int nEmoney) {
    (void)nPoint;
    if ((uint32_t)(nType - 1) < 3) {
        // *(this) = the user object;
        // vt+0x268(user) — the online check
        void* pUser = *(void**)pThis;
        char cVar1;
        {
            auto fn = (char (*)(void*))
                VtSlot(pUser, 0x268);
            cVar1 = fn(pUser);
        }
        if (cVar1 == '\0') {
            MeedAwardUserDisonline(
                pThis, uUser, nType, nPoint,
                nMoney, nEmoney);
        } else {
            g_fnMeedAwardOnline(
                pThis, uUser, nType, nPoint,
                nMoney, nEmoney);
        }
    } else {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::AwardUser, Type[%d] is
        //  not found!"
        g_fnMeedLog();
    }
}

// ---------- FUN_141781860 @ 141781860 ----------
void MeedAwardUserDisonline(void* pThis,
    uint32_t uUser, int nType, int nPoint,
    int nMoney, int nEmoney) {
    (void)nPoint;
    if ((uint32_t)(nType - 1) < 3) {
        void* puVar2 = MeedUserMgrGet();
        char cVar1 = MeedRecordUserPoint(
            puVar2, uUser, nType, nMoney,
            nEmoney);
        if (cVar1 == '\0') {
            // log_InlineLogERROR(literal):
            // "RecordUserPoint failed! idUser[%u],
            //  MeedType[%d] nEMoney[%d], nMoney[%d]"
            g_fnMeedLog();
        } else {
            void* pUser = *(void**)pThis;
            if (0 < nEmoney) {
                uint32_t uVar5 = 0;
                if (nType == 1) {
                    uVar5 = 0x1c;
                } else if (nType == 2) {
                    uVar5 = 0x17;
                } else {
                    uVar5 = 0;
                    if (nType == 3) {
                        uVar5 = 0x27;
                    }
                }
                // vt+0x350(user, emoneyType, 0,
                //           user id)
                auto fn = (void (*)(void*,
                    uint32_t, int, uint32_t))
                    VtSlot(pUser, 0x350);
                fn(pUser, uVar5, 0, uUser);
            }
            g_fnMeedTimeGet(3);  // tq::TimeGet(3)
            char local_458[0x400];
            local_458[0] = '\0';
            memset(local_458 + 1, 0, 0x3ff);
            const char* pcVar4 = (const char*)0;
            if (nType == 1) {
                pcVar4 = g_fnMeedStrGet(
                    g_fnMeedStrInst(),
                    "STR_VLM_ARENIC_"
                    "DISTRIBUTEMEED2");
            } else if (nType == 2) {
                pcVar4 = g_fnMeedStrGet(
                    g_fnMeedStrInst(),
                    "STR_SYN_ARENIC_"
                    "DISTRIBUTEMEED2");
            } else if (nType == 3) {
                pcVar4 = g_fnMeedStrGet(
                    g_fnMeedStrInst(),
                    "STR_CROSS_VLM_"
                    "ARENIC_DISTRIBUTEMEED2");
            }
            // TBD-SNPRINTF: the varargs are
            // dropped by the decompiler
            g_fnMeedSnprintf(local_458, 0x400,
                             pcVar4);
            local_458[0x3ff] = 0;
            // vt+0x358(user, "SYSTEM", id, buf)
            auto fnS = (void (*)(void*,
                const char*, uint32_t, char*))
                VtSlot(pUser, 0x358);
            fnS(pUser, "SYSTEM", uUser,
                local_458);
            const char* pcVar4b;
            if (nType == 1) {
                pcVar4b = "gmlog/vlm_meed_award";
            } else if (nType == 2) {
                pcVar4b = "gmlog/syn_meed_award";
            } else {
                pcVar4b =
                    "gmlog/cross_vlm_meed_award";
                if (nType != 3) {
                    pcVar4b = "gmlog/meed_error";
                }
            }
            // TBD-LOGSAVE: "CSynArenicMeed::"
            // "AwardUserDisonline idUser[%u], "
            // "nPoint[%d], nEmoney[%d], "
            // "nMoney[%d]" — the varargs are
            // dropped; only the user id passed
            g_fnMeedLogSave(pcVar4b,
                "CSynArenicMeed::AwardUserDisonline"
                " idUser[%u], nPoint[%d], "
                "nEmoney[%d], nMoney[%d]",
                uUser);
        }
    } else {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::AwardUserDisonline,
        //  Type[%d] is not found!"
        g_fnMeedLog();
    }
}

// ---------- FUN_141784cd0 @ 141784cd0 ----------
void MeedDistributeSyn(void* pThis,
                      uint32_t uIdSyn,
                      uint32_t uType) {
    if (uType < 4) {
        void* plVar5 = g_fnGetGameMgr();
        int64_t lVar6 = SynMemberFind(
            plVar5, uIdSyn);
        if (lVar6 == 0) {
            uint64_t uVar7 =
                MeedTypeByCompeteGet(
                    pThis, uType);
            const char* pcVar8 = MeedGmLogName(
                (int)uVar7, 2);
            // TBD-LOGSAVE: "CSynArenicMeed::"
            // "DistributeSynMeed, Syn[%u] not find"
            // " !!"
            g_fnMeedLogSave(pcVar8,
                "CSynArenicMeed::"
                "DistributeSynMeed, Syn[%u] "
                "not find !!", uIdSyn);
        } else {
            // ---- the ids vector (local_530) and
            // the entries vector (local_570) ----
            uint64_t local_530[6];  // proxy,?,?,
            uint64_t local_570[6];  // begin...
            // the ids vec: proxy = new(8);
            // *proxy = &container; container[0]
            // = proxy
            uint64_t* pProxy1 = (uint64_t*)
                g_fnMeritOpNew(8);
            local_530[3] = 0;  // begin
            local_530[4] = 0;  // end
            local_530[5] = 0;  // cap
            local_530[0] = 0;
            if (pProxy1 != (uint64_t*)0) {
                *pProxy1 = (uint64_t)local_530;
                local_530[0] = (uint64_t)pProxy1;
            }
            // the entries vec
            uint64_t* pProxy2 = (uint64_t*)
                g_fnMeritOpNew(8);
            local_570[3] = 0;
            local_570[4] = 0;
            local_570[5] = 0;
            if (pProxy2 != (uint64_t*)0) {
                *pProxy2 = (uint64_t)local_570;
            }
            local_570[0] = 0;
            local_570[0] = (uint64_t)pProxy2;
            // mgr vt+0x2b0(mgr, synId, &idsVec)
            {
                auto fn = (void (*)(void*,
                    uint32_t, void*))
                    VtSlot(plVar5, 0x2b0);
                fn(plVar5, uIdSyn, local_530);
            }
            // the random member pick
            int iVar4 = (int)MeedRandomMemberPick(
                pThis, local_530);
            int local_500 = 0;    // total
            int local_540 = 0;    // max user
            int local_538 = 0;    // max point
            uint64_t uVar7 = MeedCollectPoint(
                pThis, uIdSyn, local_570,
                &local_500, &local_540,
                &local_538, uType, local_530);
            int iVar3 = local_500;
            // the cleanup lambda (the decompile's
            // repeated tail — verbatim as a macro
            // of the same sequence)
#define MEED_DIST_CLEANUP()                        \
    do {                                           \
        if ((void*)local_570[3] != (void*)0) {      \
            g_fnMeritOpDelete(                      \
                (void*)local_570[3]);               \
        }                                          \
        local_570[3] = 0;                          \
        local_570[4] = 0;                          \
        local_570[5] = 0;                          \
        g_fnMeritOpDelete(                          \
            (void*)local_570[0]);                   \
        if ((void*)local_530[3] != (void*)0) {      \
            g_fnMeritOpDelete(                      \
                (void*)local_530[3]);               \
        }                                          \
        local_530[3] = 0;                          \
        local_530[4] = 0;                          \
        local_530[5] = 0;                          \
        g_fnMeritOpDelete(                          \
            (void*)local_530[0]);                   \
    } while (0)

            if ((char)uVar7 == '\0') {
                g_fnMeedLog();  // datum
                MEED_DIST_CLEANUP();
            } else if ((local_500 < 1)
                && ((uType == 2)
                    || (uType == 3))) {
                uint64_t uT =
                    MeedTypeByCompeteGet(
                        pThis, uType);
                const char* pcVar8 =
                    MeedGmLogName((int)uT, 2);
                // TBD-LOGSAVE: "...no user get"
                // " point !!"
                g_fnMeedLogSave(
                    pcVar8,
                    "CSynArenicMeed::"
                    "DistributeSynMeed, Syn[%u] "
                    "no user get point !!",
                    uIdSyn);
                MEED_DIST_CLEANUP();
            } else {
                int local_574 = 0;
                int local_578 = 0;
                void* pvVar10 = MeedPoolGet();
                {
                    uint64_t uT =
                        MeedTypeByCompeteGet(
                            pThis, uType);
                    g_fnMeedListFill(
                        pvVar10, &local_574,
                        &local_578, uIdSyn,
                        (int)uT);
                }
                {
                    uint64_t uT =
                        MeedTypeByCompeteGet(
                            pThis, uType);
                    MeedDeleteSynMeed(
                        pvVar10, (int)uIdSyn,
                        (int)uT);
                }
                void* plVar5b =
                    MeedSingletonGet();
                uint64_t local_538b =
                    (uint64_t)(uintptr_t)
                    MeedUserLeague(
                        plVar5b, uIdSyn);
                uint32_t* puVar12 =
                    (uint32_t*)local_570[3];
                if (local_538b == 0) {
                    g_fnMeedLog();  // datum
                    MEED_DIST_CLEANUP();
                } else if ((local_574 < 1)
                    && (local_578 < 1)) {
                    // the no-pot path: only the
                    // meed records. plVar5 = the
                    // entries PROXY (captured once);
                    // the record target = the league
                    void* plVar5c =
                        (void*)local_570[0];
                    while (true) {
                        uint32_t* puVar1 =
                            (uint32_t*)
                            local_570[4];
                        if (puVar1 < puVar12) {
                            g_fnMeritInvalid();
                        }
                        if ((*(void**)local_570
                                == (void*)0)
                            || (*(void**)local_570
                                != plVar5c)) {
                            g_fnMeritInvalid();
                        }
                        if (puVar1 == puVar12)
                            break;
                        {
                            int64_t lV =
                                *(int64_t*)
                                plVar5c;
                            if (*(uint64_t*)(
                                    lV + 0x20)
                                    <= (uint64_t)
                                    (uintptr_t)
                                    puVar12) {
                                g_fnMeritInvalid();
                            }
                        }
                        uint64_t uT =
                            MeedTypeByCompeteGet(
                                pThis, uType);
                        MeedRecordInsert(
                            (void*)(uintptr_t)
                            local_538b,
                            (int)uT, puVar12);
                        {
                            int64_t lV =
                                *(int64_t*)(
                                    (void*)
                                    local_570[0]);
                            if (*(uint64_t*)(
                                    lV + 0x20)
                                    <= (uint64_t)
                                    (uintptr_t)
                                    puVar12) {
                                g_fnMeritInvalid();
                            }
                        }
                        puVar12 = puVar12 + 5;
                    }
                    MEED_DIST_CLEANUP();
                } else {
                    int64_t lVar6b =
                        (int64_t)local_570[4]
                        - (int64_t)local_570[3];
                    int64_t lCarry = lVar6b >> 0x3f;
                    if (lVar6b / 0x14 + lCarry
                        == lCarry) {
                        // the EMPTY entries path:
                        // a synthetic entry for the
                        // random keeper + the pot
                        int local_4b8[5];
                        local_4b8[0] = 0;
                        local_4b8[2] = 0;
                        local_4b8[3] = local_574;
                        local_4b8[4] = local_578;
                        local_540 = iVar4;
                        local_4b8[1] = iVar4;
                        MeedEntryVecPush(
                            local_570,
                            (const MeedEntry5*)
                            local_4b8);
                        uint64_t uT =
                            MeedTypeByCompeteGet(
                                pThis, uType);
                        const char* pcVar8 =
                            MeedGmLogName(
                                (int)uT, 2);
                        // TBD-LOGSAVE: "...no user"
                        // " get point !! idMax"
                        // "Keeper[%u], idSyn[%d]"
                        g_fnMeedLogSave(
                            pcVar8,
                            "CSynArenicMeed::"
                            "DistributeSynMeed, "
                            "no user get point !!"
                            " idMaxKeeper[%u], "
                            "idSyn[%d]", uIdSyn);
                    } else {
                        uint64_t uT =
                            MeedTypeByCompeteGet(
                                pThis, uType);
                        uint64_t uVar11 =
                            MeedCollectAward(
                                pThis, (int)uT,
                                local_570, iVar3,
                                local_574,
                                local_578);
                        iVar4 = local_540;
                        if ((char)uVar11
                            == '\0') {
                            g_fnMeedLog();
                            MEED_DIST_CLEANUP();
                            return;
                        }
                    }
                    // ---- the final loop: the award
                    // + the record for each entry --
                    puVar12 = (uint32_t*)
                        local_570[3];
                    int local_4f8 = 0, local_4f4 = 0,
                        local_4f0 = 0,
                        local_4ec = 0,
                        local_4e8 = 0;
                    void* plVar5d =
                        (void*)local_570[0];
                    while (true) {
                        uint32_t* puVar2 =
                            (uint32_t*)
                            local_570[4];
                        if (puVar2 < puVar12) {
                            g_fnMeritInvalid();
                        }
                        if ((*(void**)local_570
                                == (void*)0)
                            || (*(void**)local_570
                                != plVar5d)) {
                            g_fnMeritInvalid();
                        }
                        iVar3 = local_4f4;
                        if (puVar2 == puVar12)
                            break;
                        {
                            int64_t lV =
                                *(int64_t*)
                                plVar5d;
                            if (*(uint64_t*)(
                                    lV + 0x20)
                                <= (uint64_t)
                                (uintptr_t)
                                puVar12) {
                                g_fnMeritInvalid();
                            }
                        }
                        if (puVar12[1]
                            == (uint32_t)iVar4) {
                            local_4f8 =
                                puVar12[0];
                            local_4f4 =
                                puVar12[1];
                            local_4f0 =
                                puVar12[2];
                            local_4ec =
                                puVar12[3];
                            local_4e8 =
                                puVar12[4];
                        }
                        {
                            uint64_t uT =
                                MeedTypeByCompeteGet(
                                    pThis, uType);
                            MeedAwardUser(
                                pThis,
                                puVar12[1],
                                (int)uT,
                                puVar12[2],
                                puVar12[3],
                                puVar12[4]);
                        }
                        {
                            uint64_t uT =
                                MeedTypeByCompeteGet(
                                    pThis, uType);
                            MeedRecordInsert(
                                (void*)(uintptr_t)
                                local_538b,
                                (int)uT, puVar12);
                        }
                        {
                            int64_t lV =
                                *(int64_t*)(
                                    (void*)
                                    local_570[0]);
                            if (*(uint64_t*)(
                                    lV + 0x20)
                                <= (uint64_t)
                                (uintptr_t)
                                puVar12) {
                                g_fnMeritInvalid();
                            }
                        }
                        puVar12 = puVar12 + 5;
                    }
                    if (local_4f4 == 0) {
                        uint64_t uT =
                            MeedTypeByCompeteGet(
                                pThis, uType);
                        const char* pcVar8 =
                            MeedGmLogName(
                                (int)uT, 2);
                        // TBD-LOGSAVE: "no member"
                        // " reward! idSyn[%u], "
                        // "EMoney[%d], Money[%d]"
                        g_fnMeedLogSave(
                            pcVar8,
                            "no member reward! "
                            "idSyn[%u], "
                            "EMoney[%d], "
                            "Money[%d]", uIdSyn);
                    } else {
                        char local_448[0x400];
                        local_448[0] = '\0';
                        memset(local_448 + 1, 0,
                               0x3ff);
                        // the game mgr
                        // vt+0xb8(mgr, the keeper id)
                        {
                            auto fn = (void (*)(
                                void*, int))
                                VtSlot(plVar5, 0xb8);
                            fn(plVar5, iVar3);
                        }
                        uint64_t uT =
                            MeedTypeByCompeteGet(
                                pThis, uType);
                        char* pcFmt =
                            MeedPromptGet(
                                pThis, (int)uT,
                                5);
                        g_fnMeedSnprintf(
                            local_448, 0x400,
                            pcFmt);
                        local_448[0x3ff] = 0;
                        // mgr vt+0x40(mgr, synId,
                        // buf, 0)
                        {
                            auto fn = (void (*)(
                                void*, uint32_t,
                                char*, int))
                                VtSlot(plVar5, 0x40);
                            fn(plVar5, uIdSyn,
                               local_448, 0);
                        }
                    }
                    MEED_DIST_CLEANUP();
                }
            }
#undef MEED_DIST_CLEANUP
        }
    } else {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::DistributeSynMeed,
        //  CompeteType[%d] is not found!"
        g_fnMeedLog();
    }
}

}  // namespace syndicate

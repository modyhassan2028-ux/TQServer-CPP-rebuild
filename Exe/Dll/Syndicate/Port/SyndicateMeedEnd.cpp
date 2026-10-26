// SyndicateMeedEnd — D54/T16: the ProcessEndMeed
// flow + the id-list builder + the erase, verbatim
// from Syndicate.dll.decompiled.c.
#include "Exe/Dll/Syndicate/Port/SyndicateMeedEnd.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"    // pool
#include "Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"    // g_fnMeedLog
#include "Exe/Dll/Syndicate/Port/SyndicateMeedSort.h"     // sorts
#include "Exe/Dll/Syndicate/Port/SyndicateMeedInfo.h"     // req id
#include "Exe/Dll/Syndicate/Port/SyndicateMeedApply.h"    // D53
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"     // singleton
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"    // op new
#include <cstring>
#include <cstdio>

namespace syndicate {

// ---- the seams ----
// DAT_14182fd60 (a .rdata fmt datum — the marker)
const char* g_szMeedLogFmtEnd = "FMT-END";
void (*g_fnMeedVecInsertInt)(
    void*, void* pPair[2], int64_t, void*) =
    [](void*, void*[2], int64_t, void*) {};

namespace {

inline void* VtSlot(void* pObj, size_t uOff) {
    void* pVt = *(void**)pObj;
    return *(void**)((char*)pVt + uOff);
}

} // namespace

// ---------- FUN_14177d7a0: BuildIdList ---------
void MeedIdListBuild(void* pPool, int nType,
                     void* pVec) {
    void** plVar10;
    if ((uint32_t)(nType - 1) < 3) {
        plVar10 = (void**)((char*)pPool
            + (uint64_t)(nType - 1) * 0x30);
    } else {
        g_fnMeedLog();   // GetVecByMeedType log
        plVar10 = (void**)((char*)pPool + 0x98);
    }
    void** puVar9 = (void**)plVar10[3];
    if ((void**)plVar10[4] < puVar9) {
        g_fnMeritInvalid();
    }
    void** plVar1 = (void**)*plVar10;
    do {
        void** puVar2 = (void**)plVar10[4];
        if (puVar2 < (void**)plVar10[3]) {
            g_fnMeritInvalid();
        }
        if ((plVar1 == nullptr)
            || (plVar1 != (void**)*plVar10)) {
            g_fnMeritInvalid();
        }
        if (puVar9 == puVar2) {
            return;
        }
        int64_t lVar6 = (plVar1 != nullptr)
            ? *(int64_t*)plVar1 : 0;
        if ((void**)*(void**)(lVar6 + 0x20)
                <= puVar9) {
            g_fnMeritInvalid();
        }
        // the member field: vt+0x10(mem, 2) ->
        //  vt+0x40() = the id (args dropped)
        void* pMem = *(void**)puVar9;
        {
            auto fnF = (void* (*)(void*, int64_t))
                VtSlot(pMem, 0x10);
            void* plVar5 = fnF(pMem, 2);
            auto fnId = (uint32_t (*)(void*))
                VtSlot(plVar5, 0x40);
            uint32_t uId = fnId(plVar5);
            // the int push (the direct store or
            // the 14172d120 grow)
            int* puVar3 = *(int**)((char*)pVec
                + 0x18);
            uint64_t uVar7 = 0;
            if (puVar3 != nullptr) {
                uVar7 = (uint64_t)(
                    (*(char**)((char*)pVec + 0x28))
                    - (char*)puVar3) >> 2;
            }
            int* puVar4 = *(int**)((char*)pVec
                + 0x20);
            if ((uint64_t)(((char*)puVar4
                    - (char*)puVar3) >> 2)
                < uVar7) {
                *puVar4 = (int)uId;
                *(int**)((char*)pVec + 0x20)
                    = puVar4 + 1;
            } else {
                if (puVar4 < puVar3) {
                    g_fnMeritInvalid();
                }
                // the debug iterator dance +
                // the grow
                void* aPair[2] = { *(void**)pVec,
                                   nullptr };
                g_fnMeedVecInsertInt(
                    pVec, aPair, 1, &uId);
            }
        }
        // the second gate
        int64_t lVar6b = (plVar1 != nullptr)
            ? *(int64_t*)plVar1 : 0;
        if ((void**)*(void**)(lVar6b + 0x20)
                <= puVar9) {
            g_fnMeritInvalid();
        }
        puVar9 = puVar9 + 1;
    } while (true);
}

// ---------- FUN_14177d180: DeleteSynMeed ------
uint64_t MeedDeleteSynMeed(void* pPool, int nId,
                           int nType) {
    if (2 < (uint32_t)(nType - 1)) {
        g_fnMeedLog();   // DeleteSynMeed Type log
        return 0;
    }
    void** plVar6 = (void**)((char*)pPool
        + (uint64_t)(nType - 1) * 0x30);
    void** _Dst = (void**)plVar6[3];
    if ((void**)plVar6[4] < _Dst) {
        g_fnMeritInvalid();
    }
    void** plVar5 = (void**)*plVar6;
    void* plVar1m = nullptr;
    do {
        while (true) {
            void** plVar1 = (void**)plVar6[4];
            if (plVar1 < (void**)plVar6[3]) {
                g_fnMeritInvalid();
            }
            void** plVar3 = (void**)*plVar6;
            if ((plVar3 == nullptr)
                || (plVar3 != plVar5)) {
                g_fnMeritInvalid();
                plVar3 = nullptr;
            }
            if (plVar1 == _Dst) {
                // the walk ended
                return 1;
            }
            int64_t lVar4 = (plVar5 != nullptr)
                ? *(int64_t*)plVar5 : 0;
            if ((void**)*(void**)(lVar4 + 0x20)
                    <= _Dst) {
                g_fnMeritInvalid();
            }
            plVar1m = *(void**)_Dst;
            if (plVar1m != nullptr) break;
            // the null-elem skip
            int64_t lVar4b = (plVar5 != nullptr)
                ? *(int64_t*)plVar5 : 0;
            if ((void**)*(void**)(lVar4b + 0x20)
                    <= _Dst) {
                g_fnMeritInvalid();
            }
            _Dst = _Dst + 1;
        }
        // the match check: vt+8(mem, 2) ->
        //  vt+0x40() == id
        void* plVar3f;
        int iVar2;
        {
            auto fnF = (void* (*)(void*, int64_t))
                VtSlot(plVar1m, 0x8);
            plVar3f = fnF(plVar1m, 2);
            auto fnId = (int (*)(void*))
                VtSlot(plVar3f, 0x40);
            iVar2 = fnId(plVar3f);
        }
        if (nId != iVar2) {
            // no match: advance
            int64_t lVar4b = (plVar5 != nullptr)
                ? *(int64_t*)plVar5 : 0;
            if ((void**)*(void**)(lVar4b + 0x20)
                    <= _Dst) {
                g_fnMeritInvalid();
            }
            _Dst = _Dst + 1;
            continue;
        }
        // matched: the compaction
        int64_t lVar4 = ((char*)plVar6[4]
            - (char*)(_Dst + 1)) >> 3;
        if (0 < lVar4) {
            // memmove_s(dst, size, src, size)
            memmove(_Dst, _Dst + 1,
                    (size_t)(lVar4 << 3));
        }
        plVar6[4] = (void**)((char*)plVar6[4]
            - 8);
        if ((_Dst < (void**)plVar6[3])
            || ((void**)plVar6[4] < _Dst)) {
            g_fnMeritInvalid();
        }
        plVar5 = (void**)*plVar6;
        // the release pair: vt+0x40(mem, 1)
        // + vt+0(mem, 1) — the deleting dtor
        {
            auto fnRel = (uint64_t (*)(
                void*, uint64_t))
                VtSlot(plVar1m, 0x40);
            fnRel(plVar1m, 1);
            auto fnDtor = (uint64_t (*)(
                void*, uint64_t))
                VtSlot(plVar1m, 0x00);
            fnDtor(plVar1m, 1);
        }
        // rescan from the SAME slot for more
    } while (true);
}

// ---------- FUN_141783470: ProcessEndMeed -----
uint64_t MeedProcessEnd(void* pUser, int nType) {
    char local_438[0x400];
    if ((uint32_t)(nType - 1) < 3) {
        void* pvVar5 = MeedPoolGet();
        void* plVar6 = LeagueSingleton();
        local_438[0] = '\0';
        memset(local_438 + 1, 0, 0x3ff);
        void* pvVar7 = local_438;
        if ((nType == 1) || (nType == 3)) {
            // the int-vector stack fixture:
            // {proxy, ?, begin, end, cap}
            void* local_4a0[6] = {};
            void* local_4c0 = g_fnMeritOpNew(8);
            if (local_4c0 == nullptr) {
                local_4a0[0] = nullptr;
            } else {
                *(void**)local_4c0 = local_4a0;
                local_4a0[0] = local_4c0;
            }
            // (the walker fills [3]=begin,
            //  [4]=end, [5]=cap — in the original
            //  these are the local_488/480/478
            //  stack slots aliased to the array)
            local_4a0[3] = nullptr;
            local_4a0[4] = nullptr;
            local_4a0[5] = nullptr;
            MeedIdListBuild(pvVar5, nType,
                            local_4a0);
            int* piVar10 =
                (int*)local_4a0[3];
            int64_t local_money = 0;   // 4b8
            int64_t local_emoney = 0;  // 4c0
            while (true) {
                if (piVar10
                        == (int*)local_4a0[4]) {
                    break;
                }
                // the verbatim mask dance:
                // BOTH pair halves cleared
                local_money &= (int64_t)
                    0xffffffff00000000ULL;
                local_emoney &= (int64_t)
                    0xffffffff00000000ULL;
                MeedPoolGetSynMeed(
                    pvVar5, (int*)&local_money,
                    (int*)&local_emoney,
                    (uint32_t)*piVar10, nType);
                char cVar4;
                {
                    auto fn = (char (*)(void*,
                        int, int64_t))
                        VtSlot(plVar6, 0x1f0);
                    cVar4 = fn(plVar6, *piVar10,
                               (int32_t)
                                   local_money);
                }
                if (cVar4 != '\0') {
                    {
                        auto fn = (char (*)(
                            void*, int,
                            uint32_t))
                            VtSlot(plVar6,
                                   0x1f8);
                        cVar4 = fn(plVar6,
                                   *piVar10,
                                   (uint32_t)
                                       local_emoney);
                    }
                }
                if (cVar4 == '\0') {
                    g_fnMeedLog();  // ProcessEnd
                                    //  Meed err
                } else {
                    if (0 < (int32_t)
                            local_emoney) {
                        void* pObj =
                            *(void**)pUser;
                        uint64_t uE =
                            MeedEmonyType(
                                pUser, nType, 4);
                        auto fn = (void (*)(
                            void*, uint64_t,
                            int, int))
                            VtSlot(pObj, 0x350);
                        fn(pObj,
                           (uint32_t)uE, 0,
                           *piVar10);
                    }
                    // the entry {id, money,
                    // emoney}
                    int local_470[3] = {
                        *piVar10,
                        (int32_t)local_money,
                        (int32_t)local_emoney
                    };
                    uint8_t local_c8 = 0;
                    uint64_t uVar8 =
                        MeedSetMgrSetSynMeed(
                            pvVar5, local_470,
                            nType, &local_c8);
                    if ((char)uVar8 == '\0') {
                        g_fnMeedLog();  // datum
                    }
                    const char* pcVar9 =
                        MeedGmLogName(nType, 1);
                    // NOTE: unlike 141780cb0 (the
                    // id provably loaded there), this
                    // MyLogSave shows NO id load in
                    // the decompile — the varargs
                    // are fully dropped; 0 passed
                    g_fnMeedLogSave(
                        pcVar9,
                        g_szMeedLogFmtEnd, 0);
                    char* pcFmt =
                        MeedPromptGet(pUser,
                                      nType, 7);
                    g_fnMeedSnprintf(
                        local_438, 0x400,
                        pcFmt);
                    local_438[0x3ff] = 0;
                    {
                        auto fn = (void (*)(
                            void*, int,
                            char*, int))
                            VtSlot(plVar6,
                                   0x40);
                        fn(plVar6, *piVar10,
                           local_438, 0);
                    }
                }
                MeedDeleteSynMeed(pvVar5,
                                  *piVar10,
                                  nType);
                ++piVar10;
            }
            // the cleanup: the begin buffer
            // then the proxy
            if (local_4a0[3] != nullptr) {
                g_fnMeritOpDelete(
                    local_4a0[3]);
            }
            g_fnMeritOpDelete(local_4a0[0]);
            pvVar7 = local_438;
        }
        return 1;
        // CONCAT71(pvVar7 >> 8, 1)
    }
    g_fnMeedLog();   // ProcessEndMeed Type log
    return 0;
}

} // namespace syndicate

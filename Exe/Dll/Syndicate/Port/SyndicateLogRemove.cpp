// SyndicateLogRemove.cpp — D60 (see the header
// for the address map and the seam list).
// All bodies VERBATIM from
// Syndicate.dll.decompiled.c.
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"   // LeagueMemberLookup
#include <ctime>
// the decompiler's raw types (kept for verbatim
// fidelity with the original listing)
typedef long long longlong;
typedef uint64_t undefined8;   // 8 BYTES (the decompiler's type)
typedef uint8_t undefined1;
typedef uint32_t undefined4;

namespace syndicate {

// ---- the seams ----
static uint64_t DefSessionKeyLookup(void*, uint32_t) {
    return 0;
}
uint64_t (*g_fnSessionKeyLookup)(void*, uint32_t) =
    DefSessionKeyLookup;
static void DefSortRange(void*, void*, int64_t, void*) {}
void (*g_fnSortRange)(void*, void*, int64_t, void*) =
    DefSortRange;
static void* DefTreeInsertF10(void* p, void*, uint32_t*) {
    return p;
}
void* (*g_fnTreeInsertF10)(void*, void*, uint32_t*) =
    DefTreeInsertF10;
static void DefSendToSession(void*, uint32_t) {}
void (*g_fnSendToSession)(void*, uint32_t) =
    DefSendToSession;
static void* DefTreeFindAF0(void* p, void*, uint32_t*) {
    return p;
}
void* (*g_fnTreeFindAF0)(void*, void*, uint32_t*) =
    DefTreeFindAF0;
static void DefTreeErase(void*, void*, void*) {}
void (*g_fnTreeErase)(void*, void*, void*) =
    DefTreeErase;
static void DefInvalid() {}
void (*g_fnLogRemoveInvalid)() = DefInvalid;
static void DefLogError() {}
void (*g_fnLogRemoveLogError)() = DefLogError;

// ================= FUN_14178c8e0 =================
// the log-record map find: head = map[6] (the
// anchor slot), root = head[1], key @ node+0x18,
// isnil @ node+0x29, value @ node+0x20.
int64_t LogRecMapFind(void* p0, uint32_t uKey) {
    longlong* param_1 = (longlong*)p0;
    longlong lVar7;
    longlong* plVar8;
    longlong* plVar2;
    longlong lVar3, lVar5;
    undefined8* puVar6;
    undefined8* puVar9;
    undefined8* puVar4;
    // the CRT iterator pairs (ADJACENT stack slots
    // in the original: {first,second})
    longlong aPairA[2];   // {local_38, local_30}
    longlong aPairB[2];   // {local_28, local_20}
    longlong local_10, local_18;

    lVar7 = 0;
    puVar9 = (undefined8*)((undefined8*)param_1[6])[1];
    char cVar1 =
        *(char*)((longlong)puVar9 + 0x29);
    puVar4 = (undefined8*)param_1[6];
    while (cVar1 == '\0') {
        if (*(uint32_t*)(puVar9 + 3) < uKey) {
            puVar6 = (undefined8*)puVar9[2];
            puVar9 = puVar4;
        }
        else {
            puVar6 = (undefined8*)*puVar9;
        }
        puVar4 = puVar9;
        puVar9 = puVar6;
        cVar1 = *(char*)((longlong)puVar6 + 0x29);
    }
    puVar9 = (undefined8*)param_1[6];
    aPairA[1] = (longlong)puVar4;   // local_30
    aPairA[0] = *param_1;           // local_38
    if (*param_1 == 0) {
        g_fnLogRemoveInvalid();
    }
    if ((puVar4 == puVar9) ||
        (uKey < *(uint32_t*)(puVar4 + 3))) {
        plVar8 = (longlong*)aPairB;
        aPairB[1] = (longlong)param_1[6];  // local_20
        aPairB[0] = (longlong)*param_1;    // local_28
    }
    else {
        plVar8 = (longlong*)aPairA;
    }
    plVar2 = (longlong*)*plVar8;
    lVar3 = param_1[6];
    local_18 = (longlong)plVar2;
    local_10 = plVar8[1];
    if (((longlong*)*param_1 == (longlong*)0x0) ||
        ((longlong*)*param_1 != plVar2)) {
        g_fnLogRemoveInvalid();
    }
    lVar5 = local_10;
    if (lVar3 != local_10) {
        if (plVar2 == (longlong*)0x0) {
            g_fnLogRemoveInvalid();
        }
        else {
            lVar7 = *plVar2;
        }
        if (lVar5 == *(longlong*)(lVar7 + 0x30)) {
            g_fnLogRemoveInvalid();
        }
        lVar7 = *(longlong*)(lVar5 + 0x20);
    }
    return lVar7;
}

// ================= FUN_1417631d0 =================
// the account-tree find: uVar5 = the session-key
// lookup (14175ee00 = SEAM); the tree root at
// *(acctmgr+0x68), anchor at acctmgr+0x38.
int64_t AcctTreeFind(void* p0, uint32_t uId) {
    longlong param_1 = (longlong)p0;
    longlong* plVar6;
    longlong* plVar2;
    longlong lVar9, lVar4;
    undefined8* puVar7;
    undefined8* puVar8;
    undefined8* puVar3;
    longlong aPairA[2];   // {local_38, local_30}
    longlong aPairB[2];   // {local_28, local_20}
    longlong local_10, local_18;
    undefined8 uVar5;

    uVar5 = (undefined8)g_fnSessionKeyLookup(
        (void*)param_1, uId);
    puVar8 =
        (undefined8*)(*(undefined8**)(param_1 +
                                       0x68))[1];
    char cVar1 =
        *(char*)((longlong)puVar8 + 0x29);
    puVar3 = *(undefined8**)(param_1 + 0x68);
    while (cVar1 == '\0') {
        undefined8* puVar7_inner;
        if (*(uint32_t*)(puVar8 + 3) <
            (uint32_t)uVar5) {
            puVar7_inner = (undefined8*)puVar8[2];
            puVar8 = puVar3;
        }
        else {
            puVar7_inner = (undefined8*)*puVar8;
        }
        puVar3 = puVar8;
        puVar8 = puVar7_inner;
        cVar1 =
            *(char*)((longlong)puVar7_inner + 0x29);
    }
    (void)puVar7;
    puVar8 = *(undefined8**)(param_1 + 0x68);
    aPairA[1] = (longlong)puVar3;                    // local_30
    aPairA[0] = *(longlong*)(param_1 + 0x38);        // local_38
    if (*(longlong*)(param_1 + 0x38) == 0) {
        g_fnLogRemoveInvalid();
    }
    if ((puVar3 == puVar8) ||
        ((uint32_t)uVar5 <
         *(uint32_t*)(puVar3 + 3))) {
        plVar6 = (longlong*)aPairB;
        aPairB[1] =
            (longlong)*(undefined8*)(param_1 + 0x68);   // local_20
        aPairB[0] =
            (longlong)*(longlong*)(param_1 + 0x38);      // local_28
    }
    else {
        plVar6 = (longlong*)aPairA;
    }
    plVar2 = (longlong*)*plVar6;
    lVar9 = *(longlong*)(param_1 + 0x68);
    local_18 = (longlong)plVar2;
    local_10 = plVar6[1];
    if ((*(longlong**)(param_1 + 0x38) ==
         (longlong*)0x0) ||
        (*(longlong**)(param_1 + 0x38) != plVar2)) {
        g_fnLogRemoveInvalid();
    }
    lVar4 = local_10;
    if (lVar9 == local_10) {
        uVar5 = 0;
    }
    else {
        if (plVar2 == (longlong*)0x0) {
            g_fnLogRemoveInvalid();
            lVar9 = 0;
        }
        else {
            lVar9 = *plVar2;
        }
        if (lVar4 == *(longlong*)(lVar9 + 0x30)) {
            g_fnLogRemoveInvalid();
        }
        uVar5 = *(undefined8*)(lVar4 + 0x20);
    }
    return (int64_t)uVar5;
}

// ================= FUN_14174b360 =================
// the field-set walk (tree @ mgr+0xc8, anchor @
// mgr+0x98, isnil @ +0x3d) + the literal writes.
void AcctFieldSet(void* p0, uint32_t uId,
                  int nField, int nVal) {
    longlong param_1 = (longlong)p0;
    char cVar1;
    longlong* plVar6;
    longlong* plVar2;
    longlong lVar8, lVar4;
    undefined8* puVar5;
    undefined8* puVar7;
    undefined8* puVar3;
    longlong aPairA[2];   // {local_48, local_40}
    longlong aPairB[2];   // {local_38, local_30}
    longlong local_20, local_28, local_10;

    puVar7 = (undefined8*)(*(undefined8**)
                              (param_1 + 200))[1];
    cVar1 = *(char*)((longlong)puVar7 + 0x3d);
    puVar3 = *(undefined8**)(param_1 + 200);
    while (cVar1 == '\0') {
        if (*(uint32_t*)(puVar7 + 3) < uId) {
            puVar5 = (undefined8*)puVar7[2];
            puVar7 = puVar3;
        }
        else {
            puVar5 = (undefined8*)*puVar7;
        }
        puVar3 = puVar7;
        puVar7 = puVar5;
        cVar1 = *(char*)((longlong)puVar5 + 0x3d);
    }
    puVar7 = *(undefined8**)(param_1 + 200);
    aPairA[1] = (longlong)puVar3;              // local_40
    aPairA[0] = *(longlong*)(param_1 + 0x98);  // local_48
    if (*(longlong*)(param_1 + 0x98) == 0) {
        g_fnLogRemoveInvalid();
    }
    if ((puVar3 == puVar7) ||
        (uId < *(uint32_t*)(puVar3 + 3))) {
        plVar6 = (longlong*)aPairB;
        aPairB[1] =
            (longlong)*(undefined8*)(param_1 + 200);   // local_30
        aPairB[0] =
            (longlong)*(longlong*)(param_1 + 0x98);     // local_38
    }
    else {
        plVar6 = (longlong*)aPairA;
    }
    plVar2 = (longlong*)*plVar6;
    lVar8 = *(longlong*)(param_1 + 200);
    local_28 = (longlong)plVar2;
    local_10 = plVar6[1];
    if ((*(longlong**)(param_1 + 0x98) ==
         (longlong*)0x0) ||
        (*(longlong**)(param_1 + 0x98) != plVar2)) {
        g_fnLogRemoveInvalid();
    }
    lVar4 = local_10;
    if (lVar8 != local_10) {
        if (plVar2 == (longlong*)0x0) {
            g_fnLogRemoveInvalid();
            lVar8 = 0;
        }
        else {
            lVar8 = *plVar2;
        }
        if (lVar4 == *(longlong*)(lVar8 + 0x30)) {
            g_fnLogRemoveInvalid();
        }
        if (nField == 4) {
            *(int*)(lVar4 + 0x1c) = nVal;
        }
        else if (nField == 5) {
            *(int*)(lVar4 + 0x20) = nVal;
        }
        else if (nField == 6) {
            *(short*)(lVar4 + 0x24) = (short)nVal;
        }
        else if (nField == 8) {
            *(bool*)(lVar4 + 0x2a) = nVal != 0;
        }
        else if (nField == 9) {
            *(int*)(lVar4 + 0x26) = nVal;
        }
    }
}

// ================= FUN_141787310 =================
// the offline flag (+0x3c) + the tick chain:
// vt+0x10(0x1a) -> _time64 & 0xffffffff ->
// vt+0xb0 -> vt+0x38 (on the FIRST object).
void RecFlagTick(void* p0, uint8_t bFlag) {
    longlong* param_1 = (longlong*)p0;
    longlong* plVar1;
    *(uint8_t*)((longlong)param_1 + 0x3c) = bFlag;
    plVar1 = (longlong*)*param_1;
    if (plVar1 != (longlong*)0x0) {
        // ORIGINAL: (**(code **)(*plVar1 + 0x10))
        //   (plVar1, 0x1a) — vt slot +0x10
        void** pVt1 = *(void***)plVar1;
        plVar1 = (longlong*)((void*(*)(void*, int64_t))
            pVt1[2])(plVar1, 0x1a);
        // ORIGINAL: _time64(0) & 0xffffffff
        uint64_t uT =
            (uint64_t)time(nullptr) & 0xffffffff;
        // ORIGINAL: (**(code **)(*plVar1 + 0xb0))
        //   (plVar1, uT) — vt slot +0xb0
        void** pVt2 = *(void***)plVar1;
        ((void(*)(void*, uint32_t))pVt2[0xb0 / 8])(
            plVar1, (uint32_t)uT);
        // ORIGINAL: (**(code **)(*param_1 + 0x38))
        //   (param_1, 0) — the FIRST object's vt
        void** pVt3 = *(void***)*param_1;
        ((void(*)(void*, int64_t))pVt3[0x38 / 8])(
            (void*)*param_1, 0);
    }
}

// ================= FUN_141785ea0 =================
uint64_t RecRankGet(void* p0) {
    longlong* param_1 = (longlong*)p0;
    longlong* plVar1;
    uint64_t uVar2;

    plVar1 = (longlong*)*param_1;
    if (plVar1 == (longlong*)0x0) {
        g_fnLogRemoveLogError();
        return 0;
    }
    void** pVtA = *(void***)plVar1;
    plVar1 = (longlong*)((void*(*)(void*, int64_t))
        pVtA[2])(plVar1, 1);
    void** pVtB = *(void***)plVar1;
    uVar2 = (uint64_t)((uint64_t(*)(void*))pVtB[8])(
        plVar1);
    return uVar2;
}

// ================= FUN_141787300 =================
bool RecIsOnline(void* pRec) {
    return *(uint8_t*)((longlong)pRec + 0x3c) != 0;
}

// ================= FUN_1417867d0 =================
int64_t RecCmpKey(void* p0) {
    longlong* param_1 = (longlong*)p0;
    longlong* plVar1;
    uint64_t uVar2;

    plVar1 = (longlong*)*param_1;
    if (plVar1 == (longlong*)0x0) {
        g_fnLogRemoveLogError();
        return 0;
    }
    void** pVtA = *(void***)plVar1;
    plVar1 = (longlong*)((void*(*)(void*, int64_t))
        pVtA[2])(plVar1, 2);
    void** pVtB = *(void***)plVar1;
    uVar2 = (uint64_t)((uint64_t(*)(void*))pVtB[9])(
        plVar1);
    return (int64_t)uVar2;
}

// ================= FUN_141785dc0 =================
uint64_t RecCmpSub(void* p0) {
    longlong* param_1 = (longlong*)p0;
    longlong* plVar1;
    uint64_t uVar2;

    plVar1 = (longlong*)*param_1;
    if (plVar1 == (longlong*)0x0) {
        g_fnLogRemoveLogError();
        return 0;
    }
    void** pVtA = *(void***)plVar1;
    plVar1 = (longlong*)((void*(*)(void*, int64_t))
        pVtA[2])(plVar1, 0);
    void** pVtB = *(void***)plVar1;
    uVar2 = (uint64_t)((uint64_t(*)(void*))pVtB[8])(
        plVar1);
    return uVar2;
}

// ================= FUN_14178f1a0 =================
// the record comparator: false if !A; true if !B;
// online(A) vs online(B) via RecIsOnline, then the
// key (RecCmpKey) asc / sub (RecCmpSub) tie-break.
bool RecComparator(void* pA, void* pB) {
    longlong* param_1 = (longlong*)pA;
    longlong* param_2 = (longlong*)pB;
    char cVar1;

    if (param_1 == (longlong*)0x0) {
        return false;
    }
    if (param_2 == (longlong*)0x0) {
        return true;
    }
    cVar1 = RecIsOnline((void*)param_1)
                ? (char)1 : (char)0;
    if ((cVar1 == '\0') &&
        (cVar1 = RecIsOnline((void*)param_2)
             ? (char)1 : (char)0,
         cVar1 != '\0')) {
        return false;
    }
    cVar1 = RecIsOnline((void*)param_1)
                ? (char)1 : (char)0;
    if ((cVar1 != '\0') &&
        (cVar1 = RecIsOnline((void*)param_2)
             ? (char)1 : (char)0,
         cVar1 == '\0')) {
        return true;
    }
    int64_t vA = RecCmpKey(param_1);
    int64_t vB = RecCmpKey(param_2);
    if ((int)vA == (int)vB) {
        uint64_t sA = RecCmpSub(param_1);
        uint64_t sB = RecCmpSub(param_2);
        return sA < sB;
    }
    vA = RecCmpKey(param_1);
    vB = RecCmpKey(param_2);
    return (int)vB < (int)vA;
}

// ================= FUN_14179e020 =================
// the record-vec sort: the range checks (first@
// +0x248 must be <= end@+0x250... literally:
// end < first → invalid; first_check order
// verbatim) then the introsort seam.
void RecVecSort(void* p0) {
    longlong param_1 = (longlong)p0;
    undefined8* puVar1 =
        *(undefined8**)(param_1 + 0x250);
    if (puVar1 <
        *(undefined8**)(param_1 + 0x248)) {
        g_fnLogRemoveInvalid();
    }
    undefined8* puVar2 =
        *(undefined8**)(param_1 + 0x248);
    longlong lVar3 =
        *(longlong*)(param_1 + 0x230);
    if (*(undefined8**)(param_1 + 0x250) <
        puVar2) {
        g_fnLogRemoveInvalid();
    }
    if ((lVar3 == 0) ||
        (lVar3 != *(longlong*)(param_1 + 0x230))) {
        g_fnLogRemoveInvalid();
    }
    g_fnSortRange(
        (void*)puVar2, (void*)puVar1,
        (longlong)((longlong)puVar1 -
                   (longlong)puVar2) >> 3,
        (void*)RecComparator);
}

// ================= FUN_141721b50 =================
uint32_t SessOwnerGetter(void* pSess) {
    return *(uint32_t*)((longlong)pSess + 0x54);
}

// ================= FUN_141767cd0 =================
// the session-map branch: the 0x4f0 owner check
// (141721b50) → the map insert (seam 141760f10)
// → the checked unwrap → the send (seam
// 14172eae0).
void SessionMapBranch(void* p0, uint32_t uId,
                      uint32_t uSyn) {
    longlong param_1 = (longlong)p0;
    longlong lVar2;
    uint32_t local_res18[2];
    // the insert's out pair: {local_18, local_10}
    // — ADJACENT slots in the original stack
    longlong aPairIns[2];
    longlong* local_18 = (longlong*)&aPairIns[0];
    longlong& local_10 = aPairIns[1];

    if ((uId != 0) && (uSyn != 0)) {
        local_res18[0] = uSyn;
        if ((*(longlong*)(param_1 + 0x4f0) == 0) ||
            (uSyn != SessOwnerGetter(
                         *(void**)(param_1 +
                                   0x4f0)))) {
            g_fnTreeInsertF10(
                (void*)(param_1 + 0x4b0),
                (void*)local_18, local_res18);
            lVar2 = *(longlong*)(param_1 + 0x4e0);
            if ((local_18 == (longlong*)0x0) ||
                (local_18 !=
                 *(longlong**)(param_1 + 0x4b0))) {
                g_fnLogRemoveInvalid();
            }
            if (local_10 == lVar2) {
                return;
            }
            if (local_18 == (longlong*)0x0) {
                g_fnLogRemoveInvalid();
                lVar2 = 0;
            }
            else {
                lVar2 = *local_18;
            }
            if (local_10 ==
                *(longlong*)(lVar2 + 0x30)) {
                g_fnLogRemoveInvalid();
            }
            lVar2 = *(longlong*)(local_10 + 0x20);
            if (lVar2 == 0) {
                g_fnLogRemoveLogError();
                return;
            }
        }
        else {
            lVar2 = *(longlong*)(param_1 + 0x4f0);
        }
        g_fnSendToSession((void*)lVar2, uId);
    }
}

// ================= FUN_141774ba0 =================
// the erase prep: the find (seam 141760af0)
// writes the {node, next} pair; the erase (seam
// 141773e60) only when the pair differs.
void ErasePrep(void* p0, uint32_t uId) {
    longlong param_1 = (longlong)p0;
    longlong* plVar1;
    longlong lVar2;
    uint32_t local_res10[6];
    // the find's out pair: {local_28, lStack_20}
    // — ADJACENT slots in the original stack
    longlong aPairFind[2];
    longlong& local_28 = aPairFind[0];
    longlong& lStack_20 = aPairFind[1];
    undefined8 local_18[2];

    if (uId != 0) {
        plVar1 = (longlong*)(param_1 + 0x2b0);
        local_res10[0] = uId;
        g_fnTreeFindAF0((void*)plVar1,
                        (void*)&aPairFind[0],
                        local_res10);
        lVar2 = *(longlong*)(param_1 + 0x2e0);
        if ((*plVar1 == 0) ||
            (*plVar1 != local_28)) {
            g_fnLogRemoveInvalid();
        }
        if (lVar2 != lStack_20) {
            g_fnTreeErase((void*)plVar1,
                          (void*)local_18,
                          (void*)&aPairFind[0]);
        }
    }
}

// ================= FUN_1417ac620 =================
// the flow itself (the D59 seam body).
void LogRemoveFlow(void* p0, uint32_t uId) {
    longlong param_1 = (longlong)p0;
    longlong* plVar2;
    longlong lVar4;
    uint64_t uVar3;
    uint32_t uVar1;

    plVar2 = (longlong*)LogRecMapFind(
        *(void**)(param_1 + 0x18), uId);
    if (plVar2 == (longlong*)0x0) {
        lVar4 = AcctTreeFind(
            *(void**)(param_1 + 0x50), uId);
        if (lVar4 == 0) {
            return;
        }
        AcctFieldSet((void*)lVar4, uId, 8, 0);
    }
    else {
        RecFlagTick(plVar2, 0);
        uVar3 = RecRankGet(plVar2);
        lVar4 = LeagueMemberLookup(
            *(void**)(param_1 + 0x10),
            (uint32_t)uVar3);
        if (lVar4 != 0) {
            RecVecSort((void*)lVar4);
        }
    }
    // ORIGINAL: (**(code **)(**(longlong **)
    //   (param_1 + 8) + 0x4a8))(*(longlong **)
    //   (param_1 + 8), param_2)
    void* pMgr = *(void**)(param_1 + 8);
    void** pVtMgr = *(void***)pMgr;
    uVar1 = (uint32_t)((uint64_t(*)(void*, int64_t))
        pVtMgr[0x4a8 / 8])(pMgr, uId);
    if (uVar1 != 0) {
        SessionMapBranch(
            *(void**)(param_1 + 0x50), uId, uVar1);
    }
    ErasePrep(*(void**)(param_1 + 0x50), uId);
}

}  // namespace syndicate

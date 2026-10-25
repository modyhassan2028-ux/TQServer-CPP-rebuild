// ============================================================
// Syndicate.dll port — unit T8/D34: the league SORT
// COMPARATOR subgraph, verbatim (see the header).
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_1417b6210 @ 1417b6210 (the singleton)
//   FUN_1417c8f70 @ 1417c8f70 (the map find)
//   FUN_1417cad00 @ 1417cad00 (the member lookup)
//   FUN_14178f270 @ 14178f270 (the rank getter)
//   FUN_14178f410 @ 14178f410 (the secondary getter)
//   FUN_1417ba4c0 @ 1417ba4c0 (the comparator)
// ============================================================
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"

namespace syndicate {

// ================= the seams =================
void* (*g_fnLeagueOpNew)(size_t) = nullptr;
void (*g_fnLeagueInvalid)() = nullptr;
void* (*g_fnLeagueLogFactory)() = nullptr;
void (*g_fnLeagueLogWrite)(void* pLog, uint32_t uId, int nLevel) = nullptr;
void* g_pLeagueVftLogic = nullptr;
void* g_pLeagueVftProvider = nullptr;
void* g_pLeagueDatInstance = nullptr;
// g_fnLeagueCmp is DEFINED in SyndicateLeagueSort.cpp (the
// D33 seam owner) — here only the extern declaration applies.

// ================= FUN_1417b6210 =================
// the CSyndicateLogic singleton: DAT_141886dd0; on the
// first call new 0x88 + the vftable stores (IProvider then
// CSyndicateLogic — the second store wins = the final
// vptr) + the zero fill (slots [1..0xb], the byte at +0xc,
// the UNALIGNED qwords at +0x61/+0x69/+0x71/+0x79).
void* LeagueSingleton() {
    char* pc;
    if (g_pLeagueDatInstance == (void*)0x0) {
        // ORIGINAL: DAT_141886dd0 = operator_new(0x88);
        g_pLeagueDatInstance = g_fnLeagueOpNew(0x88);
        if (g_pLeagueDatInstance == (void*)0x0) {
            g_pLeagueDatInstance = (void*)0x0;
        }
        else {
            pc = (char*)g_pLeagueDatInstance;
            // ORIGINAL: *DAT_141886dd0 = syndicate::IProvider::vftable;
            *(void**)pc = g_pLeagueVftProvider;
            // ORIGINAL: *DAT_141886dd0 = syndicate::CSyndicateLogic::vftable;
            *(void**)pc = g_pLeagueVftLogic;
            *(void**)(pc + 8) = (void*)0x0;        // [1]
            *(void**)(pc + 0x10) = (void*)0x0;     // [2]
            *(void**)(pc + 0x18) = (void*)0x0;     // [3]
            *(void**)(pc + 0x20) = (void*)0x0;     // [4]
            *(void**)(pc + 0x28) = (void*)0x0;     // [5]
            *(void**)(pc + 0x30) = (void*)0x0;     // [6]
            *(void**)(pc + 0x38) = (void*)0x0;     // [7]
            *(void**)(pc + 0x40) = (void*)0x0;     // [8]
            *(void**)(pc + 0x48) = (void*)0x0;     // [9]
            *(void**)(pc + 0x50) = (void*)0x0;     // [10]
            *(void**)(pc + 0x58) = (void*)0x0;     // [0xb]
            // ORIGINAL: *(undefined1 *)(DAT_141886dd0 + 0xc) = 0;
            // the base is undefined8* — slot 0xc = byte +0x60
            *(uint8_t*)(pc + 0xc * 8) = 0;
            *(void**)(pc + 0x61) = (void*)0x0;
            *(void**)(pc + 0x69) = (void*)0x0;
            *(void**)(pc + 0x71) = (void*)0x0;
            *(void**)(pc + 0x79) = (void*)0x0;
        }
        if (g_pLeagueDatInstance == (void*)0x0) {
            // ORIGINAL: log_InlineLogERROR(&DAT_141824ca8);
            void* pLog = g_fnLeagueLogFactory();
            g_fnLeagueLogWrite(pLog, 0, 1);
        }
    }
    return g_pLeagueDatInstance;
}

// ================= FUN_1417c8f70 =================
// the map find on the 0x30-node member map: the
// lower_bound descent + the found/end gate; the
// output iterator pair {anchor, node-or-head}.
// NOTE: Ghidra's local_28/local_20 and local_18/local_10
// are ADJACENT 16-byte iterator homes — the port models
// each as a 2-slot array (the raw separate locals are NOT
// guaranteed adjacent under our compiler).
void* LeagueMapFind(void* pMap, void** pOutIter, uint32_t* pKey) {
    char** pplMap = (char**)pMap;
    char* pcVar4;
    char* pcVar1;
    char* pcVar2;
    char* local_28[2];   // the found pair {anchor, node}
    char* local_18[2];   // the end pair {anchor, head}
    char** pplVar3;

    // ORIGINAL: puVar4 = (undefined8 *)param_1[6];
    char* pcHead = pplMap[6];
    pcVar4 = pcHead;
    // ORIGINAL: if (*(char *)((longlong)puVar4[1] + 0x29) == '\0')
    if (*(char*)((long long)*(char**)(pcHead + 8) + 0x29) == '\0') {
        pcVar1 = *(char**)(pcHead + 8);   // the root = head->parent
        do {
            if (*(uint32_t*)(pcVar1 + 0x18) < *pKey) {
                pcVar2 = *(char**)(pcVar1 + 0x10);   // right
            }
            else {
                pcVar2 = *(char**)pcVar1;            // left
                pcVar4 = pcVar1;
            }
            pcVar1 = pcVar2;
        } while (*(char*)((long long)pcVar2 + 0x29) == '\0');
    }
    // ORIGINAL: puVar1 = (undefined8 *)param_1[6];
    char* pcHead2 = pplMap[6];
    // ORIGINAL: local_20 = puVar4; local_28 = *param_1;
    local_28[1] = pcVar4;
    local_28[0] = *pplMap;
    if (*pplMap == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    // ORIGINAL: if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3)))
    if ((pcVar4 == pcHead2) || (*pKey < *(uint32_t*)(pcVar4 + 0x18))) {
        pplVar3 = local_18;
        // ORIGINAL: local_18 = *param_1; local_10 = param_1[6];
        local_18[0] = *pplMap;
        local_18[1] = pplMap[6];
    }
    else {
        pplVar3 = local_28;
    }
    // ORIGINAL: *param_2 = *plVar3; param_2[1] = plVar3[1];
    ((char**)pOutIter)[0] = pplVar3[0];
    ((char**)pOutIter)[1] = pplVar3[1];
    return pOutIter;
}

// ================= FUN_1417cad00 =================
// the member lookup: the 0-key gate + the find on the map
// at mgr+8 + the iterator checks + the value at node+0x20.
// the out pair from the find = {anchor, node} (the CRT
// iterator: owner + the value slot).
int64_t LeagueMemberLookup(void* pMgr, uint32_t uId) {
    char* pcMgr = (char*)pMgr;
    char* local_18[2] = {(char*)0, (char*)0};   // {anchor, node}
    int64_t lVar1;
    uint32_t local_res10[2];

    if (uId != 0) {
        local_res10[0] = uId;
        // ORIGINAL: FUN_1417c8f70((longlong *)(param_1 + 8),(longlong *)&local_18,local_res10);
        LeagueMapFind(pcMgr + 8, (void**)local_18, local_res10);
        // ORIGINAL: lVar1 = *(longlong *)(param_1 + 0x38);
        lVar1 = *(int64_t*)(pcMgr + 0x38);      // the map head
        // ORIGINAL: if ((local_18 == 0) || (local_18 != *(longlong **)(param_1 + 8)))
        if ((local_18[0] == (char*)0x0) || (local_18[0] != *(char**)(pcMgr + 8))) {
            g_fnLeagueInvalid();
        }
        // ORIGINAL: if (local_10 != lVar1)  (the node != head gate)
        if (local_18[1] != (char*)lVar1) {
            if (local_18[0] == (char*)0x0) {
                g_fnLeagueInvalid();
                lVar1 = 0;
            }
            else {
                // ORIGINAL: lVar1 = *local_18;
                lVar1 = *(int64_t*)local_18[0];   // the anchor's owner back-ref
            }
            // ORIGINAL: if (local_10 == *(longlong *)(lVar1 + 0x30))
            if (local_18[1] == *(char**)(lVar1 + 0x30)) {
                g_fnLeagueInvalid();
            }
            // ORIGINAL: return *(undefined8 *)(local_10 + 0x20);
            return *(int64_t*)(local_18[1] + 0x20);
        }
    }
    return 0;
}

// ================= FUN_14178f270 =================
// the rank getter: the +0x428 provider gate + the log +
// the resolve chain (vt+0x10 with arg 0) + the read vt+0x40.
uint64_t LeagueMemberRank(int64_t lMember) {
    char* pcMember = (char*)lMember;
    void** pplProvider;
    void* pvResolved;
    uint64_t uVar2;

    // ORIGINAL: if (*(longlong *)(param_1 + 0x428) == 0)
    if (*(int64_t*)(pcMember + 0x428) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    pplProvider = *(void***)(pcMember + 0x428);
    // ORIGINAL: plVar1 = (**(code **)(**(longlong **)(param_1 + 0x428) + 0x10))(*(longlong **)(param_1 + 0x428),0);
    // resolve = (provider->vt[0x10])(provider, 0)
    {
        void** ppvt = *(void***)pplProvider;
        void* (*pfnResolve)(void**, uint64_t) = (void* (*)(void**, uint64_t))((void**)ppvt)[2];
        pvResolved = pfnResolve(pplProvider, 0);
    }
    // ORIGINAL: uVar2 = (**(code **)(*plVar1 + 0x40))(plVar1);
    {
        void** pplvt = *(void***)pvResolved;
        uint64_t (*pfnGet)(void**) = (uint64_t (*)(void**))((void**)pplvt)[8];
        uVar2 = pfnGet((void**)pvResolved);
    }
    return uVar2;
}

// ================= FUN_14178f410 =================
// the secondary getter: the same chain with arg 0x2d +
// the read vt+0x48.
uint64_t LeagueMemberSec(int64_t lMember) {
    char* pcMember = (char*)lMember;
    void** pplProvider;
    void* pvResolved;
    uint64_t uVar2;

    if (*(int64_t*)(pcMember + 0x428) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    pplProvider = *(void***)(pcMember + 0x428);
    {
        void** ppvt = *(void***)pplProvider;
        // ORIGINAL: ...(...(*(longlong **)(param_1 + 0x428),0x2d));
        void* (*pfnResolve)(void**, uint64_t) = (void* (*)(void**, uint64_t))((void**)ppvt)[2];
        pvResolved = pfnResolve(pplProvider, 0x2d);
    }
    // ORIGINAL: uVar2 = (**(code **)(*plVar1 + 0x48))(plVar1);
    {
        void** pplvt = *(void***)pvResolved;
        uint64_t (*pfnGet)(void**) = (uint64_t (*)(void**))((void**)pplvt)[9];
        uVar2 = pfnGet((void**)pvResolved);
    }
    return uVar2;
}

// ================= FUN_1417ba4c0 =================
// the comparator (state, a, b): a missing → false;
// b missing OR rank(a) == the state → true;
// state == rank(b) → false; sec equal → rank(a) < rank(b);
// else sec(b) < sec(a) (the DESCENDING secondary key).
bool LeagueMemberCmp(int* pState, uint32_t uA, uint32_t uB) {
    void** pplSingleton;
    int64_t lVar2;
    int64_t lVar3;
    uint64_t uVar4;
    uint64_t uVar5;

    pplSingleton = (void**)LeagueSingleton();
    // ORIGINAL: lVar2 = FUN_1417cad00(puVar1[2],param_2);
    lVar2 = LeagueMemberLookup(pplSingleton[2], uA);
    if (lVar2 != 0) {
        // ORIGINAL: lVar3 = FUN_1417cad00(puVar1[2],param_3);
        lVar3 = LeagueMemberLookup(pplSingleton[2], uB);
        if ((lVar3 == 0) ||
            (uVar4 = LeagueMemberRank(lVar2), *pState == (int)uVar4)) {
            return true;
        }
        // ORIGINAL: uVar4 = FUN_14178f270(lVar3);
        uVar4 = LeagueMemberRank(lVar3);
        if (*pState != (int)uVar4) {
            // ORIGINAL: uVar4 = FUN_14178f410(lVar3); uVar5 = FUN_14178f410(lVar2);
            uVar4 = LeagueMemberSec(lVar3);
            uVar5 = LeagueMemberSec(lVar2);
            if ((int)uVar5 == (int)uVar4) {
                // ORIGINAL: uVar4 = FUN_14178f270(lVar3); uVar5 = FUN_14178f270(lVar2);
                uVar4 = LeagueMemberRank(lVar3);
                uVar5 = LeagueMemberRank(lVar2);
                return (uint32_t)uVar5 < (uint32_t)uVar4;
            }
            // ORIGINAL: uVar4 = FUN_14178f410(lVar3); uVar5 = FUN_14178f410(lVar2);
            uVar4 = LeagueMemberSec(lVar3);
            uVar5 = LeagueMemberSec(lVar2);
            return (int)uVar4 < (int)uVar5;
        }
    }
    return false;
}

}  // namespace syndicate

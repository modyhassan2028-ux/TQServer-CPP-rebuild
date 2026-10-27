// ============================================================
// Syndicate.dll port — unit T10/D36 part 1 — see the header.
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_141745520 / FUN_1417d4e70 / FUN_1417d4d60 /
//   FUN_14172b520 / FUN_141749980 / FUN_14174bac0 / FUN_14174be40
// ============================================================
#include "modules/syndicate/src/SyndicateLeagueMember.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"   // g_fnLeagueInvalid + the log seams
#include <new>

namespace syndicate {

void* g_pLeagueTokenVft = nullptr;   // syndicate::CToken::vftable

// ================= FUN_141745520 =================
// the league id getter: if the provider at +8 is null → log +
// 0; else resolve(0) then the call at rec-vt+0x48.
uint64_t LeagueGetId(int64_t lEntity) {
    char* pcEnt = (char*)lEntity;
    if (*(int64_t*)(pcEnt + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    // ORIGINAL: plVar1 = (resolve(provider, 0));
    void** pplProvider = *(void***)(pcEnt + 8);
    void** ppvt = *(void***)pplProvider;
    void* (*pfnResolve)(void**, uint64_t) =
        (void* (*)(void**, uint64_t))((void**)ppvt)[2];   // vt+0x10
    void** pplRec = (void**)pfnResolve(pplProvider, 0);
    // ORIGINAL: uVar2 = (**(code **)(*plVar1 + 0x48))(plVar1);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn48)(void**) =
        (uint64_t (*)(void**))((void**)ppvt2)[9];   // 0x48/8
    return pfn48(pplRec);
}

// ================= FUN_1417d4e70 =================
// the token key getter: the same chain with resolve(2) and the
// read at rec-vt+0x40.
uint64_t LeagueTokenKey(int64_t lToken) {
    char* pcTok = (char*)lToken;
    if (*(int64_t*)(pcTok + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    void** pplProvider = *(void***)(pcTok + 8);
    void** ppvt = *(void***)pplProvider;
    void* (*pfnResolve)(void**, uint64_t) =
        (void* (*)(void**, uint64_t))((void**)ppvt)[2];
    void** pplRec = (void**)pfnResolve(pplProvider, 2);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn40)(void**) =
        (uint64_t (*)(void**))((void**)ppvt2)[8];   // 0x40/8
    return pfn40(pplRec);
}

// ================= FUN_1417d4d60 =================
// the CToken ctor: null in → 0; else new 0x10 storing the
// CToken vftable and the rec at [1].
void* LeagueTokenNew(int64_t lRec) {
    void** ppNew;
    if (lRec == 0) {
        ppNew = (void**)0x0;
    }
    else {
        ppNew = (void**)operator new(0x10);
        if (ppNew == (void**)0x0) {
            ppNew = (void**)0x0;
        }
        else {
            // ORIGINAL: *puVar1 = syndicate::CToken::vftable;
            ppNew[0] = g_pLeagueTokenVft;
            ppNew[1] = (void*)lRec;
        }
    }
    return ppNew;
}

// ================= FUN_14172b520 =================
// the find on the users map (0x30 nodes, isnil@+0x29): the
// lower_bound descent + the found/end gate; the output iterator
// {anchor, node-or-head} as an ADJACENT pair (arrays per the
// D34 adjacency rule).
void* LeagueUserFind(int64_t lMap, void* pOutIter, uint32_t* pKey) {
    char** pplMap = (char**)lMap;
    char* pcVar4;
    char* pcVar1;
    char* pcVar2;
    char* local_28[2];   // the found pair {anchor, node}
    char* local_18[2];   // the end pair {anchor, head}
    char** pplVar3;

    // ORIGINAL: puVar4 = (undefined8 *)param_1[6];
    char* pcHead = pplMap[6];
    pcVar4 = pcHead;
    if (*(char*)(*(char**)(pcHead + 8) + 0x29) == '\0') {
        pcVar1 = *(char**)(pcHead + 8);   // the root
        do {
            if (*(uint32_t*)(pcVar1 + 0x18) < *pKey) {
                pcVar2 = *(char**)(pcVar1 + 0x10);   // right
            }
            else {
                pcVar2 = *(char**)pcVar1;            // left
                pcVar4 = pcVar1;
            }
            pcVar1 = pcVar2;
        } while (*(char*)(pcVar2 + 0x29) == '\0');
    }
    char* pcHead2 = pplMap[6];
    local_28[1] = pcVar4;
    local_28[0] = *pplMap;
    if (*pplMap == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    if ((pcVar4 == pcHead2) || (*pKey < *(uint32_t*)(pcVar4 + 0x18))) {
        pplVar3 = local_18;
        local_18[0] = *pplMap;
        local_18[1] = pplMap[6];
    }
    else {
        pplVar3 = local_28;
    }
    ((char**)pOutIter)[0] = pplVar3[0];
    ((char**)pOutIter)[1] = pplVar3[1];
    return pOutIter;
}

// ================= FUN_141749980 =================
// the find on the members map — the SAME shape with the isnil
// byte at +0x3d (a DIFFERENT node family).
void* LeagueMemberFind(int64_t lMap, void* pOutIter, uint32_t* pKey) {
    char** pplMap = (char**)lMap;
    char* pcVar4;
    char* pcVar1;
    char* pcVar2;
    char* local_28[2];
    char* local_18[2];
    char** pplVar3;

    char* pcHead = pplMap[6];
    pcVar4 = pcHead;
    if (*(char*)(*(char**)(pcHead + 8) + 0x3d) == '\0') {
        pcVar1 = *(char**)(pcHead + 8);
        do {
            if (*(uint32_t*)(pcVar1 + 0x18) < *pKey) {
                pcVar2 = *(char**)(pcVar1 + 0x10);
            }
            else {
                pcVar2 = *(char**)pcVar1;
                pcVar4 = pcVar1;
            }
            pcVar1 = pcVar2;
        } while (*(char*)(pcVar2 + 0x3d) == '\0');
    }
    char* pcHead2 = pplMap[6];
    local_28[1] = pcVar4;
    local_28[0] = *pplMap;
    if (*pplMap == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    if ((pcVar4 == pcHead2) || (*pKey < *(uint32_t*)(pcVar4 + 0x18))) {
        pplVar3 = local_18;
        local_18[0] = *pplMap;
        local_18[1] = pplMap[6];
    }
    else {
        pplVar3 = local_28;
    }
    ((char**)pOutIter)[0] = pplVar3[0];
    ((char**)pOutIter)[1] = pplVar3[1];
    return pOutIter;
}

// ================= FUN_14174bac0 =================
// the member-data lookup on the tokens map: the INLINE
// lower_bound (the right-branch candidate round-trip) + the
// iterator checks + the value@+0x20 (0 when not found).
void* LeagueMemberData(int64_t lEntity, uint32_t uToken) {
    char* pcEnt = (char*)lEntity;
    char* pcVar3;
    char* pcVar8;
    char* pcVar5;
    char* pcVar4;
    int64_t lVar4;
    int64_t lVar9;
    void* pvRet;
    // the iterator homes (ADJACENT pairs per the D34 rule)
    char foundPair[2][8];
    char endPair[2][8]; char (*pcPairSel)[8];

    // the inline lower_bound on the tokens map (anchor@+0xd8, head@+0x108)
    char* pcHead = *(char**)(pcEnt + 0x108);
    char* pcVar8b = *(char**)(pcHead + 8);   // the root
    char cVar1 = *(char*)(pcVar8b + 0x29);
    pcVar3 = pcHead;
    while (cVar1 == '\0') {
        if (*(uint32_t*)(pcVar8b + 0x18) < uToken) {
            pcVar5 = *(char**)(pcVar8b + 0x10);   // right
            pcVar8b = pcVar3;                       // the round-trip
        }
        else {
            pcVar5 = *(char**)pcVar8b;             // left
        }
        pcVar3 = pcVar8b;
        pcVar8b = pcVar5;
        cVar1 = *(char*)(pcVar5 + 0x29);
    }
    char* pcHeadAgain = *(char**)(pcEnt + 0x108);
    char* pcAnchor = *(char**)(pcEnt + 0xd8);
    if (pcAnchor == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    if ((pcVar3 == pcHeadAgain) || (uToken < *(uint32_t*)(pcVar3 + 0x18))) {
        // ORIGINAL: plVar7 = &local_28; local_20 = head; local_28 = anchor;
        *(char**)endPair[0] = pcAnchor;
        *(char**)endPair[1] = pcHeadAgain;
        pcPairSel = endPair;
    }
    else {
        *(char**)foundPair[0] = pcAnchor;
        *(char**)foundPair[1] = pcVar3;
        pcPairSel = foundPair;
    }
    // ORIGINAL: plVar2 = (longlong *)*plVar7; lVar9 = head;
    char* plVar2 = *(char**)pcPairSel[0];
    lVar9 = (int64_t)pcHeadAgain;
    char* local_18 = plVar2;      // the pair copy
    int64_t local_10 = *(int64_t*)pcPairSel[1];
    if ((pcAnchor == (char*)0x0) || (pcAnchor != plVar2)) {
        g_fnLeagueInvalid();
    }
    lVar4 = local_10;
    if (lVar9 == local_10) {
        pvRet = (void*)0x0;   // not found → 0
    }
    else {
        int64_t lTmp;
        if (plVar2 == (char*)0x0) {
            g_fnLeagueInvalid();
            lTmp = 0;
        }
        else {
            lTmp = *(int64_t*)plVar2;   // the owner back-ref
        }
        if (lVar4 == *(int64_t*)(lTmp + 0x30)) {
            g_fnLeagueInvalid();
        }
        pvRet = *(void**)(lVar4 + 0x20);   // the member data
    }
    return pvRet;
}

// ================= FUN_14174be40 =================
// the user's league: the walk on the USERS map (anchor@+0x58,
// head@+0x88) + the found record's resolve(3) → vt+0x20; the
// not-found / null-record paths return 0 (the &0xff...00 tail).
uint64_t LeagueUserLeague(int64_t lEntity, uint32_t uUser) {
    char* pcEnt = (char*)lEntity;
    char* pcVar3;
    char* pcVar5;
    char* pcVar8;
    char* pcVar4;
    char* plVar2;
    char* plVar6;
    char* plVar5;
    int64_t lVar4;
    int64_t lVar9;
    char foundPair[2][8];
    char endPair[2][8]; char (*pcPairSel)[8];

    // the inline lower_bound on the users map
    char* pcHead = *(char**)(pcEnt + 0x88);
    char* pcVar8b = *(char**)(pcHead + 8);
    char cVar1 = *(char*)(pcVar8b + 0x29);
    pcVar3 = pcHead;
    while (cVar1 == '\0') {
        if (*(uint32_t*)(pcVar8b + 0x18) < uUser) {
            pcVar5 = *(char**)(pcVar8b + 0x10);
            pcVar8b = pcVar3;
        }
        else {
            pcVar5 = *(char**)pcVar8b;
        }
        pcVar3 = pcVar8b;
        pcVar8b = pcVar5;
        cVar1 = *(char*)(pcVar5 + 0x29);
    }
    char* pcHeadAgain = *(char**)(pcEnt + 0x88);
    char* pcAnchor = *(char**)(pcEnt + 0x58);
    if (pcAnchor == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    if ((pcVar3 == pcHeadAgain) || (uUser < *(uint32_t*)(pcVar3 + 0x18))) {
        *(char**)endPair[0] = pcAnchor;
        *(char**)endPair[1] = pcHeadAgain;
        pcPairSel = endPair;
    }
    else {
        *(char**)foundPair[0] = pcAnchor;
        *(char**)foundPair[1] = pcVar3;
        pcPairSel = foundPair;
    }
    plVar2 = *(char**)pcPairSel[0];
    lVar9 = (int64_t)pcHeadAgain;
    char* local_18 = plVar2;
    int64_t local_10 = *(int64_t*)pcPairSel[1];
    plVar6 = pcAnchor;
    if ((plVar6 == (char*)0x0) || (plVar6 != plVar2)) {
        g_fnLeagueInvalid();
    }
    lVar4 = local_10;
    if (lVar9 != local_10) {
        int64_t lTmp;
        if (plVar2 == (char*)0x0) {
            g_fnLeagueInvalid();
            lTmp = 0;
        }
        else {
            lTmp = *(int64_t*)plVar2;
        }
        if (lVar4 == *(int64_t*)(lTmp + 0x30)) {
            g_fnLeagueInvalid();
        }
        // ORIGINAL: plVar2 = *(longlong **)(lVar4 + 0x20);
        plVar5 = *(char**)(lVar4 + 0x20);   // the member record
        if (plVar5 != (char*)0x0) {
            // ORIGINAL: plVar6 = (resolve(rec, 3));
            void** pplRec = (void**)plVar5;
            void** ppvt = *(void***)pplRec;
            void* (*pfnResolve)(void**, uint64_t) =
                (void* (*)(void**, uint64_t))((void**)ppvt)[2];   // vt+0x10
            void** pplRes = (void**)pfnResolve(pplRec, 3);
            // ORIGINAL: uVar7 = (**(code **)(*plVar6 + 0x20))(plVar6);
            void** ppvt2 = *(void***)pplRes;
            uint64_t (*pfn20)(void**) =
                (uint64_t (*)(void**))((void**)ppvt2)[4];   // vt+0x20
            return pfn20(pplRes);
        }
    }
    // ORIGINAL: return (ulonglong)plVar6 & 0xffffffffffffff00;
    return (uint64_t)plVar6 & (uint64_t)0xffffffffffffff00;
}

}  // namespace syndicate

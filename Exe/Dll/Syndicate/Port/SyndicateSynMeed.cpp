// ============================================================
// Syndicate.dll port — D45/T16: the CSynArenicMeed query
// layer (see SyndicateSynMeed.h for the address map).
// ============================================================
#include "SyndicateSynMeed.h"
#include "SyndicateCrossMerit.h"
#include "SyndicateModule.h"   // g_fnGetServiceInst (1417b6210)
#include <cstdlib>

namespace syndicate {

// ---- the seam defaults ----
static void DefMeedLog() {}
static int DefMgrUserId(void*) { return 0; }
static void DefMgrVt3a8(void*) {}
static void DefMgrVt378(void*, int) {}
static uint64_t DefMeedGradeOf(void*, uint64_t, int)
    { return 0; }
static void* DefMeedSub5(void* p) { return p; }
static int DefMeedSub5Flag(void*) { return 0; }
static void* DefMeedSub2(void* p) { return p; }
static int DefMeedSub2Id(void*) { return 0; }

void (*g_fnMeedLog)() = DefMeedLog;
int (*g_fnMgrUserId)(void* pMgr) = DefMgrUserId;
void (*g_fnMgrVt3a8)(void* pMgr) = DefMgrVt3a8;
void (*g_fnMgrVt378)(void* pMgr, int n)
    = DefMgrVt378;
uint64_t (*g_fnMeedGradeOf)(void*, uint64_t, int)
    = DefMeedGradeOf;
void* (*g_fnMeedSub5)(void*) = DefMeedSub5;
int (*g_fnMeedSub5Flag)(void*) = DefMeedSub5Flag;
void* (*g_fnMeedSub2)(void*) = DefMeedSub2;
int (*g_fnMeedSub2Id)(void*) = DefMeedSub2Id;

// ---- FUN_14177ace0: the 0x30 tree head ----
// (the MSVC debug-op_new zero guards verbatim)
void* MeedHeadNew() {
    char* puVar1 = (char*)g_fnMeritOpNew(0x30);
    if (puVar1 != nullptr) {
        *(int64_t*)puVar1 = 0;
    }
    if (puVar1 + 8 != nullptr) {
        *(int64_t*)(puVar1 + 8) = 0;
    }
    if (puVar1 + 0x10 != nullptr) {
        *(int64_t*)(puVar1 + 0x10) = 0;
    }
    *(uint8_t*)(puVar1 + 0x28) = 1;   // color: black
    *(uint8_t*)(puVar1 + 0x29) = 0;   // isnil: real
    return puVar1;
}

// ---- FUN_14177c6c0: the singleton ctor (0x40) ----
void* MeedSingletonCtor(void* pThis) {
    char** ppc = (char**)pThis;
    void* puVar1 = g_fnMeritOpNew(8);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        *(void**)puVar1 = pThis;
    }
    ppc[0] = (char*)puVar1;          // the proxy
    char* pHead = (char*)MeedHeadNew();
    ppc[6] = pHead;                  // head @+0x30
    *(uint8_t*)(pHead + 0x29) = 1;   // nil head
    *(char**)(pHead + 8) = pHead;    // parent: self
    *(char**)pHead = pHead;          // left: self
    *(char**)(pHead + 0x10) = pHead; // right: self
    ppc[7] = nullptr;                // size @+0x38
    return pThis;
}

// ---- FUN_14177c770: the lazy singleton get ----
void* g_pMeedSingleton = nullptr;    // DAT_141886d30
void MeedResetSingleton() {
    g_pMeedSingleton = nullptr;
}
void* MeedSingletonGet() {
    if (g_pMeedSingleton == nullptr) {
        void* puVar1 = g_fnMeritOpNew(0x40);
        void* pv = nullptr;
        if (puVar1 == nullptr) {
            g_pMeedSingleton = nullptr;
        } else {
            pv = MeedSingletonCtor(puVar1);
            g_pMeedSingleton = pv;
        }
        if (g_pMeedSingleton == nullptr) {
            g_fnMeedLog();
        }
    }
    return g_pMeedSingleton;
}

// ---- FUN_14177c0a0: the user→league lower_bound ----
// (the 0x29 family: key @+0x18, league value @+0x20,
//  head @map+0x30, the debug-iterator gates verbatim)
void* MeedUserLeague(void* pMap, uint32_t uId) {
    char** ppc = (char**)pMap;
    int64_t lVar7 = 0;
    char* puVar9 = *(char**)(ppc[6] + 8);   // the root
    char cVar1 = *(uint8_t*)(puVar9 + 0x29);
    char* puVar4 = ppc[6];                  // the head
    while (cVar1 == '\0') {
        char* puVar6;
        if (*(uint32_t*)(puVar9 + 0x18) < uId) {
            puVar6 = *(char**)(puVar9 + 0x10); // right
            puVar9 = puVar4;
        } else {
            puVar6 = *(char**)puVar9;          // left
        }
        puVar4 = puVar9;
        puVar9 = puVar6;
        cVar1 = *(uint8_t*)(puVar6 + 0x29);
    }
    // the debug iterator build (verbatim): the found
    // iterator {proxy, candidate} vs the end iterator
    // {proxy, head}
    if (*(int64_t*)ppc == 0) {
        g_fnMeritInvalid();
    }
    int64_t itFound[2] = { *(int64_t*)ppc,
                           (int64_t)puVar4 };
    int64_t itEnd[2] = { *(int64_t*)ppc,
                         (int64_t)ppc[6] };
    int64_t* plVar8;
    if (puVar4 == ppc[6]
        || uId < *(uint32_t*)(puVar4 + 0x18)) {
        plVar8 = itEnd;
    } else {
        plVar8 = itFound;
    }
    int64_t* pIt = plVar8;
    int64_t local_10 = pIt[1];
    int64_t local_18 = *pIt;
    if (*(int64_t*)ppc == 0
        || *(int64_t*)ppc != local_18) {
        g_fnMeritInvalid();
    }
    int64_t lVar3 = (int64_t)ppc[6];     // the head
    int64_t lVar5 = local_10;
    if (lVar3 != lVar5) {
        // dereference the real node
        int64_t lVar6 = (local_18 == 0) ? 0
            : *(int64_t*)local_18;
        if (lVar5 == *(int64_t*)(lVar6 + 0x30)) {
            g_fnMeritInvalid();
        }
        lVar7 = *(int64_t*)(lVar5 + 0x20);
    }
    return (void*)lVar7;
}

// ---- FUN_1417f980 → FUN_14177f980: GetUserGrade ----
uint64_t MeedGetUserGrade(uint64_t uUser, int nType) {
    if ((uint32_t)(nType - 1) > 2) {
        g_fnMeedLog();
        return 0;
    }
    // (the mgr singleton — 1417b6210 — is the test's
    //  bound seam in this layer)
    void* pMgr = g_fnGetServiceInst();
    int uId = g_fnMgrUserId(pMgr);
    if (uId != 0) {
        void* pMeed = MeedSingletonGet();
        void* pLeague = MeedUserLeague(pMeed, uId);
        if (pLeague != nullptr) {
            return g_fnMeedGradeOf(pLeague, uUser,
                                   nType);
        }
    }
    return 0;
}

// ---- FUN_14177fa10: the vt+0x378 pass-through ----
void MeedPostGrade(void* pMgr, uint64_t uA, int nType) {
    (void)uA;
    g_fnMgrVt378(pMgr, nType);
}

// ---- FUN_141740fd0: the members index walk ----
int MeedMemberIndex(void* pMembers, int nId) {
    char* pc = (char*)pMembers;
    if (nId != 0) {
        int64_t* plVar5 =
            *(int64_t**)(pc + 0x20);   // begin
        int iVar7 = 0;
        if (*(int64_t**)(pc + 0x28) < plVar5) {
            g_fnMeritInvalid();
        }
        int64_t* plVar1 =
            *(int64_t**)(pc + 8);     // the dbg proxy
        while (true) {
            int64_t* plVar4 =
                *(int64_t**)(pc + 0x28);  // end
            if (plVar4 < *(int64_t**)(pc + 0x20)) {
                g_fnMeritInvalid();
            }
            if (plVar1 == nullptr
                || plVar1
                       != *(int64_t**)(pc + 8)) {
                g_fnMeritInvalid();
            }
            if (plVar5 == plVar4) break;
            // member = *plVar5 (the proxy unwrap)
            int64_t* plVar3 = (int64_t*)*plVar5;
            if (plVar3 != nullptr) {
                void* pSub5 = g_fnMeedSub5(plVar3);
                int iVar2 = g_fnMeedSub5Flag(pSub5);
                if (iVar2 != 0) {
                    void* pSub2 =
                        g_fnMeedSub2(plVar3);
                    iVar2 =
                        g_fnMeedSub2Id(pSub2);
                    if (iVar2 == nId) {
                        return iVar7;
                    }
                }
            }
            iVar7 = iVar7 + 1;
            // the debug iterator advance (verbatim)
            int64_t lVar6 = (plVar1 == nullptr) ? 0
                : *(int64_t*)plVar1;
            if (*(int64_t*)(lVar6 + 0x20)
                <= (int64_t)plVar5) {
                g_fnMeritInvalid();
            }
            plVar5 = plVar5 + 1;
        }
    }
    return -1;
}

// ---- FUN_141741410: the null gate + the <8 check --
void MeedMemberCheck(void* pObj, int nId) {
    if (pObj == nullptr) {
        g_fnMeedLog();
        return;
    }
    void* pMgr = g_fnGetServiceInst();
    int iVar1 = g_fnMgrUserId(pMgr);
    int uVar2 = MeedMemberIndex(pObj, iVar1);
    if (uVar2 < 8) {
        g_fnMgrVt3a8(pMgr);
    }
}

} // namespace syndicate

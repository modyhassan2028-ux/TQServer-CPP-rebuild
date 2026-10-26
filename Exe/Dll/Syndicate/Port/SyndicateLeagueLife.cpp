// ============================================================
// Syndicate.dll port — T13/D38: the CLeague LIFE cycle,
// verbatim translations (see SyndicateLeagueLife.h).
// ============================================================
#include "SyndicateLeagueLife.h"
#include "SyndicateCrossMerit.h"      // the opnew/opdelete/invalid seams
#include "SyndicateLeagueTree.h"      // LeagueEraseRange/LeagueClear/LeagueErase
#include "SyndicateLeagueUsers.h"    // UsersErase
#include "SyndicateLeagueMembers.h"  // MembersEraseRange/MembersClear
#include "SyndicateLeagueCmp.h"       // the log seams
#include "SyndicateLeagueOps.h"       // the InstanceGet seam
#include "SyndicateLeagueMgr.h"       // g_fnMgrStrCopy
#include "SyndicateLeagueRelease.h"  // the real walks
#include <cstring>

namespace syndicate {

// ---------- the seams ----------
void* g_fnLeagueLifeVftable = nullptr;
// the D38 seams now DEFAULT to the D39 real walks
// (tests may override for isolation)
void (*g_fnLeagueReleaseUsers)(int64_t, int64_t, int64_t,
    int64_t) = &LeagueReleaseUsers;
void (*g_fnLeagueReleaseTokens)(int64_t, int64_t, int64_t,
    int64_t) = &LeagueReleaseTokens;
int (*g_fnLeagueMemMoveS)(void*, size_t, const void*,
                              size_t) = nullptr;

// ================= 141726c90 =================
// the users-family head alloc: opnew(0x30) + the first
// 3 qwords zeroed (the _Isnil/self-links are written by
// the map ctor, not here)
void* LeagueUsersHeadAlloc() {
    char** puVar1 = (char**)g_fnMeritOpNew(0x30);
    if (puVar1 != nullptr) {
        puVar1[0] = nullptr;
    }
    if (puVar1 + 1 != nullptr) {
        puVar1[1] = nullptr;
    }
    if (puVar1 + 2 != nullptr) {
        puVar1[2] = nullptr;
    }
    return puVar1;
}

// ================= 141746a00 =================
// the members-family head alloc: opnew(0x40) + the same
// zero tail
void* LeagueMembersHeadAlloc() {
    char** puVar1 = (char**)g_fnMeritOpNew(0x40);
    if (puVar1 != nullptr) {
        puVar1[0] = nullptr;
    }
    if (puVar1 + 1 != nullptr) {
        puVar1[1] = nullptr;
    }
    if (puVar1 + 2 != nullptr) {
        puVar1[2] = nullptr;
    }
    return puVar1;
}

// ================= 141746a60 =================
// the tokens-family head alloc: opnew(0x30)
void* LeagueTokensHeadAlloc() {
    char** puVar1 = (char**)g_fnMeritOpNew(0x30);
    if (puVar1 != nullptr) {
        puVar1[0] = nullptr;
    }
    if (puVar1 + 1 != nullptr) {
        puVar1[1] = nullptr;
    }
    if (puVar1 + 2 != nullptr) {
        puVar1[2] = nullptr;
    }
    return puVar1;
}

// ================= 141733570 =================
// the entity USERS map ctor: the proxy (opnew(8), the
// owner back-ref) + the 0x30 head + _Isnil@0x29 = 1 +
// the self-links + size 0
void* LeagueUsersMapCtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char** puVar1 = (char**)g_fnMeritOpNew(8);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        *puVar1 = (char*)param_1;
    }
    *param_1 = (char*)puVar1;
    char* lVar2 = (char*)LeagueUsersHeadAlloc();
    param_1[6] = lVar2;
    *(uint8_t*)(lVar2 + 0x29) = 1;
    *(char**)(lVar2 + 8) = lVar2;      // parent
    *(char**)lVar2 = lVar2;           // left
    *(char**)(lVar2 + 0x10) = lVar2;  // right
    param_1[7] = 0;                   // size
    return param_1;
}

// ================= 14174cc70 =================
// the entity MEMBERS map ctor: the same shape with the
// 0x40 head + _Isnil@0x3d
void* LeagueMembersMapCtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char** puVar1 = (char**)g_fnMeritOpNew(8);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        *puVar1 = (char*)param_1;
    }
    *param_1 = (char*)puVar1;
    char* lVar2 = (char*)LeagueMembersHeadAlloc();
    param_1[6] = lVar2;
    *(uint8_t*)(lVar2 + 0x3d) = 1;
    *(char**)(lVar2 + 8) = lVar2;
    *(char**)lVar2 = lVar2;
    *(char**)(lVar2 + 0x10) = lVar2;
    param_1[7] = 0;
    return param_1;
}

// ================= 14174d6b0 =================
// the entity TOKENS map ctor: the same shape with the
// 0x30 head + _Isnil@0x29
void* LeagueTokensMapCtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char** puVar1 = (char**)g_fnMeritOpNew(8);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        *puVar1 = (char*)param_1;
    }
    *param_1 = (char*)puVar1;
    char* lVar2 = (char*)LeagueTokensHeadAlloc();
    param_1[6] = lVar2;
    *(uint8_t*)(lVar2 + 0x29) = 1;
    *(char**)(lVar2 + 8) = lVar2;
    *(char**)lVar2 = lVar2;
    *(char**)(lVar2 + 0x10) = lVar2;
    param_1[7] = 0;
    return param_1;
}

// ================= 1417262c0 =================
// the users-family recursive right-subtree free
void UsersFreeSubtree(void* pMap, void* pNode) {
    char* param_2 = (char*)pNode;
    char cVar1 = *(char*)(param_2 + 0x29);
    char* plVar2;
    while (cVar1 == '\0') {
        UsersFreeSubtree(pMap,
            *(char**)(param_2 + 0x10));  // the right
        plVar2 = *(char**)param_2;        // the left
        g_fnMeritOpDelete(param_2);
        param_2 = plVar2;
        cVar1 = *(char*)(param_2 + 0x29);
    }
}

// ================= 1417276c0 =================
// the users-family clear: the root walk (the subtree
// frees + delete + the left advance) + the head
// relinks + size 0
void UsersClear(void* pMap) {
    char* param_1 = (char*)pMap;
    char* head = *(char**)(param_1 + 0x30);
    char** plVar2 = *(char***)(head + 8);  // the root
    char cVar1 = *(char*)((char*)plVar2 + 0x29);
    while (cVar1 == '\0') {
        UsersFreeSubtree(pMap,
            *(char**)((char*)plVar2 + 0x10));  // right
        char** plVar3 = *(char***)plVar2;
        g_fnMeritOpDelete(plVar2);
        plVar2 = plVar3;
        cVar1 = *(char*)((char*)plVar3 + 0x29);
    }
    *(char**)(head + 8) = head;   // root = head
    *(uint64_t*)(param_1 + 0x38) = 0;
    *(char**)head = head;         // first
    *(char**)(head + 0x10) = head; // last
}

// ================= 14172d3c0 =================
// the users-family erase-range: the owner checks + the
// both-END clear + the inline successor advance loop
void* UsersEraseRange(void* pMap, void* pOutIter,
                      void* pBegin, void* pEnd) {
    char** param_1 = (char**)pMap;
    char** param_2 = (char**)pOutIter;
    char** param_3 = (char**)pBegin;
    char** param_4 = (char**)pEnd;
    char* lVar2 = *(char**)param_1[6];   // *head
    if (*param_3 == nullptr
        || *param_3 != *(char**)param_1) {
        g_fnMeritInvalid();
    }
    if (param_3[1] == (char*)lVar2) {
        lVar2 = (char*)param_1[6];       // the head
        if (*param_4 == nullptr
            || *param_4 != *(char**)param_1) {
            g_fnMeritInvalid();
        }
        if (param_4[1] == lVar2) {
            UsersClear((void*)param_1);
            param_2[1] = *(char**)param_1[6];
            *param_2 = *(char**)param_1;
            return param_2;
        }
    }
    char* plVar6;
    char* plVar5;
    char cVar1;
    while (true) {
        if (*param_3 == nullptr
            || *param_3 != *param_4) {
            g_fnMeritInvalid();
        }
        char* lVar2b = *(char**)param_3;   // the owner
        if (param_3[1] == param_4[1]) break;
        char* lVar3 = param_3[1];         // the node
        if (*param_3 == nullptr) {
            g_fnMeritInvalid();
        }
        char* lVar4 = param_3[1];
        if (*(char*)(lVar4 + 0x29) == '\0') {
            plVar6 = *(char**)(lVar4 + 0x10);  // right
            if (*(char*)(plVar6 + 0x29) == '\0') {
                cVar1 =
                    *(char*)(*(char**)plVar6 + 0x29);
                plVar5 = *(char**)plVar6;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar5 + 0x29);
                    plVar6 = plVar5;
                    plVar5 = *(char**)plVar5;
                }
            } else {
                plVar6 = *(char**)(lVar4 + 8);  // parent
                cVar1 = *(char*)(plVar6 + 0x29);
                while (cVar1 == '\0'
                    && (param_3[1]
                        == *(char**)(plVar6 + 0x10))) {
                    param_3[1] = (char*)plVar6;
                    plVar6 = *(char**)(plVar6 + 8);
                    cVar1 = *(char*)(plVar6 + 0x29);
                }
                param_3[1] = (char*)plVar6;
                goto advance_done;
            }
            param_3[1] = (char*)plVar6;
advance_done:;
        } else {
            g_fnMeritInvalid();
        }
        // the OLD begin node home, then the erase
        char* local_28[2];
        local_28[0] = lVar2b;
        local_28[1] = lVar3;
        char* local_18[2];
        UsersErase((void*)param_1, (void*)local_18,
                   (void*)local_28);
    }
    char* lVar2c = param_3[1];
    *param_2 = *(char**)param_1;
    param_2[1] = lVar2c;
    return param_2;
}

// ================= 141730e80 =================
// the USERS map dtor: the erase-range with BOTH
// iterator homes = END — the {proxy, *head} /
// {proxy, head} pairs — then delete head, head=0,
// size=0
void LeagueUsersMapDtor(void* pMap) {
    char** param_1 = (char**)pMap;
    // local_38 = *map (the proxy); puStack_30 = head;
    // uStack_20 = *head; local_28 = proxy
    char* local_38 = *(char**)param_1;
    char* puStack_30 = (char*)param_1[6];
    char* uStack_20 = *(char**)puStack_30;
    (void)uStack_20;
    // &local_28 home = {proxy, uStack_20}
    char* local_28[2];
    local_28[0] = local_38;
    local_28[1] = uStack_20;
    // &local_38 home = {proxy, puStack_30}
    char* local_38home[2];
    local_38home[0] = local_38;
    local_38home[1] = puStack_30;
    char* local_18[2];
    UsersEraseRange((void*)param_1, (void*)local_18,
                    (void*)local_28, (void*)local_38home);
    g_fnMeritOpDelete((void*)param_1[6]);
    param_1[6] = 0;
    param_1[7] = 0;
}

// ================= 141748720 =================
// the MEMBERS map dtor (the same END-pair shape)
void LeagueMembersMapDtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char* local_38 = *(char**)param_1;
    char* puStack_30 = (char*)param_1[6];
    char* uStack_20 = *(char**)puStack_30;
    (void)uStack_20;
    char* local_28[2];
    local_28[0] = local_38;
    local_28[1] = uStack_20;
    char* local_38home[2];
    local_38home[0] = local_38;
    local_38home[1] = puStack_30;
    char* local_18[2];
    MembersEraseRange((void*)param_1, (void*)local_18,
                      (void*)local_28, (void*)local_38home);
    g_fnMeritOpDelete((void*)param_1[6]);
    param_1[6] = 0;
    param_1[7] = 0;
}

// ================= 14174c530 =================
// the TOKENS map dtor (the same END-pair shape, the
// D32-family erase-range)
void LeagueTokensMapDtor(void* pMap) {
    char** param_1 = (char**)pMap;
    char* local_38 = *(char**)param_1;
    char* puStack_30 = (char*)param_1[6];
    char* uStack_20 = *(char**)puStack_30;
    (void)uStack_20;
    char* local_28[2];
    local_28[0] = local_38;
    local_28[1] = uStack_20;
    char* local_38home[2];
    local_38home[0] = local_38;
    local_38home[1] = puStack_30;
    char* local_18[2];
    LeagueEraseRange((void*)param_1, (void*)local_18,
                     (void*)local_28, (void*)local_38home);
    g_fnMeritOpDelete((void*)param_1[6]);
    param_1[6] = 0;
    param_1[7] = 0;
}

// ================= 1417495d0 =================
// the +0x28 container truncate: the checked-iterator
// gates + the memmove_s tail (the 4-byte elements)
void StringVecEraseTail(void* pContainer) {
    char** param_1 = (char**)pContainer;
    char* _Src = (char*)param_1[4];
    if (_Src < (char*)param_1[3]) {
        g_fnMeritInvalid();
    }
    char* _Dst = (char*)param_1[3];
    if ((char*)param_1[4] < _Dst) {
        g_fnMeritInvalid();
    }
    if ((_Dst < (char*)param_1[3])
        || ((char*)param_1[4] < _Dst)) {
        g_fnMeritInvalid();
    }
    char* lVar1 = *(char**)param_1;   // the proxy
    if ((_Src < (char*)param_1[3])
        || ((char*)param_1[4] < _Src)) {
        g_fnMeritInvalid();
    }
    if ((lVar1 == nullptr) || (lVar1 != *(char**)param_1)) {
        g_fnMeritInvalid();
    }
    if (_Dst != _Src) {
        int64_t cnt = ((char*)param_1[4] - _Src) >> 2;
        size_t _DstSize = (size_t)cnt * 4;
        if (0 < cnt) {
            g_fnLeagueMemMoveS(_Dst, _DstSize, _Src,
                               _DstSize);
        }
        param_1[4] = (char*)((int64_t)_DstSize
                            + (int64_t)_Dst);
    }
}

// ================= 14174d830 =================
// LeagueCtor: the vftable + the +0x28 proxy (opnew(8)
// with the owner back-ref) + the +0x40..+0x50 zeros +
// the three map ctors + provider=0 + leader=0 + the
// name qwords 0
void* LeagueCtor(void* pEntity) {
    char** param_1 = (char**)pEntity;
    *param_1 = (char*)g_fnLeagueLifeVftable;
    char** plVar1 = (char**)g_fnMeritOpNew(8);
    char* plVar2 = nullptr;
    if (plVar1 != nullptr) {
        *plVar1 = (char*)(param_1 + 5);   // owner +0x28
        plVar2 = (char*)plVar1;
    }
    param_1[5] = plVar2;
    param_1[8] = 0;    // +0x40
    param_1[9] = 0;    // +0x48
    param_1[10] = 0;   // +0x50
    LeagueUsersMapCtor((void*)(param_1 + 0xb));    // +0x58
    LeagueMembersMapCtor((void*)(param_1 + 0x13)); // +0x98
    LeagueTokensMapCtor((void*)(param_1 + 0x1b));  // +0xd8
    param_1[1] = 0;   // +0x08 provider
    *(uint32_t*)(param_1 + 2) = 0;   // +0x10 leader
    *(uint64_t*)((char*)param_1 + 0x14) = 0;  // name[0..7]
    *(uint64_t*)((char*)param_1 + 0x1c) = 0;  // name[8..15]
    return param_1;
}

// ================= 14174cfc0 =================
// LeagueDtor: the three map dtors WITH the
// interleaved proxy deletes + the +0x40 block + the
// +0x28 proxy delete
void LeagueDtor(void* pEntity) {
    char** param_1 = (char**)pEntity;
    *param_1 = (char*)g_fnLeagueLifeVftable;
    LeagueTokensMapDtor((void*)(param_1 + 0x1b));  // +0xd8
    g_fnMeritOpDelete((void*)param_1[0x1b]); // the proxy
    LeagueMembersMapDtor((void*)(param_1 + 0x13)); // +0x98
    g_fnMeritOpDelete((void*)param_1[0x13]);
    LeagueUsersMapDtor((void*)(param_1 + 0xb));     // +0x58
    g_fnMeritOpDelete((void*)param_1[0xb]);
    if ((void*)param_1[8] != (void*)0) {
        g_fnMeritOpDelete((void*)param_1[8]);
    }
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
    g_fnMeritOpDelete((void*)param_1[5]);  // the +0x28 proxy
}

// ================= 14174d8d0 =================
// the scalar deleting dtor
void LeagueDeletingDtor(void* pEntity, uint32_t uFlags) {
    LeagueDtor(pEntity);
    if ((uFlags & 1) != 0) {
        g_fnMeritOpDelete(pEntity);
    }
}

// ================= 141743b60 =================
// LeagueInit: the four gates + the InstanceGet + the
// provider resolve + the field writes + the save
typedef int64_t  (*FnV)(void*, int64_t);
typedef FnV*     VtArr;
typedef void     (*FnVv)(void*, int64_t);
typedef FnVv*    VtArrV;
uint32_t LeagueInit(int64_t lEntity, int32_t nId,
                    int64_t lP3, uint8_t uP4, int32_t nP5,
                    const char* pName) {
    char* param_1 = (char*)lEntity;
    if ((((lP3 != 0) && (pName != (const char*)0))
         && (nId != 0)) && (nP5 != 0)) {
        // plVar1 = InstanceGet(); NO null gate here —
        // the original derefs the singleton directly
        void* plVar1 = g_fnLeagueOpsInstance();
        // provider = inst->vt[0x20/8]("cq_league")
        VtArr svt = *(VtArr*)plVar1;
        int64_t lVar2 = svt[4](plVar1, (int64_t)"cq_league");
        *(int64_t*)(param_1 + 8) = lVar2;
        if (lVar2 != 0) {
            *(int32_t*)(param_1 + 0x10) = nP5;
            g_fnMgrStrCopy(param_1 + 0x14, pName, 0x10);
            // resolve(2) → rec->vt[0xb8/8](rec, id)
            VtArr pvt = *(VtArr*)lVar2;
            void* pRec2 = (void*)pvt[2](
                (void*)lVar2, 2);
            VtArrV rvt2 = *(VtArrV*)pRec2;
            rvt2[0x17](pRec2, nId);
            // resolve(1) → rec->vt[0x80/8](rec, p3)
            void* pRec1 = (void*)pvt[2](
                (void*)lVar2, 1);
            VtArrV rvt1 = *(VtArrV*)pRec1;
            rvt1[0x10](pRec1, lP3);
            if (uP4 != 0) {
                // resolve(8) → rec->vt[0xb0/8](rec, 1)
                void* pRec8 = (void*)pvt[2](
                    (void*)lVar2, 8);
                VtArrV rvt8 = *(VtArrV*)pRec8;
                rvt8[0x16](pRec8, 1);
            }
            // the save: provider->vt[0x50/8](provider, 1)
            uint32_t uVar3 =
                (uint32_t)pvt[0xa]((void*)lVar2, 1);
            return uVar3;
        }
    }
    return 0;
}

// ================= 14174a650 =================
// the fail cleanup: the users release walk + the
// tokens release walk + the members clear + the
// +0x28 truncate + the provider dual-release + the
// self deleting dtor
void LeagueFailCleanup(void* pEntity, int64_t lP2,
                      int64_t lP3, int64_t lP4) {
    char** param_1 = (char**)pEntity;
    g_fnLeagueReleaseUsers((int64_t)param_1, lP2,
                           lP3, lP4);
    g_fnLeagueReleaseTokens((int64_t)param_1, lP2,
                            lP3, lP4);
    MembersClear((void*)(param_1 + 0x13));
    StringVecEraseTail((void*)(param_1 + 5));
    if (param_1[1] != 0) {   // the provider @+0x08
        // rec->vt[0](rec, 1) — the dual release
        VtArrV prv = *(VtArrV*)param_1[1];
        prv[0](param_1[1], 1);
        param_1[1] = 0;
        param_1[1] = 0;
    }
    // (**(code **)*param_1)(param_1, 1) — the entity's
    // OWN deleting dtor via the vtable slot 0
    VtArrV evt = *(VtArrV*)param_1;
    evt[0](param_1, 1);
}

// ================= 14174d900 =================
// LeagueCreate: the four gates + opnew(0x118) + the
// ctor + the null log + the init + the fail cleanup
void* LeagueCreate(uint32_t uId, int64_t lP2,
                   uint8_t uP3, int32_t nP4,
                   const char* pName) {
    if ((((lP2 == 0) || (pName == (const char*)0))
         || (uId == 0)) || (nP4 == 0)) {
        return nullptr;
    }
    char* puVar1 = (char*)g_fnMeritOpNew(0x118);
    if (puVar1 == nullptr) {
        puVar1 = nullptr;
    } else {
        puVar1 = (char*)LeagueCtor((void*)puVar1);
    }
    if (puVar1 == nullptr) {
        // log_InlineLogERROR(&DAT_141824ca8)
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        puVar1 = nullptr;
    } else {
        uint32_t uVar2 = LeagueInit(
            (int64_t)puVar1, (int32_t)uId, lP2, uP3,
            nP4, pName);
        if ((char)uVar2 == '\0') {
            LeagueFailCleanup((void*)puVar1,
                              (int64_t)uId, lP2,
                              (int64_t)uP3);
            puVar1 = nullptr;
        }
    }
    return puVar1;
}

}  // namespace syndicate

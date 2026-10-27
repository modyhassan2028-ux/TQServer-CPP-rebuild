// ============================================================
// Syndicate.dll port — unit T11/D36 (part 2c): AddMember /
// RemoveMember / CreateToken, verbatim against
// FUN_14174b6c0 / FUN_14174b960 / FUN_14174bbe0.
// The maps: users @ entity+0x58 (head@+0x88), members @
// entity+0x98 (head@+0xc8), tokens @ entity+0xd8
// (head@+0x108). All callee ops are the ported units
// (Users / Members / Member / Entity).
// ============================================================
#include "modules/syndicate/src/SyndicateLeagueOps.h"
#include "modules/syndicate/src/SyndicateLeagueMember.h"
#include "modules/syndicate/src/SyndicateLeagueUsers.h"
#include "modules/syndicate/src/SyndicateLeagueMembers.h"
#include "modules/syndicate/src/SyndicateLeagueEntity.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"
#include <cstring>

namespace syndicate {

void* (*g_fnLeagueOpsInstance)() = nullptr;

// ---------------- FUN_14174b6c0 ----------------
// AddMember(entity, idUser, pMemberData) → 1/0.
// pMemberData: the 0x20-byte member record — the copy
// into the node's 9-u32 value is: [key=idUser] +
// pMemberData[0..2] (3 qwords) + *(u32*)(pmd+0x18) +
// *(u16*)(pmd+0x1c) | *(u8*)(pmd+0x1e)<<16 (the
// original's local_58..local_36 stack block).
uint8_t LeagueAddMember(int64_t lEntity, uint32_t uUser,
                        void* pMemberData) {
    char* pcEnt = (char*)lEntity;
    if (uUser == 0) {
        // ORIGINAL: log_InlineLogERROR(&DAT_141824ca8)
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }

    // ---- the users-map find ----
    // ORIGINAL: plVar4 = FUN_14172b520(entity+0x58,
    //   &local_80, &key) — local_80/local_78 are the
    //   CONTIGUOUS 16-byte iter home (the afb0 trap)
    int64_t iterU[2];
    LeagueUserFind((int64_t)(pcEnt + 0x58),
                   (void*)iterU, &uUser);
    if (iterU[0] == 0
        || iterU[0] != *(int64_t*)(pcEnt + 0x58)) {
        g_fnLeagueInvalid();
    }
    if (iterU[1] == *(int64_t*)(pcEnt + 0x88)) {
        // NOT in the users map — try the members map
        // ORIGINAL: lVar1 = *(entity+200=0xc8) (the
        //   members head); lVar2 = *(entity+0x98)
        int64_t iterM[2];
        LeagueMemberFind((int64_t)(pcEnt + 0x98),
                         (void*)iterM, &uUser);
        if (iterM[0] == 0
            || iterM[0] != *(int64_t*)(pcEnt + 0x98)) {
            g_fnLeagueInvalid();
        }
        if (iterM[1] == *(int64_t*)(pcEnt + 0xc8)) {
            // ---- NOT a member anywhere: the ADD path ----
            void* pInst = g_fnLeagueOpsInstance();
            // ORIGINAL: local_78 =
            //   vt[4](instance, "cq_league_member")
            void** pplDef = *(void***)pInst;
            void* (*pfnMake)(void**, const char*) =
                (void* (*)(void**, const char*))
                    ((void**)pplDef)[4];   // vt+0x20
            void** pplDefRec =
                (void**)pfnMake((void**)pInst,
                                "cq_league_member");
            if (pplDefRec == nullptr) {
                // "CLeague::AddMember, MakeDefRecord
                //  failed! user[%u]"
                void* pLog = g_fnLeagueLogFactory();
                g_fnLeagueLogWrite(pLog, 0, 1);
                return 0;
            }
            // ORIGINAL: plVar4 = vt[2](def, 1);
            //   vt[23](plVar4, idUser)  — SetId(user)
            void** pplvt = *(void***)pplDefRec;
            void* (*pfnGetRec)(void**, uint64_t) =
                (void* (*)(void**, uint64_t))
                    ((void**)pplvt)[2];   // vt+0x10
            void** pplRec1 =
                (void**)pfnGetRec(pplDefRec, 1);
            void** pplvt1 = *(void***)pplRec1;
            void (*pfnSetId)(void**, uint64_t) =
                (void (*)(void**, uint64_t))
                    ((void**)pplvt1)[23];   // vt+0xb8
            pfnSetId(pplRec1, uUser);
            // ORIGINAL: plVar4 = vt[2](def, 2);
            //   SetId(league) via LeagueGetId
            void** pplRec2 =
                (void**)pfnGetRec(pplDefRec, 2);
            void** pplvt2 = *(void***)pplRec2;
            void (*pfnSetId2)(void**, uint64_t) =
                (void (*)(void**, uint64_t))
                    ((void**)pplvt2)[23];
            uint64_t uLeague = LeagueGetId(lEntity);
            pfnSetId2(pplRec2,
                      uLeague & 0xffffffff);
            // ORIGINAL: cVar3 = vt[10](def, 1) — the
            //   def insert gate
            uint8_t (*pfnIns)(void**, uint64_t) =
                (uint8_t (*)(void**, uint64_t))
                    ((void**)pplvt)[10];   // vt+0x50
            char cIns = (char)pfnIns(pplDefRec, 1);
            if (cIns == '\0') {
                // ORIGINAL: the verbatim dead LeagueGetId
                //   + "insert failed! user[%u] league[%u]"
                LeagueGetId(lEntity);
                void* pLog = g_fnLeagueLogFactory();
                g_fnLeagueLogWrite(pLog, 0, 1);
                // vt[0](def, 1) — the release
                void (*pfnRel)(void**, uint64_t) =
                    (void (*)(void**, uint64_t))
                        *(void**)pplvt;
                pfnRel(pplDefRec, 1);
                return 0;
            }
            // ---- the users-map insert (key = idUser) ----
            // ORIGINAL: local_80[0] = param_2 — the key
            //   overwrites the LOW HALF of the find home's
            //   anchor qword; local_78 (the find's node =
            //   the head, not-found) stays as the value —
            //   the VERBATIM 16-byte pair home {key |
            //   anchor-high, stale node} (the users
            //   node-alloc copies BOTH qwords)
            int64_t pairU[2];
            pairU[0] = (int64_t)((uint64_t)uUser
                | ((uint64_t)iterU[0]
                   & 0xffffffff00000000ULL));
            pairU[1] = iterU[1];
            int64_t outU[3];
            UsersInsertUnique(
                (void*)(pcEnt + 0x58),
                (void*)outU, (uint32_t*)pairU);
            // ---- the member record copy ----
            // ORIGINAL: local_54..local_36 = pmd[0..2] +
            //   the u32/u16/u8 tail; local_58 = idUser —
            //   the CONTIGOUS 9-u32 block (the afb0 trap)
            char* pcData = (char*)pMemberData;
            uint32_t auRec[9];
            auRec[0] = uUser;
            memcpy(&auRec[1], pcData, 0x18);
            auRec[7] = *(uint32_t*)(pcData + 0x18);
            auRec[8] = (uint32_t)(
                *(uint16_t*)(pcData + 0x1c)
                | ((uint32_t)*(uint8_t*)(pcData + 0x1e)
                   << 16));
            // ---- the members-map insert ----
            int64_t outM[3];
            MembersInsertUnique(
                (void*)(pcEnt + 0x98),
                (void*)outM, auRec);
            return 1;
        }
    }
    // ---- the user IS a member (or in the users map):
    //      the provider notify + the log ----
    if (*(int64_t*)(pcEnt + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
    } else {
        // ORIGINAL: resolve(provider, 0) → vt[9](rec)
        void** pplProvider = *(void***)(pcEnt + 8);
        void** ppvtP = *(void***)pplProvider;
        void* (*pfnResolve)(void**, uint64_t) =
            (void* (*)(void**, uint64_t))
                ((void**)ppvtP)[2];
        void** pplRec =
            (void**)pfnResolve(pplProvider, 0);
        void** ppvtR = *(void***)pplRec;
        void (*pfn48)(void**) =
            (void (*)(void**))((void**)ppvtR)[9];  // +0x48
        pfn48(pplRec);
    }
    // "CLeague::AddMember, user[%u] is league[%u] member!"
    {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
    }
    return 0;
}

// ---------------- FUN_14174b960 ----------------
// RemoveMember(entity, idUser) → 1/0
uint8_t LeagueRemoveMember(int64_t lEntity,
                           uint32_t uUser) {
    char* pcEnt = (char*)lEntity;
    if (uUser == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    // ---- the users-map find ----
    int64_t iterU[2];
    LeagueUserFind((int64_t)(pcEnt + 0x58),
                   (void*)iterU, &uUser);
    if (iterU[0] == 0
        || iterU[0] != *(int64_t*)(pcEnt + 0x58)) {
        g_fnLeagueInvalid();
    }
    if (iterU[1] == *(int64_t*)(pcEnt + 0x88)) {
        // the node == the head: NOT a member
        return 0;
    }
    // ORIGINAL: lVar3 = *local_38 (DEREF the anchor →
    //   the owning container); the CRT same-map check:
    //   the node must not be the container's head
    //   (read at the container+0x30)
    if (iterU[1]
        == *(int64_t*)(*(int64_t*)iterU[0] + 0x30)) {
        g_fnLeagueInvalid();
    }
    // ---- the member-record dual release ----
    // ORIGINAL: plVar2 = *(node + 0x20) (the value ptr)
    void** pplRec = *(void***)(iterU[1] + 0x20);
    if (pplRec == nullptr) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
    } else {
        // ORIGINAL: vt[8](rec, 0) then vt[0](rec, 1)
        void** ppvt = *(void***)pplRec;
        void (*pfn40)(void**, uint64_t) =
            (void (*)(void**, uint64_t))
                ((void**)ppvt)[8];   // vt+0x40
        pfn40(pplRec, 0);
        void (*pfn0)(void**, uint64_t) =
            (void (*)(void**, uint64_t))
                *(void**)ppvt;   // vt[0]
        pfn0(pplRec, 1);
    }
    // ---- the users erase at the found iter ----
    int64_t outE[2];
    UsersErase((void*)(pcEnt + 0x58),
               (void*)outE, (void*)iterU);
    // ---- the members erase(key) count ----
    MembersEraseKey((void*)(pcEnt + 0x98),
                    &uUser);
    return 1;
}

// ---------------- FUN_14174bbe0 ----------------
// CreateToken(entity, idToken, p3, p4) → CToken* | 0
void* LeagueCreateToken(int64_t lEntity, uint32_t uToken,
                        int64_t lP3, uint64_t uP4) {
    char* pcEnt = (char*)lEntity;
    void* pInst = g_fnLeagueOpsInstance();
    char* pcHead = *(char**)(pcEnt + 0x108);

    // ---- the INLINE lower_bound descent (the
    //      remember-updates-only-when-descending-left) ----
    // ORIGINAL: puVar7 = head[1] (the root); puVar2 = head
    char* puVar7 = *(char**)(pcHead + 8);
    char cVar3 = *(char*)(puVar7 + 0x29);
    char* puVar2 = pcHead;
    while (cVar3 == '\0') {
        char* puVar10;
        if (*(uint32_t*)(puVar7 + 0x18) < uToken) {
            puVar10 = *(char**)(puVar7 + 0x10);
            puVar7 = puVar2;   // remember UNCHANGED
        } else {
            puVar10 = *(char**)puVar7;
        }
        puVar2 = puVar7;
        puVar7 = puVar10;
        cVar3 = *(char*)(puVar10 + 0x29);
    }
    // local_48 = puVar2 (the lower bound);
    // local_50 = *(entity+0xd8) (the anchor)
    int64_t lFound[2];
    lFound[0] = *(int64_t*)(pcEnt + 0xd8);
    lFound[1] = (int64_t)puVar2;
    if (*(int64_t*)(pcEnt + 0xd8) == 0) {
        g_fnLeagueInvalid();
    }
    // ORIGINAL: the end home {anchor, head} when
    //   (lb == head || token < key(lb)); else the found
    //   home — chosen by pointer
    int64_t lEnd[2];
    lEnd[0] = *(int64_t*)(pcEnt + 0xd8);
    lEnd[1] = (int64_t)pcHead;
    int64_t* plIter = ((puVar2 == pcHead)
                       || (uToken
                           < *(uint32_t*)(puVar2 + 0x18)))
                ? lEnd
                : lFound;
    // the iterator copy local_28/local_20
    int64_t lIter[2];
    lIter[0] = plIter[0];
    lIter[1] = plIter[1];
    // the CRT same-map check (the anchor)
    if (*(int64_t*)(pcEnt + 0xd8) == 0
        || *(int64_t*)(pcEnt + 0xd8) != lIter[0]) {
        g_fnLeagueInvalid();
    }
    if ((int64_t)pcHead == lIter[1]) {
        // ---- the token does NOT exist: CREATE ----
        void** pplvtI = *(void***)pInst;
        void* (*pfnMake)(void**, const char*) =
            (void* (*)(void**, const char*))
                ((void**)pplvtI)[4];
        void** pplDef =
            (void**)pfnMake((void**)pInst,
                            "cq_league_token");
        if (pplDef == nullptr) {
            void* pLog = g_fnLeagueLogFactory();
            g_fnLeagueLogWrite(pLog, 0, 1);
            return nullptr;
        }
        // SetId(token) on resolve(2)
        void** ppvtD = *(void***)pplDef;
        void* (*pfnGetRec)(void**, uint64_t) =
            (void* (*)(void**, uint64_t))
                ((void**)ppvtD)[2];
        void** pplRec2 =
            (void**)pfnGetRec(pplDef, 2);
        int64_t lInner = *(int64_t*)pplRec2;
        void** ppvtR2 = *(void***)pplRec2;
        void (*pfnSetId)(void**, uint64_t) =
            (void (*)(void**, uint64_t))
                ((void**)ppvtR2)[23];
        pfnSetId(pplRec2, uToken);
        // SetId(league) on resolve(1)
        void** pplRec1 =
            (void**)pfnGetRec(pplDef, 1);
        void** ppvtR1 = *(void***)pplRec1;
        void (*pfnSetId1)(void**, uint64_t) =
            (void (*)(void**, uint64_t))
                ((void**)ppvtR1)[23];
        uint64_t uLeague = LeagueGetId(lEntity);
        pfnSetId1(pplRec1, uLeague & 0xffffffff);
        // the CToken ctor (1417d4d60: {vftable, def})
        void* pTok = LeagueTokenNew((int64_t)pplDef);
        if (pTok == nullptr) {
            // ORIGINAL: vt[0](def, 1) — the release
            void (*pfnRel)(void**, uint64_t) =
                (void (*)(void**, uint64_t))
                    *(void**)ppvtD;
            pfnRel(pplDef, 1);
            return nullptr;
        }
        // ORIGINAL: cVar3 = vt[10](def) — NO ARG
        //   (AddMember's gate passes 1)
        uint8_t (*pfnIns)(void**) =
            (uint8_t (*)(void**))((void**)ppvtD)[10];
        char cIns = (char)pfnIns(pplDef);
        if (cIns == '\0') {
            // ORIGINAL: FUN_1417d4db0(pTok, the 1 |
            //   league-high sentinel, lInner, p4) — the
            //   dual release (D35) → fail
            // ORIGINAL: uVar8 = CONCAT71(uVar9, 1) —
            //   the 1 | league-high sentinel as the
            //   "iter" arg of the dual release
            LeagueRecRelease2(pTok,
                (void*)(uint64_t)(
                    (uint64_t)1
                    | ((uLeague >> 8) << 8)),
                (uint64_t)lInner, uP4);
            return nullptr;
        }
        // ---- the tokens-map insert ----
        // ORIGINAL: uVar8 = LeagueTokenKey(pTok);
        //   local_28 = CONCAT44(local_28._4_4_, key) —
        //   the key REPLACES the low half of the iter
        //   home's anchor qword (the high half KEPT);
        //   local_20 = pTok; 141749a50(entity+0xd8,
        //   &local_40, &local_28)
        uint64_t uKey = LeagueTokenKey((int64_t)pTok);
        int64_t lPair[2];
        lPair[0] = (int64_t)((uint64_t)(uint32_t)uKey
            | ((uint64_t)lIter[0]
               & 0xffffffff00000000ULL));
        lPair[1] = (int64_t)pTok;
        int64_t outT[3];
        TokensInsertUnique(
            (void*)(pcEnt + 0xd8),
            (void*)outT, (uint32_t*)lPair);
        return pTok;
    }
    // ---- the token EXISTS: the provider notify + log ----
    if (*(int64_t*)(pcEnt + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
    } else {
        void** pplProvider = *(void***)(pcEnt + 8);
        void** ppvtP = *(void***)pplProvider;
        void* (*pfnResolve)(void**, uint64_t) =
            (void* (*)(void**, uint64_t))
                ((void**)ppvtP)[2];
        void** pplRec =
            (void**)pfnResolve(pplProvider, 0);
        void** ppvtR = *(void***)pplRec;
        void (*pfn48)(void**) =
            (void (*)(void**))((void**)ppvtR)[9];
        pfn48(pplRec);
    }
    // "CLeague::CreateToken: token %u is exist,league=%u"
    {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
    }
    return nullptr;
}

}  // namespace syndicate

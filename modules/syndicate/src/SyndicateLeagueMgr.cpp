// ============================================================
// Syndicate.dll port — unit T12/D37 part 1 — see the header.
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_14174b000 / FUN_14175ee00 / FUN_1417630d0 /
//   FUN_1417631d0 / FUN_141763680 / FUN_141764870 /
//   FUN_1417638e0 / FUN_1417646f0 / FUN_1417647e0 /
//   FUN_141764810 / FUN_141743e70 / FUN_141743c80 /
//   FUN_141743d10 / FUN_141743dd0 / FUN_141743d70 /
//   FUN_141743f90 / FUN_141743e80
// ============================================================
#include "modules/syndicate/src/SyndicateLeagueMgr.h"
#include "modules/syndicate/src/SyndicateLeagueMember.h"   // LeagueGetId
#include "modules/syndicate/src/SyndicateLeagueOps.h"      // the three big ops
#include "modules/syndicate/src/SyndicateLeagueCmp.h"      // the log/invalid seams
#include <cstring>

namespace syndicate {

void (*g_fnMgrStrCopy)(char*, const char*, int) = nullptr;

// ================= FUN_141743e70 =================
// the DIRECT u32 read at entity+0x10 (no provider chain).
uint32_t LeagueGetLeaderId(int64_t lEntity) {
    return *(uint32_t*)((char*)lEntity + 0x10);
}

// ---------- the shared provider resolve ----------
// ORIGINAL (per accessor): plVar1 = (**(code **)
//   (*(longlong **)(param_1 + 8) + 0x10))(provider, idx);
// the rec vtable call follows at the accessor's slot.
static void** MgrResolveRec(int64_t lEntity, uint64_t uIdx) {
    void** pplProvider = *(void***)((char*)lEntity + 8);
    void** ppvt = *(void***)pplProvider;
    void* (*pfnResolve)(void**, uint64_t) =
        (void* (*)(void**, uint64_t))ppvt[2];   // vt+0x10
    return (void**)pfnResolve(pplProvider, uIdx);
}

// ================= FUN_141743c80 =================
// null provider → 0 (NO log); resolve(2) → rec-vt+0x40.
uint64_t LeagueGetRec2U32(int64_t lEntity) {
    if (*(int64_t*)((char*)lEntity + 8) == 0) {
        return 0;
    }
    void** pplRec = MgrResolveRec(lEntity, 2);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn40)(void**) =
        (uint64_t (*)(void**))ppvt2[8];         // 0x40/8
    return pfn40(pplRec);
}

// ================= FUN_141743d10 =================
// null provider → the log + 0; resolve(9) → rec-vt+0x48.
uint64_t LeagueGetRec9Str(int64_t lEntity) {
    if (*(int64_t*)((char*)lEntity + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    void** pplRec = MgrResolveRec(lEntity, 9);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn48)(void**) =
        (uint64_t (*)(void**))ppvt2[9];         // 0x48/8
    return pfn48(pplRec);
}

// ================= FUN_141743dd0 =================
// null provider → 0 (NO log); resolve(1) → rec-vt+0x78.
uint64_t LeagueGetRec1Str(int64_t lEntity) {
    if (*(int64_t*)((char*)lEntity + 8) == 0) {
        return 0;
    }
    void** pplRec = MgrResolveRec(lEntity, 1);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn78)(void**) =
        (uint64_t (*)(void**))ppvt2[15];        // 0x78/8
    return pfn78(pplRec);
}

// ================= FUN_141743d70 =================
// the GENERIC string getter: null provider → the log + 0;
// resolve(idx) → rec-vt+0x78.
uint64_t LeagueGetRecStr(int64_t lEntity, uint32_t uIdx) {
    if (*(int64_t*)((char*)lEntity + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return 0;
    }
    void** pplRec = MgrResolveRec(lEntity, uIdx);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn78)(void**) =
        (uint64_t (*)(void**))ppvt2[15];        // 0x78/8
    return pfn78(pplRec);
}

// ---------- the shared post-set flush ----------
// ORIGINAL (both setters): if (param_4 != '\0')
//   (**(code **)(**(longlong **)(param_1 + 8) + 0x38))
//     (provider, 0);
static void MgrRecFlush(int64_t lEntity) {
    void** pplProvider = *(void***)((char*)lEntity + 8);
    void** ppvt = *(void***)pplProvider;
    void (*pfn38)(void**, uint64_t) =
        (void (*)(void**, uint64_t))ppvt[7];    // 0x38/8
    pfn38(pplProvider, 0);
}

// ================= FUN_141743f90 =================
// the generic setter: resolve(idx) → rec-vt+0x80(rec, val);
// flush → the provider vt+0x38(provider, 0).
void LeagueSetRecStr(int64_t lEntity, uint32_t uIdx,
                     uint64_t uVal, uint8_t uFlush) {
    if (*(int64_t*)((char*)lEntity + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return;
    }
    void** pplRec = MgrResolveRec(lEntity, uIdx);
    void** ppvt2 = *(void***)pplRec;
    void (*pfn80)(void**, uint64_t) =
        (void (*)(void**, uint64_t))ppvt2[16];  // 0x80/8
    pfn80(pplRec, uVal);
    if (uFlush != 0) {
        MgrRecFlush(lEntity);
    }
}

// ================= FUN_141743e80 =================
// the generic int setter: resolve(idx) → rec-vt+0xb0(rec,
// u32 val); flush → the provider vt+0x38(provider, 0).
void LeagueSetRecInt(int64_t lEntity, uint32_t uIdx,
                     uint32_t uVal, uint8_t uFlush) {
    if (*(int64_t*)((char*)lEntity + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return;
    }
    void** pplRec = MgrResolveRec(lEntity, uIdx);
    void** ppvt2 = *(void***)pplRec;
    void (*pfnb0)(void**, uint32_t) =
        (void (*)(void**, uint32_t))ppvt2[22];  // 0xb0/8
    pfnb0(pplRec, uVal);
    if (uFlush != 0) {
        MgrRecFlush(lEntity);
    }
}

// ================= FUN_14174b000 =================
// is the user in this league? the users map
// {anchor@+0x58, head@+0x88}: the lower_bound descent
// (remember-updates-only-left) + the CRT pair →
// head != node.
uint8_t LeagueUserIsMember(int64_t lEntity, uint32_t uUser) {
    char* pcEnt = (char*)lEntity;
    // ORIGINAL: puVar6 = head[1] (the root); puVar3 = head
    char* pcHead = *(char**)(pcEnt + 0x88);
    char* pcCur = *(char**)(pcHead + 8);
    char* pcRemember = pcHead;
    while (*(char*)(pcCur + 0x29) == '\0') {
        char* pcNext;
        if (*(uint32_t*)(pcCur + 0x18) < uUser) {
            pcNext = *(char**)(pcCur + 0x10);   // right
        }
        else {
            pcNext = *(char**)pcCur;            // left
            pcRemember = pcCur;
        }
        pcCur = pcNext;
    }
    // ORIGINAL: local_38 = anchor; the null gate BEFORE
    //   the found/end selection
    char* pcAnchor = *(char**)(pcEnt + 0x58);
    if (pcAnchor == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    // the found/end pair home {anchor, node}
    char* apPair[2];
    apPair[0] = pcAnchor;
    if ((pcRemember == pcHead) ||
        (uUser < *(uint32_t*)(pcRemember + 0x18))) {
        apPair[1] = pcHead;
    }
    else {
        apPair[1] = pcRemember;
    }
    // ORIGINAL: the pair re-copy + the anchor re-validate
    //   → return head != node
    if ((pcAnchor == (char*)0x0) ||
        (pcAnchor != apPair[0])) {
        g_fnLeagueInvalid();
    }
    return pcHead != apPair[1];
}

// ---------- the shared map lookup ----------
// ORIGINAL (1417630d0/1417631d0/141763680/141764870 all
// inline the same): the descent + the found/end gate +
// the CRT unwrap → the value@+0x20 or 0.
static void* MgrMapLookup(char** pplMap, uint32_t uKey) {
    // pplMap[0] = anchor, pplMap[6] = head (map+0x30)
    char* pcHead = pplMap[6];
    char* pcCur = *(char**)(pcHead + 8);        // root
    char* pcRemember = pcHead;
    while (*(char*)(pcCur + 0x29) == '\0') {
        char* pcNext;
        if (*(uint32_t*)(pcCur + 0x18) < uKey) {
            pcNext = *(char**)(pcCur + 0x10);   // right
        }
        else {
            pcNext = *(char**)pcCur;            // left
            pcRemember = pcCur;
        }
        pcCur = pcNext;
    }
    char* pcAnchor = pplMap[0];
    if (pcAnchor == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    // the found/end pair selection (adjacent pair home)
    char* apPair[2];
    if ((pcRemember == pcHead) ||
        (uKey < *(uint32_t*)(pcRemember + 0x18))) {
        apPair[0] = pcAnchor;
        apPair[1] = pcHead;
    }
    else {
        apPair[0] = pcAnchor;
        apPair[1] = pcRemember;
    }
    // ORIGINAL: the CRT unwrap — the pair re-copy, the
    //   anchor re-validate, head → 0, the *anchor
    //   container head check, the value read
    char* pcAnchor2 = apPair[0];
    if ((pcAnchor == (char*)0x0) ||
        (pcAnchor != pcAnchor2)) {
        g_fnLeagueInvalid();
    }
    char* pcNode = apPair[1];
    if (pcHead == pcNode) {
        return (void*)0x0;
    }
    char* pcContainer = pcAnchor2;
    if (pcContainer == (char*)0x0) {
        g_fnLeagueInvalid();
    }
    else {
        pcContainer = *(char**)pcContainer;     // *anchor
    }
    if (pcNode == *(char**)(pcContainer + 0x30)) {
        g_fnLeagueInvalid();
    }
    return *(void**)(pcNode + 0x20);
}

// ================= FUN_1417630d0 =================
void* MgrLeagueFind(int64_t lMgr, uint32_t uLeagueId) {
    return MgrMapLookup((char**)((char*)lMgr + 0x38),
                        uLeagueId);
}

// ================= FUN_141763680 =================
uint64_t MgrLeagueGetType(int64_t lMgr, uint32_t uLeagueId) {
    char* pcLeague = (char*)MgrMapLookup(
        (char**)((char*)lMgr + 0x38), uLeagueId);
    if (pcLeague != (char*)0x0) {
        return LeagueGetRec2U32((int64_t)pcLeague);
    }
    return 0;
}

// ================= FUN_141764870 =================
void* MgrTokenTypeFind(int64_t lMgr, uint32_t uTokenType) {
    return MgrMapLookup((char**)((char*)lMgr + 0x1a0),
                        uTokenType);
}

// ================= FUN_14175ee00 =================
// the user's league id: the FULL ITERATED walk over the
// leagues map (begin = head->_Left), the verbatim inlined
// successor, the CRT re-validation each step.
uint64_t MgrUserLeagueId(int64_t lMgr, uint32_t uUser) {
    char* pcMgr = (char*)lMgr;
    char* pcAnchor = *(char**)(pcMgr + 0x38);
    char* pcNode = **(char***)(pcMgr + 0x68);   // head->_Left
    while (true) {
        char* pcHead = *(char**)(pcMgr + 0x68);
        // ORIGINAL: the anchor re-validate (each step)
        if ((pcAnchor == (char*)0x0) ||
            (pcAnchor != *(char**)(pcMgr + 0x38))) {
            g_fnLeagueInvalid();
        }
        if (pcNode == pcHead) {
            return 0;                            // the end
        }
        char* pcContainer;
        if (pcAnchor == (char*)0x0) {
            g_fnLeagueInvalid();
            pcContainer = (char*)0x0;
        }
        else {
            pcContainer = *(char**)pcAnchor;    // *anchor
        }
        if (pcNode == *(char**)(pcContainer + 0x30)) {
            g_fnLeagueInvalid();
        }
        // the value: node+0x20
        char* pcLeague = *(char**)(pcNode + 0x20);
        if ((pcLeague != (char*)0x0) &&
            LeagueUserIsMember((int64_t)pcLeague, uUser)) {
            return LeagueGetId((int64_t)pcLeague);
        }
        // ---- the inlined _Tree_increment ----
        if (*(char*)(pcNode + 0x29) == '\0') {
            char* pcRight = *(char**)(pcNode + 0x10);
            if (*(char*)(pcRight + 0x29) == '\0') {
                // leftmost of the right subtree
                char* pcNext = *(char**)pcRight;
                while (*(char*)(pcNext + 0x29) == '\0') {
                    pcRight = pcNext;
                    pcNext = *(char**)pcNext;
                }
                pcNode = pcRight;               // successor
            }
            else {
                // climb while the node is the parent's
                // right child
                char* pcParent = *(char**)(pcNode + 8);
                char* pcCur = pcNode;
                while ((pcNode = pcParent,
                        *(char*)(pcNode + 0x29) == '\0') &&
                       (pcCur == *(char**)(pcNode + 0x10))) {
                    pcCur = pcNode;
                    pcParent = *(char**)(pcNode + 8);
                }
                // pcNode = the parent = the successor
            }
        }
        else {
            g_fnLeagueInvalid();
        }
    }
}

// ================= FUN_1417631d0 =================
void* MgrUserLeagueObj(int64_t lMgr, uint32_t uUser) {
    uint64_t uId = MgrUserLeagueId(lMgr, uUser);
    return MgrMapLookup((char**)((char*)lMgr + 0x38),
                        (uint32_t)uId);
}

// ================= FUN_1417638e0 =================
uint8_t MgrRemoveMember(int64_t lMgr, uint32_t uLeagueId,
                        uint32_t uUser) {
    if ((uLeagueId != 0) && (uUser != 0)) {
        char* pcLeague = (char*)MgrLeagueFind(lMgr,
                                              uLeagueId);
        if (pcLeague != (char*)0x0) {
            return LeagueRemoveMember((int64_t)pcLeague,
                                      uUser);
        }
    }
    return 0;
}

// ================= FUN_1417646f0 =================
uint8_t MgrAddMember(int64_t lMgr, uint32_t uUser,
                     uint32_t uLeagueId, uint32_t uP4,
                     uint32_t uP5, uint16_t uP6, uint32_t uP7,
                     uint8_t uP8, const char* pName) {
    if (((uUser != 0) && (uLeagueId != 0) &&
         (pName != (const char*)0x0)) &&
        ((uint32_t)MgrUserLeagueId(lMgr, uUser) == 0)) {
        char* pcLeague = (char*)MgrLeagueFind(lMgr,
                                              uLeagueId);
        if (pcLeague != (char*)0x0) {
            // ORIGINAL: the VERBATIM 0x1f-byte stack record
            //   local_58@0 p4, local_54@4 p5,
            //   local_50@8 p6(u16), local_4e@0xa p7(u32),
            //   local_4a@0xe p8(u8), local_49@0xf name[16]
            char acRec[0x20];
            memset(acRec, 0, 0x20);
            *(uint32_t*)(acRec + 0x0) = uP4;
            *(uint32_t*)(acRec + 0x4) = uP5;
            *(uint16_t*)(acRec + 0x8) = uP6;
            *(uint32_t*)(acRec + 0xa) = uP7;
            *(uint8_t*)(acRec + 0xe) = uP8;
            g_fnMgrStrCopy(acRec + 0xf, pName, 0x10);
            return LeagueAddMember((int64_t)pcLeague, uUser,
                                   (void*)acRec);
        }
    }
    return 0;
}

// ================= FUN_1417647e0 =================
uint32_t MgrGetLeaderId(int64_t lMgr, uint32_t uLeagueId) {
    if (uLeagueId != 0) {
        char* pcLeague = (char*)MgrLeagueFind(lMgr,
                                              uLeagueId);
        if (pcLeague != (char*)0x0) {
            return LeagueGetLeaderId((int64_t)pcLeague);
        }
    }
    return 0;
}

// ================= FUN_141764810 =================
void* MgrCreateToken(int64_t lMgr, uint32_t uLeagueId,
                     int64_t lTokenId, uint64_t uP4) {
    char* pcLeague = (char*)MgrLeagueFind(lMgr, uLeagueId);
    if (pcLeague == (char*)0x0) {
        // log_InlineLogERROR(DAT_141824ca8)
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        return (void*)0x0;
    }
    // ORIGINAL: FUN_14174bbe0(league, (uint)param_3,
    //   uVar3 (= param_3), param_4)
    return LeagueCreateToken((int64_t)pcLeague,
                             (uint32_t)lTokenId, lTokenId,
                             uP4);
}

}  // namespace syndicate

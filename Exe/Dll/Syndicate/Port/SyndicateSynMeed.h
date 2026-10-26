// ============================================================
// Syndicate.dll port — unit D45/T16: the CSynArenicMeed
// query layer (the syndicate arena grades) — the lazy
// singleton + its 0x30 head + the user→league RB lookup
// (the 0x29 family) + the grade/members helpers.
// Addresses verbatim: 14177ace0 (the 0x30 head alloc),
// 14177c6c0 (the singleton ctor: proxy@0, head@+0x30,
// size@+0x38), 14177c770 (the lazy get: DAT_141886d30),
// 14177c0a0 (the lower_bound walk + the debug-iterator
// validity gates + the +0x20 league value),
// 1417ac810 (mgr+8 vt+0x1f8 — the user id),
// 1417ac6e0 (mgr+8 vt+0x3a8), 14177f980
// (GetUserGrade: the 1-3 type gate + the chain),
// 14177fa10 (the mgr vt+0x378 pass-through),
// 141741410 (the null gate + the <8 check),
// 141740fd0 (the members-vector index walk: the
// vt(5)/vt(2) sub-object chain), 141779400 (the grade
// lookup — a seam here until D46).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the shared seams (SyndicateCrossMerit) ----
// g_fnMeritOpNew / g_fnMeritOpDelete / g_fnMeritInvalid
// (the singleton alloc + the _invalid_parameter gates)

// ---- the log (log_InlineLogERROR DAT_141824ca8) ----
extern void (*g_fnMeedLog)();

// ---- the singleton (DAT_141886d30) ----
extern void* g_pMeedSingleton;
extern void MeedResetSingleton();   // test hook

// ---- the mgr-side seams (1417ac810 / 1417ac6e0 /
// 14177fa10) ----
// (mgr+8)->vt+0x1f8() -> the user id
extern int (*g_fnMgrUserId)(void* pMgr);
// (mgr+8)->vt+0x3a8()
extern void (*g_fnMgrVt3a8)(void* pMgr);
// mgr->vt+0x378(mgr, type)
extern void (*g_fnMgrVt378)(void* pMgr, int n);

// ---- the league-grade seam (141779400, D46) ----
// (league, user, type) -> the grade u64
extern uint64_t (*g_fnMeedGradeOf)(void* pLeague,
                                   uint64_t uUser,
                                   int nType);

// ---- the members-walk seams (141740fd0) ----
// member vt+0x10(member, 5) -> sub
extern void* (*g_fnMeedSub5)(void* pMember);
// sub5 vt+0x48() -> flag
extern int (*g_fnMeedSub5Flag)(void* pSub);
// member vt+0x10(member, 2) -> sub
extern void* (*g_fnMeedSub2)(void* pMember);
// sub2 vt+0x40() -> the id
extern int (*g_fnMeedSub2Id)(void* pSub);

// ---- FUN_14177ace0: the 0x30 tree head ----
void* MeedHeadNew();

// ---- FUN_14177c6c0: the singleton ctor (0x40) ----
void* MeedSingletonCtor(void* pThis);

// ---- FUN_14177c770: the lazy singleton get ----
void* MeedSingletonGet();

// ---- FUN_14177c0a0: (the meed map, the user id) ->
// the league ptr or 0 ----
void* MeedUserLeague(void* pMap, uint32_t uId);

// ---- FUN_14177f980: GetUserGrade ----
uint64_t MeedGetUserGrade(uint64_t uUser, int nType);

// ---- FUN_14177fa10: the mgr vt+0x378 pass-through --
void MeedPostGrade(void* pMgr, uint64_t uA, int nType);

// ---- FUN_141740fd0: the members-vector index ----
int MeedMemberIndex(void* pMembers, int nId);

// ---- FUN_141741410: the null gate + the <8 check ----
void MeedMemberCheck(void* pObj, int nId);

// ---- D46: the grade lookup (141779090 / 141779400) --
// the member sub-object protocol (vt+8 with index):
extern void* (*g_fnMeedMemSub)(void* pMember, int n);
// sub(2) vt+0x40() -> the member id
extern int (*g_fnMeedSubNId)(void* pSub);
// sub(3) vt+0x48() -> the entry grade-type
extern int (*g_fnMeedSubNType)(void* pSub);
// member vt+0x10(member, 4) -> sub4
extern void* (*g_fnMeedSub4)(void* pMember);
// sub4 vt+0x48() -> the grade value
extern uint64_t (*g_fnMeedSub4Val)(void* pSub);

// ---- FUN_141779090: find the member cell matching
// (uUser, nType) in the league's meed vector →
// the out iterator {proxy, cell} (the end if absent)
void MeedEntryFind(void* pLeague, void* pItOut,
                   uint64_t uUser, int nType);

// ---- FUN_141779400: the member's grade (0 if the
// member/type is absent) ----
uint64_t MeedGradeOf(void* pLeague, uint64_t uUser,
                     int nType);

} // namespace syndicate

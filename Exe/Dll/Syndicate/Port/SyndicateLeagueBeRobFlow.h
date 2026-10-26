// ============================================================
// Syndicate.dll port — unit D70: FUN_141771f90, verbatim.
// The LEAGUE-BE-ROB BROADCAST: the biggest function left in
// the Syndicate league family (7453 bytes). For a league key
// (uKey, composite id*1000000-style) and an array of member
// ids it:
//   (A) lower_bounds the mgr map @+0x3f0 (keyed by the
//       LEAGUE key) and, when absent, builds an inner map,
//       inserts the MEMBER id into it, wraps it in the pair
//       {league key, map} (FUN_14176f690 move dance) and
//       inserts it via FUN_141770ea0; when present it
//       inserts the member id into the found node's value
//       map (@node+0x20).
//   (B) the SAME for the mgr map @+0x430 with the nesting
//       INVERTED (keyed by the MEMBER id, inner key = the
//       league key). The lower bound here is the compiler's
//       INLINE descent (isnil@+0x61, key uint@+0x18, head
//       @mgr+0x460, proxy @mgr+0x430) — ported inline.
//   (C) when the mode field @mgr+0x35c == 2 AND the logic's
//       own league (vt+0x3f0, rcx rides) == member/1000000:
//       fetches the league NAME (FUN_141766250 into a
//       zeroed 16-byte buffer, cap 0x10), builds the D69
//       CMsgLeagueBeRob, Create(type 3, key/1000000,
//       *(uint*)(mgr+0x358), name), AppendDword(key),
//       Serialize, send vt+0xb8(logic, member%1000000,
//       msg, 0). A name-fetch failure SKIPS the rest of
//       this member (jumps straight to the loop bottom).
//   (D) lower_bounds the mgr map @+0x470 by the LEAGUE
//       key; on absence builds the inner map and copies the
//       WHOLE KEY RANGE of mgr+0x370[member] and
//       mgr+0x3b0[member]'s value maps into it AND into the
//       result set; on presence copies into the found
//       node's value map (and the result set). Then the
//       pair/insert into mgr+0x470 (absent case only).
//   (E) walks mgr+0x370[member]'s value map (iter via
//       {proxy=@val+0, first=head->left}, advance via
//       FUN_141724ed0): for each KEY, lower_bounds
//       mgr+0x470 by it; on absence builds the inner map,
//       inserts the LEAGUE key, pair/inserts (key, map);
//       on presence inserts the league key into the found
//       value map. Then the per-entry mode-2 send:
//       Create(type 4, 0, *(uint*)(mgr+0x358), ""),
//       AppendDword(key), Serialize, send(logic,
//       key%1000000, msg, 0) — in a SECOND stack CMsg
//       (local_4d8). The SAME walk+send over
//       mgr+0x3b0[member]'s value map with a THIRD stack
//       CMsg (local_948).
//   The loop caps at 10 processed ids (the `9 < i` break)
//   and skips 0 ids.
// After the loop, when mode==2 AND myLeague == key/1000000:
//   the AGGREGATE block — *pIds as the anchor id; the name
//   fetched by FUN_141766170 (by member id), and when the
//   buffer is EMPTY (the byte walk exits after exactly one
//   decrement) retried by FUN_141766250 (league name);
//   Create(type 2, *pIds/1000000, *(uint*)(mgr+0x358),
//   name); a second 10-cap pass appending EVERY non-zero id
//   with the flush-and-restart dance (AppendDword fails →
//   Serialize + send(logic, key%1000000, msg, 0) + Clear +
//   re-Create + re-Append of the SAME id); then GetCount
//   != 0 → Serialize + send. Then the FOURTH stack CMsg:
//   Create(type 4, 0, *(uint*)(mgr+0x358), "") and the
//   SAME flush dance over the RESULT SET's keys, the final
//   GetCount send, and the double D69 dtor.
// The result set (built at the top with the INLINE
// FUN_141731fc0 body: proxy = operator_new(8), head =
// FUN_141726c30 self-linked, isnil@+0x1d = 1, size = 0) is
// torn down at the end (erase [first, end) via FUN_14172a410
// + head delete + proxy delete) on every exit.
//
// ---- the container kit: SEAMED, not ported here ----
// The five mgr maps and the stack maps all share the MSVC
// debug-iterator map layout this function VERBATIMLY reads:
//   container = {proxy@0, ... , head@+0x30, size@+0x38}
//   kit node  = {left@0, parent@8, right@0x10, key uint@+0x18,
//                color@+0x1c, isnil@+0x1d, value@+0x20}
//   mgr node  = {left@0, parent@8, right@0x10, key uint@+0x18,
//                value map@+0x20 (proxy@+0x20, head@+0x50),
//                isnil@+0x61}
//   iterator  = {proxy@0, node@8}
// The kit functions are generic MSVC std::map machinery
// shared by the whole league family; each is a seam bound
// to its raw address and ported verbatim in the container
// unit. The D69 message family is REAL (linked).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the runtime seams ----
extern void* (*g_fnLbrOpNew)(size_t);            // operator_new
extern void (*g_fnLbrOpDelete)(void*);          // operator_delete
extern void (*g_fnLbrInvalid)();                // _invalid_parameter_noinfo

// ---- the container kit (raw addresses, ported in the
//      container unit; contracts documented in the .cpp) ----
extern void* (*g_fnLbrHeadAlloc)();             // FUN_141726c30
extern void* (*g_fnLbrMapCtor)(void* pMap);     // FUN_141731fc0
extern void* (*g_fnLbrMapInsertKey)(void* pMap, void* pOutIter,
                                    uint32_t* pKey);          // FUN_14172ae00
extern void* (*g_fnLbrMapMoveCtor)(void* pDst, void* pSrc);  // FUN_1417695b0
extern void* (*g_fnLbrPairMake)(void* pPair, uint32_t uKey,
                               void* pSrcMap);               // FUN_14176f690
extern void* (*g_fnLbrMapLowerBound)(void* pMap, void* pOutIter,
                                    uint32_t* pKey);          // FUN_141760e40
extern void* (*g_fnLbrMapInsertPair)(void* pMap, void* pOutIter,
                                    void* pPair);             // FUN_141770ea0
extern void (*g_fnLbrMapTreeDtor)(void* pMap);                 // FUN_14172c560
extern void* (*g_fnLbrMapEraseRange)(void* pMap, void* pOutIter,
                                     void* pFirst, void* pLast); // FUN_14172a410
extern void (*g_fnLbrIterAdvance)(void* pIter);               // FUN_141724ed0
extern void (*g_fnLbrMapInsertKeyRange)(void* pMap, void* pFirstIter,
                                        void* pLastIter);     // FUN_141762f60

// ---- the name getters (league-manager methods) ----
extern int (*g_fnLbrGetNameById)(void* pMgr, uint32_t uId,
                                 char* pOut, int nCap);       // FUN_141766170
extern int (*g_fnLbrGetLeagueName)(void* pMgr, uint32_t uKey,
                                   char* pOut, int nCap);     // FUN_141766250

// ---- the logic object's vtable (mgr+8) ----
extern uint64_t (*g_fnLbrGetMyLeague)(void* pLogic);          // vt+0x3f0
extern void (*g_fnLbrSendMsg)(void* pLogic, uint64_t uPlayer,
                              void* pMsg, uint64_t uFlag);    // vt+0xb8

// FUN_141771f90 — the league BeRob broadcast
void LeagueBeRobBroadcast(void* pMgr, uint32_t uKey, int nCount,
                          uint32_t* pIds);

}  // namespace syndicate

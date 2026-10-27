// ============================================================
// Syndicate.dll port — unit T6/D32: the CLeague member
// set-tree family (the 0x30-node), verbatim.
// Node layout: left@+0, parent@+8, right@+0x10,
// key@+0x18 (16 bytes: +0x18 and +0x20; the compare
// sites read +0x18 as u32), color@+0x28, _Isnil@+0x29;
// the head sentinel: head->parent = the root,
// head->left = the first, head->right = the last.
// The map object: anchor@+0, head@+0x30, size@+0x38.
// Functions: 141746790 (the key node alloc), 141746a60
// (the head alloc: new 0x30, zeroed links, color black —
// the return was elided in the decompile but c4b0
// consumes it), 14174c4b0 (the member map ctor: the
// anchor with the owner back-ref + the head with
// _Isnil=1 + the self-links + size 0), 141749fc0 (the
// lower_bound descent + the found/end output iter),
// 141748820 (the insert + the red-black rebalance, the
// length gate at 0xffffffffffffffd), 1417447d0 (the
// iterator++ with the debug checks; the past-the-end
// tail is the CRT-compliant out_of_range throw),
// 141749c00 (the erase: the invalid-iterator gate + the
// successor splice incl. succ==right-child + the
// unlink + the first/last descents + the verbatim
// remove-rebalance loop with the CARRIED entry parent
// + the size gate), 14174a150 (the erase-range: the
// owner checks + the both-end clear + the inline
// successor advance loop), 141747270 (the clear: the
// right-subtree recursive frees + the left walk + the
// head relinks + size 0), 141746650 (the recursive
// right-subtree free), 141744560 (the LEFT-lift
// rotation), 141745ad0 (the RIGHT-lift rotation),
// 14174c530 (the member map dtor: the full-range
// erase [begin={anchor,*head}, end={anchor,head}] +
// the head delete + the zeroed slots — the ANCHOR is
// freed by the CLeague dtor cfc0, not here).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- FUN_141746790 ----
void* LeagueNodeAlloc(void* pLeft, void* pParent,
                      void* pRight, void* pKey,
                      uint8_t uColor);
// ---- FUN_141746a60 ----
void* LeagueHeadAlloc();
// ---- FUN_14174c4b0 ----
void* LeagueMemberCtor(void* pMap);
// ---- FUN_141749fc0 ----
// out = {anchor, node-or-head}
void* LeagueFind(void* pMap, void* pOutIter,
                 uint32_t* pKey);
// ---- FUN_141748820 ----
void* LeagueInsert(void* pMap, void* pOutIter,
                   uint8_t bLeft, void* pAttach,
                   void* pKey);
// ---- FUN_1417447d0 ----
// the iterator state: {owner@+0, node@+8}
void LeagueIterNext(void* pIterState);
// ---- FUN_141749c00 ----
void* LeagueErase(void* pMap, void* pOutIter,
                  void* pIter);
// ---- FUN_14174a150 ----
void* LeagueEraseRange(void* pMap, void* pOutIter,
                       void* pBegin, void* pEnd);
// ---- FUN_141747270 ----
void LeagueClear(void* pMap);
// ---- FUN_141746650 ----
void LeagueFreeSubtree(void* pMap, void* pNode);
// ---- FUN_141744560 ----
void LeagueRotateL(void* pMap, void* pNode);
// ---- FUN_141745ad0 ----
void LeagueRotateR(void* pMap, void* pNode);
// ---- FUN_14174c530 ----
void LeagueMemberDtor(void* pMap);

} // namespace syndicate

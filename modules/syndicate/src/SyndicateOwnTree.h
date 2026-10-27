// ============================================================
// Syndicate.dll port — unit T4/D30: the internal
// OWN tree family (the 0x28-node set-tree), verbatim.
// Node layout: left@+0, parent@+8, right@+0x10,
// key@+0x18 (the qword copy; the compare sites read
// it as u32), color@+0x20, _Isnil@+0x21; the head
// sentinel: head->parent = the root, head->left =
// the first, head->right = the last.
// Functions: 14173bcb0 (the anchor alloc: new 0x28,
// zeroed, color black — the return was elided in
// the decompile but c580 consumes it), 14173bd10
// (the key node alloc), 14173bc60 (the recursive
// free: the right recursion + the left reentry),
// 14173b240 (the iterator++ with the debug checks),
// 14173c580 (the map ctor), 14173c470 (the clear),
// 14173c5c0 (the insert + the red-black rebalance,
// the length gate at 0x1ffffffffffffffd),
// 14173bf40 (the double-descent pair walk).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- FUN_14173bcb0 ----
void* OwnAnchorAlloc();
// ---- FUN_14173bd10 ----
void* OwnNodeAlloc(void* pLeft, void* pParent,
                   void* pRight, void* pKey,
                   uint8_t uColor);
// ---- FUN_14173bc60 ----
void OwnFreeRecurse(void* pMap, void* pNode);
// ---- FUN_14173b240 ----
// the iterator state: {ptr@+0, the saved node@+8}
void OwnIterNext(void* pIterState);
// ---- FUN_14173c580 ----
void OwnMapCtor(void* pMap);
// ---- FUN_14173c470 ----
void OwnClear(void* pMap);
// ---- FUN_14173c5c0 ----
void* OwnInsert(void* pMap, void* pOutIter,
                uint8_t bLeft, void* pAttach,
                void* pKey);
// ---- FUN_14173bf40 ----
// out = {owner, the remember node, owner, the
// second-descent node}
void* OwnDescendPair(void* pMap, void* pOut4,
                     uint32_t* pKey);

} // namespace syndicate

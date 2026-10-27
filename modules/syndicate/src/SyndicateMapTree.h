// ============================================================
// Syndicate.dll port — unit T3/D29: the internal
// std::map tree core family, verbatim. The node
// layout (MSVC _Tree_node): left@+0, parent@+8,
// right@+0x10, key u32@+0x18, value@+0x20,
// color@+0x60, _Isnil@+0x61; the head sentinel:
// head->parent = the root, head->left = the first,
// head->right = the last.
// Functions: 14173bc00 (the node alloc: new 0x68,
// color black), 14173e1a0 (the key node alloc: the
// fields + the string-move value via de50, color
// from the arg, _Isnil 0), 14173b830 / 14173b890
// (the rotations), 14173b6c0 (the iterator++ with
// the debug checks), 14173e240 (the recursive node
// clear with the orphan call), 14173d1e0 (the
// lower_bound), 14173e790 (the insert + the
// red-black rebalance, the length_error gate at
// 0x38e38e38e38e38c).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// the map object layout: the anchor@+0, the head
// @+0x30, the size@+0x38

// ---- FUN_14173bc00 ----
void* TreeNodeAlloc();
// ---- FUN_14173e1a0 ----
// (left, parent, right, {key u32, value string},
// color) — the value via the de50 seam
void* TreeNodeAllocKey(void* pLeft, void* pParent,
                      void* pRight, uint32_t* pKeyVal,
                      uint8_t uColor);
// ---- FUN_14173b830 ----
void TreeRotateR(void* pMap, void* pNode);
// ---- FUN_14173b890 ----
void TreeRotateL(void* pMap, void* pNode);
// ---- FUN_14173b6c0 ----
// the iterator state: {ptr@+0, the saved node@+8};
// advances in-order, fires g_fnMeritInvalid on
// the past-the-end walk
void TreeIterNext(void* pIterState);
// ---- FUN_14173e240 ----
void TreeClearNodes(void* pMap, void* pNode);
// ---- FUN_14173d1e0 ----
// out[0] = the anchor, out[1] = the lower_bound
// node (the head when all keys are smaller)
void* TreeFind(void* pMap, void* pOut,
                     uint32_t* pKey);
// ---- FUN_14173e790 ----
// (map, out_iter, bLeft, attachNode, {key, value})
// — the verbatim rebalance; returns out_iter
void* TreeInsert(void* pMap, void* pOutIter,
                 uint8_t bLeft, void* pAttach,
                 uint32_t* pKeyVal);

} // namespace syndicate

// ============================================================
// Syndicate.dll port — unit T10/D36 (part 2b): the MEMBERS-MAP
// family (the 0x3d-node map @ entity+0x98), verbatim.
// Node layout: left@+0, parent@+8, right@+0x10, a NINE-u32
// value record @+0x18..+0x38 (the key is the FIRST u32,
// read at +0x18), color@+0x3c, _Isnil@+0x3d. The head: new
// 0x40, zeroed links, color black. Map layout as D32.
// Every tree function here was byte-diffed against its
// D32/users counterpart in the decompile: identical modulo
// the node-family offsets (isnil +0x29->+0x3d, color
// +0x28->+0x3c) and the callee ids — the same MSVC template
// instantiation over the 0x40 node.
//   141746a00 — the 0x40 head alloc
//   1417466e0 — the node alloc (the 9-u32 value copy)
//   141746600 — the recursive right-subtree free
//   1417478a0 — the map ctor (NO anchor — the CLeague ctor
//               owns the members-map anchor slot)
//   1417483e0 — the raw insert + rebalance (the length gate
//               0x71c71c71c71c71a)
//   141749690 — the UNIQUE insert (both neighbor dup gates;
//               flag at out+0x10; insOut[2] adjacency)
//   1417477c0 — the equal_range (the D29 leaf rule): two
//               lower_bound descents, out[0..3] =
//               {anchor, first, anchor, last}
//   141744cb0 — the iterator++ (== 1417447d0 modulo isnil)
//   141745c90 — the left-lift rotation (== 141744560)
//   141745c30 — the right-lift rotation (== 141745ad0)
//   141747400 — the single erase (== 141749c00: the invalid
//               gate + the splice + the remove-rebalance)
//   1417481d0 — the erase-range (== 14174a150)
//   141749840 — the erase(key): equal_range + the successor
//               count walk + the erase-range; returns the
//               count (MSVC map::erase(key))
//   1417471f0 — the clear (== 141747270)
// The find (141749980) is already SyndicateLeagueMember's
// LeagueMemberFind (D36 part 1).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- FUN_141746a00 ----
void* MembersHeadAlloc();
// ---- FUN_1417466e0 ----
// pVal points at the NINE-u32 value record (36 bytes)
void* MembersNodeAlloc(void* pLeft, void* pParent,
                       void* pRight, uint32_t* pVal,
                       uint8_t uColor);
// ---- FUN_141746600 ----
void MembersFreeSubtree(void* pMap, void* pNode);
// ---- FUN_1417478a0 ----
void MembersMapCtor(void* pMap);
// ---- FUN_1417483e0 ----
void* MembersInsert(void* pMap, void* pOutIter,
                    uint8_t bLeft, void* pAttach,
                    uint32_t* pVal);
// ---- FUN_141749690 ----
// pOut = {anchor, node, flag@+0x10}; returns pOut
void* MembersInsertUnique(void* pMap, void* pOut,
                          uint32_t* pKey);
// ---- FUN_1417477c0 ----
// pOut[0..3] = {anchor, first, anchor, last}
void* MembersEqualRange(void* pMap, void* pOut,
                        uint32_t* pKey);
// ---- FUN_141744cb0 ----
void MembersIterNext(void* pIterState);
// ---- FUN_141745c90 ----
void MembersRotateL(void* pMap, void* pNode);
// ---- FUN_141745c30 ----
void MembersRotateR(void* pMap, void* pNode);
// ---- FUN_141747400 ----
void* MembersErase(void* pMap, void* pOutIter,
                   void* pIter);
// ---- FUN_1417481d0 ----
void* MembersEraseRange(void* pMap, void* pOutIter,
                        void* pBegin, void* pEnd);
// ---- FUN_141749840 ----
uint64_t MembersEraseKey(void* pMap, uint32_t* pKey);
// ---- FUN_1417471f0 ----
void MembersClear(void* pMap);

} // namespace syndicate

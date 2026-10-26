// ============================================================
// Syndicate.dll port — unit T10/D36 (part 2a): the USERS-MAP
// family (the 0x30-node users map @ entity+0x58), verbatim.
// The CLeague users map keeps the SAME map/node layout as the
// D32 member map (anchor@+0, head@+0x30, size@+0x38; node:
// left/parent/right, the 16-byte pair key@+0x18, color@+0x28,
// _Isnil@+0x29 — the users-map node key is read at +0x18).
// Every function below was byte-diffed against its D32
// counterpart in the decompile: IDENTICAL modulo the callee
// ids (the allocator/advance/rotation names) — the same MSVC
// template instantiation.
//   1417265a0 — the node alloc (== 141746790)
//   141729790 — the insert + the red-black rebalance (==
//               141748820; the length gate at
//               0xffffffffffffffd; the new node's children
//               point at the head — the D29 leaf convention)
//   14172afb0 — the UNIQUE insert: the lower_bound descent +
//               the two neighbor duplicate gates (the right
//               candidate + the predecessor walk) + the raw
//               insert; output iter {anchor, node} with the
//               INSERTED FLAG byte at out+0x10. NOTE: the
//               decompile's local_38/local_30 are an ADJACENT
//               16-byte pair home (the raw insert writes both
//               slots) — modeled as insOut[2].
//   14172b160 — the erase (== 141749c00: the invalid-iterator
//               gate + the successor splice + the unlink + the
//               first/last descents + the verbatim carried-
//               parent remove-rebalance + the size gate)
//   141722ef0 — the iterator++ (== 1417447d0)
//   141724870 — the right-lift rotation (== 141745ad0)
//   1417224f0 — the left-lift rotation (== 141744560)
// The map ctor/find for the users map REUSE the D32 family
// (SyndicateLeagueTree) — no separate originals exist.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- FUN_1417265a0 ----
void* UsersNodeAlloc(void* pLeft, void* pParent,
                     void* pRight, void* pKey,
                     uint8_t uColor);
// ---- FUN_141729790 ----
// outIter = {anchor, new-node}; returns outIter
void* UsersInsert(void* pMap, void* pOutIter,
                  uint8_t bLeft, void* pAttach,
                  void* pKey);
// ---- FUN_14172afb0 ----
// pOut = {anchor, node, flag@+0x10}; returns pOut
void* UsersInsertUnique(void* pMap, void* pOut,
                        uint32_t* pKey);
// ---- FUN_14172b160 ----
void* UsersErase(void* pMap, void* pOutIter,
                 void* pIter);
// ---- FUN_141722ef0 ----
void UsersIterNext(void* pIterState);
// ---- FUN_141724870 ----
void UsersRotateR(void* pMap, void* pNode);
// ---- FUN_1417224f0 ----
void UsersRotateL(void* pMap, void* pNode);

} // namespace syndicate

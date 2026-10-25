// ============================================================
// Syndicate.dll port — unit T5/D31: the ERASE layer,
// verbatim. The value of the 0x68 map is ITSELF a
// nested 0x28 own-tree object embedded at +0x20:
// {anchor@+0x20, head@+0x50, size@+0x58} — the
// erase's value dtor calls the REAL cb90 on it.
// Functions: 14173b0e0/b140 (the 0x28 rotations),
// 14173c0b0 (the 0x28 erase: the out_of_range
// gate + the splice cases + the remove-rebalance),
// 14173cb90 (the 0x28 erase-range), 14173e350
// (the 0x68 erase + the nested-tree value dtor),
// 14173eb10 (the 0x68 erase-range), 14173ecf0
// (the 0x68 tree dtor).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- FUN_14173b0e0 ----
void OwnRotateR(void* pMap, void* pNode);
// ---- FUN_14173b140 ----
void OwnRotateL(void* pMap, void* pNode);
// ---- FUN_14173c0b0 ----
// the iter state: {owner@+0, node@+8}; throws
// std::out_of_range("invalid map/set<T> iterator")
// on the past-the-end erase
void* OwnErase(void* pMap, void* pOutIter,
               void* pIterState);
// ---- FUN_14173cb90 ----
// erases the range [param_3, param_4) of the
// iter states; the full-range case clears
void* OwnEraseRange(void* pMap, void* pOutIter,
                    void* pIterFirst,
                    void* pIterLast);
// ---- FUN_14173e350 ----
void* MapErase(void* pMap, void* pOutIter,
               void* pIterState);
// ---- FUN_14173eb10 ----
void* MapEraseRange(void* pMap, void* pOutIter,
                    void* pIterFirst,
                    void* pIterLast);
// ---- FUN_14173ecf0 ----
void MapTreeDtor(void* pMap);

} // namespace syndicate

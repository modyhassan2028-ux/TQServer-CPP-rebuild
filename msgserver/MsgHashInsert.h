#ifndef MSG_HASH_INSERT_H
#define MSG_HASH_INSERT_H
#include <cstdint>
#include "MsgHashCtor.h"

namespace msg {

// ===== M71: the INSERT family of the activity hash
// map - the FINAL unit of the hash closure (all the
// semantics resolved in M71_HASH_INSERT_PLAN.md):
//   interval [head[i], head[i+1]) inclusive, insert
//   before head[idx+1], boundaries propagate DOWN as
//   {proxy, new-node} while head[j] == old position
//   (the loose-boundary invariant), fill = {proxy,END}

// ORIGINAL FUN_14000f880: the full insert.
// pOut: 0x18 bytes {it0, it1, inserted-byte@+0x10}
// pHint: the caller's iterator pair - updated in
// place; pKey: the int key. Returns pOut.
void* HashInsert(SHashContainer* pC, void* pOut,
                 int32_t* pKey, void* pHint);

// ORIGINAL FUN_14000fd50: the rehash rebuild - walk
// the list and TRANSFER each front node to its
// bucketed position until the front is bucket-0's
// head (the MSVC _For transplant)
void HashRebuild(SHashContainer* pC);

// ORIGINAL FUN_140010970: op[] - probe; on miss
// insert with the END hint; returns node + 0x14
// (the value slot)
void* HashValueAt(SHashContainer* pC, int32_t* pKey);

} // namespace msg
#endif

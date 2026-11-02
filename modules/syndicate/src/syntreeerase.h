// ============================================================================
// syntreeerase.h — RAW Syndicate.dll v6159 · the erase side of the syndicate trees: the
//   step, both rotations, the subtree sweep, the whole-map clear, the single-node erase
//   with its red/black fixup, the range erase and the manager's erase-by-id.
//   Node: left +0x00, parent +0x08, right +0x10, key +0x18, value +0x20, colour +0x28
//   (0 red, 1 black), nil byte +0x29. Map: tag +0x00, head +0x30, count +0x38.
// ============================================================================
#ifndef SYNDICATE_SYNTREEERASE_H
#define SYNDICATE_SYNTREEERASE_H

#include <cstdint>

#include "modules/syndicate/src/syntreemap.h"

namespace tq {

// 0x1417c6e80 — walk the iterator one node on (the inlined successor, here as a function)
void SynTreeIterIncrement(SynTreeIter* pIter);

// 0x1417c6f90 — the right child moves up over its parent
void SynTreeRotateLeft(void* pMap, void* pNode);

// 0x1417c6ff0 — the left child moves up over its parent
void SynTreeRotateRight(void* pMap, void* pNode);

// 0x1417c7a50 — frees a subtree, right side before left, never touching a nil node
void SynTreeEraseSubtree(void* pMap, void* pNode);

// 0x1417c8ef0 — frees every node and points the head's three links back at itself
void SynTreeClear(void* pMap);

// 0x1417c7c30 — erase one node, keeping the red/black rules. A nil iterator is the binary's
//   std::out_of_range("invalid map/set iterator"); the count only drops when it is non-zero.
void SynTreeEraseNode(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter);

// 0x1417c9140 — erase [first, last)
void SynTreeEraseRange(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast);

// 0x1417cd3a0 — remove every entry with this key and answer how many there were
int64_t SynManagerEraseById(void* pMap, const uint32_t* pKey);

}  // namespace tq

#endif  // SYNDICATE_SYNTREEERASE_H

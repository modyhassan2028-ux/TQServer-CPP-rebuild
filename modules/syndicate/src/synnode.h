// ============================================================================
// synnode.h — RAW Syndicate.dll v6159 · the node builders behind the two container kinds,
//   the sentinel builders, the iterator comparisons and the small owner accessors.
//   The builders show the exact node layout the erase and search code already relies on:
//     id node   (0x30): left +0x00, parent +0x08, right +0x10, key +0x18, value +0x20,
//                       colour +0x28, nil +0x29
//     name node (0x48): left +0x00, parent +0x08, right +0x10, key string +0x18 (0x20 long),
//                       colour +0x40, nil +0x41
// ============================================================================
#ifndef SYNDICATE_SYNODE_H
#define SYNDICATE_SYNODE_H

#include <cstdint>
#include <string>

#include "modules/syndicate/src/syntreemap.h"

namespace tq {

// 0x1417c80d0 / 0x1417c8680 — the same id-node builder twice (one per map instantiation).
//   The pair it copies is 16 bytes: the key word then the value.
void* SynNodeNewIdA(void* pLeft, void* pParent, void* pRight, const void* pPair, uint8_t uColour);
void* SynNodeNewIdB(void* pLeft, void* pParent, void* pRight, const void* pPair, uint8_t uColour);

// 0x1417c84d0 / 0x1417c8620 — a fresh id node with every link null, black, and the nil byte
//   cleared. Note it is NOT the sentinel (the sentinel carries nil = 1).
void* SynNodeNewIdEmptyA();
void* SynNodeNewIdEmptyB();

// 0x1417c62e0 — build a name node in a caller-supplied buffer (no allocation)
void* SynNodeBuildName(void* pBuffer, void* pLeft, void* pParent, void* pRight,
                       const std::string* pKey, uint8_t uColour);

// 0x1417c82e0 — the allocating form of the same builder
void* SynNodeNewName(void* pLeft, void* pParent, void* pRight, const std::string* pKey,
                     uint8_t uColour);

// 0x1417c8530 — a fresh name node, all links null, black, nil byte cleared
void* SynNodeNewNameEmpty();

// 0x1417c5940, 0x1417c5b30, 0x1417c5b80, 0x1417c5e10 — four byte-identical bodies, one per
//   container instantiation. They only compare the node words.
bool SynIterEquals(const SynTreeIter* pA, const SynTreeIter* pB);

// 0x1417c5f60, 0x1417c6210 — the same pair of instantiations for the != form
bool SynIterNotEquals(const SynTreeIter* pA, const SynTreeIter* pB);

// 0x1417c45b0 / 0x1417c4cb0 — store the pointer unless it is null, answering whether it did
bool SynOwnerAssignA(void** ppOut, void* pValue);
bool SynOwnerAssignB(void** ppOut, void* pValue);

// 0x1417c4770 / 0x1417c4780 — the word at +0x08 of the owning object
uint32_t SynOwnerGetWordAt8(void* pObj);
void SynOwnerSetWordAt8(void* pObj, uint32_t uValue);

}  // namespace tq

#endif  // SYNDICATE_SYNODE_H

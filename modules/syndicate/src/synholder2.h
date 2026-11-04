// ============================================================================
// synholder2.h — RAW Syndicate.dll v6159 · four more copies of the eight-byte self-reference
//   holder (bodies identical to 0x1417ce920's first half, verified by diff) and the id map's
//   iterator distance, which walks the range and counts the steps.
// ============================================================================
#ifndef SYNDICATE_SYNHOLDER2_H
#define SYNDICATE_SYNHOLDER2_H

#include <cstdint>

#include "modules/syndicate/src/syntreemap.h"

namespace tq {

void* SynMapCtorHolderC(void* pOwner);   // 0x1417cc940
void* SynMapCtorHolderD(void* pOwner);   // 0x1417cc990
void* SynMapCtorHolderE(void* pOwner);   // 0x1417cc9e0
void* SynMapCtorHolderF(void* pOwner);   // 0x1417cca30

// 0x1417cca80 — count the entries in [first, last) by stepping the id map's in-order walk.
//   The third argument is the counter the binary increments in place.
void SynTreeIterDistanceId(SynTreeIter* pFirst, SynTreeIter* pLast, int64_t* pCount);

}  // namespace tq

#endif  // SYNDICATE_SYNHOLDER2_H

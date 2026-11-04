// ============================================================================
// synmeedlist.h — RAW Syndicate.dll v6159 · the meed-record slot lists: the walk that closes
//   every object in a slot range, the release that nulls them, the vector truncation both
//   end with, and the list teardown.
//   The vector lives at owner+0x08: its container tag at +0x08, its begin at owner+0x20 and
//   its end at owner+0x28.
// ============================================================================
#ifndef SYNDICATE_SYNMEEDLIST_H
#define SYNDICATE_SYNMEEDLIST_H

#include <cstdint>

namespace tq {

// 0x14172cfe0 — truncate the vector to its begin. The binary computes the byte count from
//   the same field it copies from, so the move never runs; the only real effect is
//   end = begin. Kept exactly as written, including the move that cannot fire.
void SynVectorResetEnd(void* pVector);

// 0x141779670 — for every slot in [0x20, 0x28): ask the object through slot 0x40 with a
//   zero flag, then through slot 0 with flag one. The slots keep their values, then the
//   vector is truncated.
void SynMeedDestroySlots(void* pOwner);

// 0x1417792a0 — for every non-null slot: one call through slot 0 with flag one, then the
//   slot is written zero twice. Then the vector is truncated.
void SynMeedReleaseSlots(void* pOwner);

// 0x1417798b0 — release every slot, free the vector buffer, zero the three words, free the
//   tag object at +0x08
void SynMeedListDone(void* pOwner);

}  // namespace tq

#endif  // SYNDICATE_SYNMEEDLIST_H

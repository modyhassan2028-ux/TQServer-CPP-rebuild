// ============================================================================
// synattr.h — RAW Syndicate.dll v6159 · the CSynAttr comparison row.
//   synattr.cpp is one of the 41 __FILE__ paths the binary reports, and 0x141787c60 is
//   the only row this wave reaches from it: the two-key ordering the sifts call.
// ============================================================================
#pragma once

#include <cstdint>

namespace tq {

// 0x141787c60 — compares two attribute records through the context's key reader, and when
// the keys are equal falls back to the record's second key. Returns true for "the first
// sorts after the second".
bool Slot_141787c60(void* pCtx, void* pNodeA, void* pNodeB);

}  // namespace tq

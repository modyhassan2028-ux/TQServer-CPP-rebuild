// ============================================================================
// synpbblk.h — RAW Syndicate.dll v6159 · 0x1417e3af0, the walker ReadVarint32 falls back to.
//   The order is the whole point of this one:
//     position != end            -> read from the block
//     position == end, refill ok -> read from the block
//     position == end, no refill -> the end-of-message pair runs: the flag +0x24 is raised
//                                   when less than +0x30 has been consumed, otherwise it is set
//                                   to whether +0x28 equals +0x30; both paths answer zero and
//                                   never touch the position.
// ============================================================================
#ifndef TQ_SYN_PBBLK_H
#define TQ_SYN_PBBLK_H

#include <cstdint>

namespace tq {

extern bool (*g_fnBlkRefill)(void* pThis);                  // 0x1417e4140
extern bool (*g_fnBlkReadValue)(void* pThis, int32_t* pOut);  // 0x1417e5450

// 0x1417e3af0
int32_t SynReadVarint32Walker(void* pThis);

}  // namespace tq

#endif

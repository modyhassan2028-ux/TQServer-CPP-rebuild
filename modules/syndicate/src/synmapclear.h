// ============================================================================
// synmapclear.h — RAW Syndicate.dll v6159 · emptying a whole map and letting go of its
//   sentinel. The erase covers [head->left, head), so the sentinel itself is still alive
//   for the erase to use and is freed right after.
// ============================================================================
#ifndef SYNDICATE_SYNMAPCLEAR_H
#define SYNDICATE_SYNMAPCLEAR_H

#include <cstdint>

namespace tq {

// 0x1417c9650 — erase every entry of an id map, free its head, null +0x30 and +0x38
void SynMapClearAndFreeId(void* pMap);

// 0x1417cda70 — the same for a name map
void SynMapClearAndFreeName(void* pMap);

// 0x1417c8590 — a fresh 0x28-byte node: three null links, colour one at +0x20, nil zero
//   at +0x21. Answers nothing; the binary leaves the block only in RAX as a side effect.
void* SynNodeNewEmpty28(void);

}  // namespace tq

#endif  // SYNDICATE_SYNMAPCLEAR_H

// ============================================================================
// synrecordrelease.h — RAW Syndicate.dll v6159 · the last two pieces the manager holders need:
//   the second id insert (its node builder is the twin 0x1417c8680) and the teardown that
//   empties the two maps a record carries at +0x38 (id) and +0x78 (name).
// ============================================================================
#ifndef SYNDICATE_SYNRECORDRELEASE_H
#define SYNDICATE_SYNRECORDRELEASE_H

#include <cstdint>

#include "modules/syndicate/src/syntreemap.h"

namespace tq {

// 0x1417cc600 — the same insert as 0x1417c9310, built through 0x1417c8680
void* SynMapInsertIdB(void* pMap, void* pOut, bool bLeft, void* pWhere, const void* pPair);

// 0x1417cdd70 — delete every object a map entry points at (through its slot zero with flag
//   one), free both trees, then reset both sentinels. Answers one.
uint64_t SynRecordReleaseMaps(void* pOwner);

}  // namespace tq

#endif  // SYNDICATE_SYNRECORDRELEASE_H

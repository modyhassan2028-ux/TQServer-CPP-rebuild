// ============================================================================
// synerase2.h — RAW Syndicate.dll v6159 · the third and fourth erase families. Their bodies
//   are the ones already ported, with a different colour byte, nil byte, step and rotation
//   pair; the diff against 0x1417c7c30 shows nothing else differs.
//     kind 0x28: colour +0x20, nil +0x21, step 0x1417c6580, rotations 0x1417c71f0/0x1417c7250
//     kind idB:  colour +0x28, nil +0x29, step 0x1417c6610, rotations 0x1417c6100/0x1417c6170
// ============================================================================
#ifndef SYNDICATE_SYNERASE2_H
#define SYNDICATE_SYNERASE2_H

#include <cstdint>

#include "modules/syndicate/src/syntreemap.h"

namespace tq {

// 0x1417c6580 / 0x1417c6610
void SynTreeIterIncrement28(SynTreeIter* pIter);
void SynTreeIterIncrementIdB(SynTreeIter* pIter);

// 0x1417c9de0 / 0x1417ca270
void SynTreeEraseNode28(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter);
void SynTreeEraseNodeIdB(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter);

// 0x1417cc2a0 / 0x1417cc450
void SynTreeEraseRange28(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast);
void SynTreeEraseRangeIdB(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast);

// 0x1417cdae0 / 0x1417cdbc0 — erase everything, then the sentinel goes too
void SynMapClearAndFreeC(void* pMap);
void SynMapClearAndFreeD(void* pMap);

}  // namespace tq

#endif  // SYNDICATE_SYNERASE2_H

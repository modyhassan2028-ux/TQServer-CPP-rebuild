// ============================================================================
// syntreeclear2.h — RAW Syndicate.dll v6159 · the clear pair for the third map kind (its nil
//   byte at +0x21) and the second clear pair of the id kind (the same shape as the already
//   ported 0x1417c7a50 / 0x1417c8ef0, a separate copy in the binary).
// ============================================================================
#ifndef SYNDICATE_SYNTREECLEAR2_H
#define SYNDICATE_SYNTREECLEAR2_H

namespace tq {

void SynTreeEraseSubtreeAt21(void* pMap, void* pNode);   // 0x1417c8770
void SynTreeClearAt21(void* pMap);                       // 0x1417ca1a0
void SynTreeEraseSubtreeIdB(void* pMap, void* pNode);    // 0x1417c87c0
void SynTreeClearIdB(void* pMap);                        // 0x1417ca630

}  // namespace tq

#endif  // SYNDICATE_SYNTREECLEAR2_H

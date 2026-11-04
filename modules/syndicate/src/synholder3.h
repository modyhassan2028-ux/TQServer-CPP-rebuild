// ============================================================================
// synholder3.h — RAW Syndicate.dll v6159 · the map objects the manager holds: four
//   constructors (one body, four sentinel kinds), six destroyers (clear the map, then free the
//   tag object at +0x00) and the find-then-insert that builds the hint itself.
// ============================================================================
#ifndef SYNDICATE_SYNHOLDER3_H
#define SYNDICATE_SYNHOLDER3_H

#include <cstdint>

namespace tq {

// constructors: an eight-byte tag pointing back at the map, then a sentinel
void* SynMapCtorNameA(void* pMap);   // 0x1417ce9a0, sentinel 0x1417c8530, nil +0x41
void* SynMapCtorNameB(void* pMap);   // 0x1417cf0c0, same body as above
void* SynMapCtor28(void* pMap);      // 0x1417cf140, sentinel 0x1417c8590, nil +0x21
void* SynMapCtorIdC(void* pMap);     // 0x1417ceaa0, sentinel 0x1417c8620, nil +0x29
void* SynMapCtorIdD(void* pMap);     // 0x1417cf1c0, same body as above

// destroyers: empty the map through its own clear, then release the tag
void SynMapDestroyIdA(void* pMap);    // 0x1417ce6b0
void SynMapDestroyIdA_B(void* pMap);  // 0x1417ceb20
void SynMapDestroyName(void* pMap);   // 0x1417ce6e0
void SynMapDestroyNameB(void* pMap);  // 0x1417ceb50
void SynMapDestroyC(void* pMap);      // 0x1417ce850
void SynMapDestroyC_B(void* pMap);    // 0x1417cebf0
void SynMapDestroyD(void* pMap);      // 0x1417ce8f0
void SynMapDestroyD_B(void* pMap);    // 0x1417cef20

// 0x1417ce880 — walk to the insertion point like a lower_bound (the key compared as a signed
//   dword) then insert. pPair is the sixteen-byte key-then-value pair.
void* SynMapFindInsertId(void* pMap, void* pOut, const void* pPair);

}  // namespace tq

#endif  // SYNDICATE_SYNHOLDER3_H

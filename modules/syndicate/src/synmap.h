// ============================================================================
// synmap.h — RAW Syndicate.dll v6159 · the insert side of the two container kinds: the map
//   constructors that lay down the sentinel, and the insert with its red/black fixup.
//   Map object: tag +0x00, head +0x30, count +0x38. The rest of the layout is the one the
//   search and erase code already uses (see synnode.h).
// ============================================================================
#ifndef SYNDICATE_SYNMAP_H
#define SYNDICATE_SYNMAP_H

#include <cstdint>
#include <string>

namespace tq {

// 0x1417c9c20 — lay a sentinel into the map object and empty it
void SynMapInitId(void* pMap);

// 0x1417c9c60 — the same for a name map
void SynMapInitName(void* pMap);

// 0x1417ce920 / 0x1417cf040 — both put an eight-byte self-referential holder at +0x00 and
//   then a sentinel at +0x30; the two bodies are identical, one per owning container.
void* SynMapCtorHolderA(void* pMap);
void* SynMapCtorHolderB(void* pMap);

// 0x1417c9310 — insert one id entry. bLeft says the hint belongs on the left of pWhere.
//   pPair is the 16-byte key-then-value pair the node builder copies.
void* SynMapInsertId(void* pMap, void* pOut, bool bLeft, void* pWhere, const void* pPair);

// 0x1417c9780 — insert one name entry
void* SynMapInsertName(void* pMap, void* pOut, bool bLeft, void* pWhere, const std::string* pKey);

}  // namespace tq

#endif  // SYNDICATE_SYNMAP_H

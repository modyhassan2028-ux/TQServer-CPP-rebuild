// ============================================================================
// syntreeerasestr.h — RAW Syndicate.dll v6159 · the same erase layer for the maps keyed by
//   name. The node is bigger: the key string sits at +0x18, the colour byte is +0x40 and the
//   nil byte +0x41. Everything else (head +0x30, count +0x38, left +0x00, parent +0x08,
//   right +0x10) is unchanged, so the step and both rotations are the same body as the id
//   maps and are shared here instead of being copied twice.
// ============================================================================
#ifndef SYNDICATE_SYNTREEERASESTR_H
#define SYNDICATE_SYNTREEERASESTR_H

#include <cstdint>

#include "modules/syndicate/src/syntreemap.h"

namespace tq {

// 0x1417c63c0
void SynTreeIterIncrementStr(SynTreeIter* pIter);

// 0x1417c70e0 / 0x1417c7140
void SynTreeRotateLeftStr(void* pMap, void* pNode);
void SynTreeRotateRightStr(void* pMap, void* pNode);

// 0x1417cba90 — frees a subtree and destroys each key string before releasing the node
void SynTreeEraseSubtreeStr(void* pMap, void* pNode);

// 0x1417cbee0 — erase one name node with the red/black fixup
void SynTreeEraseNodeStr(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter);

// 0x1417cd890 — erase [first, last) from a name map (both ends at the head clears the map)
void SynTreeEraseRangeStr(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast);

// 0x1417ce710 — remove every entry carrying this name and answer how many there were
int64_t SynManagerEraseByName(void* pMap, const std::string* pKey);

}  // namespace tq

#endif  // SYNDICATE_SYNTREEERASESTR_H

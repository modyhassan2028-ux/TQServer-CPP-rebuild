// ============================================================================
// syntreemap.h — RAW Syndicate.dll v6159 · the three tree searches the syndicate manager
//   is built on, plus the two manager queries that ride on them.
//   Map object: the container tag at +0x00, the head node at +0x30. Nothing else is read.
//   Node: left +0x00, parent +0x08, right +0x10, key at +0x18, value at +0x20, and the nil
//   byte at +0x29 for the id maps or +0x41 for the name maps.
// ============================================================================
#ifndef SYNDICATE_SYNTREEMAP_H
#define SYNDICATE_SYNTREEMAP_H

#include <cstdint>
#include <string>

namespace tq {

// the pair every search hands back: the map's own tag and the node it landed on
struct SynTreeIter {
    void* pTag;     // +0x00
    void* pNode;    // +0x08
};

// and the four words equal_range hands back
struct SynTreeRange {
    void* pTagFirst;    // +0x00
    void* pFirst;       // +0x08
    void* pTagLast;     // +0x10
    void* pLast;        // +0x18
};

// 0x1417c8f70 — the node that carries exactly this key, or the head when there is none
//   (the walk sets a candidate on every left turn and the final test rejects it unless the
//   keys are equal, so this is a find and not a lower_bound)
void SynTreeFindUint(void* pMap, SynTreeIter* pOut, const uint32_t* pKey);

// 0x1417c7ff0 — the same range of nodes whose key equals the wanted one
void SynTreeEqualRangeUint(void* pMap, SynTreeRange* pOut, const uint32_t* pKey);

// 0x1417c81c0 — the same, keyed by name instead of a number
void SynTreeEqualRangeStr(void* pMap, SynTreeRange* pOut, const std::string* pKey);

// 0x1417cad00 — the record the id map at +0x08 holds for that id, or null
void* SynManagerRecordById(void* pMgr, uint32_t uId);

// 0x1417cd250 — true when the name is absent from the name map at +0x48 (a null name is
// reported and answers false)
bool SynManagerNameAbsent(void* pMgr, const char* pszNewName);

}  // namespace tq

#endif  // SYNDICATE_SYNTREEMAP_H

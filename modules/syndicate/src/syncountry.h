// ============================================================================
// syncountry.h — RAW Syndicate.dll v6159 · country.cpp: the two country-list sweeps and
//   the tree erasers under them.
//   The country object keeps four map holders: the holder's debug proxy at +0x00, the
//   map's own head at +0x30 and its count at +0x38. Each sweep walks one map's records,
//   then tears that map down, then tears the neighbouring map down without touching its
//   records.
// MODELLING NOTE (declared, not guessed):
//   0x1417364e0 and 0x141736750 both carry std::map debug-iterator calls made through the
//   IAT at 0x1418233c0 (_invalid_parameter_noinfo). They are a build artefact of the
//   iterator debug level, not game logic, so they are not reproduced here; every store and
//   every call the routines really make is.
// ============================================================================
#ifndef SYNDICATE_SYNCOUNTRY_H
#define SYNDICATE_SYNCOUNTRY_H

#include <cstdint>
#include <cstddef>

namespace tq {

// the node of the list the sweeps walk: left, parent, right, the record at +0x20 and the
// nil byte the tree uses at +0x29
struct SynCountryNode {
    void* pLeft;        // +0x00
    void* pParent;      // +0x08
    void* pRight;       // +0x10
    uint64_t u18;       // +0x18
    void* pRecord;      // +0x20
    uint8_t u28;        // +0x28
    uint8_t uNil;       // +0x29
    uint8_t aPad[6];    // +0x2a
    void* pContTag;     // +0x30
};

// a holder inside the country object: proxy at +0x00, map head at +0x30, count at +0x38
struct SynMapHolder {
    void* pProxy;       // +0x00
    uint64_t aPad[5];   // +0x08
    void* pHead;        // +0x30
    uint64_t uCount;    // +0x38
};

// 0x1417262c0 (nil byte +0x29) and 0x141726310 (nil byte +0x49). 0x141726360 is the same
// body again with the nil byte at +0x1d, which 0x141726210 already carries.
void SynNodeErase29(void* pCtx, void* pNode);
void SynNodeErase49(void* pCtx, void* pNode);
void SynNodeErase1d(void* pCtx, void* pNode);

// 0x1417360a0 — the record callback the sweeps use when they are asked to keep the record
// instead of destroying it. It moves the record into the map at +0x40 keyed by the ushort
// the record's child 3 reports, and it needs that map's insert type, so it is a hook for
// now and nothing about it is invented here.
extern void (*g_pfnCountryMoveRecord)(void* pSelf, void* pRecord, void* a3, void* a4);

// 0x1417364e0 walks the holder at +0x90 (head +0xc0, count +0xc8) and then tears down the
// holder at +0x150 (head +0x180, count +0x188); 0x141736750 does the same pair one holder
// over, at +0xd0 and +0x190.
void SynCountrySweepA(void* pSelf, uint8_t uDestroy, void* a3, void* a4);
void SynCountrySweepB(void* pSelf, uint8_t uDestroy, void* a3, void* a4);

}  // namespace tq

#endif  // SYNDICATE_SYNCOUNTRY_H

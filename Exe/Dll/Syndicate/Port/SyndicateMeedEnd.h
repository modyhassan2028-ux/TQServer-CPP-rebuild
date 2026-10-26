// SyndicateMeedEnd — D54/T16: the ProcessEndMeed
// flow (141783470) + its real callees:
//   14177d7a0  CMeedSetMgr::BuildIdList — the
//              member-id list builder (the int
//              vector with the direct store +
//              the 14172d120 grow)
//   14177d180  CMeedSetMgr::DeleteSynMeed —
//              the multi-erase (the memmove
//              compaction + the vt+0x40/vt+0
//              release pair, rescans for more)
// The flow: for each member id of the type (1/3):
// the meed refund (vt+0x1f0/vt+0x1f8 POSITIVE),
// the emoney display (vt+0x350 with mt=4), the
// db90 re-apply, the gmlog (fmt 14182fd60), the
// prompt(7) announce, and the erase.
#ifndef SYNDICATE_MEED_END_H
#define SYNDICATE_MEED_END_H

#include <cstdint>

namespace syndicate {

// the int-vector grow (14172d120 — a seam; the
// direct-store path is REAL)
extern void (*g_fnMeedVecInsertInt)(
    void* pVec, void* pPair[2], int64_t n,
    void* pVal);

// DAT_14182fd60 — the ProcessEndMeed gmlog fmt
// (a .rdata datum; the marker default)
extern const char* g_szMeedLogFmtEnd;

// ---------- FUN_14177d7a0 ----------
// (pPool, nType, pIntVec {proxy,?,begin,end,cap})
void MeedIdListBuild(void* pPool, int nType,
                     void* pVec);

// ---------- FUN_14177d180 ----------
// (pPool, nId, nType) — erases EVERY member
// whose vt+8(2)->vt+0x40 == id; always 1
uint64_t MeedDeleteSynMeed(void* pPool,
                           int nId, int nType);

// ---------- FUN_141783470 ----------
// (pUser, nType)
uint64_t MeedProcessEnd(void* pUser, int nType);

}  // namespace syndicate
#endif

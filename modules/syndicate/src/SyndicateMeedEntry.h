// SyndicateMeedEntry — D55a/T16: the 5-int entry
// (0x14-stride) vector machinery + the FULL
// introsort family, verbatim from
// Syndicate.dll.decompiled.c. The back-end of the
// DistributeSynMeed flow (141784cd0):
//   141780750  the entry swap
//   1417820e0  the fwd copy (returns dst end)
//   141782c20  the bwd copy
//   141782480  the copy-backward variant
//   141782550  the fill-copy (one entry n times)
//   141782060  the rotate-backward
//   141781ca0  the alloc (the bad_alloc gate +
//              operator_new(n*0x14))
//   141783b70  the generic insert (3 paths:
//              realloc-grow / mid-move / tail)
//   141784100  the push-grow (the iterator dance)
//   1417848f0  the push (the direct store or grow)
//   141783ad0  the erase-tail
//   141781eb0  the median-of-3 network
//   141782640  the median-of-9 net (big ranges)
//   141781f30  the heap sift-down
//   1417807c0  the heap sift-up
//   141782740  the make-heap loop
//   141782810  the guarded insertion sort
//   141782990  the sift-one helper
//   1417833d0  the final insertion (unguarded)
//   141782ca0  the partition
//   141783f50  the introsort core (depth budget)
//   141784260  the sort entry (the debug gates)
// The comparator at LAB_141780100 (the awards
// order) is a .text thunk NOT decompiled — a
// documented seam (no Syndicate.dll binary in
// this workspace for an objdump pass).
#ifndef SYNDICATE_MEED_ENTRY_H
#define SYNDICATE_MEED_ENTRY_H

#include <cstdint>

namespace syndicate {

// the entry: {id, ?, point, money, emoney} —
// 5 x 4 bytes, stride 0x14
struct MeedEntry5 {
    int32_t v[5];
};

// ---- the seams ----
// LAB_141780100 — the awards comparator thunk
// (body unknown; 16 bytes of .text between the
//  meed functions). D55b must set it.
extern char (*g_fnMeedEntryCmp)(
    const MeedEntry5* a, const MeedEntry5* b);

// ---------- FUN_141780750 ----------
void MeedEntrySwap5(MeedEntry5* a, MeedEntry5* b);

// ---------- FUN_1417820e0 ----------
// copies [p1,p2) to p3 fwd; returns the dst end
MeedEntry5* MeedEntryCopyFwd(MeedEntry5* p1,
                             MeedEntry5* p2,
                             MeedEntry5* p3);

// ---------- FUN_141782c20 ----------
// copies [p1,p2) to p3 backward
int64_t MeedEntryCopyBwd(int64_t p1, int64_t p2,
                        int64_t p3);

// ---------- FUN_141782480 ----------
// the copy-backward variant (the lVar1 offset
// dance); returns p3 + count*0x14
int64_t MeedEntryCopyTo(MeedEntry5* p1,
                        MeedEntry5* p2,
                        int64_t p3);

// ---------- FUN_141782550 ----------
// copies ONE entry n times to p1
void MeedEntryFillCopy(MeedEntry5* p1, int64_t n,
                       const MeedEntry5* pSrc);

// ---------- FUN_141782060 ----------
// rotates [p2,p3) down one entry (to p1)
int64_t MeedEntryRotBwd(int64_t p1, int64_t p2,
                        int64_t p3);

// ---------- FUN_141781ca0 ----------
// allocates n entries (the bad_alloc gate)
void* MeedEntryAlloc(void* pCookie, uint64_t n);

// ---------- FUN_141783b70 ----------
// the generic insert: n entries from pSrc at
// the pair position {proxy@pPair[0], pos@pPair[1]}
void MeedEntryVecInsert(
    void* pVec, void* pPair[2], uint64_t n,
    const MeedEntry5* pSrc);

// ---------- FUN_141784100 ----------
// the push-grow (the 48f0 fallback)
void MeedEntryVecGrow(void* pVec, void* pPair[2],
                      const MeedEntry5* pSrc);

// ---------- FUN_1417848f0 ----------
// the push: the direct store or the grow
void MeedEntryVecPush(void* pVec,
                      const MeedEntry5* pEntry);

// ---------- FUN_141783ad0 ----------
// the erase-tail (the 141782480 copy + the
// end rewind)
void MeedEntryVecEraseTail(void* pVec);

// ---------- FUN_141784260 ----------
// the sort entry (the proxy gates + the core);
// the args are the MSVC iterator PAIRS:
// pPairFirst = {proxy, firstPos},
// pPairLast  = {proxy, lastPos}
void MeedEntrySort(void* pPairFirst[2],
                   void* pPairLast[2],
                   char (*pCmp)(const MeedEntry5*,
                               const MeedEntry5*));

}  // namespace syndicate
#endif

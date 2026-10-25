// ============================================================
// Syndicate.dll port — unit T7/D33: the league member-list
// SORT family (the MSVC introsort on uint[] with a
// state-carrying comparator), verbatim.
// The sorted arrays hold member IDs; the comparator is
// FUN_1417ba4c0 (a rank-then-id ordering resolved via the
// CSyndicateLogic singleton — its own subgraph is the D34
// family; here it is bound through the g_fnLeagueCmp seam,
// default nullptr = unbound, the sort never calls it).
// Functions:
//   14174cb10 — the introsort loop: (count-1)>>2 < 0x21
//     → straight insertion; depth exhausted (param_3 < 1)
//     → make_heap + sort_heap; else the median-of-3
//     partition 141747c80 + the recursion, the depth
//     shrinking as n/2 + (n/2)/2.
//   141747090 — the guarded insertion sort (the
//     end-gallop memmove + the inner shift loop).
//   141747c80 — the quicksort partition: the true median
//     (141746f30) + the sentinel walks + the 5-region
//     swap tail; returns {cut, next} (the two loop
//     bounds) in param_1[0..1].
//   141746f30 — the median-of-3/median-of-9 pivot
//     ordering (0x28 elements or more → the 9-sample
//     net via three 141746310 passes).
//   141746310 — the 3-element ordered net (sort3).
//   141747ec0 — the make_heap loop (the Floyd sift-down
//     from the last parent, hole-lifting via 1417463a0).
//   1417463a0 — the sift-down hole loop (the child pick
//     by comparator; the odd-last-child copy tail).
//   141748e30 — the sort_heap loop (swap the front with
//     the back + re-sift; until size 1).
//   141745480 — the sift-up hole loop (the final place
//     of the sift-down; NOTE: the decompile lost the
//     comparator-state argument — it shows an unnamed
//     stack slot `&stack0x00000028` = the caller's
//     state home — the port threads it as the 5th
//     parameter, Ghidra artifact documented).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// the comparator seam: FUN_1417ba4c0 (state*, a, b) —
// "a strictly before b" under the league rank order.
// bound by the D34 family port; tests bind a stub.
extern bool (*g_fnLeagueCmp)(int* pState, uint32_t uA, uint32_t uB);

// 14174cb10 — the introsort entry (first, last, depth, state)
void LeagueSortIntro(uint32_t* puFirst, uint32_t* puLast, int64_t nDepth, int nState);

// 141747090 — the insertion sort (first, last, state)
void LeagueSortInsertion(uint32_t* puFirst, uint32_t* puLast, int nState);

// 141747c80 — the partition: out[0..1] = {cut, next}
void LeagueSortPartition(uint64_t* pOut, uint32_t* puFirst, uint32_t* puLast, int nState);

// 141746f30 — the median pivot ordering
void LeagueSortMedianNet(uint32_t* puFirst, uint32_t* puMid, uint32_t* puLast, int nState);

// 141746310 — the 3-element net
void LeagueSortOrder3(uint32_t* puA, uint32_t* puB, uint32_t* puC, int nState);

// 141747ec0 — make_heap
void LeagueSortMakeHeap(int64_t lFirst, int64_t lLast, int nState);

// 1417463a0 — the sift-down hole loop
void LeagueSortSiftDown(int64_t lFirst, int64_t lHole, int64_t lLen, uint32_t uVal, int nState);

// 141748e30 — sort_heap
void LeagueSortSortHeap(uint32_t* puFirst, int64_t lLast, int nState);

// 141745480 — the sift-up final place
void LeagueSortPushHole(int64_t lFirst, int64_t lHole, int64_t lTop, uint32_t uVal, int nState);

}  // namespace syndicate

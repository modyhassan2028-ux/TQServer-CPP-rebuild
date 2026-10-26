// SyndicateMeedSort — D50/T16: the REAL sort family
// (the lazy-sort backend of CMeedRecord::GetMeedRecord)
//   1417781b0  the comparator (type/grade/sub0
//              descending; equal → TRUE, verbatim)
//   1417786d0  the median-of-3 order
//   1417788c0  the median guess (the ninther over
//              9 samples when > 0x28 elements)
//   141778760  the heap sift-down
//   141778d90  the bottom-up make-heap
//   141778f80  the sort-heap
//   141778a20  the insertion sort (the rotate path
//              via memmove when < *begin)
//   141778b60  the partition (transliterated 1:1
//              from the original disassembly —
//              the equal-run skipping + the pivot
//              cell migration; goto-faithful)
//   141779790  the introsort driver (threshold
//              0x21, depth *= 3/4, recurse the
//              smaller side, heap fallback)
#ifndef SYNDICATE_MEED_SORT_H
#define SYNDICATE_MEED_SORT_H

#include <cstdint>

namespace syndicate {

// FUN_1417781b0 (verbatim — the equal→true tail
// preserved; it is NOT a strict weak ordering,
// exactly like the original)
bool MeedSortCmp(void* a, void* b);

// the seam target: FUN_141779eb0's backend call
void MeedSortRaw(void** ppBegin, void** ppEnd,
                 int nCount);

// the individual stages (exposed for the tests)
typedef bool (*MeedSortCmpFn)(void*, void*);

void MeedMedian3(void** p1, void** p2,
                void** p3, MeedSortCmpFn cmp);
void MeedGuessMedian(void** p1, void** p2,
                     void** p3,
                     MeedSortCmpFn cmp);
void MeedSiftDown(void** base, int64_t nHole,
                  int64_t nLen, void* pVal,
                  MeedSortCmpFn cmp);
void MeedMakeHeap(void** begin, void** end,
                  MeedSortCmpFn cmp);
void MeedSortHeap(void** begin, void** end,
                  MeedSortCmpFn cmp);
void MeedInsertionSort(void** begin, void** end,
                       MeedSortCmpFn cmp);
void MeedSortDriver(void** begin, void** end,
                    int64_t nDepth,
                    MeedSortCmpFn cmp);

} // namespace syndicate
#endif

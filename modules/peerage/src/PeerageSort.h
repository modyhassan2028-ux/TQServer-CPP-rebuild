// ============================================================
// Peerage.dll port — unit T3/D19: the sort engine
// (MSVC std::sort/introsort) + the comparison chain.
// Addresses verbatim: introsort 141555b60, partition
// 1415545b0, med3/med9 141554000 / 141553aa0, the heap
// sift 141553b30, make_heap 1415547e0, sort_heap
// 141554f80, insertion 141554160, the comparator
// 141552810, the key 141552180.
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

// the comparator's row seams (elem+8 -> vt+0x10(n) ->
// rec; rec vt+0x58 = the int64 value / vt+0x40 = the
// uint id). (141552810 / the D18 FindById seams)
extern void* (*g_fnRowQuery2)(void* pRow, int n);
extern int64_t (*g_fnRowGetValue)(void* pRec);
extern uint32_t (*g_fnRowGetId)(void* pRec);
// the log seam (DAT_14155a358)
extern void (*g_fnSortLogError2)();
// _invalid_parameter_noinfo (f80's checks)
extern void (*g_fnInvalidParameter2)();

// FUN_141552180: *(dword*)(elem + 0x18)
uint32_t PeerageSortKey(void* pElem);

// FUN_141552810: the comparison chain — descending
// by the row's value (vt+0x58), tie: descending by
// the key (+0x18), tie: ascending by the id (vt+0x40)
bool PeerageSortPred(void* pA, void* pB);

// FUN_141555b60: the introsort loop (depth =
// param_3; count < 0x21 -> insertion; depth < 1 and
// count > 0x20 -> heap; else partition + the
// smaller-half recursion)
void SortIntrosort(void** ppFirst, void** ppLast,
                   int64_t nDepth,
                   bool (*pPred)(void*, void*));

// the sort family used by Introsort:
// FUN_1415545b0 (the partition; out: the mid pair)
void SortPartition(void* itOut[2], void** ppFirst,
                   void** ppLast,
                   bool (*pPred)(void*, void*));
// FUN_141554000 (med3 or the 9-sample med)
void SortMedian3or9(void** ppA, void** ppB,
                     void** ppC,
                     bool (*pPred)(void*, void*));
// FUN_141553aa0 (the 3-comparison median)
void SortMedian3(void** ppA, void** ppB,
                  void** ppC,
                  bool (*pPred)(void*, void*));
// FUN_141553b30 (the heap sift with the hole value)
void SortSiftDown(void** ppBase, int64_t nHole,
                  int64_t nLen, void* pVal,
                  bool (*pPred)(void*, void*));
// FUN_1415547e0 (make_heap, bottom-up)
void SortMakeHeap(void** ppFirst, void** ppLast,
                  bool (*pPred)(void*, void*));
// FUN_141554f80 (sort_heap, the pop loop)
void SortHeapSort(void** ppFirst, void** ppLast,
                  bool (*pPred)(void*, void*));
// FUN_141554160 (the insertion sort)
void SortInsertion(void** ppFirst, void** ppLast,
                    bool (*pPred)(void*, void*));

// the sort-call wrapper of FUN_141555f80 (the part
// before the promotion walk): the debug checks +
// Introsort(begin, end, count, the pred)
struct CPeerageSortMgr;
void SortPeerageVector(CPeerageSortMgr* pMgr);

} // namespace peerage

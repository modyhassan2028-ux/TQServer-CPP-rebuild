// ============================================================
// Peerage.dll port — unit T9/D25: the CPeerageSort
// object-family completion + the CMyHeap static
// wrappers + the MSVC container-proxy iterator family.
// Addresses verbatim: 141552040 (the CPeerageSort dtor
// — vft, the row vt[0] release, the double row zero),
// 141552180 (the +0x18 key getter), 141552190 (the
// static CMyHeap instance — init-once + atexit),
// 141552250 (the CMyHeap::Free wrapper), 1415522b0
// (the CMyHeap::IsValidPt wrapper), 141552310 (the
// CPeerageSort scalar deleting dtor — the heap free on
// odd flags), 141552780 (row vt+0x10(0) -> vt+0x40),
// 1415527a0 (row vt+0x10(2) -> vt+0xa0 set + row
// vt+0x38(0)), 141552ed0/f10/f80/fc0 (the proxy
// iterator deref/next/prev/eq with the MSVC debug
// range checks).
// NOT ported (CRT/STL boilerplate with standard
// equivalents — documented only): 141552460/4a0/4d0
// (std::bad_alloc ctor/dtor/scalar dtor), 141552530
// (an empty thunk), 141552540/590/5f0 (std::logic_error
// family), 1415525d0 (the std::string data accessor —
// SSO len > 0xf ? ptr : inline), 141552650/6b0/700
// (std::length_error family). These back the D18
// throw seams (g_fnThrowLengthError /
// g_fnThrowBadAlloc) whose defaults abort.
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

struct CPeerageSort;   // PeerageSortMgr.h

// ---- the seams ----
// row vt[0]: (row, flags, a, b, -2) — the deleting
// dtor reached from the 141552040 dtor
extern void (*g_fnRowDtorVt0)(void* pRow, uint64_t uFlags,
                              void* pA, void* pB,
                              int64_t nC);
// 141552190: CMyHeap::CMyHeap(heap, "CPeerageSort")
extern void (*g_fnMyHeapCtor)(void* pHeap,
                              const char* pszName);
// 141552190: the atexit registration
extern void (*g_fnAtexitReg)(void (*fn)());
// 141552250: CMyHeap::Free(heap, p)
extern void (*g_fnMyHeapFree)(void* p);
// 1415522b0: CMyHeap::IsValidPt(heap, p)
extern void (*g_fnMyHeapIsValidPt)(void* p);
// the peerage::CPeerageSort::vftable identity used by
// the dtor (141552040 writes it first — verbatim)
extern const void* g_pSortVftable;

// ---- FUN_141552040 ----
// (elem, a, b) — vft, then the row vt[0] release and
// the row zeroed TWICE
void DtorCPeerageSort(void* pElem, uint64_t uA,
                       uint64_t uB, uint64_t uC);

// ---- FUN_141552180 ----
uint32_t GetSortKey18(void* pElem);

// ---- FUN_141552190 ----
// the init-once static: DAT_14155f2e8 |= 1, the CMyHeap
// ctor + atexit, then &DAT_14155f2e0
void* GetHeapInstance();

// ---- FUN_141552250 ----
void HeapFreeWrap(void* p);

// ---- FUN_1415522b0 ----
void HeapIsValidPtWrap(void* p);

// ---- FUN_141552310 ----
// (elem, flags) — the dtor + the heap free on odd
void* ScalarDeletingDtorSort(void* pElem,
                             uint64_t uFlags);

// ---- FUN_141552780 ----
// elem+8 row vt+0x10(0) -> rec vt+0x40 (the id probe;
// the original discards the result)
void ElemProbeRowId0(void* pElem);

// ---- FUN_1415527a0 ----
// elem+8 row vt+0x10(2) -> rec vt+0xa0(rec, val), then
// row vt+0x38(row, 0) — the same seams as D23
void ElemSetRowValue2(void* pElem, uint64_t uVal);

// ---- the MSVC proxy iterator family ----
// the iterator: {proxy*, slot} (16 bytes)
// ---- FUN_141552ed0 ----
void* ProxyAt(void** ppIter);
// ---- FUN_141552f10 ----
void** ProxyNext(void** ppIter);
// ---- FUN_141552f80 ----
void** ProxyPrev(void** ppIter);
// ---- FUN_141552fc0 ----
bool ProxyEq(void** ppA, void** ppB);

// TEST HOOK (the original has no reset — the DAT is a
// process-lifetime static; the tests need a fresh
// instance per section)
void ResetHeapStatic();

} // namespace peerage

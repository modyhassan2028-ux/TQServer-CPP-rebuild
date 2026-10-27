// SyndicateModuleTail.h — D58: the module-family
// tail (14177e900..141780cb0, the gap between the
// module layer and the meed family).
//
// Addresses (Syndicate.dll, ImageBase 0x141720000):
//   14177ed50  SetPtrCheckA   (log+store; body
//              identical to 14177f660 — literal dup)
//   14177eda0  SendLeaveAward — DECOMPILE FAILED
//              (812 bytes, index "failed") → seam
//   14177f2d0  ScalarDtorDel  (flags&1 → delete)
//   14177f2f0  FreeStaticBuf  (DAT_141886d50)
//   14177f340  LeaveAwardFlow (the offline award
//              broadcast: vt+0x3a0 query id 0xe,
//              per-record money/emoney/type reads,
//              Delete(), SendLeaveAward, dtor)
//   14177f660  SetPtrCheckB   (literal dup of ed50)
//   14177f6b0  CallNTimes     (the MSVC array loop)
//   141780170  Vec4At         (stride-4 checked at)
//   1417801b0  Vec14Deref     (iterator deref)
//   1417801f0  Vec14Next      (cursor += 0x14)
//   141780230  Vec14DerefB    (literal dup of 1b0)
//   141780270  Vec14NextB     (literal dup of 1f0)
//   1417802f0  Vec14Eq        (container + cursor)
//   1417803c0  Vec14Diff      ((a-b)/0x14)
//   141780440  Vec14Advance   (checked += n*0x14)
//   1417804d0  Vec14New       (bad_alloc + op_new)
//   141780540  Vec14DiffB     (literal dup of 3c0)
//   1417808b0  MeedHeapInst   (CMyHeap static init)
//   141780910  MeedHeapAlloc  (CMyHeap::Alloc)
//   141780970  MeedHeapFree   (CMyHeap::Free)
//   1417809d0  MeedHeapValid  (CMyHeap::IsValidPt)
//
// The heap statics: DAT_141886d70 (the CMyHeap
// object, tag "CSynArenicMeed") + DAT_141886d78
// (the init flag) + atexit(&LAB_141821fa0).
#ifndef SYNDICATE_MODULE_TAIL_H
#define SYNDICATE_MODULE_TAIL_H

#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the seams ----
// FUN_14177eda0 (SendLeaveAward) — the decompiler
// FAILED on it (812 bytes); body TBD. Returns
// nonzero on success.
extern char (*g_fnSendLeaveAward)(void* pModule,
    uint32_t uId, int nType, int nMoney, int nEMoney);
extern void* (*g_fnOpNew8)(void);          // op_new(8)
extern void* (*g_fnTailOpNew)(size_t n);   // operator_new(n)
// (g_fnOpDelete — the SyndicateModule seam)
extern void (*g_fnTailLogError)(const char* p);
        // log_InlineLogERROR(fmt, ...)
extern void (*g_fnTailInvalid)();   // _invalid_param_noinfo
extern void (*g_fnTailThrowBadAlloc)(size_t n);
        // _CxxThrowException(bad_alloc)
// the CMyHeap family (the class lives outside the
// wave; the static object is ours)
extern void (*g_fnCMyHeapCtor)(void* pHeap,
                               const char* pTag);
extern void* (*g_fnCMyHeapAlloc)(void* pHeap,
                                 size_t n);
extern void (*g_fnCMyHeapFree)(void* pHeap, void* p);
extern char (*g_fnCMyHeapIsValidPt)(void* pHeap,
                                    void* p);
extern void (*g_fnTailAtexit)(void* pFn);
        // atexit(&LAB_141821fa0) — the dtor thunk

// ---- the heap statics ----
extern char g_abMeedHeap[16];   // DAT_141886d70
extern uint8_t g_bMeedHeapInit; // DAT_141886d78
extern const char* k_pszCSynArenicMeed;  // tag

// ---- 14177ed50 / 14177f660 ----
char SetPtrCheckA(void** pp, void* p);
char SetPtrCheckB(void** pp, void* p);

// ---- 14177f2d0 ----
void* ScalarDtorDel(void* p, uint64_t uFlags);

// ---- 14177f2f0 ----
void FreeStaticBuf(void** ppStatic);  // DAT_141886d50

// ---- 14177f340 ----
// pModule: *pModule = the mgr (vt+0x3a0 owner)
uint64_t LeaveAwardFlow(void* pModule, uint32_t uId);

// ---- 14177f6b0 ----
void CallNTimes(void* p, size_t uStride, int n,
                void (*pFn)(void*));

// ---- 141780170 ----
void* Vec4At(void* pVec, size_t uIdx);

// ---- the stride-0x14 vector helpers ----
// iterator: it[0] = the container, it[1] = cursor
void* Vec14Deref(void** ppIt);
void* Vec14DerefB(void** ppIt);
void** Vec14Next(void** ppIt);
void** Vec14NextB(void** ppIt);
char Vec14Eq(void** ppA, void** ppB);
int64_t Vec14Diff(void** ppA, void** ppB);
int64_t Vec14DiffB(void** ppA, void** ppB);
void** Vec14Advance(void** ppIt, size_t n);
void* Vec14New(size_t n);

// ---- the meed heap ----
void* MeedHeapInst();
void* MeedHeapAlloc(size_t n);
void MeedHeapFree(void* p);
char MeedHeapValid(void* p);

}  // namespace syndicate

#endif  // SYNDICATE_MODULE_TAIL_H

// ============================================================
// Training.dll port — the std::map PUBLIC-API wrapper
// family + the mgr accessor. Wave 1, unit T3/D15.
// Addresses verbatim: 1419e3750 / 1419e3840 / 1419e3860 /
// 1419e3a10 / 1419e3aa0 / 1419e3c50 / 1419e4120 /
// 1419e42d0 / 1419e3ca0 / 1419e3de0 / 1419e3e00 /
// 1419e42a0 / 1419e4320 / 1419e4350 / 1419e4170.
// ============================================================
#pragma once
#include "TrainingMgr.h"
#include "TrainingMap.h"
#include <cstdint>

namespace training {

// ---- the _time64 seam (mgr accessor's default value) ----
extern int64_t (*g_fnTime64)();

// ---- FUN_1419e3750: distance ----
// NOTE the ORIGINAL's param order: (FIRST pair, LAST
// pair, &count) — the walk advances the FIRST node.
// Proxy gates + the ++ inline walk verbatim.
void Distance(const void* const* ppFirst,  // {proxy, node}
              const void* const* ppLast,   // {proxy, node}
              uint64_t* pnCount);

// ---- FUN_1419e3840 / FUN_1419e3de0: the delete-ptr pair
// (identical bodies: operator_delete(*pp)) ----
void DeletePtr(void** pp);
void DeletePtr2(void** pp);

// ---- FUN_1419e3860: erase(first, last) ----
// the {proxy,node} pairs; if first==last==head -> Clear;
// else loop: erase(first) (via 1419e2d50) advancing the
// INLINE ++ until the last node. out = the last pair.
void EraseRange(SMapKernel* pKern, SMapIterator* pOut,
                void** ppFirst, void** ppLast);

// ---- FUN_1419e3a10: lower_bound (the thin wrapper) ----
void* LowerBoundRef(SMapKernel* pKern,
                    SMapIterator* pOut, uint32_t uKey);

// ---- the try-emplace out (1419e3aa0) ----
struct STryEmplaceOut {
    void* m_pProxy00;       // +0x00
    STreeNode* m_pNode08;   // +0x08
    uint8_t m_bInserted10;  // +0x10 (the bool)
};

// ---- FUN_1419e3aa0: try-emplace ----
// the inline attach walk (bAddLeft tracking), the
// duplicate check (key <= the walked node's key) on the
// right path, the Lmost/predecessor hint check on the
// left path, then 1419e3360. out: {proxy, node, bool}.
STryEmplaceOut* TryEmplace(SMapKernel* pKern,
                           STryEmplaceOut* pOut,
                           const SValRec* pRec);

// ---- FUN_1419e3c50 / 1419e4120 / 1419e42d0: the proxy
// chain push (three IDENTICAL bodies) —
// node = new(8); node->q0 = *pp; *pp = node ----
void ProxyChainPush(void** pp);
void ProxyChainPush4120(void** pp);
void ProxyChainPush42d0(void** pp);

// ---- FUN_1419e3ca0: erase(key) -> the erased count ----
// LowerBound -> distance(to the found greater-par) ->
// EraseRange(the walked span). Returns the count.
uint64_t EraseKeyCount(SMapKernel* pKern, uint32_t uKey);

// ---- FUN_1419e3e00: emplace_hint ----
// the full MSVC hint cascade (empty / begin / end / the
// prev-vs-key / the next-vs-key checks) falling to
// 1419e3aa0. hint = the {proxy, node} pair.
SMapIterator* EmplaceHint(SMapKernel* pKern,
                          SMapIterator* pOut,
                          const void* const* ppHint,
                          const SValRec* pRec);

// ---- FUN_1419e42a0 / 1419e4320: the kernel dtor pair
// (identical: 1419e3a30 + operator_delete(proxy)) ----
void KernelDtorProxy(SMapKernel* pKern);
void KernelDtorProxy4320(SMapKernel* pKern);

// ---- FUN_1419e4350: the mgr deleting-dtor proxy ----
// *this = vftable; DtorKernelCore(this+0x18);
// operator_delete(this->kern.proxy)
void MgrDtorProxy(void* pMgrBase);

// ---- FUN_1419e4170: the mgr accessor (operator[]) ----
// the inline lower-bound walk; on miss emplaces
// {key, pad, _time64(0)} via 1419e3e00; the proxy gates;
// the node-vs-head gate. RETURNS node + 0x20 (the value
// slot) — the caller writes it (e.g. +0x28 = the time).
void** MgrOpIndex(SMapKernel* pKern, uint32_t* pKey);

} // namespace training

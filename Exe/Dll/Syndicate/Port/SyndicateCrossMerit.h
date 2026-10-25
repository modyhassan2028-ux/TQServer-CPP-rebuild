// ============================================================
// Syndicate.dll port — unit T2/D27: the
// syndicate::CCrossMeritMgr management shell (the map
// owner family), verbatim. Addresses: 14173f3e0 (the
// anchor dtor: tree dtor + delete[0]), 14173f410 (the
// vft dtor variant: vft + tree dtor(map@+8) +
// delete[1]), 14173f450 (the deleting dtor: the tree
// clear + vt[0](p,1)), 14173f490 (the singleton
// dispatch via DAT_141886cd0), 14173f4b0 (the key
// insert: the u32 key local + the tree insert),
// 14173f4d0 (the walk: in-order ++ with the MSVC
// debug checks + the per-key log + the final clear),
// 14173f600 (the ctor: the 8-byte anchor node +
// opnew(8), mgr[0]=anchor, anchor[0]=mgr, the head
// node via 14173bc00 with _Isnil=1 and the self
// links, size=0).
// The map layout (MSVC _Tree): the anchor node at
// map[0], head at +0x30, size at +0x38; the nodes:
// left@0, right@8, parent@0x10, key u32@+0x18,
// _Isnil@+0x61.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- allocation / vft / log seams ----
extern void* (*g_fnMeritOpNew)(size_t);
extern void (*g_fnMeritOpDelete)(void*);
extern void* g_pCrossMeritVft;      // the vft marker
extern void* g_pMeritDatInstance;    // DAT_141886cd0
extern void (*g_fnMeritInvalid)();   // _invalid_parameter

// ---- the STL seams ----
// 14173bc00 — the head/node alloc (operator_new(0x68),
// zeroed links, color@+0xc=1, _Isnil=0). The decompile
// types it void but RAX carries the node.
extern void* (*g_fnNodeAlloc)();
// 14173ecf0 — the tree dtor (eb10 unwind + delete
// head + head/size zeroed)
extern void (*g_fnTreeDtor)(void* pMap);
// 14173ef10 — the tree clear on the OUTER object
// (head@outer+0x38): e240(map, head->parent) + the
// head relinks + size=0
extern void (*g_fnTreeClearOuter)(void* pOuter);
// 14173ef80 — the keyed insert (map, &key) -> count
extern int64_t (*g_fnTreeInsert)(void* pMap,
                                 uint32_t* pKey);
// 14173e240 — the recursive node clear (map, node)
extern void (*g_fnTreeClearNodes)(void* pMap,
                                 void* pNode);
// 141781b60 — the log target factory
extern void* (*g_fnMeritLogFactory)();
// 141784cd0 — (target, key u32, 3)
extern void (*g_fnMeritLogWrite)(void* pT,
                                 uint32_t uKey,
                                 int n);

// ---- FUN_14173f3e0 ----
void MeritDtorAnchor(void* pOuter);
// ---- FUN_14173f410 ----
void MeritDtorVft(void* pOuter);
// ---- FUN_14173f450 ----
void MeritDeletingDtor(void* pOuter);
// ---- FUN_14173f490 ----
void MeritStaticDispatch(uint64_t uA, uint64_t uB,
                         uint64_t uC, uint64_t uD);
// ---- FUN_14173f4b0 ----
void MeritInsert(void* pOuter, uint32_t uKey);
// ---- FUN_14173f4d0 ----
void MeritWalkAndClear(void* pOuter);
// ---- FUN_14173f600 ----
void* MeritCtor(void* pOuter);

} // namespace syndicate

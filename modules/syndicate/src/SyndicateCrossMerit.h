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


// ---- D28: the rest of the family ----
// 14173f680 — the keyed value fetch (the
// lower_bound descent + the insert-if-missing
// owner chain + the end deref check), returns
// the node value slot at +0x20
extern void* (*g_fnMeritOpNew2)(size_t);
// 14173bcb0 — the list anchor alloc (+0x21 = 1)
extern void* (*g_fnListAnchorAlloc)();
// 14173de50 — the string move
extern void (*g_fnStrMoveDE50)(void* pDst,
                              void* pSrc);
// 14173ce30 — the string dtor
extern void (*g_fnStrDtorCE30)(void* pStr);
// 14173f0c0 — the tree insert (map, out_iter,
// the {anchor, node} pair, the key)
extern void* (*g_fnTreeInsertF0C0)(void* pMap,
    void* pOut, void* pPair, uint32_t* pKey);
// 14173cb90 — the orphan unwind (owner, out, a, b)
extern void (*g_fnOrphanCB90)(void* pOwner,
    void* pOut, void* a, void* b);
// 14173cd80 — the splice (iter, owner)
extern void (*g_fnSpliceCD80)(void* pIter,
                              void* pOwner);
// 14173d1e0 — the lower_bound (map, out_pair, key)
extern void* (*g_fnLowerBoundD1E0)(void* pMap,
    void* pOut, uint32_t* pKey);
// 1417b6210 — the game mgr singleton
extern void* (*g_fnGetGameMgr)();
// the mgr vft+0x2a8 validity check (mgr, key)
extern char (*g_fnMeritValid)(void* pMgr,
                              uint32_t uKey);
// log_InlineLogERROR(&DAT_141824ca8)
extern void (*g_fnMeritLogError)();

// ---- FUN_14173f680 ----
void* MeritValueFetch(void* pMap, uint32_t* pKey);
// ---- FUN_14173f8e0 ----
void* MeritCtorVft(void* pOuter);
// ---- FUN_14173f950 ----
void* MeritDtorVftScalar(void* pOuter,
                         uint32_t uFlags);
// ---- FUN_14173f9c0 ----
void* MeritSingleton();
// ---- FUN_14173fa40 ----
uint8_t MeritGrant(void* pOuter, uint32_t uKey);
// ---- FUN_14173fc80 ----
void MeritDeleteAnchor(void* pMap);

} // namespace syndicate

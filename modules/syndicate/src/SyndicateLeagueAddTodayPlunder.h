#pragma once
// ============================================================================
// SyndicateLeagueAddTodayPlunder.h — unit D74:
// CLeagueMgr::AddTodayPlunderWarInfo — FUN_1417715f0,
// RAW-verified against the recovered v6159 Syndicate.dll.
// The original name is preserved by the embedded log literal
// "CLeagueMgr::AddTodayPlunderWarInfo data repeat idPlunder[lu%]".
//
// Structure (all kit calls map onto the existing D70 container
// seams; the target-map walk is INLINED in the RAW and ported
// inline):
//   1. gates: id==0 / count<=0
//   2. lower_bound(mgr+0x370, id) — on a hit, LOG "data
//      repeat idPlunder" and CONTINUE (no early return)
//   3. the outer value map on the stack (wrapper=OpNew(8),
//      tree=141726c30 with isnil@+0x1d=1 + self links,
//      tree@cell+0x30, size@cell+0x38)
//   4. per target (HARD CAP 10 — RAW `if (9 < i) break`):
//      skip 0; inline BST walk over mgr+0x3b0 (key@+0x18,
//      isnil@+0x61, left@+0, right@+0x10, root@head+8);
//      absent -> build a new inner map, insert uIdPlunder
//      into it, then insert {target, map} into mgr+0x3b0
//      (the pair/move-ctor dance, RAW 1417695b0/14176f690/
//      141770ea0/14172c560/14172a410) and free the
//      moved-from temps; found -> deref checks then insert
//      uIdPlunder into the entry's map at node+0x20
//   5. always: insert the target into the outer map
//      (14172ae00), then myLeague (vt+0x3f0); if
//      target/1e6 == myLeague -> the CMsgLeagueRobOpt
//      send (D71 family): ctor 1417d8390, create(4,0)
//      1417d84d0, serialize 1417d8570, vt+0xb8(logic,
//      id%1e6, msg, 0, 1), dtor 1417d83e0. A create fail
//      -> dtor + full teardown + RETURN (partial state
//      stays — RAW)
//   6. after the loop: size==0 -> teardown only; else the
//      final {id, map} pair into mgr+0x370, the same send
//      with flag 0, teardown.
// ============================================================================
#include <cstdint>

namespace syndicate {

// the D71-family CMsgLeagueRobOpt message calls (RAW ids in
// comments; seamed so tests trap them):
extern void  (*g_fnAtpMsgCtor)(void* pMsg);                    // 1417d8390
extern char  (*g_fnAtpMsgCreate)(void* pMsg, int32_t nA,
                                int32_t nB);                  // 1417d84d0
extern void  (*g_fnAtpMsgSerialize)(void* pMsg);               // 1417d8570
extern void  (*g_fnAtpMsgDtor)(void* pMsg);                    // 1417d83e0
// vt+0xb8 on *(mgr+8) — (logic, id%1e6, msg, 0, flag)
extern void  (*g_fnAtpSendOptText)(void* pLogic, uint32_t uId,
                                   void* pMsg, void* pNull,
                                   int32_t nFlag);

void AddTodayPlunderWarInfo(void* pMgr, uint32_t uIdPlunder,
                            int32_t nCount, uint32_t* aTargets);

}  // namespace syndicate

#pragma once
// ============================================================================
// SyndicateLeaguePlunderStatus.h — unit D77:
// CLeagueMgr::SendUserPlunderWarStatus — FUN_14176ca70,
// RAW-verified against the recovered v6159 Syndicate.dll.
// The name is preserved by the log literals
// "CLeagueMgr::SendUserPlunderWarStatus cannot find the
// plundered league[%lu]" and "...support idServerTarget".
// Previously only a D73 seam (g_fn14176ca70).
//
// Signature: (mgr, uKey, uParam3, uParam4).
// FIVE phases (all RAW):
//   gates: uKey != 0; uParam3 == 0 && uParam4 == 0 -> out.
//   P1 presence: key in 0x370 or 0x3b0 -> the D71
//   RobOpt family: ctor 1417d8390, create(4, 0), fail ->
//   dtor+return; serialize 1417d8570; send: uParam3 == 0
//   -> NEW vt+0x38(logic, uParam4, msg) else vt+8(logic,
//   uParam3, msg); dtor.
//   War gate: mgr+0x35c != 2 -> return.
//   P2..P5 — four RAW-duplicated phases over one NEW msg
//   family (ctor 1417d5460, create 1417d54f0(msg, type,
//   id, warFlag@mgr+0x358, name), append 1417d5820, flush
//   1417d55e0, clear 1417d55a0, count 1417d5770, dtor
//   1417d54b0):
//     P2 0x370 type 1: name 141766170, empty -> 141766250
//     P3 0x3b0 type 0: name 141766250 direct
//     P4 0x430 type 2: name 141766170, empty -> 141766250
//     P5 0x470 type 4: no name, create(4, 0, flag, "")
//   Per phase: lower_bound by uKey; absent -> skip;
//   size@+0x58 != 0; the leftmost deref checks; the first
//   id@+0x18 -> the name fetch (fail -> the phase's log +
//   FULL return); ctor + create; then the in-order loop
//   (isnil@+0x1d) appending each id via 1417d5820 with the
//   batch pattern: fail -> flush + the dual-routed send +
//   clear + RE-CREATE 1417d54f0 with the SAME args + one
//   retry; close: count != 0 -> flush + the dual-routed
//   send; dtor always (also on create fail).
// ============================================================================
#include <cstdint>

namespace syndicate {

// the NEW status msg family
extern void  (*g_fnSusMsgCtor)(void* pMsg);            // 1417d5460
extern char  (*g_fnSusMsgCreate)(void* pMsg, int32_t nType,
                                 uint32_t uId,
                                 uint32_t uWarFlag,
                                 const char* pName);   // 1417d54f0
extern char  (*g_fnSusMsgAppend)(void* pMsg, uint32_t uId);
                                                        // 1417d5820
extern void  (*g_fnSusMsgFlush)(void* pMsg);            // 1417d55e0
extern void  (*g_fnSusMsgClear)(void* pMsg);            // 1417d55a0
extern int16_t (*g_fnSusMsgCount)(void* pMsg);          // 1417d5770
extern void  (*g_fnSusMsgDtor)(void* pMsg);             // 1417d54b0

// the NEW vtable send (vt+0x38)
extern void  (*g_fnSusSendAlt)(void* pLogic, uint32_t uId,
                               void* pMsg);

void SendUserPlunderWarStatus(void* pMgr, uint32_t uKey,
                              uint32_t uParam3,
                              uint32_t uParam4);

}  // namespace syndicate

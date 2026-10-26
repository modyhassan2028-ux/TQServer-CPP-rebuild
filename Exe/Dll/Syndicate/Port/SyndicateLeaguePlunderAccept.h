#pragma once
// ============================================================================
// SyndicateLeaguePlunderAccept.h — unit D73: the two
// CLeagueMgr plunder-war ACCEPT handlers, RAW-verified
// against the recovered v6159 Syndicate.dll:
//
//   FUN_141765920 — UserAcceptPlunderWarInvite, the
//     PLUNDERING side (the mgr+0x370/0x3a0 union map).
//   FUN_141765d60 — the PLUNDERED-side mirror (the
//     mgr+0x3b0/0x3e0 map). The log literal inside it
//     names the original: "CLeagueMgr::UserAccept
//     PlunderWarInvite error point Map[lu%], posX[%d],
//     posY[%d]".
//
// The RAW gate chains (every vt call is on *(mgr+8)):
//   0. user==0 -> 0; mgr+0x35c != 2 -> 0
//   1. vt+0x288 war-open gate; fail -> STR_DIE via
//      vt+0x18 (logic, user, str) -> 0
//   2a. [65920] vt+0x280 alive gate; fail -> 0
//   2b. vt+0x4a8 user-league int; 0 -> 0
//   3.  vt+0x568 (logic, user, league) -> the union key;
//      FUN_141760e40 lower_bound into the phase map
//      (mgr+0x370 / mgr+0x3b0), the {proxy,node} itera-
//      tor checks (proxy null/changed -> invalid; node
//      == head -> not found -> 0; the deref-compat
//      check via proxy->container->head)
//   4a. [65920] the found node's value-map size@+0x58
//       != 0, else 0; first inner node via **(node+0x50)
//       with the proxy deref-check; league =
//       key(first@+0x18)/1000000; 0 -> 0
//   4b. [65d60] no inner-map gate — straight on
//   5.  vt+0x498 (logic, user, res20, res18, res10) ->
//       map info; 0 -> 0; the 8-byte res10 buffer is the
//       packed pos (uVar6), its high dword (uVar11)
//       rides the teleport's 5th arg
//   6.  vt+0x570 map-transmit check; fail ->
//       STR_MAP_NOT_TRANSMIT -> 0
//   7.  vt+0x2a0 user state; != 9 -> vt+0x2a8 set 9
//   8a. [65920] myLeague (vt+0x3f0) == league ->
//        vt+0x4c0 (logic, user, mgr+0x360, *(u64*)
//        (mgr+0x364)); fail -> the error-point log; ok
//        -> 1. Else vt+0x3e8 league2 == league ->
//        vt+0x578 OS gate; ok -> vt+0x4e8 teleport
//        (league, mgr+0x360, packed {mgr+0x364,
//        uVar11}, mgr+0x368); the 0x578 fail only logs
//        (DAT_141824ca8); -> 1. Else vt+0x4d8 enter
//        gate; fail -> STR_USER_CAN_NOT_ENTER_OS -> 0;
//        ok -> vt+0x4e0 (logic, user, league); its
//        fail only logs; then the same vt+0x4e8; -> 1
//   8b. [65d60] vt+0x278 the war-reply gate; 0 ->
//        the vt+0x4c0 local-enter path (fail -> the
//        same error-point log, -> 0/1); != 0 ->
//        vt+0x578 gate; if ok: league2 = vt+0x3e8 ->
//        the vt+0x4e8 teleport with league2; -> 1
//        (unconditional in that branch)
// ============================================================================
#include <cstdint>

namespace syndicate {

// ---- the *(mgr+8) logic vt seams ----
extern char     (*g_fnPwaWarOpenGate)(void* pLogic);        // vt+0x288
extern void     (*g_fnPwaTalkSend)(void* pLogic, int32_t nUser,
                                  const char* psz);        // vt+0x18
extern char     (*g_fnPwaAliveGate)(void* pLogic,
                                    int32_t nUser);        // vt+0x280
extern int32_t  (*g_fnPwaGetUserLeague)(void* pLogic,
                                        int32_t nUser);    // vt+0x4a8
extern uint32_t (*g_fnPwaGetUnionKey)(void* pLogic,
                                    int32_t nUser,
                                    int32_t nLeague);      // vt+0x568
extern char     (*g_fnPwaGetMapInfo)(void* pLogic,
                                     int32_t nUser,
                                     void* pRes20, void* pRes18,
                                     void* pRes10);        // vt+0x498
extern char     (*g_fnPwaCheckMapTransmit)(void* pLogic,
                                     int32_t nUser,
                                     uint32_t uA, uint32_t uB,
                                     uint64_t uPacked);    // vt+0x570
extern int32_t  (*g_fnPwaGetUserState)(void* pLogic,
                                       int32_t nUser);    // vt+0x2a0
extern void     (*g_fnPwaSetUserState)(void* pLogic,
                                       int32_t nUser,
                                       int32_t nState);    // vt+0x2a8
extern char     (*g_fnPwaEnterLocalMap)(void* pLogic,
                                     int32_t nUser,
                                     uint32_t uMap,
                                     uint64_t uPos);      // vt+0x4c0
extern uint32_t (*g_fnPwaGetUserLeague2)(void* pLogic,
                                         int32_t nUser);   // vt+0x3e8
extern char     (*g_fnPwaCheckEnterOs)(void* pLogic,
                                       int32_t nUser);    // vt+0x578
extern char     (*g_fnPwaCheckCanEnter)(void* pLogic,
                                        int32_t nUser);   // vt+0x4d8
extern char     (*g_fnPwaEnterOsLeague)(void* pLogic,
                                        int32_t nUser,
                                        uint32_t uLeague); // vt+0x4e0
extern void     (*g_fnPwaTeleport)(void* pLogic, int32_t nUser,
                                   uint32_t uLeague, uint32_t uMap,
                                   uint64_t uPackedPos,
                                   uint32_t uExtra);      // vt+0x4e8
extern char     (*g_fnPwaWarReplyGate)(void* pLogic,
                                       int32_t nUser);    // vt+0x278

// FUN_141765920 — the PLUNDERING-side accept
bool UserAcceptPlunderWarInvite(void* pMgr, int32_t nUser);
// FUN_141765d60 — the PLUNDERED-side accept
bool UserAcceptPlunderWarInvitePlundered(void* pMgr, int32_t nUser);

}  // namespace syndicate

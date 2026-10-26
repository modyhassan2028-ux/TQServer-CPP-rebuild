#pragma once
// ============================================================================
// SyndicateLeaguePlunderList.h — unit D75:
// CLeagueMgr::SendPlunderWarListToClient — FUN_141766500,
// RAW-verified against the recovered v6159 Syndicate.dll.
// The name is preserved by the log literal
// "CLeagueMgr::SendPlunderWarListToClient msg Append Error!".
//
// Structure (all RAW, v6159):
//   gates: uUser != 0; vt+0x278 (war state) must be 0;
//   vt+0x4a8 (the user's league) must be nonzero.
//   msg: a NEW family — ctor 1417d7df0 + create 1417d7e80
//   (msg, 0). On create fail: only the dtor runs.
//   first entry: if mgr+0x18 is set and != the user's
//   league: FUN_1417630d0 lookup, then the name-length
//   walk (count to -2 = empty): empty -> the +0x28 name
//   (FUN_141743dd0), else the +0x48 name (FUN_141743e00);
//   Append via 1417d8160(msg, myLeague vt+0x3f0, name);
//   fail -> log "msg Append Error!" (and CONTINUE).
//   main loop: the in-order walk over the kit map at
//   mgr+0x148/0x178 (proxy@+0x148, head@+0x178,
//   leftmost=head[0], nodes isnil@+0x21, id@+0x18,
//   key@+0x1c): skip zero id/key; lookup the key in the
//   map at mgr+0x108 (proxy@+0x108, head@+0x138) via
//   FUN_141760950; on a hit: the name tests (+0x48,
//   fallback +0x28) and the NEW batch pattern: on Append
//   fail -> Flush 1417d7f20 + Send vt+8(logic, uUser,
//   msg) + Clear 1417d7ee0 + retry the Append once.
//   close: 1417d80b0(msg) count != 0 -> Flush + the
//   final Send vt+8; dtor 1417d7e40 always.
// ============================================================================
#include <cstdint>

namespace syndicate {

// the vtable probes
extern char     (*g_fnSplWarState)(void* pLogic);      // vt+0x278
extern uint32_t (*g_fnSplUserLeague)(void* pLogic);    // vt+0x4a8
extern void     (*g_fnSplSendMsg)(void* pLogic, uint32_t uUser,
                                  void* pMsg);         // vt+8

// the league-list message family (RAW ids in comments)
extern void     (*g_fnSplMsgCtor)(void* pMsg);          // 1417d7df0
extern char     (*g_fnSplMsgCreate)(void* pMsg, int nA);// 1417d7e80
extern char     (*g_fnSplMsgAppend)(void* pMsg, uint32_t uId,
                                    const char* pName);// 1417d8160
extern void     (*g_fnSplMsgFlush)(void* pMsg);         // 1417d7f20
extern void     (*g_fnSplMsgClear)(void* pMsg);         // 1417d7ee0
extern int16_t  (*g_fnSplMsgCount)(void* pMsg);         // 1417d80b0
extern void     (*g_fnSplMsgDtor)(void* pMsg);          // 1417d7e40

// the lookups
extern void*    (*g_fnSplFindLeague)(void* pMgr,
                                    uint32_t uId);     // 1417630d0
extern void*    (*g_fnSplName48)(void* pLeague);        // 141743e00
extern void*    (*g_fnSplName28)(void* pLeague);        // 141743dd0
extern void*    (*g_fnSplLookup)(void* pMap, void* pOutIter,
                                 uint32_t* pKey);      // 141760950

void SendPlunderWarListToClient(void* pMgr, uint32_t uUser);

}  // namespace syndicate

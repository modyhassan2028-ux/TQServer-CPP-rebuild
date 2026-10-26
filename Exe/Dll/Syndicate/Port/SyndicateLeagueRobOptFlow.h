#pragma once
// ============================================================================
// SyndicateLeagueRobOptFlow.h — unit D72: FUN_14176b0d0,
// CLeagueMgr::PlunderWarStart — the plunder-war STARTUP
// broadcast. RAW-VERIFIED against the recovered original
// Syndicate.dll (Dec 2015 build) via capstone.
//
// ENTRY: PlunderWarStart(mgr, flag) — flag == 0 returns
// immediately. Nonzero: mgr+0x358 = flag, mgr+0x35c = 2.
//
// FIVE sequential walks over the mgr's five union maps
// (identical container kit as D70's LeagueBeRobBroadcast:
// embedded containers, proxy@+0, head@+0x30, size@+0x38;
// outer node = {left@0, parent@8, right@0x10, key u32
// @+0x18, inner-map container@+0x20 (head@+0x50, size
// @+0x58), isnil@+0x61}; inner member node = {left@0,
// parent@8, right@0x10, id u32@+0x18, isnil@+0x1d}):
//   (A) mgr+0x370 / mgr+0x3a0 — PLUNDERING side
//   (B) mgr+0x3b0 / mgr+0x3e0 — PLUNDERED side
//   (C) mgr+0x3f0 / mgr+0x420 — plunder TARGETS
//   (D) mgr+0x430 / mgr+0x460 — SUPPORT targets
//   (E) mgr+0x470 / mgr+0x4a0 — the final member sweep
// Then the closing broadcast: CtorCMsgLeagueOpt +
// CreateMsgLeagueOptText(0x45) (FUN_1417d6740, ported
// here) + vt+0x98 send + DtorCMsgLeagueOpt.
//
// Per-phase body (A) — name via FUN_141766170 (D70 seam)
// with the EMPTY-buffer -2 byte-walk retry via
// FUN_141766250; the D71 RobOpt msg: ctor, Create(4, 0),
// Serialize, vt+0xb8 send(uVar3 % 1000000); the D69
// BeRob msg: ctor, Create(type 1, uLeague, mgr+0x358,
// name), member AppendDword walk with the
// fail->Serialize+send+Clear+re-Create+re-Append dance,
// GetCount != 0 -> Serialize + send; the talk text:
// GetFormatString("STR_PLUNDER_WAR_PLUNDERING") via the
// string-manager seam, snprintf into the 0x100 buffer,
// vt+0xa0(mgr+8, uVar3 % 1000000, text, 0, 0x7ec) — the
// u16 0x7ec rides the 5th (stack) slot RAW; the
// CMsgLeagueOpt 0x3f: ctor + g_fn1417d6820(msg, 0x3f,
// name, 0, uLeague, 0) + vt+0x530(mgr+8, uVar3 %
// 1000000, msg) send + dtor; final D69+D71 dtors.
//
// (B) — the PLUNDERED mirror: name via FUN_141766250
// FIRST (no 141766170), D69 Create type 0, D71 AFTER the
// member walk, text "STR_PLUNDER_WAR_PLUNDERED",
// LeagueOpt type 0x47.
//
// (C)/(D) — the TARGET/SUPPORT phases: name from the
// local target: same-server -> FUN_1417630d0(mgr, id %
// 1000000) + FUN_141743e00/141743dd0 name +
// tq::SafeCopy(dst, src, 0x10); cross-server ->
// FUN_141766000(mgr, id, out8) + SafeCopy(out+0x34);
// failure -> the "cannot find the plundered/support
// idServerTarget[%lu]" log and SKIP; then the -2 walk
// retry via 141766250 ("cannot find the plundered
// idServerTarget" variant), D69 Create type 2/3, the
// member dance, and the GetCount flush-and-send.
//
// (E) — the plain sweep: D69 Create(type 4, 0,
// mgr+0x358, ""), member dance, unconditional
// Serialize + send + AppendDwordString... (final
// 1417d54b0 with the msg itself — the raw's
// end-of-message flush).
//
// STACK frames (raw sizes): D69 msg 0x470, D71 msg
// 0x460, LeagueOpt msg 0x430, name buf 0x15, text 0x100.
// ============================================================================
#include <cstdint>
#include <cstddef>

namespace syndicate {

// ---- the mgr+8 (logic) vtable seams ----
extern uint64_t (*g_fnPwsGetMyLeague)(void* pLogic);       // vt+0x3f0
extern void     (*g_fnPwsSendMsg)(void* pLogic,
                                 uint64_t uPlayer, void* pMsg,
                                 uint64_t uFlag);          // vt+0xb8
extern void*    (*g_fnPwsTextName)(void* pLogic);         // vt+0x488
extern void*    (*g_fnPwsTextNameById)(void* pLogic,
                                       uint32_t uId);      // vt+0x548
extern void     (*g_fnPwsTalk)(void* pLogic, uint32_t uKey,
                               const char* pText,
                               uint64_t uZero,
                               uint16_t uTag);             // vt+0xa0
extern void     (*g_fnPwsSendLeagueOpt)(void* pLogic,
                                        uint32_t uKey,
                                        void* pMsg);        // vt+0x530
extern void     (*g_fnPwsBroadcast45)(void* pLogic,
                                       void* pMsg);        // vt+0x98

// ---- the league-manager helpers ----
extern void*    (*g_fnPwsFindLocalTarget)(void* pMgr,
                                         uint32_t uId);    // FUN_1417630d0
extern const char* (*g_fnPwsTargetName)(void* pObj);       // FUN_141743e00
extern const char* (*g_fnPwsSupportName)(void* pObj);      // FUN_141743dd0
extern int      (*g_fnPwsResolveCrossName)(void* pMgr,
                                          uint32_t uId,
                                          void* pOut64);   // FUN_141766000
extern void     (*g_fnPwsSafeCopy)(char* pDst, const char* pSrc,
                                   size_t n);              // tq::SafeCopy
extern void     (*g_fnPwsSnprintf)(char* pDst, size_t nCap,
                                   const char* pFmt);      // _snprintf
extern void     (*g_fnPwsLogErr)(const char* pFmt,
                                 uint64_t uArg);           // log_InlineLogERROR
extern void     (*g_fnPwsInvalid)();                        // _invalid_parameter_noinfo

// ---- reused seams (D66/D70 + the CMsgCtors) ----
// g_fnLbrGetNameById    (FUN_141766170)
// g_fnLbrGetLeagueName  (FUN_141766250)
// g_fnStringMgrInstance / g_fnStringMgrGetStr (D66)
// CtorCMsgLeagueBeRob / DtorCMsgLeagueBeRob / CreateLeagueBeRob /
//   SerializeLeagueBeRob / ClearLeagueBeRob / GetCountLeagueBeRob /
//   AppendDwordLeagueBeRob                     (D69)
// CtorCMsgLeagueRobOpt / DtorCMsgLeagueRobOpt /
//   CreateLeagueRobOpt / SerializeLeagueRobOpt (D71)
// CtorCMsgLeagueOpt / DtorCMsgLeagueOpt         (LeagueSalary)
// g_fn1417d6820                                  (InviteNotify)

// FUN_1417d6740 — the CMsgLeagueOpt-family "Create":
// Init, then through the PB pointer at msg+0x408 (set by
// CtorCMsgLeagueOpt to msg+8): u16@+8 = 0x13, wire id
// u16@+0xa = 0xa3e, type u16@+0xc = uType. Returns true.
bool CreateMsgLeagueOptText(void* pMsg, uint16_t uType);

// FUN_14176b0d0
void PlunderWarStart(void* pMgr, int32_t nFlag);

}  // namespace syndicate

// ============================================================
// Syndicate.dll port — unit T12/D37 part 1: the SYNDICATE
// MANAGER lookup layer + the league RECORD ACCESSORS,
// verbatim.
//   The manager object (CSyndicateLogic-adjacent holder):
//     provider@+0x08, the LEAGUES map {anchor@+0x38,
//     head@+0x68} (0x29-isnil nodes, key u32@+0x18, the
//     CLeague* value@+0x20), the TOKEN-TYPES map
//     {anchor@+0x1a0, head@+0x1d0} (same node family).
//   14174b000 — LeagueUserIsMember(entity, user): the users
//     map lower_bound descent + the CRT pair → head != node.
//   14175ee00 — MgrUserLeagueId(mgr, user): the FULL map
//     ITERATED walk (begin = head->_Left, the verbatim
//     inlined _Tree_increment successor with the CRT
//     re-validation each step) — the first league whose
//     value passes LeagueUserIsMember → LeagueGetId;
//     end of walk → 0.
//   1417630d0 — MgrLeagueFind(mgr, id): the leagues-map
//     lower_bound descent + the found/end gate + the CRT
//     iterator unwrap (the *anchor container, the
//     container+0x30 head check) → the value@+0x20 or 0.
//   1417631d0 — MgrUserLeagueObj(mgr, user): MgrUserLeagueId
//     then the same descent/unwrap on the returned id.
//   141763680 — MgrLeagueGetType(mgr, id): the find + the
//     value → LeagueGetRec2U32 (141743c80), 0 when absent.
//   141764870 — MgrTokenTypeFind(mgr, type): the SAME
//     descent/unwrap on the token-types map (+0x1a0).
//   1417638e0 — MgrRemoveMember(mgr, leagueId, user): the
//     gates (both ids nonzero) + the find →
//     LeagueRemoveMember.
//   1417646f0 — MgrAddMember(mgr, user, leagueId, p4, p5,
//     p6, p7, p8, name): the gates (user/league/name
//     nonzero AND MgrUserLeagueId==0 — the user must be in
//     NO league) + the find + the VERBATIM 0x1f-byte stack
//     record {p4@0, p5@4, p6(u16)@8, p7(u32)@0xa, p8(u8)@0xe,
//     name[16]@0xf} → LeagueAddMember. NOTE the record tail:
//     AddMember reads u32@0x18/u16@0x1c/u8@0x1e = the
//     name[9..15] bytes (confirmed against the wrapper's
//     stack layout).
//   1417647e0 — MgrGetLeaderId(mgr, leagueId): the find →
//     LeagueGetLeaderId, 0 when absent.
//   141764810 — MgrCreateToken(mgr, leagueId, tokenId, p4):
//     the find; absent → the log_InlineLogERROR (DAT_141824ca8
//     line 0x14f-class site) + 0; else LeagueCreateToken
//     (tokenId passed BOTH as the u32 id and the 64-bit p3,
//     verbatim).
//   The RECORD ACCESSORS (all via the provider at entity+8,
//     resolve = provider-vt[2], then the record vtable
//     slot):
//   141743e70 — LeagueGetLeaderId: the DIRECT u32 read at
//     entity+0x10 (no provider chain).
//   141743c80 — LeagueGetRec2U32: null provider → 0 (NO
//     log); resolve(2) → rec-vt+0x40.
//   141743d10 — LeagueGetRec9Str: null provider → the log +
//     0; resolve(9) → rec-vt+0x48.
//   141743dd0 — LeagueGetRec1Str: null provider → 0 (NO
//     log); resolve(1) → rec-vt+0x78.
//   141743d70 — LeagueGetRecStr(entity, idx): the GENERIC
//     getter — null provider → the log + 0; resolve(idx) →
//     rec-vt+0x78. (The disasm confirms EDX = the caller's
//     index — e.g. 141763a90 passes edx=7 for the name.)
//   141743f90 — LeagueSetRecStr(entity, idx, val, flush):
//     resolve(idx) → rec-vt+0x80 setter with val, then when
//     flush: provider-vt+0x38(provider, 0).
//   141743e80 — LeagueSetRecInt(entity, idx, val, flush):
//     resolve(idx) → rec-vt+0xb0 setter with the u32 val,
//     then the same flush call.
//   The singleton/log/StrCopy are SEAMS (the same
//   g_fnLeague* family + g_fnMgrStrCopy).
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// ---------- the seams ----------
// tq::StrCopy(dst, src, cap) — a new seam for this unit
extern void (*g_fnMgrStrCopy)(char* pDst, const char* pSrc,
                              int nCap);

// ---- FUN_14174b000 ----
uint8_t LeagueUserIsMember(int64_t lEntity, uint32_t uUser);

// ---- FUN_14175ee00 ----
uint64_t MgrUserLeagueId(int64_t lMgr, uint32_t uUser);

// ---- FUN_1417630d0 ----
void* MgrLeagueFind(int64_t lMgr, uint32_t uLeagueId);

// ---- FUN_1417631d0 ----
void* MgrUserLeagueObj(int64_t lMgr, uint32_t uUser);

// ---- FUN_141763680 ----
uint64_t MgrLeagueGetType(int64_t lMgr, uint32_t uLeagueId);

// ---- FUN_141764870 ----
void* MgrTokenTypeFind(int64_t lMgr, uint32_t uTokenType);

// ---- FUN_1417638e0 ----
uint8_t MgrRemoveMember(int64_t lMgr, uint32_t uLeagueId,
                        uint32_t uUser);

// ---- FUN_1417646f0 ----
uint8_t MgrAddMember(int64_t lMgr, uint32_t uUser,
                     uint32_t uLeagueId, uint32_t uP4,
                     uint32_t uP5, uint16_t uP6, uint32_t uP7,
                     uint8_t uP8, const char* pName);

// ---- FUN_1417647e0 ----
uint32_t MgrGetLeaderId(int64_t lMgr, uint32_t uLeagueId);

// ---- FUN_141764810 ----
void* MgrCreateToken(int64_t lMgr, uint32_t uLeagueId,
                     int64_t lTokenId, uint64_t uP4);

// ---------- the record accessors ----------
// ---- FUN_141743e70 ----
uint32_t LeagueGetLeaderId(int64_t lEntity);
// ---- FUN_141743c80 ----
uint64_t LeagueGetRec2U32(int64_t lEntity);
// ---- FUN_141743d10 ----
uint64_t LeagueGetRec9Str(int64_t lEntity);
// ---- FUN_141743dd0 ----
uint64_t LeagueGetRec1Str(int64_t lEntity);
// ---- FUN_141743d70 ----
uint64_t LeagueGetRecStr(int64_t lEntity, uint32_t uIdx);
// ---- FUN_141743f90 ----
void LeagueSetRecStr(int64_t lEntity, uint32_t uIdx,
                     uint64_t uVal, uint8_t uFlush);
// ---- FUN_141743e80 ----
void LeagueSetRecInt(int64_t lEntity, uint32_t uIdx,
                     uint32_t uVal, uint8_t uFlush);

}  // namespace syndicate

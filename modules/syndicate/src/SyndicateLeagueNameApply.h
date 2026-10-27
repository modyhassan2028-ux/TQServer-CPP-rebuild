// SyndicateLeagueNameApply.h — D63: the league
// name-apply flow FUN_1417b0a40 + its 6 helpers.
//
// ORIGINAL (Syndicate.dll, ImageBase 0x141720000):
//   1417b0a40  LeagueNameApply — the deep body
//              behind the D61 seam g_fn1417b0a40
//              (case 6 of the LeagueOpt dispatcher);
//              122 decompiled lines, disasm-verified
//   141743cb0  LeagueGetRecByIdx(entity, idx) —
//              resolve(idx) -> rec-vt+0x48
//   141743e00  LeagueGetRec4Str(entity) — silent
//              null -> 0; resolve(4) -> vt+0x78
//   141744030  LeagueSetFlagFlush(entity, val,
//              flush) — resolve(8) -> vt+0xd8;
//              flush -> provider vt+0x38(0)
//   1417868c0  RecFlagIs1000(rec) — (*rec)->
//              resolve(2) -> vt+0x48 == 1000
//   14175eb70  ForbidNameFind(host, name) — the
//              checked-iterator walk over the
//              leagues map (head @ host+0x68 =
//              pplMap[6] of the map at host+0x38;
//              the entity value @ node+0x20), each
//              league's rec-1 name strncmp'd with
//              0x10 — the global name-taken check
//   1417215d0  CStrFormat2(cstr, fmt, a, b) — the
//              tq::CString formatter: vsprintf_s
//              into a 0xfff buffer, assign into
//              the std::string at cstr+8
//
// THE D63 DISCOVERY (disasm-verified, the decompiler
// hid it): the decompile showed BOTH
//   uVar6 = FUN_141743cb0(lVar5);
// calls with ONE argument. The raw disasm at
// 1417b0a97/1417b0abe:
//   mov edx, 8   ; call 0x141743cb0
//   mov edx, 2   ; call 0x141743cb0
// — the sub-object INDEX rides edx straight through
// 141743cb0's tail-jump into provider->vt+0x10
// (the resolve slot). cb0 is a 2-ARG function; the
// first call resolves sub 8, the second sub 2.
//
// LITERALS (verbatim):
//   "STR_FORBIDDEN_LEAGUE_NAME"     (rip+0x8671f)
//   "STR_BROADCAST_NEW_LEAGUE_NAME" (rip+0x86690)
//   "f:\\version\\cqserver-78.0.11-1204\\modules"
//   "\\syndicate\\src\\league.cpp"  (141743cb0 log,
//   line 322 (0x142), expr pair ("",""))
//   "f:\\version\\cqserver-78.0.11-1204\\modules"
//   "\\syndicate\\src\\league.cpp"  (141744030 log,
//   line 431, CHECK(m_pRec))
//   "f:\\version\\cqserver-78.0.11-1204\\modules"
//   "\\syndicate\\src\\synattr.cpp" (1417868c0 log,
//   line 1128, IF_OK(m_pRec))
//   the format "\xa1\xef%s(%s)\xa1\xef in %s, %d"
//   = DAT_141824ca8 (GBK \xa1\xef = ★)
//   the tq::CString vftable @ 0x141824cf0
#ifndef SYNDICATE_LEAGUE_NAME_APPLY_H
#define SYNDICATE_LEAGUE_NAME_APPLY_H

#include <cstdint>

namespace syndicate {

// ---- seams: the log + the invalid handler ----
// The InlineLogERROR literal pack (the fixed fmt
// "\xa1\xef%s(%s)\xa1\xef in %s, %d" rides the seam
// doc).
extern void (*g_fnNameApplyLog)(const char* pcExpr1,
    const char* pcExpr2, const char* pcFile,
    uint32_t uLine);
// _invalid_parameter_noinfo (14175eb70's
// checked-iterator guards)
extern void (*g_fnNameApplyInvalid)();

// ---------- FUN_141743cb0 @ 141743cb0 ----------
// (entity, idx) -> resolve(idx) -> rec-vt+0x48.
// Null provider -> the log (line 322) -> 0.
uint64_t LeagueGetRecByIdx(int64_t lEntity,
                           uint32_t uIdx);

// ---------- FUN_141743e00 @ 141743e00 ----------
// (entity) -> resolve(4) -> rec-vt+0x78.
// Null provider -> 0 SILENT (no log).
uint64_t LeagueGetRec4Str(int64_t lEntity);

// ---------- FUN_141744030 @ 141744030 ----------
// (entity, val, flush): resolve(8) -> rec-vt+0xd8
// (rec, val); flush -> provider vt+0x38 (provider,
// 0). Null provider -> the log (line 431) -> return.
void LeagueSetFlagFlush(int64_t lEntity,
                        uint32_t uVal,
                        uint8_t uFlush);

// ---------- FUN_1417868c0 @ 1417868c0 ----------
// (rec): obj = *rec; null -> the log (line 1128) ->
// false; obj resolve(2) -> sub-vt+0x48 == 1000.
bool RecFlagIs1000(void* pRec);

// ---------- FUN_14175eb70 @ 14175eb70 ----------
// (host, name): walk the leagues map from
// leftmost (**(host+0x68)) to head; for each node,
// if the entity value (node+0x20) is non-null,
// strncmp(LeagueGetRec1Str(entity), name, 0x10);
// hit -> the entity; end -> 0.
uint64_t ForbidNameFind(void* pHost, char* pszName);

// ---------- FUN_1417215d0 @ 1417215d0 ----------
// (cstr, fmt, a, b): the tq::CString formatter —
// zero a 0x1000 buffer, vsprintf_s 0xfff with the
// two staged args, assign into the std::string at
// cstr+8. Null fmt -> nothing.
void CStrFormat2(void* pCStr, const char* pcFmt,
                 uint64_t uA, uint64_t uB);

// ---------- FUN_1417b0a40 @ 1417b0a40 ----------
// (logic, actor, synId, name): the name-apply flow.
// Returns byte-true on success (the callers cast
// (char)); the failure returns zero the low byte
// (rax & ~0xff where the decompile says so).
uint64_t LeagueNameApply(void* pLogic, uint32_t uActor,
                         uint32_t uSynId, char* pszName);

// the tq::CString vftable literal (lea r13 at
// 1417b0b7e -> 0x141824cf0)
constexpr uint64_t kCStrVftable = 0x141824cf0ull;

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_NAME_APPLY_H

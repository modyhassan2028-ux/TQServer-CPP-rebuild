// SyndicateLeagueGmName.h — D64: the GM league
// name-change flow FUN_1417b03b0 + the price getter
// FUN_14174e750.
//
// ORIGINAL (Syndicate.dll, ImageBase 0x141720000):
//   1417b03b0  LeagueGmNameChange — the deep body
//              behind the D61 seam g_fn1417b03b0
//              (case 0x33 of the LeagueOpt
//              dispatcher); 116 decompiled lines,
//              disasm-verified
//   14174e750  LeagueNamePriceGet — the trivial
//              dword read *(host + 0x18c)
//
// THE D64 DISCOVERIES (raw disasm, the decompiler
// hid them):
//   1. The single FUN_141743cb0 call carries
//      `mov edx, 2` — resolve(2), NO first sub-8
//      gate (b0a40 had one; b03b0 does not).
//   2. vt+0x140 takes SIX args: (mgr, actor, 0,
//      price, 0x43 dword, byte 1) — the decompile
//      showed only four; [rsp+0x20]=0x43 and
//      [rsp+0x28]=byte 1 are the two stack args.
//   3. MyLogSave stages FIVE args (the decompile
//      dropped the stack ones):
//      MyLogSave("gmlog/emoney_buy",
//        "%u\t%s\t%u\t350\t4237\t%d\t%d\t1\t",
//        actor, name(vt+0x1d8), type(vt+0x200),
//        price, price)
//   4. The vt+0x70 tail gate is INVERTED vs
//      b0a40: called when g_fn14174e3f0 != synId
//      (no rec4-empty check), with the NAME as
//      the 5th stack arg: (mgr, 7, synId, 0,
//      name).
//   5. No LeagueSetFlagFlush and no sub8 read:
//      the success tail is SetRecStr → GetId →
//      vt+0x428 → the inverted e3f0 gate.
//
// LITERALS (verbatim, all extracted from .rdata):
//   "STR_FORBIDDEN_LEAGUE_NAME"     @ 0x141837278
//   "STR_BROADCAST_NEW_LEAGUE_NAME" @ 0x141837238
//   "gmlog/emoney_buy"              @ 0x141830c38
//   "%u\t%s\t%u\t350\t4237\t%d\t%d\t1\t" @ 0x141837258
//   the tq::CString vftable @ 0x141824cf0 (the
//   SAME table b0a40 leases — this fixed the
//   miscomputed 0x14182cef0 of D63)
#ifndef SYNDICATE_LEAGUE_GM_NAME_H
#define SYNDICATE_LEAGUE_GM_NAME_H

#include <cstdint>

namespace syndicate {

// ---- the MyLogSave seam (all five args
// disasm-verified — unlike the Meed TBD) ----
extern void (*g_fnGmNameLogSave)(const char* pcFile,
    const char* pcFmt, uint32_t uActor,
    const char* pcName, uint32_t uType,
    uint32_t uPrice, uint32_t uPrice2);

// ---------- FUN_14174e750 @ 14174e750 ----------
// (host) -> *(uint32*)(host + 0x18c)
uint32_t LeagueNamePriceGet(void* pHost);

// ---------- FUN_1417b03b0 @ 1417b03b0 ----------
// (logic, actor, synId, name) -> byte.
// Gates in the literal order:
//   1. null name -> 0
//   2. MgrLeagueFind(logic+0x50, synId) 0 -> 0
//   3. mgr vt+0x1f8(actor) != LeagueGetRecByIdx
//      (entity, 2) -> 0
//   4. LogRecMapFind(logic+0x18, actor) 0 -> 0
//   5. !RecFlagIs1000(rec) -> 0
//   6. strlen(name) >= 0x10 -> 0
//   7. mgr vt+0x2e8(name) false -> 0
//   8. ForbidNameFind hit -> STR_FORBIDDEN via
//      vt+0x18(actor, str) -> 0
//   9. LeagueNamePriceGet(host) > mgr vt+0x238
//      (actor) -> 0
//   10. mgr vt+0x140(actor, 0, price, 0x43, 1)
//       false -> 0
//   Success: the gmlog line, the broadcast pack,
//   SetRecStr(1, name, 1), GetId -> vt+0x428(id,
//   name), and the INVERTED e3f0 gate -> vt+0x70
//   (7, synId, 0, name). Return 1.
char LeagueGmNameChange(void* pLogic, uint32_t uActor,
                        uint32_t uSynId, char* pszName);

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_GM_NAME_H

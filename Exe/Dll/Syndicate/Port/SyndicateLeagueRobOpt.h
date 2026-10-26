// SyndicateLeagueRobOpt.h — D62: syndicate::
// CMsgLeagueRobOpt::Process (1417d8920).
//
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_1417d8920 @ 1417d8920 — the robopt
//   dispatcher (6 rob types via *(uint*)(+0x440))
//
// DISASSEMBLY-VERIFIED (capstone, the D59
// lesson: trust the asm over the decompiler):
//   - the gate is the SAME 1417ac700 as D61
//     (reused: syndicate::LeagueOptGate)
//   - gate TRUE -> only types 2,3,5,6 pass
//     (cmp 2 jb end; cmp 3 jbe ok; sub 5 cmp 1
//     ja end) — the INVERSE whitelist of D61
//   - gate FALSE -> all types 0..6 dispatch
//   - the id collection loop (cases 0/1/5/6):
//     up to 10 ids, each = *(uint32_t*)
//     (*(void**)(vec + i*8) + 0x48), from the
//     vector at +0x448, count at +0x450
//   - the 5th call arg is a BYTE slot
//     (mov byte [rsp+0x20], bl/1) and the 6th
//     a DWORD ([rsp+0x28]) — the decompiler's
//     "in_stack_ffffffffffffffb8 & 0xffffff00"
//     is just that byte slot zeroed
//   - case 2/3: vt 0x730 with the /1000 via the
//     magic 0x10624dd3, shr 6; %1000 = v - q*1000
#ifndef SYNDICATE_LEAGUE_ROBOPT_H
#define SYNDICATE_LEAGUE_ROBOPT_H

#include <cstdint>

namespace syndicate {

// the body
void RobOptProcess(void* pMsg, uint32_t uIdActor);
// (1417d8920)

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_ROBOPT_H

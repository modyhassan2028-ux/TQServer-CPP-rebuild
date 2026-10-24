#pragma once
// ============================================================
// NpcServer unit 20: real bodies for the small
// self-contained state-machine helpers
//   FUN_140057d30 = the transform-lock check
//   FUN_14005ad00 = the can-act gate
//   FUN_140059f40 = the teleport-approach
//   FUN_140058500 = the 8-dir wander step
// (FUN_14005c960/df70/b030 need the +0x140 attach
//  family FUN_140069xxx - a later unit)
// ============================================================
#include "NpcState.h"

namespace npc {

// ============================================================
// ===== ORIGINAL FUN_140057d30 =====
// ============================================================
// flags = row(0x15);
// return ~(flags >> 0xf) & 1;
// (the SAME bit-15 the state-6 processor gates on)
uint32_t CNpcIsTransformLocked(CNpcStateData& rN);

// ============================================================
// ===== ORIGINAL FUN_14005ad00 =====
// ============================================================
// w1 = sub->vt+0x20(); if (w1 bit5) return 0;
// w2 = sub->vt+0x20(); if (w2 bit3) return 0;
// flags = row(0x15);
// if (flags bit6) { if (!flags bit5) return 0; }
// return 1;
bool CNpcCanAct(CNpcStateData& rN);

// ============================================================
// ===== ORIGINAL FUN_140059f40 (teleport approach) ===
// ============================================================
// if (!map) { log(&DAT_1400be0b0); return 0; }
// steps = sub->vt+8(sub);           // no-arg call
// if (steps < 1) return 0;
// for (i = 1; i <= steps; i++) {
//   cx = sub->vt+0x38();            // x
//   nx = cx + (targetX - cx) * i / steps;
//   cy = sub->vt+0x40();            // y
//   ny = cy + (targetY - cy) * i / steps;
//   if (FUN_14004cc70(map, nx, ny)) {
//     FUN_1400597f0(npc, nx, ny, id);
//     return 1;                      // first visible
//   }                                // step wins
// }
// if (FUN_14004cc70(map, targetX, targetY)) {
//   FUN_1400597f0(npc, targetX, targetY, id);
//   return 1;
// }
// return 0;
// NOTE arg order: FUN_140059f40 feeds the x component
// first into FUN_14004cc70, while FUN_14005d140 feeds
// the y first - preserved per call site.
bool CNpcTeleportApproach(CNpcStateData& rN, int nTX,
                          int nTY, int nId18);

// ============================================================
// ===== ORIGINAL FUN_140058500 (8-dir wander step) ==
// ============================================================
// if (dir >= 8 || !map) {
//   log(&DAT_1400be0b0); return 0; }
// u48 = sub->vt+0x48(sub);         // no-arg call
// y = sub->vt+0x40();
// x = sub->vt+0x38();
// if (!FUN_14004bff0(map, x, y, dir, u48, 0x1a))
//   return 0;
// +0x40 = dir;                     // facing
// +0x2c = 1;                       // walk lock
// return 1;
bool CNpcWanderStep(CNpcStateData& rN, uint32_t uDir);

} // namespace npc

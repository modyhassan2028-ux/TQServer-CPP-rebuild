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
#include <functional>

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

// ============================================================
// ===== ORIGINAL FUN_14005a8f0 (rate gate) ============
// ============================================================
// uVar2 = TimeGet(0);
// iVar1 = *(int*)(p + 4);            // the stamp
// if (uVar2 < (uint)(param_2 + iVar1))
//   return 0;                         // too soon
// if ((uint)(iVar1 + param_2 * 2) <= uVar2) {
//   *(ulong*)(p + 4) = TimeGet(0);    // full reset
//   return 1;
// }
// *(int*)(p + 4) = iVar1 + param_2;   // advance
// return 1;
bool CNpcRateGate(int32_t& rnStamp, int nWindow,
                  std::function<uint32_t()>& fnTimeGet);

// ============================================================
// ===== ORIGINAL FUN_140069750 (attach alive) ========
// ============================================================
// return *(int*)(p + 8) != 0 && *(int*)(p + 0x10) != 0;
// (the npc +0x140 attach object)
bool CNpcAttachAlive(bool bHasAttach);

// ============================================================
// ===== ORIGINAL FUN_14005c960 (AI step executor) =====
// ============================================================
// key = param_2 ? 0x1a : 0x13;
// iVar2 = row->vt+0x10(row, key);       // GetInt
// if (!FUN_14005a8f0(npc+0xb8, iVar2))
//   return 1;                            // rate-held
// if (+0x2c < 1) return 0;               // empty
// iVar10 = (int8)queue[0] % 8;           // signed mod
// len = +0x2c - 1; +0x2c = len;
// if (len) memmove(queue, queue+1, len); // the shift
// if (FUN_14005b9e0(npc, iVar10, param_2)) return 1;
// if (!attach || !FUN_140069750) {       // no attach
//   if (FUN_140058260(npc, iVar10) &&
//       +0x2c != 0) {
// LAB_14005caf0:
//     +0x2c = 0;
//     return FUN_14005b9e0(npc,
//         (int8)queue[0], param_2);
//   }
//   if (row(0x15) bit5) {
//     gen->vt+0x28(gen, &res);
//     id = sub->vt+0x18();
//     return FUN_140059f40(npc,
//         res.lo, res.hi, id);   // teleport home
//   }
//   return 0;
// } else {                               // attach
//   if (!FUN_140058b80(npc, &res))
//     return 0;
//   +0x2c = 0;
//   iVar2 = RandGet(100);
//   uVar3 = iVar2 < 0x46 ? 0
//                        : row->vt+0x10(row, 0x10);
//   bVar1 = FUN_1400580e0(npc, res.lo,
//                         res.hi, uVar3);
//   if (bVar1 &&
//       !FUN_14005b9e0(npc, (int8)queue[0],
//                      param_2) &&
//       FUN_1400588b0(npc, res.lo, res.hi,
//                     iVar10) && +0x2c != 0)
//     goto LAB_14005caf0;
//   return 0;
// }
bool CNpcC960(CNpcStateData& rN, uint32_t uFlavor);

// ============================================================
// ===== ORIGINAL FUN_140058260 (attack dir pick) ====
// ============================================================
// DAT_1400c89d0 x-tab {0,-1,-1,-1,0,1,1,1}
// DAT_1400c89f0 y-tab {1,1,0,-1,-1,-1,0,1}
// (identical to the FUN_140087d50 wander probe)
// if (!map(+0x98)) { log; return 0; }
// +0x2c = 0;
// gen->vt+0x28(gen, &refX, &refY);   // gen spawn
// if (+0x84) { t = find(+0x84);
//   if (t) { refX = t->x; refY = t->y; } }
// ref = sub->vt+8(sub, refX, refY);  // dist to ref
// best = -1; r = RandGet(8); uRet = r + 8;
// for (i = r; i < r + 8; i++) {
//   dir = i % 8;                     // signed mod
//   if (dir == curDir) continue;
//   mapObj = sub->vt+0x80(); if (!mapObj)
//     { uRet = 0; continue; }
//   u48 = sub->vt+0x48();
//   if (!FUN_14004bff0(mapObj, x, y,
//       dir, u48, 0x1a)) { uRet = 0;
//       continue; }
//   cand = (x + XT[dir], y + YT[dir]);
//   d = chebyshev(cand - ref);
//   sgn = +0x3c ? 1 : -1;
//   if (0 < sgn * (ref - d)) {
//     best = dir; ref = d;
//   }
//   uRet = d;          // the VERBATIM low-byte
// }                    // leak into the return
// if (best != -1) { +0x40 = best;
//   +0x2c = 1; return 1; }
// return (uRet & 0xff) != 0;   // original leak
bool CNpcAttackDir(CNpcStateData& rN, int nCurDir);

} // namespace npc

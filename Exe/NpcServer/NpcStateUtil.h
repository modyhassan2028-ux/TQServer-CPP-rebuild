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

// ============================================================
// ===== ORIGINAL FUN_1400588b0 (pursuit dir pick) ===
// ============================================================
// Same 8-dir greedy scan as FUN_140058260 but
// the reference is the caller's res pair,
// OVERRIDDEN by the +0x84 target position.
// NOTE the verbatim quirk: when the target id
// is set but the lookup fails, the original
// assigns the UNINITIALIZED local_resc to
// all three ref vars (kept verbatim via the
// m_nRescGarbage seam field).
// if (!map) { log; return 0; }
// +0x2c = 0;  ref = (p2, p3);
// if (+0x84) { t = find;
//   if (!t) ref = garbage; else ref = t->pos; }
// refDist = sub->vt+8(sub, refX, refY);
// ... identical ring scan to 58260 ...
// if (best != -1) { +0x40; +0x2c = 1; ret 1; }
// return (leak & 0xff) != 0;
bool CNpcAttackDirNear(CNpcStateData& rN,
                       int nResX, int nResY,
                       int nCurDir);

// ============================================================
// ===== ORIGINAL FUN_140058b80 (attach res) ====
// ============================================================
// if (+0x140 == 0) { log; return 0; }
// FUN_1400696d0(+0x140);   // discarded
// holder = FUN_140034e00(
//     FUN_14001c130(FUN_14001c200()));
// if (!holder) { log; return 0; }
// if (FUN_140069910(+0x140)) {
//   if (FUN_140065750(holder) == 0)
//     gen(+0x100)->vt+0x28(&res);
//   else FUN_1400657c0(holder, &res);
// } else FUN_140065510(holder, &res);
// *out = res (both words); return 1;
bool CNpcAttachRes(CNpcStateData& rN,
                   int& rnResLo, int& rnResHi);

// ============================================================
// ===== ORIGINAL FUN_14005b9e0 (step attack) =======
// ============================================================
// if (map(+0x98) == 0) { log; return 0; }
// dirN = dir % 8 (signed mod);
// +0x24 = dirN;
// x' = sub x + XT[dirN]; y' = sub y + YT[dirN];
// if (x' >= 0 && x' < FUN_140049480(map) &&
//     y' >= 0 && y' < FUN_140049430(map)) {
//   u48 = sub->vt+0x48();
//   d   = sub->vt+0x18();   // the sub's OWN
//                            // dir, not dirN!
//   walk = FUN_14004bff0(map, sub x, sub y,
//                        d, u48, 0);  // 0, not
//                                      // 0x1a!
//   if (!walk && (!attach ||
//       !FUN_140049310(map, x', y'))) {
//     FUN_14005b2d0(npc);  // fail path
//     return 0;
//   }
//   FUN_140062030(msg);
//   if (!FUN_1400620c0(msg, id, dir,
//                      flavor)) {
//     log; FUN_140062080(msg); return 0; }
//   FUN_14001c5f0(FUN_14001c200(),
//                 id, msg);      // send
//   FUN_140058610(npc,
//     XT[dirN] + +0x34,           // jump
//     YT[dirN] + +0x38);
//   FUN_140062080(msg);  // dtor
//   return 1;
// }
// log; return 0;
bool CNpcStepAttack(CNpcStateData& rN,
                    int nDir,
                    uint32_t uFlavor);

// ============================================================
// ===== ORIGINAL FUN_140059770 (free gate) =============
// ============================================================
// if (+0x28 != 2) {
//   v = row(0x15)->vt+0x10(0x15);
//   if (bit3 clear && bit4 clear && bit11 clear)
//     return 1;
// }
// return 0;
bool CNpcFreeGate(CNpcStateData& rN);

// ============================================================
// ===== ORIGINAL FUN_14005b2d0 (stuck handler) =========
// ============================================================
// r = FUN_140059770(npc);
// if (r) {
//   if (attach(+0x140)) {
//     b = FUN_140069750(attach);
//     if (b) return 1;   // attach alive: done
//   }
//   r = FUN_14005ad00(npc);
//   if (r && sub->vt+0x50()) {
//     if (+0x18 != 0) {
//       if (x(+0x34) == stuckX(+0x11c)) {
//         stuckCount(+0x124)++;
//         if (10 < stuckCount) {
//           nx = RandGet(8) - 4 + x;
//           ny = RandGet(8) - 4 + y(+0x38);
//           w = FUN_14004cc70(map, nx, ny);
//           if (w) {
//             stuckCount =
//               max(stuckCount - 5, 0);
//             r = FUN_1400597f0(npc,
//                     nx, ny, dir(+0x24));
//           }
//         }
//         return 1;    // ALWAYS true here
//       }
//       stuckX = x;    // +0x11c
//       stuckY = y;    // +0x120 (the
//                      // pointer-arith quirk)
//       r = y;         // the leak below
//     }
//     stuckCount = 0;
//   }
// }
// return (low byte of r);  // the VERBATIM
// // leak: callers see (y & 0xff) on the
// // stuck-update path
uint32_t CNpcStuckHandler(CNpcStateData& rN);

} // namespace npc

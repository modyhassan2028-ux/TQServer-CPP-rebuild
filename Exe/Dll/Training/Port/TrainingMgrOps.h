// ============================================================
// Training.dll port — the mgr CALC helpers + the mgr
// business bodies (the real vt targets). Unit T4/D16.
// Addresses verbatim: 1419e1ae0 / 1419e23d0 /
// 1419e1b70 / 1419e4390 / 1419e44e0 / 1419e4730.
// ============================================================
#pragma once
#include "TrainingMgr.h"
#include <cstdint>

namespace training {

// ---- FUN_1419e1ae0: the exp-percent helper ----
// kernel!=0 && id!=0 && vt+0xe0(9): clamp vt+0x68(id)
// to 0..6, return table[idx]*0x3c/100; else 0x5a
uint32_t CalcExpPct(void* pMgr, uint32_t uId);

// ---- FUN_1419e23d0: the session-time pair ----
// *pnA = the usable time (min 0, capped), *pnB =
// uVar10 - uVar8 (the totals). Verbatim arithmetic
// (the ×10 then (x>>3)-(x>>0x1f) ×0xf chains, the
// 0x7777777777777777 div idioms, the /0xf×0xf path)
void CalcSessionTimes(void* pMgr, uint32_t uId,
                      uint32_t* pnA, int32_t* pnB);

// ---- FUN_1419e1b70: the exp calc ----
// vt+0x08() idx, the guard 0 < count, the double
// formula (the DAT_1419e87xx tables), writes
// *(double*)(mgr+0x10), the level loop; outputs
// *pnLevels, *plExp, *pnRate
void CalcExpValues(void* pMgr, uint32_t uId,
                   int32_t nA, int32_t* pnLevels,
                   int64_t* plExp, int32_t* pnRate);

// ---- FUN_1419e4390 (mgr vt+0x18): on-enter ----
// 0x259-check path: vt+0x30(id) -> vt+0x70(id) gate
// -> CMsgTraining + Make(2,0) + send; else the
// vt+0x98 gate; miss: _time64 + MgrOpIndex + slot[1]
void MgrEnterTraining(void* pMgr, uint32_t uId);

// ---- FUN_1419e44e0 (mgr vt+0x20): on-query ----
// the vt+0x90(mapid) true path: Make(5,0)+send; the
// calc path: the elapsed-div idiom, the vt+0x48
// comparison, Make(0, rate*10)+send
uint64_t MgrQueryTraining(void* pMgr, uint32_t uId);

// ---- FUN_1419e4730 (the claim body): the claim ----
uint8_t MgrClaimTraining(void* pMgr, uint32_t uId);

} // namespace training

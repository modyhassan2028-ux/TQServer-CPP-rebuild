#pragma once
// ============================================================
// NpcServer unit 16: the death/reborn tick + dispatcher
//   FUN_14005b5c0 = the death/reborn tick
//   FUN_140058860 = the continue-processing gate
//   FUN_14005f3b0 = the die-state dispatcher
//     (unit-15 finding: called by
//     CDefaultAIStrategy vtable+0x18 FUN_140067070)
// The state processors FUN_14005e900 (state 1),
// FUN_14005d140 (6), FUN_14005d550 (7),
// FUN_14005d330 (8) remain seams (next unit).
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

struct CNpcDeathData {
    // +0x18 state (0 alive, 1 deleted-walk?, 6/7/8
    // reborn machine) - param_1[3]
    uint32_t m_nState = 0;
    // +0x2c - cleared on reborn
    uint32_t m_dwField2C = 0;
    // +0x1c/+0x20 - reborn offsets (type row 4/5)
    uint32_t m_dwField1C = 0;
    uint32_t m_dwField20 = 0;
    // +0xb0 interval seconds, +0xb4 last-tick stamp
    uint32_t m_nIntervalB0 = 0;
    uint32_t m_nStampB4 = 0;
    // +0x148 flag (param_1[0x29]) - gate
    bool m_bGate148 = false;
    // ===== seams =====
    std::function<uint64_t()> m_fnNow;        // tq::TimeGet
    std::function<uint32_t()> m_fnRowGetFlag; // type row
    // vtable+0x10, key 0x15 -> flags dword
    std::function<uint32_t(uint32_t)> m_fnRowGetInt;  // keys
    // 4 and 5
    std::function<void(int&, int&)> m_fnGetPos; // sub
    // vtable+0x38(x)/+0x40(y)
    std::function<bool()> m_fnCheck50;       // sub+0x50
    std::function<bool()> m_fnHasMap;       // +0x98 != 0
    std::function<bool(int, int)> m_fnMapPosValid;
        // FUN_14004ae30(map, x, y)
    std::function<bool(int, int)> m_fnGenInArea; // gen
    // vtable+0x68 (gen, x, y)
    // FUN_140058860: +0x140 object gates
    std::function<bool()> m_fnHasAttach140; // +0x140 != 0
    std::function<bool()> m_fn6750;         // FUN_140069750
    std::function<bool()> m_fn6991;         // FUN_140069910
    std::function<bool()> m_fn6974;         // FUN_140069740
    // state handlers (seams for next unit)
    std::function<bool()> m_fnState1;       // FUN_14005e900
    std::function<bool()> m_fnState6;       // FUN_14005d140
    std::function<bool()> m_fnState7;       // FUN_14005d550
    std::function<bool()> m_fnState8;       // FUN_14005d330
};

// ============================================================
// ===== ORIGINAL FUN_14005b5c0 =====
// ============================================================
// now = tq::TimeGet(0);
// if (now/1000 < +0xb4 + +0xb0) return 0;
// +0xb4 = now/1000;
// flags = type-row->vtable+0x10(_, 0x15);
// if (flags bit3 || bit4 || bit7) {          // 0x8/0x10/0x80
//   (x,y) = sub vtable+0x40/vtable+0x38;
//   if (!gen->vtable+0x68(gen, x, y)) return 0; // out of
//                                             // area
// }
// if (map +0x98 != 0) {
//   (x,y) = sub vtable+0x40/vtable+0x38;
//   if (FUN_14004ae30(map, x, y)) {
//     +0x1c = row vtable+0x10(_, 4);   // reborn offset
//     +0x20 = row vtable+0x10(_, 5);
//     +0x2c = 0;
//     +0x18 = 0;                       // alive again
//     return 1;
//   }
// }
// return 0;
// NOTE: the decompile's uVar9 masks (0x10624dd3 /
// 0xffffff00) are Ghidra artifacts of the packed
// return register - the real result is the low bool.
bool CNpcRebornTick(CNpcDeathData& rN);

// ============================================================
// ===== ORIGINAL FUN_140058860 =====
// ============================================================
// o = +0x140;
// return o != 0 && FUN_140069750(o) &&
//        !FUN_140069910(o) && !FUN_140069740(o);
bool CNpcContinueGate(CNpcDeathData& rN);

// ============================================================
// ===== ORIGINAL FUN_14005f3b0 =====
// ============================================================
// uVar = FUN_14005b5c0(npc);
// if (uVar == 0 && sub->vtable+0x50() != 0 &&
//     +0x148 == 0) {
//   FUN_140058860(npc);
//   for (i = 0; i < 10; i++) {
//     state = +0x18;
//     if (state == 1) { if (FUN_14005e900) return; }
//     else if (state == 6) { if (FUN_14005d140) return; }
//     else if (state == 7) { if (FUN_14005d550) return; }
//     else if (state == 8) { if (FUN_14005d330) return; }
//   }
// }
// (the loop re-reads +0x18 each pass - a handler may
//  change the state and the next pass dispatches again;
//  unhandled states burn the 10 iterations verbatim)
void CNpcDieDispatch(CNpcDeathData& rN);

} // namespace npc

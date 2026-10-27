#pragma once
// ============================================================
// NpcServer unit 23: FUN_140066820 — the user tick
// (file literal: "f:\version\cqserver-78.0.11-1204\
//  npcserver\npckernel\user.cpp" line 0x57)
// ============================================================
// ORIGINAL flow:
//   uVar13 = (TimeGet(0) * 0x10624dd3) & 0xffffffff;
//     // the verbatim Ghidra artifact returned when
//     // the tick is not due
//   if ((uint)(+0xa0 interval + +0xa4 lastStamp)
//       <= TimeGet(0) / 1000) {        // due
//     +0xa4 = TimeGet(0) / 1000;      // stamp
//     if (+0x18 set != 0) {
//       base = (x/0x12 - 1 < 1) ? 0
//                             : x/0x12 - 1;
//       while (true) {
//         if (x/0x12 + 1 < base) break;
//         if (FUN_140049490(set) <= base)
//           break;
//         row = (y/0x12 - 1 < 1) ? 0
//                               : y/0x12 - 1;
//         for (; row <= y/0x12 + 1 &&
//                row < FUN_140049440(set);
//              row++) {
//           cell = FUN_14004ac70(set,
//                        base, row);
//           cont = FUN_1400678a0(cell);
//           for (i = 0;
//                i < cont->vt+0x10();
//                i++) {
//             item = cont->vt+0x18(cont,
//                i, "...\user.cpp", 0x57,
//                row, i);
//             if (item &&
//                 item->vt+0x50()) {
//               d = sub->vt+8(sub,
//                 item->vt+0x38(),
//                 item->vt+0x40());
//               if ((int)d < 0x13)
//                 return d;   // FOUND
//             }
//           }
//         }
//         base++;
//       }
//     }
//     world = FUN_14001c210()
//       ->vt+0x10();             // singleton
//     id   = this->vt+0x8();
//     uVar13 = world->vt+0x28(world, id);
//   }
//   return uVar13;
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

// the ORIGINAL literal path baked into the
// container-getter calls (user.cpp line 0x57)
inline const char* const k_pszUserTickFile =
    "f:\\version\\cqserver-78.0.11-1204"
    "\\npcserver\\npckernel\\user.cpp";

struct CNpcUserTickData {
    int32_t m_nInterval = 0;
        // +0xa0 (low dword of the qword read
        // via (int)param_1[0x14])
    int32_t m_nLastStampSec = 0;
        // +0xa4 last tick (seconds)
    bool m_bHasSet = false;
        // +0x18 (param_1[3]) != 0
    std::function<uint32_t()> m_fnTimeGet;
        // tq::TimeGet(0) - ms
    // ===== the sub (+0x10) =====
    std::function<int()> m_fnSubGetX38;
        // sub vtable+0x38
    std::function<int()> m_fnSubGetY40;
        // sub vtable+0x40
    std::function<uint32_t(int, int)>
        m_fnSubDist;
        // sub vtable+8(x, y)
    // ===== the +0x18 set =====
    std::function<int()> m_fn490Width;
        // FUN_140049490(set) - the base
        // (x-derived) bound
    std::function<int()> m_fn440Height;
        // FUN_140049440(set) - the row
        // (y-derived) bound
    std::function<uint64_t(int, int)>
        m_fnAc70;
        // FUN_14004ac70(set, base, row)
    std::function<uint64_t(uint64_t)>
        m_fn678a0;
        // FUN_1400678a0(cell) - container
    // ===== the container =====
    std::function<uint32_t(uint64_t)>
        m_fnContCount;
        // container vtable+0x10
    std::function<uint64_t(uint64_t,
        uint32_t, const char*, int, int, int)>
        m_fnContGet;
        // container vtable+0x18(cont, i,
        // file, 0x57, row, i)
    // ===== the item =====
    std::function<bool(uint64_t)>
        m_fnItemAlive;
        // item vtable+0x50
    std::function<int(uint64_t)>
        m_fnItemX38, m_fnItemY40;
        // item vtable+0x38 / +0x40
    // ===== the leave broadcast =====
    std::function<uint32_t()> m_fnThisId;
        // this vtable+0x8
    std::function<uint64_t(uint32_t)>
        m_fnWorldLeave;
        // world (FUN_14001c210 ->
        // vt+0x10) vtable+0x28(world, id)
};

// the tick. Returns the found distance
// (< 0x13), the world-leave result, or
// the verbatim magic artifact when idle.
uint32_t CNpcUserTick(CNpcUserTickData& rD);

} // namespace npc

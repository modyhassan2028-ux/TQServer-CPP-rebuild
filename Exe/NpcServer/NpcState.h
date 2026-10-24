#pragma once
// ============================================================
// NpcServer unit 17: the die-state processors
//   FUN_14005d140 = state 6 (reborn-follow)
//   FUN_14005d330 = state 8 (chase/attack)
// (state 7 FUN_14005d550 and state 1 FUN_14005e900
//  are the next unit; the dispatcher is unit 16)
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

// seam view of the target object (FUN_140038010
// lookup by +0x84): the accessors the state code
// calls verbatim
struct CNpcTargetSeam {
    bool m_bValid50 = true;   // vtable+0x50
    int m_nX = 0;             // vtable+0x38
    int m_nY = 0;             // vtable+0x40
    int m_nMapId = 0;         // vtable+0x30
    int m_nField48 = 0;       // vtable+0x48 (sight)
};

struct CNpcStateData {
    // ===== CNpc fields =====
    uint32_t m_nState = 0;      // +0x18 (param_1[3])
    uint32_t m_dwField2C = 0;   // +0x2c
    int m_nTargetId = 0;        // +0x84
    bool m_bHasMap = false;     // +0x98 != 0
    void* m_pAttach140 = nullptr;  // +0x140
    uint32_t m_dwFieldA8 = 0;   // +0xa8 (FUN_140002700)
    uint32_t m_nField3C = 1;    // +0x3c (attack gate)
    uint32_t m_nField3E = 0;    // +0x3e
    // ===== seams =====
    std::function<uint32_t()> m_fnRowGetFlag;   // key 0x15
    std::function<uint32_t(uint32_t)> m_fnRowGetInt;
        // key 0x10 (wander) etc.
    std::function<CNpcTargetSeam*(int)> m_fnFindTarget;
        // FUN_14001c210 + FUN_140038010(_, +0x84)
    std::function<void()> m_fnLogError;
        // log_InlineLogERROR(&DAT_1400be0b0)
    std::function<bool(int, int)> m_fnInSight;
        // FUN_14004cc70(map +0x98, y, x)
    std::function<int()> m_fnSubId18;   // sub vtable+0x18
    std::function<int(int, int)> m_fnSubDist;
        // sub vtable+8 (x, y) -> distance
    std::function<int(int)> m_fnSubDist48;
        // sub vtable+0x10 (target +0x48 value)
    std::function<int()> m_fnSubMapId;  // sub vtable+0x30
    std::function<void(int, int, int)> m_fnMoveTo;
        // FUN_1400597f0(npc, x, y, id18)
    std::function<bool()> m_fnB030;    // FUN_14005b030
    std::function<void(uint32_t)> m_fnWanderStart;
        // FUN_14005b760(npc, row(0x10) * 2)
    std::function<void(uint32_t)> m_fnC960;
        // FUN_14005c960(npc, flag)
    std::function<bool()> m_fnBC80;    // FUN_14005bc80
    std::function<bool()> m_fnAD00;    // FUN_14005ad00
    std::function<bool()> m_fn2700;    // FUN_140002700(+0xa8)
    std::function<void*()> m_fnGetRole;   // sub vtable+0xe8
    std::function<bool(void*)> m_fnAd20;
        // FUN_14004ad20(map +0x98, role)
    std::function<void(int)> m_fnAttack;
        // FUN_140058260(npc, -1) with the +0x3c
        // 0/1 gate around it
    std::function<bool()> m_fn750;
        // FUN_140069750(+0x140)
};

// ============================================================
// ===== ORIGINAL FUN_14005d140 (state 6) =====
// ============================================================
// flags = row(0x15);
// if (!(flags & 0x8000)) {                 // bit 15
//   log_InlineLogERROR(&DAT_1400be0b0);
//   +0x2c = 0; +0x18 = 1; return 1;
// }
// target = FUN_140038010(world, +0x84);
// flags = row(0x15);
// if (!(flags & 8) && !(flags & 0x10)) goto LAB_291;
// if (target) {
//   if (FUN_14004cc70(map, tgtY, tgtX)) {  // visible
//     id = sub vtable+0x18;
//     FUN_1400597f0(npc, tgtX, tgtY, id);  // move to it
//     +0x18 = 7; return 1;
//   }
// }
// LAB_14005d291:
// if (!FUN_14005b030(npc)) {
//   if (+0x2c == 0) FUN_14005b760(npc, row(0x10)*2);
//   if (+0x84 == 0) { +0x2c = 0; +0x18 = 1; return 1; }
//   if (+0x2c == 0) { +0x18 = 7; return 1; }
//   FUN_14005c960(npc, 1);
// }
// return 1;
bool CNpcState6(CNpcStateData& rN);

// ============================================================
// ===== ORIGINAL FUN_14005d330 (state 8) =====
// ============================================================
// target = FUN_140038010(world, +0x84);
// if (target == 0) goto LAB_475;
// if (!target->vtable+0x50()) goto LAB_475;
// if (target->mapId(+0x30) != sub->mapId(+0x30))
//     goto LAB_475;
// d1 = sub->vtable+8(sub, tgtY, tgtX);   // dist to it
// d2 = sub->vtable+0x10(sub, target->+0x48);
// if (d2 < d1) goto LAB_475;             // too far
// if (!FUN_140002700(&+0xa8)) goto LAB_535;
// if (map +0x98 != 0) {
//   role = sub->vtable+0xe8();
//   if (FUN_14004ad20(map, role)) {
//     +0x3c = 0; FUN_140058260(npc, -1); +0x3c = 1;
//     if (+0x2c != 0) FUN_14005c960(npc, 2);
//   }
// }
// if (+0x3e != 0) { +0x3e = 0; goto LAB_535; }
// LAB_14005d467: +0x18 = 7; goto LAB_535;
// LAB_14005d475:
//   if (+0x140 != 0) {
//     if (!FUN_140069750(+0x140)) goto LAB_48f;
//   } else {
// LAB_14005d48f:
//     if (FUN_14005bc80(npc)) {          // aggro tick
//       target2 = FUN_140038010(world, +0x84);
//       if (!target2 || !target2->vtable+0x50())
//           goto LAB_535;
//       d1 = sub->vtable+8(sub, tgtY, tgtX);
//       d2 = sub->vtable+0x10(sub, t2->+0x48);
//       if (d1 <= d2) goto LAB_535;
//       if (+0x2c != 0 && FUN_14005ad00(npc))
//           goto LAB_467;                // keep chase
//     }
//   }
//   +0x2c = 0; +0x18 = 1;                // lost it
// LAB_14005d535: return 1;
bool CNpcState8(CNpcStateData& rN);

} // namespace npc

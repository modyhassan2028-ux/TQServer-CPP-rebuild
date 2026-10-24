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
    std::function<bool(uint32_t)> m_fnC960;
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
    // ===== state-7 seams =====
    std::function<bool()> m_fnCB60;    // FUN_14005cb60
    std::function<void(int&, int&)> m_fnGenGetSpawn;
        // gen(+0x100) vtable+0x28(gen, &res8, &resc)
    std::function<bool(int, int, int)> m_fnGenInArea;
        // gen vtable+0x70(gen, mapid, x, y, 0x30)
    std::function<bool(int, int)> m_fn49310;
        // FUN_140049310(map +0x98, x, y)
    std::function<void(int, int, int)> m_fn59f40;
        // FUN_140059f40(npc, x, y, id18)
    std::function<void(int, int, int)> m_fn5a0d0;
        // FUN_14005a0d0(npc, res8, resc, id18)
    std::function<bool()> m_fn59c90;    // FUN_140059c90
    std::function<bool()> m_fnSub60;    // sub vtable+0x60
    std::function<void(int&, int&)> m_fnSubGetPos;
        // sub vtable+0x38 (x) / +0x40 (y)
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
// ===== ORIGINAL FUN_14005d550 (state 7) =====
// ============================================================
// target = FUN_140038010(world, +0x84);
// if (!target || !target->vt+0x50()) {
// LAB_14005d668:                    // no valid target
//   if (FUN_14005cb60(npc)) return 1;
//   gen->vt+0x28(gen, &res8);      // spawn point
//   flags = row(0x15);
//   if (!bit3 && !bit4 && !bit7) goto LAB_789;
//   // sight bits: the InArea dance
//   if (!gen->vt+0x70(gen, subMap, subX, subY, 0x30)) {
//     if (target && gen->vt+0x70(gen, tMap, tX, tY,
//                                 0x30)) goto LAB_969;
//     goto LAB_14005d789;           // no-sight block
//   }
// LAB_14005d969:
//   +0x84 = 0;                      // drop target
//   FUN_14005a0d0(npc, res8, resc, id18);
//   +0x18 = 1; +0x2c = 0; return 1;
// LAB_14005d789:                    // no-sight block
//   if ((bit3 || bit4 || bit0xb) && target) {
//     d = sub->vt+8(sub, tX, tY);
//     if (d > 5 && map && FUN_140049310(map,tX,tY)) {
//       FUN_1400597f0(npc, tX, tY, id18); return 1;
//     }
//   }
//   if (+0x2c != 0) {
//     FUN_14005c960(npc, +0x84 ? 1 : 0); return 1;
//   }
//   if (FUN_14005bc80(npc)) {
//     if (+0x2c != 0) return 1;
//     if (row(0x15) bit 5) {
//       target2 = find(+0x84);
//       if (!target2) log(&DAT_1400be0b0);
//       else FUN_140059f40(npc, tX, tY, id18);
//       return 1;
//     }
//   }
//   +0x18 = 1; +0x2c = 0; return 1;
// }
// // ===== valid target =====
// if (tMap != subMap) goto LAB_14005d668;
// d1 = sub->vt+8(sub, tX, tY);
// d2 = sub->vt+0x10(sub, t->+0x48);
// if (d2 < d1) goto LAB_14005d668;
// if (!bit3 && !FUN_14005ad00(npc) && sub->vt+0x60()
//     && (+0x3c == 0 && +0x2c > 0)
//     && FUN_14005c960(npc, 1)) return 1;
// FUN_140059c90(npc);
// +0x18 = 8; +0x2c = 0;
// return 1;
bool CNpcState7(CNpcStateData& rN);

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

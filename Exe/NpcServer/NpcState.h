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
    // ===== state-1 seams =====
    uint32_t m_nField44 = 0;      // +0x44 (param_1[0x11])
    uint32_t m_nField3D = 0;      // +0x3d byte
    std::function<int()> m_fnNpcVt8;
        // npc vtable+8 (identity/idx getter)
    std::function<bool(uint32_t, int, int)> m_fnCreatureInit;
        // FUN_140062460(obj, id18, y, x, 0x59, 0)
        // after the FUN_1400623e0 ctor - true ok
    std::function<void(int)> m_fnCreatureSend;
        // FUN_14001c200 + FUN_14001c5f0(mgr, id, obj)
    std::function<void()> m_fnCreatureDestroy;
        // FUN_140062430 dtor
    std::function<void()> m_fnCreatureCtor;
        // FUN_1400623e0
    std::function<bool()> m_fnDF70;    // FUN_14005df70
    std::function<bool(int, int)> m_fnGenArea68;
        // gen vtable+0x68(gen, x, y)
    std::function<uint32_t(int)> m_fnSubGetWord20;
        // sub vtable+0x20(sub, buf) - two calls,
        // bit 5 of the first / bit 3 of the second
    std::function<void()> m_fnRowVt8;  // row vtable+8
    std::function<void()> m_fnLogWarn;
        // literal: "npc: [%d][%d], target id: [%d]"
    std::function<uint32_t(uint32_t)> m_fnRandGet;
        // tq::RandGet(max)
    std::function<bool()> m_fn57d30;   // FUN_140057d30
    std::function<bool(int, int, int)> m_fn580e0;
        // FUN_1400580e0(npc, x, y, 0)
    std::function<bool(uint32_t)> m_fn58500;
        // FUN_140058500(npc, dir) - 8-dir wander
    std::function<int()> m_fnGenVt60;   // gen vtable+0x60
    std::function<int()> m_fnGenVt50;   // gen vtable+0x50
    std::function<int()> m_fnGenVt38;   // gen vtable+0x38
    std::function<int()> m_fnGenVt58;   // gen vtable+0x58
    // gen vtable+0x28 -> (x, y) pair reuses
    // m_fnGenGetSpawn above
    // ===== util (unit 20) seams =====
    uint32_t m_nField40 = 0;      // +0x40 facing dir
    std::function<int()> m_fnSubVt8;
        // sub vtable+8, no-arg (step count)
    std::function<uint32_t()> m_fnSubVt48NoArgs;
        // sub vtable+0x48, no-arg
    std::function<int()> m_fnSubGetX38;
        // sub vtable+0x38 (x)
    std::function<int()> m_fnSubGetY40;
        // sub vtable+0x40 (y)
    std::function<bool(int, int, int, uint32_t)>
        m_fnMapWalkable;
        // FUN_14004bff0(map, x, y, dir, u48, 0x1a)
    // ===== c960 (unit 21) members =====
    uint8_t m_dirQueue[16] = {0};
        // +0x40 the 8-dir walk queue
        // (+0x2c = its length, m_dwField2C)
    int32_t m_nA8f0Stamp = 0;
        // +0xbc (npc + 0xb8 + 4) rate stamp
    std::function<uint32_t()> m_fnTimeGet;
        // tq::TimeGet(0)
    bool m_bHasAttach = false;
        // npc +0x140 (param_1[0x28]) != 0
        // AND FUN_140069750(+8!=0 && +0x10!=0)
    std::function<bool(int&, int&)> m_fn58b80;
        // FUN_140058b80(npc, &res) - fills BOTH
        // res18 (lo) and res1c (hi)
    std::function<bool(int, int, int)> m_fn588b0;
        // FUN_1400588b0(npc, resLo, resHi, dir)
    std::function<bool(int, uint32_t)> m_fnB9e0;
        // FUN_14005b9e0(npc, dir, flavor)
    std::function<bool(int)> m_fnAttack260;
        // FUN_140058260(npc, dir) - attack
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
// ===== ORIGINAL FUN_14005e900 (state 1) =====
// ============================================================
// flags = row(0x15);
// if (flags bit 8) {              // the summoner bit
//   FUN_1400623e0(obj);           // creature ctor
//   if (!FUN_140062460(obj, id18,
//          y(+0x40), x(+0x38), 0x59, 0))
//     log(&DAT_1400be0b0);
//   else FUN_14001c200+
//        FUN_14001c5f0(mgr, id, obj);
//   FUN_140062430(obj);           // dtor
// }
// if (FUN_14005df70(npc)) return 1;
// flags = row(0x15);
// if (!bit3 && !bit4 && !bit0xb) {
//   if (+0x2c > 0) { FUN_14005c960(npc,0);
//                    return 1; }
//   if (bit7 && !gen->vt+0x68(gen,x,y))
//       goto LAB_14005eb1c;
//   if (!FUN_140002700(&+0xa8)) return 1;
// }
// LAB_14005eb1c:
//   +0x44 = 0; +0x3d = 0;
//   w1 = sub->vt+0x20(); w2 = sub->vt+0x20();
//   if (!(w1 bit5) && !(w2 bit3) &&
//       FUN_14005bc80(npc)) {
//     target = find(+0x84);
//     if (!target) {
//       log(&DAT_1400be0b0); row->vt+8();
//       npc->vt+8(npc);
//       logWARN("npc: [%d][%d], target id: [%d]");
//     } else {
//       d1 = sub->vt+8(sub,tX,tY);
//       d2 = sub->vt+0x10(sub,t->+0x48);
//       if (d1 <= d2) { FUN_140059c90(npc);
//         +0x2c = 0; state = 8; return 1; }
//       if (FUN_14005ad00(npc)) {
//         if (+0x2c) { state = 7; return 1; }
//         if (FUN_140057d30(npc) &&
//             0x4f < tq::RandGet(100)) {
//           +0x2c = 0; state = 6; return 1;
//         }
//         return 1;
//       }
//     }
//   }
//   // ===== movement section =====
//   flags = row(0x15);
//   if (bit3 || bit4 || bit0xb) {
//     if (+0x2c > 0) { FUN_14005c960(npc,0);
//                      return 1; }
//     if (!FUN_140002700(&+0xa8)) return 1;
//   }
//   if (!FUN_14005ad00(npc)) return 1;
//   if (gen->vt+0x68(gen,x,y)) {     // IN gen area
//     flags = row(0x15);
//     if (!bit3 && !bit4 && !bit0xb) {
//       if (tq::RandGet(5) == 0 &&
//           FUN_140058500(npc, tq::RandGet(8)))
//         FUN_14005c960(npc,0);
//     } else {
//       if ((tq::RandGet(5)==0 &&
//            1 < gen->vt+0x60()) ||
//           1 < gen->vt+0x38()) {
//         nx = gen->vt+0x50() +
//              tq::RandGet(gen->vt+0x60());
//         ny = gen->vt+0x58() +
//              tq::RandGet(gen->vt+0x38());
//         if (FUN_1400580e0(npc,nx,ny,0))
//           FUN_14005c960(npc,0);
//       }
//     }
//   } else {                        // OUT of area
//     flags = row(0x15);
//     if (!bit3 && !bit4 && !bit7 &&
//         tq::RandGet(5) != 0) return 1;
//     gen->vt+0x28(gen,&res);       // spawn res
//     if (FUN_1400580e0(npc,resLo,resHi,0))
//       FUN_14005c960(npc,0);
//     else {
//       flags = row(0x15);
//       if (bit3 || bit4 || bit5)
//         FUN_140059f40(npc,resLo,resHi,id18);
//       // else: return
//     }
//   }
// return 1;
bool CNpcState1(CNpcStateData& rN);

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

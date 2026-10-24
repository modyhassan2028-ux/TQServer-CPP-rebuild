#pragma once
// ============================================================
// NpcServer unit 30: the cell check family
//  FUN_14004b140 - cell blockers (grid value)
//  FUN_14004cc70 - cell free to stand
//  FUN_14004bff0 - the WALK CHECK
// Dir tables DAT_1400c7428 / DAT_1400c7448
// extracted from the binary (file 0xc5a28 /
// 0xc5a48) - identical to DAT_1400c89d0/89f0:
//   XT = { 0,-1,-1,-1, 0, 1, 1, 1 }
//   YT = { 1, 1, 0,-1,-1,-1, 0, 1 }
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

struct CNpcCellCheckData {
    // ===== mapdata (*(map + 0x10)) =====
    std::function<int()> m_fnMdWidth28;
        // mapdata vt+0x28 (width)
    std::function<int()> m_fnMdHeight20;
        // mapdata vt+0x20 (height)
    std::function<uint32_t(int, int)>
        m_fnCellType18;
        // mapdata vt+0x18(x, y) - nonzero
        // means the cell TYPE blocks walking
    std::function<int(int, int)> m_fnCellAlt8;
        // mapdata vt+8(x, y) - the height /
        // altitude used by the mode diff check
    // ===== the cell grid =====
    std::function<uint32_t(int, int)>
        m_fnCellGrid;
        // FUN_140049580(map+0x58, x) ->
        // FUN_14003e890(row, y) -> *uint
        // (the blocker count of a cell)
    std::function<bool(int, int)> m_fn49310;
        // FUN_140049310(map, x, y) - the
        // can-stand gate (real body: unit 12)
    std::function<bool(int, int)> m_fn4ab40;
        // FUN_14004ab40(map, x, y) - the
        // ring-cell passable gate (type 1-2)
};

// FUN_14004b140: if (x >= 0 && y >= 0 &&
//   x < width && y < height)
//   return the cell grid value; else 0
uint32_t CNpcCellBlockers(
    CNpcCellCheckData& rD, int nX, int nY);

// FUN_14004cc70: if (FUN_140049310 && the
//   blockers == 0) return 1;
// return (the blockers value with the low
//   byte cleared) - FALSE via the low byte
uint32_t CNpcCellFree(
    CNpcCellCheckData& rD, int nX, int nY);

// FUN_14004bff0(map, x, y, dir, type, mode):
//   type clamped to 4; target = x+XT, y+YT;
//   bounds + cell-type gate;
//   if (type < 3 && type < blockers(target))
//     false;
//   if (mode && mode < alt(target)-alt(x,y))
//     false;
//   u4 = (type & 1);   // the ORIGINAL's
//     // (t&1 ^ t>>31) - (t>>31) idiom
//   type 0 -> true;
//   types 1-2 -> the 3-cell ring
//     (dir-1, dir, dir+1 around the target)
//     with the 4ab40 gate and
//     u4 < blockers -> false;
//   types 3-4 -> the (type+1)/2 square around
//     the target where ONLY cells at cheb >
//     half FROM THE ORIGIN are checked
//     (the big-monster far side) with
//     u4 < blockers -> false
bool CNpcWalkCheck(CNpcCellCheckData& rD,
    int nX, int nY, int nDir,
    uint32_t uType, int nMode);

// ============================================================
// ===== THE MAP GATES (unit 32) ============================
// ===== ORIGINAL FUN_140049310 / FUN_14004ab40 ==============
// ============================================================
// Both gates operate on the map's +0x10 sub-object
// (the same mapdata receiver the cell-check family
// uses: vtable+0x28 = width, vtable+0x20 = height,
// vtable+0x18(x, y) = the cell value, 0 = free).
struct CNpcMapGateData {
    std::function<int()> m_fnWidth28;
        // mapdata vtable+0x28 (width)
    std::function<int()> m_fnHeight20;
        // mapdata vtable+0x20 (height)
    std::function<int(int, int)> m_fnCell18;
        // mapdata vtable+0x18(x, y) -
        // nonzero means the cell is TAKEN
};

// FUN_140049310(map, x, y) - the position gate:
//   if (-1 < x): w = vt+0x28(); if (x < w):
//   if (-1 < y): h = vt+0x20(); if (y < h):
//       return vt+0x18(x, y) == 0;
//   return false;
// (the ORIGINAL body the whole engine calls - the
//  NpcTransform::PosValid port now DELEGATES here)
bool CNpcPosValid49310(CNpcMapGateData& rD,
    int nX, int nY);

// FUN_14004ab40(map, x, y) - the in-bounds gate
// (the type 1-2 ring-cell gate in 4bff0):
//   if (-1 < x): w = vt+0x28(); if (x < w):
//   if (-1 < y): h = vt+0x20(); if (y < h):
//       return CONCAT71(h >> 8, 1);   // literal 1
//   return in_RAX & 0xffffffffffffff00;
// VERBATIM: NO cell check at all - pure bounds.
// VERBATIM: in_RAX carries the LAST width/height
// call result into the masked FALSE return; on
// the x < 0 path in_RAX is UNINITIALIZED (modeled
// as 0, the 59dc0 convention).
uint32_t CNpcInBounds4ab40(CNpcMapGateData& rD,
    int nX, int nY);

} // namespace npc

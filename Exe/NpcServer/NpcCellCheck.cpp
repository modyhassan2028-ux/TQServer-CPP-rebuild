#include "NpcCellCheck.h"

namespace npc {

// ORIGINAL: DAT_1400c7428 / DAT_1400c7448
// (identical to DAT_1400c89d0 / 89f0)
static const int s_nCellXt[8] =
    { 0,-1,-1,-1, 0, 1, 1, 1 };
static const int s_nCellYt[8] =
    { 1, 1, 0,-1,-1,-1, 0, 1 };

uint32_t CNpcCellBlockers(
    CNpcCellCheckData& rD, int nX, int nY) {
    // ORIGINAL FUN_14004b140
    if (nX < 0 || nY < 0) return 0;
    if (nX >= rD.m_fnMdWidth28()) return 0;
    if (nY >= rD.m_fnMdHeight20()) return 0;
    // ORIGINAL: FUN_140049580(map+0x58, x)
    // -> FUN_14003e890(row, y) -> *uint
    return rD.m_fnCellGrid(nX, nY);
}

uint32_t CNpcCellFree(
    CNpcCellCheckData& rD, int nX, int nY) {
    // ORIGINAL FUN_14004cc70
    uint32_t uRet = 0;
    // ORIGINAL: FUN_140049310 gate
    if (rD.m_fn49310(nX, nY)) {
        uRet = CNpcCellBlockers(rD, nX, nY);
        if (uRet == 0) return 1;
    }
    // ORIGINAL: return uVar2 & 0xffffff00
    // - the low byte cleared -> FALSE
    return uRet & 0xffffff00u;
}

bool CNpcWalkCheck(CNpcCellCheckData& rD,
    int nX, int nY, int nDir,
    uint32_t uType, int nMode) {
    // ORIGINAL FUN_14004bff0
    if (4 < (int)uType) uType = 4;   // clamp
    // ORIGINAL: the target cell
    int nTX = nX + s_nCellXt[nDir];
    int nTY = nY + s_nCellYt[nDir];
    // ORIGINAL: bounds + the cell TYPE gate
    if (nTX < 0 || nTY < 0 ||
        nTX >= rD.m_fnMdWidth28() ||
        nTY >= rD.m_fnMdHeight20())
        return false;
    // ORIGINAL: mapdata vt+0x18(nx, ny)
    // != 0 -> blocked
    if (rD.m_fnCellType18(nTX, nTY) != 0)
        return false;
    // ORIGINAL: if (type < 3) {
    //   b = FUN_14004b140(target);
    //   if (type < b) false; }
    if ((int)uType < 3) {
        int nB = (int)CNpcCellBlockers(
            rD, nTX, nTY);
        if ((int)uType < nB) return false;
    }
    // ORIGINAL: the mode altitude-diff check
    if (nMode != 0) {
        int nA1 = rD.m_fnCellAlt8(nTX, nTY);
        int nA0 = rD.m_fnCellAlt8(nX, nY);
        if (nMode < nA1 - nA0) return false;
    }
    // ORIGINAL: uVar4 = (t&1 ^ t>>31) -
    // (t>>31) - for the clamped 0..4 range
    // this is (type & 1)
    uint32_t u4 =
        ((uType & 1) ^ (uType >> 0x1f)) -
        (uType >> 0x1f);
    if ((int)uType < 1) {
        // type 0: no ring checks
        if ((int)uType < 3) return true;
    } else if ((int)uType < 3) {
        // types 1-2: the 3-cell ring around
        // the target: dirs dir-1, dir, dir+1
        // (iVar12 = dir + 7, 3 iterations)
        int nD = nDir + 7;
        for (int i = -1; i < 2; i++) {
            // ORIGINAL: the signed-mod idiom
            int nAdj = nD >> 0x1f & 7;
            int nDD =
                ((nD + nAdj) & 7) - nAdj;
            int nCX = nTX + s_nCellXt[nDD];
            int nCY = nTY + s_nCellYt[nDD];
            // ORIGINAL: FUN_14004ab40 gate
            if (rD.m_fn4ab40(nCX, nCY)) {
                int nB = (int)
                    CNpcCellBlockers(
                        rD, nCX, nCY);
                if ((int)u4 < nB) return false;
            }
            nD++;
        }
        return true;   // LAB_14004c17d
    }
    // types 3-4: the square check
    // ORIGINAL: half = (type + 1) / 2
    int nHalf = (int)(uType + 1) / 2;
    for (int nX2 = nTX - nHalf;
         nX2 <= nTX + nHalf; nX2++) {
        for (int nY2 = nTY - nHalf;
             nY2 <= nTY + nHalf; nY2++) {
            // ORIGINAL: chebyshev FROM THE
            // ORIGIN (x, y); ONLY cells at
            // cheb > half are checked (the
            // far side of a big monster)
            int nDX = nX2 - nX;
            int nADX = nDX < 0 ? -nDX : nDX;
            int nDY = nY2 - nY;
            int nADY = nDY < 0 ? -nDY : nDY;
            int nCheb = nADY < nADX
                ? nADX : nADY;
            // ORIGINAL: the check RUNS
            // when half < cheb (the far-side
            // cells only - verbatim
            // (half < cheb) && x2 >= 0 &&
            // y2 >= 0 && x2 < width &&
            // y2 < height)
            if (nHalf >= nCheb) continue;
            if (nX2 < 0 || nY2 < 0 ||
                nX2 >= rD.m_fnMdWidth28() ||
                nY2 >= rD.m_fnMdHeight20())
                continue;
            int nB = (int)CNpcCellBlockers(
                rD, nX2, nY2);
            if ((int)u4 < nB) return false;
        }
    }
    return true;   // LAB_14004c17d
}


// ============================================================
// ===== THE MAP GATES (unit 32) ============================
// ===== ORIGINAL FUN_140049310 @ 140049310 ================
// ============================================================
// bool FUN_140049310(longlong param_1, int x, int y)
//   [param_1 = the map object; receiver of the three
//    vtable calls = *(param_1 + 0x10) mapdata]
//   if (-1 < x) {
//     iVar1 = vcall+0x28();          // width
//     if ((x < iVar1) && (-1 < y)) {
//       iVar1 = vcall+0x20();        // height
//       if (y < iVar1) {
//         iVar1 = vcall+0x18(sub, x, y);  // cell
//         return iVar1 == 0;
//       }
//     }
//   }
//   return false;
// ============================================================
bool CNpcPosValid49310(CNpcMapGateData& rD,
    int nX, int nY) {
    if (-1 < nX) {
        int nW = rD.m_fnWidth28();
            // ORIGINAL: vcall+0x28()
        if ((nX < nW) && (-1 < nY)) {
            int nH = rD.m_fnHeight20();
                // ORIGINAL: vcall+0x20()
            if (nY < nH) {
                int nCell = rD.m_fnCell18(nX, nY);
                    // ORIGINAL: vcall+0x18(x, y)
                return nCell == 0;
            }
        }
    }
    return false;
}

// ============================================================
// ===== ORIGINAL FUN_14004ab40 @ 14004ab40 ================
// ============================================================
// undefined8 FUN_14004ab40(longlong param_1, int x, int y)
//   if (-1 < x) {
//     in_RAX = vcall+0x28();         // width
//     if ((x < (int)in_RAX) && (-1 < y)) {
//       in_RAX = vcall+0x20();       // height
//       if (y < (int)in_RAX) {
//         return CONCAT71(in_RAX >> 8, 1);  // TRUE
//       }
//     }
//   }
//   return in_RAX & 0xffffffffffffff00;  // FALSE
// VERBATIM QUIRKS:
//  - NO vt+0x18 cell probe AT ALL (pure bounds -
//    unlike 49310 this gate says NOTHING about the
//    cell being taken)
//  - the FALSE path returns the register in_RAX
//    (the LAST width/height result, or garbage
//    when x < 0 made no call) with the low byte
//    CLEARED = the standard masked-false idiom
// ============================================================
uint32_t CNpcInBounds4ab40(CNpcMapGateData& rD,
    int nX, int nY) {
    uint32_t uRax = 0;
        // ORIGINAL: in_RAX - uninitialized on
        // the x < 0 path (the 59dc0 convention:
        // modeled as 0)
    if (-1 < nX) {
        uRax = (uint32_t)rD.m_fnWidth28();
            // ORIGINAL: vcall+0x28()
        if ((nX < (int)uRax) && (-1 < nY)) {
            uRax = (uint32_t)rD.m_fnHeight20();
                // ORIGINAL: vcall+0x20()
            if (nY < (int)uRax) {
                // ORIGINAL: CONCAT71(in_RAX>>8, 1)
                return 1;
            }
        }
    }
    // ORIGINAL: in_RAX & 0xffffffffffffff00
    return uRax & 0xffffff00u;
}

} // namespace npc

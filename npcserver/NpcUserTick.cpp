#include "NpcUserTick.h"

namespace npc {

uint32_t CNpcUserTick(CNpcUserTickData& rD) {
    // ORIGINAL: uVar13 = (TimeGet(0) *
    // 0x10624dd3) & 0xffffffff - the idle
    // return, verbatim Ghidra artifact
    uint64_t uRet =
        ((uint64_t)rD.m_fnTimeGet() *
         0x10624dd3ull) & 0xffffffffull;
    // ORIGINAL: (uint)(+0xa0 + +0xa4)
    // <= TimeGet(0)/1000
    uint32_t uNow = rD.m_fnTimeGet();
    if ((uint32_t)(rD.m_nInterval +
                   rD.m_nLastStampSec)
        <= uNow / 1000u) {
        // ORIGINAL: +0xa4 = TimeGet(0)/1000
        uNow = rD.m_fnTimeGet();
        rD.m_nLastStampSec =
            (int32_t)(uNow / 1000u);
        if (rD.m_bHasSet) {   // +0x18 != 0
            // ORIGINAL: base = (x/0x12 - 1
            // < 1) ? 0 : x/0x12 - 1
            int nX = rD.m_fnSubGetX38();
            int nBase = (nX / 0x12 - 1 < 1)
                ? 0 : nX / 0x12 - 1;
            while (true) {
                // ORIGINAL: re-reads x every
                // iteration
                nX = rD.m_fnSubGetX38();
                if (nX / 0x12 + 1 < nBase)
                    break;
                // ORIGINAL:
                // FUN_140049490(set) <= base
                if (rD.m_fn490Width()
                    <= nBase)
                    break;
                int nY = rD.m_fnSubGetY40();
                // ORIGINAL: row = (y/0x12-1
                // < 1) ? 0 : y/0x12 - 1
                int nRow = (nY / 0x12 - 1 < 1)
                    ? 0 : nY / 0x12 - 1;
                // ORIGINAL: for (; row <=
                // y/0x12+1 && row <
                // FUN_140049440(set); )
                for (; nRow <= nY / 0x12 + 1
                            && nRow <
                       rD.m_fn440Height();
                     nRow++) {
                    // FUN_14004ac70(set,
                    // base, row)
                    uint64_t uCell =
                        rD.m_fnAc70(nBase,
                                    nRow);
                    // FUN_1400678a0(cell)
                    uint64_t uCont =
                        rD.m_fn678a0(
                            uCell);
                    uint32_t uCount =
                        rD.m_fnContCount(
                            uCont);
                    for (uint32_t i = 0;
                         i < uCount; i++) {
                        // ORIGINAL: the
                        // literal user.cpp
                        // + line 0x57 args
                        uint64_t uItem =
                            rD.m_fnContGet(
                              uCont, i,
                              k_pszUserTickFile,
                              0x57, nRow,
                              (int)i);
                        if (uItem != 0 &&
                            rD.m_fnItemAlive(
                                uItem)) {
                            // ORIGINAL: d =
                            // sub->vt+8(sub,
                            // item x, item y)
                            uint32_t uDist =
                                rD.m_fnSubDist(
                                  rD.m_fnItemX38(
                                      uItem),
                                  rD.m_fnItemY40(
                                      uItem));
                            // (int)d < 0x13
                            if ((int)uDist
                                < 0x13)
                                return uDist;
                        }
                    }
                }
                // ORIGINAL: base++
                nBase++;
            }
        }
        // ===== the leave broadcast =====
        // ORIGINAL: world = FUN_14001c210()
        // ->vt+0x10(); id = this->vt+0x8();
        // world->vt+0x28(world, id)
        uint32_t uId = rD.m_fnThisId();
        uRet = rD.m_fnWorldLeave(uId);
    }
    return (uint32_t)uRet;
}

} // namespace npc

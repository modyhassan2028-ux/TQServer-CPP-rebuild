#include "NpcStateUtil.h"

namespace npc {

uint32_t CNpcIsTransformLocked(CNpcStateData& rN) {
    // ORIGINAL FUN_140057d30:
    // return ~(row(0x15) >> 0xf) & 1;
    return ~(rN.m_fnRowGetFlag() >> 0xf) & 1u;
}

bool CNpcCanAct(CNpcStateData& rN) {
    // ORIGINAL FUN_14005ad00:
    // w1 bit5 blocks
    uint32_t uW1 = rN.m_fnSubGetWord20(0);
    if ((uW1 >> 5 & 1) != 0)
        return false;
    // w2 bit3 blocks
    uint32_t uW2 = rN.m_fnSubGetWord20(1);
    if ((uW2 >> 3 & 1) != 0)
        return false;
    uint32_t uFlags = rN.m_fnRowGetFlag();
    // ORIGINAL: if (flags bit6) require bit5
    if ((uFlags >> 6 & 1) != 0) {
        if ((uFlags >> 5 & 1) == 0)
            return false;
    }
    return true;
}

bool CNpcTeleportApproach(CNpcStateData& rN, int nTX,
                          int nTY, int nId18) {
    // ORIGINAL: if (!map) log error
    if (!rN.m_bHasMap) {
        rN.m_fnLogError();       // DAT_1400be0b0
        return false;
    }
    // ORIGINAL: steps = sub->vt+8(sub)
    int nSteps = rN.m_fnSubVt8();
    if (nSteps < 1)
        return false;
    for (int i = 1; i < nSteps + 1; i++) {
        int nCX = rN.m_fnSubGetX38();
        int nX = nCX + (nTX - nCX) * i / nSteps;
        int nCY = rN.m_fnSubGetY40();
        int nY = nCY + (nTY - nCY) * i / nSteps;
        // ORIGINAL: FUN_14004cc70(map, nx, ny)
        // - x component first here (vs y-first in
        // FUN_14005d140), preserved per call site
        if (rN.m_fnInSight(nX, nY)) {
            rN.m_fnMoveTo(nX, nY, nId18);
            return true;         // first visible
        }
    }
    if (rN.m_fnInSight(nTX, nTY)) {
        rN.m_fnMoveTo(nTX, nTY, nId18);
        return true;
    }
    return false;
}

bool CNpcWanderStep(CNpcStateData& rN, uint32_t uDir) {
    // ORIGINAL: dir >= 8 || !map -> the error log
    if (uDir >= 8 || !rN.m_bHasMap) {
        rN.m_fnLogError();       // DAT_1400be0b0
        return false;
    }
    // ORIGINAL: u48 = sub->vt+0x48(sub) (no-arg)
    uint32_t u48 = rN.m_fnSubVt48NoArgs();
    int nX = rN.m_fnSubGetX38();
    int nY = rN.m_fnSubGetY40();
    // ORIGINAL: FUN_14004bff0(map, x, y, dir, u48,
    // 0x1a)
    if (!rN.m_fnMapWalkable(nX, nY, (int)uDir, u48))
        return false;
    rN.m_nField40 = uDir;        // +0x40 facing
    rN.m_dwField2C = 1;          // +0x2c walk lock
    return true;
}

} // namespace npc

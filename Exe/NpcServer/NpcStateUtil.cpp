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

bool CNpcRateGate(int32_t& rnStamp, int nWindow,
                  std::function<uint32_t()>& fnTimeGet) {
    // ORIGINAL FUN_14005a8f0
    uint32_t uNow = fnTimeGet();
    int32_t nStamp = rnStamp;
    // ORIGINAL: if (uVar2 < param_2 + iVar1) return 0
    if (uNow < (uint32_t)(nWindow + nStamp))
        return false;
    // ORIGINAL: if (iVar1 + param_2*2 <= uVar2)
    if ((uint32_t)(nStamp + nWindow * 2) <= uNow) {
        rnStamp = (int32_t)fnTimeGet();  // reset
        return true;
    }
    // ORIGINAL: stamp += window; return 1
    rnStamp = nStamp + nWindow;
    return true;
}

bool CNpcAttachAlive(bool bHasAttach) {
    // ORIGINAL FUN_140069750:
    // +8 != 0 && +0x10 != 0 - modeled by the
    // single has-attach flag of the seam
    return bHasAttach;
}

bool CNpcC960(CNpcStateData& rN, uint32_t uFlavor) {
    // ORIGINAL: key = param_2 ? 0x1a : 0x13
    uint32_t uKey = uFlavor ? 0x1a : 0x13;
    int nWindow = rN.m_fnRowGetInt(uKey);
    // ORIGINAL: FUN_14005a8f0(npc+0xb8, iVar2)
    if (!CNpcRateGate(rN.m_nA8f0Stamp, nWindow,
                      rN.m_fnTimeGet))
        return true;         // rate-held: handled
    // ORIGINAL: if (+0x2c < 1) return 0
    if ((int)rN.m_dwField2C < 1)
        return false;
    // ORIGINAL: (int8)queue[0] % 8 - the Ghidra
    // sign-mod idiom (x>>31 & 7)
    int nDir = (int)(int8_t)rN.m_dirQueue[0] % 8;
    // ORIGINAL: len = +0x2c - 1; the queue shift
    int nLen = (int)rN.m_dwField2C - 1;
    rN.m_dwField2C = (uint32_t)nLen;
    if (nLen != 0) {
        // memcpy(npc+0x40, npc+0x41, len)
        for (int i = 0; i < nLen && i < 15; i++)
            rN.m_dirQueue[i] =
                rN.m_dirQueue[i + 1];
    }
    rN.m_nField40 = rN.m_dirQueue[0];
    // ORIGINAL: FUN_14005b9e0(npc, dir, flavor)
    if (rN.m_fnB9e0(nDir, uFlavor))
        return true;
    if (!rN.m_bHasAttach ||
        !CNpcAttachAlive(rN.m_bHasAttach)) {
        // ===== no-attach path =====
        // ORIGINAL: FUN_140058260(npc, dir)
        if (rN.m_fnAttack260(nDir) &&
            rN.m_dwField2C != 0) {
            // LAB_14005caf0
            rN.m_dwField2C = 0;
            return rN.m_fnB9e0(
                (int)(int8_t)rN.m_dirQueue[0],
                uFlavor);
        }
        // ORIGINAL: row(0x15) bit5 -> home
        if ((rN.m_fnRowGetFlag() >> 5 & 1) != 0) {
            int nLo = 0, nHi = 0;
            rN.m_fnGenGetSpawn(nLo, nHi);
            // ORIGINAL: FUN_140059f40(npc, lo,
            // hi, id) - the real teleport body
            return CNpcTeleportApproach(rN, nLo,
                                        nHi,
                                        rN.m_fnSubId18());
        }
        return false;
    }
    // ===== the attach path =====
    int nResLo = 0, nResHi = 0;
    // ORIGINAL: FUN_140058b80(npc, &res) - fills
    // BOTH res18/res1c words
    if (!rN.m_fn58b80(nResLo, nResHi))
        return false;
    rN.m_dwField2C = 0;
    // ORIGINAL: RandGet(100) < 0x46 ? 0
    // : row->vt+0x10(row, 0x10)
    uint32_t uParam4 =
        rN.m_fnRandGet(100) < 0x46
            ? 0 : (uint32_t)rN.m_fnRowGetInt(0x10);
    // ORIGINAL: FUN_1400580e0(npc, lo, hi, p4)
    bool bMoved = rN.m_fn580e0(nResLo, nResHi,
                               (int)uParam4);
    if (bMoved &&
        !rN.m_fnB9e0((int)(int8_t)rN.m_dirQueue[0],
                     uFlavor) &&
        rN.m_fn588b0(nResLo, nResHi, nDir) &&
        rN.m_dwField2C != 0) {
        // LAB_14005caf0
        rN.m_dwField2C = 0;
        return rN.m_fnB9e0(
            (int)(int8_t)rN.m_dirQueue[0],
            uFlavor);
    }
    // ORIGINAL: return uVar5 & mask - the packed
    // low byte here is bVar1 = the FUN_1400580e0
    // move result, NOT a plain false
    return bMoved;
}

// ORIGINAL DAT_1400c89d0 / DAT_1400c89f0 -
// identical to the FUN_140087d50 wander probe
// table (verified against the binary .rdata)
static const int s_nDirX[8] = { 0,-1,-1,-1, 0, 1, 1, 1 };
static const int s_nDirY[8] = { 1, 1, 0,-1,-1,-1, 0, 1 };

bool CNpcAttackDir(CNpcStateData& rN, int nCurDir) {
    if (!rN.m_bHasMap) {
        rN.m_fnLogError();       // DAT_1400be0b0
        return false;
    }
    rN.m_dwField2C = 0;          // +0x2c = 0
    // ORIGINAL: gen->vt+0x28 spawn as reference
    int nRefX = 0, nRefY = 0;
    rN.m_fnGenGetSpawn(nRefX, nRefY);
    // ORIGINAL: target override if found
    if (rN.m_nTargetId != 0) {
        CNpcTargetSeam* pT =
            rN.m_fnFindTarget(rN.m_nTargetId);
        if (pT != nullptr) {
            nRefX = pT->m_nX;
            nRefY = pT->m_nY;
        }
    }
    // ORIGINAL: ref = sub->vt+8(sub, refX, refY)
    int nRef = rN.m_fnSubDist(nRefX, nRefY);
    int nBest = -1;
    uint32_t uRet;
    int nRand = (int)rN.m_fnRandGet(8);
    uRet = (uint32_t)(nRand + 8);
    for (int i = nRand; i < nRand + 8; i++) {
        int nDir = i % 8;        // signed mod idiom
        if (nDir == nCurDir)
            continue;
        // ORIGINAL: mapObj = sub->vt+0x80()
        if (!rN.m_fnSubHasMap80()) {
            uRet = 0;
            continue;
        }
        uint32_t u48 = rN.m_fnSubVt48NoArgs();
        int nX = rN.m_fnSubGetX38();
        int nY = rN.m_fnSubGetY40();
        // ORIGINAL: FUN_14004bff0(map, x, y,
        // dir, u48, 0x1a)
        if (!rN.m_fnMapWalkable(nX, nY, nDir, u48)) {
            uRet = 0;
            continue;
        }
        // ORIGINAL: the candidate cell + the
        // DAT_1400c89d0/89f0 tables
        int nDX = (nX + s_nDirX[nDir]) - nRefX;
        int nDY = (nY + s_nDirY[nDir]) - nRefY;
        int nADX = nDX < 0 ? -nDX : nDX;
        int nADY = nDY < 0 ? -nDY : nDY;
        int nD = nADY < nADX ? nADX : nADY;
        // ORIGINAL: sgn = +0x3c ? 1 : -1
        int nSign = rN.m_nField3C != 0 ? 1 : -1;
        if (0 < nSign * (nRef - nD)) {
            nBest = nDir;
            nRef = nD;          // the greedy ref
        }
        uRet = (uint32_t)nD;    // the verbatim leak
    }
    if (nBest != -1) {
        // ORIGINAL: +0x40 = best; +0x2c = 1
        rN.m_dirQueue[0] = (uint8_t)nBest;
        rN.m_nField40 = (uint32_t)(uint8_t)nBest;
        rN.m_dwField2C = 1;
        return true;
    }
    // ORIGINAL: return uVar9 & 0xff00 mask -
    // the low byte LEAKS the last distance
    return (uRet & 0xff) != 0;
}

} // namespace npc

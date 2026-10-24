#include "NpcState.h"

namespace npc {

bool CNpcState6(CNpcStateData& rN) {
    // ORIGINAL: flags = row(0x15);
    uint32_t uFlags = rN.m_fnRowGetFlag();
    // ORIGINAL: if (!(flags >> 0xf & 1)) { log; reset }
    if ((uFlags >> 0xf & 1) == 0) {
        rN.m_fnLogError();       // DAT_1400be0b0
        rN.m_dwField2C = 0;      // +0x2c
        rN.m_nState = 1;         // +0x18
        return true;
    }
    CNpcTargetSeam* pTarget =
        rN.m_fnFindTarget(rN.m_nTargetId);  // +0x84
    // ORIGINAL: bits 3/4 gate the sight path
    uFlags = rN.m_fnRowGetFlag();
    bool bSightPath = (uFlags >> 3 & 1) != 0 ||
                      (uFlags >> 4 & 1) != 0;
    if (bSightPath) {
        if (pTarget != nullptr) {
            // ORIGINAL: FUN_14004cc70(map, tgtY,
            // tgtX) - arg order (map, y, x)
            if (rN.m_fnInSight(pTarget->m_nY,
                               pTarget->m_nX)) {
                int nId18 = rN.m_fnSubId18();
                // ORIGINAL: FUN_1400597f0(npc, x, y,
                // id)
                rN.m_fnMoveTo(pTarget->m_nX,
                              pTarget->m_nY, nId18);
                rN.m_nState = 7;        // +0x18 = 7
                return true;
            }
        }
    }
    // LAB_14005d291
    if (!rN.m_fnB030()) {       // FUN_14005b030
        if (rN.m_dwField2C == 0) {       // +0x2c == 0
            // ORIGINAL: FUN_14005b760(npc,
            // row(0x10) * 2)
            rN.m_fnWanderStart(
                rN.m_fnRowGetInt(0x10) * 2);
        }
        if (rN.m_nTargetId == 0) {        // +0x84 == 0
            rN.m_dwField2C = 0;
            rN.m_nState = 1;
            return true;
        }
        if (rN.m_dwField2C == 0) {
            rN.m_nState = 7;
            return true;
        }
        rN.m_fnC960(1);       // FUN_14005c960(npc, 1)
    }
    return true;
}

bool CNpcState8(CNpcStateData& rN) {
    CNpcTargetSeam* pTarget =
        rN.m_fnFindTarget(rN.m_nTargetId);
    // ===== the chase branch =====
    if (pTarget != nullptr && pTarget->m_bValid50) {
        if (pTarget->m_nMapId == rN.m_fnSubMapId()) {
            int nD1 = rN.m_fnSubDist(pTarget->m_nX,
                                     pTarget->m_nY);
            int nD2 = rN.m_fnSubDist48(
                pTarget->m_nField48);
            // ORIGINAL: if (d2 < d1) goto LAB_475
            if (!(nD2 < nD1)) {
                if (rN.m_fn2700()) {   // FUN_140002700
                    if (rN.m_bHasMap) {
                        void* pRole = rN.m_fnGetRole();
                        if (rN.m_fnAd20(pRole)) {
                            // ORIGINAL: +0x3c = 0;
                            // FUN_140058260(npc, -1);
                            // +0x3c = 1
                            rN.m_nField3C = 0;
                            rN.m_fnAttack(-1);
                            rN.m_nField3C = 1;
                            if (rN.m_dwField2C != 0)
                                rN.m_fnC960(2);
                        }
                    }
                    // ORIGINAL: if (+0x3e) { +0x3e=0;
                    // return 1; }
                    if (rN.m_nField3E != 0) {
                        rN.m_nField3E = 0;
                        return true;
                    }
                    // LAB_14005d467
                    rN.m_nState = 7;
                    return true;
                }
                return true;       // LAB_14005d535
            }
        }
    }
    // ===== LAB_14005d475: lose/keep target =====
    if (rN.m_pAttach140 != nullptr) {
        if (!rN.m_fn750()) {       // FUN_140069750
            // ORIGINAL: goto LAB_48f (the aggro
            // re-check), then still reset
        } else {
            rN.m_dwField2C = 0;
            rN.m_nState = 1;
            return true;
        }
    }
    // LAB_14005d48f: the aggro re-check
    if (rN.m_fnBC80()) {            // FUN_14005bc80
        CNpcTargetSeam* pT2 =
            rN.m_fnFindTarget(rN.m_nTargetId);
        if (pT2 != nullptr && pT2->m_bValid50) {
            int nD1 = rN.m_fnSubDist(pT2->m_nX,
                                     pT2->m_nY);
            int nD2 =
                rN.m_fnSubDist48(pT2->m_nField48);
            // ORIGINAL: if (d1 <= d2) goto LAB_535
            if (nD1 > nD2) {
                // ORIGINAL: if (+0x2c &&
                // FUN_14005ad00) goto LAB_467
                if (rN.m_dwField2C != 0 &&
                    rN.m_fnAD00()) {
                    rN.m_nState = 7;
                    return true;    // keep chasing
                }
            } else {
                return true;        // LAB_535
            }
        } else {
            return true;            // LAB_535
        }
    }
    // ORIGINAL: +0x2c = 0; +0x18 = 1;
    rN.m_dwField2C = 0;
    rN.m_nState = 1;
    return true;
}

} // namespace npc

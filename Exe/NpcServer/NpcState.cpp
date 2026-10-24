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
                               // (return unused here)
    }
    return true;
}

bool CNpcState7(CNpcStateData& rN) {
    CNpcTargetSeam* pTarget =
        rN.m_fnFindTarget(rN.m_nTargetId);
    bool bNoTarget = pTarget == nullptr ||
                     !pTarget->m_bValid50;
    if (!bNoTarget) {
        // ===== valid target: map/distance gates =====
        if (pTarget->m_nMapId == rN.m_fnSubMapId()) {
            int nD1 = rN.m_fnSubDist(pTarget->m_nX,
                                     pTarget->m_nY);
            int nD2 = rN.m_fnSubDist48(
                pTarget->m_nField48);
            if (!(nD2 < nD1)) {
                // ORIGINAL: if (!bit3 &&
                // !FUN_14005ad00 && sub->vt+0x60() &&
                // (+0x3c == 0 && +0x2c > 0) &&
                // FUN_14005c960(npc,1)) return;
                uint32_t uFlags = rN.m_fnRowGetFlag();
                if ((uFlags >> 3 & 1) == 0) {
                    if (!rN.m_fnAD00() &&
                        rN.m_fnSub60() &&
                        rN.m_nField3C == 0 &&
                        (int)rN.m_dwField2C > 0) {
                        if (rN.m_fnC960(1)) {
                            return true;   // 14005d99a
                        }
                    }
                }
                // ORIGINAL: FUN_140059c90; state 8
                rN.m_fn59c90();
                rN.m_nState = 8;
                rN.m_dwField2C = 0;
                return true;
            }
        }
        // fall into LAB_14005d668
    }
    // ===== LAB_14005d668: no valid target =====
    if (rN.m_fnCB60())
        return true;              // LAB_14005d99a
    int nRes8 = 0, nResc = 0;
    rN.m_fnGenGetSpawn(nRes8, nResc);
    uint32_t uFlags = rN.m_fnRowGetFlag();
    bool bSightBits = (uFlags >> 3 & 1) != 0 ||
                      (uFlags >> 4 & 1) != 0 ||
                      (uFlags >> 7 & 1) != 0;
    bool bWent789 = false;
    if (bSightBits) {
        // ORIGINAL: gen->vt+0x70(gen, map, x, y,
        // 0x30) InArea dance
        int nSubMap = rN.m_fnSubMapId();
        int nSubX = 0, nSubY = 0;
        rN.m_fnSubGetPos(nSubX, nSubY);
        bool bMeIn = rN.m_fnGenInArea(nSubMap, nSubX,
                                      nSubY);
        if (!bMeIn) {
            if (pTarget != nullptr &&
                rN.m_fnGenInArea(pTarget->m_nMapId,
                                 pTarget->m_nX,
                                 pTarget->m_nY)) {
                // LAB_14005d969
                rN.m_nTargetId = 0;   // +0x84 = 0
                rN.m_fn5a0d0(nRes8, nResc,
                             rN.m_fnSubId18());
                rN.m_nState = 1;
                rN.m_dwField2C = 0;
                return true;
            }
            bWent789 = true;      // goto LAB_14005d789
        } else {
            // LAB_14005d969 (me in gen area)
            rN.m_nTargetId = 0;
            rN.m_fn5a0d0(nRes8, nResc,
                         rN.m_fnSubId18());
            rN.m_nState = 1;
            rN.m_dwField2C = 0;
            return true;
        }
    } else {
        bWent789 = true;
    }
    (void)bWent789;
    // ===== LAB_14005d789: the no-sight block =====
    uFlags = rN.m_fnRowGetFlag();
    bool bTele = (uFlags >> 3 & 1) != 0 ||
                 (uFlags >> 4 & 1) != 0 ||
                 (uFlags >> 0xb & 1) != 0;
    if (bTele && pTarget != nullptr) {
        int nD = rN.m_fnSubDist(pTarget->m_nX,
                                pTarget->m_nY);
        // ORIGINAL: 5 < d && map != 0 &&
        // FUN_140049310
        if (nD > 5 && rN.m_bHasMap) {
            if (rN.m_fn49310(pTarget->m_nX,
                             pTarget->m_nY)) {
                rN.m_fnMoveTo(pTarget->m_nX,
                              pTarget->m_nY,
                              rN.m_fnSubId18());
                return true;
            }
        }
    }
    if (rN.m_dwField2C != 0) {
        // ORIGINAL: FUN_14005c960(npc, +0x84 ? 1 : 0)
        rN.m_fnC960(rN.m_nTargetId != 0 ? 1u : 0u);
        return true;
    }
    if (rN.m_fnBC80()) {
        // ORIGINAL: if (+0x2c) return
        if (rN.m_dwField2C != 0)
            return true;
        uFlags = rN.m_fnRowGetFlag();
        if ((uFlags >> 5 & 1) != 0) {
            CNpcTargetSeam* pT2 =
                rN.m_fnFindTarget(rN.m_nTargetId);
            if (pT2 == nullptr) {
                rN.m_fnLogError();   // DAT_1400be0b0
            } else {
                rN.m_fn59f40(pT2->m_nX, pT2->m_nY,
                             rN.m_fnSubId18());
            }
            return true;
        }
    }
    // ORIGINAL: +0x18 = 1; +0x2c = 0
    rN.m_nState = 1;
    rN.m_dwField2C = 0;
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

#include "NpcTargetSearch.h"

namespace npc {

uint32_t CNpcTargetSearch(
    CNpcTargetSearchData& rD) {
    // ORIGINAL FUN_14005bc80
    uint32_t uRet = 0;
    if (!rD.m_bHasMap) {          // +0x98 == 0
        // ORIGINAL: local_488 = 0x66a (the
        // error code assigned before the log)
        rD.m_fnLogError();
        return 0;   // LAB_14005bcd2
    }
    // ===== the PK block (bits 8/9 of 0x15) ==
    uint32_t v = (uint32_t)
        rD.m_fnRowGetInt(0x15);
    if ((((v >> 8) & 1) != 0) ||
        (v = (uint32_t)rD.m_fnRowGetInt(
                  0x15),
         ((v >> 9) & 1) != 0)) {
        if (!rD.m_fn59dc0()) {
            v = (uint32_t)
                rD.m_fnRowGetInt(0x15);
            // ORIGINAL: uVar11 = v >> 8 then
            // the low-byte return - bit8 set
            // makes it 1 (verbatim leak)
            if (((v >> 8) & 1) != 0)
                return ((uint32_t)(v >> 8))
                       & 0xff;
        } else {
            v = (uint32_t)
                rD.m_fnRowGetInt(0x15);
            if (((v >> 9) & 1) != 0)
                return 1;   // CONCAT71(v>>0x11,1)
        }
    }
    // ===== clear the target, remember the old =
    int nOld = rD.m_nTargetId;    // local_46c
    rD.m_nTargetId = 0;           // +0x84 = 0
    uint64_t uBestObj = 0;        // local_460
    // ORIGINAL: the ARGUMENT-LESS vt+0x10
    // render (stale-register artifact);
    // bit 1 gates the whole scan
    uint32_t uGate = (uint32_t)
        rD.m_fnRowGetIntNoArg();
    if ((uGate & 2) == 0)
        return 0;   // LAB_14005c47f
    // ===== the (dead) validate block =======
    // ORIGINAL: find is called with +0x84
    // AFTER it was zeroed -> id 0 -> dead
    uint64_t uT = rD.m_fnFindTarget(
        rD.m_nTargetId);
    if (uT == 0 || !rD.m_fnItemAlive(uT)) {
        rD.m_nTargetId = 0;       // LAB_be4b
    } else {
        int nSight0 = rD.m_fnRowGetInt(
            0x10);
        int d0 = rD.m_fnSubDist(
            rD.m_fnItemX38(uT),
            rD.m_fnItemY40(uT));
        if (nSight0 < d0)
            rD.m_nTargetId = 0;
    }
    // ===== the ring scan =====================
    int nSight = rD.m_fnRowGetInt(0x10);
    int nBest = nSight;             // local_470
    int nX = rD.m_fnSubGetX38();
    int nBase = (nX / 0x12 - 1 < 1)
        ? 0 : nX / 0x12 - 1;
    while (true) {
        // ORIGINAL: width bound inside the
        // outer loop
        if (rD.m_fn490Width() <= nBase)
            break;
        int nY = rD.m_fnSubGetY40();
        int nRow = (nY / 0x12 - 1 < 1)
            ? 0 : nY / 0x12 - 1;
        while (true) {
            if (rD.m_fn440Height()
                <= nRow)
                break;
            // ===== pass 1: the NPC container
            // (FUN_1400678b0, npc.cpp 0x68f)
            uint64_t uCell =
                rD.m_fnAc70(nBase, nRow);
            uint64_t uCont =
                rD.m_fn678b0(uCell);
            uint32_t uCount =
                rD.m_fnContCount(uCont);
            for (uint32_t i = 0;
                 i < uCount; i++) {
                uint64_t uItem =
                    rD.m_fnContGet(
                        uCont, i,
                        k_pszNpcCppFile,
                        0x68f);
                if (uItem == 0 ||
                    !rD.m_fnItemSubAlive(
                        uItem))
                    continue;
                v = (uint32_t)
                    rD.m_fnRowGetInt(0x15);
                uint32_t uFlags =
                    rD.m_fnItemSubFlags(
                        uItem);
                // ORIGINAL: the nested
                // (((B)||(C))||(D)) gate
                bool bB =
                    (((v >> 3) & 1) != 0 &&
                     (uFlags & 1) != 0) ||
                    (((v >> 4) & 1) != 0 &&
                     ((uFlags >> 0xf) & 1)
                         != 0);
                bool bC =
                    ((v >> 0xb) & 1) != 0 &&
                    rD.m_fn5ab20(uItem);
                v = (uint32_t)
                    rD.m_fnRowGetInt(0x15);
                bool bD =
                    (rD.m_fnSubVt58() &&
                     ((v >> 4) & 1) == 0) &&
                    (v = (uint32_t)
                         rD.m_fnRowGetInt(
                             0x15),
                     ((v >> 0xb) & 1) == 0);
                bool bE =
                    (!rD.m_fnItemVt78(
                          uItem) ||
                     rD.m_fnSubVt78()) ||
                    !rD.m_fn59710();
                bool bF =
                    ((uFlags >> 0x1d) & 1)
                    == 0;
                if (!((bB || bC || bD) &&
                      bE && bF))
                    continue;
                // ORIGINAL: the level clamp
                int nLevel =
                    rD.m_fnItemSubGet48(
                        uItem);
                int n468 =
                    rD.m_fnSubGetInt(
                        nLevel);
                if (nSight <= n468)
                    n468 = nSight;
                int d = rD.m_fnSubDist(
                    rD.m_fnItemX38(uItem),
                    rD.m_fnItemY40(
                        uItem));
                if ((d <= nBest &&
                     !rD.m_fnItemVt68(
                         uItem)) ||
                    (d <= n468 &&
                     rD.m_fnSubGetInt(0)
                         > 1)) {
                    nBest = d;
                    rD.m_nTargetId =
                        rD.m_fnItemId8(
                            uItem);
                    uBestObj = uItem;
                }
            }
            // ===== pass 2: the user container
            // (FUN_1400678a0, npc.cpp 0x6b2)
            uCell = rD.m_fnAc70(nBase,
                                nRow);
            uCont = rD.m_fn678a0(uCell);
            uCount = rD.m_fnContCount(
                uCont);
            for (uint32_t i = 0;
                 i < uCount; i++) {
                uint64_t uItem =
                    rD.m_fnContGet(
                        uCont, i,
                        k_pszNpcCppFile,
                        0x6b2);
                if (uItem == 0 ||
                    !rD.m_fnItemAlive(
                        uItem))
                    continue;
                // ORIGINAL:
                // (sub58 && item70) ||
                // (sub70 && item58)
                bool bG =
                    (rD.m_fnSubVt58() &&
                     rD.m_fnItemVt70(
                         uItem)) ||
                    (rD.m_fnSubVt70() &&
                     rD.m_fnItemVt58(
                         uItem));
                // ORIGINAL: item78 == 0 ||
                // sub78 || 57c50 ||
                // (GetInt(0x24) &&
                //  GetInt(0x24) != 0x3fc)
                bool bH =
                    !rD.m_fnItemVt78(
                        uItem) ||
                    rD.m_fnSubVt78() ||
                    rD.m_fn57c50() ||
                    (rD.m_fnRowGetInt(0x24)
                         != 0 &&
                     rD.m_fnRowGetInt(
                         0x24) != 0x3fc);
                if (!(bG && bH))
                    continue;
                // ORIGINAL: the owner fetch
                // (vt+0xb0(0x1040, &o))
                uint64_t uOwner =
                    rD.m_fnItemVtB0(
                        uItem);
                if (uOwner != 0 &&
                    rD.m_fnOwnerRow15Bit3(
                        uOwner))
                    continue;
                int d = rD.m_fnSubDist(
                    rD.m_fnItemX38(uItem),
                    rD.m_fnItemY40(uItem));
                if (d <= nBest) {
                    nBest = d;
                    // ORIGINAL: pass 2 does
                    // NOT update local_460
                    rD.m_nTargetId =
                        rD.m_fnItemId28(
                            uItem);
                }
            }
            nRow++;   // local_478 = iVar4+1
        }
        nBase++;       // local_474 = iVar9+1
        nX = rD.m_fnSubGetX38();
        if (nX / 0x12 + 1 < nBase)
            break;
    }
    // ===== LAB_14005c47f: the finale ==========
    if (rD.m_nTargetId == 0)
        return 0;
    // ORIGINAL: (best != null) && (old !=
    // best->vt+8) -> the shout
    if (uBestObj != 0 &&
        nOld != (int)rD.m_fnItemId8(
                     uBestObj)) {
        v = (uint32_t)rD.m_fnRowGetInt(
            0x15);
        uint32_t uBestFlags =
            rD.m_fnItemSubFlags(
                uBestObj);
        // ORIGINAL: !bit3 || !bit0 -> maybe
        // PPKER, else GUARD
        if (((v >> 3) & 1) == 0 ||
            (uBestFlags & 1) == 0) {
            if ((((v >> 4) & 1) != 0) &&
                ((uBestFlags >> 0xf) & 1)
                    != 0 &&
                rD.m_nField18Int == 1) {
                // theInstance() ->
                // "STR_PPKER_CALL_s" ->
                // sprintf -> 586b0
                rD.m_fnShout(
                    "STR_PPKER_CALL_s");
            }
        } else {
            rD.m_fnShout(
                "STR_GUARD_CALL_s");
        }
    }
    // ORIGINAL: FUN_14005b760(npc, 0)
    rD.m_fn5b760();
    return rD.m_nTargetId != 0 ? 1u : 0u;
}

} // namespace npc

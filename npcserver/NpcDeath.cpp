#include "NpcDeath.h"

namespace npc {

bool CNpcRebornTick(CNpcDeathData& rN) {
    uint64_t uNow = rN.m_fnNow();          // tq::TimeGet(0)
    // ORIGINAL: if (now/1000 < +0xb4 + +0xb0) return 0;
    if ((uint32_t)(uNow / 1000) <
        rN.m_nStampB4 + rN.m_nIntervalB0)
        return false;
    // ORIGINAL: +0xb4 = now/1000;
    rN.m_nStampB4 = (uint32_t)(uNow / 1000);

    // ORIGINAL: flags = row->vtable+0x10(_, 0x15)
    uint32_t uFlags = rN.m_fnRowGetFlag();
    // ORIGINAL: if (bit3 || bit4 || bit7) { ... gen
    // vtable+0x68 area check ... }
    if (((uFlags >> 3 & 1) != 0) ||
        ((uFlags >> 4 & 1) != 0) ||
        ((uFlags >> 7 & 1) != 0)) {
        int nX = 0, nY = 0;
        // ORIGINAL: uVar5 = sub+0x40 (y), uVar6 =
        // sub+0x38 (x); call gen+0x68(gen, x, y)
        rN.m_fnGetPos(nX, nY);
        if (!rN.m_fnGenInArea(nX, nY))
            return false;      // out of area -> stop
    }
    // ORIGINAL: if (map +0x98 != 0)
    if (rN.m_fnHasMap()) {
        int nX = 0, nY = 0;
        rN.m_fnGetPos(nX, nY);
        // ORIGINAL: FUN_14004ae30(map, x, y)
        if (rN.m_fnMapPosValid(nX, nY)) {
            // ORIGINAL: +0x1c = row(_,4); +0x20 =
            // row(_,5); +0x2c = 0; +0x18 = 0; return 1
            rN.m_dwField1C = rN.m_fnRowGetInt(4);
            rN.m_dwField20 = rN.m_fnRowGetInt(5);
            rN.m_dwField2C = 0;
            rN.m_nState = 0;
            return true;
        }
    }
    return false;
}

bool CNpcContinueGate(CNpcDeathData& rN) {
    // ORIGINAL FUN_140058860
    if (!rN.m_fnHasAttach140())
        return false;
    if (rN.m_fn6750() && !rN.m_fn6991() &&
        !rN.m_fn6974())
        return true;
    return false;
}

void CNpcDieDispatch(CNpcDeathData& rN) {
    bool bHandled = CNpcRebornTick(rN);   // FUN_14005b5c0
    if (bHandled)
        return;   // ORIGINAL: skip the state machine
    // ORIGINAL: sub vtable+0x50 != 0 && +0x148 == 0
    if (rN.m_fnCheck50() && !rN.m_bGate148) {
        CNpcContinueGate(rN);             // FUN_140058860
        // ORIGINAL: do { state = +0x18; ... } while
        // (++i < 10)
        for (int i = 0; i < 10; i++) {
            uint32_t uState = rN.m_nState;   // +0x18
            bool bStop = false;
            if (uState == 1) {
                bStop = rN.m_fnState1();      // 05e900
            } else if (uState == 6) {
                bStop = rN.m_fnState6();      // 05d140
            } else if (uState == 7) {
                bStop = rN.m_fnState7();      // 05d550
            } else if (uState == 8) {
                bStop = rN.m_fnState8();      // 05d330
            }
            if (bStop)
                return;
        }
    }
}

} // namespace npc

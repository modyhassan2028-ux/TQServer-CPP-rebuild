#include "NpcClose.h"

namespace npc {

void CNpcClose(CNpcCloseData& rN) {
    // ORIGINAL: if (param_1[0x23]) { +0x118=0; +0x114=0; }
    rN.m_fnResetTransform();
    // ORIGINAL: if (+0x98) FUN_14004c900(+0x98, this+0x10)
    rN.m_fnRemoveFromMap();
    if (rN.m_pGen != nullptr) {
        uint32_t uId = rN.m_fnGetId();       // vtable+8
        // ORIGINAL band: 0x61a82 <= id <= 0x7a11e
        // (the 0x7a121 < id && id < 599999 branch is
        // unreachable dead code in the decompile)
        if (0x61a82 <= uId && uId <= 0x7a11e)
            rN.m_fnBroadcastLeave(uId);
        // ORIGINAL: if (FUN_14001c1c0(+0x80) ||
        //   (+0x128 && +0x12c))
        //   gen->vtable+0x78(gen, id) - RESTOCK
        if (rN.m_fnIsSpecial(rN.m_nRecordId) ||
            (rN.m_bReportFlag && rN.m_bReportFlag2)) {
            rN.m_pGen->m_fnRestock(uId);
        }
    }
    if (rN.m_bReportFlag && rN.m_bReportFlag2) {
        rN.m_fnReportProcess();      // FUN_14005df30
        if (rN.m_pGen != nullptr &&
            rN.m_pGen->m_fnGetActive() == 0) {
            // report-mgr vtable+0x28(mgr, gen->vtable+8())
            // - the unregister path (FUN_14001c7a0 ->
            // FUN_140025ba0)
            rN.m_fnUnregisterGen(rN.m_pGen->m_fnGetId());
        }
    }
    rN.m_fnFinalRelease();          // FUN_14005da00
}

void CNpcCloseAndDelete(CNpcCloseData& rN,
    const std::function<void(CNpcCloseData&)>&
        rFnDeletingDtor) {
    CNpcClose(rN);                   // FUN_14005f020
    rFnDeletingDtor(rN);             // vtable+0 (_,1)
}

} // namespace npc

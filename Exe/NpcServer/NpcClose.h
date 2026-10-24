#pragma once
// ============================================================
// NpcServer unit 15: the NPC death chain
//   FUN_14005f020 = CNpc::Close (the death/cleanup body)
//   FUN_14005f450 = CNpc vtable+0xf0 = CloseAndDelete
//     (the SAME slot the Create-fail path uses, unit 9)
// Called on CNpc death (the FUN_14005f3b0 state machine
// and the delete-NPC paths converge here).
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

struct CNpcGen;

// the CNpc fields the death chain touches (unit-10 map)
struct CNpcCloseData {
    uint32_t m_nRecordId = 0;    // +0x80 (FUN_14001c1c0 key)
    std::function<uint32_t()> m_fnGetId;    // vtable+8
    std::function<void()> m_fnResetTransform; // +0x118=0,
                                              // +0x114=0
    std::function<void()> m_fnRemoveFromMap;  // FUN_14004c900
                                              // (+0x98 map)
    CNpcGen* m_pGen = nullptr;   // +0x100
    bool m_bReportFlag = false;  // +0x128
    bool m_bReportFlag2 = false; // +0x12c
    // seams
    std::function<bool(uint32_t)> m_fnIsSpecial;   // FUN_
                                                  // 14001c1c0
    std::function<void(uint32_t)> m_fnBroadcastLeave; // the
                                       // 0x61a82..0x7a11e
                                       // band notify
                                       // (FUN_14001c7a0
                                       // /FUN_140025c20
                                       // /FUN_14005e230)
    std::function<void()> m_fnReportProcess;  // FUN_14005df30
    std::function<void(uint32_t)> m_fnUnregisterGen;
        // report-mgr vtable+0x28(mgr, gen->vtable+8())
        // (FUN_14001c7a0 -> FUN_140025ba0)
    std::function<void()> m_fnFinalRelease;   // FUN_14005da00
};

// the generator side (seam view of CNpcGenerator)
struct CNpcGen {
    std::function<uint32_t()> m_fnGetId;     // vtable+8
    std::function<uint32_t()> m_fnGetActive; // vtable+0x20
    std::function<void(uint32_t)> m_fnRestock;  // vtable+0x78
                                               // = FUN_14005fb30
};

// ============================================================
// ===== ORIGINAL FUN_14005f020: CNpc::Close =====
// ============================================================
// if (+0x118) { +0x118 = 0; +0x114 = 0; }
// if (+0x98 map) FUN_14004c900(map, this+0x10);
// if (gen = +0x100) {
//   id = vtable+8();
//   if (0x61a82 <= id && id <= 0x7a11e)  // monster band
//     leave-broadcast (FUN_14001c7a0 ->
//     FUN_140025c20 -> FUN_14005e230(id record));
//     (the 0x7a121/599999 branch is dead code)
//   if (FUN_14001c1c0(+0x80) || (+0x128 && +0x12c))
//     gen->vtable+0x78(gen, id);   // RESTOCK ON DEATH
// }
// if (+0x128 && +0x12c) {
//   FUN_14005df30(this);
//   if (gen && gen->vtable+0x20() == 0)
//     report-mgr vtable+0x28(mgr, gen->vtable+8());
//     // (FUN_14001c7a0 -> FUN_140025ba0) - unregister
// }
// FUN_14005da00(this);
void CNpcClose(CNpcCloseData& rN);

// ============================================================
// ===== ORIGINAL FUN_14005f450: vtable+0xf0 =====
// ===== (invoked on the +0x10 subobject, adjusts -0x10) ==
// ============================================================
// FUN_14005f020(npc);
// vtable+0 (npc, 1);   // deleting dtor FUN_14005b550
//                       // -> FUN_14005c610(_, 1)
void CNpcCloseAndDelete(CNpcCloseData& rN,
    const std::function<void(CNpcCloseData&)>&
        rFnDeletingDtor);

} // namespace npc

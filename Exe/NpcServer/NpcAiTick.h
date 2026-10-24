// ORIGINAL: CNpc AI tick - vftable slot +0xe0.
// Extracted from the binary RTTI (type descriptor
// ".?AVCNpc@@" -> COL -> vtable at 0x1400c92f0):
//   +0xe0 = FUN_14005ada0 (the tick CNpcManager calls
//   every 3 frames on each NPC object).
#pragma once
#include <stdint.h>
#include <functional>

namespace npc {

class CNpcAiTick {
public:
    // ORIGINAL fields of FUN_14005ada0 (this+0x13c/0x140):
    int32_t  m_nHoldDelta = 0;   // +0x13c
    int32_t  m_nHoldStart = 0;   // +0x140 (0 = no hold)
    // the +0xb0 object with vcall+0x20 (this+0xb0)
    void*    m_pProcessor = nullptr;
    std::function<void(void*)> m_fnDispatch; // vcall+0x20

    // ORIGINAL FUN_14005a660 (IsProcessReady) - seam
    std::function<bool()> m_fnReady;
    // ORIGINAL FUN_14005a3b0 (the AI step) - seam
    std::function<void()> m_fnStep;
    // tq::TimeGet(0) - seam (ms)
    std::function<uint32_t()> m_fnTimeGet;

    // ===== ORIGINAL FUN_14005ada0 =====
    void Tick();
};

} // namespace npc

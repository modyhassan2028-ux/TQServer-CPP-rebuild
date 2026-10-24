#include "NpcAiTick.h"

namespace npc {

// ===== ORIGINAL FUN_14005ada0 (vtable +0xe0) =====
// if (+0x140 != 0): now = tq::TimeGet(0);
//   if (now/1000 < (+0x140) + (+0x13c)) return; (hold)
//   else clear both (+0x140 = +0x13c = 0)
// if (!FUN_14005a660(this)): if (+0xb0 obj)
//     (+0xb0 obj)->vcall+0x20(this); return;
// else FUN_14005a3b0(this);
void CNpcAiTick::Tick() {
    if (m_nHoldStart != 0) {
        uint32_t uNow = m_fnTimeGet();    // tq::TimeGet(0)
        if (uNow / 1000u <
            (uint32_t)(m_nHoldStart + m_nHoldDelta))
            return;                      // still on hold
        m_nHoldStart = 0;                // +0x140 = 0
        m_nHoldDelta = 0;                // +0x13c = 0
    }
    if (!m_fnReady()) {                  // FUN_14005a660
        if (m_pProcessor != nullptr)     // +0xb0
            m_fnDispatch(m_pProcessor);  // vcall+0x20
        return;
    }
    m_fnStep();                          // FUN_14005a3b0
}

} // namespace npc

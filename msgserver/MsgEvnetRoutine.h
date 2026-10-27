// ============================================================
// MsgServer strict port - unit M7
// ORIGINAL: the libevent worker thread
//  FUN_1404f8110 (EvnetRoutine - the thread
//                 entry, _beginthreadex target)
//  FUN_1404f72a0 (the loop: the +0x178 gate)
// NOTE: the "Evnet" TYPO is LITERAL in the
//  binary's log strings - preserved exactly.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgEvnetData {
    // the CSocketKernel object (M6 model)
    void* pKernel = nullptr;
    // kernel+0x178 = the libevent event base
    // (read directly from the object)
    std::function<void*()> m_fnGetBase;
    // FUN_1405426b0: event_base_dispatch
    std::function<void()> m_fnDispatch;
    std::function<void(const char*)> m_fnLog;
};

// ===== ORIGINAL FUN_1404f8110 @ 1404f8110 =====
// returns 0 (the thread exit code)
uint64_t MsgEvnetRoutine(MsgEvnetData& rD);

} // namespace msg

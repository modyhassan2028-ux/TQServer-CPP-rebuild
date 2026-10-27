// ============================================================
// MsgServer strict port - unit M33
// The state-3 "Kernel closing"
// cascade of FUN_140024860
// (lines ~30057-30404).
//  - FUN_14001e540("Kernel closing...")
//    + RecordThreadTimesInfo(true)
//  - FUN_14002e300/FUN_14002c6f0
//    (the pre-close)
//  - WAVE 1 (CloseThread only, no
//    messages, no destruction):
//    228(2000), 230(3000), 238(4000),
//    1b8(10000), 1c8(120000),
//    1e0(3000), the map threads
//    (array +0x1a0..+0x1a8, 60000
//    each), 1d8(8000), 1c0(4000)
//  - WAVE 2 (close + destroy via
//    the scalar deleting destructor
//    vt+0(this,1) + slot=0 +
//    FUN_140021bd0 refresh):
//    228(60000), 230(60000),
//    238(60000), 1b8(60000),
//    1c8(60000) [all with the
//    Ghidra-omitted ok/fail literal],
//    the map loop (300000, snprintf
//    "Close map group thread[%d]
//    OK\xa1\xa3" / "Close map group
//    thread[%d] failed!"),
//    1d8 (60000, "Close cross client
//    OK\xa1\xa3" / "Close cross client
//    failed!"), 1c0 (60000, "Close
//    world thread OK\xa1\xa3" / "Close
//    world thread failed!"),
//    1e8 ("Close Chat Thread OK." /
//    "Close Chat Thread Failed."),
//    1e0 ("Close Auction Search
//    Thread OK." / "Close Auction
//    Search Thread Failed."),
//    180 ("Close async DB thread OK."
//    / "Close async DB thread
//    failed." - note: refresh with
//    NO arg), SetLogThreadStatus(0),
//    178 ("Close Log thread OK." /
//    "Close Log thread failed.")
//  - the tail: log + refresh, the
//    status vt+0x30 call,
//    FUN_14050e8c0, FUN_14002e300/
//    FUN_14002d220, status ctrl = 0,
//    DatabaseUnInit, FUN_140021f60,
//    state = 4
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <vector>

namespace msg {

enum MsgKcSlot {
    KC_178 = 0, KC_180, KC_1C0,
    KC_1E0, KC_1C8, KC_1B8, KC_1D8,
    KC_1E8, KC_228, KC_238, KC_230
};

struct MsgKernelCloseState {
    void* pTh[11];
    std::vector<void*> vMapThreads;  // +0x1a0
    void* pStatusCtrl = nullptr;     // +0x1f0
    uint32_t nState = 3;
};

struct MsgKernelCloseData {
    std::function<void(const char* s)>
        m_fnLog;          // FUN_14001e540
    std::function<void()>
        m_fnRefresh;      // FUN_140021bd0
    std::function<bool(int slot,
        uint32_t ms)>
        m_fnClose;         // CloseThread
    std::function<void(int slot)>
        m_fnDestroy;       // vt+0(this,1)
    std::function<void()>
        m_fnRecordTimes;   // RecordThread-
                          // TimesInfo(true)
    std::function<void()>
        m_fnPreClose;      // 14002e300/
                          // 14002c6f0
    std::function<void()>
        m_fnSetLogThreadStatus;
    std::function<void()>
        m_fnStatusCall;    // vt+0x30
    std::function<void()>
        m_fnPostClose;     // 14050e8c0 +
                          // 14002d220 + f60
    std::function<void()>
        m_fnDbUnInit;
};

// runs the cascade; state -> 4
void MsgKernelClose(MsgKernelCloseState& st,
                    MsgKernelCloseData& rD);

} // namespace msg

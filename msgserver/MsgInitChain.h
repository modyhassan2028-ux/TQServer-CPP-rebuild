// ============================================================
// MsgServer strict port - unit M32
// The timer-1 init chain of
// FUN_140024860 (lines 29643-29890):
// the ordered thread-creation
// sequence of CMsgServerDlg.
//  - the once-flag DAT_14097593c
//  - state +0x1fc: 0 -> 4 (idle
//    done); 1 -> 3 then the chain;
//    success -> 2
//  - the slots (byte offsets):
//    +0x178 type 7 (FUN_14001b100,
//    size 0xd0, verify FUN_14001b1b0)
//    +0x180 CAsyncDBThread (size
//    0x40, ctor + vftable, verify
//    CreateThread("AsyncDBThread",
//    true))
//    +0x1c0 type 2 (FUN_14002e7e0,
//    size 0x50, verify FUN_14002e860)
//    +0x1e0 type 10 (FUN_1400f3060,
//    size 0x50, verify vt+0x20)
//    map threads: DAT_1409757d0 of
//    type i+0xe (FUN_14001d2d0,
//    size 0x58, each registered with
//    FUN_140024590(dlg+0x188),
//    verify vt+0x20)
//    +0x1c8 type 4 (FUN_14002e3d0,
//    size 0x50, verify FUN_14002e450)
//    +0x1b8 types 0xe,1
//    (FUN_14002bb50, size 0x58,
//    verify vt+0x20)
//    if flag@+0xe80: +0x1d8 type 6
//    (FUN_14004c0a0, size 0x68)
//    +0x1e8 type 8 (FUN_140001000,
//    size 0x50, verify FUN_140001080)
//    if flag@+0x1100: +0x228 type 9
//    (FUN_14050ff20, size 0x50)
//    if flag@+0x1108: +0x238 type
//    0xb (FUN_1400319c0, size 0xb0)
//    if flag@+0x1110: +0x230 type
//    0xd (FUN_140019520, size 0x8d8)
//  - after each verify:
//    AddThreadHandle(GetThreadHandle)
//  - then Resume in order: 1c0, 1e0,
//    the map threads, 1b8, 1c8, 1e8,
//    and 1d8/228/238/230 if present
//  - state 2 + the post-init:
//    FUN_14002ba80/FUN_140005550
//    handles, CPerformanceInfo::Init
//    (+0x158,"syslog/process"),
//    CThreadTimesInfo::Init, then
//    +0x144=600, +0x148=now/1000,
//    +0x14c=300, +0x150=now/1000
// The LAB_140026533 fail path stops
// the chain (state stays 3).
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <vector>

namespace msg {

enum MsgInitSlot {
    SLOT_178 = 0, SLOT_180, SLOT_1C0,
    SLOT_1E0, SLOT_1C8, SLOT_1B8,
    SLOT_1D8, SLOT_1E8, SLOT_228,
    SLOT_238, SLOT_230, SLOT_MAP0
};

struct MsgInitChainState {
    void* pTh[11 + 64];   // the slots
    std::vector<int> vMapIds;
    uint32_t nState = 1;  // +0x1fc
    uint32_t nMapThreads = 0;  // DAT_1409757d0
    bool bFlagD0 = false;   // dlg[0x1d0]
    bool bFlag20 = false;   // dlg[0x220]
    bool bFlag21 = false;   // dlg[0x221]
    bool bFlag22 = false;   // dlg[0x222]
    // the periodic timers
    uint32_t nPerf600 = 0;   // +0x144
    uint32_t tPerf600 = 0;   // +0x148
    uint32_t nPerf300 = 0;   // +0x14c
    uint32_t tPerf300 = 0;   // +0x150
};

struct MsgInitChainData {
    // create the thread object for the
    // slot (type/model VERBATIM);
    // nullptr = new failed
    std::function<void*(int nSlot,
        int nType1, int nType2)>
        m_fnCreate;
    // the per-slot verify; false stops
    std::function<bool(int nSlot)>
        m_fnVerify;
    std::function<void*()>
        m_fnCurrentThread;
    std::function<void(void* h)>
        m_fnAddHandle;
    std::function<void(int nSlot)>
        m_fnResume;
    std::function<void(const char* s)>
        m_fnLog;   // FUN_14001e540
    std::function<void()>
        m_fnSetLogThreadStatus;
    std::function<bool()>
        m_fnDatabaseInit;
    std::function<void*()>
        m_fnPostHandle1;  // FUN_14002ba80
    std::function<void*()>
        m_fnPostHandle2;  // FUN_140005550
    std::function<void()>
        m_fnPerfInit;   // +0x158 init
    std::function<void()>
        m_fnThreadTimesInit;   // +0x168
    std::function<uint32_t()>
        m_fnTimeGet;   // ms
};

// returns true on the full success
// path (state -> 2)
bool MsgTimerInitChain(
    MsgInitChainState& st,
    MsgInitChainData& rD);

} // namespace msg

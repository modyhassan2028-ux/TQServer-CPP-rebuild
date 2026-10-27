// ============================================================
// MsgServer strict port - unit M34
// The state-2 block of the WM_TIMER
// (FUN_140024860 lines ~29890-
// 30056): the performance periods
// and the socket/CCU statistics.
//  - FUN_1400149a0(dlg+0x144): the
//    600s period -> RecordPerformance
//    Info / RecordThreadTimesInfo(
//    true) / CMyHeapMgr::SaveLog
//  - FUN_1400149a0(dlg+0x14c): the
//    300s period -> FUN_14001f070,
//    then FUN_1400222e0(dlg+0x134,
//    300) gates the stats:
//      * 8 LOCK/UNLOCK zeroings:
//        DAT_1409756f8/6fc/714/718/
//        730/734/744/740
//      * the '-'x47 banner log with
//        the two dialog CStrings
//        (+0xf8, +0xe8)
//      * the socket stats log (the
//        client/Npc/Account send/recv
//        bytes/Msgs format) then 12
//        zeroings: DAT_140975788/
//        78c/790/794/798/79c/7a0/
//        7a4/7a8/7ac/7b0/7b4
//  - the CCU drift checks (VERBATIM):
//    |CCU-PCU| >= 10 or a zero
//    crossing -> log "CCU:%d, PCU:%d,
//    login:%d, logout:%d", zero
//    DAT_140975700/704, PCU = CCU
//  - FromOSCCU/ToOSCCU: same abs()
//    pattern -> "FromOSCCU:%d, PCU:%d,
//    in:%d, back:%d" (zero 71c/720),
//    "ToOSCCU:%d, PCU:%d, out:%d,
//    back:%d" (zero 738/73c)
//  - FUN_1400222e0() gates the UI
//    text build + "Game server
//    online.txt" write (a SEAM here)
//  - FUN_14050c390() > 10000 and
//    i%1000 == 0 -> "Message pipe
//    block, server may be slowly!!!"
//    + the dead-loop call-stack dump
//  - DAT_1409758f0 != 0 -> state 3
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

struct MsgStatCounters {
    // the 8 first-block zeros
    uint32_t n6f8, n6fc;
    uint32_t n714, n718;
    uint32_t n730, n734;
    uint32_t n744, n740;
    // CCU
    uint32_t nCCU;      // 6f0
    uint32_t nPCU;      // 6f4
    uint32_t nLogin;    // 700
    uint32_t nLogout;   // 704
    // FromOS
    uint32_t nFromCur;  // 70c
    uint32_t nFromMax;  // 710
    uint32_t nIn;       // 71c
    uint32_t nBack1;    // 720
    // ToOS
    uint32_t nToCur;    // 728
    uint32_t nToMax;    // 72c
    uint32_t nOut;      // 738
    uint32_t nBack2;    // 73c
    // the 12 socket counters
    uint32_t nSock[12]; // 788..7b4
};

struct MsgPerfStatsState {
    uint32_t nState = 2;
    MsgStatCounters c = {};
};

struct MsgPerfStatsData {
    std::function<bool()> m_fnPeriod600;
    std::function<bool()> m_fnPeriod300;
    std::function<void()>
        m_fnRecordPerf;
    std::function<void()>
        m_fnRecordTimes;
    std::function<void()> m_fnSaveLog;
    std::function<void()>
        m_fnRefreshUi;  // FUN_14001f070
    std::function<bool()>
        m_fnOnlineStats;  // 1400222e0
                          // (+0x134,300)
    std::function<bool()>
        m_fnUiGate;   // the second
                      // FUN_1400222e0()
                      // before the UI
                      // text build
    std::function<void()>
        m_fnLock, m_fnUnlock;
    // the composed log lines (the
    // formats composed in the port)
    std::function<void(const
        std::string&)> m_fnLogLine;
    // the UI text + online.txt write
    std::function<void()>
        m_fnUpdateUi;
    std::function<int()>
        m_fnPipeDepth;  // 14050c390
    std::function<void()>
        m_fnDumpStacks;
    // DAT_1409758f0 (the restart req)
    std::function<bool()>
        m_fnRestartRequested;
};

// the banner text (the VERBATIM
// format: 47 '-' + the two CStrings)
std::string MsgPerfBanner(
    const std::string& sTop,
    const std::string& sBottom);

// one timer tick of state 2
void MsgPerfStatsTick(
    MsgPerfStatsState& st,
    MsgPerfStatsData& rD);

// the CCU drift rule (VERBATIM):
// the UNSIGNED diff (a drop of any
// size logs!) - skip only when
// 0 <= cur-max < 10 and no zero
// crossing
bool MsgCcuDrifted(uint32_t nCur,
                   uint32_t nMax);
// the From/ToOS rule (VERBATIM):
// the SIGNED abs diff
// ((x^s)-s) < 10, then the zero
// crossing
bool MsgOscDrifted(uint32_t nCur,
                   uint32_t nMax);

} // namespace msg

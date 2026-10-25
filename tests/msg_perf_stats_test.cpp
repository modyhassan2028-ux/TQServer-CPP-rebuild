// MsgServer unit M34 - the state-2
// performance/stats block
#include "../Exe/MsgServer/Port/MsgPerfStats.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    struct Tr {
        int n600 = 0, n300 = 0;
        int nPerf = 0, nTimes = 0;
        int nSave = 0, nUi = 0;
        int nLocks = 0, nUnlocks = 0;
        int nDump = 0, nUiUpd = 0;
        std::vector<std::string> vLog;
    } tr;
    MsgPerfStatsData d;
    MsgPerfStatsState st;
    bool b600 = false, b300 = false;
    bool bOnline = true, bUiGate = true;
    int nPipe = 0; bool bRestart = false;
    d.m_fnPeriod600 = [&] {
        ++tr.n600; return b600; };
    d.m_fnPeriod300 = [&] {
        ++tr.n300; return b300; };
    d.m_fnRecordPerf = [&] { ++tr.nPerf; };
    d.m_fnRecordTimes = [&] { ++tr.nTimes; };
    d.m_fnSaveLog = [&] { ++tr.nSave; };
    d.m_fnRefreshUi = [&] { ++tr.nUi; };
    d.m_fnOnlineStats = [&] {
        return bOnline; };
    d.m_fnUiGate = [&] { return bUiGate; };
    d.m_fnLock = [&] { ++tr.nLocks; };
    d.m_fnUnlock = [&] { ++tr.nUnlocks; };
    d.m_fnLogLine = [&](const
        std::string& s) {
        tr.vLog.push_back(s); };
    d.m_fnUpdateUi = [&] { ++tr.nUiUpd; };
    d.m_fnPipeDepth = [&] {
        return nPipe; };
    d.m_fnDumpStacks = [&] {
        ++tr.nDump; };
    d.m_fnRestartRequested = [&] {
        return bRestart; };

    // ===== 1. an idle tick
    MsgPerfStatsTick(st, d);
    assert(tr.n600 == 1 &&
        tr.n300 == 1);
    assert(tr.nPerf == 0 &&
        tr.nUiUpd == 0);
    // the UI update only inside the
    // 300s period (not fired yet)
    assert(tr.nUiUpd == 0);

    // ===== 2. the 600s period fires
    b600 = true;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    assert(tr.nPerf == 1 &&
        tr.nTimes == 1 &&
        tr.nSave == 1);

    // ===== 3. the stats block fires
    // (300s + online)
    b300 = true;
    st.c.nCCU = 50; st.c.nPCU = 50;
    st.c.nLogin = 3; st.c.nLogout = 2;
    st.c.nFromCur = 5; st.c.nFromMax = 5;
    st.c.nToCur = 4; st.c.nToMax = 4;
    for (int i = 0; i < 12; ++i)
        st.c.nSock[i] = 100 + i;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    // the 8 + 12 zeroings all locked
    assert(tr.nUnlocks == tr.nLocks);
    // no CCU drift (50/50, 5/5, 4/4):
    // no drift lines, PCU kept
    assert(tr.nLocks == 20);
    assert(st.c.nPCU == 50 &&
        st.c.nFromMax == 5 &&
        st.c.nToMax == 4);
    // the 12 socket counters zeroed
    for (int i = 0; i < 12; ++i)
        assert(st.c.nSock[i] == 0);
    // the banner + socket lines
    assert(tr.vLog.size() == 2);
    assert(tr.vLog[0].find(
        "---------------") != -1);
    assert(tr.vLog[1].find(
        "client socket send bytes")
        != -1);

    // ===== 4. the CCU drift: diff 10
    st.c.nCCU = 60; st.c.nPCU = 50;
    st.c.nLogin = 7; st.c.nLogout = 9;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    assert(tr.vLog[2] ==
        "CCU:60, PCU:50, login:7,"
        " logout:9");
    assert(st.c.nLogin == 0 &&
        st.c.nLogout == 0);
    assert(st.c.nPCU == 60);

    // ===== 5. the zero crossing:
    // PCU 0 with CCU nonzero
    st.c.nCCU = 1; st.c.nPCU = 0;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    assert(st.c.nPCU == 1);

    // ===== 6. the drift window
    // (-10,10): small moves do not
    // log, big moves do
    st.c.nCCU = 62; st.c.nPCU = 60;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    assert(st.c.nPCU == 60);
    bool bCcu = false;
    for (auto& s : tr.vLog)
        if (s.find("CCU:") != -1)
            bCcu = true;
    assert(!bCcu);
    st.c.nCCU = 55; st.c.nPCU = 60;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    // a small DROP is inside the
    // signed window: no log either
    bCcu = false;
    for (auto& s : tr.vLog)
        if (s.find("CCU:") != -1)
            bCcu = true;
    assert(!bCcu);
    assert(st.c.nPCU == 60);
    // a LARGE drop (>= 10) logs
    st.c.nCCU = 45;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    bCcu = false;
    for (auto& s : tr.vLog)
        if (s.find("CCU:") != -1)
            bCcu = true;
    assert(bCcu);
    assert(st.c.nPCU == 45);
    // ===== 6b. the OSC checks use
    // the SIGNED abs: a small drop
    // does NOT log
    st.c.nCCU = st.c.nPCU = 50;
    st.c.nFromCur = 55;
    st.c.nFromMax = 60;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    bool bFrom = false;
    for (auto& s : tr.vLog)
        if (s.find("FromOSCCU:") != -1)
            bFrom = true;
    assert(!bFrom);
    assert(st.c.nFromMax == 60);

    // ===== 7. the pipe block
    st.c.nCCU = st.c.nPCU = 10;
    nPipe = 11000;   // >10000 and
                     // 11000%1000==0
    tr = Tr();
    MsgPerfStatsTick(st, d);
    bool bPipe = false;
    for (auto& s : tr.vLog)
        if (s.find("Message pipe block")
            != -1) bPipe = true;
    assert(bPipe && tr.nDump == 1);
    // 11001: not a multiple -> no
    nPipe = 11001;
    tr = Tr();
    MsgPerfStatsTick(st, d);
    bPipe = false;
    for (auto& s : tr.vLog)
        if (s.find("Message pipe block")
            != -1) bPipe = true;
    assert(!bPipe);

    // ===== 8. the restart request
    bRestart = true;
    st.nState = 2;
    MsgPerfStatsTick(st, d);
    assert(st.nState == 3);
    bRestart = false;

    // ===== the banner helper
    auto s = MsgPerfBanner("A", "B");
    assert(s.substr(0, 47) ==
        std::string(47, '-'));

    printf("MSG_PERF_STATS_OK: "
           "FUN_140024860 state-2 "
           "VERBATIM (the 600s period -> "
           "RecordPerf/RecordTimes/SaveLog, "
           "the 300s period -> the 8+12 "
           "LOCK/UNLOCK counter zeroings, "
           "the '-'x47 banner + the "
           "client/Npc/Account socket "
           "stats format, the CCU/"
           "FromOSCCU/ToOSCCU drift rule "
           "(|diff|>=10 or zero-crossing) "
           "with the zero+commit, the "
           "pipe-block check (>10000 and "
           "i%%1000==0) with the stack "
           "dump, and the restart "
           "request -> state 3)\n");
    return 0;
}

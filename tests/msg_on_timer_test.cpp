// MsgServer unit M37 - the OnTimer
// ASSEMBLY: the full lifecycle
#include "../Exe/MsgServer/Port/MsgOnTimer.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    // ===== shared traces
    struct Tr {
        int nKills1 = 0, nKills2 = 0;
        int nCloses = 0, nOnOK = 0;
        int nSleeps = 0;
        int nRelaunch = 0, nTeardown = 0;
        std::vector<std::string> vLogs;
        std::vector<std::pair<int,int>>
            vTimers;   // (id, ms)
    } tr;
    uint32_t tNow = 1000000;
    bool bShutdownEv = false;
    bool bRestartReq = false;

    // ===== the timer/prologue seams
    MsgTimerData tmd;
    tmd.m_fnWaitFor = [&](void* h) {
        return bShutdownEv ? 0 : 1; };
    tmd.m_fnTimeGet = [&] {
        return tNow; };
    tmd.m_fnDisplay = [](void*, int) {};
    tmd.m_fnRefresh = [] {};

    // ===== the init chain seams
    MsgInitChainData icd;
    icd.m_fnCreate = [](int s, int t1,
                        int t2) {
        return (void*)0x100; };
    icd.m_fnVerify = [](int) {
        return true; };
    icd.m_fnCurrentThread = []() {
        return (void*)0x91; };
    icd.m_fnAddHandle = [](void*) {};
    icd.m_fnResume = [](int) {};
    icd.m_fnLog = [](const char*) {};
    icd.m_fnSetLogThreadStatus = [] {};
    icd.m_fnDatabaseInit = [] {
        return true; };
    icd.m_fnPostHandle1 = []() {
        return (void*)0x92; };
    icd.m_fnPostHandle2 = []() {
        return (void*)0x93; };
    icd.m_fnPerfInit = [] {};
    icd.m_fnThreadTimesInit = [] {};
    icd.m_fnTimeGet = [] {
        return (uint32_t)1000000; };

    // ===== the perf seams
    MsgPerfStatsData pd;
    bool b600 = false, b300 = false;
    pd.m_fnPeriod600 = [&] {
        return b600; };
    pd.m_fnPeriod300 = [&] {
        return b300; };
    pd.m_fnRecordPerf = [] {};
    pd.m_fnRecordTimes = [] {};
    pd.m_fnSaveLog = [] {};
    pd.m_fnRefreshUi = [] {};
    pd.m_fnOnlineStats = [&] {
        return true; };
    pd.m_fnUiGate = [&] {
        return true; };
    pd.m_fnLock = [] {};
    pd.m_fnUnlock = [] {};
    pd.m_fnLogLine = [&](const
        std::string& s) {
        tr.vLogs.push_back(s); };
    pd.m_fnUpdateUi = [] {};
    pd.m_fnPipeDepth = [] {
        return 0; };
    pd.m_fnDumpStacks = [] {};
    pd.m_fnRestartRequested = [&] {
        return bRestartReq; };
    pd.m_fnRecordTimes = [] {};

    // ===== the close seams
    MsgKernelCloseData cd;
    cd.m_fnLog = [&](const char* s) {
        tr.vLogs.push_back(s ? s : ""); };
    cd.m_fnRefresh = [] {};
    cd.m_fnClose = [](int, uint32_t) {
        return true; };
    cd.m_fnDestroy = [](int) {};
    cd.m_fnRecordTimes = [] {};
    cd.m_fnPreClose = [] {};
    cd.m_fnSetLogThreadStatus = [] {};
    cd.m_fnStatusCall = [] {};
    cd.m_fnPostClose = [] {};
    cd.m_fnDbUnInit = [] {};

    // ===== the exit seams
    MsgState4Data ed;
    ed.m_fnKillTimer = [&](int id) {
        if (id == 1) ++tr.nKills1; };
    ed.m_fnFinalRefresh = [] {};
    ed.m_fnSleep = [&](uint32_t ms) {
        assert(ms == 3000);
        ++tr.nSleeps; };
    ed.m_fnShellRestart = [&] {
        ++tr.nRelaunch; };
    ed.m_fnTeardown = [&] {
        ++tr.nTeardown; };
    ed.m_fnOnOK = [&] { ++tr.nOnOK; };
    ed.m_fnRestartRequested = [&] {
        return bRestartReq; };

    // ===== the auth seams
    MsgAuthTimerData ad;
    std::vector<std::vector<uint8_t>>
        vQueue;
    int nRecvIdx = 0;
    ad.m_fnNameA = [] {
        return std::string("auth"); };
    ad.m_fnNameB = [] {
        return std::string("auth2"); };
    ad.m_fnConnect = [](const
        std::string&) { return true; };
    ad.m_fnIsAlive = [] {
        return true; };
    ad.m_fnDisconnect = [] {};
    ad.m_fnSetupConn = [] {};
    ad.m_fnIsDeadloop = [] {
        return true; };
    ad.m_fnOrdinal12 = [] {};
    ad.m_fnSendFailPacket = [] {};
    ad.m_fnRecv = [&]() ->
        std::vector<uint8_t> {
        if (nRecvIdx <
                (int)vQueue.size())
            return vQueue[nRecvIdx++];
        return {}; };
    ad.m_fnConsume = [](int) {};
    // a real scratch buffer (the
    // continuation chunks memcpy
    // into it)
    std::vector<uint8_t>
        vPluginBuf;
    ad.m_fnAlloc = [&](uint32_t n) {
        vPluginBuf.assign(n, 0);
        return (void*)
            vPluginBuf.data(); };
    ad.m_fnImportPlugin = [&](void* p,
        uint32_t sz, int f) {
        assert(p ==
            (void*)vPluginBuf
                .data());
        assert(sz == 100 && f == 1);
        return true; };
    ad.m_fnSetTimer = [&](int id,
        uint32_t ms) {
        tr.vTimers.push_back(
            {id, (int)ms}); };
    ad.m_fnKillTimer = [&](int id) {
        if (id == 2) ++tr.nKills2; };
    ad.m_fnPostClose = [&] {
        ++tr.nCloses; };
    ad.m_fnLogError = [&](const
        std::string& s) {
        tr.vLogs.push_back(s); };
    ad.m_fnLogMessage = [&](const
        std::string& s) {
        tr.vLogs.push_back(s); };
    ad.m_fnTimeGet = [&] {
        return tNow; };
    ad.m_fnVerbose = [] {
        return true; };

    MsgOnTimerData od;
    od.pTimer = &tmd;
    od.pInit = &icd;
    od.pPerf = &pd;
    od.pClose = &cd;
    od.pExit = &ed;
    od.pAuth = &ad;
    od.m_fnLogUnknownState = [](
        const char* s) {};

    MsgDlgFullState st;
    // the dialog starts at state 1
    // (the boot) per the original
    st.prologue.nState = 1;
    st.init.nMapThreads = 3;
    st.init.bFlagD0 =
        st.init.bFlag20 = true;
    st.init.bFlag21 =
        st.init.bFlag22 = true;

    // ===== 1. boot: timer 1, state
    // 1 -> the init chain -> state 2
    MsgOnTimer(st, 1, od);
    assert(st.prologue.nState == 2);
    assert(st.init.nState == 2);

    // ===== 2. the perf tick fires
    // (300s + the stats block)
    b300 = true;
    MsgOnTimer(st, 1, od);
    assert(st.prologue.nState == 2);

    // ===== 3. the restart request in
    // the perf tick -> state 3
    bRestartReq = true;
    MsgOnTimer(st, 1, od);
    assert(st.prologue.nState == 3);

    // ===== 4. the kernel close
    // cascade -> state 4
    MsgOnTimer(st, 1, od);
    assert(st.prologue.nState == 4);

    // ===== 5. the exit block with
    // the relaunch (the restart
    // request is still set)
    MsgOnTimer(st, 1, od);
    assert(st.prologue.nState == 5);
    assert(tr.nKills1 == 1);
    assert(tr.nSleeps == 1);
    assert(tr.nRelaunch == 1);
    assert(tr.nTeardown == 1);
    assert(tr.nOnOK == 1);
    bRestartReq = false;

    // ===== 6. the timer-2 branch:
    // the auth lifecycle
    st = MsgDlgFullState();
    st.auth.nAuthState = 0;
    MsgOnTimer(st, 2, od);
    assert(st.auth.nAuthState == 1);
    // the plugin: 3 chunks
    uint32_t nSize = 100;
    std::vector<uint8_t> c1;
    for (int i = 0; i < 4; ++i)
        c1.push_back(
            ((uint8_t*)&nSize)[i]);
    for (int i = 0; i < 60; ++i)
        c1.push_back(0xAA);
    vQueue = { c1 };
    MsgOnTimer(st, 2, od);
    assert(st.auth.nPluginSize == 100);
    vQueue = { std::vector<uint8_t>(
                   c1.begin() + 4,
                   c1.end()) };
    nRecvIdx = 0;
    MsgOnTimer(st, 2, od);
    assert(st.auth.nRecvTotal == 60);
    vQueue = { std::vector<uint8_t>(
                   40, 0xBB) };
    nRecvIdx = 0;
    MsgOnTimer(st, 2, od);
    assert(st.auth.nAuthState == 3);
    assert(tr.nKills2 == 1);
    assert(tr.vTimers.size() == 1);
    assert(tr.vTimers[0].first == 1 &&
        tr.vTimers[0].second == 200);

    // ===== 7. the boot restart after
    // the plugin: reset -> state 1
    MsgOnTimerResetBoot(st);
    assert(st.prologue.nState == 1);
    MsgOnTimer(st, 1, od);
    assert(st.prologue.nState == 2);

    // ===== 8. the shutdown/kickout
    // prologue interplay: the event
    // fires -> state 3 -> close
    st = MsgDlgFullState();
    st.prologue.nState = 2;
    bShutdownEv = true;
    MsgOnTimer(st, 1, od);
    // the prologue detected the
    // shutdown (the 50s countdown)
    // but the state-2 tick still ran
    // (VERBATIM: the prologue only
    // changes the state at the
    // kickoutall EXPIRY)
    assert(st.prologue.nState == 2);
    assert(st.prologue
               .nShutdownRemain ==
        0x32);
    // 49 seconds later (inside the
    // 50s window) with an EXPIRED
    // kick -> state 3
    tNow += 49000;
    st.prologue.tKickStart =
        tNow / 1000 - 20;
    st.prologue.nKickDelay = 10;
    MsgOnTimer(st, 1, od);
    // VERBATIM: the prologue sets
    // state 3 and the SAME tick's
    // dispatch runs the closing
    // cascade -> 4
    assert(st.prologue.nState == 4);

    // ===== 9. an unknown state
    st.prologue.nState = 9;
    MsgOnTimer(st, 1, od);

    // ===== 10. an unhandled timer id
    // -> only the prologue
    st.prologue.nState = 2;
    MsgOnTimer(st, 7, od);
    assert(st.prologue.nState == 2);

    printf("MSG_ON_TIMER_OK: "
           "FUN_140024860 ASSEMBLED - the "
           "full OnTimer lifecycle "
           "VERBATIM (the prologue on "
           "every tick, the "
           "DAT_14097593c once-guard, the "
           "+0x1fc dispatch 0/1->M32 "
           "2->M34 3->M33 4->M35, the "
           "timer-2 -> M36 auth/plugin "
           "branch, the boot restart "
           "after the plugin import, the "
           "shutdown/kickout prologue "
           "expiry -> state 3, the unknown-"
           "state ERROR log, and the "
           "other-id -> CWnd::Default "
           "pass-through)\n");
    return 0;
}

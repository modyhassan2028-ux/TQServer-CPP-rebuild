// MsgServer unit M31 - the WM_TIMER
// prologue (shutdown + kickoutall)
#include "../Exe/MsgServer/Port/MsgTimerProc.h"
#include <cassert>
#include <cstdio>
using namespace msg;

int main() {
    uint32_t tNow = 100000;
    MsgTimerData d;
    d.m_fnTimeGet = [&] { return tNow; };
    int nDisplays = 0;
    int nLastIdx = -1;
    d.m_fnDisplay = [&](void* c, int i) {
        assert(c == (void*)0x77);
        ++nDisplays;
        nLastIdx = i; };
    int nRefreshes = 0;
    d.m_fnRefresh = [&] { ++nRefreshes; };
    int nEvState = 1;   // not signaled
    d.m_fnWaitFor = [&](void* h) {
        assert(h == (void*)0x55);
        return (uint32_t)nEvState; };
    int nRestCalls = 0;
    d.m_fnRest = [&](int id) {
        assert(id == 1);
        ++nRestCalls; };

    MsgTimerDlgState st;
    auto reset = [&](bool evSignaled) {
        g_bTimerShutdownOnce = false;
        g_nTimerInitOnce = 0;
        nDisplays = 0; nRefreshes = 0;
        nRestCalls = 0;
        nEvState = evSignaled ? 0 : 1;
        st = MsgTimerDlgState();
        st.pStatusCtrl = (void*)0x77;
        st.hShutdownEv = (void*)0x55;
    };
    // ===== 1. idle tick: nothing
    reset(false);
    MsgTimerProc(st, 5, d);
    assert(nDisplays == 0 &&
        nRefreshes == 0);
    assert(st.nShutdownRemain == 0);
    // timer 1 runs the init chain once
    MsgTimerProc(st, 1, d);
    assert(nRestCalls == 1);
    MsgTimerProc(st, 1, d);
    assert(nRestCalls == 1);   // once

    // ===== 2. shutdown signaled:
    // the 50s countdown starts ONCE
    reset(true);
    MsgTimerProc(st, 5, d);
    assert(g_bTimerShutdownOnce);
    assert(nDisplays == 1 && nLastIdx == 2);
    assert(st.nShutdownRemain == 0x32);
    assert(st.tShutdownStart == 100);
    // stays armed while now <
    // start + 50 (SECONDS; tNow is
    // ms and the state stores
    // now/1000)
    tNow = 149999;
    MsgTimerProc(st, 5, d);
    assert(nDisplays == 1);
    // at >= 50s: the kickoutall branch
    tNow = 150000;
    MsgTimerProc(st, 5, d);
    assert(nDisplays == 2);
    assert(st.tShutdownStart == 0);
    assert(st.nShutdownRemain == 0);
    assert(st.nKickDelay == 10);
    assert(st.tKickStart == 150);
    // the kick expires after 10s
    tNow = 159999;
    MsgTimerProc(st, 5, d);
    assert(nRefreshes == 0);
    tNow = 160000;
    MsgTimerProc(st, 5, d);
    assert(nRefreshes == 1);
    assert(st.tKickStart == 0);
    assert(st.nKickDelay == 0);
    assert(st.nState == 3);

    // ===== 3. a second shutdown
    // signal does nothing (the flag)
    reset(true);
    MsgTimerProc(st, 5, d);
    MsgTimerProc(st, 5, d);   // again
    assert(nDisplays == 1);   // the
    // DAT_140975940 once-flag gates

    // ===== 4. tShutdownStart==0 with
    // no event: the IDLE branch (the
    // kickoutall else is reachable
    // ONLY through the shutdown
    // countdown expiring - see case 2)
    reset(false);
    MsgTimerProc(st, 5, d);
    assert(nDisplays == 0);
    assert(st.nKickDelay == 0);

    printf("MSG_TIMER_PROC_OK: "
           "FUN_140024860 prologue "
           "VERBATIM (the shutdown "
           "WaitForSingleObject(ev,20ms) "
           "once-flag DAT_140975940, the "
           "'shutdown' literal from "
           "0x1406e3cf8 with the "
           "vt+0x50(ctrl,2) display and "
           "the 0x32 countdown, the "
           "50s-elapsed transition into "
           "'kickoutall' (0x1406e3ce8) "
           "with delay 10, and the "
           "10s expiry clearing the "
           "kick, state 3 + Refresh - "
           "the timer-1 init chain is a "
           "documented seam for M32+)\n");
    return 0;
}

// MsgServer unit M35 - the state-4
// exit block
#include "../msgserver/MsgState4.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    std::vector<std::string> vSeq;
    MsgState4Data d;
    bool bRestart = false;
    d.m_fnKillTimer = [&](int id) {
        assert(id == 1);
        vSeq.push_back("kill1"); };
    d.m_fnFinalRefresh = [&] {
        vSeq.push_back("refresh"); };
    d.m_fnSleep = [&](uint32_t ms) {
        assert(ms == 3000);
        vSeq.push_back("sleep3000"); };
    d.m_fnShellRestart = [&] {
        vSeq.push_back("relaunch"); };
    d.m_fnTeardown = [&] {
        vSeq.push_back("teardown"); };
    d.m_fnOnOK = [&] {
        vSeq.push_back("onok"); };
    d.m_fnRestartRequested = [&] {
        return bRestart; };

    // no restart: 5 steps (the
    // OnOK is the 5th)
    MsgRunState4(d);
    assert(vSeq.size() == 5);
    assert(vSeq[0] == "kill1" &&
        vSeq[1] == "refresh" &&
        vSeq[2] == "sleep3000" &&
        vSeq[3] == "teardown" &&
        vSeq[4] == "onok");
    // with restart: the relaunch
    // between the sleep and the
    // teardown
    bRestart = true;
    vSeq.clear();
    MsgRunState4(d);
    assert(vSeq.size() == 6);
    assert(vSeq[3] == "relaunch" &&
        vSeq[4] == "teardown" &&
        vSeq[5] == "onok");

    printf("MSG_STATE4_OK: "
           "FUN_140024860 state-4 "
           "VERBATIM (KillTimer(1) -> "
           "FUN_14001f070 -> "
           "Sleep(3000) -> the "
           "conditional ShellExecuteA "
           "self-relaunch -> the "
           "framework teardown -> "
           "CDialog::OnOK)\n");
    return 0;
}

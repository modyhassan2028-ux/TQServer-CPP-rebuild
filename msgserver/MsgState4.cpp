#include "MsgState4.h"

namespace msg {

void MsgRunState4(MsgState4Data& rD) {
    rD.m_fnKillTimer(1);
    rD.m_fnFinalRefresh();
    rD.m_fnSleep(3000);
    if (rD.m_fnRestartRequested()) {
        // ShellExecuteA(NULL path =
        // the module exe) - the
        // self-relaunch
        rD.m_fnShellRestart();
    }
    rD.m_fnTeardown();
    rD.m_fnOnOK();
}

} // namespace msg

// ============================================================
// MsgServer strict port - unit M35
// The state-4 exit block of
// FUN_140024860 (lines
// ~30387-30410):
//  - KillTimer(dlg+0x40, 1)
//  - FUN_14001f070(dlg)
//  - Sleep(3000)
//  - if DAT_1409758f0 (the restart
//    request): ShellExecuteA(hwnd,
//    NULL, AfxGetModuleState()+0x20
//    (the exe path), NULL, NULL,
//    SW_SHOWNORMAL=1)
//  - FUN_140028960/14002ad90/
//    1400018c0/1400029f0 (the
//    framework teardown)
//  - CDialog::OnOK(dlg)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgState4Data {
    std::function<void(int id)>
        m_fnKillTimer;
    std::function<void()>
        m_fnFinalRefresh;   // f070
    std::function<void(uint32_t ms)>
        m_fnSleep;
    std::function<void()>
        m_fnShellRestart;   // the
                            // exe relaunch
    std::function<void()>
        m_fnTeardown;   // the 4
                        // cleanup calls
    std::function<void()>
        m_fnOnOK;
    std::function<bool()>
        m_fnRestartRequested;
};

void MsgRunState4(MsgState4Data& rD);

} // namespace msg

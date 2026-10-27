// ============================================================
// MsgServer strict port - unit M31
// The CMsgServerDlg WM_TIMER prologue
// (FUN_140024860, lines 29534-29641):
// the shutdown-event detection and
// the kickoutall countdown.
//  - DAT_140975940: the once-flag of
//    the shutdown sequence
//  - dlg+0x208: the shutdown event
//    handle; WaitForSingleObject(ev,
//    0x14 = 20ms) == 0 (signaled)
//  - "shutdown" (0x1406e3cf8) copied
//    into the 1024-byte local buffer
//  - the status display: vt+0x50(
//    dlg+0x1f0, 2)
//  - dlg+0x210 = 0x32 (the 50s
//    countdown), dlg+0x214 = now/1000
//  - the kickoutall branch:
//    "kickoutall" (0x1406e3ce8),
//    dlg+0x218 = 10, dlg+0x21c =
//    now/1000
//  - the expire check: dlg+0x21c &&
//    dlg+0x21c + dlg+0x218 <= now/1000
//    -> clear both, dlg+0x1fc = 3,
//    the dialog Refresh (FUN_14001e540)
// The init chain (timer 1) and the
// other states remain for M32+.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

// the dialog state the prologue
// touches (offsets verbatim)
struct MsgTimerDlgState {
    void* pStatusCtrl;   // +0x1f0
    void* hShutdownEv;   // +0x208
    uint32_t nShutdownRemain;   // +0x210
    uint32_t tShutdownStart;    // +0x214
    uint32_t nKickDelay; // +0x218
    uint32_t tKickStart; // +0x21c
    uint32_t nState;     // +0x1fc
};

struct MsgTimerData {
    std::function<uint32_t(void* hEv)>
        m_fnWaitFor;   // returns 0 when
                       // signaled
    std::function<uint32_t()>
        m_fnTimeGet;   // ms
    std::function<void(void* ctrl,
                       int idx)>
        m_fnDisplay;   // vt+0x50
    std::function<void()>
        m_fnRefresh;   // FUN_14001e540
    std::function<void(int nTimerId)>
        m_fnRest;      // the timer-1
                       // init chain etc
                       // (M32+)
};

// DAT_140975940
extern bool g_bTimerShutdownOnce;
// DAT_14097593c
extern int g_nTimerInitOnce;

// the prologue (runs for EVERY timer
// tick, before the timer dispatch)
void MsgTimerPrologue(MsgTimerDlgState& st,
                      MsgTimerData& rD);
// the full dispatch: the prologue +
// the timer-id switch
void MsgTimerProc(MsgTimerDlgState& st,
                  int nTimerId,
                  MsgTimerData& rD);

} // namespace msg

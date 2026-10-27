// ============================================================
// MsgServer strict port - unit M37
// The ASSEMBLY of FUN_140024860:
// the complete CMsgServerDlg::
// OnTimer with all branches wired:
//  - the prologue (M31) on every
//    tick (the shutdown event + the
//    kickoutall countdown)
//  - timer 1 under the once-guard
//    DAT_14097593c, dispatched on
//    dlg+0x1fc:
//      0 -> (return: nothing runs)
//      1 -> the init chain (M32)
//      2 -> the perf/stats tick
//           (M34)
//      3 -> the Kernel closing
//           cascade (M33)
//      4 -> the exit block (M35)
//      other -> the ERROR log
//  - timer 2 -> the authserver
//    branch (M36)
//  - other ids -> CWnd::Default
// The single source of truth for
// +0x1fc is MsgDlgFullState::
// prologue.nState; the sub-units'
// own nState fields are synced
// around each call.
// ============================================================
#pragma once
#include "MsgTimerProc.h"
#include "MsgInitChain.h"
#include "MsgPerfStats.h"
#include "MsgKernelClose.h"
#include "MsgState4.h"
#include "MsgAuthTimer.h"

namespace msg {

struct MsgDlgFullState {
    MsgTimerDlgState prologue;
    MsgInitChainState init;
    MsgPerfStatsState perf;
    MsgKernelCloseState close;
    MsgAuthTimerState auth;
};

// non-owning bundle of the sub-unit
// seam sets (the caller fills them;
// several may share lambdas)
struct MsgOnTimerData {
    MsgTimerData* pTimer;
    MsgInitChainData* pInit;
    MsgPerfStatsData* pPerf;
    MsgKernelCloseData* pClose;
    MsgState4Data* pExit;
    MsgAuthTimerData* pAuth;
    std::function<void(const char* s)>
        m_fnLogUnknownState;
};

// the full dispatch
void MsgOnTimer(MsgDlgFullState& st,
                int nTimerId,
                MsgOnTimerData& rD);

// after the plugin import succeeds
// the dialog restarts the boot: the
// once-flag drops and the state goes
// back to 1 (the original SetTimer
// (1,200) + the fresh boot)
void MsgOnTimerResetBoot(
    MsgDlgFullState& st);

} // namespace msg

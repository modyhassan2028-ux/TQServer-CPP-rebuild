#include "MsgOnTimer.h"

namespace msg {

void MsgOnTimerResetBoot(
    MsgDlgFullState& st) {
    g_nTimerInitOnce = 0;
    st.prologue.nState = 1;
}

void MsgOnTimer(MsgDlgFullState& st,
                int nTimerId,
                MsgOnTimerData& rD) {
    // ===== the prologue (M31)
    MsgTimerPrologue(st.prologue,
                     *rD.pTimer);
    if (nTimerId == 1) {
        // the once-guard
        // (DAT_14097593c)
        if (0 < g_nTimerInitOnce)
            return;
        ++g_nTimerInitOnce;
        uint32_t nState =
            st.prologue.nState;
        switch (nState) {
        case 0:
            // the original returns
            // without touching
            // anything
            break;
        case 1:
            st.init.nState = 1;
            if (MsgTimerInitChain(
                    st.init,
                    *rD.pInit)) {
                st.prologue.nState =
                    st.init.nState;
            } else {
                st.prologue.nState =
                    st.init.nState;
            }
            break;
        case 2:
            st.perf.nState = 2;
            MsgPerfStatsTick(
                st.perf, *rD.pPerf);
            if (st.perf.nState != 2)
                st.prologue.nState =
                    st.perf.nState;
            break;
        case 3:
            st.close.nState = 3;
            MsgKernelClose(st.close,
                           *rD.pClose);
            st.prologue.nState =
                st.close.nState;
            break;
        case 4:
            MsgRunState4(*rD.pExit);
            st.prologue.nState = 5;
            break;
        default:
            if (rD.m_fnLogUnknownState)
                rD.m_fnLogUnknownState(
                    "unknown state");
            break;
        }
        // LAB_140026533: the once-flag
        // decrement
        --g_nTimerInitOnce;
    } else if (nTimerId == 2) {
        MsgAuthTimerTick(st.auth,
                         *rD.pAuth);
    }
    // other ids -> CWnd::Default (no
    // state work; the prologue above
    // still ran - VERBATIM: the
    // original runs the prologue for
    // every WM_TIMER)
}

} // namespace msg

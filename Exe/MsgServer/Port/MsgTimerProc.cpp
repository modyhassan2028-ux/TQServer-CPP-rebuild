#include "MsgTimerProc.h"
#include <cstring>

namespace msg {

bool g_bTimerShutdownOnce = false
    ; // DAT_140975940
int g_nTimerInitOnce = 0;   // DAT_14097593c

static void copy9(unsigned char* dst,
                  const char* s) {
    // the Ghidra partial-init idiom:
    // 8 bytes + the 9th (the NUL of
    // "shutdown") / 11 for "kickoutall"
    std::memcpy(dst, s,
        std::strlen(s) + 1);
}

void MsgTimerPrologue(MsgTimerDlgState& st,
                      MsgTimerData& rD) {
    if (!g_bTimerShutdownOnce &&
        rD.m_fnWaitFor(st.hShutdownEv)
            == 0) {
        g_bTimerShutdownOnce = true;
        unsigned char buf[0x448];
        copy9(buf, "shutdown");   // 1406e3cf8
        // the VERBATIM strlen loop
        // over the buffer elided by
        // the compiler is preserved
        // by the copy above
        rD.m_fnDisplay(st.pStatusCtrl,
            2);   // vt+0x50(this, 2)
        st.nShutdownRemain = 0x32;
        st.tShutdownStart =
            rD.m_fnTimeGet() / 1000;
    } else if (st.tShutdownStart == 0 ||
        rD.m_fnTimeGet() / 1000 <
            st.nShutdownRemain +
                st.tShutdownStart) {
        // the kickoutall expiry
        if (st.tKickStart != 0 &&
            st.tKickStart +
                    st.nKickDelay <=
                rD.m_fnTimeGet() /
                    1000) {
            st.tKickStart = 0;
            st.nKickDelay = 0;
            st.nState = 3;
            rD.m_fnRefresh();
        }
    } else {
        st.tShutdownStart = 0;
        st.nShutdownRemain = 0;
        unsigned char buf[0x448];
        copy9(buf, "kickoutall");  // 1406e3ce8
        rD.m_fnDisplay(st.pStatusCtrl,
            2);
        st.nKickDelay = 10;
        st.tKickStart =
            rD.m_fnTimeGet() / 1000;
    }
}

void MsgTimerProc(MsgTimerDlgState& st,
                  int nTimerId,
                  MsgTimerData& rD) {
    MsgTimerPrologue(st, rD);
    if (nTimerId == 1) {
        if (0 < g_nTimerInitOnce)
            return;   // LAB_140026a28
        ++g_nTimerInitOnce;
        rD.m_fnRest(nTimerId);   // M32+
    }
}

} // namespace msg

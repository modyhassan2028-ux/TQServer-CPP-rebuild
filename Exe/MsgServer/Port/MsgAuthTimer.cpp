#include "MsgAuthTimer.h"
#include <cstring>

namespace msg {

void MsgAuthTimerTick(MsgAuthTimerState& st,
                      MsgAuthTimerData& rD) {
    if (st.nAuthState == 0) {
        // the two candidate names,
        // each gated by the connect
        // attempt (FUN_140005ea0);
        // 0 -> disconnect and try the
        // next buffer
        st.sName = rD.m_fnNameA();
        if (!rD.m_fnConnect(st.sName)) {
            rD.m_fnDisconnect();
            st.sName = rD.m_fnNameB();
            if (!rD.m_fnConnect(
                    st.sName)) {
                rD.m_fnDisconnect();
            }
        }
        if (!rD.m_fnIsAlive()) {
            if (rD.m_fnVerbose())
                rD.m_fnLogError(
                    "reconnect authserver("
                    + st.sName +
                    ") failed.");
        } else {
            st.nAuthState = 1;
            rD.m_fnSetupConn();
            if (rD.m_fnVerbose())
                rD.m_fnLogMessage(
                    "reconnect authserver("
                    + st.sName +
                    ") success.");
        }
    } else if (st.nAuthState == 1) {
        if (!rD.m_fnIsAlive()) {
            // ===== the fail path:
            // the "IP:%s VERSION:%s"
            // packet with the DEADLOOP
            // header check
            if (rD.m_fnIsDeadloop()) {
                // the raw sprintf with
                // the deadloop globals
                rD.m_fnSendFailPacket();
            } else {
                rD.m_fnOrdinal12();
                rD.m_fnSendFailPacket();
            }
            // the <0xfe length gate
            // (the strlen loop in the
            // original is elided - the
            // packet is sent only via
            // a fresh connect check)
            if (rD.m_fnConnect(st.sName)) {
                rD.m_fnSendFailPacket();
                rD.m_fnDisconnect();
            }
            if (rD.m_fnVerbose())
                rD.m_fnLogError(
                    "authentication("
                    + st.sName +
                    ") faild.");
            st.nAuthState = 3;
            rD.m_fnKillTimer(2);
            rD.m_fnPostClose();
        } else {
            // ===== the recv path
            auto v = rD.m_fnRecv();
            if (!v.empty()) {
                if (st.pPlugin ==
                    nullptr) {
                    // the first chunk must
                    // carry the 4-byte size
                    if (3 < (int)v.size()) {
                        std::memcpy(
                            &st.nPluginSize,
                            v.data(), 4);
                        st.pPlugin =
                            rD.m_fnAlloc(
                                st
                                .nPluginSize);
                        rD.m_fnConsume(4);
                        st.nRecvTotal = 0;
                    }
                } else {
                    // a continuation chunk
                    std::memcpy(
                        (uint8_t*)st
                            .pPlugin +
                        st.nRecvTotal,
                        v.data(),
                        v.size());
                    st.nRecvTotal +=
                        (uint32_t)v
                        .size();
                    rD.m_fnConsume(
                        (int)v.size());
                }
            }
            // ===== the completion
            if (st.pPlugin != nullptr &&
                st.nPluginSize <=
                    st.nRecvTotal) {
                st.nRecvTotal = 0;
                rD.m_fnDisconnect();
                st.nAuthState = 3;
                rD.m_fnKillTimer(2);
                if (rD.m_fnImportPlugin(
                        st.pPlugin,
                        st.nPluginSize,
                        1)) {
                    st.tTimeoutStart
                        = 0;
                    st.nTimeoutDelay
                        = 0;
                    rD.m_fnSetTimer(1,
                        200);
                    if (rD.m_fnVerbose())
                        rD.m_fnLogMessage(
                            "authentication("
                            + st.sName +
                            ") success.");
                } else {
                    rD.m_fnLogError(
                        "import function "
                        "failed at "
                        "f:\\version\\"
                        "cqserver-78.0.11"
                        "-1204\\msgserver\\"
                        "msgserverdlg.cpp");
                    rD.m_fnPostClose();
                }
            }
        }
    }
    // ===== the auth timeout
    if (st.nTimeoutDelay != 0 &&
        st.tTimeoutStart +
                st.nTimeoutDelay <=
            rD.m_fnTimeGet() / 1000) {
        st.nTimeoutDelay = 0;
        st.tTimeoutStart = 0;
        rD.m_fnKillTimer(2);
        rD.m_fnPostClose();
    }
}

} // namespace msg

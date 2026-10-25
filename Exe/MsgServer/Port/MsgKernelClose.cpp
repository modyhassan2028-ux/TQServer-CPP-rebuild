#include "MsgKernelClose.h"

namespace msg {

static void wave2One(MsgKernelCloseState& st,
                     MsgKernelCloseData& rD,
                     int nSlot, uint32_t ms,
                     const char* sOk,
                     const char* sFail) {
    if (st.pTh[nSlot] == nullptr)
        return;
    bool b = rD.m_fnClose(nSlot, ms);
    rD.m_fnLog(b ? sOk : sFail);
    if (st.pTh[nSlot] != nullptr) {
        rD.m_fnDestroy(nSlot);
        st.pTh[nSlot] = nullptr;
    }
    rD.m_fnRefresh();
}

void MsgKernelClose(MsgKernelCloseState& st,
                    MsgKernelCloseData& rD) {
    rD.m_fnLog("Kernel closing...");
    rD.m_fnRecordTimes();
    rD.m_fnPreClose();

    // ===== WAVE 1 (no messages)
    if (st.pTh[KC_228] != nullptr)
        rD.m_fnClose(KC_228, 2000);
    if (st.pTh[KC_230] != nullptr)
        rD.m_fnClose(KC_230, 3000);
    if (st.pTh[KC_238] != nullptr)
        rD.m_fnClose(KC_238, 4000);
    if (st.pTh[KC_1B8] != nullptr)
        rD.m_fnClose(KC_1B8, 10000);
    if (st.pTh[KC_1C8] != nullptr)
        rD.m_fnClose(KC_1C8, 120000);
    if (st.pTh[KC_1E0] != nullptr)
        rD.m_fnClose(KC_1E0, 3000);
    for (auto p : st.vMapThreads)
        rD.m_fnClose(-1, 60000);
    if (st.pTh[KC_1D8] != nullptr)
        rD.m_fnClose(KC_1D8, 8000);
    if (st.pTh[KC_1C0] != nullptr)
        rD.m_fnClose(KC_1C0, 4000);

    // ===== WAVE 2 (close + destroy)
    // NOTE: the 228/230/238/1b8/1c8
    // ok/fail literals are dropped by
    // Ghidra (both branches call the
    // log with an omitted arg) - we
    // log empty strings per branch
    wave2One(st, rD, KC_228, 60000,
        "", "");
    wave2One(st, rD, KC_230, 60000,
        "", "");
    wave2One(st, rD, KC_238, 60000,
        "", "");
    wave2One(st, rD, KC_1B8, 60000,
        "", "");
    wave2One(st, rD, KC_1C8, 60000,
        "", "");
    // the map loop
    for (size_t i = 0; i <
             st.vMapThreads.size();
         ++i) {
        bool b = rD.m_fnClose(
            (int)i - 1000, 300000);
        rD.m_fnLog(b
            ? "Close map group thread[%d] OK\xa1\xa3"
            : "Close map group thread[%d] failed!");
        if (st.vMapThreads[i] !=
            nullptr) {
            rD.m_fnDestroy(
                (int)i - 1000);
            st.vMapThreads[i] =
                nullptr;
        }
        rD.m_fnRefresh();
    }
    wave2One(st, rD, KC_1D8, 60000,
        "Close cross client OK\xa1\xa3",
        "Close cross client failed!");
    wave2One(st, rD, KC_1C0, 60000,
        "Close world thread OK\xa1\xa3",
        "Close world thread failed!");
    wave2One(st, rD, KC_1E8, 60000,
        "Close Chat Thread OK.",
        "Close Chat Thread Failed.");
    wave2One(st, rD, KC_1E0, 60000,
        "Close Auction Search Thread OK.",
        "Close Auction Search Thread Failed.");
    wave2One(st, rD, KC_180, 60000,
        "Close async DB thread OK.",
        "Close async DB thread failed.");
    rD.m_fnSetLogThreadStatus();
    wave2One(st, rD, KC_178, 60000,
        "Close Log thread OK.",
        "Close Log thread failed.");

    // ===== the tail
    rD.m_fnLog(nullptr);
    rD.m_fnRefresh();
    rD.m_fnStatusCall();
    rD.m_fnPostClose();
    st.pStatusCtrl = nullptr;
    rD.m_fnDbUnInit();
    st.nState = 4;
}

} // namespace msg

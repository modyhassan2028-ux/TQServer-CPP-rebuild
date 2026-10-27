#include "MsgPerfStats.h"
#include <cstdio>

namespace msg {

std::string MsgPerfBanner(
    const std::string& sTop,
    const std::string& sBottom) {
    static const char* kBar =
        "--------------------------------"
        "---------------\n";
    return std::string(kBar) + sTop +
        sBottom + kBar;
}

bool MsgCcuDrifted(uint32_t nCur,
                   uint32_t nMax) {
    // the VERBATIM window
    // (a-b < 10) && (-10 < a-b) -
    // a signed comparison (the -10
    // literal is meaningless unsigned)
    int nDiff = (int)(nCur - nMax);
    if (nDiff < 10 && -10 < nDiff) {
        if (nMax == 0) {
            if (nCur != 0)
                return true;   // LOG
        } else if (nCur == 0)
            return true;      // LOG
        return false;
    }
    return true;
}

bool MsgOscDrifted(uint32_t nCur,
                   uint32_t nMax) {
    // the VERBATIM abs trick:
    // uVar19 = (a-b) >> 0x1f;
    // (int)((a-b ^ uVar19) - uVar19)
    //   < 10
    uint32_t uD = nCur - nMax;
    uint32_t uS = uD >> 0x1f;
    if ((int)((uD ^ uS) - uS) < 10) {
        if (nMax == 0) {
            if (nCur != 0)
                return true;   // LOG
        } else if (nCur == 0)
            return true;      // LOG
        return false;
    }
    return true;
}

void MsgPerfStatsTick(
    MsgPerfStatsState& st,
    MsgPerfStatsData& rD) {
    // ===== the 600s period
    if (rD.m_fnPeriod600()) {
        rD.m_fnRecordPerf();
        rD.m_fnRecordTimes();
        rD.m_fnSaveLog();
    }
    // ===== the 300s period
    if (rD.m_fnPeriod300()) {
        rD.m_fnRefreshUi();
        if (rD.m_fnOnlineStats()) {
            // the 8 zeroings
            uint32_t* p8[8] = {
                &st.c.n6f8, &st.c.n6fc,
                &st.c.n714, &st.c.n718,
                &st.c.n730, &st.c.n734,
                &st.c.n744, &st.c.n740 };
            for (auto p : p8) {
                rD.m_fnLock();
                *p = 0;
                rD.m_fnUnlock();
            }
            // the banner
            rD.m_fnLogLine(
                MsgPerfBanner(
                    "TOP", "BOTTOM"));
            // the socket stats line
            // (the VERBATIM format)
            char tmp[1024];
            std::snprintf(tmp,
                sizeof(tmp),
                "\n-----------------------------------------------\n"
                "client socket send bytes: %d\n"
                "client socket send Msgs: %d\n"
                "client socket recv bytes: %d\n"
                "client socket recv Msgs: %d\n"
                "-----------------------------\n"
                "Npc socket send bytes: %d\n"
                "Npc socket send Msgs: %d\n"
                "Npc socket recv bytes: %d\n"
                "Npc socket recv Msgs: %d\n"
                "-----------------------------\n"
                "Account socket send bytes: %d\n"
                "Account socket send Msgs: %d\n"
                "Account socket recv bytes: %d\n"
                "Account socket recv Msgs: %d\n"
                "-----------------------------------------------\n",
                st.c.nSock[0],
                st.c.nSock[1],
                st.c.nSock[2],
                st.c.nSock[3],
                st.c.nSock[4],
                st.c.nSock[5],
                st.c.nSock[6],
                st.c.nSock[7],
                st.c.nSock[8],
                st.c.nSock[9],
                st.c.nSock[10],
                st.c.nSock[11]);
            rD.m_fnLogLine(tmp);
            // the 12 zeroings
            for (int i = 0; i < 12;
                 ++i) {
                rD.m_fnLock();
                st.c.nSock[i] = 0;
                rD.m_fnUnlock();
            }
        }
        // ===== the CCU drift checks
        if (MsgCcuDrifted(st.c.nCCU,
                         st.c.nPCU)) {
            char tmp[128];
            std::snprintf(tmp,
                sizeof(tmp),
                "CCU:%d, PCU:%d, login:%d,"
                " logout:%d",
                st.c.nCCU, st.c.nPCU,
                st.c.nLogin,
                st.c.nLogout);
            rD.m_fnLogLine(tmp);
            rD.m_fnLock();
            st.c.nLogin = 0;
            rD.m_fnUnlock();
            rD.m_fnLock();
            st.c.nLogout = 0;
            rD.m_fnUnlock();
            rD.m_fnLock();
            st.c.nPCU = st.c.nCCU;
            rD.m_fnUnlock();
        }
        if (MsgOscDrifted(
                st.c.nFromCur,
                st.c.nFromMax)) {
            char tmp[128];
            std::snprintf(tmp,
                sizeof(tmp),
                "FromOSCCU:%d, PCU:%d,"
                " in:%d, back:%d",
                st.c.nFromCur,
                st.c.nFromMax,
                st.c.nIn,
                st.c.nBack1);
            rD.m_fnLogLine(tmp);
            rD.m_fnLock();
            st.c.nIn = 0;
            rD.m_fnUnlock();
            rD.m_fnLock();
            st.c.nBack1 = 0;
            rD.m_fnUnlock();
            rD.m_fnLock();
            st.c.nFromMax =
                st.c.nFromCur;
            rD.m_fnUnlock();
        }
        if (MsgOscDrifted(
                st.c.nToCur,
                st.c.nToMax)) {
            char tmp[128];
            std::snprintf(tmp,
                sizeof(tmp),
                "ToOSCCU:%d, PCU:%d,"
                " out:%d, back:%d",
                st.c.nToCur,
                st.c.nToMax,
                st.c.nOut,
                st.c.nBack2);
            rD.m_fnLogLine(tmp);
            rD.m_fnLock();
            st.c.nOut = 0;
            rD.m_fnUnlock();
            rD.m_fnLock();
            st.c.nBack2 = 0;
            rD.m_fnUnlock();
            rD.m_fnLock();
            st.c.nToMax =
                st.c.nToCur;
            rD.m_fnUnlock();
        }
        // the UI text + online.txt
        // (the second FUN_1400222e0()
        // gate)
        if (rD.m_fnUiGate()) {
            rD.m_fnUpdateUi();
        }
    }
    // ===== the message-pipe block
    int nDepth = rD.m_fnPipeDepth();
    if (10000 < nDepth &&
        nDepth == (nDepth / 1000) *
                      1000) {
        rD.m_fnLogLine(
            "Message pipe block, server"
            " may be slowly!!!");
        rD.m_fnDumpStacks();
    }
    // ===== the restart request
    if (rD.m_fnRestartRequested())
        st.nState = 3;
}

} // namespace msg

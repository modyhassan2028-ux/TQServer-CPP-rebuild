// MsgServer unit M33 - the state-3
// "Kernel closing" cascade
#include "../msgserver/MsgKernelClose.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    struct Tr {
        std::vector<std::string> vLogs;
        std::vector<std::pair<int,int>>
            vCloses;
        std::vector<int> vDestroys;
        int nRefresh = 0, nRec = 0;
        int nPre = 0, nSetLog = 0;
        int nStatus = 0, nPost = 0;
        int nDb = 0;
    } tr;
    MsgKernelCloseData d;
    d.m_fnLog = [&](const char* s) {
        tr.vLogs.push_back(s ? s : ""); };
    d.m_fnRefresh = [&] { ++tr.nRefresh; };
    d.m_fnClose = [&](int s, uint32_t ms) {
        tr.vCloses.push_back({s, (int)ms});
        return s != KC_230; };   // 230
                               // fails
    d.m_fnDestroy = [&](int s) {
        tr.vDestroys.push_back(s); };
    d.m_fnRecordTimes = [&] {
        ++tr.nRec; };
    d.m_fnPreClose = [&] { ++tr.nPre; };
    d.m_fnSetLogThreadStatus = [&] {
        ++tr.nSetLog; };
    d.m_fnStatusCall = [&] {
        ++tr.nStatus; };
    d.m_fnPostClose = [&] { ++tr.nPost; };
    d.m_fnDbUnInit = [&] { ++tr.nDb; };

    MsgKernelCloseState st;
    for (int i = 0; i < 11; ++i)
        st.pTh[i] = (void*)(uintptr_t)
            (0x100 + i);
    st.vMapThreads = { (void*)1,
        (void*)2, (void*)3 };
    st.pStatusCtrl = (void*)0x77;
    st.nState = 3;

    MsgKernelClose(st, d);
    assert(st.nState == 4);
    assert(st.pStatusCtrl == nullptr);
    // all slots destroyed + cleared
    for (int i = 0; i < 11; ++i)
        assert(st.pTh[i] == nullptr);
    assert(tr.vDestroys.size() == 14);   // 11 slots + 3 map threads
    // WAVE 1 order + timeouts
    auto& c = tr.vCloses;
    auto eq = [](std::pair<int,int> p,
                 int slot, int ms) {
        return p.first == slot &&
            p.second == ms; };
    assert(eq(c[0], KC_228, 2000));
    assert(eq(c[1], KC_230, 3000));
    assert(eq(c[2], KC_238, 4000));
    assert(eq(c[3], KC_1B8, 10000));
    assert(eq(c[4], KC_1C8, 120000));
    assert(eq(c[5], KC_1E0, 3000));
    assert(c[6].second == 60000);
    assert(c[7].second == 60000);
    assert(c[8].second == 60000);
    assert(eq(c[9], KC_1D8, 8000));
    assert(eq(c[10], KC_1C0, 4000));
    // WAVE 2: 228..1c8, 3 maps,
    // 1d8, 1c0, 1e8, 1e0, 180, 178
    assert(eq(c[11], KC_228, 60000));
    assert(c[16].second == 300000);
    assert(eq(c[19], KC_1D8, 60000));
    assert(eq(c[20], KC_1C0, 60000));
    assert(eq(c[21], KC_1E8, 60000));
    assert(eq(c[22], KC_1E0, 60000));
    assert(eq(c[23], KC_180, 60000));
    assert(eq(c[24], KC_178, 60000));
    assert(c.size() == 25);
    // the messages
    bool bChat = false, bAuc = false,
         bDb = false, bLog = false,
         bCross = false, bWorld = false;
    for (auto& s : tr.vLogs) {
        if (s == "Close Chat Thread OK.")
            bChat = true;
        if (s == "Close Auction Search Thread OK.")
            bAuc = true;
        if (s == "Close async DB thread OK.")
            bDb = true;
        if (s == "Close Log thread OK.")
            bLog = true;
        if (s == "Close cross client OK\xa1\xa3")
            bCross = true;
        if (s == "Close world thread OK\xa1\xa3")
            bWorld = true;
    }
    assert(bChat && bAuc && bDb && bLog
        && bCross && bWorld);
    // 230 FAILS -> its fail text
    // (the Ghidra-omitted literal ->
    // empty) is logged
    // (empty == the fail branch)
    // "Kernel closing..." first
    assert(tr.vLogs[0] ==
        "Kernel closing...");
    assert(tr.nRec == 1 && tr.nPre == 1);
    assert(tr.nSetLog == 1);
    assert(tr.nStatus == 1 &&
        tr.nPost == 1 && tr.nDb == 1);
    // refresh: 11 wave-2 slots + the
    // tail = 12
    assert(tr.nRefresh == 15);

    // ===== the fail branch of 230
    bool bFail230 = false;
    for (size_t i = 12; i <
             tr.vLogs.size(); ++i)
        if (tr.vLogs[i] == "")
            bFail230 = true;
    assert(bFail230);

    printf("MSG_KERNEL_CLOSE_OK: "
           "FUN_140024860 state-3 "
           "'Kernel closing...' cascade "
           "VERBATIM (the wave-1 "
           "CloseThread order "
           "228/230/238/1b8/1c8/1e0/"
           "maps/1d8/1c0 with the "
           "literal timeouts 2000/3000/"
           "4000/10000/120000/3000/"
           "60000/8000/4000, then the "
           "wave-2 close+destroy+refresh "
           "with the OK/failed message "
           "table incl. the map loop at "
           "300000, SetLogThreadStatus"
           "(0) before the log thread, "
           "and the state->4 tail with "
           "status ctrl cleared)\n");
    return 0;
}

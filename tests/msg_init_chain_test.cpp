// MsgServer unit M32 - the timer-1
// init chain (FUN_140024860 lines
// 29643-29890)
#include "../msgserver/MsgInitChain.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    struct Tracer {
        std::vector<int> vCreates;
        std::vector<int> vResumes;
        std::vector<void*> vHandles;
        std::vector<std::string> vLogs;
        int nDbInit = 0;
        int nSetLog = 0;
        int nPerf = 0, nTimes = 0;
        int nPost1 = 0, nPost2 = 0;
    } tr;
    MsgInitChainData d;
    MsgInitChainState st;
    // the scenario knobs
    bool bSecondMapNull = false;
    bool bLoginOk = false;
    int nCurSlot = -1;
    bool bDbOk = false;
    bool bPost1 = false, bPost2 = false;
    int nFailAt = -1;
    (void)nCurSlot;
    d.m_fnCreate = [&](int s, int t1,
                       int t2) {
        tr.vCreates.push_back(t1 * 100 +
            t2);
        nCurSlot = s;
        if (s == SLOT_MAP0 + 1)
            return bSecondMapNull
                ? nullptr : (void*)s;
        return (void*)(uintptr_t)
            (0x100 + s); };
    d.m_fnVerify = [&](int s) {
        if (s == SLOT_178)
            return bLoginOk;
        // every other slot ok unless
        // it is the fail-at slot
        return s != nFailAt; };
    d.m_fnCurrentThread =
        [] { return (void*)0x1234; };
    d.m_fnAddHandle = [&](void* h) {
        tr.vHandles.push_back(h); };
    d.m_fnResume = [&](int s) {
        tr.vResumes.push_back(s); };
    d.m_fnLog = [&](const char* s) {
        tr.vLogs.push_back(s ? s : ""); };
    d.m_fnSetLogThreadStatus = [&] {
        ++tr.nSetLog; };
    d.m_fnDatabaseInit = [&] {
        ++tr.nDbInit;
        return bDbOk; };
    d.m_fnPostHandle1 = [&] {
        ++tr.nPost1;
        return bPost1 ? (void*)0x91
            : nullptr; };
    d.m_fnPostHandle2 = [&] {
        ++tr.nPost2;
        return bPost2 ? (void*)0x92
            : nullptr; };
    d.m_fnPerfInit = [&] { ++tr.nPerf; };
    d.m_fnThreadTimesInit = [&] {
        ++tr.nTimes; };
    uint32_t tNow = 5000000;
    d.m_fnTimeGet = [&] { return tNow; };

    // ===== 1. state 0 -> 4, nothing
    st.nState = 0;
    assert(MsgTimerInitChain(st, d));
    assert(st.nState == 4);
    assert(tr.vCreates.empty());
    assert(tr.vResumes.empty());

    // ===== 2. the full success path
    st = MsgInitChainState();
    st.nState = 1;
    st.nMapThreads = 3;
    st.bFlagD0 = st.bFlag20 = true;
    st.bFlag21 = st.bFlag22 = true;
    bLoginOk = true; bDbOk = true;
    bPost1 = bPost2 = true;
    nFailAt = -1;
    tr = Tracer();
    assert(MsgTimerInitChain(st, d));
    assert(st.nState == 2);
    // creation order: 178(7), 180,
    // 1c0(2), 1e0(10), maps (0xe,0xf,
    // 0x10), 1c8(4), 1b8(0xe,1),
    // 1d8(6), 1e8(8), 228(9), 238(b),
    // 230(d)
    assert(tr.vCreates.size() == 14);
    assert(tr.vCreates[0] == 700);
    assert(tr.vCreates[1] == 0);
    assert(tr.vCreates[2] == 200);
    assert(tr.vCreates[3] == 1000);
    // map types i+0xe encoded as
    // t1*100+t2 (decimal): 14,15,16
    assert(tr.vCreates[4] == 1400 &&
        tr.vCreates[5] == 1500 &&
        tr.vCreates[6] == 1600);
    assert(tr.vCreates[7] == 400);
    assert(tr.vCreates[8] == 1401);
    assert(tr.vCreates[9] == 600);
    assert(tr.vCreates[10] == 800);
    assert(tr.vCreates[11] == 900);
    assert(tr.vCreates[12] == 1100);
    assert(tr.vCreates[13] == 1300);
    // resumes: 1c0, 1e0, 3 maps, 1b8,
    // 1c8, 1e8, 1d8, 228, 238, 230
    assert(tr.vResumes.size() == 12);
    assert(tr.vResumes[0] == SLOT_1C0);
    assert(tr.vResumes[1] == SLOT_1E0);
    assert(tr.vResumes[2] == SLOT_MAP0);
    assert(tr.vResumes[4] ==
        SLOT_MAP0 + 2);
    assert(tr.vResumes[5] == SLOT_1B8);
    assert(tr.vResumes[6] == SLOT_1C8);
    assert(tr.vResumes[7] == SLOT_1E8);
    assert(tr.vResumes[8] == SLOT_1D8);
    assert(tr.vResumes[9] == SLOT_228);
    assert(tr.vResumes[10] == SLOT_238);
    assert(tr.vResumes[11] == SLOT_230);
    // the handles: current thread +
    // one per slot (14) + the two post
    assert(tr.vHandles.size() == 17);
    assert(tr.vHandles[0] ==
        (void*)0x1234);
    // timers 600/300 at now/1000
    assert(st.nPerf600 == 600 &&
        st.tPerf600 == 5000);
    assert(st.nPerf300 == 300 &&
        st.tPerf300 == 5000);
    assert(tr.nDbInit == 1 &&
        tr.nSetLog == 1);
    assert(tr.nPerf == 1 &&
        tr.nTimes == 1);
    assert(tr.nPost1 == 1 &&
        tr.nPost2 == 1);
    // "Init OK." logged twice
    int nInitOk = 0;
    for (auto& s : tr.vLogs)
        if (s == "Init OK.") ++nInitOk;
    assert(nInitOk == 2);

    // ===== 3. a mid-chain failure
    // (the verify of +0x1c8 fails)
    st = MsgInitChainState();
    st.nState = 1; st.nMapThreads = 2;
    bLoginOk = true; bDbOk = true;
    nFailAt = SLOT_1C8;
    tr = Tracer();
    assert(!MsgTimerInitChain(st, d));
    assert(st.nState == 3);   // stuck
    assert(tr.vResumes.empty());
    assert(st.nPerf600 == 0);
    // nothing after 1c8 was created
    assert(tr.vCreates.size() == 7);

    // ===== 4. DatabaseInit fails
    st = MsgInitChainState();
    st.nState = 1; bLoginOk = true;
    bDbOk = false;
    tr = Tracer();
    assert(!MsgTimerInitChain(st, d));
    assert(st.nState == 3);
    assert(tr.vCreates.size() == 1);

    // ===== 5. the login verify
    // (FUN_14001b1b0) fails
    st = MsgInitChainState();
    st.nState = 1; bLoginOk = false;
    bDbOk = true;
    tr = Tracer();
    assert(!MsgTimerInitChain(st, d));
    assert(tr.nDbInit == 0);

    // ===== 6. a null map thread
    // mid-loop = fail
    st = MsgInitChainState();
    st.nState = 1; st.nMapThreads = 3;
    bLoginOk = true; bDbOk = true;
    bSecondMapNull = true;
    nFailAt = -1;
    tr = Tracer();
    assert(!MsgTimerInitChain(st, d));
    assert(tr.vCreates.size() == 6);

    // ===== 7. the optional flags off
    st = MsgInitChainState();
    st.nState = 1; st.nMapThreads = 0;
    bLoginOk = true; bDbOk = true;
    nFailAt = -1;
    tr = Tracer();
    assert(MsgTimerInitChain(st, d));
    assert(st.nState == 2);
    assert(tr.vCreates.size() == 7);
    assert(tr.vResumes.size() == 5);

    printf("MSG_INIT_CHAIN_OK: "
           "FUN_140024860 timer-1 init "
           "chain VERBATIM (the state 0->4 "
           "and 1->3 dispatch, the ordered "
           "creation of slots 178/180/1c0/"
           "1e0/maps/1c8/1b8/[1d8]/1e8/"
           "[228]/[238]/[230] with the "
           "per-slot verify gates and "
           "AddThreadHandle after each, "
           "the LoginVerify/DatabaseInit "
           "gates, the map-thread loop "
           "with the mid-null fail, the "
           "Resume wave order, state 2 + "
           "the post-init handles + "
           "PerfInfo/ThreadTimes Init + "
           "the 600/300 second timers)\n");
    return 0;
}

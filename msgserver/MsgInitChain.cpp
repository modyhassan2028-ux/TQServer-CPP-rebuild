#include "MsgInitChain.h"

namespace msg {

// one creation step, VERBATIM:
// obj = new+FUN_14050c340+factory;
// slot = obj; if (obj && verify)
// { AddHandle(GetThreadHandle(obj));
//   log; return true; } fail.
static bool step(MsgInitChainState& st,
                 MsgInitChainData& rD,
                 int nSlot, int nType1,
                 int nType2) {
    void* obj = rD.m_fnCreate(nSlot,
        nType1, nType2);
    st.pTh[nSlot] = obj;
    if (obj == nullptr)
        return false;   // LAB_140026533
    if (!rD.m_fnVerify(nSlot))
        return false;
    rD.m_fnAddHandle(obj);   // GetThread-
                            // Handle+Add
    return true;
}

bool MsgTimerInitChain(
    MsgInitChainState& st,
    MsgInitChainData& rD) {
    // ===== the state dispatch
    // (once-flag handled by the
    // caller - DAT_14097593c)
    uint32_t nState = st.nState;
    if (nState == 0) {
        st.nState = 4;   // idle done
        return true;
    }
    if (nState != 1)
        return true;   // states 2-4:
                       // not here
    st.nState = 3;
    // the current thread handle
    rD.m_fnAddHandle(
        rD.m_fnCurrentThread());

    // ===== +0x178: type 7
    if (!step(st, rD, SLOT_178, 7, 0))
        return false;
    // FUN_14001e720 - the pre-DB init
    rD.m_fnLog(nullptr);
    // the verify FUN_14001b1b0 gate
    if (!rD.m_fnVerify(SLOT_178))
        return false;
    rD.m_fnSetLogThreadStatus();
    if (!rD.m_fnDatabaseInit())
        return false;

    // ===== +0x180: CAsyncDBThread
    if (!step(st, rD, SLOT_180, 0, 0))
        return false;
    rD.m_fnLog(nullptr);

    // ===== +0x1c0: type 2
    if (!step(st, rD, SLOT_1C0, 2, 0))
        return false;
    rD.m_fnLog(nullptr);

    // ===== +0x1e0: type 10
    if (!step(st, rD, SLOT_1E0, 10, 0))
        return false;
    rD.m_fnLog("Init OK.");
    rD.m_fnLog(nullptr);

    // ===== the map threads
    for (int i = 0; i <
            (int)st.nMapThreads; ++i) {
        int nSlot = SLOT_MAP0 + i;
        void* obj = rD.m_fnCreate(
            nSlot, i + 0xe, 0);
        st.pTh[nSlot] = obj;
        if (obj == nullptr) {
            // LAB_140025f61: fail if
            // more remain, else break
            if (i < (int)st.nMapThreads)
                return false;
            break;
        }
        if (!rD.m_fnVerify(nSlot))
            return false;
        rD.m_fnAddHandle(obj);
        st.vMapIds.push_back(i);
    }
    rD.m_fnLog(nullptr);

    // ===== +0x1c8: type 4
    if (!step(st, rD, SLOT_1C8, 4, 0))
        return false;
    rD.m_fnLog(nullptr);

    // ===== +0x1b8: types 0xe,1
    if (!step(st, rD, SLOT_1B8, 0xe, 1))
        return false;
    rD.m_fnLog(
        "DAT_1406e3248");   // &DAT
    if (st.bFlagD0) {
        rD.m_fnLog(nullptr);
        // +0x1d8: type 6
        if (!step(st, rD, SLOT_1D8, 6,
            0))
            return false;
        rD.m_fnLog("DAT_1406e3248");
    }

    // ===== +0x1e8: type 8
    if (!step(st, rD, SLOT_1E8, 8, 0))
        return false;
    rD.m_fnLog("Init OK.");

    if (st.bFlag20) {
        rD.m_fnLog(nullptr);
        // +0x228: type 9
        if (!step(st, rD, SLOT_228, 9, 0))
            return false;
        rD.m_fnLog("DAT_1406e3248");
    }
    if (st.bFlag21) {
        rD.m_fnLog(nullptr);
        // +0x238: type 0xb
        if (!step(st, rD, SLOT_238, 0xb,
            0))
            return false;
        rD.m_fnLog("DAT_1406e31a8");
    }
    if (st.bFlag22) {
        rD.m_fnLog(nullptr);
        // +0x230: type 0xd
        if (!step(st, rD, SLOT_230, 0xd,
            0))
            return false;
        rD.m_fnLog("DAT_1406e3248");
    }

    // ===== the Resume wave
    rD.m_fnResume(SLOT_1C0);
    rD.m_fnResume(SLOT_1E0);
    for (int i : st.vMapIds)
        rD.m_fnResume(SLOT_MAP0 + i);
    rD.m_fnResume(SLOT_1B8);
    rD.m_fnResume(SLOT_1C8);
    rD.m_fnResume(SLOT_1E8);
    if (st.pTh[SLOT_1D8] != nullptr)
        rD.m_fnResume(SLOT_1D8);
    if (st.pTh[SLOT_228] != nullptr)
        rD.m_fnResume(SLOT_228);
    if (st.pTh[SLOT_238] != nullptr)
        rD.m_fnResume(SLOT_238);
    if (st.pTh[SLOT_230] != nullptr)
        rD.m_fnResume(SLOT_230);
    rD.m_fnLog("DAT_1406e3160");

    // ===== state 2 + the post-init
    st.nState = 2;
    void* h1 = rD.m_fnPostHandle1();
    if (h1 != nullptr)
        rD.m_fnAddHandle(h1);
    void* h2 = rD.m_fnPostHandle2();
    if (h2 != nullptr)
        rD.m_fnAddHandle(h2);
    rD.m_fnPerfInit();
    rD.m_fnThreadTimesInit();
    st.nPerf600 = 600;
    st.tPerf600 = rD.m_fnTimeGet() / 1000;
    st.nPerf300 = 300;
    st.tPerf300 = rD.m_fnTimeGet() / 1000;
    return true;
}

} // namespace msg

// ===== Path-A wave 4:
// CMapGroupThread::OnProcess (14001d530)
// VERBATIM (raw-verified) =====
#include "MsgMapGroupThread.h"
#include <cstring>

namespace msg {

SMapGroupSeams g_MapGroupSeams = {};
uint32_t g_MGFirstRun = 0;
uint32_t g_MGResyncBase = 0;
uint32_t g_MGCum[5] = {0};
uint32_t g_MGCnt[5] = {0};
uint32_t g_MGMax[5] = {0};
uint32_t g_MGIdleMs = 0;

void MGResetStatics() {
    g_MGFirstRun = 0;
    g_MGResyncBase = 0;
    for (int i = 0; i < 5; i++) {
        g_MGCum[i] = 0;
        g_MGCnt[i] = 0;
        g_MGMax[i] = 0;
    }
    g_MGIdleMs = 0;
}

static inline void* Q(void* p) {   // +0x48
    return *(void**)((uint8_t*)p + 0x48);
}
static inline void* K(void* p) {   // +0x40
    return *(void**)((uint8_t*)p + 0x40);
}

// ===== M: ORIGINAL OnProcess
// (14001d530) VERBATIM — the raw
// disassembly flow =====
uint32_t MapGroupOnProcess(uint8_t* pTh) {
    SMapGroupSeams& s = g_MapGroupSeams;
    // prologue: one-time base time
    if ((g_MGFirstRun & 1) == 0) {
        g_MGFirstRun = g_MGFirstRun | 1;
        g_MGResyncBase = s.TimeGet();
    }
    // CTickAnalyst(0x47)
    // "CMapGroupThread WaitMsg"
    s.TickOn(0x47);
    // PeekMsg(q, g_MGIdleMs)
    bool bHas = s.QPeekMsg(Q(pTh),
                           g_MGIdleMs);
    s.TickOff();
    // CTickAnalyst(0) — the whole
    // process scope
    s.TickOn(0);
    uint32_t t1 = s.TimeGet();
    if (!bHas) {
        // CTickAnalyst(0xc)
        // "CMapGroupKernel::OnTimer"
        s.TickOn(0xc);
        s.KOnTimer(K(pTh), t1);
        s.TickOff();
        uint32_t diff = t1 -
            g_MGResyncBase;
        if (diff <= 0x2710) {
            // within 10000ms: slide
            g_MGResyncBase =
                g_MGResyncBase + 0x7d;
        }
        else {
            s.LogWarning(
                "resync CMapGroupKernel::"
                "OnTimer cumulative "
                "deviation %dms");
            g_MGResyncBase = t1;
        }
    }
    else {
        // the message drain loop
        uint8_t buf[0x420];
        SMGMsgInfo info;
        while (true) {
            if (!s.QWaitMsg(Q(pTh),
                    (int32_t)0xffffffff,
                    (int32_t)0xffffffff,
                    0x418, buf, &info)) {
                break;
            }
            // CTickAnalyst(1)
            // "|-ProcessMsg"
            s.TickOn(1);
            bool ok = s.KProcessMsg(
                K(pTh), info.nPacket, buf,
                info.nArg58);
            s.TickOff();
            if (!ok) {
                s.LogError(
                    "CMapGroupThread::"
                    "OnProcess ProcessMsg "
                    "returned error with "
                    "packet:%d, port:%d",
                    info.nPacket,
                    info.nPort);
            }
        }
    }
    // stats: idx = queueId - 0xe
    uint32_t id = s.QGetId(Q(pTh));
    uint32_t idx = id - 0xe;
    uint32_t t2 = s.TimeGet();
    uint32_t elapsed = t2 - t1;
    if (idx <= 4) {
        // lock xadd (cum += elapsed)
        // lock add (cnt += 1)
        g_MGCum[idx] += elapsed;
        g_MGCnt[idx] += 1;
        // non-atomic max (the raw
        // cmp/mov has NO lock)
        if (g_MGMax[idx] < elapsed) {
            g_MGMax[idx] = elapsed;
        }
    }
    // the idle window (0x7d = 125ms)
    uint32_t since = t2 - g_MGResyncBase;
    if (since < 0x7d) {
        g_MGIdleMs = 0x7d - since;
    }
    else {
        g_MGIdleMs = 0;
    }
    s.TickOff();   // CTickAnalyst(0)
    return 1;
}

} // namespace msg

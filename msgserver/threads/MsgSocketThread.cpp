// ===== Path-A wave 5:
// CSocketThread::OnProcess (14002bd30)
// VERBATIM (raw-verified) =====
#include "MsgSocketThread.h"
#include <cstring>

namespace msg {

SSocketSeams g_SocketSeams = {};
uint32_t g_SockFirstRun = 0;
uint32_t g_SockResyncBase = 0;
uint32_t g_SockCum = 0;
uint32_t g_SockCnt = 0;
uint32_t g_SockMax = 0;
uint32_t g_SockIdleMs = 0;

void SockResetStatics() {
    g_SockFirstRun = 0;
    g_SockResyncBase = 0;
    g_SockCum = 0;
    g_SockCnt = 0;
    g_SockMax = 0;
    g_SockIdleMs = 0;
}

static inline void* Q(void* p) {
    return *(void**)((uint8_t*)p + 0x48);
}
static inline void* K(void* p) {
    return *(void**)((uint8_t*)p + 0x40);
}

// ===== M: ORIGINAL OnProcess
// (14002bd30) VERBATIM =====
uint32_t SocketOnProcess(uint8_t* pTh) {
    SSocketSeams& s = g_SocketSeams;
    if ((g_SockFirstRun & 1) == 0) {
        g_SockFirstRun =
            g_SockFirstRun | 1;
        g_SockResyncBase = s.TimeGet();
    }
    bool bHas = s.QPeekMsg(Q(pTh),
                           g_SockIdleMs);
    s.TickOn(0x23);
    uint32_t t1 = s.TimeGet();
    if (!bHas) {
        s.TickOn(0x2a);
        s.KOnTimer(K(pTh), t1);
        s.TickOff();
        uint32_t diff = t1 -
            g_SockResyncBase;
        if (diff <= 0x2710) {
            g_SockResyncBase =
                g_SockResyncBase + 0x4c;
        }
        else {
            s.LogWarning(
                "resync CSocketKernel::"
                "OnTimer cumulative "
                "deviation %dms");
            g_SockResyncBase = t1;
        }
    }
    else {
        uint8_t buf[0x420];
        SMGMsgInfo info;
        while (true) {
            if (!s.QWaitMsg(Q(pTh),
                    (int32_t)0xffffffff,
                    (int32_t)0xffffffff,
                    0x418, buf, &info)) {
                break;
            }
            s.TickOn(0x24);
            bool ok = s.KProcessMsg5(
                K(pTh), info.nPacket, buf,
                info.nArg58, info.nPort);
            s.TickOff();
            if (!ok) {
                s.LogError(
                    "CSocketThread::"
                    "OnProcess ProcessMsg "
                    "returned error with "
                    "packet:%d, port:%d",
                    info.nPacket,
                    info.nPort);
            }
        }
    }
    uint32_t t2 = s.TimeGet();
    uint32_t elapsed = t2 - t1;
    // lock xadd / lock add / cmovl max
    g_SockCum += elapsed;
    g_SockCnt += 1;
    if (g_SockMax < elapsed) {
        g_SockMax = elapsed;
    }
    uint32_t since =
        t2 - g_SockResyncBase;
    if (since < 0x4c) {
        g_SockIdleMs = 0x4c - since;
    }
    else {
        g_SockIdleMs = 0;
    }
    s.TickOff();   // tick 0x23
    return 1;
}

} // namespace msg

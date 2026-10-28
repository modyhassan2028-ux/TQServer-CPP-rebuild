// ===== Path-A wave 7:
// CAuctionSearchThread::OnProcess
// (1400f31f0) VERBATIM (raw-verified) =====
#include "MsgAuctionThread.h"

namespace msg {

uint32_t g_AucFirstRun = 0;
uint32_t g_AucResyncBase = 0;
uint32_t g_AucIdleMs = 0;

void AuctionResetStatics() {
    g_AucFirstRun = 0;
    g_AucResyncBase = 0;
    g_AucIdleMs = 0;
}

// ===== M: ORIGINAL OnProcess
// (1400f31f0) VERBATIM — queue at
// +0x40, service at +0x48 (inverted
// vs every other thread) =====
uint32_t AuctionOnProcess(uint8_t* pTh) {
    SThreadSeams& s = g_ThreadSeams;
    void* pQueue = *(void**)(pTh + 0x40);
    void* pSvc = *(void**)(pTh + 0x48);
    if ((g_AucFirstRun & 1) == 0) {
        g_AucFirstRun =
            g_AucFirstRun | 1;
        g_AucResyncBase = s.TimeGet();
    }
    s.TickOn(0x4a);
    bool bHas = s.QPeekMsg(pQueue,
                           g_AucIdleMs);
    s.TickOff();
    s.TickOn(0x32);
    uint32_t t1 = s.TimeGet();
    if (!bHas) {
        s.TickOn(0x34);
        s.KOnTimer18(pSvc, t1);
        s.TickOff();
        uint32_t diff = t1 -
            g_AucResyncBase;
        if (diff <= 0x2710) {
            g_AucResyncBase =
                g_AucResyncBase + 2000;
        }
        else {
            s.LogWarning(
                "resync "
                "CAuctionSearchService::"
                "OnTimer cumulative "
                "deviation %dms");
            g_AucResyncBase = t1;
        }
    }
    else {
        uint8_t buf[0x420];
        SMGMsgInfo info;
        while (true) {
            if (!s.QWaitMsg(pQueue,
                    (int32_t)0xffffffff,
                    (int32_t)0xffffffff,
                    0x418, buf, &info)) {
                break;
            }
            s.TickOn(0x33);
            bool ok = s.KProcessMsg5(
                pSvc, info.nPacket, buf,
                info.nArg58, info.nPort);
            s.TickOff();
            if (!ok) {
                s.LogError(
                    "CAuctionSearchThread"
                    "::OnProcess ProcessMsg "
                    "returned error with "
                    "packet:%d, port:%d",
                    info.nPacket,
                    info.nPort);
            }
        }
    }
    uint32_t t2 = s.TimeGet();
    uint32_t since = t2 - g_AucResyncBase;
    if (since < 2000) {
        g_AucIdleMs = 2000 - since;
    }
    else {
        g_AucIdleMs = 0;
    }
    s.TickOff();   // tick 0x32
    return 1;
}

} // namespace msg

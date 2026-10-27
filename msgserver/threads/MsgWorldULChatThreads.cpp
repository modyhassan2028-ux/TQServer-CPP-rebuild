// ===== Path-A wave 6: World/
// UserLogin/Chat OnProcess VERBATIM
// (raw-verified) =====
#include "MsgWorldULChatThreads.h"
#include <cstring>

namespace msg {

SThreadSeams g_ThreadSeams = {};
uint32_t g_WFirstRun = 0, g_WResyncBase = 0;
uint32_t g_WCum = 0, g_WCnt = 0;
uint32_t g_WMax = 0, g_WIdleMs = 0;
uint32_t g_ULFirstRun = 0,
         g_ULResyncBase = 0, g_ULIdleMs = 0;
uint32_t g_CFirstRun = 0, g_CResyncBase = 0,
         g_CIdleMs = 0;

void ThreadResetStatics() {
    g_WFirstRun = g_WResyncBase = 0;
    g_WCum = g_WCnt = g_WMax = 0;
    g_WIdleMs = 0;
    g_ULFirstRun = g_ULResyncBase = 0;
    g_ULIdleMs = 0;
    g_CFirstRun = g_CResyncBase = 0;
    g_CIdleMs = 0;
}

static inline void* Q(void* p) {
    return *(void**)((uint8_t*)p + 0x48);
}
static inline void* K(void* p) {
    return *(void**)((uint8_t*)p + 0x40);
}

// shared body — the three raw bodies
// differ ONLY in their constants and
// stats block, each preserved verbatim
// below via the config struct
struct SRawCfg {
    uint32_t* pFirstRun;
    uint32_t* pBase;
    uint32_t* pIdle;
    uint32_t slide;
    uint32_t tickProc;
    uint32_t tickTimer;
    uint32_t tickMsg;
    bool bWaitTick;    // Chat only (0x49)
    bool bStats;       // World only
    const char* resyncFmt;
    const char* errFmt;
};

static uint32_t OnProcessCommon(
    uint8_t* pTh, const SRawCfg& c) {
    SThreadSeams& s = g_ThreadSeams;
    if ((*c.pFirstRun & 1) == 0) {
        *c.pFirstRun = *c.pFirstRun | 1;
        *c.pBase = s.TimeGet();
    }
    if (c.bWaitTick) {   // Chat raw only
        s.TickOn(0x49);
    }
    bool bHas = s.QPeekMsg(Q(pTh),
                          *c.pIdle);
    if (c.bWaitTick) {
        s.TickOff();
    }
    s.TickOn(c.tickProc);
    uint32_t t1 = s.TimeGet();
    if (!bHas) {
        s.TickOn(c.tickTimer);
        s.KOnTimer18(K(pTh), t1);
        s.TickOff();
        uint32_t diff = t1 - *c.pBase;
        if (diff <= 0x2710) {
            *c.pBase = *c.pBase + c.slide;
        }
        else {
            s.LogWarning(c.resyncFmt);
            *c.pBase = t1;
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
            s.TickOn(c.tickMsg);
            bool ok = s.KProcessMsg5(
                K(pTh), info.nPacket, buf,
                info.nArg58, info.nPort);
            s.TickOff();
            if (!ok) {
                s.LogError(c.errFmt,
                    info.nPacket, info.nPort);
            }
        }
    }
    uint32_t t2 = s.TimeGet();
    if (c.bStats) {   // World raw only
        uint32_t elapsed = t2 - t1;
        // lock xadd / lock add / cmovl
        g_WCum += elapsed;
        g_WCnt += 1;
        if (g_WMax < elapsed) {
            g_WMax = elapsed;
        }
    }
    uint32_t since = t2 - *c.pBase;
    if (since < c.slide) {
        *c.pIdle = c.slide - since;
    }
    else {
        *c.pIdle = 0;
    }
    s.TickOff();   // tickProc
    return 1;
}

// ===== M: ORIGINAL World (14002e990)
uint32_t WorldOnProcess(uint8_t* p) {
    static const SRawCfg c = {
        &g_WFirstRun, &g_WResyncBase,
        &g_WIdleMs, 1000, 0x1d, 0x1f,
        0x1e, false, true,
        "resync CWorldKernel::OnTimer"
        " cumulative deviation %dms",
        "CWorldThread::OnProcess"
        " ProcessMsg returned error"
        " with packet:%d, port:%d"};
    return OnProcessCommon(p, c);
}

// ===== M: ORIGINAL UserLogin
// (14002e580)
uint32_t UserLoginOnProcess(uint8_t* p) {
    static const SRawCfg c = {
        &g_ULFirstRun, &g_ULResyncBase,
        &g_ULIdleMs, 2000, 0x20, 0x22,
        0x21, false, false,
        "resync CUserKernel::OnTimer"
        " cumulative deviation %dms",
        "CUserLoginThread::OnProcess"
        " ProcessMsg returned error"
        " with packet:%d, port:%d"};
    return OnProcessCommon(p, c);
}

// ===== M: ORIGINAL Chat (1400011b0)
uint32_t ChatOnProcess(uint8_t* p) {
    static const SRawCfg c = {
        &g_CFirstRun, &g_CResyncBase,
        &g_CIdleMs, 2000, 0x2f, 0x31,
        0x30, true, false,
        "resync CChatKernel::OnTimer"
        " cumulative deviation %dms",
        "CChatThread::OnProcess"
        " ProcessMsg returned error"
        " with packet:%d, port:%d"};
    return OnProcessCommon(p, c);
}

} // namespace msg

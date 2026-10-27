// ===== Path-A wave 1: CLogThread VERBATIM =====
#include "MsgLogThread.h"

namespace msg {

SLogThreadSeams g_LogThreadSeams = {};
uint32_t g_LogTimerInit = 0;   // DAT_1409754fc
uint32_t g_LogTimerBase = 0;   // DAT_1409754f8
uint32_t g_LogNextWait = 0;   // +0x14 of the
                              // wait slot

static uint64_t& F64(void* p, size_t o) {
    return *(uint64_t*)((char*)p + o);
}

// ===== M: ORIGINAL ctor (14001b100) VERBATIM =
// =====
void LogThreadCtor(void* pTh, void* pPort,
                   const char* name) {
    SLogThreadSeams& s = g_LogThreadSeams;
    s.BaseCtor(pTh);
    // vftable = CLogThread::vftable
    F64(pTh, 0x40) = 0;   // ILogKernel*
    F64(pTh, 0x48) = (uint64_t)pPort;
    if (name != nullptr) {
        s.SafeCopy((char*)pTh + 0x50, name, 0x80);
    }
}

// ===== M: ORIGINAL dtor (14001b180) VERBATIM =
// =====
void LogThreadDtor(void* pTh) {
    // vftable restore, then base dtor
    g_LogThreadSeams.BaseDtor(pTh);
}

// ===== M: ORIGINAL create (14001b1b0)
// VERBATIM =====
bool LogThreadCreate(void* pTh, bool bWait) {
    SLogThreadSeams& s = g_LogThreadSeams;
    void* pK = s.KernelNew();
    F64(pTh, 0x40) = (uint64_t)pK;
    if (pK != nullptr) {
        bool ok = s.KernelInit(pK,
            (void*)F64(pTh, 0x48),
            (const char*)pTh + 0x50);
        if (ok) {
            return s.CreateThread(pTh,
                                  "LogThread",
                                  bWait);
        }
    }
    return false;
}

// ===== M: ORIGINAL OnClose (14001b220)
// VERBATIM =====
void LogThreadOnClose(void* pTh) {
    SLogThreadSeams& s = g_LogThreadSeams;
    char buf[0x740];
    int n = s.PortCount((void*)F64(pTh, 0x48));
    if (0 < n) {
        s.Snprintf(buf, 0x740,
          "error:: LOG_MSG_PORT have %d LOG not"
          " print!");
        s.KernelLog((void*)F64(pTh, 0x40),
                    (const char*)pTh + 0x50, buf, 1);
    }
    s.KernelClose((void*)F64(pTh, 0x40));
    F64(pTh, 0x40) = 0;
}

// ===== M: ORIGINAL OnTimer (14001b2d0)
// VERBATIM =====
bool LogThreadOnTimer(void* pTh) {
    SLogThreadSeams& s = g_LogThreadSeams;
    char buf[0x740];
    // the first-ever tick: latch the base
    if ((g_LogTimerInit & 1) == 0) {
        g_LogTimerInit = g_LogTimerInit | 1;
        g_LogTimerBase = s.TimeGet(0);
    }
    // WaitMsg with the current wait slot
    bool got = s.PortWait(
        (void*)F64(pTh, 0x48), g_LogNextWait);
    uint32_t now = s.TimeGet(0);
    if (!got) {
        // idle poke on the kernel
        s.KernelIdle((void*)F64(pTh, 0x40));
        // the resync machine
        uint32_t dev = now - g_LogTimerBase;
        if (dev < 0x2711) {
            g_LogTimerBase = g_LogTimerBase + 1000;
        }
        else {
            buf[0] = 0;
            s.Snprintf(buf, 0x740,
              "error:: resync CLogThread::OnTimer"
              " cumulative deviation %ldms", dev);
            s.KernelLog((void*)F64(pTh, 0x40),
                        (const char*)pTh + 0x50,
                        buf, 1);
            g_LogTimerBase = now;
        }
    }
    else {
        // the drain loop: pop and print each
        while (s.PortPop((void*)F64(pTh, 0x48),
                         -1, -1, 0x800)) {
            // vcall+0x10(kernel, hdr, buf, len)
            s.KernelPrint(
                (void*)F64(pTh, 0x40), 0, buf, 0);
        }
    }
    // compute the next wait slot
    uint32_t now2 = s.TimeGet(0);
    if ((int)(now2 - g_LogTimerBase) < 1000) {
        g_LogNextWait = (uint32_t)(
            1000 - (now2 - g_LogTimerBase));
    }
    else {
        g_LogNextWait = 0;   // 4 zero bytes
    }
    return true;
}

// ===== M: ORIGINAL deleting dtor (14001b4e0)
// VERBATIM =====
void LogThreadOnDelete(void* pTh, uint32_t flags) {
    SLogThreadSeams& s = g_LogThreadSeams;
    s.BaseDtor(pTh);
    if ((flags & 1) != 0) {
        // operator delete(pTh)
        operator delete(pTh);
    }
}

} // namespace msg

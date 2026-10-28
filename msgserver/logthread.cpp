// 14001b2d0
#include <cstdio>
#include <cstring>
#include "logthread.h"
// RAW calls the MSVC _snprintf (no NUL guarantee); the forced NUL at
// +0x73f below is part of the original code, so the C99 snprintf used
// on other platforms only changes how the same buffer is filled.
#if defined(_MSC_VER)
#define RAW_SNPRINTF _snprintf
#else
#define RAW_SNPRINTF snprintf
#endif
namespace msg {
int CLogThread::OnProcess(Seams& s) {
    if ((*s.pInitFlag & 1) == 0) {
        *s.pInitFlag |= 1;
        *s.pPacing = s.TimeGet(0);
    }
    char has = (char)(s.WaitMessage(m_pDrainer, *s.pWaitTimeout) != 0);
    s.TickEnter(kTickBody);
    uint32_t now = s.TimeGet(0);
    if (has == 0) {
        s.OnTimer(m_pPort);
        uint32_t dev = now - *s.pPacing;
        if (dev < (uint32_t)kCatchUpMs) {
            *s.pPacing = *s.pPacing + kPeriodMs;
        } else {
            memset(m_Resync, 0, kResyncLen);
            m_Resync[0] = 0;
            RAW_SNPRINTF(m_Resync, kResyncLen,
                      "error:: resync CLogThread::OnTimer cumulative "
                      "deviation %ldms",
                      (long)dev);
            m_Resync[kResyncLen - 1] = 0;
            s.WriteResync(m_pPort, m_pCtx, m_Resync, 1);
            *s.pPacing = now;
        }
    } else {
        for (;;) {
            if (s.GetMessage(m_pDrainer, -1, -1, kMsgBufLen,
                             m_MsgBuf, m_Hdr) == 0) break;
            s.TickEnter(kTickMsg);
            // the RAW ignores the ProcessMsg result here
            s.ProcessMsg(m_pPort, m_Hdr[1], m_MsgBuf, m_Hdr[2]);
            s.TickLeave(kTickMsg);
        }
    }
    uint32_t t = s.TimeGet(0);
    if ((int32_t)(t - *s.pPacing) < kPeriodMs) {
        *s.pWaitTimeout = (uint32_t)(kPeriodMs - (t - *s.pPacing));
    } else {
        *s.pWaitTimeout = 0;
    }
    s.TickLeave(kTickBody);
    return 1;
}
}

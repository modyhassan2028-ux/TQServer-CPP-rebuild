// 14002e990 CWorldThread::OnProcess + 14002e580 CUserLoginThread::OnProcess
#include "worldkernel.h"
namespace msg {
// ---------------------------------------------------------- CWorldThread
// RAW scopes: the wait has NO analyst scope; tick 0x1d (OnProcess) opens
// right after it and closes at the very end; 0x1f (OnTimer) and 0x1e
// (ProcessMsg) nest inside.
int CWorldThread::OnProcess(Seams& s) {
    if ((*s.pInitFlag & 1) == 0) {
        *s.pInitFlag |= 1;
        *s.pPacing = s.TimeGet(0);
    }
    char has = (char)(s.WaitMessage(m_pDrainer, *s.pWaitTimeout) != 0);
    s.TickEnter(kTickWait);
    uint32_t now = s.TimeGet(0);
    if (has == 0) {
        s.TickEnter(kTickOnTimer);
        s.OnTimer(m_pPort, now);
        s.TickLeave(kTickOnTimer);
        if (now - *s.pPacing < (uint32_t)kCatchUpMs) {
            *s.pPacing = *s.pPacing + kPeriodMs;
        } else {
            *s.pPacing = now;
        }
    } else {
        for (;;) {
            if (s.GetMessage(m_pDrainer, -1, -1, kMsgBufLen,
                             m_MsgBuf, m_Hdr) == 0) break;
            s.TickEnter(kTickMsg);
            char ok = (char)s.ProcessMsg(m_pPort, m_Hdr[1], m_MsgBuf,
                                         m_Hdr[2]);
            s.TickLeave(kTickMsg);
            if (ok == 0) {
                s.LogProcessError(m_Hdr[1], 0);
            }
        }
    }
    uint32_t t = s.TimeGet(0);
    int32_t spent = (int32_t)(t - now);
    *s.pSpentSum   = *s.pSpentSum + spent;
    *s.pSpentCount = *s.pSpentCount + 1;
    if (*s.pSpentMax < spent) *s.pSpentMax = spent;
    if ((int32_t)(t - *s.pPacing) < kPeriodMs) {
        *s.pWaitTimeout = (uint32_t)(kPeriodMs - (t - *s.pPacing));
    } else {
        *s.pWaitTimeout = 0;
    }
    s.TickLeave(kTickWait);
    return 1;
}
// ----------------------------------------------------- CUserLoginThread
// The wait takes the plain global DAT_1409499a8 (not s+0x20), and the
// 0x20 scope opens after it. Period 2000.
int CUserLoginThread::OnProcess(Seams& s) {
    if ((*s.pInitFlag & 1) == 0) {
        *s.pInitFlag |= 1;
        *s.pPacing = s.TimeGet(0);
    }
    char has = (char)(s.WaitMessage(m_pDrainer, *s.pWaitTimeout) != 0);
    s.TickEnter(kTickWait);
    uint32_t now = s.TimeGet(0);
    if (has == 0) {
        s.TickEnter(kTickOnTimer);
        s.OnTimer(m_pPort, now);
        s.TickLeave(kTickOnTimer);
        if (now - *s.pPacing < (uint32_t)kCatchUpMs) {
            *s.pPacing = *s.pPacing + kPeriodMs;
        } else {
            *s.pPacing = now;
        }
    } else {
        for (;;) {
            if (s.GetMessage(m_pDrainer, -1, -1, kMsgBufLen,
                             m_MsgBuf, m_Hdr) == 0) break;
            s.TickEnter(kTickMsg);
            char ok = (char)s.ProcessMsg(m_pPort, m_Hdr[1], m_MsgBuf,
                                         m_Hdr[2]);
            s.TickLeave(kTickMsg);
            if (ok == 0) {
                s.LogProcessError(m_Hdr[1], 0);
            }
        }
    }
    uint32_t t = s.TimeGet(0);
    if ((int32_t)(t - *s.pPacing) < kPeriodMs) {
        *s.pWaitTimeout = (uint32_t)(kPeriodMs - (t - *s.pPacing));
    } else {
        *s.pWaitTimeout = 0;
    }
    s.TickLeave(kTickWait);
    return 1;
}
}

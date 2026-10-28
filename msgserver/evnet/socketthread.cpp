// 14002bbe0 + 14002bd30
#include "socketthread.h"
namespace msg {
int CSocketThread::CreateThread(int isSuspended, Seams& s) {
    if (!s.BaseCreateThread(this, "SocketThread", isSuspended)) {
        return 0;
    }
    void* p = s.GetSocketKernel();
    m_pKernel = p;
    if (s.KernelAttach(p, m_pDrainer, m_pExtra)) {
        return 1;
    }
    s.MessageBox(nullptr, "CSocketThread::CreateThread failed",
                 "Conquer Online Server", 0x10);
    return 0;
}
int CSocketThread::OnProcess(Seams& s) {
    if ((*s.pInitFlag & 1) == 0) {
        *s.pInitFlag |= 1;
        *s.pPacing = s.TimeGet(0);
    }
    char has = (char)(s.WaitMessage(m_pDrainer, *s.pWaitTimeout) != 0);
    s.TickEnter(kTickWait);
    s.TickLeave(kTickWait);
    uint32_t now = s.TimeGet(0);
    if (has == 0) {
        s.TickEnter(kTickOnTimer);
        s.OnTimer(m_pKernel, now);
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
            char ok = (char)s.ProcessMsg(m_pKernel, m_Hdr[1], m_MsgBuf,
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
    return 1;
}
}

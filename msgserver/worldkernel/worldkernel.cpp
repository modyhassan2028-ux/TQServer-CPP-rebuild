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

// ------------------------------------------- CWorldKernel (added, batch A9ak)
#include <cstring>
namespace msg {
// 140060510
uint8_t CWorldKernel::ProcessAccountNetMsg(const uint16_t* msg, SWorldKernelSeams& s) {
    if (msg != nullptr) {
        if (msg[1] == 0x7533) {
            if (msg[0] == 100) {
                s.OnMobileAccount(this, *(const uint32_t*)(msg + 2),
                                  *(const uint32_t*)(msg + 6),
                                  (const uint8_t*)msg + 20, 0,
                                  *(const uint32_t*)(msg + 8));
                return 1;
            }
            s.LogAccountSize((int)msg[0]);
            return 0;
        }
        if (msg[1] == 0x7531) {
            if (0xb < msg[0]) { s.OnMobileString(); return 1; }
            s.LogStringSize((int)msg[0]);
        }
    }
    return 0;
}
// 1400552a0
int CWorldKernel::SendMsg(uint32_t msgId, int type, const void* body, int len,
                          SWorldKernelSeams& s) {
    if (body == nullptr) { s.LogNullMsg(); return 0; }
    if (type == 0)       { s.LogBadType(); return 0; }
    if (len + 4 < 0x401) {
        uint8_t frame[0x418];                  // {msgId@0, type@4, len@8, body@0xc}
        *(uint32_t*)(frame + 0) = msgId;
        *(int*)(frame + 4)      = type;
        *(int*)(frame + 8)      = len;
        if (len > 0) std::memcpy(frame + 12, body, (size_t)len);
        s.Post(m_Q[0x0a], 1, 0x7533, 0x418, frame);   // this +0x50
        return 1;
    }
    s.LogOverflow(msgId, len);
    return 0;
}
// 140066ae0
void CWorldKernel::Destruct(SWorldKernelSeams& s) {
    s.Dtor280(&m_Q[0x50]); s.Free(m_Q[0x50]);
    if (m_Q[0x4d] != nullptr) s.Free(m_Q[0x4d]);
    m_Q[0x4d] = nullptr; m_Q[0x4e] = nullptr; m_Q[0x4f] = nullptr;
    s.Free(m_Q[0x4a]);
    s.Dtor210(&m_Q[0x42]); s.Free(m_Q[0x42]);
    if (m_Q[0x39] != nullptr) s.Free(m_Q[0x39]);
    m_Q[0x39] = nullptr; m_Q[0x3a] = nullptr; m_Q[0x3b] = nullptr;
    s.Free(m_Q[0x36]);
    if (m_Q[0x33] != nullptr) {
        s.Dtor198(m_Q[0x33], m_Q[0x34], &m_Q[0x32], (uint8_t)((uintptr_t)this & 0xff));
        s.Free(m_Q[0x33]);
    }
    m_Q[0x33] = nullptr; m_Q[0x34] = nullptr; m_Q[0x35] = nullptr;
    s.Free(m_Q[0x30]);
    s.Dtor138(&m_Q[0x27]); s.Free(m_Q[0x27]);
    s.Dtor098(&m_Q[0x13]);
    s.Dtor210(&m_Q[0x02]); s.Free(m_Q[0x02]);
    m_Q[0] = nullptr;
}
} // namespace msg

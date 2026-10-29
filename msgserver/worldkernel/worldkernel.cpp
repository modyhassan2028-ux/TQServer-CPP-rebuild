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
}
namespace msg {
// 140055450 — no length guard at all (unlike CMapGroupKernel::SendNpcMsg) and
// the null message text still says CGameSocket::SendMsg.
int CWorldKernel::SendNpcMsg2(uint32_t npcId, int type, const void* body, int len,
                              SWorldSeams2& s) {
    if (body == nullptr) { s.LogNullNpcCgs(); return 0; }
    if (type == 0)       { s.LogNpcType(npcId); return 0; }
    uint8_t frame[0x418];
    *(uint32_t*)(frame + 0) = npcId;
    *(int*)(frame + 4)      = type;
    *(int*)(frame + 8)      = len;
    std::memcpy(frame + 12, body, (size_t)len);
    s.Post(m_Q[0x0a], 1, 0x7534, 0x418, frame);
    return 1;
}
// 140058540 — the version lands at this+0x1f4 (500).
uint8_t CWorldKernel::LoadGameVersionCfg(SWorldSeams2& s) {
    SDbRowSet* rs = (SDbRowSet*)s.LoadCfg(50000, 1, nullptr, nullptr);
    if (rs == nullptr) { s.LogVersionCfgFail(); return 0; }
    if (rs->RowCount() == 0) {
        s.LogVersionCfgFail();
        rs->Release();
        return 0;
    }
    void* col = rs->Column(2);
    *(uint32_t*)((uint8_t*)this + 500) = ((SDbRowSet*)col)->Int();
    s.LogVersion(*(uint32_t*)((uint8_t*)this + 500));
    rs->Release();
    return 1;
}
// 1400605b0 — account frame dispatcher; every branch compares the 16-bit
// leading size against sizeof(CMsg*_A::MSG_Info) and logs its own text.
uint8_t CWorldKernel::ProcessAccountMsg2(const uint16_t* m, SWorldSeams2& s) {
    if (m == nullptr) return 0;
    switch (m[1]) {
    case 0x3ea:
        if (m[0] == 0x20) { s.OnLogin(this, *(const uint32_t*)(m + 2),
                                      *(const uint32_t*)(m + 4), m[6], m + 7); return 1; }
        s.LogLoginSize((int)m[0]); return 0;
    case 0x41c:
        if (m[0] == 0x1c) { s.OnConnect(this, *(const uint32_t*)(m + 2),
                                        *(const uint32_t*)(m + 4), m + 6, 0); return 1; }
        s.LogConnectSize((int)m[0]); return 0;
    case 0x429:
        if (m[0] == 0xb0) { s.OnConnectFB(this, *(const uint32_t*)(m + 2),
                                          *(const uint32_t*)(m + 4), *(const uint32_t*)(m + 6),
                                          m + 8, 0); return 1; }
        s.LogConnectFBSize((int)m[0]); return 0;
    case 0x4b0:
        if (m[0] == 0xc) { s.OnFee(this, *(const uint32_t*)(m + 2), (char)m[4]); return 1; }
        s.LogFeeSize((int)m[0]); return 0;
    case 0x4b1:
        if (m[0] == 0x14) { s.OnQueryFee(this, *(const uint32_t*)(m + 2),
                                         *(const uint32_t*)(m + 4),
                                         *(const uint32_t*)(m + 6), (char)m[8]); return 1; }
        s.LogQueryFeeSize((int)m[0]); return 0;
    case 0x4b2:
        if (m[0] == 0x1ec) { s.OnWebRequest(this, m + 2, m + 0x12,
                                            *(const uint32_t*)(m + 0x52),
                                            *(const uint32_t*)(m + 0x54)); return 1; }
        s.LogWebReqSize((int)m[0]); return 0;
    case 0x5fc:
        if (m[0] == 0xc) { s.OnOfflineCheat(this, *(const uint32_t*)(m + 2),
                                            *(const uint32_t*)(m + 4)); return 1; }
        s.LogOfflineSize((int)m[0]); return 0;
    case 0x609:
        if (7 < m[0]) { s.OnTransfer(this, m[2], m[0], m + 3); return 1; }
        s.LogTransferSize((int)m[0]); return 0;
    case 0x643: {
        if (m[0] != 0x38) { s.LogJailSize((int)m[0]); return 0; }
        if (*(const char*)((const uint8_t*)m + 0x15) == 0)      // RAW writes into
            std::strncpy((char*)((uint8_t*)m + 0x15), s.BotSinName(), 0x21);
        s.OnJailEx(this, (uint16_t*)m);
        return 1;
    }
    default: return 0;
    }
}
// 1400641b0 — parses "a.b.c.d e.f.g.h" per record; anything else logs the
// record's own u16 id. Returns 1 even when the config object is missing.
int CWorldKernel::LoadIpConfig(SWorldSeams2& s) {
    s.IpReset((uint8_t*)this + 0x1b0);
    SDbRowSet* rs = (SDbRowSet*)s.LoadCfg(20000, 0, nullptr, nullptr);
    if (rs != nullptr) {
        int i = 0;
        for (int n = rs->RowCount(); i < n; n = rs->RowCount()) {
            rs->SeekRow(i);
            void* col = rs->Column(7);
            const char* src = ((SDbRowSet*)col)->Str();
            uint32_t f[8] = {0};
            if (s.Sscanf4x2(src, f, f + 4) == 8) {
                uint32_t lo = ((f[0] << 8 | f[1]) << 8 | f[2]) << 8 | f[3];
                uint32_t hi = ((f[4] << 8 | f[5]) << 8 | f[6]) << 8 | f[7];
                uint32_t range[2] = { lo, hi };
                s.IpInsert((uint8_t*)this + 0x1b0, range);
            } else {
                void* c0 = rs->Column(0);
                s.Log("CWorldKernel::LoadIpConfig bad config record %u",
                      (unsigned)((SDbRowSet*)c0)->Int());
            }
            i++;
        }
        rs->Release();
    }
    return 1;
}
} // namespace msg

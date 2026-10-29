// 14002e990 CWorldThread::OnProcess + 14002e580 CUserLoginThread::OnProcess
#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <vector>
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
// 1400651f0 — the world kernel bootstrap. Every timer pair is written as
// (period, TimeGet(0)/1000) and the port id must be MSGPORT_WORLD (2) or the
// MYASSERT fires at line 0x9f without aborting.
uint8_t CWorldKernel::Create(SCreateSeams& s) {
    s.SrandSeed(s.NowSec());
    m_Q[0x0b] = s.port;                                    // +0x58
    *(uint32_t*)((uint8_t*)this + 0x50) = s.PortId(s.port);
    s.PortSetHandler(s.port);
    s.PortSetType(s.port, 0x14);
    if (*(int*)((uint8_t*)this + 0x50) != 2)
        s.Assert(0x9f, "m_idProcess == MSGPORT_WORLD",
                 "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
    void* mem = s.Alloc(0x1d0);
    void* part = (mem != nullptr) ? s.NewKernelPart(mem) : nullptr;
    m_Q[0x0c] = part;                                      // +0x60
    if (part == nullptr) return 0;
    s.InitPart1(part, (uint8_t*)this + 8);
    mem = s.Alloc(0x38);
    part = (mem != nullptr) ? s.NewPart2(mem) : nullptr;
    m_Q[0x0d] = part;                                      // +0x68
    if (part == nullptr) return 0;
    s.InitPart2(part);
    void* nb = s.NewNewbieInfo();
    m_Q[0x0e] = nb;                                        // +0x70
    if (nb == nullptr) { s.LogNoNewbie(); return 0; }
    s.SetSingleton(this);                                  // DAT_140975af8
    m_Q[0x1d] = s.NewTimer01(1);                            // +0xe8
    m_Q[0x1e] = s.NewTimer02(1);                            // +0xf0
    void* ini = s.OpenIni("shell.ini", "Database");
    s.IniSection(ini, "System");
    int v = s.IniInt(ini, "SERVE_PORT");
    if (v != 0) *(int*)((uint8_t*)this + 300) = v;           // +0x12c
    *(uint32_t*)((uint8_t*)this + 0x78) = 0x1e;
    *(uint32_t*)((uint8_t*)this + 0x7c) = s.NowSec();
    s.IniSection(ini, "IPADPaymentsClient");
    if (s.IniInt(ini, "IsSupportIPADPayments") == 1) *(uint8_t*)((uint8_t*)this + 0x200) = 1;
    s.IniSection(ini, "GooglePaymentsClient");
    if (s.IniInt(ini, "IsSupportGooglePayments") == 1) *(uint8_t*)((uint8_t*)this + 0x201) = 1;
    s.IniSection(ini, "91AuthServerInfo");
    if (s.IniInt(ini, "Is91AccountServer") == 1) *(uint8_t*)((uint8_t*)this + 0x203) = 1;
    *(uint8_t*)((uint8_t*)this + 0x202) =
        (*(uint8_t*)((uint8_t*)this + 0x200) != 0 ||
         *(uint8_t*)((uint8_t*)this + 0x201) != 0 ||
         *(uint8_t*)((uint8_t*)this + 0x203) != 0) ? 1 : 0;
    s.IniSection(ini, "AccountServer");
    s.IniStr(ini, (char*)((uint8_t*)this + 0xfc), "SERVERNAME", 0x10);
    s.IniStr(ini, (char*)((uint8_t*)this + 0x10c), "LOGINNAME", 0x10);
    s.IniStr(ini, (char*)((uint8_t*)this + 0x11c), "PASSWORD", 0x10);
    s.LoadIpConfig(this);
    s.BindInstance(this, s.Instance());
    s.InitKernel(this);
    if (!s.LoadGameVersionCfg(this)) { s.IniFree(ini); return 0; }
    s.AfterVersion(this);
    *(uint32_t*)((uint8_t*)this + 0x1fc) = s.ReadCfg1(this);
    *(uint32_t*)((uint8_t*)this + 0x208) = s.ReadCfg2(this);
    s.PostInit();
    *(uint32_t*)((uint8_t*)this + 0x84) = 10;
    *(uint32_t*)((uint8_t*)this + 0x88) = s.NowSec();
    *(uint32_t*)((uint8_t*)this + 0x8c) = 0;
    *(uint32_t*)((uint8_t*)this + 0x90) = 0x1e;
    *(uint32_t*)((uint8_t*)this + 0x94) = s.NowSec();
    *(uint32_t*)((uint8_t*)this + 0x178) = 300;
    *(uint32_t*)((uint8_t*)this + 0x17c) = s.NowSec();
    *(uint32_t*)((uint8_t*)this + 0xe0) = 0x1e;
    *(uint32_t*)((uint8_t*)this + 0xe4) = s.NowSec();
    *(uint32_t*)((uint8_t*)this + 0x1e4) = 10;
    *(uint32_t*)((uint8_t*)this + 0x1e8) = s.NowSec();
    s.IniFree(ini);
    return 1;
}
// 140065e50 — a server connects to the world port. Order preserved exactly:
// the appointment gate, the existing-node path (give-back / busy / same data /
// data mismatch), then the fall-through that detaches twice before binding.
void CWorldKernel::ClientConnect(uint32_t portIdx, int data, uint64_t tag, int handle,
                                 int param6, SClientSeams& s) {
    if (handle == -1 || param6 == 0) {
        s.Assert(0x72c, "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
        return;
    }
    if (*(uint8_t*)((uint8_t*)this + 0x1e0) != 0 && *(uint8_t*)((uint8_t*)this + 0x203) != 0) {
        char sql[0x400];
        // RAW passes the %s with no argument (reads r8, undefined). An empty
        // literal keeps the same SQL text without the UB. Declared deviation.
        snprintf(sql, 0x400, "SELECT * FROM cq_appointment_account WHERE account='%s'", "");
        void* inst = s.Instance();
        void* rs = s.Query(inst, sql, 1);
        if (rs == nullptr) {
            s.Assert(0x735, "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
            s.KickOut(s.UnitLookup(), handle, 0);
            return;
        }
        if (s.RowCount(rs) == 0) {
            s.KickOut(s.UnitLookup(), handle, 0);
            s.Release(rs);
            return;
        }
        s.Release(rs);
    }
    void* objE = s.PortObjE(this);                     // +0xf0
    void* objD = s.PortObjD(this);                     // +0xe8
    SClientNode* node = (SClientNode*)s.FindNode(objE, portIdx);
    if (node != nullptr) {
        if (s.IsOnline(node)) {
            if (s.HasGiveBack((uint8_t*)this + 0x98, portIdx)) {
                char buf[0x400];
                s.MsgInit(buf);
                int ok = s.MsgBuild(buf, "SYSTEM", "ALLUSERS", s.Str("STR_ERROR_GIVE_BACK"));
                if (ok != 0) s.SendMsg(this, handle, buf);
                s.KickOut(s.UnitLookup(), handle, portIdx);
                s.DetachE(objE, portIdx);
                s.MsgFree(buf);
                return;
            }
            if (s.IsBannedOrQueued(s.UnitLookup(), portIdx) == 0 && s.HasFreeSlot(this) == 0) {
                char buf[0x400];
                s.MsgInit(buf);
                int ok = s.MsgBuild(buf, "SYSTEM", "ALLUSERS", s.Str("STR_ERROR_SERVER_BUSY"));
                if (ok != 0) s.SendMsg(this, handle, buf);
                s.KickOut(s.UnitLookup(), handle, portIdx);
                s.DetachE(objE, portIdx);
                s.MsgFree(buf);
                return;
            }
            char name[0x41];
            std::memset(name, 0, 0x41);
            s.SafeCopy(name, node->m_Name, 0x41);
            if (s.IsOnline(node) && node->m_Data == data) {
                void* sess = s.AllocSession();              // 140054bc0
                if (!s.BindSession(sess, portIdx, data, tag)) {
                    s.Assert(0x771, "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
                    return;
                }
                s.DetachD(objD, portIdx);
                s.PushNodeNoArg(objD);
                struct { uint32_t a, b, c, d, e; char n[0x41]; } info;
                info.a = 0; info.b = 0; std::memset(info.n, 0, 0x41);
                info.c = 2; info.d = (uint32_t)handle; info.e = (uint32_t)param6;
                *(uint32_t*)info.n = 0;                      // local_530 before SafeCopy
                s.SafeCopy(info.n, name, 0x41);
                *(int*)((uint8_t*)this + 0x2c0) += 1;
                uint32_t seq = *(uint32_t*)((uint8_t*)this + 0x2c0);
                uint8_t key[0x58];
                std::memcpy(key, &info, 0x58);
                s.InsertLogin((uint8_t*)this + 0x280, nullptr, &seq);
                char log[0x400];
                std::memset(log, 0, 0x400);
                // RAW also prints %u with no argument; the sequence counter is
                // the value it means. Declared deviation.
                snprintf(log, 0x400, " worlduserlogin****worlduserlogin [%u]", seq);
                s.LoginLog(seq);
                s.LogLine(s.Instance(), log, 0, 0);
                return;
            }
            if (s.IsOnline(node) && node->m_Data != data) {
                s.Assert(0x788, "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
            }
            s.KickOut(s.UnitLookup(), handle, portIdx);
            s.DetachE(objE, portIdx);
            return;
        }
        s.DetachE(objE, portIdx);
    }
    s.DetachD(objD, portIdx);       // different object (+0xe8) than the one above
    void* mem = s.NewSessionArr(0x88);
    void* sess = (mem != nullptr) ? s.InitSession(mem) : nullptr;
    if (!s.BindSession(sess, portIdx, data, tag)) {
        s.Assert(0x794, "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
    } else {
        s.PushNode(objD, sess);
        s.OnLoginOk(this, handle);
        s.OnLoginInfo(this, portIdx, param6, handle);
    }
}

namespace {
// the console sidebar tags from .rdata
static const uint8_t g_tag_1406e87d0[1] = {0};
static const uint8_t g_tag_1406ed450[1] = {1};
static const uint8_t g_tag_1406ed478[1] = {2};
static const uint8_t g_tag_1406ed4a0[1] = {3};
static const uint8_t g_tag_1406ed4c8[1] = {4};
// _stricmp equivalent (the RAW compares console commands case-insensitively)
static int cmpi(const char* a, const char* b) {
    for (;; a++, b++) {
        int ca = std::tolower((unsigned char)*a), cb = std::tolower((unsigned char)*b);
        if (ca != cb || ca == 0) return ca - cb;
    }
}
}

// 1400613e0 — the world port dispatcher. The id ladder is checked in order:
// ids below 0x4e22 first (0x4e21 console text, then 0x3e9/0x3ea/0x3eb/0x3f6/
// 0x3f7), the rest through a switch where 0x4e2d is the logged default.
int CWorldKernel::ProcessMsg(uint32_t msgId, int* buf, SProcessSeams& s) {
    if (msgId < 0x4e22) {
        if (msgId == 0x4e21) {
            char cmd[256];
            // the RAW re-sends the command text as msg 0x9c41 with its length
            int n = 0;
            while (((const char*)buf)[n] != '\0') n++;
            s.PortSend(s.port, 0, 0x9c41, (uint32_t)n);
            std::memset(cmd, 0, sizeof cmd);
            if (sscanf((const char*)buf, "%s", cmd) != 1) return 1;
            if (cmpi(cmd, "setmaxplayer") == 0) {
                int v = 0;
                if (sscanf((const char*)buf, "%s %d", cmd, &v) != 2) return 1;
                *(uint32_t*)s.MaxPlayerGet() = (uint32_t)v;      // LOCK/UNLOCK in RAW
                char out[256];
                std::memset(out, 0, sizeof out);
                snprintf(out, 0xff, "Set max player limit to %d", *(int*)s.MaxPlayerGet());
                s.PortSend(s.port, 0, 0x9c41, (uint32_t)std::strlen(out));
                return 1;
            }
            if (cmpi(cmd, "kickoutall") == 0) {
                s.PortSend(s.port, 1, 0x753b, 0xea65);
                return 1;
            }
            if (cmpi(cmd, "broadcast") == 0) {
                const char* text = (const char*)buf + std::strlen(cmd);
                if (*text == ' ') text++;
                s.ConsoleBroadcast(s.World(), &g_tag_1406e87d0, text, 0);
                return 1;
            }
            if (cmpi(cmd, "shutdown") == 0) {
                s.ConsoleBroadcast(s.World(), &g_tag_1406e87d0, s.Str("STR_SHUTDOWN_NOTIFY"), 0);
                s.PortSend(s.port, 0, 0x9c41, (uint32_t)std::strlen("Send shut down broadcast message."));
                return 1;
            }
            if (cmpi(cmd, "restartserver") == 0) {
                if (s.RestartServerAllowed()) { s.SetGlobal(0, 1); return 1; }
                s.PortSend(s.port, 0, 0x9c41,
                           (uint32_t)std::strlen("Please <kickoutall> before <restartserver>!"));
                return 1;
            }
            if (cmpi(cmd, "restartwindows") == 0) {
                if (s.RestartServerAllowed()) {
                    if (!s.RestartWindows()) s.Log("ExitWindowsEx");
                    return 1;
                }
                s.PortSend(s.port, 0, 0x9c41,
                           (uint32_t)std::strlen("Please <kickoutall> before <restartserver>!"));
                return 1;
            }
            return 1;
        }
        if (msgId == 0x3e9) { s.OnClientLogin(this, buf[0], buf[1], buf + 3); return 1; }
        if (msgId == 0x3ea) { s.OnClientLogout(this, buf[0], buf[1], buf + 3); return 1; }
        if (msgId == 0x3eb) {
            int id = buf[0];
            if (s.IsChatUser(s.Unit(), id)) {
                int count = s.PortCount(s.port);
                for (uint32_t i = 0xe; i < (uint32_t)count; i++)
                    s.PortSend(s.port, i & 0xffffffff, 0x3eb, 0xea65);
                return 1;
            }
            s.KickChat(s.Unit(), id);
            s.DropUser(s.World(), id);
            return 1;
        }
        if (msgId == 0x3f6) {
            int a = buf[0], b = buf[1];
            if (b != 0) { s.ChatMsg1(s.World(), a, b); return 1; }
            s.ChatMsg2(s.World(), a);
            return 1;
        }
        if (msgId == 0x3f7) {
            s.ChatMsg3(s.World(), buf[0], buf[1], buf[3]);
            return 1;
        }
        s.Log("CWorldKernel::ProcessMsg default");
        return 1;
    }
    switch (msgId) {
    case 0x4e22: s.Offline1(s.Unit(), buf[0], buf[1]); break;
    case 0x4e23:
        s.KickChat(s.Unit(), buf[0]);
        s.DropUser(s.World(), buf[0]);
        break;
    case 0x4e24: {
        int a = buf[0], b = buf[1];
        void* n = s.FindByPtr(s.Unit(), buf + 3);
        if (n == nullptr) {
            if (b == 0x3ec && a != -1) {
                void* u = s.FindById(s.Unit(), a);
                if (u != nullptr) {
                    char msg[1024];
                    s.MsgInit(msg);
                    s.MsgBuild(msg, "SYSTEM", (char*)u + 4, s.Str("STR_TARGET_OFFLINE"));
                    s.SendToUnit(u, msg);
                    s.MsgFree(msg);
                }
            }
        } else {
            s.CallVt8((uint8_t*)this + 8, *(uint32_t*)((uint8_t*)n + 0x60), b, buf + 7);
        }
        break;
    }
    case 0x4e25: {
        void* n = s.FindById2(s.Unit(), buf[3]);
        if (n != nullptr)
            s.CallVt8((uint8_t*)this + 8, *(uint32_t*)((uint8_t*)n + 0x60), buf[1], buf + 4);
        break;
    }
    case 0x4e26: {
        void* n = s.FindById2(s.World(), buf[0]);
        if (n == nullptr) s.Log("CWorldKernel::ProcessMsg 0x4e26 node");
        else s.SetNodeTime(n);
        break;
    }
    case 0x4e27:
        if (*(int*)((uint8_t*)this + 0xf8) == 3) s.ChangeServer(this, buf[0], 0, 0);
        break;
    case 0x4e28:
        if (buf[0] == -1) s.Log("CWorldKernel::ProcessMsg 0x4e28 id");
        else s.SetOffline(s.Unit(), buf[0]);
        break;
    case 0x4e29:
        if (buf[0] == -1) s.OnClientLogout(this, buf[1], 0, nullptr);
        else s.OnClientLogin(this, buf[0], buf[2], buf + 5);
        break;
    case 0x4e2a: {
        int key = 0; uint32_t value = 0;
        if (sscanf((const char*)buf, "%d %u", &key, &value) == 2)
            s.MapSet((uint8_t*)this + 0x10, key, value);
        break;
    }
    case 0x4e2b:
        if (!s.DbReconnect(s.Db())) s.Log("Worldkernel reconnect database failed at %s, %d");
        else s.LogMsg("Worldkernel reconnect database success.");
        break;
    case 0x4e2c: {
        struct { int id; uint32_t when; int val; } rec;
        rec.id = buf[0];
        rec.when = s.NowSec();
        rec.val = buf[1];
        s.AddRecord((uint8_t*)this + 0x98, rec.id, &rec);
        break;
    }
    case 0x4e2e: {
        int a = buf[0], id = buf[1];
        if (*(int*)((uint8_t*)this + 0xf8) == 3) {
            if (buf[2] == 0) {
                s.DropAndLog(this, id, 1);
                s.ChangeServer(this, id, 0, 0);
                s.LogFile("gmlog/ChangeServer", &g_tag_1406ed4c8);
            } else if (s.ChangeServer(this, id, 0, 0) == 0) {
                int key = id;
                s.MapInsert((uint8_t*)this + 0x138, &key, a);
                s.LogFile("gmlog/ChangeServer", &g_tag_1406ed478);
            } else {
                s.LogFile("gmlog/ChangeServer", &g_tag_1406ed4a0);
            }
        } else {
            s.LogFile("gmlog/ChangeServer", &g_tag_1406ed450);
        }
        break;
    }
    case 0x4e2f: {
        uint8_t first[0x420];
        std::memset(first, 0, sizeof first);
        uint16_t* len = (uint16_t*)first;                  // local_468
        int32_t*  a   = (int32_t*)(first + 2);              // local_464
        int32_t*  b   = (int32_t*)(first + 6);              // local_460
        *len = 0; *a = buf[0]; *b = buf[1];
        if ((uint32_t)buf[2] > 0x409) return 0;
        std::memcpy(first + 10, buf + 3, (size_t)(uint32_t)buf[2]);   // local_45c
        uint8_t out[0x420];
        std::memset(out, 0, sizeof out);
        *(uint16_t*)(out + 0) = (uint16_t)(buf[2] + 0x16);
        *(uint16_t*)(out + 2) = 0x608;
        *(uint16_t*)(out + 4) = 2;
        // RAW copies 0xf + len bytes from the first buffer, i.e. 5 bytes past it
        std::memcpy(out + 6, first, (size_t)(uint16_t)(buf[2] + 0xf));
        s.SendPort(this, out, *(uint16_t*)out);
        break;
    }
    case 0x4e30: {
        uint8_t first[0x420];
        std::memset(first, 0, sizeof first);
        *(uint16_t*)(first + 0) = 6;
        *(int32_t*)(first + 2) = buf[0];
        *(int32_t*)(first + 6) = buf[1];
        if ((uint32_t)buf[2] > 0x409) return 0;
        std::memcpy(first + 10, buf + 3, (size_t)(uint32_t)buf[2]);
        uint8_t out[0x420];
        std::memset(out, 0, sizeof out);
        *(uint16_t*)(out + 0) = (uint16_t)(buf[2] + 0x16);
        *(uint16_t*)(out + 2) = 0x608;
        *(uint16_t*)(out + 4) = 2;
        std::memcpy(out + 6, first, (size_t)(uint16_t)(buf[2] + 0xf));
        s.SendPort(this, out, *(uint16_t*)out);
        break;
    }
    case 0x4e31: {
        int key = buf[0];
        s.MapErase((uint8_t*)this + 0x10, &key);
        break;
    }
    case 0x4e32: {
        uint8_t m[12];
        std::memset(m, 0, sizeof m);
        *(uint16_t*)(m + 0) = 0xc;   // local_1778
        *(uint16_t*)(m + 2) = 0x640; // local_1776
        *(int32_t*)(m + 4) = buf[0]; // local_1774
        m[8] = (uint8_t)buf[1];      // local_1770
        s.SendPort2(this, m);
        break;
    }
    case 0x4e33:
        if (buf[0] == 1) {
            *(int*)((uint8_t*)this + 0xf8) = 2;
            if (*(uint8_t*)((uint8_t*)this + 0x203) == 0) s.OnAccountConnected(this);
            else s.OnAccountAlt(this);
        } else {
            *(int*)((uint8_t*)this + 0xf8) = 0;
            s.SetGlobal(1, 0);
            s.PortSend(s.port, 0, 0x9c41, (uint32_t)std::strlen("Account server connection broken."));
        }
        break;
    case 0x4e34:
        if (buf != nullptr) {
            if (*(uint8_t*)((uint8_t*)this + 0x203) == 0) s.ProcessAccountMsg(this, buf + 1);
            else s.ProcessAccountMsg91(this, buf + 1);
        }
        break;
    case 0x4e35:
        if (buf == nullptr) {
            s.Log("CWorldKernel::ProcessMsg, WORLD_M91_RECHARGE_QUERY, buf is NULL, type:%d, from:%d");
            return 0;
        }
        if (buf[2] == 0) {
            *(uint32_t*)((uint8_t*)this + 0x1ec) = 0;
        } else {
            if (buf[2] != 1) {
                s.Log("CWorldKernel::WORLD_M91_RECHARGE_QUERY, RECHARGE_91QUERY, case[%d] error. User[%u], type:%d, from:%d");
                return 0;
            }
            s.RechargeQuery(this, buf[0], buf[1]);
        }
        break;
    default:
        s.Log("CWorldKernel::ProcessMsg default");
        break;
    }
    return 1;
}

// 1400567f0 — builds the login packet from +0x1fc and the dword at +0x208 and
// hands it to the kernel send. A failed build frees the buffer and reports 0.
uint8_t CWorldKernel::SendLoginPacket(int handle, SLoginPacketSeams& s) {
    uint8_t buf[0x430];
    s.Init(buf);
    if (s.Build(buf, *(uint32_t*)((uint8_t*)this + 0x1fc),
                *(int*)((uint8_t*)this + 0x208)) == 0) {
        s.Free(buf);
        return 0;
    }
    uint8_t r = s.SendMsg(this, handle, buf);
    s.Free(buf);
    return r;
}

// 140064330 — the cq_ippointrecord bookkeeping. Reads lastloginip /
// lastlogintime / initialip plus the five slots, updates the point of the
// matched ip only when the day stamp changed, or appends / evicts a record,
// then writes the row back.
namespace {
static void vfmt(char* out, const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); vsnprintf(out, 0x400, fmt, ap); va_end(ap);
}
static int slotv(const std::vector<SIpRec>& v, size_t i, int which) {
    if (i >= v.size()) return 0;
    switch (which) {
    case 0: return (int)v[i].ip;
    case 1: return (int)v[i].ipcode;
    case 2: return v[i].point;
    default: return (int)v[i].logintime;
    }
}
}
void CWorldKernel::RecordLoginIp(int id, int p4, SIpSeams& s) {
    int key = s.AccountKey(this, id);
    uint32_t now = s.Now();
    int lastIp = 0, initialIp = 0, saved[2] = {0, 0};
    uint32_t lastTime = 0;
    std::vector<SIpRec> recs;
    char sql[0x400];
    void* db = s.Db();
    vfmt(sql, "SELECT * FROM cq_ippointrecord WHERE account_id=%u", (uint32_t)id);
    void* rs = s.Query(db, sql);
    void* table = nullptr;
    if (rs != nullptr) {
        table = s.RsFields(rs);
        s.RsRelease(rs);
    }
    if (table == nullptr) table = s.GetTable(db, "cq_ippointrecord");
    if (table == nullptr) {
        s.Assert(0xac5, "f:\\version\\cqserver-78.0.11-1204\\msgserver\\worldkernel\\worldkernel.cpp");
    } else {
        lastIp    = s.AsInt(s.Field(table, "lastloginip"));
        lastTime  = (uint32_t)s.AsInt(s.Field(table, "lastlogintime"));
        initialIp = s.AsInt(s.Field(table, "initialip"));
        for (int i = 1; i <= 5; i++) {
            char n1[32], n2[32], n3[32], n4[32];
            snprintf(n1, sizeof n1, "ippoint%d", i);
            void* f1 = s.Field(table, n1);
            if (s.IsNull(f1) <= 0) continue;          // the RAW probe is (+0x48) > 0
            snprintf(n2, sizeof n2, "ip%d", i);
            snprintf(n3, sizeof n3, "ipcode%d", i);
            snprintf(n4, sizeof n4, "iplogintime%d", i);
            SIpRec r;
            r.ip        = (uint32_t)s.AsInt(s.Field(table, n2));
            r.ipcode    = (uint32_t)s.AsInt(s.Field(table, n3));
            r.point     = s.IsNull(f1);
            r.logintime = (uint32_t)s.AsInt(s.Field(table, n4));
            recs.push_back(r);
        }
    }
    if (recs.empty()) {
        if (initialIp == 0) {
            vfmt(sql, "INSERT cq_ippointrecord SET account_id=%u, ip1=%u, ipcode1=%u, ippoint1=30, "
                      "iplogintime1=%u, lastloginip=%u, lastlogintime=%u, initialip=%u, initialipcode=%u",
                 (uint32_t)id, (uint32_t)key, now, now, (uint32_t)id, (uint32_t)key, now, now);
        } else {
            vfmt(sql, "UPDATE cq_ippointrecord SET ip1=%u, ipcode1=%u, ippoint1=30, iplogintime1=%u,"
                      "lastloginip=%u, lastlogintime=%u WHERE account_id=%u LIMIT 1",
                 (uint32_t)id, (uint32_t)key, now, now, (uint32_t)id, (uint32_t)key);
        }
        s.Exec(db, sql);
        lastIp = 0; lastTime = 0;
    } else {
        const uint32_t today = now / 0x15180;
        int found = -1;
        for (size_t i = 0; i < recs.size(); i++) {
            if ((int)i < 2) saved[i] = (int)recs[i].ip;
            if ((int)recs[i].ip == id) { found = (int)i; break; }
        }
        if (found >= 0) {
            SIpRec& r = recs[(size_t)found];
            if (today != r.logintime / 0x15180) {
                int32_t np = r.point;
                if (found < 2) np += ((int)r.ip == lastIp) ? 2 : 1;
                else           np += ((int)r.ip == lastIp) ? 4 : 3;
                if (np > 0x3c) np = 0x3c;
                r.point = np;
                r.logintime = now;
            }
        } else if (recs.size() < 5) {
            SIpRec r;
            r.ip = (uint32_t)id; r.ipcode = (uint32_t)key; r.point = 0x1e; r.logintime = now;
            recs.push_back(r);
        } else {
            for (size_t i = 0; i < recs.size(); i++) {
                if ((int)i < 2) {
                    recs[i].point -= 2;
                    if (recs[i].point < 0x1e) recs[i].point = 0x1e;
                } else if ((int)i < 4) {
                    recs[i].point -= 1;
                    if (recs[i].point < 1) recs[i].point = 1;
                } else {
                    recs[i].ip = (uint32_t)id;
                    recs[i].ipcode = (uint32_t)key;
                    recs[i].point = 1;
                    recs[i].logintime = now;
                }
            }
        }
        if (recs.size() > 1) s.Sort(&recs[0], &recs[0] + recs.size());
        vfmt(sql, "UPDATE cq_ippointrecord SET ip1=%u, ipcode1=%u, ippoint1=%d, iplogintime1=%u, \t\t\t"
                  "ip2=%u, ipcode2=%u, ippoint2=%d, iplogintime2=%u, ip3=%u, ipcode3=%u, ippoint3=%d, iplogintime3=%u, \t\t\t"
                  "ip4=%u, ipcode4=%u, ippoint4=%d, iplogintime4=%u, ip5=%u, ipcode5=%u, ippoint5=%d, iplogintime5=%u, \t\t\t"
                  "lastloginip=%u, lastlogintime=%u WHERE account_id=%u LIMIT 1",
             slotv(recs, 0, 0), slotv(recs, 0, 1), slotv(recs, 0, 2), slotv(recs, 0, 3),
             slotv(recs, 1, 0), slotv(recs, 1, 1), slotv(recs, 1, 2), slotv(recs, 1, 3),
             slotv(recs, 2, 0), slotv(recs, 2, 1), slotv(recs, 2, 2), slotv(recs, 2, 3),
             slotv(recs, 3, 0), slotv(recs, 3, 1), slotv(recs, 3, 2), slotv(recs, 3, 3),
             slotv(recs, 4, 0), slotv(recs, 4, 1), slotv(recs, 4, 2), slotv(recs, 4, 3),
             (uint32_t)id, now, (uint32_t)id);
        s.Exec(db, sql);
    }
    // the "new address" flag: both remembered ips differ from lastloginip
    int flag = (saved[0] != lastIp && saved[1] != lastIp) ? 1 : 0;
    s.OnIpNotified(this, id, lastIp, (int)lastTime, flag, p4);
    s.OnIpLogged(this, id, p4);
}

// 14005f7a0 — sends the "your login ip changed" notice. When +0x1f8 is set the
// RAW reports success without building or sending anything; otherwise it
// renders both addresses to text, compares them and feeds the result into the
// builder as a flag, and only a successful build is sent.
uint8_t CWorldKernel::SendIpChangedNotice(int p2, int p3, int p4, uint8_t p5,
                                          int p6, SIpNoticeSeams& s) {
    if (*(char*)((uint8_t*)this + 0x1f8) != 0) return 1;
    char oldIp[256], newIp[256];
    oldIp[0] = '\0';
    newIp[0] = '\0';
    s.IpToString(this, p2, oldIp, 0xff);
    s.IpToString(this, p3, newIp, 0xff);
    int same = 1;
    for (int i = 0;; i++) {
        if (oldIp[i] != newIp[i]) { same = 0; break; }
        if (oldIp[i] == '\0') break;
    }
    uint8_t buf[0x430];
    s.NoticeInit(buf);
    if (s.NoticeBuild(buf, p4, p5, same) == 0) {
        s.NoticeFree(buf);
        return 0;
    }
    s.SendMsg(this, p6, buf);
    s.NoticeFree(buf);
    return 1;
}

// 14005f900 — the login-ip notice: render the address, build, and send only
// when the builder reports success. The buffer is released on both branches.
bool CWorldKernel::SendIpLoggedNotice(int p2, int p3, SIpNoticeSeams& s) {
    char ipText[256];
    ipText[0] = '\0';
    s.IpToString(this, p2, ipText, 0xff);
    uint8_t buf[0x430];
    s.LoginInit(buf);
    int ok = s.LoginBuild(buf, ipText);
    if (ok != 0) {
        s.SendMsg(this, p3, buf);
        s.LoginFree(buf);
    } else {
        s.LoginFree(buf);
    }
    return ok != 0;
}
} // namespace msg

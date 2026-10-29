// 140089140..140089660 — CMapGroup senders
#include "mapgroup.h"
#include <cstring>
#include <cstdio>
#if defined(_MSC_VER)
#define RAW_SNPRINTF _snprintf
#else
#define RAW_SNPRINTF snprintf
#endif
namespace msg {
int CMapGroup::SendClientMsg(uint32_t ch, SMapGroupMsg* m, SMapGroupSeams& s) {
    if (m == nullptr) { s.LogNullClient(); return 0; }
    m->f414 = ch;
    m->f410 = m_ServerId;
    m->f418 = 0;
    m->f41c = 0;
    return s.KernelSendOne(m_pKernel, m);
}
int CMapGroup::SendCrossMsg(uint32_t userId, SMapGroupMsg* m, SMapGroupSeams& s) {
    if (userId == 0) { s.LogNullUser(); return 0; }
    if (m == nullptr) { s.LogNullCross(); return 0; }
    return s.KernelSendCross6(m_pKernel, userId, 0xffffffff, m->f410,
                              (const uint8_t*)m + 0x10, m->f414, 1);
}
int CMapGroup::SendCrossMsg(SMapGroupMsg* m, SMapGroupSeams& s) {
    if (m == nullptr) { s.LogNullCross(); return 0; }
    return s.KernelSendCross3(m_pKernel, m->f410, 0xffffffff,
                              (const uint8_t*)m + 0x10, m->f414, 1);
}
int CMapGroup::SendGSOrOSS2SMsg(uint32_t s2s, SMapGroupMsg* m, SMapGroupSeams& s) {
    if (m == nullptr) { s.LogNullGs(); return 0; }
    return s.KernelSendCross3(m_pKernel, m->f410, s2s,
                              (const uint8_t*)m + 0x10, m->f414, 8);
}
int CMapGroup::SendCrossMsg(uint32_t userId, uint32_t s2s, SMapGroupMsg* m,
                            uint32_t flag, SMapGroupSeams& s) {
    if (userId == 0) { s.LogNullUser(); return 0; }
    if (m == nullptr) { s.LogNullCross(); return 0; }
    return s.KernelSendCross6(m_pKernel, userId, s2s, m->f410,
                              (const uint8_t*)m + 0x10, m->f414, flag);
}
int CMapGroup::SendCrossMsg2(uint32_t s2s, SMapGroupMsg* m, uint32_t flag,
                             SMapGroupSeams& s) {
    if (m == nullptr) { s.LogNullCross(); return 0; }
    return s.KernelSendCross3(m_pKernel, m->f410, s2s,
                              (const uint8_t*)m + 0x10, m->f414, flag);
}
int CMapGroup::SendNpcMsg(uint32_t ch, SMapGroupMsg* m, SMapGroupSeams& s) {
    if (m == nullptr) { s.LogNullNpc(); return 0; }
    m->f418 = ch;
    m->f414 = 0xffffffff;
    m->f41c = 0xffffffff;
    m->f410 = m_ServerId;
    return s.KernelSendOne(m_pKernel, m);
}
int CMapGroup::BroadcastOtherServerMsg(void* msg, uint32_t a, uint16_t kind,
                                       SMapGroupSeams& s) {
    if (msg == nullptr) { s.LogNullClient(); return 0; }   // the CHECKF at 0x966
    uint8_t talk[1104];
    s.TalkCtor(talk);
    // fields written by RAW, in its order
    uint8_t* t = talk;
    t[0x38] = 1;                       // local_4a8
    *(uint32_t*)(t + 0x30) = 0;        // local_4b0
    *(uint32_t*)(t + 0x28) = 0;        // local_4b8
    *(uint16_t*)(t + 0x20) = 0;        // local_4c0
    *(uint16_t*)(t + 0x18) = kind;     // local_4c8
    *(void**)(t + 0x08) = (void*)nullptr;  // local_4d8 = param_3
    *(uint32_t*)(t + 0x10) = a;        // local_4d0
    if (s.TalkCreate(talk, "SYSTEM", "ALLUSERS", msg) == 0) {
        s.LogBroadcastCreate();
        s.TalkDtor(talk);
        return 0;
    }
    int r = s.SelfSend(this, 0, talk, 10);
    s.TalkDtor(talk);
    return r;
}
} // namespace msg

// ---------------------------------------------------------------
// 140092b60 CMapGroup::SendChatFriendInfo
// ---------------------------------------------------------------
namespace msg {
// DAT_1406f38a0, read out of .rdata: the per-level friend cap
static const int kFriendCap[7] = { 50, 55, 60, 70, 80, 90, 100 };

void CMapGroup::SendChatFriendInfo(int* ids, SMapGroupChatSeams& s) {
    if (ids[0] != 0) {
        void* w = s.UserWorld(m_pWorld, (uint32_t)ids[0]);
        if (w != nullptr) {
            void* same = s.UserWorld(m_pWorld, 0);
            int level = s.LevelOf(same);
            void* list = s.UserByServer(m_ServerId);
            uint32_t flags = *(uint32_t*)((uint8_t*)list + 0x2ac);
            if ((int)flags < 1 || (((flags >> 10) & 1) == 0) || level < 0) {
                level = 0;
            } else if (level > 6) {
                level = 6;
            }
            uint8_t out[0x194];
            *(int32_t*)out = 0;
            std::memset(out + 4, 0, 400);
            if (kFriendCap[level] != -1) {
                int n = kFriendCap[level] + 1;
                int* dst = (int*)(out + 4);
                for (int i = 0; i < n; ++i) {
                    if (ids[i] != 0) dst[i] = ids[i];
                }
            }
            s.Post(m_pPort, 8, 0x15f94, 0x194, out);
            return;
        }
    }
    s.LogNoUser();
}

// ---------------------------------------------------------------
// 140093ec0 CMapGroup::IsAllowEnterOS
// ---------------------------------------------------------------
bool CMapGroup::IsAllowEnterOS(int action, SMapGroupChatSeams& s) {
    if (action == 3) {
        int n = s.Count(s.UserList(s.UserByServer(m_ServerId)));
        return n < *(int*)((uint8_t*)this + 0x10);
    }
    if (action == 4) {
        if (*(char*)((uint8_t*)this + 0x77c) != 0) {
            int n = s.Count(s.UserList(s.UserByServer(m_ServerId)));
            if (n < *(int*)((uint8_t*)this + 0x10)) {
                void* mod = s.Module(s.CurrentInstance(), 0x25);
                if (mod != nullptr) return s.ModuleReady(mod) != 0;
            }
        }
        return false;
    }
    s.LogWrongAction(action);
    return false;
}
} // namespace msg

// 1400b4420 CMapGroup::LoadDataSysData
namespace msg {
void CMapGroup::LoadDataSysData(SMapGroupDbSeams& s) {
    s.UserByServer(m_ServerId);                       // side effect only
    void* db = s.InstanceGet();
    void* rs = s.Query(db, "SELECT * FROM cq_dyna_global_data", 2);
    if (rs != nullptr && s.RowCount(rs) != 0) {
        int n = s.RowCount(rs);                       // RAW reads it twice
        for (int i = 0; i < n; ++i) {
            s.SetRow(rs, i);
            void* g = s.NewGameData();
            if (g == nullptr) { s.LogCreateNewError(); }
            else if (s.GameDataCreate(g, rs) == 0) {
                s.LogCreateError();
                s.GameDataDestroy(g);
            } else {
                struct { int key; void* obj; } pair;
                pair.key = s.GameDataKey(g);
                pair.obj = g;
                s.InsertSysData(&m_SysData, &pair);   // this + 0x800
            }
            n = s.RowCount(rs);                       // RAW re-reads per row
        }
    }
    if (rs != nullptr) s.Destroy(rs);
}

// 1400943f0 CMapGroup::CheckTableAutoId
int CMapGroup::CheckTableAutoId(const char* table, uint32_t want, SMapGroupDbSeams& s) {
    char sql[0x400];
    sql[0] = 0;
    std::memset(&sql[1], 0, 0x3ff);
    RAW_SNPRINTF(sql, 0x400, "SELECT max(id) from %s", table);
    s.UserByServer(m_ServerId);
    void* db = s.InstanceGet();
    void* rs = s.Query(db, sql, 1);
    if (rs == nullptr) { s.LogLoadAutoIdFail(table); return 0; }
    int rows = s.RowCount(rs);
    if (rows == 1) {
        void* f = s.Field(rs, 0);
        int v = s.FieldInt(f);
        if ((uint32_t)v < want) { s.Destroy(rs); return 1; }
        s.Destroy(rs);
        s.LogAutoIdMore(table, want);
        return 0;
    }
    s.Destroy(rs);
    s.LogAutoIdCounts(table, rows);
    return 0;
}

// 1400b27a0 CMapGroup::LoadMonsterDropRateConfig
void CMapGroup::LoadMonsterDropRateConfig(SMapGroupDbSeams& s) {
    int n2 = 0;
    void* rs = s.LoadConfigTable(0x1d4c, 0);
    if (rs != nullptr) {
        int rows = s.RowCount(rs);
        if (rows > 0) {
            int i = 0;
            do {
                s.SetRow(rs, i);
                void* f2 = s.Field(rs, 2);
                int rate = s.FieldInt(f2);
                void* f3 = s.Field(rs, 3);
                int sort = s.FieldInt(f3);
                void* f4 = s.Field(rs, 4);
                int mete = s.FieldInt(f4);
                if (mete < 0) s.LogMonsterRateError(rate, sort, mete);
                else {
                    struct { int a; int b; int v; } pair;
                    pair.a = (uint32_t)rate;
                    pair.b = (uint32_t)sort;
                    pair.v = mete;
                    s.InsertDropRate(&m_DropRateMonster, &pair);  // this + 0x548
                }
                ++i;
                rows = s.RowCount(rs);
            } while (i < rows);
        }
        s.Destroy(rs);
    }
    rs = s.LoadConfigTable(0x1d4d, 0);
    int rows = 0;
    if (rs != nullptr) {
        rows = s.RowCount(rs);
        if (rows > 0) {
            do {
                s.SetRow(rs, n2);                          // RAW uses this counter
                void* f2 = s.Field(rs, 2);
                int rate = s.FieldInt(f2);
                void* f3 = s.Field(rs, 3);
                int sort = s.FieldInt(f3);
                void* f4 = s.Field(rs, 4);
                int mete = s.FieldInt(f4);
                if (mete < 0) s.LogDragonRateError(rate, sort, mete);
                else {
                    struct { int a; int b; int v; } pair;
                    pair.a = (uint32_t)rate;
                    pair.b = (uint32_t)sort;
                    pair.v = mete;
                    s.InsertDropRate(&m_DropRateDragon, &pair);   // this + 0x588
                }
                ++n2;
                rows = s.RowCount(rs);
            } while (n2 < rows);
        }
        s.Destroy(rs);
    }
}
} // namespace msg

// 1400a65b0 / 1400a6950 — the two multi-send paths. RAW has two iterator
// branches (capacity < 2 and >= 2) whose bodies are identical: send through
// this->vt[0] once per id, and stop after the 2001st send with a Dead Loop log.
namespace msg {
int CMapGroup::SendMultiClientMsg(const uint32_t* ids, size_t n, void* msg) {
    if (msg == nullptr) return 0;
    if ((int)(kMultiCap - m_Multi.GetSize(msg)) < 0) {
        m_Multi.LogSize();                       // ", (_MAX_MSGSIZE - GetSize()) < 0."
        return 0;
    }
    if (n == 0) return 0;
    int sent = 0;
    for (size_t i = 0; i < n; ++i) {
        m_Multi.SendOne(this, ids[i], msg);
        sent = sent + 1;
        if (kMultiDeadLoop < sent) { m_Multi.LogDeadLoop(); break; }
    }
    return 1;
}
int CMapGroup::SendMultiOSClientMsg(const uint32_t* ids, size_t n, void* msg) {
    if (msg == nullptr) { m_Multi.LogNull(); return 0; }
    if ((int)(kMultiCap - m_Multi.GetSize(msg)) < 0) {
        m_Multi.LogSize();
        return 0;
    }
    if (n == 0) return 0;
    int sent = 0;
    for (size_t i = 0; i < n; ++i) {
        m_Multi.SendOne(this, ids[i], msg);
        sent = sent + 1;
        if (kMultiDeadLoop < sent) { m_Multi.LogDeadLoop(); break; }
    }
    return 1;
}
} // namespace msg

// 1400a7ab0 CMapGroup::ProcessQueryOSConnectStatus
namespace msg {
void CMapGroup::ProcessQueryOSConnectStatus(void* reply, SOsEntry* v, size_t n,
                                            SeamsQuery& s) {
    if (reply == nullptr) { s.LogCheck(0xe9a); return; }
    uint8_t buf[0x430];
    void* msg = s.Ctor(buf);
    unsigned char val = 0;
    if (m_Flg730 != 0) {
        void* u = s.UserByServer(m_ServerId);
        void* p = (u != nullptr) ? *(void**)((uint8_t*)u + 0x148) : nullptr;
        if (p == nullptr) { s.LogCheck(0x14d); p = nullptr; }
        val = s.GetVal(p);          // RAW calls it even when p is null
    }
    if (s.CreateMsg(msg, val) == 0) {
        s.LogCreateFailed();
        s.Destroy(msg);
        return;
    }
    int appended = 1;
    for (size_t i = 0; i < n; ++i) {
        if (s.Append(msg, v[i].key, v[i].flag) == 0) { appended = 0; break; }
    }
    if (appended == 0) s.LogAppendFailed();
    s.SendReply(reply, msg);
    s.Destroy(msg);
}
} // namespace msg

// 1400a73d0 CMapGroup::LoadStatisticsKillMonsterByProCfg
namespace msg {
void CMapGroup::LoadStatisticsKillMonsterByProCfg(SeamsStat& s) {
    void* rs = s.LoadTable(0x1fbd3, 1);
    if (rs == nullptr) return;                 // RAW does nothing at all
    if (s.RowCount(rs) == 0) { s.DestroyRs(rs); return; }
    void* f2 = s.Field(rs, 2);
    m_StatType = s.FieldByte(f2);              // +0x33c
    void* f3 = s.Field(rs, 3);
    m_StatTime = s.FieldInt(f3);               // +0x340
    void* f4 = s.Field(rs, 4);
    m_StatFlag = s.FieldByte(f4);              // +0x344
    if (m_StatTime == 0) {
        s.LogTimeZero((int)m_StatType);
        m_StatType = 0;
    }
    s.DestroyRs(rs);
    if (m_StatType == 0) return;
    void* rs2 = s.LoadTable(0x1fbd4, 0);
    if (rs2 == nullptr) return;
    if (s.RowCount(rs2) == 0) { s.DestroyRs(rs2); return; }
    uint8_t scratch[24] = {0};
    s.ClearStat(m_StatRows);                   // +0x348
    int i = 0;
    int n = s.RowCount(rs2);
    while (i < n) {
        s.SetRow(rs2, i);
        uint32_t a = s.FieldInt(s.Field(rs2, 2));
        uint32_t b = s.FieldInt(s.Field(rs2, 3));
        if (a != 0 && b != 0) {
            int pair[2] = { (int)a, (int)b };
            s.InsertStat(m_StatRows, scratch, pair);
        }
        i = i + 1;
        n = s.RowCount(rs2);                   // RAW re-reads every iteration
    }
    s.DestroyRs(rs2);
}
} // namespace msg

// 1400b39e0 CMapGroup::SetOSConnectStatus
namespace msg {
void CMapGroup::SetOSConnectStatus(uint32_t serverId, char on, SeamsOsStatus& s) {
    if (!s.Found(this, serverId)) { s.LogNotFound(serverId); return; }
    s.SetFlag(this, serverId, on);             // node +0x30
    if (on == 0) {
        void* u = s.UserByServer(m_ServerId);
        void* l = s.UserList(u);
        s.UserListSet(l, serverId, 0);
        s.Post(m_pPort, 6, 0x3f1, 4, &serverId);
    } else {
        void* inst = s.CurrentInstance();
        if (inst != nullptr && m_Flg77c != 0) {
            void* mod = s.Module(inst, 0x25);
            if (mod != nullptr) s.ModuleNotify(mod, serverId);
        }
    }
    if (m_Flg77c == 0) return;
    uint32_t rec = s.NodeNpc(this, serverId);  // node +0x44
    void* u2 = s.UserByServer(m_ServerId);
    void* nm = s.NpcMgr(u2);
    void* npc = s.NpcGet(nm, rec);
    void* attached = nullptr;
    if (npc == nullptr || s.NpcAttach(npc, 0x1040, &attached) == 0) {
        s.LogNpcNotFound(rec);
        return;
    }
    uint32_t x, y, z;
    if (on == 0) {
        x = s.PosX(attached);
        y = s.PosY(attached);
        z = s.PosZ(attached);
    } else {
        void* sub = *(void**)((uint8_t*)attached + 0xc0);   // local_res8[0xc]
        if (sub == nullptr) s.LogCheck(0); else x = s.SubVar(sub, 0x13);
        sub = *(void**)((uint8_t*)attached + 0xc0);
        if (sub == nullptr) s.LogCheck(0); else y = s.SubVar(sub, 0x14);
        sub = *(void**)((uint8_t*)attached + 0xc0);
        if (sub == nullptr) s.LogCheck(0); else z = s.SubVar(sub, 0x15);
    }
    if (s.ChangePos(attached, x, y, z) == 0) {
        s.LogChangePosFailed(rec, x, y, z);
    }
}
} // namespace msg

// 1400a6190 CMapGroup::SendModMultiClientMsg
namespace msg {
int CMapGroup::SendModMultiClientMsg(const uint32_t* ids, size_t n, void* msg) {
    if (msg == nullptr) return 0;
    uint16_t size = *(uint16_t*)((uint8_t*)msg + 8);      // 16-bit here
    if ((int)(kMultiCap - (uint32_t)size) < 0) {
        m_Multi.LogSize();
        return 0;
    }
    if (n == 0) return 0;
    int cap = (int)((uint32_t)(kMultiCap - (uint32_t)size) >> 2);
    if (cap < 2 || (int)n < 2) {
        // single-mod path: one object per call, ids appended by the callee
        uint32_t srv;                       // RAW does an unaligned load at +0xd
        std::memcpy(&srv, (uint8_t*)this + 0xd, 4);
        void* o = m_Multi.CreateMod(srv, 0xffffffff,
                                    *(uint16_t*)((uint8_t*)msg + 0xa),
                                    (uint8_t*)msg + 0xc);
        if (o == nullptr) { m_Multi.LogCheck(0x80e); return 0; }
        int cnt = 0;
        size_t i = 0;
        for (;;) {
            if (i >= n) break;
            m_Multi.SendOne(this, ids[i], o);
            cnt = cnt + 1;
            if (kMultiDeadLoop < cnt) { m_Multi.LogDeadLoop(); break; }
            i = i + 1;
        }
        m_Multi.DestroySendObj(o);                        // vt[0](o, 1)
        return 1;
    }
    // batch path: {count@0, f4@4, size@8, body@0xc, ids@0xc+size}
    uint8_t hdr[0x418];
    std::memset(hdr, 0, sizeof hdr);
    uint16_t k = *(uint16_t*)((uint8_t*)msg + 0xa);
    std::memcpy(hdr + 4, &k, 2);
    std::memcpy(hdr + 8, &size, 2);
    std::memcpy(hdr + 0xc, (uint8_t*)msg + 0xc, size);
    void* port = m_pPort;                                 // this + 0x80
    size_t idx = 0;
    uint32_t total = 0;
    do {
        uint32_t batch = 0;
        for (;;) {
            if ((int)batch >= cap) break;
            if (idx >= n) break;
            union { uint32_t u; uint8_t b[4]; } v;
            v.u = ids[idx];
            std::memcpy(hdr + 0xc + size + batch * 4, v.b, 4);
            batch = batch + 1;
            total = total + 1;
            idx = idx + 1;
        }
        if ((int)batch > 0) {
            uint32_t cnt = batch;
            std::memcpy(hdr, &cnt, 4);
            m_Multi.PostBatch753e(port, 1, 0x753e, 0x418, hdr);
        }
    // RAW's outer loop only tests total < 0x7d1 and re-enters the filler even
    // after the id list is exhausted, so it reads past the vector end until
    // the counter reaches 2001. The port keeps the same structure and the same
    // cap but stops at the end of the list instead of reading past it; that
    // single deviation is declared in the handoff.
    } while (total < 0x7d1 && idx < n);
    m_Multi.LogDeadLoop();                                // RAW logs it here always
    return 1;
}
} // namespace msg

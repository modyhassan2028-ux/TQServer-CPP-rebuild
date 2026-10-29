#include "mapgroupkernel.h"
namespace msg {
int CMapGroupKernel::InitOnlyOnce(SMapGroupKernelSeams& s) {
    if (m_Type == 0xe) {
        m_pAdapter = s.AdapterCreate(0xe);
        if (m_pAdapter == nullptr) { s.AssertCreateFailed("!\"AdapterCreate\"", 0x94d); return 0; }
        m_pResponder = s.ResponderCreate(0xe);
        if (m_pResponder == nullptr) {
            if (m_pAdapter != nullptr) { s.DeleteAdapter(m_pAdapter); m_pAdapter = nullptr; }
            s.AssertCreateFailed("!\"ResponderCreate\"", 0x955);
            return 0;
        }
        uint8_t flag = s.GetFlag(s.UserByServer(m_Type));
        void*   oth  = s.GetOther(s.UserByServer(m_Type));
        int game = s.GameCreate(m_pAdapter, m_pResponder, oth, flag);
        m_pGame = nullptr;
        if (game == 0) {
            if (m_pAdapter != nullptr) { s.DeleteAdapter(m_pAdapter); m_pAdapter = nullptr; }
            if (m_pResponder != nullptr) {
                if (m_pResponder != nullptr) s.DestroyResponder(m_pResponder);
                m_pResponder = nullptr;
            }
            s.LogGameCrash(0x95e);
            s.Exit(1);                 // RAW exits the process here
            return 0;                  // unreachable in RAW
        }
        m_pGame = (void*)(intptr_t)game;
        int threadId = s.ThreadId(s.SelfThread(this));
        if (s.CheckServer(s.UserByServer((uint32_t)threadId)) == 0) {
            s.OnCheckFail(s.UserByServer((uint32_t)s.ThreadId(s.SelfThread(this))));
            return 0;
        }
        const uint32_t kinds[2] = {0x11, 0x12};
        for (int i = 0; i < 2; ++i) {
            void* holder = s.ProviderHolder(s.UserByServer(m_Type));
            void* p = s.FindProvider(holder, kinds[i], 1);
            if (p != nullptr) {
                void* gm = s.GlobalMgr();
                uint32_t sub = s.ProviderSub(p);
                uint32_t id  = s.ProviderId(p);
                s.GlobalReg(gm, id, sub);
            }
        }
        if (s.LoadWorld(s.AuctionOf(s.UserByServer(m_Type))) == 0) return 0;
        s.MgrD0(s.GlobalMgr());
        s.MgrE0(s.GlobalMgr());
        s.LoadAuction(s.AuctionOf(s.UserByServer(m_Type)));
        if (s.LoadAuction2(s.Auction2Of(s.UserByServer(m_Type))) == 0) s.LogAuction();
        void* mod = s.InstanceModule(s.CurrentInstance(), 8);
        if (mod == nullptr || s.ModuleInit(mod) == 0) {
            s.AssertCreateFailed("pIProider && pIProider->ProcessInit()", 0x985);
            return 0;
        }
        if (s.GetFlag(s.UserByServer(m_Type)) == 0) {
            void* m2 = s.InstanceModule(s.CurrentInstance(), 0x1c);
            if (m2 == nullptr || s.ModuleInit80(m2) == 0) { s.LogVexillum(); return 0; }
        } else {
            void* m3 = s.InstanceModule(s.CurrentInstance(), 0x25);
            if (m3 == nullptr || s.ModuleInit80(m3) == 0) { s.LogFrontier(); return 0; }
        }
        s.AfterInit();
        s.CallLua(s.LuaState(), "</F>Event_Server_Start", 0, 0, 0, 0);
    }
    return 1;
}
} // namespace msg

// 1400eb590 CMapGroupKernel::OnTimer
namespace msg {
static int g_TimerTick = 0;                     // DAT_140975ca4
// test hook only: the RAW counter is a file-level global, so tests reset it here
void ResetOnTimerCounter() { g_TimerTick = 0; }
int CMapGroupKernel::OnTimer(uint32_t tick, SeamsTimer& s) {
    g_TimerTick = g_TimerTick + 1;
    if (g_TimerTick < 4) {
        if (0 < g_TimerTick) {
            s.UserTick(s.UserByServer(m_Type), tick);
            return 1;
        }
    } else {
        g_TimerTick = 0;
    }
    for (;;) {
        uint32_t serial = s.LoginGet();
        if (serial == 0) break;
        SLoginEntry* e = s.FindLogin(this, serial);
        if (e == nullptr) {
            s.LogNoSerial(serial);              // falls through to the tick work
            break;
        }
        s.Post(m_pSelfThread, 4, 0xc351, 0x5c, &e->body[1]);
        s.EraseLogin(this, e);
    }
    if (m_pGame != nullptr && m_Type == 0xe) s.GameTick(m_pGame);
    uint32_t now = s.TimeSeconds();
    if ((uint32_t)((int)m_F40 + (int)m_F44) <= now) {
        m_F44 = s.TimeSeconds();
        s.TimerWork(this);
        s.GlobalTick();
        void* lua = s.LuaState();
        if (lua == nullptr) s.LogCheck(0x3cd);
        else s.LuaTick(lua);
        void* users = s.UserByServer(m_Type);
        if (*(void**)((uint8_t*)users + 0x100) == nullptr) s.LogCheck(0x144);
        else s.MagicTick(s.MagicOf(users));
    }
    return 1;
}
} // namespace msg

// ---- kernel senders, all posted through this+0x18 vt+0x50 ----
#include <cstring>
namespace msg {
int CMapGroupKernel::SendMsg(uint32_t msgId, int type, const void* body, int len,
                             SeamsSend& s) {
    if (body == nullptr) { s.LogNullMsg(); return 0; }
    if (type == 0)       { s.LogBadType(); return 0; }
    if (len + 4 < 0x401) {
        uint8_t f[0x418];
        *(uint32_t*)(f + 0) = msgId;
        *(int*)(f + 4)      = type;
        *(int*)(f + 8)      = len;
        if (len > 0) std::memcpy(f + 12, body, (size_t)len);
        s.Post(m_pSocket, 1, 0x7533, 0x418, f);          // this +0x18
        return 1;
    }
    s.LogOverflow(msgId, len);
    return 0;
}
int CMapGroupKernel::SendNpcMsg(uint32_t npcId, int type, const void* body, int len,
                                SeamsSend& s) {
    if (body == nullptr) { s.LogNpcNull(npcId, len); return 0; }
    if (type == 0)       { s.LogNpcBadType(npcId); return 0; }
    uint8_t f[0x418];                                    // no length guard here
    *(uint32_t*)(f + 0) = npcId;
    *(int*)(f + 4)      = type;
    *(int*)(f + 8)      = len;
    if (len > 0) std::memcpy(f + 12, body, (size_t)len);
    s.Post(m_pSocket, 1, 0x7534, 0x418, f);
    return 1;
}
int CMapGroupKernel::SendCrossMsg(uint32_t msgId, uint32_t s2s, int type,
                                  const void* body, int len, uint32_t flag,
                                  SeamsSend& s) {
    if (body == nullptr) { s.LogCrossNull(); return 0; }
    if (type == 0)       { s.LogCrossBadType(msgId); return 0; }
    if (len + 4 < 0x401) {
        uint8_t f[0x428];
        *(uint32_t*)(f + 0)  = msgId;
        *(uint32_t*)(f + 4)  = s2s;
        *(int*)(f + 8)       = type;
        *(int*)(f + 12)      = len;
        *(uint32_t*)(f + 16) = flag;
        if (len > 0) std::memcpy(f + 20, body, (size_t)len);
        s.Post(m_pSocket, 6, 0x3fc, 0, f);               // RAW passes no length
        return 1;
    }
    s.LogOverflow(msgId, len);
    return 0;
}
int CMapGroupKernel::SendCrossMsg2(uint32_t msgId, uint32_t s2s, const void* body,
                                   int len, uint32_t flag, SeamsSend& s) {
    if (body == nullptr) { s.LogCrossNull(); return 0; }
    if (msgId == 0)      { s.LogCrossBadType2(); return 0; }
    if (len + 4 < 0x401) {
        uint8_t f[0x428];
        *(uint32_t*)(f + 0)  = 0;                        // RAW zeroes the first field
        *(uint32_t*)(f + 4)  = s2s;
        *(uint32_t*)(f + 8)  = msgId;
        *(int*)(f + 12)      = len;
        *(uint32_t*)(f + 16) = flag;
        if (len > 0) std::memcpy(f + 20, body, (size_t)len);
        s.Post(m_pSocket, 6, 0x3fc, 0, f);
        return 1;
    }
    s.LogOverflow(msgId, len);
    return 0;
}
} // namespace msg

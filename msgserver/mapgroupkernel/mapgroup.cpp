// 140089140..140089660 — CMapGroup senders
#include "mapgroup.h"
#include <cstring>
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

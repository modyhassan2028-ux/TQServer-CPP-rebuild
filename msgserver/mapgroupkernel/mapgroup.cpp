// 140089140..140089660 — CMapGroup senders
#include "mapgroup.h"
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

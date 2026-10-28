#ifndef MAP_GROUP_H
#define MAP_GROUP_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\mapgroupkernel\mapgroup.cpp
// (proven: the path is in the __FILE__ table)
// Members from RAW: +0x68 serverId, +0x70 the kernel object.
#include <cstdint>
namespace msg {
struct SMapGroupMsg {           // the message block the senders fill
    uint8_t  hdr[0x410];
    uint32_t f410;              // +0x410 server id
    uint32_t f414;              // +0x414
    uint32_t f418;              // +0x418
    uint32_t f41c;              // +0x41c
};
struct SMapGroupSeams {
    void (*LogNullClient)(void);        // "CMapGroup::SendClientMsg, NULL message"
    void (*LogNullUser)(void);          // "CMapGroup::SendCrossMsg user id is null!"
    void (*LogNullCross)(void);         // "CMapGroup::SendCrossMsg, NULL message"
    void (*LogNullGs)(void);            // "CMapGroup::SendGSOrOSS2SMsg, NULL message"
    void (*LogNullNpc)(void);           // "CMapGroup::SendNpcMsg, NULL message"
    void (*LogBroadcastCreate)(void);   // "CMapGroup::BroadcastOtherServerMsg CMsgTalk Create Faild."
    int  (*KernelSendOne)(void* kernel, void* msg);                       // vt+0x08
    // vt+0x18: (kernel, id, x, body, len, flag)
    int  (*KernelSendCross3)(void* kernel, uint32_t id, uint32_t x,
                             const void* body, uint32_t len, uint32_t flag);
    // vt+0x20: (kernel, user, x, id, body, len, flag)
    int  (*KernelSendCross6)(void* kernel, uint32_t user, uint32_t x,
                             uint32_t id, const void* body, uint32_t len,
                             uint32_t flag);
    void (*TalkCtor)(void* t);                       // 14015b240
    void (*TalkDtor)(void* t);                       // 14015b2c0
    int  (*TalkCreate)(void* t, const char* g, const char* u, void* msg); // 14015b300
    int  (*SelfSend)(void* self, uint32_t a, void* msg, uint32_t ch);      // (*this+0x20)
};
class CMapGroup {
public:
    uint8_t m_Hdr[0x68];
    uint32_t m_ServerId;        // +0x68
    uint8_t m_Pad[4];
    void*    m_pKernel;         // +0x70
    int SendClientMsg(uint32_t ch, SMapGroupMsg* m, SMapGroupSeams& s);
    int SendCrossMsg(uint32_t userId, SMapGroupMsg* m, SMapGroupSeams& s);
    int SendCrossMsg(SMapGroupMsg* m, SMapGroupSeams& s);
    int SendGSOrOSS2SMsg(uint32_t s2s, SMapGroupMsg* m, SMapGroupSeams& s);
    int SendCrossMsg(uint32_t userId, uint32_t s2s, SMapGroupMsg* m,
                     uint32_t flag, SMapGroupSeams& s);
    int SendCrossMsg2(uint32_t s2s, SMapGroupMsg* m, uint32_t flag,
                      SMapGroupSeams& s);
    int SendNpcMsg(uint32_t ch, SMapGroupMsg* m, SMapGroupSeams& s);
    int BroadcastOtherServerMsg(void* msg, uint32_t a, uint16_t kind,
                                SMapGroupSeams& s);
};
} // namespace msg
#endif

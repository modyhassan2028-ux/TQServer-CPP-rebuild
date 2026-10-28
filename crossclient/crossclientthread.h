#ifndef CROSS_CLIENT_THREAD_H
#define CROSS_CLIENT_THREAD_H
// Original unit: f:\version\cqserver-78.0.11-1204\crossclient\
//                crossclientthread.cpp   (path proven by __FILE__)
//
// 14004c300 CCrossClientThread::OnProcess
//   tick 0x48 around WaitMessage(*(this+0x40), 0x14)   <- CONSTANT 20
//   tick 0x2b wraps the whole loop (no pacing tail, no counters)
//   loop: GetMessage(*(this+0x40), -1, -1, 0x418, rec)
//     id = rec.id  (dword at +0x04)
//     id != 0x3e9 ->
//        tick 0x2d;  if (*(u8*)(this+0x50) == 0) {
//            if (id == 0x3fc) { if (body.b0 != 0x9c4f) skip }
//            else if (id != 0x3f1 && id != 0x11173 && id != 0x11174) skip
//        }
//        if (!skip) 140054380(*(this+0x48), id, &body, rec.size)
//     id == 0x3e9 ->
//        tick 0x2c; if flag==0 -> next; if 140054160(kernel,&body)==0 -> next;
//        h = 140052920(kernel,&body); if h==0 -> next;
//        build: zero=0, ff=0xffffffff, v=h, kind=body.kind,
//               total=(u16)(body.len + 0x10),
//               memcpy(payload, body.payload, body.len)
//        send only if (body.len + 0x10) < 0x419 and total != 0
//        (*(*this + 0x28))(this, &packet) == 0 -> close 0x2c, 0x2b, return 1
//
// The header offsets below are the RAW stack slots:
//   in : +0x00 zero0, +0x04 id, +0x08 size, then body
//        body: +0x00 b0, +0x04 kind, +0x06 pad, +0x08 len, +0x0c payload
//   out: +0x00 (u16)0, +0x02 unwritten, +0x04 v, +0x08 0xffffffff,
//        +0x0c (u16)total, +0x0e (u16)kind, +0x10 payload
#include <cstdint>
namespace msg {
struct SCrossBody {
    uint32_t b0;                 // +0x00
    uint16_t kind;               // +0x04
    uint16_t pad;                // +0x06
    int32_t  len;                // +0x08
    uint8_t  payload[0x414];     // +0x0c (RAW local_42c[1044])
};
struct SCrossInPacket {
    uint32_t  zero0;             // +0x00
    uint32_t  id;                // +0x04
    uint32_t  size;              // +0x08
    SCrossBody body;             // +0x0c
};
struct SCrossOutPacket {
    uint16_t zero;               // +0x00 = 0
    uint16_t pad;                // +0x02
    int32_t  v;                  // +0x04
    uint32_t ff;                 // +0x08 = 0xffffffff
    uint16_t total;              // +0x0c = len + 0x10
    uint16_t kind;               // +0x0e
    uint8_t  payload[0x410];     // +0x10
};
class CCrossClientThread {
public:
    static const int kTickWait  = 0x48;
    static const int kTickBody  = 0x2b;
    static const int kTickLocal = 0x2d;
    static const int kTickClient= 0x2c;
    static const int kWaitMs    = 0x14;      // constant in RAW
    static const int kMsgLen    = 0x418;
    static const uint32_t kIdLocalTest = 0x3e9;
    static const uint32_t kIdB0Check   = 0x3fc;
    static const uint32_t kB0Expected  = 0x9c4f;
    static const int kOutMax    = 0x419;
    struct Seams {
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // +0x40 vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* rec);              // +0x40 vt+0x48
        void (*ProcessLocalMsg)(void* kernel, uint32_t id,
                                SCrossBody* body, uint32_t size); // 140054380
        int  (*IsClientBody)(void* kernel, SCrossBody* body);     // 140054160
        int  (*GetSession)(void* kernel, SCrossBody* body);       // 140052920
        int  (*SendBuiltPacket)(CCrossClientThread* self,
                                SCrossOutPacket* pkt);            // this vt+0x28
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pDrainer = nullptr;    // +0x40
    void*   m_pKernel  = nullptr;    // +0x48
    uint8_t m_pPad[8]  = {};
    uint8_t m_bFlag    = 0;          // +0x50
private:
    SCrossInPacket  m_In = {};
    SCrossOutPacket m_Out = {};
};
}
#endif

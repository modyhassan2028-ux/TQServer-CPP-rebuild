#ifndef IPAD_PAYMENTS_SOCKET_THREAD_H
#define IPAD_PAYMENTS_SOCKET_THREAD_H
// Original unit: f:\version\cqserver-78.0.11-1204\
//                ipadpaymentssocket\ipadpaymentssocketthread.cpp
//
// 140510960 CIPADPaymentsSocketThread::OnProcess
//   init once DAT_14097675c |= 1, DAT_140976758 = TimeGet(0)
//   WaitMessage(*(+0x40), DAT_140970740)     <-- a plain global slot
//   body tick 0x35, now = TimeGet(0)
//   idle -> tick 0x37 and NOTHING else (no OnTimer call at all);
//           while behind < 0x2711: pacing += 1000 else pacing = now
//   msg  -> tick 0x36: ok = ProcessMsg(this, hdr[1], buf, hdr[2])
//           (a DIRECT call to 1405108d0, not a vtable slot)
//           !ok -> "CIPADPaymentsSocketThread::OnProcess ProcessMsg
//                   returned error with packet:%d, port:%d"
//   tail: DAT_140970740 = 1000 - (t - pacing) while < 1000 else 0
#include <cstdint>
namespace msg {
class CIPADPaymentsSocketThread {
public:
    static const int kTickBody    = 0x35;
    static const int kTickMsg     = 0x36;
    static const int kTickOnTimer = 0x37;   // scope opened with no body
    static const int kPeriodMs    = 1000;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // +0x40 vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr);
        int  (*ProcessMsg)(void* self, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // 1405108d0
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_14097675c
        uint32_t* pPacing;        // DAT_140976758
        uint32_t* pWaitTimeout;   // DAT_140970740
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pDrainer = nullptr;   // +0x40
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
}
#endif

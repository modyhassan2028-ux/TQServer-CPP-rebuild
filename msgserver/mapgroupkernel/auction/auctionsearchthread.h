#ifndef AUCTION_SEARCH_THREAD_H
#define AUCTION_SEARCH_THREAD_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\
//                mapgroupkernel\auction\auctionsearchthread.cpp
//
// 1400f31f0 CAuctionSearchThread::OnProcess
//   NOTE: this family member has the two sub-objects SWAPPED -
//   the drainer is at +0x40 and the message port at +0x48.
//   init once DAT_140975cac |= 1, DAT_140975ca8 = TimeGet(0)
//   tick 0x4a around WaitMessage(*(+0x40), s+0x28)      <-- slot +0x28
//   body tick 0x32, now = TimeGet(0)
//   idle  -> tick 0x34: (*(+0x48)->vt+0x18)(port, now);
//            while behind < 0x2711: pacing += 2000 else pacing = now
//   msg   -> loop { (*(+0x40)->vt+0x48)(drainer,-1,-1,0x418,buf,hdr)
//                    tick 0x33: (*(+0x48)->vt+0x10)(port,hdr[1],buf,hdr[2])
//                    !ok -> "CAuctionSearchThread::OnProcess ProcessMsg
//                            returned error with packet:%d, port:%d" }
//   tail: wait(+0x28) = 2000 - (t - pacing) while < 2000 else 0
//   (nothing was created for code 0x46/0x47 in this thread)
#include <cstdint>
namespace msg {
class CAuctionSearchThread {
public:
    static const int kTickWait    = 0x4a;
    static const int kTickBody    = 0x32;
    static const int kTickMsg     = 0x33;
    static const int kTickOnTimer = 0x34;
    static const int kPeriodMs    = 2000;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // +0x40 vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr); // +0x40 vt+0x48
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // +0x48 vt+0x10
        void (*OnTimer)(void* port, uint32_t now);                // +0x48 vt+0x18
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_140975cac
        uint32_t* pPacing;        // DAT_140975ca8
        uint32_t* pWaitTimeout;   // s___AVCAuctionSearchThread___14094b928 + 0x28
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pDrainer = nullptr;   // +0x40  (swapped in this class)
    void*   m_pPort    = nullptr;   // +0x48
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
}
#endif

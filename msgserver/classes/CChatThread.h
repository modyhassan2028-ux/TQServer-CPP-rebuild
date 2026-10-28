#ifndef C_CHAT_THREAD_H
#define C_CHAT_THREAD_H
// 1400011b0 CChatThread::OnProcess
//   init once: DAT_1409754e4 |= 1, DAT_1409754e0 = TimeGet(0)
//   tick 0x49 around WaitMessage(drainer, s___AVCThreadBase+0x20)
//   tick 0x2f, now = TimeGet(0)
//   no message -> tick 0x31: (*(vt+0x18))(port, now);
//                 if (now - DAT < 0x2711) DAT += 2000 else DAT = now
//   messages    -> loop { (*(vt+0x48))(drainer,-1,-1,0x418,buf,hdr)
//                          tick 0x30: (*(vt+0x10))(port,hdr[1],buf,hdr[2])
//                          !ok -> "CChatThread::OnProcess ProcessMsg
//                                  returned error with packet:%d, port:%d" }
//   tail: t=TimeGet(0); if ((int)(t-DAT) < 2000) s+0x20 = 2000-(t-DAT)
//         else s+0x14..0x17 = 0 ; return 1
// Ports +0x40 (message port) and +0x48 (the drainer/waiter).
#include <cstdint>
namespace msg {
class CChatThread {
public:
    static const int kTickWait   = 0x49;
    static const int kTickOnTimer= 0x31;
    static const int kTickBody   = 0x2f;
    static const int kTickMsg    = 0x30;
    static const int kPeriodMs   = 2000;
    static const int kCatchUpMs  = 0x2711;
    static const int kMsgBufLen  = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr); // vt+0x48
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // vt+0x10
        void (*OnTimer)(void* port, uint32_t now);                // vt+0x18
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_1409754e4
        uint32_t* pPacing;        // DAT_1409754e0
        uint32_t* pWaitTimeout;   // s___AVCThreadBase___140949040 + 0x20
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pPort    = nullptr;   // +0x40
    void*   m_pDrainer = nullptr;   // +0x48
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
}
#endif

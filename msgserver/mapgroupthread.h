#ifndef C_MAP_GROUP_THREAD_H
#define C_MAP_GROUP_THREAD_H
// 14001d530 CMapGroupThread::OnProcess
//   init once: DAT_140975504 |= 1, DAT_140975500 = TimeGet(0)
//   tick 0x47 around WaitMessage(drainer, s+0x20)
//   tick 0x00, now = TimeGet(0)
//   no message -> tick 0x0c: (*(vt+0x20))(port, now);
//                 if (now - DAT < 0x2711) DAT += 0x7d else DAT = now
//   messages    -> loop { (*(vt+0x48))(drainer,-1,-1,0x418,buf,hdr)
//                          tick 0x01: (*(vt+0x18))(port,hdr[1],buf,hdr[2])
//                          !ok -> "CMapGroupThread::OnProcess ProcessMsg
//                                  returned error with packet:%d, port:%d" }
//   k = (*(vt+0x08))(drainer); idx = (uint32)(k - 0x0e);
//   t = TimeGet(0); spent = t - now;
//   if (idx < 5):  sum[idx] += spent; count[idx] += 1;
//                  if (max[idx] < spent) max[idx] = spent;
//   if ((int)(t - DAT) < 0x7d) s+0x20 = 0x7d-(t-DAT) else s+0x20 = 0
#include <cstdint>
namespace msg {
class CMapGroupThread {
public:
    static const int kTickWait    = 0x47;
    static const int kTickBody    = 0x00;
    static const int kTickOnTimer = 0x0c;
    static const int kTickMsg     = 0x01;
    static const int kPeriodMs    = 0x7d;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    static const int kKindBase    = 0x0e;
    static const int kKindSlots   = 5;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr); // vt+0x48
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // vt+0x18
        void (*OnTimer)(void* port, uint32_t now);                // vt+0x20
        int  (*GetKernelIndex)(void* drainer);                    // vt+0x08
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t*  pInitFlag;     // DAT_140975504
        uint32_t*  pPacing;       // DAT_140975500
        uint32_t*  pWaitTimeout;  // s+0x20
        int32_t*   pSpentSum;     // DAT_1409756c4[5]
        int32_t*   pSpentCount;   // DAT_1409756d8[5]
        int32_t*   pSpentMax;     // DAT_1409756b0[5]
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

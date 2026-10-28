#ifndef WORLD_KERNEL_H
#define WORLD_KERNEL_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\worldkernel\
//                worldkernel.cpp / worldkernel.h   (path proven by __FILE__)
//
// 14002e990 CWorldThread::OnProcess
//   init once DAT_140975a90 |= 1, DAT_140975a8c = TimeGet(0)
//   wait: tick 0x1d, WaitMessage(drainer, s___AVCWorldThread___1409499c8+0x20)
//   body tick 0x1f... exactly: tick 0x1d before the wait, then tick 0x1f
//   idle: tick 0x1e -> (*(vt+0x18))(port, now); pacing += 1000 while behind < 0x2711
//   msg : tick 0x1e -> (*(vt+0x10))(port, hdr[1], buf, hdr[2]);
//         !ok -> "CWorldThread::OnProcess ProcessMsg returned error with packet:%d, port:%d"
//   tail: spent = t2 - now; sum/max/count at DAT_1409756a8/6a4/6ac;
//         wait = 1000 - (t - pacing) while < 1000 else 0
//
// 14002e580 CUserLoginThread::OnProcess
//   init once DAT_140975a88 |= 1, DAT_140975a84 = TimeGet(0)
//   WaitMessage(drainer, DAT_1409499a8)   <- a plain global, NOT s+0x20
//   tick 0x20 is entered AFTER the wait (RAW construction order differs
//   from the other threads), body tick 0x20, idle tick 0x22, msg tick 0x21
//   period 2000, catch-up 0x2711, wait slot DAT_1409499a8
//   !ok -> "CUserLoginThread::OnProcess ProcessMsg returned error with
//           packet:%d, port:%d"
#include <cstdint>
namespace msg {
// ---------------------------------------------------------------- world
class CWorldThread {
public:
    static const int kTickWait    = 0x1d;
    static const int kTickMsg     = 0x1e;
    static const int kTickOnTimer = 0x1f;
    static const int kPeriodMs    = 1000;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr);
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // vt+0x10
        void (*OnTimer)(void* port, uint32_t now);                // vt+0x18
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_140975a90
        uint32_t* pPacing;        // DAT_140975a8c
        uint32_t* pWaitTimeout;   // s___AVCWorldThread___1409499c8 + 0x20
        int32_t*  pSpentSum;      // DAT_1409756a8
        int32_t*  pSpentCount;    // DAT_1409756ac
        int32_t*  pSpentMax;      // DAT_1409756a4
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pPort    = nullptr;   // +0x40
    void*   m_pDrainer = nullptr;   // +0x48
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
// ----------------------------------------------------------- user login
class CUserLoginThread {
public:
    static const int kTickWait    = 0x20;
    static const int kTickMsg     = 0x21;
    static const int kTickOnTimer = 0x22;
    static const int kPeriodMs    = 2000;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr);
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);
        void (*OnTimer)(void* port, uint32_t now);
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_140975a88
        uint32_t* pPacing;        // DAT_140975a84
        uint32_t* pWaitTimeout;   // DAT_1409499a8
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

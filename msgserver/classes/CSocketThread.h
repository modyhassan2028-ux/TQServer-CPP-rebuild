#ifndef C_SOCKET_THREAD_H
#define C_SOCKET_THREAD_H
// 14002bbe0 CSocketThread::CreateThread(name, isSuspended)
//   if (!CThreadBase::CreateThread(this,"SocketThread",flag)) -> 0
//   p = 1404ff780(); *(this+0x40) = p;
//   if ((*(vt+0x08))(p, *(this+0x48), *(this+0x50))) -> 1
//   MessageBoxA(NULL,"CSocketThread::CreateThread failed",
//               "Conquer Online Server",0x10) -> 0
//
// 14002bd30 CSocketThread::OnProcess  (identical shape to the other
// threads; tick ids 0x23 / 0x2a / 0x24, period 0x4c, catch-up 0x2711,
// counters DAT_14097569c/+6a0/+698 and the wait slot at
// s___AVCSocketThread___140949888 + 0x20)
#include <cstdint>
namespace msg {
class CSocketThread {
public:
    static const int kTickWait    = 0x23;
    static const int kTickOnTimer = 0x2a;
    static const int kTickMsg     = 0x24;
    static const int kPeriodMs    = 0x4c;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        // creation
        int  (*BaseCreateThread)(void* self, const char* name, int flag);
        void* (*GetSocketKernel)();                    // 1404ff780
        int  (*KernelAttach)(void* kernel, void* a, void* b); // vt+0x08
        void (*MessageBox)(void* hwnd, const char* text,
                           const char* caption, unsigned type);
        // loop
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr);
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // vt+0x10
        void (*OnTimer)(void* port, uint32_t now);                // vt+0x20
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_1409759d0
        uint32_t* pPacing;        // DAT_1409759cc
        uint32_t* pWaitTimeout;   // s___AVCSocketThread___140949888+0x20
        int32_t*  pSpentSum;      // DAT_14097569c
        int32_t*  pSpentCount;    // DAT_1409756a0
        int32_t*  pSpentMax;      // DAT_140975698
    };
    int  CreateThread(int isSuspended, Seams& s);
    int  OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pKernel  = nullptr;   // +0x40
    void*   m_pDrainer = nullptr;   // +0x48
    void*   m_pExtra   = nullptr;   // +0x50
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
}
#endif

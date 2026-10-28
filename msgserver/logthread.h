#ifndef LOG_THREAD_H
#define LOG_THREAD_H
// 14001b2d0 CLogThread::OnProcess
//   PATH NOTE: no logthread source path exists in the __FILE__ table of
//   MsgServer.exe (the class never emits __FILE__), so this file's path
//   is INFERRED as msgserver\logthread.cpp and is declared as inferred
//   in NEXT_AGENT_HANDOFF.md.
//
//   init once DAT_1409754fc |= 1, DAT_1409754f8 = TimeGet(0)
//   has = WaitMessage(*(this+0x48), s___AVCLogThread___140949440+0x20)
//   tick 0x3c wraps everything after the wait
//   idle:
//     (*(port->vt+0x18))(port)                  <-- OnTimer, no args
//     dev = now - DAT_1409754f8
//     if (dev < 0x2711) DAT += 1000
//     else { build "error:: resync CLogThread::OnTimer cumulative
//            deviation %ldms" (0x740 buffer, forced NUL at +0x73f)
//            (*(port->vt+0x28))(port, this+0x50, buf, 1)   <-- write
//            DAT = now }
//   messages: GetMessage(drainer, -1, -1, 0x800, buf, hdr)   <-- 2048
//             tick 0x3d: (*(port->vt+0x10))(port, hdr[1], buf, hdr[2])
//             (the return value is IGNORED - no error log here)
//   tail: wait slot = 1000 - (t - DAT) while < 1000 else 0
#include <cstdint>
namespace msg {
class CLogThread {
public:
    static const int kTickBody = 0x3c;
    static const int kTickMsg  = 0x3d;
    static const int kPeriodMs = 1000;
    static const int kCatchUpMs= 0x2711;
    static const int kMsgBufLen= 0x800;
    static const int kResyncLen= 0x740;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // +0x48 vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr); // +0x48 vt+0x48
        void (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // +0x40 vt+0x10
        void (*OnTimer)(void* port);                              // +0x40 vt+0x18
        void (*WriteResync)(void* port, void* ctx, const char* text,
                            int flag);                            // +0x40 vt+0x28
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_1409754fc
        uint32_t* pPacing;        // DAT_1409754f8
        uint32_t* pWaitTimeout;   // s___AVCLogThread___140949440 + 0x20
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pPort    = nullptr;   // +0x40
    void*   m_pDrainer = nullptr;   // +0x48
    void*   m_pCtx     = nullptr;   // +0x50  (passed to the resync writer)
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
    char     m_Resync[kResyncLen] = {};
};
}
#endif

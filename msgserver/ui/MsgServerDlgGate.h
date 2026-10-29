#ifndef MSG_SERVER_DLG_GATE_H
#define MSG_SERVER_DLG_GATE_H
// ===== CMsgServerDlg::OnTimer lines 45-108: the shutdown gate =====
//
// Verbatim from FUN_140024860:
//   if (DAT_140975940 == 0 && WaitForSingleObject(*(p+0x208), 0x14) == 0) {
//       DAT_140975940 = 1;
//       copy "shutdown" (9 bytes) byte by byte into a local;
//       count its length by hand into a register that is never read;
//       socket->vtable[+0x50](socket, 2);   //  +0x1f0 holds the socket
//       p[0x210] = 0x32;  p[0x214] = TimeGet(0)/1000;
//   }
//   else if (p[0x214] == 0 ||
//            TimeGet(0)/1000 < (uint)(p[0x210] + p[0x214])) {
//       if (p[0x21c] != 0 && (uint)(p[0x21c] + p[0x218]) <= TimeGet(0)/1000) {
//           p[0x21c] = 0; p[0x218] = 0; p[0x1fc] = 3; 14001e540();  // no args
//       }
//   }
//   else {
//       p[0x214] = 0; p[0x210] = 0;
//       copy "kickoutall" (11 bytes) byte by byte; count and discard;
//       socket->vtable[+0x50](socket, 2);
//       p[0x218] = 10;  p[0x21c] = TimeGet(0)/1000;
//   }
//
// Quirks kept: the hand count is dead work; the "kickoutall" call is logged
// with no argument at all; the shutdown branch fires ONCE (the flag is global).
#include <cstdint>
#include <cstddef>

namespace msg {

struct SGateSeams {
    uintptr_t (*WaitEvent)(void* handle, uint32_t ms);   // WaitForSingleObject
    void  (*SocketCall50)(void* sock, int arg);          // vtable +0x50
    uint32_t (*TimeGet)(int mode);                       // tq::TimeGet(0)
    void  (*LogNoArgs)();                                // 14001e540 with no args
    int32_t* shutdownFlag;                               // DAT_140975940
    const char* shutdownText;                            // s_shutdown_1406e3cf8, 9
    const char* kickoutText;                             // s_kickoutall_1406e3ce8, 11
    uintptr_t waitResult;                                // set by WaitEvent
};

// the RAW's hand length count: lVar16 = -1; ... returns the same value it
// produces (0 - 1 - len), so the dead register can be asserted verbatim
long long HandLength(const char* s);

void OnTimerShutdownGate(void* pDlg, SGateSeams& s);

} // namespace msg
#endif

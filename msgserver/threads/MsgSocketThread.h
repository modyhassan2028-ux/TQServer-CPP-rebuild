#ifndef MSG_SOCKET_THREAD_H
#define MSG_SOCKET_THREAD_H
// ===== Path-A wave 5:
// CSocketThread::OnProcess (14002bd30)
// VERBATIM — raw-objdump-verified =====
// Same shape as CMapGroupThread (A-4)
// with the socket deltas:
//  - statics: 0x1409759d0 flag /
//    0x1409759cc base
//  - tick ids 0x23 (process) / 0x2a
//    (kernel OnTimer) / 0x24 (ProcessMsg)
//  - ProcessMsg is kernel vt+0x10 and
//    takes FIVE raw args: (k, packet,
//    buf, info.arg8, info.port)
//  - slide/resync window 0x4c (76),
//    threshold cmp 0x2710
//  - stats are DIRECT dwords (no idx):
//    cum 0x14097569c lock xadd, cnt
//    0x1409756a0 lock add, max
//    0x140975698 via cmovl (branchless,
//    non-atomic)
//  - idle at 0x14094989c, window 0x4c
#include "MsgMapGroupThread.h"   // SMGMsgInfo

namespace msg {

struct SSocketSeams {
    uint32_t (*QGetId)(void* q);  // unused
    bool (*QWaitMsg)(void* q, int32_t f1,
        int32_t f2, uint32_t size,
        uint8_t* buf, SMGMsgInfo* info);
    bool (*QPeekMsg)(void* q,
                    uint32_t idleMs);
    // vt+0x10: 5 args raw
    bool (*KProcessMsg5)(void* k,
        uint32_t packet, uint8_t* buf,
        uint32_t arg8, uint32_t port);
    void (*KOnTimer)(void* k,
                     uint32_t nowMs);
    uint32_t (*TimeGet)();
    void (*TickOn)(uint32_t id);
    void (*TickOff)();
    void (*LogError)(const char* fmt,
        uint32_t packet, uint32_t port);
    void (*LogWarning)(const char* fmt);
};

extern SSocketSeams g_SocketSeams;

extern uint32_t g_SockFirstRun;  // 9759d0
extern uint32_t g_SockResyncBase;// 9759cc
extern uint32_t g_SockCum;       // 97569c
extern uint32_t g_SockCnt;       // 9756a0
extern uint32_t g_SockMax;       // 975698
extern uint32_t g_SockIdleMs;    // 94989c

void SockResetStatics();
uint32_t SocketOnProcess(uint8_t* pTh);

} // namespace msg
#endif

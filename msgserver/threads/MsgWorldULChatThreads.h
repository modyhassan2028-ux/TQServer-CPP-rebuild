#ifndef MSG_WORLD_UL_CHAT_THREADS_H
#define MSG_WORLD_UL_CHAT_THREADS_H
// ===== Path-A wave 6: CWorldThread /
// CUserLoginThread / CChatThread
// OnProcess — VERBATIM, raw-objdump
// verified (14002e990 / 14002e580 /
// 1400011b0) =====
// All three share the SAME raw shape
// (verified per-function):
//  - ProcessMsg: kernel vt+0x10 with
//    FIVE raw args (k, packet=
//    [info+4], buf, arg8=[info+8],
//    port=[info+0] as 5th stack arg)
//  - ERROR log: (packet=[info+4],
//    port=[info+0])
//  - kernel OnTimer: vt+0x18 (NOT
//    +0x20 like MapGroup/Socket)
//  - threshold cmp 0x2710, slide per
//    class
// Per-class raw deltas:
//  World     14002e990: flag
//    0x140975a90 base 0x140975a8c,
//    slide 1000, ticks 0x1d/0x1f
//    (OnTimer)/0x1e (ProcessMsg),
//    STATS: cum 0x1409756a8 lock
//    xadd, cnt 0x1409756ac lock add,
//    max 0x1409756a4, idle
//    0x1409499dc
//  UserLogin 14002e580: flag
//    0x140975a88 base 0x140975a84,
//    slide 2000, ticks 0x20/0x22/
//    0x21, NO stats, idle 0x1409499a8
//  Chat      1400011b0: flag
//    0x1409754e4 base 0x1409754e0,
//    slide 2000, ticks 0x2f/0x31/0x30
//    PLUS tick 0x49 around Peek
//    ("CChatThread WaitMsg"), NO
//    stats, idle 0x140949054
#include "MsgMapGroupThread.h"   // SMGMsgInfo

namespace msg {

struct SThreadSeams {
    bool (*QWaitMsg)(void* q, int32_t f1,
        int32_t f2, uint32_t size,
        uint8_t* buf, SMGMsgInfo* info);
    bool (*QPeekMsg)(void* q,
                    uint32_t idleMs);
    bool (*KProcessMsg5)(void* k,
        uint32_t packet, uint8_t* buf,
        uint32_t arg8, uint32_t port);
    void (*KOnTimer18)(void* k,
                       uint32_t nowMs);
    uint32_t (*TimeGet)();
    void (*TickOn)(uint32_t id);
    void (*TickOff)();
    void (*LogError)(const char* fmt,
        uint32_t packet, uint32_t port);
    void (*LogWarning)(const char* fmt);
};

extern SThreadSeams g_ThreadSeams;

// per-class statics
extern uint32_t g_WFirstRun,
       g_WResyncBase, g_WCum, g_WCnt,
       g_WMax, g_WIdleMs;
extern uint32_t g_ULFirstRun,
       g_ULResyncBase, g_ULIdleMs;
extern uint32_t g_CFirstRun,
       g_CResyncBase, g_CIdleMs;

void ThreadResetStatics();
uint32_t WorldOnProcess(uint8_t* pTh);
uint32_t UserLoginOnProcess(uint8_t* pTh);
uint32_t ChatOnProcess(uint8_t* pTh);

} // namespace msg
#endif

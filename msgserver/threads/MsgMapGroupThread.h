#ifndef MSG_MAPGROUP_THREAD_H
#define MSG_MAPGROUP_THREAD_H
// ===== Path-A wave 4:
// CMapGroupThread::OnProcess (14001d530)
// VERBATIM — raw-disassembly-verified
// (objdump 14001d530-14001d7e0) =====
// The thread object: +0x40 = kernel
// (CMapGroupKernel iface), +0x48 = the
// msg queue iface.
// The msg info written by WaitMsg
// (16 bytes; raw rsp+0x50):
//   +0x00 port   +0x04 packet
//   +0x08 arg58  (ProcessMsg 4th)
//   +0x0c arg5c
#include <cstdint>

namespace msg {

struct SMGMsgInfo {
    uint32_t nPort;    // [rsp+0x50]
    uint32_t nPacket;  // [rsp+0x54]
    uint32_t nArg58;   // [rsp+0x58]
    uint32_t nArg5c;   // [rsp+0x5c]
};

struct SMapGroupSeams {
    // the queue iface (this+0x48):
    //   vt+0x08: thread id
    uint32_t (*QGetId)(void* q);
    //   vt+0x48: WaitMsg(q, -1, -1,
    //     0x418, buf, &info) -> bool
    bool (*QWaitMsg)(void* q, int32_t f1,
        int32_t f2, uint32_t size,
        uint8_t* buf, SMGMsgInfo* info);
    //   vt+0x58: PeekMsg(q, idleMs)
    //     -> bool (msg waiting?)
    bool (*QPeekMsg)(void* q,
                    uint32_t idleMs);
    // the kernel iface (this+0x40):
    //   vt+0x18: ProcessMsg(k, packet,
    //     buf, arg58) -> bool
    bool (*KProcessMsg)(void* k,
        uint32_t packet, uint8_t* buf,
        uint32_t arg58);
    //   vt+0x20: OnTimer(k, nowMs)
    void (*KOnTimer)(void* k,
                     uint32_t nowMs);
    uint32_t (*TimeGet)();
    // CTickAnalyst ctor/dtor (id)
    void (*TickOn)(uint32_t id);
    void (*TickOff)();
    // log_InlineLogERROR /
    // log_InlineLogWARNING (raw: the
    // WARNING passes NO args — only
    // the format)
    void (*LogError)(const char* fmt,
        uint32_t packet, uint32_t port);
    void (*LogWarning)(const char* fmt);
};

extern SMapGroupSeams g_MapGroupSeams;

// the raw statics
extern uint32_t g_MGFirstRun;   // 975504
extern uint32_t g_MGResyncBase; // 975500
extern uint32_t g_MGCum[5];     // 9756c4
extern uint32_t g_MGCnt[5];     // 9756d8
extern uint32_t g_MGMax[5];     // 9756b0
extern uint32_t g_MGIdleMs;     // 949640

// reset ONLY by the binary's own
// first-run flag logic (keep for
// tests)
void MGResetStatics();

// the OnProcess body (returns 1)
uint32_t MapGroupOnProcess(
    uint8_t* pThread);

} // namespace msg
#endif

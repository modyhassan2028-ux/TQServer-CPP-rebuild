#ifndef MSG_STATUS_MONITOR_CMD_H
#define MSG_STATUS_MONITOR_CMD_H
// ===== Path-A wave 8a: CServerStatus
// Monitor command layer — VERBATIM,
// raw-objdump-verified =====
// ctor 140029ff0 / create 14002a480 /
// dtor 14002a510 / free 14002a070 /
// vec-alloc 140029150 / insert_n
// 14002a1d0 / insert 14002ac60 /
// push 14002ae40 / clear 14002a0e0 /
// HANDLER 14002aef0 / timer-check
// 14002adc0 / shutdown 14002ad90 =====
// Monitor object (0x70 bytes):
//   +0x00 main thread ptr
//   +0x08 interval dword (2 = 2s)
//   +0x0c next-report dword (sec)
//   +0x10 container {proxy@+0x10,
//     first@+0x28, last@+0x30,
//     cap@+0x38} — vector<socket>
//     with MSVC debug-iterator checks
//     (raw abort sites preserved)
//   +0x40 CRITICAL_SECTION
//   +0x68 event handle
// Commands (raw strings):
//   "get_run_info\r\n" "close_server\r\n"
//   "reset_crash_state\r\n"
//   "reset_dbserver_state\r\n"
// Replies: unknown -> "\r\n" (2),
//   known -> "OK\r\n" (4)
#include <cstdint>
#include <cstddef>

namespace msg {

struct SMSCmdSeams {
    void* (*New)(size_t n);          // op new
    void (*Del)(void* p);            // op delete
    void (*LogErrorFmt)(const char* f);
    uint32_t (*TimeGet)();           // ms
    int64_t* (*CrashTimeGet)();      // ptr to crash ts (sec)
    // (socket, WSABUF*, 1, &sent)
    int (*WSASend)(uint64_t sock,
        uint32_t len, const uint8_t* buf,
        uint32_t* sent);
    void (*EnterCS)(void* cs);
    void (*LeaveCS)(void* cs);
    void (*InitCS)(void* cs);
    void (*DelCS)(void* cs);
    // CloseHandle(handle)
    void (*CloseHandle)(uint64_t h);
    void (*SetCloseFlag)(void* mainTh,
                        uint32_t f);  // 14001f4b0
    // the report builder (A-8b)
    void (*BuildAndSend)(uint8_t* mon);
    void (*InvalidParam)();          // abort
    void (*ThrowBadAlloc)();
};

extern SMSCmdSeams g_MSCmdSeams;
extern uint8_t* g_pStatusMonitor;    // 0x140975948
extern uint32_t g_ResetDbState;      // 0x140975998

// ===== raw object helpers =====
static inline uint64_t& MQ(uint8_t* o, size_t off) {
    return *(uint64_t*)(o + off);
}
static inline uint32_t& MD(uint8_t* o, size_t off) {
    return *(uint32_t*)(o + off);
}
// container triple (abs offsets)
#define MON_FIRST(m) MQ((m), 0x28)
#define MON_LAST(m)  MQ((m), 0x30)
#define MON_CAP(m)   MQ((m), 0x38)
#define MON_PROXY(m) MQ((m), 0x10)

uint8_t* MonitorCtor(uint8_t* obj, void* mainTh);
int MonitorCreate(void* mainTh);
void MonitorDtor(uint8_t* mon, uint32_t bFreeSelf);
void MonitorTimerCheck(uint8_t* mon);
void MonitorShutdown();
// client entry: {+0x00 socket,
// +0x08 offset dword, +0x0c buf[]}
void MonitorHandleCmd(uint8_t* mon,
                      uint8_t* client);
// vector ops (raw, used by handler)
void VecPush(uint8_t* cont, uint8_t* client);
void VecClear(uint8_t* cont);

} // namespace msg
#endif

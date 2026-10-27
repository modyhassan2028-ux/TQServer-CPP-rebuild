#ifndef MSG_LOG_THREAD_H
#define MSG_LOG_THREAD_H
// ===== Path-A wave 1: CLogThread — VERBATIM
// from the raw decompile =====
// 14001b100 ctor: base + vtable + ILogKernel*(+0x40)
//   + msg-port(+0x48) + SafeCopy name (+0x50, 0x80)
// 14001b180 dtor
// 14001b1b0 create: ILogKernel::CreateNew ->
//   vcall+8(port, +0x50) -> CreateThread
//   ("LogThread")
// 14001b220 OnClose: leftover LOG_MSG_PORT ->
//   "error:: LOG_MSG_PORT have %d LOG not
//   print!" + vcall+0x28 + vcall+0x20 + null
// 14001b2d0 OnTimer: WaitMsg(+0x48, wait4);
//   miss -> vcall+0x18 + the resync machine
//   (DAT_1409754fc/4f8, deviation 0x2711,
//   "error:: resync CLogThread::OnTimer
//   cumulative deviation %ldms"); hit ->
//   drain loop vcall+0x48(-1,-1,0x800) ->
//   vcall+0x10 print; then next wait
// 14001b4e0 deleting dtor
#include <cstddef>
#include <cstdint>

namespace msg {

struct SLogThreadSeams {
    // CThreadBase
    void (*BaseCtor)(void* p);
    void (*BaseDtor)(void* p);
    bool (*CreateThread)(void* p, const char* name,
                         bool bWait);
    // ILogKernel::CreateNew + vtable:
    // +8 init(port, name), +0x10 print(level,
    //   buf, len), +0x18 idle, +0x20 close,
    //   +0x28 log(port, name, buf, sev)
    void* (*KernelNew)();
    bool (*KernelInit)(void* pKernel, void* port,
                       const char* name);
    void (*KernelPrint)(void* pKernel,
                        uint32_t a, const char* buf,
                        uint32_t b);
    void (*KernelIdle)(void* pKernel);
    void (*KernelClose)(void* pKernel);
    void (*KernelLog)(void* pKernel, const char* n,
                      const char* buf, int sev);
    // LOG_MSG_PORT vtable (at +0x48):
    // +0x10 count, +0x48 pop(-1,-1,0x800),
    // +0x58 wait(timeout)
    int (*PortCount)(void* port);
    bool (*PortPop)(void* port, int a, int b,
                    uint32_t c);
    bool (*PortWait)(void* port, uint32_t t);
    // tq
    uint32_t (*TimeGet)(int i);
    void (*SafeCopy)(char* dst, const char* src,
                     size_t n);
    void (*TickOpen)(void* p, int id);
    void (*TickClose)(void* p);
    // libc
    int (*Snprintf)(char* d, size_t n,
                    const char* fmt, ...);
};

extern SLogThreadSeams g_LogThreadSeams;

// the object: 0x100 = CThreadBase + 0x40
// kernel, 0x48 port, 0x50 name[0x80]
static const size_t kLogThreadSize = 0xd0;

void LogThreadCtor(void* pTh, void* pPort,
                   const char* name);
void LogThreadDtor(void* pTh);
bool LogThreadCreate(void* pTh, bool bWait);
void LogThreadOnClose(void* pTh);
bool LogThreadOnTimer(void* pTh);
void LogThreadOnDelete(void* pTh, uint32_t flags);

// the OnTimer resync globals (raw)
extern uint32_t g_LogTimerInit;   // 1409754fc
extern uint32_t g_LogTimerBase;   // 1409754f8
extern uint32_t g_LogNextWait;    // 140949440+0x14

} // namespace msg
#endif

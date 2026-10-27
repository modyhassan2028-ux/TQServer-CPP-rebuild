#ifndef MSG_SERVER_DLG_TIMER_H
#define MSG_SERVER_DLG_TIMER_H
// ===== MsgServer UI-3a: the ORIGINAL OnTimer
// state machines (from msgserverdlg.cpp in the
// raw decompile) =====
//
// FUN_140024860 (OnTimer core) + FUN_140026a90
// (the dialog OnTimer with the timer-2 auth state
// machine). Control flow, field offsets and
// constants are VERBATIM; not-yet-ported callees
// are a seam table so the dispatch is testable on
// Linux before their waves land.
//
// Dialog fields (from the raw):
//   +0x40  HWND (KillTimer/SetTimer/PostQuit)
//   +0x144/0x148 perf window (600s), +0x14c/0x150
//          save window (300s)
//   +0x158 CPerformanceInfo, +0x168 CThreadTimesInfo
//   +0x178 log thread, +0x180 async DB thread,
//   +0x188 worker thread array
//   +0x1b8,+0x1c0,+0x1c8,+0x1d8,+0x1e0,+0x1e8,
//   +0x228,+0x230,+0x238 the spawned threads
//   +0x1f0 kernel, +0x1fc server state:
//     0 -> 4 (idle -> closing)
//     1 -> 2 (spawn all threads -> running)
//     2     (periodic: perf/heap/save/stats)
//     3     (kernel closing)
//     4     (final: KillTimer(1) + shutdown)
//   +0x208 shutdown event HANDLE, +0x210/0x214
//          shutdown countdown (50s),
//   +0x218/0x21c kickall countdown (10s)
//   +0x2278 auth state: 0 reconnect, 1 verify,
//          3 done (KillTimer(2) + SetTimer(1,200))
//   +0x227c/+0x228c/+0x229c auth server strings
//   +0x22b0/+0x22b8 import stream,
//   +0x22bc/0x22c0 auth timeout (600s)
#include <cstddef>
#include <cstdint>

namespace msg {

struct SOnTimerSeams {
    uint64_t (*TimeGet)(int);          // tq::TimeGet
    void (*KernelBroadcastShutdown)(void* pKernel);
    uint32_t (*WaitShutdownEvent)(void* hEvent);
    void* (*SpawnThread)(int id, size_t cb);
    bool (*ThreadInit)(void* pThread);
    void (*ThreadResume)(void* pThread);
    void* (*ThreadHandle)(void* pThread);
    void (*AddThreadHandle)(void* pDlg, void* h);
    bool (*DatabaseInit)();
    void* (*MakeAsyncDB)();
    void* (*WorkerSlot)(void* pArr);
    void (*DlgLog)(void* pDlg, const char* s);
    void (*OnPeriodic)(void* pDlg);
    void (*OnKernelClosing)(void* pDlg);
    void (*OnState4Final)(void* pDlg);
    bool (*AuthConnect)(void* pClient, const char* ip);
    void (*AuthClose)(void* pClient);
    bool (*AuthIsConnected)(void* pClient);
    void (*AuthSendFail)(void* pClient, int len);
    bool (*ImportFunctions)(void* pBuf, uint32_t cb,
                            int a3);
    void* (*KbSetTimer)(void* pDlg, int id,
                        uint32_t ms);
    void (*KillTimer)(void* pDlg, int id);
    void (*PostQuit)(void* pDlg);
    int nReentrancy;    // DAT_14097593c
    int bShutdownSeen;  // DAT_140975940
    int nThreadCount;   // DAT_1409757d0
    int bShutdownFlag;  // DAT_1409758f0
};

extern SOnTimerSeams g_OnTimerSeams;

// FUN_140024860: the OnTimer core (timer 1 +
// the shutdown/kickall preamble)
void MsgOnTimerCore(void* pDlg, int nEvent);

// FUN_140026a90 body: the timer-2 auth machine
void MsgOnTimerAuth(void* pDlg, int nEvent);

} // namespace msg
#endif

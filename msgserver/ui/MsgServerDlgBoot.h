#ifndef MSG_SERVER_DLG_BOOT_H
#define MSG_SERVER_DLG_BOOT_H
// ===== CMsgServerDlg::OnTimer timer 1, states 0 and 1 (lines 110-375) =====
//
// The reentrancy gate is DAT_14097593c: a positive value bails out at once,
// otherwise it is raised for the duration and lowered again at LAB_140026533.
// Both the plain failures and the four `goto LAB_140026533` sites end at that
// same decrement with nothing else in between, so an early return here is
// exactly the RAW's control flow (documented, not simplified).
//
// state 0 -> 4 (nothing else).  state 1 -> 3 and the fifteen step boot chain:
//   the log thread (port 7, 0xd0), the async DB thread (0x40, "AsyncDBThread"),
//   port 2 (0x50), port 10 (0x50), the worker loop over DAT_1409757d0
//   (0x58 each, port i+0xe), port 4 (0x50), port 0xe then port 1 (0x58),
//   the optional 0x1d0 / 0x220 / 0x221 / 0x222 threads (ports 6, 9, 0xb, 0xd),
//   the resume sweep, state 2, two extra thread handles, and the two windows
//   (600 s at +0x144/+0x148, 300 s at +0x14c/+0x150).
// States 2, 3 and 4 are MsgOnTimerPeriodic / KernelClosing / State4Final.
#include <cstdint>
#include <cstddef>

namespace msg {

struct SBootSeams {
    // reentrancy guard, DAT_14097593c
    int32_t* reentrancy;
    // the manager pair
    void*  (*GetGlobalMgr)();                 // 140028960
    void   (*MgrBootStep)(void* mgr);         // 14002adc0
    int    (*ProcessOnce)(void* pDlg);        // 140021bd0
    void   (*InitStep1)(void* pDlg);          // 14001e720
    // threads
    void*  (*New)(size_t n);
    void   (*RegisterPort)(int port);         // 14050c340
    void   (*AddThreadHandle)(void* pDlg, void* h);   // CThreadTimesInfo
    void*  (*GetCurrentThread)();
    void*  (*GetThreadHandle)(void* thr);
    bool   (*StartVtable20)(void* thr);
    void   (*ResumeThread)(void* thr);
    // the individual factories (return the constructed thread)
    void*  (*MakeLogThread)(void* mem);       // 14001b100
    bool   (*StartLogThread)();               // 14001b1b0
    void   (*SetLogThreadStatus)(int st);     // tq::SetLogThreadStatus
    bool   (*DatabaseInit)();                 // DatabaseInit
    void   (*CtorAsyncDB)(void* mem);         // CAsyncDBThread::ctor
    void   (*SetAsyncDBVtable)(void* mem);
    bool   (*CreateThread)(void* thr, const char* name, bool start);
    void*  (*MakePort2)(void* mem);           // 14002e7e0
    bool   (*StartPort2)();                   // 14002e860
    void*  (*MakePort10)(void* mem);          // 1400f3060
    void*  (*MakeWorker)(void* mem);          // 14001d2d0
    void   (*PushWorker)(void* vec);          // 140024590 (+0x188)
    void*  (*WorkerAt)(void* vec, int i);     // 14001f5b0
    void*  (*MakePort4)(void* mem);           // 14002e3d0
    bool   (*StartPort4)();                   // 14002e450
    void*  (*MakeCross)(void* mem);           // 14002bb50
    void*  (*MakePort6)(void* mem);           // 14004c0a0
    void*  (*MakePort8)(void* mem);           // 140001000
    bool   (*StartPort8)();                   // 140001080
    void*  (*MakePort9)(void* mem);           // 14050ff20
    void*  (*MakePort11)(void* mem);          // 1400319c0
    void*  (*MakePort13)(void* mem);          // 140019520
    void*  (*MgrAuxHandle)(void* mgr);        // 14002ba80
    void*  (*DBAuxHandle)();                  // 1400018c0 + 140005550
    void   (*PerfInit)(void* pDlg, const char* tag);  // CPerformanceInfo::Init
    void   (*ThreadTimesInit)(void* pDlg);            // CThreadTimesInfo::Init
    void   (*Log)(void* pDlg, const char* text);      // 14001e540
    uint32_t (*TimeGet)(int mode);
    int32_t workerCount;                      // DAT_1409757d0
    // the three .rdata strings the RAW passes as &DAT_1406xxxxx (not decoded)
    const char* str3248;
    const char* str31a8;
    const char* str3160;
};

void OnTimerBootTimer1(void* pDlg, SBootSeams& s);

} // namespace msg
#endif

// ===== MsgServer UI-3a: the ORIGINAL OnTimer
// state machines — VERBATIM dispatch =====
// FUN_140024860 (timer-1 core + shutdown
// preamble) and FUN_140026a90 (timer-2 auth).
// Bodies of states 2/3 and the deep init
// branches are seams (their waves come next);
// every constant, offset, order and guard is
// verbatim from the raw decompile.
#include "MsgServerDlgTimer.h"

namespace msg {

SOnTimerSeams g_OnTimerSeams = {};

static uint32_t& F32(void* p, size_t off) {
    return *(uint32_t*)((char*)p + off);
}
static uint64_t& F64(void* p, size_t off) {
    return *(uint64_t*)((char*)p + off);
}

// the "shutdown" preamble + timer-1 machine
// ===== M: ORIGINAL FUN_140024860 VERBATIM =====
void MsgOnTimerCore(void* pDlg, int nEvent) {
    SOnTimerSeams& s = g_OnTimerSeams;
    uint64_t now;
    if (s.bShutdownSeen == 0 &&
        s.WaitShutdownEvent((void*)F64(pDlg, 0x208))
            == 0) {
        s.bShutdownSeen = 1;   // DAT_140975940
        // broadcast "shutdown" via kernel vcall+0x50
        s.KernelBroadcastShutdown(
            (void*)F64(pDlg, 0x1f0));
        F32(pDlg, 0x210) = 0x32;   // 50s countdown
        now = s.TimeGet(0);
        F32(pDlg, 0x214) =
            (uint32_t)(now / 1000);
    }
    else if (F32(pDlg, 0x214) == 0 ||
             (now = s.TimeGet(0),
              (uint32_t)(now / 1000) <
                  F32(pDlg, 0x210) +
                      F32(pDlg, 0x214))) {
        // inside the shutdown countdown: the
        // kickall branch (10s after countdown end)
        if (F32(pDlg, 0x21c) != 0 &&
            (now = s.TimeGet(0),
             (uint32_t)(F32(pDlg, 0x21c) +
                        F32(pDlg, 0x218)) <=
                 (uint32_t)(now / 1000))) {
            F32(pDlg, 0x21c) = 0;
            F32(pDlg, 0x218) = 0;
            F32(pDlg, 0x1fc) = 3;   // -> closing
            s.DlgLog(pDlg, nullptr);
        }
    }
    else {
        // shutdown countdown elapsed: kickall
        F32(pDlg, 0x214) = 0;
        F32(pDlg, 0x210) = 0;
        // broadcast "kickoutall" via vcall+0x50
        s.KernelBroadcastShutdown(
            (void*)F64(pDlg, 0x1f0));
        F32(pDlg, 0x218) = 10;
        now = s.TimeGet(0);
        F32(pDlg, 0x21c) = (uint32_t)(now / 1000);
    }

    if (nEvent != 1)
        return;
    // timer 1: reentrancy guard (DAT_14097593c) —
    // the guard jumps PAST the decrement (raw
    // LAB_140026a28); only the incrementing path
    // decrements (raw LAB_140026533)
    if (0 < s.nReentrancy)
        return;
    s.nReentrancy = s.nReentrancy + 1;
    {
        int st = (int)F32(pDlg, 0x1fc);
        if (st == 0) {
            F32(pDlg, 0x1fc) = 4;
        }
        else if (st == 1) {
            // the ORIGINAL thread-cascade (spawn
            // ids in the raw order):
            //   7 log (+0x178), DatabaseInit,
            //   AsyncDB (+0x180), 2 socket (+0x1c0),
            //   10 mapgroup0 (+0x1e0),
            //   14..N workers (+0x188 loop),
            //   4 (+0x1c8), 0xe/1 (+0x1b8),
            //   6 (+0x1d8), 8 (+0x1e8),
            //   9 (+0x228), 0xb (+0x238),
            //   0xd (+0x230)
            static const struct {
                int id; size_t cb; size_t off;
            } spawn[] = {
                {7,  0xd0, 0x178},
                {2,  0x50, 0x1c0},
                {10, 0x50, 0x1e0},
                {4,  0x50, 0x1c8},
                {0xe,0x58, 0x1b8},
                {1,  0x58, 0x1b8},
                {6,  0x68, 0x1d8},
                {8,  0x50, 0x1e8},
                {9,  0x50, 0x228},
                {0xb,0xb0, 0x238},
                {0xd,0x8d8,0x230},
            };
            bool bOK = true;
            for (size_t i = 0;
                 i < sizeof spawn / sizeof *spawn;
                 i++) {
                void* t = s.SpawnThread(
                    spawn[i].id, spawn[i].cb);
                F64(pDlg, spawn[i].off) =
                    (uint64_t)t;
                if (t == nullptr ||
                    !s.ThreadInit(t)) {
                    bOK = false; break;
                }
                s.AddThreadHandle(
                    pDlg, s.ThreadHandle(t));
            }
            // the worker threads (+0x188): id 14..
            if (bOK) {
                for (int i = 0;
                     i < s.nThreadCount; i++) {
                    void* t = s.SpawnThread(
                        14 + i, 0x58);
                    if (t == nullptr) {
                        if (i < s.nThreadCount)
                            goto LAB_DEC;
                        break;
                    }
                    void* slot = s.WorkerSlot(
                        (void*)((char*)pDlg +
                                0x188));
                    if (slot == nullptr ||
                        !s.ThreadInit(slot)) {
                        if (i < s.nThreadCount)
                            goto LAB_DEC;
                        break;
                    }
                    s.AddThreadHandle(
                        pDlg, s.ThreadHandle(slot));
                }
            }
            // the AsyncDB thread
            if (bOK && s.DatabaseInit()) {
                void* t = s.MakeAsyncDB();
                F64(pDlg, 0x180) = (uint64_t)t;
                if (t != nullptr &&
                    s.ThreadInit(t)) {
                    s.AddThreadHandle(
                        pDlg, s.ThreadHandle(t));
                }
            }
            if (bOK) {
                // resume in the ORIGINAL order
                s.ThreadResume(
                    (void*)F64(pDlg, 0x1c0));
                s.ThreadResume(
                    (void*)F64(pDlg, 0x1e0));
                for (int i = 0;
                     i < s.nThreadCount; i++)
                    s.ThreadResume(s.WorkerSlot(
                        (void*)((char*)pDlg +
                                0x188)));
                s.ThreadResume(
                    (void*)F64(pDlg, 0x1b8));
                s.ThreadResume(
                    (void*)F64(pDlg, 0x1c8));
                s.ThreadResume(
                    (void*)F64(pDlg, 0x1e8));
                if (F64(pDlg, 0x1d8) != 0)
                    s.ThreadResume(
                        (void*)F64(pDlg, 0x1d8));
                if (F64(pDlg, 0x228) != 0)
                    s.ThreadResume(
                        (void*)F64(pDlg, 0x228));
                if (F64(pDlg, 0x238) != 0)
                    s.ThreadResume(
                        (void*)F64(pDlg, 0x238));
                if (F64(pDlg, 0x230) != 0)
                    s.ThreadResume(
                        (void*)F64(pDlg, 0x230));
                F32(pDlg, 0x1fc) = 2;  // running
                F32(pDlg, 0x144) = 600;
                now = s.TimeGet(0);
                F32(pDlg, 0x148) =
                    (uint32_t)(now / 1000);
                F32(pDlg, 0x14c) = 300;
                now = s.TimeGet(0);
                F32(pDlg, 0x150) =
                    (uint32_t)(now / 1000);
            }
        }
        else if (st == 2) {
            MsgOnTimerPeriodic(pDlg);
            if (s.bShutdownFlag != 0)
                F32(pDlg, 0x1fc) = 3;
        }
        else if (st == 3) {
            MsgOnTimerKernelClosing(pDlg);
        }
        else if (st == 4) {
            s.KillTimer(pDlg, 1);
            MsgOnTimerState4Final(pDlg);
        }
        else {
            s.DlgLog(pDlg, nullptr);  // error line
        }
    }
LAB_DEC:
    s.nReentrancy = s.nReentrancy - 1;
LAB_END:
    ;
}

// ===== M: ORIGINAL FUN_140026a90 timer-2 body
// VERBATIM (auth state machine) =====
void MsgOnTimerAuth(void* pDlg, int nEvent) {
    SOnTimerSeams& s = g_OnTimerSeams;
    if (nEvent != 2)
        return;
    void* cli = (void*)((char*)pDlg + 0x240);
    int st = (int)F32(pDlg, 0x2278);
    if (st == 0) {
        // try 0x229c then 0x228c (verbatim)
        char* ip = (char*)pDlg + 0x229c;
        if (!s.AuthConnect(cli, ip)) {
            s.AuthClose(cli);
            ip = (char*)pDlg + 0x228c;
            if (!s.AuthConnect(cli, ip))
                s.AuthClose(cli);
        }
        if (s.AuthIsConnected(cli)) {
            F32(pDlg, 0x2278) = 1;
            // log "reconnect authserver(%s) success."
            s.DlgLog(pDlg, nullptr);
        }
    }
    else if (st == 1) {
        if (!s.AuthIsConnected(cli)) {
            // "authentication(%s) faild." -> state 3
            // + KillTimer(2) + PostQuit(0x12)
            s.DlgLog(pDlg, nullptr);
            F32(pDlg, 0x2278) = 3;
            s.KillTimer(pDlg, 2);
            s.PostQuit(pDlg);
        }
        else {
            // the import stream (raw: buffered at
            // DAT_140975938, flushed via +0x22b0)
            if (F64(pDlg, 0x22b0) != 0 &&
                s.ImportFunctions(
                    (void*)F64(pDlg, 0x22b0),
                    F32(pDlg, 0x22b8), 1)) {
                F32(pDlg, 0x22bc) = 0;
                F32(pDlg, 0x22c0) = 0;
                F32(pDlg, 0x2278) = 3;
                s.KillTimer(pDlg, 2);
                s.KbSetTimer(pDlg, 1, 200);
                // "authentication(%s) success."
                s.DlgLog(pDlg, nullptr);
            }
        }
    }
    // the auth timeout: 600s -> PostQuit
    if (F32(pDlg, 0x22c0) != 0 &&
        (uint32_t)(F32(pDlg, 0x22bc) +
                   F32(pDlg, 0x22c0)) <=
            (uint32_t)(s.TimeGet(0) / 1000)) {
        F32(pDlg, 0x22c0) = 0;
        F32(pDlg, 0x22bc) = 0;
        s.KillTimer(pDlg, 2);
        s.PostQuit(pDlg);
    }
}

// ===== M: ORIGINAL state-2 body (periodic)
// VERBATIM (FUN_140024860 case 2) =====
void MsgOnTimerPeriodic(void* pDlg) {
    SOnTimerSeams& s = g_OnTimerSeams;
    // perf window (600s @ +0x144)
    if (s.WindowElapsed(pDlg, 0x144)) {
        s.RecordPerf(pDlg);          // +0x158
        s.RecordThreads(pDlg, true); // +0x168
        s.HeapSaveLog(nullptr);      // g_MyHeapMgr
    }
    // save window (300s @ +0x14c)
    if (s.WindowElapsed(pDlg, 0x14c)) {
        s.SavePeriodic(pDlg);
    }
    // stats window: FUN_1400222e0(+0x134, 300)
    if (s.StatsWindowElapsed(pDlg, 300)) {
        // zero the client/npc/account counters
        // under LOCK/UNLOCK (DAT_1409756f8..b4)
        s.LogMessage(nullptr);
        // CCU deltas (DAT_1409756f0/6f4...)
        s.LogMessage(nullptr);
        // FromOSCCU (DAT_14097570c/710...)
        s.LogMessage(nullptr);
        // ToOSCCU (DAT_140975728/72c...)
        s.LogMessage(nullptr);
    }
    // the UI status windows + "Game server
    // online.txt" + the deadloop dump and the
    // message-pipe watchdog
    s.UpdateData(pDlg);
    s.WriteOnlineFile(pDlg);
    int nPipe = s.PipeMsgCount();
    if (10000 < nPipe &&
        nPipe == (nPipe / 1000) * 1000) {
        s.DlgLog(pDlg,
          "Message pipe block, server may be"
          " slowly!!!");
        s.LogError("dump all call stack:");
        s.DumpDeadLoops();
    }
}

// ===== M: ORIGINAL state-3 body (kernel closing)
// VERBATIM (FUN_140024860 case 3) =====
void MsgOnTimerKernelClosing(void* pDlg) {
    SOnTimerSeams& s = g_OnTimerSeams;
    s.DlgLog(pDlg, "Kernel closing...");
    s.RecordThreads(pDlg, true);
    s.WorldStop();
    // the ORIGINAL close order + timeouts:
    // first sweep: pre-close with short timeouts
    struct { size_t off; uint32_t ms; } pre[] = {
        {0x228, 2000}, {0x230, 3000}, {0x238, 4000},
        {0x1b8, 10000}, {0x1c8, 120000},
        {0x1e0, 3000},
    };
    for (size_t i = 0; i < 6; i++)
        if (F64(pDlg, pre[i].off) != 0)
            s.CloseThread((void*)F64(pDlg,
                pre[i].off), pre[i].ms);
    // the map-group array (+0x1a0..0x1a8)
    size_t nMap = (size_t)(
        (F64(pDlg, 0x1a8) - F64(pDlg, 0x1a0))
        >> 3);
    if (nMap != 0) {
        for (size_t i = 0; i < nMap; i++)
            s.CloseThread(*(void**)(
                (char*)F64(pDlg, 0x1a0) + i * 8),
                60000);
    }
    if (F64(pDlg, 0x1d8) != 0)
        s.CloseThread((void*)F64(pDlg, 0x1d8),
                      8000);
    if (F64(pDlg, 0x1c0) != 0)
        s.CloseThread((void*)F64(pDlg, 0x1c0),
                      4000);
    // second sweep: real close + release + null
    size_t close2[] = {0x228, 0x230, 0x238,
                       0x1b8, 0x1c8};
    for (size_t i = 0; i < 5; i++) {
        if (F64(pDlg, close2[i]) != 0) {
            bool b = s.CloseThread(
                (void*)F64(pDlg, close2[i]), 60000);
            s.DlgLog(pDlg, nullptr);  // ok/failed
            if (F64(pDlg, close2[i]) != 0) {
                s.ThreadRelease(
                    (void*)F64(pDlg, close2[i]), 0);
                F64(pDlg, close2[i]) = 0;
            }
            s.FlushLog(pDlg);
        }
    }
    // the map-group threads: close 300000 +
    // "Close map group thread[%d] failed!"
    nMap = (size_t)(
        (F64(pDlg, 0x1a8) - F64(pDlg, 0x1a0))
        >> 3);
    for (size_t i = 0; i < nMap; i++) {
        void** arr = (void**)F64(pDlg, 0x1a0);
        bool b = s.CloseThread(arr[i], 300000);
        s.DlgLog(pDlg, b ? nullptr
            : "Close map group thread[%d] failed!");
        if (arr[i] != 0) {
            s.ThreadRelease(arr[i], 0);
            arr[i] = 0;
        }
        s.FlushLog(pDlg);
    }
    // cross client / world / chat with their
    // original log lines
    struct { size_t off; const char* ok;
             const char* bad; } fin[] = {
        {0x1d8, nullptr, "Close cross client failed!"},
        {0x1c0, nullptr, "Close world thread failed!"},
        {0x1e8, "Close Chat Thread OK.",
                "Close Chat Thread Failed."},
    };
    for (size_t i = 0; i < 3; i++) {
        if (F64(pDlg, fin[i].off) != 0) {
            bool b = s.CloseThread(
                (void*)F64(pDlg, fin[i].off), 60000);
            s.DlgLog(pDlg, b ? fin[i].ok
                            : fin[i].bad);
            if (F64(pDlg, fin[i].off) != 0) {
                s.ThreadRelease(
                    (void*)F64(pDlg, fin[i].off), 1);
                F64(pDlg, fin[i].off) = 0;
            }
            s.FlushLog(pDlg);
        }
    }
    // socket thread (+0x1e0): ok/failed
    if (F64(pDlg, 0x1e0) != 0) {
        bool b = s.CloseThread(
            (void*)F64(pDlg, 0x1e0), 60000);
        s.DlgLog(pDlg, nullptr);
        if (F64(pDlg, 0x1e0) != 0) {
            s.ThreadRelease(
                (void*)F64(pDlg, 0x1e0), 1);
            F64(pDlg, 0x1e0) = 0;
        }
        s.FlushLog(pDlg);
    }
    // async DB thread (+0x180)
    if (F64(pDlg, 0x180) != 0) {
        bool b = s.CloseThread(
            (void*)F64(pDlg, 0x180), 60000);
        s.DlgLog(pDlg, nullptr);
        if (F64(pDlg, 0x180) != 0) {
            s.ThreadRelease(
                (void*)F64(pDlg, 0x180), 1);
            F64(pDlg, 0x180) = 0;
        }
        s.FlushLog(pDlg);
    }
    // the log thread (+0x178): "Close Log thread
    // OK."/"failed"
    if (F64(pDlg, 0x178) != 0) {
        bool b = s.CloseThread(
            (void*)F64(pDlg, 0x178), 60000);
        s.DlgLog(pDlg, b ? "Close Log thread OK."
                    : "Close Log thread failed.");
        if (F64(pDlg, 0x178) != 0) {
            s.ThreadRelease(
                (void*)F64(pDlg, 0x178), 1);
            F64(pDlg, 0x178) = 0;
        }
        s.FlushLog(pDlg);
    }
    s.DlgLog(pDlg, nullptr);
    s.FlushLog(pDlg);
    s.KernelRelease((void*)F64(pDlg, 0x1f0));
    s.FinalCleanup();
    F64(pDlg, 0x1f0) = 0;
    s.DbUninit();
    F32(pDlg, 0x1fc) = 4;
}

// ===== M: ORIGINAL state-4 body VERBATIM
// (FUN_140024860 case 4, after KillTimer(1)) =====
void MsgOnTimerState4Final(void* pDlg) {
    SOnTimerSeams& s = g_OnTimerSeams;
    s.State4Save();
    s.SleepMs(3000);
    if (s.bShutdownFlag != 0)
        s.ShellExec(pDlg);
    s.OnOK(pDlg);
}

} // namespace msg

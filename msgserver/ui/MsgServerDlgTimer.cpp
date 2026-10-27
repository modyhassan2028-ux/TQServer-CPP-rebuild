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
            s.OnPeriodic(pDlg);
            if (s.bShutdownFlag != 0)
                F32(pDlg, 0x1fc) = 3;
        }
        else if (st == 3) {
            s.OnKernelClosing(pDlg);
        }
        else if (st == 4) {
            s.KillTimer(pDlg, 1);
            s.OnState4Final(pDlg);
            // (raw: Sleep(3000) + optional
            // ShellExecute + OnOK)
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

} // namespace msg

// UI-3b unit test — the VERBATIM state bodies:
// periodic (case 2), kernel closing (case 3) and
// the final (case 4) of FUN_140024860
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgServerDlgTimer.h"
using namespace msg;

static uint64_t s_qFakeNow = 1000000;
static uint64_t TTimeGet(int) { return s_qFakeNow; }
static uint32_t TWait(void*) { return 1; }
static void* TSpawn(int, size_t) { return nullptr; }
static bool TInit(void*) { return true; }
static void TResume(void*) {}
static void* THandle(void* t) { return t; }
static void TAddHnd(void*, void*) {}
static bool TDB() { return true; }
static void* TAsync() { return nullptr; }
static void* TSlot(void*) { return nullptr; }
static void TLog(void*, const char*) {}
static void* TSetTimer(void*, int, uint32_t) {
    return nullptr;
}
static void TKill(void*, int) {}
static void TQuit(void*) {}
static bool TConnect(void*, const char*) {
    return true;
}
static void TCloseC(void*) {}
static bool TConned(void*) { return true; }
static void TSendFail(void*, int) {}
static bool TImport(void*, uint32_t, int) {
    return true;
}

// UI-3b seams
static int s_nPerfRec = 0, s_nThreadRec = 0,
           s_nHeap = 0, s_nSave = 0,
           s_nUpdate = 0, s_nOnline = 0,
           s_nDead = 0, s_nOK = 0,
           s_nShell = 0, s_nDb = 0,
           s_nKernel = 0, s_nFinal = 0,
           s_nWorld = 0;
static int s_nPipe = 0;
static bool s_bWin = true;
static bool TWin(void*, size_t) { return s_bWin; }
static void TRecPerf(void*) { s_nPerfRec++; }
static void TRecThreads(void*, bool) {
    s_nThreadRec++;
}
static void THeap(void*) { s_nHeap++; }
static void TSave(void*) { s_nSave++; }
static bool TStats(void*, uint32_t) { return false; }
static void TMsg(const char*) {}
static void TErr(const char*) {}
static int TPipe() { return s_nPipe; }
static void TDump() { s_nDead++; }
static void TUpdate(void*) { s_nUpdate++; }
static void TOnline(void*) { s_nOnline++; }
static void* TWorld() { s_nWorld++; return nullptr; }
// close recorder: (offset, timeout) pairs
static size_t s_aCloseOff[32];
static uint32_t s_aCloseMs[32];
static int s_nClose = 0;
static void* s_aRel[16]; static int s_nRel = 0;
static bool TClose(void* t, uint32_t ms) {
    s_aCloseOff[s_nClose] = (size_t)t; // id
    s_aCloseMs[s_nClose] = ms;
    s_nClose++;
    return true;
}
static void TRel(void* t, int) { s_aRel[s_nRel++] = t; }
static void TKernel(void*) { s_nKernel++; }
static void TDbUn() { s_nDb++; }
static void TFlush(void*) {}
static void TFinalC() { s_nFinal++; }
static void TSave4() {}
static void TSleep(uint32_t) {}
static void TShell(void*) { s_nShell++; }
static void TOnOK(void*) { s_nOK++; }

static uint8_t s_dlg[0x2400];
template<class T> T& F(size_t o) {
    return *(T*)((char*)s_dlg + o);
}
static void ResetSeams() {
    std::memset(&g_OnTimerSeams, 0,
                sizeof g_OnTimerSeams);
    std::memset(s_dlg, 0, sizeof s_dlg);
    g_OnTimerSeams.TimeGet = TTimeGet;
    g_OnTimerSeams.WaitShutdownEvent = TWait;
    g_OnTimerSeams.KernelBroadcastShutdown =
        [](void*){};
    g_OnTimerSeams.SpawnThread = TSpawn;
    g_OnTimerSeams.ThreadInit = TInit;
    g_OnTimerSeams.ThreadResume = TResume;
    g_OnTimerSeams.ThreadHandle = THandle;
    g_OnTimerSeams.AddThreadHandle = TAddHnd;
    g_OnTimerSeams.DatabaseInit = TDB;
    g_OnTimerSeams.MakeAsyncDB = TAsync;
    g_OnTimerSeams.WorkerSlot = TSlot;
    g_OnTimerSeams.DlgLog = TLog;
    g_OnTimerSeams.KbSetTimer = TSetTimer;
    g_OnTimerSeams.KillTimer = TKill;
    g_OnTimerSeams.PostQuit = TQuit;
    g_OnTimerSeams.AuthConnect = TConnect;
    g_OnTimerSeams.AuthClose = TCloseC;
    g_OnTimerSeams.AuthIsConnected = TConned;
    g_OnTimerSeams.AuthSendFail = TSendFail;
    g_OnTimerSeams.ImportFunctions = TImport;
    g_OnTimerSeams.WindowElapsed = TWin;
    g_OnTimerSeams.RecordPerf = TRecPerf;
    g_OnTimerSeams.RecordThreads = TRecThreads;
    g_OnTimerSeams.HeapSaveLog = THeap;
    g_OnTimerSeams.SavePeriodic = TSave;
    g_OnTimerSeams.StatsWindowElapsed = TStats;
    g_OnTimerSeams.LogMessage = TMsg;
    g_OnTimerSeams.LogError = TErr;
    g_OnTimerSeams.PipeMsgCount = TPipe;
    g_OnTimerSeams.DumpDeadLoops = TDump;
    g_OnTimerSeams.UpdateData = TUpdate;
    g_OnTimerSeams.WriteOnlineFile = TOnline;
    g_OnTimerSeams.WorldStop = TWorld;
    g_OnTimerSeams.CloseThread = TClose;
    g_OnTimerSeams.ThreadRelease = TRel;
    g_OnTimerSeams.KernelRelease = TKernel;
    g_OnTimerSeams.DbUninit = TDbUn;
    g_OnTimerSeams.FlushLog = TFlush;
    g_OnTimerSeams.FinalCleanup = TFinalC;
    g_OnTimerSeams.State4Save = TSave4;
    g_OnTimerSeams.SleepMs = TSleep;
    g_OnTimerSeams.ShellExec = TShell;
    g_OnTimerSeams.OnOK = TOnOK;
    s_nPerfRec = s_nThreadRec = s_nHeap = s_nSave =
    s_nUpdate = s_nOnline = s_nDead = s_nOK =
    s_nShell = s_nDb = s_nKernel = s_nFinal =
    s_nWorld = s_nClose = s_nRel = 0;
    s_nPipe = 0;
    s_bWin = true;
}

int main() {
    printf("UI3b start\n"); fflush(stdout);

    // ==== S1: the periodic body (case 2) ====
    {
        ResetSeams();
        MsgOnTimerPeriodic(s_dlg);
        assert(s_nPerfRec == 1);
        assert(s_nThreadRec == 1);
        assert(s_nHeap == 1);
        assert(s_nSave == 1);
        assert(s_nUpdate == 1);
        assert(s_nOnline == 1);
        assert(s_nDead == 0);
        // the message-pipe watchdog: 15000 (>
        // 10000 and multiple of 1000) -> dump
        s_nPipe = 15000;
        MsgOnTimerPeriodic(s_dlg);
        assert(s_nDead == 1);
        printf("S1 ok (periodic)\n"); fflush(stdout);
    }

    // ==== S2: the closing body (case 3) — the
    // ORIGINAL order and timeouts ====
    {
        ResetSeams();
        // fill all thread slots
        void* ids[] = {0,0,0,0};
        size_t offs[] = {0x228, 0x230, 0x238, 0x1b8,
                         0x1c8, 0x1e0, 0x1d8, 0x1c0,
                         0x1e8, 0x180, 0x178};
        for (size_t i = 0; i < 11; i++)
            F<uint64_t>(offs[i]) =
                (uint64_t)(0x100 + i);
        // the map-group array: 2 threads
        static uint64_t arr[2] = {0xaaa, 0xbbb};
        F<uint64_t>(0x1a0) = (uint64_t)arr;
        F<uint64_t>(0x1a8) =
            (uint64_t)((char*)arr + 16);
        F<uint64_t>(0x1f0) = 0x777;
        F<uint32_t>(0x1fc) = 3;
        MsgOnTimerKernelClosing(s_dlg);
        // first sweep: pre-close order+timeouts
        assert(s_aCloseOff[0] == 0x100 + 0
            && s_aCloseMs[0] == 2000);    // 0x228
        assert(s_aCloseMs[1] == 3000);    // 0x230
        assert(s_aCloseMs[2] == 4000);    // 0x238
        assert(s_aCloseMs[3] == 10000);   // 0x1b8
        assert(s_aCloseMs[4] == 120000);  // 0x1c8
        assert(s_aCloseMs[5] == 3000);    // 0x1e0
        assert(s_aCloseMs[6] == 60000);   // map0
        assert(s_aCloseMs[7] == 60000);   // map1
        assert(s_aCloseMs[8] == 8000);   // 0x1d8
        assert(s_aCloseMs[9] == 4000);   // 0x1c0
        // second sweep: 5 closes @60000
        for (int i = 10; i < 15; i++)
            assert(s_aCloseMs[i] == 60000);
        // map threads @300000
        assert(s_aCloseMs[15] == 300000);
        assert(s_aCloseMs[16] == 300000);
        // cross/world/chat/socket/asyncdb/log @60000
        for (int i = 17; i < 23; i++)
            assert(s_aCloseMs[i] == 60000);
        assert(s_nClose == 23);
        // all released slots nulled
        assert(F<uint64_t>(0x228) == 0);
        assert(F<uint64_t>(0x1c8) == 0);
        assert(F<uint64_t>(0x1e0) == 0);
        assert(F<uint64_t>(0x180) == 0);
        assert(F<uint64_t>(0x178) == 0);
        assert(arr[0] == 0 && arr[1] == 0);
        assert(F<uint64_t>(0x1f0) == 0);
        assert(s_nWorld == 1);
        assert(s_nKernel == 1);
        assert(s_nDb == 1);
        assert(s_nFinal == 1);
        assert(F<uint32_t>(0x1fc) == 4);
        printf("S2 ok (closing order)\n"); fflush(stdout);
    }

    // ==== S3: the final body (case 4) ====
    {
        ResetSeams();
        g_OnTimerSeams.bShutdownFlag = 1;
        MsgOnTimerState4Final(s_dlg);
        assert(s_nShell == 1);
        assert(s_nOK == 1);
        printf("S3 ok (final)\n"); fflush(stdout);
    }

    // ==== S4: the full machine integration:
    // state 3 via the dispatcher ====
    {
        ResetSeams();
        F<uint32_t>(0x1fc) = 3;
        F<uint64_t>(0x228) = 0x100;
        MsgOnTimerCore(s_dlg, 1);
        assert(s_nClose >= 2);   // pre + final
        assert(F<uint32_t>(0x1fc) == 4);
        // state 4 next tick: KillTimer(1)+final
        s_nOK = 0;
        MsgOnTimerCore(s_dlg, 1);
        assert(s_nOK == 1);
        printf("S4 ok (machine 3->4->OK)\n");
        fflush(stdout);
    }

    printf("UI3b ALL-OK\n");
    return 0;
}

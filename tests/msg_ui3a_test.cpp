// UI-3a unit test — the ORIGINAL OnTimer state
// machines: FUN_140024860 (timer-1 core) +
// FUN_140026a90 (timer-2 auth), seam-driven
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgServerDlgTimer.h"
using namespace msg;

static uint64_t s_qFakeNow = 1000000;
static uint64_t TTimeGet(int) { return s_qFakeNow; }
static uint32_t s_nWaitRet = 1;   // not signaled
static uint32_t TWait(void*) { return s_nWaitRet; }

static int s_nSpawn = 0;
static void* s_aSpawned[32];
static bool s_bSpawnOK = true;
static void* TSpawn(int id, size_t) {
    void* p = (void*)(0x1000 + s_nSpawn);
    s_aSpawned[s_nSpawn] = p;
    s_nSpawn++;
    return s_bSpawnOK ? p : nullptr;
}
static bool TInit(void* t) { return t != nullptr; }
static int s_nResume = 0;
static void TResume(void*) { s_nResume++; }
static void* THandle(void* t) { return t; }
static void* s_aHnd[64]; static int s_nHnd = 0;
static void TAddHnd(void*, void* h) {
    s_aHnd[s_nHnd++] = h;
}
static bool s_bDB = true;
static bool TDB() { return s_bDB; }
static void* TAsync() { return (void*)0xdead; }
static void* TSlot(void*) { return (void*)0x2000; }

static int s_nPeriodic = 0, s_nClosing = 0,
           s_nFinal = 0;
static void TPeriodic(void*) { s_nPeriodic++; }
static void TClosing(void*) { s_nClosing++; }
static void TFinal(void*) { s_nFinal++; }

static int s_nSetTimer = 0, s_nKill1 = 0,
           s_nKill2 = 0, s_nQuit = 0;
static void* TSetTimer(void*, int, uint32_t) {
    s_nSetTimer++; return nullptr;
}
static void TKill(void*, int id) {
    if (id == 1) s_nKill1++; else s_nKill2++;
}
static void TQuit(void*) { s_nQuit++; }

static int s_nConnect = 0;
static bool s_bConnectOK = true, s_bConn = true;
static bool s_bImport = true;
static void* TConn;
static bool TConnect(void*, const char*) {
    s_nConnect++; return s_bConnectOK;
}
static void TCloseC(void*) {}
static bool TConned(void*) { return s_bConn; }
static void TSendFail(void*, int) {}
static bool TImport(void*, uint32_t, int) {
    return s_bImport;
}
static void TLog(void*, const char*) {}

static uint8_t s_dlg[0x2400];
static void* D() { return s_dlg; }
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
    g_OnTimerSeams.OnPeriodic = TPeriodic;
    g_OnTimerSeams.OnKernelClosing = TClosing;
    g_OnTimerSeams.OnState4Final = TFinal;
    g_OnTimerSeams.KbSetTimer = TSetTimer;
    g_OnTimerSeams.KillTimer = TKill;
    g_OnTimerSeams.PostQuit = TQuit;
    g_OnTimerSeams.AuthConnect = TConnect;
    g_OnTimerSeams.AuthClose = TCloseC;
    g_OnTimerSeams.AuthIsConnected = TConned;
    g_OnTimerSeams.AuthSendFail = TSendFail;
    g_OnTimerSeams.ImportFunctions = TImport;
    s_nSpawn = s_nResume = s_nHnd = 0;
    s_nPeriodic = s_nClosing = s_nFinal = 0;
    s_nSetTimer = s_nKill1 = s_nKill2 = s_nQuit = 0;
    s_nConnect = 0;
    s_bSpawnOK = s_bDB = s_bConnectOK = s_bConn =
        s_bImport = true;
    s_nWaitRet = 1;
    F<uint64_t>(0x208) = (uint64_t)0x7777;
}

int main() {
    printf("UI3a start\n"); fflush(stdout);

    // ==== S1: timer-1 idle state 0 -> 4 ====
    {
        ResetSeams();
        MsgOnTimerCore(D(), 1);
        assert(F<uint32_t>(0x1fc) == 4);
        assert(g_OnTimerSeams.nReentrancy == 0);
        assert(s_nSpawn == 0);   // no cascade yet
        printf("S1 ok (state 0 -> 4)\n"); fflush(stdout);
    }

    // ==== S2: state 1 -> the full thread cascade
    // -> 2 (running) with timers armed ====
    {
        ResetSeams();
        F<uint32_t>(0x1fc) = 1;
        g_OnTimerSeams.nThreadCount = 2;
        MsgOnTimerCore(D(), 1);
        assert(F<uint32_t>(0x1fc) == 2);
        // 11 fixed spawns + 2 workers + AsyncDB
        assert(s_nSpawn >= 13);
        assert(F<uint64_t>(0x178) != 0);
        assert(F<uint64_t>(0x1e0) != 0);
        assert(F<uint64_t>(0x180) == 0xdead);
        // resume order count: 8 + 2 workers + opt 4
        assert(s_nResume >= 10);
        assert(F<uint32_t>(0x144) == 600);
        assert(F<uint32_t>(0x14c) == 300);
        printf("S2 ok (cascade -> running)\n");
        fflush(stdout);
    }

    // ==== S3: reentrancy guard (nReentrancy) ====
    {
        ResetSeams();
        g_OnTimerSeams.nReentrancy = 1;
        F<uint32_t>(0x1fc) = 1;
        MsgOnTimerCore(D(), 1);
        assert(F<uint32_t>(0x1fc) == 1);  // unchanged
        assert(s_nSpawn == 0);
        assert(g_OnTimerSeams.nReentrancy == 1);
        printf("S3 ok (reentrancy guard)\n");
        fflush(stdout);
    }

    // ==== S4: the shutdown preamble: event ->
    // countdown 50s, then kickall -> state 3 ====
    {
        ResetSeams();
        s_nWaitRet = 0;    // shutdown signaled
        F<uint32_t>(0x1fc) = 2;
        MsgOnTimerCore(D(), 1);
        assert(g_OnTimerSeams.bShutdownSeen == 1);
        assert(F<uint32_t>(0x210) == 0x32);
        // countdown elapsed: t >= start+50
        s_qFakeNow += 60000;
        MsgOnTimerCore(D(), 1);
        assert(F<uint32_t>(0x210) == 0);  // kickall
        assert(F<uint32_t>(0x218) == 10);
        // 10s later -> state 3 (kernel closing)
        s_qFakeNow += 20000;
        MsgOnTimerCore(D(), 1);
        assert(F<uint32_t>(0x1fc) == 3);
        assert(s_nPeriodic >= 1);
        printf("S4 ok (shutdown -> kickall -> 3)\n");
        fflush(stdout);
    }

    // ==== S5: state 4 -> KillTimer(1) + final ====
    {
        ResetSeams();
        F<uint32_t>(0x1fc) = 4;
        MsgOnTimerCore(D(), 1);
        assert(s_nKill1 == 1);
        assert(s_nFinal == 1);
        printf("S5 ok (state 4 final)\n"); fflush(stdout);
    }

    // ==== S6: timer-2 auth: 0 -> connect -> 1;
    // verify success -> 3 + SetTimer(1,200) ====
    {
        ResetSeams();
        F<uint32_t>(0x2278) = 0;
        MsgOnTimerAuth(D(), 2);
        assert(s_nConnect == 1);
        assert(F<uint32_t>(0x2278) == 1);
        // state 1: import stream ready -> success
        F<uint64_t>(0x22b0) = (uint64_t)0xabc;
        F<uint32_t>(0x22b8) = 32;
        MsgOnTimerAuth(D(), 2);
        assert(F<uint32_t>(0x2278) == 3);
        assert(s_nKill2 == 1);
        assert(s_nSetTimer == 1);   // the 200ms beat
        printf("S6 ok (auth -> heartbeat)\n");
        fflush(stdout);
    }

    // ==== S7: auth failure -> PostQuit; and the
    // 600s timeout -> PostQuit ====
    {
        ResetSeams();
        F<uint32_t>(0x2278) = 1;
        s_bConn = false;
        MsgOnTimerAuth(D(), 2);
        assert(F<uint32_t>(0x2278) == 3);
        assert(s_nKill2 == 1);
        assert(s_nQuit == 1);
        // timeout path
        ResetSeams();
        F<uint32_t>(0x2278) = 3;
        F<uint32_t>(0x22bc) = 0;
        F<uint32_t>(0x22c0) = 1;   // started 'now'
        s_qFakeNow += 700000;      // 700s later
        MsgOnTimerAuth(D(), 2);
        assert(s_nQuit == 1);
        assert(F<uint32_t>(0x22c0) == 0);
        printf("S7 ok (fail/timeout -> quit)\n");
        fflush(stdout);
    }

    printf("UI3a ALL-OK\n");
    return 0;
}

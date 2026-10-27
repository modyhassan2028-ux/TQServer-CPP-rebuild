// Path-A wave 2 test — CAsyncDBThread (DB.dll)
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "MsgAsyncDBThread.h"
using namespace msg;

static char s_aLogs[32][512];
static int s_nLogs = 0;
static bool s_bErr;
static void TLogMsg(const char* f, ...) {
    std::snprintf(s_aLogs[s_nLogs], 511, "%s", f);
    s_nLogs++; s_bErr = false;
}
static void TLogErr(const char* f, ...) {
    std::snprintf(s_aLogs[s_nLogs], 511, "%s", f);
    s_nLogs++; s_bErr = true;
}
static void TBaseC(void*) {} static void TBaseD(void*) {}
static int s_nClose; static uint32_t s_aCloseMs[4];
static void TClose(void*, uint32_t ms) {
    s_aCloseMs[s_nClose < 4 ? s_nClose++ : 3] = ms;
}
static void* TCreateEv() { return (void*)0xE1; }
static int s_aWaitMs[8]; static int s_nWait;
static int s_iWait;
static const int s_aWaitRes[] = {0, 0x102,
    (int)0xffffffffu, 7};
static int TWait(void*, uint32_t ms) {
    s_aWaitMs[s_nWait < 8 ? s_nWait++ : 7] =
        (int)ms;
    return s_aWaitRes[s_iWait];
}
static int s_nSet; static void TSet(void*) { s_nSet++; }
static int s_nClosedH; static void TCloseH(void* h) {
    assert(h == (void*)0xE1); s_nClosedH++;
}
static uint32_t TGetLast() { return 5; }
static bool TIsCross() { return false; }
static bool TGetGameCfg(char* h, uint32_t* p,
        char* u, char* d, char* pa, char* cs,
        uint32_t* sid, char*) {
    std::strcpy(h, "127.0.0.1"); *p = 3306;
    std::strcpy(u, "root"); std::strcpy(d, "cq");
    std::strcpy(pa, "pw"); std::strcpy(cs, "latin1");
    *sid = 7; return true;
}
static void* s_pMy = (void*)0x999;
static void* TMyInit() { return s_pMy; }
static int s_aOpt[8]; static int s_nOpt;
static void TOpt(void* m, int o, const void*) {
    assert(m == s_pMy);
    s_aOpt[s_nOpt < 8 ? s_nOpt++ : 7] = o;
}
static void* TConnect(void* m, const char* h,
        const char* u, const char*) {
    assert(m == s_pMy);
    assert(std::strcmp(h, "127.0.0.1") == 0);
    assert(std::strcmp(u, "root") == 0);
    return s_pMy;
}
static const char* TMyErr(void*) { return "err"; }
static int s_nMyClose;
static void TMyClose(void* m) {
    assert(m == s_pMy); s_nMyClose++;
}
static char s_aSQL[8][256]; static int s_nSQL;
static int TQuery(void*, const char* q, uint32_t) {
    std::snprintf(s_aSQL[s_nSQL < 8 ? s_nSQL++ : 7],
                  255, "%s", q);
    return 0;
}
static int s_nLock;
static void TLockE() { s_nLock++; }
static void TLockL() { s_nLock--; }

static SADBEntry s_ring[8];
static uint32_t s_ul[4], s_ser[4];

static void ResetAll() {
    std::memset(&g_AsyncDBSeams, 0,
        sizeof g_AsyncDBSeams);
    SAsyncDBSeams& s = g_AsyncDBSeams;
    s.BaseCtor = TBaseC; s.BaseDtor = TBaseD;
    s.CloseThread = TClose;
    s.CreateEventA = TCreateEv;
    s.WaitForSingleObject = TWait;
    s.SetEvent = TSet; s.CloseHandle = TCloseH;
    s.GetLastError = TGetLast;
    s.IsCrossServer = TIsCross;
    s.GetGameConfig = TGetGameCfg;
    s.MysqlInit = TMyInit;
    s.MysqlOptions = TOpt;
    s.MysqlRealConnect = TConnect;
    s.MysqlError = TMyErr;
    s.MysqlClose = TMyClose;
    s.RealQuery = TQuery;
    s.InlineLogMessage = TLogMsg;
    s.InlineLogError = TLogErr;
    s.LockEnter = TLockE;
    s.LockLeave = TLockL;
    g_ADBEvent = nullptr; g_ADBMysql = nullptr;
    g_ADBPort = 0;
    g_ADBHost[0] = g_ADBUser[0] = g_ADBPass[0] =
        g_ADBDb[0] = g_ADBCharset[0] = 0;
    g_ADBRing = s_ring; g_ADBRingCap = 8;
    g_ADBHead = 0; g_ADBCount = 0;
    for (auto& e : s_ring) e.pStr = nullptr;
    g_ULRing = s_ul; g_ULHead = 0;
    g_ULCount = 0; g_ULCap = 4;
    g_SerRing = s_ser; g_SerHead = 0;
    g_SerCount = 0; g_SerCap = 4;
    s_nLogs = 0; s_nClose = 0; s_nWait = 0;
    s_iWait = 0; s_nSet = 0; s_nClosedH = 0;
    s_nOpt = 0; s_nMyClose = 0;
    s_nSQL = 0; s_nLock = 0;
}

int main() {
    printf("TH2 start\n"); fflush(stdout);
    uint8_t th[0x100];

    // ==== S1: OnInit — event + config +
    // mysql option chain (0x14, 7, 3, 3) ====
    {
        ResetAll();
        ADBOnInit(th);
        assert(g_ADBEvent == (void*)0xE1);
        assert(g_ADBPort == 3306);
        assert(g_ADBMysql == s_pMy);
        assert(s_nOpt == 4);
        assert(s_aOpt[0] == 0x14 &&
               s_aOpt[1] == 7 &&
               s_aOpt[2] == 3 && s_aOpt[3] == 3);
        assert(std::strstr(s_aLogs[0],
            "got game server config"));
        assert(std::strstr(s_aLogs[1],
            "async DB OK"));
        printf("S1 ok (OnInit)\n"); fflush(stdout);
    }

    // ==== S2: OnProcess — TIMEOUT returns
    // true with NO drain; WAIT_FAILED logs
    // + GetLastError; 0 runs the drain ====
    {
        ResetAll();
        g_ADBEvent = (void*)0xE1;
        g_ADBMysql = s_pMy;
        s_iWait = 1;   // 0x102
        assert(ADBOnProcess(th));
        assert(s_aWaitMs[0] == 1000);
        assert(s_nSQL == 0);
        // WAIT_FAILED path
        s_iWait = 2;   // 0xffffffff
        assert(ADBOnProcess(th));
        assert(s_bErr);
        assert(std::strstr(
            s_aLogs[s_nLogs-1],
            "WaitForSingleObject error"));
        // signaled (0): drain executes
        s_iWait = 0;
        ADBExecuteAsyncSQL("UPDATE t SET a=1");
        assert(s_nSet == 1);   // SetEvent fired
        assert(ADBOnProcess(th));
        assert(s_nSQL == 1);
        assert(std::strcmp(s_aSQL[0],
            "UPDATE t SET a=1") == 0);
        printf("S2 ok (OnProcess)\n"); fflush(stdout);
    }

    // ==== S3: OnProcess with dead mysql ->
    // ReConnectDB (close + init + connect) ====
    {
        ResetAll();
        ADBOnInit(th);   // populate the config
        assert(g_ADBEvent == (void*)0xE1);
        s_iWait = 0;
        g_ADBMysql = nullptr;   // dead
        assert(ADBOnProcess(th));
        assert(s_nMyClose == 0);   // was null
        assert(g_ADBMysql == s_pMy);
        assert(std::strstr(
            s_aLogs[s_nLogs-1],
            "ReConnectDB async DB OK"));
        printf("S3 ok (reconnect)\n"); fflush(stdout);
    }

    // ==== S4: ExecuteAsyncSQL — no event =
    // refuse + log; with event: ring push +
    // wrap at cap 8 ====
    {
        ResetAll();
        assert(!ADBExecuteAsyncSQL("X"));
        assert(std::strstr(s_aLogs[0],
            "cannot execute SQL"));
        g_ADBEvent = (void*)0xE1;
        g_ADBMysql = s_pMy;   // executor active
        const char* q =
            "INSERT INTO logs VALUES(1)";
        // push 10 with drain interleaved:
        // push 8 (fills ring), drain, push 2
        for (int i = 0; i < 8; i++)
            assert(ADBExecuteAsyncSQL(q));
        assert(g_ADBCount == 8);
        ADBDrainExecSQL();
        assert(g_ADBCount == 0);
        assert(s_nSQL == 8);
        // head wrapped to 0
        assert(g_ADBHead == 0);
        for (int i = 0; i < 2; i++)
            assert(ADBExecuteAsyncSQL(q));
        assert(g_ADBCount == 2);
        ADBDrainExecSQL();
        assert(g_ADBCount == 0);
        // lock balanced everywhere
        assert(s_nLock == 0);
        printf("S4 ok (ring push/wrap)\n"); fflush(stdout);
    }

    // ==== S5: UserLoginGet + serial rings:
    // empty -> 0; FIFO order + wrap ====
    {
        ResetAll();
        assert(ADBUserLoginGet() == 0);
        g_ULRing[0] = 11; g_ULRing[1] = 22;
        g_ULRing[2] = 33; g_ULRing[3] = 44;
        g_ULCount = 4;
        assert(ADBUserLoginGet() == 11);
        assert(ADBUserLoginGet() == 22);
        assert(g_ULHead == 2);
        assert(ADBUserLoginGet() == 33);
        assert(ADBUserLoginGet() == 44);
        // wrap: head hit cap -> 0, count 0
        assert(g_ULHead == 0);
        assert(g_ULCount == 0);
        assert(ADBUserLoginGet() == 0);
        // serial ring same machine
        g_SerRing[0] = 1001; g_SerCount = 1;
        assert(ADBGetWorldUserLoginSerial() ==
               1001);
        assert(g_SerCount == 0);
        assert(ADBGetWorldUserLoginSerial() ==
               0);
        assert(s_nLock == 0);
        printf("S5 ok (rings)\n"); fflush(stdout);
    }

    // ==== S6: OnDestroy — leftovers logged
    // as "unexecuted", event closed+null ====
    {
        ResetAll();
        g_ADBEvent = (void*)0xE1;
        g_ADBRing[0].pStr = (char*)std::malloc(
            32); std::strcpy(g_ADBRing[0].pStr,
            "UPDATE x SET b=2");
        g_ADBRing[1].pStr = (char*)std::malloc(
            32); std::strcpy(g_ADBRing[1].pStr,
            "DELETE FROM y");
        g_ADBCount = 2;
        ADBOnDestroy(th);
        assert(g_ADBCount == 0);
        assert(s_nLogs == 2);
        assert(std::strstr(s_aLogs[0],
            "unexecuted async SQL"));
        assert(s_nClosedH == 1);
        assert(g_ADBEvent == nullptr);
        assert(s_nSQL == 0);   // NOT executed
        assert(s_nLock == 0);
        printf("S6 ok (OnDestroy)\n"); fflush(stdout);
    }

    printf("TH2 ALL-OK\n");
    return 0;
}

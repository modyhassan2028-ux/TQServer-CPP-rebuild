// Path-A wave 1 test — CLogThread VERBATIM
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgLogThread.h"
using namespace msg;

static uint64_t s_qNow = 500000;
static uint32_t TTime(int) { return (uint32_t)s_qNow; }
static void TBaseCtor(void*) {}
static void TBaseDtor(void*) {}
static bool TCreate(void*, const char* n, bool) {
    assert(std::strcmp(n, "LogThread") == 0);
    return true;
}
static void* TKernelNew() { return (void*)0x777; }
static bool TKernelInit(void* k, void* port,
                        const char* n) {
    assert(k == (void*)0x777);
    assert(port == (void*)0x888);
    assert(std::strcmp(n, "gamelog") == 0);
    return true;
}
static int s_nPrint = 0;
static void TPrint(void*, uint32_t, const char*,
                   uint32_t) { s_nPrint++; }
static int s_nIdle = 0;
static void TIdle(void*) { s_nIdle++; }
static int s_nClose = 0;
static void TClose(void*) { s_nClose++; }
static char s_aLastLog[0x740];
static int s_nKLog = 0;
static void TKLog(void*, const char*,
                  const char* buf, int sev) {
    assert(sev == 1);
    std::strncpy(s_aLastLog, buf,
                 sizeof s_aLastLog - 1);
    s_aLastLog[sizeof s_aLastLog - 1] = 0;
    s_nKLog++;
}
static int s_nPort = 0;   // pending msgs
static int s_nPopped = 0;
static int TPortCount(void*) { return s_nPort; }
static int s_aPopArgs[4]; static bool s_bPopMore;
static bool TPop(void*, int a, int b, uint32_t c){
    s_aPopArgs[0]=a; s_aPopArgs[1]=b;
    s_aPopArgs[2]=(int)c;
    if (s_nPopped < s_nPort) { s_nPopped++;
        return true; }
    return false;
}
static int s_nWaits = 0;
static uint32_t s_aWaitT[8];
static bool TPortWait(void*, uint32_t t) {
    s_aWaitT[s_nWaits < 8 ? s_nWaits : 7] = t;
    s_nWaits++;
    return s_bPopMore;   // msg available?
}
static void TSafeCopy(char* d, const char* s,
                      size_t n) {
    std::strncpy(d, s ? s : "", n - 1);
    d[n - 1] = 0;
}
static void TTickO(void*, int) {}
static void TTickC(void*) {}
static int TSnprintf(char* d, size_t n,
                     const char* f, ...) {
    int r = std::snprintf(d, n, "%s", f);
    return r;
}
static uint8_t s_th[0xd0];

static void ResetSeams() {
    std::memset(&g_LogThreadSeams, 0,
                sizeof g_LogThreadSeams);
    std::memset(s_th, 0, sizeof s_th);
    g_LogThreadSeams.BaseCtor = TBaseCtor;
    g_LogThreadSeams.BaseDtor = TBaseDtor;
    g_LogThreadSeams.CreateThread = TCreate;
    g_LogThreadSeams.KernelNew = TKernelNew;
    g_LogThreadSeams.KernelInit = TKernelInit;
    g_LogThreadSeams.KernelPrint = TPrint;
    g_LogThreadSeams.KernelIdle = TIdle;
    g_LogThreadSeams.KernelClose = TClose;
    g_LogThreadSeams.KernelLog = TKLog;
    g_LogThreadSeams.PortCount = TPortCount;
    g_LogThreadSeams.PortPop = TPop;
    g_LogThreadSeams.PortWait = TPortWait;
    g_LogThreadSeams.TimeGet = TTime;
    g_LogThreadSeams.SafeCopy = TSafeCopy;
    g_LogThreadSeams.TickOpen = TTickO;
    g_LogThreadSeams.TickClose = TTickC;
    g_LogThreadSeams.Snprintf = TSnprintf;
    s_nPrint = s_nIdle = s_nClose = s_nKLog =
    s_nWaits = s_nPopped = 0;
    s_nPort = 0;
    s_bPopMore = false;
    g_LogTimerInit = 0;
    g_LogTimerBase = 0;
    g_LogNextWait = 0;
    s_qNow = 500000;
}

int main() {
    printf("TH1 start\n"); fflush(stdout);

    // ==== S1: the ctor layout ====
    {
        ResetSeams();
        LogThreadCtor(s_th, (void*)0x888,
                      "gamelog");
        assert(*(uint64_t*)((char*)s_th + 0x40)
            == 0);
        assert(*(uint64_t*)((char*)s_th + 0x48)
            == 0x888);
        assert(std::strcmp(
            (char*)s_th + 0x50, "gamelog") == 0);
        // null name: no copy
        LogThreadCtor(s_th, (void*)0x888, nullptr);
        assert(std::strcmp(
            (char*)s_th + 0x50, "gamelog") == 0);
        printf("S1 ok (ctor)\n"); fflush(stdout);
    }

    // ==== S2: create — kernel new + init +
    // CreateThread("LogThread") ====
    {
        ResetSeams();
        LogThreadCtor(s_th, (void*)0x888,
                      "gamelog");
        assert(LogThreadCreate(s_th, true));
        assert(*(uint64_t*)((char*)s_th + 0x40)
            == 0x777);
        printf("S2 ok (create)\n"); fflush(stdout);
    }

    // ==== S3: OnTimer — first tick latches
    // base; miss -> idle + +=1000; next wait =
    // 1000-(now-base) ====
    {
        ResetSeams();
        LogThreadCtor(s_th, (void*)0x888,
                      "gamelog");
        s_qNow = 1000000;
        assert(LogThreadOnTimer(s_th));
        assert(g_LogTimerInit & 1);
        // RAW: base latches at 1000000 then the
        // miss path adds 1000 in the SAME tick
        assert(g_LogTimerBase == 1001000);
        assert(s_nIdle == 1);
        // 32-bit wait slot: 1000-(now-base)
        // = 1000-0xFFFFFC18 = 2000
        assert(g_LogNextWait == 2000);
        // +1100ms: dev=100 < 0x2711 -> +=1000
        s_qNow = 1001100;
        LogThreadOnTimer(s_th);
        assert(g_LogTimerBase == 1002000);
        assert(g_LogNextWait == 1900);
        printf("S3 ok (OnTimer miss/resync)\n");
        fflush(stdout);
    }

    // ==== S4: OnTimer — big deviation >=
    // 0x2711 -> the resync error + base=now ====
    {
        ResetSeams();
        LogThreadCtor(s_th, (void*)0x888,
                      "gamelog");
        s_qNow = 1000000;
        LogThreadOnTimer(s_th);   // base 1001000
        s_qNow = 1000000 + 21000;  // 21s drift
        LogThreadOnTimer(s_th);
        assert(s_nKLog == 1);
        assert(std::strstr(s_aLastLog, "resync")
            != nullptr);
        assert(g_LogTimerBase == 1021000);
        printf("S4 ok (resync error)\n");
        fflush(stdout);
    }

    // ==== S5: OnTimer — msg hit: the drain
    // loop pops ALL then prints each; wait 0
    // when caught up ====
    {
        ResetSeams();
        LogThreadCtor(s_th, (void*)0x888,
                      "gamelog");
        s_qNow = 1000000;
        s_bPopMore = true;   // WaitMsg got one
        s_nPort = 3;
        LogThreadOnTimer(s_th);
        assert(s_aPopArgs[0] == -1);
        assert(s_aPopArgs[1] == -1);
        assert(s_aPopArgs[2] == 0x800);
        // 3 pops (drained) then the 4th stops
        assert(s_nPopped == 3);
        printf("S5 ok (drain)\n"); fflush(stdout);
    }

    // ==== S6: OnClose — leftover -> the exact
    // error + kernel close + null ====
    {
        ResetSeams();
        LogThreadCtor(s_th, (void*)0x888,
                      "gamelog");
        *(uint64_t*)((char*)s_th + 0x40) = 0x777;
        s_nPort = 5;
        LogThreadOnClose(s_th);
        assert(s_nKLog == 1);
        assert(std::strstr(s_aLastLog,
                "LOG_MSG_PORT have") != nullptr);
        assert(s_nClose == 1);
        assert(*(uint64_t*)((char*)s_th + 0x40)
            == 0);
        // no leftover: just close
        s_nPort = 0; s_nKLog = 0;
        LogThreadOnClose(s_th);
        assert(s_nKLog == 0);
        printf("S6 ok (OnClose)\n"); fflush(stdout);
    }

    printf("TH1 ALL-OK\n");
    return 0;
}

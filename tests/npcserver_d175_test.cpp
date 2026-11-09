// D175 — NpcServer.exe 0x1400027f0 CKernelThread::OnProcess().
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static long long g_clockSeq[8] = {1000, 1200, 1400, 1500, 0, 0, 0, 0};
static int g_clockCalls = 0;
static unsigned long Clock(unsigned long long) { unsigned long v = (unsigned long)g_clockSeq[g_clockCalls < 7 ? g_clockCalls : 7]; ++g_clockCalls; return v; }

static int g_scopeIds[8] = {0,0,0,0,0,0,0,0};
static int g_scopeCtors = 0, g_scopeDtors = 0;
static void ScopeCtor(void* p, int nId) { (void)p; g_scopeIds[g_scopeCtors < 8 ? g_scopeCtors : 7] = nId; ++g_scopeCtors; }
static void ScopeDtor(void* p) { (void)p; ++g_scopeDtors; }

static int g_workCalls = 0, g_workArg = -1;
static bool Work(void* p, int nDelay) { (void)p; ++g_workCalls; g_workArg = nDelay; return true; }

static int g_recvTypes[4] = { 0x1fbd1, 0x1fbd2, 0x1234, 0 };
static int g_recvCalls = 0;
static long long g_recvBound = 0;
static bool Recv(void* p, long long a2, long long a3, long long uBound, void* pBody, void* pHeader) {
    (void)p; (void)a2; (void)a3;
    g_recvBound = uBound;
    if (g_recvCalls >= 3) return false;
    ((int*)pHeader)[1] = g_recvTypes[g_recvCalls];
    *(long long*)pBody = -1;                       // the fd word, so neither packet branch fires
    ++g_recvCalls;
    return true;
}

static int g_tickSlot1 = 0, g_tickSlot4 = 0;
static unsigned int g_tickArg = 0;
static void TickSlot1(void* p) { (void)p; ++g_tickSlot1; }
static void TickSlot4(void* p, unsigned int uValue) { (void)p; ++g_tickSlot4; g_tickArg = uValue; }
static int g_msgSlot0 = 0;
static const char* g_msgText = nullptr;
static void MsgSlot0(void* p, const char* s) { (void)p; ++g_msgSlot0; g_msgText = s; }

static int g_logs = 0;
static const void* g_logFmt = nullptr;
static int g_logArg = 0;
static void Log(const void* pFmt, ...) {
    ++g_logs; g_logFmt = pFmt;
    va_list ap; va_start(ap, pFmt); g_logArg = va_arg(ap, int); va_end(ap);
}
static int g_warns = 0;
static void Warn(const void* pFmt, unsigned long long uValue) { (void)pFmt; (void)uValue; ++g_warns; }

static unsigned char g_socket[0x840];

int main() {
    g_pfnNpcTimeGet = &Clock;
    g_pfnNpcTickAnalystCtor = &ScopeCtor;
    g_pfnNpcTickAnalystDtor = &ScopeDtor;
    g_pfnNpcInlineLogError = &Log;
    g_pfnNpcInlineLogWARNING = &Warn;
    std::memset(g_socket, 0, sizeof g_socket);

    // the null guard: both words are checked, and only the first message is logged
    {
        unsigned char obj[0x80];
        std::memset(obj, 0, sizeof obj);
        g_logs = 0; g_clockCalls = 0;
        assert(FUN_1400027f0((long long)obj) == 1);
        assert(g_logs == 1 && g_logFmt == (const void*)&g_symNpcStr_1400beab0);
        assert(g_clockCalls == 0);
        *(void**)(obj + 0x60) = g_socket;            // socket present, loop object missing
        g_logs = 0;
        assert(FUN_1400027f0((long long)obj) == 1);
        assert(g_logs == 1 && g_clockCalls == 0);
    }

    // the whole pass: three packets, then the tick and the counters
    {
        unsigned char obj[0x80];
        std::memset(obj, 0, sizeof obj);
        void* vLoop[12]; for (int i = 0; i < 12; ++i) vLoop[i] = (void*)&Recv;
        vLoop[9] = (void*)&Recv; vLoop[11] = (void*)&Work;
        void* loopObj[1] = { (void*)vLoop };
        void* vTick[5]; for (int i = 0; i < 5; ++i) vTick[i] = (void*)&TickSlot1;
        vTick[1] = (void*)&TickSlot1; vTick[4] = (void*)&TickSlot4;
        void* tickObj[1] = { (void*)vTick };
        void* vMsg[1] = { (void*)&MsgSlot0 };
        void* msgObj[1] = { (void*)vMsg };
        *(void**)(obj + 0x50) = loopObj;
        *(void**)(obj + 0x60) = g_socket;
        *(void**)(obj + 0x68) = tickObj;
        *(void**)(obj + 0x48) = msgObj;
        *(int*)(obj + 0x78) = 0;
        *(int*)(obj + 0x7c) = 0;                      // the reconnect block stays closed

        g_clockCalls = 0; g_scopeCtors = 0; g_scopeDtors = 0; g_logs = 0; g_recvCalls = 0;
        g_workCalls = 0; g_workArg = -1; g_tickSlot4 = 0; g_tickSlot1 = 0;
        g_nNpcLoopDelay_140102148 = 0;
        g_nNpcTickClock_140103c60 = 0; g_nNpcTickClockInit_140103c64 = 0;
        g_nNpcStatCount_140103f28 = 0; g_nNpcStatSum_140103f2c = 0; g_nNpcStatMax_140103f30 = 0;

        assert(FUN_1400027f0((long long)obj) == 1);

        assert(g_workCalls == 1 && g_workArg == 0);                       // the delay is handed over
        assert(g_recvBound == 0x418);                                     // the body's bound
        assert(g_recvCalls == 3);                                         // three packets, then stop
        // loop scope first, then 0x4d and 0x4f for the two types, then 0x50 for the tick
        assert(g_scopeCtors == 4);
        assert(g_scopeIds[0] == 0x4c && g_scopeIds[1] == 0x4d && g_scopeIds[2] == 0x4f && g_scopeIds[3] == 0x50);
        assert(g_scopeDtors == 4);
        // the unknown type is the only thing that logs, with the type as its argument
        assert(g_logs == 1 && g_logFmt == (const void*)&g_symNpcStr_1400beb30 && g_logArg == 0x1234);
        // neither packet branch ran (fd -1), so neither slot was touched
        assert(g_tickSlot1 == 0 && g_msgSlot0 == 0);
        // 1400 - 1200 = 200 is over 99 and under 0x2711, so the clock advances by exactly 100
        assert(g_nNpcTickClock_140103c60 == 1300);
        assert(g_tickSlot4 == 1 && g_tickArg == 1400);
        assert(g_warns == 0);
        // the counters: one pass, 1500 - 1000 elapsed, the maximum follows it
        assert(g_nNpcStatCount_140103f28 == 1);
        assert(g_nNpcStatSum_140103f2c == 500);
        assert(g_nNpcStatMax_140103f30 == 500);
        // 50 - 0 - 500 clamps to 1
        assert(g_nNpcLoopDelay_140102148 == 1);
        assert(g_clockCalls == 4);
    }

    std::printf("NPCSERVER_D175_OK: 0x1400027f0 CKernelThread::OnProcess\n");
    return 0;
}

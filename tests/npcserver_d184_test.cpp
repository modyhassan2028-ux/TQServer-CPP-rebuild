// D184 — NpcServer.exe 0x1400165d0, 0x1400163c0, 0x140016720, 0x1400127e0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned long long g_tickA = 0, g_tickB = 0;
static unsigned long long TicksA(void) { return g_tickA; }
static unsigned long long TicksB(void) { return g_tickB; }
static unsigned int g_tickSeq[4] = { 0, 0, 0, 0 }; static int g_tickN = 0;
static unsigned int GetTicks(void) { return g_tickSeq[g_tickN++ & 3]; }
static unsigned long long g_fileTime = 0;
static void GetFileTime(void* p) { ((unsigned long long*)p)[0] = g_fileTime; }
static int g_qpcCalls = 0; static long long g_count = 0;
static int Qpc(void* p) { ++g_qpcCalls; ((long long*)p)[0] = g_count; return 1; }
static int g_monitorFix = 0;
static void FixMonitor(long long p, int* o) { (void)p; ++g_monitorFix; o[0] += 1000; }
static void* g_tableRet = nullptr; static long long g_tableArgs[2] = {0, 0};
static void* AllocTable(long long n, long long sz) { g_tableArgs[0] = n; g_tableArgs[1] = sz; return g_tableRet; }
static void* g_hookFrees[4]; static int g_hookFreeN = 0;
static void* HookFree(void* p) { if (g_hookFreeN < 4) g_hookFrees[g_hookFreeN] = p; ++g_hookFreeN; return nullptr; }
static void* g_crtFrees[4]; static int g_crtFreeN = 0;
static void* CrtFree(void* p) { if (g_crtFreeN < 4) g_crtFrees[g_crtFreeN] = p; ++g_crtFreeN; return nullptr; }
static int g_errLogs = 0; static const char* g_errFmt = nullptr;
static void ErrLog(const char* pFmt, ...) { ++g_errLogs; g_errFmt = pFmt; }
static int g_e30 = 0, g_e50 = 0;
static void E30(void) { ++g_e30; } static void E50(void) { ++g_e50; }

int main() {
    g_pfnNpcGetTickCount = &GetTicks;
    g_pfnNpcGetSystemTimeAsFileTime = &GetFileTime;
    g_pfnNpcQueryPerformanceCounter = &Qpc;
    g_pfnNpc_1400164f0 = &FixMonitor;
    g_pfnNpc_140011850 = &AllocTable;
    g_pfnNpcEventFree_140103fa8 = nullptr;
    g_pfnNpcCrtFree = &CrtFree;
    g_pfnNpc_140019050 = &ErrLog;
    g_pfnNpc_140016e30 = &E30;
    g_pfnNpc_140016e50 = &E50;

    // 0x1400165d0: the first entry point, then the second, then the wrapping counter
    {
        unsigned char m[0x30];
        std::memset(m, 0, sizeof m);
        g_tickA = 0x1122334455ull;
        *(void**)(m + 0) = (void*)&TicksA;
        assert(FUN_1400165d0(m) == 0x1122334455ull);
        g_tickB = 0x123456789ABCDEF0ull;
        *(void**)(m + 0) = nullptr;
        *(void**)(m + 8) = (void*)&TicksB;
        unsigned long long expect = (g_tickB & 0xffffffffull) | ((g_tickB >> 0x12) & 0x3fff00000000ull);
        assert(FUN_1400165d0(m) == expect);
        // the plain counter: the reading is kept, and a backwards step bumps the wrap counter
        *(void**)(m + 8) = nullptr;
        g_tickSeq[0] = 5; g_tickSeq[1] = 3; g_tickN = 0;
        assert(FUN_1400165d0(m) == 5);
        assert(*(unsigned long long*)(m + 0x10) == 5);
        assert(FUN_1400165d0(m) == 0x100000003ull);
        assert(*(unsigned long long*)(m + 0x10) == 3);
    }

    // 0x1400163c0: the epoch guard, then the seconds and microseconds
    {
        int out[2] = { -1, -1 };
        assert(FUN_1400163c0(nullptr) == 0xffffffffull);
        g_fileTime = 0x19db1ded53e7fffULL;                       // exactly the epoch: refused
        assert(FUN_1400163c0(out) == 0xffffffffull);
        assert(out[0] == -1);
        g_fileTime = 0x01D9E2C3B4A59600ULL;                      // a 2026 reading
        assert(FUN_1400163c0(out) == 0);
        assert(out[0] == 1694225816);
        assert(out[1] == 139110);   // 32-bit wrap of the tenths field
    }

    // 0x140016720: the plain path divides the tick by 1000 and keeps milliseconds as its remainder
    {
        unsigned char m[0x50];
        std::memset(m, 0, sizeof m);
        g_tickA = 12345678; *(void**)(m + 0) = (void*)&TicksA;
        int out[2] = { 0, 0 };
        g_monitorFix = 0;
        assert(FUN_140016720(m, out) == 0);
        assert(out[0] == 12345 + 1000);                          // 0x1400164f0 adjusts the result afterwards
        assert(out[1] == 678000);
        assert(g_monitorFix == 1);                               // 0x1400164f0 always follows
        // the counter path: a drifting reading rebases the stored counter and re-bases the remainder
        std::memset(m, 0, sizeof m);
        *(int*)(m + 0x38) = 1;
        *(double*)(m + 0x30) = 1.0;
        g_tickA = 2000; *(void**)(m + 0) = (void*)&TicksA;
        g_count = 2000; g_qpcCalls = 0;
        assert(FUN_140016720(m, out) == 0);
        assert(g_qpcCalls == 1);
        assert(out[0] == 2 + 1000 && out[1] == 0);
        assert(*(long long*)(m + 0x28) == -1998000);             // the rebased counter
    }

    // 0x1400127e0: the bounds, the table, its relinking and its release
    {
        static unsigned char base[0x2b0];
        std::memset(base, 0, sizeof base);
        assert(FUN_1400127e0((long long)base, 0, 0, 0) == 0xffffffffull);
        assert(FUN_1400127e0((long long)base, 256, 0, 0) == 0xffffffffull);
        *(int*)(base + 0xd8) = 1;
        assert(FUN_1400127e0((long long)base, 4, 0, 0) == 0xffffffffull);
        *(int*)(base + 0xd8) = 0;
        // a successful sizing
        static unsigned char table[0x40];
        std::memset(table, 0xAA, sizeof table);
        g_tableRet = table; g_tableArgs[0] = 0; g_tableArgs[1] = 0;
        assert(FUN_1400127e0((long long)base, 4, 0, 0) == 0);
        assert(g_tableArgs[0] == 4 && g_tableArgs[1] == 0x10);
        assert(*(long long*)(base + 0xf8) == (long long)table);
        assert(*(int*)(base + 0x100) == 4);
        for (int i = 0; i < 4; ++i) {
            assert(*(void**)(table + i * 0x10) == nullptr);
            assert(*(void**)(table + i * 0x10 + 8) == (void*)(table + i * 0x10));
        }
        // re-sizing releases the old table through the runtime free when no hook is installed
        static unsigned char table2[0x20];
        g_crtFreeN = 0; g_tableRet = table2;
        assert(FUN_1400127e0((long long)base, 2, 0, 0) == 0);
        assert(g_crtFreeN == 1 && g_crtFrees[0] == (void*)table);
        assert(*(int*)(base + 0x100) == 2);
        assert(*(long long*)(base + 0xf8) == (long long)table2);
        // a failing allocation answers -1 and leaves the size at zero
        g_tableRet = nullptr; g_errLogs = 0;
        assert(FUN_1400127e0((long long)base, 3, 0, 0) == 0xffffffffull);
        assert(*(int*)(base + 0x100) == 0);
        assert(g_errLogs == 1 && std::strcmp(g_errFmt, "%s: calloc") == 0);
        // the notifier is cycled around the work
        static unsigned char table3[0x60];
        g_tableRet = table3; g_e30 = 0; g_e50 = 0;
        *(long long*)(base + 0x1d0) = 1;
        assert(FUN_1400127e0((long long)base, 5, 0, 0) == 0);
        assert(g_e30 == 1 && g_e50 == 1);
    }

    std::printf("NPCSERVER_D184_OK: tick, wall clock and priority table\n");
    return 0;
}

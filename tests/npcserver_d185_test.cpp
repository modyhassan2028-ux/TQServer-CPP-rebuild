// D185 — NpcServer.exe 0x140074b80 (the IOCP backend launch).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_block[0x50], g_handles[0x40];
static bool g_blockNull = false, g_handlesNull = false;
static long long g_allocArgs[2][2]; static int g_allocN = 0;
static void* Alloc(long long n, long long sz) {
    if (g_allocN < 2) { g_allocArgs[g_allocN][0] = n; g_allocArgs[g_allocN][1] = sz; }
    ++g_allocN;
    if (n == 1 && sz == 0x50) return g_blockNull ? nullptr : (void*)g_block;
    return g_handlesNull ? nullptr : (void*)g_handles;
}
static int g_once = 0;
static void Once(void* p) { (void)p; ++g_once; }
static unsigned int g_iocpThreads = 0; static void* g_iocpRet = (void*)0x1000; static int g_iocpCalls = 0;
static void* Iocp(void* a, void* b, unsigned long c, unsigned int d) {
    g_iocpThreads = d; ++g_iocpCalls;
    assert(a == (void*)(long long)-1 && b == nullptr && c == 0);
    return g_iocpRet;
}
static void* g_semRet = (void*)0x2000; static int g_semCalls = 0;
static void* Sem(void* a, long i, long m, const char* n) {
    ++g_semCalls; assert(a == nullptr && i == 0 && m == 1 && n == nullptr); return g_semRet;
}
static int g_beginCalls = 0, g_beginFailAt = -1;
static unsigned long long Begin(void (*fn)(void*), unsigned int st, void* arg) {
    assert(st == 0);
    if (g_beginFailAt >= 0 && g_beginCalls == g_beginFailAt) { ++g_beginCalls; return 0xffffffffffffffffull; }
    assert(arg == (void*)g_block);
    (void)fn;
    return 0x9000ull + (unsigned long long)g_beginCalls++;
}
static unsigned long g_spin = 0; static void* g_spinSection = nullptr;
static unsigned long Spin(void* p, unsigned long n) { g_spinSection = p; g_spin = n; return 1; }
static void* g_closed[8]; static int g_closedN = 0;
static int Close(void* h) { if (g_closedN < 8) g_closed[g_closedN] = h; ++g_closedN; return 1; }
static void* g_freed[8]; static int g_freedN = 0;
static void Free(void* p) { if (g_freedN < 8) g_freed[g_freedN] = p; ++g_freedN; }
static int g_threadProcHits = 0;
static void ThreadProc(void* p) { (void)p; ++g_threadProcHits; }

int main() {
    g_pfnNpc_140011850 = &Alloc;
    g_pfnNpc_140074930 = &Once;
    g_pfnNpcCreateIoCompletionPort = &Iocp;
    g_pfnNpcCreateSemaphoreA = &Sem;
    g_pfnNpcBeginThread = &Begin;
    g_pfnNpcInitializeCriticalSectionAndSpinCount = &Spin;
    g_pfnNpcCloseHandle = &Close;
    g_pfnNpcFree_1400119c0 = &Free;
    g_pfnNpcThreadProc_140074780 = &ThreadProc;

    // the block itself fails: nothing else is touched
    {
        g_blockNull = true; g_allocN = 0; g_once = 0; g_iocpCalls = 0;
        g_nNpcFlag_140104cc8 = 0;
        assert(FUN_140074b80(4) == nullptr);
        assert(g_once == 1);                                     // the once-init still ran
        assert(g_allocN == 1 && g_iocpCalls == 0);
        g_blockNull = false;
    }

    // a full launch: two threads requested, so four slots
    {
        std::memset(g_block, 0, sizeof g_block);
        std::memset(g_handles, 0xAA, sizeof g_handles);
        g_allocN = 0; g_iocpCalls = 0; g_semCalls = 0; g_beginCalls = 0; g_beginFailAt = -1;
        g_spin = 0; g_spinSection = nullptr; g_closedN = 0; g_freedN = 0;
        g_nNpcFlag_140104cc8 = 1;
        void* p = FUN_140074b80(2);
        assert(p == (void*)g_block);
        assert(g_once == 1);                                     // the flag was already set
        assert(g_allocArgs[0][0] == 1 && g_allocArgs[0][1] == 0x50);
        assert(g_allocArgs[1][0] == 4 && g_allocArgs[1][1] == 8);  // two per thread
        assert(*(short*)(g_block + 0x30) == 4);
        assert(*(void**)(g_block + 0x38) == (void*)g_handles);
        assert(*(void**)g_block == (void*)0x1000);                // the port
        assert(*(unsigned int*)(g_block + 0x34) == 0xffffffffu);  // the slot marker
        assert(*(void**)(g_block + 0x48) == (void*)0x2000);       // the semaphore
        assert(g_iocpThreads == 2);
        assert(g_beginCalls == 4);
        for (int i = 0; i < 4; ++i)
            assert(*(unsigned long long*)(g_handles + i * 8) == 0x9000ull + (unsigned long long)i);
        assert(*(short*)(g_block + 0x40) == 4);                   // the started count
        assert(g_spinSection == (void*)(g_block + 0x08) && g_spin == 1000);
        assert(g_closedN == 0 && g_freedN == 0);
    }

    // a zero request becomes two, and the port is asked for two workers
    {
        std::memset(g_block, 0, sizeof g_block);
        g_allocN = 0; g_iocpCalls = 0; g_beginCalls = 0; g_beginFailAt = -1; g_closedN = 0;
        void* p = FUN_140074b80(0);
        assert(p == (void*)g_block);
        assert(g_iocpThreads == 2);                               // the replacement value
        assert(*(short*)(g_block + 0x30) == 4);
        assert(g_beginCalls == 4);
    }

    // a worker that will not start unwinds the port, the slots, the semaphore and the block
    {
        std::memset(g_block, 0, sizeof g_block);
        std::memset(g_handles, 0, sizeof g_handles);
        g_allocN = 0; g_beginCalls = 0; g_beginFailAt = 2; g_closedN = 0; g_freedN = 0;
        assert(FUN_140074b80(2) == nullptr);
        assert(g_beginCalls == 3);                                // two started, the third refused
        assert(g_closedN == 2);                                   // the port and the semaphore
        assert(g_closed[0] == (void*)0x1000 && g_closed[1] == (void*)0x2000);
        assert(g_freedN == 2);                                    // the slot array and the block
        assert(g_freed[0] == (void*)g_handles && g_freed[1] == (void*)g_block);
        assert(*(short*)(g_block + 0x40) == 2);                    // only the two that started
        g_beginFailAt = -1;
    }

    // no slot array at all: no port is created and the block alone is released
    {
        std::memset(g_block, 0, sizeof g_block);
        g_handlesNull = true; g_allocN = 0; g_iocpCalls = 0; g_closedN = 0; g_freedN = 0;
        assert(FUN_140074b80(2) == nullptr);
        assert(g_iocpCalls == 0);
        assert(g_closedN == 0);
        assert(g_freedN == 1 && g_freed[0] == (void*)g_block);
        g_handlesNull = false;
    }

    std::printf("NPCSERVER_D185_OK: 0x140074b80 IOCP backend launch\n");
    return 0;
}

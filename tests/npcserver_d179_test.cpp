// D179 — NpcServer.exe 0x140005400..0x1400055f0: the eight registered threading handlers.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_block = 0;

static unsigned char g_heap[0x200];
static int g_mallocs = 0; static long long g_mallocArg = 0;
static void* Malloc(long long n) { g_mallocArg = n; ++g_mallocs; return g_heap; }
static int g_frees = 0; static void* g_freeArg = nullptr;
static void Free(void* p) { g_freeArg = p; ++g_frees; }
static int g_initRet = 1; static void* g_initArg = nullptr; static unsigned long g_initSpin = 0;
static int InitCS(void* p, unsigned long s) { g_initArg = p; g_initSpin = s; return g_initRet; }
static int g_delCS = 0; static void* g_delArg = nullptr;
static void DelCS(void* p) { g_delArg = p; ++g_delCS; }
static int g_enter = 0, g_leave = 0; static void* g_leaveArg = nullptr;
static void EnterCS(void* p) { (void)p; if (++g_enter > 2000) { std::printf("LOOP EnterCS block %d\n", g_block); std::abort(); } }
static void LeaveCS(void* p) { g_leaveArg = p; ++g_leave; }
static int g_tryRet = 0; static void* g_tryArg = nullptr;
static int TryEnter(void* p) { g_tryArg = p; return g_tryRet; }
static void* g_event = (void*)0x9000;
static void* CreateEvent(void* s, int manual, int initial, const char* n) {
    (void)s; (void)n; assert(manual == 1 && initial == 0); return g_event;
}
static int g_sets = 0, g_resets = 0;
static int SetEv(void* h) { (void)h; if (++g_sets > 2000) { std::printf("LOOP SetEv\n"); std::abort(); } return 1; }
static int ResetEv(void* h) { (void)h; if (++g_resets > 2000) { std::printf("LOOP ResetEv\n"); std::abort(); } return 1; }
static int g_closes = 0; static void* g_closeArg = nullptr;
static int CloseH(void* h) { g_closeArg = h; if (++g_closes > 2000) { std::printf("LOOP CloseH\n"); std::abort(); } return 1; }
static unsigned int g_waitRet = 0; static unsigned int g_waitMillis = 0;
static bool g_waitBumps = false; static NpcEvthreadCondition* g_waitCond = nullptr;
static int g_waits = 0;
static unsigned int WaitObj(void* h, unsigned int ms) {
    (void)h; g_waitMillis = ms;
    if (++g_waits > 2000) { std::printf("LOOP WaitObj block %d\n", g_block); std::abort(); }
    if (g_waitBumps && g_waitCond != nullptr) { g_waitCond->nWaitCount += 1; g_waitCond->nSignals = 1; }
    return g_waitRet;
}
static unsigned int g_ticks[4] = { 0, 0, 0, 0 }; static int g_tickN = 0;
static unsigned int GetTicks(void) { return g_ticks[g_tickN < 3 ? g_tickN++ : 3]; }
static unsigned int TvMs(int* pTv) { return pTv != nullptr ? (unsigned int)pTv[0] : 0; }

int main() {
    g_pfnNpcMalloc_140011830 = &Malloc;
    g_pfnNpcFree_1400119c0 = &Free;
    g_pfnNpcInitCS = &InitCS;
    g_pfnNpcDeleteCS = &DelCS;
    g_pfnNpcEnterCS = &EnterCS;
    g_pfnNpcLeaveCS = &LeaveCS;
    g_pfnNpcTryEnterCS = &TryEnter;
    g_pfnNpcCreateEventA = &CreateEvent;
    g_pfnNpcSetEvent = &SetEv;
    g_pfnNpcResetEvent = &ResetEv;
    g_pfnNpcCloseHandle = &CloseH;
    g_pfnNpcWaitForSingleObject = &WaitObj;
    g_pfnNpcGetTickCount = &GetTicks;
    g_pfnNpc_140016450 = &TvMs;

    g_block = 1;
    // 0x140005400: 0x28 bytes and a spin count of 2000; a failed init frees and answers nothing
    {
        g_mallocs = 0; g_frees = 0; g_initRet = 1; g_initSpin = 0;
        assert(FUN_140005400() == (void*)g_heap);
        assert(g_mallocArg == 0x28 && g_initArg == (void*)g_heap && g_initSpin == 2000);
        g_initRet = 0;
        assert(FUN_140005400() == nullptr);
        assert(g_frees == 1 && g_freeArg == (void*)g_heap);
        g_initRet = 1;
    }

    g_block = 2;
    // 0x140005450: the section is released before the block
    {
        g_delCS = 0; g_frees = 0;
        FUN_140005450(g_heap);
        assert(g_delCS == 1 && g_delArg == (void*)g_heap && g_frees == 1);
    }

    g_block = 3;
    // 0x140005470: flag 0x10 is the try form and a failed try answers true
    {
        g_tryRet = 0; g_enter = 0;
        assert(FUN_140005470(0x10, g_heap) == true);
        g_tryRet = 1;
        assert(FUN_140005470(0x10, g_heap) == false);
        assert(g_enter == 0);
        assert(FUN_140005470(0, g_heap) == false);
        assert(g_enter == 1 && g_tryArg == (void*)g_heap);
    }

    g_block = 4;
    // 0x1400054a0
    {
        g_leave = 0;
        assert(FUN_1400054a0(0x55, g_heap) == 0);
        assert(g_leave == 1 && g_leaveArg == (void*)g_heap);
    }

    g_block = 5;
    // 0x1400054d0: the handle and the section, the counters only once the handle exists
    {
        NpcEvthreadCondition* p = (NpcEvthreadCondition*)g_heap;
        std::memset(g_heap, 0, sizeof g_heap);
        p->nWaiters = 5; p->nSignals = 5; p->nWaitCount = 5;
        g_event = (void*)0x9000; g_mallocs = 0; g_frees = 0; g_initArg = nullptr;
        assert(FUN_1400054d0() == (void*)p);
        assert(g_mallocArg == 0x40 && g_initArg == (void*)p->cs && g_initSpin == 2000);
        assert(p->hEvent == (void*)0x9000);
        assert(p->nWaiters == 0 && p->nSignals == 0 && p->nWaitCount == 0);
        // no handle: the section is released and the block freed
        g_event = nullptr; g_delCS = 0; g_frees = 0;
        assert(FUN_1400054d0() == nullptr);
        assert(g_delCS == 1 && g_frees == 1);
        // no section: only the block
        g_event = (void*)0x9000; g_initRet = 0; g_frees = 0;
        assert(FUN_1400054d0() == nullptr && g_frees == 1);
        g_initRet = 1;
    }

    g_block = 6;
    // 0x140005560
    {
        NpcEvthreadCondition* p = (NpcEvthreadCondition*)g_heap;
        p->hEvent = (void*)0x9000;
        g_delCS = 0; g_closes = 0; g_frees = 0;
        FUN_140005560(p);
        assert(g_delCS == 1 && g_delArg == (void*)p->cs);
        assert(g_closes == 1 && g_closeArg == (void*)0x9000);
        assert(g_frees == 1);
    }

    g_block = 7;
    // 0x140005590: a single wake bumps one, a broadcast makes every waiter pending
    {
        NpcEvthreadCondition* p = (NpcEvthreadCondition*)g_heap;
        std::memset(g_heap, 0, sizeof g_heap);
        p->nWaiters = 3; g_sets = 0;
        assert(FUN_140005590(p, 0) == 0);
        assert(p->nSignals == 1 && p->nWaitCount == 1 && g_sets == 1);
        assert(FUN_140005590(p, 1) == 0);
        assert(p->nSignals == 3 && p->nWaitCount == 2 && g_sets == 2);
    }

    g_block = 8;
    // 0x1400055f0: a timed wait that runs out answers 1
    {
        NpcEvthreadCondition* p = (NpcEvthreadCondition*)g_heap;
        std::memset(g_heap, 0, sizeof g_heap);
        int tv[2] = { 500, 0 };
        g_waitRet = 0; g_waitBumps = false; g_resets = 0; g_enter = 0; g_leave = 0;
        g_ticks[0] = 1000; g_ticks[1] = 1600; g_tickN = 0;   // the deadline is start + 500
        unsigned int r = FUN_1400055f0(p, (void*)0x7777, tv);
        assert(r == 1);
        assert(g_waitMillis == 500);                       // the interval came from the timeval
        assert(p->nWaiters == 0);
        assert(g_resets == 1);                             // the last waiter resets the handle
        assert(g_enter == 4 && g_leave == 4);              // section, mutex and the re-entry
    }

    g_block = 9;
    // 0x1400055f0: a signalled wait answers 0 and consumes one signal
    {
        NpcEvthreadCondition* p = (NpcEvthreadCondition*)g_heap;
        std::memset(g_heap, 0, sizeof g_heap);
        p->nSignals = 1;
        g_waitRet = 0; g_waitBumps = true; g_waitCond = p; g_resets = 0; g_tickN = 0;
        unsigned int r = FUN_1400055f0(p, (void*)0x7777, nullptr);
        assert(r == 0);
        assert(g_waitMillis == 0xffffffffu);               // no timeval, an infinite interval
        assert(p->nSignals == 0 && p->nWaiters == 0);
        assert(g_resets == 1);                             // the last waiter resets the handle
        g_waitBumps = false; g_waitCond = nullptr;
    }

    g_block = 10;
    // 0x1400055f0: a timeout answers 1 and only retires the waiter
    {
        NpcEvthreadCondition* p = (NpcEvthreadCondition*)g_heap;
        std::memset(g_heap, 0, sizeof g_heap);
        g_waitRet = 0x102; g_resets = 0; g_tickN = 0;
        unsigned int r = FUN_1400055f0(p, (void*)0x7777, nullptr);
        assert(r == 1);
        assert(p->nWaiters == 0);
        // and any other failure answers -1
        g_waitRet = 0x102 + 5;
        assert(FUN_1400055f0(p, (void*)0x7777, nullptr) == 0xffffffffu);
    }

    std::printf("NPCSERVER_D179_OK: 0x140005400..0x1400055f0 threading handlers\n");
    return 0;
}

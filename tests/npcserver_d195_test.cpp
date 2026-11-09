// D195 — NpcServer.exe 0x140075480 (one poll cycle over the three buffers).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_q[0x38];
static unsigned char g_a1[0x100], g_a2[0x100];
static unsigned char g_b[3][0x100];            // poll buffers at q+6, q+8, q+10
static unsigned char g_base[0x400];
static long long g_mech[4];

static void Reset(unsigned int nCap, unsigned int nA1, unsigned int nA2) {
    std::memset(g_q, 0, sizeof g_q);
    std::memset(g_a1, 0, sizeof g_a1); std::memset(g_a2, 0, sizeof g_a2);
    for (int i = 0; i < 3; ++i) std::memset(g_b[i], 0, 0x100);
    *(unsigned int*)g_q = nCap;
    *(void**)(g_q + 8) = g_a1;
    *(void**)(g_q + 0x10) = g_a2;
    *(void**)(g_q + 0x18) = g_b[0];
    *(void**)(g_q + 0x20) = g_b[1];
    *(void**)(g_q + 0x28) = g_b[2];
    *(unsigned int*)g_a1 = nA1;
    *(unsigned int*)g_a2 = nA2;
    *(void**)(g_base + 8) = g_q;   // the base holds the queue object at +8
}
static int g_reallocCalls = 0, g_reallocFailAt = 0;
static unsigned long long g_reallocSize = 0;
static void* Realloc(void* p, unsigned long long n) {
    ++g_reallocCalls; g_reallocSize = n;
    if (g_reallocFailAt && g_reallocCalls >= g_reallocFailAt) return nullptr;
    return p;
}
static unsigned int g_slept = 0; static int g_sleepCalls = 0;
static void SleepSeam(unsigned int ms) { g_slept = ms; ++g_sleepCalls; }
static unsigned int g_waitRet = 50;
static unsigned int WaitMs(int* p) { (void)p; return g_waitRet; }
static int g_e50 = 0, g_e30 = 0;
static void E50(void) { ++g_e50; }
static void E30(void) { ++g_e30; }
static unsigned int g_pollN = 0, g_pollArgc = 0;
static void* g_pollR = nullptr; static void* g_pollW = nullptr; static void* g_pollE = nullptr;
static int* g_pollT = nullptr;
static int g_pollRet = 0;
static int Poll(unsigned int n, void* r, void* w, void* e, int* t) {
    g_pollN = n; g_pollR = r; g_pollW = w; g_pollE = e; g_pollT = t;
    ++g_pollArgc; return g_pollRet;
}
static int g_rotate = 0;
static int Rotate(unsigned int* p, int n) { (void)p; (void)n; return g_rotate; }
static long long g_act[16]; static int g_actFlag[16]; static int g_actN = 0;
static void Activate(long long p, long long k, int f) {
    if (g_actN < 16) { g_act[g_actN] = k; g_actFlag[g_actN] = f; }
    ++g_actN;
}

int main() {
    g_mech[1] = (long long)g_q;
    long long pBase = (long long)g_base;
    g_pfnNpcRealloc_1400119a0 = &Realloc;
    g_pfnNpcSleep = &SleepSeam;
    g_pfnNpc_140016450 = &WaitMs;
    g_pfnNpc_140016e50 = &E50;
    g_pfnNpc_140016e30 = &E30;
    g_pfnNpcWsaPoll_Ordinal18 = &Poll;
    g_pfnNpc_1400089a0 = &Rotate;
    g_pfnNpc_14001a5d0 = &Activate;
    *(long long*)(g_base + 0x1d0) = 0;

    // both buffers empty and no timeout: the thread sleeps for good
    {
        Reset(0x20, 0, 0);
        g_sleepCalls = 0; g_slept = 0; g_pollArgc = 0;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(g_sleepCalls == 1 && g_slept == 0x7fffffffu);
        assert(g_pollArgc == 0);
    }

    // an empty cycle with a timeout asks the timeout object, and a negative answer means sleep for good
    {
        Reset(0x20, 0, 0);
        int timeout[2] = { 0, 0 };
        g_sleepCalls = 0; g_slept = 0; g_waitRet = 50;
        assert(FUN_140075480(pBase, timeout) == 0);
        assert(g_slept == 50);
        g_waitRet = 0xffffffffu;
        assert(FUN_140075480(pBase, timeout) == 0);
        assert(g_slept == 0x7fffffffu);
        g_waitRet = 50;
    }

    // the resize flag: all three buffers are resized to (cap - 1) * 8 + 0x10 and the flag is cleared; a
    // failure at any of the three answers -1 without touching the flag
    {
        Reset(0x10, 0, 0);
        *(unsigned int*)(g_q + 4) = 1;
        g_reallocCalls = 0; g_reallocSize = 0;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(g_reallocCalls == 3);
        assert(g_reallocSize == (0x10u - 1) * 8 + 0x10);
        assert(*(unsigned int*)(g_q + 4) == 0);
        Reset(0x10, 0, 0);
        *(unsigned int*)(g_q + 4) = 1;
        g_reallocCalls = 0; g_reallocFailAt = 2;
        assert(FUN_140075480(pBase, nullptr) == -1);
        assert(g_reallocCalls == 2);
        assert(*(unsigned int*)(g_q + 4) == 1);          // still pending
        g_reallocFailAt = 0;
    }

    // the copies: array one into buffer one, array two into buffers two and three
    {
        Reset(4, 2, 3);
        *(unsigned long long*)(g_a1 + 8) = 0xA0;
        *(unsigned long long*)(g_a1 + 0x10) = 0xA1;
        *(unsigned long long*)(g_a2 + 8) = 0xB0;
        *(unsigned long long*)(g_a2 + 0x10) = 0xB1;
        *(unsigned long long*)(g_a2 + 0x18) = 0xB2;
        g_pollRet = 0; g_actN = 0;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(*(unsigned int*)g_b[0] == 2 && *(unsigned long long*)(g_b[0] + 8) == 0xA0);
        assert(*(unsigned long long*)(g_b[0] + 0x10) == 0xA1);
        assert(*(unsigned int*)g_b[1] == 3 && *(unsigned long long*)(g_b[1] + 0x18) == 0xB2);
        assert(*(unsigned int*)g_b[2] == 3 && *(unsigned long long*)(g_b[2] + 8) == 0xB0);
        // the higher of the last two counts went to the poll
        assert(g_pollN == 3);
        assert(g_pollR == (void*)g_b[0] && g_pollW == (void*)g_b[1] && g_pollE == (void*)g_b[2]);
        assert(g_actN == 0);                              // nothing ready
    }

    // the poll refusing to run or reporting nothing hands its own answer straight back
    {
        Reset(4, 1, 0);
        *(unsigned long long*)(g_a1 + 8) = 0x55;
        g_pollRet = -1; g_actN = 0;
        assert(FUN_140075480(pBase, nullptr) == -1);
        assert(g_actN == 0);
        g_pollRet = 0;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(g_actN == 0);
    }

    // a ready cycle activates every entry of every non-empty buffer, flags 2, 4, 4, starting the walk at
    // the rotated entry
    {
        Reset(4, 3, 2);
        *(unsigned long long*)(g_a1 + 8) = 0xE0;
        *(unsigned long long*)(g_a1 + 0x10) = 0xE1;
        *(unsigned long long*)(g_a1 + 0x18) = 0xE2;
        *(unsigned long long*)(g_a2 + 8) = 0xF0;
        *(unsigned long long*)(g_a2 + 0x10) = 0xF1;
        g_pollRet = 3; g_actN = 0; g_rotate = 1;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(g_actN == 3 + 2 + 2);                      // buffer one three, the other two twice each
        // buffer one is walked from index 2: E2, E0, E1 with flag 2
        assert(g_act[0] == 0xE2 && g_actFlag[0] == 2);
        assert(g_act[1] == 0xE0 && g_actFlag[1] == 2);
        assert(g_act[2] == 0xE1 && g_actFlag[2] == 2);
        // then the second buffer, then the third, both with flag 4. With two entries and a start of one,
        // the step lands past the end at once and wraps to the first entry.
        assert(g_act[3] == 0xF0 && g_actFlag[3] == 4);
        assert(g_act[4] == 0xF1 && g_actFlag[4] == 4);
        assert(g_act[5] == 0xF0 && g_actFlag[5] == 4);
        assert(g_act[6] == 0xF1 && g_actFlag[6] == 4);
    }

    // a base that carries a notification handle brackets the poll with the two hooks; without it neither runs
    {
        Reset(4, 1, 0);
        g_pollRet = 0; g_e50 = 0; g_e30 = 0;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(g_e50 == 0 && g_e30 == 0);
        *(long long*)(g_base + 0x1d0) = 0x5000;
        assert(FUN_140075480(pBase, nullptr) == 0);
        assert(g_e50 == 1 && g_e30 == 1);
        *(long long*)(g_base + 0x1d0) = 0;
    }

    std::printf("NPCSERVER_D195_OK: 0x140075480 poll cycle\n");
    return 0;
}

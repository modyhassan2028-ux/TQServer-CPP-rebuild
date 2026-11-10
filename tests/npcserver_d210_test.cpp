// D210 — NpcServer.exe 0x14007a830 (flush), 0x14007a8e0 (limit raise), 0x14007a9c0 (limit left).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

namespace {

int g_sinkCalls = 0;       int g_sinkAmount = 0;

static void* g_vt[4];
void Sink(long long p, int n) { (void)p; ++g_sinkCalls; g_sinkAmount = n; }
}  // namespace

int main() {
    g_vt[2] = (void*)&Sink;

    // the byte limit that is left
    {
        unsigned char b[0x40];
        std::memset(b, 0, sizeof b);
        *(int*)(b + 0x28) = 0x7fffffff;
        *(int*)(b + 0x18) = 5;                              // five bytes consumed, no overrun
        assert(FUN_14007a9c0((long long)b) == -1);          // no limit is reported as -1, not as a count
        *(int*)(b + 0x28) = 100;
        assert(FUN_14007a9c0((long long)b) == 95);
        *(int*)(b + 0x18) = 100;
        assert(FUN_14007a9c0((long long)b) == 0);           // exactly used up is zero, not -1
    }

    // raising the limit: consumed + extra, pinned at 0x7fffffff when the sum would pass it
    {
        unsigned char b[0x40];
        std::memset(b, 0, sizeof b);
        // the sink is reached through two indirections: the object's first word points at the word holding the
        // vtable, and the call hands that inner word as its first argument
        static long long s_inner[2];
        s_inner[0] = (long long)g_vt;
        *(long long*)b = (long long)s_inner;
        *(int*)(b + 0x28) = 40;
        *(int*)(b + 0x18) = 10;                             // ten bytes consumed
        assert(FUN_14007a8e0((long long)b, 20) == 40);       // answers the limit from before
        assert(*(int*)(b + 0x28) == 30);                     // consumed + extra, and that is the smaller one

        // the settle keeps the smaller of the new limit and the one from before, so a raise never grows past the old
        // limit; the overrun at +0x2c is then recomputed against that
        *(int*)(b + 0x28) = 7;
        *(int*)(b + 0x18) = 5;
        *(int*)(b + 0x30) = 0;
        assert(FUN_14007a8e0((long long)b, 5) == 7);
        assert(*(int*)(b + 0x28) == 7);                      // 10 would have grown it past 7

        // a negative amount is pinned at 0x7fffffff first, and the settle then keeps the old 7 again
        *(int*)(b + 0x28) = 7;
        assert(FUN_14007a8e0((long long)b, -1) == 7);
        assert(*(int*)(b + 0x28) == 7);
        assert(FUN_14007a8e0((long long)b, 0x7fffffff) == 7);
        assert(*(int*)(b + 0x28) == 7);                      // 5 + 0x7fffffff would pass the top
    }

    // the flush: pending + both counters, handed to the sink only when positive
    {
        unsigned char b[0x40];
        std::memset(b, 0, sizeof b);
        // the sink is reached through two indirections: the object's first word points at the word holding the
        // vtable, and the call hands that inner word as its first argument
        static long long s_inner[2];
        s_inner[0] = (long long)g_vt;
        *(long long*)b = (long long)s_inner;
        g_sinkCalls = 0; g_sinkAmount = 0;
        *(int*)(b + 0x2c) = 0; *(int*)(b + 0x1c) = 0;
        FUN_14007a830((long long*)b);
        assert(g_sinkCalls == 0);                           // nothing waiting, nothing flushed

        *(int*)(b + 0x2c) = 7; *(int*)(b + 0x1c) = 3;
        *(int*)(b + 0x18) = 100;
        // the byte count is the object's own limit minus its current pointer: two bytes are still waiting
        *(long long*)(b + 0x08) = 1000; *(long long*)(b + 0x10) = 1002;
        FUN_14007a830((long long*)b);
        assert(g_sinkCalls == 1 && g_sinkAmount == 12);     // 2 pending + 7 + 3
        assert(*(int*)(b + 0x18) == 91);                    // 100 - (2 + 7)
        assert(*(long long*)(b + 0x10) == 1000);            // the current pointer is copied into the end word
        assert(*(int*)(b + 0x2c) == 0 && *(int*)(b + 0x1c) == 0);
    }

    std::printf("NPCSERVER_D210_OK: 0x14007a830/8e0/9c0\n");
    return 0;
}

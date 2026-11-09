// D173 — NpcServer.exe 0x140002700, 0x140002760, 0x140002790: the deadline helpers and the thread ctor.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned long g_clock[4] = {0, 0, 0, 0};
static int g_clockCalls = 0;
static unsigned long Clock(unsigned long long) { unsigned long v = g_clock[g_clockCalls < 4 ? g_clockCalls : 3]; ++g_clockCalls; return v; }
static int g_ctorCalls = 0;
static void CtorHook(void* p) { (void)p; ++g_ctorCalls; }

int main() {
    g_pfnNpcTimeGet = &Clock;
    g_pfnNpcThreadBaseCtor = &CtorHook;

    // 0x140002700 — not yet due returns the residue with the low byte clear
    {
        int pair[2] = { 5, 10 };                       // total 15, deadline second 10
        g_clockCalls = 0; g_clock[0] = 5000;           // 5 <= 15, not due
        unsigned long long r = FUN_140002700(pair);
        assert((r & 0xffull) == 0);                    // low byte clear
        assert(pair[1] == 10);                         // untouched
        // now due: the second read re-arms the deadline and the low byte is 1
        g_clockCalls = 0; g_clock[0] = 15000; g_clock[1] = 20000;
        r = FUN_140002700(pair);
        assert((r & 0xffull) == 1);
        assert(pair[1] == 20);                         // 20000 / 1000
        assert(g_clockCalls == 2);                     // read twice on that path
    }

    // 0x140002760 — store the value and the current second
    {
        unsigned int pair[2] = {0, 0};
        g_clockCalls = 0; g_clock[0] = 5000;
        FUN_140002760(pair, 0x11u);
        assert(pair[0] == 0x11u && pair[1] == 5u);
    }

    // 0x140002790 — base constructor first, then both tables and the eight cleared words
    {
        unsigned char obj[0x80];
        std::memset(obj, 0xFF, sizeof obj);
        g_ctorCalls = 0;
        assert(FUN_140002790(obj) == (void*)obj);
        assert(g_ctorCalls == 1);
        assert(*(void**)(obj + 0x00) == (void*)&g_symNpcVftbl_1400be730);
        assert(*(void**)(obj + 0x40) == (void*)&g_symNpcVftbl_1400be6f8);
        assert(*(unsigned int*)(obj + 0x78) == 0 && *(unsigned int*)(obj + 0x7c) == 0);
        const int cleared[6] = { 0x48, 0x50, 0x58, 0x60, 0x68, 0x70 };
        for (int i = 0; i < 6; ++i)
            assert(*(void**)(obj + cleared[i]) == nullptr);
        // a word the body never writes is left alone (0x70 is an eight-byte store, so 0x74 is inside it)
        assert(*(unsigned int*)(obj + 0x30) == 0xFFFFFFFFu);
    }

    std::printf("NPCSERVER_D173_OK: 0x140002700, 0x140002760, 0x140002790\n");
    return 0;
}

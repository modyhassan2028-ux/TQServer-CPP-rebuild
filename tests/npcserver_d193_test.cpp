// D193 — NpcServer.exe 0x1400750d0 (the 0x38 queue object).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_obj[0x38];
static unsigned char g_buf[5][0x108];
static int g_callocCalls = 0;
static void* Calloc(long long n, long long sz) {  // real calloc zeroes the block
    (void)n; (void)sz; ++g_callocCalls; std::memset(g_obj, 0, 0x38); return g_obj; }
static int g_mallocCalls = 0, g_mallocFailAt = 0;
static void* Malloc(long long n) {
    (void)n; ++g_mallocCalls;
    if (g_mallocFailAt != 0 && g_mallocCalls >= g_mallocFailAt) return nullptr;
    std::memset(g_buf[g_mallocCalls - 1], 0xCC, 0x108);
    return g_buf[g_mallocCalls - 1];
}
static void* g_freed[8]; static int g_freeN = 0;
static void Free(void* p) { if (g_freeN < 8) g_freed[g_freeN] = p; ++g_freeN; }
static long long g_b590Arg0 = 0, g_b590Arg1 = 0, g_b590Arg2 = 0, g_b590Arg3 = 0;
static int g_b590Calls = 0, g_b590Ret = 0;
static long long B590(long long a0, unsigned long long a1, unsigned long long a2, unsigned long long a3) {
    g_b590Arg0 = a0; g_b590Arg1 = (long long)a1; g_b590Arg2 = (long long)a2; g_b590Arg3 = (long long)a3;
    ++g_b590Calls; return g_b590Ret;
}
static int g_8930Calls = 0; static long long g_8930Field = 0; static int g_8930Value = -1;
static void F8930(int* p, int v) { ++g_8930Calls; g_8930Field = (long long)p; g_8930Value = v; }
static unsigned char g_base[0x400];

int main() {
    g_pfnNpc_140011850 = &Calloc;
    g_pfnNpcMalloc_140011830 = &Malloc;
    g_pfnNpcFree_1400119c0 = &Free;
    g_pfnNpc_14001b590 = &B590;
    g_pfnNpc_140008930 = &F8930;

    // the object itself cannot be allocated: nothing else is attempted
    {
        g_pfnNpc_140011850 = nullptr;
        g_mallocCalls = 0; g_freeN = 0; g_b590Calls = 0; g_8930Calls = 0;
        assert(FUN_1400750d0((long long)g_base, 0, 0x77, 0x88) == nullptr);
        assert(g_mallocCalls == 0 && g_freeN == 0 && g_b590Calls == 0 && g_8930Calls == 0);
        g_pfnNpc_140011850 = &Calloc;
    }

    // the third buffer fails: the two already taken are released in order, then the object
    {
        g_mallocCalls = 0; g_mallocFailAt = 3; g_freeN = 0; g_b590Calls = 0; g_8930Calls = 0;
        std::memset(g_obj, 0, sizeof g_obj);
        assert(FUN_1400750d0((long long)g_base, 0, 0, 0) == nullptr);
        assert(g_mallocCalls == 3);
        assert(g_freeN == 3);
        assert(g_freed[0] == (void*)g_buf[0] && g_freed[1] == (void*)g_buf[1]);
        assert(g_freed[2] == (void*)g_obj);
        assert(g_b590Calls == 0 && g_8930Calls == 0);
        g_mallocFailAt = 0;
    }

    // the whole object: capacity 0x20, five buffers each cleared through the first word, then 0x14001b590
    {
        g_mallocCalls = 0; g_freeN = 0; g_b590Calls = 0; g_8930Calls = 0;
        std::memset(g_obj, 0xAA, sizeof g_obj);   // calloc will clear it again
        g_b590Ret = 0;
        void* p = FUN_1400750d0((long long)g_base, 0xDEAD, 0x77, 0x88);
        assert(p == (void*)g_obj);
        assert(g_mallocCalls == 5 && g_freeN == 0);
        assert(*(unsigned int*)g_obj == 0x20);
        for (int i = 0; i < 5; ++i) {
            assert(*(void**)(g_obj + 8 + i * 8) == (void*)g_buf[i]);
            assert(*(unsigned int*)g_buf[i] == 0);           // cleared through its first word
        }
        assert(*(unsigned int*)(g_obj + 0x30) == 0);         // no flag on a good answer
        assert(g_b590Calls == 1);
        assert(g_b590Arg0 == (long long)g_base && g_b590Arg1 == 0x38);
        assert(g_b590Arg2 == 0x77 && g_b590Arg3 == 0x88);
        assert(g_8930Calls == 1 && g_8930Field == (long long)(g_base + 0x2a0) && g_8930Value == 0);
    }

    // a negative answer from 0x14001b590 sets flag 1 and still clears the caller's field
    {
        g_mallocCalls = 0; g_freeN = 0; g_b590Calls = 0; g_8930Calls = 0;
        std::memset(g_obj, 0, sizeof g_obj);
        g_b590Ret = -1;
        void* p = FUN_1400750d0((long long)g_base, 0, 0, 0);
        assert(p == (void*)g_obj);
        assert(*(unsigned int*)(g_obj + 0x30) == 1);
        assert(g_8930Calls == 1);
        assert(g_freeN == 0);
    }

    std::printf("NPCSERVER_D193_OK: 0x1400750d0 queue object\n");
    return 0;
}

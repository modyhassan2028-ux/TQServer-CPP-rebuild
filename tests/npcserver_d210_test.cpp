// D210 — NpcServer.exe 0x14007a830 (flush), 0x14007a8e0 (limit raise), 0x14007a9c0 (limit left).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

namespace {
long long g_c650 = 0;      long long g_c650Ret = 0;
int g_c670Ret = 0;         int g_c6a0Calls = 0;
int g_sinkCalls = 0;       int g_sinkAmount = 0;
int g_d140Limit = 0;       int g_d140Calls = 0;  bool g_d140Override = false;  int g_d140Value = 0;

static void* g_vt[4];

long long Pend(long long p) { (void)p; return g_c650Ret; }
int Used(long long p) { (void)p; return g_c670Ret; }
void Wire(long long p) { (void)p; ++g_c6a0Calls; }
int* Settle(int* pLimit, int* pOld) { ++g_d140Calls; g_d140Limit = *pLimit; *pOld = *pOld; 
    if (g_d140Override) *pLimit = g_d140Value; return pLimit; }
void Sink(long long p, int n) { (void)p; ++g_sinkCalls; g_sinkAmount = n; }
}  // namespace

int main() {
    g_pfnNpc_14007c650 = &Pend;
    g_pfnNpc_14007c670 = &Used;
    g_pfnNpc_14007c6a0 = &Wire;
    g_pfnNpc_14007d140 = &Settle;
    g_vt[2] = (void*)&Sink;

    // the byte limit that is left
    {
        unsigned char b[0x40];
        std::memset(b, 0, sizeof b);
        *(int*)(b + 0x28) = 0x7fffffff;
        g_c670Ret = 5;
        assert(FUN_14007a9c0((long long)b) == -1);          // no limit is reported as -1, not as a count
        *(int*)(b + 0x28) = 100;
        assert(FUN_14007a9c0((long long)b) == 95);
        g_c670Ret = 100;
        assert(FUN_14007a9c0((long long)b) == 0);           // exactly used up is zero, not -1
    }

    // raising the limit: consumed + extra, pinned at 0x7fffffff when the sum would pass it
    {
        unsigned char b[0x40];
        std::memset(b, 0, sizeof b);
        *(long long*)b = (long long)g_vt;
        *(int*)(b + 0x28) = 40;
        g_c670Ret = 10; g_c6a0Calls = 0; g_d140Calls = 0; g_d140Override = false;
        assert(FUN_14007a8e0((long long)b, 20) == 40);       // answers the limit from before
        assert(*(int*)(b + 0x28) == 30 && g_d140Limit == 30);
        assert(g_d140Calls == 1 && g_c6a0Calls == 1);        // the wire is told once, after the settle

        *(int*)(b + 0x28) = 7;
        g_d140Override = true; g_d140Value = 11;
        assert(FUN_14007a8e0((long long)b, 5) == 7);
        assert(*(int*)(b + 0x28) == 11);                    // the settle has the final word

        *(int*)(b + 0x28) = 7;
        g_d140Override = false; g_c670Ret = 100;
        assert(FUN_14007a8e0((long long)b, -1) == 7);       // a negative amount pins the limit
        assert(*(int*)(b + 0x28) == 0x7fffffff);
        assert(FUN_14007a8e0((long long)b, 0x7fffffff) == 0x7fffffff);
        assert(*(int*)(b + 0x28) == 0x7fffffff);            // 100 + 0x7fffffff would pass the top
    }

    // the flush: pending + both counters, handed to the sink only when positive
    {
        unsigned char b[0x40];
        std::memset(b, 0, sizeof b);
        *(long long*)b = (long long)g_vt;
        g_sinkCalls = 0; g_sinkAmount = 0;
        g_c650Ret = 0;
        *(int*)(b + 0x2c) = 0; *(int*)(b + 0x1c) = 0;
        FUN_14007a830((long long*)b);
        assert(g_sinkCalls == 0);                           // nothing waiting, nothing flushed

        *(int*)(b + 0x2c) = 7; *(int*)(b + 0x1c) = 3;
        g_c650Ret = 2;
        *(int*)(b + 0x18) = 100;
        *(long long*)(b + 0x08) = 0x2222; *(long long*)(b + 0x10) = 0x1111;
        FUN_14007a830((long long*)b);
        assert(g_sinkCalls == 1 && g_sinkAmount == 12);     // 2 pending + 7 + 3
        assert(*(int*)(b + 0x18) == 91);                    // 100 - (2 + 7)
        assert(*(long long*)(b + 0x10) == 0x2222);          // the current pointer is copied into the end word
        assert(*(int*)(b + 0x2c) == 0 && *(int*)(b + 0x1c) == 0);
    }

    std::printf("NPCSERVER_D210_OK: 0x14007a830/8e0/9c0\n");
    return 0;
}

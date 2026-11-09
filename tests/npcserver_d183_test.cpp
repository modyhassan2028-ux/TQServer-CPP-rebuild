// D183 — NpcServer.exe 0x14001a010/190, 0x14001ad50, 0x140016f00/df0/e70, 0x140010860,
// 0x140016640, 0x1400105b0, 0x140015e70.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static char g_getenvArg[0x40]; static int g_getenvCalls = 0; static bool g_envHit = false;
static char* GetenvStub(const char* n) {
    std::strncpy(g_getenvArg, n, sizeof g_getenvArg); ++g_getenvCalls;
    return g_envHit ? (char*)"1" : nullptr;
}
static char g_fmt[32]; static const char* g_fmtArg = nullptr; static unsigned long long g_fmtSize = 0;
static int SprintfStub(char* pBuf, unsigned long long n, const char* pFmt, const char* pszArg) {
    g_fmtSize = n; std::strncpy(g_fmt, pFmt, sizeof g_fmt); g_fmtArg = pszArg;
    std::strcpy(pBuf, "EVENT_NO"); std::strcat(pBuf, pszArg);
    return (int)std::strlen(pBuf);
}
static int g_upperCalls = 0;
static unsigned char UpperStub(unsigned char c) { ++g_upperCalls; return (unsigned char)(c >= 'a' && c <= 'z' ? c - 32 : c); }
static void* g_hModule = (void*)0x7000; static const char* g_gapNames[2]; static int g_gapN = 0;
static const char* g_modName = nullptr;
static void* ModHandle(const char* n) { g_modName = n; return g_hModule; }
static void* Gap(void* h, const char* n) { g_gapNames[g_gapN++ & 1] = n; return (void*)(0x8000 + g_gapN); }
static unsigned long long g_resolveRet = 0x55;
static unsigned long long Resolve(void* p) { (void)p; return g_resolveRet; }
static int g_qpfCalls = 0, g_qpcCalls = 0;
static long long g_freq = 1000000, g_count = 1234;
static int Qpf(void* p) { ++g_qpfCalls; ((long long*)p)[0] = g_freq; return 1; }
static int Qpc(void* p) { ++g_qpcCalls; ((long long*)p)[0] = g_count; return 1; }
static int g_ef0 = 0;
static void Ef0(void) { ++g_ef0; }
static unsigned long long g_monRet = 0; static int g_outUsed = 0;
static unsigned long long Mon(void* p, void* o) { (void)p; if (g_outUsed) { ((int*)o)[0] = 77; ((int*)o)[1] = 88; } return g_monRet; }
static int g_clock[2] = { 100, 500000 };
static void Clock(void* p) { ((int*)p)[0] = g_clock[0]; ((int*)p)[1] = g_clock[1]; }
static int g_e30 = 0, g_e50 = 0;
static void E30(void) { ++g_e30; } static void E50(void) { ++g_e50; }
static void* g_e900Ret = nullptr; static int g_e900Calls = 0;
static void* E900(void* b, long long a2, unsigned long long a3, unsigned long long a4) {
    (void)b; (void)a2; (void)a3; (void)a4; ++g_e900Calls; return g_e900Ret;
}

static unsigned long long RET_FN(void) { return 0xC0DE; }

int main() {
    g_pfnNpcGetenv = &GetenvStub;
    g_pfnNpc_140009250 = &SprintfStub;
    g_pfnNpc_140008820 = &UpperStub;
    g_pfnNpcGetModuleHandle_140008b90 = &ModHandle;
    g_pfnNpcGetProcAddress = &Gap;
    g_pfnNpc_1400165d0 = &Resolve;
    g_pfnNpcQueryPerformanceFrequency = &Qpf;
    g_pfnNpcQueryPerformanceCounter = &Qpc;
    g_pfnNpc_140016ef0 = &Ef0;
    g_pfnNpc_140016720 = &Mon;
    g_pfnNpc_1400163c0 = &Clock;
    g_pfnNpc_140016e30 = &E30;
    g_pfnNpc_140016e50 = &E50;
    g_pfnNpc_140014900 = &E900;

    // 0x14001a190 and 0x14001ad50 clear what they say they clear
    {
        unsigned char b[0x20];
        std::memset(b, 0xAA, sizeof b);
        FUN_14001a190(b);
        assert(*(long long*)(b + 0) == 0 && *(unsigned int*)(b + 8) == 0);
        assert(b[0x0c] == 0xAA);                                    // and nothing else
        std::memset(b, 0xAA, sizeof b);
        FUN_14001ad50(b);
        assert(*(long long*)(b + 0) == 0 && *(unsigned int*)(b + 8) == 0 && *(unsigned int*)(b + 0xc) == 0);
        std::memset(b, 0xAA, sizeof b);
        FUN_14001a010(b);
        assert(*(long long*)(b + 0) == 0 && *(unsigned int*)(b + 8) == 0);
        assert(*(unsigned int*)(b + 0xc) == 0 && *(unsigned int*)(b + 0x10) == 0);
        assert(*(unsigned int*)(b + 0x14) == 0xffffffffu);
        assert(b[0x18] == 0xAA);
    }

    // 0x140016f00 reads the flag
    {
        g_nNpcFlag_140103fd0 = 0; assert(FUN_140016f00() == false);
        g_nNpcFlag_140103fd0 = 1; assert(FUN_140016f00() == true);
        g_nNpcFlag_140103fd0 = 0;
    }

    // 0x140016df0 and 0x140016e70 call their hooks only when one is installed
    {
        g_pfnNpc_140103fc0 = nullptr; g_pNpcCondCopy_140103ff0 = nullptr;
        assert(FUN_140016df0() == 0 && FUN_140016e70() == 0);
        g_pfnNpc_140103fc0 = (void*)&RET_FN; g_pNpcCondCopy_140103ff0 = (void*)&RET_FN;
        assert(FUN_140016df0() == 0xC0DE && FUN_140016e70() == 0xC0DE);
        g_pfnNpc_140103fc0 = nullptr; g_pNpcCondCopy_140103ff0 = nullptr;
    }

    // 0x140010860: the prefix stays as it is, the method name is upper-cased, then looked up
    {
        g_upperCalls = 0; g_getenvCalls = 0; g_envHit = false;
        assert(FUN_140010860("epoll") == false);
        assert(std::strcmp(g_fmt, "EVENT_NO%s") == 0 && g_fmtSize == 0x40);
        assert(std::strcmp(g_fmtArg, "epoll") == 0);
        assert(std::strcmp(g_getenvArg, "EVENT_NOEPOLL") == 0);
        assert(g_upperCalls == 5);                                  // only the five name bytes
        g_envHit = true;
        assert(FUN_140010860("epoll") == true);
        g_envHit = false;
    }

    // 0x140016640: two entry points when bit 1 is clear, plus the resolution reading
    {
        unsigned char m[0x60];
        std::memset(m, 0xAA, sizeof m);
        g_gapN = 0; g_qpfCalls = 0; g_qpcCalls = 0; g_resolveRet = 0x55;
        FUN_140016640(m, 0);
        assert(m[0x18] == 0 && m[0x19] == 0);                       // the cleared span reaches past them
        assert(m[0x50] == 0xAA);
        assert(*(void**)(m + 0x00) != nullptr && *(void**)(m + 0x08) != nullptr);
        assert(*(unsigned long long*)(m + 0x10) == 0x55);
        assert(*(unsigned long long*)(m + 0x20) == 0x55);
        assert(g_qpfCalls == 0 && g_qpcCalls == 0);                  // bit 0 was clear
        // bit 1 set: no entry points, and no counter either
        std::memset(m, 0, sizeof m);
        FUN_140016640(m, 3);
        assert(*(void**)(m + 0x00) == nullptr && *(void**)(m + 0x08) == nullptr);
        assert(g_qpfCalls == 0);
        // bit 0 only: the counter is read and scaled
        std::memset(m, 0, sizeof m);
        FUN_140016640(m, 1);
        assert(g_qpfCalls == 1 && g_qpcCalls == 1);
        assert(*(unsigned int*)(m + 0x38) == 1);
        assert(*(long long*)(m + 0x28) == 1234);
        assert(*(double*)(m + 0x30) == 1000000.0 / 1000000.0);
    }

    // 0x1400105b0: cached word, then the monitor, then the refresh arithmetic
    {
        static unsigned char base[0x2b0];
        std::memset(base, 0, sizeof base);
        int out[2] = { 0, 0 };
        *(long long*)(base + 0x1d0) = 1; g_ef0 = 0;
        *(int*)(base + 0x160) = 42;
        assert(FUN_1400105b0((long long)base, out) == 0);
        assert(g_ef0 == 1);                                          // the notifier was taken down first
        assert(*(long long*)out == 42);                              // the cached word answers directly
        // no cache, the monitor says nothing usable
        *(int*)(base + 0x160) = 0; g_monRet = 0xffffffffull;
        assert(FUN_1400105b0((long long)base, out) == 0xffffffffull);
        // no cache, the monitor fills the pair, and the cached second is far enough behind
        g_monRet = 0; g_outUsed = 1; g_clock[0] = 1000; g_clock[1] = 500000;
        *(long long*)(base + 0x1c0) = 10;
        g_outUsed = 1;
        assert(FUN_1400105b0((long long)base, out) == 0);
        // the monitor wrote 77/88 through the same pointer, and 15 < 77 refreshes the pair
        assert(*(long long*)(base + 0x1c0) == 77);
        assert(*(int*)(base + 0x1b8) == 1000 - 77);
        assert(*(int*)(base + 0x1bc) == 500000 - 88);
        // a borrow in the microseconds moves one second across and adds a million back
        g_clock[1] = 10; g_clock[0] = 1000;
        *(long long*)(base + 0x1c0) = 10;
        assert(FUN_1400105b0((long long)base, out) == 0);
        assert(*(int*)(base + 0x1b8) == (1000 - 77) - 1);
        assert(*(int*)(base + 0x1bc) == (10 - 88) + 1000000);
        g_outUsed = 0;
    }

    // 0x140015e70: null answers -1; otherwise the notifier is cycled around the install
    {
        static unsigned char base[0x2b0];
        std::memset(base, 0, sizeof base);
        assert(FUN_140015e70(nullptr, 1, 0, 0) == 0xffffffffull);
        g_e30 = 0; g_e50 = 0; g_e900Calls = 0; g_e900Ret = nullptr;
        assert(FUN_140015e70(base, 1, 0, 0) == 0);              // no notifier to cycle
        assert(g_e30 == 0 && g_e50 == 0 && g_e900Calls == 1);
        *(long long*)(base + 0x1d0) = 1;
        g_e900Ret = (void*)-1;
        assert(FUN_140015e70(base, 1, 0, 0) == 0xffffffffull);  // the install's -1 comes through
        assert(g_e30 == 1 && g_e50 == 1);
        g_e900Ret = (void*)0x1234;
        assert(FUN_140015e70(base, 1, 0, 0) == 0x1234);         // and anything else is truncated
        assert(g_e30 == 2 && g_e50 == 2);
    }

    std::printf("NPCSERVER_D183_OK: timer and queue helpers\n");
    return 0;
}

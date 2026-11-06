// Generated with family M — one check per body.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_m.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_v1 = 0, g_v2 = 0; static int g_nCalls = 0;

static void* Hookg_fnMD5392971984(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5392972208(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393108320(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393124912(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393158512(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393158624(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393420256(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393446512(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMD5393684784(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMS141823240(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }
static void* Hookg_fnMS141823248(void* a, void* b, void* c, void* d) { g_v1 = (uintptr_t)a; g_v2 = (uintptr_t)b; ++g_nCalls; return (void*)0x99; }

static unsigned char g_ab[0x3000];

int main() {
    g_fnMD5392971984 = &Hookg_fnMD5392971984;
    g_fnMD5392972208 = &Hookg_fnMD5392972208;
    g_fnMD5393108320 = &Hookg_fnMD5393108320;
    g_fnMD5393124912 = &Hookg_fnMD5393124912;
    g_fnMD5393158512 = &Hookg_fnMD5393158512;
    g_fnMD5393158624 = &Hookg_fnMD5393158624;
    g_fnMD5393420256 = &Hookg_fnMD5393420256;
    g_fnMD5393446512 = &Hookg_fnMD5393446512;
    g_fnMD5393684784 = &Hookg_fnMD5393684784;
    g_fnMS141823240 = &Hookg_fnMS141823240;
    g_fnMS141823248 = &Hookg_fnMS141823248;
    int arg2 = -5;
    {   // 0x14174a640
        g_nCalls = 0;
        void* pB = SynM2_14174a640(g_ab, nullptr, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == 0);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x141791450
        g_nCalls = 0;
        void* pB = SynM2_141791450(g_ab, nullptr, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == 0);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x14179a000
        g_nCalls = 0;
        void* pB = SynM2_14179a000(g_ab, nullptr, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == 0);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417d1a70
        g_nCalls = 0;
        void* pB = SynM2_1417d1a70(g_ab, nullptr, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == 0);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417de460
        g_nCalls = 0;
        void* pB = SynM2_1417de460(g_ab, nullptr, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == 0);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417de480
        g_nCalls = 0;
        void* pB = SynM2_1417de480(g_ab, nullptr, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == 0);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x141754910
        g_nCalls = 0;
        void* pB = SynM3_141754910(g_ab, &arg2, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)g_ab);
        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x141754930
        g_nCalls = 0;
        void* pB = SynM3_141754930(g_ab, &arg2, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)g_ab);
        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417914c0
        g_nCalls = 0;
        void* pB = SynM3_1417914c0(g_ab, &arg2, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)g_ab);
        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417b9e90
        g_nCalls = 0;
        void* pB = SynM3_1417b9e90(g_ab, &arg2, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)g_ab);
        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417bb870
        g_nCalls = 0;
        void* pB = SynM3_1417bb870(g_ab, &arg2, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)g_ab);
        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);
        CHECK(pB == (void*)0x99);
    }
    {   // 0x1417bb8a0
        g_nCalls = 0;
        void* pB = SynM3_1417bb8a0(g_ab, &arg2, nullptr, nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)g_ab);
        CHECK((intptr_t)g_v2 == (intptr_t)(int64_t)(int32_t)(intptr_t)&arg2);
        CHECK(pB == (void*)0x99);
    }

    std::printf("SYNDICATE_THUNKS7_OK: 35 bodies, %d checks\n", g_nChecks);
    return 0;
}

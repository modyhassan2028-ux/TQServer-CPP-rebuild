// Generated with family GR — the forwarded pointer is arg2 plus the summed displacement.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_gr.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_pSeen = 0; static int g_nCalls = 0;
static void* Hook(void* p) { ++g_nCalls; g_pSeen = (uintptr_t)p; return (void*)0xA55A; }

static unsigned char aRec[0x400];

int main() {
    g_fnGR_141727880 = &Hook;
    g_fnGR_141731c00 = &Hook;
    g_fnGR_14173db90 = &Hook;
    g_fnGR_141740c20 = &Hook;
    g_fnGR_14176f350 = &Hook;
    g_fnGR_14178d7f0 = &Hook;

    {   // 0x1417fac10
        g_nCalls = 0;
        void* pR = SynFwdTail_1417fac10(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x68);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1417fac50
        g_nCalls = 0;
        void* pR = SynFwdTail_1417fac50(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x68);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1417fd570
        g_nCalls = 0;
        void* pR = SynFwdTail_1417fd570(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0xa0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1417fd5b0
        g_nCalls = 0;
        void* pR = SynFwdTail_1417fd5b0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0xa0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1417fe280
        g_nCalls = 0;
        void* pR = SynFwdTail_1417fe280(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x58);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1417fe2e0
        g_nCalls = 0;
        void* pR = SynFwdTail_1417fe2e0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x58);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141807530
        g_nCalls = 0;
        void* pR = SynFwdTail_141807530(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x158);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141807570
        g_nCalls = 0;
        void* pR = SynFwdTail_141807570(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x158);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141807650
        g_nCalls = 0;
        void* pR = SynFwdTail_141807650(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x1f8);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141807a10
        g_nCalls = 0;
        void* pR = SynFwdTail_141807a10(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x158);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141807a50
        g_nCalls = 0;
        void* pR = SynFwdTail_141807a50(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x158);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141807b30
        g_nCalls = 0;
        void* pR = SynFwdTail_141807b30(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x1f8);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808030
        g_nCalls = 0;
        void* pR = SynFwdTail_141808030(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x670);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808070
        g_nCalls = 0;
        void* pR = SynFwdTail_141808070(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x670);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808150
        g_nCalls = 0;
        void* pR = SynFwdTail_141808150(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x7a8);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808470
        g_nCalls = 0;
        void* pR = SynFwdTail_141808470(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x5e0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418084b0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418084b0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x5e0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808590
        g_nCalls = 0;
        void* pR = SynFwdTail_141808590(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x880);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418088d0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418088d0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x628);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808910
        g_nCalls = 0;
        void* pR = SynFwdTail_141808910(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x628);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418089f0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418089f0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x7f0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808c30
        g_nCalls = 0;
        void* pR = SynFwdTail_141808c30(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x6b8);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808c70
        g_nCalls = 0;
        void* pR = SynFwdTail_141808c70(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x6b8);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808d50
        g_nCalls = 0;
        void* pR = SynFwdTail_141808d50(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x838);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808fb0
        g_nCalls = 0;
        void* pR = SynFwdTail_141808fb0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x598);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141808ff0
        g_nCalls = 0;
        void* pR = SynFwdTail_141808ff0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x598);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418090d0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418090d0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x8c8);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418097f0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418097f0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0xe0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141809830
        g_nCalls = 0;
        void* pR = SynFwdTail_141809830(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0xe0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x141809910
        g_nCalls = 0;
        void* pR = SynFwdTail_141809910(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0x128);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418128b0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418128b0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0xc0);
        CHECK(pR == (void*)0xA55A);
    }
    {   // 0x1418128f0
        g_nCalls = 0;
        void* pR = SynFwdTail_1418128f0(nullptr, aRec);
        CHECK(g_nCalls == 1);
        CHECK(g_pSeen == (uintptr_t)aRec + 0xc0);
        CHECK(pR == (void*)0xA55A);
    }

    std::printf("SYNDICATE_THUNKS_GR_OK: 32 bodies, %d checks\n", g_nChecks);
    return 0;
}

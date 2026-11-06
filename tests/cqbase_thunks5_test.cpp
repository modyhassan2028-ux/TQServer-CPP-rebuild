// Generated with families I, J and K — one check per function.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_i.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_v1 = 0; static int g_nCalls = 0;
static int32_t g_counters[53];

static void* SlotHook_1418230a0(void* p) { g_v1 = (uintptr_t)p; ++g_nCalls; return (void*)0x1234; }
static void* SlotHook_141823268(void* p) { g_v1 = (uintptr_t)p; ++g_nCalls; return (void*)0x1234; }
static void* SlotHook_141823290(void* p) { g_v1 = (uintptr_t)p; ++g_nCalls; return (void*)0x1234; }
static void* SlotHook_141823400(void* p) { g_v1 = (uintptr_t)p; ++g_nCalls; return (void*)0x1234; }

static unsigned char g_ab[0xd30];   // one byte past the largest offset read

int main() {
    g_fnSlot_1418230a0 = &SlotHook_1418230a0;
    g_fnSlot_141823268 = &SlotHook_141823268;
    g_fnSlot_141823290 = &SlotHook_141823290;
    g_fnSlot_141823400 = &SlotHook_141823400;
    for (int i = 0; i < 53; ++i) g_counters[i] = 0;
    g_pnGlob_141886cc8 = &g_counters[0];
    g_pnGlob_141886cd8 = &g_counters[1];
    g_pnGlob_141886ce8 = &g_counters[2];
    g_pnGlob_141886cf8 = &g_counters[3];
    g_pnGlob_141886cfc = &g_counters[4];
    g_pnGlob_141886d08 = &g_counters[5];
    g_pnGlob_141886d18 = &g_counters[6];
    g_pnGlob_141886d28 = &g_counters[7];
    g_pnGlob_141886d2c = &g_counters[8];
    g_pnGlob_141886d38 = &g_counters[9];
    g_pnGlob_141886d48 = &g_counters[10];
    g_pnGlob_141886d4c = &g_counters[11];
    g_pnGlob_141886d58 = &g_counters[12];
    g_pnGlob_141886d68 = &g_counters[13];
    g_pnGlob_141886d78 = &g_counters[14];
    g_pnGlob_141886d88 = &g_counters[15];
    g_pnGlob_141886d8c = &g_counters[16];
    g_pnGlob_141886d98 = &g_counters[17];
    g_pnGlob_141886da8 = &g_counters[18];
    g_pnGlob_141886dac = &g_counters[19];
    g_pnGlob_141886db8 = &g_counters[20];
    g_pnGlob_141886dbc = &g_counters[21];
    g_pnGlob_141886dc8 = &g_counters[22];
    g_pnGlob_141886dd8 = &g_counters[23];
    g_pnGlob_141886de8 = &g_counters[24];
    g_pnGlob_141886dec = &g_counters[25];
    g_pnGlob_141886df8 = &g_counters[26];
    g_pnGlob_141886dfc = &g_counters[27];
    g_pnGlob_141886e08 = &g_counters[28];
    g_pnGlob_141886e18 = &g_counters[29];
    g_pnGlob_141886e1c = &g_counters[30];
    g_pnGlob_141886e28 = &g_counters[31];
    g_pnGlob_141886e2c = &g_counters[32];
    g_pnGlob_141886e30 = &g_counters[33];
    g_pnGlob_141886e34 = &g_counters[34];
    g_pnGlob_141886e38 = &g_counters[35];
    g_pnGlob_141886e3c = &g_counters[36];
    g_pnGlob_141886e40 = &g_counters[37];
    g_pnGlob_141886e44 = &g_counters[38];
    g_pnGlob_141886e48 = &g_counters[39];
    g_pnGlob_141886e4c = &g_counters[40];
    g_pnGlob_141886e50 = &g_counters[41];
    g_pnGlob_141886e54 = &g_counters[42];
    g_pnGlob_141886e58 = &g_counters[43];
    g_pnGlob_141886e5c = &g_counters[44];
    g_pnGlob_141886e60 = &g_counters[45];
    g_pnGlob_141886e64 = &g_counters[46];
    g_pnGlob_141886e68 = &g_counters[47];
    g_pnGlob_141886e6c = &g_counters[48];
    g_pnGlob_141886e70 = &g_counters[49];
    g_pnGlob_141886e74 = &g_counters[50];
    g_pnGlob_141886e78 = &g_counters[51];

    {   // 0x1417f5ea0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f5ea0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f5ee0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f5ee0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f5f40
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f5f40(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f5fa0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f5fa0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6080
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6080(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f60c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f60c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6120
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6120(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6140
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6140(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6160
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6160(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6180
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6180(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6260
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6260(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6280
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6280(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f62a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f62a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f62e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f62e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6300
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6300(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6320
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6320(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6360
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6360(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f63a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f63a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f63c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f63c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f63e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f63e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6400
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6400(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6420
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6420(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6440
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6440(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6460
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6460(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6480
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6480(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f64c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f64c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f64e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f64e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6500
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6500(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6520
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6520(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6540
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6540(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6560
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6560(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6580
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6580(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f65a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f65a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f65c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f65c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f65e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f65e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6ef0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6ef0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6f10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6f10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6f30
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6f30(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6f70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6f70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6f90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6f90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f6fb0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f6fb0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7050
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7050(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7070
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7070(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7090
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7090(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f76d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f76d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f76f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f76f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7710
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7710(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7750
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7750(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7770
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7770(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7790
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7790(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f77d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f77d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f77f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f77f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7810
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7810(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7850
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7850(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7870
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7870(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7890
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7890(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7c50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7c50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7c70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7c70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7c90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7c90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7cd0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7cd0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7cf0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7cf0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7d10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7d10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7d50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7d50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7d70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7d70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f7d90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f7d90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f8d60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f8d60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f8d80
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f8d80(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f8da0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f8da0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f9dd0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f9dd0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f9df0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f9df0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417f9e10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417f9e10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb260
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb260(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x70));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb280
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb280(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xa8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb2c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb2c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xa8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb2e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb2e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x70));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb300
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb300(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xa8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb340
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb340(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xa8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb360
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb360(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x70));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xa8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb3c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb3c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xa8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb440
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb440(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x498));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb480
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb480(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x498));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb4e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb4e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x498));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb520
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb520(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x498));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb5a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb5a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x4a8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb5e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb5e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x4a8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb9c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb9c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fb9e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fb9e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fba00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fba00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fba20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fba20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fbbf0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fbbf0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fbc10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fbc10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fbc30
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fbc30(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fbca0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fbca0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fbcc0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fbcc0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fbce0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fbce0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fcee0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fcee0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x98));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fcf00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fcf00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fcf20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fcf20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fd060
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fd060(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fd080
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fd080(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fd0a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fd0a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fda40
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fda40(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fda60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fda60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fda80
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fda80(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fdac0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fdac0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fdae0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fdae0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fdb00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fdb00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fdb40
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fdb40(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fdc20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fdc20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe3a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe3a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe3c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe3c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe400
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe400(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe420
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe420(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe440
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe440(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe480
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe480(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe4a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe4a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe4c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe4c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe4e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe4e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe500
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe500(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe520
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe520(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe540
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe540(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe560
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe560(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe840
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe840(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe860
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe860(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fe880
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fe880(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fea40
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fea40(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fea60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fea60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fea80
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fea80(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417feac0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417feac0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417feae0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417feae0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417feb00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417feb00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fecc0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fecc0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fece0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fece0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fed00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fed00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff010
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff010(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x100));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff050
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff050(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x100));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff0f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff0f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x130));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff130
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff130(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x130));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff150
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff150(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x100));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff1b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff1b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x130));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff1d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff1d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x100));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff270
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff270(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x130));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff290
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff290(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x100));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff2b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff2b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x88));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff2f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff2f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x88));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417ff390
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417ff390(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x88));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fffc0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1417fffc0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x80));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800000
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800000(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x80));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800060
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800060(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x80));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800340
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800340(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800360
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800360(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418003c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418003c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418003e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418003e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800400
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800400(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800440
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800440(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800460
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800460(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800480
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800480(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418004a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418004a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418004c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418004c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418004e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418004e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800500
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800500(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800520
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800520(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800540
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800540(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800560
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800560(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800580
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800580(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418005a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418005a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418005c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418005c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418005e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418005e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800600
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800600(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800620
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800620(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800640
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800640(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800660
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800660(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800680
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800680(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418006a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418006a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418006c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418006c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418006e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418006e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800700
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800700(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141800720
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141800720(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418014d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418014d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418014f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418014f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801510
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801510(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801550
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801550(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801570
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801570(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801590
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801590(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418015d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418015d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418015f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418015f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801610
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801610(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801650
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801650(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801670
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801670(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801690
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801690(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801700
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801700(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801720
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801720(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801740
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801740(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801780
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801780(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418017a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418017a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418017c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418017c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801800
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801800(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801820
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801820(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801840
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801840(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801880
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801880(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418018a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418018a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418018c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418018c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801900
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801900(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801920
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801920(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801940
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801940(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141801980
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141801980(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418019a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418019a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418019c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418019c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802240
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802240(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802260
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802260(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802280
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802280(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418022c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418022c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418022e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418022e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802300
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802300(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802340
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802340(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802360
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802360(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418023c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418023c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418023e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418023e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802400
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802400(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802440
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802440(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802460
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802460(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802480
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802480(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802b20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802b20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802b40
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802b40(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141802b60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141802b60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806a70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806a70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806a90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806a90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806ab0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806ab0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806ca0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806ca0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x98));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806cc0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806cc0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806ce0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806ce0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806f20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806f20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806f40
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806f40(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141806f60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141806f60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418095d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418095d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x98));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418095f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418095f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141809610
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141809610(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b370
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b370(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b390
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b390(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b4b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b4b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b4d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b4d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b4f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b4f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b530
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b530(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b550
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b550(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180b570
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180b570(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c150
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c150(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c1f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c1f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c210
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c210(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c230
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c230(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c450
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c450(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c470
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c470(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c490
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c490(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c5b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c5b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x30));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c5d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c5d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c5f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c5f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c610
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c610(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180c7d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180c7d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x70));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180dae0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180dae0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180db00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180db00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180db20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180db20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180db60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180db60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180dd70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180dd70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180e8d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180e8d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180e8f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180e8f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180e950
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180e950(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180e970
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180e970(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ec50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ec50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ec70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ec70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ec90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ec90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ee50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ee50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ee70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ee70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ee90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ee90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180eed0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180eed0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180eef0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180eef0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ef10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ef10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ef50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ef50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ef70
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ef70(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180ef90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180ef90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180f390
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180f390(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x90));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180f3b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180f3b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180f3f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180f3f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180f490
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180f490(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x90));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180f4b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180f4b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180f4f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180f4f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14180fe50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14180fe50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418101b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418101b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418101d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418101d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418101f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418101f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810230
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810230(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810250
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810250(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810270
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810270(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810290
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810290(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810330
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810330(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810350
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810350(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810370
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810370(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810390
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810390(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810870
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810870(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810890
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810890(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418108b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418108b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418108f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418108f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810910
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810910(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810930
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810930(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810970
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810970(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810990
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810990(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418109b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418109b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810cb0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810cb0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810cd0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810cd0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141810cf0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141810cf0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141812380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141812380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418123a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418123a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418123c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418123c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141812500
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141812500(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x98));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141812520
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141812520(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141812540
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141812540(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418146a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418146a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418146c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418146c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418146e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418146e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814720
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814720(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814740
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814740(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814760
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814760(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418147a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418147a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418147c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418147c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814860
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814860(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814880
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814880(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814bc0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814bc0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814be0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814be0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814da0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814da0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814dc0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814dc0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814de0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814de0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814e80
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814e80(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814ea0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814ea0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141814ec0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141814ec0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141815c60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141815c60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141815ce0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141815ce0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x4b0));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141815d60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141815d60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x490));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141815de0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141815de0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141815f20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141815f20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418160e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418160e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816120
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816120(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816140
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816140(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816180
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816180(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816220
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816220(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x48));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816240
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816240(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x4b8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816280
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816280(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x4b8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816320
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816320(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x490));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816380
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816380(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x8c0));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418165a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418165a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x58));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418168e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418168e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141816b20
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141816b20(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x58));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418175c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418175c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x80));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418176c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418176c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x80));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418176e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418176e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xb0));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141817720
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141817720(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xb0));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141817780
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141817780(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x80));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141817b10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141817b10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xcf0));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141818900
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141818900(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x520));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141818c90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141818c90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x4e0));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418190d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418190d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0xc8));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819710
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819710(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819730
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819730(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819750
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819750(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819770
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819770(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819830
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819830(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819850
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819850(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819870
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819870(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819890
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819890(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418199d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418199d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1418199f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_1418199f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819a10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819a10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819f10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819f10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819f30
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819f30(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819f50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819f50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819f90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819f90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819fb0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819fb0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141819fd0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141819fd0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a030
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a030(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a050
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a050(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a070
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a070(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a0b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a0b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a0d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a0d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a0f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a0f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a4f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a4f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a510
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a510(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a530
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a530(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a570
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a570(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a590
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a590(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a5b0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a5b0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a610
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a610(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a630
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a630(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181a650
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181a650(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181ab60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181ab60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181bb90
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181bb90(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181bcf0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181bcf0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181bd10
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181bd10(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c330
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c330(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x120));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c590
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c590(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x120));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c8d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c8d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c8f0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c8f0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c910
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c910(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c950
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c950(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181c970
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181c970(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d190
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d190(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d2d0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d2d0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d620
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d620(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d6c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d6c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d840
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d840(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d9a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d9a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181d9c0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181d9c0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181db60
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181db60(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181db80
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181db80(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x38));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181dd80
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181dd80(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181dda0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181dda0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e070
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e070(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x460));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e510
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e510(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e530
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e530(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x50));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e550
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e550(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x78));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e840
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e840(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e890
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e890(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x28));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e8e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e8e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e980
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e980(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x90));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e9a0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e9a0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x68));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181e9e0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181e9e0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x128));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181ea00
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181ea00(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x100));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181ed50
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181ed50(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x14181eeb0
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_14181eeb0(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x60));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x141821760
        g_nCalls = 0; g_v1 = 0;
        void* pBack = SynThkI_141821760(g_ab, g_ab);
        CHECK(g_nCalls == 1);
        CHECK(g_v1 == (uintptr_t)(g_ab + 0x40));
        CHECK(pBack == (void*)0x1234);
    }
    {   // 0x1417fdb60
        *g_pnGlob_141886cf8 = 0x1ff;
        int32_t r = SynMask_1417fdb60(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886cf8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1417fdb80
        *g_pnGlob_141886cf8 = 0x1ff;
        int32_t r = SynMask_1417fdb80(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886cf8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1417fdba0
        *g_pnGlob_141886cf8 = 0x1ff;
        int32_t r = SynMask_1417fdba0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886cf8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1417fdbc0
        *g_pnGlob_141886cf8 = 0x1ff;
        int32_t r = SynMask_1417fdbc0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886cf8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1417fe040
        *g_pnGlob_141886cf8 = 0x1ff;
        int32_t r = SynMask_1417fe040(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886cf8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1417fe060
        *g_pnGlob_141886cf8 = 0x1ff;
        int32_t r = SynMask_1417fe060(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886cf8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180bed0
        *g_pnGlob_141886d28 = 0x1ff;
        int32_t r = SynMask_14180bed0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d28 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180bef0
        *g_pnGlob_141886d28 = 0x1ff;
        int32_t r = SynMask_14180bef0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d28 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180bf10
        *g_pnGlob_141886d28 = 0x1ff;
        int32_t r = SynMask_14180bf10(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d28 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180bf30
        *g_pnGlob_141886d28 = 0x1ff;
        int32_t r = SynMask_14180bf30(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d28 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180bfd0
        *g_pnGlob_141886d28 = 0x1ff;
        int32_t r = SynMask_14180bfd0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d28 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180db80
        *g_pnGlob_141886d78 = 0x1ff;
        int32_t r = SynMask_14180db80(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d78 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180dba0
        *g_pnGlob_141886d78 = 0x1ff;
        int32_t r = SynMask_14180dba0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d78 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180dbc0
        *g_pnGlob_141886d78 = 0x1ff;
        int32_t r = SynMask_14180dbc0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d78 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180dbe0
        *g_pnGlob_141886d78 = 0x1ff;
        int32_t r = SynMask_14180dbe0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d78 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180dd30
        *g_pnGlob_141886d78 = 0x1ff;
        int32_t r = SynMask_14180dd30(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d78 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180e6b0
        *g_pnGlob_141886d88 = 0x1ff;
        int32_t r = SynMask_14180e6b0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d88 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180e6d0
        *g_pnGlob_141886d88 = 0x1ff;
        int32_t r = SynMask_14180e6d0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d88 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180e6f0
        *g_pnGlob_141886d88 = 0x1ff;
        int32_t r = SynMask_14180e6f0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d88 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180e710
        *g_pnGlob_141886d88 = 0x1ff;
        int32_t r = SynMask_14180e710(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d88 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14180e830
        *g_pnGlob_141886d88 = 0x1ff;
        int32_t r = SynMask_14180e830(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886d88 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418102b0
        *g_pnGlob_141886da8 = 0x1ff;
        int32_t r = SynMask_1418102b0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886da8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418102d0
        *g_pnGlob_141886da8 = 0x1ff;
        int32_t r = SynMask_1418102d0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886da8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418102f0
        *g_pnGlob_141886da8 = 0x1ff;
        int32_t r = SynMask_1418102f0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886da8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141810310
        *g_pnGlob_141886da8 = 0x1ff;
        int32_t r = SynMask_141810310(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886da8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141814660
        *g_pnGlob_141886da8 = 0x1ff;
        int32_t r = SynMask_141814660(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886da8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418147e0
        *g_pnGlob_141886db8 = 0x1ff;
        int32_t r = SynMask_1418147e0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886db8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141814800
        *g_pnGlob_141886db8 = 0x1ff;
        int32_t r = SynMask_141814800(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886db8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141814820
        *g_pnGlob_141886db8 = 0x1ff;
        int32_t r = SynMask_141814820(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886db8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141814840
        *g_pnGlob_141886db8 = 0x1ff;
        int32_t r = SynMask_141814840(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886db8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141819430
        *g_pnGlob_141886de8 = 0x1ff;
        int32_t r = SynMask_141819430(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886de8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141819450
        *g_pnGlob_141886de8 = 0x1ff;
        int32_t r = SynMask_141819450(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886de8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141819470
        *g_pnGlob_141886de8 = 0x1ff;
        int32_t r = SynMask_141819470(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886de8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141819490
        *g_pnGlob_141886de8 = 0x1ff;
        int32_t r = SynMask_141819490(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886de8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418194b0
        *g_pnGlob_141886de8 = 0x1ff;
        int32_t r = SynMask_1418194b0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886de8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141819570
        *g_pnGlob_141886df8 = 0x1ff;
        int32_t r = SynMask_141819570(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886df8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x141819590
        *g_pnGlob_141886df8 = 0x1ff;
        int32_t r = SynMask_141819590(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886df8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418195b0
        *g_pnGlob_141886df8 = 0x1ff;
        int32_t r = SynMask_1418195b0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886df8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418195d0
        *g_pnGlob_141886df8 = 0x1ff;
        int32_t r = SynMask_1418195d0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886df8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418195f0
        *g_pnGlob_141886df8 = 0x1ff;
        int32_t r = SynMask_1418195f0(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886df8 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14181c810
        *g_pnGlob_141886e18 = 0x1ff;
        int32_t r = SynMask_14181c810(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886e18 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14181c830
        *g_pnGlob_141886e18 = 0x1ff;
        int32_t r = SynMask_14181c830(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886e18 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14181c850
        *g_pnGlob_141886e18 = 0x1ff;
        int32_t r = SynMask_14181c850(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886e18 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14181c870
        *g_pnGlob_141886e18 = 0x1ff;
        int32_t r = SynMask_14181c870(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886e18 == (0x1ff & 0xfffffffe));
    }
    {   // 0x14181c890
        *g_pnGlob_141886e18 = 0x1ff;
        int32_t r = SynMask_14181c890(nullptr, nullptr);
        CHECK(r == (0x1ff & 0xfffffffe));
        CHECK(*g_pnGlob_141886e18 == (0x1ff & 0xfffffffe));
    }
    {   // 0x1418218b0
        *g_pnGlob_141886cc8 = 0;
        int32_t r = SynStore_1418218b0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886cc8 == 0x1234);
    }
    {   // 0x1418218d0
        *g_pnGlob_141886cd8 = 0;
        int32_t r = SynStore_1418218d0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886cd8 == 0x1234);
    }
    {   // 0x1418218f0
        *g_pnGlob_141886ce8 = 0;
        int32_t r = SynStore_1418218f0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886ce8 == 0x1234);
    }
    {   // 0x141821910
        *g_pnGlob_141886cfc = 0;
        int32_t r = SynStore_141821910(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886cfc == 0x1234);
    }
    {   // 0x141821930
        *g_pnGlob_141886d08 = 0;
        int32_t r = SynStore_141821930(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d08 == 0x1234);
    }
    {   // 0x141821950
        *g_pnGlob_141886d18 = 0;
        int32_t r = SynStore_141821950(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d18 == 0x1234);
    }
    {   // 0x141821970
        *g_pnGlob_141886d2c = 0;
        int32_t r = SynStore_141821970(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d2c == 0x1234);
    }
    {   // 0x141821990
        *g_pnGlob_141886d38 = 0;
        int32_t r = SynStore_141821990(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d38 == 0x1234);
    }
    {   // 0x1418219b0
        *g_pnGlob_141886d48 = 0;
        int32_t r = SynStore_1418219b0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d48 == 0x1234);
    }
    {   // 0x1418219d0
        *g_pnGlob_141886d4c = 0;
        int32_t r = SynStore_1418219d0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d4c == 0x1234);
    }
    {   // 0x1418219f0
        *g_pnGlob_141886d58 = 0;
        int32_t r = SynStore_1418219f0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d58 == 0x1234);
    }
    {   // 0x141821a10
        *g_pnGlob_141886d68 = 0;
        int32_t r = SynStore_141821a10(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d68 == 0x1234);
    }
    {   // 0x141821a30
        *g_pnGlob_141886d8c = 0;
        int32_t r = SynStore_141821a30(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d8c == 0x1234);
    }
    {   // 0x141821a50
        *g_pnGlob_141886d98 = 0;
        int32_t r = SynStore_141821a50(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886d98 == 0x1234);
    }
    {   // 0x141821a70
        *g_pnGlob_141886dac = 0;
        int32_t r = SynStore_141821a70(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886dac == 0x1234);
    }
    {   // 0x141821a90
        *g_pnGlob_141886dbc = 0;
        int32_t r = SynStore_141821a90(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886dbc == 0x1234);
    }
    {   // 0x141821ab0
        *g_pnGlob_141886dc8 = 0;
        int32_t r = SynStore_141821ab0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886dc8 == 0x1234);
    }
    {   // 0x141821ad0
        *g_pnGlob_141886dd8 = 0;
        int32_t r = SynStore_141821ad0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886dd8 == 0x1234);
    }
    {   // 0x141821af0
        *g_pnGlob_141886dec = 0;
        int32_t r = SynStore_141821af0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886dec == 0x1234);
    }
    {   // 0x141821b10
        *g_pnGlob_141886dfc = 0;
        int32_t r = SynStore_141821b10(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886dfc == 0x1234);
    }
    {   // 0x141821b30
        *g_pnGlob_141886e08 = 0;
        int32_t r = SynStore_141821b30(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e08 == 0x1234);
    }
    {   // 0x141821b50
        *g_pnGlob_141886e1c = 0;
        int32_t r = SynStore_141821b50(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e1c == 0x1234);
    }
    {   // 0x141821b70
        *g_pnGlob_141886e28 = 0;
        int32_t r = SynStore_141821b70(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e28 == 0x1234);
    }
    {   // 0x141821b90
        *g_pnGlob_141886e2c = 0;
        int32_t r = SynStore_141821b90(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e2c == 0x1234);
    }
    {   // 0x141821bb0
        *g_pnGlob_141886e30 = 0;
        int32_t r = SynStore_141821bb0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e30 == 0x1234);
    }
    {   // 0x141821bd0
        *g_pnGlob_141886e34 = 0;
        int32_t r = SynStore_141821bd0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e34 == 0x1234);
    }
    {   // 0x141821bf0
        *g_pnGlob_141886e38 = 0;
        int32_t r = SynStore_141821bf0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e38 == 0x1234);
    }
    {   // 0x141821c10
        *g_pnGlob_141886e3c = 0;
        int32_t r = SynStore_141821c10(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e3c == 0x1234);
    }
    {   // 0x141821c30
        *g_pnGlob_141886e40 = 0;
        int32_t r = SynStore_141821c30(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e40 == 0x1234);
    }
    {   // 0x141821c50
        *g_pnGlob_141886e44 = 0;
        int32_t r = SynStore_141821c50(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e44 == 0x1234);
    }
    {   // 0x141821c70
        *g_pnGlob_141886e48 = 0;
        int32_t r = SynStore_141821c70(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e48 == 0x1234);
    }
    {   // 0x141821c90
        *g_pnGlob_141886e4c = 0;
        int32_t r = SynStore_141821c90(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e4c == 0x1234);
    }
    {   // 0x141821cb0
        *g_pnGlob_141886e50 = 0;
        int32_t r = SynStore_141821cb0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e50 == 0x1234);
    }
    {   // 0x141821cd0
        *g_pnGlob_141886e54 = 0;
        int32_t r = SynStore_141821cd0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e54 == 0x1234);
    }
    {   // 0x141821cf0
        *g_pnGlob_141886e58 = 0;
        int32_t r = SynStore_141821cf0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e58 == 0x1234);
    }
    {   // 0x141821d10
        *g_pnGlob_141886e5c = 0;
        int32_t r = SynStore_141821d10(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e5c == 0x1234);
    }
    {   // 0x141821d30
        *g_pnGlob_141886e60 = 0;
        int32_t r = SynStore_141821d30(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e60 == 0x1234);
    }
    {   // 0x141821d50
        *g_pnGlob_141886e64 = 0;
        int32_t r = SynStore_141821d50(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e64 == 0x1234);
    }
    {   // 0x141821d70
        *g_pnGlob_141886e68 = 0;
        int32_t r = SynStore_141821d70(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e68 == 0x1234);
    }
    {   // 0x141821d90
        *g_pnGlob_141886e6c = 0;
        int32_t r = SynStore_141821d90(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e6c == 0x1234);
    }
    {   // 0x141821db0
        *g_pnGlob_141886e70 = 0;
        int32_t r = SynStore_141821db0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e70 == 0x1234);
    }
    {   // 0x141821dd0
        *g_pnGlob_141886e74 = 0;
        int32_t r = SynStore_141821dd0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e74 == 0x1234);
    }
    {   // 0x141821df0
        *g_pnGlob_141886e78 = 0;
        int32_t r = SynStore_141821df0(nullptr, nullptr);
        CHECK(r == 0x1234);
        CHECK(*g_pnGlob_141886e78 == 0x1234);
    }

    std::printf("SYNDICATE_THUNKS5_OK: 519 functions, %d checks\n", g_nChecks);
    return 0;
}

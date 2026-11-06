// Generated with family SD — the sentinel points at itself on all three links.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_sd.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static void* g_pThisSeen = nullptr; static int g_nAlloc = 0;
static unsigned char aNode[0x80]; static unsigned char aThis[0x80];
static void Zero(void* p) { std::memset(p, 0, 0x80); }
static void* Hook(void* pThis) { ++g_nAlloc; g_pThisSeen = pThis; Zero(aNode); return aNode; }

int main() {
    g_fnSD_141726c30 = &Hook;
    g_fnSD_141726c90 = &Hook;
    g_fnSD_141726cf0 = &Hook;
    g_fnSD_141726d50 = &Hook;
    g_fnSD_141726db0 = &Hook;
    g_fnSD_141726ec0 = &Hook;
    g_fnSD_14173bc00 = &Hook;
    g_fnSD_14173bcb0 = &Hook;
    g_fnSD_141746a00 = &Hook;
    g_fnSD_141746a60 = &Hook;
    g_fnSD_141755f90 = &Hook;
    g_fnSD_141756200 = &Hook;
    g_fnSD_141756260 = &Hook;
    g_fnSD_1417562c0 = &Hook;
    g_fnSD_1417563b0 = &Hook;
    g_fnSD_141756410 = &Hook;
    g_fnSD_141756470 = &Hook;
    g_fnSD_1417564d0 = &Hook;
    g_fnSD_1417565b0 = &Hook;
    g_fnSD_141756610 = &Hook;
    g_fnSD_141776670 = &Hook;
    g_fnSD_14177ace0 = &Hook;
    g_fnSD_14178a6a0 = &Hook;
    g_fnSD_14178a700 = &Hook;
    g_fnSD_1417935d0 = &Hook;
    g_fnSD_141793680 = &Hook;
    g_fnSD_141793760 = &Hook;
    g_fnSD_1417a76e0 = &Hook;
    g_fnSD_1417c8590 = &Hook;
    g_fnSD_1417c8620 = &Hook;

    {   // 0x141727d20
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141727d20(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x1d) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141727d60
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141727d60(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141727da0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141727da0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x51) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141727de0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141727de0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x49) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141727e20
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141727e20(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x1d) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417281a0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417281a0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x1b) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x14173c020
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_14173c020(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x61) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x14173c580
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_14173c580(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x21) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417478a0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417478a0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x3d) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417478e0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417478e0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141757df0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141757df0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x2d) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417584f0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417584f0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758530
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758530(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x59) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758590
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758590(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758910
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758910(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x61) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758950
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758950(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758990
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758990(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x61) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417589d0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417589d0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758d50
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758d50(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x69) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141758d90
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141758d90(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417768c0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417768c0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x39) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x14177adf0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_14177adf0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x14178b090
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_14178b090(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x14178b260
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_14178b260(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x49) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141794800
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141794800(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x61) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141794dd0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141794dd0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x21) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x141795150
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_141795150(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417a7860
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417a7860(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417c9cd0
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417c9cd0(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x21) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }
    {   // 0x1417c9d10
        std::memset(aThis, 0, sizeof(aThis));
        g_nAlloc = 0;
        SynSentinelInit_1417c9d10(aThis);
        CHECK(g_nAlloc == 1);
        CHECK(g_pThisSeen == (void*)aThis);                       // rcx at insn 3
        CHECK(*(void**)(aThis + 0x30) == (void*)aNode);           // insn 4
        CHECK(*(unsigned char*)(aNode + 0x29) == 0x1);           // insn 5
        CHECK(*(void**)(aNode + 0x8) == (void*)aNode);            // parent = self
        CHECK(*(void**)(aNode + 0x0) == (void*)aNode);            // left = self
        CHECK(*(void**)(aNode + 0x10) == (void*)aNode);           // right = self
        CHECK(*(void**)(aThis + 0x38) == (void*)0x0);            // insn 12
    }

    std::printf("SYNDICATE_THUNKS_SD_OK: 30 bodies, %d checks\n", g_nChecks);
    return 0;
}

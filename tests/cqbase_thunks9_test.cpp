// Generated with family H2 — one check per variant, plus the null path.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include "modules/syndicate/src/synthunks_h2.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uint64_t g_nAsked = 0; static int g_bNull = 0; static unsigned char g_blk[64];
static void* Hook(uint64_t n) { g_nAsked = n; return g_bNull ? nullptr : (void*)g_blk; }

int main() {
    g_fnH2D1417f3166 = &Hook;
    unsigned char aThis[16];
    std::memset(aThis, 0xCC, sizeof(aThis));

    {   // 0x1417270f0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417270f0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417270f0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141727140
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141727140(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141727140(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141727190
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141727190(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141727190(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417271e0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417271e0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417271e0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141727230
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141727230(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141727230(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141727280
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141727280(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141727280(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141727a00
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141727a00(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141727a00(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141727c70
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141727c70(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141727c70(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141728b90
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141728b90(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141728b90(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141728be0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141728be0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141728be0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141728c30
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141728c30(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141728c30(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141728c80
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141728c80(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141728c80(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141728cd0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141728cd0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141728cd0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141728d20
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141728d20(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141728d20(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172aa60
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172aa60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172aa60(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172aab0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172aab0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172aab0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172ab00
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172ab00(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172ab00(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172ab50
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172ab50(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172ab50(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172aba0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172aba0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172aba0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172ac00
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172ac00(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172ac00(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172d0d0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172d0d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172d0d0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172d570
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172d570(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172d570(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172d5c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172d5c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172d5c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172d7c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172d7c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172d7c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172d9c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172d9c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172d9c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14172da10
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14172da10(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14172da10(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173c900
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173c900(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173c900(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173c950
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173c950(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173c950(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173d050
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173d050(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173d050(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173d0a0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173d0a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173d0a0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173d760
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173d760(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173d760(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173d7b0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173d7b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173d7b0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173daf0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173daf0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173daf0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173db40
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14173db40(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14173db40(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141740650
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141740650(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141740650(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141746b90
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141746b90(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141746b90(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141746be0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141746be0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141746be0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417479e0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417479e0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417479e0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141747a30
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141747a30(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141747a30(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141748cf0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141748cf0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141748cf0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141748d40
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141748d40(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141748d40(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14174a100
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14174a100(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14174a100(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14174a300
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14174a300(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14174a300(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756970
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756970(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756970(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417569c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417569c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417569c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756a10
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756a10(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756a10(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756a60
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756a60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756a60(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756ab0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756ab0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756ab0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756b00
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756b00(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756b00(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756b50
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756b50(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756b50(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756ba0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756ba0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756ba0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756bf0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756bf0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756bf0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141756c40
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141756c40(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141756c40(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141757ab0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141757ab0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141757ab0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141757b00
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141757b00(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141757b00(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175aad0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175aad0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175aad0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ab20
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ab20(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ab20(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ab70
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ab70(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ab70(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175abc0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175abc0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175abc0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ac10
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ac10(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ac10(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ac60
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ac60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ac60(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175acb0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175acb0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175acb0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ad00
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ad00(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ad00(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ad50
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ad50(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ad50(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175ada0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175ada0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175ada0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e5c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e5c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e5c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e610
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e610(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e610(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e660
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e660(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e660(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e6b0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e6b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e6b0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e700
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e700(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e700(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e750
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e750(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e750(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e7a0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e7a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e7a0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e7f0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e7f0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e7f0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e840
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e840(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e840(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14175e890
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14175e890(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14175e890(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417627e0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417627e0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417627e0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762830
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762830(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762830(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762b30
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762b30(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762b30(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762b80
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762b80(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762b80(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762bd0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762bd0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762bd0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762c20
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762c20(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762c20(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762c70
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762c70(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762c70(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762cc0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762cc0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762cc0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762d10
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762d10(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762d10(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141762d60
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141762d60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141762d60(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417770d0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417770d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417770d0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141777500
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141777500(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141777500(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417779e0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417779e0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417779e0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141777ce0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141777ce0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141777ce0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14177ad40
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14177ad40(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14177ad40(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14177ae30
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14177ae30(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14177ae30(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14177b2b0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14177b2b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14177b2b0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14177be60
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14177be60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14177be60(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141782ae0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141782ae0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141782ae0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178b2d0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178b2d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178b2d0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178b320
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178b320(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178b320(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178c600
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178c600(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178c600(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178c650
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178c650(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178c650(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178d0a0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178d0a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178d0a0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178d0f0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178d0f0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178d0f0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178d750
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178d750(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178d750(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178d7a0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_14178d7a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_14178d7a0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141793820
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141793820(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141793820(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141793870
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141793870(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141793870(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417938c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417938c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417938c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141794440
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141794440(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141794440(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417955f0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417955f0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417955f0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141795640
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141795640(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141795640(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141795690
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141795690(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141795690(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141797430
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141797430(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141797430(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141797480
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141797480(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141797480(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417974d0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417974d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417974d0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141799f10
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141799f10(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141799f10(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141799f60
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141799f60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141799f60(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141799fb0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_141799fb0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_141799fb0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a4790
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417a4790(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417a4790(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a78a0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417a78a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417a78a0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a7d20
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417a7d20(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417a7d20(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a87c0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417a87c0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417a87c0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a8ce0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417a8ce0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417a8ce0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417bc010
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417bc010(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417bc010(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417bc060
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417bc060(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417bc060(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417bc0e0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417bc0e0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417bc0e0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c8810
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417c8810(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417c8810(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c8860
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417c8860(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417c8860(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c88b0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417c88b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417c88b0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c8900
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417c8900(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417c8900(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417ca6b0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417ca6b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417ca6b0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417ca700
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417ca700(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417ca700(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417ca750
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417ca750(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417ca750(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417ca7a0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417ca7a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417ca7a0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417cdc30
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417cdc30(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417cdc30(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417cdc80
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417cdc80(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417cdc80(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417cdcd0
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417cdcd0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417cdcd0(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417cdd20
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417cdd20(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417cdd20(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417d2870
        g_bNull = 0; g_nAsked = 0;
        void* pB = SynAlc2_1417d2870(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pB == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bNull = 1;
        pB = SynAlc2_1417d2870(aThis);
        CHECK(pB == aThis);
        CHECK(*(void**)aThis == nullptr);
    }

    std::printf("SYNDICATE_THUNKS9_OK: 136 variants, %d checks\n", g_nChecks);
    return 0;
}

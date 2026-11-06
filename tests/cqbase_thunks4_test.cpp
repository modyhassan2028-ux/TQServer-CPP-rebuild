// Generated with family H — one check per function, plus the null path.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include "modules/syndicate/src/synthunks_h.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uint64_t g_nAsked = 0; static int g_bGiveNull = 0; static unsigned char g_blk[64];
static void* AllocHook(uint64_t n) { g_nAsked = n; return g_bGiveNull ? nullptr : (void*)g_blk; }


int main() {
    g_fnAlloc1417f3166 = &AllocHook;

    unsigned char aThis[16];
    std::memset(aThis, 0xCC, sizeof(aThis));

    {   // 0x141725a60
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141725a60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141725a60(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141725aa0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141725aa0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141725aa0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141725ae0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141725ae0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141725ae0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141725b20
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141725b20(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141725b20(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141725b60
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141725b60(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141725b60(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141726550
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141726550(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141726550(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141726a50
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141726a50(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141726a50(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173bd90
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_14173bd90(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_14173bd90(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14173bdd0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_14173bdd0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_14173bdd0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141740350
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141740350(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141740350(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417405b0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417405b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417405b0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141746070
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141746070(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141746070(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417460b0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417460b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417460b0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417545d0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417545d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417545d0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754610
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754610(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754610(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754650
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754650(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754650(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754690
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754690(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754690(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417546d0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417546d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417546d0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754710
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754710(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754710(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754750
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754750(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754750(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754790
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754790(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754790(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417547d0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417547d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417547d0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141754810
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141754810(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141754810(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417558e0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417558e0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417558e0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141755920
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141755920(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141755920(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141776800
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141776800(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141776800(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14177aac0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_14177aac0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_14177aac0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141782340
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141782340(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141782340(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178a760
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_14178a760(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_14178a760(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x14178a7a0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_14178a7a0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_14178a7a0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141792700
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141792700(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141792700(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141792740
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141792740(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141792740(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x141792780
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_141792780(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_141792780(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417933b0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417933b0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417933b0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a3ce0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417a3ce0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417a3ce0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417a7740
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417a7740(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417a7740(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417bb790
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417bb790(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417bb790(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417bb7d0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417bb7d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417bb7d0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417bb810
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417bb810(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417bb810(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c76d0
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417c76d0(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417c76d0(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c7710
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417c7710(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417c7710(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c7750
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417c7750(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417c7750(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417c7790
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417c7790(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417c7790(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }
    {   // 0x1417d2320
        g_bGiveNull = 0; g_nAsked = 0;
        void* pBack = SynAlc_1417d2320(aThis);
        CHECK(g_nAsked == 0x8);
        CHECK(pBack == aThis);
        CHECK(*(void**)g_blk == aThis);
        CHECK(*(void**)aThis == (void*)g_blk);
        g_bGiveNull = 1;
        pBack = SynAlc_1417d2320(aThis);
        CHECK(pBack == aThis);
        CHECK(*(void**)aThis == nullptr);
    }

    std::printf("SYNDICATE_THUNKS4_OK: 44 functions, %d checks\n", g_nChecks);
    return 0;
}

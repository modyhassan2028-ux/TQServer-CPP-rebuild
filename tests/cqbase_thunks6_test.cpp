// Generated with family L — one check per helper.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_l.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_a = 0, g_b = 0, g_f = 0; static uint32_t g_nLine = 0; static int g_nCalls = 0;

static void RepHook_141823038(void* a, void* b, uint32_t n, void* f) { g_a = (uintptr_t)a; g_b = (uintptr_t)b; g_nLine = n; g_f = (uintptr_t)f; ++g_nCalls; }

int main() {
    g_fnRep_141823038 = &RepHook_141823038;
    int sentinel = 7;
    {   // 0x1417f5f00
        g_nCalls = 0;
        void* pBack = SynLit_1417f5f00(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x8d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141721874);
    }
    {   // 0x1417f5f60
        g_nCalls = 0;
        void* pBack = SynLit_1417f5f60(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x93);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417218b6);
    }
    {   // 0x1417f5fc0
        g_nCalls = 0;
        void* pBack = SynLit_1417f5fc0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0xa2);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141721949);
    }
    {   // 0x1417f6000
        g_nCalls = 0;
        void* pBack = SynLit_1417f6000(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0xad);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141721a09);
    }
    {   // 0x1417f6040
        g_nCalls = 0;
        void* pBack = SynLit_1417f6040(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x70d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141721ccc);
    }
    {   // 0x1417f60e0
        g_nCalls = 0;
        void* pBack = SynLit_1417f60e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x8fd);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14172205e);
    }
    {   // 0x1417fa030
        g_nCalls = 0;
        void* pBack = SynLit_1417fa030(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0xa3b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141734db4);
    }
    {   // 0x1417faee0
        g_nCalls = 0;
        void* pBack = SynLit_1417faee0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0xa2b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141736088);
    }
    {   // 0x1417fb980
        g_nCalls = 0;
        void* pBack = SynLit_1417fb980(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x5b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14173ac36);
    }
    {   // 0x1417fd320
        g_nCalls = 0;
        void* pBack = SynLit_1417fd320(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141828078);
        CHECK(g_b == 0x141827bb0);
        CHECK(g_nLine == 0x1c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14173f46e);
    }
    {   // 0x1417fec40
        g_nCalls = 0;
        void* pBack = SynLit_1417fec40(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0xbe);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141748f35);
    }
    {   // 0x1417fec80
        g_nCalls = 0;
        void* pBack = SynLit_1417fec80(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0xeb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174911d);
    }
    {   // 0x1417fefd0
        g_nCalls = 0;
        void* pBack = SynLit_1417fefd0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x45);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174a6a4);
    }
    {   // 0x141800080
        g_nCalls = 0;
        void* pBack = SynLit_141800080(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141829668);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x52);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e03b);
    }
    {   // 0x1418000e0
        g_nCalls = 0;
        void* pBack = SynLit_1418000e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x32);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e0d3);
    }
    {   // 0x141800120
        g_nCalls = 0;
        void* pBack = SynLit_141800120(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x38);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e0f0);
    }
    {   // 0x141800160
        g_nCalls = 0;
        void* pBack = SynLit_141800160(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x273);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e50f);
    }
    {   // 0x1418001a0
        g_nCalls = 0;
        void* pBack = SynLit_1418001a0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x288);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e5bd);
    }
    {   // 0x1418001e0
        g_nCalls = 0;
        void* pBack = SynLit_1418001e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x296);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e692);
    }
    {   // 0x141800220
        g_nCalls = 0;
        void* pBack = SynLit_141800220(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x2a4);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e72a);
    }
    {   // 0x141800260
        g_nCalls = 0;
        void* pBack = SynLit_141800260(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x2e8);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174e7ce);
    }
    {   // 0x1418002c0
        g_nCalls = 0;
        void* pBack = SynLit_1418002c0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x7ab);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174eacf);
    }
    {   // 0x141800300
        g_nCalls = 0;
        void* pBack = SynLit_141800300(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x84d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14174eb96);
    }
    {   // 0x1418029e0
        g_nCalls = 0;
        void* pBack = SynLit_1418029e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x2cf);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14175f36f);
    }
    {   // 0x141802a60
        g_nCalls = 0;
        void* pBack = SynLit_141802a60(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x833);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14175fc82);
    }
    {   // 0x141802aa0
        g_nCalls = 0;
        void* pBack = SynLit_141802aa0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x128b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14175ffaf);
    }
    {   // 0x141803730
        g_nCalls = 0;
        void* pBack = SynLit_141803730(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x1a5);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141763485);
    }
    {   // 0x141803810
        g_nCalls = 0;
        void* pBack = SynLit_141803810(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x7fd);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141765225);
    }
    {   // 0x141803850
        g_nCalls = 0;
        void* pBack = SynLit_141803850(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x803);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176529f);
    }
    {   // 0x141803970
        g_nCalls = 0;
        void* pBack = SynLit_141803970(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182bb78);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0xf69);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176752e);
    }
    {   // 0x1418039b0
        g_nCalls = 0;
        void* pBack = SynLit_1418039b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x1260);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141768e69);
    }
    {   // 0x1418039f0
        g_nCalls = 0;
        void* pBack = SynLit_1418039f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x1262);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141768e95);
    }
    {   // 0x141804cb0
        g_nCalls = 0;
        void* pBack = SynLit_141804cb0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0xf5);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176aace);
    }
    {   // 0x141805110
        g_nCalls = 0;
        void* pBack = SynLit_141805110(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x1273);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176db2f);
    }
    {   // 0x141805150
        g_nCalls = 0;
        void* pBack = SynLit_141805150(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x1283);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176dba2);
    }
    {   // 0x141806390
        g_nCalls = 0;
        void* pBack = SynLit_141806390(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x132);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176fa5f);
    }
    {   // 0x1418063d0
        g_nCalls = 0;
        void* pBack = SynLit_1418063d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x19b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14176fb67);
    }
    {   // 0x141806a30
        g_nCalls = 0;
        void* pBack = SynLit_141806a30(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182cc38);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0xd6);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417705e2);
    }
    {   // 0x14180be50
        g_nCalls = 0;
        void* pBack = SynLit_14180be50(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182d450);
        CHECK(g_nLine == 0x23);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177808e);
    }
    {   // 0x14180c010
        g_nCalls = 0;
        void* pBack = SynLit_14180c010(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182d540);
        CHECK(g_nLine == 0x46);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141779384);
    }
    {   // 0x14180c050
        g_nCalls = 0;
        void* pBack = SynLit_14180c050(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182d540);
        CHECK(g_nLine == 0x157);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417795fd);
    }
    {   // 0x14180c090
        g_nCalls = 0;
        void* pBack = SynLit_14180c090(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182d540);
        CHECK(g_nLine == 0x16b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177972c);
    }
    {   // 0x14180c550
        g_nCalls = 0;
        void* pBack = SynLit_14180c550(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182db40);
        CHECK(g_nLine == 0x21);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177b3e8);
    }
    {   // 0x14180c770
        g_nCalls = 0;
        void* pBack = SynLit_14180c770(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182db40);
        CHECK(g_nLine == 0x67);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177c00c);
    }
    {   // 0x14180cf00
        g_nCalls = 0;
        void* pBack = SynLit_14180cf00(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182db40);
        CHECK(g_nLine == 0xb0);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177c857);
    }
    {   // 0x14180cff0
        g_nCalls = 0;
        void* pBack = SynLit_14180cff0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182de70);
        CHECK(g_nLine == 0x29);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177d10f);
    }
    {   // 0x14180d030
        g_nCalls = 0;
        void* pBack = SynLit_14180d030(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182de70);
        CHECK(g_nLine == 0xff);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177d2d8);
    }
    {   // 0x14180d1a0
        g_nCalls = 0;
        void* pBack = SynLit_14180d1a0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182de70);
        CHECK(g_nLine == 0x22b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177db70);
    }
    {   // 0x14180d8e0
        g_nCalls = 0;
        void* pBack = SynLit_14180d8e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182e750);
        CHECK(g_nLine == 0xf2);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14177f323);
    }
    {   // 0x14180ddb0
        g_nCalls = 0;
        void* pBack = SynLit_14180ddb0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182ed30);
        CHECK(g_nLine == 0x5c7);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x141782293);
    }
    {   // 0x14180e080
        g_nCalls = 0;
        void* pBack = SynLit_14180e080(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182fe18);
        CHECK(g_b == 0x14182ed30);
        CHECK(g_nLine == 0x3ca);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417846b9);
    }
    {   // 0x14180e0c0
        g_nCalls = 0;
        void* pBack = SynLit_14180e0c0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182fea0);
        CHECK(g_b == 0x14182ed30);
        CHECK(g_nLine == 0x402);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417848cb);
    }
    {   // 0x14180e5b0
        g_nCalls = 0;
        void* pBack = SynLit_14180e5b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418302d0);
        CHECK(g_nLine == 0x2a);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14178577f);
    }
    {   // 0x14180f110
        g_nCalls = 0;
        void* pBack = SynLit_14180f110(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0x74);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14178c836);
    }
    {   // 0x14180fe70
        g_nCalls = 0;
        void* pBack = SynLit_14180fe70(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0xe8);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14178dc30);
    }
    {   // 0x14180feb0
        g_nCalls = 0;
        void* pBack = SynLit_14180feb0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141831828);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0xeb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14178dc38);
    }
    {   // 0x141810150
        g_nCalls = 0;
        void* pBack = SynLit_141810150(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0x30);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x14178de78);
    }
    {   // 0x141810f10
        g_nCalls = 0;
        void* pBack = SynLit_141810f10(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0xb44);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417986f3);
    }
    {   // 0x141813530
        g_nCalls = 0;
        void* pBack = SynLit_141813530(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0x36);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417a1c5b);
    }
    {   // 0x141813570
        g_nCalls = 0;
        void* pBack = SynLit_141813570(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0x3c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417a1ca0);
    }
    {   // 0x1418135b0
        g_nCalls = 0;
        void* pBack = SynLit_1418135b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0x4b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417a1d31);
    }
    {   // 0x141815000
        g_nCalls = 0;
        void* pBack = SynLit_141815000(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x1418345b0);
        CHECK(g_nLine == 0xf2);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417a8bfe);
    }
    {   // 0x141815760
        g_nCalls = 0;
        void* pBack = SynLit_141815760(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xe7);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417a9f08);
    }
    {   // 0x141815b40
        g_nCalls = 0;
        void* pBack = SynLit_141815b40(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836528);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xb43);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417ac6c9);
    }
    {   // 0x141815fc0
        g_nCalls = 0;
        void* pBack = SynLit_141815fc0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836e28);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1203);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417aea62);
    }
    {   // 0x141818260
        g_nCalls = 0;
        void* pBack = SynLit_141818260(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141839348);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1ba);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417c083f);
    }
    {   // 0x1418193b0
        g_nCalls = 0;
        void* pBack = SynLit_1418193b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839b40);
        CHECK(g_nLine == 0x1d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417c458f);
    }
    {   // 0x1418194f0
        g_nCalls = 0;
        void* pBack = SynLit_1418194f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839cd0);
        CHECK(g_nLine == 0x1c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417c4c8f);
    }
    {   // 0x141819630
        g_nCalls = 0;
        void* pBack = SynLit_141819630(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x3b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417c5459);
    }
    {   // 0x141819d90
        g_nCalls = 0;
        void* pBack = SynLit_141819d90(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183a7a8);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x2bc);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417c8d52);
    }
    {   // 0x141819dd0
        g_nCalls = 0;
        void* pBack = SynLit_141819dd0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183a808);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x2d1);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417c8e8d);
    }
    {   // 0x14181b000
        g_nCalls = 0;
        void* pBack = SynLit_14181b000(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xf8);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417cde52);
    }
    {   // 0x14181c790
        g_nCalls = 0;
        void* pBack = SynLit_14181c790(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14183b7b0);
        CHECK(g_nLine == 0x20);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417d005f);
    }
    {   // 0x14181cc40
        g_nCalls = 0;
        void* pBack = SynLit_14181cc40(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x2a);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417d3d6f);
    }
    {   // 0x14181cce0
        g_nCalls = 0;
        void* pBack = SynLit_14181cce0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x44);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417d4140);
    }
    {   // 0x14181d050
        g_nCalls = 0;
        void* pBack = SynLit_14181d050(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14183beb0);
        CHECK(g_nLine == 0x1d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pBack == (void*)0x1417d4de2);
    }

    std::printf("SYNDICATE_THUNKS6_OK: 76 helpers, %d checks\n", g_nChecks);
    return 0;
}

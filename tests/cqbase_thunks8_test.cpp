// Generated with families L2 and N — one check per body.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_n.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_a = 0, g_b = 0, g_f = 0, g_s = 0, g_d = 0; static uint32_t g_nLine = 0; static int g_nCalls = 0;

static void Rep2_141823038(void* a, void* b, uint32_t n, void* f) { g_a = (uintptr_t)a; g_b = (uintptr_t)b; g_nLine = n; g_f = (uintptr_t)f; ++g_nCalls; }
static void* N2_141722ef0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141722fc0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141723090(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141723a50(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141724ed0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417250d0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_14173b240(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_14173b6c0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417447d0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141744cb0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141750670(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141750760(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417512f0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141751380(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141753470(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141753500(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141753620(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417536b0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141753d70(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141754000(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141776460(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_14177a5c0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417899e0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141789d70(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141790e10(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141791080(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_141792240(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417a70b0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417c63c0(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417c6580(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417c6610(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }
static void* N2_1417c6e80(void* s, void* d) { g_s = (uintptr_t)s; g_d = (uintptr_t)d; ++g_nCalls; return (void*)0x5A5A; }

int main() {
    g_fnRep2_141823038 = &Rep2_141823038;
    g_fnN2_141722ef0 = &N2_141722ef0;
    g_fnN2_141722fc0 = &N2_141722fc0;
    g_fnN2_141723090 = &N2_141723090;
    g_fnN2_141723a50 = &N2_141723a50;
    g_fnN2_141724ed0 = &N2_141724ed0;
    g_fnN2_1417250d0 = &N2_1417250d0;
    g_fnN2_14173b240 = &N2_14173b240;
    g_fnN2_14173b6c0 = &N2_14173b6c0;
    g_fnN2_1417447d0 = &N2_1417447d0;
    g_fnN2_141744cb0 = &N2_141744cb0;
    g_fnN2_141750670 = &N2_141750670;
    g_fnN2_141750760 = &N2_141750760;
    g_fnN2_1417512f0 = &N2_1417512f0;
    g_fnN2_141751380 = &N2_141751380;
    g_fnN2_141753470 = &N2_141753470;
    g_fnN2_141753500 = &N2_141753500;
    g_fnN2_141753620 = &N2_141753620;
    g_fnN2_1417536b0 = &N2_1417536b0;
    g_fnN2_141753d70 = &N2_141753d70;
    g_fnN2_141754000 = &N2_141754000;
    g_fnN2_141776460 = &N2_141776460;
    g_fnN2_14177a5c0 = &N2_14177a5c0;
    g_fnN2_1417899e0 = &N2_1417899e0;
    g_fnN2_141789d70 = &N2_141789d70;
    g_fnN2_141790e10 = &N2_141790e10;
    g_fnN2_141791080 = &N2_141791080;
    g_fnN2_141792240 = &N2_141792240;
    g_fnN2_1417a70b0 = &N2_1417a70b0;
    g_fnN2_1417c63c0 = &N2_1417c63c0;
    g_fnN2_1417c6580 = &N2_1417c6580;
    g_fnN2_1417c6610 = &N2_1417c6610;
    g_fnN2_1417c6e80 = &N2_1417c6e80;
    int sentinel = 3;
    unsigned char aSrc[32], aDst[32];

    {   // 0x1417f9730
        g_nCalls = 0;
        void* pB = SynLit2_1417f9730(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x6aa);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141732c1a);
    }
    {   // 0x1417f9770
        g_nCalls = 0;
        void* pB = SynLit2_1417f9770(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x6cb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141732e5d);
    }
    {   // 0x1417f97b0
        g_nCalls = 0;
        void* pB = SynLit2_1417f97b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x6cd);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141732e87);
    }
    {   // 0x1417fafe0
        g_nCalls = 0;
        void* pB = SynLit2_1417fafe0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0xe7);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417365c6);
    }
    {   // 0x1417fb020
        g_nCalls = 0;
        void* pB = SynLit2_1417fb020(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0xfd);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141736836);
    }
    {   // 0x1417fb060
        g_nCalls = 0;
        void* pB = SynLit2_1417fb060(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141824e30);
        CHECK(g_nLine == 0x121);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141736b96);
    }
    {   // 0x1417fc3c0
        g_nCalls = 0;
        void* pB = SynLit2_1417fc3c0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141827cc8);
        CHECK(g_b == 0x141827bb0);
        CHECK(g_nLine == 0x7a);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14173dcee);
    }
    {   // 0x1417fe0f0
        g_nCalls = 0;
        void* pB = SynLit2_1417fe0f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828540);
        CHECK(g_nLine == 0x53);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417427e5);
    }
    {   // 0x1417ff070
        g_nCalls = 0;
        void* pB = SynLit2_1417ff070(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x75);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174a9b0);
    }
    {   // 0x1417ff0b0
        g_nCalls = 0;
        void* pB = SynLit2_1417ff0b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x77);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174a9fa);
    }
    {   // 0x1417ff170
        g_nCalls = 0;
        void* pB = SynLit2_1417ff170(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x86);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174ab11);
    }
    {   // 0x1417ff1f0
        g_nCalls = 0;
        void* pB = SynLit2_1417ff1f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x96);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174ac75);
    }
    {   // 0x1417ff230
        g_nCalls = 0;
        void* pB = SynLit2_1417ff230(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x9c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174ace6);
    }
    {   // 0x1417ff310
        g_nCalls = 0;
        void* pB = SynLit2_1417ff310(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0xdc);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174af4b);
    }
    {   // 0x1417ff350
        g_nCalls = 0;
        void* pB = SynLit2_1417ff350(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0xe2);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174afad);
    }
    {   // 0x1417ff3b0
        g_nCalls = 0;
        void* pB = SynLit2_1417ff3b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x2b8);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174b862);
    }
    {   // 0x1417ff3f0
        g_nCalls = 0;
        void* pB = SynLit2_1417ff3f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x2d3);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174ba67);
    }
    {   // 0x1417ff430
        g_nCalls = 0;
        void* pB = SynLit2_1417ff430(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x310);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174bdd7);
    }
    {   // 0x1417ff470
        g_nCalls = 0;
        void* pB = SynLit2_1417ff470(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x316);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174bdf3);
    }
    {   // 0x1417ff4b0
        g_nCalls = 0;
        void* pB = SynLit2_1417ff4b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x367);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174c298);
    }
    {   // 0x1417ff4f0
        g_nCalls = 0;
        void* pB = SynLit2_1417ff4f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x374);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174c3c0);
    }
    {   // 0x1417fff80
        g_nCalls = 0;
        void* pB = SynLit2_1417fff80(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0x21);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174d9d8);
    }
    {   // 0x141800020
        g_nCalls = 0;
        void* pB = SynLit2_141800020(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141828950);
        CHECK(g_nLine == 0xb3);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14174dc73);
    }
    {   // 0x141803770
        g_nCalls = 0;
        void* pB = SynLit2_141803770(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x2b4);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141763804);
    }
    {   // 0x1418037b0
        g_nCalls = 0;
        void* pB = SynLit2_1418037b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x2c6);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417638b7);
    }
    {   // 0x141803890
        g_nCalls = 0;
        void* pB = SynLit2_141803890(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182b968);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0xb4a);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141765d46);
    }
    {   // 0x1418038d0
        g_nCalls = 0;
        void* pB = SynLit2_1418038d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182baa8);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0xb9d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141765fef);
    }
    {   // 0x141806310
        g_nCalls = 0;
        void* pB = SynLit2_141806310(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x109);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14176f8bd);
    }
    {   // 0x141806350
        g_nCalls = 0;
        void* pB = SynLit2_141806350(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418297c0);
        CHECK(g_nLine == 0x112);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14176f924);
    }
    {   // 0x14180c170
        g_nCalls = 0;
        void* pB = SynLit2_14180c170(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182d540);
        CHECK(g_nLine == 0x30);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141779aed);
    }
    {   // 0x14180c1b0
        g_nCalls = 0;
        void* pB = SynLit2_14180c1b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182d540);
        CHECK(g_nLine == 0x38);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141779b11);
    }
    {   // 0x14180c940
        g_nCalls = 0;
        void* pB = SynLit2_14180c940(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14182db40);
        CHECK(g_nLine == 0x3f);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177c45a);
    }
    {   // 0x14180d120
        g_nCalls = 0;
        void* pB = SynLit2_14180d120(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182de70);
        CHECK(g_nLine == 0x46);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177d59f);
    }
    {   // 0x14180d160
        g_nCalls = 0;
        void* pB = SynLit2_14180d160(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182de70);
        CHECK(g_nLine == 0x4d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177d5c9);
    }
    {   // 0x14180d800
        g_nCalls = 0;
        void* pB = SynLit2_14180d800(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182e620);
        CHECK(g_nLine == 0xcf);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177ed1b);
    }
    {   // 0x14180d840
        g_nCalls = 0;
        void* pB = SynLit2_14180d840(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182e7c8);
        CHECK(g_b == 0x14182e750);
        CHECK(g_nLine == 0xb8);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177f0af);
    }
    {   // 0x14180d880
        g_nCalls = 0;
        void* pB = SynLit2_14180d880(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182e750);
        CHECK(g_nLine == 0xdb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177f218);
    }
    {   // 0x14180d9b0
        g_nCalls = 0;
        void* pB = SynLit2_14180d9b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14182e750);
        CHECK(g_nLine == 0x46);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14177f551);
    }
    {   // 0x14180e100
        g_nCalls = 0;
        void* pB = SynLit2_14180e100(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182ff68);
        CHECK(g_b == 0x14182ed30);
        CHECK(g_nLine == 0x37d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141784cbe);
    }
    {   // 0x14180e5f0
        g_nCalls = 0;
        void* pB = SynLit2_14180e5f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418302d0);
        CHECK(g_nLine == 0x9c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141785cdd);
    }
    {   // 0x14180e730
        g_nCalls = 0;
        void* pB = SynLit2_14180e730(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x1418302d0);
        CHECK(g_nLine == 0x8f);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141788024);
    }
    {   // 0x14180f350
        g_nCalls = 0;
        void* pB = SynLit2_14180f350(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0x5c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14178d259);
    }
    {   // 0x14180f410
        g_nCalls = 0;
        void* pB = SynLit2_14180f410(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0x64);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14178d30f);
    }
    {   // 0x14180f450
        g_nCalls = 0;
        void* pB = SynLit2_14180f450(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0xc5);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14178d401);
    }
    {   // 0x14180f510
        g_nCalls = 0;
        void* pB = SynLit2_14180f510(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418315e8);
        CHECK(g_b == 0x141830e10);
        CHECK(g_nLine == 0xd0);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x14178d4a6);
    }
    {   // 0x141810ed0
        g_nCalls = 0;
        void* pB = SynLit2_141810ed0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418323d0);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0x29d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141797cca);
    }
    {   // 0x141810f70
        g_nCalls = 0;
        void* pB = SynLit2_141810f70(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418326c0);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0xc9e);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x141798e55);
    }
    {   // 0x141812b90
        g_nCalls = 0;
        void* pB = SynLit2_141812b90(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141833e00);
        CHECK(g_b == 0x1418319b0);
        CHECK(g_nLine == 0x366);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417a09fd);
    }
    {   // 0x1418156e0
        g_nCalls = 0;
        void* pB = SynLit2_1418156e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xca);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417a9ea4);
    }
    {   // 0x141815720
        g_nCalls = 0;
        void* pB = SynLit2_141815720(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xd0);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417a9ebe);
    }
    {   // 0x141815800
        g_nCalls = 0;
        void* pB = SynLit2_141815800(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141835cd8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x11f);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417aa14d);
    }
    {   // 0x1418158a0
        g_nCalls = 0;
        void* pB = SynLit2_1418158a0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141835e48);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x3c3);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417aa8dd);
    }
    {   // 0x1418158e0
        g_nCalls = 0;
        void* pB = SynLit2_1418158e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141835f78);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x3ff);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417aab3d);
    }
    {   // 0x141815940
        g_nCalls = 0;
        void* pB = SynLit2_141815940(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836068);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x4bd);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417aaf6b);
    }
    {   // 0x1418159c0
        g_nCalls = 0;
        void* pB = SynLit2_1418159c0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836158);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x674);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ab5d9);
    }
    {   // 0x141815a00
        g_nCalls = 0;
        void* pB = SynLit2_141815a00(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836218);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x6ed);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ab896);
    }
    {   // 0x141815a40
        g_nCalls = 0;
        void* pB = SynLit2_141815a40(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418362d8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x71e);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417aba9b);
    }
    {   // 0x141815a80
        g_nCalls = 0;
        void* pB = SynLit2_141815a80(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418363b8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x781);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417abbf5);
    }
    {   // 0x141815ac0
        g_nCalls = 0;
        void* pB = SynLit2_141815ac0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836438);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x7ee);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417abe39);
    }
    {   // 0x141815b00
        g_nCalls = 0;
        void* pB = SynLit2_141815b00(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836498);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x94c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ac40b);
    }
    {   // 0x141815b80
        g_nCalls = 0;
        void* pB = SynLit2_141815b80(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836588);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xcc3);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ac98f);
    }
    {   // 0x141815bc0
        g_nCalls = 0;
        void* pB = SynLit2_141815bc0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418365f8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xd77);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417acc54);
    }
    {   // 0x141815c20
        g_nCalls = 0;
        void* pB = SynLit2_141815c20(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418366b8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xda2);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417acd83);
    }
    {   // 0x141815ca0
        g_nCalls = 0;
        void* pB = SynLit2_141815ca0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836718);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xe16);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ad166);
    }
    {   // 0x141815d20
        g_nCalls = 0;
        void* pB = SynLit2_141815d20(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418367c8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xf16);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ad768);
    }
    {   // 0x141815da0
        g_nCalls = 0;
        void* pB = SynLit2_141815da0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836998);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xf7b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417adb84);
    }
    {   // 0x141815e20
        g_nCalls = 0;
        void* pB = SynLit2_141815e20(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836b18);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xfcb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ade85);
    }
    {   // 0x141815e80
        g_nCalls = 0;
        void* pB = SynLit2_141815e80(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836b98);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1061);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ae0fb);
    }
    {   // 0x141815ee0
        g_nCalls = 0;
        void* pB = SynLit2_141815ee0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836c38);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x10b7);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ae369);
    }
    {   // 0x141815f60
        g_nCalls = 0;
        void* pB = SynLit2_141815f60(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836ce8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x10fd);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ae5fc);
    }
    {   // 0x141816000
        g_nCalls = 0;
        void* pB = SynLit2_141816000(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836e98);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x129c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417af022);
    }
    {   // 0x141816040
        g_nCalls = 0;
        void* pB = SynLit2_141816040(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141836fc8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1312);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417af20c);
    }
    {   // 0x1418162a0
        g_nCalls = 0;
        void* pB = SynLit2_1418162a0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141837708);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1fe7);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b2dcb);
    }
    {   // 0x1418164e0
        g_nCalls = 0;
        void* pB = SynLit2_1418164e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141837e38);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x217);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b64b2);
    }
    {   // 0x141816520
        g_nCalls = 0;
        void* pB = SynLit2_141816520(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141837ee8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x271);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b6600);
    }
    {   // 0x141816560
        g_nCalls = 0;
        void* pB = SynLit2_141816560(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141837f48);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x2bb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b6748);
    }
    {   // 0x1418165e0
        g_nCalls = 0;
        void* pB = SynLit2_1418165e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141837fa8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x311);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b6a84);
    }
    {   // 0x141816640
        g_nCalls = 0;
        void* pB = SynLit2_141816640(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838058);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x35e);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b6dc8);
    }
    {   // 0x141816760
        g_nCalls = 0;
        void* pB = SynLit2_141816760(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838148);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xb1b);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b7816);
    }
    {   // 0x1418167c0
        g_nCalls = 0;
        void* pB = SynLit2_1418167c0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838228);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xd13);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b7abf);
    }
    {   // 0x141816820
        g_nCalls = 0;
        void* pB = SynLit2_141816820(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838318);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xe37);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b7bee);
    }
    {   // 0x1418168a0
        g_nCalls = 0;
        void* pB = SynLit2_1418168a0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838378);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xe83);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b7e47);
    }
    {   // 0x141816920
        g_nCalls = 0;
        void* pB = SynLit2_141816920(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418383d8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1016);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b8125);
    }
    {   // 0x141816960
        g_nCalls = 0;
        void* pB = SynLit2_141816960(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838458);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1196);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b8449);
    }
    {   // 0x1418169a0
        g_nCalls = 0;
        void* pB = SynLit2_1418169a0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418384d8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x12d1);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b85fc);
    }
    {   // 0x1418169e0
        g_nCalls = 0;
        void* pB = SynLit2_1418169e0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838538);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x155c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417b8913);
    }
    {   // 0x141816ae0
        g_nCalls = 0;
        void* pB = SynLit2_141816ae0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838978);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x741);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ba6dc);
    }
    {   // 0x141816ba0
        g_nCalls = 0;
        void* pB = SynLit2_141816ba0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x1418389e8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xa2d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417bad1e);
    }
    {   // 0x141816c00
        g_nCalls = 0;
        void* pB = SynLit2_141816c00(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838ac8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xc0e);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417bb0ad);
    }
    {   // 0x141816c80
        g_nCalls = 0;
        void* pB = SynLit2_141816c80(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838b58);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xc89);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417bb4d1);
    }
    {   // 0x141816cc0
        g_nCalls = 0;
        void* pB = SynLit2_141816cc0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141838bc8);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0xd35);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417bb5cd);
    }
    {   // 0x141817ad0
        g_nCalls = 0;
        void* pB = SynLit2_141817ad0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141839088);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x1f76);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417bed4c);
    }
    {   // 0x141818b00
        g_nCalls = 0;
        void* pB = SynLit2_141818b00(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141839518);
        CHECK(g_b == 0x141835bd0);
        CHECK(g_nLine == 0x2096);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417c243a);
    }
    {   // 0x1418193f0
        g_nCalls = 0;
        void* pB = SynLit2_1418193f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839b40);
        CHECK(g_nLine == 0x81);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417c48ad);
    }
    {   // 0x141819530
        g_nCalls = 0;
        void* pB = SynLit2_141819530(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839cd0);
        CHECK(g_nLine == 0x9f);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417c509d);
    }
    {   // 0x1418196b0
        g_nCalls = 0;
        void* pB = SynLit2_1418196b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183a098);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x374);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417c57ff);
    }
    {   // 0x1418197b0
        g_nCalls = 0;
        void* pB = SynLit2_1418197b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183a098);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x32f);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417c6b0c);
    }
    {   // 0x1418197f0
        g_nCalls = 0;
        void* pB = SynLit2_1418197f0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183a098);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x33e);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417c6bb2);
    }
    {   // 0x14181a2d0
        g_nCalls = 0;
        void* pB = SynLit2_14181a2d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x3fa);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cb338);
    }
    {   // 0x14181a310
        g_nCalls = 0;
        void* pB = SynLit2_14181a310(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x411);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cb428);
    }
    {   // 0x14181a890
        g_nCalls = 0;
        void* pB = SynLit2_14181a890(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xa6);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cccb6);
    }
    {   // 0x14181a8d0
        g_nCalls = 0;
        void* pB = SynLit2_14181a8d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xb3);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccd54);
    }
    {   // 0x14181a910
        g_nCalls = 0;
        void* pB = SynLit2_14181a910(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xb8);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccd1e);
    }
    {   // 0x14181a950
        g_nCalls = 0;
        void* pB = SynLit2_14181a950(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xbc);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccd75);
    }
    {   // 0x14181a990
        g_nCalls = 0;
        void* pB = SynLit2_14181a990(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xd5);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccea7);
    }
    {   // 0x14181a9d0
        g_nCalls = 0;
        void* pB = SynLit2_14181a9d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xe2);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccf45);
    }
    {   // 0x14181aa10
        g_nCalls = 0;
        void* pB = SynLit2_14181aa10(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xe7);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccf0f);
    }
    {   // 0x14181aa50
        g_nCalls = 0;
        void* pB = SynLit2_14181aa50(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0xeb);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ccf64);
    }
    {   // 0x14181b170
        g_nCalls = 0;
        void* pB = SynLit2_14181b170(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x1e1);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ce640);
    }
    {   // 0x14181b1b0
        g_nCalls = 0;
        void* pB = SynLit2_14181b1b0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183b0a8);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x207);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ce680);
    }
    {   // 0x14181bbb0
        g_nCalls = 0;
        void* pB = SynLit2_14181bbb0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x24c);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ceecd);
    }
    {   // 0x14181bbf0
        g_nCalls = 0;
        void* pB = SynLit2_14181bbf0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183b498);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x250);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417ceee5);
    }
    {   // 0x14181c2d0
        g_nCalls = 0;
        void* pB = SynLit2_14181c2d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x60);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf5a1);
    }
    {   // 0x14181c410
        g_nCalls = 0;
        void* pB = SynLit2_14181c410(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x70);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf86f);
    }
    {   // 0x14181c450
        g_nCalls = 0;
        void* pB = SynLit2_14181c450(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x71);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf88c);
    }
    {   // 0x14181c490
        g_nCalls = 0;
        void* pB = SynLit2_14181c490(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x7d);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf924);
    }
    {   // 0x14181c4d0
        g_nCalls = 0;
        void* pB = SynLit2_14181c4d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x7e);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf93e);
    }
    {   // 0x14181c510
        g_nCalls = 0;
        void* pB = SynLit2_14181c510(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x83);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf77c);
    }
    {   // 0x14181c550
        g_nCalls = 0;
        void* pB = SynLit2_14181c550(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x87);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cf955);
    }
    {   // 0x14181c750
        g_nCalls = 0;
        void* pB = SynLit2_14181c750(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183b718);
        CHECK(g_b == 0x141839fe0);
        CHECK(g_nLine == 0x307);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417cffa9);
    }
    {   // 0x14181c7d0
        g_nCalls = 0;
        void* pB = SynLit2_14181c7d0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14183b7b0);
        CHECK(g_nLine == 0xa5);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d040d);
    }
    {   // 0x14181cad0
        g_nCalls = 0;
        void* pB = SynLit2_14181cad0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183bb18);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x240);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d3504);
    }
    {   // 0x14181cd20
        g_nCalls = 0;
        void* pB = SynLit2_14181cd20(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x11a);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d4451);
    }
    {   // 0x14181cd60
        g_nCalls = 0;
        void* pB = SynLit2_14181cd60(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x72);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d45e8);
    }
    {   // 0x14181cda0
        g_nCalls = 0;
        void* pB = SynLit2_14181cda0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x78);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d4619);
    }
    {   // 0x14181cde0
        g_nCalls = 0;
        void* pB = SynLit2_14181cde0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x79);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d4630);
    }
    {   // 0x14181ce20
        g_nCalls = 0;
        void* pB = SynLit2_14181ce20(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x141824e18);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x80);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d4663);
    }
    {   // 0x14181ce60
        g_nCalls = 0;
        void* pB = SynLit2_14181ce60(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183bcb8);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0xec);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d484d);
    }
    {   // 0x14181cea0
        g_nCalls = 0;
        void* pB = SynLit2_14181cea0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14182db20);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x182);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d49a6);
    }
    {   // 0x14181cee0
        g_nCalls = 0;
        void* pB = SynLit2_14181cee0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183bd20);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x188);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d49ea);
    }
    {   // 0x14181cff0
        g_nCalls = 0;
        void* pB = SynLit2_14181cff0(nullptr, nullptr, nullptr, &sentinel);
        CHECK(g_nCalls == 1);
        CHECK(g_a == 0x14183bd88);
        CHECK(g_b == 0x14183b940);
        CHECK(g_nLine == 0x1c4);
        CHECK(g_f == (uintptr_t)&sentinel);
        CHECK(pB == (void*)0x1417d4d12);
    }
    {   // 0x1417255a0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417255a0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417255f0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417255f0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141725620
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141725620(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141725fb0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141725fb0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141726040
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141726040(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141726e90
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141726e90(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141726f20
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141726f20(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141726f70
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141726f70(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x14173b7b0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_14173b7b0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x14173bb80
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_14173bb80(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141745ec0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141745ec0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141746850
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141746850(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141754090
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141754090(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141754190
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141754190(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141755b40
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141755b40(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141756710
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141756710(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141756740
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141756740(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141756770
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141756770(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417567c0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417567c0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141756870
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141756870(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417568a0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417568a0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417568f0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417568f0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417578e0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417578e0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x14175bb00
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_14175bb00(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141776780
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141776780(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x14177aa30
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_14177aa30(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x14178a5f0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_14178a5f0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x14178a620
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_14178a620(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x141792300
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_141792300(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417937c0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417937c0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417937f0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417937f0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417a74f0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417a74f0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417c8450
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417c8450(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417c8480
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417c8480(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417c85f0
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417c85f0(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }
    {   // 0x1417c8740
        *(uint64_t*)aSrc = 0x1111;  *(uint64_t*)(aSrc + 8) = 0x2222;
        *(uint64_t*)aDst = 0;  *(uint64_t*)(aDst + 8) = 0;
        g_nCalls = 0;
        void* pB = SynCp2_1417c8740(aSrc, aDst);
        CHECK(g_nCalls == 1);
        CHECK(g_s == (uintptr_t)aSrc);
        CHECK(g_d == (uintptr_t)aDst);
        CHECK(*(uint64_t*)aDst == 0x1111);
        CHECK(*(uint64_t*)(aDst + 8) == 0x2222);
        CHECK(pB == aDst);
    }

    std::printf("SYNDICATE_THUNKS8_OK: 167 bodies, %d checks\n", g_nChecks);
    return 0;
}

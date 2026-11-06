// Generated with family P - `insert n copies`. Every accepted body is driven through
// the zero, positive and negative count paths, and each path asserts the seam call,
// its four exact arguments, and the returned pDst.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_p.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

typedef void* (*Fn)(void*, void*, void*);

struct Case { Fn fn; unsigned shift; unsigned scale; bool callOnNegative; uintptr_t addr; };

static const Case g_cases[] = {
    { &SynInsN_1417241f0, 3u, 8u, false, 0x1417241f0 },
    { &SynInsN_141724390, 3u, 8u, true, 0x141724390 },
    { &SynInsN_141724440, 3u, 8u, true, 0x141724440 },
    { &SynInsN_141724600, 2u, 4u, true, 0x141724600 },
    { &SynInsN_141725bd0, 3u, 8u, true, 0x141725bd0 },
    { &SynInsN_141725d90, 3u, 8u, true, 0x141725d90 },
    { &SynInsN_141725e30, 2u, 4u, true, 0x141725e30 },
    { &SynInsN_1417272d0, 3u, 8u, false, 0x1417272d0 },
    { &SynInsN_141727520, 3u, 8u, true, 0x141727520 },
    { &SynInsN_1417275d0, 2u, 4u, true, 0x1417275d0 },
    { &SynInsN_141728ec0, 2u, 4u, true, 0x141728ec0 },
    { &SynInsN_14173ffd0, 2u, 4u, false, 0x14173ffd0 },
    { &SynInsN_141740120, 2u, 4u, true, 0x141740120 },
    { &SynInsN_141740540, 2u, 4u, true, 0x141740540 },
    { &SynInsN_1417407f0, 2u, 4u, false, 0x1417407f0 },
    { &SynInsN_141740900, 2u, 4u, true, 0x141740900 },
    { &SynInsN_141740b50, 2u, 4u, true, 0x141740b50 },
    { &SynInsN_141745120, 2u, 4u, false, 0x141745120 },
    { &SynInsN_141745440, 3u, 8u, true, 0x141745440 },
    { &SynInsN_1417462d0, 3u, 8u, true, 0x1417462d0 },
    { &SynInsN_141746c30, 2u, 4u, false, 0x141746c30 },
    { &SynInsN_141746ef0, 3u, 8u, true, 0x141746ef0 },
    { &SynInsN_141747c40, 3u, 8u, true, 0x141747c40 },
    { &SynInsN_141751f60, 3u, 8u, false, 0x141751f60 },
    { &SynInsN_141752350, 3u, 8u, true, 0x141752350 },
    { &SynInsN_141754b80, 3u, 8u, true, 0x141754b80 },
    { &SynInsN_141756cb0, 3u, 8u, false, 0x141756cb0 },
    { &SynInsN_141756ec0, 3u, 8u, true, 0x141756ec0 },
    { &SynInsN_14175af90, 3u, 8u, true, 0x14175af90 },
    { &SynInsN_141791510, 3u, 8u, false, 0x141791510 },
    { &SynInsN_141791610, 3u, 8u, true, 0x141791610 },
    { &SynInsN_141791730, 3u, 8u, true, 0x141791730 },
    { &SynInsN_141792910, 3u, 8u, true, 0x141792910 },
    { &SynInsN_141793910, 3u, 8u, false, 0x141793910 },
    { &SynInsN_141793bb0, 3u, 8u, true, 0x141793bb0 },
    { &SynInsN_1417959f0, 3u, 8u, true, 0x1417959f0 },
    { &SynInsN_1417a3030, 3u, 8u, false, 0x1417a3030 },
    { &SynInsN_1417a30a0, 3u, 8u, false, 0x1417a30a0 },
    { &SynInsN_1417a3300, 3u, 8u, true, 0x1417a3300 },
    { &SynInsN_1417a3340, 3u, 8u, true, 0x1417a3340 },
    { &SynInsN_1417a3970, 3u, 8u, true, 0x1417a3970 },
    { &SynInsN_1417a39b0, 3u, 8u, true, 0x1417a39b0 },
    { &SynInsN_1417a3f30, 3u, 8u, false, 0x1417a3f30 },
    { &SynInsN_1417a3f70, 3u, 8u, false, 0x1417a3f70 },
    { &SynInsN_1417a4100, 3u, 8u, true, 0x1417a4100 },
    { &SynInsN_1417a4140, 3u, 8u, true, 0x1417a4140 },
    { &SynInsN_1417a4900, 3u, 8u, true, 0x1417a4900 },
    { &SynInsN_1417a4940, 3u, 8u, true, 0x1417a4940 },
    { &SynInsN_1417d1aa0, 3u, 8u, false, 0x1417d1aa0 },
    { &SynInsN_1417d1c30, 3u, 8u, true, 0x1417d1c30 },
    { &SynInsN_1417d2040, 3u, 8u, true, 0x1417d2040 },
    { &SynInsN_1417d2460, 3u, 8u, false, 0x1417d2460 },
    { &SynInsN_1417d2550, 3u, 8u, true, 0x1417d2550 },
    { &SynInsN_1417d2950, 3u, 8u, true, 0x1417d2950 },
};
static const int g_nCases = (int)(sizeof g_cases / sizeof g_cases[0]);

static uintptr_t g_a1, g_a2, g_a3, g_a4;
static int g_nCalls = 0;
static void* Hook(void* x1, void* x2, void* x3, void* x4) {
    g_a1 = (uintptr_t)x1; g_a2 = (uintptr_t)x2;
    g_a3 = (uintptr_t)x3; g_a4 = (uintptr_t)x4;
    ++g_nCalls;
    return (void*)0xBEEF;   // must be ignored: the body returns pDst (rbx), not rax
}

int main() {
    g_fnP_1418232a8 = &Hook;
    unsigned char abuf[4096];
    std::memset(abuf, 0x5A, sizeof abuf);
    CHECK(g_nCases > 0);
    for (int i = 0; i < g_nCases; ++i) {
        const Case& c = g_cases[i];
        // every accepted address appears exactly once
        for (int j = i + 1; j < g_nCases; ++j) CHECK(c.addr != g_cases[j].addr);

        void* const pBase = abuf + 2048;
        void* const pBegin = abuf + 1024;
        const uintptr_t kSpan = (uintptr_t)3 * c.scale;

        // ---- path 1: three elements (n == +3) -> the seam always runs
        g_nCalls = 0; g_a1 = g_a2 = g_a3 = g_a4 = 0;
        void* pR = c.fn(pBegin, (void*)((uint8_t*)pBegin + kSpan), pBase);
        CHECK(g_nCalls == 1);
        CHECK(g_a1 == (uintptr_t)pBase);
        CHECK(g_a2 == kSpan);
        CHECK(g_a3 == (uintptr_t)pBegin);
        CHECK(g_a4 == kSpan);
        CHECK(pR == (void*)((uint8_t*)pBase + kSpan));

        // ---- path 2: empty range (n == 0) -> the guard skips the seam
        g_nCalls = 0;
        pR = c.fn(pBegin, pBegin, pBase);
        CHECK(g_nCalls == 0);
        CHECK(pR == pBase);

        // ---- path 3: pEnd below pBegin (n == -3) -> je calls, jle does not
        g_nCalls = 0; g_a1 = g_a2 = g_a3 = g_a4 = 0;
        pR = c.fn(pBegin, (void*)((uint8_t*)pBegin - kSpan), pBase);
        const uintptr_t kNegSpan = (uintptr_t)0 - kSpan;
        if (c.callOnNegative) {
            CHECK(g_nCalls == 1);
            CHECK(g_a1 == (uintptr_t)pBase);
            CHECK(g_a2 == kNegSpan);
            CHECK(g_a3 == (uintptr_t)pBegin);
            CHECK(g_a4 == kNegSpan);
        } else {
            CHECK(g_nCalls == 0);
        }
        CHECK(pR == (void*)((uint8_t*)pBase - kSpan));

        // ---- path 4: one element, a different count, so shift/scale is really used
        g_nCalls = 0; g_a2 = 0;
        void* const pOne = (void*)((uint8_t*)pBegin + c.scale);
        pR = c.fn(pBegin, pOne, pBase);
        CHECK(c.scale == (1u << c.shift));
        CHECK(g_nCalls == 1);
        CHECK(g_a2 == c.scale);
        CHECK(pR == (void*)((uint8_t*)pBase + c.scale));
    }
    CHECK(g_nCases == 54);
    std::printf("SYNDICATE_THUNKS_P_OK: %d bodies, %d checks\n", g_nCases, g_nChecks);
    return 0;
}

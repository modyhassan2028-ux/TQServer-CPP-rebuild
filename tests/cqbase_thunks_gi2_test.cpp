// Generated with tools/bulk/gen_gi2.py - the advancing-probe battery.
#include "modules/syndicate/src/synthunks_gi2.h"
#include <cstdio>
#include <cstring>

using namespace tq;

static int g_checks = 0, g_fails = 0;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; \
    std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static void* g_last = nullptr;
static int g_n = 0;
static void HookReport(void* p) { ++g_n; g_last = p; }
static void* Q(void* p, size_t o) { return *(void**)((uint8_t*)p + o); }
static void  S(void* p, size_t o, void* v) { *(void**)((uint8_t*)p + o) = v; }

static void RunBody(void* (*fn)(void*), uint64_t cur, size_t offCur, size_t offLim,
                    void (**slot)(void*), void (*hook)(void*)) {
    *slot = hook;
    unsigned char aThis[0x40], aOuter[0x40], aInner[0x40];
    std::memset(aThis, 0, sizeof(aThis)); std::memset(aOuter, 0, sizeof(aOuter)); std::memset(aInner, 0, sizeof(aInner));
    S(aThis, 0x00, aOuter); S(aOuter, 0x00, aInner);
    S(aThis, offCur, (void*)(uintptr_t)cur);
    S(aInner, offLim, (void*)(uintptr_t)100);

    // (a) below the limit: no report, and the stored value still advances
    g_n = 0; g_last = nullptr;
    S(aThis, offCur, (void*)(uintptr_t)cur);
    void* r = fn(aThis);
    CHECK(r == aThis);                                   // the holder is the return value
    CHECK(g_n == 0);
    CHECK(*(uint64_t*)(aThis + offCur) == cur + 8);

    // (b) at the limit: one report with the holder, and the value advances anyway
    S(aThis, offCur, (void*)(uintptr_t)100);
    g_n = 0;
    r = fn(aThis);
    CHECK(r == aThis);
    CHECK(g_n == 1 && g_last == aThis);
    CHECK(*(uint64_t*)(aThis + offCur) == 108);
}

int main() {
    RunBody(SynProbeGX_141722a60, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_141722b80, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417246d0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417247b0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_14174fbb0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_14174fc50, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417525a0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_141752620, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417801f0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_141780270, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_141790660, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_141791cc0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417a2b80, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417a3630, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417b5a20, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417b5af0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417b5bc0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417b9bb0, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417b9c70, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417b9d30, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417d1790, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    RunBody(SynProbeGX_1417d1e30, 0x0, 0x8, 0x20, &g_fnGI2_1418233c0, HookReport);
    if (g_fails) { std::printf("GI2_FAILED: %d of %d\n", g_fails, g_checks); return 1; }
    std::printf("GI2_OK: 22 bodies, %d checks\n", g_checks);
    return 0;
}


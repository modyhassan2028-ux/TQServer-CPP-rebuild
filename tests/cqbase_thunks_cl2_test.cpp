// Generated with tools/bulk/gen_cl2.py - the subtree-destroy battery.
#include "modules/syndicate/src/synthunks_cl2.h"
#include <cstdio>
#include <cstring>
#include <set>

using namespace tq;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

#define Q(p, o) (*(void**)((uint8_t*)(p) + (o)))
#define B(p, o) (*(uint8_t*)((uint8_t*)(p) + (o)))

static unsigned char g_pool[16][0x40];
static std::set<void*> g_freed;
static void HookDel(void* p) { if (p) g_freed.insert(p); }

static void Build(int mark, void** pThis, void** pH, void** pA, void** pB, void** pC, void** pD, void** pE) {
    std::memset(g_pool, 0, sizeof(g_pool));
    *pThis = g_pool[0]; *pH = g_pool[1];
    *pA = g_pool[2]; *pB = g_pool[3]; *pC = g_pool[4]; *pD = g_pool[5]; *pE = g_pool[6];
    B(*pH, mark) = 1;
    Q(*pH, 0x00) = *pA; Q(*pH, 0x08) = *pA; Q(*pH, 0x10) = *pB;
    Q(*pA, 0x00) = *pH; Q(*pA, 0x08) = *pH; Q(*pA, 0x10) = *pB;   // A is the root, B hangs on its right
    Q(*pB, 0x00) = *pC; Q(*pB, 0x08) = *pA; Q(*pB, 0x10) = *pD;
    Q(*pC, 0x00) = *pH; Q(*pC, 0x08) = *pB; Q(*pC, 0x10) = *pH;
    Q(*pD, 0x00) = *pE; Q(*pD, 0x08) = *pB; Q(*pD, 0x10) = *pH;
    Q(*pE, 0x00) = *pH; Q(*pE, 0x08) = *pD; Q(*pE, 0x10) = *pH;
}

static void RunBody(void (*fn)(void*, void*), int mark) {
    void *pThis, *qH, *qA, *qB, *qC, *qD, *qE;
    Build(mark, &pThis, &qH, &qA, &qB, &qC, &qD, &qE);
    g_freed.clear();
    fn(pThis, qA);
    CHECK(g_freed.size() == 5);
    CHECK(g_freed.count(qA) == 1);
    CHECK(g_freed.count(qB) == 1);
    CHECK(g_freed.count(qC) == 1);
    CHECK(g_freed.count(qD) == 1);
    CHECK(g_freed.count(qE) == 1);
    CHECK(g_freed.count(qH) == 0);
    g_freed.clear();
    fn(pThis, qH);
    CHECK(g_freed.empty());
}
int main() {
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_1417270a0, 0x1b);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_14173bc60, 0x21);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141746600, 0x3d);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141746650, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_1417540c0, 0x2d);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141755490, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_1417555f0, 0x59);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141755640, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141755690, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_1417556e0, 0x69);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141755730, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141756920, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_1417767b0, 0x39);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_14177aa60, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_14178a650, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141793220, 0x29);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_141793630, 0x21);
    g_fnCL2_1417f2fdc = HookDel;
    RunBody(SynDestroySub_1417a75b0, 0x29);
    std::printf("CL2_OK: 18 bodies, %d checks\n", g_checks);
    return g_fails == 0 ? 0 : 1;
}

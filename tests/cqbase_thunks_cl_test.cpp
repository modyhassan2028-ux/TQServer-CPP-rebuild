// Generated with tools/bulk/gen_cl.py - the clear() battery for every body.
#include "synthunks_cl.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace tq;

static int g_checks = 0, g_fails = 0;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; \
    std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static int g_mark = 0;
static unsigned char g_pool[16][0x80];
static int g_used = 0;
static void* g_head = nullptr;
static std::vector<void*> g_freed, g_torn, g_tornArg;
static void* g_this = nullptr;

static void* Q(void* p, size_t o) { return *(void**)((uint8_t*)p + o); }
static void  S(void* p, size_t o, void* v) { *(void**)((uint8_t*)p + o) = v; }
static bool  Nil(void* p) { return ((uint8_t*)p)[g_mark] != 0; }
static void  SetNil(void* p, bool b) { ((uint8_t*)p)[g_mark] = b ? 1 : 0; }

static void* New(void* left, void* right, void* parent) {
    unsigned char* n = g_pool[g_used++];
    std::memset(n, 0xCD, sizeof(g_pool[0]));
    S(n, 0x00, left); S(n, 0x10, right); S(n, 0x08, parent);
    SetNil(n, false);
    return n;
}

static void HookTeardown(void* pThis, void* pArg) { g_torn.push_back(pThis); g_tornArg.push_back(pArg); }
static void HookFree(void* pNode) { g_freed.push_back(pNode); }

// tree:  n1 (root) -> left n2 -> left n3 ; n2->right nil ; n1->right n4
static void Build() {
    g_used = 0; g_freed.clear(); g_torn.clear(); g_tornArg.clear();
    g_head = g_pool[15];
    std::memset(g_head, 0xCD, 0x80);
    SetNil(g_head, true);
    g_used = 0;
}

static void RunBody(void* (*fn)(void*), int mark, const char* name,
                    void (**slotT)(void*, void*), void (*hookT)(void*, void*),
                    void (**slotD)(void*), void (*hookD)(void*)) {
    g_mark = mark;
    *slotT = hookT; *slotD = hookD;
    Build();
    void* n3 = New(g_head, g_head, nullptr);
    void* n2 = New(n3, g_head, nullptr);
    void* n4 = New(g_head, g_head, nullptr);
    void* n1 = New(n2, n4, g_head);
    S(n2, 0x08, n1); S(n3, 0x08, n2); S(n4, 0x08, n1);
    S(g_head, 0x08, n1); S(g_head, 0x00, n3); S(g_head, 0x10, n4);

    static unsigned char aThis[0x40];
    std::memset(aThis, 0, sizeof(aThis));
    S(aThis, 0x30, g_head);
    *(uint64_t*)(aThis + 0x38) = 3;

    void* r = fn(aThis);

    CHECK(r == g_head);                                    // rax is the head at the end
    CHECK(g_freed.size() == 3);
    if (g_freed.size() == 3) {
        CHECK(g_freed[0] == n1); CHECK(g_freed[1] == n2); CHECK(g_freed[2] == n3);
    }
    CHECK(g_torn.size() == 3);                             // the teardown helper owns the right subtree
    if (g_torn.size() == 3) {
        CHECK(g_tornArg[0] == n4);
        CHECK(g_tornArg[1] == g_head);
        CHECK(g_tornArg[2] == g_head);
        CHECK(g_torn[0] == aThis);
    }
    CHECK(Q(g_head, 0x08) == g_head);                      // head is self-linked again
    CHECK(Q(g_head, 0x00) == g_head);
    CHECK(Q(g_head, 0x10) == g_head);
    CHECK(*(uint64_t*)(aThis + 0x38) == 0);
    (void)name;
}

int main() {
    RunBody(SynTreeClear_1417276c0, 0x29, "0x1417276c0", &g_fnCL_t_1417262c0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141727740, 0x49, "0x141727740", &g_fnCL_t_141726310, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417277c0, 0x1d, "0x1417277c0", &g_fnCL_t_141726360, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141728b10, 0x1b, "0x141728b10", &g_fnCL_t_1417270a0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_14173c470, 0x21, "0x14173c470", &g_fnCL_t_14173bc60, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417471f0, 0x3d, "0x1417471f0", &g_fnCL_t_141746600, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141747270, 0x29, "0x141747270", &g_fnCL_t_141746650, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417567f0, 0x2d, "0x1417567f0", &g_fnCL_t_1417540c0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141757580, 0x29, "0x141757580", &g_fnCL_t_141755490, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141757640, 0x59, "0x141757640", &g_fnCL_t_1417555f0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417576c0, 0x29, "0x1417576c0", &g_fnCL_t_141755640, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141757740, 0x29, "0x141757740", &g_fnCL_t_141755690, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417577c0, 0x69, "0x1417577c0", &g_fnCL_t_1417556e0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141757840, 0x29, "0x141757840", &g_fnCL_t_141755730, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417599c0, 0x29, "0x1417599c0", &g_fnCL_t_141756920, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141777050, 0x39, "0x141777050", &g_fnCL_t_1417767b0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_14177ac60, 0x29, "0x14177ac60", &g_fnCL_t_14177aa60, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_14178af30, 0x29, "0x14178af30", &g_fnCL_t_14178a650, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141794280, 0x29, "0x141794280", &g_fnCL_t_141793220, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_141794c70, 0x21, "0x141794c70", &g_fnCL_t_141793630, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    RunBody(SynTreeClear_1417a7780, 0x29, "0x1417a7780", &g_fnCL_t_1417a75b0, HookTeardown, &g_fnCL_d_1417f2fdc, HookFree);
    if (g_fails) { std::printf("CL_FAILED: %d of %d checks\n", g_fails, g_checks); return 1; }
    std::printf("CL_OK: %d bodies, %d checks\n", 21, g_checks);
    return 0;
}


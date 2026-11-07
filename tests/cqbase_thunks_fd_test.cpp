// Generated with tools/bulk/gen_fd.py — the lookup battery for every body of the family.
#include "synthunks_fd_family.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace tq;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static int gMark;
static int gReports;
static void HookReport(void*) { ++gReports; }

#define Q(p, off) (*(void**)((unsigned char*)(p) + (off)))
#define B(p, off) (*(unsigned char*)((unsigned char*)(p) + (off)))

static unsigned char g_pool[16][0x80];
static unsigned char g_head[0x80];
static unsigned char g_db[0x40];

static void* Gp(int i) { return g_pool[i]; }

typedef void* (*FindFn)(void*, void*, const uint32_t*);

static void RunBody(FindFn fn, int mark, const char* name) {
    std::memset(g_pool, 0, sizeof(g_pool));
    std::memset(g_head, 0, sizeof(g_head));
    std::memset(g_db, 0, sizeof(g_db));
    gMark = mark;

    // a fixed seven-key tree: 40 at the root, 20/60 below it, 10/30/50/70 as leaves.
    // index 0..6 = keys 40,20,60,10,30,50,70
    static const uint32_t keys[7] = {40, 20, 60, 10, 30, 50, 70};
    // left/right/parent as tree indices, -1 = the nil sentinel (the head node)
    static const int kid[7][3] = {  // left, right, parent
        {1, 2, -1}, {3, 4, 0}, {5, 6, 0}, {-1, -1, 1}, {-1, -1, 1}, {-1, -1, 2}, {-1, -1, 2}
    };
    for (int i = 0; i < 7; ++i) {
        unsigned char* n = g_pool[i];
        Q(n, 0x00) = kid[i][0] < 0 ? (void*)g_head : Gp(kid[i][0]);
        Q(n, 0x10) = kid[i][1] < 0 ? (void*)g_head : Gp(kid[i][1]);
        Q(n, 0x08) = kid[i][2] < 0 ? (void*)g_head : Gp(kid[i][2]);
        *(uint32_t*)(n + 0x18) = keys[i];
        B(n, mark) = 0;                       // not the sentinel
    }
    B(g_head, mark) = 1;                      // the sentinel / nil node
    Q(g_head, 0x00) = Gp(3);                  // leftmost  = 10
    Q(g_head, 0x10) = Gp(6);                  // rightmost = 70
    Q(g_head, 0x08) = Gp(0);                  // root      = 40
    Q(g_db, 0x30) = (void*)g_head;            // this->head
    Q(g_db, 0x00) = (void*)0xC0FFEE;          // this->f00 (the container tag)

    struct { void* f00; void* f08; } out;
    struct Probe { uint32_t key; int want; } probes[] = {
        {40, 0}, {20, 1}, {60, 2}, {10, 3}, {30, 4}, {50, 5}, {70, 6},
        {25, -1}, {65, -1}, {5, -1}, {75, -1}, {100, -1}, {45, -1}
    };

    gReports = 0;
    g_fnFD_1418233c0 = HookReport;
    for (const Probe& p : probes) {
        std::memset(&out, 0, sizeof(out));
        void* ret = fn(g_db, &out, &p.key);
        CHECK(ret == (void*)&out);
        CHECK(out.f00 == (void*)0xC0FFEE);
        CHECK(out.f08 == (p.want < 0 ? (void*)g_head : Gp(p.want)));
    }
    CHECK(gReports == 0);                     // the container tag is never null here

    // the null-container path: the report fires and the iterator carries the null container
    Q(g_db, 0x00) = nullptr;
    gReports = 0;
    std::memset(&out, 0, sizeof(out));
    fn(g_db, &out, &keys[0]);
    CHECK(gReports == 1);
    CHECK(out.f00 == nullptr);
}

int main() {
    RunBody(&SynFind_14172b520, 0x29, "0x14172b520");
    RunBody(&SynFind_14172bc30, 0x49, "0x14172bc30");
    RunBody(&SynFind_14173d1e0, 0x61, "0x14173d1e0");
    RunBody(&SynFind_14173d330, 0x21, "0x14173d330");
    RunBody(&SynFind_141749980, 0x3d, "0x141749980");
    RunBody(&SynFind_141749fc0, 0x29, "0x141749fc0");
    RunBody(&SynFind_1417600e0, 0x1d, "0x1417600e0");
    RunBody(&SynFind_1417604a0, 0x29, "0x1417604a0");
    RunBody(&SynFind_141760950, 0x59, "0x141760950");
    RunBody(&SynFind_141760a20, 0x29, "0x141760a20");
    RunBody(&SynFind_141760af0, 0x61, "0x141760af0");
    RunBody(&SynFind_141760d70, 0x29, "0x141760d70");
    RunBody(&SynFind_141760e40, 0x61, "0x141760e40");
    RunBody(&SynFind_141760f10, 0x29, "0x141760f10");
    RunBody(&SynFind_1417618a0, 0x2d, "0x1417618a0");
    RunBody(&SynFind_14177bbc0, 0x29, "0x14177bbc0");
    RunBody(&SynFind_14178b6c0, 0x29, "0x14178b6c0");
    RunBody(&SynFind_141796480, 0x1d, "0x141796480");
    RunBody(&SynFind_141796550, 0x29, "0x141796550");
    RunBody(&SynFind_141796740, 0x61, "0x141796740");
    RunBody(&SynFind_141796810, 0x21, "0x141796810");
    RunBody(&SynFind_1417993b0, 0x61, "0x1417993b0");
    RunBody(&SynFind_141799770, 0x29, "0x141799770");
    RunBody(&SynFind_1417a8520, 0x29, "0x1417a8520");
    RunBody(&SynFind_1417cd6d0, 0x21, "0x1417cd6d0");
    if (g_fails) { std::printf("THUNKS_FD_FAIL: %d of %d\n", g_fails, g_checks); return 1; }
    std::printf("THUNKS_FD_OK: %d bodies, %d checks\n", 25, g_checks);
    return 0;
}


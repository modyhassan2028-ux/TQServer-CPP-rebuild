// syndicate_d41_test — D41a/T16: the nine REAL family
// erase-ranges wired into the mgr dtor: the empty-map
// fast paths (the family clears + the special nested
// relinks) run as REAL code with the erase-one sub-
// seams still null (never reached on empty maps), the
// full ctor→dtor balance, and the fast-path output
// iterator shape checked directly per family.
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgrErase.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgrLife.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueLife.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>

using namespace syndicate;

struct Ent { void* p; size_t sz; int used; };
static Ent* g_tab = nullptr;
static const size_t g_cap = 1u << 16;
static void TabInit() {
    if (!g_tab) {
        g_tab = (Ent*)malloc(g_cap * sizeof(Ent));
        memset(g_tab, 0, g_cap * sizeof(Ent));
    }
}
static size_t TabCount() {
    TabInit(); size_t n = 0;
    for (size_t i = 0; i < g_cap; ++i)
        if (g_tab[i].used == 1) ++n;
    return n;
}
static int g_nOpNew = 0, g_nOpDelete = 0, g_nInvalid = 0;
static void* CountNew(size_t sz) {
    void* p = malloc(sz ? sz : 1);
    TabInit();
    size_t i = (size_t)p / 8 % g_cap;
    while (g_tab[i].used == 1) i = (i + 1) % g_cap;
    g_tab[i] = { p, sz, 1 };
    ++g_nOpNew; return p;
}
static void CountDel(void* p) {
    if (!p) return;
    TabInit();
    size_t i = (size_t)p / 8 % g_cap;
    while (g_tab[i].used) {
        if (g_tab[i].used == 1 && g_tab[i].p == p) {
            g_tab[i].used = 2; ++g_nOpDelete; free(p);
            return;
        }
        i = (i + 1) % g_cap;
    }
    assert(!"double/foreign free");
}
void* operator new(size_t sz) { return CountNew(sz); }
void  operator delete(void* p) noexcept { CountDel(p); }
void  operator delete(void* p, size_t) noexcept { CountDel(p); }

static void Bind() {
    g_fnMeritOpNew = CountNew;
    g_fnMeritOpDelete = CountDel;
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnMgrVftable = (void*)0x1234;
    // NOTE: the 9 g_fnMgrErase* seams now DEFAULT to
    // the REAL D41a erase-ranges — do NOT override.
}

static char s_mgr[0x580];

// a direct fast-path probe on ONE family map: build the
// map, call its real erase-range with begin/end
// iterators, verify the out pair + no invalid
static void ProbeFamily(size_t mapIdx, int isnilOff,
                        size_t headSize,
                        FnMgrEraseRange rng) {
    char* m = s_mgr + mapIdx * 8;
    // free the ctor's proxy/head first (the probe
    // rebuilds the map slot)
    CountDel(*(void**)(m + 0x30));    // head
    CountDel(*(void**)m);             // proxy
    // fresh ctor for this map slot
    void* proxy = CountNew(8);
    *(void**)proxy = m; *(void**)m = proxy;
    char* head = (char*)CountNew(headSize);
    *(char*)(head + isnilOff) = 1;
    *(char**)(head + 8) = head;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
    *(char**)(m + 0x30) = head;
    *(uint64_t*)(m + 0x38) = 0;
    int64_t pair1[2] = { (int64_t)proxy, *(int64_t*)head };
    int64_t pair2[2] = { (int64_t)proxy, (int64_t)head };
    int64_t out[2] = { 0, 0 };
    rng(m, out, pair1, pair2);
    assert(g_nInvalid == 0 && "no CRT invalid");
    assert(*(void**)out == proxy && "out proxy");
    assert(out[1] == *(int64_t*)head
        && "out node = *head (post-clear first)");
    assert(*(uint64_t*)(m + 0x38) == 0 && "size 0");
    assert(*(char**)(head + 8) == head
        && *(char**)head == head
        && *(char**)(head + 0x10) == head
        && "the relinks");
    // (no cleanup — the MgrDtor frees the probe's
    //  head/proxy with the rest)
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    Bind();

    // ---------- D41-1: ctor→dtor with the REAL
    // erase-ranges (no seam overrides at all) ----------
    memset(s_mgr, 0, sizeof s_mgr);
    g_nOpNew = g_nOpDelete = 0;
    MgrCtor(s_mgr);
    assert(g_nOpNew == 37);
    MgrDtor(s_mgr);
    assert(TabCount() == 0 && "full balance");
    assert(g_nOpDelete == 37);
    assert(g_nInvalid == 0);
    printf("D41-1 ctor-dtor with real erase-ranges ok\n");

    // ---------- D41-2: the deleting dtor (heap) ------
    char* heap = (char*)CountNew(0x580);
    memset(heap, 0, 0x580);
    MgrCtor(heap);
    g_nOpNew = g_nOpDelete = 0;
    MgrDeletingDtor(heap, 1);
    assert(g_nOpDelete == 38 && "37 + the mgr");
    assert(TabCount() == 0);
    assert(g_nInvalid == 0);
    printf("D41-2 heap deleting dtor ok\n");

    // ---------- D41-3: direct fast-path probes ------
    memset(s_mgr, 0, sizeof s_mgr);
    MgrCtor(s_mgr);   // gives each map a real proxy/head
    // (probe one uniform + one special + the 0x59)
    g_nOpNew = g_nOpDelete = 0;
    ProbeFamily(7, 0x29, 0x30, MgrEraseRange38);
    ProbeFamily(0xa7, 0x29, 0x30, MgrEraseRange538);
    ProbeFamily(0x6e, 0x61, 0x68, MgrEraseRange470);
    ProbeFamily(0x56, 0x61, 0x68, MgrEraseRange2b0);
    ProbeFamily(0x21, 0x59, 0x60, MgrEraseRange108);
    ProbeFamily(0x96, 0x29, 0x30, MgrEraseRange4b0);
    ProbeFamily(0x9f, 0x69, 0x70, MgrEraseRange4f8);
    assert(g_nInvalid == 0);
    // the probes rebuilt those maps — dtor the mgr
    MgrDtor(s_mgr);
    assert(TabCount() == 0 && "the dtor freed the probed"
        " maps' real heads too");
    printf("D41-3 fast-path probes (7 families) ok\n");

    printf(
      "SYNDICATE-D41-OK: the mgr family ERASE-RANGES"
      " CLOSED (part A) - the nine real ranges wired as"
      " the seam defaults (the CRT proxy gates, the"
      " whole-range fast paths: 7 family clears + the 2"
      " SPECIAL nested-free relink paths, the inline"
      " successor advance), 5 clears + 5 subtree frees +"
      " the 2 recursive nested frees ported verbatim -"
      " full 37/37 ctor-dtor balance with NO seam mocks;"
      " the erase-ones (9) + the nested erase-ranges (2)"
      " remain D41b sub-seams (unreachable on empty"
      " maps)\n");
    return 0;
}

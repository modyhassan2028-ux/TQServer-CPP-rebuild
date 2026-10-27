// syndicate_d40_test — D40a/T15: the CLeagueMgr life
// cycle (141775b40 ctor / 141775800 dtor / 141775df0
// deleting dtor + the 19 map members, the 3 inline
// proxy groups, the head allocators, the family dtor
// wrappers, the post-init clears, and the config
// defaults — with the 9 family erase-ranges as
// counting seams and the 0x28 family on the REAL
// ported OwnEraseRange).
#include "../modules/syndicate/src/SyndicateLeagueMgrLife.h"
#include "../modules/syndicate/src/SyndicateLeagueLife.h"
#include "../modules/syndicate/src/SyndicateCrossMerit.h"
#include "../modules/syndicate/src/SyndicateEraseLayer.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <initializer_list>

using namespace syndicate;

// ---------- the counting registry ----------
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
static int g_nOpNew = 0, g_nOpDelete = 0;
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
static int g_nInvalid = 0;

// ---------- the erase-range seams (counting) ----------
struct EraseCall { void* map; void* out;
                  void* proxy; void* first;
                  void* lastNode; };
static EraseCall g_calls[64];
static int g_nEraseCalls = 0;
static void* CountErase(int slot, void* m, void* o,
                        void* pf, void* pl) {
    int64_t* f = (int64_t*)pf;
    int64_t* l = (int64_t*)pl;
    assert(g_nEraseCalls < 64);
    g_calls[g_nEraseCalls] = { m, o,
        (void*)f[0], (void*)f[1], (void*)l[1] };
    ++g_nEraseCalls; (void)slot;
    return o;   // the out iterator
}
static void Bind() {
    g_fnMeritOpNew = CountNew;
    g_fnMeritOpDelete = CountDel;
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnMgrVftable = (void*)0x1234;
    g_fnMgrErase38  = [](void* m, void* o, void* a, void* b) { return CountErase(1, m, o, a, b); };
    g_fnMgrErase538 = [](void* m, void* o, void* a, void* b) { return CountErase(2, m, o, a, b); };
    g_fnMgrErase4f8 = [](void* m, void* o, void* a, void* b) { return CountErase(3, m, o, a, b); };
    g_fnMgrErase4b0 = [](void* m, void* o, void* a, void* b) { return CountErase(4, m, o, a, b); };
    g_fnMgrErase470 = [](void* m, void* o, void* a, void* b) { return CountErase(5, m, o, a, b); };
    g_fnMgrErase318 = [](void* m, void* o, void* a, void* b) { return CountErase(6, m, o, a, b); };
    g_fnMgrErase2b0 = [](void* m, void* o, void* a, void* b) { return CountErase(7, m, o, a, b); };
    g_fnMgrErase228 = [](void* m, void* o, void* a, void* b) { return CountErase(8, m, o, a, b); };
    g_fnMgrErase108 = [](void* m, void* o, void* a, void* b) { return CountErase(9, m, o, a, b); };
    // the Life-unit vtable seam (the ctor of the users
    // map member needs no vtable, but the map ctor from
    // the Life unit touches the merit seams only)
}

// the mgr (0x540 bytes)
static char s_mgr[0x580];
static char* M() { return s_mgr; }

// a map member: verify the proxy + head family
static void CheckMap(char* mgr, size_t idx, int isnilOff,
                     size_t headSize) {
    char* m = mgr + idx * 8;
    void* proxy = *(void**)m;
    assert(proxy && "the proxy allocated");
    assert(*(void**)proxy == m && "the backref");
    char* head = *(char**)(m + 0x30);
    assert(head && "the head");
    assert(*(char*)(head + isnilOff) == 1 && "isnil 1");
    assert(*(char**)(head + 8) == head
        && *(char**)head == head
        && *(char**)(head + 0x10) == head
        && "the self-links");
    assert(*(uint64_t*)(m + 0x38) == 0 && "size 0");
    // the head size via the registry (find its entry)
    TabInit();
    size_t i = (size_t)head / 8 % g_cap;
    while (g_tab[i].used) {
        if (g_tab[i].used == 1 && g_tab[i].p == head) {
            assert(g_tab[i].sz == headSize);
            return;
        }
        i = (i + 1) % g_cap;
    }
    assert(!"head not allocated");
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    Bind();
    memset(s_mgr, 0, sizeof s_mgr);

    // ---------- D40-1: the ctor layout ----------
    MgrCtor(s_mgr);
    assert(*(void**)s_mgr == (void*)0x1234
        && "the vftable");
    assert(g_MgrDat141886d00 == 0);
    assert(*(void**)(s_mgr + 8) == nullptr
        && *(void**)(s_mgr + 0x10) == nullptr);
    // the 19 maps (byte offsets + families)
    CheckMap(M(), 7, 0x29, 0x30);      // +0x38
    CheckMap(M(), 0x21, 0x59, 0x60);  // +0x108
    CheckMap(M(), 0x29, 0x21, 0x28);  // +0x148
    CheckMap(M(), 0x34, 0x29, 0x30);  // +0x1a0
    CheckMap(M(), 0x3c, 0x21, 0x28);  // +0x1e0
    CheckMap(M(), 0x45, 0x29, 0x30);  // +0x228
    CheckMap(M(), 0x4e, 0x21, 0x28);  // +0x270
    CheckMap(M(), 0x56, 0x61, 0x68);  // +0x2b0
    CheckMap(M(), 0x63, 0x29, 0x30);  // +0x318
    CheckMap(M(), 0x6e, 0x61, 0x68);  // +0x370
    CheckMap(M(), 0x76, 0x61, 0x68);  // +0x3b0
    CheckMap(M(), 0x7e, 0x61, 0x68);  // +0x3f0
    CheckMap(M(), 0x86, 0x61, 0x68);  // +0x430
    CheckMap(M(), 0x8e, 0x61, 0x68);  // +0x470
    CheckMap(M(), 0x96, 0x29, 0x30);  // +0x4b0
    CheckMap(M(), 0x9f, 0x69, 0x70);  // +0x4f8
    CheckMap(M(), 0xa7, 0x29, 0x30);  // +0x538
    // the 3 inline groups (proxy + 3 zeros)
    for (size_t gi : {0xful, 0x15ul, 0x1bul}) {
        char* slot = s_mgr + gi * 8;
        assert(*(void**)slot && "the inline proxy");
        assert(*(void**)(*(char***)slot)
            == slot && "the backref");
        assert(*(void**)(slot + 0x18) == nullptr
            && *(void**)(slot + 0x20) == nullptr
            && *(void**)(slot + 0x28) == nullptr);
    }
    // the config defaults
    assert(*(uint32_t*)(s_mgr + 0x188) == 10000);
    assert(*(uint32_t*)(s_mgr + 0x18c) == 0x10e);
    assert(*(uint32_t*)(s_mgr + 0x190) == 0x16);
    assert(*(uint32_t*)(s_mgr + 0x194) == 2);
    assert(*(uint32_t*)(s_mgr + 0x198) == 5);
    assert(*(uint32_t*)(s_mgr + 0x26c) == 180000);
    assert(*(uint32_t*)(s_mgr + 0x268) == 1);
    assert(*(uint32_t*)(s_mgr + 0x30c) == 0xb4);
    assert(*(uint32_t*)(s_mgr + 0x18) == 0);
    assert(*(uint32_t*)(s_mgr + 0x24) == 0);
    assert(*(uint8_t*)(s_mgr + 0x20) == 0);
    assert(*(uint8_t*)(s_mgr + 0x2c) == 0);
    assert(*(uint32_t*)(s_mgr + 0x30) == 0);
    // 19 maps x (proxy+head) + 3 inline proxies
    assert(g_nOpNew == 37);
    assert(g_nInvalid == 0);
    printf("D40-1 ctor layout ok (19 maps + 3 groups)\n");

    // ---------- D40-2: the dtor (the reverse walk) ----
    g_nEraseCalls = 0;
    MgrDtor(s_mgr);
    // the 9 seam families + 3 real OwnEraseRange calls
    // (the 0x28 family, via the ported 14173cb90)
    assert(g_nEraseCalls == 13 && "the 13 seam calls");
    assert(TabCount() == 0 && "full balance");
    assert(g_nOpDelete == 37);
    assert(g_nInvalid == 0);
    printf("D40-2 dtor balance ok\n");

    // ---------- D40-3: the seam call shapes ----------
    // rebuild + recheck the FIRST seam call: map +0x38
    memset(s_mgr, 0, sizeof s_mgr);
    g_nOpNew = g_nOpDelete = 0; g_nEraseCalls = 0;
    MgrCtor(s_mgr);
    MgrDtor(s_mgr);
    assert(g_nEraseCalls == 13);
    EraseCall& c0 = g_calls[0];   // the +0x538 map dtor
    // (dtor order: [0xa7] first)
    assert(c0.map == (void*)(s_mgr + 0x538));
    assert(c0.proxy == *(void**)(s_mgr + 0x538)
        && "the proxy value of the map");
    assert(c0.first == c0.lastNode
        && "empty map: begin == head == end");
    assert(g_nInvalid == 0);
    printf("D40-3 erase seam shapes ok\n");

    // ---------- D40-4: the deleting dtor flags ------
    memset(s_mgr, 0, sizeof s_mgr);
    g_nOpNew = g_nOpDelete = 0;
    MgrCtor(s_mgr);
    g_nEraseCalls = 0;
    // flags 0 keeps the mgr
    MgrDeletingDtor(s_mgr, 0);
    // (the mgr is a static buffer — NOT in the registry;
    //  zero live means all 37 map allocations freed)
    assert(TabCount() == 0);
    assert(g_nOpDelete == 37);
    // flags 1 frees a HEAP mgr
    char* heap = (char*)CountNew(0x580);
    memset(heap, 0, 0x580);
    MgrCtor(heap);
    g_nOpNew = g_nOpDelete = 0; g_nEraseCalls = 0;
    MgrDeletingDtor(heap, 1);
    assert(g_nOpDelete == 38 && "the 37 + the mgr");
    assert(TabCount() == 0 && "the mgr freed too");
    assert(g_nInvalid == 0);
    printf("D40-4 deleting dtor flags ok\n");

    printf(
      "SYNDICATE-D40-OK: the CLeagueMgr LIFE CLOSED - the"
      " ctor (0x540 bytes: the vftable + 19 map-family"
      " members with their head sizes 0x30/0x60/0x28/"
      "0x30/0x28/0x30/0x28/0x68/0x30/0x68x5/0x30/0x70/"
      "0x30 + the 3 inline proxy groups + the defaults"
      " 10000/0x10e/22/2/5/180000/1/0xb4 + DAT141886d00"
      " = 0 + the two post-init clears), the dtor (the"
      " reverse walk with the 9 family erase seams +"
      " the real 0x28 OwnEraseRange), and the deleting"
      " dtor — 37 allocations in, 37 out\n");
    return 0;
}

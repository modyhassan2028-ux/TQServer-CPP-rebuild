// syndicate_d38_test — D38/T13: the CLeague LIFE cycle
// (141726c90/141746a00/141746a60, 141733570/14174cc70/
//  14174d6b0, 1417262c0/1417276c0/14172d3c0, 141730e80/
//  141748720/14174c530, 1417495d0, 14174d830, 14174cfc0,
//  14174d8d0, 141743b60, 14174a650, 14174d900):
//  the ctor layout (the +0x28 proxy + the three map
//  ctors with the family head sizes/isnil flags), the
//  dtor on EMPTY and on a STORM map (the erase-range
//  loops with both iterator homes = END), the scalar
//  deleting dtor, the INIT chain (the gates, the
//  InstanceGet with NO null check, "cq_league", the
//  resolve(2)/(1)/(8) vtable slots with the exact
//  args, the save), the fail cleanup (the release
//  walks, the members clear, the +0x28 truncate, the
//  provider dual-release, the self deleting dtor), and
//  the factory (the gates, the 0x118 alloc, the null
//  log, the init-fail cleanup).
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueLife.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueUsers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMembers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueOps.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <malloc.h>
#include <new>

using namespace syndicate;

// ---------- counting allocators ----------
// a malloc-based registry (NOT std::map — the global
// operator-new override would recurse into it)
struct Ent { void* p; size_t sz; int used; };
static Ent* g_tab = nullptr;
static const size_t g_cap = 1u << 16;
static void TabInit() {
    if (!g_tab) {
        g_tab = (Ent*)malloc(g_cap * sizeof(Ent));
        memset(g_tab, 0, g_cap * sizeof(Ent));
    }
}
// used: 0 = free, 1 = live, 2 = tombstone
static Ent* TabFind(void* p) {
    TabInit();
    size_t i = (size_t)p / 8 % g_cap;
    while (g_tab[i].used) {
        if (g_tab[i].used == 1 && g_tab[i].p == p)
            return &g_tab[i];
        i = (i + 1) % g_cap;
    }
    return nullptr;
}
static void TabPut(void* p, size_t sz) {
    TabInit();
    assert(!TabFind(p) && "double alloc");
    size_t i = (size_t)p / 8 % g_cap;
    while (g_tab[i].used == 1) i = (i + 1) % g_cap;
    g_tab[i] = { p, sz, 1 };
}
static size_t TabCount() {
    TabInit();
    size_t n = 0;
    for (size_t i = 0; i < g_cap; ++i)
        if (g_tab[i].used == 1) ++n;
    return n;
}
static void TabDump(const char* tag) {
    TabInit();
    printf("LIVE(%s):", tag);
    for (size_t i = 0; i < g_cap; ++i)
        if (g_tab[i].used == 1)
            printf(" %p(0x%zx)", g_tab[i].p, g_tab[i].sz);
    printf("\n");
}
static int g_nOpNew = 0, g_nOpDelete = 0;
static void* CountNew(size_t sz) {
    void* p = malloc(sz ? sz : 1);
    TabPut(p, sz); ++g_nOpNew; return p;
}
static void CountDel(void* p) {
    if (!p) return;
    Ent* e = TabFind(p);
    assert(e && "double/foreign free");
    e->used = 2; ++g_nOpDelete; free(p);
}
#define g_live_count TabCount()
#define g_live_has(p) (TabFind(p) != nullptr)
#define g_live_size(p) (TabFind(p) ? TabFind(p)->sz : 0)

void* operator new(size_t sz) { return CountNew(sz); }
void  operator delete(void* p) noexcept { CountDel(p); }
void  operator delete(void* p, size_t) noexcept { CountDel(p); }

static int g_nInvalid = 0;
static void BindBase() {
    g_fnMeritOpNew  = CountNew;
    g_fnMeritOpDelete = CountDel;
    g_fnMeritInvalid = []() { ++g_nInvalid; };
}

// ---------- the entity vtable ----------
// slot 0 = the REAL deleting dtor (the original's
// vftable slot 0 is the scalar deleting dtor)
typedef void (*FnV)(void*, int64_t);
static FnV s_vtEntity[32];
static void BindVtable() {
    memset(s_vtEntity, 0, sizeof s_vtEntity);
    s_vtEntity[0] = (FnV)&LeagueDeletingDtor;
    g_fnLeagueLifeVftable = (void*)s_vtEntity;
}

// ---------- the singleton/provider/record chain ----------
typedef int64_t (*FnI)(void*, int64_t);
static FnI s_vtSingle[8], s_vtProv[16], s_vtRec2[32],
          s_vtRec1[32], s_vtRec8[32];
static char s_single[16], s_prov[16];
static char s_rec2[16], s_rec1[16], s_rec8[16];
static int g_vResolve[8]; static int g_nResolve = 0;
struct SidRec { int idx; int64_t v; };
static SidRec g_vSetIds[8]; static int g_nSetIds = 0;
static int g_saveRet = 1;
static int g_nSave = 0; static int64_t g_nSaveArg = -1;
static int g_nInstGet = 0;
static const char* g_pProviderName = nullptr;
static int g_nProvRelease = 0; static int64_t g_nProvRelArg = -1;
static int g_nStrCopy = 0;
static char g_szName[0x20];

static int64_t SingleMakeProv(void* p, int64_t n) {
    (void)p; (void)n; return 0; }
static int64_t SingleMakeProv2(void* p,
        const char* name) {
    (void)p; g_pProviderName = name;
    return (int64_t)s_prov; }

static int64_t ProvResolve(void* p, int64_t idx) {
    (void)p; g_vResolve[g_nResolve++] = (int)idx;
    switch (idx) {
        case 2: return (int64_t)&s_rec2;
        case 1: return (int64_t)&s_rec1;
        case 8: return (int64_t)&s_rec8;
    }
    return 0;
}
static int64_t ProvSave(void* p, int64_t arg) {
    (void)p; ++g_nSave; g_nSaveArg = arg;
    return g_saveRet;
}
static void ProvRelease(void* p, int64_t arg) {
    (void)p; ++g_nProvRelease; g_nProvRelArg = arg; }

static void RecSetIdInt(void* p, int64_t v) {
    (void)p; g_vSetIds[g_nSetIds++] = {2, v}; }
static void RecSetId64(void* p, int64_t v) {
    (void)p; g_vSetIds[g_nSetIds++] = {1, v}; }
static void RecSetOne(void* p, int64_t v) {
    (void)p; g_vSetIds[g_nSetIds++] = {8, v}; }

static void BindChain() {
    memset(s_single, 0, sizeof s_single);
    memset(s_prov, 0, sizeof s_prov);
    memset(s_rec2, 0, sizeof s_rec2);
    memset(s_rec1, 0, sizeof s_rec1);
    memset(s_rec8, 0, sizeof s_rec8);
    memset(s_vtSingle, 0, sizeof s_vtSingle);
    memset(s_vtProv, 0, sizeof s_vtProv);
    memset(s_vtRec2, 0, sizeof s_vtRec2);
    memset(s_vtRec1, 0, sizeof s_vtRec1);
    memset(s_vtRec8, 0, sizeof s_vtRec8);
    *(void***)s_single = reinterpret_cast<void**>(s_vtSingle);
    *(void***)s_prov   = reinterpret_cast<void**>(s_vtProv);
    *(void***)s_rec2   = reinterpret_cast<void**>(s_vtRec2);
    *(void***)s_rec1   = reinterpret_cast<void**>(s_vtRec1);
    *(void***)s_rec8   = reinterpret_cast<void**>(s_vtRec8);
    s_vtSingle[4] = (FnI)&SingleMakeProv2;   // +0x20
    s_vtProv[2]   = (FnI)&ProvResolve;      // +0x10
    s_vtProv[10]  = (FnI)&ProvSave;          // +0x50
    s_vtProv[0]   = (FnI)&ProvRelease;       // slot 0
    s_vtRec2[23]  = (FnI)&RecSetIdInt;       // +0xb8
    s_vtRec1[16]  = (FnI)&RecSetId64;        // +0x80
    s_vtRec8[22]  = (FnI)&RecSetOne;          // +0xb0
    g_fnLeagueOpsInstance = []() -> void* {
        ++g_nInstGet; return s_single; };
    g_fnMgrStrCopy = [](char* d, const char* s,
                        int cap) {
        ++g_nStrCopy;
        memset(g_szName, 0, sizeof g_szName);
        memcpy(g_szName, s, strnlen(s, cap));
        memcpy(d, g_szName, cap); (void)cap; };
}

// ---------- the misc seams ----------
static int g_nLog = 0, g_nMemMove = 0;
static int g_nRelUsers = 0, g_nRelTokens = 0;
static int64_t g_vRelArgsU[4], g_vRelArgsT[4];
static void BindMisc() {
    g_fnLeagueLogFactory = []() -> void* {
        ++g_nLog; return (void*)1; };
    g_fnLeagueLogWrite = [](void* p, uint32_t id,
                            int lvl) { (void)p; (void)id;
                              (void)lvl; };
    g_fnLeagueMemMoveS = [](void* d, size_t ds,
            const void* s, size_t ss) -> int {
        ++g_nMemMove; memmove(d, s, ss < ds ? ss : ds);
        return 0; };
    g_fnLeagueReleaseUsers = [](int64_t e, int64_t a,
            int64_t b, int64_t c) {
        ++g_nRelUsers; g_vRelArgsU[0]=e; g_vRelArgsU[1]=a;
        g_vRelArgsU[2]=b; g_vRelArgsU[3]=c; };
    g_fnLeagueReleaseTokens = [](int64_t e, int64_t a,
            int64_t b, int64_t c) {
        ++g_nRelTokens; g_vRelArgsT[0]=e; g_vRelArgsT[1]=a;
        g_vRelArgsT[2]=b; g_vRelArgsT[3]=c; };
}

// ---------- the entity helpers ----------
static char s_ent[0x118];
static char* E() { return s_ent; }
static char* MapUsers()   { return E() + 0x58; }
static char* MapMembers() { return E() + 0x98; }
static char* MapTokens()  { return E() + 0xd8; }
static char* ProxyOf(char* m) {
    return *(char**)m; }
static char* HeadOf(char* m) {
    return *(char**)(m + 0x30); }
static size_t SizeOf(char* m) {
    return (size_t)*(uint64_t*)(m + 0x38); }
static void CheckMapFresh(char* m, int off) {
    char* px = ProxyOf(m);
    assert(px && g_live_has(px));
    assert(g_live_size(px) == 8);
    assert(*(char**)px == m && "the owner back-ref");
    char* h = HeadOf(m);
    assert(h && g_live_has(h));
    *(uint8_t*)(h + (off == 0x3d ? 0x3d : 0x29)) == 1;
    assert(*(uint8_t*)(h + (off == 0x3d ? 0x3d : 0x29))
           == 1 && "the head _Isnil");
    assert(*(char**)(h + 8) == h);
    assert(*(char**)h == h);
    assert(*(char**)(h + 0x10) == h);
    assert(SizeOf(m) == 0);
    (void)off;
}
static uint8_t InsertU(char* m, uint32_t k) {
    uint32_t kv[4] = { k, 0, 0, 0 };
    char out[3][8]; memset(out, 0, sizeof out);
    UsersInsertUnique(m, out[0], kv);
    return *(uint8_t*)(out[0] + 0x10);
}
static uint8_t InsertM(char* m, uint32_t k) {
    uint32_t kv[4] = { k, 0, 0, 0 };
    char out[3][8]; memset(out, 0, sizeof out);
    MembersInsertUnique(m, out[0], kv);
    return *(uint8_t*)(out[0] + 0x10);
}
static uint8_t InsertT(char* m, uint32_t k) {
    uint32_t kv[4] = { k, 0, 0, 0 };
    char out[3][8]; memset(out, 0, sizeof out);
    TokensInsertUnique(m, out[0], kv);
    return *(uint8_t*)(out[0] + 0x10);
}

static void ResetCounters() {
    g_nOpNew = g_nOpDelete = g_nInvalid = 0;
    g_nInstGet = g_nStrCopy = g_nSave = 0;
    g_nSaveArg = -1; g_nLog = g_nMemMove = 0;
    g_nRelUsers = g_nRelTokens = 0;
    g_nProvRelease = 0; g_nProvRelArg = -1;
    g_pProviderName = nullptr;
    g_nResolve = 0; g_nSetIds = 0;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    BindBase(); BindVtable(); BindChain(); BindMisc();

    // ---------- D38-1: the ctor layout ----------
    ResetCounters();
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent);
    assert(*(void**)E() == (void*)s_vtEntity);
    assert(*(uint64_t*)(E() + 0x08) == 0);
    assert(*(uint32_t*)(E() + 0x10) == 0);
    assert(*(uint64_t*)(E() + 0x14) == 0);
    assert(*(uint64_t*)(E() + 0x1c) == 0);
    char* px28 = *(char**)(E() + 0x28);
    assert(px28 && *(char**)px28 == E() + 0x28);
    assert(g_live_size(px28) == 8);
    assert(*(uint64_t*)(E() + 0x40) == 0);
    assert(*(uint64_t*)(E() + 0x48) == 0);
    assert(*(uint64_t*)(E() + 0x50) == 0);
    CheckMapFresh(MapUsers(), 0x29);
    assert(g_live_size(HeadOf(MapUsers())) == 0x30);
    CheckMapFresh(MapMembers(), 0x3d);
    assert(g_live_size(HeadOf(MapMembers())) == 0x40);
    CheckMapFresh(MapTokens(), 0x29);
    assert(g_live_size(HeadOf(MapTokens())) == 0x30);
    assert(g_nOpNew == 7 && "1 proxy + 3 map proxies + 3 heads");
    assert(g_nInvalid == 0);
    printf("D38-1 ctor layout ok\n");

    // ---------- D38-2: the dtor on the EMPTY maps ----------
    LeagueDtor(s_ent);
    assert(g_nOpDelete == 7 && "the 3 heads + 4 proxies");
    assert(TabCount() == 0 && "full balance");
    assert(g_nInvalid == 0);
    assert(*(char**)(MapUsers() + 0x30) == nullptr);
    assert(SizeOf(MapUsers()) == 0);
    assert(*(char**)(MapMembers() + 0x30) == nullptr);
    assert(*(char**)(MapTokens() + 0x30) == nullptr);
    printf("D38-2 empty dtor ok\n");

    // ---------- D38-3: the scalar deleting dtor ----------
    ResetCounters();
    memset(s_ent, 0, sizeof s_ent);
    char* ent2 = (char*)CountNew(0x118);
    memset(ent2, 0, 0x118);
    LeagueCtor(ent2);
    LeagueDeletingDtor(ent2, 0);
    assert(g_live_has(ent2) && "flags 0 keeps it");
    assert(TabCount() == 1);
    CountDel(ent2);   // the caller owns it now
    // a fresh entity for the flags=1 half (the original
    // crashes on a double dtor just the same)
    char* ent3 = (char*)CountNew(0x118);
    memset(ent3, 0, 0x118);
    LeagueCtor(ent3);
    LeagueDeletingDtor(ent3, 1);
    assert(!g_live_has(ent3) && "flags 1 frees it");
    assert(TabCount() == 0 && "full balance");
    printf("D38-3 deleting dtor flags gate ok\n");

    // ---------- D38-4: INIT success ----------
    ResetCounters();
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent);
    g_saveRet = 1;
    uint32_t r = LeagueInit((int64_t)s_ent, 77, 0xABC,
                            1, 555, "Alpha");
    assert(r == 1);
    assert(g_nInstGet == 1);
    assert(g_pProviderName
           && !strcmp(g_pProviderName, "cq_league"));
    assert(*(void**)(E() + 0x08) == (void*)s_prov);
    assert(*(uint32_t*)(E() + 0x10) == 555);
    assert(g_nStrCopy == 1);
    assert(!strncmp(g_szName, "Alpha", 5));
    assert(g_nResolve == 3 && g_vResolve[0] == 2
           && g_vResolve[1] == 1 && g_vResolve[2] == 8);
    assert(g_nSetIds == 3);
    assert(g_vSetIds[0].idx == 2 && g_vSetIds[0].v == 77);
    assert(g_vSetIds[1].idx == 1
           && g_vSetIds[1].v == 0xABC);
    assert(g_vSetIds[2].idx == 8
           && g_vSetIds[2].v == 1);
    assert(g_nSave == 1 && g_nSaveArg == 1);
    assert(g_nInvalid == 0);
    LeagueDtor(s_ent);
    TabDump("d38-4");
    assert(TabCount() == 0);
    printf("D38-4 init success chain ok\n");

    // ---------- D38-5: the INIT gates ----------
    struct { int32_t id; int64_t p3; uint8_t p4;
             int32_t p5; const char* nm; } G[] = {
        {77, 0, 1, 555, "x"}, {0, 0xABC, 1, 555, "x"},
        {77, 0xABC, 1, 0, "x"}, {77, 0xABC, 1, 555, 0},
    };
    for (auto& g : G) {
        ResetCounters();
        assert(LeagueInit((int64_t)s_ent, g.id, g.p3,
                          g.p4, g.p5, g.nm) == 0);
        assert(g_nInstGet == 0 && "no provider fetch");
        assert(g_nSave == 0);
    }
    printf("D38-5 init gates ok\n");

    // ---------- D38-6: the provider-null path ----------
    ResetCounters();
    g_fnLeagueOpsInstance = []() -> void* {
        ++g_nInstGet; return s_single; };
    s_vtSingle[4] = (FnI)&SingleMakeProv;  // returns 0
    memset(s_ent, 0, sizeof s_ent);
    assert(LeagueInit((int64_t)s_ent, 77, 0xABC, 1,
                      555, "x") == 0);
    assert(g_nInstGet == 1);
    assert(*(uint64_t*)(E() + 0x08) == 0);
    assert(g_nSave == 0);
    s_vtSingle[4] = (FnI)&SingleMakeProv2;
    printf("D38-6 provider-null ok\n");

    // ---------- D38-7: INIT without the flag ----------
    ResetCounters();
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent); g_saveRet = 1;
    LeagueInit((int64_t)s_ent, 77, 0xABC, 0, 555, "x");
    assert(g_nResolve == 2 && g_vResolve[0] == 2
           && g_vResolve[1] == 1);
    assert(g_nSetIds == 2);
    LeagueDtor(s_ent);
    assert(TabCount() == 0);
    printf("D38-7 no-flag resolve ok\n");

    // ---------- D38-8: the CREATE success ----------
    ResetCounters();
    g_saveRet = 1;
    void* p = LeagueCreate(77, 0xABC, 1, 555, "Alpha");
    assert(p != nullptr);
    assert(g_nOpNew == 8 && "0x118 + the ctor's 7");
    assert(g_live_has(p) && g_live_size(p) == 0x118);
    assert(*(uint32_t*)((char*)p + 0x10) == 555);
    assert(g_nLog == 0);
    LeagueDtor(p);
    CountDel(p);
    assert(TabCount() == 0);
    printf("D38-8 create success ok\n");

    // ---------- D38-9: the CREATE gates ----------
    ResetCounters();
    assert(LeagueCreate(0, 0xABC, 1, 555, "x") == nullptr);
    assert(LeagueCreate(77, 0, 1, 555, "x") == nullptr);
    assert(LeagueCreate(77, 0xABC, 1, 0, "x") == nullptr);
    assert(LeagueCreate(77, 0xABC, 1, 555, 0) == nullptr);
    assert(g_nOpNew == 0 && g_nInstGet == 0);
    printf("D38-9 create gates ok\n");

    // ---------- D38-10: the init-FAIL cleanup ----------
    ResetCounters();
    g_saveRet = 0;
    void* q = LeagueCreate(77, 0xABC, 1, 555, "Beta");
    assert(q == nullptr);
    assert(g_nRelUsers == 1 && g_nRelTokens == 1);
    assert(g_vRelArgsU[1] == 77 && g_vRelArgsU[2] == 0xABC
           && g_vRelArgsU[3] == 1);
    assert(g_vRelArgsT[1] == 77
           && g_vRelArgsT[3] == 1);
    assert(g_nMemMove == 0 && "empty container");
    assert(g_nProvRelease == 1 && g_nProvRelArg == 1);
    assert(TabCount() == 0
        && "the self deleting dtor freed everything");
    assert(g_nInvalid == 0);
    printf("D38-10 fail cleanup ok\n");

    // ---------- D38-11: the STORM dtor (the
    // erase-range loops on real trees) ----------
    ResetCounters();
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent);
    for (uint32_t i = 1; i <= 40; ++i)
        assert(InsertU(MapUsers(), i * 3));
    assert(InsertU(MapUsers(), 60) == 0 && "dup");
    for (uint32_t i = 1; i <= 25; ++i)
        assert(InsertM(MapMembers(), i * 5));
    for (uint32_t i = 1; i <= 15; ++i)
        assert(InsertT(MapTokens(), i * 7));
    assert(SizeOf(MapUsers()) == 40);
    assert(SizeOf(MapMembers()) == 25);
    assert(SizeOf(MapTokens()) == 15);
    size_t liveBefore = TabCount();
    assert(liveBefore == 7 + 40 + 25 + 15);
    LeagueDtor(s_ent);
    assert(TabCount() == 0 && "the storm fully freed");
    assert(g_nInvalid == 0);
    printf("D38-11 storm dtor ok\n");

    // ---------- D38-12: the +0x28 truncate ----------
    // the checked-iterator gates + the dead memmove_s
    ResetCounters();
    char cont[5][8]; memset(cont, 0, sizeof cont);
    int data[8] = {1,2,3,4,5,6,7,8};
    *(void***)cont = (void**)cont;       // the proxy
    *(int64_t*)(cont[3]) = (int64_t)(data + 2);
    *(int64_t*)(cont[4]) = (int64_t)(data + 6);
    StringVecEraseTail(cont);
    // VERBATIM: _Src == param_1[4] by construction, so
    // (param_1[4] - _Src) >> 2 == 0 — the memmove_s
    // branch is dead code in the original as
    // decompiled; the tail write collapses to _Dst
    assert(g_nMemMove == 0);
    assert(*(int64_t*)cont[4]
           == (int64_t)(data + 2));
    assert(g_nInvalid == 0);
    printf("D38-12 truncate tail ok\n");

    printf(
      "SYNDICATE-D38-OK: the CLeague LIFE cycle CLOSED -"
      " the ctor (the vftable + the +0x28 proxy + the"
      " three family map ctors with the head sizes"
      " 0x30/0x40/0x30 and the _Isnil flags), the dtor"
      " (the three map dtors with the interleaved proxy"
      " deletes - BOTH iterator homes = END), the"
      " scalar deleting dtor, INIT (the four gates, the"
      " unchecked InstanceGet, \"cq_league\", the"
      " resolve(2)/(1)/(8) chain with the exact vtable"
      " slots + args, the save), the fail cleanup (the"
      " release walks, the members clear, the +0x28"
      " truncate, the provider dual-release, the self"
      " deleting dtor), the factory, and the 40/25/15"
      " storm dtor with the full allocation balance\n");
    return 0;
}

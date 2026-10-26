// syndicate_d39_test — D39/T14: the RELEASE walks
// (141748ea0 users, 1417d4db0 the token release,
//  141749040 tokens): the begin-walk with the CRT
//  iterator gates + the value dual-release (the users
//  node value NOT nulled; the token value nulled TWICE
//  verbatim), the do-style successor prelude (the
//  right-child-first roles), the inlined map clears
//  (the users family / the D32 family), and the full
//  fail-cleanup integration with the REAL walks (the
//  D38 seams now default here) over a 3-map storm.
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueRelease.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueLife.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueUsers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMembers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>

using namespace syndicate;

// ---------- the malloc-based counting registry ----------
struct Ent { void* p; size_t sz; int used; };
static Ent* g_tab = nullptr;
static const size_t g_cap = 1u << 16;
static void TabInit() {
    if (!g_tab) {
        g_tab = (Ent*)malloc(g_cap * sizeof(Ent));
        memset(g_tab, 0, g_cap * sizeof(Ent));
    }
}
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
static size_t TabCount() {
    TabInit();
    size_t n = 0;
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
    Ent* e = TabFind(p);
    assert(e && "double/foreign free");
    e->used = 2; ++g_nOpDelete; free(p);
}
void* operator new(size_t sz) { return CountNew(sz); }
void  operator delete(void* p) noexcept { CountDel(p); }
void  operator delete(void* p, size_t) noexcept { CountDel(p); }
static int g_nInvalid = 0;

// ---------- the entity vtable (slot 0 = the real
// deleting dtor, as in the original) ----------
typedef void (*FnV)(void*, int64_t);
static FnV s_vtEntity[32];
// ---------- the mock user record (vt slot 0) ----------
static FnV s_vtUserRec[4];
static char s_userRecs[64][16];
static int g_nUserRel[64];
static void UserRecRelease(void* p, int64_t f) {
    int i = (int)((char*)p - (char*)s_userRecs) / 16;
    assert(i >= 0 && i < 64);
    assert(f == 1 && "the dual-release flag");
    ++g_nUserRel[i];
}
// ---------- the mock token ----------
static FnV s_vtToken[4], s_vtTokenSub[4];
static char s_tokens[64][32];   // +0 vt, +8 sub
static char s_tokenSubs[64][16];
static int g_nTokenDtor[64], g_nSubRel[64];
static int64_t g_subArgs[64][5];
static void TokenSubRelease(void* p, int64_t f,
        int64_t p3, int64_t p4, int64_t m2) {
    int i = (int)((char*)p - (char*)s_tokenSubs) / 16;
    assert(i >= 0 && i < 64);
    assert(f == 1);
    g_subArgs[i][0] = f; g_subArgs[i][1] = p3;
    g_subArgs[i][2] = p4; g_subArgs[i][3] = m2;
    ++g_nSubRel[i];
}
static void TokenDtor(void* p, int64_t f) {
    int i = (int)((char*)p - (char*)s_tokens) / 32;
    assert(i >= 0 && i < 64);
    assert(f == 1);
    ++g_nTokenDtor[i];
}
// ---------- the mock provider (vt[0] dual-release) ----------
static FnV s_vtProv[4];
static char s_prov[16];
static int g_nProvRel = 0;
static void ProvRelease(void* p, int64_t f) {
    (void)p; assert(f == 1); ++g_nProvRel;
}

static void Bind() {
    g_fnMeritOpNew = CountNew;
    g_fnMeritOpDelete = CountDel;
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnLeagueLogFactory = []() -> void* {
        return (void*)1; };
    g_fnLeagueLogWrite = [](void*, uint32_t, int) {};
    g_fnMgrStrCopy = [](char* d, const char* s, int c) {
        memcpy(d, s, strnlen(s, c)); };
    memset(s_vtEntity, 0, sizeof s_vtEntity);
    s_vtEntity[0] = (FnV)&LeagueDeletingDtor;
    g_fnLeagueLifeVftable = (void*)s_vtEntity;
    memset(s_vtUserRec, 0, sizeof s_vtUserRec);
    s_vtUserRec[0] = (FnV)&UserRecRelease;
    memset(s_vtToken, 0, sizeof s_vtToken);
    s_vtToken[0] = (FnV)&TokenDtor;
    memset(s_vtTokenSub, 0, sizeof s_vtTokenSub);
    s_vtTokenSub[0] = (FnV)&TokenSubRelease;
    memset(s_vtProv, 0, sizeof s_vtProv);
    s_vtProv[0] = (FnV)&ProvRelease;
    *(void***)s_prov =
        reinterpret_cast<void**>(s_vtProv);
}

// ---------- the entity ----------
static char s_ent[0x118];
static char* g_ent = s_ent;
static char* E() { return g_ent; }
static char* MapUsers()   { return E() + 0x58; }
static char* MapMembers() { return E() + 0x98; }
static char* MapTokens()  { return E() + 0xd8; }
static size_t SizeOf(char* m) {
    return (size_t)*(uint64_t*)(m + 0x38); }
static uint8_t InsertU(char* m, uint32_t k, void* val) {
    uint64_t kv[2] = { k, (uint64_t)(uintptr_t)val };
    char out[3][8]; memset(out, 0, sizeof out);
    UsersInsertUnique(m, out[0], (uint32_t*)kv);
    return *(uint8_t*)(out[0] + 0x10);
}
static uint8_t InsertM(char* m, uint32_t k) {
    uint64_t kv[2] = { k, 0 };
    char out[3][8]; memset(out, 0, sizeof out);
    MembersInsertUnique(m, out[0], (uint32_t*)kv);
    return *(uint8_t*)(out[0] + 0x10);
}
static uint8_t InsertT(char* m, uint32_t k, void* val) {
    uint64_t kv[2] = { k, (uint64_t)(uintptr_t)val };
    char out[3][8]; memset(out, 0, sizeof out);
    TokensInsertUnique(m, out[0], (uint32_t*)kv);
    return *(uint8_t*)(out[0] + 0x10);
}
static void CheckCleared(char* m) {
    char* h = *(char**)(m + 0x30);
    assert(h);
    assert(*(char**)(h + 8) == h && "the root relink");
    assert(*(char**)h == h && "the first relink");
    assert(*(char**)(h + 0x10) == h && "the last relink");
    assert(SizeOf(m) == 0);
}

static void ResetCounts() {
    memset(g_nUserRel, 0, sizeof g_nUserRel);
    memset(g_nTokenDtor, 0, sizeof g_nTokenDtor);
    memset(g_nSubRel, 0, sizeof g_nSubRel);
    memset(g_subArgs, 0, sizeof g_subArgs);
    g_nProvRel = g_nInvalid = 0;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    Bind();

    // ---------- D39-1: the walks on EMPTY maps ----------
    ResetCounts();
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent);
    LeagueReleaseUsers((int64_t)s_ent, 11, 22, 33);
    LeagueReleaseTokens((int64_t)s_ent, 11, 22, 33);
    assert(g_nInvalid == 0);
    CheckCleared(MapUsers());
    CheckCleared(MapTokens());
    printf("D39-1 empty walks ok\n");

    // ---------- D39-2: the users release walk ----------
    ResetCounts();
    // re-init the users map (the walk cleared it — but
    // the ctor state is reusable; re-ctor the entity)
    LeagueDtor(s_ent);
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent);
    for (int i = 0; i < 24; ++i) {
        *(void***)s_userRecs[i] =
            reinterpret_cast<void**>(s_vtUserRec);
        assert(InsertU(MapUsers(), (uint32_t)(i * 7 + 3),
                       &s_userRecs[i]));
    }
    assert(SizeOf(MapUsers()) == 24);
    size_t nodes = TabCount() - 7;   // minus the ctor's
    assert(nodes == 24);
    LeagueReleaseUsers((int64_t)s_ent, 0, 0, 0);
    for (int i = 0; i < 24; ++i)
        assert(g_nUserRel[i] == 1 && "each user once");
    assert(g_nInvalid == 0);
    CheckCleared(MapUsers());
    assert(TabCount() == 7 && "the nodes freed");
    printf("D39-2 users walk ok\n");

    // ---------- D39-3: the token release (the
    // array-based version with arg capture) ----------
    ResetCounts();
    int i0 = 0;
    memset(s_tokens[0], 0, 32);
    memset(s_tokenSubs[0], 0, 16);
    *(void***)s_tokens[0] =
        reinterpret_cast<void**>(s_vtToken);
    *(void**)(s_tokens[0] + 8) = s_tokenSubs[0];
    *(void***)s_tokenSubs[0] =
        reinterpret_cast<void**>(s_vtTokenSub);
    LeagueTokenRelease(s_tokens[0], 9, 0xAAA, 0xBBB);
    assert(g_nSubRel[0] == 1);
    assert(g_subArgs[0][0] == 1 && g_subArgs[0][1] == 0xAAA
           && g_subArgs[0][2] == 0xBBB
           && g_subArgs[0][3] == -2);
    assert(g_nTokenDtor[0] == 1);
    assert(*(void**)(s_tokens[0] + 8) == nullptr);
    printf("D39-3b token release args ok\n");

    // ---------- D39-4: the tokens release walk ----------
    ResetCounts();
    LeagueDtor(s_ent);
    memset(s_ent, 0, sizeof s_ent);
    LeagueCtor(s_ent);
    for (int i = 0; i < 18; ++i) {
        memset(s_tokens[i], 0, 32);
        memset(s_tokenSubs[i], 0, 16);
        *(void***)s_tokens[i] =
            reinterpret_cast<void**>(s_vtToken);
        *(void**)(s_tokens[i] + 8) = s_tokenSubs[i];
        *(void***)s_tokenSubs[i] =
            reinterpret_cast<void**>(s_vtTokenSub);
        assert(InsertT(MapTokens(), (uint32_t)(i * 5 + 1),
                       s_tokens[i]));
    }
    assert(SizeOf(MapTokens()) == 18);
    LeagueReleaseTokens((int64_t)s_ent, 7, 0x1234, 0x5678);
    for (int i = 0; i < 18; ++i) {
        assert(g_nSubRel[i] == 1 && "the sub released");
        assert(g_subArgs[i][1] == 0x1234
               && g_subArgs[i][2] == 0x5678
               && g_subArgs[i][3] == -2);
        assert(g_nTokenDtor[i] == 1);
        assert(*(void**)(s_tokens[i] + 8) == nullptr);
    }
    assert(g_nInvalid == 0);
    CheckCleared(MapTokens());
    assert(TabCount() == 7 && "the token nodes freed");
    printf("D39-4 tokens walk ok\n");

    // ---------- D39-5: the full fail-cleanup with the
    // REAL walks (no seam overrides) ----------
    ResetCounts();
    LeagueDtor(s_ent);
    // a HEAP entity (the cleanup's self deleting dtor
    // frees the entity itself)
    char* ent = (char*)CountNew(0x118);
    memset(ent, 0, 0x118);
    g_ent = ent;         // repoint the helpers
    LeagueCtor(ent);
    for (int i = 0; i < 10; ++i) {
        *(void***)s_userRecs[i] =
            reinterpret_cast<void**>(s_vtUserRec);
        assert(InsertU(MapUsers(), (uint32_t)(i * 3 + 1),
                       &s_userRecs[i]));
        memset(s_tokens[i], 0, 32);
        memset(s_tokenSubs[i], 0, 16);
        *(void***)s_tokens[i] =
            reinterpret_cast<void**>(s_vtToken);
        *(void**)(s_tokens[i] + 8) = s_tokenSubs[i];
        *(void***)s_tokenSubs[i] =
            reinterpret_cast<void**>(s_vtTokenSub);
        assert(InsertT(MapTokens(), (uint32_t)(i * 9 + 2),
                       s_tokens[i]));
        assert(InsertM(MapMembers(), (uint32_t)(i * 4 + 1)));
    }
    // the provider + INIT-ish fields for the cleanup
    *(void**)(ent + 0x08) = s_prov;
    LeagueFailCleanup((void*)ent, 0, 0, 0);
    for (int i = 0; i < 10; ++i) {
        assert(g_nUserRel[i] == 1);
        assert(g_nTokenDtor[i] == 1 && g_nSubRel[i] == 1);
    }
    assert(g_nProvRel == 1 && "the provider dual-release");
    assert(g_nInvalid == 0);
    // the entity is FREED by the self dtor — the map
    // slots are nulled (verified via the counters + the
    // balance; the tree clears are covered by D39-2/4)
    assert(TabCount() == 0
        && "the cleanup freed EVERYTHING (the self dtor)");
    g_ent = s_ent;   // restore the helpers
    printf("D39-5 fail-cleanup integration ok\n");

    printf(
      "SYNDICATE-D39-OK: the release walks CLOSED - the"
      " users begin-walk (the CRT gates + the value"
      " dual-release + the do-style successor prelude +"
      " the inlined users-family clear), the token"
      " release (the sub dual-release with the (1, p3,"
      " p4, -2) args + the self deleting dtor + the"
      " double null), the tokens walk (the triple CRT"
      " blocks + the value nulled TWICE + the D32-family"
      " clear), and the full fail-cleanup with the REAL"
      " walks over the 10/10/10 storm with a complete"
      " allocation balance\n");
    return 0;
}

// syndicate_d36d_test — D36 part 2c: the three big CLeague
// ops END-TO-END with mock providers/vtables:
//   AddMember    (14174b6c0): the double find, the
//     MakeDefRecord("cq_league_member") chain, SetId(user
//     on resolve(1)) + SetId(league on resolve(2)), the
//     vt+0x50 gate (WITH arg 1), the users insert (the
//     VERBATIM 16-byte pair {key|anchor-high, stale
//     node}), the 9-u32 member record copy, the members
//     insert — and the dup / gate-fail / make-fail paths
//   RemoveMember (14174b960): zero-id, not-found, the
//     record dual release (vt[8] with 0 then vt[0] with
//     1), the users erase-at + the members erase(key)
//   CreateToken  (14174bbe0): the inline descent, the
//     create chain (SetId(token on resolve(2)) +
//     SetId(league on resolve(1)) — REVERSED vs
//     AddMember), the CToken ctor {vft, def}, the vt+0x50
//     gate (NO arg), the key getter, the {key |
//     anchor-high, CToken*} pair insert, the
//     LeagueMemberData readback, and the exists /
//     gate-fail (the dual release) / make-fail paths
#include "../modules/syndicate/src/SyndicateLeagueOps.h"
#include "../modules/syndicate/src/SyndicateLeagueMember.h"
#include "../modules/syndicate/src/SyndicateLeagueUsers.h"
#include "../modules/syndicate/src/SyndicateLeagueMembers.h"
#include "../modules/syndicate/src/SyndicateLeagueTree.h"
#include "../modules/syndicate/src/SyndicateCrossMerit.h"
#include "../modules/syndicate/src/SyndicateLeagueCmp.h"
#include "../modules/syndicate/src/SyndicateLeagueEntity.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace syndicate;

// ---------- the counters ----------
static int g_nInvalid = 0, g_nLogs = 0;
static int g_nRel40 = 0, g_nRel0 = 0;
static int g_nDefReleased = 0;
static int g_nProviderHit = 0;
static int g_nTokVt0 = 0;
static uint64_t g_uDefRel_a = 0, g_uDefRel_c = 0;
static bool g_bMakeFail = false;

static void* g_pInstVt[8];
static void* g_pInst[2] = { g_pInstVt, nullptr };

static void Bind() {
    g_fnMeritOpDelete = [](void* p) { free(p); };
    g_fnMeritInvalid  = []() { ++g_nInvalid; };
    g_fnLeagueInvalid = []() { ++g_nInvalid; };
    g_fnLeagueLogFactory = []() { ++g_nLogs; return (void*)1; };
    g_fnLeagueLogWrite  = [](void*, uint32_t, int) { };
    g_fnLeagueOpsInstance = []() { return (void*)g_pInst; };
}

// ---------- the fakes ----------
struct FakeHolder {
    void* vft;
    void* inner;
    uint64_t uId;      // what SetId received
};
struct FakeDef {
    void* vft;
    char  name[32];
    void* holders[4];  // resolve(1)/(2)
    bool  bInsert;
    uint64_t uInsArg;
};

static void* g_pHolderVt[32];
static void* s_defVt[16];
static FakeDef* g_pDefMemberCur = nullptr;
static FakeDef* g_pDefTokenCur  = nullptr;

static void* FakeMakeDef(void* /*self*/, const char* name) {
    if (g_bMakeFail) return nullptr;
    // ONE persistent def per name (the test toggles its
    // insert gate between calls)
    FakeDef* d = nullptr;
    if (!strcmp(name, "cq_league_member")) {
        d = g_pDefMemberCur;
    } else if (!strcmp(name, "cq_league_token")) {
        d = g_pDefTokenCur;
    } else {
        return nullptr;
    }
    if (d == nullptr) {
        d = (FakeDef*)calloc(1, sizeof(FakeDef));
        d->vft = s_defVt;   // the def vtable
        snprintf(d->name, sizeof d->name, "%s", name);
        d->bInsert = true;
        for (int i = 1; i <= 2; ++i) {
            FakeHolder* h = (FakeHolder*)calloc(
                1, sizeof(FakeHolder));
            h->vft = g_pHolderVt;
            h->inner = (void*)(0x1000 + i);
            d->holders[i] = h;
        }
        if (!strcmp(name, "cq_league_member"))
            g_pDefMemberCur = d;
        else
            g_pDefTokenCur = d;
    }
    return d;
}
static void* FakeResolveDef(void* self, uint64_t idx) {
    return ((FakeDef*)self)->holders[idx];
}
static void FakeSetId(void* self, uint64_t id) {
    ((FakeHolder*)self)->uId = id;
}
static uint8_t FakeInsArg(void* self, uint64_t arg) {
    ((FakeDef*)self)->uInsArg = arg;
    return ((FakeDef*)self)->bInsert ? 1 : 0;
}
// the def vt[0] release — called BOTH as a plain 2-arg
// release (AddMember's gate-fail) and as the dual
// release's 5-arg holder call (..., -2 sentinel).
// Distinguish by the sentinel.
static int g_nDualHolder = 0;
static void FakeDefRelease5(void*, uint64_t a, uint64_t,
                           uint64_t c, int64_t d) {
    ++g_nDefReleased;
    if (d == (int64_t)0xfffffffffffffffe) {
        g_nDualHolder = 1;
        g_uDefRel_a = a; g_uDefRel_c = c;
    }
}

// the holder key getter (vt+0x40): returns the stored id
static uint64_t FakeHolderKey(void* self) {
    return ((FakeHolder*)self)->uId;
}

// ---------- the member record (users node value) ----------
static void FakeRecRel40(void*, uint64_t) { ++g_nRel40; }
static void FakeRecRel0(void*, uint64_t)  { ++g_nRel0; }
static void* g_pRecVt[16];
static void* g_pFakeRec[2];

// ---------- the provider (entity+8) ----------
static uint64_t FakeProvGet(void*) {
    ++g_nProviderHit;
    return 777;   // the league id
}
static void* g_pProvHoldVt[16];
static void* g_pProvHolder[2];
static void* FakeResolveProv(void*, uint64_t idx) {
    assert(idx == 0);
    return g_pProvHolder;
}
static void* g_pProvVt[4];
static void* g_pProv[2];

// the token vtable seam (g_pLeagueTokenVft): the stub at
// [0] for the dual release's rec-vt[0] call
static void FakeTokRel(void*, uint64_t) { ++g_nTokVt0; }
static void* g_pTokVt[4];

// ---------- the entity + maps ----------
static char s_ent[0x120];
static char* UAnchor(){ return *(char**)(s_ent+0x58); }
static char* UHead()  { return *(char**)(s_ent+0x88); }
static char* MAnchor(){ return *(char**)(s_ent+0x98); }
static char* MHead()  { return *(char**)(s_ent+0xc8); }
static char* THead()  { return *(char**)(s_ent+0x108); }

static void BuildEntity() {
    memset(s_ent, 0, sizeof s_ent);
    auto mkMap = [&](int off, bool bMembers) {
        char* anchor = (char*)calloc(1, 8);
        *(char**)anchor = s_ent + off;
        if (bMembers) MembersMapCtor(s_ent + off);
        else          LeagueMemberCtor(s_ent + off);
        // the ctor takes ownership of the anchor slot —
        // re-point it at OUR anchor (the owner back-ref)
        *(char**)(s_ent + off) = anchor;
    };
    mkMap(0x58, false);   // users
    mkMap(0x98, true);    // members
    mkMap(0xd8, false);   // tokens
    *(void**)(s_ent + 8) = g_pProv;
}

// the ordered walks
static std::vector<uint32_t> WalkU() {
    std::vector<uint32_t> v;
    char* n = *(char**)UHead();
    while (*(uint8_t*)(n + 0x29) == 0) {
        v.push_back(*(uint32_t*)(n + 0x18));
        char it[2][8];
        *(char**)it[0] = UAnchor();
        *(char**)(it[0] + 8) = n;
        UsersIterNext(it[0]);
        n = *(char**)(it[0] + 8);
    }
    return v;
}
static std::vector<uint32_t> WalkM() {
    std::vector<uint32_t> v;
    char* n = *(char**)MHead();
    while (*(uint8_t*)(n + 0x3d) == 0) {
        v.push_back(*(uint32_t*)(n + 0x18));
        char it[2][8];
        *(char**)it[0] = MAnchor();
        *(char**)(it[0] + 8) = n;
        MembersIterNext(it[0]);
        n = *(char**)(it[0] + 8);
    }
    return v;
}

int main() {
    Bind();

    // ---- the vtables ----
    g_pInstVt[4] = (void*)&FakeMakeDef;
    s_defVt[2]  = (void*)&FakeResolveDef;
    s_defVt[10] = (void*)&FakeInsArg;
    s_defVt[0]  = (void*)&FakeDefRelease5;
    g_pHolderVt[23] = (void*)&FakeSetId;
    g_pHolderVt[8]  = (void*)&FakeHolderKey;
    g_pRecVt[8] = (void*)&FakeRecRel40;
    g_pRecVt[0] = (void*)&FakeRecRel0;
    g_pFakeRec[0] = g_pRecVt;
    g_pProvHoldVt[9] = (void*)&FakeProvGet;   // +0x48
    g_pProvHolder[0] = g_pProvHoldVt;
    g_pProvVt[2] = (void*)&FakeResolveProv;
    g_pProv[0] = g_pProvVt;
    g_pTokVt[0] = (void*)&FakeTokRel;
    g_pLeagueTokenVft = g_pTokVt;

    BuildEntity();

    // ================= AddMember =================
    uint8_t md[0x20];
    memset(md, 0xAB, sizeof md);
    *(uint32_t*)md = 0x11111111;

    // (1) the zero id → a log + 0
    assert(LeagueAddMember((int64_t)s_ent, 0, md) == 0);
    assert(g_nLogs == 1);

    // (2) a clean add: both maps gain the user
    assert(LeagueAddMember((int64_t)s_ent, 500, md) == 1);
    {
        auto vu = WalkU(); auto vm = WalkM();
        assert(vu.size() == 1 && vu[0] == 500);
        assert(vm.size() == 1 && vm[0] == 500);
    }
    // the def chain: SetId(user) on resolve(1), SetId(777)
    // on resolve(2), the gate saw arg 1
    assert(g_pDefMemberCur->holders[1]
           && ((FakeHolder*)g_pDefMemberCur
               ->holders[1])->uId == 500);
    assert(((FakeHolder*)g_pDefMemberCur
            ->holders[2])->uId == 777);
    assert(g_pDefMemberCur->uInsArg == 1);
    // the VERBATIM stale value at the users node +0x20
    // (the pair {key|anchor-high, the find's head})
    {
        char* n = *(char**)UHead();
        assert(*(uint32_t*)(n + 0x18) == 500);
        assert(*(char**)(n + 0x20) == UHead());
    }
    // the member record: {500, md[0..2], md+0x18 u32,
    // the u16|u8 tail}
    {
        char* n = *(char**)MHead();
        uint32_t* r = (uint32_t*)(n + 0x18);
        assert(r[0] == 500);
        assert(r[1] == 0x11111111);
        assert(r[7] == *(uint32_t*)(md + 0x18));
        assert(r[8] == ((*(uint32_t*)(md + 0x1c))
                        & 0x00ffffff));
    }

    // (3) the dup → the provider notify + the log + 0
    // (note: LeagueGetId inside (2) already hit the
    // provider once — assert the DELTA)
    {
        int nBefore = g_nProviderHit;
        assert(LeagueAddMember(
                   (int64_t)s_ent, 500, md) == 0);
        assert(g_nProviderHit == nBefore + 1);
    }
    // (4) the users-map presence alone also dups
    {
        int64_t pair[2];
        pair[0] = 900
            | ((uint64_t)(uintptr_t)UAnchor()
               & 0xffffffff00000000ULL);
        pair[1] = (int64_t)g_pFakeRec;
        int64_t out[3];
        UsersInsertUnique((void*)(s_ent + 0x58), out,
                          (uint32_t*)pair);
        assert(LeagueAddMember(
                   (int64_t)s_ent, 900, md) == 0);
    }
    // (5) the insert-gate fail → the def released + 0
    {
        g_pDefMemberCur->bInsert = false;
        assert(LeagueAddMember(
                   (int64_t)s_ent, 600, md) == 0);
        assert(g_nDefReleased == 1);
        g_pDefMemberCur->bInsert = true;
    }
    // (6) MakeDef fails → a log + 0
    {
        g_bMakeFail = true;
        assert(LeagueAddMember(
                   (int64_t)s_ent, 700, md) == 0);
        g_bMakeFail = false;
    }

    // ================= RemoveMember =================
    // (7) the zero id
    assert(LeagueRemoveMember((int64_t)s_ent, 0) == 0);
    // (8) not found
    assert(LeagueRemoveMember(
               (int64_t)s_ent, 4242) == 0);
    // (9) the user 900 (a REAL record value): the
    //     release pair fires on the fake record
    assert(LeagueRemoveMember(
               (int64_t)s_ent, 900) == 1);
    assert(g_nRel40 == 1 && g_nRel0 == 1);
    {
        auto vu = WalkU();
        assert(vu.size() == 1 && vu[0] == 500);
        auto vm = WalkM();
        assert(vm.size() == 1 && vm[0] == 500);
    }
    // (10) remove 500: the ORIGINAL leaves the stale +0x20
    //      slot for the record system — patch it to the
    //      fake record, then verify the full removal
    {
        char* n = *(char**)UHead();
        *(void**)(n + 0x20) = (void*)g_pFakeRec;
        assert(LeagueRemoveMember(
                   (int64_t)s_ent, 500) == 1);
        assert(g_nRel40 == 2 && g_nRel0 == 2);
        assert(WalkU().empty());
        assert(WalkM().empty());
        assert(*(uint64_t*)(s_ent + 0x98 + 0x38) == 0);
    }

    // ================= CreateToken =================
    // (11) a clean create
    void* pTok = LeagueCreateToken(
        (int64_t)s_ent, 7000, 0, 0xBEEF);
    assert(pTok != nullptr);
    {
        // the CToken = {vftable, def}
        assert(*(void**)pTok == g_pLeagueTokenVft);
        assert(*(void**)((char*)pTok + 8)
               == (void*)g_pDefTokenCur);
        (void)0;
        // SetId(token) on resolve(2), SetId(league) on
        // resolve(1) — REVERSED vs AddMember
        assert(((FakeHolder*)g_pDefTokenCur
                ->holders[2])->uId == 7000);
        assert(((FakeHolder*)g_pDefTokenCur
                ->holders[1])->uId == 777);
        // the tokens map holds {7000 | anchor-high, pTok}
        char* n = *(char**)THead();
        assert(*(uint32_t*)(n + 0x18) == 7000);
        assert(*(char**)(n + 0x20) == pTok);
        // the readback via the part-1 lookup
        assert(LeagueMemberData((int64_t)s_ent, 7000)
               == pTok);
    }
    // (12) exists → the notify + the log + 0
    assert(LeagueCreateToken(
               (int64_t)s_ent, 7000, 0, 0xBEEF)
           == nullptr);
    // (13) the gate fail → the dual release (the
    //     D35 1417d4db0: the def-holder call with the
    //     -2 sentinel + the token-vt[0] release) + 0
    {
        g_pDefTokenCur->bInsert = false;
        g_nDefReleased = 0;
        assert(LeagueCreateToken(
                   (int64_t)s_ent, 8000, 0, 0xBEEF)
               == nullptr);
        assert(g_nDualHolder == 1);
        assert(g_uDefRel_a == 1);          // the 1|high
        assert(g_uDefRel_c == 0xBEEF);     // param_4
        assert(g_nTokVt0 == 1);            // the vt[0] rel
        g_pDefTokenCur->bInsert = true;
    }
    // (14) MakeDef fails → 0
    {
        g_bMakeFail = true;
        assert(LeagueCreateToken(
                   (int64_t)s_ent, 9000, 0, 0)
               == nullptr);
        g_bMakeFail = false;
    }

    // ================= the storm =================
    // 40 adds, 20 removes, 25 tokens — the maps stay
    // ordered + consistent
    BuildEntity();
    for (uint32_t k = 1; k <= 40; ++k)
        assert(LeagueAddMember(
                   (int64_t)s_ent, k * 3, md) == 1);
    {
        auto vu = WalkU(); auto vm = WalkM();
        assert(vu.size() == 40 && vm.size() == 40);
        for (size_t i = 0; i < 40; ++i)
            assert(vm[i] == vu[i]);
        assert(vm[0] == 3 && vm[39] == 120);
    }
    for (uint32_t k = 1; k <= 40; k += 2) {
        uint32_t key = k * 3;
        int64_t it[2];
        LeagueUserFind((int64_t)(s_ent + 0x58),
                       it, &key);
        assert(it[1] != *(int64_t*)(s_ent + 0x88));
        *(void**)(it[1] + 0x20) = (void*)g_pFakeRec;
        assert(LeagueRemoveMember(
                   (int64_t)s_ent, key) == 1);
    }
    {
        auto vm = WalkM();
        assert(vm.size() == 20);
        assert(vm[0] == 6 && vm[19] == 120);
    }
    for (uint32_t k = 1; k <= 25; ++k)
        assert(LeagueCreateToken(
                   (int64_t)s_ent, 10000 + k * 7, 0, 0)
               != nullptr);
    assert(LeagueMemberData(
               (int64_t)s_ent, 10000 + 7 * 13)
           != nullptr);

    printf("SYNDICATE_D36D_OK: AddMember (the double find, "
           "the def chain SetId(user/league), the gate with "
           "arg 1, the verbatim {key|anchor-high, stale "
           "node} users pair, the 9-u32 record copy, the "
           "dup/gate-fail/make-fail paths), RemoveMember "
           "(the release pair vt[8]/vt[0], the erase-at + "
           "the erase(key), not-found), CreateToken (the "
           "inline descent, the REVERSED SetId chain, the "
           "CToken ctor, the NO-ARG gate, the key getter + "
           "the pair insert + the readback, exists + the "
           "gate-fail dual release with the -2 sentinel + "
           "make-fail) — plus a 40/20/25 storm\n");
    return 0;
}

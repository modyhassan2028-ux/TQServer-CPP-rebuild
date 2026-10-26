// syndicate_d37_test.cpp — the D37 part 1 manager layer:
// the record accessors, the is-member check, the manager
// lookups (leagues/token-types), the user's-league walk,
// and the add/remove/token wrappers.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMember.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueUsers.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOps.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMembers.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace syndicate;

// ---------- counters ----------
static int g_nInvalid = 0, g_nLogs = 0;
static int g_nDefReleased = 0;
static bool g_bMakeFail = false;

static void* g_pInstVt[8];
static void* g_pInst[2] = { g_pInstVt, nullptr };

static void Bind() {
    g_fnLeagueInvalid = []() { ++g_nInvalid; };
    g_fnLeagueLogFactory = []() { ++g_nLogs; return (void*)1; };
    g_fnLeagueLogWrite  = [](void*, uint32_t, int) { };
    g_fnLeagueOpsInstance = []() { return (void*)g_pInst; };
    g_fnMgrStrCopy = [](char* d, const char* s, int cap) {
        int i = 0;
        for (; i + 1 < cap && s[i]; ++i) d[i] = s[i];
        for (; i < cap; ++i) d[i] = 0;
    };
}

// ---------- the def/holder fakes (the d36d recipe) ----------
struct FakeHolder {
    void* vft;
    void* inner;
    uint64_t uId;
};
struct FakeDef {
    void* vft;
    char  name[32];
    void* holders[4];
    bool  bInsert;
    uint64_t uInsArg;
};

static void* g_pHolderVt[32];
static void* s_defVt[16];
static FakeDef* g_pDefMemberCur = nullptr;
static FakeDef* g_pDefTokenCur  = nullptr;

static void* FakeMakeDef(void*, const char* name) {
    if (g_bMakeFail) return nullptr;
    FakeDef* d = nullptr;
    if (!strcmp(name, "cq_league_member")) d = g_pDefMemberCur;
    else if (!strcmp(name, "cq_league_token")) d = g_pDefTokenCur;
    else return nullptr;
    if (d == nullptr) {
        d = (FakeDef*)calloc(1, sizeof(FakeDef));
        d->vft = s_defVt;
        snprintf(d->name, sizeof d->name, "%s", name);
        d->bInsert = true;
        for (int i = 1; i <= 2; ++i) {
            FakeHolder* h = (FakeHolder*)calloc(1, sizeof(FakeHolder));
            h->vft = g_pHolderVt;
            h->inner = (void*)(0x1000 + i);
            d->holders[i] = h;
        }
        if (!strcmp(name, "cq_league_member")) g_pDefMemberCur = d;
        else g_pDefTokenCur = d;
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
static void FakeDefRelease5(void*, uint64_t, uint64_t,
                           uint64_t, int64_t d) {
    ++g_nDefReleased;
    if (d == (int64_t)0xfffffffffffffffe) { }
}
static uint64_t FakeHolderKey(void* self) {
    return ((FakeHolder*)self)->uId;
}

// ---------- the member record release fakes ----------
static int g_nRel40 = 0, g_nRel0 = 0, g_nTokVt0 = 0;
static void FakeRecRel40(void*, uint64_t) { ++g_nRel40; }
static void FakeRecRel0(void*, uint64_t)  { ++g_nRel0; }
static void FakeTokRel(void*, uint64_t) { ++g_nTokVt0; }
static void* g_pRecVt[16];
static void* g_pFakeRec[2];
static void* g_pTokVt[4];

// ---------- the ACCESSOR provider (entity+8) ----------
// resolve(idx) → a distinct fake holder per index
struct FakeAccRec {
    void* vft;
    uint64_t uVal[8];     // the per-slot storage
    uint64_t uIdx;
};
static void* g_pAccVt[32];
static FakeAccRec* g_apAccRec[16];   // by resolve idx
static uint64_t FakeAccGet40(void* self) {
    return ((FakeAccRec*)self)->uVal[0];
}
static uint64_t FakeAccGet48(void* self) {
    return ((FakeAccRec*)self)->uVal[1];
}
static uint64_t FakeAccGet78(void* self) {
    return ((FakeAccRec*)self)->uVal[2];
}
static void FakeAccSet80(void* self, uint64_t v) {
    ((FakeAccRec*)self)->uVal[3] = v;
}
static void FakeAccSetB0(void* self, uint32_t v) {
    ((FakeAccRec*)self)->uVal[4] = v;
}
static int g_nAccFlush = 0;
static void FakeAccFlush(void*, uint64_t) { ++g_nAccFlush; }
struct FakeProv {
    void* vft;
    FakeAccRec* recs[16];
};
static void* FakeAccResolve(void* self, uint64_t idx) {
    FakeProv* pr = (FakeProv*)self;
    assert(idx < 16 && pr->recs[idx]);
    return pr->recs[idx];
}
static void* g_pAccProvVt[8];
// make a provider whose resolve(0)→vt+0x48 (LeagueGetId)
// returns uLeagueId; its other records are fresh
static FakeProv* MkProv(uint64_t uLeagueId) {
    FakeProv* pr = (FakeProv*)calloc(1, sizeof(FakeProv));
    pr->vft = g_pAccProvVt;
    for (int i = 0; i < 16; ++i) {
        FakeAccRec* r = (FakeAccRec*)calloc(1, sizeof(FakeAccRec));
        r->vft = g_pAccVt;
        r->uVal[0] = 0x4000 + i;
        r->uVal[1] = 0x4800 + i;
        r->uVal[2] = 0x7800 + i;
        pr->recs[i] = r;
    }
    pr->recs[0]->uVal[1] = uLeagueId;   // the league id
    return pr;
}
static FakeProv* g_pAccProv = nullptr;   // the accessor test
static FakeProv* g_pProvA = nullptr;     // lgA (id 777)
static FakeProv* g_pProvB = nullptr;     // lgB (id 778)
static FakeProv* g_pProvC = nullptr;     // lgC (id 779)

// (the id role is served by the SAME accessor provider —
//  record 0's vt+0x48 = uVal[1] is the league id)
// ---------- the manager + league entities ----------
static char s_mgr[0x220];
static char s_lgA[0x120];
static char s_lgB[0x120];

static void MkMap(char* pOwner, int off, bool bMembers) {
    char* anchor = (char*)calloc(1, 8);
    *(char**)anchor = pOwner + off;
    if (bMembers) MembersMapCtor(pOwner + off);
    else          LeagueMemberCtor(pOwner + off);
    *(char**)(pOwner + off) = anchor;
}
static void BuildLeague(char* pEnt, uint32_t uLeader,
                        void* pProv) {
    memset(pEnt, 0, 0x120);
    MkMap(pEnt, 0x58, false);   // users
    MkMap(pEnt, 0x98, true);    // members
    MkMap(pEnt, 0xd8, false);   // tokens
    *(void**)(pEnt + 8) = pProv;
    *(uint32_t*)(pEnt + 0x10) = uLeader;
}
static void BuildMgr() {
    memset(s_mgr, 0, sizeof s_mgr);
    MkMap(s_mgr, 0x38, false);    // the leagues map
    MkMap(s_mgr, 0x1a0, false);  // the token-types map
    BuildLeague(s_lgA, 111, g_pProvA);
    BuildLeague(s_lgB, 222, g_pProvB);
}
// insert a league into the mgr map: the 16-byte pair home
// {key, value} — node key@+0x18, value@+0x20
static void MgrInsertLeague(uint32_t uId, char* pLg) {
    uint64_t pair[2];
    pair[0] = uId;
    pair[1] = (uint64_t)pLg;
    int64_t out[3];
    UsersInsertUnique((void*)(s_mgr + 0x38), (void*)out,
                      (uint32_t*)pair);
}
static void MgrInsertTokenType(uint32_t uId, void* pVal) {
    uint64_t pair[2];
    pair[0] = uId;
    pair[1] = (uint64_t)pVal;
    int64_t out[3];
    UsersInsertUnique((void*)(s_mgr + 0x1a0), (void*)out,
                      (uint32_t*)pair);
}
// put a user in a league's users map (the 16-byte home:
// {key | anchor-low-half, the stale head node as value})
static void LeaguePutUser(char* pLg, uint32_t uUser) {
    uint64_t pair[2];
    pair[0] = uUser;
    char* pcAnchor = *(char**)(pLg + 0x58);
    pair[0] = (uint64_t)uUser |
              ((uint64_t)pcAnchor & 0xffffffff00000000ULL);
    pair[1] = (uint64_t)*(char**)(pLg + 0x88);  // head
    int64_t out[3];
    UsersInsertUnique((void*)(pLg + 0x58), (void*)out,
                      (uint32_t*)pair);
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
    g_pTokVt[0] = (void*)&FakeTokRel;
    g_pLeagueTokenVft = g_pTokVt;
    // the accessor record vtable: slots 8/9/15/16/22
    g_pAccVt[8]  = (void*)&FakeAccGet40;
    g_pAccVt[9]  = (void*)&FakeAccGet48;
    g_pAccVt[15] = (void*)&FakeAccGet78;
    g_pAccVt[16] = (void*)&FakeAccSet80;
    g_pAccVt[22] = (void*)&FakeAccSetB0;
    g_pAccProvVt[2] = (void*)&FakeAccResolve;
    g_pAccProvVt[7] = (void*)&FakeAccFlush;
    g_pAccProv = MkProv(0x9999);   // the accessor entity
    g_pProvA = MkProv(777);
    g_pProvB = MkProv(778);
    g_pProvC = MkProv(779);
    for (int i = 0; i < 16; ++i)
        g_apAccRec[i] = g_pAccProv->recs[i];

    BuildMgr();

    // ================= the accessors =================
    // e70: the DIRECT read at +0x10
    assert(LeagueGetLeaderId((int64_t)s_lgA) == 111);
    assert(LeagueGetLeaderId((int64_t)s_lgB) == 222);

    // a null-provider entity
    static char s_nullEnt[0x20];
    memset(s_nullEnt, 0, sizeof s_nullEnt);
    int n0 = g_nLogs;
    // c80: null → 0 with NO log
    assert(LeagueGetRec2U32((int64_t)s_nullEnt) == 0);
    assert(g_nLogs == n0);
    // d10: null → the LOG + 0
    assert(LeagueGetRec9Str((int64_t)s_nullEnt) == 0);
    assert(g_nLogs == n0 + 1);
    // dd0: null → 0 with NO log
    assert(LeagueGetRec1Str((int64_t)s_nullEnt) == 0);
    assert(g_nLogs == n0 + 1);
    // d70 generic: null → the LOG + 0
    assert(LeagueGetRecStr((int64_t)s_nullEnt, 7) == 0);
    assert(g_nLogs == n0 + 2);
    // the setters on the null provider: the LOG + return
    LeagueSetRecStr((int64_t)s_nullEnt, 3, 0xAA, 1);
    LeagueSetRecInt((int64_t)s_nullEnt, 3, 0xBB, 1);
    assert(g_nLogs == n0 + 4);

    // the happy chains via the accessor provider
    static char s_accEnt[0x20];
    memset(s_accEnt, 0, sizeof s_accEnt);
    *(void**)(s_accEnt + 8) = g_pAccProv;
    // c80: resolve(2) → vt+0x40 = 0x4000+2
    assert(LeagueGetRec2U32((int64_t)s_accEnt) == 0x4002);
    // d10: resolve(9) → vt+0x48 = 0x4800+9
    assert(LeagueGetRec9Str((int64_t)s_accEnt) == 0x4809);
    // dd0: resolve(1) → vt+0x78 = 0x7800+1
    assert(LeagueGetRec1Str((int64_t)s_accEnt) == 0x7801);
    // d70 generic idx 7 (the a90 name path): → 0x7807
    assert(LeagueGetRecStr((int64_t)s_accEnt, 7) == 0x7807);
    // f90: resolve(5) → vt+0x80 setter + the flush
    int nf0 = g_nAccFlush;
    LeagueSetRecStr((int64_t)s_accEnt, 5, 0xABCD, 1);
    assert(g_apAccRec[5]->uVal[3] == 0xABCD);
    assert(g_nAccFlush == nf0 + 1);
    LeagueSetRecStr((int64_t)s_accEnt, 5, 0x1111, 0);
    assert(g_apAccRec[5]->uVal[3] == 0x1111);
    assert(g_nAccFlush == nf0 + 1);     // no flush
    // e80: resolve(6) → vt+0xb0 int setter + the flush
    LeagueSetRecInt((int64_t)s_accEnt, 6, 0x77, 1);
    assert(g_apAccRec[6]->uVal[4] == 0x77);
    assert(g_nAccFlush == nf0 + 2);
    LeagueSetRecInt((int64_t)s_accEnt, 6, 0x88, 0);
    assert(g_apAccRec[6]->uVal[4] == 0x88);
    assert(g_nAccFlush == nf0 + 2);     // no flush

    // ================= the is-member check =================
    LeaguePutUser(s_lgA, 55);
    assert(LeagueUserIsMember((int64_t)s_lgA, 55) == 1);
    assert(LeagueUserIsMember((int64_t)s_lgA, 56) == 0);
    assert(LeagueUserIsMember((int64_t)s_lgB, 55) == 0);
    // the empty map (lgB) → the root is the head → not found
    assert(LeagueUserIsMember((int64_t)s_lgB, 1) == 0);

    // ================= the manager lookups =================
    MgrInsertLeague(777, s_lgA);
    MgrInsertLeague(778, s_lgB);
    assert(MgrLeagueFind((int64_t)s_mgr, 777) == (void*)s_lgA);
    assert(MgrLeagueFind((int64_t)s_mgr, 778) == (void*)s_lgB);
    assert(MgrLeagueFind((int64_t)s_mgr, 999) == nullptr);
    // MgrLeagueGetType: the find + c80 on the league —
    // the league provider is the LEAGUE-ID mock: resolve(0)
    // → vt+0x48 = 777... BUT c80 needs resolve(2): the
    // mock asserts idx==0 → the league provider can't
    // serve it. Use the accessor-provider entity instead:
    // a THIRD "league" carrying the acc provider.
    static char s_lgC[0x120];
    BuildLeague(s_lgC, 333, g_pProvC);
    MgrInsertLeague(779, s_lgC);
    assert(MgrLeagueGetType((int64_t)s_mgr, 779) == 0x4002);
    assert(MgrLeagueGetType((int64_t)s_mgr, 777) == 0x4002);
    assert(MgrLeagueGetType((int64_t)s_mgr, 999) == 0);

    // MgrGetLeaderId: the find + the direct +0x10 read
    assert(MgrGetLeaderId((int64_t)s_mgr, 777) == 111);
    assert(MgrGetLeaderId((int64_t)s_mgr, 778) == 222);
    assert(MgrGetLeaderId((int64_t)s_mgr, 999) == 0);
    assert(MgrGetLeaderId((int64_t)s_mgr, 0) == 0);

    // the token-types map (+0x1a0)
    static char s_tok1[8], s_tok2[8];
    MgrInsertTokenType(12, s_tok1);
    MgrInsertTokenType(34, s_tok2);
    assert(MgrTokenTypeFind((int64_t)s_mgr, 12) == (void*)s_tok1);
    assert(MgrTokenTypeFind((int64_t)s_mgr, 34) == (void*)s_tok2);
    assert(MgrTokenTypeFind((int64_t)s_mgr, 56) == nullptr);

    // ================= the user's-league walk =================
    // user 55 is in lgA (id via the provider = 777)
    assert(MgrUserLeagueId((int64_t)s_mgr, 55) == 777);
    assert(MgrUserLeagueObj((int64_t)s_mgr, 55) == (void*)s_lgA);
    // a user in NO league → 0 / null
    assert(MgrUserLeagueId((int64_t)s_mgr, 66) == 0);
    assert(MgrUserLeagueObj((int64_t)s_mgr, 66) == nullptr);
    // a league with a NULL value (a zeroed node value) is
    // skipped: insert a 4th entry whose value is null
    {
        uint64_t pair[2] = { 50, 0 };
        int64_t out[3];
        UsersInsertUnique((void*)(s_mgr + 0x38), (void*)out,
                          (uint32_t*)pair);
    }
    assert(MgrUserLeagueId((int64_t)s_mgr, 66) == 0);
    // walk ORDER independence: user 66 in lgB → 777? no —
    // lgB's provider also returns 777 (the same mock)!
    LeaguePutUser(s_lgB, 66);
    assert(MgrUserLeagueObj((int64_t)s_mgr, 66) == (void*)s_lgB);
    // a user in BOTH leagues: the walk returns the FIRST in
    // the tree order (id 700 < 800 → lgA)
    LeaguePutUser(s_lgB, 55);
    assert(MgrUserLeagueObj((int64_t)s_mgr, 55) == (void*)s_lgA);

    // ================= the wrappers =================
    // ---- MgrAddMember: the gates ----
    assert(MgrAddMember((int64_t)s_mgr, 0, 777, 1,2,3,4,5,
                        "x") == 0);       // user 0
    assert(MgrAddMember((int64_t)s_mgr, 90, 0, 1,2,3,4,5,
                        "x") == 0);       // league 0
    assert(MgrAddMember((int64_t)s_mgr, 90, 777, 1,2,3,4,5,
                        nullptr) == 0);   // name null
    assert(MgrAddMember((int64_t)s_mgr, 55, 777, 1,2,3,4,5,
                        "x") == 0);       // already in lgA
    assert(MgrAddMember((int64_t)s_mgr, 90, 999, 1,2,3,4,5,
                        "x") == 0);       // league absent
    // ---- MgrAddMember: the happy path on lgC (a CLEAN
    //      league whose provider is the acc mock — but
    //      AddMember needs resolve(0) for the notify and
    //      resolve(1)/(2) for the def chain... the acc
    //      provider serves any idx) ----
    uint8_t r = MgrAddMember((int64_t)s_mgr, 90, 779, 1,2,3,4,5,
                             "abcdefgh");
    assert(r == 1);
    // the def chain ids: user on resolve(1), league on
    // resolve(2) — the league id = LeagueGetId(lgC) = the
    // provider's resolve(0)→vt+0x48... the acc mock's
    // record[0]->uVal[0] = 0x4000
    FakeDef* d = g_pDefMemberCur;
    assert(d);
    assert(d->uInsArg == 1);             // the vt+0x50 gate arg
    assert(((FakeHolder*)d->holders[1])->uId == 90);   // user
    assert(((FakeHolder*)d->holders[2])->uId == 779);  // league
    // the member record: the users node inserted at 90
    assert(LeagueUserIsMember((int64_t)s_lgC, 90) == 1);
    // read back the member record from the members map:
    // MembersMapFind(lgC+0x98, 90) → node value@+0x20
    {
        char* pcHead = *(char**)(s_lgC + 0xc8);
        char* pcCur = *(char**)(pcHead + 8);
        char* pcRem = pcHead;
        while (*(char*)(pcCur + 0x3d) == 0) {
            if (*(uint32_t*)(pcCur + 0x18) < 90)
                pcCur = *(char**)(pcCur + 0x10);
            else { if (*(uint32_t*)(pcCur + 0x18) >= 90) pcRem = pcCur;
                   pcCur = *(char**)pcCur; }
        }
        (void)pcRem;
        // walk all member nodes; find key 90
        char* n = *(char**)pcHead;
        char* found = nullptr;
        while (*(uint8_t*)(n + 0x3d) == 0) {
            if (*(uint32_t*)(n + 0x18) == 90) found = n;
            char it[2][8];
            *(char**)it[0] = *(char**)(s_lgC + 0x98);
            *(char**)(it[0] + 8) = n;
            MembersIterNext(it[0]);
            n = *(char**)(it[0] + 8);
        }
        assert(found);
        // the members node value is INLINE at +0x18 (the
        // 9-u32 record, the key being rec[0])
        uint32_t* rec = (uint32_t*)(found + 0x18);
        assert(rec[0] == 90);             // the user id
        // auRec[1..2] = the memcpy 8 bytes = p4/p5
        assert(rec[1] == 1 && rec[2] == 2);
        // auRec[3] = {p6(u16)=3, p7.low16=4}
        assert(rec[3] == (uint32_t)(3 | (4 << 16)));
        // auRec[4] = bytes 0xc..0xf = {p7.high16, p8@0xe,
        //   name[0]@0xf} → p8<<16 | 'a'<<24
        assert(rec[4] == (uint32_t)(((uint32_t)5 << 16) |
                                    ((uint32_t)'a' << 24)));
        // auRec[5..6] = name[1..4] / name[5..8]
        assert(rec[5] == (uint32_t)('b' | ('c' << 8) |
                                    ('d' << 16) |
                                    ((uint32_t)'e' << 24)));
        assert(rec[6] == (uint32_t)('f' | ('g' << 8) |
                                    ('h' << 16)));
        // auRec[7..8] = u32@0x18 / u16@0x1c|u8@0x1e<<16 = 0
        assert(rec[7] == 0 && rec[8] == 0);
    }
    // now 90 IS a member → the add gate fails
    assert(MgrAddMember((int64_t)s_mgr, 90, 779, 1,2,3,4,5,
                        "x") == 0);

    // ---- MgrRemoveMember ----
    // the ORIGINAL: the users node's +0x20 slot holds the
    // member RECORD object (the record system's owner —
    // the same d36d rule); point it at the fake record
    // before the removal
    {
        char* n = **(char***)(s_lgC + 0x88);  // head->_Left
        while (*(uint8_t*)(n + 0x29) == 0) {
            if (*(uint32_t*)(n + 0x18) == 90) break;
            char it[2][8];
            *(char**)it[0] = *(char**)(s_lgC + 0x58);
            *(char**)(it[0] + 8) = n;
            UsersIterNext(it[0]);
            n = *(char**)(it[0] + 8);
        }
        assert(*(uint32_t*)(n + 0x18) == 90);
        *(void**)(n + 0x20) = (void*)g_pFakeRec;
    }
    int nRel0 = g_nRel0, nRel40 = g_nRel40;
    assert(MgrRemoveMember((int64_t)s_mgr, 0, 90) == 0);
    assert(MgrRemoveMember((int64_t)s_mgr, 779, 0) == 0);
    assert(MgrRemoveMember((int64_t)s_mgr, 999, 90) == 0);
    assert(MgrRemoveMember((int64_t)s_mgr, 779, 90) == 1);
    assert(g_nRel40 == nRel40 + 1 && g_nRel0 == nRel0 + 1);
    assert(LeagueUserIsMember((int64_t)s_lgC, 90) == 0);

    // ---- MgrCreateToken ----
    // absent league → the log + 0
    n0 = g_nLogs;
    assert(MgrCreateToken((int64_t)s_mgr, 999, 0x42, 5) ==
           nullptr);
    assert(g_nLogs == n0 + 1);
    // happy path on lgC (the token def chain — the acc
    // provider's resolve(1)/(2) serve the REVERSED chain)
    void* pTok = MgrCreateToken((int64_t)s_mgr, 779, 0x77, 9);
    assert(pTok != nullptr);
    FakeDef* dt = g_pDefTokenCur;
    assert(dt);
    // the CToken = {vftable, def}
    assert(*(void**)pTok == g_pLeagueTokenVft);
    assert(*(void**)((char*)pTok + 8) == (void*)dt);
    // the REVERSED chain: SetId(token) on resolve(2),
    // SetId(league) on resolve(1) — the league id = 779
    assert(((FakeHolder*)dt->holders[2])->uId == 0x77);
    assert(((FakeHolder*)dt->holders[1])->uId == 779);
    // the tokens map holds {0x77 | anchor-high, pTok}
    char* nT = *(char**)(s_lgC + 0x108);   // the head
    nT = *(char**)nT;                       // head->_Left
    assert(*(uint32_t*)(nT + 0x18) == 0x77);
    assert(*(char**)(nT + 0x20) == pTok);
    // the readback via the part-1 lookup
    assert(LeagueMemberData((int64_t)s_lgC, 0x77) ==
           pTok);
    // the exists-dup → the log + 0
    n0 = g_nLogs;
    assert(MgrCreateToken((int64_t)s_mgr, 779, 0x77, 9)
           == nullptr);
    assert(g_nLogs == n0 + 1);

    printf("SYNDICATE-D37-OK: the record accessors (the "
           "direct +0x10 leader read, the null-provider "
           "log/no-log gates, resolve(2)→+0x40 / (9)→+0x48"
           " / (1)→+0x78 / the GENERIC (idx)→+0x78, the "
           "+0x80/+0xb0 setters + the vt+0x38 flush), the "
           "is-member check, the manager lookups (leagues "
           "+0x38 / token-types +0x1a0), the user's-league "
           "walk with the inlined successor (null-value "
           "skip + tree order), the add/remove/token "
           "wrappers with the verbatim 0x1f record tail\n");
    return 0;
}

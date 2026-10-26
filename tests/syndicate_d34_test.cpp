// ============================================================
// syndicate_d34_test — the league SORT COMPARATOR subgraph
// (T8/D34): the singleton 1417b6210 + the map find 1417c8f70
// + the member lookup 1417cad00 + the getters 14178f270/
// 14178f410 + the comparator 1417ba4c0 — and the END-TO-END
// binding into the D33 introsort through g_fnLeagueCmp.
// The member map is a REAL 0x30-node tree built with the
// D32 tree functions (LeagueMemberCtor/LeagueInsert).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueSort.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"

using namespace syndicate;

// ---------------- the seams ----------------
static int s_nOpNew = 0;
static void* TestOpNew(size_t n) { s_nOpNew++; return malloc(n); }
static int s_nInvalid = 0;
static void TestInvalid() { s_nInvalid++; }
static int s_nLogs = 0;
static void* TestLogFactory() { s_nLogs++; return (void*)0x1; }
static void TestLogWrite(void*, uint32_t, int) {}
static uint8_t s_vftLogic[8];
static uint8_t s_vftProvider[8];

// ---------------- the member/provider mock ----------------
// each member owns its provider: *(member+0x428) = the
// provider; provider[0] = the vtable; vt[0x10] = the
// resolver (provider, 0|0x2d) → the wrapper; wrapper[0]
// = the vtable; vt[0x40] = rank getter, vt[0x48] = sec
// getter — the getter receives the wrapper (vt at pw[0],
// the member at pw[1]).
struct Member {
    char raw[0x430];
    uint32_t id;
    uint32_t rank;
    int32_t sec;
};
struct Wrapper { void* vt; void* m; };
struct Provider { void* vt; void* wrapper; };

static uint64_t GetRank(void** pw) { return ((Member*)pw[1])->rank; }
static uint64_t GetSec(void** pw) { return ((Member*)pw[1])->sec; }
static void* Resolve(void** provider, uint64_t idx) {
    assert(idx == 0 || idx == 0x2d);   // the two probe ids of 78f270/78f410
    return ((Provider*)provider)->wrapper;
}
static void* g_wrapperVt[16];
static void* g_providerVt[16];
static std::vector<Provider> s_providers;
static std::vector<Wrapper> s_wrappers;

static void SetProvider(Member* m) {
    g_wrapperVt[8] = (void*)&GetRank;     // vt+0x40
    g_wrapperVt[9] = (void*)&GetSec;      // vt+0x48
    g_providerVt[2] = (void*)&Resolve;    // vt+0x10
    s_providers.push_back({ g_providerVt, &s_wrappers[s_wrappers.size()] });
    s_wrappers.push_back({ g_wrapperVt, m });
    *(void**)(m->raw + 0x428) = &s_providers.back();
}

// ---------------- the manager + the real map ----------------
static char s_mgr[0x100];
static std::vector<Member*> s_members;

static void InsertMember(uint32_t uId, uint32_t uRank, int32_t nSec) {
    Member* m = (Member*)calloc(1, sizeof(Member));
    m->id = uId; m->rank = uRank; m->sec = nSec;
    SetProvider(m);
    // the map node: key@+0x18 = id, value@+0x20 = the member
    uint64_t kv[2] = { uId, (uint64_t)(uintptr_t)m };
    char* pmap = s_mgr + 8;
    char* head = *(char**)(pmap + 0x30);
    char* attach = head;
    bool bLeft = true;
    if (*(char*)(*(char**)(head + 8) + 0x29) == '\0') {
        char* cur = *(char**)(head + 8);
        do {
            attach = cur;
            bLeft = uId < *(uint32_t*)(cur + 0x18);
            cur = bLeft ? *(char**)cur : *(char**)(cur + 0x10);
        } while (*(char*)(cur + 0x29) == '\0');
    }
    char out[2][8];
    LeagueInsert(pmap, out[0], bLeft ? 1 : 0, attach, kv);
    s_members.push_back(m);
}

// reserve first so the stored wrapper pointers stay valid
struct Reserver { Reserver() { s_providers.reserve(300); s_wrappers.reserve(300); } };
static Reserver s_reserver;

// the D32 tree seams (the same mock kit as syndicate_d32_test)
namespace syndicate {
// the merit seams come from SyndicateCrossMerit.o
// (the defaults) — these were bare re-definitions that
// collided at link time once SyndicateMapTree needed
// the real definitions
}

int main() {
    // ---- bind the D34 seams ----
    g_fnLeagueOpNew = TestOpNew;
    g_fnLeagueInvalid = TestInvalid;
    g_fnLeagueLogFactory = TestLogFactory;
    g_fnLeagueLogWrite = TestLogWrite;
    g_pLeagueVftLogic = s_vftLogic;
    g_pLeagueVftProvider = s_vftProvider;
    memset(s_mgr, 0, sizeof(s_mgr));

    // ================= D34-1: the singleton =================
    {
        assert(g_pLeagueDatInstance == nullptr);
        void* p1 = LeagueSingleton();
        assert(p1 != nullptr);
        assert(s_nOpNew == 1);                       // one alloc of 0x88
        char* pc = (char*)p1;
        assert(*(void**)pc == (void*)s_vftLogic);     // the LAST vftable store wins
        assert(*(void**)(pc + 0x10) == nullptr);      // slot [2]
        assert(*(uint8_t*)(pc + 0x60) == 0);          // the byte slot [0xc]
        assert(*(void**)(pc + 0x61) == nullptr);      // the unaligned qwords
        assert(*(void**)(pc + 0x79) == nullptr);
        void* p2 = LeagueSingleton();
        assert(p1 == p2 && s_nOpNew == 1);           // cached
        printf("D34-1 singleton ok\n");
    }

    // ================= D34-2: the member lookup =================
    {
        // the real 0x30-node map at mgr+8
        LeagueMemberCtor(s_mgr + 8);
        // wire the singleton slot [2] = the mgr
        *(void**)((char*)g_pLeagueDatInstance + 0x10) = s_mgr;

        InsertMember(10, 5, 100);
        InsertMember(20, 5, 100);
        InsertMember(30, 2, 300);
        InsertMember(40, 9, 300);
        InsertMember(50, 1, 700);

        Member* m = (Member*)(uintptr_t)LeagueMemberLookup(s_mgr, 10);
        assert(m && m->id == 10);
        m = (Member*)(uintptr_t)LeagueMemberLookup(s_mgr, 40);
        assert(m && m->id == 40 && m->rank == 9);
        assert(LeagueMemberLookup(s_mgr, 0) == 0);         // the 0-key gate
        assert(LeagueMemberLookup(s_mgr, 999) == 0);       // missing
        assert(s_nInvalid == 0);
        printf("D34-2 member lookup ok (real map, 5 members)\n");
    }

    // ================= D34-3: the getters =================
    {
        Member* a = s_members[0];
        assert(LeagueMemberRank((int64_t)a->raw) == 5);
        assert(LeagueMemberSec((int64_t)a->raw) == 100);
        Member* b = s_members[4];
        assert(LeagueMemberRank((int64_t)b->raw) == 1);
        assert(LeagueMemberSec((int64_t)b->raw) == 700);
        // the null-provider gate: log + 0
        char* bare = (char*)calloc(0x430, 1);
        int nLogs0 = s_nLogs;
        assert(LeagueMemberRank((int64_t)bare) == 0);
        assert(LeagueMemberSec((int64_t)bare) == 0);
        assert(s_nLogs == nLogs0 + 2);   // one log per failed getter
        printf("D34-3 getters ok (+ the null-provider gate)\n");
    }

    // ================= D34-4: the comparator branches =================
    {
        g_fnLeagueCmp = &LeagueMemberCmp;
        int st = 99;   // a rank NO member has → the full order
        // a missing → false
        assert(!LeagueMemberCmp(&st, 999, 10));
        // b missing → true (a resolves)
        assert(LeagueMemberCmp(&st, 10, 999));
        // rank(a) == the state → true
        int st5 = 5;   assert(LeagueMemberCmp(&st5, 10, 30));   // rank(10)=5 == state
        int st9 = 9;   assert(LeagueMemberCmp(&st9, 40, 50));   // rank(40)=9 == state
        // state == rank(b) → false
        int st2 = 2;   assert(!LeagueMemberCmp(&st2, 10, 30));  // rank(30)=2 == state
        int st1 = 1;   assert(!LeagueMemberCmp(&st1, 10, 50)); // rank(50)=1 == state
        // sec equal → rank ASC: 30(2,300) vs 40(9,300)
        assert(LeagueMemberCmp(&st, 30, 40) == (2 < 9));
        assert(LeagueMemberCmp(&st, 40, 30) == (9 < 2));
        // 10(5,100) vs 20(5,100): sec AND rank equal → false both ways
        assert(!LeagueMemberCmp(&st, 10, 20));
        assert(!LeagueMemberCmp(&st, 20, 10));
        // sec differs → sec DESC: 10(sec100) vs 30(sec300)
        assert(LeagueMemberCmp(&st, 10, 30) == (300 < 100));   // false
        assert(LeagueMemberCmp(&st, 30, 10) == (100 < 300));   // true
        printf("D34-4 comparator branches ok\n");
    }

    // ================= D34-5: end-to-end with the D33 sort =================
    {
        // 40 more members with mixed ranks/secs
        for (uint32_t i = 100; i < 140; i++) {
            InsertMember(i, 1 + (i * 7) % 9, (int32_t)(i * 13) % 400);
        }
        std::vector<uint32_t> ids;
        for (auto* m : s_members) ids.push_back(m->id);
        // shuffle deterministically
        uint32_t seed = 7;
        for (size_t i = ids.size(); i > 1; i--) {
            seed = seed * 1103515245 + 12345;
            size_t j = (seed >> 17) % i;
            std::swap(ids[i - 1], ids[j]);
        }
        int st = 99;   // not any rank → the full order: sec DESC, then rank ASC
        LeagueSortIntro(ids.data(), ids.data() + ids.size(), 4000, st);
        // verify: no later element strictly before its predecessor
        for (size_t i = 1; i < ids.size(); i++) {
            assert(!LeagueMemberCmp(&st, ids[i], ids[i - 1]));
        }
        // and the bag is preserved
        std::vector<uint32_t> sorted = ids;
        std::sort(sorted.begin(), sorted.end());
        std::vector<uint32_t> orig;
        for (auto* m : s_members) orig.push_back(m->id);
        std::sort(orig.begin(), orig.end());
        assert(sorted == orig);
        printf("D34-5 end-to-end sort ok (%zu members)\n", ids.size());
    }

    printf("SYNDICATE-D34-OK: the comparator subgraph complete — the "
           "CSyndicateLogic singleton b6210 (0x88 + the dual vftable stores "
           "+ the unaligned zero fills), the map find c8f70 (the lower_bound "
           "on the 0x30 nodes + the end-iter output), the lookup cad00 (the "
           "0-key gate + the owner/node iterator checks + the value@+0x20), "
           "the getters 78f270/78f410 (the +0x428 provider gate + the "
           "resolve/read vtable chains), the comparator ba4c0 (a-missing "
           "false / b-missing true / the state==rank gates / sec-desc + "
           "rank-asc) — bound live into the D33 introsort\n");
    return 0;
}

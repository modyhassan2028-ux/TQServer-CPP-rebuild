// syndicate_d49_test — D49/T16: the REAL grade page
// query (141779f40 = CMeedRecord::GetMeedRecord):
// the lazy sort flag (141779eb0 — the sort itself a
// seam for D50), the type match (1417782c0), and the
// verbatim page walks (type 2: the skip window +
// frozen rank; types 1/3: the SELF slot-0 path +
// the offset window + the page fill + the self-exit
// and the empty-vector return of 1).
#include "../modules/syndicate/src/SyndicateMeedFlow.h"
#include "../modules/syndicate/src/SyndicateSynMeed.h"
#include "../modules/syndicate/src/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace syndicate;

static int g_nInvalid = 0, g_nLog = 0;
static void MockInvalid() { ++g_nInvalid; }
static void MockLog() { ++g_nLog; }
static int g_nSort = 0;
static void MockSortRaw(void** b, void** e, int n) {
    ++g_nSort;
    assert(e - b == n);
}

// the member: {id, type, f4, f5, f6}
struct Member {
    uint64_t id, type, f4, f5, f6;
};
static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    switch (n) {
    case 0: case 2: return &m->id;
    case 3: return &m->type;
    case 4: return &m->f4;
    case 5: return &m->f5;
    case 6: return &m->f6;
    default: return &m->id;
    }
}
static int SubNId(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static int SubNVal(void* pS) {   // vt+0x48
    // (the mock: the slot index is implicit — the
    //  caller passes the right member field)
    return (int)(((uint64_t*)pS)[0]);
}
static void* MemSubV(void* pM) {
    return &((Member*)pM)->f4;
}
static uint32_t SubVVal(void* pS) {
    return (uint32_t)(((uint64_t*)pS)[0]);
}
// per-index value reads (vt+0x48): 4/5/6
static int SubNType(void* pS) {
    return (int)(((uint64_t*)pS)[0]);
}

// the league ABI for this walk: dbg proxy@+8,
// begin@+0x20, end@+0x28, the sort flag@+0x38
struct Rec {
    void* pad0;        // +0
    void* pad1;        // +8 (the proxy anchor)
    void* pad2;        // +0x10
    void* pad3;        // +0x18
    void** begin;      // +0x20
    void** end;        // +0x28
    uint8_t flag;      // +0x30
    uint8_t pad4[7];   // -> +0x38
    uint8_t sorted;    // +0x38
};
static void* dbgAnchor[1] = { (void*)1 };

static void Build(Rec* r, void** cells, int n) {
    memset(r, 0, sizeof(*r));
    r->pad1 = &r->pad1;   // the dbg proxy anchor
    r->begin = cells;
    r->end = cells + n;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedLog = MockLog;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubNId;
    g_fnMeedSubNType = SubNType;
    g_fnMeedMemSubV = MemSubV;
    g_fnMeedSubVVal = SubVVal;
    g_fnMeedSortRaw = MockSortRaw;

    // ---------- D49-1: the type match + gates ------
    static Member m5 = { 0x50, 2, 400, 500, 600 };
    assert(!MeedRecMatchType(nullptr, nullptr, 2)
        && g_nLog == 1 && "the null member logs");
    assert(MeedRecMatchType(nullptr, &m5, 2));
    assert(!MeedRecMatchType(nullptr, &m5, 1));
    printf("D49-1 the type match ok\n");

    // ---------- D49-2: the lazy sort flag ----------
    static void* cells1[1] = { &m5 };
    Rec r1;
    Build(&r1, cells1, 1);
    g_nSort = 0;
    MeedSortIfNeeded(&r1);
    assert(g_nSort == 1 && r1.sorted == 1);
    MeedSortIfNeeded(&r1);
    assert(g_nSort == 2
        && "the sort itself does NOT re-check"
           " (the caller gates via the flag)");
    // the type gate of GetRecord
    g_nLog = 0;
    int32_t out[40] = { 0 };
    assert(MeedGetRecord(&r1, 0x50, out, 4, 0, 4)
        == 0 && g_nLog == 1);
    // the sort fires once on the first query
    r1.sorted = 0;
    g_nSort = 0;
    MeedGetRecord(&r1, 0x50, out, 2, 0, 4);
    assert(g_nSort == 1 && r1.sorted == 1);
    printf("D49-2 the lazy sort flag ok\n");

    // ---------- D49-3: type 2, page 1 -------------
    // (limit=0: no window; every cell written with
    //  the FROZEN rank matches+1 = 1 — verbatim)
    static Member t2[5] = {
        { 0x11, 2, 41, 51, 61 },
        { 0x12, 2, 42, 52, 62 },
        { 0x13, 2, 43, 53, 63 },
        { 0x14, 2, 44, 54, 64 },
        { 0x15, 2, 45, 55, 65 } };
    static void* c2[5] = { &t2[0], &t2[1], &t2[2],
                           &t2[3], &t2[4] };
    Rec r2;
    Build(&r2, c2, 5);
    memset(out, 0, sizeof(out));
    int n = MeedGetRecord(&r2, 0x77, out, 2, 0, 8);
    assert(n == 5);
    for (int i = 0; i < 5; ++i) {
        assert(out[i * 5 + 0] == 1
            && "the rank frozen at matches+1");
        assert(out[i * 5 + 1] == (int32_t)t2[i].id);
        assert(out[i * 5 + 2] == 41 + i);
        assert(out[i * 5 + 3] == 51 + i);
        assert(out[i * 5 + 4] == 61 + i);
    }
    printf("D49-3 type 2 page 1 ok\n");

    // ---------- D49-4: type 2, the skip window ----
    // page 2 (limit=8): the first 8 matches skip;
    //  with only 5 cells: matches reaches 5 then...
    //  the loop writes NOTHING (all 5 skip) — wait:
    //  the write only happens once matches >= 8,
    //  so with 5 cells all skip → visited hits
    //  count → return 0? NO — the early return fires
    //  first (count <= visited → return ret=0).
    memset(out, 0, sizeof(out));
    n = MeedGetRecord(&r2, 0x77, out, 2, 8, 8);
    assert(n == 0
        && "all cells consumed by the window");
    // page 2 with 10 cells: 8 skip, 2 write rank 9
    static Member t2b[10];
    static void* c2b[10];
    for (int i = 0; i < 10; ++i) {
        t2b[i] = { (uint64_t)(0x20 + i), 2,
                   (uint64_t)(40 + i),
                   (uint64_t)(50 + i),
                   (uint64_t)(60 + i) };
        c2b[i] = &t2b[i];
    }
    Rec r2b;
    Build(&r2b, c2b, 10);
    memset(out, 0, sizeof(out));
    n = MeedGetRecord(&r2b, 0x77, out, 2, 8, 8);
    assert(n == 2 && "8 skip then 2 written");
    assert(out[0] == 9 && out[5] == 9
        && "the frozen rank = window+1");
    assert(out[1] == 0x28 && out[6] == 0x29);
    assert(out[2] == 48 && out[3] == 58);
    assert(out[4] == 68);
    printf("D49-4 type 2 the skip window ok\n");

    // ---------- D49-5: types 1/3 — the self path --
    // 6 cells, self at index 2; page 1 (limit=0,
    // page=4)
    static Member t1[6] = {
        { 0x31, 1, 10, 11, 12 },
        { 0x32, 1, 20, 21, 22 },
        { 0x50, 1, 30, 31, 32 },   // the SELF
        { 0x34, 1, 40, 41, 42 },
        { 0x35, 1, 50, 51, 52 },
        { 0x36, 1, 60, 61, 62 } };
    static void* c1[6] = { &t1[0], &t1[1], &t1[2],
                           &t1[3], &t1[4], &t1[5] };
    Rec r1b;
    Build(&r1b, c1, 6);
    memset(out, 0, sizeof(out));
    n = MeedGetRecord(&r1b, 0x50, out, 1, 0, 4);
    assert(n == 4);
    // slot 0 = the self (written at rank 3)
    assert(out[0] == 3 && out[1] == 0x50
        && out[2] == 30 && out[3] == 31
        && out[4] == 32);
    // slots 1-4 = the cells 0,1,2,3 with ranks
    // 1,2,3,4 (the self ALSO lands in the page —
    // verbatim: the a22d fallthrough)
    assert(out[5] == 1 && out[6] == 0x31
        && out[10] == 2 && out[11] == 0x32);
    assert(out[15] == 3 && out[16] == 0x50);
    assert(out[20] == 4 && out[21] == 0x34);
    printf("D49-5 types 1/3 the self path ok\n");

    // ---------- D49-6: the self-exit + full page --
    // 10 cells, self at index 9; page 1 fills the
    // 4 slots first → the self path exits with
    // ret+1 = 5
    static Member t1b[10];
    static void* c1b[10];
    for (int i = 0; i < 10; ++i) {
        t1b[i] = { (uint64_t)(i == 9 ? 0x50
                                     : 0x70 + i),
                   1, (uint64_t)(10 * i),
                   (uint64_t)(10 * i + 1),
                   (uint64_t)(10 * i + 2) };
        c1b[i] = &t1b[i];
    }
    Rec r1c;
    Build(&r1c, c1b, 10);
    memset(out, 0, sizeof(out));
    n = MeedGetRecord(&r1c, 0x50, out, 1, 0, 4);
    assert(n == 5
        && "4 page entries + the self exit");
    assert(out[0] == 10 && out[1] == 0x50
        && "slot 0 = the self at rank 10");
    assert(out[5] == 1 && out[10] == 2
        && out[15] == 3 && out[20] == 4);
    // the empty vector → 1 (the a300 inc, verbatim)
    Rec r1d;
    Build(&r1d, c1b, 0);
    memset(out, 0, sizeof(out));
    n = MeedGetRecord(&r1d, 0x50, out, 1, 0, 4);
    assert(n == 1
        && "the empty vector returns 1 (verbatim)");
    assert(g_nInvalid == 0);
    printf("D49-6 the self-exit + gates ok\n");

    // ---------- D49-7: the seam default ---------
    assert(g_fnMeedGradePage == &MeedGetRecord
        && "the flow seam = the REAL function");
    printf("D49-7 the seam default ok\n");

    printf(
      "SYNDICATE-D49-OK: the REAL 141779f40 grade page"
      " query - the lazy sort flag (141779eb0, the"
      " introsort a seam for D50), the type match"
      " (1417782c0) and the verbatim walks: type 2"
      " (the skip window + the FROZEN rank + the early"
      " return), types 1/3 (the SELF slot-0 + the"
      " a22d fallthrough + the page fill + the"
      " self-exit ret+1 + the empty-vector 1); the"
      " flow seam g_fnMeedGradePage now defaults to"
      " the REAL function\n");
    return 0;
}

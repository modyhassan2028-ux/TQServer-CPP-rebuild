// syndicate_d50_test — D50/T16: the REAL introsort
// family (the lazy-sort backend of the grade page
// query): the comparator (1417781b0 — equal→TRUE
// verbatim), median-3/median-guess (1417786d0/
// 1417788c0), the heap (141778760/141778d90/
// 141778f80), the insertion sort (141778a20), the
// partition (141778b60 — goto-faithful from the
// disassembly) and the driver (141779790 —
// threshold 0x21, depth 3/4, heap fallback). The
// invariants: lexicographic DESC by (type, grade,
// sub0), permutation preservation, all size bands.
#include "../Exe/Dll/Syndicate/Port/SyndicateMeedSort.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <random>
#include <vector>

using namespace syndicate;

static void MockInvalid() {}
static void MockLog() {}

// the member: {id(sub0), type(sub3), grade(sub4)}
struct Member {
    uint64_t id, type, grade;
};
static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    if (n == 3) return &m->type;
    if (n == 4) return &m->grade;
    return &m->id;      // 0 and 2
}
static int SubId(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static int SubVal(void* pS) {   // vt+0x48
    return (int)(((uint64_t*)pS)[0]);
}

// the key: (type, grade, sub0) — desc
struct Key {
    uint64_t t, g, v;
};
static Key KeyOf(const Member& m) {
    return { m.type, m.grade, m.id };
}
static bool KeyGe(const Key& a, const Key& b) {
    if (a.t != b.t) return a.t > b.t;
    if (a.g != b.g) return a.g > b.g;
    return a.v > b.v;
}

static bool CheckSorted(const std::vector<Member*>& v) {
    for (size_t i = 1; i < v.size(); ++i) {
        Key a = KeyOf(*v[i - 1]);
        Key b = KeyOf(*v[i]);
        if (!KeyGe(a, b) && !(a.t == b.t && a.g == b.g
                              && a.v == b.v)) {
            return false;   // a < b strictly
        }
    }
    return true;
}
static bool SameMultiset(const std::vector<Member*>& x,
                        const std::vector<Member*>& y) {
    std::vector<uint64_t> kx, ky;
    for (auto* m : x) {
        kx.push_back(m->id * 1000003 ^ m->type
                     * 7919 ^ m->grade);
    }
    for (auto* m : y) {
        ky.push_back(m->id * 1000003 ^ m->type
                     * 7919 ^ m->grade);
    }
    std::sort(kx.begin(), kx.end());
    std::sort(ky.begin(), ky.end());
    return kx == ky;
}

static void RunCase(const char* name, int n,
                    std::mt19937_64& rng,
                    int dupBands) {
    std::vector<Member> mem(n);
    for (int i = 0; i < n; ++i) {
        // duplicate-friendly key bands
        mem[i] = { rng() % (dupBands * 3 + 1),
                   rng() % (dupBands + 1) + 1,
                   rng() % (dupBands * 2 + 1) + 1 };
    }
    std::vector<Member*> ptrs;
    for (auto& m : mem) ptrs.push_back(&m);
    std::vector<Member*> before = ptrs;
    MeedSortRaw((void**)ptrs.data(),
                (void**)(ptrs.data()
                         + ptrs.size()),
                (int)ptrs.size());
    assert(CheckSorted(ptrs)
        && "sorted desc (type,grade,sub0)");
    assert(SameMultiset(before, ptrs)
        && "permutation preserved");
    printf("D50-case %-14s n=%5d ok\n", name, n);
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedLog = MockLog;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubId;
    g_fnMeedSubNType = SubVal;

    // ---------- D50-1: the comparator -----------
    static Member a = { 5, 2, 100 };
    static Member b = { 7, 2, 100 };
    static Member c = { 5, 3, 1 };
    static Member d = { 5, 2, 50 };
    assert(!MeedSortCmp(nullptr, &a)
        && "null a → false");
    assert(MeedSortCmp(&a, nullptr)
        && "null b → true");
    assert(MeedSortCmp(&c, &a)
        && "higher type first");
    assert(!MeedSortCmp(&a, &c));
    assert(MeedSortCmp(&b, &a)
        && "same type: higher sub0 first");
    assert(MeedSortCmp(&a, &d)
        && "same type: higher grade first");
    assert(MeedSortCmp(&a, &a)
        && "equal → TRUE (verbatim)");
    printf("D50-1 the comparator ok\n");

    // ---------- D50-2: median-3 / guess ---------
    static Member m1 = { 1, 1, 1 };
    static Member m2 = { 2, 5, 1 };
    static Member m3 = { 3, 3, 3 };
    void* p1 = &m1; void* p2 = &m2; void* p3 = &m3;
    MeedMedian3(&p1, &p2, &p3);
    // p2 = the median (type 3)
    assert(((Member*)p2)->type == 3
        && "the median lands at p2");
    assert(((Member*)p1)->type == 5
        && ((Member*)p3)->type == 1
        && "p1 = the FIRST per cmp (the top),"
           " p3 = the last");
    printf("D50-2 the median-3 ok\n");

    // ---------- D50-3: the size bands ----------
    std::mt19937_64 rng(6159);
    RunCase("tiny-1", 1, rng, 1);
    RunCase("small-8", 8, rng, 2);
    RunCase("insert-32", 32, rng, 4);
    RunCase("part-33", 33, rng, 4);
    RunCase("guess-41", 41, rng, 6);
    RunCase("guess-200", 200, rng, 8);
    RunCase("big-1000", 1000, rng, 10);
    RunCase("dup-heavy-500", 500, rng, 1);
    RunCase("big-10000", 10000, rng, 20);
    printf("D50-3 the size bands ok\n");

    // ---------- D50-4: the heap fallback -------
    // depth 0 → the introsort takes the heapsort
    // path for n > 0x20 (and the insertion path
    // for the tail)
    {
        int n = 500;
        std::vector<Member> mem(n);
        for (int i = 0; i < n; ++i) {
            mem[i] = { rng() % 97 + 1,
                       rng() % 5 + 1,
                       rng() % 211 + 1 };
        }
        std::vector<Member*> ptrs;
        for (auto& m : mem) ptrs.push_back(&m);
        std::vector<Member*> before = ptrs;
        MeedSortDriver((void**)ptrs.data(),
                       (void**)(ptrs.data() + n),
                       0);
        assert(CheckSorted(ptrs));
        assert(SameMultiset(before, ptrs));
        printf("D50-4 the heap fallback ok\n");
    }

    // ---------- D50-5: the integration ---------
    // MeedSortIfNeeded (D49) now sorts FOR REAL:
    // build the D49-style record and verify the
    // page walk sees the sorted order
    {
        struct Rec {
            void* pad0; void* pad1; void* pad2;
            void* pad3; void** begin; void** end;
            uint8_t flag;
            uint8_t pad4[7];
            uint8_t sorted;
        };
        int n = 60;
        static Member mem[60];
        static void* cells[60];
        for (int i = 0; i < n; ++i) {
            mem[i] = { (uint64_t)(0x30 + i),
                       (uint64_t)(1 + i % 3),
                       (uint64_t)(1000 - i) };
            cells[i] = &mem[i];
        }
        Rec r;
        memset(&r, 0, sizeof(r));
        r.pad1 = &r.pad1;
        r.begin = cells;
        r.end = cells + n;
        // type-2 ranks: after the REAL sort the
        // first page (limit=0, page=8) must hold
        // the top-8 by (type,grade,sub0) desc
        int32_t out[40] = { 0 };
        int cnt = MeedGetRecord(&r, 0x99, out, 2,
                                0, 8);
        assert(cnt == 8);
        // the top key: type 3 (i%3==2 → i=2,5,8..)
        // grade desc among type 3s: grade=1000-i
        // → the biggest grade = the smallest i with
        // i%3==2 → i=2 (grade 998, id 0x32)
        assert(out[1] == 0x32
            && "the REAL sort: top entry first");
        assert(out[2] == 998);
        // the second call: the flag skips the sort
        assert(r.sorted == 1);
        int32_t out2[40] = { 0 };
        int cnt2 = MeedGetRecord(&r, 0x99, out2,
                                2, 0, 8);
        assert(cnt2 == 8
            && memcmp(out, out2, sizeof(out)) == 0);
        printf("D50-5 the D49 integration ok\n");
    }

    printf(
      "SYNDICATE-D50-OK: the REAL introsort family"
      " (141779790 driver + 141778b60 partition"
      " goto-faithful + 141778a20 insertion + the"
      " heap 141778760/141778d90/141778f80 + the"
      " guess 1417788c0/1417786d0 + the comparator"
      " 1417781b0 with the verbatim equal→TRUE"
      " tail); the seam g_fnMeedSortRaw now"
      " defaults to the REAL family — GetMeedRecord"
      " sorts for real; all size bands + heap"
      " fallback + permutation preservation green\n");
    return 0;
}

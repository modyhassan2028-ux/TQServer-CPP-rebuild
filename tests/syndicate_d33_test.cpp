// ============================================================
// syndicate_d33_test — the league member-list SORT family
// (T7/D33): introsort 14174cb10 + insertion 141747090 +
// partition 141747c80 + median 141746f30/141746310 +
// make_heap 141747ec0 + sift 1417463a0/141745480 +
// sort_heap 141748e30.
// The comparator seam g_fnLeagueCmp binds a stub with the
// ba4c0 STRUCTURE (a rank table lookup + the id tie-break);
// the real comparator subgraph is the D34 family.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <algorithm>
#include "../modules/syndicate/src/SyndicateLeagueSort.h"

using namespace syndicate;

// ---- the comparator stub (the D34 ba4c0 shape) ----
static std::vector<uint32_t> g_vRank;   // rankOf[id] (0 = missing)
static bool StubCmp(int* pState, uint32_t uA, uint32_t uB) {
    // simplified total order preserving the ba4c0 branch shape:
    // missing-a → false; rank-by-table; id tie-break
    if (uA >= g_vRank.size() || g_vRank[uA] == 0) return false;   // a not found
    uint32_t rA = g_vRank[uA];
    if (uB >= g_vRank.size() || g_vRank[uB] == 0) return true;    // b not found → true
    uint32_t rB = g_vRank[uB];
    if (rA != rB) return rA < rB;
    return uA < uB;   // the id tie-break (strict)
}
static void BindCmp() { g_fnLeagueCmp = StubCmp; }

static bool IsSortedBy(const std::vector<uint32_t>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (StubCmp(nullptr, v[i], v[i - 1])) return false;
    }
    return true;
}
static bool SameBag(const std::vector<uint32_t>& a, const std::vector<uint32_t>& b) {
    std::vector<uint32_t> x = a, y = b;
    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());
    return x == y;
}
static uint64_t s_calls = 0;
static uint64_t Calls() { return s_calls; }

static void SortIt(std::vector<uint32_t>& v, int64_t nDepth) {
    LeagueSortIntro(v.data(), v.data() + v.size(), nDepth, 7);
}

int main() {
    BindCmp();

    // ================= D33-1: the 3-element net =================
    {
        std::vector<uint32_t> r(97);
        for (uint32_t i = 0; i < 97; i++) r[i] = 1 + (i % 96);   // ranks 1..96
        g_vRank = r;
        struct { uint32_t a, b, c; } cases[] = {
            {1, 2, 3}, {3, 2, 1}, {2, 2, 2}, {5, 5, 1}, {96, 1, 96}, {7, 7, 3},
        };
        for (auto& cs : cases) {
            std::vector<uint32_t> v = {cs.a, cs.b, cs.c};
            LeagueSortOrder3(&v[0], &v[1], &v[2], 7);
            assert(IsSortedBy(v));
            std::vector<uint32_t> orig = {cs.a, cs.b, cs.c};
            assert(SameBag(v, orig));
        }
        printf("D33-1 order3 net ok\n");
    }

    // ================= D33-2: the insertion sort =================
    {
        g_vRank.assign(200, 0);
        for (uint32_t i = 1; i <= 150; i++) g_vRank[i] = 1 + (i * 37 % 90);
        for (size_t n = 0; n <= 33; n++) {
            std::vector<uint32_t> v(n);
            for (size_t i = 0; i < n; i++) v[i] = 1 + (uint32_t)((i * 53 + n * 11) % 150);
            std::vector<uint32_t> orig = v;
            LeagueSortInsertion(v.data(), v.data() + v.size(), 3);
            assert(IsSortedBy(v));
            assert(SameBag(v, orig));
        }
        printf("D33-2 insertion sort ok (sizes 0..33)\n");
    }

    // ================= D33-3: the introsort, quick paths =================
    {
        size_t sizes[] = {0, 1, 2, 3, 32, 33, 34, 40, 41, 64, 100, 333, 1000};
        for (size_t n : sizes) {
            std::vector<uint32_t> v(n);
            uint32_t seed = (uint32_t)n + 1;
            for (size_t i = 0; i < n; i++) {
                seed = seed * 1103515245 + 12345;
                v[i] = 1 + (seed >> 17) % 150;
            }
            std::vector<uint32_t> orig = v;
            SortIt(v, 4000);   // deep depth → quicksort all the way
            assert(IsSortedBy(v));
            assert(SameBag(v, orig));
        }
        printf("D33-3 introsort quick paths ok (13 sizes)\n");
    }

    // ================= D33-4: the heap fallback path =================
    {
        for (size_t n : {33u, 40u, 41u, 100u, 777u}) {
            std::vector<uint32_t> v(n);
            uint32_t seed = (uint32_t)n * 7 + 3;
            for (size_t i = 0; i < n; i++) {
                seed = seed * 1103515245 + 12345;
                v[i] = 1 + (seed >> 17) % 150;
            }
            std::vector<uint32_t> orig = v;
            SortIt(v, 0);   // depth 0 → make_heap + sort_heap (>32)
            assert(IsSortedBy(v));
            assert(SameBag(v, orig));
        }
        printf("D33-4 heap fallback path ok\n");
    }

    // ================= D33-5: heavy duplicates (rank ties) =================
    {
        g_vRank.assign(50, 0);
        for (uint32_t i = 1; i <= 40; i++) g_vRank[i] = 1 + (i % 3);   // 3 ranks only
        std::vector<uint32_t> v(500);
        uint32_t seed = 99;
        for (size_t i = 0; i < v.size(); i++) {
            seed = seed * 1103515245 + 12345;
            v[i] = 1 + (seed >> 17) % 40;
        }
        std::vector<uint32_t> orig = v;
        for (int64_t d : {0, 1, 2, 4000}) {
            std::vector<uint32_t> w = v;
            SortIt(w, d);
            assert(IsSortedBy(w));
            assert(SameBag(w, orig));
        }
        printf("D33-5 heavy-rank-ties ok (4 depth modes)\n");
    }

    // ================= D33-6: adversarial patterns =================
    {
        // sawtooth / organ / reverse / all-equal at 0x21 boundaries
        size_t n = 32;
        std::vector<std::vector<uint32_t>> pats;
        pats.push_back(std::vector<uint32_t>(n));       // zeros
        pats.push_back(std::vector<uint32_t>(n));       // reverse
        pats.push_back(std::vector<uint32_t>(n));       // organ
        pats.push_back(std::vector<uint32_t>(n));       // sawtooth
        pats.push_back(std::vector<uint32_t>(2 * n));   // big sawtooth
        for (size_t i = 0; i < n; i++) {
            pats[0][i] = 5;
            pats[1][i] = (uint32_t)(n - i);
            pats[2][i] = (uint32_t)(i < n / 2 ? i * 2 + 1 : (n - i) * 2);
            pats[3][i] = (uint32_t)(i % 7) + 1;
        }
        for (size_t i = 0; i < 2 * n; i++) pats[4][i] = (uint32_t)(i % 13) + 1;
        for (auto& v : pats) {
            std::vector<uint32_t> orig = v;
            for (int64_t d : {0, 4000}) {
                std::vector<uint32_t> w = v;
                SortIt(w, d);
                assert(IsSortedBy(w));
                assert(SameBag(w, orig));
            }
        }
        printf("D33-6 adversarial patterns ok\n");
    }

    // restore a plain rank table for the record
    printf("SYNDICATE-D33-OK: the league member-list SORT family complete — "
           "introsort 14174cb10 (the 0x21 gate + the depth-exhausted heap "
           "fallback + the median partition), insertion 141747090 (the "
           "end-gallop memmove + the shift loop), partition 141747c80 (the "
           "sentinel walks + the 5-region tail), median nets 141746f30/141746310 "
           "(the 9-sample path at >=0x29 spans), make_heap 141747ec0 (the Floyd "
           "loop), sift-down 1417463a0 (the child pick + the odd-last tail), "
           "push-hole 141745480 (the state home recovered from the Ghidra "
           "stack-slot artifact), sort_heap 141748e30\n");
    return 0;
}

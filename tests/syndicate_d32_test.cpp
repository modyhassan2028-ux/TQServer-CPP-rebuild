// syndicate_d32_test — the CLeague member set-tree
// (the 0x30-node family): ctor + insert/find/erase/
// erase-range/clear/dtor, all real, with the full
// red-black validation.
#include "../modules/syndicate/src/SyndicateLeagueTree.h"
#include "../modules/syndicate/src/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace syndicate;

static std::vector<void*> g_vFreed;
static int g_nInvalid = 0;

static void Bind() {
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_fnMeritInvalid = []() { ++g_nInvalid; };
}

static char s_map[0x40];

static char* PAnchor() { return *(char**)s_map; }
static char* PHead() {
    return *(char**)(s_map + 0x30); }

static bool NNil(char* n) {
    return *(uint8_t*)(n + 0x29) != 0; }
static uint32_t NK(char* n) {
    return *(uint32_t*)(n + 0x18); }

static void BuildMap() {
    memset(s_map, 0, sizeof s_map);
    LeagueMemberCtor(s_map);
}

static void InsertKey(uint32_t uKey) {
    uint32_t kv[4] = { uKey, 0, 0, 0 };
    char* pHead = PHead();
    char* plVar6 = pHead;
    bool bWentLeft = true;
    if (!NNil(*(char**)(pHead + 8))) {
        char* plVar5 = *(char**)(pHead + 8);
        do {
            plVar6 = plVar5;
            bWentLeft = uKey < NK(plVar5);
            plVar5 = bWentLeft
                ? *(char**)plVar5
                : *(char**)(plVar5 + 0x10);
        } while (!NNil(plVar5));
    }
    char out[2][8];
    LeagueInsert(s_map, out[0],
        bWentLeft ? 1 : 0, plVar6, kv);
}

static std::vector<uint32_t> Walk() {
    std::vector<uint32_t> v;
    char* n = *(char**)PHead();   // the first
    while (!NNil(n)) {
        v.push_back(NK(n));
        char it[2][8];
        *(char**)it[0] = PAnchor();
        *(char**)(it[0] + 8) = n;
        LeagueIterNext(it[0]);
        n = *(char**)(it[0] + 8);
    }
    return v;
}

// the full red-black validation (root black,
// no red-red, equal black heights) — returns the
// black height
static int g_nLeaves = -1;
static size_t ValidateRB(char* n, int hBlack) {
    if (NNil(n)) {
        if (g_nLeaves < 0) g_nLeaves = hBlack;
        assert(g_nLeaves == hBlack);
        return 0;
    }
    assert(*(uint8_t*)(n + 0x28) <= 1);   // 0/1
    if (*(uint8_t*)(n + 0x28) == 0) {      // red
        assert(*(uint8_t*)(*(char**)n + 0x28)
            != 0);   // no red-red
        assert(*(uint8_t*)(*(char**)(n + 0x10)
            + 0x28) != 0);
    }
    int h2 = hBlack + *(uint8_t*)(n + 0x28);
    size_t l = ValidateRB(*(char**)n, h2);
    size_t r = ValidateRB(*(char**)(n + 0x10), h2);
    (void)l; (void)r;
    return 0;
}

static void CheckTree(size_t nExpectSize) {
    assert(*(uint64_t*)(s_map + 0x38)
        == nExpectSize);
    char* root = *(char**)(PHead() + 8);
    if (nExpectSize) {
        assert(*(uint8_t*)(root + 0x28) == 1);
    }
    g_nLeaves = -1;
    ValidateRB(root, 0);
    auto v = Walk();
    assert(v.size() == nExpectSize);
    if (nExpectSize) {
        assert(NK(*(char**)PHead()) == v.front());
        assert(NK(*(char**)(PHead() + 0x10))
            == v.back());
    } else {
        assert(*(char**)PHead() == PHead());
    }
    for (size_t i = 1; i < v.size(); ++i) {
        assert(v[i] > v[i - 1]);
    }
}

int main() {
    Bind();
    // ---- 1. the ctor + 15 inserts ----
    {
        BuildMap();
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        CheckTree(15);
        puts("D32-1 ctor+inserts ok");
    }
    // ---- 2. find + iter++ ----
    {
        for (uint32_t k = 1; k <= 15; ++k) {
            char out[2][8];
            LeagueFind(s_map, out[0], &k);
            char* n = *(char**)(out[0] + 8);
            assert(!NNil(n));
            assert(NK(n) == k);
        }
        uint32_t kAbs = 100;
        char out[2][8];
        LeagueFind(s_map, out[0], &kAbs);
        assert(NNil(*(char**)(out[0] + 8)));
        puts("D32-2 find ok");
    }
    // ---- 3. mixed-order single erases ----
    {
        uint32_t order[] = { 8, 1, 15, 4, 12, 2,
            7, 13, 3, 14, 5, 11, 6, 10, 9 };
        size_t n = 15;
        for (uint32_t k : order) {
            size_t nBefore = g_vFreed.size();
            char out[2][8];
            LeagueFind(s_map, out[0], &k);
            char* node = *(char**)(out[0] + 8);
            assert(!NNil(node));
            char it[2][8];
            *(char**)it[0] = PAnchor();
            *(char**)(it[0] + 8) = node;
            char outE[2][8];
            LeagueErase(s_map, outE[0], it[0]);
            --n;
            CheckTree(n);
            assert(g_vFreed.size() == nBefore + 1);
        }
        puts("D32-3 single erases ok");
    }
    // ---- 4. erase-range [4, 8) ----
    {
        BuildMap();
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        uint32_t k4 = 4, k8 = 8;
        char it4[2][8], it8[2][8];
        *(char**)it4[0] = PAnchor();
        *(char**)it8[0] = PAnchor();
        LeagueFind(s_map, it4[0], &k4);
        LeagueFind(s_map, it8[0], &k8);
        char out[2][8];
        size_t nBefore = g_vFreed.size();
        LeagueEraseRange(s_map, out[0],
            it4[0], it8[0]);
        CheckTree(11);
        assert(g_vFreed.size() == nBefore + 4);
        auto v = Walk();
        for (uint32_t x : v) {
            assert(x < 4 || x >= 8);
        }
        puts("D32-4 erase range ok");
    }
    // ---- 5. the clear + reinsert ----
    {
        size_t nBefore = g_vFreed.size();
        LeagueClear(s_map);
        CheckTree(0);
        assert(g_vFreed.size() == nBefore + 11);
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        CheckTree(15);
        puts("D32-5 clear+reinsert ok");
    }
    // ---- 6. the member dtor ----
    {
        size_t nBefore = g_vFreed.size();
        LeagueMemberDtor(s_map);
        assert(*(char**)(s_map + 0x30) == nullptr);
        assert(*(uint64_t*)(s_map + 0x38) == 0);
        assert(g_vFreed.size()
            == nBefore + 15 /*nodes*/ + 1 /*head*/);
        puts("D32-6 member dtor ok");
    }
    puts("SYNDICATE-D32-OK: the CLeague member "
        "set-tree (0x30) family complete — ctor "
        "(c4b0: anchor + isnil=1 head + self-links), "
        "node/head allocs (746790/746a60: the "
        "16-byte key + color@0x28/isnil@0x29), find "
        "(749fc0: lower_bound + end), insert (748820: "
        "the 0xffffffffffffffd gate + the verbatim "
        "rebalance), iter++ (7447d0: leftmost/climb "
        "+ out_of_range tail), erase (749c00: splice "
        "incl. succ==right-child + unlink + the "
        "carried-parent rebalance), erase-range "
        "(74a150: owner checks + both-end clear + "
        "advance loop), clear (747270 + 746650), "
        "rotations (744560/745ad0), member dtor "
        "(c530: [first,head) + the head delete)");
    return 0;
}

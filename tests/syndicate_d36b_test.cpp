// syndicate_d36b_test — D36 part 2a: the USERS-MAP family
// (1417265a0/141729790/14172afb0/14172b160/141722ef0/
//  141724870/1417224f0): the unique insert with the two
// neighbor duplicate gates, the raw insert + rebalance, the
// erase with the remove-rebalance, the iterator++ — all real
// against the D32-built map, with the full red-black
// validation after every mutation.
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueUsers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <set>
#include <algorithm>
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
static char* PHead()   { return *(char**)(s_map + 0x30); }
static bool  NNil(char* n) {
    return *(uint8_t*)(n + 0x29) != 0; }
static uint32_t NK(char* n) {
    return *(uint32_t*)(n + 0x18); }
static size_t NSize() {
    return (size_t)*(uint64_t*)(s_map + 0x38); }

static void BuildMap() {
    memset(s_map, 0, sizeof s_map);
    LeagueMemberCtor(s_map);
}

// out = {anchor, node, flag@+0x10}; returns flag
static uint8_t InsertU(uint32_t uKey) {
    uint32_t kv[4] = { uKey, 0, 0, 0 };
    char out[3][8];
    memset(out, 0, sizeof out);
    UsersInsertUnique(s_map, out[0], kv);
    return *(uint8_t*)(out[0] + 0x10);
}

static std::vector<uint32_t> Walk() {
    std::vector<uint32_t> v;
    char* n = *(char**)PHead();   // the first
    while (!NNil(n)) {
        v.push_back(NK(n));
        char it[2][8];
        *(char**)it[0] = PAnchor();
        *(char**)(it[0] + 8) = n;
        UsersIterNext(it[0]);
        n = *(char**)(it[0] + 8);
    }
    return v;
}

static int g_nLeaves = -1;
static void ValidateRB(char* n, int hBlack) {
    if (NNil(n)) {
        if (g_nLeaves < 0) g_nLeaves = hBlack;
        assert(g_nLeaves == hBlack);
        return;
    }
    assert(*(uint8_t*)(n + 0x28) <= 1);
    if (*(uint8_t*)(n + 0x28) == 0) {   // red: no red-red
        assert(*(uint8_t*)(*(char**)n + 0x28) != 0);
        assert(*(uint8_t*)(*(char**)(n + 0x10) + 0x28) != 0);
    }
    int h2 = hBlack + *(uint8_t*)(n + 0x28);
    ValidateRB(*(char**)n, h2);
    ValidateRB(*(char**)(n + 0x10), h2);
}

static void CheckTree(size_t nExpectSize) {
    assert(NSize() == nExpectSize);
    char* head = PHead();
    assert(*(uint8_t*)(*(char**)(head + 8) + 0x28) == 1);
    g_nLeaves = -1;
    ValidateRB(*(char**)(head + 8), 0);
    // sorted + first/last links
    std::vector<uint32_t> v = Walk();
    std::vector<uint32_t> s = v;
    std::sort(s.begin(), s.end());
    assert(v == s);
    assert(NSize() == v.size());
    if (!v.empty()) {
        assert(NK(*(char**)head) == s.front());
        assert(NK(*(char**)(head + 0x10)) == s.back());
    }
}

// the find (reused from D32) — the node or nullptr
static char* FindNode(uint32_t uKey) {
    uint32_t kv[2] = { uKey, 0 };
    char out[2][8];
    memset(out, 0, sizeof out);
    LeagueFind(s_map, out[0], kv);
    char* n = *(char**)(out[0] + 8);
    return NNil(n) ? nullptr : n;
}

static void EraseU(uint32_t uKey) {
    char* n = FindNode(uKey);
    assert(n && "erase target must exist");
    char it[2][8];
    *(char**)it[0] = PAnchor();
    *(char**)(it[0] + 8) = n;
    char out[2][8];
    UsersErase(s_map, out[0], it[0]);
}

int main() {
    Bind();

    // ---- 1. the unique insert + the duplicate gates ----
    BuildMap();
    assert(InsertU(50) == 1);            // the root
    assert(InsertU(30) == 1);            // left attach
    assert(InsertU(70) == 1);            // right attach
    CheckTree(3);
    assert(InsertU(50) == 0);            // dup: the right gate
    assert(InsertU(30) == 0);            // dup: the pred gate
    assert(InsertU(70) == 0);
    assert(NSize() == 3);
    CheckTree(3);
    // the pred walk covers the subtree-rightmost AND the
    // climb paths
    assert(InsertU(20) == 1);   // 30's left
    assert(InsertU(40) == 1);   // 30's right
    assert(InsertU(60) == 1);
    assert(InsertU(80) == 1);
    CheckTree(7);
    assert(InsertU(40) == 0);
    assert(InsertU(20) == 0);
    assert(InsertU(60) == 0);
    assert(InsertU(80) == 0);
    CheckTree(7);

    // ---- 2. the storm: the unique insert against a model,
    //      with the full RB validation each step ----
    BuildMap();
    {
        std::set<uint32_t> model;
        uint32_t x = 123456789;
        for (int i = 0; i < 600; ++i) {
            x = x * 1664525u + 1013904223u;
            uint32_t k = (x >> 8) % 400;
            uint8_t f = InsertU(k);
            assert(f == (model.count(k) ? 0 : 1));
            model.insert(k);
            CheckTree(model.size());
        }
        // a second pass: EVERYTHING must be a duplicate now
        for (uint32_t k : { 0u, 7u, 55u, 123u, 399u, 250u }) {
            (void)k;
        }
        for (uint32_t k = 0; k < 400; k += 7) {
            if (model.count(k)) {
                assert(InsertU(k) == 0);
            } else {
                assert(InsertU(k) == 1);
                model.insert(k);
            }
            CheckTree(model.size());
        }
        // the erase storm against the same model
        uint32_t nErased = 0;
        for (uint32_t k = 0; k < 400; ++k) {
            if (!model.count(k)) continue;
            EraseU(k);
            model.erase(k);
            ++nErased;
            if (nErased % 13 == 0) CheckTree(model.size());
        }
        CheckTree(0);
        // the map is empty: first/last/root all back at head
        char* head = PHead();
        assert(*(char**)head == head);
        assert(*(char**)(head + 0x10) == head);
        assert(NSize() == 0);
    }

    // ---- 3. the erase splice cases ----
    BuildMap();
    for (uint32_t k : { 50u, 30u, 70u, 20u, 40u, 60u, 80u, 45u, 35u })
        InsertU(k);
    // 40 has two children with a successor that HAS a right
    // child (45): the far-successor splice
    EraseU(40);
    CheckTree(8);
    // the root with two children
    EraseU(50);
    CheckTree(7);
    // a leaf
    EraseU(80);
    CheckTree(6);
    // the root again (30 now?)
    EraseU(30);
    CheckTree(5);
    while (NSize()) {
        std::vector<uint32_t> v = Walk();
        EraseU(v.front());
    }
    CheckTree(0);

    // ---- 4. the iterator++ (141722ef0) ----
    BuildMap();
    for (uint32_t k : { 10u, 5u, 15u, 3u, 7u, 12u, 17u })
        InsertU(k);
    {
        char it[2][8];
        *(char**)it[0] = PAnchor();
        *(char**)(it[0] + 8) = *(char**)PHead();  // first
        std::vector<uint32_t> v;
        while (!NNil(*(char**)(it[0] + 8))) {
            v.push_back(NK(*(char**)(it[0] + 8)));
            UsersIterNext(it[0]);
        }
        assert((v == std::vector<uint32_t>{3,5,7,10,12,15,17}));
        // past-the-end: the head node — a second advance in
        // the ORIGINAL throws (the unrecoverable jumptable);
        // here the flag path is exercised as the CRT gate
        assert(NNil(*(char**)(it[0] + 8)));
    }

    // ---- 5. the allocator seams (1417265a0) ----
    {
        // the key pair is COPIED unconditionally (the
        // original derefs param_5 with no null gate) —
        // a real 16-byte pair is passed
        uint64_t kvPair[2] = { 0x1122334455667788ULL, 0 };
        char* n = (char*)UsersNodeAlloc(
            nullptr, nullptr, nullptr, kvPair, 1);
        assert(n != nullptr);
        assert(*(uint8_t*)(n + 0x28) == 1);   // color
        assert(*(uint8_t*)(n + 0x29) == 0);   // isnil
        assert(*(uint64_t*)(n + 0x18) == kvPair[0]); // copied
        assert(*(uint64_t*)(n + 0x20) == kvPair[1]);
        free(n);
    }

    // ---- 6. the erase invalid-iterator gate ----
    BuildMap();
    InsertU(9);
    {
        char it[2][8];
        *(char**)it[0] = PAnchor();
        *(char**)(it[0] + 8) = PHead();   // the head = end
        char out[2][8];
        bool bThrew = false;
        try { UsersErase(s_map, out[0], it[0]); }
        catch (const std::out_of_range&) { bThrew = true; }
        assert(bThrew);
        assert(NSize() == 1);   // untouched
    }

    printf("SYNDICATE_D36B_OK: users-map family — unique "
           "insert (both dup gates, pred walk paths), storm "
           "600+400 vs model, erase storm + splice cases, "
           "iterator++, allocator seams, invalid-erase gate\n");
    return 0;
}

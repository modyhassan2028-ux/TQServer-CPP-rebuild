// syndicate_d36c_test — D36 part 2b: the MEMBERS-MAP family
// (0x3d nodes: the 9-u32 value record, color@+0x3c,
//  isnil@+0x3d) + the tokens-map unique insert
// (141749a50): ctor, raw insert + rebalance, unique insert
// (both dup gates), equal_range, iterator++, erase /
// erase-range / erase(key) with the count, clear — all
// storm-tested with the full red-black validation.
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueUsers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMembers.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMember.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>

using namespace syndicate;

static std::vector<void*> g_vFreed;
static int g_nInvalid = 0;
static void Bind() {
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_fnMeritInvalid = []() { ++g_nInvalid; };
}

// ---- the members map (0x3d nodes) ----
static char s_map[0x40];
static char* PAnchor() { return *(char**)s_map; }
static char* PHead()   { return *(char**)(s_map + 0x30); }
static bool  NNil(char* n) {
    return *(uint8_t*)(n + 0x3d) != 0; }
static uint32_t NK(char* n) {
    return *(uint32_t*)(n + 0x18); }
static size_t NSize() {
    return (size_t)*(uint64_t*)(s_map + 0x38); }

static void BuildMap() {
    memset(s_map, 0, sizeof s_map);
    MembersMapCtor(s_map);
    // the anchor: the CLeague ctor owns this slot in the
    // original — the test allocates the standalone anchor
    char* anchor = (char*)malloc(8);
    *(char**)anchor = s_map;   // the owner back-ref
    *(char**)s_map = anchor;
}

static std::vector<uint32_t> Walk() {
    std::vector<uint32_t> v;
    char* n = *(char**)PHead();
    while (!NNil(n)) {
        v.push_back(NK(n));
        char it[2][8];
        *(char**)it[0] = PAnchor();
        *(char**)(it[0] + 8) = n;
        MembersIterNext(it[0]);
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
    assert(*(uint8_t*)(n + 0x3c) <= 1);
    if (*(uint8_t*)(n + 0x3c) == 0) {
        assert(*(uint8_t*)(*(char**)n + 0x3c) != 0);
        assert(*(uint8_t*)(*(char**)(n + 0x10) + 0x3c) != 0);
    }
    int h2 = hBlack + *(uint8_t*)(n + 0x3c);
    ValidateRB(*(char**)n, h2);
    ValidateRB(*(char**)(n + 0x10), h2);
}

static void CheckTree(size_t nExpectSize) {
    assert(NSize() == nExpectSize);
    char* head = PHead();
    assert(*(uint8_t*)(*(char**)(head + 8) + 0x3c) == 1);
    g_nLeaves = -1;
    ValidateRB(*(char**)(head + 8), 0);
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

static uint8_t InsertU(uint32_t uKey) {
    // kv[0] IS the key (the compare reads the record's
    // first u32 at node+0x18); kv[1..8] the payload
    uint32_t kv[9];
    kv[0] = uKey;
    for (int i = 1; i < 9; ++i) kv[i] = uKey * 10 + i;
    char out[3][8];
    memset(out, 0, sizeof out);
    MembersInsertUnique(s_map, out[0], kv);
    // the value record must have landed whole
    if (*(uint8_t*)(out[0] + 0x10)) {
        char* n = *(char**)(out[0] + 8);
        for (int i = 0; i < 9; ++i)
            assert(*(uint32_t*)(n + 0x18 + 4*i)
                   == kv[i]);
    }
    return *(uint8_t*)(out[0] + 0x10);
}

static void EraseU(uint32_t uKey) {
    // erase(key) with the count (MSVC map::erase(key))
    uint32_t k = uKey;
    uint64_t n = MembersEraseKey(s_map, &k);
    assert(n == 1);
}

int main() {
    Bind();

    // ---- 1. the ctor + the unique insert + dup gates ----
    BuildMap();
    assert(InsertU(50) == 1);
    assert(InsertU(30) == 1);
    assert(InsertU(70) == 1);
    CheckTree(3);
    assert(InsertU(50) == 0);
    assert(InsertU(30) == 0);
    assert(InsertU(70) == 0);
    CheckTree(3);
    assert(InsertU(20) == 1 && InsertU(40) == 1);
    assert(InsertU(60) == 1 && InsertU(80) == 1);
    CheckTree(7);
    assert(InsertU(40) == 0);

    // ---- 2. the storm 600+400 vs a model ----
    BuildMap();
    {
        std::set<uint32_t> model;
        uint32_t x = 777777777;
        for (int i = 0; i < 600; ++i) {
            x = x * 1664525u + 1013904223u;
            uint32_t k = (x >> 8) % 400;
            uint8_t f = InsertU(k);
            assert(f == (model.count(k) ? 0 : 1));
            model.insert(k);
            if (i % 7 == 0) CheckTree(model.size());
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
        // the equal_range: [first,last) over a present key
        {
            uint32_t k = 399;
            // the range home: {anchor, first, anchor, last}
            int64_t rg[4];
            MembersEqualRange(s_map, rg, &k);
            assert((char*)rg[0] == PAnchor());
            assert((char*)rg[2] == PAnchor());
            char* pFirst = (char*)rg[1];
            char* pLast  = (char*)rg[3];
            assert(!NNil(pFirst) && NK(pFirst) == 399);
            // unique map: first == the node, last == the
            // successor (or head when it is the max)
            char it[2][8];
            *(char**)it[0] = PAnchor();
            *(char**)(it[0] + 8) = pFirst;
            MembersIterNext(it[0]);
            assert(*(char**)(it[0] + 8) == pLast);
        }
        // the erase storm via erase(key)
        uint32_t nErased = 0;
        for (uint32_t k = 0; k < 400; ++k) {
            if (!model.count(k)) continue;
            EraseU(k);
            model.erase(k);
            ++nErased;
            if (nErased % 11 == 0) CheckTree(model.size());
        }
        CheckTree(0);
        char* head = PHead();
        assert(*(char**)head == head);
        assert(*(char**)(head + 0x10) == head);
        assert(NSize() == 0);
    }

    // ---- 3. the erase(key) count on a missing key ----
    BuildMap();
    InsertU(10);
    {
        uint32_t k = 999;
        assert(MembersEraseKey(s_map, &k) == 0);
        k = 10;
        assert(MembersEraseKey(s_map, &k) == 1);
        assert(NSize() == 0);
    }

    // ---- 4. the splice cases ----
    BuildMap();
    for (uint32_t k : {50u,30u,70u,20u,40u,60u,80u,45u,35u})
        assert(InsertU(k) == 1);
    EraseU(40);   // the far-successor splice
    CheckTree(8);
    EraseU(50);   // the root with two children
    CheckTree(7);
    EraseU(80);   // a leaf
    CheckTree(6);
    while (NSize()) { std::vector<uint32_t> v = Walk(); EraseU(v.front()); }
    CheckTree(0);

    // ---- 5. the clear ----
    BuildMap();
    for (uint32_t k = 0; k < 100; k += 3) InsertU(k);
    CheckTree(34);
    MembersClear(s_map);
    assert(NSize() == 0);
    char* head = PHead();
    assert(*(char**)head == head);
    assert(*(char**)(head + 0x10) == head);

    // ---- 6. the tokens-map unique insert (141749a50) ----
    // (0x29 nodes; the raw insert callee = the D32 insert)
    char tmap[0x40];
    memset(tmap, 0, sizeof tmap);
    LeagueMemberCtor(tmap);
    {
        auto TInsU = [&](uint32_t k) -> uint8_t {
            uint32_t kv[2] = { k, k * 7 };
            char out[3][8];
            memset(out, 0, sizeof out);
            TokensInsertUnique(tmap, out[0], kv);
            return *(uint8_t*)(out[0] + 0x10);
        };
        assert(TInsU(100) == 1);
        assert(TInsU(50) == 1);
        assert(TInsU(150) == 1);
        assert(TInsU(100) == 0);
        assert(TInsU(50) == 0);
        assert(TInsU(150) == 0);
        assert(TInsU(25) == 1 && TInsU(75) == 1);
        assert(TInsU(125) == 1 && TInsU(175) == 1);
        assert(TInsU(75) == 0);
        assert((uint64_t)*(uint64_t*)(tmap + 0x38) == 7);
        // storm the tokens map too (seeded with the
        // seven manual inserts above)
        std::set<uint32_t> model;
        for (uint32_t k : {100u,50u,150u,25u,75u,
                           125u,175u}) model.insert(k);
        uint32_t x = 31313131;
        for (int i = 0; i < 500; ++i) {
            x = x * 1664525u + 1013904223u;
            uint32_t k = (x >> 8) % 300;
            uint8_t f = TInsU(k);
            assert(f == (model.count(k) ? 0 : 1));
            model.insert(k);
        }
        assert((uint64_t)*(uint64_t*)(tmap + 0x38)
               == model.size());
    }

    printf("SYNDICATE_D36C_OK: members-map family (0x3d) — "
           "ctor, unique insert (dup gates + 9-u32 value "
           "record), storm 600+400 RB-checked, equal_range "
           "[first,last), erase(key) count + storm, splice "
           "cases, clear, and the tokens-map insert 141749a50 "
           "(d32-callee) with its own storm\n");
    return 0;
}

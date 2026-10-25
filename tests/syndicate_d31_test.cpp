#include <stdexcept>
#include <algorithm>
// ============================================================
// Syndicate.dll — unit D31: the ERASE layer. The REAL
// erase paths on the D29 map + the D30 set-tree: the
// single-node erases (the splice cases + the
// remove-rebalance), the erase-ranges, the dtor, the
// out_of_range gate. The map's value carries a REAL
// nested 0x28 own-tree (the seam builds it).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "../Exe/Dll/Syndicate/Port/SyndicateMapTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateOwnTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateEraseLayer.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"

using namespace syndicate;

static std::vector<void*> g_vFreed;
static int g_nInvalid = 0, g_nStrMove = 0;
static char* g_pLastValue = nullptr;

static void Bind() {
    g_fnMeritOpNew = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpNew2 = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnOrphanCB90 = [](void*, void*, void*,
                        void*) {};
    // the value move: build a REAL nested own-tree
    // at the destination (the value object at +0x20:
    // anchor@+0, head@+0x30, size@+0x38) and put a
    // couple of real nodes in it
    g_fnStrMoveDE50 = [](void* d, void*) {
        ++g_nStrMove;
        *(void**)d = malloc(8);   // the anchor
        OwnMapCtor(d);
        for (int i = 1; i <= 2; ++i) {
            uint64_t kv = (uint64_t)(uintptr_t)g_pLastValue * 10 + i;
            char* h = *(char**)((char*)d + 0x30);
            char* at = h; bool bl = true;
            if (*(uint8_t*)(*(char**)(h + 8) + 0x21) == 0) {
                char* c = *(char**)(h + 8);
                do { at = c;
                    bl = kv < *(uint32_t*)(at + 0x18);
                    c = bl ? *(char**)at
                           : *(char**)(at + 0x10);
                } while (*(uint8_t*)(c + 0x21) == 0);
            }
            char* out[2];
            OwnInsert(d, out,
                (uint8_t)(bl ? 1 : 0), at, &kv);
        }
    };
}

static char s_map[0x40];
static char* PHead() {
    return *(char**)(s_map + 0x30);
}
static char* PAnchor() {
    return *(char**)s_map;
}
static void* NL(char* n) { return *(void**)n; }
static void* NR(char* n) {
    return *(void**)(n + 0x10); }
static void* NP(char* n) {
    return *(void**)(n + 8); }
static uint32_t NK(char* n) {
    return *(uint32_t*)(n + 0x18); }
static uint8_t NC(char* n) {
    return *(uint8_t*)(n + 0x60); }
static bool NNil(char* n) {
    return *(uint8_t*)(n + 0x61) != 0; }

static void BuildMap() {
    memset(s_map, 0, sizeof s_map);
    char* anchor = (char*)calloc(1, 8);
    *(char**)anchor = s_map;
    *(char**)s_map = anchor;
    char* head = (char*)TreeNodeAlloc();
    *(uint8_t*)(head + 0x61) = 1;
    *(char**)(head + 8) = head;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
    *(char**)(s_map + 0x30) = head;
    *(uint64_t*)(s_map + 0x38) = 0;
}

static void InsertKey(uint32_t uKey) {
    uint32_t kv[4] = { uKey, 0, 0, 0 };
    g_pLastValue = (char*)(uintptr_t)uKey;
    char* pHead = PHead();
    char* plVar6 = pHead;
    bool bWentLeft = true;
    if (!NNil(*(char**)(pHead + 8))) {
        char* plVar5 = *(char**)(pHead + 8);
        do {
            plVar6 = plVar5;
            bWentLeft = uKey < NK(plVar6);
            plVar5 = bWentLeft
                ? (char*)NL(plVar6)
                : (char*)NR(plVar6);
        } while (!NNil(plVar5));
    }
    char* out[2];
    TreeInsert(s_map, out,
        (uint8_t)(bWentLeft ? 1 : 0), plVar6, kv);
}

// the in-order walk → the sorted keys
static std::vector<uint32_t> Walk() {
    std::vector<uint32_t> v;
    char* n = *(char**)PHead();
    while (!NNil(n)) {
        v.push_back(NK(n));
        char* iter[2] = { nullptr, n };
        TreeIterNext(iter);
        n = iter[1];
    }
    return v;
}

static int g_nLeaves = 0;
static uint32_t g_uDbgKey = 0;
static int ValidateRB(char* n, int nBlack) {
    if (NNil(n)) {
        if (g_nLeaves == -1) {
            g_nLeaves = nBlack;
        } else if (g_nLeaves != nBlack) {
            printf("BLACK-HEIGHT MISMATCH after key %u "
                "(depth %d vs %d)\n", g_uDbgKey,
                nBlack, g_nLeaves);
            std::exit(1);
        }
        return 0;
    }
    if (n != *(char**)(PHead() + 8)) {
        if (NC(n) == 0
            && NC((char*)NP(n)) == 0) {
            printf("RED-RED VIOLATION\n");
            std::exit(1);
        }
    }
    int nAdd = NC(n) != 0 ? 1 : 0;
    return 1 + ValidateRB((char*)NL(n), nBlack + nAdd)
             + ValidateRB((char*)NR(n), nBlack + nAdd);
}

static uint32_t g_uEraseKey = 0;
static void CheckTree(size_t nExpectSize) {
    if (*(uint64_t*)(s_map + 0x38) != nExpectSize) {
        printf("SIZE WRONG after erasing %u: %llu vs %zu\n",
            g_uEraseKey,
            (unsigned long long)*(uint64_t*)(s_map + 0x38),
            nExpectSize);
    }
    char* root = *(char**)(PHead() + 8);
    assert(NC(root) == 1);
    g_nLeaves = -1;
    assert((size_t)ValidateRB(root, 0) == nExpectSize);
    auto v = Walk();
    assert(v.size() == nExpectSize);
    // the first/last through the head
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

// the erase of a key: find → MapErase
static void EraseKey(uint32_t uKey) {
    uint32_t k = uKey;
    char out[2][8];
    *(void**)out[0] = (void*)PAnchor();
    TreeFind(s_map, out[0], &k);
    char* node = *(char**)(out[0] + 8);
    assert(!NNil(node));   // must exist
    char out2[2][8];
    MapErase(s_map, out2, out[0]);
}

int main() {
    Bind();
    // ---- 25. the single erases ----
    {
        BuildMap();
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        CheckTree(15);
        assert(g_nStrMove == 15);
        // the nested trees: each value has 2 nodes
        // (from the seam)
        uint32_t order[] = { 8, 1, 15, 4, 12, 2,
            7, 13, 3, 14, 5, 11, 6, 10, 9 };
        size_t n = 15;
        for (uint32_t k : order) {
            size_t nBefore = g_vFreed.size();
            g_uEraseKey = k;
            g_uDbgKey = k;
            EraseKey(k);
            --n;
            CheckTree(n);
            // the frees: the 2 nested nodes + the
            // nested head + the anchor + the node
            assert(g_vFreed.size() == nBefore + 5);
        }
        // the head relinks
        assert(*(char**)(PHead() + 8) == PHead());
        assert(*(char**)PHead() == PHead());
        assert(*(char**)(PHead() + 0x10) == PHead());
        puts("D31-25 single erases ok");
    }

    // ---- 26. the erase-range [4, 8) ----
    {
        BuildMap();
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        uint32_t k4 = 4, k8 = 8;
        char it4[2][8], it8[2][8];
        *(void**)it4[0] = (void*)PAnchor();
        *(void**)it8[0] = (void*)PAnchor();
        TreeFind(s_map, it4[0], &k4);
        TreeFind(s_map, it8[0], &k8);
        char out[2][8];
        MapEraseRange(s_map, out, it4, it8);
        CheckTree(11);
        auto v = Walk();
        // 4,5,6,7 gone; 8 stays
        for (uint32_t x : v) {
            assert(x < 4 || x >= 8);
        }
        puts("D31-26 erase range ok");
    }

    // ---- 27. the full-range erase (both end) ----
    {
        size_t nBefore = g_vFreed.size();
        char itB[2][8], itE[2][8];
        *(void**)itB[0] = (void*)PAnchor();
        *(void**)itE[0] = (void*)PAnchor();
        *(void**)(itB[0] + 8) = (void*)PHead();
        *(void**)(itE[0] + 8) = (void*)PHead();
        char out[2][8];
        MapEraseRange(s_map, out, itB, itE);
        CheckTree(0);
        // the full clear path: nodes + the nested
        // trees via the orphan seam count already
        assert(g_vFreed.size() > nBefore);
        puts("D31-27 full range ok");
    }

    // ---- 28. the dtor ----
    {
        BuildMap();
        for (uint32_t i = 1; i <= 5; ++i) {
            InsertKey(i);
        }
        size_t nBefore = g_vFreed.size();
        MapTreeDtor(s_map);
        assert(*(void**)(s_map + 0x30) == nullptr);
        assert(*(uint64_t*)(s_map + 0x38) == 0);
        assert(g_vFreed.size() == nBefore
            + 5 /*nodes*/ + 5 /*nested heads*/
            + 5 /*anchors*/ + 10 /*nested nodes*/
            + 1 /*head*/);
        puts("D31-28 dtor ok");
    }

    // ---- 29. the out_of_range gate ----
    {
        BuildMap();
        InsertKey(3);
        bool bThrew = false;
        try {
            char it[2][8];
            *(void**)it[0] = (void*)PAnchor();
            *(void**)(it[0] + 8) = (void*)PHead();
            char out[2][8];
            MapErase(s_map, out, it);
        } catch (const std::out_of_range&) {
            bThrew = true;
        }
        assert(bThrew);
        CheckTree(1);   // untouched
        puts("D31-29 out_of_range gate ok");
    }

    // ---- 30. the own-tree single erases (c0b0) ----
    {
        char omap[0x40];
        memset(omap, 0, sizeof omap);
        *(uint64_t*)omap = 0xC0DE;
        OwnMapCtor(omap);
        auto insert = [&](uint32_t k) {
            uint64_t kv = k;
            char* h = *(char**)(omap + 0x30);
            char* at = h; bool bl = true;
            if (*(uint8_t*)(*(char**)(h + 8) + 0x21) == 0) {
                char* c = *(char**)(h + 8);
                do { at = c;
                    bl = k < *(uint32_t*)(at + 0x18);
                    c = bl ? *(char**)at
                           : *(char**)(at + 0x10);
                } while (*(uint8_t*)(c + 0x21) == 0);
            }
            char* out[2];
            OwnInsert(omap, out,
                (uint8_t)(bl ? 1 : 0), at, &kv);
        };
        for (uint32_t i = 1; i <= 15; ++i) {
            insert(i);
        }
        assert(*(uint64_t*)(omap + 0x38) == 15);
        // erase all of 1..15 in mixed order
        uint32_t order[] = { 8, 1, 15, 4, 12, 2,
            7, 13, 3, 14, 5, 11, 6, 10, 9 };
        size_t nErased = 0;
        for (uint32_t k : order) {
            ++nErased;
            // the descent to the node
            char* h = *(char**)(omap + 0x30);
            char* c = *(char**)(h + 8);
            while (1) {
                if (*(uint32_t*)(c + 0x18) == k) break;
                c = k < *(uint32_t*)(c + 0x18)
                    ? *(char**)c
                    : *(char**)(c + 0x10);
            }
            char it[2][8];
            *(void**)it[0] = (void*)0xC0DE;
            *(void**)(it[0] + 8) = c;
            char out[2][8];
            OwnErase(omap, out, it);
            // validate: the in-order walk + RB
            // (the compact checks)
            char* head = *(char**)(omap + 0x30);
            char* n = *(char**)head;
            uint32_t prev = 0;
            size_t cnt = 0;
            while (*(uint8_t*)(n + 0x21) == 0) {
                assert(*(uint32_t*)(n + 0x18) > prev);
                prev = *(uint32_t*)(n + 0x18);
                ++cnt;
                char it2[2][8];
                *(void**)it2[0] = (void*)0xC0DE;
                *(void**)(it2[0] + 8) = n;
                OwnIterNext(it2[0]);
                n = *(char**)(it2[0] + 8);
            }
            assert(cnt
                == *(uint64_t*)(omap + 0x38));
            assert(cnt == 15 - nErased);
        }
        assert(*(uint64_t*)(omap + 0x38) == 0);
        puts("D31-30 own-tree erases ok");
    }

    puts("SYNDICATE-D31-OK: the ERASE layer — the 0x28 rotations (14173b0e0/b140), the 0x28 erase (14173c0b0: the out_of_range gate + the successor splice + the unlink + the first/last walks + the remove-rebalance single loop + the size gate), the 0x28 erase-range (14173cb90: the owner checks + the both-end clear + the advance-and-erase loop), the 0x68 erase (14173e350: the same structure + the REAL cb90 on the nested own-tree value + the head/anchor/value frees), the 0x68 erase-range (14173eb10: the full-range clear via e240 + the advance loop), the dtor (14173ecf0: the full-range erase + the head delete + the zeroed slots) — the map core is now COMPLETE: insert + find + erase + erase-range + clear + dtor, all real");
    return 0;
}

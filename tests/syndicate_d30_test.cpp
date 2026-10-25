// ============================================================
// Syndicate.dll — unit D30: the internal OWN tree
// family (the 0x28-node set-tree). A REAL tree:
// the ctor, sequential inserts 1..15 (the rotations
// + the rebalance), the iterator walk, the
// double-descent pair, the clear.
// Node: left@+0, parent@+8, right@+0x10, key@+0x18,
// color@+0x20, _Isnil@+0x21.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "../Exe/Dll/Syndicate/Port/SyndicateOwnTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"

using namespace syndicate;

static std::vector<void*> g_vFreed;
static int g_nInvalid = 0;

static void Bind() {
    g_fnMeritOpNew = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpNew2 = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnStrMoveDE50 = [](void*, void*) {};
    g_fnOrphanCB90 = [](void*, void*, void*, void*) {};
}

// the map: anchor@+0, head@+0x30, size@+0x38
static char s_map[0x40];
static char* PHead() {
    return *(char**)(s_map + 0x30);
}
static void* NL(char* n) { return *(void**)n; }
static void* NR(char* n) {
    return *(void**)(n + 0x10); }
static void* NP(char* n) {
    return *(void**)(n + 8); }
static uint32_t NK(char* n) {
    return *(uint32_t*)(n + 0x18); }
static uint8_t NC(char* n) {
    return *(uint8_t*)(n + 0x20); }
static bool NNil(char* n) {
    return *(uint8_t*)(n + 0x21) != 0; }

// the insert driver (the descent + the real
// insert) — the same shape as ed60's walk
static void InsertKey(uint32_t uKey) {
    uint64_t kv = uKey;
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
    OwnInsert(s_map, out,
        (uint8_t)(bWentLeft ? 1 : 0), plVar6, &kv);
}

// the red-black validation
static int g_nLeaves = 0;
static int ValidateRB(char* n, int nBlack) {
    if (NNil(n)) {
        if (g_nLeaves == -1) {
            g_nLeaves = nBlack;
        } else if (g_nLeaves != nBlack) {
            printf("BLACK-HEIGHT MISMATCH\n");
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

int main() {
    Bind();

    // ---- 21. the allocs + the ctor ----
    {
        memset(s_map, 0, sizeof s_map);
        *(uint64_t*)s_map = (uint64_t)0xC0DE; // owner
        OwnMapCtor(s_map);
        char* head = PHead();
        assert(head != nullptr);
        assert(*(uint8_t*)(head + 0x21) == 1);
        assert(*(char**)(head + 8) == head);
        assert(*(char**)head == head);
        assert(*(char**)(head + 0x10) == head);
        assert(*(uint64_t*)(s_map + 0x38) == 0);
        // the node alloc
        uint64_t kv = 77;
        char* n = (char*)OwnNodeAlloc(
            (void*)0x11, (void*)0x22, (void*)0x33,
            &kv, 1);
        assert(n != nullptr);
        assert(NK(n) == 77);
        assert(NC(n) == 1);
        assert(!NNil(n));
        puts("D30-21 allocs ctor ok");
    }

    // ---- 22. the sequential insert 1..15 ----
    {
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        assert(*(uint64_t*)(s_map + 0x38) == 15);
        // the in-order walk from head->left
        char* n = *(char**)PHead();
        uint32_t uPrev = 0;
        int nCount = 0;
        while (!NNil(n)) {
            assert(NK(n) > uPrev);
            uPrev = NK(n);
            ++nCount;
            char* iter[2] = { nullptr, n };
            OwnIterNext(iter);
            n = iter[1];
        }
        assert(nCount == 15);
        assert(n == PHead());
        // the red-black validation
        char* root = *(char**)(PHead() + 8);
        assert(NC(root) == 1);
        g_nLeaves = -1;
        assert(ValidateRB(root, 0) == 15);
        // the past-the-end walk fires the gate
        char iter[2][8];
        *(void**)iter[0] = (void*)0x1;   // non-null
        *(void**)(iter[1]) = PHead();
        g_nInvalid = 0;
        OwnIterNext((void*)iter);
        assert(g_nInvalid == 1);
        puts("D30-22 sequential insert ok");
    }

    // ---- 23. the double-descent pair — the
    // equal_range walk: out[1] = the
    // LOWER_BOUND node, out[3] = the UPPER_BOUND
    // node ----
    {
        uint32_t k = 7;
        char* out[4];
        OwnDescendPair(s_map, out, &k);
        assert(out[0] == *(char**)s_map);  // owner
        assert(out[2] == *(char**)s_map);  // owner
        assert(NK(out[1]) == 7);    // the exact
        assert(NK(out[3]) == 8);    // the upper
        // a key beyond all: both walks end at
        // the HEAD (the not-found marker)
        k = 100;
        OwnDescendPair(s_map, out, &k);
        assert(out[1] == PHead());
        assert(out[3] == PHead());
        // the lowest key: both walks land on 1
        k = 0;
        OwnDescendPair(s_map, out, &k);
        assert(NK(out[1]) == 1);
        assert(NK(out[3]) == 1);
        puts("D30-23 descend pair ok");
    }

    // ---- 24. the clear ----
    {
        size_t nFreedBefore = g_vFreed.size();
        OwnClear(s_map);
        assert(g_vFreed.size() == nFreedBefore + 15);
        // the head relinks + the size reset
        char* head = PHead();
        assert(*(char**)(head + 8) == head);
        assert(*(char**)head == head);
        assert(*(char**)(head + 0x10) == head);
        assert(*(uint64_t*)(s_map + 0x38) == 0);
        // reinsert after the clear works
        InsertKey(9);
        assert(NK(*(char**)(PHead() + 8)) == 9);
        puts("D30-24 clear ok");
    }

    puts("SYNDICATE-D30-OK: the internal OWN tree family (the 0x28 set-tree) — the anchor alloc (14173bcb0: new 0x28, zeroed, color black — the elided return documented), the key node alloc (14173bd10: the fields + the qword key + the color arg), the recursive free (14173bc60: the right recursion + the left reentry), the iterator++ (14173b240: the right-subtree leftmost / the parent climb / the past-the-end gate), the map ctor (14173c580: the anchor head + the self-links + size 0), the clear (14173c470: the right-subtree frees + the left walk + the head relinks), the insert + the red-black rebalance (14173c5c0: the 0x1ffffffffffffffd length gate + the head/attach cases + the uncle-recolor / the inlined inner rotations / the grand rotation + the black root), the equal_range double-descent pair (14173bf40: the lower_bound first walk + the upper_bound second walk + the {owner,lower,owner,upper} output) — a REAL set-tree: 15 sequential inserts pass the in-order walk + the red-black validation");
    return 0;
}

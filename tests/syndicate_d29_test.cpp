// ============================================================
// Syndicate.dll — unit D29: the internal map tree
// core. A REAL map: the head sentinel + sequential
// inserts 1..15 (forcing the rotations + the
// rebalance), the lower_bound queries, the iterator
// walk, the clear.
// Node: left@+0, parent@+8, right@+0x10, key@+0x18,
// value@+0x20, color@+0x60, _Isnil@+0x61.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "../Exe/Dll/Syndicate/Port/SyndicateMapTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"

using namespace syndicate;

static std::vector<void*> g_vFreed;
static int g_nInvalid = 0, g_nStrMove = 0;
static int g_nOrphan = 0;

static void Bind() {
    g_fnMeritOpNew = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpNew2 = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    // the value's TWO heap buffers: the string
    // object at +0x20 (its buffer ptr at +0x20)
    // and the second buffer at +0x50 — both
    // freed by the clear (e240)
    g_fnStrMoveDE50 = [](void* d, void* s) {
        (void)s;
        ++g_nStrMove;
        *(void**)d = malloc(8);
        *(void**)((char*)d + 0x30) = malloc(8);
    };
    g_fnOrphanCB90 = [](void* o, void*, void*,
                        void*) {
        (void)o; ++g_nOrphan; };
}

// the map: anchor@+0, head@+0x30, size@+0x38
static char s_map[0x40];
static char* PHead() {
    return *(char**)(s_map + 0x30);
}
static void* NLeft(char* n) {
    return *(void**)n; }
static void* NRight(char* n) {
    return *(void**)(n + 0x10); }
static void* NParent(char* n) {
    return *(void**)(n + 8); }
static uint32_t NKey(char* n) {
    return *(uint32_t*)(n + 0x18); }
static uint8_t NColor(char* n) {
    return *(uint8_t*)(n + 0x60); }
static bool NNil(char* n) {
    return *(uint8_t*)(n + 0x61) != 0; }

static void BuildMap() {
    memset(s_map, 0, sizeof s_map);
    // the anchor (its [0] = the map owner)
    char* anchor = (char*)calloc(1, 0x68);
    *(char**)anchor = s_map;
    *(char**)s_map = anchor;
    // the head
    char* head = (char*)TreeNodeAlloc();
    *(uint8_t*)(head + 0x61) = 1;
    *(char**)(head + 8) = head;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
    *(char**)(s_map + 0x30) = head;
    *(uint64_t*)(s_map + 0x38) = 0;
}

// the insert driver (the ed60 descent): the attach
// node + the direction, then the real insert
static void InsertKey(uint32_t uKey) {
    uint32_t kv[4] = { uKey, 0, 0, 0 };
    char* pHead = PHead();
    char* plVar6 = pHead;
    bool bWentLeft = true;
    if (!NNil(*(char**)(pHead + 8))) {
        char* plVar5 = *(char**)(pHead + 8);
        do {
            plVar6 = plVar5;
            bWentLeft =
                uKey < NKey(plVar6);
            plVar5 = bWentLeft
                ? (char*)NLeft(plVar6)
                : (char*)NRight(plVar6);
        } while (!NNil(plVar5));
    }
    char* out[2];
    TreeInsert(s_map, out,
        (uint8_t)(bWentLeft ? 1 : 0),
        plVar6, kv);
}

// the red-black validation: root black, no
// red-red, equal black height
static int g_nLeaves = 0;
static int ValidateRB(char* n, int nBlack) {
    if (NNil(n)) {
        if (g_nLeaves == -1) {
            g_nLeaves = nBlack;
        } else if (g_nLeaves != nBlack) {
            printf("BLACK-HEIGHT MISMATCH\\n");
            std::exit(1);
        }
        return 0;
    }
    if (n != *(char**)(PHead() + 8)) {
        // not the root: check the red-red rule
        if (NColor(n) == 0
            && NColor((char*)NParent(n)) == 0) {
            printf("RED-RED VIOLATION\\n");
            std::exit(1);
        }
    }
    int nAdd = NColor(n) != 0 ? 1 : 0;
    return 1 + ValidateRB((char*)NLeft(n),
                nBlack + nAdd)
             + ValidateRB((char*)NRight(n),
                nBlack + nAdd);
}

int main() {
    Bind();

    // ---- 16. the node allocs ----
    {
        char* n = (char*)TreeNodeAlloc();
        assert(n != nullptr);
        assert(NLeft(n) == nullptr);
        assert(NParent(n) == nullptr);
        assert(NRight(n) == nullptr);
        assert(NColor(n) == 1);      // black
        assert(!NNil(n));           // isnil = 0
        uint32_t kv[4] = { 77, 0, 0, 0 };
        char* nk = (char*)TreeNodeAllocKey(
            nullptr, nullptr, nullptr, kv, 1);
        assert(NKey(nk) == 77);
        assert(NColor(nk) == 1);
        assert(!NNil(nk));
        assert(g_nStrMove == 1);   // the value move
        puts("D29-16 node allocs ok");
    }

    // ---- 17. the sequential insert 1..15 ----
    {
        BuildMap();
        g_nStrMove = 0;
        for (uint32_t i = 1; i <= 15; ++i) {
            InsertKey(i);
        }
        assert(*(uint64_t*)(s_map + 0x38) == 15);
        assert(g_nStrMove == 15);
        // the in-order walk from head->left
        char* n = *(char**)PHead();   // the first
        uint32_t uPrev = 0;
        int nCount = 0;
        while (!NNil(n)) {
            assert(NKey(n) > uPrev);
            uPrev = NKey(n);
            ++nCount;
            // the iterator walk
            char* iter[2] = { nullptr, n };
            TreeIterNext(iter);
            n = iter[1];
        }
        assert(nCount == 15);
        assert(n == PHead());   // past-the-end
        // the red-black validation
        char* root = *(char**)(PHead() + 8);
        assert(NColor(root) == 1);   // black
        g_nLeaves = -1;
        int nTotal = ValidateRB(root, 0);
        assert(nTotal == 15);
        puts("D29-17 sequential insert ok");
    }

    // ---- 18. the find (14173d1e0: the exact
    // match or the end iterator) ----
    {
        // an existing key → the node
        uint32_t k = 7;
        char* out[2];
        TreeFind(s_map, out, &k);
        assert(out[0] == *(char**)s_map);   // anchor
        assert(NKey(out[1]) == 7);
        // beyond all → the end (the head)
        k = 100;
        TreeFind(s_map, out, &k);
        assert(out[1] == PHead());          // head
        // rebuild with the odd keys 1..15
        BuildMap();
        for (uint32_t i = 1; i <= 15; i += 2) {
            InsertKey(i);
        }
        // 6 is missing → the end iterator (the
        // verbatim `key < remembered` gate)
        k = 6;
        TreeFind(s_map, out, &k);
        assert(out[1] == PHead());
        k = 5;              // exact
        TreeFind(s_map, out, &k);
        assert(NKey(out[1]) == 5);
        k = 15;             // the highest exact
        TreeFind(s_map, out, &k);
        assert(NKey(out[1]) == 15);
        puts("D29-18 find ok");
    }

    // ---- 19. the rotations direct ----
    {
        BuildMap();
        InsertKey(10); InsertKey(5); InsertKey(1);
        // 1 forced a rotation: 5 is the root now
        char* root = *(char**)(PHead() + 8);
        assert(NKey(root) == 5);
        assert(NKey((char*)NLeft(root)) == 1);
        assert(NKey((char*)NRight(root)) == 10);
        // the first/last through the head
        assert(NKey(*(char**)PHead()) == 1);
        assert(NKey(*(char**)(PHead() + 0x10))
            == 10);
        puts("D29-19 rotations ok");
    }

    // ---- 20. the clear ----
    {
        size_t nFreedBefore = g_vFreed.size();
        // clear from the root
        TreeClearNodes(
            s_map, *(char**)(PHead() + 8));
        // each node frees: the +0x50 buffer, the
        // +0x20 buffer, and the node itself
        assert(g_vFreed.size()
            == nFreedBefore + 3 * 3);
        assert(g_nOrphan == 3);   // the value dtors
        puts("D29-20 clear ok");
    }

    puts("SYNDICATE-D29-OK: the internal map tree core — the node allocs (14173bc00: color black + the zeroed links; 14173e1a0: the key + the string-move value + the color arg), the rotations (14173b830/b890: the root/left-child/right-child cases with the isnil parent fixups), the iterator++ (14173b6c0: the right-subtree leftmost / the parent climb / the past-the-end invalid), the recursive clear (14173e240: the right recursion + the left reentry + the orphan + the deletes), the lower_bound (14173d1e0: the descent + the anchor checks + the end iterator), the insert + the rebalance (14173e790: the length gate 0x38e38e38e38e38c + the attach cases + the uncle-recolor / the inner rotate / the grand rotate + the black root) — a REAL map: 15 sequential inserts pass the in-order + the red-black validation");
    return 0;
}

// syndicate_d43_test — D41c/T16: the two NESTED
// families REAL (SyndicateLeagueMgrNested): the
// recursive subtree erasers, the clears, the
// erase-ones (BYTE color +0x1c/+0x2c) and the
// erase-ranges (the CRT gates + the clear shortcut +
// the advance loop), plus the FULL INTEGRATION: a
// special mgr node (470-family) carrying a populated
// nested map erased through MgrErOne470 with the real
// g_fnNestedErA.
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgrNested.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgrErOne.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMgrErase.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <stdexcept>

using namespace syndicate;

// the allocation registry (leak/double-free proof)
struct Ent { void* p; int used; };
static Ent* g_tab = nullptr;
static const size_t g_cap = 1u << 16;
static void TabInit() {
    if (!g_tab) {
        g_tab = (Ent*)malloc(g_cap * sizeof(Ent));
        memset(g_tab, 0, g_cap * sizeof(Ent));
    }
}
static int g_nOpNew = 0, g_nOpDelete = 0, g_nInvalid = 0;
static void* CountNew(size_t sz) {
    void* p = malloc(sz ? sz : 1);
    TabInit();
    size_t i = (size_t)p / 8 % g_cap;
    while (g_tab[i].used == 1) i = (i + 1) % g_cap;
    g_tab[i] = { p, 1 };
    ++g_nOpNew; return p;
}
static void CountDel(void* p) {
    if (!p) return;
    TabInit();
    size_t i = (size_t)p / 8 % g_cap;
    while (g_tab[i].used) {
        if (g_tab[i].used == 1 && g_tab[i].p == p) {
            g_tab[i].used = 2; ++g_nOpDelete; free(p);
            return;
        }
        i = (i + 1) % g_cap;
    }
    assert(!"double/foreign free");
}
void* operator new(size_t sz) { return CountNew(sz); }
void  operator delete(void* p) noexcept { CountDel(p); }
void  operator delete(void* p, size_t) noexcept
    { CountDel(p); }

// the map fixture (works for the nested families: the
// color byte sits at isnil-1, head self-links, the
// FIRST/LAST maintenance)
struct Fixture {
    char map[0x40];
    char* head;
    void* proxy;
    int isnil; size_t nodeSize;
    void Init(int isnilOff, size_t headSize,
              size_t nsz) {
        isnil = isnilOff; nodeSize = nsz;
        memset(map, 0, sizeof map);
        proxy = CountNew(8);
        *(void**)proxy = map;
        *(void**)map = proxy;
        head = (char*)CountNew(headSize);
        *(char*)(head + isnilOff - 1) = 1;  // nil BLACK
        *(char*)(head + isnilOff) = 1;
        *(char**)(head + 8) = head;
        *(char**)head = head;
        *(char**)(head + 0x10) = head;
        *(char**)(map + 0x30) = head;
        *(uint64_t*)(map + 0x38) = 0;
    }
    char* Node(int black) {
        char* n = (char*)CountNew(nodeSize);
        memset(n, 0, nodeSize);
        *(char**)n = head;
        *(char**)(n + 8) = head;
        *(char**)(n + 0x10) = head;
        *(char*)(n + isnil - 1) = black ? 1 : 0;
        return n;
    }
    void SetRoot(char* n) {
        *(char**)(head + 8) = n;
        *(char**)head = n;
        *(char**)(head + 0x10) = n;
        *(char**)(n + 8) = head;
        (*(uint64_t*)(map + 0x38))++;
    }
    void SetL(char* p, char* c) {
        *(char**)p = c;
        *(char**)(c + 8) = p;
        if (*(char**)(head) == p)
            *(char**)(head) = c;
        (*(uint64_t*)(map + 0x38))++;
    }
    void SetR(char* p, char* c) {
        *(char**)(p + 0x10) = c;
        *(char**)(c + 8) = p;
        if (*(char**)(head + 0x10) == p)
            *(char**)(head + 0x10) = c;
        (*(uint64_t*)(map + 0x38))++;
    }
    int Black(char* n) {
        return n == head ? 1 : *(char*)(n + isnil - 1);
    }
};

// the RB validity checker
static int CheckRB(Fixture& f, char* n) {
    if (n == f.head) return 1;
    char* l = *(char**)n;
    char* r = *(char**)(n + 0x10);
    char* p = *(char**)(n + 8);
    if (l != f.head && *(char**)(l + 8) != n)
        assert(!"left child parent mismatch");
    if (r != f.head && *(char**)(r + 8) != n)
        assert(!"right child parent mismatch");
    if (p != f.head && n != *(char**)p
        && n != *(char**)(p + 0x10))
        assert(!"parent child mismatch");
    if (f.Black(n) == 0
        && (f.Black(l) == 0 || f.Black(r) == 0))
        assert(!"red-red violation");
    int lb = CheckRB(f, l);
    int rb = CheckRB(f, r);
    assert(lb == rb && "black-height mismatch");
    return lb + (f.Black(n) == 1 ? 1 : 0);
}
static void CheckTree(Fixture& f) {
    char* root = *(char**)(f.head + 8);
    assert(f.Black(root) == 1 && "the root is black");
    if (root != f.head) CheckRB(f, root);
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritOpNew = CountNew;
    g_fnMeritOpDelete = CountDel;
    g_fnMeritInvalid = []() { ++g_nInvalid; };

    // ---------- D43-1: nested A erase-one (0x1d/0x1c) ---
    {
        Fixture f; f.Init(0x1d, 0x20, 0x20);
        char* n = f.Node(1); f.SetRoot(n);
        g_nOpDelete = 0;
        int64_t it[2] = { (int64_t)f.proxy, (int64_t)n };
        int64_t out[2];
        NestedErOneA(f.map, out, it);
        assert(g_nOpDelete == 1);
        assert(*(char**)(f.head + 8) == f.head);
        assert(*(uint64_t*)(f.map + 0x38) == 0);
        CheckTree(f);
        // the fixup chain (the case 5/6 shape) on the
        // nested family
        Fixture g; g.Init(0x1d, 0x20, 0x20);
        char* root = g.Node(1); g.SetRoot(root);
        char* x = g.Node(1); g.SetL(root, x);
        char* s = g.Node(1); g.SetR(root, s);
        char* sl = g.Node(0); g.SetL(s, sl);
        char* sr = g.Node(0); g.SetR(s, sr);
        g_nOpDelete = 0;
        int64_t it2[2] = { (int64_t)g.proxy,
                           (int64_t)x };
        NestedErOneA(g.map, out, it2);
        assert(g_nOpDelete == 1);
        CheckTree(g);
        assert(g_nInvalid == 0);
        printf("D43-1 nested A erase-one + fixup ok\n");
    }

    // ---------- D43-2: nested A subtree + clear -------
    {
        // the subtree eraser ALONE (a 3-node right
        // subtree under its own mini-root)
        Fixture f; f.Init(0x1d, 0x20, 0x20);
        char* rc = f.Node(1); f.SetRoot(rc);
        char* rlc = f.Node(0); f.SetL(rc, rlc);
        char* rrc = f.Node(0); f.SetR(rc, rrc);
        g_nOpDelete = 0;
        NestedSubtreeA(f.map, rc);
        assert(g_nOpDelete == 3
            && "rc + rlc + rrc freed");
        // the clear on a SEPARATE intact tree
        Fixture g; g.Init(0x1d, 0x20, 0x20);
        char* root = g.Node(1); g.SetRoot(root);
        char* lc = g.Node(0); g.SetL(root, lc);
        char* r2 = g.Node(0); g.SetR(root, r2);
        char* rl2 = g.Node(0); g.SetL(r2, rl2);
        char* rr2 = g.Node(0); g.SetR(r2, rr2);
        g_nOpDelete = 0;
        NestedClearA(g.map);
        assert(g_nOpDelete == 5
            && "all five nodes freed");
        assert(*(char**)(g.head + 8) == g.head
            && *(char**)g.head == g.head
            && *(char**)(g.head + 0x10) == g.head);
        assert(*(uint64_t*)(g.map + 0x38) == 0);
        printf("D43-2 nested A subtree + clear ok\n");
    }

    // ---------- D43-3: nested A erase-range -----------
    {
        // the whole map [begin, end) → the clear path
        Fixture f; f.Init(0x1d, 0x20, 0x20);
        char* root = f.Node(1); f.SetRoot(root);
        char* lc = f.Node(0); f.SetL(root, lc);
        char* rc = f.Node(0); f.SetR(root, rc);
        g_nOpDelete = 0;
        int64_t p1[2] = { (int64_t)f.proxy,
                         (int64_t)*(char**)f.head };
        int64_t p2[2] = { (int64_t)f.proxy,
                         (int64_t)f.head };
        int64_t out[2];
        NestedErRangeA(f.map, out, p1, p2);
        assert(g_nOpDelete == 3);
        assert(*(char**)(f.head + 8) == f.head);
        assert(*(uint64_t*)(f.map + 0x38) == 0);
        assert(out[1] == (int64_t)f.head);
        // a partial range: erase the LAST node only
        // (a true sub-range, not from begin)
        Fixture g; g.Init(0x1d, 0x20, 0x20);
        char* rt = g.Node(1); g.SetRoot(rt);
        char* lf = g.Node(0); g.SetL(rt, lf);
        char* rf = g.Node(0); g.SetR(rt, rf);
        g_nOpDelete = 0;
        int64_t q1[2] = { (int64_t)g.proxy,
                          (int64_t)rf };
        int64_t q2[2] = { (int64_t)g.proxy,
                          (int64_t)g.head };
        NestedErRangeA(g.map, out, q1, q2);
        assert(g_nOpDelete == 1);
        assert(*(char**)(rt + 0x10) == g.head);
        assert(*(uint64_t*)(g.map + 0x38) == 2);
        CheckTree(g);
        assert(g_nInvalid == 0);
        printf("D43-3 nested A erase-range ok\n");
    }

    // ---------- D43-4: nested B (0x2d/0x2c) ----------
    {
        Fixture f; f.Init(0x2d, 0x30, 0x30);
        char* root = f.Node(1); f.SetRoot(root);
        char* x = f.Node(1); f.SetL(root, x);
        char* s = f.Node(1); f.SetR(root, s);
        char* sl = f.Node(0); f.SetL(s, sl);
        char* sr = f.Node(0); f.SetR(s, sr);
        g_nOpDelete = 0;
        int64_t out[2];
        int64_t it[2] = { (int64_t)f.proxy, (int64_t)x };
        NestedErOneB(f.map, out, it);
        assert(g_nOpDelete == 1);
        CheckTree(f);
        // the B clear + range
        Fixture h; h.Init(0x2d, 0x30, 0x30);
        char* r2 = h.Node(1); h.SetRoot(r2);
        char* c2 = h.Node(0); h.SetR(r2, c2);
        g_nOpDelete = 0;
        NestedClearB(h.map);
        assert(g_nOpDelete == 2);
        assert(*(char**)(h.head + 8) == h.head);
        assert(g_nInvalid == 0);
        printf("D43-4 nested B erase-one + clear ok\n");
    }

    // ---------- D43-5: the INTEGRATION (the payoff) ---
    // a special mgr node (470-family, 0x68) with a
    // POPULATED nested map, erased via MgrErOne470 with
    // the REAL g_fnNestedErA: the nested nodes + the
    // nested head + the nested proxy + the node all
    // freed.
    {
        Fixture m; m.Init(0x61, 0x68, 0x68);  // mgr map
        char* node = m.Node(1); m.SetRoot(node);
        // the nested map inside the node: base +0x20,
        // head +0x50
        char* nbase = node + 0x20;
        void* nproxy = CountNew(8);
        *(void**)(nbase + 0) = nproxy;
        *(void**)nproxy = nbase;
        char* nhead = (char*)CountNew(0x20);
        *(char*)(nhead + 0x1c) = 1;   // nil BLACK
        *(char*)(nhead + 0x1d) = 1;
        *(char**)(nhead + 8) = nhead;
        *(char**)nhead = nhead;
        *(char**)(nhead + 0x10) = nhead;
        *(char**)(nbase + 0x30) = nhead;
        *(uint64_t*)(nbase + 0x38) = 0;
        // two nested nodes
        char* n1 = (char*)CountNew(0x20);
        memset(n1, 0, 0x20);
        *(char**)n1 = nhead; *(char**)(n1 + 8) = nhead;
        *(char**)(n1 + 0x10) = nhead;
        *(char*)(n1 + 0x1c) = 1;   // black root
        *(char**)(nhead + 8) = n1;
        *(char**)nhead = n1;
        *(char**)(nhead + 0x10) = n1;
        char* n2 = (char*)CountNew(0x20);
        memset(n2, 0, 0x20);
        *(char**)n2 = nhead;
        *(char**)(n2 + 8) = n1;
        *(char**)(n2 + 0x10) = nhead;
        *(char*)(n2 + 0x1c) = 0;   // red right child
        *(char**)(n1 + 0x10) = n2;
        *(char**)(nhead + 0x10) = n2;
        (*(uint64_t*)(nbase + 0x38)) = 2;
        // erase the mgr node: the nested destroy runs
        // with the REAL nested range (the clear path)
        g_nOpDelete = 0;
        int64_t it[2] = { (int64_t)m.proxy,
                          (int64_t)node };
        int64_t out[2];
        MgrErOne470(m.map, out, it);
        // (the range clear frees n1 + n2; the special
        //  tail frees the nested head + the nested
        //  proxy + the node = 5)
        assert(g_nOpDelete == 5
            && "n1 + n2 + the nested head + the nested"
               " proxy + the node");
        assert(*(char**)(m.head + 8) == m.head);
        assert(*(uint64_t*)(m.map + 0x38) == 0);
        assert(g_nInvalid == 0);
        printf("D43-5 the special-node INTEGRATION ok\n");
    }

    assert(g_nInvalid == 0);
    printf(
      "SYNDICATE-D43-OK: the NESTED families CLOSED"
      " (D41c) - the subtree erasers + the clears +"
      " the byte-color erase-ones (0x1c/0x2c) + the"
      " erase-ranges (the CRT gates + the clear"
      " shortcut + the advance loop) verbatim for the"
      " two nested families, and the special mgr"
      " erase-ones now destroy their POPULATED nested"
      " maps through the REAL seams - the T16 mgr"
      " erase layer is FULLY real end-to-end\n");
    return 0;
}

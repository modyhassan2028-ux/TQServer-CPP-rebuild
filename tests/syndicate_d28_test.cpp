// ============================================================
// Syndicate.dll — unit D28: the rest of the
// CCrossMeritMgr family (14173f680/f8e0/f950/f9c0/
// fa40/fc80). The same real-tree kit as D27:
// left@+0, parent@+8, right@+0x10, key@+0x18,
// _Isnil@+0x61; the leaves point at the head.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"

using namespace syndicate;

struct SNode {
    SNode* m_pLeft;
    SNode* m_pParent;
    SNode* m_pRight;
    uint32_t m_uKey;
    uint8_t m_pad[0x45];   // _Isnil @+0x61
    uint8_t m_abNil;
};

static SNode s_head, s_n10, s_n20, s_n30;
static SNode s_anchor;
static char s_map[0x40];
static char s_owner[0x40];

static void MkNode(SNode* p, uint32_t k) {
    memset(p, 0, sizeof(SNode));
    p->m_uKey = k;
}

static void BuildTree() {
    memset(&s_head, 0, sizeof s_head);
    s_head.m_abNil = 1;
    MkNode(&s_n10, 10); MkNode(&s_n20, 20);
    MkNode(&s_n30, 30);
    s_n20.m_pLeft = &s_n10; s_n20.m_pRight = &s_n30;
    s_n10.m_pParent = &s_n20; s_n30.m_pParent = &s_n20;
    s_n10.m_pLeft = &s_head; s_n10.m_pRight = &s_head;
    s_n30.m_pLeft = &s_head; s_n30.m_pRight = &s_head;
    s_n20.m_pParent = &s_head;
    s_head.m_pLeft = &s_n10; s_head.m_pRight = &s_n30;
    s_head.m_pParent = &s_n20;
    // the map object: anchor@+0, head@+0x30,
    // size@+0x38; anchor[0] = the owner; the
    // owner+0x30 = head (the end-check slot)
    memset(s_map, 0, sizeof s_map);
    memset(s_owner, 0, sizeof s_owner);
    memset(&s_anchor, 0, sizeof s_anchor);
    *(void**)s_map = &s_anchor;
    *(void**)&s_anchor.m_pLeft = s_owner;
    *(void**)(s_owner + 0x30) = &s_head;
    *(void**)(s_map + 0x30) = &s_head;
    *(uint64_t*)(s_map + 0x38) = 3;
}

static void Reset() {
    BuildTree();
}

// the seam recorders
static std::vector<void*> g_vFreed;
static std::vector<void*> g_vStrMove, g_vStrDtor;
static std::vector<void*> g_vIns;
static std::vector<void*> g_vAnchorAlloc;
static std::vector<void*> g_vOrphan, g_vSplice;
static std::vector<void*> g_vLower;
static int g_nInvalid = 0, g_nLogErr = 0;
static int g_nValid = 0;
static uint32_t g_uValidKey = 0;
static char g_cValidRet = 1;

// the insert seam: place a fresh node with the key
// and return the out-iterator {anchor, newnode}
static char s_newnode[0x68];
static void* InsF0C0(void* pMap, void* pOut,
                     void* pPair, uint32_t* pKey) {
    g_vIns.push_back(pMap);
    memset(s_newnode, 0, sizeof s_newnode);
    *(uint32_t*)(s_newnode + 0x18) = *pKey;
    ((char**)pOut)[0] = (char*)&s_anchor;
    ((char**)pOut)[1] = s_newnode;
    return pOut;
}
// the lower_bound seam: writes {anchor, node}
static void* LowerD1E0(void* pMap, void* pOut,
                        uint32_t* pKey) {
    g_vLower.push_back(pMap);
    // end (the head) for missing keys — the
    // caller then takes the insert path
    ((char**)pOut)[0] = (char*)&s_anchor;
    ((char**)pOut)[1] = (char*)&s_head;
    return pOut;
}

static void Bind() {
    g_fnMeritOpNew = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpNew2 = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnMeritLogError = []() { ++g_nLogErr; };
    g_fnNodeAlloc = []() -> void* {
        return calloc(1, 0x68); };
    g_fnTreeDtor = [](void*) {};
    g_fnTreeClearOuter = [](void*) {};
    g_fnTreeInsert = [](void*, uint32_t*) ->
        int64_t { return 0; };
    g_fnTreeClearNodes = [](void*, void*) {};
    g_fnMeritLogFactory = []() -> void* {
        return nullptr; };
    g_fnMeritLogWrite = [](void*, uint32_t, int) {};
    g_fnListAnchorAlloc = []() -> void* {
        void* p = calloc(1, 0x20);
        g_vAnchorAlloc.push_back(p);
        return p; };
    g_fnStrMoveDE50 = [](void* d, void* s) {
        g_vStrMove.push_back(d); (void)s;
        // the string move initializes the buffer
        // slot (the dtor path frees it)
        *(void**)d = malloc(8); };
    g_fnStrDtorCE30 = [](void* p) {
        g_vStrDtor.push_back(p); };
    g_fnTreeInsertF0C0 = InsF0C0;
    g_fnOrphanCB90 = [](void* o, void*, void* a,
                        void* b) {
        g_vOrphan.push_back(o); (void)a; (void)b; };
    g_fnSpliceCD80 = [](void* i, void* w) {
        g_vSplice.push_back(i); (void)w; };
    g_fnLowerBoundD1E0 = LowerD1E0;
    g_fnGetGameMgr = []() -> void* {
        return (void*)0x99; };
    g_fnMeritValid = [](void*, uint32_t k) -> char {
        ++g_nValid; g_uValidKey = k;
        return g_cValidRet; };
    g_pMeritDatInstance = nullptr;
}

int main() {
    Bind();

    // ---- 9. MeritValueFetch — found (14173f680) ----
    {
        Reset();
        g_vIns.clear(); g_nInvalid = 0;
        uint32_t k = 20;
        void* r = MeritValueFetch(s_map, &k);
        // the node's value slot at +0x20
        assert(r == (void*)((char*)&s_n20 + 0x20));
        assert(g_vIns.empty());       // no insert
        assert(g_nInvalid == 0);      // not end
        // the 10 (smaller, still found later):
        k = 10;
        r = MeritValueFetch(s_map, &k);
        assert(r == (void*)((char*)&s_n10 + 0x20));
        // the 30:
        k = 30;
        r = MeritValueFetch(s_map, &k);
        assert(r == (void*)((char*)&s_n30 + 0x20));
        puts("D28-9 value fetch found ok");
    }

    // ---- 10. MeritValueFetch — missing (insert) ----
    {
        Reset();
        g_vIns.clear(); g_vStrMove.clear();
        g_vAnchorAlloc.clear();
        uint32_t k = 15;
        void* r = MeritValueFetch(s_map, &k);
        assert(g_vIns.size() == 1);   // the insert
        // the owner + list anchor allocated
        assert(g_vAnchorAlloc.size() == 1);
        assert(g_vStrMove.size() == 1);
        // the returned value = the new node + 0x20
        assert(r == (void*)(s_newnode + 0x20));
        assert(g_nInvalid == 0);
        puts("D28-10 value fetch insert ok");
    }

    // ---- 11. MeritCtorVft (14173f8e0) ----
    {
        static char outer[0x48];
        memset(outer, 0, sizeof outer);
        g_fnTreeClearNodes = [](void* m, void* n) {
            g_vOrphan.push_back(m); (void)n; };
        g_vOrphan.clear();
        void* r = MeritCtorVft(outer);
        assert(r == outer);
        assert(*(void**)outer == g_pCrossMeritVft);
        // the map at +8 built: the anchor + head
        void* anchor = *(void**)(outer + 8);
        assert(anchor != nullptr);
        assert(*(void**)anchor == (void*)(outer + 8));
        char* head = *(char**)(outer + 0x38);
        assert((uint8_t)head[0x61] == 1);
        assert(*(char**)(head + 8) == head);
        assert(*(char**)head == head);
        assert(*(char**)(head + 0x10) == head);
        assert(*(uint64_t*)(outer + 0x40) == 0);
        // the defensive clear fired (from the root)
        assert(g_vOrphan.size() == 1);
        assert(g_vOrphan[0] == (void*)(outer + 8));
        g_fnTreeClearNodes = [](void*, void*) {};
        puts("D28-11 ctor vft ok");
    }

    // ---- 12. MeritDtorVftScalar (14173f950) ----
    {
        static std::vector<void*> vTree;
        g_fnTreeDtor = [](void* m) {
            vTree.push_back(m); };
        char* outer = (char*)calloc(1, 0x48);
        void* anchor = malloc(8);
        *(void**)(outer + 8) = anchor;
        void* r = MeritDtorVftScalar(outer, 0);
        assert(r == outer);
        assert(*(void**)outer == g_pCrossMeritVft);
        assert(vTree.size() == 1
            && vTree[0] == (void*)(outer + 8));
        // the anchor freed; the outer NOT (flags 0)
        bool bAnchor = false;
        for (auto p : g_vFreed) if (p == anchor) {
            bAnchor = true; }
        assert(bAnchor);
        bool bOuter = false;
        for (auto p : g_vFreed) if (p == (void*)outer) {
            bOuter = true; }
        assert(!bOuter);
        // flags 1 → the outer freed too
        *(void**)(outer + 8) = malloc(8);
        MeritDtorVftScalar(outer, 1);
        bOuter = false;
        for (auto p : g_vFreed) if (p == (void*)outer) {
            bOuter = true; }
        assert(bOuter);
        puts("D28-12 dtor vft scalar ok");
    }

    // ---- 13. MeritSingleton (14173f9c0) ----
    {
        g_pMeritDatInstance = nullptr;
        g_nLogErr = 0;
        void* r = MeritSingleton();
        assert(r != nullptr);
        assert(*(void**)r == g_pCrossMeritVft);
        assert(g_nLogErr == 0);
        // the cached path
        void* r2 = MeritSingleton();
        assert(r2 == r);
        // the fail path: the alloc returns null
        g_pMeritDatInstance = nullptr;
        auto fnOld = g_fnMeritOpNew2;
        g_fnMeritOpNew2 = [](size_t) -> void* {
            return nullptr; };
        g_nLogErr = 0;
        r = MeritSingleton();
        assert(r == nullptr);
        assert(g_nLogErr == 1);
        g_fnMeritOpNew2 = fnOld;
        g_pMeritDatInstance = nullptr;
        puts("D28-13 singleton ok");
    }

    // ---- 14. MeritGrant (14173fa40) ----
    {
        static char outer[0x48];
        memset(outer, 0, sizeof outer);
        // a real map at outer+8 (head@outer+0x38)
        Reset();
        *(void**)(outer + 8) = &s_anchor;
        *(void**)(outer + 0x38) = &s_head;
        *(uint64_t*)(outer + 0x40) = 3;
        // key 0 → the log error, no grant
        g_nLogErr = 0; g_nValid = 0;
        assert(MeritGrant(outer, 0) == 0);
        assert(g_nLogErr == 1);
        assert(g_nValid == 0);
        // the validity check fails → 0
        g_cValidRet = 0;
        assert(MeritGrant(outer, 555) == 0);
        assert(g_nValid == 1);
        assert(g_uValidKey == 555);
        // valid + the lower_bound seam returns end
        // → the insert chain → 1
        g_cValidRet = 1;
        g_vLower.clear(); g_vIns.clear();
        g_vAnchorAlloc.clear(); g_vSplice.clear();
        assert(MeritGrant(outer, 777) == 1);
        assert(g_vLower.size() == 1);   // lower_bound
        assert(g_vIns.size() == 1);      // the fetch
        assert(g_vSplice.size() == 1);   // the splice
        assert(g_uValidKey == 777);
        puts("D28-14 grant ok");
    }

    // ---- 15. MeritDeleteAnchor (14173fc80) ----
    {
        static char map[0x40];
        memset(map, 0, sizeof map);
        void* anchor = malloc(8);
        *(void**)map = anchor;
        MeritDeleteAnchor(map);
        bool bFreed = false;
        for (auto p : g_vFreed) if (p == anchor) {
            bFreed = true; }
        assert(bFreed);
        puts("D28-15 delete anchor ok");
    }

    puts("SYNDICATE-D28-OK: the CCrossMeritMgr family CLOSED — the keyed value fetch (the lower_bound descent + the insert-if-missing owner chain: opnew(8) owner + the +0x21 list anchor + the string move + the f0c0 tree insert + the anchor unwind, the end deref check, the value@+0x20), the vft ctor (f600 map@+8 + the defensive clear from the root), the vft scalar deleting dtor (tree dtor + anchor delete + the flags-1 outer delete), the DAT_141886cd0 singleton (alloc 0x48 + ctor + the log on fail + the cached path), the grant (the key-0 gate + the mgr vt+0x2a8 validity + the lower_bound + the end→insert chain + the orphan/splice), the anchor delete");
    return 0;
}

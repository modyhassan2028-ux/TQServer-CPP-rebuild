// ============================================================
// Syndicate.dll — unit D27: the CCrossMeritMgr
// management shell. A real 3-node in-order tree honors
// the MSVC _Tree node layout: left@+0, parent@+8,
// right@+0x10, key u32@+0x18, _Isnil@+0x61.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "../modules/syndicate/src/SyndicateCrossMerit.h"

using namespace syndicate;
using std::string;
using std::to_string;

static std::vector<string> g_vLog;
static std::vector<uint32_t> g_vKeys;
static int g_nInvalid = 0;
static std::vector<void*> g_vDtor, g_vClearOuter;
static std::vector<void*> g_vClearNodes;
static std::vector<void*> g_vIns;
static std::vector<void*> g_vFreed;
static int g_nVtCall = 0;
static void* g_pVtLast = nullptr;
static uint64_t g_uVtFlags = 0;
static void* s_pOuter = nullptr;

// a node: left, parent, right, key, ..., _Isnil
struct SNode {
    SNode* m_pLeft;
    SNode* m_pParent;
    SNode* m_pRight;
    uint32_t m_uKey;
    uint8_t m_pad[0x45];   // _Isnil @+0x61
    uint8_t m_abNil;
};

static SNode s_head;   // _Isnil = 1

static void MkNode(SNode* p, uint32_t k) {
    memset(p, 0, sizeof(SNode));
    p->m_uKey = k;
    p->m_abNil = 0;
}

// build: root=20, left=10, right=30
static SNode s_n10, s_n20, s_n30;
static char s_outer[0x48];
static SNode s_anchor;   // anchor[0] = the map owner

static void BuildTree() {
    memset(&s_head, 0, sizeof s_head);
    s_head.m_abNil = 1;
    MkNode(&s_n10, 10); MkNode(&s_n20, 20);
    MkNode(&s_n30, 30);
    // links (the MSVC tree: the leaves' children
    // point at the head sentinel)
    s_n20.m_pLeft = &s_n10; s_n20.m_pRight = &s_n30;
    s_n10.m_pParent = &s_n20; s_n30.m_pParent = &s_n20;
    s_n10.m_pLeft = &s_head; s_n10.m_pRight = &s_head;
    s_n30.m_pLeft = &s_head; s_n30.m_pRight = &s_head;
    s_n20.m_pParent = &s_head;
    s_head.m_pLeft = &s_n10;      // first
    s_head.m_pRight = &s_n30;     // last
    s_head.m_pParent = &s_n20;    // root
    // the outer: map@+8 with head@+0x38, size@+0x40
    memset(s_outer, 0, sizeof s_outer);
    // map[0] = the anchor; anchor[0] = the owner
    // (owner+0x30 = the checked head slot)
    static char mapbase[0x40];
    memset(mapbase, 0, sizeof mapbase);
    *(void**)(s_outer + 8) = mapbase;
    *(void**)&s_anchor.m_pLeft = mapbase;    // anchor[0] = owner
    *(void**)mapbase = &s_anchor;  // map[0] = anchor
    *(void**)(mapbase + 0x30) = &s_head;  // map head
    // the owner check reads owner+0x30
    *(void**)(mapbase + 0x30) = &s_head;
    *(void**)(s_outer + 0x38) = &s_head;
    *(uint64_t*)(s_outer + 0x40) = 3;
}

static void Bind() {
    g_fnMeritOpNew = [](size_t n) -> void* {
        return malloc(n); };
    g_fnMeritOpDelete = [](void* p) {
        g_vFreed.push_back(p); free(p); };
    g_pCrossMeritVft = (void*)0x77;
    g_pMeritDatInstance = nullptr;
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnNodeAlloc = []() -> void* {
        SNode* p = (SNode*)malloc(sizeof(SNode));
        memset(p, 0, sizeof(SNode));
        return p; };
    g_fnTreeDtor = [](void* pMap) {
        g_vDtor.push_back(pMap); };
    g_fnTreeClearOuter = [](void* pOuter) {
        g_vClearOuter.push_back(pOuter); };
    g_fnTreeInsert = [](void* pMap,
                       uint32_t* pKey) -> int64_t {
        g_vIns.push_back(pMap);
        g_vKeys.push_back(*pKey);
        return 1; };
    g_fnTreeClearNodes = [](void* pMap, void* pNode) {
        g_vClearNodes.push_back(pNode); };
    g_fnMeritLogFactory = []() -> void* {
        return (void*)0x55; };
    g_fnMeritLogWrite = [](void* pT, uint32_t uKey,
                           int n) {
        g_vLog.push_back(
            to_string((size_t)pT) + ":"
            + to_string(uKey) + ":" + to_string(n));
    };
}

// the vtable for the deleting dtor path
static void* VtDtor(void* p, uint64_t uF) {
    ++g_nVtCall; g_pVtLast = p; g_uVtFlags = uF;
    free(p);
    return p;
}
static void* s_vt[1] = { nullptr };

int main() {
    Bind();
    s_vt[0] = (void*)VtDtor;

    // ---- 1. MeritCtor (14173f600) ----
    {
        char outer[0x40];
        memset(outer, 0, sizeof outer);
        void* r = MeritCtor(outer);
        assert(r == outer);
        // mgr[0] = the anchor; anchor[0] = mgr
        void* anchor = *(void**)outer;
        assert(anchor != nullptr);
        assert(*(void**)anchor == outer);
        // the head: _Isnil=1, self links, size=0
        char* head = *(char**)(outer + 0x30);
        assert(head != nullptr);
        assert((uint8_t)head[0x61] == 1);
        assert(*(void**)(head + 8) == head);
        assert(*(void**)head == head);
        assert(*(void**)(head + 0x10) == head);
        assert(*(uint64_t*)(outer + 0x38) == 0);
        puts("D27-1 ctor ok");
    }

    // ---- 2. MeritInsert (14173f4b0) ----
    {
        g_vIns.clear(); g_vKeys.clear();
        static char outer[0x48];
        memset(outer, 0, sizeof outer);
        MeritInsert(outer, 1234);
        assert(g_vIns.size() == 1
            && g_vIns[0] == (void*)(outer + 8));
        assert(g_vKeys.size() == 1
            && g_vKeys[0] == 1234);
        puts("D27-2 insert ok");
    }

    // ---- 3. MeritDtorAnchor (14173f3e0) ----
    {
        g_vDtor.clear(); g_vFreed.clear();
        static char outer[0x48];
        memset(outer, 0, sizeof outer);
        void* mem = malloc(8);
        *(void**)outer = mem;
        MeritDtorAnchor(outer);
        assert(g_vDtor.size() == 1
            && g_vDtor[0] == outer);
        assert(g_vFreed.size() == 1
            && g_vFreed[0] == mem);
        puts("D27-3 anchor dtor ok");
    }

    // ---- 4. MeritDtorVft (14173f410) ----
    {
        g_vDtor.clear(); g_vFreed.clear();
        static char outer[0x48];
        memset(outer, 0, sizeof outer);
        void* mem = malloc(8);
        *(void**)(outer + 8) = mem;
        MeritDtorVft(outer);
        assert(*(void**)outer == (void*)0x77);
        assert(g_vDtor.size() == 1
            && g_vDtor[0] == (void*)(outer + 8));
        assert(g_vFreed.size() == 1
            && g_vFreed[0] == mem);
        puts("D27-4 vft dtor ok");
    }

    // ---- 5. MeritDeletingDtor (14173f450) ----
    {
        g_vClearOuter.clear(); g_nVtCall = 0;
        char* outer = (char*)malloc(0x48);
        memset(outer, 0, 0x48);
        *(void**)outer = s_vt;
        MeritDeletingDtor(outer);
        assert(g_vClearOuter.size() == 1
            && g_vClearOuter[0] == outer);
        assert(g_nVtCall == 1);
        assert(g_pVtLast == outer);
        assert(g_uVtFlags == 1);
        // the null path: clear, no vt call
        g_nVtCall = 0;
        MeritDeletingDtor(nullptr);
        assert(g_vClearOuter.size() == 2);
        assert(g_nVtCall == 0);
        puts("D27-5 deleting dtor ok");
    }

    // ---- 6. MeritStaticDispatch (14173f490) ----
    {
        g_vClearOuter.clear();
        g_pMeritDatInstance = nullptr;
        g_nVtCall = 0;
        MeritStaticDispatch(0, 0, 0, 0);
        assert(g_vClearOuter.empty());
        char* inst = (char*)malloc(0x48);
        memset(inst, 0, 0x48);
        *(void**)inst = s_vt;
        g_pMeritDatInstance = inst;
        MeritStaticDispatch(0, 0, 0, 0);
        assert(g_vClearOuter.size() == 1);
        assert(g_nVtCall == 1);
        // (inst was freed by the vt deleting dtor)
        g_pMeritDatInstance = nullptr;
        puts("D27-6 static dispatch ok");
    }

    // ---- 7. MeritWalkAndClear (14173f4d0) ----
    {
        BuildTree();
        g_vLog.clear(); g_nInvalid = 0;
        g_vClearNodes.clear();
        MeritWalkAndClear(s_outer);
        // the in-order walk: 10, 20, 30 (each logged
        // with target 0x55, level 3)
        assert(g_vLog.size() == 3);
        assert(g_vLog[0] == "85:10:3");
        assert(g_vLog[1] == "85:20:3");
        assert(g_vLog[2] == "85:30:3");
        assert(g_nInvalid == 0);
        // the final clear: e240(map, head->parent=root)
        assert(g_vClearNodes.size() == 1);
        assert(g_vClearNodes[0] == (void*)&s_n20);
        // head relinks + size=0
        assert(s_head.m_pParent == &s_head);
        assert(s_head.m_pLeft == &s_head);
        assert(s_head.m_pRight == &s_head);
        assert(*(uint64_t*)(s_outer + 0x40) == 0);
        puts("D27-7 walk and clear ok");
    }

    // ---- 8. the debug checks (verbatim firing) ----
    {
        BuildTree();
        // repoint map[0] at a fake owner whose head
        // slot (+0x30) collides with a real node —
        // the ownership check fires at that visit
        static char fakeOwner[0x40];
        memset(fakeOwner, 0, sizeof fakeOwner);
        *(void**)(fakeOwner + 0x30) = &s_n20;
        char** mapbase = *(char***)(s_outer + 8);
        *(void**)mapbase = fakeOwner;
        g_vLog.clear(); g_nInvalid = 0;
        MeritWalkAndClear(s_outer);
        assert(g_nInvalid >= 1);   // at the 20 visit
        assert(g_vLog.size() == 3);  // the walk still
        // completes — the original aborts inside
        // _invalid_parameter_noinfo; the counter seam
        // lets the walk continue
        puts("D27-8 debug checks ok");
    }

    puts("SYNDICATE-D27-OK: CCrossMeritMgr shell literal — anchor dtor (tree dtor + delete[0]), vft dtor variant (map@+8), deleting dtor (tree clear + vt[0](p,1) + the null path), the DAT_141886cd0 singleton dispatch, the u32 key insert (map@+8), the in-order walk with the MSVC ++ (right descent / leftmost / parent climb / past-the-end) + the anchor ownership checks + the per-key log + the final clear (e240 from the root, head relinks, size=0), the ctor (opnew(8) anchor + the head node: _Isnil=1 + the self links + size=0)");
    return 0;
}

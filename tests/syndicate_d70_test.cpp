// tests/syndicate_d70_test.cpp — the syndicate::
// FUN_141771f90 league BeRob broadcast (unit D70). The
// D69 message family is REAL (linked); the container kit +
// name getters + the logic vt are test fakes that honor the
// raw layouts: container {proxy@0, head@+0x30, size@+0x38},
// kit node (isnil@+0x1d), mgr node (isnil@+0x61, value map
// @+0x20). Verbatim facts checked: the 10-entry cap, the
// zero-id skip, the /1000000 and mode==2 gates, the (A)/(B)
// nesting inversion, the (D) range unions into mgr+0x470 +
// the result set, the (E) walked-key inserts + type-4 sends,
// the name-failure skip, the aggregate type-2/type-4 blocks
// with the flush-and-restart dance, and the teardown order.
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"
#include "modules/syndicate/src/SyndicateLeagueBeRob.h"
#include "modules/syndicate/src/SyndicateModule.h"
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

using namespace syndicate;

static int g_fail = 0;
#define CHECK(cond, name) do { \
    if (cond) printf("  ok  %s\n", name); \
    else { printf("  FAIL %s\n", name); g_fail = 1; } \
} while (0)
#define SECT(n) printf("== %s ==\n", n)

// ============ the call recorder ============
struct Rec {
    std::string tag; uint64_t a = 0, b = 0, c = 0, d = 0;
};
static std::vector<Rec> g_calls;
static void C(const std::string& tag, uint64_t a = 0, uint64_t b = 0,
              uint64_t c = 0, uint64_t d = 0) {
    g_calls.push_back({tag, a, b, c, d});
}
static int Count(const std::string& s) {
    int n = 0;
    for (auto& r : g_calls) if (r.tag == s) n++;
    return n;
}
static bool HasTag(const std::string& s, uint64_t a,
                   uint64_t b = 0, bool bCheckB = false) {
    for (auto& r : g_calls)
        if (r.tag == s && r.a == a &&
            (!bCheckB || r.b == b)) return true;
    return false;
}
static void Reset() { g_calls.clear(); }

// ============ the fake container kit ============
// container: {proxy@0, head@+0x30 (kit: isnil@+0x1d), size@+0x38}
static void* RdP(void* p, size_t o) { return *(void**)((char*)p + o); }
static void WrP(void* p, size_t o, void* v) { *(void**)((char*)p + o) = v; }
static void SelfLink(void* h) {
    WrP(h, 0, h); WrP(h, 8, h); WrP(h, 0x10, h);
    *(unsigned char*)((char*)h + 0x1d) = 1;
}
// the MGR-map head: the 0x68 node flavor (isnil@+0x61)
static void* FakeMgrHeadAlloc() {
    char* n = (char*)calloc(1, 0x68);
    *(unsigned char*)(n + 0x1c) = 1;
    WrP(n, 0, n); WrP(n, 8, n); WrP(n, 0x10, n);
    *(unsigned char*)(n + 0x61) = 1;
    return n;
}
static void FakeMgrMapInit(void* pMap) {
    char* m = (char*)pMap; memset(m, 0, 0x40);
    void* proxy = malloc(8); *(void**)proxy = m; WrP(m, 0, proxy);
    WrP(m, 0x30, FakeMgrHeadAlloc());
}
static void* FakeHeadAlloc() {               // FUN_141726c30
    char* n = (char*)calloc(1, 0x20);
    *(unsigned char*)(n + 0x1c) = 1;
    return n;
}
static void FakeMapInit(void* pMap) {
    char* m = (char*)pMap; memset(m, 0, 0x40);
    void* proxy = malloc(8); *(void**)proxy = m; WrP(m, 0, proxy);
    void* head = FakeHeadAlloc(); SelfLink(head);
    WrP(m, 0x30, head);
}
static void* FakeMapCtor(void* pMap) {       // FUN_141731fc0
    FakeMapInit(pMap); C("mapctor", (uint64_t)(uintptr_t)pMap);
    return pMap;
}
static void* FakeMapInsertKey(void* pMap, void* pOut, uint32_t* pKey);
static void FakeIterAdvance(void* pIter);
// deep-clone src's kit tree into dst (dst keeps its OWN
// proxy + head; the keys are re-inserted in tree order via
// the same BST insert the flow itself uses)
static void CloneKitTree(void* pDst, void* pSrc) {
    void* srcHead = RdP(pSrc, 0x30);
    void* cur = RdP(srcHead, 0);          // head->left = first
    char out[16];
    while (cur != srcHead) {
        uint32_t k = *(uint32_t*)((char*)cur + 0x18);
        FakeMapInsertKey(pDst, out, &k);
        uint64_t it[2] = { (uint64_t)(uintptr_t)RdP(pSrc, 0),
                           (uint64_t)(uintptr_t)cur };
        FakeIterAdvance(it);
        cur = (void*)(uintptr_t)it[1];
    }
}
static void FreeKitMap(void* pMap) {
    char* m = (char*)pMap;
    void* head = RdP(m, 0x30);
    void* proxy = RdP(m, 0);
    if (head == nullptr) return;
    std::vector<void*> toFree;
    void* cur = RdP(head, 0);          // head->_Left = the first
    while (cur != head) {              // in-order to the head
        toFree.push_back(cur);
        uint64_t it[2] = { (uint64_t)(uintptr_t)proxy,
                           (uint64_t)(uintptr_t)cur };
        FakeIterAdvance(it);
        cur = (void*)(uintptr_t)it[1];
        if (toFree.size() > 100000) break;   // safety valve
    }
    for (void* n : toFree) free(n);
    free(head);
    WrP(m, 0x30, nullptr);
    *(uint64_t*)(m + 0x38) = 0;
}
static void FakeTreeDtor(void* pMap) {       // FUN_14172c560
    FreeKitMap(pMap);
    C("treedtor", (uint64_t)(uintptr_t)pMap);
}


static void* FakeMapMoveCtor(void* pDst, void* pSrc) {  // FUN_1417695b0
    FakeMapInit(pDst);
    free(RdP(pDst, 0x30));   // the throwaway init head
    WrP(pDst, 0x30, RdP(pSrc, 0x30));       // steal the tree
    *(uint64_t*)((char*)pDst + 0x38) = *(uint64_t*)((char*)pSrc + 0x38);
    // the husk: a fresh empty head (proxy stays)
    void* sh = FakeHeadAlloc(); SelfLink(sh);
    WrP(pSrc, 0x30, sh);
    *(uint64_t*)((char*)pSrc + 0x38) = 0;
    C("movector", (uint64_t)(uintptr_t)pSrc);
    return pDst;
}
static void* FakePairMake(void* pPair, uint32_t uKey, void* pSrc) { // 14176f690
    *(uint32_t*)pPair = uKey;
    FakeMapMoveCtor((char*)pPair + 8, pSrc);
    FakeTreeDtor(pSrc);
    free(RdP(pSrc, 0));                      // operator_delete(proxy)
    C("pairmake", uKey);
    return pPair;
}
// the kit BST insert (isnil@+0x1d nodes)
static void* FakeMapInsertKey(void* pMap, void* pOut, uint32_t* pKey) { // 14172ae00
    char* m = (char*)pMap;
    void* head = RdP(m, 0x30);
    void* cur = RdP(head, 8);   // root (head->parent)
    void* parent = head;
    bool bLeft = true;
    while (*(unsigned char*)((char*)cur + 0x1d) == 0) {
        parent = cur;
        if (*pKey < *(uint32_t*)((char*)cur + 0x18)) {
            bLeft = true; cur = RdP(cur, 0);
        } else { bLeft = false; cur = RdP(cur, 0x10); }
    }
    char* n = (char*)calloc(1, 0x28);
    *(uint32_t*)(n + 0x18) = *pKey;
    WrP(n, 8, parent);
    if (parent == head) {  // first node
        SelfLink(head);
        WrP(head, 8, n);  // parent = root
        WrP(head, 0, n); WrP(head, 0x10, n);   // left = right = n
        WrP(n, 0, head); WrP(n, 0x10, head);  // nil children
    } else {
        if (bLeft) { WrP(parent, 0, n); } else { WrP(parent, 0x10, n); }
        WrP(n, 0, head); WrP(n, 0x10, head);
        // MSVC head bookkeeping: _Left = leftmost, _Right = rightmost
        void* lm = RdP(head, 0);
        if (lm == head || *pKey < *(uint32_t*)((char*)lm + 0x18))
            WrP(head, 0, n);
        void* rm = RdP(head, 0x10);
        if (rm == head || *(uint32_t*)((char*)rm + 0x18) < *pKey)
            WrP(head, 0x10, n);
    }
    *(uint64_t*)(m + 0x38) += 1;
    *(uint64_t*)pOut = (uint64_t)(uintptr_t)RdP(m, 0);   // proxy
    *(uint64_t*)((char*)pOut + 8) = (uint64_t)(uintptr_t)n;
    C("inskey", (uint64_t)*pKey, (uint64_t)(uintptr_t)pMap);
    return pMap;
}
// the MGR lower bound (isnil@+0x61 nodes)
static void* FakeMapLowerBound(void* pMap, void* pOut, uint32_t* pKey) { // 141760e40
    char* m = (char*)pMap;
    void* head = RdP(m, 0x30);
    void* cur = RdP(head, 8);   // root
    void* best = head;
    while (*(unsigned char*)((char*)cur + 0x61) == 0) {
        if (*(uint32_t*)((char*)cur + 0x18) < *pKey) cur = RdP(cur, 0x10);
        else { best = cur; cur = RdP(cur, 0); }
    }
    *(uint64_t*)pOut = (uint64_t)(uintptr_t)RdP(m, 0);
    if ((best == head) || (*pKey < *(uint32_t*)((char*)best + 0x18))) {
        *(uint64_t*)((char*)pOut + 8) = (uint64_t)(uintptr_t)head;
    } else {
        *(uint64_t*)((char*)pOut + 8) = (uint64_t)(uintptr_t)best;
    }
    C("lbound", *pKey, (uint64_t)(uintptr_t)pMap);
    return pOut;
}
static void* FakeMapInsertPair(void* pMap, void* pOut, void* pPair) { // 141770ea0
    char* m = (char*)pMap;
    void* head = RdP(m, 0x30);
    uint32_t key = *(uint32_t*)pPair;
    void* cur = RdP(head, 8); void* parent = head; bool bLeft = true;
    while (*(unsigned char*)((char*)cur + 0x61) == 0) {
        parent = cur;
        if (key < *(uint32_t*)((char*)cur + 0x18)) { bLeft = true; cur = RdP(cur, 0); }
        else { bLeft = false; cur = RdP(cur, 0x10); }
    }
    char* n = (char*)calloc(1, 0x68);       // the mgr node
    *(uint32_t*)(n + 0x18) = key;
    *(unsigned char*)(n + 0x61) = 0;
    FakeMapInit(n + 0x20);                   // the value map
    // CLONE the pair's D tree into the value map (insert
    // COPIES the map value; D is freed by the caller after)
    char* pD = (char*)pPair + 8;
    CloneKitTree(n + 0x20, pD);
    // link into the mgr tree
    if (parent == head) {
        WrP(head, 8, n); WrP(head, 0, n); WrP(head, 0x10, n);
        WrP(n, 0, head); WrP(n, 0x10, head);
        *(unsigned char*)(n + 0x61) = 0;
    } else {
        if (bLeft) WrP(parent, 0, n); else WrP(parent, 0x10, n);
        WrP(n, 0, head); WrP(n, 0x10, head);
    }
    WrP(n, 8, parent);          // the parent link (successor walks)
    // MSVC head bookkeeping: _Left = leftmost, _Right = rightmost
    void* lm = RdP(head, 0);
    if (lm == head ||
        *(uint32_t*)(n + 0x18) < *(uint32_t*)((char*)lm + 0x18))
        WrP(head, 0, n);
    void* rm = RdP(head, 0x10);
    if (rm == head ||
        *(uint32_t*)((char*)rm + 0x18) < *(uint32_t*)(n + 0x18))
        WrP(head, 0x10, n);
    *(uint64_t*)(m + 0x38) += 1;
    *(uint64_t*)pOut = (uint64_t)(uintptr_t)RdP(m, 0);
    *(uint64_t*)((char*)pOut + 8) = (uint64_t)(uintptr_t)n;
    C("inspair", key, *(uint64_t*)(pD + 0x38));
    return pOut;
}
static void FakeIterAdvance(void* pIter) {   // FUN_141724ed0
    void** it = (void**)pIter;
    void* n = it[1];
    void* head = it[0] ? RdP(RdP(it[0], 0), 0x30) : nullptr;
    void* r = RdP(n, 0x10);
    if (r != head && *(unsigned char*)((char*)r + 0x1d) == 0) {
        void* cur = r;
        while (*(unsigned char*)((char*)RdP(cur, 0) + 0x1d) == 0)
            cur = RdP(cur, 0);
        it[1] = cur;
        return;
    }
    void* p = RdP(n, 8);
    while (p != head && RdP(p, 0x10) == n) { n = p; p = RdP(p, 8); }
    it[1] = p;
}
static void FakeInsertKeyRange(void* pMap, void* pFirst, void* pLast) { // 141762f60
    void** f = (void**)pFirst; void** l = (void**)pLast;
    char tmpOut[16];
    while (f[1] != l[1]) {
        uint32_t k = *(uint32_t*)((char*)f[1] + 0x18);
        FakeMapInsertKey(pMap, tmpOut, &k);
        uint64_t it2[2] = { (uint64_t)(uintptr_t)f[0],
                            (uint64_t)(uintptr_t)f[1] };
        FakeIterAdvance(it2);
        f[1] = (void*)(uintptr_t)it2[1];
        C("rangeinsert", k, (uint64_t)(uintptr_t)pMap);
    }
}
static void* FakeEraseRange(void* pMap, void* pOut, void* pF, void* pL) { // 14172a410
    void** f = (void**)pF; void** l = (void**)pL;
    char* m = (char*)pMap; void* head = RdP(m, 0x30);
    std::vector<void*> toFree;      // collect, THEN free: the
    while (f[1] != l[1]) {          // successor walk must not
        void* n = f[1];             // touch freed parents
        uint64_t it2[2] = { (uint64_t)(uintptr_t)f[0],
                            (uint64_t)(uintptr_t)n };
        FakeIterAdvance(it2);
        f[1] = (void*)(uintptr_t)it2[1];
        toFree.push_back(n);
        *(uint64_t*)(m + 0x38) -= 1;
    }
    for (void* n : toFree) free(n);
    WrP(m, 0, head); SelfLink(head);
    *(uint64_t*)pOut = (uint64_t)(uintptr_t)RdP(m, 0);
    *(uint64_t*)((char*)pOut + 8) = (uint64_t)(uintptr_t)head;
    C("eraseall", (uint64_t)(uintptr_t)pMap);
    return pOut;
}

// ============ the D69 seams (real family) ============
static void* s_vtPb[16]; static void* s_vtEntry[2];
static int g_nInit = 0;
static void FakeTqInit(void*) { ++g_nInit; }
static void* FakeOpNew(size_t n) { void* p = calloc(1, n + 16); return p; }
static void FakeOpDel(void* p) { free(p); }
static void FakeOpDelArr(void* p) { free(p); }
static void FakePbDefaultInit() {}
static char FakeSerialize(void*, void*, size_t cap) {
    C("pbser", cap); return 1;
}
static const int* FakeIntMax(const int* a, const int* b) {
    return (*a >= *b) ? a : b;
}
static void FakePbBaseDtor(void*) {}
static uint64_t g_cachedSize = 8;
static uint64_t FakeGetCachedSize(void*) { return g_cachedSize; }
static char FakeIsInit(void*) { return 0; }
static char g_errInline = 1;
static uint64_t FakeErrString(void*, void* pOut) {
    char* p = (char*)pOut;
    if (g_errInline) { *(uint64_t*)(p + 0x20) = 5; memcpy(p + 8, "abcde", 6); }
    else { *(uint64_t*)(p + 0x20) = 0x11;
           *(uint64_t*)(p + 8) = (uint64_t)(uintptr_t)"heap-error"; }
    return (uint64_t)(uintptr_t)pOut;
}
static int g_nClear = 0;
static void FakePbClear(void*) { ++g_nClear; }
static void FakeEntryDeletingDtor(void* p, uint64_t) {
    ((std::string*)((char*)p + 8))->~basic_string();
    free(p);
}
// the PB object's name slot: D69's SetName manages a
// string via op_new(0x28); the fake op_new returns calloc so
// the name lives; the test asserts the assigned name.
static const std::string* LastMsgName(const void* pMsg) {
    char* pb = (char*)pMsg + 0x408;
    std::string* pName = *(std::string**)(pb + 0x40);
    return pName;
}

// ============ the manager fixture ============
static void* MgNext(void* n, void* head) {
    void* r = RdP(n, 0x10);
    if (r != head && *(unsigned char*)((char*)r + 0x61) == 0) {
        void* cur = r;
        while (*(unsigned char*)((char*)RdP(cur, 0) + 0x61) == 0)
            cur = RdP(cur, 0);
        return cur;
    }
    void* p = RdP(n, 8);
    while (p != head && RdP(p, 0x10) == n) { n = p; p = RdP(p, 8); }
    return p;
}
struct Mgr {
    char ab[0x500];
    void* maps[5];      // +0x3f0, +0x430, +0x470, +0x370, +0x3b0
    void* logic;
    Mgr() {
        memset(ab, 0, sizeof(ab));
        logic = calloc(1, 8);
        WrP(ab, 8, logic);
        *(int32_t*)(ab + 0x35c) = 2;      // the league mode
        *(uint32_t*)(ab + 0x358) = 0xAA;  // the field-0x358 id
        // EMBED the containers at the raw offsets (the real
        // layout: the maps live INSIDE the manager object)
        size_t offs[5] = { 0x3f0, 0x430, 0x470, 0x370, 0x3b0 };
        for (int i = 0; i < 5; i++) {
            FakeMgrMapInit(ab + offs[i]);
            maps[i] = ab + offs[i];
        }
    }
    ~Mgr() {
        // free every mgr map: nodes (+ their value maps), the
        // heads, and the proxies (keeps ASan leak-free)
        for (int i = 0; i < 5; i++) {
            char* m = (char*)maps[i];
            void* head = RdP(m, 0x30);
            void* proxy = RdP(m, 0);
            if (head) {
                std::vector<void*> toFree;
                void* cur = RdP(head, 0);
                while (cur != head) {
                    toFree.push_back(cur);
                    cur = MgNext(cur, head);
                    if (toFree.size() > 100000) break;
                }
                for (void* n : toFree) {
                    char* val = (char*)n + 0x20;
                    FreeKitMap(val);
                    free(RdP(val, 0));
                    free(n);
                }
                free(head);
            }
            free(RdP(m, 0));
        }
        free(logic);
    }
    // insert an mgr node with a value map pre-filled with keys
    void* AddNode(int iMap, uint32_t key, std::vector<uint32_t> valKeys) {
        char* m = (char*)maps[iMap];
        void* head = RdP(m, 0x30);
        void* cur = RdP(head, 8); void* parent = head; bool bL = true;
        while (*(unsigned char*)((char*)cur + 0x61) == 0) {
            parent = cur;
            if (key < *(uint32_t*)((char*)cur + 0x18)) { bL = true; cur = RdP(cur, 0); }
            else { bL = false; cur = RdP(cur, 0x10); }
        }
        char* n = (char*)calloc(1, 0x68);
        *(uint32_t*)(n + 0x18) = key;
        *(unsigned char*)(n + 0x61) = 0;
        FakeMapInit(n + 0x20);
        char out[16];
        for (uint32_t k : valKeys) FakeMapInsertKey(n + 0x20, out, &k);
        if (parent == head) {
            WrP(head, 8, n); WrP(head, 0, n); WrP(head, 0x10, n);
            WrP(n, 0, head); WrP(n, 0x10, head);
        } else {
            if (bL) WrP(parent, 0, n); else WrP(parent, 0x10, n);
            WrP(n, 0, head); WrP(n, 0x10, head);
            void* lm = RdP(head, 0);
            if (lm == head || key < *(uint32_t*)((char*)lm + 0x18))
                WrP(head, 0, n);
            void* rm = RdP(head, 0x10);
            if (rm == head || *(uint32_t*)((char*)rm + 0x18) < key)
                WrP(head, 0x10, n);
        }
        WrP(n, 8, parent);       // the parent link
        *(uint64_t*)(m + 0x38) += 1;
        return n;
    }
};

// ============ the logic vt seams ============
static uint64_t g_myLeague = 0;
static uint64_t FakeMyLeague(void* pLogic) {
    C("myl");
    return g_myLeague;
}
static void FakeSend(void* pLogic, uint64_t uPlayer, void* pMsg,
                     uint64_t uFlag) {
    // the player id rides rdx: uVar18 % 1000000
    C("send", uPlayer, (uint64_t)(uintptr_t)pMsg, uFlag);
}

// ============ the name getters ============
static bool g_nameFail = false;
static bool g_nEmptyIdName = false;     // return an EMPTY buffer
static bool g_nLeagueNameFail = false;  // the fallback fails
static int* g_pLeagueNameCount = nullptr;
static int FakeGetNameById(void*, uint32_t, char* pOut, int) {
    if (g_nameFail) return 0;
    if (g_nEmptyIdName) { memset(pOut, 0, 16); return 1; }
    strcpy(pOut, "MemberName");
    return 1;
}
static int FakeGetLeagueName(void*, uint32_t, char* pOut, int) {
    if (g_pLeagueNameCount) (*g_pLeagueNameCount)++;
    if (g_nLeagueNameFail) return 0;
    if (g_nameFail) return 0;
    strcpy(pOut, "LeagueName");
    return 1;
}

static void Wire() {
    // the D70 seams
    g_fnLbrOpNew = FakeOpNew;
    g_fnLbrOpDelete = FakeOpDel;
    g_fnLbrInvalid = []() { C("invalid"); };
    g_fnLbrHeadAlloc = FakeHeadAlloc;
    g_fnLbrMapCtor = FakeMapCtor;
    g_fnLbrMapInsertKey = FakeMapInsertKey;
    g_fnLbrMapMoveCtor = FakeMapMoveCtor;
    g_fnLbrPairMake = FakePairMake;
    g_fnLbrMapLowerBound = FakeMapLowerBound;
    g_fnLbrMapInsertPair = FakeMapInsertPair;
    g_fnLbrMapTreeDtor = FakeTreeDtor;
    g_fnLbrMapEraseRange = FakeEraseRange;
    g_fnLbrIterAdvance = FakeIterAdvance;
    g_fnLbrMapInsertKeyRange = FakeInsertKeyRange;
    g_fnLbrGetNameById = FakeGetNameById;
    g_fnLbrGetLeagueName = FakeGetLeagueName;
    g_fnLbrGetMyLeague = FakeMyLeague;
    g_fnLbrSendMsg = FakeSend;
    // the D69 seams
    g_pTqCMsgVft = (void*)0x111;
    g_pVtPbMessageLite = (void*)0x222;
    g_pVtCMsgLeagueBeRob = (void*)0x333;
    g_pVtCMsgLeagueBeRobPB = s_vtPb;
    g_pVtCMsgLeagueBeRobRePB = s_vtEntry;
    g_pPbDefaultInstance = (void*)0x666;
    g_fnTqCMsgInit = FakeTqInit;
    g_fnOpNew = FakeOpNew;
    g_fnOpDelete = FakeOpDel;
    g_fnOpDeleteArr = FakeOpDelArr;
    g_fnPbDefaultInit = FakePbDefaultInit;
    g_fnPbSerializeToArray = FakeSerialize;
    g_fnPbIntMax = FakeIntMax;
    static const int s_floor = 4;
    g_pPbReserveFloor = &s_floor;
    g_fnPbBaseDtor = FakePbBaseDtor;
    s_vtPb[3] = (void*)FakePbClear;
    s_vtPb[4] = (void*)FakeIsInit;
    s_vtPb[5] = (void*)FakeErrString;
    s_vtPb[8] = (void*)FakeGetCachedSize;
    s_vtEntry[0] = (void*)FakeEntryDeletingDtor;
}

int main() {
    Wire();

    SECT("D70-gates");
    {
        Reset();
        Mgr mgr;
        uint32_t zeros[3] = { 1, 2, 3 };
        LeagueBeRobBroadcast(&mgr, 0, 3, zeros);
        LeagueBeRobBroadcast(&mgr, 77, 0, nullptr);
        CHECK(g_calls.empty(), "key=0 / count=0 -> nothing happens");
    }

    SECT("D70-cap-skip");
    {
        Reset();
        Mgr mgr;
        *(int32_t*)(mgr.ab + 0x35c) = 1;   // (C)/aggregate off here
        g_myLeague = 0;
        std::vector<uint32_t> ids = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        LeagueBeRobBroadcast(&mgr, 5000001, (int)ids.size(), ids.data());
        // (A) insert: 10 non... 12 ids, one zero -> processed:
        // ids with a member id: 1,2,3,4,5,6,7,8,9,10 (the 10-cap)
        // 12 ids: the cap counts ITERATIONS (the zero id is one)
        // -> 10 iterations = ids 1,0,2..9 -> 9 non-zero members
        printf("  [dbg cap inskey=%d]\n", Count("inskey"));
        for (auto& r : g_calls) if (r.tag == "inskey")
            printf("  [inskey a=%llu map=%llx]\n",
                   (unsigned long long)r.a,
                   (unsigned long long)r.b);
        // 18 flow inserts (A: 1 absent + 8 found, B: 9) + the 10
        // pair-insert CLONE re-inserts (the fake insert copies
        // the map by re-inserting every key)
        CHECK(Count("inskey") == 18 + 10,
              "10-cap (iterations): A+B inserts + pair-clone copies");
        CHECK(!HasTag("inskey", 11), "the 11th id never inserted");
        CHECK(Count("send") == 0, "no sends (myLeague=0)");
    }

    SECT("D70-AB-nesting");
    {
        Reset();
        Mgr mgr;
        g_myLeague = 0;
        std::vector<uint32_t> ids = { 77 };
        LeagueBeRobBroadcast(&mgr, 9000017, 1, ids.data());
        // (A): mgr+0x3f0 keyed 9000017, inner insert member 77
        CHECK(HasTag("lbound", 9000017, (uint64_t)(uintptr_t)mgr.maps[0], true),
              "(A) lower bound mgr+0x3f0 by the league key");
        CHECK(HasTag("inskey", 77), "(A) member id in the inner map");
        CHECK(HasTag("inspair", 9000017), "(A) pair inserted into mgr+0x3f0");
        // (B): mgr+0x430 keyed 77 (the member), inner key = the league key
        CHECK(HasTag("inskey", 9000017),
              "(B) inline descent: the league id in the inner map");
        CHECK(HasTag("inspair", 77), "(B) pair inserted into mgr+0x430");
        // the second member: (A) now FOUND -> insert into the value map
        uint32_t two[2] = { 77, 78 };
        LeagueBeRobBroadcast(&mgr, 9000017, 2, two);
        // 77 exists in mgr+0x430; the (B) inner insert goes to the
        // found node's value map, no new mgr+0x430 pair
        int n77pairs = 0;
        for (auto& r : g_calls)
            if (r.tag == "inspair" && r.a == 77) n77pairs++;
        CHECK(n77pairs == 1, "member 77 present -> no duplicate pair");
    }

    SECT("D70-C-msg");
    {
        Reset();
        Mgr mgr;
        g_myLeague = 9;        // member 9000005 / 1000000 == 9
        g_cachedSize = 8;
        uint32_t ids[1] = { 9000005 };
        LeagueBeRobBroadcast(&mgr, 9000017, 1, ids);
        CHECK(Count("send") == 2,
              "(C) send + the aggregate type-2 final send");
        if (Count("send") == 1) {
            Rec& s = g_calls[0];
            CHECK(s.a == 9000005 % 1000000, "send to member%1000000");
            CHECK(s.c == 0, "the vt+0xb8 flag is 0");
        }
        CHECK(HasTag("pbser", 0x3fc), "the msg was serialized");
        // myLeague(9) == 9000017/1000000 -> the aggregate RUNS:
        // (C) 1 + type-2 final 1 + type-4 final 1 (the result
        // set is EMPTY here -> GetCount==0 -> NO type-4 send)
        CHECK(Count("send") == 2,
              "(C) send + the aggregate type-2 final send");
    }

    SECT("D70-C-namefail");
    {
        Reset();
        Mgr mgr;
        g_myLeague = 9;
        g_nameFail = true;
        uint32_t ids[1] = { 9000005 };
        LeagueBeRobBroadcast(&mgr, 9000017, 1, ids);
        CHECK(Count("send") == 0, "name fetch failed -> no (C) msg");
        CHECK(!HasTag("lbound", 9000017,
                      (uint64_t)(uintptr_t)mgr.maps[2], true),
              "name failure SKIPS (D)/(E) (no mgr+0x470 lookup)");
        g_nameFail = false;
    }

    SECT("D70-D-union");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(3, 42, { 101, 102 });  // mgr+0x370[42] keys
        mgr.AddNode(4, 42, { 103 });       // mgr+0x3b0[42] keys
        g_myLeague = 0;
        uint32_t ids[1] = { 42 };
        LeagueBeRobBroadcast(&mgr, 5000017, 1, ids);
        // (D): the ranges went into mgr+0x470[5000017]'s inner
        // map AND the result set: keys 101,102,103 twice each
        int n101 = 0, n103 = 0;
        for (auto& r : g_calls)
            if (r.tag == "rangeinsert") {
                if (r.a == 101) n101++;
                if (r.a == 103) n103++;
            }
        CHECK(n101 == 2, "key 101 copied into BOTH the inner map "
                         "and the result set");
        CHECK(n103 == 2, "key 103 copied from mgr+0x3b0 into both");
        CHECK(HasTag("inspair", 5000017),
              "(D) the league pair inserted into mgr+0x470");
    }

    SECT("D70-E-walk");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(3, 77, { 2000001, 2000002 });  // walked keys
        g_myLeague = 2;    // 2000001/1000000 == 2
        uint32_t ids[1] = { 77 };
        LeagueBeRobBroadcast(&mgr, 5000017, 1, ids);
        // (E): mgr+0x470 lookups by 2000001 and 2000002
        CHECK(HasTag("lbound", 2000001, (uint64_t)(uintptr_t)mgr.maps[2], true),
              "(E) walked key lower bound in mgr+0x470");
        CHECK(HasTag("inskey", 5000017),
              "(E) the league key inserted into the walked entries");
        CHECK(HasTag("inspair", 2000001),
              "(E) the pair for the walked key inserted");
        // sends: the (E) type-4 msgs to 2000001%1000000=1 and
        // 2000002%1000000=2 — but only when myLeague ==
        // key/1000000: 2000001/1e6=2==2 ok; 2000002/1e6=2 ok
        int nE = 0;
        for (auto& r : g_calls)
            if (r.tag == "send" && r.a <= 2) nE++;
        CHECK(nE == 2, "the (E) type-4 sends to both walked members");
        // no aggregate: myLeague(2) != 5000017/1000000 (5)
        CHECK(Count("eraseall") >= 1, "the result set torn down");
    }

    SECT("D70-aggregate");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(3, 5000009, { 601 });   // keyed by the MEMBER id
        g_myLeague = 5;                // == 5000017/1000000
        g_cachedSize = 8;
        uint32_t ids[3] = { 5000009, 0, 5000010 };
        LeagueBeRobBroadcast(&mgr, 5000017, 3, ids);
        // (C) msg for 5000009 (5 == 5000009/1e6) — and 5000010 (5)
        // aggregate: type-2 with all non-zero ids + the type-4
        // over the result set {601}
        int nSends = Count("send");
        CHECK(nSends == 4, "2 (C) sends + type-2 + type-4 finals");
        CHECK(HasTag("send", 5000017 % 1000000),
              "the aggregate sends go to key%1000000");
        CHECK(Count("pbser") == 4,
              "2 (C) + type-2 + type-4 serializes (the appends "
              "made both aggregate msgs non-empty)");
    }

    SECT("D70-flush-restart");
    {
        Reset();
        Mgr mgr;
        g_myLeague = 5;
        // append 1 ok, then the size gate forces every later
        // append to fail -> flush + re-Create + re-append
        g_cachedSize = 0x3fd;
        uint32_t ids[2] = { 5000009, 5000010 };
        LeagueBeRobBroadcast(&mgr, 5000017, 2, ids);
        // the type-2 pass: append 5000009 fails (0x3fd+4 >= 0x400)
        // -> serialize+send, clear, re-create, re-append
        int nFlushSends = 0;
        for (auto& r : g_calls)
            if (r.tag == "send" && r.a == 5000017 % 1000000)
                nFlushSends++;
        CHECK(nFlushSends >= 2,
              "the flush dance sends at least twice (type-2 and "
              "type-4 restarts)");
        g_cachedSize = 8;
    }

    SECT("D70-name-fallback");
    {
        Reset();
        Mgr mgr;
        g_myLeague = 5;
        // the by-id name returns an EMPTY buffer -> the byte
        // walk (-2) -> the league-name fallback runs
        int nLeagueNames = 0;
        g_nEmptyIdName = true;   // the by-id getter: empty buf
        g_pLeagueNameCount = &nLeagueNames;
        uint32_t ids[1] = { 5000009 };
        LeagueBeRobBroadcast(&mgr, 5000017, 1, ids);
        CHECK(nLeagueNames >= 2,
              "empty member name -> the league-name fallback "
              "(the (C) fetch + the aggregate retry)");
        // the fallback FAILING -> the early return
        Reset();
        g_nLeagueNameFail = true;
        uint32_t ids2[1] = { 5000009 };
        LeagueBeRobBroadcast(&mgr, 5000017, 1, ids2);
        CHECK(Count("send") == 0,
              "the aggregate name fallback failure -> the early "
              "return (no aggregate sends)");
        // restore
        g_nEmptyIdName = false;
        g_nLeagueNameFail = false;
        g_pLeagueNameCount = nullptr;
    }

    if (g_fail == 0) printf("D70-LEAGUE-BE-ROB-FLOW-OK\n");
    else printf("D70-LEAGUE-BE-ROB-FLOW-FAIL\n");
    return g_fail;
}

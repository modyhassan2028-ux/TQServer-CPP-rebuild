// tests/syndicate_d72_test.cpp — the syndicate::
// FUN_14176b0d0 PlunderWarStart (unit D72). The
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
#include "modules/syndicate/src/SyndicateLeagueRobOptFlow.h"
#include "modules/syndicate/src/SyndicateLeagueRobOptClass.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateLeagueSalary.h"
#include "modules/syndicate/src/SyndicateInviteNotify.h"
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


// ============ the D72-specific seams ============
static uint32_t g_myTextLeague = 777;
static void* FakeTextName(void* pLogic) {
    C("textname", (uint64_t)(uintptr_t)pLogic);
    return (void*)0x1;
}
static void* FakeTextNameById(void* pLogic, uint32_t uId) {
    C("textnamebyid", (uint64_t)(uintptr_t)pLogic, uId);
    return (void*)0x1;
}
static void FakeTalk(void* pLogic, uint32_t uKey,
                     const char* pText, uint64_t uZero,
                     uint16_t uTag) {
    C("talk", (uint64_t)(uintptr_t)pLogic, uKey,
      (uint64_t)(uintptr_t)pText, uTag);
    (void)uZero;
}
static void FakeSendLeagueOpt(void* pLogic, uint32_t uKey,
                              void* pMsg) {
    C("sendopt", (uint64_t)(uintptr_t)pLogic, uKey,
      (uint64_t)(uintptr_t)pMsg);
}
static void FakeBroadcast45(void* pLogic, void* pMsg) {
    C("bcast45", (uint64_t)(uintptr_t)pLogic,
      (uint64_t)(uintptr_t)pMsg);
}
static void* s_pLocalTarget = nullptr;
static void* FakeFindLocalTarget(void*, uint32_t uId) {
    C("findlocal", uId);
    return s_pLocalTarget;
}
static const char* s_pTargetName = nullptr;
static const char* FakeTargetName(void* pObj) {
    C("tgtname", (uint64_t)(uintptr_t)pObj);
    return s_pTargetName ? s_pTargetName : "TargetN";
}
static const char* s_pSupportName = nullptr;
static const char* FakeSupportName(void* pObj) {
    C("supname", (uint64_t)(uintptr_t)pObj);
    return s_pSupportName ? s_pSupportName : "SupportN";
}
static bool g_crossFail = false;
static int FakeResolveCross(void*, uint32_t uId, void* pOut) {
    C("cross", uId);
    if (g_crossFail) return 0;
    memcpy((char*)pOut + 0x34, "CrossN", 7);
    return 1;
}
static void FakeSafeCopy(char* pDst, const char* pSrc,
                         size_t n) {
    C("safecopy", (uint64_t)(uintptr_t)pSrc, n);
    // tq::SafeCopy semantics: bounded by NUL, never past n
    size_t k = 0;
    while (k < n && pSrc[k] != 0) k++;
    memcpy(pDst, pSrc, k);
    pDst[k] = 0;
}
static void FakeSnprintf(char* pDst, size_t n,
                        const char* pFmt) {
    snprintf(pDst, n, "%s", pFmt);
}
static void FakeLogErr(const char* pFmt, uint64_t uArg) {
    C("log", (uint64_t)(uintptr_t)pFmt, uArg);
}
// the string manager (D66 pattern)
static void* FakeStrMgrInstance() { return (void*)0x55; }
static const char* s_pFmtStr = "PWSFMT";
static void* FakeStrMgrGetStr(void*, const char* psz) {
    C("getstr", (uint64_t)(uintptr_t)psz);
    return (void*)(uintptr_t)s_pFmtStr;
}
// the 1417d6820 LeagueOpt Create fake
static bool FakeLeagueOptCreate(void* pMsg, uint32_t uType,
                                const char* psz, uint32_t a,
                                uint32_t uActor,
                                uint32_t b) {
    C("optcreate", uType, (uint64_t)(uintptr_t)psz,
      uActor);
    (void)pMsg; (void)a; (void)b;
    return true;
}
// CStrPacker fakes for the LeagueOpt ctor/dtor
static void FakePackerCtor(void*) { C("packerctor"); }
static void FakePackerSetBuf(void*, char*, size_t, bool) {
    C("packersetbuf");
}
static void FakePackerDtor(void*) { C("packerdtor"); }
// D71 log seams (fail paths must not fire here)
static void FakeLogRobOptErr(const void*, const char*) { C("robopterr"); }
static void FakeLogRobOptFail(const void*) {}
static void* FakeCheckBuild(void*, int, const void*, int) {
    return nullptr;
}
static void* FakeCheckText(void*, const void*) {
    return nullptr;
}
static void FakeCheckStream(void*, void*) {}
static void FakeCheckDone(void*) {}
static char FakePbParse(void*, const void* p, int n) {
    (void)p; (void)n; return 1;
}

static void WireD72() {
    // the D72 flow seams
    g_fnPwsGetMyLeague = FakeMyLeague;
    g_fnPwsSendMsg = FakeSend;
    g_fnPwsTextName = FakeTextName;
    g_fnPwsTextNameById = FakeTextNameById;
    g_fnPwsTalk = FakeTalk;
    g_fnPwsSendLeagueOpt = FakeSendLeagueOpt;
    g_fnPwsBroadcast45 = FakeBroadcast45;
    g_fnPwsFindLocalTarget = FakeFindLocalTarget;
    g_fnPwsTargetName = FakeTargetName;
    g_fnPwsSupportName = FakeSupportName;
    g_fnPwsResolveCrossName = FakeResolveCross;
    g_fnPwsSafeCopy = FakeSafeCopy;
    g_fnPwsSnprintf = FakeSnprintf;
    g_fnPwsLogErr = FakeLogErr;
    g_fnPwsInvalid = []() { C("invalid"); };
    g_fnStringMgrInstance = FakeStrMgrInstance;
    g_fnStringMgrGetStr = FakeStrMgrGetStr;
    g_fn1417d6820 = FakeLeagueOptCreate;
    // the LeagueOpt ctor/dtor packer seams
    g_fnCStrPackerCtor = FakePackerCtor;
    g_fnCStrPackerSetBuf = FakePackerSetBuf;
    g_fnCStrPackerDtor = FakePackerDtor;
    // the D71 family
    g_pVtCMsgLeagueRobOpt = (void*)0x444;
    g_pVtCMsgLeagueRobOptPB = s_vtPb;
    g_pVtCMsgLeagueRobOptServer = s_vtEntry;
    g_fnPbParseFromArray = FakePbParse;
    g_fnLogRobOptErr = FakeLogRobOptErr;
    g_fnLogRobOptFail = FakeLogRobOptFail;
    g_fnPbCheckBuild = FakeCheckBuild;
    g_fnPbCheckText = FakeCheckText;
    g_fnPbCheckStream = FakeCheckStream;
    g_fnPbCheckDone = FakeCheckDone;
}

int main() {
    Wire();
    WireD72();

    SECT("D72-gates");
    {
        Reset();
        Mgr mgr;
        g_myLeague = 0;
        PlunderWarStart(&mgr, 0);
        CHECK(g_calls.empty(),
              "flag=0 -> nothing at all");
        CHECK(*(uint32_t*)(mgr.ab + 0x35c) == 2,
              "ctor default mgr+0x35c = 2");
    }
    {
        Reset();
        Mgr mgr;
        g_myLeague = 0;
        PlunderWarStart(&mgr, 0x5A);
        CHECK(*(int32_t*)(mgr.ab + 0x358) == 0x5A,
              "flag -> mgr+0x358");
        CHECK(*(uint32_t*)(mgr.ab + 0x35c) == 2,
              "mgr+0x35c = 2");
        CHECK(Count("bcast45") == 1,
              "empty maps -> only the 0x45 broadcast");
    }

    SECT("D72-phaseA");
    {
        Reset();
        Mgr mgr;
        // outer key 5000001 (server 5); the RAW reads the
        // anchor league-full id from the FIRST inner
        // node's key: 5000011 -> league 5 == myLeague ->
        // the textname (my-league) branch
        mgr.AddNode(3, 5000001, { 5000011, 5000012 });
        g_myLeague = 5;
        g_cachedSize = 8;
        PlunderWarStart(&mgr, 0x5A);
        // the D71 msg: Create(4,0) + serialize + send
        CHECK(HasTag("send", 1),
              "phaseA: send key%1e6 = 1");
        CHECK(Count("pbser") >= 1,
              "phaseA: D71 or D69 serialize ran");
        // the D69 type-1 create ran -> pbser + appends
        CHECK(Count("talk") == 1,
              "phaseA: the talk broadcast");
        CHECK(HasTag("optcreate", 0x3f),
              "phaseA: LeagueOpt 0x3f create");
        CHECK(Count("sendopt") == 1,
              "phaseA: LeagueOpt sent");
        CHECK(Count("textname") == 1,
              "phaseA: my-league text-name path");
        CHECK(Count("bcast45") == 1, "the closing 0x45");
    }

    SECT("D72-phaseA-names");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(3, 5000001, { 11 });
        g_myLeague = 5;
        // .170 fails -> log + skip (no .250 retry here:
        // the retry only fires on the EMPTY-buffer -2 walk)
        g_nameFail = true;
        PlunderWarStart(&mgr, 1);
        CHECK(Count("log") == 1,
              "phaseA: .170 fail -> the log");
        CHECK(Count("talk") == 0,
              "phaseA: name fail skips the talk");
        g_nameFail = false;
    }

    SECT("D72-phaseB");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(4, 6000002, { 21 });      // mgr+0x3b0
        g_myLeague = 6;
        PlunderWarStart(&mgr, 1);
        CHECK(Count("optcreate") >= 1 &&
              HasTag("optcreate", 0x47),
              "phaseB: LeagueOpt 0x47 create");
        CHECK(Count("sendopt") == 1,
              "phaseB: the LeagueOpt send");
        CHECK(Count("textnamebyid") == 1,
              "phaseB: the other-league name path");
    }

    SECT("D72-phaseC-local");
    {
        Reset();
        Mgr mgr;
        // targets map +0x3f0: outer 7000003, inner target
        // full 9000045 -> target league 9 == myLeague 7? no
        // -> cross. Use inner 7000045: league 7 == myLeague
        mgr.AddNode(0, 7000003, { 7000045 });
        g_myLeague = 7;
        s_pLocalTarget = (void*)0x99;
        PlunderWarStart(&mgr, 1);
        CHECK(Count("findlocal") == 1 &&
              HasTag("findlocal", 45),
              "phaseC: local target by full%1e6 = 45");
        CHECK(Count("tgtname") == 1,
              "phaseC: the target-name getter");
        CHECK(Count("safecopy") >= 1,
              "phaseC: SafeCopy ran");
    }

    SECT("D72-phaseC-cross");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(0, 7000003, { 8000045 });
        g_myLeague = 7;
        PlunderWarStart(&mgr, 1);
        CHECK(Count("cross") == 1 && HasTag("cross", 8000045),
              "phaseC: cross-server resolve by full id");
        CHECK(Count("tgtname") == 0,
              "phaseC: no local getter on cross");
    }

    SECT("D72-phaseC-crossfail");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(0, 7000003, { 8000045 });
        g_myLeague = 7;
        g_crossFail = true;
        PlunderWarStart(&mgr, 1);
        CHECK(Count("log") == 1,
              "phaseC: cross fail -> the log + skip");
        g_crossFail = false;
    }

    SECT("D72-phaseD");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(1, 7000003, { 7000045 });
        g_myLeague = 7;
        s_pLocalTarget = (void*)0x77;
        PlunderWarStart(&mgr, 1);
        CHECK(Count("supname") == 1,
              "phaseD: the SUPPORT name getter");
        CHECK(Count("findlocal") == 1,
              "phaseD: local find ran");
    }

    SECT("D72-phaseE");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(2, 7000009, { 31 });      // mgr+0x470
        g_myLeague = 7;
        PlunderWarStart(&mgr, 1);
        // type-4 create + the unconditional final flush:
        // send with key%1e6 = 9 (the D69 msg itself)
        CHECK(HasTag("send", 9),
              "phaseE: the final sweep send");
        CHECK(Count("talk") == 0,
              "phaseE: no talk");
        // wrong server: nothing
        Reset();
        Mgr mgr2;
        mgr2.AddNode(2, 7000009, { 31 });
        g_myLeague = 3;
        PlunderWarStart(&mgr2, 1);
        CHECK(!HasTag("send", 9),
              "phaseE: other-server entry skipped");
    }

    SECT("D72-flush-dance");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(3, 5000001, { 11 });
        g_myLeague = 5;
        g_cachedSize = 0x500;    // every AppendDword fails
        int nSend1 = 0;
        for (auto& r : g_calls)
            if (r.tag == "send" && r.a == 1) nSend1++;
        PlunderWarStart(&mgr, 1);
        int nSend1b = 0;
        for (auto& r : g_calls)
            if (r.tag == "send" && r.a == 1) nSend1b++;
        CHECK(nSend1b - nSend1 == 2,
              "dance: D71 send + the dance send (key 1)");
        CHECK(g_nClear >= 1, "dance: the Clear ran");
        g_cachedSize = 8;
    }

    SECT("D72-empty-retry");
    {
        Reset();
        Mgr mgr;
        mgr.AddNode(3, 5000001, { 11 });
        g_myLeague = 5;
        g_nEmptyIdName = true;    // .170 returns an EMPTY
                                  // 16-byte buffer -> the
                                  // -2 walk -> .250 retry
        PlunderWarStart(&mgr, 1);
        CHECK(Count("talk") == 1,
              "retry: .250 name used, phaseA completes");
        g_nEmptyIdName = false;
    }

    if (g_fail) { printf("D72-FAIL\n"); return 1; }
    printf("D72-OK\n");
    return 0;
}

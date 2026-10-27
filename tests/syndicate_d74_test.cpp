// tests/syndicate_d74_test.cpp — the syndicate::
// FUN_141765920/141765d60 accept handlers (unit D73). The
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
#include "modules/syndicate/src/SyndicateLeaguePlunderAccept.h"
#include "modules/syndicate/src/SyndicateLeagueAddTodayPlunder.h"
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
static bool HasStr(const std::string& tag, const char* psz) {
    for (auto& r : g_calls)
        if (r.tag == tag && r.a != 0 &&
            strcmp((const char*)r.a, psz) == 0) return true;
    return false;
}
static bool HasAB(const std::string& tag, uint64_t a, uint64_t b) {
    for (auto& r : g_calls)
        if (r.tag == tag && r.a == a && r.b == b) return true;
    return false;
}
static bool HasAC(const std::string& tag, uint64_t a, uint64_t c) {
    for (auto& r : g_calls)
        if (r.tag == tag && r.a == a && r.c == c) return true;
    return false;
}

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
}
static void* FakeCheckText(void*, const void*) {
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


// ============ the D73 (Pwa) seams ============
static char g_warOpen = 1;
static char FakeWarOpenGate(void*) { return g_warOpen; }
static void FakeTalkSend(void*, int nUser, const char* psz) {
    C("talksend", (uint64_t)nUser, (uint64_t)(uintptr_t)psz);
}
static char g_alive = 1;
static int g_nAlive = 0;
static char FakeAliveGate(void*, int) { g_nAlive++; return g_alive; }
static int32_t g_userLeague = 7;
static int32_t FakeGetUserLeague(void*, int nUser) {
    C("getul", (uint64_t)nUser);
    return g_userLeague;
}
static uint32_t g_unionKey = 5000001;
static uint32_t FakeGetUnionKey(void*, int nUser, int32_t nL) {
    C("getkey", (uint64_t)nUser, (uint64_t)nL);
    return g_unionKey;
}
static char g_mapInfoOk = 1;
static uint64_t g_posPacked = 0x1122334455667788ULL;
static char FakeGetMapInfo(void*, int, void* p20, void* p18,
                           void* p10) {
    C("getmapinfo");
    if (!g_mapInfoOk) return 0;
    *(uint32_t*)p20 = 0x1002;
    *(uint16_t*)p18 = 0x300;
    *(uint64_t*)p10 = g_posPacked;
    return 1;
}
static char g_transmit = 1;
static char FakeCheckMapTransmit(void*, int nUser, uint32_t a,
                                 uint32_t b, uint64_t p) {
    C("transmit", (uint64_t)nUser, a, b, p);
    return g_transmit;
}
static int32_t g_userState = 9;
static int g_nSetState = 0;
static int32_t FakeGetUserState(void*, int) { return g_userState; }
static void FakeSetUserState(void*, int nUser, int32_t n) {
    C("setstate", (uint64_t)nUser, (uint64_t)n);
    g_nSetState++;
}
static char g_localOk = 1;
static int g_nLocal = 0;
static char FakeEnterLocalMap(void*, int nUser, uint32_t uMap,
                              uint64_t uPos) {
    C("local", (uint64_t)nUser, uMap, uPos);
    g_nLocal++;
    return g_localOk;
}
static uint32_t g_userLeague2 = 999;
static uint32_t FakeGetUserLeague2(void*, int) { return g_userLeague2; }
static char g_osGate = 1;
static char FakeCheckEnterOs(void*, int nUser) {
    C("osgate", (uint64_t)nUser);
    return g_osGate;
}
static char g_canEnter = 1;
static char FakeCheckCanEnter(void*, int nUser) {
    C("canenter", (uint64_t)nUser);
    return g_canEnter;
}
static char g_osLeague = 1;
static char FakeEnterOsLeague(void*, int nUser, uint32_t uL) {
    C("osleague", (uint64_t)nUser, uL);
    return g_osLeague;
}
static int g_nTeleport = 0;
static void FakeTeleport(void*, int nUser, uint32_t uL,
                         uint32_t uMap, uint64_t uPos,
                         uint32_t uX) {
    C("teleport", (uint64_t)nUser, uL, uMap, uPos);
    g_nTeleport++;
    (void)uX;
}
static char g_replyGate = 0;
static char FakeWarReplyGate(void*, int nUser) {
    C("reply", (uint64_t)nUser);
    return g_replyGate;
}

static void WireD73() {
    g_fnPwaWarOpenGate = FakeWarOpenGate;
    g_fnPwaTalkSend = FakeTalkSend;
    g_fnPwaAliveGate = FakeAliveGate;
    g_fnPwaGetUserLeague = FakeGetUserLeague;
    g_fnPwaGetUnionKey = FakeGetUnionKey;
    g_fnPwaGetMapInfo = FakeGetMapInfo;
    g_fnPwaCheckMapTransmit = FakeCheckMapTransmit;
    g_fnPwaGetUserState = FakeGetUserState;
    g_fnPwaSetUserState = FakeSetUserState;
    g_fnPwaEnterLocalMap = FakeEnterLocalMap;
    g_fnPwaGetUserLeague2 = FakeGetUserLeague2;
    g_fnPwaCheckEnterOs = FakeCheckEnterOs;
    g_fnPwaCheckCanEnter = FakeCheckCanEnter;
    g_fnPwaEnterOsLeague = FakeEnterOsLeague;
    g_fnPwaTeleport = FakeTeleport;
    g_fnPwaWarReplyGate = FakeWarReplyGate;
}


// ============ the D74 fakes ============
static uint64_t g_my74 = 5;
static uint64_t FakeMy74(void*) { return g_my74; }
static void* FakeOpNew74(size_t n) { return malloc(n); }
static int g_nDel74 = 0;
static void FakeOpDelete74(void* p) { g_nDel74++; free(p); }
static void* FakeHeadAlloc74() {
    // all three isnil flavors (+0x1c the fixture kit walk,
    // +0x1d the D72 kit, +0x61 the mgr trees) so the
    // fixture ctor/teardown and the kit stay compatible
    char* h = (char*)calloc(1, 0x68);
    *(unsigned char*)(h + 0x1c) = 1;
    *(unsigned char*)(h + 0x1d) = 1;
    *(unsigned char*)(h + 0x61) = 1;
    ((void**)h)[0] = h; ((void**)h)[1] = h; ((void**)h)[2] = h;
    return h;
}
// 14172ae00 — find-or-add on the +0x1d-isnil trees
static void* FakeInsKey74(void* pCell, void* pOut, uint32_t* pKey) {
    char* cell = (char*)pCell;
    char* head = *(char**)(cell + 0x30);
    char* cur = *(char**)(head + 8);
    char* parent = head; bool bLeft = true; char* found = nullptr;
    while (*(unsigned char*)(cur + 0x1d) == 0) {
        uint32_t k = *(uint32_t*)(cur + 0x18);
        if (*pKey < k) { parent = cur; bLeft = true; cur = *(char**)cur; }
        else if (k < *pKey) { parent = cur; bLeft = false; cur = *(char**)(cur + 0x10); }
        else { found = cur; break; }
    }
    uint64_t* it = (uint64_t*)pOut;
    if (found) {
        it[0] = (uint64_t)(uintptr_t)*(void**)cell; it[1] = (uint64_t)(uintptr_t)found;
        C("inskey", *pKey, 1); return pOut;
    }
    char* n = (char*)calloc(1, 0x28);
    *(uint32_t*)(n + 0x18) = *pKey;
    *(char**)(n + 8) = parent;
    *(char**)(n + 0) = head; *(char**)(n + 0x10) = head;
    if (parent == head) *(char**)(head + 8) = n;
    else if (bLeft) *(char**)parent = n;
    else *(char**)(parent + 0x10) = n;
    // maintain head[0] = leftmost (FreeKitMap walks it)
    char* lm = *(char**)(head + 8);
    while (*(char**)lm != head) lm = *(char**)lm;
    *(char**)head = lm;
    *(uint64_t*)(cell + 0x38) += 1;   // the size
    it[0] = (uint64_t)(uintptr_t)*(void**)cell; it[1] = (uint64_t)(uintptr_t)n;
    C("inskey", *pKey, 0);
    return pOut;
}
// 1417695b0 — the map move-ctor (clone the wrapper)
static char* FreshHead74() {
    char* h = (char*)calloc(1, 0x68);
    *(unsigned char*)(h + 0x1c) = 1;
    *(unsigned char*)(h + 0x1d) = 1;
    *(unsigned char*)(h + 0x61) = 1;
    ((void**)h)[0] = h; ((void**)h)[1] = h; ((void**)h)[2] = h;
    return h;
}
static void* FakeMove74(void* pDst, void* pSrc) {
    // STEAL semantics: share the tree pointer (the single
    // owner frees it); clone the wrapper for the dst
    memcpy(pDst, pSrc, 0x40);
    void* w = malloc(8);
    *(void**)w = pDst;
    *(void**)pDst = w;
    C("move");
    return pDst;
}
// 14176f690 — pair make (SHALLOW container copy)
static void* FakePair74(void* pPair, uint32_t uKey, void* pSrc) {
    *(uint32_t*)pPair = uKey;
    memcpy((char*)pPair + 8, pSrc, 0x40);   // share both
    C("pairmake", uKey);
    return pPair;
}
// 141770ea0 — mgr-map insert (the +0x61 BST)
static void* FakeInsPair74(void* pMap, void* pOutIter, void* pPair) {
    char* cell = (char*)pMap;
    char* head = *(char**)(cell + 0x30);
    uint32_t key = *(uint32_t*)pPair;
    char* cur = *(char**)(head + 8);
    char* parent = head; bool bLeft = true;
    while (*(unsigned char*)(cur + 0x61) == 0) {
        parent = cur;
        if (key < *(uint32_t*)(cur + 0x18)) { bLeft = true; cur = *(char**)cur; }
        else { bLeft = false; cur = *(char**)(cur + 0x10); }
    }
    char* n = (char*)calloc(1, 0x68);
    *(uint32_t*)(n + 0x18) = key;
    *(char**)(n + 8) = parent;
    *(char**)(n + 0) = head; *(char**)(n + 0x10) = head;
    if (parent == head) *(char**)(head + 8) = n;
    else if (bLeft) *(char**)parent = n;
    else *(char**)(parent + 0x10) = n;
    // maintain head[0] = leftmost (the Mgr dtor walks it)
    char* lm = *(char**)(head + 8);
    while (*(char**)lm != head) lm = *(char**)lm;
    *(char**)head = lm;
    memcpy(n + 0x20, (char*)pPair + 8, 0x40);
    *(void**)(n + 0x20 + 0x30) = FreshHead74();   // fresh tree
    void* w = malloc(8);
    *(void**)w = n + 0x20;
    *(void**)(n + 0x20) = w;
    ((uint64_t*)pOutIter)[0] = (uint64_t)(uintptr_t)w;
    ((uint64_t*)pOutIter)[1] = (uint64_t)(uintptr_t)n;
    C("inspair", key);
    return pOutIter;
}
static void FreeTreeNodes74(char* head) {
    // free every kit node from the ROOT slot (head+8),
    // keep the head itself (its owner frees it)
    if (!head) return;
    std::vector<char*> st;
    char* n = *(char**)(head + 8);
    while (n != head || !st.empty()) {
        while (n != head) { st.push_back(n); n = *(char**)n; }
        if (st.empty()) break;
        char* c = st.back(); st.pop_back();
        char* r = *(char**)(c + 0x10);
        free(c);
        n = r;
    }
    ((void**)head)[0] = head;
    *(char**)(head + 8) = head;
    ((void**)head)[2] = head;
}
static void FakeTreeDtor74(void* p) {
    C("treedtor");
    (void)p;   // steal semantics: no free here
}
static void* FakeErase74(void* pMap, void* a, void* b, void* c) {
    C("erase");
    FreeTreeNodes74(*(char**)((char*)pMap + 0x30));
    *(uint64_t*)((char*)pMap + 0x38) = 0;   // size
    (void)a; (void)b; (void)c;
    return pMap;
}
static void FakeInvalid74() { C("invalid"); }
static void FakeLogErr74(const char* f, uint64_t u) {
    C("log", (uint64_t)(uintptr_t)f, u);
}
static char g_create74 = 1;
static void FakeMsgCtor74(void*) { C("msgctor"); }
static char FakeMsgCreate74(void*, int a, int b) {
    C("msgcreate", (uint64_t)a, (uint64_t)b);
    return g_create74;
}
static void FakeMsgSer74(void*) { C("msgser"); }
static void FakeMsgDtor74(void*) { C("msgdtor"); }
static void FakeSend74(void*, uint32_t uId, void*, void*, int f) {
    C("sendopt", uId, (uint64_t)f);
}
static bool HasLogStr(const char* psz, uint64_t u) {
    for (auto& r : g_calls)
        if (r.tag == "log" && r.a != 0 &&
            strstr((const char*)r.a, psz) != nullptr && r.b == u)
            return true;
    return false;
}
static int CountKey(const std::string& tag, uint64_t a) {
    int n = 0;
    for (auto& r : g_calls) if (r.tag == tag && r.a == a) n++;
    return n;
}

static void WireD74() {
    g_fnLbrGetMyLeague = FakeMy74;
    g_fnLbrOpNew = FakeOpNew74;
    g_fnLbrOpDelete = FakeOpDelete74;
    g_fnLbrHeadAlloc = FakeHeadAlloc74;
    g_fnLbrMapInsertKey = FakeInsKey74;
    g_fnLbrMapMoveCtor = FakeMove74;
    g_fnLbrPairMake = FakePair74;
    g_fnLbrMapInsertPair = FakeInsPair74;
    g_fnLbrMapTreeDtor = FakeTreeDtor74;
    g_fnLbrMapEraseRange = FakeErase74;
    g_fnLbrInvalid = FakeInvalid74;
    g_fnPwsLogErr = FakeLogErr74;
    g_fnAtpMsgCtor = FakeMsgCtor74;
    g_fnAtpMsgCreate = FakeMsgCreate74;
    g_fnAtpMsgSerialize = FakeMsgSer74;
    g_fnAtpMsgDtor = FakeMsgDtor74;
    g_fnAtpSendOptText = FakeSend74;
}

int main() {
    Wire(); WireD72(); WireD73(); WireD74();

    SECT("D74-gates");
    {
        Reset();
        Mgr mgr;
        AddTodayPlunderWarInfo(&mgr, 0, 3, nullptr);
        CHECK(g_calls.empty(), "id=0: nothing");
        uint32_t a1[1] = { 5000011 };
        AddTodayPlunderWarInfo(&mgr, 5000001, 0, a1);
        CHECK(g_calls.empty(), "count=0: nothing");
        AddTodayPlunderWarInfo(&mgr, 5000001, -1, a1);
        CHECK(g_calls.empty(), "count<0: nothing");
    }

    SECT("D74-happy");
    {
        Reset();
        Mgr mgr;
        uint32_t a1[3] = { 5000011, 5000012, 0 };
        AddTodayPlunderWarInfo(&mgr, 5000001, 3, a1);
        CHECK(Count("invalid") == 0, "no invalid anywhere");
        CHECK(CountKey("inskey", 5000001) == 2,
              "uIdPlunder into BOTH inner maps");
        CHECK(CountKey("inskey", 5000011) == 1 &&
              CountKey("inskey", 5000012) == 1,
              "the two targets into the outer map");
        CHECK(CountKey("inspair", 5000011) == 1 &&
              CountKey("inspair", 5000012) == 1,
              "the 0x3b0 inserts");
        CHECK(CountKey("inspair", 5000001) == 1,
              "the final 0x370 insert");
        CHECK(Count("sendopt") == 3,
              "two target sends + the final");
        CHECK(HasAB("sendopt", 11, 1) &&
              HasAB("sendopt", 12, 1),
              "target sends flag 1, id%1e6");
        CHECK(HasAB("sendopt", 1, 0),
              "the final send flag 0, id%1e6=1");
        CHECK(Count("msgctor") == 3 && Count("msgdtor") == 3,
              "3 ctor/dtor pairs");
        CHECK(Count("msgcreate") == 3, "3 creates (4,0)");
        CHECK(CountKey("msgcreate", 4) == 3, "create(4, 0) each");
        CHECK(Count("msgser") == 3, "3 serializes");
        CHECK(Count("erase") == 3,
              "2 inner erases + the outer teardown");
        CHECK(Count("log") == 0, "no repeat log");
    }

    SECT("D74-repeat");
    {
        Reset();
        Mgr mgr;
        uint32_t a1[2] = { 5000011, 5000012 };
        AddTodayPlunderWarInfo(&mgr, 5000001, 2, a1);
        Reset();
        AddTodayPlunderWarInfo(&mgr, 5000001, 2, a1);
        CHECK(HasLogStr("data repeat idPlunder", 5000001),
              "the repeat log fires and CONTINUES");
        CHECK(CountKey("inspair", 5000011) == 0,
              "second call: target FOUND (no new 0x3b0 node)");
        CHECK(CountKey("inskey", 5000001) == 2,
              "both targets FOUND: 2 existing-path inserts");
        CHECK(Count("sendopt") == 3,
              "second call still sends everything");
    }

    SECT("D74-cap-10");
    {
        Reset();
        Mgr mgr;
        uint32_t a12[12] = { 5000011, 5000012, 5000013,
            5000014, 5000015, 5000016, 5000017, 5000018,
            5000019, 5000020, 5000021, 5000022 };
        AddTodayPlunderWarInfo(&mgr, 5000001, 12, a12);
        int nOuter = 0;
        for (auto& r : g_calls)
            if (r.tag == "inskey" && r.a >= 5000011 &&
                r.a <= 5000022) nOuter++;
        CHECK(nOuter == 10, "the RAW hard cap: 10 targets");
        CHECK(CountKey("inspair", 5000001) == 1,
              "the final insert still runs");
    }

    SECT("D74-all-zero");
    {
        Reset();
        Mgr mgr;
        uint32_t az[3] = { 0, 0, 0 };
        AddTodayPlunderWarInfo(&mgr, 5000001, 3, az);
        CHECK(Count("inskey") == 0, "zero targets: no inserts");
        CHECK(Count("inspair") == 0, "no map inserts at all");
        CHECK(Count("sendopt") == 0, "no sends");
        CHECK(Count("erase") == 1, "the empty teardown");
    }

    SECT("D74-create-fail");
    {
        Reset();
        Mgr mgr;
        uint32_t a1[1] = { 5000011 };
        g_create74 = 0;
        AddTodayPlunderWarInfo(&mgr, 5000001, 1, a1);
        CHECK(Count("msgdtor") == 1 && Count("sendopt") == 0,
              "create fail: dtor, no send");
        CHECK(CountKey("inspair", 5000001) == 0,
              "create fail: NO final 0x370 insert");
        CHECK(CountKey("inspair", 5000011) == 1,
              "the 0x3b0 insert already happened (partial RAW)");
        CHECK(Count("erase") == 2,
              "inner teardown + the outer teardown");
        g_create74 = 1;
    }

    SECT("D74-wrong-league");
    {
        Reset();
        Mgr mgr;
        g_my74 = 3;                     // != 5
        uint32_t a1[2] = { 5000011, 3000013 };  // leagues 5, 3
        AddTodayPlunderWarInfo(&mgr, 5000001, 2, a1);
        CHECK(Count("sendopt") == 1 &&
              HasAB("sendopt", 13, 1),
              "only the matching league target sends");
        CHECK(CountKey("inspair", 5000001) == 1 &&
              HasAB("sendopt", 1, 0) == false,
              "wrong-league id: the final send is skipped");
        CHECK(CountKey("inskey", 5000011) == 1 &&
              CountKey("inskey", 3000013) == 1,
              "BOTH targets still enter the maps");
        g_my74 = 5;
    }

    if (g_fail) { printf("D74-FAIL\n"); return 1; }
    printf("D74-OK\n");
    return 0;
}

// tests/syndicate_d77_test.cpp — the syndicate::
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
#include "modules/syndicate/src/SyndicateLeaguePlunderList.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderQuery.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderStatus.h"
#include "modules/syndicate/src/SyndicateLeaguePlunderSignup.h"
#include "modules/syndicate/src/SyndicateLeagueSupportPublish.h"
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


// ============ the D75 fakes ============
static uint64_t g_warOn = 0, g_userLeague75 = 5000001;
static int g_createOk75 = 1, g_appendOk75 = 1, g_cnt75 = 0;
static void* g_league75 = nullptr;
static char g_name48[32] = "", g_name28[32] = "";
static std::vector<char*> g_mapK;

static char FakeSplWar(void*) { return (char)g_warOn; }
static uint32_t FakeSplULeague(void*) { return (uint32_t)g_userLeague75; }
static void FakeSplSend(void*, uint32_t u, void*) { C("sendmsg", u); }
static void FakeSplCtor(void*) { C("msgctor"); }
static char FakeSplCreate(void*, int a) {
    C("msgcreate", (uint64_t)a);
    return (char)g_createOk75;
}
static char FakeSplAppend(void*, uint32_t id, const char* nm) {
    C("append", id, (uint64_t)(uintptr_t)nm);
    if (g_appendOk75) g_cnt75++;   // only a success adds an entry
    return (char)g_appendOk75;
}
static void FakeSplFlush(void*) { C("flush"); }
static void FakeSplClear(void*) { C("clear"); g_cnt75 = 0; }
static int16_t FakeSplCount(void*) { C("count"); return (int16_t)g_cnt75; }
static void FakeSplDtor(void*) { C("msgdtor"); }
static void* FakeSplFind(void*, uint32_t id) {
    C("findleague", id);
    return g_league75;
}
static void* FakeSplName48F(void* l) {
    C("name48");
    return (l == g_league75) ? (void*)g_name48 : (void*)"";
}
static void* FakeSplName28F(void* l) {
    C("name28");
    return (l == g_league75) ? (void*)g_name28 : (void*)"";
}
static void* FakeSplLookup(void* pMap, void* pOut, uint32_t* pKey) {
    char* cell = (char*)pMap;
    char* head = *(char**)(cell + 0x30);
    C("lookup", *pKey);
    for (char* n : g_mapK)
        if (*(uint32_t*)(n + 0x18) == *pKey) {
            ((uint64_t*)pOut)[0] = (uint64_t)(uintptr_t)*(void**)cell;
            ((uint64_t*)pOut)[1] = (uint64_t)(uintptr_t)n;
            return pOut;
        }
    ((uint64_t*)pOut)[0] = (uint64_t)(uintptr_t)*(void**)cell;
    ((uint64_t*)pOut)[1] = (uint64_t)(uintptr_t)head;
    return pOut;
}
static void WireD75() {
    g_fnSplWarState = FakeSplWar;
    g_fnSplUserLeague = FakeSplULeague;
    g_fnSplSendMsg = FakeSplSend;
    g_fnSplMsgCtor = FakeSplCtor;
    g_fnSplMsgCreate = FakeSplCreate;
    g_fnSplMsgAppend = FakeSplAppend;
    g_fnSplMsgFlush = FakeSplFlush;
    g_fnSplMsgClear = FakeSplClear;
    g_fnSplMsgCount = FakeSplCount;
    g_fnSplMsgDtor = FakeSplDtor;
    g_fnSplFindLeague = FakeSplFind;
    g_fnSplName48 = FakeSplName48F;
    g_fnSplName28 = FakeSplName28F;
    g_fnSplLookup = FakeSplLookup;
}

// the RAW mgr fields for D75: the two NEW kit maps
// (mgr+0x108/0x138 and mgr+0x148/0x178, isnil@+0x21)
struct Mgr75 {
    char ab[0x200];
    char *headL, *headK;
    void *proxyL, *proxyK;
    char* logic;
    std::vector<char*> nodesL;
    Mgr75() {
        memset(ab, 0, sizeof(ab));
        logic = (char*)calloc(1, 8);
        *(void**)(ab + 8) = logic;
        // the war-list tree at +0x148 (head at +0x178)
        headL = (char*)calloc(1, 0x28);
        *(unsigned char*)(headL + 0x21) = 1;
        ((void**)headL)[0] = headL;
        ((void**)headL)[1] = headL;
        ((void**)headL)[2] = headL;
        proxyL = malloc(8);
        *(void**)proxyL = ab + 0x148;
        *(void**)(ab + 0x148) = proxyL;
        *(void**)(ab + 0x178) = headL;
        // the key map at +0x108 (head at +0x138)
        headK = (char*)calloc(1, 0x70);
        *(unsigned char*)(headK + 0x61) = 1;
        proxyK = malloc(8);
        *(void**)proxyK = ab + 0x108;
        *(void**)(ab + 0x108) = proxyK;
        *(void**)(ab + 0x138) = headK;
    }
    ~Mgr75() {
        for (char* n : nodesL) free(n);
        for (char* n : g_mapK) free(n);
        g_mapK.clear();
        free(headL); free(headK);
        free(proxyL); free(proxyK); free(logic);
    }
    void AddWar(uint32_t id, uint32_t key) {
        char* n = (char*)calloc(1, 0x28);
        *(uint32_t*)(n + 0x18) = id;
        *(uint32_t*)(n + 0x1c) = key;
        ((void**)n)[0] = headL; ((void**)n)[1] = headL;
        ((void**)n)[2] = headL;          // nil -> head
        if (*(void**)(headL + 8) == headL) {   // empty
            ((void**)headL)[1] = n;      // root
            ((void**)n)[1] = headL;      // parent = head
        } else {
            char* rm = ((char**)headL)[2];
            ((void**)rm)[2] = n;         // right child
            ((void**)n)[1] = rm;
        }
        ((void**)headL)[0] =             // leftmost (first)
            *(void**)(headL + 8) == (void*)n ? (void*)n
            : ((void**)headL)[0];
        ((void**)headL)[2] = n;          // rightmost
        nodesL.push_back(n);
    }
    void SetFirst(uint32_t u) { *(uint32_t*)(ab + 0x18) = u; }
};
static char* AddKey75(uint32_t key, const char* n48,
                      const char* n28) {
    char* n = (char*)calloc(1, 0x70);
    *(uint32_t*)(n + 0x18) = key;
    strcpy(n + 0x28, n28);
    strcpy(n + 0x48, n48);
    g_mapK.push_back(n);
    return n;
}
static bool HasAppend(uint64_t id, const char* nm) {
    for (auto& r : g_calls)
        if (r.tag == "append" && r.a == id && r.b != 0 &&
            strcmp((const char*)r.b, nm) == 0) return true;
    return false;
}
static std::string AppendOrder() {
    std::string s;
    for (auto& r : g_calls)
        if (r.tag == "append") s += std::to_string(r.a) + ",";
    return s;
}
static void Reset75() {
    g_createOk75 = 1; g_appendOk75 = 1; g_cnt75 = 0;
    g_league75 = nullptr; g_warOn = 0;
    g_userLeague75 = 5000001;
    g_name48[0] = 0; g_name28[0] = 0;
    Reset();
}


// ============ the D76 fakes ============
static uint32_t g_key76 = 0;
static int g_append76 = 1, g_cnt76 = 0;
static uint32_t FakeCqpKey(void*, uint32_t, int32_t) {
    return g_key76;
}
static uint16_t FakeCqpCount(void*) {
    C("count");
    return (uint16_t)g_cnt76;
}
// the RAW passes stack buffers; keep a stable copy at
// record time so later calls cannot clobber the content
static char g_names76[64][32];
static int g_nName76 = 0;
static uint64_t KeepName76(const char* s) {
    if (s == nullptr) return 0;
    if (g_nName76 >= 64) g_nName76 = 0;
    strncpy(g_names76[g_nName76], s, 31);
    g_names76[g_nName76][31] = 0;
    return (uint64_t)(uintptr_t)g_names76[g_nName76++];
}
static char FakeCqpAppend(void*, int32_t id, const char* s1,
                          const char* s2) {
    C("append", (uint64_t)id, KeepName76(s1));
    C("appendb", (uint64_t)id, KeepName76(s2));
    if (g_append76) g_cnt76++;
    return (char)g_append76;
}
static int FakeName76(void* p, uint32_t uId, char* pOut,
                      int nCap) {
    C("getname", uId);
    snprintf(pOut, nCap, "N%u", uId);
    return 0;
}
static void WireD76() {
    g_fnCqpMemberKey = FakeCqpKey;
    g_fnCqpMsgCount = FakeCqpCount;
    g_fnCqpMsgAppend = FakeCqpAppend;
    g_fnLbrGetLeagueName = FakeName76;
    g_fnLbrGetNameById = FakeName76;
}
static void Reset76() {
    g_key76 = 0; g_append76 = 1; g_cnt76 = 0;
    Reset75();
}
// the direct fixture: an outer mgr node with a REAL inner
// kit tree (FakeInsPair74 nodes own fresh empty trees by
// the D74 safety contract, so D76 builds its own nodes)
static char* MakeOuterNode76(uint32_t key,
                             std::vector<uint32_t> members) {
    char* n = (char*)calloc(1, 0x68);
    *(uint32_t*)(n + 0x18) = key;
    void* w = malloc(8);
    *(void**)w = n + 0x20;              // the wrapper
    *(void**)(n + 0x20) = w;
    *(void**)(n + 0x50) = FreshHead74();  // the inner tree
    for (uint32_t m : members) {
        uint32_t k = m;
        uint64_t it[2];
        FakeInsKey74(n + 0x20, it, &k);   // kit insert
    }
    return n;
}
static void InsertOuter76(void* pMap, char* n) {
    char* cell = (char*)pMap;
    char* head = *(char**)(cell + 0x30);
    uint32_t key = *(uint32_t*)(n + 0x18);
    char* cur = *(char**)(head + 8);
    char* parent = head; bool bLeft = true;
    while (*(unsigned char*)(cur + 0x61) == 0) {
        parent = cur;
        if (key < *(uint32_t*)(cur + 0x18)) {
            bLeft = true; cur = *(char**)cur;
        } else {
            bLeft = false; cur = *(char**)(cur + 0x10);
        }
    }
    *(char**)(n + 8) = parent;
    *(char**)(n + 0) = head;
    *(char**)(n + 0x10) = head;
    if (parent == head) *(char**)(head + 8) = n;
    else if (bLeft) *(char**)parent = n;
    else *(char**)(parent + 0x10) = n;
    // maintain the fixture dtor's leftmost walk
    char* lm = *(char**)(head + 8);
    while (*(char**)lm != head) lm = *(char**)lm;
    *(char**)head = lm;
}
// mgr+0x370 = {5000001 -> {11,12,13}},
// mgr+0x3b0 = {5000011 -> {5000001}}
static void Populate76(Mgr& mgr) {
    InsertOuter76(mgr.ab + 0x370,
        MakeOuterNode76(5000001,
            { 5000011, 5000012, 5000013 }));
    InsertOuter76(mgr.ab + 0x3b0,
        MakeOuterNode76(5000011, { 5000001 }));
    Reset();
    g_cnt76 = 0;
}
static bool HasAppend76(const std::string& tag, uint64_t id,
                        const char* nm) {
    for (auto& r : g_calls)
        if (r.tag == tag && r.a == id && r.b != 0 &&
            strcmp((const char*)r.b, nm) == 0) return true;
    return false;
}


// ============ the D77 fakes ============
static int g_create77 = 1, g_append77 = 1, g_cnt77 = 0;
static uint32_t g_emptyNameId77 = 0, g_nameFailId77 = 0;
static void FakeSusCtor(void*) { C("susctor"); }
static char FakeSusCreate(void*, int32_t t, uint32_t id,
                          uint32_t fl, const char* nm) {
    C("suscreate", (uint64_t)t, KeepName76(nm));
    C("suscreate2", id, fl);
    g_cnt77 = 0;      // a fresh msg
    return (char)g_create77;
}
static char FakeSusAppend(void*, uint32_t id) {
    C("susappend", id);
    if (g_append77) g_cnt77++;
    return (char)g_append77;
}
static void FakeSusFlush(void*) { C("susflush"); }
static void FakeSusClear(void*) { C("susclear"); g_cnt77 = 0; }
static int16_t FakeSusCount(void*) {
    C("suscount");
    return (int16_t)g_cnt77;
}
static void FakeSusDtor(void*) { C("susdtor"); }
static void FakeSusSendAlt(void*, uint32_t id, void*) {
    C("sendalt", id);
}
// D77 CHECKS the name-fetch return (0 = fail, unlike
// D76). The empty-name rule applies to the 170 first
// choice only; the 250 fallback always fills a name.
static int FakeNameById77(void*, uint32_t uId, char* pOut,
                          int nCap) {
    C("getname", uId);
    if (uId == g_nameFailId77) return 0;
    if (uId == g_emptyNameId77) {
        pOut[0] = 0;
        return 1;
    }
    snprintf(pOut, nCap, "N%u", uId);
    return 1;
}
static int FakeNameByKey77(void*, uint32_t uId, char* pOut,
                           int nCap) {
    C("getname", uId);
    if (uId == g_nameFailId77) return 0;
    snprintf(pOut, nCap, "N%u", uId);
    return 1;
}
static void WireD77() {
    g_fnSusMsgCtor = FakeSusCtor;
    g_fnSusMsgCreate = FakeSusCreate;
    g_fnSusMsgAppend = FakeSusAppend;
    g_fnSusMsgFlush = FakeSusFlush;
    g_fnSusMsgClear = FakeSusClear;
    g_fnSusMsgCount = FakeSusCount;
    g_fnSusMsgDtor = FakeSusDtor;
    g_fnSusSendAlt = FakeSusSendAlt;
    g_fnLbrGetNameById = FakeNameById77;
    g_fnLbrGetLeagueName = FakeNameByKey77;
}
static void Reset77() {
    g_create77 = 1; g_append77 = 1; g_cnt77 = 0;
    g_emptyNameId77 = 0; g_nameFailId77 = 0;
    Reset76();
}
// the key sits in all four maps -> all phases fire
static void Populate77(Mgr& mgr, bool bAll) {
    *(int32_t*)(mgr.ab + 0x35c) = 2;   // the war gate
    *(uint32_t*)(mgr.ab + 0x358) = 7;  // the war flag
    InsertOuter76(mgr.ab + 0x370,
        MakeOuterNode76(888888, { 5000011, 5000012 }));
    if (bAll) {
        InsertOuter76(mgr.ab + 0x3b0,
            MakeOuterNode76(888888, { 5000013 }));
        InsertOuter76(mgr.ab + 0x430,
            MakeOuterNode76(888888, { 5000014 }));
        InsertOuter76(mgr.ab + 0x470,
            MakeOuterNode76(888888, { 5000015 }));
    }
    Reset();
    g_cnt77 = 0;
}


static std::string CreateOrder77(const std::string& tag) {
    std::string s;
    for (auto& r : g_calls)
        if (r.tag == tag) s += std::to_string(r.a) + ",";
    return s;
}
static bool HasCreateName(const std::string& tag,
                          uint64_t type, const char* nm) {
    for (auto& r : g_calls)
        if (r.tag == tag && r.a == type && r.b != 0 &&
            strcmp((const char*)r.b, nm) == 0) return true;
    return false;
}


// ============ the D78 fakes ============
static uint32_t g_key78 = 555;
static uint32_t g_myTarget78 = 77, g_resolve78 = 7000012;
static int g_signed78 = 0, g_mgrGate78 = 0;
static void* g_league78 = (void*)0x1L;
static void* g_token78 = (void*)0x2L;
static void* g_row78 = (void*)0x3L;
static uint32_t g_tokId78 = 9, g_tokFlag78 = 4;
static int g_tokFail78 = 0, g_rowNull78 = 0;
static int64_t g_ppl78 = 10, g_max78 = 100;
static int32_t g_cfg78 = 4, g_rowOff78 = 100;
static int g_textFail78 = 0;
static int g_cnt78v = 0, g_appendOk78 = 1, g_createOk78 = 1;
static uint32_t g_supportCnt78 = 50;
static int g_charge78 = 1, g_infoFail78 = 0, g_stCheck78 = 1, g_stOk78 = 1;
static char g_lastTalk[64] = "";
static char g_lastNotify[64] = "";

static char g_warOn78 = 0;
static char FakeWar78(void*) { return (char)g_warOn78; }
static char FakeMgrGate78(void*) { return (char)g_mgrGate78; }
static uint32_t FakeULeague78(void*, uint32_t) { return 5000001; }
static void* FakeFindLg78(void*, uint32_t) { return g_league78; }
static uint32_t FakeKey78(void*, uint32_t, uint32_t) { return g_key78; }
static char FakeSigned78(void*, uint32_t) { return (char)g_signed78; }
static uint32_t FakeMyTgt78(void*) { return g_myTarget78; }
static uint32_t FakeResolve78(void*, uint32_t u) {
    C("resolve", u);
    // RAW dedupes the RESOLVED value vs the member key:
    // the key id must resolve to itself so the dedupe holds
    return (u == 3000012) ? g_resolve78 : u;
}
static void* FakeVecInsert78(void* pVec, void* pIt, uint64_t, void* pV) {
    uint64_t* v = (uint64_t*)pVec;
    uint32_t* b = (uint32_t*)(uintptr_t)v[1];
    uint32_t* e = (uint32_t*)(uintptr_t)v[2];
    uint64_t c = v[3];
    uint64_t n = b ? (uint64_t)(e - b) : 0;
    uint64_t cap = b ? ((c - (uint64_t)(uintptr_t)b) / 4) : 0;
    uint64_t nc = cap ? cap * 2 : 1;
    uint32_t* nb = (uint32_t*)malloc(nc * 4);
    for (uint64_t k = 0; k < n; k++) nb[k] = b[k];
    nb[n] = *(uint32_t*)pV;
    free(b);
    v[1] = (uint64_t)(uintptr_t)nb;
    v[2] = (uint64_t)(uintptr_t)(nb + n + 1);
    v[3] = (uint64_t)(uintptr_t)(nb + nc);
    if (v[0]) {
        void* cont = *(void**)(uintptr_t)v[0];
        *(void**)((char*)cont + 0x20) = (void*)(uintptr_t)v[3];
    }
    C("vecins", *(uint32_t*)pV);
    return pIt;
}
static void* FakeTokAcq78(void*, int32_t t) {
    C("tokacq", (uint64_t)t);
    return g_tokFail78 ? nullptr : g_token78;
}
static void* FakeTokRetry78(void*, int32_t t) {
    C("tokretry", (uint64_t)t);
    return g_tokFail78 == 2 ? g_token78 : nullptr;
}
static uint32_t FakeTokId78(void* p) { C("tokid"); return g_tokId78; }
static uint32_t FakeTokFlag78(void*) { return g_tokFlag78; }
static void FakeTokSet78(void*, int32_t i, uint32_t v, char b) {
    C("tokset", (uint64_t)i, v, (uint64_t)b);
}
static void* FakeTokRow78(void*, uint32_t id) {
    C("tokrow", id);
    return g_rowNull78 ? nullptr : g_row78;
}
static char FakeText78(void*, uint32_t u, void*, void*, void*, void*) {
    C("text", u);
    return (char)!g_textFail78;
}
static void* FakeLgCount78(void*) { return (void*)(uintptr_t)g_ppl78; }
static void FakeLgAdd78(void*, int64_t n, char b) { C("lgadd", (uint64_t)n, (uint64_t)b); }
static void FakeLgInfo78(void*, void* o) { memset(o, 0xAB, 8); C("lginfo"); }
static void FakeNameA78(void*, uint32_t, uint32_t* oId, char* o, int32_t) {
    *oId = 5000011; strcpy(o, "PlunderName"); C("nameA");
}
static void FakeNameB78(void*, uint32_t, uint32_t* oId, char* o, int32_t) {
    *oId = 6000022; strcpy(o, "PlunderedName"); C("nameB");
}
static int32_t FakeCfg78(void*) { C("cfg"); return g_cfg78; }
static void FakeTalk78(void*, uint32_t, const void* pStr, uint32_t c) {
    snprintf(g_lastTalk, 64, "%s", (const char*)pStr);
    C("talk", (uint64_t)(uintptr_t)pStr, c);
}
static uint32_t FakeSupCnt78(void*, uint32_t) { C("supcnt"); return g_supportCnt78; }
static char FakeCharge78(void*, uint32_t, int32_t, uint32_t u) {
    C("charge", u);
    return (char)g_charge78;
}
static void FakePaid78(void*, uint32_t) { C("paid"); }
static void* FakeUName78(void*, uint32_t) { return (void*)"Mizo"; }
static void FakeLogSave78(const char* f, const char*, uint64_t u, void* n) {
    C("mylog", u, (uint64_t)(uintptr_t)n, (uint64_t)(uintptr_t)f);
}
static void FakeSnprintf78(char* d, uint64_t, const char* f) {
    snprintf(d, 64, "%s", f);
    C("snprintf", (uint64_t)(uintptr_t)f);
}
static void FakeNotify78(void*, const char* t, uint16_t ch) {
    snprintf(g_lastNotify, 64, "%s", t);
    C("notify", ch);
}
static uint32_t FakeTime78(int32_t n) { C("time", (uint64_t)n); return 1000; }
static void FakeDbLog78(const char* f, uint64_t id, const char* p, uint32_t l) {
    C("dblog", id, l, (uint64_t)(uintptr_t)p);
    (void)f;
}
static void FakeInfoFail78(const char* a, const char* b, const char* c, const char* d) {
    C("infofail", (uint64_t)(uintptr_t)b, (uint64_t)(uintptr_t)c, (uint64_t)(uintptr_t)d);
    (void)a;
}
static void FakeMsgICtor78(void*) { C("mic_ctor"); }
static char FakeMsgICreate78(void*, void*, uint32_t f, uint32_t a, uint32_t b,
                             const char* n1, const char* n2) {
    C("mic_create", f, a, b);
    // keep stable copies (the RAW passes stack buffers)
    C("mic_n1", KeepName76(n1));
    C("mic_n2", KeepName76(n2));
    return (char)!g_infoFail78;
}
static void FakeMsgIDtor78(void*) { C("mic_dtor"); }
static uint32_t FakeAward78(void*, uint32_t, void*) { C("award"); return 3; }
static void FakeMsgSCtor78(void*) { C("ms_ctor"); }
static char FakeMsgSCheck78(void*) { C("ms_check"); return (char)g_stCheck78; }
static char FakeMsgSCreate78(void*, uint8_t f, uint8_t id, uint64_t e) {
    C("ms_create", (uint64_t)f, (uint64_t)id, e);
    return (char)g_stOk78;
}
static void FakeMsgSFlush78(void*) { C("ms_flush"); }
static void FakeMsgSDtor78(void*) { C("ms_dtor"); }
static void FakeDbSave78(void*) { C("dbsave"); }
static void* FakeRowField78(void* r, int32_t i) {
    C("rowfield", (uint64_t)i);
    return r;
}
static int64_t FakeRowValA78(void*) { C("rowvalA"); return g_max78; }
static int32_t FakeRowValB78(void*) { C("rowvalB"); return g_rowOff78; }
static char FakeApp78(void*, int32_t id) {
    C("app", (uint64_t)id);
    if (g_appendOk78) g_cnt78v++;
    return (char)g_appendOk78;
}
static int16_t FakeCnt78(void*) { C("cnt"); return (int16_t)g_cnt78v; }

static void Reset78() {
    g_key78 = 555; g_myTarget78 = 77; g_resolve78 = 7000012;
    g_signed78 = 0; g_mgrGate78 = 0; g_league78 = (void*)0x1L;
    g_token78 = (void*)0x2L; g_row78 = (void*)0x3L;
    g_tokId78 = 9; g_tokFail78 = 0; g_rowNull78 = 0;
    g_ppl78 = 10; g_max78 = 100; g_cfg78 = 4; g_rowOff78 = 100;
    g_textFail78 = 0; g_cnt78v = 0; g_appendOk78 = 1; g_createOk78 = 1;
    g_supportCnt78 = 50; g_charge78 = 1; g_infoFail78 = 0;
    g_stCheck78 = 1; g_stOk78 = 1;
    g_lastTalk[0] = 0; g_lastNotify[0] = 0;
}
// the talks need the ACTUAL requested string back
static void* FakeStrMgrGetStr78(void*, const char* psz) {
    C("getstr", (uint64_t)(uintptr_t)psz);
    return (void*)(uintptr_t)psz;
}
static void WireD78() {
    g_fnStringMgrGetStr = FakeStrMgrGetStr78;
    g_fnSupWarState = FakeWar78;
    g_fnSplMgrGate = FakeMgrGate78;
    g_fnSupUserLeague = FakeULeague78;
    g_fnSupFindLeague = FakeFindLg78;
    g_fnSupMemberKey = FakeKey78;
    g_fnSplAlreadySigned = FakeSigned78;
    g_fnSplMyTarget = FakeMyTgt78;
    g_fnSplResolveId = FakeResolve78;
    g_fnSplVecInsert = FakeVecInsert78;
    g_fnSplTokenAcquire = FakeTokAcq78;
    g_fnSplTokenRetry = FakeTokRetry78;
    g_fnSplTokenId = FakeTokId78;
    g_fnSplTokenFlag = FakeTokFlag78;
    g_fnSplTokenSet = FakeTokSet78;
    g_fnSplTokenRow = FakeTokRow78;
    g_fnSplBuildText = FakeText78;
    g_fnSplLeagueCount = FakeLgCount78;
    g_fnSplLeagueAdd = FakeLgAdd78;
    g_fnSplLeagueInfo = FakeLgInfo78;
    g_fnSplGetNameA = FakeNameA78;
    g_fnSplGetNameB = FakeNameB78;
    g_fnSplTargetCfg = FakeCfg78;
    g_fnSupTalk = FakeTalk78;
    g_fnSplSupportCnt = FakeSupCnt78;
    g_fnSplChargeEmoney = FakeCharge78;
    g_fnSplEmoneyPaid = FakePaid78;
    g_fnSplUserName = FakeUName78;
    g_fnSupMyLogSave = FakeLogSave78;
    g_fnSupSnprintf = FakeSnprintf78;
    g_fnSupNotifyTalk = FakeNotify78;
    g_fnSupTimeGet = FakeTime78;
    g_fnSplDbLog = FakeDbLog78;
    g_fnSplInfoFailLog = FakeInfoFail78;
    g_fnSplMsgInfoCtor = FakeMsgICtor78;
    g_fnSplMsgInfoCreate = FakeMsgICreate78;
    g_fnSplMsgInfoDtor = FakeMsgIDtor78;
    g_fnSplAwardFlag = FakeAward78;
    g_fnSplMsgStCtor = FakeMsgSCtor78;
    g_fnSplMsgStCheck = FakeMsgSCheck78;
    g_fnSplMsgStCreate = FakeMsgSCreate78;
    g_fnSplMsgStFlush = FakeMsgSFlush78;
    g_fnSplMsgStDtor = FakeMsgSDtor78;
    g_fnSplDbSave = FakeDbSave78;
    g_fnSplRowField = FakeRowField78;
    g_fnSplRowValA = FakeRowValA78;
    g_fnSplRowValB = FakeRowValB78;
    g_fnSupMsgAppend = FakeApp78;
    g_fnSupMsgCount = FakeCnt78;
    g_create74 = 1;   // the RobOpt create (D74 seam)
}

// ============ main ============

// ============ the D80 additions ============
static uint64_t g_rejectTgt80 = 0;
static int g_allow80 = 1;
static char FakePstAllowed(void*, uint32_t, uint32_t uT) {
    C("pstgate", uT);
    if (!g_allow80) return 0;
    return (uT == g_rejectTgt80) ? 0 : 1;
}
static uint32_t g_uLg80 = 5000001;
static uint32_t FakeULeague80(void*, uint32_t) { return g_uLg80; }
static void WireD80() {
    g_fnPstTargetAllowed = FakePstAllowed;
    // the port resolves 1417630d0 via D75's seam name; wire
    // it to the D78 fixture fake (same RAW function)
    g_fnSplFindLeague = FakeFindLg78;
}
static void Reset80() { g_rejectTgt80 = 0; g_allow80 = 1; }

// every in-section Reset78() wipes the D80 setup globals; a
// run must re-apply them or it dies at the mgr gate
static void Prep80() {
    Reset(); Reset78(); Reset80();
    g_my74 = 5; g_mgrGate78 = 1;
    g_resolve78 = 7000012; g_key78 = 555;
    g_ppl78 = 10; g_max78 = 100; g_cfg78 = 4;
}

// ================= D81 fixture =================
#include "modules/syndicate/src/SyndicateLeagueTokenMapPublish.h"
static uint64_t s_vtD81, s_mgrD81;

static uint32_t g_war81 = 1, g_signed81 = 0;
static uint32_t g_gate28081, g_gate4c881;
static uint32_t g_uLg81 = 5000001, g_key81 = 555, g_award81 = 7;
static int64_t  g_money81 = 1000, g_cost81 = 100, g_off81 = 50;
static char     g_build81 = 1, g_rowNull81, g_lgNull81, g_tok81 = 1;
static uint32_t g_timeout81 = 60, g_rec81;
static char     g_warStateB81 = 1, g_signedPublish81;

static void Reset81() {
    g_war81 = 1; g_signed81 = 0; g_gate28081 = 0; g_gate4c881 = 0;
    g_uLg81 = 5000001; g_key81 = 555; g_award81 = 7;
    g_money81 = 1000; g_cost81 = 100; g_off81 = 50;
    g_build81 = 1; g_rowNull81 = 0; g_lgNull81 = 0; g_tok81 = 1;
    g_timeout81 = 60; g_rec81 = 0;
    g_warStateB81 = 1; g_signedPublish81 = 0;
}

static char FakeWarStateB81(void*) { return g_warStateB81; }
static char FakeSigned81(void*, uint32_t u) { C("signed", u); return g_signed81; }
static char FakeGate28081(void*, uint32_t u) { C("g280", u); return g_gate28081; }
static char FakeGate4c881(void*, uint32_t u) { C("g4c8", u); return g_gate4c881; }
static uint32_t FakeUlg81(void*, uint32_t u) { C("ulg", u); return g_uLg81; }
static char FakeGate26881(void*, uint32_t u) { C("g268", u); return 1; }
static char FakeGate4d881(void*, uint32_t u) { C("g4d8", u); return 1; }
static char FakeGate4d081(void*, uint32_t u) { C("g4d0", u); return 1; }
static uint32_t FakeTreeKey81(void*, uint32_t u, uint32_t lg) { C("treekey", u, lg); return g_key81; }
static uint32_t FakeTimeout81(void*) { return g_timeout81; }
static char FakeSignedPublish81(void*, uint32_t a, uint32_t b, uint32_t c) {
    C("signedpub", a, ((uint64_t)b << 32) | c); return g_signedPublish81;
}
static void FakeSend81(void*, uint32_t u, void* m) { C("send", u); }
static void FakeBroadcast81(void*, void* m, uint64_t* cont) { C("bcast"); }
static void FakeTalk81(void*, uint32_t u, const void* s, uint32_t c) {
    C("talk", u, (uint64_t)(uintptr_t)s, c);
    snprintf(g_lastTalk, sizeof(g_lastTalk), "%s", (const char*)s);
}
static void* FakeFindLg81(void*, uint32_t lg) { C("findlg", lg); return g_lgNull81 ? nullptr : (void*)(uintptr_t)0x1111; }
static void* FakeTokFindA81(void*, uint32_t t) { C("tokfinda", t); return g_tok81 ? (void*)(uintptr_t)0x2222 : nullptr; }
static void* FakeTokFindB81(void*, uint32_t a, uint32_t b, uint32_t c) {
    C("tokfindb", a, b, c);
    return g_tok81 ? (void*)(uintptr_t)0x2222 : nullptr;
}
static uint32_t FakeTokId81(void*) { C("tokid"); return 9; }
static uint32_t FakeTokFlag81(void*) { return 0x6a; }
static void* FakeTokRow81(void*, uint32_t id) { C("tokrow", id); return g_rowNull81 ? nullptr : (void*)(uintptr_t)0x3333; }
static char FakeBuildText81(void*, uint32_t u, void*, void*, void*, void* pStr) {
    C("buildtext", u);
    *(const char**)pStr = "MizoToken";
    return g_build81;
}
static int64_t FakeMoney81(void*) { return g_money81; }
static void FakeSetMoney81(void* lg, uint64_t v, char f) { C("setmoney", (uint64_t)(uintptr_t)lg, v, f); }
static void FakeTokSet81(void*, int32_t i, uint32_t v, char b) { C("tokset", (uint64_t)i, v, (uint64_t)b); }
static void FakeMsgStCtor81(void*) { C("stctor"); }
static char FakeMsgTokCreate81(void*, uint8_t f, uint8_t t, uint64_t e) { C("stcreate", f, t, e); return 1; }
static void FakeMsgStDtor81(void*, uint64_t u, uint64_t t, void* r) { C("stdtor"); }
static void FakeLeagueInfo81(void*, void* b) { C("lginfo"); }
static void FakeGetNameA81(void*, uint32_t k, uint32_t* p, char* n, int32_t c) {
    *p = 7000012; memset(n, 0, (size_t)c); snprintf(n, (size_t)c, "P1");
    C("namea", k);
}
static void FakeGetNameB81(void*, uint32_t k, uint32_t* p, char* n, int32_t c) {
    *p = 3000012; memset(n, 0, (size_t)c); snprintf(n, (size_t)c, "P2");
    C("nameb", k);
}
static void FakeMsgInfoCtor81(void*) { C("infoctor"); }
static uint32_t FakeAwardFlag81(void*, uint32_t u, void*) { C("award", u); return g_award81; }
static char FakeMsgInfoCreate81(void*, void*, uint32_t aw, uint32_t pl, uint32_t pr,
        const char*, const char*) {
    C("infocreate", aw, ((uint64_t)pl << 32) | pr); return 1;
}
static void FakeMsgInfoDtor81(void*) { C("infodtor"); }
static void* FakeTreeInsert81(uint64_t* cont, void* v) {
    uint32_t u = *(uint32_t*)v;
    uint32_t* b = (uint32_t*)(uintptr_t)cont[3];
    uint32_t* e = (uint32_t*)(uintptr_t)cont[4];
    if (!b) {
        b = (uint32_t*)malloc(16 * 4); cont[3] = (uint64_t)(uintptr_t)b;
        e = b; cont[5] = (uint64_t)(uintptr_t)(b + 16);
    }
    uint32_t cap = (uint32_t)(((uint64_t)(uintptr_t)cont[5] - (uint64_t)(uintptr_t)b) / 4);
    uint32_t n = (uint32_t)(e - b);
    if (n >= cap) {
        cap *= 2; uint32_t* nb = (uint32_t*)malloc(cap * 4);
        memcpy(nb, b, n * 4); free(b); b = nb;
        cont[3] = (uint64_t)(uintptr_t)b;
        cont[5] = (uint64_t)(uintptr_t)(b + cap); e = b + n;
    }
    b[n] = u; cont[4] = (uint64_t)(uintptr_t)(b + n + 1);
    C("treeins", u);
    return cont;
}
static void FakeReserveCallup81(void*, uint32_t u, uint32_t lg, uint32_t t, uint64_t* cont) {
    C("reserve", u, lg, t);
    uint32_t* b = (uint32_t*)malloc(16 * 4);
    b[0] = 0; b[1] = 77; b[2] = u; b[3] = 0;
    cont[3] = (uint64_t)(uintptr_t)b;
    cont[4] = (uint64_t)(uintptr_t)(b + 4);
    cont[5] = (uint64_t)(uintptr_t)(b + 16);
}
static void FakeMsgLtCtor81(void*) { C("ltctor"); }
static char FakeMsgLtCreate81(void*, int32_t ty, uint32_t u, int32_t t,
        const char* s, uint64_t to) {
    C("ltcreate", (uint64_t)(uint32_t)ty, u, ((uint64_t)(uint32_t)t << 32) | to);
    return 1;
}
static void FakeMsgLtDtor81(void*) { C("ltdtor"); }
static void FakePublishRecord81(void*, uint32_t u, int32_t t, void* r) {
    C("rec", u, (uint64_t)(uint32_t)t, *(uint64_t*)r);
    g_rec81++;
}
static void FakeLogErr81(const char*, const char* who, const char*, const char*) {
    C("logerr", (uint64_t)(uintptr_t)who);
}
static void FakeDbLogErr81(const char*, uint64_t id, const char*, uint32_t l) {
    C("dblog", id, l);
}
static const char* FakeGetStr81(void*, const char* k) { return k; }
static void* FakeStrMgr81(void) { return (void*)(uintptr_t)0x9999; }
static uint32_t FakeTimeGet81(int32_t t) { C("timeget", (uint64_t)t); return 1234; }
static uint64_t FakeTimeNow81(void) { return 77777; }
static void* FakeNew81(uint64_t n) { return malloc(n); }
static void FakeDelete81(void* p) { free(p); }
static void* FakeRowField81(void*, int32_t i) { C("rowfield", (uint64_t)i); return (void*)(uintptr_t)0x4444; }
static int64_t FakeRowCost81(void*) { return g_cost81; }
static int32_t FakeRowOffset81(void*) { return (int32_t)g_off81; }

static void WireD81() {
    g_fnMapWarStateB = FakeWarStateB81;
    g_fnMapMemberSigned = FakeSigned81;
    g_fnMapMemberGateC = FakeGate28081;
    g_fnMapMemberGateF = FakeGate4c881;
    g_fnMapUserLeague = FakeUlg81;
    g_fnMapSignedPublish = FakeSignedPublish81;
    g_fnMapMemberTreeKey = FakeTreeKey81;
    g_fnMapCallupTimeout = FakeTimeout81;
    g_fnMapMemberGateA = FakeGate26881;
    g_fnMapMemberGateD = FakeGate4d881;
    g_fnMapMemberGateE = FakeGate4d081;
    g_fnMapSendMsg = FakeSend81;
    g_fnMapBroadcast = FakeBroadcast81;
    g_fnMapTalk = FakeTalk81;
    g_fnMapFindLeague = FakeFindLg81;
    g_fnMapTokenFindA = FakeTokFindA81;
    g_fnMapTokenFindB = FakeTokFindB81;
    g_fnMapTokenId = FakeTokId81;
    g_fnMapTokenFlag = FakeTokFlag81;
    g_fnMapTokenRow = FakeTokRow81;
    g_fnMapBuildText = FakeBuildText81;
    g_fnMapLeagueMoney = FakeMoney81;
    g_fnMapLeagueSetMoney = FakeSetMoney81;
    g_fnMapTokenSet = FakeTokSet81;
    g_fnMapMsgStCtor = FakeMsgStCtor81;
    g_fnMapMsgTokCreate = FakeMsgTokCreate81;
    g_fnMapMsgStDtor = FakeMsgStDtor81;
    g_fnMapLeagueInfo = FakeLeagueInfo81;
    g_fnMapGetNameA = FakeGetNameA81;
    g_fnMapGetNameB = FakeGetNameB81;
    g_fnMapMsgInfoCtor = FakeMsgInfoCtor81;
    g_fnMapAwardFlag = FakeAwardFlag81;
    g_fnMapMsgInfoCreate = FakeMsgInfoCreate81;
    g_fnMapMsgInfoDtor = FakeMsgInfoDtor81;
    g_fnMapTreeInsert = FakeTreeInsert81;
    g_fnMapReserveCallup = FakeReserveCallup81;
    g_fnMapMsgLtCtor = FakeMsgLtCtor81;
    g_fnMapMsgLtCreate = FakeMsgLtCreate81;
    g_fnMapMsgLtDtor = FakeMsgLtDtor81;
    g_fnMapPublishRecord = FakePublishRecord81;
    g_fnMapLogErr = FakeLogErr81;
    g_fnMapDbLogErr = FakeDbLogErr81;
    g_fnMapGetStr = FakeGetStr81;
    g_fnMapStrMgr = FakeStrMgr81;
    g_fnMapTimeGet = FakeTimeGet81;
    g_fnMapTimeNow = FakeTimeNow81;
    g_fnMapNew = FakeNew81;
    g_fnMapDelete = FakeDelete81;
    g_fnMapRowField = FakeRowField81;
    g_fnMapRowCost = FakeRowCost81;
    g_fnMapRowOffset = FakeRowOffset81;
}

// ================= D82 fixture =================
#include "modules/syndicate/src/SyndicateVlmAward.h"
#include <vector>
static std::vector<void*> g_pool82;
static void* P82(size_t n) { void* p = malloc(n); g_pool82.push_back(p); return p; }

static void*   FakeFindSyn82(void* mgr, uint32_t id) { C("findsyn", id); return (void*)(uintptr_t)(0x6000 + id); }
static char    FakeAddMoney82(void* syn, uint64_t amt) { C("addmoney", (uint64_t)(uintptr_t)syn, amt); return 1; }
static void*   FakeSynName82(void* syn) { return (void*)(uintptr_t)0x7000; }
static uint64_t g_emoney82[512];
static uint32_t g_idOf82(void* syn) { return (uint32_t)((uint64_t)(uintptr_t)syn - 0x6000); }
static uint64_t FakeGetEmoney82(void* syn) { return g_emoney82[g_idOf82(syn)]; }
static uint32_t FakeEmoneyField82(void* syn) { C("field", g_idOf82(syn)); return (uint32_t)g_emoney82[g_idOf82(syn)]; }
static char    g_setFail82;
static char    FakeSetEmoney82(void* syn, uint64_t v) {
    C("setemoney", g_idOf82(syn), v);
    if (!g_setFail82) g_emoney82[g_idOf82(syn)] = v;
    return g_setFail82 ? 0 : 1;
}
static void FakeBitAdv82(void* p) {
    uint64_t* a = (uint64_t*)p;                 // {proxy, word, bit}
    if (a[2] < 0x1f) { a[2] = a[2] + 1; return; }   // RAW 141741730
    a[1] = a[1] + 4; a[2] = 0;
}
static void* FakeBitSeek82(void* p, int64_t n) {
    uint64_t* a = (uint64_t*)p;                 // RAW 141741c50
    if (n != 0) {
        a[1] = a[1] + (((uint64_t)((int64_t)a[2] + n)) >> 5) * 4;
        a[2] = (uint64_t)(((int64_t)a[2] + n) & 0x1f);
    }
    return p;
}
static void FakeSendMsg82(void* o, uint32_t a, uint32_t b, uint32_t c) { C("sendmsg", a, b, c); }
static void FakeBroadcast82(void* o, uint32_t id, const void* s, uint32_t f) { C("bcast", id, f); }
static void FakeMyLogSave82(const char* file, const char* fmt, void* nm,
        uint32_t id, uint64_t rank, uint32_t amt) {
    C("logsave", (uint64_t)(uintptr_t)file, id, rank, amt);
}
static const char* FakeGetStr82(void*, const char* k) { return k; }
static void* FakeStrMgr82(void) { return (void*)(uintptr_t)0x8888; }
static void FakeSnprintf82(char* b, uint64_t n, const char* fmt, uint32_t a, uint32_t c) {
    snprintf(b, n, fmt, a, c);
}
static void FakeLogErr82(const char* s) { C("logerr", (uint64_t)(uintptr_t)s); }

static void WireD82() {
    g_fnVlmFindSyn = FakeFindSyn82;
    g_fnVlmAddMoney = FakeAddMoney82;
    g_fnVlmSynName = FakeSynName82;
    g_fnVlmGetEmoney = FakeGetEmoney82;
    g_fnVlmEmoneyField = FakeEmoneyField82;
    g_fnVlmSetEmoney = FakeSetEmoney82;
    g_fnVlmBitAdv = FakeBitAdv82;
    g_fnVlmBitSeek = FakeBitSeek82;
    g_fnVlmSendMsg = FakeSendMsg82;
    g_fnVlmBroadcast = FakeBroadcast82;
    g_fnVlmMyLogSave = FakeMyLogSave82;
    g_fnVlmGetStr = FakeGetStr82;
    g_fnVlmStrMgr = FakeStrMgr82;
    g_fnVlmSnprintf = FakeSnprintf82;
    g_fnVlmLogErr = FakeLogErr82;
}
static void Reset82() { memset(g_emoney82, 0, sizeof(g_emoney82)); g_setFail82 = 0; }

static uint64_t s_vt82, s_mgr82;
static void BuildVec82(uint64_t* v, const uint32_t* ids, int n) {
    uint32_t* b = (uint32_t*)P82(n * 4);
    memcpy(b, ids, n * 4);
    v[0] = 0xAAAA; v[3] = (uint64_t)(uintptr_t)b; v[4] = (uint64_t)(uintptr_t)(b + n);
}

// ================= D83 fixture =================
#include "modules/syndicate/src/SyndicateMsgProcess3.h"
#include <vector>
static std::vector<std::string> g_addStr83;
static uint32_t g_packSize83;
static uint32_t g_rank83, g_targetUser83, g_talkArg83, g_find83;
static int64_t  g_maxRank83 = 1000;
static char g_gateA83 = 1, g_gateB83, g_gateC83 = 1,
     g_inWar83 = 1, g_warOpen83, g_announceChk83 = 1,
     g_backAdd83 = 1, g_blAdd83 = 1, g_blRem83 = 1;
static uint32_t g_strAmount83 = 1;
static const char* g_str83 = "hello";
static uint16_t g_hdr83[8];

static void*   FakeGetMgr83(void) { return (void*)(uintptr_t)0x9000; }
static char    FakeGateA83(void*) { return g_gateA83; }
static char    FakeInWar83(void*) { return g_inWar83; }
static char    FakeGateB83(void*) { return g_gateB83; }
static char    FakeGateC83(void*) { return g_gateC83; }
static char    FakeWarOpen83(void*) { return g_warOpen83; }
static int64_t FakeMaxRank83(void*) { return g_maxRank83; }
static uint32_t FakeTargetUser83(void*) { C("tuser83"); return g_targetUser83; }
static uint32_t FakeTalkArg83(void*) { return g_talkArg83; }
static uint32_t FakeLockA83(void*) { C("lock83"); return 0x55; }
static void    FakeAc43083(void*) { C("ac430"); }
static void    FakeUnlock83(void*) { C("unlock"); }
static void*   FakeFindByUser83(void*, uint32_t u) { C("findu83", u); return (void*)(uintptr_t)g_find83; }
static void    FakeTalk83(void* m, uint32_t id, const char* s, uint64_t a) { C("talk83", id, a, (uint64_t)(uintptr_t)s); }
static void*   FakeStrMgr83(void) { return (void*)(uintptr_t)0x77; }
static const char* FakeGetStr83(void*, const char* k) { return k; }
static uint32_t FakeGetRank83(void*, uint32_t id) { C("getrank", id); return g_rank83; }
static void    FakeVt01883(void* m, uint32_t id) { C("vt18", id); }
static void    FakeVt0e883(void* m, uint32_t id, const char* s, uint32_t f) { C("vt0e8", id, f); }
static void    FakeVt10083(void* m, uint32_t id) { C("vt100", id); }
static void    FakeVt12083(void* m, uint32_t id, uint32_t t) { C("vt120", id, t); }
static void    FakeVt13883(void* m, uint32_t id, uint32_t t) { C("vt138", id, t); }
static void    FakeVt1a883(void* m, uint32_t id, const char* s) { C("vt1a8", id); }
static void    FakeVt1b083(void* m, uint32_t id, const char* s) { C("vt1b0", id); }
static void    FakeVt1b883(void* m, uint32_t id, const char* s) { C("vt1b8", id); }
static void    FakeBad5083(void* m, uint32_t id, uint32_t t, uint64_t a) { C("bad50", id, t, a); }
static void    FakeBb0e083(void* m, uint32_t id, uint32_t t) { C("bb0e0", id, t); }
static void    FakeAc82083(void* m, uint32_t id, uint32_t t) { C("ac820", id, t); }
static void    FakeB785083(void* m, uint32_t id, const char* s) { C("b7850", id, (uint64_t)(uintptr_t)s); }
static void    FakeAc9c083(void* m, uint32_t id, int32_t d) { C("ac9c0", id, d); }
static void    FakeBb50083(void* m, uint32_t id, const char* s, int32_t d) { C("bb500", id, d); }
static void    FakeAab7083(void* m, uint32_t id, uint32_t a, uint32_t b, uint32_t c) { C("aab70", id, a, b, c); }
static void    FakeAcc8083(void* m, uint32_t id, const char* s) { C("acc80", id); }
static void    FakeB7ae083(void* m, uint32_t id, const char* s, int32_t r) { C("b7ae0", id, r); }
static void    FakeAcda083(void* m, uint32_t id, const char* s) { C("acda0", id); }
static void    FakeB7c1083(void* m, uint32_t u, uint32_t id, int32_t r) { C("b7c10", u, id, r); }
static void    FakeB7e7083(void* m, uint32_t id, const char* s) { C("b7e70", id); }
static void    FakeAdeb083(void* m, uint32_t id) { C("adeb0", id); }
static void    FakeAe13083(void* m, uint32_t id) { C("ae130", id); }
static void    FakeAe3a083(void* m, uint32_t id, const char* s) { C("ae3a0", id); }
static void    FakeAd19083(void* m, uint32_t id, const char* s, uint32_t t) { C("ad190", id, t); }
static void    FakeAd79083(void* m, uint32_t id, const char* s) { C("ad790", id); }
static void    FakeAdbb083(void* m, uint32_t id, const char* s) { C("adbb0", id); }
static void    FakeAe6b083(void* m, uint32_t id, int32_t d) { C("ae6b0", id, d); }
static char    FakeBackAdd83(void* o, uint32_t f) { C("backadd", f); return g_backAdd83; }
static char    FakeBlAdd83(void* o, uint32_t id, uint32_t t) { C("bladd", id, t); return g_blAdd83; }
static char    FakeBlRem83(void* o, uint32_t id, uint32_t t) { C("blrem", id, t); return g_blRem83; }
static void    FakeRankSet83(void* o, uint32_t r) { C("rankset", r); }
static void    FakeRankAdd83(void* o, uint32_t r) { C("rankadd", r); }
static void    FakeMsgCtor83(void* p) { C("msgctor"); }
static void    FakeMsgInit83(void* p) { C("msginit"); }
static void    FakeMsgSetVft83(void* p) { C("setvft"); }
static uint32_t FakeGetStrAmount83(void* p) { return g_strAmount83; }
static void    FakeGetString83(void* p, uint32_t i, char* b, uint32_t n) {
    snprintf(b, n, "%s", g_str83);
}
static void    FakeAddString83(void* p, const char* s) {
    g_addStr83.push_back(s);
    g_packSize83 += (uint32_t)strlen(s) + 1;
    C("addstr", (uint64_t)(uintptr_t)s);
}
static uint32_t FakeGetSize83(void* p) { return g_packSize83; }
static void    FakePackerDtor83(void* p) { C("packdtor"); }
static void    FakeSnprintf83(char* b, uint64_t n, const char* f, uint32_t v) {
    C("snpr", v);
    snprintf(b, n, "%u", v);
}
static int32_t FakeAnnounceChk83(const char* s, int32_t f) { C("annchk", f); return g_announceChk83; }
static void    FakeLogErr83(const char* s, uint64_t a, uint64_t b) {
    C("logerr83", (uint64_t)(uintptr_t)s, a, b);
}

static void WireD83() {
    g_fnM83GetMgr = FakeGetMgr83;   g_fnM83GateA = FakeGateA83;
    g_fnM83InWar = FakeInWar83;     g_fnM83GateB = FakeGateB83;
    g_fnM83GateC = FakeGateC83;     g_fnM83WarOpen = FakeWarOpen83;
    g_fnM83MaxRank = FakeMaxRank83; g_fnM83TargetUser = FakeTargetUser83;
    g_fnM83TalkArg = FakeTalkArg83; g_fnM83LockA = FakeLockA83;
    g_fnM83Ac430 = FakeAc43083;     g_fnM83Unlock = FakeUnlock83;
    g_fnM83FindByUser = FakeFindByUser83; g_fnM83Talk = FakeTalk83;
    g_fnM83StrMgr = FakeStrMgr83;   g_fnM83GetStr = FakeGetStr83;
    g_fnM83GetRank = FakeGetRank83; g_fnM83Vt018 = FakeVt01883;
    g_fnM83Vt0e8 = FakeVt0e883;     g_fnM83Vt100 = FakeVt10083;
    g_fnM83Vt120 = FakeVt12083;     g_fnM83Vt138 = FakeVt13883;
    g_fnM83Vt1a8 = FakeVt1a883;     g_fnM83Vt1b0 = FakeVt1b083;
    g_fnM83Vt1b8 = FakeVt1b883;     g_fnM83Bad50 = FakeBad5083;
    g_fnM83Bb0e0 = FakeBb0e083;    g_fnM83Ac820 = FakeAc82083;
    g_fnM83B7850 = FakeB785083;    g_fnM83Ac9c0 = FakeAc9c083;
    g_fnM83Bb500 = FakeBb50083;    g_fnM83Aab70 = FakeAab7083;
    g_fnM83Acc80 = FakeAcc8083;    g_fnM83B7ae0 = FakeB7ae083;
    g_fnM83Acda0 = FakeAcda083;    g_fnM83B7c10 = FakeB7c1083;
    g_fnM83B7e70 = FakeB7e7083;    g_fnM83Adeb0 = FakeAdeb083;
    g_fnM83Ae130 = FakeAe13083;    g_fnM83Ae3a0 = FakeAe3a083;
    g_fnM83Ad190 = FakeAd19083;    g_fnM83Ad790 = FakeAd79083;
    g_fnM83Adbb0 = FakeAdbb083;    g_fnM83Ae6b0 = FakeAe6b083;
    g_fnM83BackAdd = FakeBackAdd83; g_fnM83BlAdd = FakeBlAdd83;
    g_fnM83BlRem = FakeBlRem83;    g_fnM83RankSet = FakeRankSet83;
    g_fnM83RankAdd = FakeRankAdd83; g_fnM83MsgCtor = FakeMsgCtor83;
    g_fnM83MsgInit = FakeMsgInit83; g_fnM83MsgSetVft = FakeMsgSetVft83;
    g_fnM83GetStrAmount = FakeGetStrAmount83;
    g_fnM83GetString = FakeGetString83;
    g_fnM83AddString = FakeAddString83;
    g_fnM83GetSize = FakeGetSize83;
    g_fnM83PackerDtor = FakePackerDtor83;
    g_fnM83Snprintf = FakeSnprintf83;
    g_fnM83AnnounceChk = FakeAnnounceChk83;
    g_fnM83LogErr = FakeLogErr83;
}
static void Reset83() {
    memset(&g_gateA83, 0, 0); // keep defaults below
    g_gateA83 = 1; g_gateB83 = 0; g_gateC83 = 1; g_inWar83 = 1;
    g_warOpen83 = 0; g_announceChk83 = 1; g_backAdd83 = 1;
    g_blAdd83 = 1; g_blRem83 = 1; g_strAmount83 = 1;
    g_rank83 = 0; g_targetUser83 = 0; g_talkArg83 = 0;
    g_find83 = 0; g_maxRank83 = 1000; g_packSize83 = 0;
    g_addStr83.clear();
}

static uint8_t s_msg83[0x420];
static uint8_t s_data83[0x18];
static void Prep83(uint16_t action, uint32_t target,
        uint32_t d3 = 0, uint32_t d4 = 0, uint32_t d5 = 0,
        uint32_t byte0c = 0) {
    Reset(); Reset83();
    memset(s_msg83, 0, sizeof(s_msg83));
    memset(s_data83, 0, sizeof(s_data83));
    *(uint16_t*)(s_data83 + 4) = action;
    *(uint32_t*)(s_data83 + 8) = target;
    *(uint32_t*)(s_data83 + 0xc) = d3;
    *(uint32_t*)(s_data83 + 0x10) = d4;
    *(uint32_t*)(s_data83 + 0x14) = d5;
    if (byte0c) s_data83[0xc] = (uint8_t)byte0c;
    memset((uint8_t*)s_msg83 + 0x408, 0, 0x18);
    *(uint64_t*)(s_msg83 + 0x408) = (uint64_t)(uintptr_t)s_data83;
}
static void Run83(uint32_t id = 77, uint64_t arg4 = 0xABCD) {
    syndicate::MsgSyndicateProcess((void**)s_msg83, id, arg4);
}
// ================= D84 fixture =================
#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include <map>
struct FakeUser84 { uint32_t id, synId, rank; char online, hasFlag, hasSub, hasOld; uint32_t oldId; };
static std::vector<FakeUser84> g_users84;
static std::map<uint32_t, std::string> g_names84;
static uint32_t g_synOf84, g_rankCount84, g_rankMax84 = 5, g_vt32884;
static char g_msgAppend84 = 1;
static uint32_t g_lastMsg84[8];
static void* Find84(uint32_t id) {
    for (auto& u : g_users84) if (u.id == id) return &u;
    return nullptr;
}
static void  FakeA84LogErr(const char* s, uint64_t a, uint64_t b) { C("logerr84", (uint64_t)(uintptr_t)s, a, b); }
static void* FakeA84FindUserById(void* m, uint32_t id) { C("fubyid", id); return Find84(id); }
static char  FakeA84IsValid(void* u) { return 1; }
static uint32_t FakeA84GetSynId(void* u) { return ((FakeUser84*)u)->synId; }
static void* FakeA84FindSyn(void* m, uint32_t id) { C("fsyn", id); return id == g_synOf84 ? (void*)(uintptr_t)0x5000 : nullptr; }
static void* FakeA84FindUserByName(void* m, const char* n) {
    C("fubyname", (uint64_t)(uintptr_t)n);
    for (auto& u : g_users84)
        if (g_names84[u.id] == n) return &u;
    return nullptr;
}
static char  FakeA84IsOnline(void* u) { C("online", ((FakeUser84*)u)->id); return ((FakeUser84*)u)->online; }
static uint32_t FakeA84GetId(void* u) { return ((FakeUser84*)u)->id; }
static char  FakeA84HasFlag(void* u) { C("flag", ((FakeUser84*)u)->id); return ((FakeUser84*)u)->hasFlag; }
static uint32_t FakeA84GetRank(void* u) { return ((FakeUser84*)u)->rank; }
static uint32_t FakeA84RankCount(void* s, uint32_t r) { C("rcount", r); return g_rankCount84; }
static int32_t FakeA84RankMax(void* s, uint32_t r) { C("rmax", r); return g_rankMax84; }
static char  FakeA84HasSubRank(void* u) { return ((FakeUser84*)u)->hasSub; }
static void  FakeA84ClearSubRank(void* u, uint32_t x) { C("clearsub", ((FakeUser84*)u)->id, x); }
static void  FakeA84SetMemberRank(void* s, void* u, uint32_t r) { C("setrank", ((FakeUser84*)u)->id, r); ((FakeUser84*)u)->rank = r; }
static uint32_t FakeA84Vt328(void* c, uint32_t id) { C("vt328", id); return g_vt32884; }
static void  FakeA84RecordUpdate(void* m, void* u, void* s, uint32_t x) { C("rec", ((FakeUser84*)u)->id, x); }
static void* FakeA84GetActorName(void* u) { return (void*)(uintptr_t)"ActorName"; }
static void* FakeA84StrMgr84(void) { return (void*)(uintptr_t)0x9; }
static const char* FakeA84GetStr(void* m, const char* k) { return k; }
static void  FakeA84Snprintf(char* b, uint64_t n, const char* f, const char* s) { snprintf(b, n, "%s %s", f, s); }
static void  FakeA84SynTalk(void* c, uint32_t id, const char* s, uint32_t f) { C("syntalk", id, f); }
static void  FakeA84UserTalk(void* c, uint32_t id, const char* s, uint32_t f) { C("usertalk", id, f); }
static void  FakeA84SendMsg(void* c, uint32_t id, void* m) { C("sendmsg", id); }
static void  FakeA84MsgCtor(void* m) { C("msgctor"); }
static char  FakeA84MsgAppend(void* m, uint32_t a, uint32_t b, uint32_t c, const char* d) {
    C("msgapp", a, b, c);
    return g_msgAppend84;
}
static void  FakeA84MsgDtor(void* m) { C("msgdtor"); }
static char  FakeA84HasOldPos(void* u) { return ((FakeUser84*)u)->hasOld; }
static uint32_t FakeA84GetOldId(void* u) { return ((FakeUser84*)u)->oldId; }
static void  FakeA84RankSetMisc(void* s, void* u, uint32_t r, uint32_t x, const char* d) { C("setmisc", ((FakeUser84*)u)->id, r, x); }
static void  FakeA84SynSave(void* s) { C("synsave"); }
static void WireD84() {
    g_fnA84LogErr = FakeA84LogErr;   g_fnA84FindUserById = FakeA84FindUserById;
    g_fnA84IsValid = FakeA84IsValid; g_fnA84GetSynId = FakeA84GetSynId;
    g_fnA84FindSyn = FakeA84FindSyn; g_fnA84FindUserByName = FakeA84FindUserByName;
    g_fnA84IsOnline = FakeA84IsOnline; g_fnA84GetId = FakeA84GetId;
    g_fnA84HasFlag = FakeA84HasFlag; g_fnA84GetRank = FakeA84GetRank;
    g_fnA84RankCount = FakeA84RankCount; g_fnA84RankMax = FakeA84RankMax;
    g_fnA84HasSubRank = FakeA84HasSubRank; g_fnA84ClearSubRank = FakeA84ClearSubRank;
    g_fnA84SetMemberRank = FakeA84SetMemberRank; g_fnA84Vt328 = FakeA84Vt328;
    g_fnA84RecordUpdate = FakeA84RecordUpdate; g_fnA84GetActorName = FakeA84GetActorName;
    g_fnA84StrMgr = FakeA84StrMgr84;  g_fnA84GetStr = FakeA84GetStr;
    g_fnA84Snprintf = FakeA84Snprintf; g_fnA84SynTalk = FakeA84SynTalk;
    g_fnA84UserTalk = FakeA84UserTalk; g_fnA84SendMsg = FakeA84SendMsg;
    g_fnA84MsgCtor = FakeA84MsgCtor;   g_fnA84MsgAppend = FakeA84MsgAppend;
    g_fnA84MsgDtor = FakeA84MsgDtor;  g_fnA84HasOldPos = FakeA84HasOldPos;
    g_fnA84GetOldId = FakeA84GetOldId; g_fnA84RankSetMisc = FakeA84RankSetMisc;
    g_fnA84SynSave = FakeA84SynSave;
}
static uint64_t s_aLogic84[8];
static void AddU84(uint32_t id, const char* nm, uint32_t syn, uint32_t rank) {
    FakeUser84 u = { id, syn, rank, 1, 0, 0, 0, 0 };
    g_users84.push_back(u);
    g_names84[id] = nm;
}
static void Prep84() {
    Reset(); g_users84.clear(); g_names84.clear();
    g_synOf84 = 42; g_rankCount84 = 0; g_rankMax84 = 5;
    g_vt32884 = 0xAB12; g_msgAppend84 = 1;
    AddU84(7, "Actor", 42, 0x200);
    AddU84(9, "Target", 42, 0x100);
    s_aLogic84[1] = 0x900; s_aLogic84[2] = 0x908; s_aLogic84[3] = 0x910;
}
static uint32_t Run84(const char* accept) {
    return syndicate::AppointPosition3de((void**)s_aLogic84, 7, accept);
}// ================= D85 fixture =================
#include "modules/syndicate/src/CountryLeagueOnStage.h"
#include <map>
#include <set>
struct SimpleTree85 {  // a real MSVC-layout tree builder
    std::map<uint32_t, void*> m_data;
    CountryTreeNode* m_pHead;
    std::vector<CountryTreeNode*> m_nodes;
    void* m_pWrap;
    SimpleTree85() : m_pHead(nullptr), m_pWrap(nullptr) {}
    ~SimpleTree85() { for (auto* n : m_nodes) delete n; delete m_pHead; }
    void Build(const std::map<uint32_t, void*>& data) {
        m_data = data;
        for (auto* n : m_nodes) delete n;
        m_nodes.clear();
        delete m_pHead;
        m_pHead = new CountryTreeNode();
        m_pHead->m_bNil = 1;   // +0x29
        m_pHead->m_bNilH = 1;  // +0x49
        if (data.empty()) {
            m_pHead->m_left = m_pHead; m_pHead->m_right = m_pHead;
            m_pHead->m_parent = m_pHead;
            return;
        }
        // build a simple right-spine tree in key order (valid BST)
        CountryTreeNode* pPrev = nullptr;
        for (auto& kv : data) {
            CountryTreeNode* n = new CountryTreeNode();
            n->m_key = kv.first; n->m_value = kv.second;
            n->m_left = m_pHead; n->m_right = m_pHead;  // nil leaves
            n->m_bNilH = 0;
            m_nodes.push_back(n);
            if (pPrev == nullptr) {
                m_pHead->m_left = n; n->m_parent = m_pHead;
            } else {
                pPrev->m_right = n; n->m_parent = pPrev;
            }
            pPrev = n;
        }
        m_pHead->m_right = m_pHead;  // head's right = head (end)
        pPrev->m_right = m_pHead;
        m_pHead->m_parent = pPrev;
    }
    CountryTreeNode* First() { return m_pHead->m_left; }
    CountryTreeNode* End() { return m_pHead; }
};
static SimpleTree85 g_mapA85, g_mapHarem85, g_mapD85, g_mapE85, g_mapF85;
static SimpleTree85 g_temp85;
struct FakeVal85 { uint32_t id; uint32_t rank; };  // rank = vt+0x30 of sub-object 3
static std::map<uint32_t, FakeVal85> g_vals85;
static std::set<uint32_t> g_tempKeys85;
static uint32_t g_countryId85 = 5, g_kingFail85;
static void* g_createdKing85 = (void*)1;
static char g_afterKing85, g_enthrone85;
static uint32_t g_memberRank85 = 3;   // FUN_14172ecb0 default (temp sweep)
static char g_mapFindFail85, g_mapInsertFail85;
static void* FakeC85CreateKing(void** c, uint32_t a, uint32_t b, uint32_t r) {
    C("createking", a, b, r);
    if (g_kingFail85) g_createdKing85 = nullptr;
    return g_createdKing85;
}
static void  FakeC85AfterKing(void** c, uint32_t f) { C("afterking", f); }
static void  FakeC85Enthrone(void** c, uint32_t id) { C("enthrone", id); }
static void* FakeC85MapFind(void** m, void* a, void** b) { C("mapfind"); return (void*)1; }
static void  FakeC85MapInsert(void** m, void* a, void* b) { C("mapinsert"); }
static void  FakeC85SetRank4000(void** c, uint32_t r) { C("set4000", r); }
static void  FakeC85MoveKing(void** c, void* king, void* it, const char* n) { C("moveking", (uint64_t)(uintptr_t)n); }
static void* FakeC85NewTreeHead(void) { C("newhead"); return operator new(0x40); }
static void  FakeC85FillTempMap(void** c, void** proxy, void* pHead) {
    C("filltemp");
    // build a right-spine BST under the port's own head (RAW insert)
    CountryTreeNode* pH = (CountryTreeNode*)pHead;
    CountryTreeNode* pPrev = nullptr;
    for (auto k : g_tempKeys85) {
        CountryTreeNode* n = new CountryTreeNode();
        n->m_key = k; n->m_value = (void*)(uintptr_t)(0x7000 + k);
        n->m_left = pH; n->m_right = pH;  // nil leaves
        n->m_bNilH = 0;
        g_temp85.m_nodes.push_back(n);
        if (pPrev == nullptr) { pH->m_left = n; n->m_parent = pH; }
        else { pPrev->m_right = n; n->m_parent = pPrev; }
        pPrev = n;
    }
    if (pPrev) { pPrev->m_right = pH; pH->m_parent = pPrev; }
}
static uint32_t FakeC85MemberRank(void** c, uint32_t id) { C("mrank", id); return g_memberRank85; }
static void  FakeC85TempMapClear(void** p, void* a, void* b, void* d) { C("clear"); }
static void  FakeC85UpdateMember(void* m, int32_t id, int32_t r) { C("upd", id, r); }
static void  FakeC85LeagueName(void* m, uint32_t id) { C("lgname", id); }
static void  FakeC85LogErr(const char* s, uint64_t a, uint64_t b) { C("logerr85", (uint64_t)(uintptr_t)s, a); }
static void* FakeC85StrMgr85(void) { return (void*)(uintptr_t)0x5; }
static const char* FakeC85GetStr(void* m, const char* k) { return k; }
static void  FakeC85Snprintf(char* b, uint64_t n, const char* s) { snprintf(b, n, "%s", s); }
static void* FakeC85VtCall(void* v, uint32_t idx, uint32_t off) { C("vtcall", idx, off); return v; }
static uint32_t FakeC85VtGetId(void* v) { return ((FakeVal85*)v)->id; }
static uint32_t FakeC85VtGetLeaderName(void* v) { C("vt30", ((FakeVal85*)v)->id); return ((FakeVal85*)v)->rank; }
static void  FakeC85Broadcast(void** c, uint32_t id, const char* s, uint32_t col) { C("bcast", id, col); }
static void WireD85() {
    g_fnC85CreateKing = FakeC85CreateKing;
    g_fnC85AfterKing = FakeC85AfterKing;
    g_fnC85Enthrone = FakeC85Enthrone;
    g_fnC85MapFind = FakeC85MapFind;
    g_fnC85MapInsert = FakeC85MapInsert;
    g_fnC85SetRank4000 = FakeC85SetRank4000;
    g_fnC85MoveKing = FakeC85MoveKing;
    g_fnC85NewTreeHead = FakeC85NewTreeHead;
    g_fnC85FillTempMap = FakeC85FillTempMap;
    g_fnC85MemberRank = FakeC85MemberRank;
    g_fnC85TempMapClear = FakeC85TempMapClear;
    g_fnC85UpdateMember = FakeC85UpdateMember;
    g_fnC85LeagueName = FakeC85LeagueName;
    g_fnC85LogErr = FakeC85LogErr;
    g_fnC85StrMgr = FakeC85StrMgr85;
    g_fnC85GetStr = FakeC85GetStr;
    g_fnC85Snprintf = FakeC85Snprintf;
    g_fnC85VtCall = FakeC85VtCall;
    g_fnC85VtGetId = FakeC85VtGetId;
    g_fnC85VtGetLeaderName = FakeC85VtGetLeaderName;
    g_fnC85Broadcast = FakeC85Broadcast;
}
static uint64_t s_aCountry85[0x50];
static void Build85(const std::map<uint32_t, FakeVal85>& members,
        std::set<uint32_t> tempKeys = {}, bool bEmptyHarem = false) {
    Reset();
    for (auto* n : g_temp85.m_nodes) delete n;
    g_temp85.m_nodes.clear(); delete g_temp85.m_pHead;
    g_temp85.m_pHead = new CountryTreeNode();
    g_temp85.m_pHead->m_bNil = 1; g_temp85.m_pHead->m_bNilH = 1;
    g_kingFail85 = 0; g_createdKing85 = (void*)1;
    g_afterKing85 = g_enthrone85 = 0;
    g_memberRank85 = 3;
    g_mapFindFail85 = g_mapInsertFail85 = 0;
    g_vals85 = members; g_tempKeys85 = tempKeys;
    memset(s_aCountry85, 0, sizeof(s_aCountry85));
    std::map<uint32_t, void*> a, h, d, e;
    for (auto& kv : members) {
        a[kv.first] = &g_vals85[kv.first];
        d[kv.first] = &g_vals85[kv.first];
        e[kv.first] = &g_vals85[kv.first];
        if (!bEmptyHarem) h[kv.first] = &g_vals85[kv.first];
    }
    g_mapA85.Build(a); g_mapHarem85.Build(h);
    g_mapD85.Build(d); g_mapE85.Build(e);
    // wire the tree anchors into the country object RAW-style:
    // slot[0x22] = wrapper ptr; wrapper[0] = head (end at +0x30);
    // slot[0x28] = first node
    auto WireTree = [](uint64_t* obj, int slotObj, int slotHead,
                       SimpleTree85& t) {
        // RAW: slot[obj] = map object, slot[head] = the head node
        obj[slotObj] = (uint64_t)(uintptr_t)t.m_pHead;
        obj[slotHead] = (uint64_t)(uintptr_t)t.m_pHead;
    };
    // RAW pairs: [0x22]/[0x28] members; [0x1a]/[0x20];
    // [0x12]/[0x18]; [0x3a]/[0x40]
    WireTree(s_aCountry85, 0x22, 0x28, g_mapA85);
    WireTree(s_aCountry85, 0x1a, 0x20, g_mapD85);
    WireTree(s_aCountry85, 0x12, 0x18, g_mapE85);
    // RAW harem: [0x3a] = tree object, [0x40] = the head node,
    // and the head's parent field (+8) is the ROOT
    CountryTreeNode* pH = g_mapHarem85.m_pHead;
    if (!g_mapHarem85.m_nodes.empty())
        pH->m_parent = g_mapHarem85.m_nodes[0];  // root = leftmost spine
    s_aCountry85[0x3a] = (uint64_t)(uintptr_t)pH;
    s_aCountry85[0x40] = (uint64_t)(uintptr_t)pH;
    s_aCountry85[1] = 0x6000;      // member-mgr handle
    s_aCountry85[10] = 5;          // the country id
    *(uint32_t*)((uint8_t*)s_aCountry85 + 0x54) = 9; // sub id
}
static void Run85(uint32_t idLeague, const char* nm = "K") {
    syndicate::CountryLeagueOnStage((void**)s_aCountry85, idLeague, nm);
}
static int Cnt85(uint64_t line) {
    int n = 0;
    for (auto& r : g_calls)
        if (r.tag == "logerr85" && r.b == line) n++;
    return n;
}
int main() {
    Wire(); WireD72(); WireD73(); WireD74(); WireD75(); WireD76();
    WireD77(); WireD78(); WireD80(); WireD81(); WireD82(); WireD83();
    WireD84(); WireD85();
    SECT("D85-king-gate");
    Build85({}); g_kingFail85 = 1;
    Run85(0);
    CHECK(Count("createking") == 1, "king create attempted");
    CHECK(Count("logerr85") == 1, "create-king-fail log");
    CHECK(Count("upd") == 0, "nothing after fail");
    Build85({}); g_kingFail85 = 0; s_aCountry85[0xb] = 0;
    Run85(0);
    CHECK(Count("afterking") == 1, "after-king hook ran");
    CHECK(HasTag("upd", (uint64_t)5, (uint64_t)1), "LAB entry update");
    Build85({}); s_aCountry85[0xb] = (uint64_t)1;
    Run85(0);
    CHECK(Count("createking") == 0, "existing king: no create");

    SECT("D85-empty-sweeps");
    Build85({}); s_aCountry85[0xb] = 1;
    Run85(0);
    CHECK(Count("bcast") == 0, "no members, no broadcast");
    CHECK(Count("newhead") == 1 && Count("filltemp") == 1, "temp map built");
    CHECK(Count("clear") == 1, "temp map cleared");

    SECT("D85-enthrone-new");
    // candidate 20 is NOT a member, no rank-4000 member exists:
    // walk A finds nothing, walk B ends -> enthrone directly
    Build85({ {10, {10, 1}}, {11, {11, 2}} }, {10, 11});
    s_aCountry85[0xb] = 1;
    Run85(20);
    CHECK(Count("enthrone") == 1, "enthrone when no king");
    CHECK(HasTag("enthrone", (uint64_t)20), "enthroned the candidate");
    CHECK(HasTag("upd", (uint64_t)10) && HasTag("upd", (uint64_t)11),
          "members ranked in temp sweep");
    CHECK(Count("mapfind") == 0, "non-member: no member-map op");

    SECT("D85-candidate-staging");
    // candidate 30 IS a member (rank 1 != 4000): walk A stages it
    // (harem insert + move), then walk B finds no king -> enthrone
    Build85({ {30, {30, 1}}, {40, {40, 2}} }, {30, 40});
    s_aCountry85[0xb] = 1;
    Run85(30);
    CHECK(Count("mapfind") == 1, "walk-A member-map op");
    CHECK(Count("mapinsert") == 1, "harem insert by candidate id");
    CHECK(HasTag("set4000", (uint64_t)1), "walk-A rank = candidate rank");
    CHECK(Count("moveking") == 1, "candidate moved (walk A)");
    CHECK(HasTag("enthrone", (uint64_t)30), "enthroned by walk B");
    CHECK(HasTag("vt30", (uint64_t)30) && HasTag("vt30", (uint64_t)40),
          "rank probes via vt+0x30");

    SECT("D85-existing-king-same");
    // member 20 already holds rank 4000 and IS the candidate:
    // walk A skips (rank == 4000), walk B finds the king with the
    // same id -> no switch, bStaged = false
    Build85({ {20, {20, 4000}} }, {20});
    s_aCountry85[0xb] = 1;
    Run85(20);
    CHECK(Count("mapfind") == 0, "same king: no harem switch");
    CHECK(Count("enthrone") == 0, "same king: no enthrone");
    CHECK(HasTag("upd", (uint64_t)20), "not staged: still ranked");

    SECT("D85-king-switch");
    // candidate 30 is a member (rank 1); member 40 is the king:
    // walk A stages 30, walk B replaces king 40 -> the 4000 literal
    Build85({ {30, {30, 1}}, {40, {40, 4000}} }, {30, 40});
    s_aCountry85[0xb] = 1;
    Run85(30);
    CHECK(Count("mapfind") == 2, "both walks touched the member map");
    CHECK(Count("mapinsert") == 2, "harem inserts for candidate and king");
    CHECK(HasTag("set4000", (uint64_t)4000), "the RAW 4000 literal");
    CHECK(Count("moveking") == 2, "candidate + king both moved");
    CHECK(HasTag("enthrone", (uint64_t)30), "new king enthroned");
    bool bSkipped = true;
    for (auto& r : g_calls)
        if (r.tag == "upd" && r.a == 30) bSkipped = false;
    CHECK(bSkipped, "staged id skipped in temp sweep");
    {
        uint32_t n30 = 0, n40 = 0;
        for (auto& r : g_calls) {
            if (r.tag != "bcast") continue;
            if (r.a == 30) n30++;
            if (r.a == 40) n40++;
        }
        // D and E sweeps broadcast EVERYONE (no bVar4 guard in RAW);
        // only the F sweep skips the staged id
        CHECK(n30 == 2, "staged id broadcast in D+E sweeps only");
        CHECK(n40 == 3, "old king broadcast in D+E+F");
    }
    CHECK(HasTag("bcast", (uint64_t)40, (uint64_t)0xffff00),
          "the original yellow color");

    SECT("D85-harem-missing");
    // empty harem: the RAW iterInfo log with lines 0x254/0x276
    Build85({ {30, {30, 1}}, {40, {40, 4000}} }, {30, 40}, true);
    s_aCountry85[0xb] = 1;
    Run85(30);
    CHECK(Cnt85(0x254) == 1, "walk-A iterInfo 0x254");
    CHECK(Cnt85(0x276) == 1, "walk-B iterInfo 0x276");
    CHECK(Count("mapinsert") == 0, "nothing inserted into empty harem");
    CHECK(HasTag("enthrone", (uint64_t)30), "enthrone still runs");

    SECT("D85-null-value-guards");
    std::map<uint32_t, FakeVal85> m = { {50, {50, 1}} };
    Build85(m, {50});
    s_aCountry85[0xb] = 1;
    g_mapA85.m_nodes[0]->m_value = nullptr;
    Run85(60);
    CHECK(Cnt85(0x246) == 1, "walk-A null 0x246");
    CHECK(Cnt85(0x262) == 1, "walk-B null 0x262");
    CHECK(Count("enthrone") == 1, "no king found -> enthrone");
    Build85(m, {50}); s_aCountry85[0xb] = 1;
    g_mapD85.m_nodes[0]->m_value = nullptr;
    Run85(0);
    CHECK(Cnt85(0x299) == 1, "D-sweep error line");
    Build85(m, {50}); s_aCountry85[0xb] = 1;
    g_mapE85.m_nodes[0]->m_value = nullptr;
    Run85(0);
    CHECK(Cnt85(0x2a7) == 1, "E-sweep error line");
    Build85(m, {50}); s_aCountry85[0xb] = 1;
    g_mapA85.m_nodes[0]->m_value = nullptr;
    Run85(0);
    CHECK(Cnt85(0x2b5) == 1, "F-sweep error line");

    printf(g_fail == 0 ? "D85-OK\n" : "D85-FAIL\n");
    return g_fail == 0 ? 0 : 1;
}

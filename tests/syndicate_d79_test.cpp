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
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRobFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRob.h"
#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptClass.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueSalary.h"
#include "Exe/Dll/Syndicate/Port/SyndicateInviteNotify.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderAccept.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueAddTodayPlunder.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderList.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderQuery.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderStatus.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderSignup.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaguePlunderClose.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
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

// ============ the D79 fakes ============
static int g_nTreeDest = 0; static void* g_lastTreeMap;
static void FakePwcTreeDestroy(void* pMap, void* pRoot) {
    ++g_nTreeDest; g_lastTreeMap = pMap;
    C("tdestroy", (uint64_t)(uintptr_t)pMap,
      (uint64_t)(uintptr_t)pRoot);
    // free the subtree at pRoot (mgr-node kit, isnil@+0x61)
    char* root = (char*)pRoot;
    char* head = (char*)RdP(pMap, 0x30);
    if (root == head || root == nullptr) return;
    std::vector<char*> st; std::vector<char*> toFree;
    st.push_back(root);
    while (!st.empty()) {
        char* n = st.back(); st.pop_back();
        if (*(unsigned char*)(n + 0x61) != 0) continue;
        toFree.push_back(n);
        char* l = *(char**)n; char* r = *(char**)(n + 0x10);
        if (*(unsigned char*)(l + 0x61) == 0) st.push_back(l);
        if (*(unsigned char*)(r + 0x61) == 0) st.push_back(r);
    }
    (void)head;
    for (char* n : toFree) {
        // free the node's inner kit map too (else ASan
        // leaks them once the Mgr dtor can no longer see
        // the re-inited tree)
        FreeKitMap(n + 0x20);
        free(RdP(n + 0x20, 0));
        free(n);
    }
}
static void FakePwcWarUiState(void*, int32_t a, int32_t b) {
    C("uistate", (uint64_t)a, (uint64_t)b);
}
static void FakeOptDtor79(void*) { C("optdtor"); }
static void WireD79() {
    g_fnPwcTreeDestroy = FakePwcTreeDestroy;
    g_fnPwcWarUiState = FakePwcWarUiState;
    // the LeagueOpt dtor seam was never wired in the base
    g_fn1417d66c0 = FakeOptDtor79;
}
static void Reset79() { g_nTreeDest = 0; g_lastTreeMap = nullptr; }

int main() {
    Wire(); WireD72(); WireD73(); WireD74(); WireD75();
    WireD76(); WireD77(); WireD78(); WireD79();
    int nFail0 = 0; (void)nFail0;

    SECT("D79-close-empty");
    {
        Reset(); Reset79(); Reset76();
        Mgr mgr;
        PlunderWarClose(&mgr);
        CHECK(*(int32_t*)(mgr.ab + 0x35c) == 3,
              "war state 3 even with both maps empty");
        CHECK(g_nTreeDest == 5, "five trees destroyed");
        CHECK(HasTag("uistate", 3) &&
              HasTag("uistate", 10),
              "vt+0x528(3) and (10,1)");
        CHECK(Count("getname") == 0,
              "no names looked up (empty)");
    }

    SECT("D79-close-43");
    {
        Reset(); Reset79(); Reset76();
        Mgr mgr;
        // 0x370: {5000001 -> {5000011}} — myLeague 5
        InsertOuter76((char*)mgr.ab + 0x370,
            MakeOuterNode76(5000001, { 5000011 }));
        // 0x3b0 empty
        g_my74 = 5;
        PlunderWarClose(&mgr);
        // the 0x43 send: name 170 "N5000011", type 0x43,
        // send id%1e6 = 1
        CHECK(Count("getname") >= 1, "the name looked up");
        CHECK(HasTag("uistate", 3), "the ui state ran");
        CHECK(*(int32_t*)(mgr.ab + 0x35c) == 3,
              "state 3 after the close");
        // the name fake from D77 wiring: writes N%u for 170
        // (FakeNameById77) — check the create type via the
        // seam: count any 0x43-type records? The create is
        // g_fn1417d6820 — wired by WireD72-era fakes? No —
        // the D79 port calls the REAL g_fn1417d6820 seam...
        CHECK(Count("tdestroy") == 5, "all five cleared");
        CHECK(Count("sendopt") == 1 &&
              HasTag("sendopt", 1),
              "the 0x43 send (id 5000001 %% 1e6 = 1)");
    }

    SECT("D79-close-44");
    {
        Reset(); Reset79(); Reset76();
        Mgr mgr;
        // 0x370 empty, 0x3b0: {5000012 -> {5000022}}
        InsertOuter76((char*)mgr.ab + 0x3b0,
            MakeOuterNode76(5000012, { 5000022 }));
        g_my74 = 5;   // 5000012/1e6 = 5 == myLeague
        PlunderWarClose(&mgr);
        CHECK(*(int32_t*)(mgr.ab + 0x35c) == 3, "state 3");
        CHECK(g_nTreeDest == 5, "the teardown ran");
        CHECK(HasTag("uistate", 10), "the second ui call");
        CHECK(Count("sendopt") == 1 &&
              HasTag("sendopt", 12),
              "the 0x44 send (id 5000012 %% 1e6 = 12)");
    }

    SECT("D79-close-both");
    {
        Reset(); Reset79(); Reset76();
        Mgr mgr;
        InsertOuter76((char*)mgr.ab + 0x370,
            MakeOuterNode76(5000001, { 5000011 }));
        InsertOuter76((char*)mgr.ab + 0x370,
            MakeOuterNode76(5000003, { 5000013 }));
        InsertOuter76((char*)mgr.ab + 0x3b0,
            MakeOuterNode76(5000012, { 5000022 }));
        g_my74 = 5;
        PlunderWarClose(&mgr);
        CHECK(*(int32_t*)(mgr.ab + 0x35c) == 3, "state 3");
        // the head re-init: leftmost == head again
        char* h370 = (char*)RdP(mgr.ab + 0x370, 0x30);
        CHECK(*(char**)h370 == h370 &&
              *(char**)(h370 + 8) == h370 &&
              *(char**)(h370 + 0x10) == h370,
              "0x370 head fully re-inited");
        CHECK(*(uint64_t*)(mgr.ab + 0x3a8) == 0,
              "the 0x370 size field zeroed");
    }

    printf("%s\n", g_fail ? "D79-FAIL" : "D79-OK");
    return g_fail ? 1 : 0;
}

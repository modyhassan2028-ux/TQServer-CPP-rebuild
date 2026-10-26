// syndicate_d45_test — D45/T16: the CSynArenicMeed
// query layer (SyndicateSynMeed): the lazy singleton
// (0x40, proxy + the 0x30 nil head), the user→league
// lower_bound walk (the 0x29 family: key@+0x18,
// league@+0x20), GetUserGrade (the 1-3 type gate +
// the id → meed → league → grade chain), the
// members-index walk (the vt(5)/vt(2) chain), and the
// <8 check pass-through.
#include "../Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateModule.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace syndicate;

static int g_nOpNew = 0, g_nDel = 0, g_nInvalid = 0;
static void* CountNew(size_t n) {
    ++g_nOpNew; return malloc(n ? n : 1);
}
static void CountDel(void* p) {
    ++g_nDel; free(p);
}
static int g_nLog = 0;
static void MockLog() { ++g_nLog; }

static void* g_mgr = (void*)0x777;
static int g_mgrUserId = 0x4242;
static int MockMgrUserId(void* m) {
    assert(m == g_mgr); return g_mgrUserId;
}
static int g_nVt3a8 = 0;
static void MockVt3a8(void* m) {
    assert(m == g_mgr); ++g_nVt3a8;
}
static int g_nVt378 = 0; static int g_vt378Arg = 0;
static void MockVt378(void* m, int n) {
    assert(m == g_mgr); ++g_nVt378; g_vt378Arg = n;
}
static int g_nGrade = 0;
static uint64_t MockGradeOf(void* pL, uint64_t uU,
                            int nT) {
    ++g_nGrade;
    assert(pL == (void*)0x500);
    assert(uU == 0x999);
    return (uint64_t)(nT * 100);
}

// the members-walk mocks
static void* MockSub5(void* p) {
    return (char*)p + 0x100;
}
static int MockSub5Flag(void* pS) {
    // flag nonzero only for the ODD members
    return (*(int*)pS == 1) ? 1 : 0;
}
static void* MockSub2(void* p) {
    return (char*)p + 0x200;
}
static int MockSub2Id(void* pS) {
    return *(int*)pS;
}

// build a small meed map (the singleton layout):
// node: left@0, parent@8, right@0x10, key@+0x18,
// league@+0x20, color@+0x28, isnil@+0x29 (0x2a bytes)
static char* NodeAlloc() {
    char* n = (char*)calloc(1, 0x2a);
    return n;
}
static char* g_head;
static char* Node(uint32_t key, void* league,
                  int black) {
    char* n = NodeAlloc();
    *(char**)n = g_head;
    *(char**)(n + 8) = g_head;
    *(char**)(n + 0x10) = g_head;
    *(uint32_t*)(n + 0x18) = key;
    *(void**)(n + 0x20) = league;
    *(uint8_t*)(n + 0x28) = black ? 1 : 0;
    return n;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritOpNew = CountNew;
    g_fnMeritOpDelete = CountDel;
    g_fnMeritInvalid = []() { ++g_nInvalid; };
    g_fnMeedLog = MockLog;
    g_fnGetServiceInst = []() { return g_mgr; };
    g_fnMgrUserId = MockMgrUserId;
    g_fnMgrVt3a8 = MockVt3a8;
    g_fnMgrVt378 = MockVt378;
    g_fnMeedGradeOf = MockGradeOf;
    g_fnMeedSub5 = MockSub5;
    g_fnMeedSub5Flag = MockSub5Flag;
    g_fnMeedSub2 = MockSub2;
    g_fnMeedSub2Id = MockSub2Id;

    // ---------- D45-1: the singleton ----------
    MeedResetSingleton();
    g_nOpNew = 0; g_nLog = 0;
    void* s1 = MeedSingletonGet();
    assert(s1 != nullptr);
    assert(g_nOpNew == 3
        && "0x40 singleton + the 8-byte proxy"
               " + the 0x30 head");
    assert(g_nLog == 0);
    char* pc = (char*)s1;
    // proxy → this
    assert(**(void***)pc == (void*)s1
        && *(void***)pc != nullptr);
    g_head = pc[6 - 6 + (6 * 8)] ? nullptr : nullptr;
    g_head = *(char**)(pc + 0x30);
    assert(g_head != nullptr);
    assert(*(uint8_t*)(g_head + 0x29) == 1);
    assert(*(uint8_t*)(g_head + 0x28) == 1
        && "the head is black");
    assert(*(char**)g_head == g_head
        && *(char**)(g_head + 8) == g_head
        && *(char**)(g_head + 0x10) == g_head);
    assert(*(uint64_t*)(pc + 0x38) == 0);
    // the cached second call: no new allocs
    g_nOpNew = 0;
    assert(MeedSingletonGet() == s1);
    assert(g_nOpNew == 0);
    // the alloc-fail → the log
    MeedResetSingleton();
    auto saveNew = g_fnMeritOpNew;
    g_fnMeritOpNew = [](size_t) -> void* {
        return nullptr; };
    assert(MeedSingletonGet() == nullptr);
    assert(g_nLog == 1);
    g_fnMeritOpNew = saveNew;
    printf("D45-1 the lazy singleton ok\n");

    // ---------- D45-2: the user→league lookup ------
    // rebuild the singleton + a 3-node map
    MeedResetSingleton();
    void* meed = MeedSingletonGet();
    char* mc = (char*)meed;
    g_head = *(char**)(mc + 0x30);
    char* r = Node(50, (void*)0x500, 1);
    char* lc = Node(20, (void*)0x200, 0);
    char* rc = Node(80, (void*)0x800, 0);
    *(char**)(g_head + 8) = r;
    *(char**)g_head = lc;
    *(char**)(g_head + 0x10) = rc;
    *(char**)(r + 8) = g_head;
    *(char**)r = lc; *(char**)(r + 8) = g_head;
    *(char**)(r + 0x10) = rc;
    *(char**)(lc + 8) = r;
    *(char**)(rc + 8) = r;
    *(uint64_t*)(mc + 0x38) = 3;
    // the hits
    assert(MeedUserLeague(meed, 50) == (void*)0x500);
    assert(MeedUserLeague(meed, 20) == (void*)0x200);
    assert(MeedUserLeague(meed, 80) == (void*)0x800);
    // the miss → 0 (no invalid fired)
    assert(MeedUserLeague(meed, 999) == nullptr);
    assert(MeedUserLeague(meed, 10) == nullptr);
    assert(g_nInvalid == 0);
    printf("D45-2 the lower_bound lookup ok\n");

    // ---------- D45-3: GetUserGrade ----------
    // (the map has id 0x4242? no — wire the mgr id to
    //  an existing key)
    g_nLog = 0;
    assert(MeedGetUserGrade(0x999, 0) == 0);
    assert(g_nLog == 1
        && "the type<1 gate logs");
    assert(MeedGetUserGrade(0x999, 4) == 0);
    assert(g_nLog == 2
        && "the type>3 gate logs");
    // the id not in the map → 0
    g_mgrUserId = 999;
    assert(MeedGetUserGrade(0x999, 2) == 0);
    assert(g_nGrade == 0);
    // the full chain
    g_mgrUserId = 50;
    assert(MeedGetUserGrade(0x999, 2) == 200);
    assert(g_nGrade == 1);
    assert(MeedGetUserGrade(0x999, 1) == 100);
    // the mgr id == 0 gate
    g_mgrUserId = 0;
    assert(MeedGetUserGrade(0x999, 1) == 0);
    assert(g_nGrade == 2
        && "no grade call on the 0 id");
    printf("D45-3 GetUserGrade ok\n");

    // ---------- D45-4: the vt pass-throughs ----------
    g_nVt378 = 0;
    MeedPostGrade(g_mgr, 0xAB, 0x16);
    assert(g_nVt378 == 1 && g_vt378Arg == 0x16);
    printf("D45-4 the vt pass-through ok\n");

    // ---------- D45-5: the members index walk ------
    // a members "vector": dbg-proxy@+8, begin@+0x20,
    // end@+0x28. Each member = one int64 cell: low
    // int = the vt(5) flag, high int = the vt(2) id.
    // (the vector cells are POINTERS to member cells)
    // (low = the flag, high = the id)
    static int64_t m0 = (10LL << 32);      // f0, id 10
    static int64_t m1 = (20LL << 32) | 1;  // f1, id 20
    static int64_t m2c = (30LL << 32);     // f0, id 30
    static int64_t* m3[3] = { &m0, &m1, &m2c };
    // the dbg proxy: *[0] must hold a +0x20 field >=
    // the end (the iterator-range gate) — point it at
    // a fake container whose +0x20 = end
    static void* dbgCont[8] = { nullptr };
    dbgCont[0] = dbgCont;   // *(dbg)+0x20 = the end
    struct Vec {
        void* pad0; void* dbg; void* pad2;
        void* pad3;                  // +0x18
        void* begin; void* end;      // +0x20, +0x28
    } vec = { nullptr, &dbgCont[0], nullptr, nullptr,
              &m3[0], &m3[3] };
    // the +0x20 slot of the dbg container = the end
    dbgCont[4] = &m3[3];
    g_fnMeedSub5 = [](void* p) -> void* {
        return (char*)p; };
    g_fnMeedSub5Flag = [](void* pS) -> int {
        return (int)(*(int64_t*)pS & 0xffffffff); };
    g_fnMeedSub2 = [](void* p) -> void* {
        return (char*)p; };
    g_fnMeedSub2Id = [](void* pS) -> int {
        return (int)(*(uint64_t*)pS >> 32); };
    g_nInvalid = 0;
    // id 20 (flag=1) → index 1
    assert(MeedMemberIndex(&vec, 20) == 1);
    // the flag-0 ids never match → -1
    assert(MeedMemberIndex(&vec, 10) == -1);
    assert(MeedMemberIndex(&vec, 30) == -1);
    // the nId==0 gate → -1 without the walk
    assert(MeedMemberIndex(&vec, 0) == -1);
    assert(g_nInvalid == 0);
    // a nonzero flag + the matching id at index 2
    m2c = (77LL << 32) | 1;
    assert(MeedMemberIndex(&vec, 77) == 2);
    assert(g_nInvalid == 0);
    printf("D45-5 the members index walk ok\n");

    // ---------- D45-6: MeedMemberCheck ----------
    // (mgr id 77 → index 2 → 2 < 8 → vt3a8 fires)
    g_mgrUserId = 77; g_nVt3a8 = 0;
    MeedMemberCheck(&vec, 1);
    assert(g_nVt3a8 == 1
        && "index<8 → the vt+0x3a8 call");
    // a MISS → -1 → (-1 < 8 on the signed int IS
    // true → the call fires — verbatim)
    g_mgrUserId = 404;
    MeedMemberCheck(&vec, 1);
    assert(g_nVt3a8 == 2
        && "the miss → -1 → the call still fires");
    // the null gate
    g_nLog = 0;
    MeedMemberCheck(nullptr, 1);
    assert(g_nLog == 1);
    printf("D45-6 MeedMemberCheck ok\n");

    assert(g_nInvalid == 0);
    printf(
      "SYNDICATE-D45-OK: the CSynArenicMeed query layer"
      " REAL - the lazy 0x40 singleton (proxy + the"
      " 0x30 nil head), the 0x29-family user→league"
      " lower_bound (key@+0x18, value@+0x20, the"
      " debug-iterator gates), GetUserGrade (the type"
      " gate + the id→meed→league→grade chain), the"
      " vt+0x378 pass-through, the members-vector index"
      " walk (vt5/vt2 chain) and the <8 check\n");
    return 0;
}

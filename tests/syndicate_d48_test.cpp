// syndicate_d48_test — D48/T16: the REAL pool list
// fill (14177cdc0 = CMeedSetMgr::GetSynMeed) +
// GetVecByMeedType (14177cb40) + IsMemberUser
// (14177cad0): the per-type 0x30 vectors, the
// member-cell walk with the debug gates, the user
// match via the vt+8 sub(2) protocol, and the
// sub(3)/sub(4) outs.
#include "../Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace syndicate;

static int g_nInvalid = 0, g_nLog = 0;
static void MockInvalid() { ++g_nInvalid; }
static void MockLog() { ++g_nLog; }

// the member: {id, type, grade, value}
struct Member { uint64_t id, type, grade, value; };
static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    switch (n) {
    case 2: return &m->id;
    case 3: return &m->type;
    default: return &m->grade;
    }
}
static int SubNId(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static int SubNType(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static void* MemSubV(void* pM) {
    return &((Member*)pM)->value;
}
static uint32_t SubVVal(void* pS) {
    return (uint32_t)(((uint64_t*)pS)[0]);
}

// the per-type vector (0x30 header): proxy@0,
// ..., begin@0x18, end@0x20
struct TypeVec {
    void* pad[3];      // +0..0x10
    void** begin;      // +0x18
    void** end;        // +0x20
};
// the pool (0xd0): three type vecs at +0/0x30/0x60
// + the +0x98 anchor vec
struct Pool {
    char v1[0x30];
    char v2[0x30];
    char v3[0x30];
    char pad[0x08];    // +0x90
    TypeVec anchor;    // +0x98
};

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedLog = MockLog;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubNId;
    g_fnMeedSubNType = SubNType;
    g_fnMeedMemSubV = MemSubV;
    g_fnMeedSubVVal = SubVVal;

    // ---------- D48-1: GetVecByMeedType ----------
    static char pool[0xd0];
    assert(MeedPoolVecByType(pool, 1)
        == (void*)pool);
    assert(MeedPoolVecByType(pool, 2)
        == (void*)(pool + 0x30));
    assert(MeedPoolVecByType(pool, 3)
        == (void*)(pool + 0x60));
    g_nLog = 0;
    assert(MeedPoolVecByType(pool, 4)
        == (void*)(pool + 0x98)
        && "the miss falls back to +0x98");
    assert(MeedPoolVecByType(pool, 0)
        == (void*)(pool + 0x98));
    assert(g_nLog == 2);
    printf("D48-1 GetVecByMeedType ok\n");

    // ---------- D48-2: IsMemberUser ----------
    static Member m1 = { 0x50, 2, 100, 555 };
    assert(MeedIsMemberUser(&m1, 0x50));
    assert(!MeedIsMemberUser(&m1, 0x51));
    g_nLog = 0;
    assert(!MeedIsMemberUser(nullptr, 1));
    assert(g_nLog == 1
        && "the null member logs");
    printf("D48-2 IsMemberUser ok\n");

    // ---------- D48-3: GetSynMeed — the walk ------
    // build the type-2 vector: two members, the
    // second matches the user
    static Member mem[2] = {
        { 0x60, 2, 100, 1 },
        { 0x50, 2, 200, 777 } };
    static void* cells[2] = { &mem[0], &mem[1] };
    static void* dbgC[8] = { nullptr };
    dbgC[0] = dbgC;
    dbgC[4] = &cells[2];       // the +0x20 sentinel
    TypeVec tv2 = { { nullptr, nullptr, nullptr },
                    &cells[0], &cells[2] };
    Pool* p = (Pool*)pool;
    memset(pool, 0, sizeof(pool));
    p->v1;  // (unused warnings)
    // write the type-2 vec at pool+0x30
    memcpy(pool + 0x30, &tv2, sizeof(tv2));
    *(void**)(pool + 0x30) = &dbgC[0]; // the proxy
    // the vec's +0x18 begin / +0x20 end already set
    *(void**)(pool + 0x18) = &cells[0];
    *(void**)(pool + 0x20) = &cells[2];

    int a = -1, b = -1;
    g_nInvalid = 0;
    MeedPoolGetSynMeed(pool, &a, &b, 0x50, 2);
    assert(a == 2 && b == 777
        && "sub(3) → A (the type field),"
           " sub(4) → B (the value field)");
    assert(g_nInvalid == 0);
    // the user miss → the end → 0/0
    a = -1; b = -1;
    MeedPoolGetSynMeed(pool, &a, &b, 0x61, 2);
    assert(a == 0 && b == 0);
    // the FIRST match wins (add an earlier match)
    static Member mem0 = { 0x50, 2, 111, 222 };
    cells[0] = &mem0;
    MeedPoolGetSynMeed(pool, &a, &b, 0x50, 2);
    assert(a == 2 && b == 222
        && "the first matching cell wins");
    printf("D48-3 the GetSynMeed walk ok\n");

    // ---------- D48-4: the gates -----------------
    g_nLog = 0;
    MeedPoolGetSynMeed(pool, nullptr, &b, 1, 1);
    assert(g_nLog == 1 && "the null out A logs");
    MeedPoolGetSynMeed(pool, &a, nullptr, 1, 1);
    assert(g_nLog == 2 && "the null out B logs");
    MeedPoolGetSynMeed(pool, &a, &b, 1, 5);
    assert(g_nLog == 3 && "the type miss logs");
    assert(g_nInvalid == 0);
    // an empty vector (type 1): the walk breaks at
    // once with 0/0
    *(void**)(pool + 0x18) = &cells[0];
    *(void**)(pool + 0x20) = &cells[0]; // end=begin
    *(void**)(pool + 0x20) = (void*)&cells[0];
    char* v1p = pool;   // the type-1 vec
    *(void**)(v1p + 0x18) = &cells[0];
    *(void**)(v1p + 0x20) = &cells[0];
    *(void**)(v1p) = &dbgC[0];
    a = -1; b = -1;
    MeedPoolGetSynMeed(pool, &a, &b, 0x50, 1);
    assert(a == 0 && b == 0
        && "the empty vec → 0/0 at once");
    assert(g_nInvalid == 0);
    printf("D48-4 the gates ok\n");

    // ---------- D48-5: the flow seam default ----
    // (the d47 flow calls the seam — verify it now
    //  resolves to the REAL function)
    assert(g_fnMeedListFill
        == &MeedPoolGetSynMeed
        && "the seam default = the REAL function");
    printf("D48-5 the seam default ok\n");

    printf(
      "SYNDICATE-D48-OK: the REAL 14177cdc0 pool list"
      " fill - GetVecByMeedType (the 0x30 per-type"
      " vectors + the +0x98 fallback), IsMemberUser"
      " (the vt+8 sub(2) id protocol), the GetSynMeed"
      " walk (the debug gates, the first-match-wins,"
      " the sub(3)/sub(4) outs) and the gates; the"
      " flow seam g_fnMeedListFill now defaults to the"
      " REAL function\n");
    return 0;
}

// syndicate_d46_test — D46/T16: the REAL grade
// lookup (141779090/141779400): the member-cell walk
// matching (user, type) through the vt+8 sub-object
// protocol, the debug-iterator gates, the stride-8
// advance, and the found → sub(4).vt+0x48 grade.
#include "../Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>

using namespace syndicate;

static int g_nInvalid = 0;
static void MockInvalid() { ++g_nInvalid; }

// the league layout: dbg-proxy@+8, begin@+0x20,
// end@+0x28 (the vector cells = member pointers)
struct League {
    void* pad0;
    void* dbg;      // +8
    void* pad2;     // +0x10
    void* pad3;     // +0x18
    void** begin;   // +0x20
    void** end;     // +0x28
};

// a meed member: {id, type, grade} — the vt mocks
struct Member {
    uint64_t id;      // sub(2).vt+0x40
    uint64_t type;    // sub(3).vt+0x48
    uint64_t grade;   // sub(4).vt+0x48
};

static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    switch (n) {
    case 2: return &m->id;
    case 3: return &m->type;
    default: return nullptr;
    }
}
static int SubNId(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static int SubNType(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static void* Sub4(void* pM) {
    Member* m = (Member*)pM;
    return &m->grade;
}
static uint64_t Sub4Val(void* pS) {
    return ((uint64_t*)pS)[0];
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubNId;
    g_fnMeedSubNType = SubNType;
    g_fnMeedSub4 = Sub4;
    g_fnMeedSub4Val = Sub4Val;

    // ---------- D46-1: the member-cell walk --------
    // three members: (u10,t1), (u20,t2), (u20,t3)
    static Member mem[3] = {
        { 10, 1, 1111 },
        { 20, 2, 2222 },
        { 20, 3, 3333 },
    };
    static void* cells[3] = { &mem[0], &mem[1],
                              &mem[2] };
    // the dbg container: +0x20 = the end sentinel
    static void* dbgCont[8] = { nullptr };
    dbgCont[0] = dbgCont;
    dbgCont[4] = &cells[3];
    League lg = { nullptr, &dbgCont[0], nullptr,
                  nullptr, &cells[0], &cells[3] };

    // the hits
    assert(MeedGradeOf(&lg, 20, 2) == 2222);
    assert(MeedGradeOf(&lg, 20, 3) == 3333);
    assert(MeedGradeOf(&lg, 10, 1) == 1111);
    // the misses: wrong type, unknown user
    assert(MeedGradeOf(&lg, 20, 1) == 0);
    assert(MeedGradeOf(&lg, 10, 3) == 0);
    assert(MeedGradeOf(&lg, 99, 1) == 0);
    assert(g_nInvalid == 0
        && "the walk never hits the aborts");
    printf("D46-1 the grade lookup hits/misses ok\n");

    // ---------- D46-2: the out iterator ----------
    int64_t it[2] = { -1, -1 };
    MeedEntryFind(&lg, it, 20, 3);
    assert(it[0] == (int64_t)&dbgCont[0]
        && "the iterator carries the dbg proxy");
    assert(it[1] == (int64_t)&cells[2]
        && "(20,3) = mem[2] → cell 2");
    // the absent (user,type) → the END cell
    MeedEntryFind(&lg, it, 20, 1);
    assert(it[1] == (int64_t)&cells[3]
        && "the miss → the end iterator");
    printf("D46-2 the out iterator ok\n");

    // ---------- D46-3: the empty vector ----------
    static void* ecells[1] = { nullptr };
    static void* edbg[8] = { nullptr };
    edbg[0] = edbg;
    edbg[4] = &ecells[0];
    League elg = { nullptr, &edbg[0], nullptr,
                   nullptr, &ecells[0], &ecells[0] };
    assert(MeedGradeOf(&elg, 5, 1) == 0);
    assert(g_nInvalid == 0);
    printf("D46-3 the empty vector ok\n");

    // ---------- D46-4: the null member cell ------
    static void* ncells[2] = { nullptr, nullptr };
    static void* ndbg[8] = { nullptr };
    ndbg[0] = ndbg;
    ndbg[4] = &ncells[1];
    League nlg = { nullptr, &ndbg[0], nullptr,
                   nullptr, &ncells[0], &ncells[1] };
    assert(MeedGradeOf(&nlg, 5, 1) == 0);
    assert(g_nInvalid == 0
        && "the null cell is skipped verbatim");
    printf("D46-4 the null member cell ok\n");

    // ---------- D46-5: the integration with D45 --
    // g_fnMeedGradeOf seam → the real MeedGradeOf
    g_fnMeedGradeOf = MeedGradeOf;

    printf(
      "SYNDICATE-D46-OK: the 141779400 grade lookup"
      " REAL - the member-cell walk (vt+8 protocol:"
      " sub(2)id / sub(3)type), the stride-8 debug"
      " advance, the found → sub(4).vt+0x48 grade,"
      " the misses/empty/null-cell paths, and the"
      " D45 seam now wired to the real function\n");
    return 0;
}

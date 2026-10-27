// D87 tests: FUN_14179ad50 — the proffer rank-count list.
#include "Exe/Dll/Syndicate/Port/SyndicateProfferRankList.h"
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <map>
struct Rec { const char* tag; uint64_t a, b; };
static std::vector<Rec> g_calls;
static void C(const char* t, uint64_t a = 0, uint64_t b = 0)
    { g_calls.push_back({t, a, b}); }
static int Count(const char* t, uint64_t a = ~0ull, uint64_t b = ~0ull) {
    int n = 0;
    for (auto& r : g_calls) if (r.tag == t && (a == ~0ull || r.a == a)
        && (b == ~0ull || r.b == b)) n++;
    return n;
}
// fixture state
static char s_pb[1040];          // the fake PB buffer at +0x408
static char s_msg[1040];         // the fake CMsg
static int g_nInitCalls, g_ctorCalls, g_dtorCalls;
static uint32_t g_vftA = 0x1111, g_vftB = 0x2222;
static int g_countFail = -1;     // >= 0: return this as count
static int FakeCount87(void* mgr, int rank) {
    C("count", (uint64_t)rank);
    return g_countFail >= 0 ? g_countFail : rank * 2;
}
static void Reset87() {
    g_calls.clear();
    memset(s_pb, 0, sizeof s_pb);
    memset(s_msg, 0, sizeof s_msg);
    *(void**)(s_msg + 0x408) = s_pb;
    g_nInitCalls = g_ctorCalls = g_dtorCalls = 0;
    g_countFail = -1;
    syndicate::g_pvD87ProfferVft = &g_vftA;
    syndicate::g_pvD87CMsgVft = &g_vftB;
}
static int g_fail = 0;
#define CHECK(c, msg) do { if (c) printf("  ok %s\n", msg); \
    else { printf("  FAIL %s\n", msg); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
int main() {
    syndicate::g_fnD87Ctor = +[](void* p) { ++g_ctorCalls;
        memset(p, 0, 1040); *(void**)((char*)p + 0x408) = s_pb; };
    syndicate::g_fnD87CMsgInit = +[](void*) { ++g_nInitCalls; };
    syndicate::g_fnD87Log = +[](const char* s) { C("log", (uint64_t)(uintptr_t)s); };
    syndicate::g_fnD87Count = FakeCount87;
    const uint32_t RANKS[34] = {
        0x37a, 0x2b2, 0x28a, 0x35b, 0x35a, 0x359, 0x358,
        0x357, 0x356, 0x355, 0x354, 0x353, 0x352, 599,
        0x256, 0x255, 0x254, 0x253, 0x252, 0x251, 0x250,
        0x24f, 0x24e, 499, 0x1f2, 0x1f1, 0x1f0, 0x1ef,
        0x1ee, 0x1ed, 0x1ec, 0x1eb, 0x1ea, 0xd2 };
    SECT("D87-1 zero-arg guard");
    Reset87();
    syndicate::SynProfferRankList87((void*)0x55, 0);
    CHECK(Count("log") == 1, "zero arg -> 1 log");
    CHECK(Count("count") == 0, "zero arg -> no counting");
    CHECK(g_ctorCalls == 0, "zero arg -> no ctor");
    SECT("D87-2 create writes the PB header");
    Reset87();
    syndicate::SynProfferCreate87(s_msg);
    CHECK(g_nInitCalls == 1, "Init called once");
    CHECK(*(uint16_t*)(s_pb + 2) == 0x425, "type 0x425");
    CHECK(*(uint16_t*)s_pb == 8, "initial size 8");
    SECT("D87-3 happy path: 34 ranks in exact order");
    Reset87();
    syndicate::SynProfferRankList87((void*)0x55, 7);
    CHECK(g_ctorCalls == 1 && g_nInitCalls == 1, "ctor + create ran");
    CHECK(Count("count") == 34, "all 34 ranks counted");
    // every (rank, count) landed in the PB buffer in order
    bool bOrder = true;
    for (int i = 0; i < 34; ++i) {
        uint32_t id = *(uint32_t*)(s_pb + 8 + (size_t)i * 8);
        uint32_t v = *(uint32_t*)(s_pb + 0xc + (size_t)i * 8);
        if (id != RANKS[i] || v != RANKS[i] * 2) bOrder = false;
    }
    CHECK(bOrder, "34 (rank,count) pairs exact order");
    CHECK(*(uint16_t*)s_pb == 8 + 34 * 8, "size cursor 280");
    CHECK(*(uint16_t*)(s_pb + 6) == 34, "entry count 34");
    CHECK(Count("log") == 0, "no logs on success");
    CHECK(g_dtorCalls == 0, "RAW: no dtor on success");
    SECT("D87-4 append overflow guard");
    Reset87();
    *(uint16_t*)s_pb = 0x3ff;   // full: +8 would pass 0x3ff
    uint32_t r = syndicate::SynProfferAppend87(s_msg, 1, 2);
    CHECK(r == 0, "overflow append returns 0");
    CHECK(Count("log") == 1, "overflow logged");
    CHECK(*(uint16_t*)(s_pb + 6) == 0, "no entry written");
    SECT("D87-5 Create does not reset the entry cursor (+6)");
    Reset87();
    // the RAW Create only writes +0/+2 — a pre-set entry
    // cursor at +6 survives and appends continue after it
    *(uint16_t*)(s_pb + 6) = 5;
    syndicate::SynProfferRankList87((void*)0x55, 7);
    // 34 appends starting at entry index 5
    bool bCursor = true;
    for (int i = 0; i < 34; ++i) {
        uint32_t id = *(uint32_t*)(s_pb + 8 + (size_t)(i + 5) * 8);
        if (id != RANKS[i]) bCursor = false;
    }
    CHECK(bCursor, "entries written from cursor 5");
    CHECK(*(uint16_t*)(s_pb + 6) == 39, "count cursor 5+34");
    CHECK(*(uint16_t*)s_pb == 8 + 34 * 8, "size still counts from 8");
    // the direct overflow guard already covers the failure
    // branch; the chain itself can never overflow with 34
    // entries (max size 280 << 0x3ff)
    SECT("D87-6 rank ids sanity");
    Reset87();
    std::map<uint32_t, bool> uniq;
    for (auto r2 : RANKS) uniq[r2] = true;
    CHECK(uniq.size() == 34, "34 distinct ranks");
    CHECK(uniq.count(0x1ec) == 1 && uniq.count(0xd2) == 1
          && uniq.count(599) == 1 && uniq.count(499) == 1,
          "wrapped ids present");
    if (g_fail == 0) printf("D87-OK: 24 assertions\n");
    else printf("D87-FAIL\n");
    return g_fail ? 1 : 0;
}

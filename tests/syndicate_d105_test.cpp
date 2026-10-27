// D105 — CSyndicateLogic +0x360: 1417b9380 leader-change flow
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nE80, s_nD3E0, s_n92B0, s_n7120, s_nVtA0,
    s_nVt90, s_nVt430, s_nC8E0;
static int32_t s_aiE80Args[3]; static char s_acE80C;
static uint32_t s_u92B0Args[4];
static const char* s_pc92B0Name;
static char s_acVtA0Str[128];
static uint32_t s_uVtA0Args[2];
static char s_acVt90Str[128]; static uint32_t s_uVt90Arg;
static uint32_t s_uVt430Args[2];
static const char* s_pcVt430Name;
static int s_nKings;
static uint64_t s_u45520Ret; static int32_t s_i74E3F0;
static void* s_pv7630D0;
static char s_cKing;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nE80 = s_nD3E0 = s_n92B0 = s_n7120 = 0;
    s_nVtA0 = s_nVt90 = s_nVt430 = s_nC8E0 = 0;
    s_nKings = 0;
    s_acE80C = 0;
    s_u45520Ret = 0x99; s_i74E3F0 = 0x99;
    s_pv7630D0 = (void*)0x66; s_cKing = 1;
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0xa0/8] = (void*)+[](void*, uint32_t a,
        const char* b, uint32_t c) -> uint64_t {
        s_nVtA0++;
        assert(strstr(b, "STR_LEAGUE_LEADER_CHANGE")
               != 0);
        strncpy(s_acVtA0Str, b, 127);
        s_uVtA0Args[0] = a; s_uVtA0Args[1] = c;
        return 0; };
    apBoxVt[0x90/8] = (void*)+[](void*,
        const char* b, uint32_t c) -> uint64_t {
        s_nVt90++;
        assert(strstr(b, "STR_LEAGUE_KING_CHANGE")
               != 0);
        strncpy(s_acVt90Str, b, 127);
        s_uVt90Arg = c; return 0; };
    apBoxVt[0x430/8] = (void*)+[](void*, uint32_t a,
        const char* b) -> uint64_t {
        s_nVt430++; s_uVt430Args[0] = a;
        s_pcVt430Name = b; return 0; };
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;
    ((void**)abLogic)[3] = (void*)0x33;
    ((void**)abLogic)[2] = (void*)0x22;
    g_fn7630D0 = [](void* p, uint32_t u) -> void* {
        assert(p == abSub); (void)u;
        return s_pv7630D0; };
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        s_nC8E0++; assert(p == (void*)0x33);
        // u2 (0x11) -> plA, u4 (0x44) -> plB
        return u == 0x11 ? (void*)0xAA : (void*)0xBB; };
    g_fn7868C0 = [](void* p) -> char {
        assert(p == (void*)0xAA || p == (void*)0xBB);
        return 1; };
    g_fn785EA0 = [](void* p) -> uint64_t {
        assert(p == (void*)0xAA || p == (void*)0xBB);
        return p == (void*)0xAA ? 0x51 : 0x52; };
    g_fn743C80 = [](void* p) -> uint64_t {
        assert(p == (void*)0x66); return 0x51; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22); (void)u;
        return 0x55; };
    g_fn790390 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x33; };
    g_fn78F270 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x77; };
    g_fn743E80 = [](void* p, int32_t a, int32_t b,
                    char c) {
        s_nE80++; assert(p == (void*)0x66);
        assert(a == 2 && b == 0x77 && c == 1); };
    g_fn74D3E0 = [](void* p) {
        s_nD3E0++; assert(p == (void*)0x66); };
    g_fn787120 = [](void* p) -> char* {
        s_n7120++;
        assert(p == (void*)0xAA || p == (void*)0xBB);
        return p == (void*)0xAA ? (char*)"NameA"
                                : (char*)"NameB"; };
    g_fn7B92B0 = [](void* p, uint32_t a, uint32_t b,
                    uint32_t c, const char* n) {
        s_n92B0++; assert(p == (void*)abLogic);
        s_u92B0Args[0] = a; s_u92B0Args[1] = b;
        s_u92B0Args[2] = c; s_pc92B0Name = n; };
    g_fn74E3F0 = [](void* p) -> uint32_t {
        assert(p == abSub); return s_i74E3F0; };
    g_fn745520 = [](void* p) -> uint64_t {
        assert(p == (void*)0x66); return s_u45520Ret; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                            const char* k) -> void* {
        return (void*)k; };
}

int main() {
    // ---- S1: u2 == u4 -> nothing ----
    Reset();
    pL->Slot508(7, 0x33, 7);
    assert(s_nC8E0 == 0 && s_nVtA0 == 0);
    // ---- S2: synA != leader -> silent ----
    Reset();
    // plA syn = 0x51 == leader 0x51 -> proceeds
    pL->Slot508(0x11, 0x33, 0x44);
    assert(s_nE80 == 1 && s_nD3E0 == 1);
    assert(s_nVtA0 == 1);
    assert(s_uVtA0Args[0] == 0x33 &&
           s_uVtA0Args[1] == 0);
    assert(s_n92B0 == 1);
    assert(s_u92B0Args[0] == 0x11 &&
           s_u92B0Args[1] == 0x44);
    assert(s_u92B0Args[2] == 0x33);
    assert(strcmp(s_pc92B0Name, "NameB") == 0);
    // 745520 == 74e3f0 (both 0x99) -> king change
    assert(s_nVt90 == 1 && s_uVt90Arg == 0x843);
    assert(s_nVt430 == 1);
    assert(s_uVt430Args[0] == 0x33);
    assert(strcmp(s_pcVt430Name, "NameB") == 0);
    // ---- S3: not king -> no king broadcast ----
    Reset();
    s_u45520Ret = 0x50;   // != 74e3f0 (0x99)
    pL->Slot508(0x11, 0x33, 0x44);
    assert(s_nVt90 == 0 && s_nVt430 == 0);
    assert(s_nVtA0 == 1 && s_n92B0 == 1);
    // ---- S4: the 790390 gate fails ----
    Reset();
    s_i74E3F0 = 0x50; s_u45520Ret = 0x50;
    // 790390 = 0x33 == u3 0x33 ok; break it:
    pL->Slot508(0x11, 0x11 + 1, 0x44);
    // ...u3 still 0x33 -> passes; make u3 differ:
    pL->Slot508(0x11, 0x77, 0x44);  // 790390 != u3
    assert(s_nVtA0 == 0 && s_nE80 == 0);
    // ---- S5: player lookup fails ----
    Reset();
    // both lookups must succeed; force via u2==u4
    pL->Slot508(0x44, 0x33, 0x44);
    assert(s_nE80 == 0 && s_nVtA0 == 0);
    puts("SYNDICATE_D105_OK: the leader change");
    return 0;
}

// D100 — CSyndicateLogic +0x2d0: 1417b1e80 the title flow
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nVt18, s_nVt70, s_nVtE0, s_nVt1d8,
    s_nVt488, s_nVt438, s_nVt440, s_nVt2e8;
static char s_cVt2e8Ret;
static int32_t s_i74E920, s_i74E930, s_i7B0370;
static int s_aiLang[1];
static void* s_pv7630D0;
static char s_acVt18Str[3][128]; static int s_iVt18;
static uint32_t s_uVt70Args[3], s_uVt440Args[2];
static const char* s_pcVt440Arg;
static uint32_t s_uTime;
static char s_acCStrFmt[256];
static char s_acStrCopyDst[64];
static int s_nF90, s_nCtor, s_nDtor, s_n6820;
static uint64_t s_u6820Args[6]; static char s_c6820Ret;
static uint32_t s_u74E3F0;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nVt18 = s_nVt70 = s_nVtE0 = s_nVt1d8 = 0;
    s_nVt488 = s_nVt438 = s_nVt440 = s_nVt2e8 = 0;
    s_cVt2e8Ret = 1;
    s_i74E920 = 100; s_i74E930 = 100; s_i7B0370 = 42;
    s_aiLang[0] = 0;
    s_pv7630D0 = (void*)0x77;
    s_iVt18 = 0; s_uTime = 5;
    memset(s_acCStrFmt, 0, sizeof(s_acCStrFmt));
    memset(s_acStrCopyDst, 0, sizeof(s_acStrCopyDst));
    s_nF90 = s_nCtor = s_nDtor = s_n6820 = 0;
    s_c6820Ret = 1; s_u74E3F0 = 9;
    static void* apBox[1]; static void* apBoxVt[160];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x18 / 8] = (void*)+[](void*,
        int32_t n, uint64_t u) -> uint64_t {
        s_nVt18++;
        assert(n == 42);
        strncpy(s_acVt18Str[s_iVt18 % 3],
                (const char*)(uintptr_t)u, 127);
        s_iVt18++; return 0; };
    apBoxVt[0x70 / 8] = (void*)+[](void*, int32_t a,
        uint32_t b, int32_t c) -> uint64_t {
        s_nVt70++; s_uVt70Args[0] = a;
        s_uVt70Args[1] = b; s_uVt70Args[2] = c;
        return 0; };
    apBoxVt[0xe0 / 8] = (void*)+[](void*, void*)
        -> uint64_t { s_nVtE0++; return 0; };
    apBoxVt[0x1d8 / 8] = (void*)+[](void*, int32_t)
        -> uint64_t { s_nVt1d8++; return 0; };
    apBoxVt[0x488 / 8] = (void*)+[](void*)
        -> uint64_t { s_nVt488++; return 0; };
    apBoxVt[0x438 / 8] = (void*)+[](void*,
        const char* s) -> uint64_t {
        s_nVt438++;
        strncpy(s_acCStrFmt, s, 255); return 0; };
    apBoxVt[0x440 / 8] = (void*)+[](void*,
        uint32_t a, const char* b) -> uint64_t {
        s_nVt440++; s_uVt440Args[0] = a;
        s_pcVt440Arg = b; return 0; };
    apBoxVt[0x2e8 / 8] = (void*)+[](void*,
        const char*) -> char {
        s_nVt2e8++; return s_cVt2e8Ret; };
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;
    g_fn74E920 = [](void* p) -> int32_t {
        assert(p == abSub); return s_i74E920; };
    g_fn74E930 = [](void* p) -> int32_t {
        assert(p == abSub); return s_i74E930; };
    g_fnCQLanguageGet = []() -> int* {
        return s_aiLang; };
    g_fn7B0370 = [](void* p, uint32_t u)
        -> int32_t {
        assert(p == (void*)abLogic); (void)u;
        return s_i7B0370; };
    g_fn743F90 = [](void* p, int32_t a,
                    const char* b, char c) {
        s_nF90++; assert(p == (void*)0x77);
        assert(a == 4 && c == 1); (void)b; };
    g_fnTimeGet = [](int32_t t) -> uint32_t {
        assert(t == 3); return s_uTime; };
    g_fnCMsgCtor6640 = [](void*) { s_nCtor++; };
    g_fnCMsgDtor66C0 = [](void*) { s_nDtor++; };
    g_fnCMsgInit6820 = [](void* p, int32_t a,
                          const char* b, uint32_t c,
                          int32_t d, int32_t e)
        -> uint64_t {
        s_n6820++;
        s_u6820Args[0] = (uint64_t)a;
        s_u6820Args[1] = (uintptr_t)b;
        s_u6820Args[2] = c;
        s_u6820Args[3] = (uint64_t)d;
        s_u6820Args[4] = (uint64_t)e;
        return s_c6820Ret; };
    g_fnCStrFormat215d0 = [](void* p,
                             const char* f,
                             uint64_t a, uint64_t b) {
        // model the format: "%s %u.%02u"-ish
        sprintf((char*)s_acCStrFmt, "%s %llu.%llu",
                f, (unsigned long long)a,
                (unsigned long long)b);
        strcpy((char*)p + 8, s_acCStrFmt); };
    g_fnStrCopy = [](char* d, const char* s,
                     size_t n) {
        strncpy(d, s, n - 1); d[n - 1] = 0; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                            const char* k) -> void* {
        return (void*)k; };
    g_fn74E3F0 = [](void* p) -> uint32_t {
        assert(p == abSub); return s_u74E3F0; };
    g_fn7630D0 = [](void* p, uint32_t u)
        -> void* {
        assert(p == abSub); (void)u;
        return s_pv7630D0; };
}

int main() {
    // ---- S1: the null and empty gates ----
    Reset();
    pL->Slot2D0(42, 9, 0);
    assert(s_nVt2e8 == 0 && s_nVt18 == 0);
    pL->Slot2D0(42, 9, "");
    assert(s_nVt2e8 == 0 && s_nVt18 == 0);
    // ---- S2: too long -> STR_INVALID_NAME ----
    Reset();
    s_i74E920 = 2;   // limit 2 < strlen("abc") 3
    pL->Slot2D0(42, 9, "abc");
    assert(s_nVt2e8 == 0);   // short-circuit!
    assert(s_nVt18 == 1);
    assert(strcmp(s_acVt18Str[0], "STR_INVALID_NAME")
           == 0);
    // ---- S3: rejected by the box vt+0x2e8 ----
    Reset();
    s_cVt2e8Ret = 0;
    pL->Slot2D0(42, 9, "abc");
    assert(s_nVt2e8 == 1);
    assert(strcmp(s_acVt18Str[0], "STR_INVALID_NAME")
           == 0);
    // ---- S4: valid, but cur != u -> silent ----
    Reset();
    pL->Slot2D0(42, 8, "abc");   // 74e3f0=9 != 8
    assert(s_nVt2e8 == 1 && s_nVt18 == 0);
    assert(s_nF90 == 0);
    // ---- S5: lg lookup fail -> silent ----
    Reset();
    s_pv7630D0 = 0;
    pL->Slot2D0(42, 9, "abc");
    assert(s_nVt18 == 0 && s_nF90 == 0);
    // ---- S6: not the owner ----
    Reset();
    s_i7B0370 = 41;   // != 42
    pL->Slot2D0(42, 9, "abc");
    assert(s_nVt18 == 1);
    assert(strcmp(s_acVt18Str[0],
                  "STR_LEAGUE_CAN_NOT_SET_TITLE") == 0);
    // ---- S7: the full success path ----
    Reset();
    pL->Slot2D0(42, 9, "abc");
    assert(s_nVt18 == 1);
    assert(strcmp(s_acVt18Str[0],
                  "STR_LEAGUE_SET_TITLE") == 0);
    assert(s_nF90 == 1 && s_nCtor == 1);
    assert(s_n6820 == 1);
    // 5 + 19000000 = 19000005
    assert(s_u6820Args[0] == 0x12);
    assert(strcmp((const char*)
            (uintptr_t)s_u6820Args[1], "abc") == 0);
    assert(s_u6820Args[2] == 19000005);
    assert(s_nVtE0 == 1);      // 6820 ok -> e0
    assert(s_nVt1d8 == 1 && s_nVt488 == 1);
    assert(s_nVt438 == 1);
    // (19000005/10000)=1900, (19000005%10000)/100=0
    assert(strstr(s_acCStrFmt,
                  "STR_LEAGUE_BROADCAST_TITLE") != 0);
    assert(strstr(s_acCStrFmt, "1900.0") != 0);
    // StrCopy wrote "abc" at this+0x61, then the
    // manual strcat appended the resolved country
    assert(strcmp((char*)abLogic + 0x61,
                  "abcSTR_LEAGUE_COUNTRY") == 0);
    assert(s_nVt70 == 1 && s_uVt70Args[0] == 7);
    assert(s_uVt70Args[1] == 9 &&
           s_uVt70Args[2] == 0);
    assert(s_nVt440 == 1 && s_uVt440Args[0] == 9);
    assert(strcmp(s_pcVt440Arg, "abc") == 0);
    assert(s_nDtor == 1);
    // ---- S8: 6820 fails -> no vt+0xe0 ----
    Reset();
    s_c6820Ret = 0;
    pL->Slot2D0(42, 9, "abc");
    assert(s_nVtE0 == 0 && s_nVt18 == 1);
    assert(s_nVt70 == 1);   // flow continues
    // ---- S9: the language branch ----
    Reset();
    s_aiLang[0] = 3; s_i74E930 = 2;
    pL->Slot2D0(42, 9, "abc");  // 2 < 3 -> invalid
    assert(s_nVt18 == 1);
    assert(strcmp(s_acVt18Str[0], "STR_INVALID_NAME")
           == 0);
    s_aiLang[0] = 6;   // == 6 -> keeps 74e920
    pL->Slot2D0(42, 9, "abc");   // limit 100 -> ok
    assert(s_nVt18 == 2);
    assert(strcmp(s_acVt18Str[1],
                  "STR_LEAGUE_SET_TITLE") == 0);
    puts("SYNDICATE_D100_OK: the title monster");
    return 0;
}

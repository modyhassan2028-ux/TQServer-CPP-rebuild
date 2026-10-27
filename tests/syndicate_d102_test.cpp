// D102 — CSyndicateLogic +0x340: 1417b8940 create-league flow
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nVt18, s_nVt2e8, s_nVt350, s_nVt200,
    s_nVt1d8, s_nVt480, s_nVt8, s_nVt710, s_nVt90,
    s_nVt478, s_nEB70, s_nC8E0, s_n68C0, s_nF7F0,
    s_nDCD0, s_n03D0, s_n0EA0, s_nEA30, s_n45920,
    s_nLog, s_nF550, s_nFa70, s_nMyLog;
static char s_acVt18Str[3][128]; static int s_iVt18;
static char s_c2e8Ret, s_c68C0Ret, s_cF7F0Null;
static int64_t s_iEB70Ret;
static void* s_pvC8E0;
static uint64_t s_u5EA0, s_uF550, s_uF270, s_u45520,
    s_u90390;
static int32_t s_i74E740, s_i74E740b;
static int s_n74E740Calls;
static uint32_t s_uVt350Args[2], s_uVt710Args[3];
static const char* s_pcVt90Buf; static uint32_t s_uVt90Arg;
static uint32_t s_uVt478Args[2];
static char s_acMyLogFile[64], s_acMyLogFmt[128];
static const char* s_pcNameArg;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nVt18 = s_nVt2e8 = s_nVt350 = s_nVt200 = 0;
    s_nVt1d8 = s_nVt480 = s_nVt8 = s_nVt710 = 0;
    s_nVt90 = s_nVt478 = 0;
    s_nEB70 = s_nC8E0 = s_n68C0 = s_nF7F0 = 0;
    s_nDCD0 = s_n03D0 = s_n0EA0 = s_nEA30 = 0;
    s_n45920 = s_nLog = s_nF550 = s_nFa70 = 0;
    s_nMyLog = 0;
    s_iVt18 = 0;
    s_c2e8Ret = 1; s_c68C0Ret = 1; s_cF7F0Null = 0;
    s_iEB70Ret = 0;
    s_pvC8E0 = (void*)0x88;
    s_u5EA0 = 0x31; s_uF550 = 500; s_uF270 = 0x77;
    s_u45520 = 0xAB; s_u90390 = 0;
    s_i74E740 = 100; s_i74E740b = 100;
    s_n74E740Calls = 0;
    s_pcNameArg = 0;
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x18/8] = (void*)+[](void*, uint32_t a,
        uint64_t b) -> uint64_t {
        s_nVt18++; (void)a;
        strncpy(s_acVt18Str[s_iVt18 % 3],
                (const char*)(uintptr_t)b, 127);
        s_iVt18++; return 0; };
    apBoxVt[0x2e8/8] = (void*)+[](void*,
        const char*) -> char {
        s_nVt2e8++; return s_c2e8Ret; };
    apBoxVt[0x350/8] = (void*)+[](void*, int32_t a,
        uint32_t b) -> uint64_t {
        s_nVt350++; s_uVt350Args[0] = a;
        s_uVt350Args[1] = b; return 0; };
    apBoxVt[0x200/8] = (void*)+[](void*, uint32_t)
        -> uint64_t { s_nVt200++; return 0; };
    apBoxVt[0x1d8/8] = (void*)+[](void*, uint32_t)
        -> uint64_t { s_nVt1d8++; return 0; };
    apBoxVt[0x480/8] = (void*)+[](void*, void* b,
        int32_t c) -> uint64_t {
        s_nVt480++; assert(b != 0 && c == 0);
        return 0; };
    apBoxVt[0x8/8] = (void*)+[](void*, uint32_t a,
        void* b) -> uint64_t {
        s_nVt8++; (void)a; assert(b != 0);
        return 0; };
    apBoxVt[0x90/8] = (void*)+[](void*,
        const char* b, uint32_t c) -> uint64_t {
        s_nVt90++;
        assert(strstr(b, "STR_LEAGUE_CREATE_LEAGUE")
               != 0);
        s_pcVt90Buf = b; s_uVt90Arg = c;
        return 0; };
    apBoxVt[0x478/8] = (void*)+[](void*, uint32_t a,
        int32_t b) -> uint64_t {
        s_nVt478++; s_uVt478Args[0] = a;
        s_uVt478Args[1] = b; return 0; };
    static void* apLogicVt[0x720/8];
    memset(apLogicVt, 0, sizeof(apLogicVt));
    apLogicVt[0x710/8] = (void*)+[](void*, void* a,
        uint32_t b, int32_t c) -> uint64_t {
        s_nVt710++; assert(a == (void*)0x55);
        s_uVt710Args[0] = b; s_uVt710Args[1] = c;
        return 0; };
    *(void***)abLogic = apLogicVt;
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[3] = (void*)0x33;  // p1[3]
    ((void**)abLogic)[10] = abSub;
    ((void**)abLogic)[2] = (void*)0x22;
    g_fn75EB70 = [](void* p, const char* n)
        -> int64_t {
        s_nEB70++; assert(p == abSub); (void)n;
        return s_iEB70Ret; };
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        s_nC8E0++; assert(p == (void*)0x33);
        (void)u; return s_pvC8E0; };
    g_fn7868C0 = [](void* p) -> char {
        assert(p == (void*)0x88);
        return s_c68C0Ret; };
    g_fn785EA0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x88); return s_u5EA0; };
    g_fn74E740 = [](void* p) -> int32_t {
        assert(p == abSub); s_n74E740Calls++;
        return s_n74E740Calls == 1
            ? s_i74E740 : s_i74E740b; };
    g_fn78F270 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return s_uF270; };
    g_fn787120 = [](void* p) -> char* {
        assert(p == (void*)0x88);
        return (char*)"PlayerName"; };
    g_fn76F7F0 = [](void* p, uint32_t u,
                    const char* n, char c,
                    uint32_t u2, const char* pn)
        -> void* {
        s_nF7F0++; assert(p == abSub);
        assert(u == 0x31); (void)n;
        s_pcNameArg = n;
        assert(c == 0 || c == 1);
        (void)u2; (void)pn;
        return s_cF7F0Null ? 0 : (void*)0x66; };
    g_fn74DCD0 = [](void* p, int32_t a) {
        s_nDCD0++; assert(p == (void*)0x66);
        assert(a == (int32_t)0x77); };
    g_fn7903D0 = [](void* p, int32_t a) -> char {
        s_n03D0++; assert(p == (void*)0x55);
        assert(a == (int32_t)0xAB); return 1; };
    g_fn7B0EA0 = [](void* p, uint32_t u, char c) {
        s_n0EA0++; assert(p == (void*)abLogic);
        assert(u == 0x42 && c == 1); };
    g_fn74EA30 = [](void* p, int32_t a) {
        s_nEA30++; assert(p == abSub);
        assert(a == 1); };
    g_fn745920 = [](void* p, void* b) {
        s_n45920++; assert(p == (void*)0x66);
        (void)b; };
    g_fn745520 = [](void* p) -> uint64_t {
        assert(p == (void*)0x66); return s_u45520; };
    g_fn790390 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return s_u90390; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22); (void)u;
        return (int64_t)0x55; };
    g_fnLgF550 = [](void* p) -> uint64_t {
        s_nF550++; assert(p == (void*)0x55);
        return s_uF550; };
    g_fnLgFa70 = [](void* p, uint64_t v) -> char {
        s_nFa70++; assert(p == (void*)0x55);
        assert((int32_t)v == 500 - 100);
        return 1; };
    g_fnMyLogSave = [](const char* f, const char* s) {
        s_nMyLog++;
        strncpy(s_acMyLogFile, f, 63);
        strncpy(s_acMyLogFmt, s, 127); };
    g_fn74E3F0 = [](void* p) -> uint32_t {
        assert(p == abSub); return 0x99; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                            const char* k) -> void* {
        return (void*)k; };
    g_fnCMsgCtor6640 = [](void*) {};
    g_fnCMsgDtor66C0 = [](void*) {};
    g_fnCMsgInit6790 = [](void* p, int32_t a,
                          uint32_t b, uint32_t c,
                          uint32_t d) -> uint64_t {
        assert(a == 6 && b == 0xAB && c == 0x99);
        (void)d; return 1; };
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
}

int main() {
    // ---- S1: the null gate ----
    Reset();
    assert(pL->Slot340(0x42, 0, 1) == false);
    assert(s_nVt18 == 0);
    // ---- S2: too long (> 15) -> no vt+0x2e8 ----
    Reset();
    assert(pL->Slot340(0x42, "aaaaaaaaaaaaaaaa", 1)
           == false);
    assert(s_nVt2e8 == 0 && s_nVt18 == 1);
    assert(strcmp(s_acVt18Str[0], "STR_INVALID_NAME")
           == 0);
    // ---- S3: rejected by vt+0x2e8 ----
    Reset();
    s_c2e8Ret = 0;
    assert(pL->Slot340(0x42, "abc", 1) == false);
    assert(s_nVt2e8 == 1 && s_nVt18 == 1);
    // ---- S4: forbidden name ----
    Reset();
    s_iEB70Ret = 5;
    assert(pL->Slot340(0x42, "abc", 1) == false);
    assert(strcmp(s_acVt18Str[0],
                  "STR_FORBIDDEN_LEAGUE_NAME") == 0);
    // ---- S5/S6: the player gates ----
    Reset();
    s_pvC8E0 = 0;
    assert(pL->Slot340(0x42, "abc", 1) == false);
    assert(s_nEB70 == 1 && s_n68C0 == 0);
    Reset();
    s_c68C0Ret = 0;
    assert(pL->Slot340(0x42, "abc", 1) == false);
    assert(s_nC8E0 == 1 && s_nF7F0 == 0);
    // ---- S7: the lg gates ----
    Reset();
    s_u90390 = 7;
    assert(pL->Slot340(0x42, "abc", 1) == false);
    assert(s_nF7F0 == 0);
    // ---- S8: c4=0, not enough money ----
    Reset();
    s_uF550 = 50;   // < cost 100
    assert(pL->Slot340(0x42, "abc", 0) == false);
    assert(s_nF550 == 1 && s_nFa70 == 0);
    assert(s_nF7F0 == 0);
    // ---- S9: c4=0, F7F0 fails -> the money ran ----
    Reset();
    s_cF7F0Null = 1;
    assert(pL->Slot340(0x42, "abc", 0) == false);
    assert(s_nFa70 == 1);
    assert(s_nVt350 == 1 && s_uVt350Args[0] == 0x42);
    assert(s_uVt350Args[1] == 0x77);
    assert(s_nVt200 == 1 && s_nVt1d8 == 1);
    assert(s_nMyLog == 1);
    assert(strcmp(s_acMyLogFile, "gmlog/emoney_buy")
           == 0);
    assert(strstr(s_acMyLogFmt, "4227") != 0);
    assert(s_nF7F0 == 1);
    // ---- S10: full success, c4=0 ----
    Reset();
    assert(pL->Slot340(0x42, "abc", 0) == true);
    assert(s_nMyLog == 1);   // the money path
    assert(s_nF7F0 == 1);
    assert(strcmp(s_pcNameArg, "abc") == 0);
    assert(s_nDCD0 == 1 && s_n03D0 == 1);
    assert(s_n45920 == 1 && s_nVt480 == 1);
    assert(s_nVt8 == 0);      // c4==0: no CMsg
    assert(s_nVt710 == 1);
    assert(s_uVt710Args[0] == 0xAB &&
           s_uVt710Args[1] == 7);
    assert(s_n0EA0 == 1);
    assert(s_nVt1d8 == 2);    // money + create
    assert(s_nVt90 == 1 && s_uVt90Arg == 0x7d5);
    assert(s_nVt478 == 0);
    // ---- S11: full success, c4=1 ----
    Reset();
    assert(pL->Slot340(0x42, "abc", 1) == true);
    assert(s_nMyLog == 0);   // no money path
    assert(s_nVt8 == 1);      // the CMsg broadcast
    // 74e740 second call = 100 != 0 -> create path
    assert(s_nVt90 == 1);
    assert(s_nVt478 == 0 && s_nEA30 == 0);
    // ---- S12: c4=1, 74e740 == 0 -> the else path ----
    Reset();
    s_i74E740b = 0;
    assert(pL->Slot340(0x42, "abc", 1) == true);
    assert(s_nVt90 == 0);
    assert(s_nVt478 == 1 && s_uVt478Args[1] == 6);
    assert(s_nEA30 == 1);
    puts("SYNDICATE_D102_OK: the create flow");
    return 0;
}

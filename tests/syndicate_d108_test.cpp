// D108 — CSyndicateLogic wave 13 (TRUE +0x1d0..+0x288)
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];
static int s_nLgFind, s_nLog, s_nVt8, s_nVt108;
static int64_t s_iLgFindRet;
static uint32_t s_uVt8Args[3];
static uint32_t s_uVt108Args[4];
static int s_n6440, s_n6620, s_nDD6E0, s_nDD730,
    s_nCFA30, s_nDB30, s_nC4F0, s_nCAD90, s_nC8AA0;
static uint32_t s_u6440Ret; static int32_t s_i6440Cur;
static char s_cDD790;
static std::vector<uint32_t> s_vec;
static const char* s_pcCFAVec;
static uint32_t s_uC4F0Arg;
static int64_t s_iC8AA0Ret;
static uint32_t s_uCADE0Ret;
static uint64_t s_u4F0Ret, s_u550Ret, s_uBF80Ret,
    s_uFA70Ret, s_uAB90Ret, s_uFB00Ret, s_u5B0Ret,
    s_uB9010Ret;
static uint32_t s_uE4A0Ret, s_uE400Ret;
static int64_t s_iBF80Arg; static int32_t s_iFA70Arg;
static uint32_t s_uCE230Ret;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nLgFind = s_nLog = s_nVt8 = s_nVt108 = 0;
    s_n6440 = s_n6620 = s_nDD6E0 = s_nDD730 = 0;
    s_nCFA30 = s_nDB30 = s_nC4F0 = s_nCAD90 = 0;
    s_nC8AA0 = 0;
    s_iLgFindRet = 0x55; s_u6440Ret = 3; s_i6440Cur = 3;
    s_cDD790 = 1; s_pcCFAVec = 0; s_uC4F0Arg = 0;
    s_iC8AA0Ret = 0x66; s_uCADE0Ret = 0x71;
    s_u4F0Ret = 100; s_u550Ret = 50; s_uBF80Ret = 0x81;
    s_uFA70Ret = 0x82; s_uAB90Ret = 0x83;
    s_uFB00Ret = 0x84; s_u5B0Ret = 0x85;
    s_uB9010Ret = 0x86; s_uE4A0Ret = 7; s_uE400Ret = 8;
    s_uCE230Ret = 9;
    s_vec = {11, 22, 33};
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x8/8] = (void*)+[](void*, uint32_t a,
        void* b) -> uint64_t {
        s_nVt8++; s_uVt8Args[0] = a;
        s_uVt8Args[1] = (uint32_t)(uintptr_t)b;
        return 0; };
    apBoxVt[0x108/8] = (void*)+[](void*, uint32_t a,
        uint32_t b, uint32_t c) -> uint64_t {
        s_nVt108++;
        s_uVt108Args[0] = a; s_uVt108Args[1] = b;
        s_uVt108Args[2] = c; return 0; };
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[2] = (void*)0x22;
    ((void**)abLogic)[3] = (void*)0x33;
    ((void**)abLogic)[6] = (void*)0x44;
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        s_nLgFind++; assert(p == (void*)0x22);
        (void)u; return s_iLgFindRet; };
    g_fnT1LogError = [](const char* s) { s_nLog++; (void)s; };
    g_fn78E4A0 = [](void* p, int32_t n) -> uint32_t {
        assert(p == (void*)0x55); assert(n == 4);
        return s_uE4A0Ret; };
    g_fn78E400 = [](void* p, int32_t n) -> uint32_t {
        assert(p == (void*)0x55); assert(n == 4);
        return s_uE400Ret; };
    g_fn78F470 = [](void* p) -> void* {
        assert(p == (void*)0x55); return (void*)0x99; };
    g_fn78F4F0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return s_u4F0Ret; };
    g_fn79BF80 = [](void* p, int64_t l) -> uint64_t {
        assert(p == (void*)0x55); s_iBF80Arg = l;
        return s_uBF80Ret; };
    g_fn7CAB90 = [](void* p) -> uint64_t {
        assert(p == (void*)0x22); return s_uAB90Ret; };
    g_fn78FB00 = [](void* p, uint8_t c) -> uint64_t {
        assert(p == (void*)0x55); assert(c == 2);
        return s_uFB00Ret; };
    g_fn78F5B0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return s_u5B0Ret; };
    g_fn786440 = [](void* p) -> uint32_t {
        s_n6440++; return s_i6440Cur; };
    g_fn786620 = [](void* p, int32_t n) {
        s_n6620++; assert(n == 9); };
    g_fn7DD6E0 = [](void* m) { s_nDD6E0++; (void)m; };
    g_fn7DD790 = [](void* m, int32_t a, void* b)
        -> char {
        assert(a == 0x10); (void)m; (void)b;
        return s_cDD790; };
    g_fn7DD730 = [](void* m) -> uint64_t {
        s_nDD730++; (void)m; return 0; };
    g_fn7CFA30 = [](void* p, void* v) {
        s_nCFA30++; assert(p == (void*)0x22);
        *(std::vector<uint32_t>*)v = s_vec; };
    g_fn79DB30 = [](void* p, int32_t n) {
        s_nDB30++; assert(p == (void*)0x55);
        assert(n == 0x10); };
    g_fn7CE230 = [](void* p, uint32_t a,
                     const char* b, uint32_t c, int32_t d,
                     uint32_t e) -> uint32_t {
        assert(p == (void*)0x22);
        assert(a == 1 && !strcmp(b, "nm"));
        assert(c == 2 && d == 3 && e == 4);
        return s_uCE230Ret; };
    g_fn77C4F0 = [](void* p, uint32_t u) {
        s_nC4F0++; assert(p == (void*)0x44);
        s_uC4F0Arg = u; };
    g_fn7B9010 = [](void* p, uint32_t a, uint32_t b)
        -> uint64_t {
        assert(p == (void*)abLogic);
        assert(a == 1 && b == 9);
        return s_uB9010Ret; };
    g_fn7CAD90 = [](void* p, uint32_t u) {
        s_nCAD90++; assert(p == (void*)0x22);
        assert(u == 6); };
    g_fn7C8AA0 = [](void* p, const char* n) -> int64_t {
        s_nC8AA0++; assert(p == (void*)0x22);
        assert(!strcmp(n, "syn"));
        return s_iC8AA0Ret; };
    g_fn7CADE0 = [](void* p, uint32_t u) -> uint64_t {
        assert(p == (void*)0x22); (void)u;
        return s_uCADE0Ret; };
    g_fn78F550 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return s_u550Ret; };
    g_fn78FA70 = [](void* p, int32_t n) -> uint64_t {
        assert(p == (void*)0x55); s_iFA70Arg = n;
        return s_uFA70Ret; };
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        assert(p == (void*)0x33);
        return u == 1 ? (void*)0x77 : 0; };
    g_fn78F270 = [](void* p) -> uint64_t {
        assert(p == (void*)0x66); return 0x87; };
    g_fn78F400 = [](void* p) -> uint32_t {
        assert(p == (void*)0x55); return 0x88; };
}

int main() {
    // ---- S1: constants & comparators ----
    Reset();
    assert(pL->Slot1D0() == 0xf);
    assert(pL->Slot1D8() == 0xf);
    assert(pL->Slot280(0x3de) == true);
    assert(pL->Slot280(0x3dd) == false);
    assert(pL->Slot288(0x37a) == true);
    assert(pL->Slot288(0x37b) == false);
    // ---- S2: the +0x1e0/+0x1e8 double chains ----
    Reset();
    assert(pL->Slot1E0(1, 4) == (const char*)0x99);
    assert(pL->Slot1E8(1, 4) == (const char*)0x99);
    assert(s_nLgFind == 4);
    s_uE4A0Ret = 0;
    assert(pL->Slot1E0(1, 4) == 0);
    // RAW: no log when uSyn == 0 (log is inside the
    // uSyn != 0 branch, only on the second-find miss)
    assert(s_nLog == 0);
    // second-find miss -> log: 1st find ok, 2nd fails
    {
        static int s_iCall = 0;
        g_fnLgFind = [](void* p, uint32_t u)
            -> int64_t {
            (void)p; (void)u;
            return (++s_iCall == 1) ? 0x55 : 0; };
        s_uE4A0Ret = 7;   // uSyn != 0 for the 2nd-find miss
        s_nLog = 0;
        assert(pL->Slot1E0(1, 4) == 0);
        assert(s_nLog == 1);
    }
    // ---- S3: the funds +0x1f0 ----
    Reset();
    uint64_t r0 = pL->Slot1F0(0, 5);
    printf("r0=%llu s_nLog=%d\n",(unsigned long long)r0,s_nLog);
    assert(r0 == 0 && s_nLog == 1);
    assert(pL->Slot1F0(1, 0) == 1);
    assert(pL->Slot1F0(1, 10) == 0x81);  // 100+10 ok
    assert(s_iBF80Arg == 10);
    // sum = 199999999999 < 200000000000 (0x2e90edd000)
    assert(pL->Slot1F0(1, 200000000000LL-101)
           == 0x81);
    // 100 + 199999999900 = exactly the cap -> reject
    assert(pL->Slot1F0(1, 200000000000LL-100) == 0);
    assert(s_nLgFind == 3);
    // ---- S4: the rank +0x1f8 ----
    Reset();
    assert(pL->Slot1F8(0, 5) == 0 && s_nLog == 1);
    assert(pL->Slot1F8(1, 0) == 1);
    assert(pL->Slot1F8(1, 10) == 0x82);
    assert(s_iFA70Arg == 60);
    // 50 + 0x3b9aca00 < 0x3b9aca01
    assert(pL->Slot1F8(1, 0x3b9aca01-51) == 0x82);
    // 50 + 0x3b9aca00+1 = exactly the cap -> reject
    assert(pL->Slot1F8(1, 0x3b9aca01-50) == 0);
    // ---- S5: the small wrappers ----
    Reset();
    // CONCAT71: (0x83 & ~0xff) | 1 == 1
    assert(pL->Slot200() == 1);
    assert(pL->Slot208(1, 2) == 0x84);
    assert(pL->Slot208(0, 2) == 0);
    assert(pL->Slot210(1) == 0x85);
    assert(pL->Slot268(1) == 100);
    assert(pL->Slot270(1, 3) == 0x81);
    assert(s_iBF80Arg == 3);
    assert(pL->Slot278(1) == 50);
    assert(pL->Slot278(0) == 0 && s_nLog == 1);
    assert(pL->Slot258(1) == 0x88);
    assert(pL->Slot248(6) == 0 && s_nCAD90 == 1);
    // ---- S6: the name flows ----
    Reset();
    assert(pL->Slot250("syn") == 0x87);
    assert(pL->Slot250(0) == 0 && s_nLog == 1);
    s_iC8AA0Ret = 0;
    assert(pL->Slot250("syn") == 0);
    // ---- S7: +0x260 the in-out probe ----
    Reset();
    uint32_t u = 5;
    assert(pL->Slot260(&u) == 1 && u == 0x71);
    s_uCADE0Ret = 0;
    u = 5;
    assert(pL->Slot260(&u) == 0 && u == 5);
    // ---- S8: +0x218 the CMsg push ----
    Reset();
    assert(pL->Slot218(0, 9) == 0 && s_nLog == 1);
    assert(pL->Slot218(2, 9) == 0 && s_nLog == 2);
    assert(pL->Slot218(1, 3) == 1);   // 6440 == 3: no set
    assert(s_nVt8 == 1 && s_nDD6E0 == 1);
    assert(s_nDD730 == 1 && s_n6620 == 0);
    assert(s_uVt8Args[0] == 1);
    assert(pL->Slot218(1, 9) == 1);
    assert(s_n6620 == 1);   // 6440 != 9 -> set
    // ---- S9: +0x220 the member sweep ----
    Reset();
    pL->Slot220();
    assert(s_nCFA30 == 1 && s_nDB30 == 3);
    // ---- S10: +0x228 the create+broadcast ----
    Reset();
    // CONCAT71: (0x86 & ~0xff) | 1 == 1
    assert(pL->Slot228(1, "nm", 2, 3, 4) == 1);
    assert(s_nVt108 == 1 && s_uVt108Args[0] == 1);
    assert(s_uVt108Args[1] == 9);
    assert(s_uVt108Args[2] == 0);
    assert(s_nC4F0 == 1 && s_uC4F0Arg == 9);
    s_uCE230Ret = 0;
    assert(pL->Slot228(1, "nm", 2, 3, 4) == 0);
    assert(s_nVt108 == 1 && s_nC4F0 == 1);
    puts("SYNDICATE_D108_OK: wave 13");
    return 0;
}

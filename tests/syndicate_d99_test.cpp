// D99 — CSyndicateLogic wave 9: slots +0x260..+0x2c8
// (14 verbatim bodies + the STR_NOTIFY_NEW_COUNTRY_LEAGUE
// flow in +0x278 and the manual strcmp in +0x2c0).
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x80];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];
static uint8_t abInner[0x40];

static int s_nCtor, s_nDtor, s_nD10, s_nE60, s_nCdf,
    s_nEcf0, s_nEe60, s_nFbf0, s_nVt8, s_nVt98,
    s_nVtA0, s_n9220, s_n52d0, s_nLog;
static uint32_t s_u510, s_u74E3F0, s_u763C80, s_u763680;
static uint32_t s_u763C80Arg;
static void* s_pv7630D0; static char s_c6790;
static uint64_t s_u6790Args[6];
static int s_n6790;
static int32_t s_u6790Types[4];
static uint32_t s_uVt8Args[3], s_uVtA0Args[4];
static uint64_t s_u9220Args[3], s_u52d0Args[4];
static char s_ac510Ret;
static uint32_t s_u647E0Ret;
static void* s_pv743Dd0, *s_pv743D70;
static char s_cFbf0Last;
static char s_acName[16];
static const char* s_pcVtA0Buf;
static char s_acVtA0Copy[128];

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    memset(abInner, 0, sizeof(abInner));
    strcpy(s_acName, "LeagueName");
    s_nCtor = s_nDtor = s_nD10 = s_nE60 = s_nCdf = 0;
    s_nEcf0 = s_nEe60 = s_nFbf0 = 0;
    s_nVt8 = s_nVt98 = s_nVtA0 = 0;
    s_n9220 = s_n52d0 = s_nLog = 0;
    s_u510 = 7; s_u74E3F0 = 0; s_u763C80 = 0;
    s_u763680 = 0; s_pv7630D0 = 0; s_c6790 = 1;
    s_pv743Dd0 = 0; s_pv743D70 = s_acName;
    s_u647E0Ret = 0;
    s_n6790 = 0;
    // the box: an object whose [0] is the vt
    static void* apBox[1]; static void* apBoxVt[64];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x8 / 8] = (void*)+[](void*,
        uint32_t a, void* b) -> uint64_t {
        s_nVt8++; s_uVt8Args[0] = a;
        s_uVt8Args[1] = (uint32_t)(uint64_t)b;
        return 0; };
    apBoxVt[0x98 / 8] = (void*)+[](void*, void*)
        -> uint64_t { s_nVt98++; return 0; };
    apBoxVt[0xa0 / 8] = (void*)+[](void*,
        uint32_t a, const char* b, uint32_t c)
        -> uint64_t {
        s_nVtA0++; s_uVtA0Args[0] = a;
        // copy now — the stack buffer dies at return
        strncpy(s_acVtA0Copy, b, 127);
        s_pcVtA0Buf = s_acVtA0Copy; s_uVtA0Args[2] = c;
        return 0; };
    // the logic vt (0x510 rank gate + identity)
    static void* apLogicVt[0x600/8];
    memset(apLogicVt, 0, sizeof(apLogicVt));
    apLogicVt[0x510 / 8] = (void*)+[]()
        -> uint32_t { return s_u510; };
    *(void***)abLogic = apLogicVt;
    // this+8 = the box, this+0x50/0x10 = sub objects
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;   // +0x50
    ((void**)abLogic)[2] = (void*)0x22;  // +0x10 mgr
    g_fnMgrCdfD0 = [](void* p) {
        s_nCdf++; assert(p == (void*)0x33); };
    g_fn647E0 = [](void* p, uint32_t u)
        -> int32_t {
        assert(p == abSub); (void)u;
        return (int32_t)s_u647E0Ret; };
    g_fn74E3F0 = [](void* p) -> uint32_t {
        assert(p == abSub); return s_u74E3F0; };
    g_fn7630D0 = [](void* p, uint32_t u)
        -> void* {
        assert(p == abSub); (void)u;
        return s_pv7630D0; };
    g_fn743D10 = [](void* p) {
        s_nD10++; assert(p == (void*)0x77); };
    g_fn743E60 = [](void* p) {
        s_nE60++; assert(p == (void*)0x77); };
    g_fn743Dd0 = [](void* p) -> void* {
        assert(p == (void*)0x77); return s_pv743Dd0; };
    g_fn743D70 = [](void* p) -> void* {
        assert(p == (void*)0x77); return s_pv743D70; };
    g_fn763C80 = [](void* p, uint32_t u)
        -> uint32_t {
        assert(p == abSub); s_u763C80Arg = u;
        return s_u763C80; };
    g_fn76EE60 = [](void* p, uint32_t u,
                    int32_t n) {
        s_nEe60++; assert(p == abSub);
        assert(u == 9 && n == 3); };
    g_fn76FBF0 = [](void* p, uint32_t u,
                    int32_t n, uint64_t v, char c) {
        s_nFbf0++; assert(p == abSub);
        assert(u == 5 && n == 4);
        s_cFbf0Last = c; };
    g_fn763680 = [](void* p, uint32_t u)
        -> uint64_t {
        assert(p == abSub); (void)u;
        return s_u763680; };
    g_fn78F2D0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0xAA; };
    g_fn76ECF0 = [](void* p, uint32_t u,
                    int32_t n) {
        s_nEcf0++; assert(p == abSub);
        assert(u == 6 && n == 2); };
    g_fn7B9220 = [](void* p, uint32_t a,
                    uint32_t b) -> uint32_t {
        s_n9220++; assert(p == (void*)abLogic);
        s_u9220Args[0] = a; s_u9220Args[1] = b;
        return 0x99; };
    g_fn7B52D0 = [](void* p, uint32_t a,
                    uint32_t b, void* c) {
        s_n52d0++; assert(p == (void*)abLogic);
        s_u52d0Args[0] = a; s_u52d0Args[1] = b;
        s_u52d0Args[2] = (uint64_t)c; };
    g_fnLgFind = [](void* p, uint32_t u)
        -> int64_t {
        assert(p == (void*)0x22);
        return u == 0x88 ? (int64_t)0x55 : 0; };
    g_fnCMsgCtor6640 = [](void*) { s_nCtor++; };
    g_fnCMsgInit6790 = [](void* p, int32_t t,
                          uint32_t a, uint32_t b,
                          uint32_t c) -> uint64_t {
        if (s_n6790 < 4) {
            s_u6790Types[s_n6790] = t;
            s_u6790Args[1] = a; s_u6790Args[2] = b;
            s_u6790Args[3] = c;
        }
        s_n6790++;
        return s_c6790; };
    g_fnCMsgDtor66C0 = [](void*) { s_nDtor++; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                            const char* k) -> void* {
        return (void*)k; };
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
}

int main() {
    // ---- S1: +0x260 the destroy guard ----
    Reset();
    ((void**)abLogic)[2] = 0;        // +0x10 == 0
    pL->Slot260Destroy();
    assert(s_nCdf == 0);
    ((void**)abLogic)[2] = (void*)0x33;
    pL->Slot260Destroy();
    assert(s_nCdf == 1);
    ((void**)abLogic)[2] = (void*)0x22;  // back to mgr
    // ---- S2: +0x268 / +0x270 the rank gates ----
    Reset();
    assert(pL->Slot268(0) == 0);
    assert(pL->Slot268(1) == 0);      // 1 != 0
    s_u647E0Ret = 1;
    assert(pL->Slot268(1) == 1);      // match
    assert(pL->Slot270(0) == 0);
    s_u510 = 0;
    assert(pL->Slot270(1) == 0);      // vt510 ret 0
    s_u510 = 7; s_u74E3F0 = 7;
    assert(pL->Slot270(1) == 1);      // 7 == 7
    // ---- S3: +0x278 the country-league flow ----
    Reset();
    s_u763680 = 0x88; s_u763C80 = 0;
    pL->Slot278(5, 4, 0x66, 1);      // c5=1: no bcast
    assert(s_nFbf0 == 1 && s_cFbf0Last == 1
           && s_nVt8 == 1);
    assert(s_uVt8Args[0] == 0xAA);   // the lg type
    assert(s_n6790 == 2);
    assert(s_u6790Types[0] == 0x11);  // the A msg
    assert(s_u6790Types[1] == 0x15);  // the B msg
    assert(s_nVt98 == 1);            // 6790 ok -> vt98
    assert(s_nVtA0 == 0);            // c5!=0: no a0
    assert(s_nCtor == 2 && s_nDtor == 2);
    // c5=0 + uVar3<n3 -> the STR_NOTIFY bcast
    pL->Slot278(5, 4, 0x66, 0);
    assert(s_nVtA0 == 1 && s_nVt98 == 2);
    assert(strstr(s_pcVtA0Buf,
                  "STR_NOTIFY_NEW_COUNTRY_LEAGUE")
           != 0);
    assert(s_nDtor == 4);
    // ---- S4: +0x280 the short cousin ----
    Reset();
    s_u763680 = 0x88;
    pL->Slot280(6, 2, (void*)0x66);
    assert(s_nEcf0 == 1 && s_n9220 == 1);
    assert(s_u52d0Args[0] == 0x99);
    // ---- S5: the +0x50 family ----
    Reset();
    s_u763C80 = 33;
    pL->Slot288(9);
    assert(s_u763C80Arg == 9);   // u forwarded
    pL->Slot298();
    s_pv7630D0 = (void*)0x77; s_u74E3F0 = 3;
    pL->Slot290();
    assert(s_nD10 == 1);
    pL->Slot2A8();
    assert(s_nE60 == 1);
    pL->Slot2A0(9, 3);
    assert(s_nEe60 == 1);
    // ---- S6: the name getters ----
    Reset();
    s_pv7630D0 = (void*)0x77; s_u74E3F0 = 3;
    assert(pL->Slot2B0() == 0);      // Dd0 null
    s_pv743Dd0 = s_acName;
    assert(pL->Slot2B0() == s_acName);
    assert(pL->Slot2B8() ==
           (uint64_t)(uint64_t*)s_acName);
    assert(s_nLog == 0);            // found: no log
    // the manual strcmp(name, ""): empty name ->
    // the Dd0 path (currently s_acName)
    s_pv743D70 = (char*)"";
    assert(pL->Slot2C0() == s_acName);
    assert(s_nLog == 0);
    // non-empty name -> this+0x61
    s_pv743D70 = s_acName;
    assert(pL->Slot2C0() == abLogic + 0x61);
    // empty + Dd0 null -> the "" fallback
    s_pv743Dd0 = 0; s_pv743D70 = (char*)"";
    assert(strcmp((char*)pL->Slot2C0(), "") == 0);
    // lookup fail -> the literal log + 0
    s_pv7630D0 = 0;
    pL->Slot2B8(); pL->Slot2C0();
    assert(s_nLog == 2);
    // ---- S7: +0x2c8 ----
    Reset();
    s_pv7630D0 = (void*)0x77; s_pv743Dd0 = s_acName;
    assert(pL->Slot2C8(0) == 0);
    assert(pL->Slot2C8(5) == s_acName);
    puts("SYNDICATE_D99_OK: wave 9");
    return 0;
}

// D103 — CSyndicateLogic +0x350: 1417b16b0 join-league flow
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nVt28, s_nVt90, s_nVt3f0, s_nVt710, s_nC80,
    s_n977D0, s_n3920, s_nE7E0, s_nDCD0, s_n03D0,
    s_nF470, s_nCA70, s_nLog, s_nC3D0;
static char s_cLog2, s_acVt28Str[3][128];
static uint32_t s_uVt28Args[3]; static int s_iVt28;
static uint32_t s_uVt90Arg; static const char* s_pcVt90;
static uint64_t s_uC80Ret; static char s_c977D0Ret,
    s_c3920Ret, s_c03D0Ret;
static int32_t s_iVt3f0Ret;
static uint32_t s_uCA70Args[4];
static uint64_t s_uLgFindIds[4]; static int s_nLgFind;
static void* s_pv7630D0;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nVt28 = s_nVt90 = s_nVt3f0 = s_nVt710 = 0;
    s_nC80 = s_n977D0 = s_n3920 = s_nE7E0 = 0;
    s_nDCD0 = s_n03D0 = s_nF470 = s_nCA70 = 0;
    s_nLog = 0; s_iVt28 = 0;
    s_cLog2 = 0;
    s_uC80Ret = 0x41; s_c977D0Ret = 0;
    s_c3920Ret = 0; s_c03D0Ret = 1;
    s_iVt3f0Ret = 3;
    s_nLgFind = 0; s_nC3D0 = 0;
    s_pv7630D0 = (void*)0x66;
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x28/8] = (void*)+[](void*, uint32_t a,
        const char* b, uint32_t c) -> uint64_t {
        s_nVt28++;
        strncpy(s_acVt28Str[s_iVt28 % 3], b, 127);
        s_uVt28Args[0] = a;
        s_uVt28Args[1] = c; s_iVt28++; return 0; };
    apBoxVt[0x90/8] = (void*)+[](void*,
        const char* b, uint32_t c) -> uint64_t {
        s_nVt90++; s_pcVt90 = b; s_uVt90Arg = c;
        return 0; };
    apBoxVt[0x3f0/8] = (void*)+[](void*, void*)
        -> int32_t { s_nVt3f0++; return s_iVt3f0Ret; };
    static void* apLogicVt[0x720/8];
    memset(apLogicVt, 0, sizeof(apLogicVt));
    apLogicVt[0x710/8] = (void*)+[](void*, void* a,
        uint32_t b, int32_t c) -> uint64_t {
        s_nVt710++; assert(a == (void*)0x55);
        assert(b == 0x44 && c == 0xb);
        return 0; };
    *(void***)abLogic = apLogicVt;
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;
    ((void**)abLogic)[2] = (void*)0x22;
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22);
        s_uLgFindIds[s_nLgFind % 4] = u; s_nLgFind++;
        // u3=0x33 -> 0x55; the leader id 0x41 -> 0x77
        if (u == 0x33) return 0x55;
        if (u == 0x41) return 0x77;
        return 0; };
    g_fn78F2D0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x22; };
    g_fn790390 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0; };
    g_fn7630D0 = [](void* p, uint32_t u) -> void* {
        assert(p == abSub); (void)u;
        return s_pv7630D0; };
    g_fn743C80 = [](void* p) -> uint64_t {
        s_nC80++; assert(p == (void*)0x66);
        return s_uC80Ret; };
    g_fn7977D0 = [](void* p, uint32_t u) -> char {
        s_n977D0++;
        // leader lg (0x77) or self lg (0x55)
        assert(p == (void*)0x77 || p == (void*)0x55);
        (void)u; return s_c977D0Ret; };
    g_fn763920 = [](void* p, uint32_t u) -> char {
        s_n3920++; assert(p == abSub);
        assert(u == 0x22); return s_c3920Ret; };
    g_fn74E7E0 = [](void* p) {
        s_nE7E0++; assert(p == abSub); };
    g_fn7903D0 = [](void* p, int32_t a) -> char {
        s_n03D0++;
        assert(p == (void*)0x55 && a == 0x44);
        return s_c03D0Ret; };
    g_fn74DCD0 = [](void* p, int32_t a) {
        s_nDCD0++; assert(p == (void*)0x66);
        assert(a == 0x33); };
    g_fn78F470 = [](void* p) -> void* {
        s_nF470++; assert(p == (void*)0x55);
        return 0; };
    g_fn76CA70 = [](void* p, uint32_t a, int32_t b,
                    uint32_t c) -> int32_t {
        s_nCA70++; assert(p == abSub);
        s_uCA70Args[0] = a; s_uCA70Args[1] = (uint32_t)b;
        s_uCA70Args[2] = c;
        return 0; };
    g_fn743Dd0 = [](void* p) -> void* {
        s_nC3D0++; assert(p == (void*)0x66);
        return (void*)"SynName"; };
    g_fnT1LogError = [](const char* s) {
        s_nLog++;
        if (strstr(s, "SynJoinLeague failure"))
            s_cLog2 = 1; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                            const char* k) -> void* {
        return (void*)k; };
}

int main() {
    // ---- S1: the lg gate fails silently ----
    Reset();
    pL->Slot350(0x22, 0x99, 0x44);  // LgFind miss
    assert(s_nLgFind == 1 && s_nVt28 == 0);
    // ---- S2: type mismatch -> silent ----
    Reset();
    // 78f2d0 = 0x22 == u2 0x22 ok; use u2 wrong:
    pL->Slot350(0x99, 0x33, 0x44);
    assert(s_nC80 == 0 && s_nVt28 == 0);
    // ---- S3: leader lookup fails -> literal log ----
    Reset();
    s_uC80Ret = 0x71;   // no lg at 0x71
    pL->Slot350(0x22, 0x33, 0x44);
    assert(s_nC80 == 2);   // called again in the log
    assert(s_nLog == 1);
    // ---- S4: enemy -> STR_LEAGUE_IS_ENEMY_SYN ----
    Reset();
    s_c977D0Ret = 1;
    pL->Slot350(0x22, 0x33, 0x44);
    assert(s_nVt28 == 1 && s_nVt90 == 0);
    assert(strcmp(s_acVt28Str[0],
                  "STR_LEAGUE_IS_ENEMY_SYN") == 0);
    assert(s_uVt28Args[1] == 0xffff00);
    // ---- S5: leave-soon -> STR_LEAGUE_LEAVE_SOON ----
    Reset();
    s_c3920Ret = 0;   // 763920 == 0 -> leave path
    pL->Slot350(0x22, 0x33, 0x44);
    assert(s_n977D0 == 2);   // both checks ran
    assert(s_nE7E0 == 1);
    assert(strcmp(s_acVt28Str[0],
                  "STR_LEAGUE_LEAVE_SOON") == 0);
    assert(s_nVt90 == 0 && s_nLog == 0);
    // ---- S6: 03D0 fails -> the failure log ----
    Reset();
    s_c3920Ret = 1; s_c03D0Ret = 0;
    pL->Slot350(0x22, 0x33, 0x44);
    assert(s_nF470 == 1 && s_nLog == 1
           && s_cLog2 == 1);
    assert(s_nVt90 == 0 && s_nDCD0 == 0);
    // ---- S7: the full success path ----
    Reset();
    s_c3920Ret = 1;
    pL->Slot350(0x22, 0x33, 0x44);
    assert(s_nDCD0 == 1 && s_nVt710 == 1);
    assert(s_nVt3f0 == 1);
    // 0x44 + 3*1000000 = 3000068
    assert(s_uCA70Args[0] == 0x44 + 3000000);
    assert(s_uCA70Args[1] == 0 && s_uCA70Args[2] == 0x33);
    assert(s_nC3D0 == 1 && s_nF470 == 1);
    assert(s_nVt90 == 1 && s_uVt90Arg == 0x843);
    assert(strstr(s_pcVt90, "STR_SYN_JOIN_LEAGUE") != 0);
    assert(s_nVt28 == 0 && s_nLog == 0);
    puts("SYNDICATE_D103_OK: the join flow");
    return 0;
}

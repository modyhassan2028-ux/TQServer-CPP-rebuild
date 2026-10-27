// D110 — CSyndicateLogic wave 15 (+0x050/+0x060/+0x120)
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static int s_nLog;
static void* s_pPlayer[2];
static uint32_t s_uPlayerArg[4];
static uint64_t s_uEa0Ret[2]; static int s_nEa0;
static int64_t s_i62C0Ret; static int s_n62C0, s_n5F00;
static int32_t s_i5F00Args[3];
static int64_t s_l4F0Ret; static int s_nBF80, s_nMyLog;
static int64_t s_iBF80Arg;
static int s_n7370[2]; static uint32_t s_u7370Args[2][2];
static char s_cE590; static int s_nE590;
static int64_t s_i67D0[2]; static int s_n67D0;
static int64_t s_iA05D; static int s_nA05D, s_nA0760;
static int32_t s_iA0760Args[4]; static char s_cA0760Arg5;
static char s_cAEB; static int s_nAEB;
static int s_nDB2B0, s_nDB3A0, s_nDB330;
static char s_cDB3A0; static uint64_t s_uDB330;
static int s_nVt10, s_nVt18, s_nVt88, s_nVt328, s_nVt8;
static uint32_t s_uVtArgs[4];
static char s_pcVt18Str[64]; static int64_t s_lLgFind;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    s_nLog = 0;
    s_pPlayer[0] = s_pPlayer[1] = 0;
    s_uPlayerArg[0] = s_uPlayerArg[1] = 0;
    s_nEa0 = 0; s_uEa0Ret[0] = 500; s_uEa0Ret[1] = 500;
    s_i62C0Ret = 100; s_n62C0 = s_n5F00 = 0;
    memset(s_i5F00Args, 0, sizeof(s_i5F00Args));
    s_l4F0Ret = 1000; s_nBF80 = s_nMyLog = 0;
    s_iBF80Arg = 0;
    memset(s_n7370, 0, sizeof(s_n7370));
    memset(s_u7370Args, 0, sizeof(s_u7370Args));
    s_cE590 = 0; s_nE590 = 0;
    s_i67D0[0] = 1000; s_i67D0[1] = 1000;
    s_n67D0 = 0;
    s_iA05D = 1; s_nA05D = s_nA0760 = 0;
    memset(s_iA0760Args, 0, sizeof(s_iA0760Args));
    s_cA0760Arg5 = -1;
    s_cAEB = 1; s_nAEB = 0;
    s_nDB2B0 = s_nDB3A0 = s_nDB330 = 0;
    s_cDB3A0 = 1; s_uDB330 = 0x55;
    s_nVt10 = s_nVt18 = s_nVt88 = s_nVt328 = s_nVt8 = 0;
    memset(s_uVtArgs, 0, sizeof(s_uVtArgs));
    s_pcVt18Str[0] = 0; s_lLgFind = 0x66;
    static void* apBox[1]; static void* apBoxVt[0x400/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x10/8] = (void*)+[](void*, uint32_t a,
        int32_t b, const void* c) -> uint64_t {
        s_nVt10++; s_uVtArgs[0] = a;
        assert(b == 2000); assert(!strcmp(
            (const char*)c, "EXPLOST_PAYBY_SYNFUND"));
        return 0; };
    apBoxVt[0x328/8] = (void*)+[](void*, uint32_t a)
        -> uint32_t {
        s_nVt328++; s_uVtArgs[1] = a; return 0x77; };
    // NOTE: the RAW 3-arg call sites leave the 4th
    // register as garbage; only read d when the
    // string says this is the 4-arg kick site
    apBoxVt[0x18/8] = (void*)+[](void*, uint32_t a,
        const void* c, void* d) -> uint64_t {
        s_nVt18++; s_uVtArgs[2] = a;
        snprintf(s_pcVt18Str, sizeof(s_pcVt18Str),
                 "%s", (const char*)c);
        if (!strcmp((const char*)c,
                    "STR_KICKOUT_ME_s"))
            snprintf(s_pcVt18Str +
                strlen(s_pcVt18Str), 32, "|%s",
                (char*)d);
        return 0; };
    apBoxVt[0x88/8] = (void*)+[](void*, uint32_t a,
        void* b, uint64_t d) -> uint64_t {
        s_nVt88++; s_uVtArgs[3] = a;
        assert(d == 0); (void)b; return 0; };
    apBoxVt[8/8] = (void*)+[](void*, uint32_t a,
        void* b) -> uint64_t {
        s_nVt8++; s_uVtArgs[0] = a; (void)b; return 0; };
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[2] = (void*)0x22;
    ((void**)abLogic)[3] = (void*)0x33;
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        assert(p == (void*)0x33);
        return u == 1 ? s_pPlayer[0] :
               u == 2 ? s_pPlayer[1] : 0; };
    g_fn785EA0 = [](void* p) -> uint64_t {
        return p == s_pPlayer[0] ? 5 :
               p == s_pPlayer[1] ? 6 : 7; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22); (void)u;
        return s_lLgFind; };
    g_fn7868C0 = [](void*) -> char { return 0; };
    g_fn7AEA90 = [](void* a, void* b, void* c)
        -> int32_t {
        s_nEa0++; assert(a == (void*)abLogic);
        (void)b; (void)c;
        return (int32_t)s_uEa0Ret[s_nEa0 - 1]; };
    g_fn7862C0 = [](void*) -> int64_t {
        s_n62C0++; return s_i62C0Ret; };
    g_fn785F00 = [](void* p, int32_t a, void* b,
                    int64_t c) {
        s_n5F00++; (void)p;
        s_i5F00Args[0] = a; s_i5F00Args[1] =
            (int32_t)(intptr_t)b; s_i5F00Args[2] =
            (int32_t)c; };
    g_fn78F4F0 = [](void*) -> uint64_t {
        return (uint64_t)s_l4F0Ret; };
    g_fn79BF80 = [](void* p, int64_t v)
        -> uint64_t {
        s_nBF80++; (void)p; s_iBF80Arg = v;
        return 0; };
    g_fnMyLogSave = [](const char* f, const char* m) {
        s_nMyLog++;
        assert(!strcmp(f, "gmlog/syndenote"));
        assert(strstr(m, "Spend (Death Lost)")); };
    g_fn787370 = [](void* p, uint32_t u) {
        for (int i = 0; i < 2; i++) if (!s_n7370[i]) {
            s_n7370[i]++;
            s_u7370Args[i][0] =
                (uint32_t)(p == s_pPlayer[0]);
            s_u7370Args[i][1] = u; return; } };
    g_fn78E590 = [](void* p) -> char {
        s_nE590++; (void)p; return s_cE590; };
    g_fn7867D0 = [](void* p) -> int64_t {
        s_n67D0++;
        return p == s_pPlayer[0] ? s_i67D0[0] :
               s_i67D0[1]; };
    g_fn7A05D0 = [](void* a, void* b, void* c)
        -> int64_t {
        s_nA05D++; (void)a; (void)b; (void)c;
        return s_iA05D; };
    g_fn7A0760 = [](void* a, void* b, int32_t c,
                    uint32_t d, char e) {
        s_nA0760++; (void)a; (void)b;
        s_iA0760Args[0] = c; s_iA0760Args[1] =
            (int32_t)d; s_cA0760Arg5 = e; };
    g_fn7AEBB0 = [](void* a, void* b, void* c,
                    const char* d, char e, char f,
                    char g) -> uint64_t {
        s_nAEB++; (void)a; (void)b; (void)c;
        assert(strstr(d, "KickOutMember By ID"));
        (void)e; assert(f == 1); (void)g;
        return (uint64_t)(uint8_t)s_cAEB; };
    g_fn7DB2B0 = [](void* p) {
        s_nDB2B0++; (void)p; };
    g_fn7DB3A0 = [](void* p, int32_t a, int32_t b)
        -> char {
        s_nDB3A0++; (void)p;
        assert(a == 0x2c && b == 0); return s_cDB3A0; };
    g_fn7DB330 = [](void* p) -> uint64_t {
        s_nDB330++; (void)p; return s_uDB330; };
    g_fn787120 = [](void*) -> char* {
        return (char*)"PlayerOne"; };
    g_fn78F270 = [](void*) -> uint64_t {
        return 0x99; };
    static const char* s_apStrs[] = {
        "EXPLOST_PAYBY_SYNFUND",
        "STR_TOO_LOWER_SYN_MONEY",
        "STR_KICKOUT_ME_s", "STR_KICKOUT_MEMBER_s"};
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x10; };
    g_fnStringMgrGetStr = [](void* p,
        const char* n) -> void* {
        assert(p == (void*)0x10);
        bool ok = false;
        for (auto s : s_apStrs)
            if (!strcmp(n, s)) ok = true;
        assert(ok); return (void*)n; };
}

int main() {
    // ---- S1: +0x050 the id-zero reject ----
    Reset();
    assert(pL->Slot050(0, 0, 100) == 0);
    assert(s_nLog == 1);
    // ---- S2: +0x050 player miss / league miss ----
    Reset();
    assert(pL->Slot050(9, 0, 100) == 100);
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_lLgFind = 0;
    assert(pL->Slot050(1, 0, 100) == 100);
    // ---- S3: +0x050 the full spend ----
    Reset();
    s_pPlayer[0] = (void*)0x50;   // not leader
    // 500*100000/10000 = 5000; 5000/10000=0 -> min 1
    // player money 100 >= 1 -> 5F00(99)
    // spend clamped to the fund (1000), so
    // 100000 - 1000*100 == 0
    assert(pL->Slot050(1, 0, 100000) == 0);
    Reset();
    s_pPlayer[0] = (void*)0x50;
    // 7AEA90=0 -> spend 0, but the player-money
    // check (100 < 1) passes -> 5F00(99) still runs
    s_uEa0Ret[0] = 0;
    assert(pL->Slot050(1, 0, 500) == 500);
    assert(s_n5F00 == 1 && s_i5F00Args[0] == 99);
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_uEa0Ret[0] = 100; s_i62C0Ret = 2;
    // 100*50/10000 = 0; 0/10000=0 -> min 1;
    // 2 >= 1 ok -> 5F00(1, lg, l4=50)
    assert(pL->Slot050(1, 0, 50) == 50 - 0);
    assert(s_n5F00 == 1 && s_i5F00Args[0] == 1);
    // ---- S4: +0x050 the >9999 log path ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_uEa0Ret[0] = 100000000;
    s_i62C0Ret = 1000000000;  // money check passes
    // spend 1000000 clamped to fund 20000 -> log
    s_l4F0Ret = 20000;
    assert(pL->Slot050(1, 0, 100) == 0);
    assert(s_nMyLog == 1 && s_nBF80 == 1);
    assert(s_iBF80Arg == -20000);
    assert(s_nVt10 == 1 && s_uVtArgs[0] == 1);
    // ---- S5: +0x060 the swap ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    s_uEa0Ret[0] = 0;
    // leagues differ (5 vs 6) -> & ~0xff
    assert(pL->Slot060(1, 2) == 0);
    assert(s_n7370[0] == 1 && s_n7370[1] == 1);
    assert(s_u7370Args[0][1] == 2 &&
           s_u7370Args[1][1] == 1);
    // ---- S6: +0x060 same league, roles ok ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    // same-league path: force 85ea0 equal
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    s_iA05D = 1; s_i67D0[1] = 0x398;
    assert(pL->Slot060(1, 2) == 1);   // CONCAT71 |1
    assert(s_nA05D == 1 && s_nA0760 == 1);
    assert(s_iA0760Args[0] == 0x262);  // 0x398 role
    assert(s_iA0760Args[1] == 0x77);   // vt+0x328
    assert(s_cA0760Arg5 == 0);
    // ---- S7: +0x060 pair-check both fail ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    s_iA05D = 0; s_i67D0[0] = 1000;
    assert(pL->Slot060(1, 2) == 1);   // still CONCAT71
    assert(s_nA05D == 2 && s_nA0760 == 0);
    // ---- S8: +0x120 the early rejects ----
    Reset();
    assert(pL->Slot120(0, 2) == 0);
    assert(s_nLog == 1);
    assert(pL->Slot120(1, 0) == 0);
    assert(s_nLog == 2);
    Reset();
    assert(pL->Slot120(1, 2) == 0);   // both miss
    // ---- S9: +0x120 the low-money tip ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    s_i67D0[0] = 1000;   // leader rank
    s_cE590 = 1;         // league too poor
    assert(pL->Slot120(1, 2) == 0);
    assert(s_nVt18 == 1 && !strcmp(s_pcVt18Str,
        "STR_TOO_LOWER_SYN_MONEY"));
    assert(s_nAEB == 0);
    // ---- S10: +0x120 the kick-out success ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    s_i67D0[0] = 1000;   // 1000 -> rank gate ok
    s_cE590 = 0;         // league money fine
    s_cAEB = 1;          // kick succeeds
    assert(pL->Slot120(1, 2) == 1);  // CONCAT71 |1
    assert(s_nAEB == 1);
    assert(s_nVt18 == 1 && !strcmp(s_pcVt18Str,
        "STR_KICKOUT_ME_s|PlayerOne"));
    assert(s_nVt88 == 1 && s_uVtArgs[3] == 0x99);
    assert(s_nDB2B0 == 1 && s_nDB3A0 == 1);
    assert(s_nVt8 == 1 && s_uVtArgs[0] == 1);
    assert(s_nDB330 == 1);
    // ---- S11: +0x120 the kick fails ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    s_i67D0[0] = 1000; s_cE590 = 0; s_cAEB = 0;
    assert(pL->Slot120(1, 2) == 0);
    assert(s_nVt88 == 0 && s_nDB2B0 == 0);
    // ---- S12: +0x120 different leagues ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    // leagues 5 vs 6 -> & ~0xff
    assert(pL->Slot120(1, 2) == 0);
    // ---- S13: +0x120 the rank gate ----
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    // 900: not 1000, not >0x397 -> gate closed
    s_i67D0[0] = 900;
    assert(pL->Slot120(1, 2) == 0);
    assert(s_nE590 == 0);   // never reached league
    // >0x397 and target < 0x2b3 -> open
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    g_fn785EA0 = [](void* p) -> uint64_t {
        (void)p; return 5; };
    s_i67D0[0] = 0x398; s_i67D0[1] = 100;
    s_cE590 = 1;
    assert(pL->Slot120(1, 2) == 0);
    assert(s_nE590 == 1 && s_nVt18 == 1);
    puts("SYNDICATE_D110_OK: wave 15");
    return 0;
}

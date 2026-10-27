// D97 — CSyndicateLogic wave 7 (+0x210..+0x258) —
// the delegate family + the invite flow.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x68];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static void* apBoxVt[128];
static void* apBox[1] = {apBoxVt};

static void* apSub[16];
static int s_nLog, s_nD3, s_nF4E0, s_nDelay, s_nAd50,
    s_nB19C0, s_nSub10, s_nVt370, s_nVt1f8b;
static char s_cVt1f8;   // the no-arg box vt+0x1f8 result
static int32_t s_nVt1f8Arg;  // the (box,u) variant
static uint32_t s_uLast[8]; static int s_nu;
static uint32_t s_uA, s_uB, s_uC;
static const void* s_pv[4]; static int s_npv;
static int32_t s_na, s_nb; static int16_t s_ns[6];
static char s_cInvite, s_cMoneyLow, s_cFull,
    s_cVt78, s_cB8470;
static char s_acBcast[128], s_acTip[64];
static int s_nTip, s_nBcast;
static uint32_t s_uTipUser, s_uBcastId;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(apBoxVt, 0, sizeof(apBoxVt));
    memset(apSub, 0, sizeof(apSub));
    *(void**)(abLogic + 8) = apBox;
    for (int k = 0; k < 12; k++) apSub[k] = (void*)(0x100 + k*0x10);
    *(void**)(abLogic + 0x28) = apSub[2];
    *(void**)(abLogic + 0x30) = apSub[3];
    *(void**)(abLogic + 0x38) = apSub[4];
    *(void**)(abLogic + 0x48) = apSub[5];
    ((void**)abLogic)[9] = apSub[9];
    ((void**)abLogic)[10] = apSub[10];
    ((void**)abLogic)[2] = (void*)0x22;
    s_nLog = s_nD3 = s_nF4E0 = s_nDelay = s_nAd50 = 0;
    s_nB19C0 = s_nSub10 = s_nVt370 = s_nVt1f8b = 0;
    s_cVt1f8 = 0; s_nVt1f8Arg = 0; s_nu = s_npv = 0;
    s_uA = s_uB = s_uC = 0;
    s_cInvite = s_cMoneyLow = s_cFull = 0;
    s_cVt78 = 0; s_cB8470 = 0; s_nTip = s_nBcast = 0;
    s_acBcast[0] = s_acTip[0] = 0;
    // the seams
    g_fnT1LogError = [](const char*) { s_nLog++; };
    g_fnSink3Get = []() -> void* { return (void*)0x33; };
    g_fnSink3OpD = [](void* p) { s_pv[s_npv++ % 4] = p; };
    g_fnSub38Cdc0 = [](void* s, const void* p,
                       const void* q, int32_t a,
                       int32_t b) {
        s_pv[s_npv++ % 4] = s; s_na = a; s_nb = b;
        s_pv[s_npv++ % 4] = p; s_pv[s_npv++ % 4] = q; };
    g_fnSub28Cd0 = [](void* s, uint32_t a, uint32_t b) {
        s_pv[s_npv++ % 4] = s; s_uA = a; s_uB = b; };
    g_fnSub28F980 = [](void* s, int32_t a, int32_t b)
        -> uint64_t {
        s_pv[s_npv++ % 4] = s; s_na = a; s_nb = b;
        return 0x77; };
    g_fnB4B0 = [](void* s, int32_t n, const void* a,
                  const void* b) {
        s_pv[s_npv++ % 4] = s; s_na = n;
        s_pv[s_npv++ % 4] = a; s_pv[s_npv++ % 4] = b; };
    g_fnSub48D4670 = [](void* s, uint32_t a,
                        uint32_t b, const char* str,
                        uint32_t c, int16_t a1, int16_t a2,
                        int16_t a3, int16_t a4,
                        int16_t a5, int16_t a6) {
        s_pv[s_npv++ % 4] = s; s_uA = a; s_uB = b;
        s_pv[s_npv++ % 4] = (void*)str; s_uC = c;
        s_ns[0]=a1; s_ns[1]=a2; s_ns[2]=a3;
        s_ns[3]=a4; s_ns[4]=a5; s_ns[5]=a6; };
    g_fnSub48D3100 = [](void* s, int32_t a,
                        uint64_t b) {
        s_pv[s_npv++ % 4] = s; s_na = a;
        s_uLast[s_nu++ % 8] = (uint32_t)b; };
    g_fnLgFind = [](void*, uint32_t u) -> int64_t {
        return u == 0x60 ? 0x31 : 0; };
    g_fnLgInviteOk = [](void* l, uint32_t u,
                        uint64_t a, uint64_t b) -> char {
        s_pv[s_npv++ % 4] = l; s_uA = u;
        s_uB = (uint32_t)a; s_uC = (uint32_t)b;
        return s_cInvite; };
    g_fnSub9D3530 = [](void* s, uint32_t u,
                      uint32_t lg) -> char {
        s_pv[s_npv++ % 4] = s; s_uA = u; s_uB = lg;
        return 1; };
    g_fnLgMoneyLow = [](void*) -> char {
        return s_cMoneyLow; };
    g_fnLgMemberFull = [](void*) -> char {
        return s_cFull; };
    g_fnLgLeaderRank = [](void*) -> uint64_t {
        return 0xabc; };
    g_fnLogicVt510 = [](void* p, uint32_t u)
        -> uint32_t {
        s_pv[s_npv++ % 4] = p; s_uLast[s_nu++ % 8] = u;
        return 0xabc; };
    g_fnSub10Call = [](void* s, uint32_t a,
                       uint32_t b) {
        s_pv[s_npv++ % 4] = s; s_uA = a; s_uB = b;
        s_nSub10++; };
    g_fnB19C0 = [](void* p, uint32_t u, char c,
                   uint64_t b) {
        s_nB19C0++; s_uA = u; s_uB = (uint32_t)b; };
    g_fnB8470 = [](void* p, void* l, uint32_t u,
                   int32_t a, int32_t b, char c) -> char {
        s_uA = u; s_na = a; s_nb = b;
        return s_cB8470; };
    g_fnLgRefresh = [](void*) -> void* { return 0; };
    g_fnLgF4E0 = [](void*) { s_nF4E0++; };
    g_fnDelayMs = [](uint32_t n) { s_nDelay++;
        s_uLast[s_nu++ % 8] = n; };
    g_fnLgGetId = [](void* p) -> uint64_t {
        return 0x60; };
    g_fnLgAd50 = [](void* l, uint32_t u) {
        s_nAd50++; s_uA = u; };
    g_fnSub9D3680 = [](void* s, int32_t a,
                       int32_t b) {
        s_pv[s_npv++ % 4] = s; s_na = a; s_nb = b;
        s_nD3++; };
    g_fnLogicVt78 = [](void*) -> char {
        return s_cVt78; };
    g_fnBoxVt1d8 = [](void*, uint32_t) -> uint64_t {
        return 0x99; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                             const char* k) -> void* {
        strncpy(s_acTip, k, 63);
        return (void*)s_acTip; };
    apBoxVt[0x18 / 8] = (void*)+[](void*, uint32_t u,
                                   const void* pv)
        -> uint64_t {
        s_nTip++; s_uTipUser = u;
        strncpy(s_acBcast, (const char*)pv, 127);
        return 0; };
    apBoxVt[0x88 / 8] = (void*)+[](void*, uint32_t u,
                                   const char* psz,
                                   uint64_t) -> uint64_t {
        s_nBcast++; s_uBcastId = u;
        strncpy(s_acBcast, psz, 127);
        return 0; };
    // the no-arg box vt+0x1f8 default: 0 (the flow runs)
    apBoxVt[0x1f8 / 8] = (void*)+[]() -> uint64_t {
        return 0; };
    // the no-arg box vt+0x370
    apBoxVt[0x370 / 8] = (void*)+[]() -> uint64_t {
        s_nVt370++; return 0; };
}

int main() {
    // ---- S1: the +0x60 flag gate ----
    Reset();
    pL->Slot210Flag60Sink3();
    assert(s_npv == 0);
    abLogic[0x60] = 1;
    pL->Slot210Flag60Sink3();
    assert(s_pv[0] == (void*)0x33);
    // ---- S2: the sub delegates ----
    Reset();
    pL->Slot220Sub38Cdc0(1, 2, (void*)0xa, (void*)0xb);
    assert(s_pv[0] == apSub[4] && s_na == 1 && s_nb == 2
           && s_pv[1] == (void*)0xa
           && s_pv[2] == (void*)0xb);
    pL->Slot228Sub28Cd0(7, 8);
    assert(s_pv[3] == apSub[2] && s_uA == 7 && s_uB == 8);
    assert(pL->Slot230Sub28F980(3, 4) == 0x77);
    assert(s_pv[0] == apSub[2] && s_na == 3 && s_nb == 4);
    assert(pL->Slot230Sub28F980(3, 4) == 0x77);
    assert(s_pv[1] == apSub[2]);
    // the null-gates
    *(void**)(abLogic + 0x28) = 0;
    assert(pL->Slot230Sub28F980(1, 2) == 0);
    pL->Slot228Sub28Cd0(1, 2);
    pL->Slot238Sub30B4b0(5, (void*)0xc, (void*)0xd);
    assert(s_pv[2] == apSub[3]);
    // ---- S3: the +0x48 guards ----
    Reset();
    *(void**)(abLogic + 0x48) = 0;
    pL->Slot240Sub48D4670(1, 2, "s", 3, 1, 2, 3, 4, 5, 6);
    assert(s_nLog == 1);
    pL->Slot248Sub48D3100(1, 2);
    assert(s_nLog == 2);
    *(void**)(abLogic + 0x48) = apSub[5];
    pL->Slot240Sub48D4670(1, 2, "s", 3, 1, 2, 3, 4, 5, 6);
    assert(s_pv[0] == apSub[5] && s_uA == 1 && s_uB == 2
           && s_ns[0] == 1 && s_ns[5] == 6);
    pL->Slot248Sub48D3100(9, 0x1234);
    assert(s_pv[0] == apSub[5] && s_na == 9);
    // ---- S4: the invite flow — the gates ----
    Reset();
    // gate 3: lg id == 0
    pL->Slot250InviteFlow(5, 0, 0);
    assert(s_nLog == 1);
    // gate 1: pp[9] == 0
    ((void**)abLogic)[9] = 0;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_nLog == 2);
    // gate 2: pp[2] == 0
    ((void**)abLogic)[9] = apSub[9];
    ((void**)abLogic)[2] = 0;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_nLog == 3);
    ((void**)abLogic)[2] = (void*)0x22;
    // bind box vt+0x1f8 BEFORE the calls (nonzero ->
    // early out)
    apBoxVt[0x1f8 / 8] = (void*)+[]() -> uint64_t {
        return (uint64_t)(uint8_t)1; };
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_npv == 0);
    apBoxVt[0x1f8 / 8] = (void*)+[]() -> uint64_t {
        return 0; };   // iVar4 == 0 -> the flow runs
    s_cInvite = 0;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_npv >= 1);  // the invite check ran
    // money too low
    Reset(); s_cInvite = 1; s_cMoneyLow = 1;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_nTip == 1);
    assert(strstr(s_acBcast, "TOO_LOWER_SYN_MONEY") != 0);
    // full
    Reset(); s_cInvite = 1; s_cFull = 1;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(strstr(s_acBcast, "STR_SYN_FULL") != 0);
    // the leader path: vt+0x510 rank matches
    Reset(); s_cInvite = 1;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_nSub10 == 1 && s_nB19C0 == 0);
    // non-leader -> b19c0
    Reset(); s_cInvite = 1;
    g_fnLogicVt510 = [](void*, uint32_t) -> uint32_t {
        return 0x999; };
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_nSub10 == 0 && s_nB19C0 == 1);
    // the send: b8470 -> the STR_SYN_INVITE_JOIN bcast
    Reset(); s_cInvite = 1; s_cB8470 = 1;
    pL->Slot250InviteFlow(5, 0x60, 0);
    assert(s_nVt370 == 1);  // the box vt+0x370 fired
    assert(s_nF4E0 == 1 && s_nDelay == 1);
    assert(s_nBcast == 1 && s_uBcastId == 0x60);
    assert(strstr(s_acBcast, "STR_SYN_INVITE_JOIN") != 0);
    assert(s_nAd50 == 1);
    // ---- S5: Slot258 ----
    Reset();
    pL->Slot258Sub9D3680(0);
    assert(s_nLog == 1);
    pL->Slot258Sub9D3680(7);
    assert(s_nLog == 1);   // vt78 = 0 -> stop (no log)
    s_cVt78 = 1;
    apBoxVt[0x1f8 / 8] = (void*)+[](void*, int32_t n)
        -> int32_t { return n == 7 ? 3 : 0; };
    pL->Slot258Sub9D3680(7);
    assert(s_nD3 == 1 && s_pv[0] == apSub[9]
           && s_na == 7 && s_nb == 3);
    puts("SYNDICATE_D97_OK: the delegate wave");
    return 0;
}

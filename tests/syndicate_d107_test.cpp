// D107 — CSyndicateLogic wave 12: slots +0x0e8..+0x130
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nCB000, s_nF4E0, s_n73A0, s_n8800, s_nF400,
    s_nF410, s_nACF0, s_nLgFind, s_nLog, s_n9E6D0;
static int64_t s_iF4E0Ret;
static int32_t s_i8800Ret;
static uint32_t s_uF400Ret;
static uint64_t s_uF410Ret;
static uint32_t s_uArgs[6];
static void* s_pvVec[3];

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    memset(s_pvVec, 0, sizeof(s_pvVec));
    s_nCB000 = s_nF4E0 = s_n73A0 = s_n8800 = 0;
    s_nF400 = s_nF410 = s_nACF0 = 0;
    s_nLgFind = s_nLog = s_n9E6D0 = 0;
    s_iF4E0Ret = 0x81; s_i8800Ret = 0x82;
    s_uF400Ret = 0x83; s_uF410Ret = 0x84;
    memset(s_uArgs, 0, sizeof(s_uArgs));
    ((void**)abLogic)[2] = (void*)0x22;
    ((void**)abLogic)[10] = abSub;
    g_fn7CB000 = [](void* p, uint32_t u) {
        s_nCB000++; assert(p == (void*)0x22);
        assert(u == 5); };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        s_nLgFind++; assert(p == (void*)0x22);
        (void)u; return 0x55; };
    g_fn78F4E0 = [](void* p) -> int64_t {
        s_nF4E0++; assert(p == (void*)0x55);
        return s_iF4E0Ret; };
    g_fn7873A0 = [](int32_t n) {
        s_n73A0++; assert(n == 9); };
    g_fn798800 = [](void* p) -> int32_t {
        s_n8800++; assert(p == (void*)0x55);
        return s_i8800Ret; };
    g_fn78F400 = [](void* p) -> uint32_t {
        s_nF400++; assert(p == (void*)0x55);
        return s_uF400Ret; };
    g_fn78F410 = [](void* p) -> uint64_t {
        s_nF410++; assert(p == (void*)0x55);
        return s_uF410Ret; };
    g_fn76ACF0 = [](void* p, int32_t a, uint32_t b,
                     int32_t c, uint16_t d,
                     uint16_t e) {
        s_nACF0++; assert(p == abSub);
        s_uArgs[0] = (uint32_t)a;
        s_uArgs[1] = b; s_uArgs[2] = (uint32_t)c;
        s_uArgs[3] = d; s_uArgs[4] = e; };
    g_fn79E6D0 = [](void* p, void* v) -> char {
        s_n9E6D0++; assert(p == (void*)0x55);
        assert(v == s_pvVec);
        return 1; };
    g_fn78F2D0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x85; };
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
}

int main() {
    // ---- S1: the direct pass-throughs ----
    Reset();
    pL->Slot0E8(5);
    assert(s_nCB000 == 1);
    pL->Slot0F8(9);
    assert(s_n73A0 == 1);
    pL->Slot130(1, 2, 3, 4, 5);
    assert(s_nACF0 == 1);
    assert(s_uArgs[0] == 1 && s_uArgs[1] == 2);
    assert(s_uArgs[2] == 3 && s_uArgs[3] == 4);
    assert(s_uArgs[4] == 5);
    // ---- S2: the LgFind wrappers ----
    Reset();
    assert(pL->Slot0F0(0) == 0);   // the null gate
    assert(s_nLgFind == 0);
    assert(pL->Slot0F0(1) == 0x81);
    assert(pL->Slot100(1) == true);
    assert(s_nLgFind == 2);
    assert(pL->Slot128(0) == 0);
    assert(pL->Slot128(1) == 0x85);
    // ---- S3: the log-on-miss wrappers ----
    Reset();
    assert(pL->Slot108(1, s_pvVec) == 1);
    assert(s_n9E6D0 == 1 && s_nLog == 0);
    assert(pL->Slot110(1) == 0x82);
    assert(s_nLog == 0);
    // the miss path: LgFind returns 0
    Reset();
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        (void)p; (void)u; return 0; };
    assert(pL->Slot108(1, s_pvVec) == 0);
    assert(s_nLog == 1 && s_n9E6D0 == 0);
    assert(pL->Slot110(1) == 0);
    assert(s_nLog == 2 && s_n8800 == 0);
    // ---- S4: the null-mgr guards (+0x118/+0x120) ----
    Reset();
    assert(pL->Slot118(1) == 0x83);
    assert(pL->Slot120(1) == 0x84);
    assert(s_nLog == 0);
    // mgr null -> log, no LgFind
    Reset();
    ((void**)abLogic)[2] = 0;
    assert(pL->Slot118(1) == 0);
    assert(s_nLog == 1 && s_nLgFind == 0);
    assert(pL->Slot120(1) == 0);
    assert(s_nLog == 2);
    // LgFind miss inside -> 0, no log
    Reset();
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        (void)p; (void)u; return 0; };
    assert(pL->Slot118(1) == 0);
    assert(s_nLog == 0 && s_nF400 == 0);
    assert(pL->Slot120(1) == 0);
    assert(s_nF410 == 0);
    puts("SYNDICATE_D107_OK: wave 12");
    return 0;
}

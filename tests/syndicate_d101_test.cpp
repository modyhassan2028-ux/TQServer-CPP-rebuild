// D101 — CSyndicateLogic wave 10: slots +0x2d8..+0x330
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nFE50, s_nACE0, s_n3DD0, s_n4000, s_n4230,
    s_n4300, s_nEFC0, s_nF190, s_n45920, s_n45C0,
    s_nEA40, s_nEA30, s_nF470, s_nLog, s_nVt480,
    s_nVt478, s_nVtA0, s_nVt4e8, s_nLgFind;
static int32_t s_aiFE50[2];
static int32_t s_aiArgs[4];
static const char* s_pcArg;
static uint16_t s_uVt480Arg;
static uint32_t s_uVt478Args[2];
static uint32_t s_uVt4e8Args[3];
static char s_cEA40Ret;
static uint64_t s_u90390Ret;
static void* s_pv7630D0;
static uint64_t s_u745520Ret, s_uLgFindRet;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nFE50 = s_nACE0 = s_n3DD0 = s_n4000 = 0;
    s_n4230 = s_n4300 = s_nEFC0 = s_nF190 = 0;
    s_n45920 = s_n45C0 = s_nEA40 = s_nEA30 = 0;
    s_nF470 = s_nLog = s_nVt480 = 0;
    s_nVt478 = s_nVtA0 = s_nVt4e8 = s_nLgFind = 0;
    s_cEA40Ret = 0; s_u90390Ret = 0;
    s_pv7630D0 = (void*)0x77;
    s_u745520Ret = 0xAB; s_uLgFindRet = 0x55;
    static void* apBox[1]; static void* apBoxVt[160];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x480 / 8] = (void*)+[](void*, void* b,
        uint16_t c) -> uint64_t {
        s_nVt480++; s_uVt480Arg = c;
        assert(b != 0); return 0; };
    apBoxVt[0x478 / 8] = (void*)+[](void*,
        uint32_t a, int32_t b) -> uint64_t {
        s_nVt478++; s_uVt478Args[0] = a;
        s_uVt478Args[1] = b; return 0; };
    apBoxVt[0xa0 / 8] = (void*)+[](void*)
        -> uint64_t { s_nVtA0++; return 0; };
    static void* apLogicVt[0x500/8];
    memset(apLogicVt, 0, sizeof(apLogicVt));
    apLogicVt[0x4e8 / 8] = (void*)+[](void*, uint32_t a,
        void* b, int32_t c) -> uint64_t {
        s_nVt4e8++; s_uVt4e8Args[0] = a;
        s_uVt4e8Args[1] = (uint32_t)(uintptr_t)b;
        s_uVt4e8Args[2] = c; return 0; };
    *(void***)abLogic = apLogicVt;
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;
    ((void**)abLogic)[2] = (void*)0x22;
    g_fn76FE50 = [](void* p, int32_t* a) {
        s_nFE50++; assert(p == abSub);
        s_aiFE50[0] = a[0]; s_aiFE50[1] = a[1]; };
    g_fn76ACE0 = [](void* p) {
        s_nACE0++; assert(p == abSub); };
    g_fn763DD0 = [](void* p, int32_t a, int32_t b,
                    const char* c) {
        s_n3DD0++; assert(p == abSub);
        s_aiArgs[0] = a; s_aiArgs[1] = b;
        s_pcArg = c; };
    g_fn764000 = [](void* p, int32_t a, int32_t b,
                    const char* c) {
        s_n4000++; assert(p == abSub);
        s_aiArgs[0] = a; s_aiArgs[1] = b;
        s_pcArg = c; };
    g_fn764230 = [](void* p, int32_t a, int32_t b,
                    const char* c) {
        s_n4230++; assert(p == abSub);
        s_aiArgs[0] = a; s_aiArgs[1] = b;
        s_pcArg = c; };
    g_fn764300 = [](void* p, uint32_t a, int32_t b) {
        s_n4300++; assert(p == abSub);
        s_aiArgs[0] = (int32_t)a;
        s_aiArgs[1] = b; };
    g_fn76EFC0 = [](void* p, int32_t a, int32_t b,
                    int32_t c) {
        s_nEFC0++; assert(p == abSub);
        s_aiArgs[0] = a; s_aiArgs[1] = b;
        s_aiArgs[2] = c; };
    g_fn76F190 = [](void* p) {
        s_nF190++; assert(p == abSub); };
    g_fn745920 = [](void* p, void* b) {
        s_n45920++; assert(p == (void*)0x77);
        ((uint32_t*)b)[0] = 0xDEAD; };
    g_fn7645C0 = [](void* p, uint32_t a) {
        s_n45C0++; assert(p == abSub);
        s_aiArgs[0] = (int32_t)a; };
    g_fn74EA40 = [](void* p) -> char {
        assert(p == abSub); return s_cEA40Ret; };
    g_fn74EA30 = [](void* p, int32_t a) {
        s_nEA30++; assert(p == abSub);
        assert(a == 1); };
    g_fn790390 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55);
        return s_u90390Ret; };
    g_fn78F470 = [](void* p) -> void* {
        s_nF470++; assert(p == (void*)0x55);
        return (void*)0x66; };
    g_fn745520 = [](void* p) -> uint64_t {
        assert(p == (void*)0x77); return s_u745520Ret; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        s_nLgFind++; assert(p == (void*)0x22);
        (void)u; return (int64_t)s_uLgFindRet; };
    g_fn7630D0 = [](void* p, uint32_t u) -> void* {
        assert(p == abSub); (void)u;
        return s_pv7630D0; };
    g_fn74E3F0 = [](void* p) -> uint32_t {
        assert(p == abSub); return 0; };
    g_fn78F2D0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x1234; };
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
}

int main() {
    // ---- S1: the pass-through family ----
    Reset();
    int32_t ai[2] = {11, 22};
    pL->Slot480(ai);
    assert(s_nFE50 == 1 && s_aiFE50[0] == 11
           && s_aiFE50[1] == 22);
    pL->Slot488();
    assert(s_nACE0 == 1);
    pL->Slot490(1, 2, "x");
    assert(s_n3DD0 == 1 && s_aiArgs[0] == 1
           && s_aiArgs[1] == 2 && s_pcArg[0] == 'x');
    pL->Slot498(3, 4, "y");
    assert(s_n4000 == 1 && s_aiArgs[0] == 3);
    pL->Slot4A0(5, 6, "z");
    assert(s_n4230 == 1 && s_aiArgs[0] == 5);
    pL->Slot4A8(7, 8);
    assert(s_n4300 == 1 && s_aiArgs[0] == 7
           && s_aiArgs[1] == 8);
    pL->Slot4B0(1, 2, 3);
    assert(s_nEFC0 == 1 && s_aiArgs[2] == 3);
    pL->Slot4B8();
    assert(s_nF190 == 1);
    pL->Slot4C8(0x77);
    assert(s_n45C0 == 1 && s_aiArgs[0] == 0x77);
    pL->Slot4D8();
    assert(s_nVtA0 == 1);
    // ---- S2: +0x318 the lookup pair ----
    Reset();
    pL->Slot4C0(9, 0x44);   // 7630d0 -> 0x77
    assert(s_n45920 == 1 && s_nVt480 == 1);
    assert(s_uVt480Arg == 9);
    s_pv7630D0 = 0;
    pL->Slot4C0(9, 0x44);
    assert(s_nLog == 1 && s_nVt480 == 1);
    // ---- S3: +0x328 the cur==0 gate ----
    Reset();
    // 74e3f0=0, ea40=0 -> proceed; 90390=0 ->
    // the vt+0x4e8 path
    pL->Slot4D0(0x31);
    assert(s_nLgFind == 1 && s_nF470 == 1);
    assert(s_nVt4e8 == 1);
    assert(s_uVt4e8Args[0] == 0x1234);
    assert(s_uVt4e8Args[1] == 0x66);
    assert(s_uVt4e8Args[2] == 1);
    assert(s_nLog == 0);
    // 90390 != 0 -> the box vt+0x478 path
    Reset();
    s_u90390Ret = 0x99;
    pL->Slot4D0(0x31);
    assert(s_nVt4e8 == 0 && s_nVt478 == 1);
    assert(s_uVt478Args[0] == 0xAB);
    assert(s_uVt478Args[1] == 6);
    assert(s_nEA30 == 1);
    // the inner lookup fails -> literal log
    Reset();
    s_u90390Ret = 0x99; s_pv7630D0 = 0;
    pL->Slot4D0(0x31);
    assert(s_nLog == 1 && s_nVt478 == 0);
    // LgFind fails -> literal log, no other calls
    Reset();
    s_uLgFindRet = 0;
    pL->Slot4D0(0x31);
    assert(s_nLog == 1 && s_nF470 == 0);
    // the gate blocks: ea40 != 0
    Reset();
    s_cEA40Ret = 1;
    pL->Slot4D0(0x31);
    assert(s_nLgFind == 0 && s_nLog == 0);
    puts("SYNDICATE_D101_OK: wave 10");
    return 0;
}

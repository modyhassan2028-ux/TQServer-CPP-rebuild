// D106 — CSyndicateLogic wave 11: slots +0x368..+0x3b0
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nEE00, s_nEF00, s_nEF20, s_nED30, s_nEBE0,
    s_nEC50, s_nECC0, s_n8020, s_n24D0, s_nC8E0,
    s_nVt518, s_nVt4a8;
static uint32_t s_uEE00Ret, s_uEF00Ret, s_uECC0Ret;
static uint64_t s_uEF20Ret;
static uint32_t s_uArgs[4];
static int32_t s_iVt4a8Ret, s_iVt518Ret;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nEE00 = s_nEF00 = s_nEF20 = s_nED30 = 0;
    s_nEBE0 = s_nEC50 = s_nECC0 = s_n8020 = 0;
    s_n24D0 = s_nC8E0 = s_nVt518 = s_nVt4a8 = 0;
    s_uEE00Ret = 0x61; s_uEF00Ret = 0x62;
    s_uEF20Ret = 0x63; s_uECC0Ret = 0x64;
    s_iVt4a8Ret = 5; s_iVt518Ret = 0x65;
    memset(s_uArgs, 0, sizeof(s_uArgs));
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x4a8/8] = (void*)+[](void*, void*)
        -> int32_t { s_nVt4a8++;
        return s_iVt4a8Ret; };
    static void* apLogicVt[0x520/8];
    memset(apLogicVt, 0, sizeof(apLogicVt));
    apLogicVt[0x518/8] = (void*)+[](void*, uint32_t a)
        -> uint32_t {
        s_nVt518++; s_uArgs[0] = a;
        return s_iVt518Ret; };
    *(void***)abLogic = apLogicVt;
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;
    ((void**)abLogic)[3] = (void*)0x33;
    ((void**)abLogic)[2] = (void*)0x22;
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        s_nC8E0++; assert(p == (void*)0x33);
        return u == 0x11 ? (void*)0xAA : 0; };
    g_fn785EA0 = [](void* p) -> uint64_t {
        assert(p == (void*)0xAA); return 0x51; };
    g_fn75EE00 = [](void* p, uint32_t u) -> uint32_t {
        s_nEE00++; assert(p == abSub);
        assert(u == 0x42); return s_uEE00Ret; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22); (void)u;
        return 0x55; };
    g_fn790390 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x71; };
    g_fn74EF00 = [](void* p, uint32_t u) -> uint64_t {
        s_nEF00++; assert(p == abSub);
        s_uArgs[0] = u; return s_uEF00Ret; };
    g_fn74EF20 = [](void* p, int32_t n) -> uint64_t {
        s_nEF20++; assert(p == abSub);
        s_uArgs[0] = (uint32_t)n;
        return s_uEF20Ret; };
    g_fn74ED30 = [](void* p, uint32_t u) {
        s_nED30++; assert(p == abSub);
        assert(u == 7); };
    g_fn74EBE0 = [](void* p, uint32_t u, int32_t i) {
        s_nEBE0++; assert(p == abSub);
        assert(u == 7 && i == 5); };
    g_fn74EC50 = [](void* p, uint32_t u, int32_t i) {
        s_nEC50++; assert(p == abSub);
        assert(u == 7 && i == 5); };
    g_fn74ECC0 = [](void* p, uint32_t u, int32_t i)
        -> uint64_t {
        s_nECC0++; assert(p == abSub);
        assert(u == 7 && i == 5);
        return s_uECC0Ret; };
    g_fn768020 = [](void* p, uint16_t u) {
        s_n8020++; assert(p == abSub);
        assert(u == 9); };
    g_fn7524D0 = [](void* p, int32_t n, uint32_t u) {
        s_n24D0++; assert(p == abSub);
        assert(n == 3 && u == 4); };
}

int main() {
    // ---- S1: +0x368 the id triage ----
    Reset();
    assert(pL->Slot510(0) == 0);   // the null gate
    assert(pL->Slot510(0x11) == 0x65);  // player found
    assert(s_nVt518 == 1 && s_uArgs[0] == 0x51);
    assert(pL->Slot510(0x42) == 0x61);  // player miss
    assert(s_nEE00 == 1 && s_nC8E0 == 2);
    // ---- S2: +0x370 ----
    Reset();
    assert(pL->Slot518(1) == 0x71);
    assert(pL->Slot518(0) == 0x71);   // lg always found
    // ---- S3: +0x378/+0x380 null gates ----
    Reset();
    assert(pL->Slot520(0) == 0);
    assert(pL->Slot520(2) == 0x62);
    assert(s_uArgs[0] == 2);
    assert(pL->Slot380(0) == 0);
    assert(pL->Slot380(-3) == 0x63);
    assert(s_uArgs[0] == (uint32_t)-3);
    // ---- S4: +0x388 ----
    Reset();
    pL->Slot388(7);
    assert(s_nED30 == 1);
    // ---- S5: +0x390/+0x398 with the vt+0x4a8 gate ----
    Reset();
    pL->Slot390(7);
    assert(s_nVt4a8 == 1 && s_nEBE0 == 1);
    pL->Slot398(7);
    assert(s_nVt4a8 == 2 && s_nEC50 == 1);
    s_iVt4a8Ret = 0;
    pL->Slot390(7); pL->Slot398(7);
    assert(s_nEBE0 == 1 && s_nEC50 == 1);  // gated
    // ---- S6: +0x3a0 the CONCAT71 pattern ----
    Reset();
    assert(pL->Slot3A0(7) == 0x64);
    s_iVt4a8Ret = 0;
    // CONCAT71((int7)(uVar1 >> 8), 1) with uVar1 = 0
    assert(pL->Slot3A0(7) == 1);
    // ---- S7: +0x3a8/+0x3b0 gates ----
    Reset();
    pL->Slot3A8(0);   // u2 == 0 -> no call
    assert(s_n8020 == 0);
    ((void**)abLogic)[10] = 0;
    pL->Slot3A8(9);   // p10 == 0 -> no call
    assert(s_n8020 == 0);
    ((void**)abLogic)[10] = abSub;
    pL->Slot3A8(9);
    assert(s_n8020 == 1);
    pL->Slot3B0(0, 4);   // n2 == 0 -> no call
    assert(s_n24D0 == 0);
    pL->Slot3B0(3, 4);
    assert(s_n24D0 == 1);
    puts("SYNDICATE_D106_OK: wave 11");
    return 0;
}

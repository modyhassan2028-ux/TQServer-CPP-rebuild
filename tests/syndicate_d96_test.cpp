// D96 — CSyndicateLogic wave 6 (+0x1d0..+0x208) —
// the sink/broadcast family.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x60];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static void* apSub[2] = {(void*)0x40, 0};
static void* apSub30[2] = {(void*)0x50, 0};

static int s_nA8940, s_nS1OpA, s_nS1OpB, s_nS1OpC,
    s_nS2OpA, s_nS3OpA, s_nS3OpB, s_nS3OpC, s_nB4B0,
    s_nSink3Get;
static uint32_t s_uA, s_uB[3], s_uA8940Ret;
static int32_t s_nLast;
static void* s_pLast[8]; static int s_np;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    *(void**)(abLogic + 0x20) = apSub[0];
    *(void**)(abLogic + 0x30) = apSub30[0];
    s_nA8940 = s_nS1OpA = s_nS1OpB = s_nS1OpC = 0;
    s_nS2OpA = s_nS3OpA = s_nS3OpB = s_nS3OpC = 0;
    s_nB4B0 = s_nSink3Get = s_np = 0;
    s_uA = 0; s_nLast = 0; s_uA8940Ret = 7;
    memset(s_pLast, 0, sizeof(s_pLast));
    g_fnA8940 = [](void*, uint32_t u) -> uint32_t {
        s_nA8940++; s_uA = u; return s_uA8940Ret; };
    g_fnSink1Get = []() -> void* { return (void*)0x11; };
    g_fnSink1OpA = [](void* p, uint32_t u) {
        s_nS1OpA++; s_pLast[s_np++ % 8] = p; s_uA = u; };
    g_fnSink1OpB = [](void* p, uint32_t a, uint32_t b,
                      uint32_t c) {
        s_nS1OpB++; s_pLast[s_np++ % 8] = p;
        s_uB[0] = a; s_uB[1] = b; s_uB[2] = c; };
    g_fnSink1OpC = [](void* p) {
        s_nS1OpC++; s_pLast[s_np++ % 8] = p; };
    g_fnSink2Get = []() -> void* { return (void*)0x22; };
    g_fnSink2OpA = [](void* p, int32_t n) {
        s_nS2OpA++; s_pLast[s_np++ % 8] = p;
        s_nLast = n; };
    g_fnSink3Get = []() -> void* {
        s_nSink3Get++; return (void*)0x33; };
    g_fnSink3OpA = [](void* p, void* q) {
        s_nS3OpA++; s_pLast[s_np++ % 8] = p;
        s_pLast[s_np++ % 8] = q; };
    g_fnSink3OpB = [](void* p, int32_t n) {
        s_nS3OpB++; s_pLast[s_np++ % 8] = p;
        s_nLast = n; };
    g_fnSink3OpC = [](void* p) {
        s_nS3OpC++; s_pLast[s_np++ % 8] = p; };
    g_fnB4B0 = [](void* p, int32_t n, const void* a,
                  const void* b) {
        s_nB4B0++; s_pLast[s_np++ % 8] = p;
        s_nLast = n; s_uB[0] = (uint32_t)(uint64_t)a;
        s_uB[1] = (uint32_t)(uint64_t)b; };
}

int main() {
    // ---- S1: the +0x20 delegate ----
    Reset();
    assert(pL->Slot1d0Sub20Delegate(5) == 7 &&
           s_nA8940 == 1 && s_uA == 5);
    *(void**)(abLogic + 0x20) = 0;
    assert(pL->Slot1d0Sub20Delegate(5) == 0 &&
           s_nA8940 == 1);
    // ---- S2: the sink-1 family ----
    Reset();
    pL->Slot1d8Sink1OpA(9);
    assert(s_nS1OpA == 1 && s_pLast[0] == (void*)0x11 &&
           s_uA == 9);
    pL->Slot1e0Sink1OpB(1, 2, 3);
    assert(s_nS1OpB == 1 && s_uB[0] == 1 &&
           s_uB[1] == 2 && s_uB[2] == 3);
    pL->Slot1e8Sink1OpC();
    assert(s_nS1OpC == 1 &&
           s_pLast[0] == (void*)0x11);
    // ---- S3: the sink-2 ----
    Reset();
    pL->Slot1f0Sink2OpA(-4);
    assert(s_nS2OpA == 1 && s_pLast[0] == (void*)0x22 &&
           s_nLast == -4);
    // ---- S4: the 0x48 loop ----
    Reset();
    uint8_t abItems[4][0x48] = {};
    pL->Slot1f8Sink3Loop(3, &abItems[0][0]);
    assert(s_nSink3Get == 3 && s_nS3OpA == 3);
    assert(s_pLast[1] == &abItems[0][0]);
    assert(s_pLast[3] == &abItems[1][0]);
    assert(s_pLast[5] == &abItems[2][0]);
    // zero and negative counts: no calls
    pL->Slot1f8Sink3Loop(0, &abItems[0][0]);
    assert(s_nSink3Get == 3);
    // ---- S5: the b4b0 + sink-3 ----
    Reset();
    pL->Slot208B4b0ThenSink3((void*)0x61, (void*)0x62);
    assert(s_nB4B0 == 1 && s_pLast[0] == (void*)0x50 &&
           s_nLast == 3 && s_uB[0] == 0x61 &&
           s_uB[1] == 0x62);
    assert(s_nS3OpC == 1 && s_pLast[1] == (void*)0x33);
    puts("SYNDICATE_D96_OK: the sink wave");
    return 0;
}

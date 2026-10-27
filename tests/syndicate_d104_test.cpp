// D104 — CSyndicateLogic +0x358: 1417c13e0 exit-league flow
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abSub[0x40];

static int s_nD490, s_nC1180, s_nACA0, s_n9E6D0, s_nC3D0,
    s_nVt88, s_nVt710, s_n268, s_n280, s_n2a0, s_n2a8,
    s_nFreed;
static uint32_t s_uD490Args[2], s_uC1180Args[4],
    s_uACA0Args[2], s_uVt88Args[2],
    s_uVt710Args[3];
static char s_c9E6D0Ret, s_c9E6D0Null;
static const char* s_pcVt88Buf;
static int32_t s_ai268Ret[16], s_ai280Ret[16],
    s_ai2a0Ret[16];
static uint32_t s_u2a8Args[8][3]; static int s_i2a8;
static uint32_t s_auIds[16]; static int s_nIds;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abSub, 0, sizeof(abSub));
    s_nD490 = s_nC1180 = s_nACA0 = s_n9E6D0 = 0;
    s_nC3D0 = s_nVt88 = s_nVt710 = 0;
    s_n268 = s_n280 = s_n2a0 = s_n2a8 = 0;
    s_nFreed = 0; s_i2a8 = 0; s_nIds = 0;
    s_c9E6D0Ret = 1; s_c9E6D0Null = 0;
    memset(s_ai268Ret, 1, sizeof(s_ai268Ret));
    memset(s_ai280Ret, 0, sizeof(s_ai280Ret));
    for (int i = 0; i < 16; i++) s_ai2a0Ret[i] = 9;
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x88/8] = (void*)+[](void*, uint32_t a,
        const char* b, uint32_t c) -> uint64_t {
        s_nVt88++;
        assert(strstr(b, "STR_SYN_EXIT_LEAGUE") != 0);
        s_pcVt88Buf = b;
        s_uVt88Args[0] = a; s_uVt88Args[1] = c;
        return 0; };
    apBoxVt[0x268/8] = (void*)+[](void*, uint32_t id)
        -> char {
        s_n268++;
        return (char)s_ai268Ret[s_n268 - 1]; };
    apBoxVt[0x280/8] = (void*)+[](void*, uint32_t id)
        -> char {
        s_n280++; (void)id;
        return (char)s_ai280Ret[s_n280 - 1]; };
    apBoxVt[0x2a0/8] = (void*)+[](void*, uint32_t id)
        -> int32_t {
        s_n2a0++; (void)id;
        return s_ai2a0Ret[s_n2a0 - 1]; };
    apBoxVt[0x2a8/8] = (void*)+[](void*, uint32_t id,
        int32_t c) -> uint64_t {
        s_n2a8++;
        s_u2a8Args[s_i2a8][0] = id;
        s_u2a8Args[s_i2a8][1] = (uint32_t)c;
        s_i2a8++; return 0; };
    static void* apLogicVt[0x720/8];
    memset(apLogicVt, 0, sizeof(apLogicVt));
    apLogicVt[0x710/8] = (void*)+[](void*, void* a,
        uint32_t b, int32_t c) -> uint64_t {
        s_nVt710++; assert(a == (void*)0x55);
        s_uVt710Args[0] = b; s_uVt710Args[1] = c;
        return 0; };
    *(void***)abLogic = apLogicVt;
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[10] = abSub;
    ((void**)abLogic)[2] = (void*)0x22;
    g_fn7630D0 = [](void* p, uint32_t u) -> void* {
        assert(p == abSub); (void)u;
        return (void*)0x66; };
    g_fn743C80 = [](void* p) -> uint64_t {
        assert(p == (void*)0x66); return 0x71; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22); (void)u;
        return 0x55; };
    g_fn78F2D0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x22; };
    g_fn790390 = [](void* p) -> uint64_t {
        assert(p == (void*)0x55); return 0x44; };
    g_fn7903D0 = [](void* p, int32_t a) -> char {
        assert(p == (void*)0x55 && a == 0);
        return 1; };
    g_fn74D490 = [](void* p, uint32_t a) {
        s_nD490++; assert(p == (void*)0x66);
        s_uD490Args[0] = (uint32_t)(uintptr_t)p;
        s_uD490Args[1] = a;
        assert(a == 0x33); };
    g_fn743Dd0 = [](void* p) -> void* {
        s_nC3D0++; assert(p == (void*)0x66);
        return (void*)"SynName"; };
    g_fn7C1180 = [](void* p, uint32_t a, uint32_t b,
                    uint64_t c) {
        s_nC1180++; assert(p == (void*)abLogic);
        s_uC1180Args[0] = a; s_uC1180Args[1] = b;
        s_uC1180Args[2] = (uint32_t)c;
        assert(c == 5); };
    g_fn76ACA0 = [](void* p, uint32_t a) {
        s_nACA0++; assert(p == abSub);
        s_uACA0Args[0] = a; };
    g_fn79E6D0 = [](void* p, void* vec) -> char {
        s_n9E6D0++;
        assert(p == (void*)0x55);
        void** pv = (void**)vec;
        if (s_c9E6D0Null) return 0;
        uint32_t* aIds =
            (uint32_t*)malloc(4 * sizeof(uint32_t));
        aIds[0] = 1; aIds[1] = 2;
        aIds[2] = 3; aIds[3] = 4;
        pv[1] = aIds;
        pv[2] = aIds + 4;
        return 1; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*,
                            const char* k) -> void* {
        return (void*)k; };
}

int main() {
    // ---- S1: the lead gate (743c80 == u3) ----
    Reset();
    pL->Slot500(0x22, 0x71, 0x44);  // 743c80=0x71==u3
    assert(s_nD490 == 0 && s_nVt88 == 0);
    // ---- S2: lg lookup fails -> silent ----
    Reset();
    // 743c80 = 0x71 != 0x33 -> proceeds; LgFind(u3=
    // 0x33) -> 0x55 ok; 78f2d0=0x22==u2 ok;
    // 790390=0x44==u4 ok; 7903d0 ok -> full path
    pL->Slot500(0x22, 0x33, 0x44);
    assert(s_nD490 == 1);
    assert(s_nVt88 == 1);
    assert(s_uVt88Args[0] == 0x33 &&
           s_uVt88Args[1] == 0);
    assert(s_nVt710 == 1);
    assert(s_uVt710Args[0] == 0 &&
           s_uVt710Args[1] == 5);
    assert(s_nC1180 == 1);
    assert(s_uC1180Args[0] == 0x33 &&
           s_uC1180Args[1] == 0x44);
    assert(s_nACA0 == 1 && s_uACA0Args[0] == 0x22);
    // the sweep: 4 ids, all (268=1,280=0,2a0=9) ->
    // four 2a8 calls with 3
    assert(s_n9E6D0 == 1);
    assert(s_n268 == 4 && s_n280 == 4);
    assert(s_n2a0 == 4 && s_n2a8 == 4);
    assert(s_u2a8Args[0][1] == 3);
    // ---- S3: the condition matrix ----
    Reset();
    // id 1: 268 fails -> no 280
    s_ai268Ret[0] = 0;
    // id 2 (first 280 call): 280 != 0 -> no 2a0
    s_ai280Ret[0] = 1;
    // id 3 (first 2a0 call): 2a0 != 9 -> no 2a8
    s_ai2a0Ret[0] = 7;
    // id 4: full
    pL->Slot500(0x22, 0x33, 0x44);
    assert(s_n2a8 == 1);
    assert(s_u2a8Args[0][0] == 4);
    assert(s_n280 == 3 && s_n2a0 == 2);
    // ---- S4: 9e6d0 fails -> no sweep, no leak ----
    Reset();
    s_c9E6D0Null = 1;
    pL->Slot500(0x22, 0x33, 0x44);
    assert(s_n268 == 0 && s_n2a8 == 0);
    // ---- S5: the 7903d0 gate ----
    Reset();
    pL->Slot500(0x22, 0x33, 0x55);  // 790390 != u4
    assert(s_nD490 == 0 && s_nVt88 == 0);
    puts("SYNDICATE_D104_OK: the exit flow");
    return 0;
}

// D98 — CSyndicateLogic +0x218 — AwardPrizeVlmOrCross,
// the checked-iterator monster, with the literal prize
// tables read from .rdata.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace syndicate;

static uint8_t abLogic[0x68];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static uint8_t abOwner[0x40];
static uint8_t abInner[0x40];
static void* apProxy1[2], *apProxy2[2];
static uint8_t abNode[0x40];
static uint8_t abCont[0x40];
static uint8_t abLg[0x40];

static int s_nLog, s_nInvalid, s_nRefresh, s_nIter730,
    s_nVt350, s_nVt40;
static char s_acLog[128], s_acBcast[128], s_acStr[64];
static uint32_t s_uVt350Args[4];
static uint32_t s_uBcastSyn;
static char s_cBf80, s_cFa70;
static uint64_t s_uBf80Val, s_uFa70Val, s_uF550Ret;
static void* s_pvIter730[4]; static int s_nIter730Obj;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(abOwner, 0, sizeof(abOwner));
    memset(abInner, 0, sizeof(abInner));
    // the cross-path iterator proxy chain:
    // vecB[0] -> proxy1 -> proxy2 -> node
    memset(apProxy1, 0, sizeof(apProxy1));
    memset(apProxy2, 0, sizeof(apProxy2));
    memset(abNode, 0, sizeof(abNode));
    apProxy1[0] = apProxy2;
    apProxy2[0] = abNode;
    memset(abCont, 0, sizeof(abCont));
    *(void**)abNode = abCont;   // *node = container
    *(void**)(abCont + 0x10) = (void*)0x10000;  // size
    // the owner chain: pSyn[0] -> owner -> *owner=inner,
    // inner+0x20 = container begin (> the id array)
    *(void**)abOwner = abInner;
    *(void**)(abInner + 0x20) = (void*)0x7fff0000;
    memset(abLg, 0, sizeof(abLg));
    *(void**)(abLogic + 8) = (void*)0x1;  // box unused
    ((void**)abLogic)[2] = (void*)0x22;   // lg mgr
    s_nLog = s_nInvalid = s_nRefresh = 0;
    s_nIter730 = s_nVt350 = s_nVt40 = 0;
    s_nIter730Obj = 0;
    s_acLog[0] = s_acBcast[0] = s_acStr[0] = 0;
    s_cBf80 = 1; s_cFa70 = 1;
    s_uBf80Val = s_uFa70Val = 0; s_uF550Ret = 0;
    g_fnT1LogError = [](const char* s) {
        s_nLog++; if (s) strncpy(s_acLog, s, 127); };
    g_fnInvalidParam = []() { s_nInvalid++; };
    g_fnMyLogSave = [](const char* f, const char* fmt) {
        strncpy(s_acLog, f, 127);
        (void)fmt; };
    g_fnLgFind = [](void*, uint32_t u) -> int64_t {
        return u >= 0x60 ? (int64_t)(uint64_t)&abLg
                         : 0; };
    g_fnLgBf80 = [](void*, uint64_t v) -> char {
        s_uBf80Val = v; return s_cBf80; };
    g_fnLgF550 = [](void*) -> uint64_t {
        return s_uF550Ret; };
    g_fnLgFa70 = [](void*, uint64_t v) -> char {
        s_uFa70Val = v; return s_cFa70; };
    g_fnLgRefresh = [](void*) -> void* {
        s_nRefresh++; return 0; };
    g_fnLgGetId = [](void* p) -> uint64_t {
        return p == (void*)&abLg ? 0x60 : 0; };
    // the C50 iterator attach marks the pair as live
    // (pos = 1 — never equal to RAW's local_470 == 0)
    g_fnIterC50 = [](void* p, void*) {
        ((uint64_t*)p)[1] = 1; };
    g_fnIter730 = [](void* p) {
        s_nIter730++; if (s_nIter730Obj < 4)
            s_pvIter730[s_nIter730Obj++] = p; };
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x99; };
    g_fnStringMgrGetStr = [](void*, const char* k)
        -> void* {
        strncpy(s_acStr, k, 63);
        return (void*)s_acStr; };
    // the box: only vt+0x350 is used here
    static void* apBox[1];
    static void* apBoxVt[128]; memset(apBoxVt, 0,
                                      sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x350 / 8] = (void*)+[](
        void*, uint32_t a, uint32_t b, uint32_t c)
        -> uint64_t {
        s_nVt350++;
        s_uVt350Args[0] = a; s_uVt350Args[1] = b;
        s_uVt350Args[2] = c;
        return 0; };
    *(void**)(abLogic + 8) = apBox;
    // the logic vt+0x40 broadcast (STR_*_VLM_AWARD)
    static void* apLogicVt[128]; memset(apLogicVt, 0,
                                        sizeof(apLogicVt));
    apLogicVt[0x40 / 8] = (void*)+[](void*,
        uint32_t u, const char* psz, uint32_t)
        -> uint64_t {
        s_nVt40++; s_uBcastSyn = u;
        strncpy(s_acBcast, psz, 127); return 0; };
    *(void***)abLogic = apLogicVt;
}

// the fixture: MSVC-style vector structs
struct VecSynID { void* p[8]; uint32_t uIds[8]; };
struct VecBSelf { void* p[8]; uint32_t uB[8]; };

int main() {
    // ---- S1: the size mismatch ----
    Reset();
    VecSynID vA; memset(&vA, 0, sizeof(vA));
    VecBSelf vB; memset(&vB, 0, sizeof(vB));
    vA.p[0] = abOwner;   // the vector owner object
    vB.p[0] = apProxy1;  // the checked-iterator proxy
    vA.p[3] = vA.uIds; vA.p[4] = vA.uIds + 2; // 2 ids
    vB.p[6] = vB.uB;  vB.p[7] = vB.uB + 2;   // 2 flags
    vB.p[2] = (void*)2;  // the size field
    vA.uIds[0] = 0x60; vA.uIds[1] = 0x61;
    ((void**)abLogic)[2] = (void*)0x22;
    pL->Slot218AwardPrizeVlmOrCross(&vA, &vB, 0);
    assert(s_nLog == 0);  // sizes match (2==2)
    // make them mismatch
    vA.p[4] = vA.uIds + 3;
    pL->Slot218AwardPrizeVlmOrCross(&vA, &vB, 0);
    assert(s_nLog == 1);
    assert(strstr(s_acLog, "vecSynID.size() != "
               "vecBSelf.size()") != 0);
    vA.p[4] = vA.uIds + 2;
    // ---- S2: the vlm path — rank money ×10000 ----
    Reset();
    vA.uIds[0] = 0x60; vA.uIds[1] = 0x61;
    vB.uB[0] = 0xffffffff; vB.uB[1] = 0xffffffff;
    pL->Slot218AwardPrizeVlmOrCross(&vA, &vB, 0);
    // the last rank (2): 10000*10000; rank1 was
    // 12000*10000 (checked via the tables below)
    assert(s_uBf80Val == 10000ULL * 10000);
    assert(s_auVlmMoney[0] == 12000 &&
           s_auVlmEmoney[0] == 3000);
    assert(s_nRefresh >= 1);
    assert(strstr(s_acLog, "gmlog/synvlmaward") != 0);
    // the emoney sum: f550 + 3000 then vt+0x350
    assert(s_uFa70Val == 2000);  // rank2 emoney (rank1 was 3000)
    assert(s_nVt350 == 2 && s_uVt350Args[0] == 0x2b
           && s_uVt350Args[2] == 0x60);
    assert(s_nVt40 == 2);   // both ranks broadcast
    // the STR_VLM_AWARD went through the string mgr
    assert(strstr(s_acStr, "STR_VLM_AWARD") != 0);
    assert(s_nIter730 >= 1);
    // ---- S3: the cross path ----
    Reset();
    s_nVt40 = 0;
    // the container begin/end = the vecB storage
    *(void**)(abCont + 0x30) = vB.uB;
    *(void**)(abCont + 0x38) = vB.uB + 8;
    pL->Slot218AwardPrizeVlmOrCross(&vA, &vB, 1);
    // rank2 (the last): 80000*10000; rank1 was 100000
    assert(s_uBf80Val == 80000ULL * 10000);
    assert(strstr(s_acLog, "gmlog/syncrossvlmaward")
           != 0);
    // rank2 cross emoney = 8000 (rank1 was 10000)
    assert(s_uFa70Val == 8000);
    assert(strstr(s_acStr, "STR_CROSS_VLM_AWARD") != 0);
    assert(s_nVt40 == 2 && s_uBcastSyn == 0x61);
    // ---- S4: the 8-rank cap ----
    Reset();
    memset(&vA, 0, sizeof(vA)); memset(&vB, 0,
                                       sizeof(vB));
    vA.p[0] = abOwner;
    vB.p[0] = apProxy1;
    uint32_t auIds[12]; uint32_t auB[12];
    for (int i = 0; i < 12; i++) {
        auIds[i] = 0x60 + i; auB[i] = 0xffffffff; }
    vA.p[3] = auIds; vA.p[4] = auIds + 12;
    vB.p[6] = auB;   vB.p[7] = auB + 12;
    vB.p[2] = (void*)12;
    static uint64_t s_uSaveBf80 = 0;
    g_fnLgBf80 = [](void*, uint64_t v) -> char {
        s_uSaveBf80 = v; return 1; };
    pL->Slot218AwardPrizeVlmOrCross(&vA, &vB, 0);
    assert(s_nRefresh == 16);  // 8 awards × 2 saves
    assert(s_uSaveBf80 == 2000ULL * 10000);  // rank 8
    // ---- S5: the not-exist id ----
    Reset();
    vA.p[3] = vA.uIds; vA.p[4] = vA.uIds + 1;
    vA.p[0] = abOwner;
    vB.p[0] = apProxy1;
    vA.uIds[0] = 5;   // not found
    vB.p[6] = vB.uB;  vB.p[7] = vB.uB + 1;
    vB.p[2] = (void*)1;
    pL->Slot218AwardPrizeVlmOrCross(&vA, &vB, 0);
    assert(strstr(s_acLog, "SynID[%u] is not exist")
           != 0);
    puts("SYNDICATE_D98_OK: the iterator monster");
    return 0;
}

// ============================================================
// Training.dll — Unit T4 (D16) regression: the mgr CALC
// helpers + the mgr business bodies. Verbatim:
// 1419e1ae0 / 1419e23d0 / 1419e1b70 / 1419e4390 /
// 1419e44e0 / 1419e4730 — with the kernel-vt seams
// (TrainingKernelIface.h) and the ms-div idioms
// bit-exact. Must print TRAINING-D16-OK.
#include "../modules/training/src/TrainingMgrOps.h"
#include "../modules/training/src/TrainingKernelIface.h"
#include "../modules/training/src/TrainingMapApi.h"
#include "../modules/training/src/TrainingMsgGlue.h"
#include "../modules/training/src/TrainingModule.h"
#include "../modules/training/src/TrainingMgr.h"
#include "../modules/training/src/TrainingMap.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace training;

static int64_t g_nClock = 100000;
static int g_nLogs = 0;
static int64_t TstClock() { return g_nClock; }
static void TstLog() { ++g_nLogs; }

// a test mgr shell: the kernel at +0x18 like the real one
struct STstMgr {
    void* m_pVftable00;
    void* m_pKernel08;
    void* m_pPad10;
    SMapKernel m_kern18;
    uint8_t m_abRest[0x20];
};

int main() {
    int nAlloc = 0, nFree = 0;
    g_fnAlloc = [&](size_t n) {
        ++nAlloc; return calloc(1, n); };
    g_fnFree = [&](void* p) { ++nFree; free(p); };
    g_fnTime64 = TstClock;

    STstMgr mgr;
    memset(&mgr, 0, sizeof(mgr));
    CtorKernelCore(&mgr.m_kern18);
    mgr.m_pKernel08 = (void*)1;   // the non-null gate

    // ---------- 1. CalcExpPct (1419e1ae0) ----------
    mgr.m_pKernel08 = nullptr;
    assert(CalcExpPct(&mgr, 5) == 0x5a);
    mgr.m_pKernel08 = (void*)1;
    assert(CalcExpPct(&mgr, 0) == 0x5a);
    g_fnKvtE0 = [](int32_t) { return false; };
    assert(CalcExpPct(&mgr, 5) == 0x5a);
    g_fnKvtE0 = [](int32_t) { return true; };
    uint8_t tbl[7] = {0, 10, 20, 30, 40, 50, 60};
    memcpy(g_abTable84c8, tbl, 7);
    g_fnKvt68 = [](uint32_t) { return 2; };
    assert(CalcExpPct(&mgr, 5) == 12);  // (20*0x3c)/100
    g_fnKvt68 = [](uint32_t) { return -3; };   // clamp 0
    assert(CalcExpPct(&mgr, 5) == 0);
    g_fnKvt68 = [](uint32_t) { return 9; };    // clamp 6
    assert(CalcExpPct(&mgr, 5) == 36);  // (60*0x3c)/100

    // ---------- 2. CalcSessionTimes (1419e23d0) ------
    g_fnKvt68 = [](uint32_t) { return 2; };
    g_fnKvt48 = [](uint32_t) { return 1000; };
    g_fnKvt58 = [](uint32_t) { return 94600; };
    g_fnKvt88 = [](uint32_t) { return true; };
    uint32_t uA = 0; int32_t nB = 0;
    CalcSessionTimes(&mgr, 5, &uA, &nB);
    // s=12: uVar10=120 (120 rounded to 15); diff=5400
    // = 90 min < 120 -> cap: 90 rounded to 15 = 90
    assert(uA == 90);
    assert(nB == (int32_t)(120 - 90));
    g_fnKvt58 = [](uint32_t) { return 99640; };
    CalcSessionTimes(&mgr, 5, &uA, &nB);
    // diff=360 = 6 min < 120 -> cap: t=6-3=3,
    // sdiv8(3)=0 -> uVar9 = 0; A=0, B=120
    assert(uA == 0);
    assert(nB == (int32_t)120);
    // the vt+0x88-false path (verified against the
    // idiom itself)
    g_fnKvt58 = [](uint32_t) { return 94600; };
    g_fnKvt88 = [](uint32_t) { return false; };
    g_fnKvt80 = [](uint32_t) { return 64000; };
    CalcSessionTimes(&mgr, 5, &uA, &nB);
    {
        auto prod = (__int128)(int64_t)-0x7777777777777777
                    * (__int128)(int64_t)64000;
        int64_t l6b = (int64_t)(prod >> 64) + 64000;
        auto prod2 = (__int128)(int64_t)-0x7777777777777777
                    * (__int128)(int64_t)5400;
        int64_t l7 = (int64_t)(prod2 >> 64) + 5400;
        int32_t diff = ((int32_t)(l6b >> 5)
                        - (int32_t)(l6b >> 63))
                     - ((int32_t)(l7 >> 5)
                        - (int32_t)(l7 >> 63));
        uint16_t expA = (uint16_t)((int16_t)(
            (uint32_t)diff / 0xf) * 0xf);
        if (90 < expA) expA = 90;
        assert(uA == expA);
        assert(nB == (int32_t)(120 - uA));
    }

    // ---------- 3. CalcExpValues (1419e1b70) ---------
    g_fnKvt08 = []() { return 1; };
    g_fnKvt10 = []() { return 4; };      // the limit
    g_fnKvt18 = [](int32_t i) {
        return i == 1 ? 100 : i == 2 ? 200
            : i == 3 ? 300 : 50; };
    g_fnKvt20 = [](int32_t) { return 2; };
    g_fnKvt28 = [](uint32_t) { return 40; };
    g_fnKvt30 = [](uint32_t) { return 3; };
    g_dTable87a0 = 1.0; g_dTable87a8 = 1.0;
    g_dTable87b0 = 1.0; g_dTable8798 = 0.5;
    int32_t nLevels = 0; int64_t lExp = 0;
    int32_t nRate = 0;
    CalcExpValues(&mgr, 5, 10, &nLevels,
                  &lExp, &nRate);
    // dVar7 = 30 + (40*100)/2 = 2030; the loop runs
    // at idx 1,2,3 (limit 4): levels=3, dVar7=1430
    assert(nLevels == 3);
    assert(*(double*)((char*)&mgr + 0x10) == 30.0);
    assert(lExp == 57);   // (2*1430)/50
    assert(nRate == 14);  // (57/2)*0.5
    // the guard: count <= 0 -> all untouched
    g_fnKvt20 = [](int32_t) { return 0; };
    nLevels = 5; lExp = 9; nRate = 7;
    CalcExpValues(&mgr, 5, 10, &nLevels,
                  &lExp, &nRate);
    assert(nLevels == 5 && lExp == 9 && nRate == 7);
    g_fnKvt20 = [](int32_t) { return 2; };

    // ---------- 4. MgrEnterTraining (1419e4390) ------
    uint32_t uSentAction = 0, uSentId = 0;
    int nSends = 0;
    g_fnKvtC8 = [&](uint32_t id, void* pMsg) {
        ++nSends; uSentId = id;
        uint8_t* b = (uint8_t*)
            *(void**)((uint8_t*)pMsg + 0x408);
        uSentAction = *(uint16_t*)(b + 4);
    };
    g_fnKvtA0 = []() { return 0x259; };
    g_fnKvt30 = [](uint32_t) { return 1; };
    g_fnKvt70 = [](uint32_t) { return true; };
    MgrEnterTraining(&mgr, 5);
    assert(nSends == 1 && uSentId == 5
        && uSentAction == 2);
    assert(mgr.m_kern18.m_nSize38 == 0);   // no map
    // path B: not 0x259 + 0x98 false -> the stamp
    g_fnKvtA0 = []() { return 0x100; };
    g_fnKvt98 = []() { return false; };
    MgrEnterTraining(&mgr, 5);
    assert(nSends == 1);
    assert(mgr.m_kern18.m_nSize38 == 1);
    {
        SMapIterator lb;
        LowerBound(&mgr.m_kern18, &lb, 5);
        assert(lb.m_pNode08->m_nVal28 == 100000);
    }
    // path C: not 0x259 + 0x98 true + 0x70 true
    g_fnKvt98 = []() { return true; };
    MgrEnterTraining(&mgr, 5);
    assert(nSends == 2 && uSentAction == 2);
    // path D: 0x259 + vt+0x30 == 0 -> nothing
    g_fnKvtA0 = []() { return 0x259; };
    g_fnKvt30 = [](uint32_t) { return 0; };
    MgrEnterTraining(&mgr, 5);
    assert(nSends == 2);
    // path E: the log gate
    g_fnKvt30 = [](uint32_t) { return 1; };
    g_fnKvt70 = [](uint32_t) { return false; };
    g_fnInlineLogError = TstLog;
    MgrEnterTraining(&mgr, 5);
    assert(nSends == 2 && g_nLogs == 1);
    g_fnKvt70 = [](uint32_t) { return true; };

    // ---------- 5. MgrQueryTraining (1419e44e0) -----
    g_fnKvtA0 = []() { return 0x100; };
    g_fnKvt90 = [](uint32_t) { return true; };
    assert(MgrQueryTraining(&mgr, 5)
        == ((uint64_t)0 & ~0xffull));
    assert(nSends == 3 && uSentAction == 5);
    // the calc path
    g_fnKvt90 = [](uint32_t) { return false; };
    g_fnKvt98 = []() { return false; };
    g_fnKvt68 = [](uint32_t) { return 2; };
    g_fnKvtE0 = [](int32_t) { return true; };
    g_fnKvt48 = [](uint32_t) { return 1000; };
    uint64_t uRet = MgrQueryTraining(&mgr, 5);
    assert(uRet == 1);
    assert(nSends == 4 && uSentAction == 0);
    // the elapsed branch: 0x48 small -> bVar3 = 0 +
    // (lVar1>>5)
    g_fnKvt48 = [](uint32_t) { return 0; };
    g_nClock = 100000 + 5400;   // diff = 5400 -> 258
    MgrQueryTraining(&mgr, 5);
    assert(nSends == 5);

    // ---------- 6. MgrClaimTraining (1419e4730) ------
    g_nClock = 100000;
    g_fnKvt70 = [](uint32_t) { return false; };
    assert(MgrClaimTraining(&mgr, 5) == 0);
    g_fnKvt70 = [](uint32_t) { return true; };
    g_fnKvt48 = [](uint32_t) { return 1000; };
    g_fnKvt58 = [](uint32_t) { return 94600; };   // diff 5400 -> A=90
    g_fnKvt88 = [](uint32_t) { return true; };
    g_fnKvt08 = []() { return 1; };
    g_fnKvt10 = []() { return 2; };    // the limit
    g_fnKvt18 = [](int32_t) { return 100; };
    g_fnKvt20 = [](int32_t) { return 2; };
    g_fnKvt28 = [](uint32_t) { return 2000; };   // >= exp
    g_fnKvt30 = [](uint32_t) { return 0; };   // exp base 0:
    // dVar7 = 0 + 2000*100/2 = 1000, lExp =
    // 2*1000/100 = 20 <= 2000 -> the happy path
    g_fnKvt38 = [&](uint32_t, int32_t, char* p) {
        *p = 1; };
    g_fnKvt40 = [&](uint32_t, int32_t, int64_t,
                    int32_t) { assert(false); };
    g_fnKvt50 = [](uint32_t, int32_t, int32_t) {};
    g_fnKvt78 = [](uint32_t, int32_t, int32_t) {};
    g_fnKvt98 = []() { return true; };
    assert(MgrClaimTraining(&mgr, 5) == 1);
    // the 98-false continuation
    g_fnKvt98 = []() { return false; };
    uint32_t uD0Arg = 0, uC0Id = 0;
    uint64_t uC0Packed = 0;
    g_fnKvtA8 = [](uint32_t) { return 0x11; };
    g_fnKvtB8 = [](uint32_t* p, uint32_t) {
        *p = 0x22; };
    g_fnKvtD0 = [&](uint32_t u) {
        uD0Arg = u; return true; };
    g_fnKvtD8 = [](uint32_t, uint32_t, uint32_t) {
        return true; };
    g_fnKvtC0 = [&](uint32_t id, uint32_t a,
                    uint64_t p) {
        uC0Id = id; uC0Packed = p;
        return (uint8_t)7; };
    uint8_t uC = MgrClaimTraining(&mgr, 5);
    assert(uC == 7 && uD0Arg == 0x11 && uC0Id == 5);
    assert(uC0Packed == ((uint64_t)0 << 32) | 0x22);
    // the D0-false fallback
    g_fnKvtD0 = [](uint32_t) { return false; };
    g_fnKvtE8 = [](int64_t* p) {
        *p = 0x0000003300000044ull; };
    uC = MgrClaimTraining(&mgr, 5);
    assert(uC == 7);
    assert(uC0Packed == ((uint64_t)0x33 << 32) | 0x44);
    // the levels<1 path -> the vt+0x40 call:
    // vt28 = 0 -> dVar7 = 0 < 500 at the first
    // loop check -> levels stay 0
    g_fnKvt28 = [](uint32_t) { return 0; };
    g_fnKvt18 = [](int32_t) { return 500; };
    int nVt40Calls = 0;
    g_fnKvt40 = [&](uint32_t, int32_t a,
                    int64_t b, int32_t c) {
        ++nVt40Calls;
        assert(a == 5 && c == 1);
    };
    uC = MgrClaimTraining(&mgr, 5);
    assert(nVt40Calls == 1);

    // ---------- cleanup + balance ----------
    KernelDtorProxy(&mgr.m_kern18);
    assert(nAlloc == nFree);
    printf("TRAINING-D16-OK\n");
    return 0;
}

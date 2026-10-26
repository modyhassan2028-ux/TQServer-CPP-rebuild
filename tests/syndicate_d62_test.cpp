// syndicate_d62_test.cpp — CMsgLeagueRobOpt::
// Process (1417d8920) — the robopt dispatcher.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace syndicate;

// ---- the recording state ----
static int s_nGate;
static char s_cGateRet;
static int s_nVt680, s_nVt6e0, s_nVt730;
static uint64_t s_aA[6];   // last call args
static int s_aCount;
static uint32_t s_auLastIds[10];

static char MockGate(void*) {
    s_nGate++; return s_cGateRet;
}
static void Mock680(void* a, uint32_t b, int32_t c,
                    uint32_t* d, char e, uint32_t f) {
    s_nVt680++; s_aCount = c;
    memcpy(s_auLastIds, d, sizeof(s_auLastIds));
    s_aA[0] = (uint64_t)(uintptr_t)a;
    s_aA[1] = b; s_aA[2] = (uint32_t)c;
    s_aA[4] = (uint8_t)e; s_aA[5] = f;
}
static void Mock6e0(void* a, uint32_t b, int32_t c,
                    uint32_t* d, char e, uint32_t f) {
    s_nVt6e0++; s_aCount = c;
    memcpy(s_auLastIds, d, sizeof(s_auLastIds));
    s_aA[4] = (uint8_t)e; s_aA[5] = f;
    s_aA[1] = b;
}
static void Mock730(void* a, uint32_t b,
                    uint32_t c, uint32_t d,
                    uint32_t e) {
    s_nVt730++;
    s_aA[1] = b; s_aA[2] = c; s_aA[3] = d;
    s_aA[4] = e;
}

int main() {
    // ---------- the fixtures ----------
    // the logic vtable: 232 slots
    static void* apLogicVt[232];
    for (int i = 0; i < 232; i++)
        apLogicVt[i] = (void*)+[](void*, uint64_t,
            uint64_t, uint64_t, uint64_t,
            uint64_t) {};
    apLogicVt[0x680 / 8] = (void*)Mock680;
    apLogicVt[0x6e0 / 8] = (void*)Mock6e0;
    apLogicVt[0x730 / 8] = (void*)Mock730;

    // the mgr at logic+8: the gate at slot 79
    static void* apMgrVt[80];
    for (int i = 0; i < 80; i++)
        apMgrVt[i] = (void*)+[](void*) {};
    apMgrVt[79] = (void*)MockGate;
    static void* apMgrBox[1] = { apMgrVt };

    static uint8_t abLogic[0x58];
    *(void**)(abLogic + 0) = apLogicVt;
    *(void**)(abLogic + 8) = apMgrBox;

    g_fnGetGameMgr = []() -> void* {
        return abLogic;
    };

    // the msg: +0x440 type, +0x444 value,
    // +0x448 the vector, +0x450 the count
    static uint8_t abMsg[0x458];
    // the vector elements: 12 fake objects, each
    // +0x48 = 1000+i
    static uint8_t abElems[12][0x50];
    static void* apVec[12];
    for (int i = 0; i < 12; i++) {
        *(uint32_t*)(abElems[i] + 0x48) =
            1000 + i;
        apVec[i] = abElems[i];
    }
    *(void**)(abMsg + 0x448) = apVec;

    // ---- D62-1: the actor-0 skip ----
    {
        s_nVt680 = s_nVt6e0 = s_nVt730 = 0;
        *(uint32_t*)(abMsg + 0x440) = 0;
        RobOptProcess(abMsg, 0);
        assert(s_nVt680 + s_nVt6e0 + s_nVt730 ==
               0);
        printf("D62-1 the actor-0 skip ok\n");
    }

    // ---- D62-2: gate TRUE → only 2/3/5/6 ----
    {
        s_cGateRet = 1;
        // type 0 → skipped
        *(uint32_t*)(abMsg + 0x440) = 0;
        s_nVt680 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 == 0);
        // type 1 → skipped
        *(uint32_t*)(abMsg + 0x440) = 1;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 == 0);
        // type 4 → skipped
        *(uint32_t*)(abMsg + 0x440) = 4;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 + s_nVt6e0 + s_nVt730 ==
               0);
        // type 2 → DISPATCHES 0x730
        *(uint32_t*)(abMsg + 0x440) = 2;
        *(uint32_t*)(abMsg + 0x444) = 1234567;
        s_nVt730 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt730 == 1);
        assert(s_aA[2] == 2);               // type
        assert(s_aA[3] == 1234567 % 1000);
        assert(s_aA[4] == 1234567 / 1000);
        printf("D62-2 the inverse whitelist ok\n");
    }

    // ---- D62-3: gate FALSE → all 0..6 ----
    {
        s_cGateRet = 0;
        // case 0: vt 0x680, byte 0, dword 0
        *(uint32_t*)(abMsg + 0x440) = 0;
        *(int32_t*)(abMsg + 0x450) = 3;
        s_nVt680 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 == 1);
        assert(s_aCount == 3);
        assert(s_auLastIds[0] == 1000);
        assert(s_auLastIds[1] == 1001);
        assert(s_auLastIds[2] == 1002);
        assert(s_auLastIds[3] == 0);   // zeroed
        assert(s_aA[4] == 0);
        assert(s_aA[5] == 0);
        // case 1: byte 1, dword = +0x444
        *(uint32_t*)(abMsg + 0x440) = 1;
        *(uint32_t*)(abMsg + 0x444) = 0x99887766;
        s_nVt680 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 == 1);
        assert(s_aA[4] == 1);
        assert(s_aA[5] == 0x99887766);
        printf("D62-3 the 680 cases ok\n");
    }

    // ---- D62-4: the 10-id cap ----
    {
        *(uint32_t*)(abMsg + 0x440) = 0;
        *(int32_t*)(abMsg + 0x450) = 12;   // 12!
        s_nVt680 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 == 1);
        assert(s_aCount == 12);   // count passes
        assert(s_auLastIds[9] == 1009);
        printf("D62-4 the 10-id cap ok\n");
    }

    // ---- D62-5: cases 5/6 → vt 0x6e0 ----
    {
        *(int32_t*)(abMsg + 0x450) = 2;
        *(uint32_t*)(abMsg + 0x440) = 5;
        s_nVt6e0 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt6e0 == 1);
        assert(s_aA[4] == 0);
        assert(s_aA[5] == 0);
        assert(s_auLastIds[1] == 1001);
        *(uint32_t*)(abMsg + 0x440) = 6;
        *(uint32_t*)(abMsg + 0x444) = 42;
        s_nVt6e0 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt6e0 == 1);
        assert(s_aA[4] == 1);
        assert(s_aA[5] == 42);
        // case 3 → 0x730 too
        *(uint32_t*)(abMsg + 0x440) = 3;
        *(uint32_t*)(abMsg + 0x444) = 999;
        s_nVt730 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt730 == 1);
        assert(s_aA[2] == 3);
        assert(s_aA[3] == 999);
        assert(s_aA[4] == 0);
        printf("D62-5 the 6e0/730 cases ok\n");
    }

    // ---- D62-6: type > 6 → nothing ----
    {
        s_cGateRet = 0;
        *(uint32_t*)(abMsg + 0x440) = 7;
        s_nVt680 = s_nVt6e0 = s_nVt730 = 0;
        RobOptProcess(abMsg, 7);
        assert(s_nVt680 + s_nVt6e0 + s_nVt730 ==
               0);
        printf("D62-6 the type-7 bound ok\n");
    }

    printf("SYNDICATE_D62_OK: the robopt\n");
    return 0;
}

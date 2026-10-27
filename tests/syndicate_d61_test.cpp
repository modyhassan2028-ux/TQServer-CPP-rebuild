// syndicate_d61_test.cpp — CMsgLeagueOpt::Process
// (1417d68d0) + the gate + the 12 wrappers.
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace syndicate;

// ---- the recording state ----
static int s_nGate;             // the gate fn hits
static char s_cGateRet;         // the gate return
static int s_nVtCall;           // vt slot calls
static uint64_t s_aVtArgs[4];   // last args
static int s_nMgrSend;          // vt+0x28 sends
static uint64_t s_uSendColor;
static std::string s_sSendStr;
static int s_nTail;             // tail dispatches
static std::vector<std::string> s_aLogs;
static std::vector<std::string> s_aStrMgr;

// the gate: vt slot 0x278/8 = 79 on the mgr
static char MockGate(void*) {
    s_nGate++; return s_cGateRet;
}
// the tail dispatch: mgr vt slot 1
static void MockTail() { s_nTail++; }
// a generic vt recorder (4 args max)
static void MockVtCall(void* a, uint64_t b,
                      uint64_t c, uint64_t d) {
    s_nVtCall++; s_aVtArgs[0] = (uint64_t)(uintptr_t)a;
    s_aVtArgs[1] = b; s_aVtArgs[2] = c;
    s_aVtArgs[3] = d;
}

int main() {
    // ---------- the fixtures ----------
    // the logic: a vtable with 232 slots, all
    // pointing at the recorder
    static void* apLogicVt[232];
    for (int i = 0; i < 232; i++)
        apLogicVt[i] = (void*)MockVtCall;
    // the logic's FIRST qword = the vtable
    // DIRECTLY (the port reads *(void***)logic)

    // the mgr at logic+8: its vtable with the
    // gate at slot 79 and the send at slot 5
    static void* apMgrVt[80];
    for (int i = 0; i < 80; i++)
        apMgrVt[i] = (void*)MockVtCall;
    apMgrVt[1] = (void*)MockTail;
    apMgrVt[79] = (void*)MockGate;
    static void* apMgrBox[1] = { apMgrVt };

    static uint8_t abLogic[0x58];
    *(void**)(abLogic + 0) = apLogicVt;
    *(void**)(abLogic + 8) = apMgrBox;
    *(void**)(abLogic + 0x50) = (void*)0xACC7;

    // the game mgr seam returns the logic
    g_fnGetGameMgr = []() -> void* {
        return abLogic;
    };

    // the msg: +0x408 the PB, +0x410 the packer
    static uint8_t abMsg[0x418];
    static uint8_t abPb[16];
    *(void**)(abMsg + 0x408) = abPb;

    // ---- D61-1: the gate ----
    {
        s_nGate = 0; s_cGateRet = 1;
        assert(LeagueOptGate(abLogic) == 1);
        assert(s_nGate == 1);
        s_cGateRet = 0;
        assert(LeagueOptGate(abLogic) == 0);
        printf("D61-1 the gate ok\n");
    }

    // ---- D61-2: the m_pInfo null log ----
    {
        s_aLogs.clear();
        g_fnLeagueOptLogError =
            [](void*, const char* a,
               const char* b, const char* c) {
                s_aLogs.push_back(
                    std::string(a) + "|" +
                    std::string(b) + "|" +
                    std::string(c));
            };
        *(void**)(abMsg + 0x408) = 0;
        LeagueOptProcess(abMsg, 7);
        assert(s_aLogs.size() == 1);
        assert(s_aLogs[0].find("CHECK") !=
               std::string::npos);
        assert(s_aLogs[0].find("m_pInfo") !=
               std::string::npos);
        assert(s_aLogs[0].find(
            "msgleagueopt.cpp") != std::string::npos);
        *(void**)(abMsg + 0x408) = abPb;
        printf("D61-2 the null log ok\n");
    }

    // ---- D61-3: the gate whitelist ----
    {
        s_cGateRet = 1;   // the gate TRUE
        s_nVtCall = 0;
        // opt 8 NOT in the whitelist → return
        *(uint16_t*)(abPb + 4) = 8;
        LeagueOptProcess(abMsg, 7);
        assert(s_nVtCall == 0);
        // opt 4 IS whitelisted → dispatches 0x5b8
        *(uint16_t*)(abPb + 4) = 4;
        *(uint32_t*)(abPb + 0xe) = 0x55;
        s_nVtCall = 0;
        LeagueOptProcess(abMsg, 7);
        assert(s_nVtCall == 1);
        assert(s_aVtArgs[1] == 7);        // actor
        assert(s_aVtArgs[2] == 0x55);     // PB+0xe
        printf("D61-3 the whitelist ok\n");
    }

    // ---- D61-4: the plain vt dispatches ----
    {
        s_cGateRet = 0;   // the gate FALSE
        // case 0 → vt 0x5b0 (logic, actor)
        *(uint16_t*)(abPb + 4) = 0;
        s_nVtCall = 0;
        LeagueOptProcess(abMsg, 3);
        assert(s_nVtCall == 1);
        assert(s_aVtArgs[1] == 3);
        // case 1 → vt 0x5c0 (actor, PB+6, PB+0xe)
        *(uint16_t*)(abPb + 4) = 1;
        *(uint32_t*)(abPb + 6) = 0x66;
        *(uint32_t*)(abPb + 0xe) = 0x77;
        s_nVtCall = 0;
        LeagueOptProcess(abMsg, 3);
        assert(s_nVtCall == 1);
        assert(s_aVtArgs[1] == 3);
        assert(s_aVtArgs[2] == 0x66);
        assert(s_aVtArgs[3] == 0x77);
        // case 0x17 → vt 0x5f0 with the BYTE at
        // PB+0xe
        *(uint16_t*)(abPb + 4) = 0x17;
        *(uint8_t*)(abPb + 0xe) = 0xAB;
        s_nVtCall = 0;
        LeagueOptProcess(abMsg, 3);
        assert(s_nVtCall == 1);
        assert(s_aVtArgs[2] == 0xAB);
        // case 0x13 → vt 0x718 (logic, actor)
        *(uint16_t*)(abPb + 4) = 0x13;
        s_nVtCall = 0;
        LeagueOptProcess(abMsg, 3);
        assert(s_nVtCall == 1);
        assert(s_aVtArgs[1] == 3);
        printf("D61-4 the vt dispatches ok\n");
    }

    // ---- D61-5: the string cases ----
    {
        // case 6: GetString → b0a40 TRUE →
        // PB+4 = 0x16 + the tail dispatch
        g_fnCStrPackerGetString =
            [](void*, int32_t, char* pOut,
               int32_t) -> bool {
            strcpy(pOut, "NAME");
            return true;
        };
        g_fn1417b0a40 =
            [](void* p, uint32_t a, uint32_t b,
               char* c) -> uint64_t {
            assert(b == 0x6666);
            assert(strcmp(c, "NAME") == 0);
            return 1;
        };
        s_nTail = 0;
        *(uint16_t*)(abPb + 4) = 6;
        *(uint32_t*)(abPb + 6) = 0x6666;
        LeagueOptProcess(abMsg, 3);
        assert(*(uint16_t*)(abPb + 4) == 0x16);
        assert(s_nTail == 1);
        // case 33: b03b0 TRUE → PB+4 = 0x33
        g_fn1417b03b0 =
            [](void*, uint32_t, uint32_t,
               char*) -> char { return 1; };
        s_nTail = 0;
        *(uint16_t*)(abPb + 4) = 0x33;
        LeagueOptProcess(abMsg, 3);
        assert(*(uint16_t*)(abPb + 4) == 0x33);
        assert(s_nTail == 1);
        // case 42: GetStrAmount 0 → nothing;
        // nonzero → b0680 + vt 0x5b0
        g_fnCStrPackerGetStrAmount =
            [](void*) -> uint32_t { return 2; };
        int nDeep = 0;
        g_fn1417b0680 =
            [](void*, uint32_t, char*,
                uint64_t uCap) {
            assert(uCap == 0x100);
        };
        *(uint16_t*)(abPb + 4) = 0x42;
        nDeep = 0; s_nVtCall = 0;
        LeagueOptProcess(abMsg, 3);
        assert(s_nVtCall == 1);   // the 0x5b0
        g_fnCStrPackerGetStrAmount =
            [](void*) -> uint32_t { return 0; };
        s_nVtCall = 0;
        LeagueOptProcess(abMsg, 3);
        assert(s_nVtCall == 0);
        printf("D61-5 the string cases ok\n");
    }

    // ---- D61-6: the wrappers ----
    {
        // b0db0: the null gates
        int nAcct = 0;
        g_fn14174ed50 =
            [](void* pAcct, int32_t a,
               char* p, uint32_t b, uint16_t c) {
            assert(pAcct == (void*)0xACC7);
            assert(strcmp(p, "NM") == 0);
            assert(a == 9); assert(b == 4);
            assert(c == 6);
        };
        Fn1417b0db0(abLogic, 0, "NM", 4, 6);
        Fn1417b0db0(abLogic, 9, 0, 4, 6);
        Fn1417b0db0(abLogic, 9, "NM", 4, 6);
        printf("D61-6a the b0db0 gates ok\n");
        // b0e00: the '\0' char arg + the acct
        static uint64_t uChar;
        g_fn14174eda0 =
            [](void*, uint32_t a, char c,
               void* p4) {
            uChar = (uint8_t)c;
            assert(p4 == (void*)kImageBase);
            assert(a == 5);
        };
        Fn1417b0e00(abLogic, 5, 0x1a,
                    (void*)kImageBase);
        assert(uChar == 0);
        // b1690: the NULL last arg
        g_fn14174eec0 =
            [](void*, int32_t a, uint32_t b,
               char* pNull) {
            assert(a == 7); assert(b == 3);
            assert(pNull == 0);
        };
        Fn1417b1690(abLogic, 7, 3);
        // bf4d0: the tri-switch routing
        static void* apRoute[3] = {0, 0, 0};
        g_fn1417b3300 =
            [](void*, uint32_t, bool, uint64_t) {
            apRoute[0] = (void*)1; };
        g_fn1417bed70 =
            [](void*, uint32_t, bool, uint64_t) {
            apRoute[1] = (void*)1; };
        g_fn1417b3a90 =
            [](void*, uint32_t, bool, uint64_t) {
            apRoute[2] = (void*)1; };
        Fn1417bf4d0(abLogic, 5, 0x67, 1, 9);
        assert(apRoute[0] && !apRoute[1]);
        Fn1417bf4d0(abLogic, 5, 0xcd, 1, 9);
        assert(apRoute[1]);
        Fn1417bf4d0(abLogic, 5, 0xce, 1, 9);
        assert(apRoute[2]);
        // b1a40: the vt 0x510 gate
        static int nTok;
        static void* apTokVt[232];
        memcpy(apTokVt, apLogicVt,
               sizeof(apTokVt));
        apTokVt[0x510 / 8] =
            (void*)+[](void*) -> uint32_t {
            return 0; };
        // (the first qword = the vtable)
        static uint8_t abTokLogic[0x58];
        memcpy(abTokLogic, abLogic, 0x58);
        *(void**)(abTokLogic + 0) = apTokVt;
        g_fn14176ea30 =
            [](void*, uint32_t, uint32_t,
               uint32_t) -> uint64_t {
            return 1;
        };
        g_fn1417b0ea0 =
            [](void*, uint32_t u3, char c) {
            nTok++; assert(u3 == 5); assert(c == 1);
        };
        Fn1417b1a40(abTokLogic, 3, 5);
        assert(nTok == 0);   // the 0x510 gate 0
        // now a nonzero 0x510 → the flow runs
        apTokVt[0x510 / 8] =
            (void*)+[](void*) -> uint32_t {
            return 0x4242; };
        nTok = 0;
        Fn1417b1a40(abTokLogic, 3, 5);
        assert(nTok == 1);
        printf("D61-6 the wrappers ok\n");
    }

    // ---- D61-7: the concubine flows ----
    {
        // b15b0: the owner EQUAL → the apply
        static void* apOwnVt[80];
        for (int i = 0; i < 80; i++)
            apOwnVt[i] = (void*)MockVtCall;
        // the mgr vt: slot 79 (0x4a8) → 0x99,
        // slot 5 (0x28) → the send recorder
        s_nMgrSend = 0;
        apOwnVt[0x4a8 / 8] =
            (void*)+[](void*) -> int32_t {
            return 0x99;
        };
        apOwnVt[0x28 / 8] =
            (void*)+[](void* pMgr, uint32_t uActor,
                       void* pStr,
                       uint32_t uColor) {
            s_nMgrSend++;
            s_uSendColor = uColor;
            s_sSendStr = (const char*)pStr;
            assert(uActor == 3);
        };
        static void* apOwnBox[1] = { apOwnVt };
        static uint8_t abOwnLogic[0x58];
        memcpy(abOwnLogic, abLogic, 0x58);
        *(void**)(abOwnLogic + 8) = apOwnBox;
        g_fn14174e3f0 =
            [](void*) -> int32_t { return 0x99; };
        static int nApply;
        g_fn14174ee70 =
            [](void*, int32_t a, int32_t b,
                int16_t c) {
            nApply++; assert(a == 3);
            assert(b == 11); assert(c == 4);
        };
        Fn1417b15b0(abOwnLogic, 3, 11, 4);
        assert(nApply == 1);
        assert(s_nMgrSend == 0);
        // the owner UNEQUAL → the FAIL string send
        g_fn14174e3f0 =
            [](void*) -> int32_t { return 0xAA; };
        s_aStrMgr.clear();
        g_fnStringMgrInstance =
            []() -> void* { return (void*)1; };
        g_fnStringMgrGetStr =
            [](void*, const char* p) -> void* {
            s_aStrMgr.push_back(p);
            return (void*)p;
        };
        Fn1417b15b0(abOwnLogic, 3, 11, 4);
        assert(nApply == 1);
        assert(s_nMgrSend == 1);
        assert(s_uSendColor == 0xffff00);
        assert(s_aStrMgr.size() == 1);
        assert(s_aStrMgr[0] ==
               "STR_LEAGUE_CONCUBINES_FAIL");
        // b14c0: the +0x1e0 OFFLINE → the
        // USER_OFFLINE string
        apOwnVt[0x1e0 / 8] =
            (void*)+[](void*, void*) -> int32_t {
            return 0;   // offline
        };
        Fn1417b14c0(abOwnLogic, 3, (void*)0x77,
                    4, 5, 6);
        assert(s_aStrMgr.size() == 2);
        assert(s_aStrMgr[1] ==
               "STR_LEAGUE_CONCUBINES_USER_OFFLINE");
        // online but ANOTHER LEAGUE → the OTHER
        // string
        apOwnVt[0x1e0 / 8] =
            (void*)+[](void*, void*) -> int32_t {
            return 0x55;
        };
        apOwnVt[0x4a8 / 8] =
            (void*)+[](void*, int32_t) -> int32_t {
            return 0x66;   // ≠ 0xAA
        };
        Fn1417b14c0(abOwnLogic, 3, (void*)0x77,
                    4, 5, 6);
        assert(s_aStrMgr.size() == 3);
        assert(s_aStrMgr[2] ==
               "STR_LEAGUE_OTHER_LEAGUE_USER");
        // the SAME league → the apply e40
        apOwnVt[0x4a8 / 8] =
            (void*)+[](void*, int32_t) -> int32_t {
            return 0xAA;
        };
        static int nE40;
        g_fn14174ee40 =
            [](void* pA, int32_t a, int32_t b,
                uint16_t c, uint32_t d,
                int32_t e) {
            nE40++;
            assert(pA == (void*)0xACC7);
            assert(a == 3); assert(b == 0x55);
            assert(c == 4); assert(d == 5);
            assert(e == 6);
        };
        Fn1417b14c0(abOwnLogic, 3, (void*)0x77,
                    4, 5, 6);
        assert(nE40 == 1);
        assert(s_aStrMgr.size() == 3);
        printf("D61-7 the concubine flows ok\n");
    }

    // ---- D61-8: the 0x4a-0x4d swap cases ----
    {
        static uint32_t uP3, uP2;
        g_fn1417b48b0 =
            [](void*, uint32_t a, uint32_t b,
               bool, bool) {
            uP2 = a; uP3 = b;
        };
        // case 0x4a: (logic, actor, PB+10, ...)
        *(uint16_t*)(abPb + 4) = 0x4a;
        *(uint32_t*)(abPb + 10) = 0x9999;
        *(uint32_t*)(abPb + 0xe) = 0;
        LeagueOptProcess(abMsg, 3);
        assert(uP2 == 3 && uP3 == 0x9999);
        // case 0x4c: SWAPPED — actor via param 3
        *(uint16_t*)(abPb + 4) = 0x4c;
        LeagueOptProcess(abMsg, 3);
        assert(uP2 == 0x9999 && uP3 == 3);
        printf("D61-8 the swap cases ok\n");
    }

    printf("SYNDICATE_D61_OK: the league opt\n");
    return 0;
}

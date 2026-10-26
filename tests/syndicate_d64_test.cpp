// syndicate_d64_test.cpp — the GM name-change flow
// 1417b03b0 + the price getter 14174e750 (the D61
// case-0x33 seam's real body) — the header has the
// full discovery notes.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueGmName.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueNameApply.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace syndicate;

// ---- the recording state ----
static int s_nUnexpected;
static int s_nInvalid;
static int s_nEntResolve[16];
static int s_nSub1Set80; static uint64_t s_uSub1Set80Val;
static int s_nProvFlush38;
static int s_nMgr18;  static uint64_t s_aMgr18[2];
static int s_nMgr70;  static uint64_t s_aMgr70[4];
static int s_nMgr90;  static std::string s_sMgr90Str;
static int s_uMgr90Arg;
static int s_nMgr428; static uint64_t s_aMgr428[3];
static int s_nMgr140; static uint64_t s_aMgr140[6];
static int s_nMgr238; static uint64_t s_uMgr238Ret;
static int s_nMgr200; static uint64_t s_uMgr200Ret;
static int s_nMgr1D8; static uint64_t s_uMgr1D8Ret;
static int s_nLogSave;
static std::string s_sLogFile, s_sLogFmt, s_sLogLine;
static std::vector<std::string> s_aStrFetch;
static int s_nTail;

static uint64_t s_uChargeRet = 1;

// ---- the mock sub fns ----
static const char* s_szCurName = "OldName";
static uint64_t s_uSub2Val = 0x1111;
static uint64_t s_uFlag1000 = 1000;

static void* Sub1Get78(void**) {
    return (void*)(uintptr_t)s_szCurName; }
static void Sub1Set80(void**, uint64_t v) {
    s_nSub1Set80++; s_uSub1Set80Val = v; }
static void* Sub2Get48(void**) { return (void*)s_uSub2Val; }
static void* Sub2bGet48(void**) { return (void*)s_uFlag1000; }
static void* Sub0Get48(void**) { return (void*)0x77; }

static void* s_apSubs[16];
static void* MockEntResolve(void*, uint64_t idx) {
    assert(idx < 16);
    s_nEntResolve[idx]++;
    return s_apSubs[idx];
}
static void MockProvFlush38(void*, uint64_t) {
    s_nProvFlush38++; }

// ---- the fixtures ----
static void* s_apSub1Vt[32]; static void* s_apSub2Vt[16];
static void* s_apSub0Vt[16]; static void* s_apSub2bVt[16];
static void* s_apProvVt[16];
static void* s_apSubBox[16][4];
static void* s_apProvBox[1];
static void* s_apEntity[2];

// the rec chain
static void* s_apRecAnchorBox[1];
static void* s_apRecAnchorInner[8];
static uint8_t s_abRecHead[0x30];
static uint8_t s_abRecNode[0x30];
static void* s_apRecMap[8];
static void* s_apRecBox[1];
static void* s_apAttrBox[1];
static void* s_apAttrVt[4];
static void* s_apSub2bBox[4];

// the host (0x190 — the price field at +0x18c)
static uint8_t s_abHost[0x190];
static void* s_apLgAnchorBox[1];
static void* s_apLgAnchorInner[8];
static uint8_t s_abLgHead[0x30];
static uint8_t s_abLgNode[0x30];

// the mgr
static void* s_apMgrVt[256];
static void* s_apMgrBox[1];
static void* MgrVt1F8(void* p, uint64_t a) {
    (void)p; (void)a; return (void*)0x1111; }
static void* MgrVt2E8(void* p, uint64_t a) {
    (void)p; (void)a; return (void*)1; }
static void* MgrVt18(void* p, uint64_t a, uint64_t b) {
    (void)p; s_nMgr18++;
    s_aMgr18[0] = a; s_aMgr18[1] = b;
    return (void*)0x55; }
static void MgrVt70(void* p, uint64_t a, uint64_t b,
                   uint64_t c, uint64_t d) {
    (void)p; s_nMgr70++;
    s_aMgr70[0] = a; s_aMgr70[1] = b;
    s_aMgr70[2] = c; s_aMgr70[3] = d; }
static void MgrVt90(void* p, const char* s, uint64_t n) {
    (void)p; s_nMgr90++; s_sMgr90Str = s;
    s_uMgr90Arg = (int)n; }
static void MgrVt428(void* p, uint64_t a, uint64_t b) {
    (void)p; s_nMgr428++;
    s_aMgr428[0] = a; s_aMgr428[1] = b; }
// vt+0x140 — SIX args (the discovery)
static void* MgrVt140(void* p, uint64_t a, uint64_t b,
                      uint64_t c, uint64_t d, uint64_t e) {
    (void)p; s_nMgr140++;
    s_aMgr140[0] = a; s_aMgr140[1] = b;
    s_aMgr140[2] = c; s_aMgr140[3] = d;
    s_aMgr140[4] = e;
    return (void*)s_uChargeRet;
}
// vt+0x238 — the emoney read
static uint64_t MgrVt238(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr238++;
    return s_uMgr238Ret;
}
// vt+0x200 — the type
static uint64_t MgrVt200(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr200++;
    return s_uMgr200Ret;
}
// vt+0x1d8 — the name
static uint64_t MgrVt1D8(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr1D8++;
    return s_uMgr1D8Ret;
}
static void MockTail() { s_nTail++; }
static char MockGate() { return 0; }

// the logic
static uint8_t s_abLogic[0x58];
static void* s_apLogicVt[232];
static void MockLogicVt(void*, uint64_t) {
    s_nUnexpected++; }

// the string mgr
static void* s_pStrMgr = (void*)0x77AA;
static void* MockStrMgrInstance() { return s_pStrMgr; }
static void* MockStrMgrGetStr(void* p, const char* k) {
    assert(p == s_pStrMgr);
    s_aStrFetch.push_back(k);
    if (strcmp(k, "STR_FORBIDDEN_LEAGUE_NAME") == 0)
        return (void*)(uintptr_t)"FRB!";
    if (strcmp(k, "STR_BROADCAST_NEW_LEAGUE_NAME") == 0)
        return (void*)(uintptr_t)"cur=%s got=%s";
    return (void*)(uintptr_t)"?";
}
static bool MockGetStr(void*, int32_t, char* out, int32_t) {
    strcpy(out, "NewName"); return true; }

// the logsave seam (all five args)
static void MockLogSave(const char* f, const char* fmt,
                        uint32_t actor, const char* who,
                        uint32_t type, uint32_t p1,
                        uint32_t p2) {
    s_nLogSave++;
    s_sLogFile = f; s_sLogFmt = fmt;
    char ac[256];
    snprintf(ac, sizeof ac,
             "%u|%s|%u|%u|%u", actor, who, type, p1, p2);
    s_sLogLine = ac;
}

// the attr resolve
static void* MockAttrResolve(void*, uint64_t idx) {
    assert(idx == 2);
    return s_apSub2bBox;
}

static void ResetCounters() {
    s_nUnexpected = 0; s_nInvalid = 0;
    memset(s_nEntResolve, 0, sizeof s_nEntResolve);
    s_nSub1Set80 = 0; s_nProvFlush38 = 0;
    s_nMgr18 = 0; s_nMgr70 = 0; s_nMgr90 = 0;
    s_nMgr428 = 0; s_nMgr140 = 0; s_nMgr238 = 0;
    s_nMgr200 = 0; s_nMgr1D8 = 0; s_nLogSave = 0;
    s_nTail = 0;
    s_aStrFetch.clear();
    s_szCurName = "OldName";
    s_uSub2Val = 0x1111; s_uFlag1000 = 1000;
    s_uChargeRet = 1; s_uMgr238Ret = 5000;
    s_uMgr200Ret = 0x99;
    s_uMgr1D8Ret = (uint64_t)(uintptr_t)"Player";
}

static void FillVt(void** vt, int n) {
    for (int i = 0; i < n; i++)
        vt[i] = (void*)MockLogicVt;   // trap
}

int main() {
    // ================= the fixtures =================
    FillVt(s_apSub1Vt, 32);
    s_apSub1Vt[15] = (void*)Sub1Get78;
    s_apSub1Vt[16] = (void*)Sub1Set80;
    FillVt(s_apSub2Vt, 16);
    s_apSub2Vt[9] = (void*)Sub2Get48;
    FillVt(s_apSub0Vt, 16);
    s_apSub0Vt[9] = (void*)Sub0Get48;
    FillVt(s_apSub2bVt, 16);
    s_apSub2bVt[9] = (void*)Sub2bGet48;
    s_apSubBox[0][0] = s_apSub0Vt;
    s_apSubBox[1][0] = s_apSub1Vt;
    s_apSubBox[2][0] = s_apSub2Vt;
    s_apSubs[0] = s_apSubBox[0];
    s_apSubs[1] = s_apSubBox[1];
    s_apSubs[2] = s_apSubBox[2];
    FillVt(s_apProvVt, 16);
    s_apProvVt[2] = (void*)MockEntResolve;
    s_apProvVt[7] = (void*)MockProvFlush38;
    s_apProvBox[0] = s_apProvVt;
    s_apEntity[1] = s_apProvBox;

    // the rec chain + map
    s_apSub2bBox[0] = s_apSub2bVt;
    FillVt(s_apAttrVt, 4);
    s_apAttrVt[2] = (void*)MockAttrResolve;
    s_apAttrBox[0] = s_apAttrVt;
    s_apRecBox[0] = s_apAttrBox;
    s_apRecAnchorInner[6] = (void*)0x4321;
    s_apRecAnchorBox[0] = s_apRecAnchorInner;
    memset(s_abRecHead, 0, sizeof s_abRecHead);
    memset(s_abRecNode, 0, sizeof s_abRecNode);
    *(char*)(s_abRecHead + 0x29) = 1;
    *(void**)(s_abRecNode + 0) = s_abRecHead;
    *(void**)(s_abRecNode + 8) = s_abRecHead;
    *(void**)(s_abRecNode + 0x10) = s_abRecHead;
    *(uint32_t*)(s_abRecNode + 0x18) = 0x42;
    *(void**)(s_abRecNode + 0x20) = s_apRecBox;
    *(void**)(s_abRecHead + 8) = s_abRecNode;
    s_apRecMap[0] = s_apRecAnchorBox;
    s_apRecMap[6] = s_abRecHead;

    // the host + the leagues map
    s_apLgAnchorInner[6] = (void*)0x8888;
    s_apLgAnchorBox[0] = s_apLgAnchorInner;
    memset(s_abLgHead, 0, sizeof s_abLgHead);
    memset(s_abLgNode, 0, sizeof s_abLgNode);
    *(char*)(s_abLgHead + 0x29) = 1;
    *(void**)(s_abLgNode + 0) = s_abLgHead;
    *(void**)(s_abLgNode + 8) = s_abLgHead;
    *(void**)(s_abLgNode + 0x10) = s_abLgHead;
    *(uint32_t*)(s_abLgNode + 0x18) = 0x6666;
    *(void**)(s_abLgNode + 0x20) = s_apEntity;
    *(void**)(s_abLgHead + 0) = s_abLgNode;
    *(void**)(s_abLgHead + 8) = s_abLgNode;
    memset(s_abHost, 0, sizeof s_abHost);
    *(void**)(s_abHost + 0x38) = s_apLgAnchorBox;
    *(void**)(s_abHost + 0x68) = s_abLgHead;
    *(uint32_t*)(s_abHost + 0x18c) = 300;   // the price

    // the mgr
    FillVt(s_apMgrVt, 256);
    s_apMgrVt[1] = (void*)MockTail;
    s_apMgrVt[3] = (void*)MgrVt18;
    s_apMgrVt[14] = (void*)MgrVt70;
    s_apMgrVt[18] = (void*)MgrVt90;
    s_apMgrVt[40] = (void*)MgrVt140;   // 0x140/8
    s_apMgrVt[59] = (void*)MgrVt1D8;   // 0x1d8/8
    s_apMgrVt[63] = (void*)MgrVt1F8;
    s_apMgrVt[64] = (void*)MgrVt200;   // 0x200/8
    s_apMgrVt[71] = (void*)MgrVt238;   // 0x238/8
    s_apMgrVt[79] = (void*)MockGate;
    s_apMgrVt[93] = (void*)MgrVt2E8;
    s_apMgrVt[133] = (void*)MgrVt428;
    s_apMgrBox[0] = s_apMgrVt;

    // the logic
    FillVt(s_apLogicVt, 232);
    *(void**)(s_abLogic + 0) = s_apLogicVt;
    *(void**)(s_abLogic + 8) = s_apMgrBox;
    *(void**)(s_abLogic + 0x18) = s_apRecMap;
    *(void**)(s_abLogic + 0x50) = s_abHost;

    // the seams
    g_fnGmNameLogSave = MockLogSave;
    g_fnStringMgrInstance = MockStrMgrInstance;
    g_fnStringMgrGetStr = MockStrMgrGetStr;
    g_fnGetGameMgr = []() -> void* {
        return s_abLogic; };
    g_fn14174e3f0 = [](void*) -> int32_t {
        return 0x7777; };   // the owner != synId
    g_fnCStrPackerGetString = MockGetStr;
    g_fnNameApplyInvalid = []() { s_nInvalid++; };

    // ============ D64-1: the price getter ============
    {
        assert(LeagueNamePriceGet(s_abHost) == 300);
        *(uint32_t*)(s_abHost + 0x18c) = 777;
        assert(LeagueNamePriceGet(s_abHost) == 777);
        *(uint32_t*)(s_abHost + 0x18c) = 300;
        printf("D64-1 the price field ok\n");
    }

    // ============ D64-2: the gates ============
    {
        ResetCounters();
        // null name
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, nullptr) == 0);
        // unknown league
        *(void**)(s_abLgHead + 0) = s_abLgHead;
        *(void**)(s_abLgHead + 8) = s_abLgHead;
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        *(void**)(s_abLgHead + 0) = s_abLgNode;
        *(void**)(s_abLgHead + 8) = s_abLgNode;
        // mismatch 1f8 vs cb0(2)
        s_uSub2Val = 0x9999;
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        s_uSub2Val = 0x1111;
        // NO sub8 gate: cb0(2) is the FIRST (and
        // only) cb call so far
        assert(s_nEntResolve[8] == 0);
        assert(s_nEntResolve[2] == 1);
        // no rec
        *(void**)(s_abRecHead + 8) = s_abRecHead;
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        *(void**)(s_abRecHead + 8) = s_abRecNode;
        // the flag
        s_uFlag1000 = 999;
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        s_uFlag1000 = 1000;
        // 16-char name
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666,
            (char*)"AAAAAAAAAAAAAAAA") == 0);
        // vt+0x2e8 false
        // (vt93 returns 1; make it 0 via the mgr vt)
        s_apMgrVt[93] = (void*)MgrVt1D8;  // ret "Player"!=0... trap
        // simpler: a 0-returning mock
        s_apMgrVt[93] = (void*)MgrVt200;
        s_uMgr200Ret = 0;
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        s_apMgrVt[93] = (void*)MgrVt2E8;   // restore
        // forbidden
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"OldName") == 0);
        assert(s_aStrFetch.size() == 1);
        assert(s_aStrFetch[0] ==
            "STR_FORBIDDEN_LEAGUE_NAME");
        assert(s_nMgr18 == 1);
        assert(s_aMgr18[0] == 0x42);
        assert(strcmp((const char*)
            (uintptr_t)s_aMgr18[1], "FRB!") == 0);
        // the price gate: emoney < price
        s_uMgr238Ret = 100;   // < 300
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        assert(s_nMgr140 == 0);
        s_uMgr238Ret = 5000;
        // the charge false
        s_uChargeRet = 0;
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        assert(s_nMgr140 == 1);
        s_uChargeRet = 1;
        assert(s_nLogSave == 0);   // nothing logged
        assert(s_nUnexpected == 0);
        printf("D64-2 the gates ok\n");
    }

    // ============ D64-3: the success flow ============
    {
        ResetCounters();
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 1);
        // the gmlog pack (the FIVE args)
        assert(s_nLogSave == 1);
        assert(s_sLogFile == "gmlog/emoney_buy");
        assert(s_sLogFmt ==
            "%u\t%s\t%u\t350\t4237\t%d\t%d\t1\t");
        assert(s_sLogLine == "66|Player|153|300|300");
        // the charge call (SIX args)
        assert(s_nMgr140 == 1);
        assert(s_aMgr140[0] == 0x42);   // actor
        assert(s_aMgr140[1] == 0);     // 0
        assert(s_aMgr140[2] == 300);   // price
        assert(s_aMgr140[3] == 0x43);  // 'C'
        assert(s_aMgr140[4] == 1);     // byte 1
        // the broadcast
        assert(s_aStrFetch.size() == 1);
        assert(s_aStrFetch[0] ==
            "STR_BROADCAST_NEW_LEAGUE_NAME");
        assert(s_sMgr90Str == "cur=OldName got=NewName");
        assert(s_uMgr90Arg == 2000);
        // the rec write
        assert(s_nSub1Set80 == 1);
        assert(strcmp((const char*)
            (uintptr_t)s_uSub1Set80Val, "NewName") == 0);
        assert(s_nProvFlush38 == 1);   // ONE flush
        // the id grant
        assert(s_nMgr428 == 1);
        assert(s_aMgr428[0] == 0x77);
        assert(strcmp((const char*)
            (uintptr_t)s_aMgr428[1], "NewName") == 0);
        // the INVERTED gate: owner 0x7777 != 0x6666
        assert(s_nMgr70 == 1);
        assert(s_aMgr70[0] == 7);
        assert(s_aMgr70[1] == 0x6666);
        assert(s_aMgr70[2] == 0);
        assert(strcmp((const char*)
            (uintptr_t)s_aMgr70[3], "NewName") == 0);
        assert(s_nUnexpected == 0);
        // the equal owner -> NO vt+0x70
        g_fn14174e3f0 = [](void*) -> int32_t {
            return 0x6666; };
        ResetCounters();
        assert(LeagueGmNameChange(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 1);
        assert(s_nMgr70 == 0);
        g_fn14174e3f0 = [](void*) -> int32_t {
            return 0x7777; };
        printf("D64-3 the success flow ok\n");
    }

    // ============ D64-4: the E2E (case 0x33) ============
    {
        ResetCounters();
        g_fn1417b03b0 = LeagueGmNameChange;
        static uint8_t abMsg[0x418];
        static uint8_t abPb[16];
        *(void**)(abMsg + 0x408) = abPb;
        *(uint16_t*)(abPb + 4) = 0x33;
        *(uint32_t*)(abPb + 6) = 0x6666;
        LeagueOptProcess(abMsg, 0x42);
        assert(*(uint16_t*)(abPb + 4) == 0x33);
        assert(s_nTail == 1);
        assert(s_nLogSave == 1);
        assert(s_sLogLine == "66|Player|153|300|300");
        assert(s_nUnexpected == 0);
        printf("D64-4 the case-0x33 E2E ok\n");
    }

    printf("SYNDICATE_D64_OK: the GM name change\n");
    return 0;
}

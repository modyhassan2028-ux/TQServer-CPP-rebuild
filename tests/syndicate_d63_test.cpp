// syndicate_d63_test.cpp — the league name-apply
// flow 1417b0a40 + the 6 helpers (the D61 case-6
// seam's real body) — see SyndicateLeagueNameApply.h
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
static std::vector<std::string> s_aLogs;
static int s_nInvalid;
static int s_nEntResolve[16];
static int s_nSub1Set80; static uint64_t s_uSub1Set80Val;
static int s_nSub8SetD8; static uint32_t s_uSub8SetD8Val;
static int s_nProvFlush38; static uint64_t s_uProvFlush38Arg;
static int s_nMgr18;   static uint64_t s_aMgr18[2];
static int s_nMgr70;   static uint64_t s_aMgr70[4];
static int s_nMgr90;   static std::string s_sMgr90Str;
static int s_uMgr90Arg;
static int s_nMgr428;  static uint64_t s_aMgr428[3];
static std::vector<std::string> s_aStrFetch;
static int s_nTail;

// ---- the seams ----
static void MockLog(const char* p1, const char* p2,
                    const char* pf, uint32_t ln) {
    char ac[256];
    snprintf(ac, sizeof ac, "%s|%s|%s|%u", p1, p2,
            strrchr(pf, '\\') + 1, ln);
    s_aLogs.push_back(ac);
}
static void MockInvalid() { s_nInvalid++; }

// ---- the entity/provider/subs ----
static const char* s_szCurName = "OldName";
static const char* s_szRec4 = "";
static uint64_t s_uSub2Val = 0x1111;
static uint64_t s_uSub8Val = 1;
static uint64_t s_uFlag1000 = 1000;

static void* Sub1Get78(void**) {
    return (void*)(uintptr_t)s_szCurName; }
static void Sub1Set80(void**, uint64_t v) {
    s_nSub1Set80++; s_uSub1Set80Val = v; }
static void* Sub2Get48(void**) { return (void*)s_uSub2Val; }
static void* Sub8Get48(void**) { return (void*)s_uSub8Val; }
static void Sub8SetD8(void**, uint32_t v) {
    s_nSub8SetD8++; s_uSub8SetD8Val = v; }
static void* Sub4Get78(void**) {
    return (void*)(uintptr_t)s_szRec4; }
static void* Sub0Get48(void**) { return (void*)0x77; }
static void* Sub2bGet48(void**) { return (void*)s_uFlag1000; }

static void* s_apSubs[16];
static void* MockEntResolve(void*, uint64_t idx) {
    assert(idx < 16);
    s_nEntResolve[idx]++;
    return s_apSubs[idx];
}
static void MockProvFlush38(void*, uint64_t a) {
    s_nProvFlush38++; s_uProvFlush38Arg = a; }

static void* s_apSub1Vt[32]; static void* s_apSub2Vt[16];
static void* s_apSub4Vt[16]; static void* s_apSub8Vt[32];
static void* s_apSub0Vt[16]; static void* s_apSub2bVt[16];
static void* s_apProvVt[16];
static void* s_apSubBox[16][4];
static void* s_apProvBox[1];

// ---- the log-record fixture ----
static void* s_apRecAnchorBox[1];
static void* s_apRecAnchorInner[8];
static uint8_t s_abRecHead[0x30];
static uint8_t s_abRecNode[0x30];
static void* s_apRecMap[8];
static void* s_apRecBox[1];
static void* s_apAttrBox[1];
static void* s_apAttrVt[4];
static void* s_apSub2bBox[4];

// ---- the acct host + the leagues map ----
static uint8_t s_abHost[0x70];
static void* s_apLgAnchorBox[1];
static void* s_apLgAnchorInner[8];
static uint8_t s_abLgHead[0x30];
static uint8_t s_abLgNode[0x30];
static void* s_apEntity[2];

// ---- the mgr fixture ----
static uint64_t s_uMgr63Ret = 0x1111;
static uint64_t s_uMgr93Ret = 1;
static uint64_t s_uMgr18Ret = 0x55;
static void* MgrVt1F8(void* p, uint64_t a) {
    (void)p; (void)a; return (void*)s_uMgr63Ret; }
static void* MgrVt2E8(void* p, uint64_t a) {
    (void)p; (void)a; return (void*)s_uMgr93Ret; }
static void* MgrVt18(void* p, uint64_t a, uint64_t b) {
    (void)p; s_nMgr18++;
    s_aMgr18[0] = a; s_aMgr18[1] = b;
    return (void*)s_uMgr18Ret; }
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
static void MockTail() { s_nTail++; }
// the gate (mgr vt+0x278): 0 -> the main switch
static char MockGate() { return 0; }

static void* s_apMgrVt[256];
static void* s_apMgrBox[1];

// ---- the logic fixture ----
static uint8_t s_abLogic[0x58];
static void* s_apLogicVt[232];
static void MockLogicVt(void*, uint64_t) {
    s_nUnexpected++; }

// ---- the string-manager seams ----
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

// the attr's own resolve (returns sub2b always)
static void* MockAttrResolve(void*, uint64_t idx) {
    assert(idx == 2);
    return s_apSub2bBox;
}

static void ResetCounters() {
    s_nUnexpected = 0; s_nInvalid = 0;
    memset(s_nEntResolve, 0, sizeof s_nEntResolve);
    s_nSub1Set80 = 0; s_nSub8SetD8 = 0;
    s_nProvFlush38 = 0; s_nMgr18 = 0; s_nMgr70 = 0;
    s_nMgr90 = 0; s_nMgr428 = 0; s_nTail = 0;
    s_aLogs.clear(); s_aStrFetch.clear();
    s_szCurName = "OldName"; s_szRec4 = "";
    s_uSub2Val = 0x1111; s_uSub8Val = 1;
    s_uFlag1000 = 1000; s_uMgr63Ret = 0x1111;
    s_uMgr93Ret = 1; s_uMgr18Ret = 0x55;
}

static void FillVt(void** vt, int n) {
    for (int i = 0; i < n; i++)
        vt[i] = (void*)MockLogicVt;   // trap
}

int main() {
    // ================= the fixtures =================
    FillVt(s_apSub1Vt, 32);
    s_apSub1Vt[15] = (void*)Sub1Get78;   // 0x78/8
    s_apSub1Vt[16] = (void*)Sub1Set80;   // 0x80/8
    FillVt(s_apSub2Vt, 16);
    s_apSub2Vt[9] = (void*)Sub2Get48;   // 0x48/8
    FillVt(s_apSub4Vt, 16);
    s_apSub4Vt[15] = (void*)Sub4Get78;   // 0x78/8
    FillVt(s_apSub8Vt, 32);
    s_apSub8Vt[9] = (void*)Sub8Get48;    // 0x48/8
    s_apSub8Vt[27] = (void*)Sub8SetD8;  // 0xd8/8
    FillVt(s_apSub0Vt, 16);
    s_apSub0Vt[9] = (void*)Sub0Get48;   // 0x48/8 (id)
    FillVt(s_apSub2bVt, 16);
    s_apSub2bVt[9] = (void*)Sub2bGet48; // 0x48/8 (flag)
    s_apSubBox[0][0] = s_apSub0Vt;
    s_apSubBox[1][0] = s_apSub1Vt;
    s_apSubBox[2][0] = s_apSub2Vt;
    s_apSubBox[4][0] = s_apSub4Vt;
    s_apSubBox[8][0] = s_apSub8Vt;
    s_apSubs[0] = s_apSubBox[0];
    s_apSubs[1] = s_apSubBox[1];
    s_apSubs[2] = s_apSubBox[2];
    s_apSubs[4] = s_apSubBox[4];
    s_apSubs[8] = s_apSubBox[8];
    // the provider
    FillVt(s_apProvVt, 16);
    s_apProvVt[2] = (void*)MockEntResolve;  // 0x10/8
    s_apProvVt[7] = (void*)MockProvFlush38; // 0x38/8
    s_apProvBox[0] = s_apProvVt;
    s_apEntity[1] = s_apProvBox;

    // the rec: rec[0] = the attr box; attr resolve(2)
    // -> the sub2b box
    s_apSub2bBox[0] = s_apSub2bVt;
    FillVt(s_apAttrVt, 4);
    s_apAttrVt[2] = (void*)MockAttrResolve;
    s_apAttrBox[0] = s_apAttrVt;
    s_apRecBox[0] = s_apAttrBox;

    // the log-record map (logic+0x18): anchor@0,
    // head@6, root = *(head+8)
    s_apRecAnchorInner[6] = (void*)0x4321;
    s_apRecAnchorBox[0] = s_apRecAnchorInner;
    memset(s_abRecHead, 0, sizeof s_abRecHead);
    memset(s_abRecNode, 0, sizeof s_abRecNode);
    *(char*)(s_abRecHead + 0x29) = 1;          // nil head
    *(void**)(s_abRecNode + 0) = s_abRecHead;  // left
    *(void**)(s_abRecNode + 8) = s_abRecHead;  // parent
    *(void**)(s_abRecNode + 0x10) = s_abRecHead; // right
    *(uint32_t*)(s_abRecNode + 0x18) = 0x42;  // key
    *(void**)(s_abRecNode + 0x20) = s_apRecBox; // val
    *(void**)(s_abRecHead + 8) = s_abRecNode;  // root
    s_apRecMap[0] = s_apRecAnchorBox;
    s_apRecMap[6] = s_abRecHead;

    // the acct host (logic+0x50): the leagues map at
    // +0x38 (anchor@+0x38, head@+0x68)
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
    *(void**)(s_abLgHead + 0) = s_abLgNode;   // leftmost
    *(void**)(s_abLgHead + 8) = s_abLgNode;   // root
    *(void**)(s_abHost + 0x38) = s_apLgAnchorBox;
    *(void**)(s_abHost + 0x68) = s_abLgHead;

    // the mgr (logic+8)
    FillVt(s_apMgrVt, 256);
    s_apMgrVt[1] = (void*)MockTail;           // tail
    s_apMgrVt[79] = (void*)MockGate;          // 0x278/8
    s_apMgrVt[3] = (void*)MgrVt18;            // 0x18/8
    s_apMgrVt[14] = (void*)MgrVt70;           // 0x70/8
    s_apMgrVt[18] = (void*)MgrVt90;           // 0x90/8
    s_apMgrVt[63] = (void*)MgrVt1F8;          // 0x1f8/8
    s_apMgrVt[93] = (void*)MgrVt2E8;          // 0x2e8/8
    s_apMgrVt[133] = (void*)MgrVt428;         // 0x428/8
    s_apMgrBox[0] = s_apMgrVt;

    // the logic
    FillVt(s_apLogicVt, 232);
    *(void**)(s_abLogic + 0) = s_apLogicVt;
    *(void**)(s_abLogic + 8) = s_apMgrBox;
    *(void**)(s_abLogic + 0x18) = s_apRecMap;
    *(void**)(s_abLogic + 0x50) = s_abHost;

    // the seams
    g_fnNameApplyLog = MockLog;
    g_fnNameApplyInvalid = MockInvalid;
    g_fnStringMgrInstance = MockStrMgrInstance;
    g_fnStringMgrGetStr = MockStrMgrGetStr;
    g_fnGetGameMgr = []() -> void* {
        return s_abLogic; };
    g_fn14174e3f0 = [](void*) -> int32_t {
        return 0x6666; };   // the owner == synId
    g_fnCStrPackerGetString = MockGetStr;

    // ============ D63-1: LeagueGetRecByIdx ============
    {
        ResetCounters();
        // null provider -> the log (0x142=322, ""/"")
        static void* apEntNull[2] = {0, 0};
        assert(LeagueGetRecByIdx((int64_t)apEntNull,
                                 8) == 0);
        assert(s_aLogs.size() == 1);
        assert(s_aLogs[0] == "||league.cpp|322");
        // the resolve idx rides through (THE fix)
        assert(LeagueGetRecByIdx(
            (int64_t)s_apEntity, 8) == 1);
        assert(s_nEntResolve[8] == 1);
        assert(LeagueGetRecByIdx(
            (int64_t)s_apEntity, 2) == 0x1111);
        assert(s_nEntResolve[2] == 1);
        assert(s_aLogs.size() == 1);
        printf("D63-1 the idx rides edx ok\n");
    }

    // ============ D63-2: LeagueGetRec4Str ============
    {
        ResetCounters();
        static void* apEntNull[2] = {0, 0};
        assert(LeagueGetRec4Str((int64_t)apEntNull)
            == 0);
        assert(s_aLogs.empty());   // SILENT
        const char* pc0 = (const char*)LeagueGetRec4Str(
            (int64_t)s_apEntity);          // the ptr
        assert(pc0 != 0 && strcmp(pc0, "") == 0);
        assert(s_nEntResolve[4] == 1);
        s_szRec4 = "X";
        const char* p = (const char*)LeagueGetRec4Str(
            (int64_t)s_apEntity);
        assert(p != 0 && strcmp(p, "X") == 0);
        printf("D63-2 the silent rec4 getter ok\n");
    }

    // ============ D63-3: LeagueSetFlagFlush ============
    {
        ResetCounters();
        static void* apEntNull[2] = {0, 0};
        LeagueSetFlagFlush((int64_t)apEntNull, 5, 1);
        assert(s_aLogs.size() == 1);
        assert(s_aLogs[0] ==
            "CHECK|m_pRec|league.cpp|431");
        // the set + the flush
        LeagueSetFlagFlush((int64_t)s_apEntity, 0, 1);
        assert(s_nSub8SetD8 == 1);
        assert(s_uSub8SetD8Val == 0);
        assert(s_nProvFlush38 == 1);
        assert(s_uProvFlush38Arg == 0);
        // flush 0 -> no provider call
        s_nProvFlush38 = 0;
        LeagueSetFlagFlush((int64_t)s_apEntity, 7, 0);
        assert(s_nSub8SetD8 == 2);
        assert(s_uSub8SetD8Val == 7);
        assert(s_nProvFlush38 == 0);
        printf("D63-3 the flag setter ok\n");
    }

    // ============ D63-4: RecFlagIs1000 ============
    {
        ResetCounters();
        static void* apRecNull[1] = {0};
        assert(RecFlagIs1000(apRecNull) == false);
        assert(s_aLogs.size() == 1);
        assert(s_aLogs[0] ==
            "IF_OK|m_pRec|synattr.cpp|1128");
        assert(RecFlagIs1000(s_apRecBox) == true);
        s_uFlag1000 = 999;
        assert(RecFlagIs1000(s_apRecBox) == false);
        printf("D63-4 the 1000 flag ok\n");
    }

    // ============ D63-5: ForbidNameFind ============
    {
        ResetCounters();
        // null name -> 0
        assert(ForbidNameFind(s_abHost, nullptr) == 0);
        // the walk: our entity is named "OldName"
        assert(ForbidNameFind(
            s_abHost, (char*)"OldName") ==
            (uint64_t)(uintptr_t)s_apEntity);
        assert(ForbidNameFind(
            s_abHost, (char*)"NewName") == 0);
        // 0x10-bound: names equal over the first 16
        // bytes match (strncmp stops at 0x10)
        s_szCurName = "OldNameOldNameOldName";  // 20
        assert(ForbidNameFind(
            s_abHost, (char*)"OldNameOldNameOldNa") ==
            (uint64_t)(uintptr_t)s_apEntity);
        // the full names differ past byte 15 but
        // strncmp stops at 0x10 -> still a match
        assert(ForbidNameFind(
            s_abHost, (char*)"OldNameOldNameOlXXXXXXX") ==
            (uint64_t)(uintptr_t)s_apEntity);
        // a byte-14 diff -> no match
        assert(ForbidNameFind(
            s_abHost, (char*)"OldNameOldNameXX") ==
            0);
        s_szCurName = "OldName";   // restore
        // no invalid-parameter hits
        assert(s_nInvalid == 0);
        // the empty map -> 0 (head points at itself)
        *(void**)(s_abLgHead + 0) = s_abLgHead;
        *(void**)(s_abLgHead + 8) = s_abLgHead;
        assert(ForbidNameFind(
            s_abHost, (char*)"OldName") == 0);
        assert(s_nInvalid == 0);
        // restore
        *(void**)(s_abLgHead + 0) = s_abLgNode;
        *(void**)(s_abLgHead + 8) = s_abLgNode;
        printf("D63-5 the name-taken walk ok\n");
    }

    // ============ D63-6: CStrFormat2 ============
    {
        struct LocalCStr { const void* vt;
                          std::string s; } st;
        st.vt = nullptr;
        new (&st.s) std::string();
        // null fmt -> nothing
        CStrFormat2(&st, nullptr, 1, 2);
        assert(st.s.empty());
        // the two staged args
        CStrFormat2(&st, "A=%s B=%s", (uint64_t)
            (uintptr_t)"xx", (uint64_t)(uintptr_t)"yy");
        assert(st.s == "A=xx B=yy");
        // the 0xfff truncation
        std::string sA(2500, 'a'), sB(2500, 'b');
        CStrFormat2(&st, "%s%s", (uint64_t)
            (uintptr_t)sA.c_str(), (uint64_t)
            (uintptr_t)sB.c_str());
        assert(st.s.size() == 0xfff - 1);
        printf("D63-6 the formatter ok\n");
    }

    // ============ D63-7: the flow gates ============
    {
        ResetCounters();
        // null name
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, nullptr) == 0);
        assert(s_nUnexpected == 0);
        // unknown league (empty map)
        *(void**)(s_abLgHead + 0) = s_abLgHead;
        *(void**)(s_abLgHead + 8) = s_abLgHead;
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        *(void**)(s_abLgHead + 0) = s_abLgNode;
        *(void**)(s_abLgHead + 8) = s_abLgNode;
        // sub8 == 0
        s_uSub8Val = 0;
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        assert(s_nMgr18 == 0);   // vt untouched yet
        // mismatch: 63 != sub2 — & ~0xff
        s_uSub8Val = 1;
        s_uMgr63Ret = 5; s_uSub2Val = 0x1ff;
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0x100);
        assert(s_nMgr18 == 0);
        // no log record
        s_uMgr63Ret = 0x1111; s_uSub2Val = 0x1111;
        *(void**)(s_abRecHead + 8) = s_abRecHead;
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        *(void**)(s_abRecHead + 8) = s_abRecNode;
        // the flag != 1000
        s_uFlag1000 = 999;
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        s_uFlag1000 = 1000;
        // 16-char name (strlen >= 0x10)
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666,
            (char*)"AAAAAAAAAAAAAAAA") == 0);
        // the mgr name check false
        s_uMgr93Ret = 0;
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 0);
        s_uMgr93Ret = 1;
        // forbidden (the entity's own name is taken)
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"OldName") == 0);
        assert(s_aStrFetch.size() == 1);
        assert(s_aStrFetch[0] ==
            "STR_FORBIDDEN_LEAGUE_NAME");
        assert(s_nMgr18 == 1);
        assert(s_aMgr18[0] == 0x42);
        assert(strcmp((const char*)
            (uintptr_t)s_aMgr18[1], "FRB!") == 0);
        assert(s_nMgr90 == 0);   // no broadcast
        assert(s_nUnexpected == 0);
        printf("D63-7 the gates ok\n");
    }

    // ============ D63-8: the success flow ============
    {
        ResetCounters();
        s_szRec4 = "";   // the current rec4 name empty
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 1);
        // the broadcast pack
        assert(s_aStrFetch.size() == 1);
        assert(s_aStrFetch[0] ==
            "STR_BROADCAST_NEW_LEAGUE_NAME");
        assert(s_nMgr90 == 1);
        assert(s_sMgr90Str == "cur=OldName got=NewName");
        assert(s_uMgr90Arg == 2000);
        // the rec writes
        assert(s_nSub1Set80 == 1);
        assert(strcmp((const char*)
            (uintptr_t)s_uSub1Set80Val, "NewName") == 0);
        assert(s_nSub8SetD8 == 1);
        assert(s_uSub8SetD8Val == 0);
        assert(s_nProvFlush38 == 2);   // set + flag
        // the vt+0x428 id grant
        assert(s_nMgr428 == 1);
        assert(s_aMgr428[0] == 0x77);
        assert(strcmp((const char*)
            (uintptr_t)s_aMgr428[1], "NewName") == 0);
        // the owner gate: e3f0 == synId + rec4 ""
        // -> vt+0x70(7, synId, 0, name)
        assert(s_nMgr70 == 1);
        assert(s_aMgr70[0] == 7);
        assert(s_aMgr70[1] == 0x6666);
        assert(s_aMgr70[2] == 0);
        assert(strcmp((const char*)
            (uintptr_t)s_aMgr70[3], "NewName") == 0);
        assert(s_nUnexpected == 0);
        // the rec4 non-empty variant: no vt+0x70
        ResetCounters();
        s_szRec4 = "X";
        assert(LeagueNameApply(s_abLogic, 0x42,
            0x6666, (char*)"NewName") == 1);
        assert(s_nMgr70 == 0);
        assert(s_nUnexpected == 0);
        printf("D63-8 the success flow ok\n");
    }

    // ============ D63-9: the E2E (case 6) ============
    {
        ResetCounters();
        s_szRec4 = "";
        // install the real body behind the D61 seam
        g_fn1417b0a40 = LeagueNameApply;
        static uint8_t abMsg[0x418];
        static uint8_t abPb[16];
        *(void**)(abMsg + 0x408) = abPb;
        *(uint16_t*)(abPb + 4) = 6;
        *(uint32_t*)(abPb + 6) = 0x6666;
        LeagueOptProcess(abMsg, 0x42);
        assert(*(uint16_t*)(abPb + 4) == 0x16);
        assert(s_nTail == 1);
        assert(s_nMgr90 == 1);
        assert(s_sMgr90Str ==
            "cur=OldName got=NewName");
        assert(s_nUnexpected == 0);
        printf("D63-9 the case-6 E2E ok\n");
    }

    printf("SYNDICATE_D63_OK: the league name apply\n");
    return 0;
}

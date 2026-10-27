// syndicate_d65_test.cpp — the league salary grant
// flow 1417b4310 + its 12 helpers. The header
// (SyndicateLeagueSalary.h) carries the discovery
// notes; this file asserts the literal gates, the
// six-arg charges, the mail struct, the TimeGet
// date math and the E2E case 0x27.
#include "modules/syndicate/src/SyndicateLeagueSalary.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"  // g_fnGetGameMgr
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateLeagueGmName.h"
#include "modules/syndicate/src/SyndicateLeagueMgr.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateLogRemove.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
#include "modules/syndicate/src/SyndicateModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace syndicate;

// ---- the recording state ----
static int s_nUnexpected, s_nInvalid;
static int s_nDbError; static std::string s_sDbErrMsg;
static uint32_t s_uDbErrCode;
static uint32_t s_uTimeGetSec = 1234567890;
static int s_nMgr28;  static std::string s_sMgr28Str;
static uint32_t s_uMgr28Color, s_uMgr28Actor;
static int s_nMgr118; static std::vector<std::string> s_aMails;
static int s_nMgr248; static char s_cMgr248Ret = 1;
static int s_nMgr290; static uint32_t s_uMgr290Ret = 500;
static int s_nMgr298; static int64_t s_nMgr298Delta;
static uint8_t s_bMgr298Byte;
static int s_nMgr500; static uint64_t s_aMgr500[6];
static int s_nMgr508; static uint64_t s_aMgr508[6];
static char s_cMgr508Ret = 0;
static int s_nMgr518; static uint32_t s_uMgr518Ret = 5;
static int s_nMgr140; static uint64_t s_aMgr140[6];
static char s_cMgr140Ret = 1;
static int s_nMgr238; static uint32_t s_uMgr238Ret = 5000;
static int s_nMgr200; static uint32_t s_uMgr200Ret = 0x99;
static int s_nMgr1D8; static uint64_t s_uMgr1D8Ret =
    (uint64_t)(uintptr_t)"Player";
static int s_nLogSave; static std::string s_sLogFmt;
static std::string s_sLogLine;
static int s_nTail; static void* s_pTailMsg;
static int s_nPackerDtor;
static int s_nRecResolve3, s_nRecResolve1b;
static int s_nRecPostSet; static uint32_t s_uRecPostSetVal;
static uint8_t s_bRecPostSetFlush;
static int s_nRecProvFlush;
static int s_nMemResolve3;
static int s_nMemSubGet20; static uint8_t s_cMemSubGet20Ret = 1;
static int s_nMemSubSetD8; static uint8_t s_bMemSubSetD8Val;
static int s_nMemProvFlush;
static int s_nSalResolve3, s_nSalResolve4;
static uint32_t s_uSalCountRet = 3, s_uSalAmountRet = 250;
static std::vector<std::string> s_aStrFetch;
static uint32_t s_uLogicSynId = 0x6666;

// ---- the sub mocks ----
static void* RecPostGet48(void**) { return (void*)1; }
static void RecPostSetB0(void**, uint64_t v) {
    s_nRecPostSet++; s_uRecPostSetVal = (uint32_t)v; }
static uint8_t MemSubGet20(void**) {
    s_nMemSubGet20++; return s_cMemSubGet20Ret; }
static void MemSubSetD8(void**, uint8_t v) {
    s_nMemSubSetD8++; s_bMemSubSetD8Val = v; }
static void MemProvFlush38(void*, uint64_t) {
    s_nMemProvFlush++; }
static void RecProvFlush38(void*, uint64_t) {
    s_nRecProvFlush++; }
static uint32_t SalCountGet40(void**) {
    return s_uSalCountRet; }
static uint32_t SalAmountGet40(void**) {
    return s_uSalAmountRet; }

// ---- the fixtures ----
static void* s_apRecPostVt[32];
static void* s_apRecPostBox[4];
static void* s_apRecProvVt[8];
static void* s_apRecProvBox[1];
static void* s_apRecBox[1];

static void* s_apMemSubVt[32];
static void* s_apMemSubBox[4];
static void* s_apMemProvVt[8];
static void* s_apMemProvBox[1];
static uint8_t s_abMemHead[0x38];
static uint8_t s_abMemNode[0x30];
static uint8_t s_abMemNodeB[0x30];
static void* s_apMemContInner[8];
static void* s_apMemContBox[1];
static uint8_t s_abEntity[0x90];

static void* s_apSalProvVt[8];
static void* s_apSalProvBox[1];
static void* s_apSalCountVt[16];
static void* s_apSalCountBox[4];
static void* s_apSalAmtVt[16];
static void* s_apSalAmtBox[4];
static uint8_t s_abRecHead[0x38];
static uint8_t s_abRecNode[0x30];
static void* s_apRecAnchorInner[8];
static void* s_apRecAnchorBox[1];
static uint8_t s_abSalHead[0x38];
static uint8_t s_abSalNode[0x30];
static void* s_apSalContInner[8];
static void* s_apSalContBox[1];

static uint8_t s_abHost[0x570];
static void* s_apLgAnchorBox[1];
static void* s_apLgAnchorInner[8];
static uint8_t s_abLgHead[0x38];
static uint8_t s_abLgNode[0x30];
static void* s_apRecMap[8];

static void* s_apMgrVt[256];
static void* s_apMgrBox[1];
static uint8_t s_abLogic[0x58];
static void* s_apLogicVt[232];

static void* s_apProvBox[1];   // the entity+8 provider

static void* MockRecResolve(void* p, uint64_t idx) {
    (void)p;
    if (idx == 0x1b) { s_nRecResolve1b++;
        return s_apRecPostBox; }
    s_nUnexpected++; return nullptr;
}
static void* MockMemResolve(void* p, uint64_t idx) {
    (void)p;
    if (idx == 3) { s_nMemResolve3++;
        return s_apMemSubBox; }
    s_nUnexpected++; return nullptr;
}
static void* MockSalResolve(void* p, uint64_t idx) {
    (void)p;
    if (idx == 3) { s_nSalResolve3++;
        return s_apSalCountBox; }
    if (idx == 4) { s_nSalResolve4++;
        return s_apSalAmtBox; }
    s_nUnexpected++; return nullptr;
}

// the mgr mocks
static void MgrVt28(void* p, uint32_t a, void* s,
                    uint32_t c) {
    (void)p; s_nMgr28++; s_uMgr28Actor = a;
    s_sMgr28Str = (const char*)s; s_uMgr28Color = c;
}
static void MgrVt118(void* p, void* mail) {
    (void)p; s_nMgr118++;
    char* m = (char*)mail;
    char ac[512];
    snprintf(ac, sizeof ac,
        "actor=%u sender=[%.10s] title=[%.15s] "
        "body=[%.25s] amt=%u six=%u",
        *(uint32_t*)(m + 0),
        m + 4, m + 0x24, m + 0x44,
        *(uint32_t*)(m + 0x14c),
        *(uint32_t*)(m + 0x154));
    s_aMails.push_back(ac);
}
static void* MgrVt248(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr248++;
    return (void*)(uintptr_t)s_cMgr248Ret;
}
static void* MgrVt290(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr290++;
    return (void*)(uintptr_t)s_uMgr290Ret;
}
static void MgrVt298(void* p, uint64_t a, int64_t d,
                     uint8_t b) {
    (void)p; (void)a; s_nMgr298++;
    s_nMgr298Delta = d; s_bMgr298Byte = b;
}
static void MgrVt500(void* p, uint64_t a, uint64_t b,
                     uint64_t c, uint64_t d, uint64_t e) {
    (void)p; s_nMgr500++;
    s_aMgr500[0]=a; s_aMgr500[1]=b; s_aMgr500[2]=c;
    s_aMgr500[3]=d; s_aMgr500[4]=e;
}
static void* MgrVt508(void* p, uint64_t a, uint64_t b,
                      uint64_t c, uint64_t d,
                      uint64_t e) {
    (void)p; s_nMgr508++;
    s_aMgr508[0]=a; s_aMgr508[1]=b; s_aMgr508[2]=c;
    s_aMgr508[3]=d; s_aMgr508[4]=e;
    return (void*)(uintptr_t)s_cMgr508Ret;
}
static void* MgrVt518(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr518++;
    return (void*)(uintptr_t)s_uMgr518Ret;
}
static void* MgrVt140(void* p, uint64_t a, uint64_t b,
                      uint64_t c, uint64_t d, uint64_t e) {
    (void)p; s_nMgr140++;
    s_aMgr140[0]=a; s_aMgr140[1]=b; s_aMgr140[2]=c;
    s_aMgr140[3]=d; s_aMgr140[4]=e;
    return (void*)(uintptr_t)s_cMgr140Ret;
}
static void* MgrVt238(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr238++;
    return (void*)(uintptr_t)s_uMgr238Ret;
}
static void* MgrVt200(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr200++;
    return (void*)(uintptr_t)s_uMgr200Ret;
}
static void* MgrVt1D8(void* p, uint64_t a) {
    (void)p; (void)a; s_nMgr1D8++;
    return (void*)s_uMgr1D8Ret;
}
static void MgrVt8Tail(void* p, uint64_t a, void* msg) {
    (void)p; s_nTail++; s_pTailMsg = msg;
    (void)a;
}
static char MockGate() { return 0; }  // pass

// the string mgr
static void* s_pStrMgr = (void*)0x77AA;
static void* MockStrMgrInstance() { return s_pStrMgr; }
static void* MockStrMgrGetStr(void* p, const char* k) {
    assert(p == s_pStrMgr);
    s_aStrFetch.push_back(k);
    if (!strcmp(k, "STR_SYSTEM_NAME"))
        return (void*)(uintptr_t)"SYSTEM";
    if (!strcmp(k, "STR_LEAGUE_TITLE_ORDER_SALARY"))
        return (void*)(uintptr_t)"SALARY_TITLE";
    if (!strcmp(k, "STR_LEAGUE_ORDER_SALARY_MAIL_CONTENT"))
        return (void*)(uintptr_t)"Salary %u/%u/%u";
    if (!strcmp(k, "STR_TRAINING_GONGFU_EMONEY_NOT_ENOUGH"))
        return (void*)(uintptr_t)"NO_EMONEY";
    return (void*)(uintptr_t)"?";
}
static void MockLogSave(const char* f, const char* fmt,
                        uint32_t a, const char* who,
                        uint32_t t, uint32_t p1,
                        uint32_t p2) {
    (void)f; s_nLogSave++; s_sLogFmt = fmt;
    char ac[256];
    snprintf(ac, sizeof ac, "%u|%s|%u|%u|%u",
             a, who, t, p1, p2);
    s_sLogLine = ac;
}
static void MockDbError(const char* m, uint32_t c) {
    s_nDbError++; s_sDbErrMsg = m; s_uDbErrCode = c;
}
static uint32_t MockTimeGet(uint32_t m) {
    assert(m == 3); return s_uTimeGetSec;
}
static void MockLogicVt(void*, uint64_t) {
    s_nUnexpected++;
}
static void* LogicVt510(void* p, uint64_t a) {
    (void)p; (void)a; return
        (void*)(uintptr_t)s_uLogicSynId;
}
static void FillVt(void** vt, int n) {
    for (int i = 0; i < n; i++)
        vt[i] = (void*)MockLogicVt;   // trap
}
static void ResetCounters() {
    s_nUnexpected=0; s_nInvalid=0; s_nDbError=0;
    s_nMgr28=0; s_nMgr118=0; s_nMgr248=0;
    s_nMgr290=0; s_nMgr298=0; s_nMgr500=0;
    s_nMgr508=0; s_nMgr518=0; s_nMgr140=0;
    s_nMgr238=0; s_nMgr200=0; s_nMgr1D8=0;
    s_nLogSave=0; s_nTail=0; s_nPackerDtor=0;
    s_nRecResolve3=0; s_nRecResolve1b=0;
    s_nRecPostSet=0; s_nRecProvFlush=0;
    s_nMemResolve3=0; s_nMemSubGet20=0;
    s_nMemSubSetD8=0; s_nMemProvFlush=0;
    s_nSalResolve3=0; s_nSalResolve4=0;
    s_aMails.clear(); s_aStrFetch.clear();
    s_cMgr248Ret=1; s_uMgr290Ret=500;
    s_cMgr508Ret=0; s_cMgr140Ret=1;
    s_uMgr238Ret=5000; s_cMemSubGet20Ret=1;
    s_uSalCountRet=3; s_uSalAmountRet=250;
    s_uTimeGetSec=1234567890;
    s_uLogicSynId=0x6666;
    memset(s_abHost + 0x2f8, 0, 0x18);  // configs
}

// wire ONE node into a map (head, node)
static void WireNode(uint8_t* pHead, uint8_t* pNode,
                     uint64_t uKey) {
    memset(pHead, 0, 0x38);
    memset(pNode, 0, 0x30);
    *(char*)(pHead + 0x29) = 1;         // isnil
    *(void**)(pNode + 0) = pHead;
    *(void**)(pNode + 8) = pHead;
    *(void**)(pNode + 0x10) = pHead;
    *(uint32_t*)(pNode + 0x18) = (uint32_t)uKey;
    *(void**)(pHead + 8) = pNode;       // the root
}

int main() {
    // ================= the fixtures =================
    // the rec chain (resolve 0x1b -> the post sub)
    FillVt(s_apRecPostVt, 32);
    s_apRecPostVt[9] = (void*)RecPostGet48;   // +0x48
    s_apRecPostVt[22] = (void*)RecPostSetB0;  // +0xb0
    s_apRecPostBox[0] = s_apRecPostVt;
    FillVt(s_apRecProvVt, 8);
    s_apRecProvVt[2] = (void*)MockRecResolve;
    s_apRecProvVt[7] = (void*)RecProvFlush38;
    s_apRecProvBox[0] = s_apRecProvVt;
    s_apRecBox[0] = s_apRecProvBox;
    WireNode(s_abMemHead, s_abMemNode, 0x42);
    *(void**)(s_abMemNode + 0x20) = s_apMemProvBox;
    // the second member node (0x77) on the right
    memset(s_abMemNodeB, 0, sizeof s_abMemNodeB);
    *(uint32_t*)(s_abMemNodeB + 0x18) = 0x77;
    *(void**)(s_abMemNodeB + 0) = s_abMemHead;
    *(void**)(s_abMemNodeB + 8) = s_abMemNode;
    *(void**)(s_abMemNodeB + 0x10) = s_abMemHead;
    *(void**)(s_abMemNodeB + 0x20) = s_apMemProvBox;
    *(void**)(s_abMemNode + 0x10) = s_abMemNodeB;
    s_apMemContInner[0] = s_abMemHead;
    s_apMemContBox[0] = s_apMemContInner;

    // the member provider/sub
    FillVt(s_apMemSubVt, 32);
    s_apMemSubVt[4] = (void*)MemSubGet20;   // +0x20
    s_apMemSubVt[27] = (void*)MemSubSetD8;  // +0xd8
    s_apMemSubBox[0] = s_apMemSubVt;
    FillVt(s_apMemProvVt, 8);
    s_apMemProvVt[2] = (void*)MockMemResolve;
    s_apMemProvVt[7] = (void*)MemProvFlush38;
    s_apMemProvBox[0] = s_apMemProvVt;

    // the entity: +8 provider, +0x58 cont, +0x88 head
    memset(s_abEntity, 0, sizeof s_abEntity);
    *(void**)(s_abEntity + 8) = s_apProvBox;
    *(void**)(s_abEntity + 0x58) = s_apMemContBox;
    *(void**)(s_abEntity + 0x88) = s_abMemHead;

    // the salary map (word key = the rank)
    WireNode(s_abSalHead, s_abSalNode, 5);
    *(void**)(s_abSalNode + 0x20) = s_apSalProvBox;
    s_apSalContInner[0] = s_abSalHead;
    s_apSalContBox[0] = s_apSalContInner;
    FillVt(s_apSalProvVt, 8);
    s_apSalProvVt[2] = (void*)MockSalResolve;
    s_apSalProvBox[0] = s_apSalProvVt;
    FillVt(s_apSalCountVt, 16);
    s_apSalCountVt[8] = (void*)SalCountGet40;
    s_apSalCountBox[0] = s_apSalCountVt;
    FillVt(s_apSalAmtVt, 16);
    s_apSalAmtVt[8] = (void*)SalAmountGet40;
    s_apSalAmtBox[0] = s_apSalAmtVt;

    // the rec map (key 0x42 -> s_apRecBox)
    WireNode(s_abRecHead, s_abRecNode, 0x42);
    *(void**)(s_abRecNode + 0x20) = s_apRecBox;
    s_apRecAnchorInner[6] = (void*)0x4321;
    s_apRecAnchorBox[0] = s_apRecAnchorInner;
    s_apRecMap[0] = s_apRecAnchorBox;
    s_apRecMap[6] = s_abRecHead;

    // the leagues map (key 0x6666 -> the entity)
    s_apLgAnchorInner[6] = (void*)0x8888;
    s_apLgAnchorBox[0] = s_apLgAnchorInner;
    WireNode(s_abLgHead, s_abLgNode, 0x6666);
    *(void**)(s_abLgNode + 0x20) = s_abEntity;

    // the host
    memset(s_abHost, 0, sizeof s_abHost);
    *(void**)(s_abHost + 0x38) = s_apLgAnchorBox;
    *(void**)(s_abHost + 0x68) = s_abLgHead;
    *(void**)(s_abHost + 0x538) = s_apSalContBox;
    *(void**)(s_abHost + 0x568) = s_abSalHead;

    // the mgr
    FillVt(s_apMgrVt, 256);
    s_apMgrVt[1] = (void*)MgrVt8Tail;
    s_apMgrVt[5] = (void*)MgrVt28;
    s_apMgrVt[35] = (void*)MgrVt118;   // 0x118/8
    s_apMgrVt[40] = (void*)MgrVt140;   // 0x140/8
    s_apMgrVt[59] = (void*)MgrVt1D8;   // 0x1d8/8
    s_apMgrVt[64] = (void*)MgrVt200;   // 0x200/8
    s_apMgrVt[71] = (void*)MgrVt238;   // 0x238/8
    s_apMgrVt[73] = (void*)MgrVt248;   // 0x248/8
    s_apMgrVt[79] = (void*)MockGate;
    s_apMgrVt[82] = (void*)MgrVt290;   // 0x290/8
    s_apMgrVt[83] = (void*)MgrVt298;   // 0x298/8
    s_apMgrVt[160] = (void*)MgrVt500;  // 0x500/8
    s_apMgrVt[161] = (void*)MgrVt508; // 0x508/8
    s_apMgrVt[163] = (void*)MgrVt518; // 0x518/8
    s_apMgrBox[0] = s_apMgrVt;

    // the logic
    FillVt(s_apLogicVt, 232);
    s_apLogicVt[162] = (void*)LogicVt510;  // 0x510/8
    *(void**)(s_abLogic + 0) = s_apLogicVt;
    *(void**)(s_abLogic + 8) = s_apMgrBox;
    *(void**)(s_abLogic + 0x18) = s_apRecMap;
    *(void**)(s_abLogic + 0x50) = s_abHost;

    // the seams
    g_fnStringMgrInstance = MockStrMgrInstance;
    g_fnStringMgrGetStr = MockStrMgrGetStr;
    g_fnGmNameLogSave = MockLogSave;
    g_fnSalaryDbError = MockDbError;
    g_fnSalaryTimeGet = MockTimeGet;
    g_fnSalaryInvalid = []() { s_nInvalid++; };
    g_fnCStrPackerDtor = [](void*) { s_nPackerDtor++; };
    g_fnTqCMsgInit = [](void*) {};
    g_fnCStrPackerCtor = [](void*) {};
    g_fnCStrPackerSetBuf = [](void*, char*, size_t,
                              bool) {};
    g_pTqCMsgVft = (void*)0x1001;
    g_pVtCMsgLeagueOpt = (void*)0x1002;

    // ======== D65-1: the config getters ========
    {
        *(uint32_t*)(s_abHost + 0x2f8) = 100;
        *(uint32_t*)(s_abHost + 0x2fc) = 300;
        *(uint32_t*)(s_abHost + 0x300) = 2;
        *(uint32_t*)(s_abHost + 0x304) = 3;
        *(uint32_t*)(s_abHost + 0x308) = 5;
        assert(HostContribCostGet(s_abHost) == 100);
        assert(HostEmoneyPriceGet(s_abHost) == 300);
        assert(HostFreeAmountGet(s_abHost) == 2);
        assert(HostContribAmountGet(s_abHost) == 3);
        assert(HostEmoneyAmountGet(s_abHost) == 5);
        printf("D65-1 the config fields ok\n");
    }

    // ======== D65-2: the walks ========
    {
        assert(SalaryCountGet(s_abHost, 5) == 3);
        assert(s_nSalResolve3 == 1);
        assert(SalaryAmountGet(s_abHost, 5) == 250);
        assert(s_nSalResolve4 == 1);
        assert(SalaryCountGet(s_abHost, 9) == 0);
        assert(SalaryAmountGet(s_abHost, 9) == 0);
        assert(LeagueMemberPostGet(s_abEntity, 0x42)
               == 1);
        assert(s_nMemResolve3 == 1);
        assert(LeagueMemberPostGet(s_abEntity, 0x99)
               == 0);
        assert(MemberRecPostGet(s_apRecBox) == 1);
        assert(s_nRecResolve1b == 1);
        ResetCounters();
        LeagueMemberPostSet(s_abEntity, 0x42, 2, 1);
        assert(s_nMemSubSetD8 == 1);
        assert(s_bMemSubSetD8Val == 2);
        assert(s_nMemProvFlush == 1);
        MemberRecPostSet(s_apRecBox, 2, 1);
        assert(s_nRecPostSet == 1);
        assert(s_uRecPostSetVal == 2);
        assert(s_nRecProvFlush == 1);
        assert(s_nUnexpected == 0);
        printf("D65-2 the walks ok\n");
    }

    // ======== D65-3: the gates ========
    {
        ResetCounters();
        // type 4: the rank read happens BEFORE the
        // switch (vt+0x518), then the bail
        LeagueSalaryGrant(s_abLogic, 0x42, 4);
        assert(s_nMgr518 == 1 && s_nUnexpected == 0);
        assert(s_nMgr508 == 0 && s_nDbError == 0);
        // synId 0 -> no entity -> bail (before 518)
        s_uLogicSynId = 0;
        LeagueSalaryGrant(s_abLogic, 0x42, 1);
        assert(s_nMgr518 == 1);
        s_uLogicSynId = 0x6666;
        // rec path, free>0, count==0 -> the bail
        // before 0x508
        *(uint32_t*)(s_abHost + 0x300) = 2;  // free
        s_uSalCountRet = 0;
        LeagueSalaryGrant(s_abLogic, 0x42, 1);
        assert(s_nMgr518 == 2);
        assert(s_nMgr508 == 0 && s_nMgr118 == 0);
        s_uSalCountRet = 3;
        // actor 0x77 -> no rec -> be40==0 -> bail
        // BEFORE the rank read
        s_cMemSubGet20Ret = 0;
        LeagueSalaryGrant(s_abLogic, 0x77, 1);
        assert(s_nMemSubGet20 == 1);
        assert(s_nMgr518 == 2);
        assert(s_nMgr508 == 0);
        s_cMemSubGet20Ret = 1;
        // actor 0x77 with be40==1 -> passes to the
        // free gate; free=0 -> the DBERROR
        memset(s_abHost + 0x300, 0, 4);
        LeagueSalaryGrant(s_abLogic, 0x77, 1);
        assert(s_nDbError == 1);
        assert(s_uDbErrCode == 0x249ff);
        assert(s_sDbErrMsg.find("free salary amount")
               != std::string::npos);
        *(uint32_t*)(s_abHost + 0x300) = 2;
        assert(s_nUnexpected == 0);
        printf("D65-3 the gates ok\n");
    }

    // ======== D65-4: the type cases ========
    {
        // -- type 2: amount <= 0 -> the DBERROR
        ResetCounters();
        memset(s_abHost + 0x304, 0, 4);
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        assert(s_nDbError == 1);
        assert(s_sDbErrMsg.find("contribution salary")
               != std::string::npos);
        assert(s_nMgr290 == 0);
        // -- cost > contrib -> bail
        *(uint32_t*)(s_abHost + 0x304) = 3;
        *(uint32_t*)(s_abHost + 0x2f8) = 600;
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        assert(s_nMgr290 == 1);
        assert(s_nMgr298 == 0);
        // -- cost <= 0 -> bail
        *(uint32_t*)(s_abHost + 0x2f8) = 0;
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        assert(s_nMgr298 == 0);
        // -- success: vt298(-cost, 1)
        *(uint32_t*)(s_abHost + 0x2f8) = 100;
        *(uint32_t*)(s_abHost + 0x300) = 2;
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        assert(s_nMgr298 == 1);
        assert(s_nMgr298Delta == -100);
        assert(s_bMgr298Byte == 1);
        // 3 mails (the contribution amount), single
        // reply flag 0
        assert(s_nMgr118 == 3);
        assert(s_nMgr508 == 1 && s_nMgr500 == 0);
        assert(s_nTail == 1);
        // (cumulative: the section-opening amount<=0
        //  call already logged one DBERROR)
        assert(s_nDbError == 1);
        // -- type 3: 0x248 false -> bail
        ResetCounters();
        s_cMgr248Ret = 0;
        LeagueSalaryGrant(s_abLogic, 0x42, 3);
        assert(s_nMgr248 == 1 && s_nMgr140 == 0);
        s_cMgr248Ret = 1;
        // -- amount <= 0 -> the emoney DBERROR
        memset(s_abHost + 0x308, 0, 4);
        LeagueSalaryGrant(s_abLogic, 0x42, 3);
        assert(s_nDbError == 1);
        assert(s_sDbErrMsg.find("emoney salary")
               != std::string::npos);
        *(uint32_t*)(s_abHost + 0x308) = 5;
        // -- price 0 -> bail
        memset(s_abHost + 0x2fc, 0, 4);
        LeagueSalaryGrant(s_abLogic, 0x42, 3);
        assert(s_nMgr140 == 0);
        *(uint32_t*)(s_abHost + 0x2fc) = 300;
        // -- price > emoney -> the STR send
        s_uMgr238Ret = 100;
        LeagueSalaryGrant(s_abLogic, 0x42, 3);
        assert(s_nMgr28 == 1);
        assert(s_sMgr28Str == "NO_EMONEY");
        assert(s_uMgr28Color == 0xffff00);
        assert(s_nMgr140 == 0);
        s_uMgr238Ret = 5000;
        // -- success: 0x140 with 0x49 + the 4318 log
        //    (esi = the FREE amount — set it > 0 so
        //     the flow reaches the mails)
        *(uint32_t*)(s_abHost + 0x300) = 2;
        LeagueSalaryGrant(s_abLogic, 0x42, 3);
        assert(s_nMgr140 == 1);
        assert(s_aMgr140[0] == 0x42);
        assert(s_aMgr140[1] == 0);
        assert(s_aMgr140[2] == 300);
        assert(s_aMgr140[3] == 0x49);   // D64 was 0x43
        assert(s_aMgr140[4] == 1);
        assert(s_nLogSave == 1);
        assert(s_sLogFmt ==
            "%lu\t%s\t%lu\t350\t4318\t%u\t%u\t1\t");
        assert(s_sLogLine == "66|Player|153|300|300");
        // the emoney loop count = the FREE amount (2)
        assert(s_nMgr118 == 2);
        assert(s_nUnexpected == 0);
        printf("D65-4 the type cases ok\n");
    }

    // ======== D65-5: the mail + the flag ========
    {
        ResetCounters();
        *(uint32_t*)(s_abHost + 0x300) = 1;  // 1 mail
        *(uint32_t*)(s_abHost + 0x304) = 1;
        *(uint32_t*)(s_abHost + 0x2f8) = 100;
        s_uSalAmountRet = 250;
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        // sec=1234567890 — the literal magic math:
        //   uDays = sec/10000 = 123456 (the magic
        //   0xd1b71759 shr 13 is div 10000, NOT
        //   86400), year = 123456+0x76c = 125356;
        //   mid = (sec - 1234560000)/100 = 78;
        //   rem = sec % 100 = 90
        assert(s_aMails.size() == 1);
        assert(s_aMails[0] ==
            "actor=66 sender=[SYSTEM] "
            "title=[SALARY_TITLE] "
            "body=[Salary 125356/78/90] "
            "amt=250 six=6");
        // the loop flag 0 rides the reply
        assert(s_nTail == 1);
        char* pcPb = *(char**)((char*)s_pTailMsg
                               + 0x408);
        assert(*(uint16_t*)(pcPb + 0) == 0x13);
        assert(*(uint16_t*)(pcPb + 2) == 0xa3e);
        assert(*(uint16_t*)(pcPb + 4) == 0x27);
        assert(*(uint32_t*)(pcPb + 6) == 0);
        assert(*(uint32_t*)(pcPb + 0xe) == 0);
        assert(*(uint32_t*)(pcPb + 10) == 0);
        assert(s_nPackerDtor == 1);
        // the single-shot: flag 1
        ResetCounters();
        s_cMgr508Ret = 1;
        *(uint32_t*)(s_abHost + 0x300) = 2;
        *(uint32_t*)(s_abHost + 0x304) = 1;
        *(uint32_t*)(s_abHost + 0x2f8) = 100;
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        // 0x508(mgr, actor, cnt, amount, byte1, word1)
        assert(s_nMgr508 == 1);
        assert(s_aMgr508[0] == 0x42);
        assert(s_aMgr508[1] == 3);   // the count
        assert(s_aMgr508[2] == 1);   // the amount
        assert(s_aMgr508[3] == 1 &&
               s_aMgr508[4] == 1);
        // 0x500(mgr, actor, cnt, 1, amount, byte1)
        assert(s_nMgr500 == 1);
        assert(s_aMgr500[0] == 0x42);
        assert(s_aMgr500[1] == 3);
        assert(s_aMgr500[2] == 1);   // edi = 1
        assert(s_aMgr500[3] == 1);   // amount
        assert(s_aMgr500[4] == 1);   // byte 1
        assert(s_aMails.size() == 0);
        assert(s_nTail == 1);
        pcPb = *(char**)((char*)s_pTailMsg + 0x408);
        assert(*(uint32_t*)(pcPb + 0xe) == 1);
        s_cMgr508Ret = 0;
        assert(s_nUnexpected == 0);
        printf("D65-5 the mail + flag ok\n");
    }

    // ======== D65-6: the record flag paths ========
    {
        ResetCounters();
        *(uint32_t*)(s_abHost + 0x304) = 2;
        *(uint32_t*)(s_abHost + 0x300) = 2;
        *(uint32_t*)(s_abHost + 0x2f8) = 100;
        LeagueSalaryGrant(s_abLogic, 0x42, 2);
        assert(s_nRecPostSet == 1);
        assert(s_uRecPostSetVal == 2);
        assert(s_nRecProvFlush == 1);
        assert(s_nMemSubSetD8 == 0);
        LeagueSalaryGrant(s_abLogic, 0x77, 2);
        assert(s_nRecPostSet == 1);   // unchanged
        assert(s_nMemSubSetD8 == 1);
        assert(s_bMemSubSetD8Val == 2);
        assert(s_nMemProvFlush == 1);
        assert(s_nUnexpected == 0);
        printf("D65-6 the record flag ok\n");
    }

    // ======== D65-7: E2E case 0x27 ========
    {
        ResetCounters();
        g_fn1417b4310 = LeagueSalaryGrant;
        g_fnGetGameMgr = []() -> void* {
            return s_abLogic; };
        static uint8_t abMsg[0x418];
        static uint8_t abPb[32];
        *(void**)(abMsg + 0x408) = abPb;
        *(uint16_t*)(abPb + 4) = 0x27;
        *(uint32_t*)(abPb + 0xe) = 2;   // the type
        *(uint32_t*)(s_abHost + 0x304) = 2;
        *(uint32_t*)(s_abHost + 0x300) = 2;
        *(uint32_t*)(s_abHost + 0x2f8) = 100;
        LeagueOptProcess(abMsg, 0x42);
        assert(s_nMgr298 == 1);
        assert(s_nTail == 1);
        assert(s_nUnexpected == 0);
        printf("D65-7 the case-0x27 E2E ok\n");
    }

    printf("SYNDICATE_D65_OK: the salary grant\n");
    return 0;
}

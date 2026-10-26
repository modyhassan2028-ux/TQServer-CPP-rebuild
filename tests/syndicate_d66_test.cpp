// tests/syndicate_d66_test.cpp — the 12-body batch unit
// Verbatim-behavior tests: exact call sequences, args,
// gates, jumptable edges, out-pointers, sign-extension.
#include "Exe/Dll/Syndicate/Port/SyndicateMsgProcess2.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace syndicate;

// ---- recorders ----
static int nCalls = 0;
static void Call(const char* tag) {
    printf("CALL %s\n", tag); nCalls++;
}
#define REC(name, ...) Call(name); (void)0

static std::string g_log;
static void Log5(const char* tag, const char* expr,
                 const char* file, uint32_t line) {
    char b[256];
    snprintf(b, sizeof b, "LOG5 %s|%s|%#x|%s", tag, expr,
             line, file);
    g_log = b; Call("log5");
}
static std::string g_invlog;
static void InvLog(const char* fmt, int32_t act) {
    char b[256];
    snprintf(b, sizeof b, "INVLOG %d|%s", act, fmt);
    g_invlog = b; Call("invlog");
}

// gates
static bool s_gate6f0 = true, s_gate710 = true;
static bool Gate6f0(void*, uint32_t) { Call("gate6f0"); return s_gate6f0; }
static bool Gate710(void*, uint32_t) { Call("gate710"); return s_gate710; }
static int32_t s_ac810ret = 0;
static int32_t Ac810(void*, uint32_t) { Call("ac810"); return s_ac810ret; }

// announce
static std::string g_announce;
static void Announce(void*, uint32_t a, const char* s,
                     void*) {
    char b[128]; snprintf(b, sizeof b, "ANN %u|%s", a, s);
    g_announce = b; Call("announce");
}

// string mgr
static void* StrMgrInstance() { Call("strmgr"); return (void*)0x1234; }
static void* StrMgrGetStr(void*, const char* k) {
    return (void*)(uintptr_t)k; // identity: the key rides
}

// deep bodies
static uint32_t g_ae640p = 0;
static void Ae640(void*, uint32_t a, uint32_t p) {
    g_ae640p = p; char b[64];
    snprintf(b, sizeof b, "ae640 %u %u", a, p); Call(b);
}
static uint8_t g_b4 = 0, g_b5 = 0;
static void Ae720(void*, uint32_t, uint8_t b4, uint8_t b5) {
    g_b4 = b4; g_b5 = b5; Call("ae720");
}
static uint32_t g_ae790p = 0;
static void Ae790(void*, uint32_t, uint32_t p) {
    g_ae790p = p; Call("ae790");
}
static void Ae9b0(void*, uint32_t) { Call("ae9b0"); }
static std::string g_af62, g_af67;
static void Af620(void*, uint32_t a, uint32_t p6, uint32_t pa) {
    char b[80]; snprintf(b, sizeof b, "af620 %u %u %u", a, p6, pa);
    g_af62 = b; Call(b);
}
static void Af670(void*, uint32_t a, uint32_t p6, uint32_t pa) {
    char b[80]; snprintf(b, sizeof b, "af670 %u %u %u", a, p6, pa);
    g_af67 = b; Call(b);
}
static std::string g_af6c;
static void Af6c0(void*, uint32_t a, uint32_t p6, uint32_t s16,
                  uint32_t u12, uint16_t w4) {
    char b[110];
    snprintf(b, sizeof b, "af6c0 %u %u %u %u %u", a, p6, s16, u12, w4);
    g_af6c = b; Call(b);
}
static void* SomeObj() { return (void*)0x77; }
static std::string g_410f0;
static void F410f0(void* o, uint32_t a, uint32_t pa) {
    char b[80];
    snprintf(b, sizeof b, "410f0 %p %u %u", o, a, pa);
    g_410f0 = b; Call(b);
}
static int32_t s_40fd0ret = 41;
static std::string g_40fd0;
static int32_t F40fd0(void* o, int32_t v) {
    char b[64]; snprintf(b, sizeof b, "40fd0 %p %d", o, v);
    g_40fd0 = b; Call(b); return s_40fd0ret;
}
static std::string g_41410;
static void F41410(void* o, uint32_t a) {
    char b[64];
    snprintf(b, sizeof b, "41410 %p %u", o, a);
    g_41410 = b; Call(b);
}
static void* D77d350() { Call("d77d350"); return (void*)0x88; }
static bool s_caa0 = true;
static std::string g_caa0;
static bool D77caa0(void* o, int32_t s16, int32_t u12) {
    char b[64];
    snprintf(b, sizeof b, "caa0 %p %d %d", o, s16, u12);
    g_caa0 = b; Call(b); return s_caa0;
}
static bool s_strcheck = true;
static bool AnnounceStrCheck(const char*, int32_t) {
    Call("strcheck"); return s_strcheck;
}
// token gates
static bool s_b2df0 = true;
static uint32_t g_z78 = 11, g_z70 = 22, g_z68 = 33;
static std::string g_b2df0;
static bool B2df0(void*, uint32_t a, uint32_t* p78,
                  uint32_t* p70, uint32_t* p68) {
    char b[96];
    snprintf(b, sizeof b, "b2df0 %u %p %p %p", a, (void*)p78,
             (void*)p70, (void*)p68);
    g_b2df0 = b;
    *p78 = g_z78; *p70 = g_z70; *p68 = g_z68; // the OUTs
    Call("b2df0"); return s_b2df0;
}
static uint32_t s_b2e20 = 77;
static uint32_t B2e20(void*) { Call("b2e20"); return s_b2e20; }

// ---- the fake logic + mgr vtables ----
static std::string g_vtcall;
static void VtAny(const char* tag) {
    if (!g_vtcall.empty()) g_vtcall += ";";
    g_vtcall += tag; Call(tag);
}
static void Vt5(void* l, uint32_t a) {
    char b[64]; snprintf(b, sizeof b, "vt5 %p %u", l, a);
    VtAny(b);
}
static void Vt125(void* l, uint32_t a, uint32_t p4,
    const char* p8, uint32_t x108, uint16_t x110,
    uint16_t x112, uint16_t x116, uint16_t x118,
    uint16_t x11a, uint16_t x114) {
    char b[230];
    snprintf(b, sizeof b,
        "vt125 %p %u %u %s %u %u %u %u %u %u %u", l, a, p4,
        p8, x108, x110, x112, x116, x118, x11a, x114);
    VtAny(b);
}
static void Vt126(void* l, uint32_t a, int64_t p) {
    char b[80];
    snprintf(b, sizeof b, "vt126 %p %u %lld", l, a,
             (long long)p);
    VtAny(b);
}
static void Vt127(void* l, uint32_t a, uint32_t p) {
    char b[80];
    snprintf(b, sizeof b, "vt127 %p %u %u", l, a, p);
    VtAny(b);
}
static void Vt128(void* l, uint32_t a) {
    char b[64]; snprintf(b, sizeof b, "vt128 %p %u", l, a);
    VtAny(b);
}
static std::string g_vt193, g_vt194;
static void Vt193(void* l, uint32_t a, uint32_t p444,
                  uint32_t p448) {
    char b[96];
    snprintf(b, sizeof b, "vt193 %p %u %u %u", l, a, p444, p448);
    g_vt193 = b; VtAny(b);
}
static void Vt194(void* l, uint32_t a, uint32_t p448,
    uint32_t e20, uint32_t z78, uint32_t z70, uint32_t z68) {
    char b[130];
    snprintf(b, sizeof b, "vt194 %p %u %u %u %u %u %u",
             l, a, p448, e20, z78, z70, z68);
    g_vt194 = b; VtAny(b);
}
static void* g_vtLogic[0x620 / 8];
static void* g_vtMgr[8];
static void* g_fakeMgrData[2] = {(void*)g_vtMgr, (void*)0};
static void* g_fakeLogicData[2] = {(void*)g_vtLogic,
                                   (void*)g_fakeMgrData};
static void MgrVt1(void* m, uint32_t a, void* msg) {
    char b[80];
    snprintf(b, sizeof b, "mgrvt1 %p %u %p", m, a, msg);
    VtAny(b);
}

static void* GetGameMgr() { return (void*)g_fakeLogicData; }

// ---- the msg fixtures ----
static uint8_t g_msg[0x460];
static uint8_t g_pb[0x130];
static void ResetMsg() {
    memset(g_msg, 0, sizeof g_msg);
    memset(g_pb, 0, sizeof g_pb);
    *(void**)(g_msg + 0x408) = g_pb;
}

static int g_fail = 0;
#define CHECK(cond, name) do { \
    if (cond) printf("  ok  %s\n", name); \
    else { printf("  FAIL %s\n", name); g_fail = 1; } \
} while (0)
#define SECT(n) printf("== %s ==\n", n)

int main() {
    // wire the seams
    g_fnGetGameMgr = GetGameMgr;
    g_fnMgrGateUserOnline = Gate6f0;
    g_fnMgrGate710 = Gate710;
    g_fnMgrAc810 = Ac810;
    g_fnAnnounce750 = Announce;
    g_fnB2df0 = B2df0;
    g_fnB2e20 = B2e20;
    g_fnAe640 = Ae640; g_fnAe720 = Ae720;
    g_fnAe790 = Ae790; g_fnAe9b0 = Ae9b0;
    g_fnAf620 = Af620; g_fnAf670 = Af670;
    g_fnAf6c0 = Af6c0;
    g_fnGetSomeObj41a30 = SomeObj;
    g_fn410f0 = F410f0; g_fn40fd0 = F40fd0;
    g_fn41410 = F41410;
    g_fnD77d350 = D77d350;
    g_fnD77caa0 = D77caa0;
    g_fnAnnounceStrCheck = AnnounceStrCheck;
    g_fnStringMgrInstance = StrMgrInstance;
    g_fnStringMgrGetStr = StrMgrGetStr;
    g_fnMsgBatchLog = Log5;
    g_fnInvalidActionLog = InvLog;
    g_vtLogic[0x28 / 8] = (void*)Vt5;
    g_vtLogic[0x3e8 / 8] = (void*)Vt125;
    g_vtLogic[0x3f0 / 8] = (void*)Vt126;
    g_vtLogic[0x3f8 / 8] = (void*)Vt127;
    g_vtLogic[0x400 / 8] = (void*)Vt128;
    g_vtLogic[0x608 / 8] = (void*)Vt193;
    g_vtLogic[0x610 / 8] = (void*)Vt194;
    g_vtMgr[1] = (void*)MgrVt1;

    // ---- 1. SynDomain ----
    SECT("syn-domain");
    s_gate6f0 = true;
    ResetMsg(); *(uint32_t*)(g_pb + 8) = 0xABCD;
    *(uint16_t*)(g_pb + 4) = 0;
    nCalls = 0; g_ae790p = 0;
    MsgSynDomainProcess(g_msg, 55);
    CHECK(nCalls == 2 && g_ae790p == 0xABCD,
          "ae790 called with PB+8");
    *(uint16_t*)(g_pb + 4) = 2;
    nCalls = 0; g_ae790p = 0;
    MsgSynDomainProcess(g_msg, 55);
    CHECK(nCalls == 1 && g_ae790p == 0, "PB+4!=0 -> silent");
    s_gate6f0 = false; nCalls = 0;
    MsgSynDomainProcess(g_msg, 55);
    CHECK(nCalls == 1, "gate fail -> gate only");
    s_gate6f0 = true;

    // ---- 2. SynProffer ----
    SECT("syn-proffer");
    ResetMsg(); nCalls = 0; g_vtcall.clear();
    MsgSynProfferProcess(g_msg, 7);
    CHECK(g_vtcall == "vt5 0x1ea417741 7" ||
          g_vtcall.find("vt5 ") == 0, "logic-vt[5] called");
    s_gate6f0 = false; nCalls = 0; g_vtcall.clear();
    MsgSynProfferProcess(g_msg, 7);
    CHECK(g_vtcall.empty(), "gate fail -> no vt call");
    s_gate6f0 = true;

    // ---- 3. AttrInfo ----
    SECT("syn-attrinfo");
    g_log.clear(); MsgSynAttrInfoProcess(g_msg, 1);
    CHECK(g_log.find("LOG5 ASSERT|") == 0 &&
          g_log.find("|0x79|") != std::string::npos,
          "the ASSERT quintuple (line 0x79)");

    // ---- 4. MemberInfo ----
    SECT("syn-memberinfo");
    ResetMsg(); nCalls = 0;
    MsgSynMemberInfoProcess(g_msg, 9);
    CHECK(nCalls == 1, "ae9b0 direct (no gate)");

    // ---- 5. MemberList ----
    SECT("syn-memberlist");
    ResetMsg(); *(uint32_t*)(g_pb + 8) = 0x5151;
    *(uint16_t*)(g_pb + 4) = 0; nCalls = 0; g_ae640p = 0;
    MsgSynMemberListProcess(g_msg, 4);
    CHECK(g_ae640p == 0x5151, "action 0 -> ae640(PB+8)");
    *(uint16_t*)(g_pb + 4) = 3; g_invlog.clear(); nCalls = 0;
    MsgSynMemberListProcess(g_msg, 4);
    CHECK(g_invlog == "INVLOG 3|CMsgSynMemberList::Process "
          "invalid action:%d", "invalid action log (3)");

    // ---- 6. BaseProffer ----
    SECT("syn-baseproffer");
    nCalls = 0; MsgSynBaseProfferProcess(g_msg, 1);
    CHECK(nCalls == 0, "the `ret 0` body");

    // ---- 7. ProfferRank ----
    SECT("syn-profferrank");
    ResetMsg(); g_pb[4] = 0xAB; g_pb[5] = 0xCD;
    g_b4 = g_b5 = 0;
    MsgSynProfferRankProcess(g_msg, 6);
    CHECK(g_b4 == 0xAB && g_b5 == 0xCD, "PB+4/PB+5 bytes");

    // ---- 8. SelfSynMemAwardRank ----
    SECT("self-awardrank");
    ResetMsg();
    g_log.clear(); MsgSelfSynMemAwardRankProcess(g_msg, 0);
    CHECK(g_log.find("|0xdf|") != std::string::npos,
          "actor 0 -> line 0xdf");
    s_gate6f0 = false; g_log.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_log.find("|0xe4|") != std::string::npos,
          "gate6f0 fail -> line 0xe4");
    s_gate6f0 = true; s_gate710 = false; g_announce.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_announce.find("ANN 5|STR_DIE") == 0,
          "gate710 fail -> STR_DIE announce");
    s_gate710 = true;
    // case 0 / 1
    ResetMsg(); *(uint32_t*)(g_pb + 6) = 0x66;
    *(uint32_t*)(g_pb + 0xa) = 0xAA;
    *(uint16_t*)(g_pb + 4) = 0; g_af62.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_af62 == "af620 5 0x66 0xaa" ||
          g_af62.find("af620 5 102 170") == 0, "case 0");
    *(uint16_t*)(g_pb + 4) = 1; g_af67.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_af67.find("af670 5") == 0, "case 1");
    // case 2 sign-ok true / false / sign-mismatch
    ResetMsg(); *(uint16_t*)(g_pb + 4) = 2;
    *(uint32_t*)(g_pb + 0x12) = 0x1E;
    *(int32_t*)(g_pb + 0x16) = -7;
    *(uint32_t*)(g_pb + 0x1a) = 0xFFFFFFFF; // the ext
    g_caa0.clear(); s_caa0 = false; g_af6c.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_caa0.find("caa0 0x88 -7 30") == 0 &&
          g_af6c.empty(), "case 2 caa0 false -> no af6c0");
    s_caa0 = true;
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_af6c.find("af6c0 5") == 0, "case 2 caa0 true");
    // sign mismatch (qword at +0x16 upper bits set)
    *(int32_t*)(g_pb + 0x16) = 1;
    *(uint32_t*)(g_pb + 0x1a) = 0x99; // upper dword != 0
    g_caa0.clear(); s_caa0 = true;
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_caa0.empty(), "sign-mismatch -> silent");
    // case 10
    ResetMsg(); *(uint16_t*)(g_pb + 4) = 10;
    *(uint32_t*)(g_pb + 0xa) = 0x71; g_410f0.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_410f0.find("410f0 0x77 5 113") == 0, "case 10");
    // case 0xb n==0
    ResetMsg(); *(uint16_t*)(g_pb + 4) = 0xb;
    s_ac810ret = 0; g_vtcall.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(*(uint32_t*)(g_pb + 0x12) == 0 &&
          g_vtcall.find("mgrvt1 ") == 0, "case b n=0");
    // case 0xb n!=0
    ResetMsg(); *(uint16_t*)(g_pb + 4) = 0xb;
    s_ac810ret = 9; g_40fd0.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_40fd0.find("40fd0 0x77 9") == 0 &&
          *(uint32_t*)(g_pb + 0x12) == 42, "case b n!=0 (+1)");
    // case 0xc both edges
    ResetMsg(); *(uint16_t*)(g_pb + 4) = 0xc;
    *(uint32_t*)(g_pb + 6) = 3; g_41410.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_41410.find("41410 0x77 5") == 0, "case c == 3");
    *(uint32_t*)(g_pb + 6) = 1; g_41410.clear();
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(g_41410.empty(), "case c != 3 -> silent");
    // case 9 (jumptable default)
    ResetMsg(); *(uint16_t*)(g_pb + 4) = 9; nCalls = 0;
    MsgSelfSynMemAwardRankProcess(g_msg, 5);
    CHECK(nCalls == 2, "case 9 -> gates only");

    // ---- 9. RecruitAdvertising ----
    SECT("recruit-adv");
    ResetMsg();
    s_gate6f0 = false; g_log.clear();
    MsgSynRecruitAdvertisingProcess(g_msg, 3);
    CHECK(g_log.find("|0x44|") != std::string::npos,
          "gate fail -> line 0x44");
    s_gate6f0 = true; s_gate710 = false; g_announce.clear();
    MsgSynRecruitAdvertisingProcess(g_msg, 3);
    CHECK(g_announce.find("ANN 3|STR_DIE") == 0,
          "gate710 fail -> STR_DIE");
    s_gate710 = true;
    strcpy((char*)(g_pb + 8), "hello"); // 5 chars
    s_strcheck = false; g_announce.clear();
    MsgSynRecruitAdvertisingProcess(g_msg, 3);
    CHECK(g_announce.find("ANN 3|STR_INVALID_CHARACTER") == 0,
          "strcheck fail -> STR_INVALID");
    s_strcheck = true;
    // 256-char name -> silent
    memset(g_pb + 8, 'x', 256); g_pb[8 + 256] = 0;
    g_vtcall.clear(); g_announce.clear();
    MsgSynRecruitAdvertisingProcess(g_msg, 3);
    CHECK(g_vtcall.empty() && g_announce.empty(),
          "len 256 -> SILENT (no announce, no vt)");
    // the 11-arg call
    strcpy((char*)(g_pb + 8), "hello");
    *(uint32_t*)(g_pb + 4) = 0x4444;
    *(uint32_t*)(g_pb + 0x108) = 0x111;
    *(uint16_t*)(g_pb + 0x110) = 0x1110;
    *(uint16_t*)(g_pb + 0x112) = 0x1112;
    *(uint16_t*)(g_pb + 0x116) = 0x1116;
    *(uint16_t*)(g_pb + 0x118) = 0x1118;
    *(uint16_t*)(g_pb + 0x11a) = 0x111a;
    *(uint16_t*)(g_pb + 0x114) = 0x1114;
    g_vtcall.clear();
    MsgSynRecruitAdvertisingProcess(g_msg, 3);
    CHECK(g_vtcall.find("vt125 ") == 0 &&
          g_vtcall.find(" 3 17476 hello 273 4368 4370 4374 4376 4378 4372") != std::string::npos,
          "the 11-arg vt125 call");

    // ---- 10. RAOpt ----
    SECT("recruit-advopt");
    ResetMsg(); s_gate710 = true;
    *(uint16_t*)(g_pb + 4) = 1; *(uint32_t*)(g_pb + 8) = 0x8888;
    g_vtcall.clear();
    MsgSynRecruitAdvertisingOptProcess(g_msg, 12);
    CHECK(g_vtcall.find("vt127 ") == 0 &&
          g_vtcall.find(" 12 34952") != std::string::npos,
          "case 1 -> vt127(PB+8)");
    *(uint16_t*)(g_pb + 4) = 2; g_vtcall.clear();
    MsgSynRecruitAdvertisingOptProcess(g_msg, 12);
    CHECK(g_vtcall.find("vt128 ") == 0, "case 2 -> vt128");
    *(uint16_t*)(g_pb + 4) = 5; g_invlog.clear();
    MsgSynRecruitAdvertisingOptProcess(g_msg, 12);
    CHECK(g_invlog.find("INVLOG 5|") == 0,
          "default -> the GBK invalid log");

    // ---- 11. RAList ----
    SECT("recruit-advlist");
    ResetMsg();
    *(int32_t*)(g_pb + 4) = -3; g_vtcall.clear();
    MsgSynRecruitAdvertisingListProcess(g_msg, 21);
    CHECK(g_vtcall.find("vt126 ") == 0 &&
          g_vtcall.find(" -3") != std::string::npos,
          "movsxd sign-extended");

    // ---- 12. LeagueToken ----
    SECT("league-token");
    ResetMsg(); nCalls = 0;
    MsgLeagueTokenProcess(g_msg, 0);
    CHECK(nCalls == 0, "actor 0 -> silent");
    *(int32_t*)(g_msg + 0x440) = 5; nCalls = 0;
    MsgLeagueTokenProcess(g_msg, 8);
    CHECK(nCalls == 0, "type 5 -> nothing");
    *(int32_t*)(g_msg + 0x440) = 0;
    s_b2df0 = false; nCalls = 0;
    MsgLeagueTokenProcess(g_msg, 8);
    CHECK(nCalls == 1, "b2df0 false -> stop");
    s_b2df0 = true;
    *(uint32_t*)(g_msg + 0x448) = 0x4848;
    g_vt194.clear(); g_b2df0.clear();
    MsgLeagueTokenProcess(g_msg, 8);
    CHECK(g_b2df0.find("b2df0 8 ") == 0 &&
          g_vt194.find("vt194 ") == 0 &&
          g_vt194.find(" 8 18504 77 11 22 33") != std::string::npos,
          "type 0 -> the 7-arg vt194");
    *(int32_t*)(g_msg + 0x440) = 2;
    *(uint32_t*)(g_msg + 0x444) = 0x4444;
    g_vt193.clear();
    MsgLeagueTokenProcess(g_msg, 8);
    CHECK(g_vt193.find("vt193 ") == 0 &&
          g_vt193.find(" 8 17476 18504") != std::string::npos,
          "type 2 -> vt193 tail");

    if (!g_fail) printf("D66-OK\n");
    else printf("D66-FAIL\n");
    return g_fail;
}

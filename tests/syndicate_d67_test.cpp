// tests/syndicate_d67_test.cpp — CMsgSyndicate::Process
// The 29-case dispatcher + the case-0x25 rank machine.
#include "Exe/Dll/Syndicate/Port/SyndicateMsgSyndicate.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMsgProcess2.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueSalary.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"
#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace syndicate;

static int g_fail = 0;
#define CHECK(cond, name) do { \
    if (cond) printf("  ok  %s\n", name); \
    else { printf("  FAIL %s\n", name); g_fail = 1; } \
} while (0)
#define SECT(n) printf("== %s ==\n", n)

// ---- recorders ----
static std::vector<std::string> g_calls;
static void C(const std::string& s) { g_calls.push_back(s); }

static bool s_g6f0 = true, s_g710 = true, s_g700 = false,
            s_g720 = true, s_g730 = false;
static bool G6f0(void*, uint32_t) { C("g6f0"); return s_g6f0; }
static bool G710(void*, uint32_t) { C("g710"); return s_g710; }
static bool G700(void*, uint32_t) { C("g700"); return s_g700; }
static bool G720(void*, uint32_t) { C("g720"); return s_g720; }
static bool G730(void*, uint32_t) { C("g730"); return s_g730; }
static int64_t s_7e0 = 100;
static int64_t A7e0(void*, uint32_t) { C("7e0"); return s_7e0; }
static uint32_t s_7f0 = 0;
static uint32_t A7f0(void*, const char* psz) {
    C(std::string("7f0|") + psz); return s_7f0; }
static int64_t s_800 = 0x555;
static int64_t A800(void*, uint32_t) { C("800"); return s_800; }
static void A820(void*, uint32_t a, uint32_t t) {
    char b[64]; snprintf(b, sizeof b, "820 %u %u", a, t);
    C(b); }
static void A9c0(void*, uint32_t a, int32_t t) {
    char b[64]; snprintf(b, sizeof b, "9c0 %u %d", a, t);
    C(b); }
static uint32_t s_430 = 42;
static uint32_t A430(void*, uint32_t) { C("430"); return s_430; }
static void Bad50(void*, uint32_t a, uint32_t t, void*) {
    char b[64]; snprintf(b, sizeof b, "bad50 %u %u", a, t);
    C(b); }
static void Bb0e0(void*, uint32_t a, uint32_t t) {
    char b[64]; snprintf(b, sizeof b, "bb0e0 %u %u", a, t);
    C(b); }
static void B7850(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "b7850 %u %s", a, s);
    C(b); }
static void Bb500(void*, uint32_t a, const char* s, uint32_t t) {
    char b[96];
    snprintf(b, sizeof b, "bb500 %u %s %u", a, s, t); C(b); }
static void Aab70(void*, uint32_t a, uint32_t p1,
                  uint32_t p2, uint32_t p3) {
    char b[96];
    snprintf(b, sizeof b, "aab70 %u %u %u %u", a, p1, p2, p3);
    C(b); }
static std::string g_announce;
static void Announce(void*, uint32_t a, const char* s, void* r9) {
    char b[128];
    snprintf(b, sizeof b, "ann %u %s %p", a, s, r9);
    g_announce = b; C(b); }
static void Acc80(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "acc80 %u %s", a, s);
    C(b); }
static void Acda0(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "acda0 %u %s", a, s);
    C(b); }
static void B7ae0(void*, uint32_t a, const char* s, int32_t r) {
    char b[96];
    snprintf(b, sizeof b, "b7ae0 %u %s %d", a, s, r); C(b); }
static void B7c10(void*, uint32_t u, uint32_t a, int32_t r) {
    char b[96];
    snprintf(b, sizeof b, "b7c10 %u %u %d", u, a, r); C(b); }
static void B7e70(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "b7e70 %u %s", a, s);
    C(b); }
static void Adeb0(void*, uint32_t a) {
    char b[32]; snprintf(b, sizeof b, "adeb0 %u", a); C(b); }
static void Ae130(void*, uint32_t a) {
    char b[32]; snprintf(b, sizeof b, "ae130 %u", a); C(b); }
static void Ae3a0(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "ae3a0 %u %s", a, s);
    C(b); }
static void Ad190(void*, uint32_t a, const char* s, uint32_t t) {
    char b[96];
    snprintf(b, sizeof b, "ad190 %u %s %u", a, s, t); C(b); }
static void Ad790(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "ad790 %u %s", a, s);
    C(b); }
static void Adbb0(void*, uint32_t a, const char* s) {
    char b[80]; snprintf(b, sizeof b, "adbb0 %u %s", a, s);
    C(b); }
static void Ae6b0(void*, uint32_t a, uint32_t t) {
    char b[64]; snprintf(b, sizeof b, "ae6b0 %u %u", a, t);
    C(b); }
// record-side
static uint32_t s_a50 = 3, s_ce0 = 7;
static uint32_t R1a50(void*, uint32_t r) {
    char b[48]; snprintf(b, sizeof b, "1a50 %u", r); C(b);
    return s_a50; }
static uint32_t R9ce0(void*, uint32_t r) {
    char b[48]; snprintf(b, sizeof b, "9ce0 %u", r); C(b);
    return s_ce0; }
static bool s_83e0 = true;
static bool R83e0(void*, int32_t x) {
    char b[48]; snprintf(b, sizeof b, "83e0 %d", x); C(b);
    return s_83e0; }
static bool s_9c700 = true;
static bool R9c700(void*, uint32_t a, uint32_t t) {
    char b[64];
    snprintf(b, sizeof b, "9c700 %u %u", a, t); C(b);
    return s_9c700; }
static bool s_9c820 = true;
static bool R9c820(void*, uint32_t a, uint32_t t) {
    char b[64];
    snprintf(b, sizeof b, "9c820 %u %u", a, t); C(b);
    return s_9c820; }
// packers
static uint32_t s_amount = 1;
static uint32_t PackAmount(void*) { C("amount"); return s_amount; }
static char g_packed[64][256];
static int g_npacked = 0;
static bool PackGetString(void*, int32_t, char* dst, int32_t n) {
    C("getstr");
    snprintf(dst, (size_t)n, "NAME%d", 1);
    return true;
}
static uint16_t s_psize = 6;
static std::vector<std::string> g_added;
static void PackAddString(void*, const char* s) {
    g_added.push_back(s); C(std::string("add|") + s); }
static uint32_t PackGetSize(void*) {
    C("getsize"); return s_psize; }
static void PackDtor(void* p) { (void)p; C("packdtor"); }
// str mgr / gates
static void* StrMgrInstance() { return (void*)0x999; }
static void* StrMgrGetStr(void*, const char* k) {
    return (void*)(uintptr_t)k; }
static bool s_strcheck = true;
static bool AnnounceStrCheck(const char*, int32_t) {
    C("strcheck"); return s_strcheck; }
static uint32_t s_ac810 = 5;
static int32_t Ac810(void*, uint32_t) { C("ac810");
    return (int32_t)s_ac810; }
static std::string g_log5;
static void Log5(const char* tag, const char* e,
                 const char* f, uint32_t l) {
    char b[160];
    snprintf(b, sizeof b, "log5 %s|%s|%#x|%s", tag, e, l, f);
    g_log5 = b; C(b); }
static std::string g_invlog;
static void InvActionLog(const char* f, int32_t a) {
    char b[96]; snprintf(b, sizeof b, "invlog %d|%s", a, f);
    g_invlog = b; C(b); }
static std::string g_ranklog;
static void IllegalRankLog(const char* f, int32_t r,
                           int32_t a) {
    char b[96];
    snprintf(b, sizeof b, "ranklog %d %d|%s", r, a, f);
    g_ranklog = b; C(b); }

uint32_t g_rankNow = 0;
static uint32_t VtRankReturn(void*, uint32_t) {
    return g_rankNow; }

// ---- the real member-map fixture (the REAL SynMemberFind
// chain runs on it — the D34 pattern, getters stripped) ----
static char s_inner[0x100];   // logic+0x10 -> this
static int g_nInvalid = 0;
static void LeagueInvalidNoop() { g_nInvalid++; }
static void InsertNode(uint32_t id, void* value) {
    uint64_t kv[2] = { id, (uint64_t)(uintptr_t)value };
    char* pmap = s_inner + 8;
    char* head = *(char**)(pmap + 0x30);
    char* attach = head;
    bool bLeft = true;
    if (*(char*)(*(char**)(head + 8) + 0x29) == '\0') {
        char* cur = *(char**)(head + 8);
        do {
            attach = cur;
            bLeft = id < *(uint32_t*)(cur + 0x18);
            cur = bLeft ? *(char**)cur : *(char**)(cur + 0x10);
        } while (*(char*)(cur + 0x29) == '\0');
    }
    char out[2][8];
    LeagueInsert(pmap, out[0], bLeft ? 1 : 0, attach, kv);
}
static void SeedMap() {
    memset(s_inner, 0, sizeof s_inner);
    LeagueMemberCtor(s_inner + 8);
    InsertNode(5, (void*)0x777);   // ac810() = 5
}

// ---- fake logic/mgr ----
static void* g_vtLogic[0x140];
static void* g_vtMgr[8];
static void* g_fakeMgr[2] = {(void*)g_vtMgr, (void*)0};
static void* g_fakeLogic[3] = {(void*)g_vtLogic,
                              (void*)g_fakeMgr,
                              (void*)s_inner};
static void* GetGameMgr() { return (void*)g_fakeLogic; }
static uint32_t s_vtRank = 0x348;
static void VtRank(void*, uint32_t a) {   // slot 31 (0xf8)
    char b[32]; snprintf(b, sizeof b, "vt31 %u", a); C(b);
}
static std::string g_vt3, g_vt29, g_vt32, g_vt36, g_vt39,
                    g_vt53, g_vt54, g_vt55, g_mgrvt1;
static void* s_ac7d0msg = nullptr;
static void MgrVt1(void* m, uint32_t a, void* msg) {
    s_ac7d0msg = msg;
    char b[64];
    snprintf(b, sizeof b, "mgrvt1 %p %u %p", m, a, msg);
    g_mgrvt1 = b; C(b); }
static void Vt3(void* l, uint32_t a) {
    char b[32]; snprintf(b, sizeof b, "vt3 %u", a);
    g_vt3 = b; C(b); }
static void Vt29(void* l, uint32_t a, const char* s,
                 uint32_t z) {
    char b[80];
    snprintf(b, sizeof b, "vt29 %u %s %u", a, s, z);
    g_vt29 = b; C(b); }
static void Vt32(void* l, uint32_t a) {
    char b[32]; snprintf(b, sizeof b, "vt32 %u", a);
    g_vt32 = b; C(b); }
static void Vt36(void* l, uint32_t a, uint32_t t) {
    char b[48]; snprintf(b, sizeof b, "vt36 %u %u", a, t);
    g_vt36 = b; C(b); }
static void Vt39(void* l, uint32_t a, uint32_t t) {
    char b[48]; snprintf(b, sizeof b, "vt39 %u %u", a, t);
    g_vt39 = b; C(b); }
static void Vt53(void* l, uint32_t a, const char* s) {
    char b[64]; snprintf(b, sizeof b, "vt53 %u %s", a, s);
    g_vt53 = b; C(b); }
static void Vt54(void* l, uint32_t a, const char* s) {
    char b[64]; snprintf(b, sizeof b, "vt54 %u %s", a, s);
    g_vt54 = b; C(b); }
static void Vt55(void* l, uint32_t a, const char* s) {
    char b[64]; snprintf(b, sizeof b, "vt55 %u %s", a, s);
    g_vt55 = b; C(b); }
// ---- msg fixture ----
static uint8_t g_msg[0x460];
static uint8_t g_pb[0x40];
static uint8_t g_packer[0x100];
static void ResetMsg(uint16_t uAction) {
    memset(g_msg, 0, sizeof g_msg);
    memset(g_pb, 0, sizeof g_pb);
    *(void**)(g_msg + 0x408) = g_pb;
    memcpy(g_msg + 0x410, g_packer, 0x50);
    *(uint16_t*)(g_pb + 4) = uAction;
    *(uint32_t*)(g_pb + 8) = 77;
}

static void WIRE() {
    g_fnGetGameMgr = GetGameMgr;
    g_fnMgrGateUserOnline = G6f0;
    g_fnMgrGate710 = G710;
    g_fnMgrAc810 = Ac810;
    g_fnAc700Gate = G700;
    g_fnAc720Gate = G720;
    g_fnAc730Gate = G730;
    g_fnAc7e0 = A7e0;
    g_fnAc7f0 = A7f0;
    g_fnAc800 = A800;
    g_fnAc820 = A820;
    g_fnAc9c0 = A9c0;
    g_fnAc430 = A430;
    g_fnBad50 = Bad50;
    g_fnBb0e0 = Bb0e0;
    g_fnB7850 = B7850;
    g_fnBb500 = Bb500;
    g_fnAab70 = Aab70;
    g_fnAnnounce750 = Announce;
    g_fnAcc80 = Acc80;
    g_fnAcda0 = Acda0;
    g_fnB7ae0 = B7ae0;
    g_fnB7c10 = B7c10;
    g_fnB7e70 = B7e70;
    g_fnAdeb0 = Adeb0;
    g_fnAe130 = Ae130;
    g_fnAe3a0 = Ae3a0;
    g_fnAd190 = Ad190;
    g_fnAd790 = Ad790;
    g_fnAdbb0 = Adbb0;
    g_fnAe6b0 = Ae6b0;
    g_fn791a50 = R1a50;
    g_fn797ce0 = R9ce0;
    g_fn7983e0 = R83e0;
    g_fn79c700 = R9c700;
    g_fn79c820 = R9c820;
    g_fnCStrPackerAddString = PackAddString;
    g_fnCStrPackerGetSize = PackGetSize;
    g_fnCStrPackerDtor = PackDtor;
    g_fnCStrPackerGetString = PackGetString;
    g_fnCStrPackerGetStrAmount = PackAmount;
    g_fnCStrPackerSetBuf = +[](void*, char*, size_t, bool){};
    g_fnCStrPackerCtor = +[](void*){};
    g_pTqCMsgVft = (void*)0x14182e368ull;
    g_pVtCMsgSyndicate = (void*)0x14183dc10ull;
    g_fnTqCMsgInit = +[](void*){};
    g_fnIllegalRankLog = IllegalRankLog;
    g_fnStringMgrInstance = StrMgrInstance;
    g_fnStringMgrGetStr = StrMgrGetStr;
    g_fnAnnounceStrCheck = AnnounceStrCheck;
    g_fnMsgBatchLog = Log5;
    g_fnInvalidActionLog = InvActionLog;
    g_vtLogic[0x18 / 8] = (void*)Vt3;
    g_vtLogic[0xe8 / 8] = (void*)Vt29;
    g_vtLogic[0xf8 / 8] = (void*)VtRank;
    g_vtLogic[0x100 / 8] = (void*)Vt32;
    g_vtLogic[0x120 / 8] = (void*)Vt36;
    g_vtLogic[0x138 / 8] = (void*)Vt39;
    g_vtLogic[0x1a8 / 8] = (void*)Vt53;
    g_vtLogic[0x1b0 / 8] = (void*)Vt54;
    g_vtLogic[0x1b8 / 8] = (void*)Vt55;
    g_vtMgr[1] = (void*)MgrVt1;
    g_fnLeagueInvalid = LeagueInvalidNoop;
    SeedMap();
}

static int HasCall(const char* sub) {
    for (auto& s : g_calls)
        if (s.find(sub) != std::string::npos) return 1;
    return 0;
}

int main() {
    WIRE();
    // ---- entry gates ----
    SECT("entry");
    ResetMsg(3); g_calls.clear();
    MsgSyndicateProcess(g_msg, 0);
    CHECK(g_log5.find("log5 CHECK|ID_NONE != idActor"
          "|0xb4|") == 0, "actor 0 -> CHECK line 0xb4");
    s_g6f0 = false; ResetMsg(3); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_calls.size() == 1 && g_calls[0] == "g6f0",
          "gate6f0 fail -> stop");
    s_g6f0 = true; s_g710 = false; g_calls.clear();
    g_announce.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_announce.find("ann 5 STR_DIE") == 0,
          "gate710 fail -> STR_DIE announce");
    s_g710 = true;
    // ac700 true && action != 6 -> end
    s_g700 = true; ResetMsg(7); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_calls.size() == 3, "ac700 true -> end");
    // ac700 true && action == 6 -> dispatch case 6
    ResetMsg(6); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("820 5 77"), "ac700+case6 -> ac820");
    s_g700 = false;

    // ---- the simple cases ----
    SECT("simple-cases");
    ResetMsg(1); g_calls.clear();
    *(uint32_t*)(g_pb + 8) = 0; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(!HasCall("bad50"), "case1 target=0 -> silent");
    *(uint32_t*)(g_pb + 8) = 5; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(!HasCall("bad50"), "case1 target==actor -> silent");
    *(uint32_t*)(g_pb + 8) = 77; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("bad50 5 77"), "case1 -> bad50");
    ResetMsg(2); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("bb0e0 5 77"), "case2 -> bb0e0");
    ResetMsg(3); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt32 == "vt32 5", "case3 -> vt32");
    ResetMsg(4); *(uint32_t*)(g_pb + 8) = 0; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(!HasCall("vt36"), "case4 target=0 -> silent");
    *(uint32_t*)(g_pb + 8) = 77; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt36 == "vt36 5 77", "case4 -> vt36");
    ResetMsg(7); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("b7850 5 NAME1"), "case7 -> b7850(str)");
    ResetMsg(8); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt54 == "vt54 5 NAME1", "case8 -> vt54");
    ResetMsg(9); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt53 == "vt53 5 NAME1", "case9 -> vt53");
    ResetMsg(10); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt55 == "vt55 5 NAME1", "case10 -> vt55");
    ResetMsg(0xb); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt39 == "vt39 5 77", "case b -> vt39");
    s_7e0 = 50; g_calls.clear();   // 77 > 50 -> jg end
    MsgSyndicateProcess(g_msg, 5);
    CHECK(!HasCall("vt39"), "case b 77>cap -> silent");
    s_7e0 = 100;
    ResetMsg(0xc); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt3 == "vt3 5", "case c -> vt3");
    ResetMsg(0x14); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("9c0 5 77"), "case 14 -> ac9c0");
    s_g730 = true; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(!HasCall("9c0"), "case 14 gate730 -> silent");
    s_g730 = false;
    ResetMsg(0x17); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("bb500 5 NAME1 77"), "case 17 -> bb500");
    ResetMsg(0x18); g_calls.clear();
    *(uint32_t*)(g_pb + 0xc) = 1;
    *(uint32_t*)(g_pb + 0x10) = 2;
    *(uint32_t*)(g_pb + 0x14) = 3;
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("aab70 5 1 2 3"), "case 18 -> aab70");
    ResetMsg(0x1f); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("adeb0 5"), "case 1f -> adeb0");
    ResetMsg(0x20); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("ae130 5"), "case 20 -> ae130");
    ResetMsg(0x21); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("ae3a0 5 NAME1"), "case 21 -> ae3a0");
    ResetMsg(0x22); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("ad190 5 NAME1 77"), "case 22 -> ad190");
    ResetMsg(0x23); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("ad790 5 NAME1"), "case 23 -> ad790");
    ResetMsg(0x24); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("adbb0 5 NAME1"), "case 24 -> adbb0");
    ResetMsg(0x26); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("ae6b0 5 77"), "case 26 -> ae6b0");
    ResetMsg(5); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_calls.size() == 3, "case 5 (default) -> gates only");
    ResetMsg(0x1e); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("b7e70 5 NAME1"), "case 1e -> b7e70");

    // ---- case 0x1b: the name checks ----
    SECT("case-1b");
    ResetMsg(0x1b); g_calls.clear(); g_announce.clear();
    s_strcheck = false;
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_announce.find("ann 5 STR_INVALID_CHARACTER") == 0
          && g_announce.find("0x100") != std::string::npos,
          "1b strcheck-fail -> STR_INVALID (r9=0x100)");
    s_strcheck = true; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("acc80 5 NAME1"), "1b strcheck-ok -> acc80");

    // ---- case 0x1c: the rank ladder ----
    SECT("case-1c");
    ResetMsg(0x1c);
    *(int32_t*)(g_pb + 8) = 0x1fe; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("b7ae0 5 NAME1 510"), "1c 0x1fe -> b7ae0");
    *(int32_t*)(g_pb + 8) = 0x263; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("b7ae0 5 NAME1 611"), "1c 0x263 -> b7ae0");
    *(int32_t*)(g_pb + 8) = 0x25a; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("b7ae0 5 NAME1 602"), "1c 0x25a -> b7ae0");
    *(int32_t*)(g_pb + 8) = 0x200; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_ranklog == "ranklog 512 28|Illegal rank:%d "
          "Action:%d", "1c 0x200 -> illegal log");
    *(int32_t*)(g_pb + 8) = 0x3de; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("acda0 5 NAME1"), "1c 0x3de -> acda0");
    *(int32_t*)(g_pb + 8) = 1000; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_vt29 == "vt29 5 NAME1 0", "1c 1000 -> vt29(..,0)");

    // ---- case 0x1d ----
    SECT("case-1d");
    ResetMsg(0x1d); s_7f0 = 88; g_calls.clear(); g_announce.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("7f0|NAME1"), "1d ac7f0(logic, BUF)");
    CHECK(g_announce.find("ann 88 STR_DENY_APPOINTMENT "
          "0x555") == 0, "1d deny -> ac750(uNew, ac800ret)");
    g_pb[0xc] = 1; *(int32_t*)(g_pb + 8) = 0x25a;
    g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("b7c10 88 5 602"), "1d rank -> b7c10");
    *(int32_t*)(g_pb + 8) = 0x201; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_ranklog.find("ranklog 513 29|") == 0,
          "1d bad rank -> illegal");
    s_7f0 = 0; g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_calls.size() == 6, "1d ac7f0=0 -> stop after");

    // ---- case 0x2d/0x30/0x32 ----
    SECT("backlist");
    ResetMsg(0x2d); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    // rank(0x348) != 0x3de -> silent
    CHECK(!HasCall("83e0"), "2d rank!=0x3de -> silent");
    g_calls.clear();
    ((uint32_t(*)(void*,uint32_t))0) // placeholder
    ;
    // force rank via vt: rerun with s_vtRank captured — the
    // VtRank stub returns void; emulate by direct call:
    // (the vt slot returns the rank — rewire for this case)
    ResetMsg(0x2d);
    g_vtLogic[0xf8 / 8] = (void*)+[](void*, uint32_t a) -> uint32_t {
        (void)a; return 0x3de; };
    g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(HasCall("83e0 0") && s_ac7d0msg == g_msg,
          "2d rank==0x3de -> 83e0 + ac7d0(MSG)");
    g_vtLogic[0xf8 / 8] = (void*)VtRank;
    ResetMsg(0x30); g_calls.clear(); g_announce.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_announce.find("ann 5 STR_SYNDICATE_BACKLIST_ADD"
          "_SUCCESS") == 0, "30 -> ADD_SUCCESS announce");
    ResetMsg(0x32); g_calls.clear(); g_announce.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_announce.find("ann 5 STR_SYNDICATE_BACKLIST_"
          "REMOVE_SUCCESS") == 0, "32 -> REMOVE_SUCCESS");
    s_9c700 = false; ResetMsg(0x30); g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_calls.size() == 5, "30 9c700-false -> silent");
    s_9c700 = true; s_9c820 = false; ResetMsg(0x32);
    g_calls.clear();
    MsgSyndicateProcess(g_msg, 5);
    CHECK(g_calls.size() == 5, "32 9c820-false -> silent");
    s_9c820 = true;

    // ---- case 0x25: the rank machine ----
    SECT("case-25");
    s_ac810 = 5;
    struct RV { uint32_t rank; };
    auto run25 = [&](uint32_t rank) {
        ResetMsg(0x25);
        g_vtLogic[0xf8 / 8] = (void*)VtRankReturn;
        g_rankNow = rank;
        g_calls.clear(); g_added.clear();
        MsgSyndicateProcess(g_msg, 5);
        g_vtLogic[0xf8 / 8] = (void*)VtRank;
    };
    run25(0x348);
    CHECK(g_added.size() == 1 && g_added[0] == "511 7 1 42 0",
          "25 0x348 pack (511,7,1,42,0)");
    run25(0x352);
    CHECK(g_added.size() == 1 && g_added[0] == "511 7 1 42 0",
          "25 0x352 same handler");
    run25(0x370);
    CHECK(g_added.size() == 1 && g_added[0] == "510 7 1 42 0",
          "25 0x370 pack (510,...)");
    run25(0x398);
    CHECK(g_added[0] == "610 7 1 42 0", "25 0x398 -> 0x262");
    run25(0x3d4);
    CHECK(g_added[0] == "611 7 1 42 0", "25 0x3d4 -> 0x263");
    run25(0x3de);
    CHECK(g_added[0] == "611 7 1 42 0", "25 0x3de -> 0x263");
    run25(1000);
    CHECK(g_added.size() == 7 &&
          g_added[0] == "1000 1 1 42 0",
          "25 1000 first literal pack");
    CHECK(g_added[1] == "990 7 3 42 0", "25 1000 0x3de");
    CHECK(g_added[2] == "980 7 3 42 650", "25 1000 0x3d4 c5");
    CHECK(g_added[3] == "880 7 3 42 320", "25 1000 0x370 c5");
    CHECK(g_added[4] == "840 7 3 42 270", "25 1000 0x348 c5");
    CHECK(g_added[5] == "680 7 3 42 100", "25 1000 0x2a8 c5");
    CHECK(g_added[6] == "602 7 3 42 0", "25 1000 0x25a c5");
    run25(0x349);
    CHECK(g_added.empty(), "25 rank-349 -> default silent");
    // the epilogue: ac7d0 + packdtor + vptr restores
    run25(0x348);
    CHECK(HasCall("mgrvt1") && s_ac7d0msg != g_msg &&
          s_ac7d0msg != nullptr && HasCall("packdtor"),
          "25 epilogue: ac7d0(stackMsg) + packdtor");
    s_ac810 = 999; run25(0x348);   // the map miss
    CHECK(g_added.empty() && !HasCall("mgrvt1"),
          "25 rec=0 (map miss) -> silent");
    s_ac810 = 5;

    if (!g_fail) printf("D67-OK\n");
    else printf("D67-FAIL\n");
    return g_fail;
}

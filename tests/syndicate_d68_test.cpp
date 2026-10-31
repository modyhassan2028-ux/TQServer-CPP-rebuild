// tests/syndicate_d68_test.cpp — the five deep bodies
// (the invite/notify family): SynTalkGate,
// MemberOverhead, LeagueInfoPush, InviteSynReply,
// InviteLeagueReply. All the raw-disasm facts: the
// hidden snprintf varargs, /1000 (magic 0x431bde83),
// the *1000000 rides, the 6-arg vt+0x410, the
// bAccept ride in b4d60's JOIN.
#include "modules/syndicate/src/SyndicateInviteNotify.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateLeagueMgr.h"
#include "modules/syndicate/src/SyndicateLeagueMember.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"
#include "modules/syndicate/src/SyndicateLeagueTree.h"
#include "modules/syndicate/src/SyndicateLeagueUsers.h"
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateModule.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

using namespace syndicate;

static int g_fail = 0;
#define CHECK(cond, name) do { \
    if (cond) printf("  ok  %s\n", name); \
    else { printf("  FAIL %s\n", name); g_fail = 1; } \
} while (0)
#define SECT(n) printf("== %s ==\n", n)

// ================= the recorders =================
static std::vector<std::string> g_calls;
static void C(const std::string& s) { g_calls.push_back(s); }
// A recording prints the pointer it was handed, and a raw pointer's hex digits can
// happen to spell a call name: 0x55af7d5cb6c0 contains b6c0. Pointer text is not a
// call, so it is masked out before a name is looked for.
static std::string MaskPointers(const std::string& strIn) {
    std::string strOut;
    for (size_t i = 0; i < strIn.size(); ) {
        if (strIn[i] == '0' && i + 2 < strIn.size() &&
            (strIn[i + 1] == 'x' || strIn[i + 1] == 'X') &&
            std::isxdigit((unsigned char)strIn[i + 2])) {
            i += 2;
            while (i < strIn.size() &&
                   std::isxdigit((unsigned char)strIn[i])) ++i;
            strOut += "<ptr>";
        } else {
            strOut += strIn[i++];
        }
    }
    return strOut;
}
static bool Has(const std::string& s) {
    for (auto& x : g_calls)
        if (MaskPointers(x).find(s) != std::string::npos) return true;
    return false;
}
static void Reset() { g_calls.clear(); }

// ---- the fake logic / mgr / host objects ----
static void* g_vtLogic[0x120];
static void* g_vtMgr[0x180];
static void* g_fakeMgr[2];
static void* g_fakeHost[0x60 / 8];
static char s_inner[0x100];       // logic+0x10: member map
static char s_lgA[0x120];         // the league rec
static char s_lgTgt[0x40];        // the target "league"
static void* g_fakeLogic[11];     // +0 vt, +8 mgr,
                                  // +0x10 inner, +0x50 host

// ---------- the member map (LeagueMemberLookup) ----------
static int g_nInvalid = 0;
static void LeagueInvalidNoop() { ++g_nInvalid; }
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

// ---------- the host map (MgrLeagueFind) — D37 kit ----------
static void MkMap(char* pOwner, int off) {
    char* anchor = (char*)calloc(1, 8);
    *(char**)anchor = pOwner + off;
    LeagueMemberCtor(pOwner + off);
    *(char**)(pOwner + off) = anchor;
}
static void MgrInsertLeague(uint32_t uId, char* pLg) {
    uint64_t pair[2] = { uId, (uint64_t)(uintptr_t)pLg };
    int64_t out[3];
    UsersInsertUnique((void*)(g_fakeHost + 7), (void*)out,
                      (uint32_t*)pair);   // host+0x38
}
// the accessor provider kit
struct FakeAccRec {
    void* vft; uint64_t uVal[8]; uint64_t uIdx;
};
struct FakeProv { void* vft; FakeAccRec* recs[16]; };
static void* g_pAccVt[24];
static void* g_pAccProvVt[8];
static uint64_t FakeAccGet40(void* s) {
    return ((FakeAccRec*)s)->uVal[0]; }
static uint64_t FakeAccGet48(void* s) {
    return ((FakeAccRec*)s)->uVal[1]; }
static uint64_t FakeAccGet78(void* s) {
    return ((FakeAccRec*)s)->uVal[2]; }
static void FakeAccSet80(void* s, uint64_t v) {
    ((FakeAccRec*)s)->uVal[3] = v; }
static int g_nAccFlush = 0;
static void FakeAccFlush(void*, uint64_t) { ++g_nAccFlush; }
static void* FakeAccResolve(void* s, uint64_t idx) {
    FakeProv* pr = (FakeProv*)s;
    assert(idx < 16 && pr->recs[idx]);
    return pr->recs[idx];
}
static FakeProv* MkProv(uint64_t uLid) {
    FakeProv* pr = (FakeProv*)calloc(1, sizeof(FakeProv));
    pr->vft = g_pAccProvVt;
    for (int i = 0; i < 16; ++i) {
        FakeAccRec* r = (FakeAccRec*)calloc(1,
            sizeof(FakeAccRec));
        r->vft = g_pAccVt; r->uIdx = i;
        pr->recs[i] = r;
    }
    pr->recs[0]->uVal[1] = uLid;   // LeagueGetId
    pr->recs[1]->uVal[2] = 0x4444; // LeagueGetRec1Str
    return pr;
}
static void BuildLeague(char* pEnt, uint32_t uLeader,
                        void* pProv) {
    memset(pEnt, 0, 0x120);
    MkMap(pEnt, 0x58);
    MkMap(pEnt, 0x98);
    MkMap(pEnt, 0xd8);
    *(void**)(pEnt + 8) = pProv;
    *(uint32_t*)(pEnt + 0x10) = uLeader;
}

// ============ the seam stubs ============
static uint32_t s_talkLid = 0;   // b0370 ret
static uint32_t S1417b0370(void*, uint32_t id) {
    C("b0370"); return s_talkLid ? s_talkLid : id; }
static bool s_f020 = true;
static bool S14174f020(void*, uint32_t, void*) {
    C("f020"); return s_f020; }
static void S141745580(void* rec, void* out) {
    *(void**)out = rec; C("5580"); }
static uint32_t s_5370 = 77;
static uint32_t S1417b5370(void*, uint32_t, void*) {
    C("5370"); return s_5370; }
static uint32_t s_6b60 = 5000000, s_6d10 = 1000;
static void S141766b60(void*, uint32_t, void* out,
                       void* buf, uint32_t cap) {
    *(uint32_t*)out = s_6b60;
    memset(buf, 0, cap);
    *(uint32_t*)buf = 0xABCD;
    C("6b60"); }
static void S141766d10(void*, uint32_t, void* out,
                       void* buf, uint32_t cap) {
    *(uint32_t*)out = s_6d10;
    memset(buf, 0, cap);
    C("6d10"); }
static int g_n61c0 = 0;
static bool s_b61c0 = true;
static std::string g_61c0;
static bool S1417d61c0(void*, const void*, uint32_t r,
    uint32_t a, uint32_t b, const char* s1,
    const char* s2) {
    ++g_n61c0;
    char t[256];
    snprintf(t, sizeof t, "61c0 r=%u a=%u b=%u s1=%s "
        "s2=%s", r, a, b, s1, s2);
    g_61c0 = t; C(t);
    return s_b61c0;
}
static bool s_6790 = true;
static bool S1417d6790(void*, uint32_t t, uint32_t a,
                       uint32_t b, uint32_t c) {
    char t2[64]; snprintf(t2, sizeof t2,
        "6790 %u %u %u %u", t, a, b, c); C(t2);
    return s_6790; }
static bool s_6820 = true;
static bool S1417d6820(void*, uint32_t t, const char* s,
                       uint32_t a, uint32_t act,
                       uint32_t b) {
    char t2[96]; snprintf(t2, sizeof t2,
        "6820 %u %s %u %u %u", t, s, a, act, b); C(t2);
    return s_6820; }
static int g_n61c0Ctor = 0, g_n61c0Dtor = 0;
static void S1417d6110(void*) { ++g_n61c0Ctor; }
static void S1417d6160(void*) { ++g_n61c0Dtor; }
static int g_n66Ctor = 0, g_n66Dtor = 0;
static void S1417d66c0(void*) { ++g_n66Dtor; }
static int g_n99Ctor = 0, g_n99Dtor = 0;
static void S1417d9900(void*) { ++g_n99Ctor; }
static void S1417d9950(void*) { ++g_n99Dtor; }
static uint32_t s_e3f0 = 3;
static uint32_t S14174e3f0(void*) { return s_e3f0; }
static uint32_t s_b6c0 = 1;
static bool S14174b6c0(void*, uint32_t, void*) {
    C("b6c0"); return s_b6c0; }
static uint32_t s_e7e0 = 66;
static uint32_t S14174e7e0(void*) { C("e7e0");
    return s_e7e0; }
static std::string g_e7f0;
static void S14174e7f0(void*, uint32_t t, uint32_t id,
                       uint8_t one, uint16_t eight) {
    char t2[96]; snprintf(t2, sizeof t2,
        "e7f0 %u %u %u %u", t, id, one, eight);
    g_e7f0 = t2; C(t2); }
static bool s_63920 = true;
static bool S141763920(void*, uint32_t) { C("63920");
    return s_63920; }
static std::string g_ca70;
static void S14176ca70(void*, uint32_t id,
                       uint32_t tgt, uint32_t a) {
    char t2[96]; snprintf(t2, sizeof t2,
        "ca70 %u %u %u", id, tgt, a);
    g_ca70 = t2; C(t2); }
static uint32_t s_f2d0 = 0;
static uint32_t S14178f2d0(void* lg) {
    C("f2d0"); return s_f2d0 ? s_f2d0 : (uint32_t)(uintptr_t)lg; }
static int32_t S14178f470(void*) { C("f470"); return 0; }
static int32_t s_90390 = 0;
static int32_t S141790390(void*) { C("90390");
    return s_90390; }
static std::string g_903d0;
static char S1417903d0(void* lg, uint32_t id) {
    char t2[64]; snprintf(t2, sizeof t2, "903d0 %u",
        id); g_903d0 = t2; C(t2); return 0; }
static std::string g_dcd0;
static void S14174dcd0(void*, uint32_t a) {
    char t2[64]; snprintf(t2, sizeof t2, "dcd0 %u", a);
    g_dcd0 = t2; C(t2); }
static std::string g_strcopy;
static void TqStrCopy(char* d, const char* s, size_t c) {
    snprintf(d, c, "%s", s ? s : "");
    char t2[64]; snprintf(t2, sizeof t2, "strcopy %zu",
        c); g_strcopy = t2; C(t2); }
static std::string g_ann750;
static void Ann750(void* l, uint32_t a, const char* s,
                   void* r9) {
    char t2[96]; snprintf(t2, sizeof t2,
        "ann750 %u %s %p", a, s, r9);
    g_ann750 = t2; C(t2); }
static bool s_strcheck = true;
static bool StrCheck(const char* s, int) { C("strcheck");
    (void)s; return s_strcheck; }
static void* StrMgrInst() { return (void*)0x999; }
static std::string StrMgrGetStr(void*, const char* k) {
    C(std::string("getstr ") + k);
    if (!strcmp(k, "STR_INVALID_CHARACTER")) return "INVALID";
    if (!strcmp(k, "STR_LEAGUE_REFUSE_INVITE_SYN"))
        return "REFUSE=%s";
    if (!strcmp(k, "STR_LEAGUE_INVITE_LEAVE_SOON"))
        return "SOON=%d";
    if (!strcmp(k, "STR_LEAGUE_INVITE_JOIN_LEAGUE"))
        return "JOIN=%d|%s";
    if (!strcmp(k, "STR_SYN_JOIN_LEAGUE"))
        return "SYN=%d|%d";
    if (!strcmp(k, "STR_LEAGUE_JOIN_SUCESSS"))
        return "WIN=%s|%d";
    return "?";
}
static std::string g_log;
static void BatchLog(const char* tag, const char* expr,
                     const char* file, uint32_t line) {
    char t2[128]; snprintf(t2, sizeof t2,
        "log %s %d", tag, line); g_log = t2; C(t2);
    (void)expr; (void)file; }
// the ctor seams (CMsgLeagueOpt)
static void MockCMsgInit(void*) {}
static void MockPackerCtor(void*) {}
static void MockPackerSetBuf(void*, char*, size_t, bool) {}
static void* g_pVtCMsgLeagueOptFake = (void*)0x777;
void* g_pVtCMsgLeagueOpt = (void*)g_pVtCMsgLeagueOptFake;

// ============ the fake mgr-vt recorders ============
static bool s_g278a = false;      // 1st (stale edx)
static bool s_g278b = false;      // 2nd (param)
static uint32_t s_4a8 = 555;
static std::map<uint32_t,uint32_t> s_510;  // logic-vt
static bool s_g2d0 = true;
static bool s_g268 = true;
static bool s_g280 = false;
static uint32_t s_1f8 = 888;
static std::map<uint32_t,const char*> s_1d8;
static uint32_t s_3f0 = 3;
static std::string g_vt188, g_vt180, g_vt710,
                   g_vt028, g_vt090, g_vt058, g_vt0410,
                   g_vt468, g_vt470;
static const char* s_468name = "CTY";
static const char* s_470name = "MEM";

// ONE vt slot serves both 278 calls: the stale-edx one
// (our convention x=0) and the (mgr, target) one.
static bool M278(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m278 %u", x);
    C(t); (void)m;
    return (x == 0) ? s_g278a : s_g278b; }
static uint32_t M4a8(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m4a8 %u", x);
    C(t); (void)m; return s_4a8; }
static bool M2d0(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m2d0 %u", x);
    C(t); (void)m; return s_g2d0; }
static bool M268(void* m, uint32_t x) {
    C("m268"); (void)m; (void)x; return s_g268; }
static bool M280(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m280 %u", x);
    C(t); (void)m; return s_g280; }
static uint32_t M1f8(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m1f8 %u", x);
    C(t); (void)m; return s_1f8; }
static const char* M1d8(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m1d8 %u", x);
    C(t); (void)m;
    auto it = s_1d8.find(x);
    return it != s_1d8.end() ? it->second : "NAME"; }
static uint32_t M3f0(void* m) {
    C("m3f0"); (void)m; return s_3f0; }
static void M188(void* m, uint32_t a, uint32_t b,
                 uint32_t c) {
    char t[80]; snprintf(t, sizeof t,
        "m188 %u %u %u", a, b, c); g_vt188 = t; C(t);
    (void)m; }
static bool M180(void* m, uint32_t a, uint32_t b,
                 uint32_t c) {
    char t[80]; snprintf(t, sizeof t,
        "m180 %u %u %u", a, b, c); g_vt180 = t; C(t);
    (void)m; return true; }
static void M710(void* l, void* lg, uint32_t a,
                 uint32_t b) {
    char t[96]; snprintf(t, sizeof t,
        "m710 %p %u %u", lg, a, b); g_vt710 = t; C(t);
    (void)l; }
static void M028(void* m, uint32_t a, const char* s,
                 uint32_t col) {
    char t[160]; snprintf(t, sizeof t,
        "m028 %u %s %x", a, s, col); g_vt028 = t; C(t);
    (void)m; }
static void M090(void* m, const char* s, uint32_t col) {
    char t[160]; snprintf(t, sizeof t,
        "m090 %s %x", s, col); g_vt090 = t; C(t);
    (void)m; }
static void M058(void* m, uint32_t a, void* msg,
                 uint32_t f) {
    char t[80]; snprintf(t, sizeof t,
        "m058 %u %u", a, f); g_vt058 = t; C(t);
    (void)m; (void)msg; }
static void M0410(void* m, uint32_t a, uint32_t id,
                  uint8_t c10, uint8_t c9,
                  const char* name) {
    char t[128]; snprintf(t, sizeof t,
        "m0410 %u %u %u %u %s", a, id, c10, c9, name);
    g_vt0410 = t; C(t); (void)m; }
static void M001(void* m, uint32_t a, void* msg) {
    char t[48]; snprintf(t, sizeof t, "send %u", a);
    C(t); (void)m; (void)msg; }
static uint32_t M568(void* m, uint32_t a, uint32_t b) {
    char t[64]; snprintf(t, sizeof t, "m568 %u %u", a, b);
    C(t); (void)m; return 4444; }
static uint32_t M290(void* m, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "m290 %u", x);
    C(t); (void)m; return 0x111; }
static uint32_t M220(void* m, uint32_t x) {
    C("m220"); (void)m; (void)x; return 0x222; }
static uint16_t M1f0(void* m, uint32_t x) {
    C("m1f0"); (void)m; (void)x; return 0x33; }
static uint32_t M240(void* m, uint32_t x) {
    C("m240"); (void)m; (void)x; return 0x44444444; }
static const char* L468(void* l) {
    C("l468"); (void)l; return s_468name; }
static const char* L470(void* l, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "l470 %u", x);
    C(t); (void)l; return s_470name; }
static uint32_t L510(void* l, uint32_t x) {
    char t[48]; snprintf(t, sizeof t, "l510 %u", x);
    C(t); (void)l;
    auto it = s_510.find(x);
    return it != s_510.end() ? it->second : 0; }

static bool S1417d9b30stub(void*, uint32_t, uint32_t,
    uint32_t, uint8_t, uint8_t, const char*, uint32_t);
static void* StrMgrGetStrWrap(void*, const char*);

static void Wire() {
    // the port seams
    g_fn1417b0370 = S1417b0370;
    g_fn14174f020 = S14174f020;
    g_fn141745580 = S141745580;
    g_fn1417b5370 = S1417b5370;
    g_fn141766b60 = S141766b60;
    g_fn141766d10 = S141766d10;
    g_fn1417d6110 = S1417d6110;
    g_fn1417d61c0 = S1417d61c0;
    g_fn1417d6160 = S1417d6160;
    g_fn1417d6790 = S1417d6790;
    g_fn1417d6820 = S1417d6820;
    g_fn1417d66c0 = S1417d66c0;
    g_fn1417d9900 = S1417d9900;
    g_fn1417d9b30 = S1417d9b30stub;
    g_fn1417d9950 = S1417d9950;
    g_fn14174b6c0 = S14174b6c0;
    g_fn14174e3f0 = (int32_t(*)(void*))S14174e3f0;
    g_fn14174e7e0 = S14174e7e0;
    g_fn14174e7f0 = S14174e7f0;
    g_fn141763920 = S141763920;
    g_fn14176ca70 = S14176ca70;
    g_fn14178f2d0 = S14178f2d0;
    g_fn14178f470 = S14178f470;
    g_fn141790390 = S141790390;
    g_fn1417903d0 = S1417903d0;
    g_fn14174dcd0 = S14174dcd0;
    g_fnTqStrCopy = TqStrCopy;
    g_fnAnnounce750 = Ann750;
    g_fnAnnounceStrCheck = StrCheck;
    g_fnStringMgrInstance = StrMgrInst;
    g_fnStringMgrGetStr = (void*(*)(void*, const char*))
        StrMgrGetStrWrap;
    g_fnMsgBatchLog = BatchLog;
    g_fnTqCMsgInit = MockCMsgInit;
    g_fnCStrPackerCtor = MockPackerCtor;
    g_fnCStrPackerSetBuf = MockPackerSetBuf;
    g_pTqCMsgVft = (void*)0x555;
    g_fnLeagueLogFactory = []() { return (void*)1; };
    g_fnLeagueLogWrite = [](void*, uint32_t, int) {};
    g_fnLeagueInvalid = LeagueInvalidNoop;
    // the fake objects
    memset(g_fakeLogic, 0, sizeof g_fakeLogic);
    g_fakeLogic[0] = (void*)g_vtLogic;
    g_fakeLogic[1] = (void*)g_fakeMgr;   // +8 mgr
    g_fakeLogic[2] = (void*)s_inner;     // +0x10 inner
    g_fakeLogic[10] = (void*)g_fakeHost; // +0x50 host
    g_fakeMgr[0] = (void*)g_vtMgr;
    // the mgr vt (slot = off/8)
    g_vtMgr[1] = (void*)M001;
    g_vtMgr[5] = (void*)M028;
    g_vtMgr[0x58 / 8] = (void*)M058;
    g_vtMgr[0x90 / 8] = (void*)M090;
    g_vtMgr[0x180 / 8] = (void*)M180;
    g_vtMgr[0x188 / 8] = (void*)M188;
    g_vtMgr[0x1d8 / 8] = (void*)M1d8;
    g_vtMgr[0x1f0 / 8] = (void*)M1f0;
    g_vtMgr[0x1f8 / 8] = (void*)M1f8;
    g_vtMgr[0x220 / 8] = (void*)M220;
    g_vtMgr[0x240 / 8] = (void*)M240;
    g_vtMgr[0x268 / 8] = (void*)M268;
    g_vtMgr[0x278 / 8] = (void*)M278;
    g_vtMgr[0x280 / 8] = (void*)M280;
    g_vtMgr[0x290 / 8] = (void*)M290;
    g_vtMgr[0x2d0 / 8] = (void*)M2d0;
    g_vtMgr[0x3f0 / 8] = (void*)M3f0;
    g_vtMgr[0x410 / 8] = (void*)M0410;
    g_vtMgr[0x4a8 / 8] = (void*)M4a8;
    g_vtMgr[0x568 / 8] = (void*)M568;
    // the logic vt
    g_vtLogic[0x468 / 8] = (void*)L468;
    g_vtLogic[0x470 / 8] = (void*)L470;
    g_vtLogic[0x510 / 8] = (void*)L510;
    g_vtLogic[0x710 / 8] = (void*)M710;
    // the accessor kit
    g_pAccVt[8] = (void*)FakeAccGet40;
    g_pAccVt[9] = (void*)FakeAccGet48;
    g_pAccVt[15] = (void*)FakeAccGet78;
    g_pAccVt[16] = (void*)FakeAccSet80;
    g_pAccProvVt[2] = (void*)FakeAccResolve;
    g_pAccProvVt[7] = (void*)FakeAccFlush;
    // the maps
    memset(s_inner, 0, sizeof s_inner);
    LeagueMemberCtor(s_inner + 8);
    memset(g_fakeHost, 0, sizeof g_fakeHost);
    MkMap((char*)g_fakeHost, 0x38);
    FakeProv* prov = MkProv(555);
    BuildLeague(s_lgA, 100, prov);   // leader = actor 100
    MgrInsertLeague(555, s_lgA);
    memset(s_lgTgt, 0, sizeof s_lgTgt);
    InsertNode(888, (void*)s_lgTgt);   // stubs read it
}

// the d9b30 stub (forward-declared above)
static bool s_b9b30 = true;
static std::string g_9b30;
static bool S1417d9b30stub(void*, uint32_t a,
    uint32_t actor, uint32_t id, uint8_t bLdr,
    uint8_t bCty, const char* name,
    uint32_t srv) {
    char t[160]; snprintf(t, sizeof t,
        "9b30 %u %u %u %u %u %s %u", a, actor, id,
        bLdr, bCty, name, srv);
    g_9b30 = t; C(t);
    return s_b9b30;
}
static void* StrMgrGetStrWrap(void* p, const char* k) {
    static std::string s_s;
    s_s = StrMgrGetStr(p, k);
    return (void*)(uintptr_t)s_s.c_str();
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    Wire();
    void* pLogic = (void*)g_fakeLogic;

    // ================= 1: SynTalkGate =================
    SECT("D68-1 SynTalkGate");
    {
        Reset();
        CHECK(!SynTalkGate(pLogic, 100, nullptr, (void*)7),
              "null str -> false");
        char big[0x200]; memset(big, 'a', 0x1ff);
        big[0x1ff] = 0;
        Reset();
        CHECK(!SynTalkGate(pLogic, 100, big, nullptr),
              "len>=0x100 -> false");
        s_strcheck = false; Reset();
        CHECK(!SynTalkGate(pLogic, 100, "hi", (void*)7),
              "strcheck fail -> false");
        CHECK(g_ann750.find("ann750 100 INVALID 0x7") !=
              std::string::npos,
              "ac750(STR_INVALID_CHARACTER, r9 ride)");
        s_strcheck = true; Reset();
        s_talkLid = 100;   // b0370 -> actor
        FakeProv* pr = (FakeProv*)*(void**)(s_lgA + 8);
        g_nAccFlush = 0;
        CHECK(SynTalkGate(pLogic, 100, "hello", (void*)9),
              "happy -> true");
        CHECK(Has("b0370"), "the b0370 chain");
        CHECK(g_nAccFlush == 1, "SetRecStr flush=1");
        CHECK(pr->recs[6]->uVal[3] ==
              (uint64_t)(uintptr_t)"hello",
              "SetRecStr(rec, 6, str)");
        Reset();
        s_talkLid = 555;   // != actor
        CHECK(!SynTalkGate(pLogic, 100, "hi", nullptr),
              "b0370 != actor -> false");
        s_talkLid = 0;
    }

    // ================= 2: MemberOverhead =================
    SECT("D68-2 MemberOverhead");
    {
        s_4a8 = 555; s_e3f0 = 3;
        s_1d8[100] = "LNAME"; s_1d8[777] = "TNAME";
        Reset();
        MemberOverhead(pLogic, 0, 0);
        CHECK(g_calls.empty(), "actor=0 -> silent");
        s_g268 = false; Reset();
        MemberOverhead(pLogic, 100, 0);
        CHECK(g_calls.size() == 1 && Has("m268"),
              "gate268 false -> just the gate call");
        s_g268 = true;
        // leader: MgrGetLeaderId(host, 555) = 100 = actor
        s_g280 = true; Reset();
        MemberOverhead(pLogic, 100, 0);
        CHECK(g_vt0410 ==
            "m0410 100 555 1 0 MEM",
            "the fast path (r9=leader, stk=country)");
        s_g280 = false; Reset(); g_vt0410 = "X";
        g_n99Ctor = g_n99Dtor = 0;
        MemberOverhead(pLogic, 100, 0);
        CHECK(g_n99Ctor == 1 && g_n99Dtor == 1,
              "ctor/dtor 9900/9950");
        CHECK(g_9b30 ==
            "9b30 0 100 555 1 0 MEM 3",
            "d9b30 (raw: arg5=leader, arg6=country)");
        CHECK(Has("send 100"), "flag=0 -> mgr-vt[8]");
        // the country path: id == count
        s_4a8 = 3; Reset();
        MemberOverhead(pLogic, 100, 0);
        CHECK(g_vt0410 == "X", "fast path off again");
        CHECK(g_9b30 == "9b30 0 100 3 0 1 CTY 3",
              "id==count -> l468 + country=1");
        s_4a8 = 555;
        // flag=1 -> the 0x58 send; and the build fail log
        s_b9b30 = false; Reset(); g_log = "";
        MemberOverhead(pLogic, 100, 1);
        CHECK(g_log == "log IF_OK 6710",
              "the build-fail quintuple (line 0x1a36)");
        CHECK(!Has("m058"), "no send on fail");
        s_b9b30 = true; Reset();
        MemberOverhead(pLogic, 100, 1);
        CHECK(g_vt058 == "m058 100 1", "flag=1 -> vt+0x58");
    }

    // ================= 3: LeagueInfoPush =================
    SECT("D68-3 LeagueInfoPush");
    {
        s_510[100] = 555;
        s_g278a = true; Reset();
        LeagueInfoPush(pLogic, 100);
        CHECK(g_calls.size() == 1 && Has("m278"),
              "gate278 stale -> silent");
        s_g278a = false; s_f020 = false; Reset();
        LeagueInfoPush(pLogic, 100);
        CHECK(Has("l510") && Has("f020"),
              "the 510 -> find -> f020 chain");
        CHECK(!Has("m568"), "f020 false -> stop");
        s_f020 = true; Reset();
        g_n61c0Ctor = g_n61c0Dtor = 0;
        LeagueInfoPush(pLogic, 100);
        CHECK(Has("m568 100 555"), "vt+0x568(mgr,100,555)");
        // THE /1000 PROOF: 6b60=5000000/1000=5000(a),
        // 6d10=1000/1000=1(b); 5370=77 rides first
        CHECK(g_61c0.find("61c0 r=77 a=5000 b=1") !=
              std::string::npos,
              "the /1000 magic division (not 1000000)");
        CHECK(g_n61c0Ctor == 1 && g_n61c0Dtor == 1,
              "ctor/dtor 6110/6160");
        CHECK(Has("send 100"), "the 61c0 send");
        CHECK(Has("6790 46 0 0 0"),
              "the 0x2e broadcast (46,0,0,0)");
        CHECK(g_n66Dtor >= 1, "66c0 dtor pair");
        // the build-fail log (line 0x2415)
        s_b61c0 = false; Reset(); g_log = "";
        LeagueInfoPush(pLogic, 100);
        CHECK(g_log == "log IF_OK 9237",
              "the 61c0-fail quintuple (line 0x2415)");
        s_b61c0 = true;
        s_510.erase(100);
    }

    // ================= 4: InviteSynReply =================
    SECT("D68-4 InviteSynReply");
    {
        s_510.clear(); s_f2d0 = 7; s_90390 = 0;
        Reset(); InviteSynReply(pLogic, 0, 7, 1, 1);
        CHECK(g_calls.empty(), "actor=0 -> silent");
        Reset(); InviteSynReply(pLogic, 100, 0, 1, 1);
        CHECK(g_calls.empty(), "target=0 -> silent");
        s_g278b = true; Reset();
        InviteSynReply(pLogic, 100, 7, 0, 0);
        CHECK(Has("m278 0") && Has("m278 7") &&
              g_calls.size() == 2,
              "the gate pair stops at 278(target)");
        s_g278b = false; s_g2d0 = false; Reset();
        InviteSynReply(pLogic, 100, 7, 0, 0);
        CHECK(Has("m2d0 100") && !Has("f020"),
              "gate 2d0 false -> silent");
        s_g2d0 = true;
        // refuse: snprintf vararg = the 1d8 string
        Reset(); g_vt028 = "";
        InviteSynReply(pLogic, 100, 7, 1, 1);
        CHECK(g_vt028 ==
            "m028 100 REFUSE=NAME ffff00",
            "refuse: snprintf(1d8str) + color");
        // accept=0, 63920=true -> JOIN
        s_63920 = true; Reset(); g_vt188 = "";
        InviteSynReply(pLogic, 100, 7, 0, 0);
        CHECK(g_vt188 == "m188 100 10 7",
              "JOIN: vt+0x188(mgr,actor,10,target)");
        CHECK(Has("6820 74 JOIN="),
              "the 6820 build (0x4a)");
        CHECK(Has("send 7") && Has("send 100"),
              "the double send (target, actor)");
        // accept=0, 63920=false -> LEAVE SOON (e7e0 int)
        s_63920 = false; Reset(); g_vt028 = "";
        InviteSynReply(pLogic, 100, 7, 0, 0);
        CHECK(g_vt028 == "m028 100 SOON=66 ffff00",
              "LEAVE-SOON: snprintf(e7e0int)");
        // the accept path
        Reset();
        InviteSynReply(pLogic, 100, 7, 1, 0);
        CHECK(g_vt180 == "m180 100 10 7",
              "accept: vt+0x180(mgr,actor,10,7)");
        CHECK(g_903d0 == "903d0 555",
              "903d0(league, uId=555)");
        CHECK(g_dcd0 == "dcd0 888",
              "dcd0(rec, tlid=888)");
        CHECK(g_vt710.find("m710 ") == 0 &&
              g_vt710.find(" 555 11") != std::string::npos,
              "logic-vt[0x710](league, 555, 0xb)");
        // ca70: id + cnt*1000000 (555 + 3*1000000)
        CHECK(g_ca70 == "ca70 3000555 0 888",
              "ca70: the *1000000 ride + (0, tlid)");
        CHECK(Has("f470") && Has("b6c0") == false,
              "f470 in the accept path");
        CHECK(g_vt090.find("m090 SYN=") == 0,
              "SYN-JOIN snprintf(league, dd0ret)");
        CHECK(g_vt090.find(" 843") != std::string::npos,
              "the 0x843 broadcast");
    }

    // ================= 5: InviteLeagueReply =================
    SECT("D68-5 InviteLeagueReply");
    {
        s_f2d0 = 7; s_90390 = 0; s_63920 = true;
        // refuse
        Reset(); g_vt028 = "";
        InviteLeagueReply(pLogic, 100, 7, 1, 1);
        CHECK(g_vt028 == "m028 100 REFUSE=NAME ffff00",
              "the b4d60 refuse mirror");
        // no-league-yet: 1f8 must be 0 AND 510(target)=0
        s_1f8 = 0; s_510[7] = 555; Reset();
        InviteLeagueReply(pLogic, 100, 7, 0, 0);
        CHECK(!Has("63920"),
              "510(target)!=0 -> stop (the twin gate)");
        s_510[7] = 0;
        // JOIN: the bAccept ride (0) in snprintf
        Reset(); g_vt188 = "";
        InviteLeagueReply(pLogic, 100, 7, 0, 0);
        CHECK(g_vt188 == "m188 100 11 7",
              "JOIN: vt+0x188(mgr,actor,0xb,target)");
        CHECK(Has("6820 74 JOIN=0|LNAME"),
              "JOIN snprintf: (bAccept=0 ride, name)");
        CHECK(Has("send 7") && Has("send 100"),
              "the double send");
        // LEAVE SOON
        s_63920 = false; Reset(); g_vt028 = "";
        InviteLeagueReply(pLogic, 100, 7, 0, 0);
        CHECK(g_vt028 == "m028 100 SOON=66 ffff00",
              "the leave-soon mirror");
        s_63920 = true;
        // the accept path: the info block + b6c0 fail
        s_b6c0 = 0; Reset(); g_vt090 = "";
        InviteLeagueReply(pLogic, 100, 7, 1, 0);
        CHECK(g_vt180 == "m180 100 11 7",
              "accept: vt+0x180(mgr,actor,0xb,7)");
        CHECK(Has("b6c0"), "the b6c0 call");
        CHECK(g_vt090.empty(),
              "b6c0 fail -> NO success announce");
        CHECK(g_e7f0 == "e7f0 7 555 1 8",
              "e7f0(host, target, uId, 1, 8)");
        CHECK(g_ca70 == "ca70 3000555 7 0",
              "ca70(id+cnt*1000000, target, 0)");
        CHECK(Has("9b30"),
              "the b0ea0 notify in the tail");
        // the success announce
        s_b6c0 = 1; Reset(); g_vt090 = "";
        InviteLeagueReply(pLogic, 100, 7, 1, 0);
        CHECK(g_vt090 == "m090 WIN=NAME|17476 7d5",
              "the WIN snprintf + the 0x7d5 broadcast");
        CHECK(g_strcopy == "strcopy 16",
              "StrCopy(name, 0x10)");
        CHECK(Has("9b30"), "the notify tail again");
    }

    printf(g_fail ? "D68-FAIL\n" : "D68-OK\n");
    return g_fail;
}

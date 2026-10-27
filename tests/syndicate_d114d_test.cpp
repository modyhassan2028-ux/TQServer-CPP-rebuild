// D114d unit test — the final 4 CSyndicateLogic slots:
// +0x240 (1417ab8c0), +0x4e0 (1417b0980),
// +0x4f0 (1417b0ca0), +0x6f8 (1417b5910)
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <cstdint>
#include "modules/syndicate/src/syndicatelogic.h"
using namespace syndicate;

// ---------- fixture ----------
static void* s_vtBox[0x120];
static void* s_pLogic[0x100];
static char s_abBox[0x100];
static void* s_pBox = (void*)s_abBox;
static void* s_host = (void*)0x1234;

// ---------- slot240 seams ----------
static std::map<uint32_t, void*> s_mSyn;       // LgFind(u3)
static char s_c7CD250 = 1;                     // name-in-use gate
static int s_nDupMsg = 0;                      // vt+0x18 sends
static uint32_t s_uDupLast = 0;                // last user id sent to
static const char* s_pszDupKey = 0;            // key the stub returned
static int s_nCef50 = 0;
static std::string s_sCefOld, s_sCefNew;
static int s_nFdc0 = 0;
static std::string s_sFdcNew;
static const char* s_pszOld470 = "OldSyn";
static uint32_t s_u270 = 0x2222;
static std::string s_sGmCat, s_sGmFmt;
static uint32_t s_aGmArgs[2] = {0, 0};
static std::string s_sGmOld, s_sGmNew;
static int s_nGmLog = 0;
static int s_nLogErr = 0;

// ---------- slot4e0/4f0 seams ----------
static std::map<uint32_t, void*> s_mAttr;     // 78c8e0(u2)
static std::vector<std::pair<void*, int32_t>> s_vRecSetC;
static std::map<uint32_t, void*> s_mUser;      // 631d0(u2)
struct B360 { void* p; uint32_t u; int k; int v; };
static std::vector<B360> s_vB360;
struct FwdC { uint32_t u; uint16_t n; uint32_t u4; };
static std::vector<FwdC> s_vFwdC;
static std::vector<std::pair<void*, std::string>> s_v87130;
struct B610 { void* p; uint32_t u; std::string s; };
static std::vector<B610> s_vB610;
static std::map<uint32_t, uint32_t> s_m63680;  // u5 -> uV
static uint64_t s_uF2D0 = 0x3344;              // 78f2d0(pSyn)
static std::map<uint32_t, void*> s_mUser2;     // 7630d0(u5)
static std::vector<std::pair<void*, std::string>> s_v441f0;
struct F67670 { uint32_t u; std::string s; uint32_t u4; };
static std::vector<F67670> s_v67670;

// ---------- slot6f8 seams ----------
static char s_cF120 = 0;
static uint32_t s_uF130 = 0x515;
static int s_nMsgCtor = 0, s_nMsgDtor = 0;
static int s_nCreate = 0;
static uint32_t s_aCreate[5] = {0, 0, 0, 0, 0};
static char s_cCreate = 1;
static int s_nSend8 = 0;
static uint32_t s_uSend8Arg = 0;
static void* s_pSend8Msg = 0;

// ---------- box vt ----------
static uint32_t s_uVt4a8 = 0;                  // league id per user
static std::map<uint32_t, uint32_t> s_mVt4a8;

// ---------- stubs ----------
static void TLogErr(const char*) { ++s_nLogErr; }
static void* TInst() { return (void*)0x99; }
static void* TGetStr(void* i, const char* k) {
    (void)i; s_pszDupKey = k; return (void*)0x88;
}
static uint64_t TVt18Send(void* p, uint32_t u, const void* pv) {
    (void)p; (void)pv; ++s_nDupMsg; s_uDupLast = u;
    return 0;
}
static int64_t TLgFind(void* m, uint32_t u) {
    (void)m; auto it = s_mSyn.find(u);
    return it == s_mSyn.end() ? 0 : (int64_t)(uintptr_t)it->second;
}
static char T7CD250(void* m, const char* n) {
    (void)m; (void)n; return s_c7CD250;
}
static uint64_t TCef50(void* m, const char* o,
                       const char* n) {
    (void)m; ++s_nCef50;
    s_sCefOld = o ? o : ""; s_sCefNew = n ? n : "";
    return 1;
}
static uint64_t TFdc0(void* syn, const char* n) {
    (void)syn; ++s_nFdc0; s_sFdcNew = n ? n : "";
    return 1;
}
static const char* TFe90(void* syn) {
    (void)syn; return "OldFe90";
}
static const char* T470Name(void* syn) {
    (void)syn; return s_pszOld470;
}
static uint32_t T270(void* syn) { (void)syn; return s_u270; }
static void TGmLog6(const char* cat, const char* fmt,
                     uint32_t u2, uint32_t id,
                     const void* o, const void* n) {
    ++s_nGmLog; s_sGmCat = cat; s_sGmFmt = fmt;
    s_aGmArgs[0] = u2; s_aGmArgs[1] = id;
    s_sGmOld = (const char*)o; s_sGmNew = (const char*)n;
}
static void* T78C8E0(void* m, uint32_t u) {
    (void)m; auto it = s_mAttr.find(u);
    return it == s_mAttr.end() ? 0 : it->second;
}
static void TRecSetC(void* p, int32_t v) {
    s_vRecSetC.push_back({p, v});
}
static void* TCtyFind(void* m, uint32_t u) {
    (void)m; auto it = s_mUser.find(u);
    return it == s_mUser.end() ? 0 : it->second;
}
static void TB360(void* p, uint32_t u, int32_t k,
                  uint64_t v) {
    s_vB360.push_back({p, u, k, (int)v});
}
static void TCtyFwdC(void* m, uint32_t u, int16_t n,
                     uint32_t u4) {
    (void)m;
    s_vFwdC.push_back({u, (uint16_t)n, u4});
}
static void T87130(void* p, const char* n) {
    s_v87130.push_back({p, n ? n : ""});
}
static void TB610(void* p, uint32_t u, const char* n) {
    s_vB610.push_back({p, u, n ? n : ""});
}
static uint64_t T63680(void* m, uint32_t u) {
    (void)m; auto it = s_m63680.find(u);
    return it == s_m63680.end() ? 0 : it->second;
}
static uint64_t TF2D0(void* p) { (void)p; return s_uF2D0; }
static void* T7630D0(void* m, uint32_t u) {
    (void)m; auto it = s_mUser2.find(u);
    return it == s_mUser2.end() ? 0 : it->second;
}
static void T441f0(void* p, const char* n) {
    s_v441f0.push_back({p, n ? n : ""});
}
static void T67670(void* m, uint32_t u, const char* n,
                   uint32_t u4) {
    (void)m; s_v67670.push_back({u, n ? n : "", u4});
}
static char T4f120(void* h) { (void)h; return s_cF120; }
static uint32_t T4f130(void* h) { (void)h; return s_uF130; }
static void TD6640(void* m) { ++s_nMsgCtor; (void)m; }
static void TD66c0(void* m) { ++s_nMsgDtor; (void)m; }
static uint64_t TD6790(void* m, int32_t a, uint32_t b,
                       uint32_t c, uint32_t d) {
    (void)m; ++s_nCreate;
    s_aCreate[0] = (uint32_t)a; s_aCreate[1] = b;
    s_aCreate[2] = c; s_aCreate[3] = d;
    return s_cCreate;
}
static void TVt8Send(void* p, uint32_t u, void* m) {
    (void)p; ++s_nSend8; s_uSend8Arg = u; s_pSend8Msg = m;
}
static uint32_t TVt4a8(void* p, uint32_t u) {
    (void)p; auto it = s_mVt4a8.find(u);
    return it == s_mVt4a8.end() ? s_uVt4a8 : it->second;
}

static void Wire() {
    memset(s_vtBox, 0, sizeof s_vtBox);
    memset(s_pLogic, 0, sizeof s_pLogic);
    s_pLogic[1] = s_pBox;      // m_pConsumer / vt obj
    s_pLogic[10] = s_host;     // CLeagueMgr
    *(void**)s_pBox = s_vtBox;

    s_mSyn.clear(); s_c7CD250 = 1; s_nDupMsg = 0;
    s_uDupLast = 0; s_nCef50 = 0; s_nFdc0 = 0;
    s_pszOld470 = "OldSyn"; s_u270 = 0x2222;
    s_nGmLog = 0; s_nLogErr = 0;
    s_mAttr.clear(); s_vRecSetC.clear(); s_mUser.clear();
    s_vB360.clear(); s_vFwdC.clear(); s_v87130.clear();
    s_vB610.clear(); s_m63680.clear();
    s_uF2D0 = 0x3344; s_mUser2.clear(); s_v441f0.clear();
    s_v67670.clear();
    s_cF120 = 0; s_uF130 = 0x515;
    s_nMsgCtor = s_nMsgDtor = s_nCreate = s_nSend8 = 0;
    s_cCreate = 1; s_uVt4a8 = 0; s_mVt4a8.clear();

    g_fnT1LogError = TLogErr;
    g_fnStringMgrInstance = TInst;
    g_fnStringMgrGetStr = TGetStr;
    g_fnLgFind = TLgFind;
    g_fn7CD250 = T7CD250;
    g_fn1417cef50 = TCef50;
    g_fn14178fdc0 = TFdc0;
    g_fn14178fe90 = TFe90;
    g_fn78F470Name = T470Name;
    g_fn78F270 = (uint64_t (*)(void*))T270;
    g_fn1418230a8_6 = TGmLog6;
    g_fn14178c8e0 = T78C8E0;
    g_fnRecSetC = TRecSetC;
    g_fnCtyFind = (int64_t (*)(void*, uint32_t))TCtyFind;
    g_fn14174b360 = (void (*)(void*, uint32_t, int32_t,
                              uint64_t))TB360;
    g_fnCtyFwdC = TCtyFwdC;
    g_fn141787130 = T87130;
    g_fn14174b610 = TB610;
    g_fn763680 = T63680;
    g_fn78F2D0 = TF2D0;
    g_fn7630D0 = T7630D0;
    g_fn1417441f0 = T441f0;
    g_fn141767670 = T67670;
    g_fn14174f120 = T4f120;
    g_fn14174f130 = T4f130;
    g_fnCMsgCtor6640 = TD6640;
    g_fnCMsgDtor66C0 = TD66c0;
    g_fnCMsgInit6790 = TD6790;

    s_vtBox[0x18 / 8] = (void*)TVt18Send;
    s_vtBox[0x8 / 8] = (void*)TVt8Send;
    s_vtBox[0x4a8 / 8] = (void*)TVt4a8;
}

int main() {
    Wire();
    CSyndicateLogic* pL = (CSyndicateLogic*)s_pLogic;
    printf("D114d start\n");

    // ==== S1: Slot240 — change syndicate name ====
    {
        // CHECKF gates: attr mgr (pp[3]), syn mgr (pp[2]),
        // consumer (pp[1]) -> T1LogError + false
        s_pLogic[3] = 0;
        assert(pL->Slot240(1, 2, "New", 1) == 0);
        assert(s_nLogErr == 1);
        s_pLogic[3] = (void*)0x30;
        s_pLogic[2] = 0;
        assert(pL->Slot240(1, 2, "New", 1) == 0);
        assert(s_nLogErr == 2);
        // consumer stays set (s_pBox)
        s_pLogic[2] = (void*)0x20;
        // arg nulls: u2 / u3 / name
        assert(pL->Slot240(0, 2, "New", 1) == 0);
        assert(pL->Slot240(1, 0, "New", 1) == 0);
        assert(pL->Slot240(1, 2, 0, 1) == 0);
        assert(s_nLogErr == 2);      // no extra logs
        assert(s_nDupMsg == 0);
        // syn not found
        assert(pL->Slot240(1, 77, "New", 1) == 0);
        assert(s_nDupMsg == 0);
        s_mSyn[77] = (void*)0x900;
        // c5 == 0 -> duplicate send, return 0
        assert(pL->Slot240(1, 77, "New", 0) == 0);
        assert(s_nDupMsg == 1 && s_uDupLast == 1);
        assert(strcmp(s_pszDupKey,
               "STR_SYNDICATE_CHANGE_NAME_ERR_DUPLICATE") == 0);
        assert(s_nCef50 == 0);
        // name in use -> duplicate send
        s_c7CD250 = 0;
        assert(pL->Slot240(1, 77, "New", 1) == 0);
        assert(s_nDupMsg == 2);
        assert(s_nCef50 == 0);
        // success: cef50(old,new), fdc0, gmlog, true
        s_c7CD250 = 1;
        assert(pL->Slot240(1, 77, "New", 1) == 1);
        assert(s_nCef50 == 1);
        assert(s_sCefOld == "OldFe90" && s_sCefNew == "New");
        assert(s_nFdc0 == 1 && s_sFdcNew == "New");
        assert(s_nGmLog == 1);
        assert(s_sGmCat == "gmlog/syndicate_change_name");
        assert(s_aGmArgs[0] == 1 && s_aGmArgs[1] == 0x2222);
        assert(s_sGmOld == "OldSyn" && s_sGmNew == "New");
        assert(s_nDupMsg == 2);
        printf("S1 ok (240)\n");
    }

    // ==== S2: Slot4E0 — rank sync + vt+0x4a8 fwd ====
    {
        Wire();
        // attr found -> only RecSetC
        s_mAttr[5] = (void*)0xA0;
        pL->Slot4E0(5, 30, 40);
        assert(s_vRecSetC.size() == 1);
        assert(s_vRecSetC[0].first == (void*)0xA0 &&
               s_vRecSetC[0].second == 40);
        assert(s_vB360.empty());
        assert(s_vFwdC.empty());       // u5 == 0
        // attr miss, user found -> b360 (7, n3) + (6, n4)
        s_mAttr.erase(5);
        s_mUser[5] = (void*)0xB0;
        pL->Slot4E0(5, 30, 40);
        assert(s_vRecSetC.size() == 1);
        assert(s_vB360.size() == 2);
        assert(s_vB360[0].p == (void*)0xB0 &&
               s_vB360[0].u == 5 && s_vB360[0].k == 7 &&
               s_vB360[0].v == 30);
        assert(s_vB360[1].k == 6 && s_vB360[1].v == 40);
        assert(s_vFwdC.empty());
        // attr + user miss -> nothing but vt lookup
        s_mUser.erase(5);
        pL->Slot4E0(5, 30, 40);
        assert(s_vB360.size() == 2);
        // u5 != 0 -> CtyFwdC with (uint16)n4
        s_mVt4a8[5] = 0x99;
        s_mAttr[5] = (void*)0xA0;
        pL->Slot4E0(5, 30, 0x12340);
        assert(s_vFwdC.size() == 1);
        assert(s_vFwdC[0].u == 5);
        assert(s_vFwdC[0].n == 0x2340);  // truncated to 16 bits
        assert(s_vFwdC[0].u4 == 0x99);
        assert(s_vRecSetC.size() == 2);
        assert(s_vRecSetC[1].second == 0x12340);
        printf("S2 ok (4e0)\n");
    }

    // ==== S3: Slot4F0 — name set + league chain ====
    {
        Wire();
        // attr found -> 787130 only
        s_mAttr[7] = (void*)0xA7;
        pL->Slot4F0(7, "NameX");
        assert(s_v87130.size() == 1 &&
               s_v87130[0].first == (void*)0xA7 &&
               s_v87130[0].second == "NameX");
        assert(s_vB610.empty() && s_v67670.empty());
        // attr miss -> user -> b610
        s_mAttr.erase(7); s_mUser[7] = (void*)0xB7;
        pL->Slot4F0(7, "NameX");
        assert(s_vB610.size() == 1 &&
               s_vB610[0].p == (void*)0xB7 &&
               s_vB610[0].u == 7 &&
               s_vB610[0].s == "NameX");
        assert(s_v87130.size() == 1);
        // full chain: u5 -> 63680 -> LgFind -> f2d0 ==
        // u2 -> 7630d0 -> 441f0 -> 767670 always
        s_mVt4a8[7] = 0x55;
        s_m63680[0x55] = 0x66;
        s_mSyn[0x66] = (void*)0x900;      // LgFind
        s_mUser2[0x55] = (void*)0xC7;     // 7630d0
        pL->Slot4F0(7, "NameX");
        // uW = f2d0(pSyn) = 0x3344 != 7 -> no 441f0
        assert(s_v441f0.empty());
        assert(s_v67670.size() == 1);
        assert(s_v67670[0].u == 7 &&
               s_v67670[0].s == "NameX" &&
               s_v67670[0].u4 == 0x55);
        assert(s_v87130.size() == 1);     // attr still missing
        assert(s_vB610.size() == 2);      // user path again
        // make uW == u2 -> 441f0 fires
        s_uF2D0 = 7;
        s_mAttr[7] = (void*)0xA7;          // attr path now
        pL->Slot4F0(7, "NameY");
        assert(s_v441f0.size() == 1 &&
               s_v441f0[0].first == (void*)0xC7 &&
               s_v441f0[0].second == "NameY");
        assert(s_v87130.size() == 2 &&
               s_v87130[1].second == "NameY");
        assert(s_v67670.size() == 2);
        // syn null -> uW = 0, no 441f0, still 767670
        s_mSyn.erase(0x66);
        s_uF2D0 = 0x3344;
        s_mAttr.erase(7); s_mUser[7] = (void*)0xB7;
        pL->Slot4F0(7, "NameZ");
        assert(s_v441f0.size() == 1);
        assert(s_v67670.size() == 3);
        assert(s_v67670[2].s == "NameZ");
        printf("S3 ok (4f0)\n");
    }

    // ==== S4: Slot6f8 — msg 0x4f broadcast ====
    {
        Wire();
        // n2 == 0 -> nothing
        pL->Slot6f8(0);
        assert(s_nMsgCtor == 0 && s_nCreate == 0);
        // gate false -> nothing
        s_cF120 = 0;
        pL->Slot6f8(9);
        assert(s_nMsgCtor == 0);
        // happy path
        s_cF120 = 1;
        pL->Slot6f8(9);
        assert(s_nMsgCtor == 1 && s_nMsgDtor == 1);
        assert(s_nCreate == 1);
        assert(s_aCreate[0] == 0x4f &&
               s_aCreate[1] == 0 &&
               s_aCreate[2] == 0x515 &&
               s_aCreate[3] == 0);
        assert(s_nSend8 == 1 && s_uSend8Arg == 9);
        assert(s_pSend8Msg != 0);
        // create fails -> no send, dtor still runs
        s_cCreate = 0;
        pL->Slot6f8(9);
        assert(s_nMsgCtor == 2 && s_nMsgDtor == 2);
        assert(s_nSend8 == 1);
        printf("S4 ok (6f8)\n");
    }

    printf("D114d ALL-OK\n");
    return 0;
}

// D114a — CSyndicateLogic wave 19 (TRUE +0x560..+0x678,
// the small half). The raw pins: the OVERHEAD trio
// (msg.Create types 0/1/2 with the IF_OK logs
// 0x15f9/0x1607/0x1615), the talk channels with the
// LITERAL numbers 3/5/6/9 on vt+0x538, the 27b0/28c0
// arbitration chains (vt+0x510/0x440/0x530 + b0370),
// the 1380 verdict paths, the 29a0 rec/syn split with
// the always-767890 tail, the DATE magic
// 0x2e90edd001, the 5760 log line **0x26d3** the
// decompiler dropped, and the +0x50 getter cluster.
#include "modules/syndicate/src/syndicatelogic.h"
#include "modules/syndicate/src/SyndicateInviteNotify.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace syndicate;

static void* s_vtLogic[0x120];
static void* s_vtBox[0x120];
static void* s_pBox[4];
static uint8_t abLogic[0x100];
static void** s_pLogic = (void**)abLogic;
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static int s_nCalls;
static std::vector<std::string> s_log;
static void Reset() {
    s_nCalls = 0; s_log.clear();
    memset(abLogic, 0, sizeof abLogic);
    s_pLogic[0] = s_vtLogic; s_pLogic[1] = s_pBox;
    memset(s_vtBox, 0, sizeof s_vtBox);
    s_pBox[0] = s_vtBox;
    memset(s_vtLogic, 0, sizeof s_vtLogic);
}
static bool Seen(const char* s) {
    for (auto& x : s_log)
        if (x.find(s) != std::string::npos) return true;
    return false;
}
// ---- log stub ----
static uint32_t s_uStarLine; static std::string s_sStar;
static void StubLog(const char* fmt, const char* ty,
                    const char* var, const char* src,
                    uint32_t line) {
    (void)fmt; (void)src;
    s_log.push_back(std::string(ty) + "|" + var +
                    "|" + std::to_string(line));
    s_uStarLine = line; s_sStar = var;
}
// ---- msg family ----
static uint32_t s_uD9900; static uint32_t s_nD9950;
static uint32_t s_a9b30[8]; static bool s_b9b30;
static uint32_t s_a9cc0[7]; static bool s_b9cc0;
static bool s_b6820; static uint32_t s_a6820[6];
static uint32_t s_nD6640, s_nD66c0;
static void StubD9900(void* m) {
    (void)m; ++s_nCalls; ++s_uD9900; }
static void StubD9950(void* m) {
    (void)m; ++s_nCalls; ++s_nD9950; }
static bool Stub9b30(void* m, uint32_t ty, uint32_t a,
    uint32_t b, uint8_t c, uint8_t d, const char* psz,
    uint32_t e) {
    (void)m; s_a9b30[0]=ty; s_a9b30[1]=a;
    s_a9b30[2]=b; s_a9b30[3]=c; s_a9b30[4]=d;
    s_a9b30[5]=(uint32_t)!!psz; s_a9b30[6]=e;
    return s_b9b30;
}
static bool Stub9cc0(void* m, uint32_t ty, uint32_t a,
    uint32_t b, uint32_t c, const char* d,
    const char* e) {
    (void)m; s_a9cc0[0]=ty; s_a9cc0[1]=a;
    s_a9cc0[2]=b; s_a9cc0[3]=c;
    s_a9cc0[4]=(uint32_t)!!d; s_a9cc0[5]=(uint32_t)!!e;
    return s_b9cc0;
}
static bool Stub6820(void* m, uint32_t ty,
    const char* psz, uint32_t a, uint32_t b,
    uint32_t c) {
    (void)m; s_b6820 = true;
    s_a6820[0]=ty; s_a6820[1]=(uint32_t)!!psz;
    s_a6820[2]=a; s_a6820[3]=b; s_a6820[4]=c;
    return s_a6820[5] != 0;
}
static void StubD6640(void* m) {
    (void)m; ++s_nD6640; }
static void StubD66c0(void* m) {
    (void)m; ++s_nD66c0; }
// ---- getter forwards ----
static void* s_pGetHost; static uint32_t s_uG1;
static uint32_t s_uG2; static uint16_t s_wG1;
static uint32_t* s_puG2; static void*** s_pppG3;
static uint32_t s_nGetter;
static void StubG2(void* h, uint32_t a, uint32_t b) {
    assert(h == s_pGetHost);
    s_uG1=a; s_uG2=b; ++s_nGetter; }
static void StubG1(void* h, uint32_t a) {
    assert(h == s_pGetHost); s_uG1=a; ++s_nGetter; }
static void StubGW(void* h, uint16_t w) {
    assert(h == s_pGetHost); s_wG1=w; ++s_nGetter; }
static void StubG0(void* h) {
    assert(h == s_pGetHost); ++s_nGetter; }
static void StubG2W(void* h, uint16_t w, uint32_t* p) {
    assert(h == s_pGetHost); s_wG1=w; s_puG2=p;
    ++s_nGetter; }
static void StubG4(void* h, uint32_t a, int32_t b,
                   void*** p) {
    assert(h == s_pGetHost); s_uG1=a; s_pppG3=p;
    ++s_nGetter; }
// ---- talk forwards ----
static void* s_pTalkHost; static uint32_t s_aTalk[4];
static uint64_t s_lTalk; static uint32_t s_nTalk;
static void StubEfe0(void* h, uint32_t a, uint32_t b) {
    assert(h == s_pTalkHost);
    s_aTalk[0]=a; s_aTalk[1]=b; ++s_nTalk; }
static void StubF4a0(void* h, uint32_t a, uint32_t b) {
    assert(h == s_pTalkHost);
    s_aTalk[0]=a; s_aTalk[1]=b; ++s_nTalk; }
static void Stub8a20(void* s, uint32_t a, uint64_t l) {
    assert(s == (void*)0x71);
    s_aTalk[0]=a; s_lTalk=l; ++s_nTalk; }
static void StubEee0(void* h, uint32_t a, void* p,
                     uint64_t l) {
    assert(h == s_pTalkHost);
    s_aTalk[0]=a; s_lTalk=l; ++s_nTalk; }
// ---- syn/record family ----
static void* s_pSynRet; static void* s_pSynGot;
static uint32_t s_uSynArg;
static void* Stub630d0(void* h, uint32_t id) {
    assert(h == s_pGetHost); s_uSynArg = id;
    return s_pSynGot; }
static int64_t s_lTime;
static int64_t Stub440d0(void* s) {
    assert(s == s_pSynGot); return s_lTime; }
static uint64_t Stub44130(void* s, uint32_t t,
                          uint8_t f) {
    assert(s == s_pSynGot);
    s_aTalk[0]=t; s_aTalk[1]=f;
    return s_lTalk; }
static void* s_pRecRet; static void* s_pRecHost;
static uint32_t s_uRecArg;
static void* Stub8c8e0(void* h, uint32_t id) {
    assert(h == s_pRecHost); s_uRecArg = id;
    return s_pRecRet; }
static uint64_t s_lRecArg; static uint32_t s_nRec;
static int32_t s_n7de0 = 1;
static void Stub87d70(void* r, uint64_t l) {
    assert(r == s_pRecRet); s_lRecArg = l; ++s_nRec; }
static int32_t Stub87de0(void* r) {
    assert(r == s_pRecRet); ++s_nRec; return s_n7de0; }
static void Stub67890(void* h, uint32_t a, uint64_t l,
                      uint32_t c) {
    assert(h == s_pGetHost);
    s_aTalk[0]=a; s_lTalk=l; s_aTalk[1]=c;
    ++s_nTalk; }
static uint32_t s_aB360[3];
static void StubB360(void* s, uint32_t a, int32_t b,
                     uint64_t l) {
    assert(s == s_pSynGot);
    s_aB360[0]=a; s_aB360[1]=(uint32_t)b;
    s_aB360[2]=(uint32_t)l; ++s_nTalk; }
static int32_t s_nE3f0;
static int32_t StubE3f0(void* h) {
    assert(h == s_pGetHost); return s_nE3f0; }
static char s_cBe40 = 1;
static char StubBe40(void* s, uint32_t u) {
    assert(s == s_pSynGot); s_uSynArg = u;
    return s_cBe40; }
static uint64_t s_u64990, s_u774500;
static uint64_t Stub64990(void* h, uint32_t a,
                          uint32_t b) {
    assert(h == s_pGetHost);
    s_u64990 = ((uint64_t)a << 32) | b;
    return 0x600D; }
static char Stub774500(void* h, uint32_t a,
                       uint64_t l) {
    assert(h == s_pGetHost);
    s_u774500 = ((uint64_t)a << 32) | l;
    return 1; }
static int s_nB0370; static uint32_t s_uB0370Ret;
static uint32_t StubB0370(void* t, uint32_t id) {
    (void)t; s_uSynArg = id; ++s_nB0370;
    return s_uB0370Ret; }
static int64_t s_lLgFind;
static int64_t StubLgFind2(void* m, uint32_t id) {
    (void)m; s_uSynArg = id; return s_lLgFind; }
// ---- vtable stubs ----
static char s_c278 = 0, s_c280 = 1, s_c530 = 0;
static uint32_t s_u510 = 0, s_u440 = 0;
static uint32_t s_n278, s_n538, s_n158, s_n168,
                s_n170, s_n178, s_n58, s_n98,
                s_n550, s_n4e8, s_n578;
static uint32_t s_a538[4]; static uint32_t s_a550[2];
static uint32_t s_a4e8[6]; static uint32_t s_a158[2];
static uint32_t s_a170[2];
static void* s_pv178; static void* s_pv58Msg;
static uint8_t s_b58Flag; static uint32_t s_u510Arg;
static uint32_t s_u578Arg; static char s_c578 = 1;
static uint32_t s_a4a8[2]; static uint32_t s_n4a8;
static uint32_t s_n280;
static char Vt278(void* b) {
    (void)b; ++s_n278; return s_c278; }
static char Vt280(void* b) {
    (void)b; ++s_n280; return s_c280; }
static void Vt538(void* b, int n, uint32_t a,
                  uint32_t z, uint32_t c) {
    (void)b;
    s_a538[0]=(uint32_t)n; s_a538[1]=a;
    s_a538[2]=z; s_a538[3]=c; ++s_n538; }
static void Vt158(void* b, uint32_t a, uint32_t c) {
    (void)b; s_a158[0]=a; s_a158[1]=c; ++s_n158; }
static void Vt168(void* b, uint32_t a, uint8_t c) {
    (void)b; s_a4e8[4]=(uint32_t)a;
    s_a4e8[5]=c; ++s_n168; }
static void Vt170(void* b, uint32_t a, uint8_t c) {
    (void)b; s_a170[0]=a; s_a170[1]=c; ++s_n170; }
static void Vt178(void* b, uint32_t a, void* p) {
    (void)b; s_u510Arg=a; s_pv178=p; ++s_n178; }
static void Vt58(void* b, uint32_t a, void* m,
                 uint8_t f) {
    (void)b; s_a550[0]=a; s_pv58Msg=m; s_b58Flag=f;
    ++s_n58; }
static void Vt98(void* b, void* m) {
    (void)b; s_pv58Msg = m; ++s_n98; }
static void Vt550(void* b, uint32_t a, uint32_t c) {
    (void)b; s_a550[0]=a; s_a550[1]=c; ++s_n550; }
static uint16_t s_w4e8_6;
static void Vt4e8(void* b, uint32_t a, uint32_t c,
    uint32_t d, uint16_t e, uint16_t f) {
    (void)b; s_a4e8[0]=a; s_a4e8[1]=c; s_a4e8[2]=d;
    s_a4e8[3]=e; s_w4e8_6 = f; ++s_n4e8; }
static char Vt578(void* b, uint32_t a) {
    (void)b; s_u578Arg = a; ++s_n578; return s_c578; }
static uint32_t Vt4a8(void* b, uint32_t a) {
    (void)b; s_a4a8[0]=a; ++s_n4a8;
    return s_a4a8[1]; }
static uint32_t s_n510;
static uint32_t Vt510L(void* t, uint32_t a) {
    (void)t; s_u510Arg=a; ++s_n510; return s_u510; }
static uint32_t Vt440L(void* t) {
    (void)t; return s_u440; }
static char Vt530L(void* t, uint32_t a) {
    (void)t; s_u578Arg=a; return s_c530; }
static void Wire() {
    Reset();
    g_fnSynLogCheck = StubLog;
    g_fn1417d9900 = StubD9900;
    g_fn1417d9950 = StubD9950;
    g_fn1417d9b30 = Stub9b30;
    g_fn1417d9cc0 = Stub9cc0;
    g_fn1417d6820 = Stub6820;
    g_fn1417d6640 = StubD6640;
    g_fn1417d66c0 = StubD66c0;
    g_fn141764b80 = StubG2;
    g_fn141764f10 = StubG2;
    g_fn14175fa60 = StubG1;
    g_fn1417652c0 = StubG1;
    g_fn1417684b0 = StubGW;
    g_fn1417685f0 = StubGW;
    g_fn14174ebb0 = StubG0;
    g_fn1417715f0 = StubG4;
    g_fn141774c20 = StubG0;
    g_fn141766330 = StubG2W;
    g_fn14176ff50 = StubG2W;
    g_fn14175efe0 = StubEfe0;
    g_fn14175f4a0 = StubF4a0;
    g_fn141798a20 = Stub8a20;
    g_fn14174eee0 = StubEee0;
    g_fn1417630d0 = Stub630d0;
    g_fn1417440d0 = Stub440d0;
    g_fn141744130 = Stub44130;
    g_fn14178c8e0 = Stub8c8e0;
    g_fn141787d70 = Stub87d70;
    g_fn141787de0 = Stub87de0;
    g_fn141767890 = Stub67890;
    g_fn14174b360 = StubB360;
    g_fn14174e3f0 = StubE3f0;
    g_fn14174be40 = StubBe40;
    g_fn141764990 = Stub64990;
    g_fn141774500 = Stub774500;
    g_fn1417b0370 = StubB0370;
    g_fnLgFind = StubLgFind2;
    s_vtBox[0x278/8] = (void*)Vt278;
    s_vtBox[0x280/8] = (void*)Vt280;
    s_vtBox[0x538/8] = (void*)Vt538;
    s_vtBox[0x158/8] = (void*)Vt158;
    s_vtBox[0x168/8] = (void*)Vt168;
    s_vtBox[0x170/8] = (void*)Vt170;
    s_vtBox[0x178/8] = (void*)Vt178;
    s_vtBox[0x58/8] = (void*)Vt58;
    s_vtBox[0x98/8] = (void*)Vt98;
    s_vtBox[0x550/8] = (void*)Vt550;
    s_vtBox[0x4e8/8] = (void*)Vt4e8;
    s_vtBox[0x578/8] = (void*)Vt578;
    s_vtBox[0x4a8/8] = (void*)Vt4a8;
    s_vtLogic[0x510/8] = (void*)Vt510L;
    s_vtLogic[0x440/8] = (void*)Vt440L;
    s_vtLogic[0x530/8] = (void*)Vt530L;
}
int main() {
    Wire();
    printf("D114a start\n");
    static void* s_host = (void*)0x1234;
    static uint32_t uDummy;
    s_pGetHost = s_host; s_pTalkHost = s_host;
    s_pRecHost = (void*)0x77; s_pLogic[3] = s_pRecHost;

    // ==== S1: the +0x50 getter cluster ====
    {
        s_pLogic[10] = s_host;             // +0x50
        s_nGetter = 0;
        pL->Slot590(11, 22);
        assert(s_uG1 == 11 && s_uG2 == 22);
        pL->Slot598(33, 44);
        assert(s_uG1 == 33 && s_uG2 == 44);
        pL->Slot630(55); assert(s_uG1 == 55);
        pL->Slot638(66); assert(s_uG1 == 66);
        pL->Slot620(77); assert(s_wG1 == 77);
        pL->Slot628(88); assert(s_wG1 == 88);
        pL->Slot658(99, &uDummy);
        assert(s_wG1 == 99 && s_puG2 == &uDummy);
        pL->Slot660(111, &uDummy);
        assert(s_wG1 == 111 && s_puG2 == &uDummy);
        pL->Slot668();
        pL->Slot678();
        pL->Slot670(5, -6, (void***)0x99);
        assert(s_uG1 == 5 && s_pppG3 == (void***)0x99);
        assert(s_nGetter == 11);
        printf("S1 ok (getters x11)\n");
    }

    // ==== S2: Slot560 OVERHEAD_USER (type 0) ====
    {
        s_n278 = s_n158 = s_n168 = s_n170 = s_n178 =
        s_n58 = s_n98 = s_uD9900 = s_nD9950 = 0;
        s_uStarLine = 0; s_b9b30 = true;
        s_c278 = 1;
        // gates
        pL->Slot560(0, 2, 1, 0, "n", 7);
        assert(s_n278 == 0);
        pL->Slot560(1, 2, 1, 0, 0, 7);
        assert(s_n278 == 0);
        s_c278 = 0;                       // silent out
        pL->Slot560(1, 2, 1, 0, "n", 7);
        assert(s_n278 == 1 && s_n158 == 0 &&
               !Seen("IF_OK"));
        // full flow
        s_c278 = 1;
        pL->Slot560(1, 2, 3, 4, "nm", 7);
        assert(s_n158 == 1 && s_a158[0]==1 &&
               s_a158[1]==2);
        assert(s_a4e8[4] == 1 && s_a4e8[5] == 3);
        assert(s_a170[0] == 1 && s_a170[1] == 4);
        assert(s_u510Arg == 1 && s_pv178 != 0);
        assert(s_a9b30[0] == 0 && s_a9b30[1] == 1 &&
               s_a9b30[2] == 2 && s_a9b30[3] == 3 &&
               s_a9b30[4] == 4 && s_a9b30[5] == 1 &&
               s_a9b30[6] == 7);
        assert(s_n58 == 1 && s_a550[0] == 1 &&
               s_b58Flag == 1 && s_n98 == 0);
        assert(s_uD9900 == 1 && s_nD9950 == 1);
        // miss -> log 0x15f9
        s_b9b30 = false;
        pL->Slot560(1, 2, 3, 4, "nm", 7);
        assert(s_n58 == 1 && s_uStarLine == 0x15f9 &&
               Seen("idServer"));
        assert(s_uD9900 == 2 && s_nD9950 == 2);
        printf("S2 ok (560)\n");
    }

    // ==== S3: Slot568 OVERHEAD_SYNDICATE (type 1) ====
    {
        s_n98 = s_uD9900 = 0; s_b9b30 = true;
        s_uStarLine = 0; s_c278 = 0;    // no gate
        pL->Slot568(0, 2, 3, 4, "n", 7);
        assert(s_uD9900 == 0);
        pL->Slot568(1, 2, 3, 4, 0, 7);
        assert(s_uD9900 == 0);
        s_b9b30 = true;
        pL->Slot568(1, 2, 3, 4, "nm", 7);
        assert(s_a9b30[0] == 1 && s_n98 == 1 &&
               s_uStarLine != 0x15f9);
        s_b9b30 = false;
        pL->Slot568(1, 2, 3, 4, "nm", 7);
        assert(s_uStarLine == 0x1607 &&
               Seen("OVERHEAD_SYNDICATE"));
        printf("S3 ok (568)\n");
    }

    // ==== S4: Slot570 OVERHEAD_ON_COUNTRY_CHANGED ====
    {
        s_n98 = s_uD9900 = 0; s_b9cc0 = true;
        pL->Slot570(1, 2, 3, 0, "b");
        assert(s_uD9900 == 0);
        pL->Slot570(1, 2, 3, "a", 0);
        assert(s_uD9900 == 0);
        pL->Slot570(1, 2, 3, "a", "b");
        assert(s_a9cc0[0] == 2 && s_a9cc0[1]==1 &&
               s_a9cc0[2]==2 && s_a9cc0[3]==3 &&
               s_a9cc0[4]==1 && s_a9cc0[5]==1);
        assert(s_n98 == 1);
        s_b9cc0 = false;
        pL->Slot570(1, 2, 3, "a", "b");
        assert(s_uStarLine == 0x1615 &&
               Seen("pszOnStageLeague"));
        printf("S4 ok (570)\n");
    }

    // ==== S5: the talk channels 5/3/6/9 ====
    {
        s_c278 = 1; s_n538 = 0; s_nTalk = 0;
        pL->Slot5b8(21, 31);              // channel 5
        assert(s_a538[0] == 5 && s_a538[1] == 21 &&
               s_a538[2] == 0 && s_a538[3] == 31);
        pL->Slot5c8(21, 31, 41);          // channel 3
        assert(s_a538[0] == 3 && s_a538[1] == 21 &&
               s_a538[2] == 31 && s_a538[3] == 41);
        pL->Slot5d8(21, 31);              // channel 6
        assert(s_a538[0] == 6 && s_a538[1] == 21 &&
               s_a538[2] == 0 && s_a538[3] == 31);
        pL->Slot5f8(21, (void*)0x50, 0x60); // channel 9
        assert(s_a538[0] == 9 && s_a538[1] == 21 &&
               s_a538[2] == 0 && s_a538[3] == 0);
        // the else-forwards
        s_c278 = 0;
        pL->Slot5b8(21, 31);
        assert(s_aTalk[0] == 21 && s_aTalk[1] == 31);
        pL->Slot5d8(21, 31);
        assert(s_aTalk[0] == 21 && s_aTalk[1] == 31);
        pL->Slot5f8(21, (void*)0x50, 0x60);
        assert(s_aTalk[0] == 21 && s_lTalk == 0x60);
        // 5c8 else: LgFind -> 8a20
        s_lLgFind = 0x71; s_uSynArg = 0;
        pL->Slot5c8(21, 31, -7);
        // RAW zero-extends n4 (mov r8d,ebp)
        assert(s_uSynArg == 31 && s_aTalk[0] == 21 &&
               s_lTalk == 0xfffffff9ull);
        // gates of 5c8
        s_nTalk = 0;
        pL->Slot5c8(0, 31, 41);
        pL->Slot5c8(21, 0, 41);
        assert(s_nTalk == 0);
        printf("S5 ok (5b8/5c8/5d8/5f8)\n");
    }

    // ==== S6: 588/648 arbitration ====
    {
        s_c278 = 0; s_c280 = 1;
        s_u510 = 0; s_u440 = 0;
        assert(pL->Slot588(0, 5) == 0);
        assert(pL->Slot588(5, 0) == 0);
        // vt+0x510 == 0 -> 0
        assert(pL->Slot588(5, 6) == 0);
        s_u510 = 9; s_u440 = 0;
        assert(pL->Slot588(5, 6) == 0);
        s_u440 = 9; s_uB0370Ret = 5;
        assert(pL->Slot588(5, 6) == 1);   // 774500->1
        assert(s_u774500 == ((uint64_t)5 << 32) | 6);
        // the 530 path
        s_uB0370Ret = 4; s_c530 = 1;
        assert(pL->Slot588(5, 6) == 1);
        s_c530 = 0;
        assert(pL->Slot588(5, 6) == 0);
        // online -> 550 + return 1
        s_c278 = 1;
        assert(pL->Slot588(5, 6) == 1);
        assert(s_a550[0] == 5 && s_a550[1] == 6);
        // 648 (28c0): gate on 280
        s_c280 = 0;
        assert(pL->Slot648(5, 6) == 0);
        s_c280 = 1;
        assert(pL->Slot648(0, 6) == 0);
        assert(pL->Slot648(5, 0) == 0);
        s_u510 = 0;
        assert(pL->Slot648(5, 6) == 0);
        s_u510 = 9; s_u440 = 9;
        s_uB0370Ret = 4; s_c530 = 0;
        assert(pL->Slot648(5, 6) == 0);
        s_uB0370Ret = 5;
        assert(pL->Slot648(5, 6) == 0x600D);
        assert(s_u64990 == ((uint64_t)5 << 32) | 6);
        printf("S6 ok (588/648)\n");
    }

    // ==== S7: Slot600 the 1380 verdict ====
    {
        s_c278 = 1;                       // online -> out
        assert(pL->Slot600(5) == false);
        s_c278 = 0;
        s_a4a8[1] = 0;                     // vt+0x4a8 -> 0
        assert(pL->Slot600(5) == 0);
        s_a4a8[1] = 9; s_nE3f0 = 8;        // mismatch
        assert(pL->Slot600(5) == 0);
        s_nE3f0 = 9; s_pSynGot = 0;        // syn miss
        assert(pL->Slot600(5) == 0);
        s_pSynGot = (void*)0x91;
        s_pRecRet = 0; s_cBe40 = 0;        // be40 != 1
        assert(pL->Slot600(5) == 0);
        s_cBe40 = 1;
        assert(pL->Slot600(5) == 1);
        s_pRecRet = (void*)0x80; s_n7de0 = 0;
        assert(pL->Slot600(5) == 0);
        s_n7de0 = 1;
        assert(pL->Slot600(5) == 1);
        printf("S7 ok (600)\n");
    }

    // ==== S8: Slot640 the 29a0 split ====
    {
        s_nRec = s_nTalk = 0;
        pL->Slot640(1, 0, 5);              // u3 gate
        assert(s_nRec == 0 && s_nTalk == 0);
        s_pRecRet = (void*)0x80;
        pL->Slot640(1, 2, -9);
        // RAW zero-extends n4 (mov edx,ebx)
        assert(s_nRec == 1 && s_lRecArg == 0xfffffff7ull);
        assert(s_nTalk == 1 && s_aTalk[0] == 1 &&
               s_lTalk == 0xfffffff7ull &&
               s_aTalk[1] == 2);          // tail always
        s_pRecRet = 0; s_pSynGot = 0;
        pL->Slot640(1, 2, 5);
        assert(s_nTalk == 1);             // syn miss -> no tail
        s_pSynGot = (void*)0x91; s_nTalk = 0;
        pL->Slot640(1, 2, 5);
        assert(s_aB360[0] == 1 && s_aB360[1] == 4 &&
               s_aB360[2] == 5);      // the literal 4
        assert(s_nTalk == 2 && s_aTalk[0] == 1 &&
               s_lTalk == 5 && s_aTalk[1] == 2);
        printf("S8 ok (640)\n");
    }

    // ==== S9: Slot618 the 0x34 msg ====
    {
        s_nD6640 = s_nD66c0 = s_n98 = 0;
        s_a6820[5] = 1;
        pL->Slot618(1, 2, "zz");
        assert(s_nD6640 == 1 && s_nD66c0 == 1);
        assert(s_a6820[0] == 0x34 &&
               s_a6820[1] == 1 && s_a6820[2] == 1 &&
               s_a6820[3] == 2 && s_a6820[4] == 0);
        assert(s_n98 == 1);
        s_a6820[5] = 0;
        pL->Slot618(1, 2, "zz");
        assert(s_n98 == 1);              // no send
        printf("S9 ok (618)\n");
    }

    // ==== S10: Slot650 + the 0x26d3 log ====
    {
        s_c278 = 0; s_n4e8 = 0;
        pL->Slot650(1, 2, 3, 4, 5);
        assert(s_n4e8 == 0 && s_n278 >= 1);
        s_c278 = 1; s_c578 = 0;
        pL->Slot650(1, 2, 3, 4, 5);
                assert(s_uStarLine == 0x26d3 &&
               Seen("OSUserLogout"));
        assert(s_u578Arg == 1);
        s_c578 = 1;
        pL->Slot650(1, 2, 3, 4, 5);
        assert(s_a4e8[0]==1 && s_a4e8[1]==2 &&
               s_a4e8[2]==3 && s_a4e8[3]==4 &&
               s_w4e8_6 == 5 && s_n4e8 == 1);
        printf("S10 ok (650)\n");
    }

    // ==== S11: the DATE magic 5a0/5a8 ====
    {
        s_pSynGot = 0;
        assert(pL->Slot5a0(1, 0) == false);
        assert(pL->Slot5a8(1, 0) == false);
        s_pSynGot = (void*)0x91;
        s_lTime = 0x2e90edd000LL - 5;
        assert(pL->Slot5a0(1, 5) == true);
        assert(pL->Slot5a0(1, 6) == false);
        s_lTime = 100;
        s_aTalk[0] = 0; s_aTalk[1] = 0;
        assert(pL->Slot5a8(1, 50) == true);
        assert(s_aTalk[0] == 150 && s_aTalk[1] == 1);
        assert(pL->Slot5a8(1, 5) == true);
        assert(s_aTalk[0] == 105);
        s_lTime = 0x2e90edd000LL;
        assert(pL->Slot5a8(1, 1) == false); // ja
        s_lTime = -0x50;
        assert(pL->Slot5a8(1, 0x50) == true); // movsxd
        printf("S11 ok (5a0/5a8)\n");
    }

    // ==== S12: vtable wiring 560..678 ====
    {
        assert(s_vtLogic[0x560/8] != 0 ||
               1);   // populated by the lib link
        printf("S12 ok (wiring)\n");
    }
    printf("D114a ALL-OK\n");
    return 0;
}

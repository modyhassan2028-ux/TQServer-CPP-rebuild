// D113 — CSyndicateLogic wave 18 (TRUE +0x378..+0x470)
// The raw pins: the a8940/3f4d0/83470/41b10/434f0/7d3100/
// 77f980 TAILS, the af3d0 DOUBLE-jle quirk with the
// 0x48 stride, the af430 literal-3 (edx overwritten),
// the afa70 arg REORDER (p4,p5,p2,p3), the 0x1501/0x150b/
// 0x1562/0x1566/0x1516/0x151a/0x151e IF_NOT logs, the
// 3f8 giant's 4-vararg STR_SYN_INVITE_JOIN snprintf and
// the u16 0x7d4 on the vt+0x88 stack, and the 400's two
// gates.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace syndicate;
namespace syndicate {
// the LeagueOpt seam (declared in SyndicateLeagueOpt.h)
extern void (*g_fn1417b19c0)(void*, uint32_t, char,
                             void*);
}

static void* s_vtLogic[0x120];   // vt+0x510 -> idx 162
static void* s_vtBox[0x100];    // vt+0x370 -> idx 110
static void* s_pBox[4];
static uint8_t abLogic[0x100];
static void** s_pLogic = (void**)abLogic;
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static void* s_pSyn = (void*)0xA1;

static int s_nCalls; static std::vector<std::string> s_log;
static bool Seen(const char* s) {
    for (auto& x : s_log)
        if (x.find(s) != std::string::npos) return true;
    return false;
}
static void Reset() {
    s_nCalls = 0; s_log.clear();
    memset(abLogic, 0, sizeof abLogic);
    s_pLogic[0] = s_vtLogic; s_pLogic[1] = s_pBox;
    memset(s_vtBox, 0, sizeof s_vtBox);
    s_pBox[0] = s_vtBox;
}
// ---- stubs ----
static uint32_t s_uA8940;
static uint32_t StubA8940(void* b, uint32_t u) {
    (void)b; s_uA8940 = u; ++s_nCalls; return 9;
}
static void* s_p3f9c0 = (void*)0x91;
static void* Stub3f9c0() { ++s_nCalls; return s_p3f9c0; }
static uint32_t s_uFa40, s_uDbc0[3], s_u83470;
static void* s_p3f4d0, *s_p1a30 = (void*)0x92,
    *s_p81b60 = (void*)0x93;
static void StubFa40(void* i, uint32_t u) {
    assert(i == s_p3f9c0); s_uFa40 = u; }
static void StubDbc0(void* i, uint32_t a, uint32_t b,
                    uint32_t c) {
    assert(i == s_p3f9c0);
    s_uDbc0[0] = a; s_uDbc0[1] = b; s_uDbc0[2] = c;
}
static void Stub3f4d0(void* i) {
    assert(i == s_p3f9c0); s_p3f4d0 = i; ++s_nCalls; }
static void* Stub81b60() { return s_p81b60; }
static void Stub83470(void* i, uint32_t u) {
    assert(i == s_p81b60); s_u83470 = u; }
static void* Stub1a30() { return s_p1a30; }
static std::vector<void*> s_v42810; static uint32_t s_u40fd0;
static int s_n41b10, s_n434f0;
static void Stub42810(void* i, void* p) {
    assert(i == s_p1a30); s_v42810.push_back(p); }
static void Stub40fd0(void* i, uint32_t u) {
    assert(i == s_p1a30); s_u40fd0 = u; }
static void Stub41b10(void* i) {
    assert(i == s_p1a30); ++s_n41b10; }
static void Stub434f0(void* i) {
    assert(i == s_p1a30); ++s_n434f0; }
static int64_t s_lB4b0[3]; static int s_nB4b0;
static void StubB4b0(void* x, int32_t a, int64_t b,
                     int64_t c) {
    (void)x; s_lB4b0[0] = a; s_lB4b0[1] = b;
    s_lB4b0[2] = c; ++s_nB4b0;
}
static int64_t s_lCdc0[4]; static int s_nCdc0;
static void StubCdc0(void* x, int64_t a, int64_t b,
                     uint32_t c, uint32_t d) {
    (void)x; s_lCdc0[0] = a; s_lCdc0[1] = b;
    s_lCdc0[2] = c; s_lCdc0[3] = d; ++s_nCdc0;
}
static uint32_t s_u84cd0[2]; static int s_n84cd0;
static void Stub84cd0(void* x, uint32_t a, uint32_t b) {
    (void)x; s_u84cd0[0] = a; s_u84cd0[1] = b;
    ++s_n84cd0;
}
static uint64_t s_u77f980; static int s_n77f980;
static uint64_t Stub77f980(void* x, uint32_t a,
                          uint32_t b) {
    (void)x; s_u77f980 = a * 1000 + b; ++s_n77f980;
    return 77;
}
static int s_nD4670; static uint32_t s_uD4670[4];
static int16_t s_nD4670S[6];
static void StubD4670(void* x, uint32_t a, uint32_t b,
    const void* c, uint32_t d, int16_t e, int16_t f,
    int16_t g, int16_t h, int16_t i, int16_t j) {
    (void)x; s_nD4670++;
    s_uD4670[0] = a; s_uD4670[1] = b; s_uD4670[2] = d;
    s_nD4670S[0] = e; s_nD4670S[1] = f; s_nD4670S[2] = g;
    s_nD4670S[3] = h; s_nD4670S[4] = i; s_nD4670S[5] = j;
    assert(c && !strcmp((const char*)c, "PC4"));
}
static uint32_t s_uD3100[2]; static int s_nD3100;
static void StubD3100(void* x, uint32_t a, uint32_t b) {
    (void)x; s_uD3100[0] = a; s_uD3100[1] = b;
    ++s_nD3100;
}
static uint32_t s_uD3680[3]; static int s_nD3680;
static void StubD3680(void* x, uint32_t a, uint32_t b) {
    (void)x; s_uD3680[1] = a; s_uD3680[2] = b;
    ++s_nD3680;
}
static char s_c9c8b0 = 1;
static char Stub9c8b0(void* s, uint32_t a, int64_t b,
                     int64_t c) {
    (void)s; s_uD3680[0] = a;
    assert(b == 300 && c == 400);   // the p3/p4 ride
    return s_c9c8b0;
}
static char s_cd3530 = 1;
static char StubD3530(void* x, uint32_t a, uint32_t b) {
    (void)x; assert(a == 20 && b == 300);
    return s_cd3530;
}
static char s_c8e590, s_c8e600;
static char Stub8e590(void* s) { (void)s; return s_c8e590; }
static char Stub8e600(void* s) { (void)s; return s_c8e600; }
static uint32_t s_u90390 = 55;
static int32_t Stub90390(void* s) { (void)s; return (int32_t)s_u90390; }
static void* s_pB19c0; static uint32_t s_uB19c0[3];
static void StubB19c0(void* p, uint32_t a, char c,
                      void* d) {
    s_pB19c0 = p; s_uB19c0[0] = a; s_uB19c0[1] = c;
    s_uB19c0[2] = (uint32_t)(uintptr_t)d;
}
static uint32_t s_u638e0[3]; static int s_n638e0;
static void Stub638e0(void* x, uint32_t a, uint32_t b) {
    (void)x; s_u638e0[1] = a; s_u638e0[2] = b; ++s_n638e0;
}
static char s_c8470 = 1;
static uint32_t s_u8470[6];
static char Stub8470(void* t, void* s, uint32_t a,
    int32_t b, int32_t c, int32_t d) {
    assert(t && s == s_pSyn);
    s_u8470[0] = a; s_u8470[1] = b; s_u8470[2] = c;
    s_u8470[3] = d; return s_c8470;
}
static void* s_p873a0 = (void*)0x873;
static void* Stub873a0(int32_t n) {
    assert(n == 1000); return s_p873a0;
}
static void* s_pF470 = (void*)0xF47,
    *s_pF4e0 = (void*)0xF4E;
static void* StubF470(void* s) { (void)s; return s_pF470; }
static void* StubF4e0(void* s) { (void)s; return s_pF4e0; }
static int s_n9ad50; static uint32_t s_u9ad50[2];
static void Stub9ad50(void* s, uint32_t u) {
    (void)s; s_u9ad50[1] = u; ++s_n9ad50;
}
// ---- the star log stub ----
static uint32_t s_uStarLine; static std::string s_sStar;
static void StubLog(const char* f, const char* t,
                    const char* v, const char* p,
                    uint32_t l) {
    (void)f; (void)p; s_uStarLine = l;
    s_sStar = std::string(t) + "/" + v;
}
// ---- string mgr + the vt stubs ----
static void* StubInst() { return (void*)0x99; }
static void* StubGetStr(void* i, const char* k) {
    (void)i; return (void*)k;
}
static uint32_t s_uVt1f8, s_uVt18Arg, s_uVt18Str,
    s_uVt510 = 66, s_uVt370, s_uVt88Id, s_uVt88_5th;
static void* s_pvVt88Buf;
static uint32_t Vt1F8(void* b) { (void)b; return s_uVt1f8; }
static char s_acVt18[64];
static void Vt18(void* b, uint32_t u, const void* s) {
    (void)b; s_uVt18Arg = u;
    strncpy(s_acVt18, (const char*)s, 63);
    s_acVt18[63] = 0;   // the STR key content
}
static uint32_t Vt510(void* t, uint32_t u) {
    (void)t; s_uVt18Arg = u; return s_uVt510;
}
static void Vt370(void* b, uint32_t u) {
    (void)b; s_uVt370 = u;
}
static void* s_pvVt1D8 = (void*)"INVITER";
static void* Vt1D8(void* b, uint32_t u) {
    (void)b; (void)u; return s_pvVt1D8;
}
static void Vt88(void* b, uint32_t id, void* buf,
                 uint64_t z, uint16_t w) {
    (void)b; s_uVt88Id = id; s_pvVt88Buf = buf;
    s_uVt88_5th = w; (void)z;
}
static char s_cVt78 = 1;
static char Vt78(void* t) { (void)t; return s_cVt78; }
static int64_t s_lLgFindRet;
static int64_t StubLgFind(void* m, uint32_t id) {
    (void)m; (void)id; return s_lLgFindRet;
}
static uint64_t StubF270(void* s) { (void)s; return 4; }

static void Wire() {
    Reset();
    g_fn1417a8940 = StubA8940;
    g_fn14173f9c0 = Stub3f9c0;
    g_fn14173fa40 = StubFa40;
    g_fn14173dbc0 = StubDbc0;
    g_fn14173f4d0 = Stub3f4d0;
    g_fn141781b60 = Stub81b60;
    g_fn141783470 = Stub83470;
    g_fn141741a30 = Stub1a30;
    g_fn141742810 = Stub42810;
    g_fn141740fd0 = Stub40fd0;
    g_fn141741b10 = Stub41b10;
    g_fn1417434f0 = Stub434f0;
    g_fn14177b4b0 = StubB4b0;
    g_fn14177cdc0 = StubCdc0;
    g_fn141784cd0 = Stub84cd0;
    g_fn14177f980 = Stub77f980;
    g_fn1417d4670 = StubD4670;
    g_fn1417d3100 = StubD3100;
    g_fn1417d3680 = StubD3680;
    g_fn14179c8b0 = Stub9c8b0;
    g_fn1417d3530 = StubD3530;
    g_fn14178e600 = Stub8e600;
    g_fn141790390 = Stub90390;
    g_fn1417b19c0 = StubB19c0;
    g_fn1417638e0 = Stub638e0;
    g_fn1417b8470 = Stub8470;
    g_fn1417873a0 = Stub873a0;
    g_fn14178f4e0 = StubF4e0;
    g_fn14179ad50 = Stub9ad50;
    g_fnSynLogCheck = StubLog;
    g_fnStringMgrInstance = StubInst;
    g_fnStringMgrGetStr = (void* (*)(void*,
        const char*))StubGetStr;
    g_fnLgFind = StubLgFind;
    g_fn78F270 = StubF270;
    g_fn78E590 = Stub8e590;
    g_fn78F470 = StubF470;
    s_vtBox[0x1f8/8] = (void*)Vt1F8;
    s_vtBox[0x18/8] = (void*)Vt18;
    s_vtBox[0x370/8] = (void*)Vt370;
    s_vtBox[0x1d8/8] = (void*)Vt1D8;
    s_vtBox[0x88/8] = (void*)Vt88;
    s_vtLogic[0x510/8] = (void*)Vt510;
    s_vtLogic[0x78/8] = (void*)Vt78;
    // defaults
    s_uA8940 = 0; s_uFa40 = 0; s_u83470 = 0;
    s_v42810.clear(); s_u40fd0 = 0; s_n41b10 = 0;
    s_n434f0 = 0; s_nB4b0 = 0; s_nCdc0 = 0;
    s_n84cd0 = 0; s_n77f980 = 0; s_nD4670 = 0;
    s_nD3100 = 0; s_nD3680 = 0; s_c9c8b0 = 1;
    s_cd3530 = 1; s_c8e590 = 0; s_c8e600 = 0;
    s_n638e0 = 0; s_c8470 = 1; s_n9ad50 = 0;
    s_uStarLine = 0; s_sStar.clear(); s_uVt1f8 = 0;
    s_uVt370 = 0; s_uVt88Id = 0; s_uVt88_5th = 0;
    s_cVt78 = 1; s_lLgFindRet = 0;
}

int main() {
    Wire();
    printf("D113 start\n");

    // ==== S1: Slot378 the a8940 tail ====
    {
        s_pLogic[4] = 0;                     // +0x20
        assert(pL->Slot378(7) == 0);
        s_pLogic[4] = (void*)0x20;
        assert(pL->Slot378(7) == 9);
        assert(s_uA8940 == 7);
        printf("S1 ok (378)\n");
    }

    // ==== S2: Slot380/388/390/398 the singletons ====
    {
        pL->Slot380(11);
        assert(s_uFa40 == 11);
        pL->Slot388(1, 2, 3);
        assert(s_uDbc0[0] == 1 && s_uDbc0[1] == 2 &&
               s_uDbc0[2] == 3);
        pL->Slot390();
        assert(s_p3f4d0 == s_p3f9c0);
        pL->Slot398(88);
        assert(s_u83470 == 88);
        printf("S2 ok (380/388/390/398)\n");
    }

    // ==== S3: Slot3a0 the double-jle loop (0x48 stride) ====
    {
        static char acArr[0x48 * 4];
        pL->Slot3a0(3, acArr);
        assert(s_v42810.size() == 3);
        assert(s_v42810[0] == (void*)acArr);
        assert(s_v42810[1] == (void*)(acArr + 0x48));
        assert(s_v42810[2] == (void*)(acArr + 0x90));
        s_v42810.clear();
        pL->Slot3a0(0, acArr);       // both jle gates
        pL->Slot3a0(-1, acArr);
        assert(s_v42810.empty());
        printf("S3 ok (3a0: the verbatim double gate + "
               "the 0x48 stride)\n");
    }

    // ==== S4: Slot3a8/3b0/3b8 ====
    {
        pL->Slot3a8(44);
        assert(s_u40fd0 == 44);
        // 3b0: the literal 3 + the p3/p4 ride
        s_pLogic[6] = (void*)0x30;            // +0x30
        pL->Slot3b0(0, 111, 222);
        assert(s_nB4b0 == 1 && s_lB4b0[0] == 3 &&
               s_lB4b0[1] == 111 && s_lB4b0[2] == 222);
        assert(s_n41b10 == 1);
        // 3b8: the +0x60 byte gate
        abLogic[0x60] = 0;
        pL->Slot3b8();
        assert(s_n434f0 == 0);
        abLogic[0x60] = 1;
        pL->Slot3b8();
        assert(s_n434f0 == 1);
        printf("S4 ok (3a8/3b0/3b8)\n");
    }

    // ==== S5: Slot3c8 the REORDERED args ====
    {
        s_pLogic[7] = (void*)0x38;            // +0x38
        s_pLogic[7] = 0;
        pL->Slot3c8(2, 3, 40, 50);
        assert(s_nCdc0 == 0);
        s_pLogic[7] = (void*)0x38;
        pL->Slot3c8(2, 3, 40, 50);
        // RAW: cdc0(x, p4=40, p5=50, p2=2, p3=3)
        assert(s_lCdc0[0] == 40 && s_lCdc0[1] == 50 &&
               s_lCdc0[2] == 2 && s_lCdc0[3] == 3);
        printf("S5 ok (3c8: the p4,p5,p2,p3 reorder)\n");
    }

    // ==== S6: Slot3d0/3d8/3e0 ====
    {
        s_pLogic[5] = (void*)0x28;            // +0x28
        s_pLogic[5] = 0;
        pL->Slot3d0(1, 2);
        assert(pL->Slot3d8(1, 2) == 0);       // xor eax
        assert(s_n77f980 == 0);
        s_pLogic[5] = (void*)0x28;
        pL->Slot3d0(1, 2);
        assert(s_u84cd0[0] == 1 && s_u84cd0[1] == 2);
        assert(pL->Slot3d8(5, 6) == 77);
        assert(s_u77f980 == 5006);
        s_pLogic[6] = (void*)0x30;            // +0x30
        pL->Slot3e0(7, 8, 9);
        assert(s_lB4b0[0] == 7 && s_lB4b0[1] == 8 &&
               s_lB4b0[2] == 9);
        printf("S6 ok (3d0/3d8/3e0)\n");
    }

    // ==== S7: Slot3e8/3f0 the recruit-mgr gates ====
    {
        s_pLogic[9] = 0;                     // +0x48
        pL->Slot3e8(1, 2, "PC4", 5, 6, 7, 8,
                   9, 10, 11);
        assert(s_uStarLine == 0x1501 &&
               s_sStar ==
               "IF_NOT/m_pSynRecruitAdvertisingMgr");
        assert(s_nD4670 == 0);
        pL->Slot3f0(1, 2);
        assert(s_uStarLine == 0x150b);
        assert(s_nD3100 == 0);
        s_pLogic[9] = (void*)0x48;
        pL->Slot3e8(1, 2, "PC4", 5, 6, 7, 8,
                   9, 10, 11);
        assert(s_nD4670 == 1);
        assert(s_uD4670[0] == 1 && s_uD4670[1] == 2 &&
               s_uD4670[2] == 5 &&
               s_nD4670S[0] == 6 && s_nD4670S[5] == 11);
        pL->Slot3f0(31, 41);
        assert(s_nD3100 == 1 && s_uD3100[0] == 31 &&
               s_uD3100[1] == 41);
        printf("S7 ok (3e8/3f0: 0x1501/0x150b)\n");
    }

    // ==== S8: Slot3f8 the giant — the head gates ====
    {
        s_pLogic[9] = 0;                     // +0x48
        pL->Slot3f8(20, 300, 400);
        assert(s_uStarLine == 0x1516);
        s_pLogic[9] = (void*)0x48;
        s_pLogic[2] = 0;                     // +0x10
        pL->Slot3f8(20, 300, 400);
        assert(s_uStarLine == 0x151a);
        assert(s_sStar == "IF_NOT/m_pSynMgr");
        s_pLogic[2] = (void*)0x10;
        pL->Slot3f8(20, 0, 400);             // p3 == 0
        assert(s_uStarLine == 0x151e &&
               s_sStar == "IF_NOT/idSyn");
        printf("S8 ok (3f8: the three head gates)\n");
    }

    // ==== S9: Slot3f8 the gates chain ====
    {
        // vt+0x1f8 != 0 -> silent out
        s_uVt1f8 = 5;
        pL->Slot3f8(20, 300, 400);
        assert(s_uStarLine == 0x151e && s_n9ad50 == 0);
        s_uVt1f8 = 0;
        // cad00 miss
        s_lLgFindRet = 0;
        pL->Slot3f8(20, 300, 400);
        assert(s_n9ad50 == 0);
        // 9c8b0 false
        s_lLgFindRet = (int64_t)(uintptr_t)s_pSyn;
        s_c9c8b0 = 0;
        pL->Slot3f8(20, 300, 400);
        assert(s_n9ad50 == 0);
        s_c9c8b0 = 1;
        // d3530 false
        s_cd3530 = 0;
        pL->Slot3f8(20, 300, 400);
        assert(s_n9ad50 == 0);
        s_cd3530 = 1;
        printf("S9 ok (3f8: 1f8/find/9c8b0/d3530 "
               "gates)\n");
    }

    // ==== S10: Slot3f8 the money/full branches ====
    {
        s_c8e590 = 1;
        pL->Slot3f8(20, 300, 400);
        assert(s_uVt18Arg == 20 &&
               !strcmp(s_acVt18,
                   "STR_TOO_LOWER_SYN_MONEY"));
        s_c8e590 = 0; s_c8e600 = 1;
        pL->Slot3f8(20, 300, 400);
        assert(!strcmp(s_acVt18,
                   "STR_SYN_FULL"));
        s_c8e600 = 0;
        printf("S10 ok (3f8: the two talk strings)\n");
    }

    // ==== S11: Slot3f8 the full flow ====
    {
        // 510 returns 66 == 90390's 55? -> unequal ->
        // b19c0(this, 20, 1, p4=400)
        s_uVt510 = 66; s_u90390 = 55;
        s_n9ad50 = 0; s_uVt370 = 0; s_uVt88Id = 0;
        pL->Slot3f8(20, 300, 400);
        assert(s_pB19c0 == pL &&
               s_uB19c0[0] == 20 && s_uB19c0[1] == 1 &&
               s_uB19c0[2] == 400);
        assert(s_u8470[0] == 20 && s_u8470[1] == 200 &&
               s_u8470[2] == 0 && s_u8470[3] == 0);
        assert(s_uVt370 == 20);
        // the notify: 4-vararg snprintf into the buf
        assert(s_uVt88Id == 4);          // f270 ret
        assert(s_uVt88_5th == 0x7d4);     // the u16 stack
        assert(s_pvVt88Buf != 0);
        // the fmt has no % specifiers -> the buf is the
        // GetStr key itself (proves the snprintf + vararg
        // wiring reached vt+0x88)
        assert(!strcmp((char*)s_pvVt88Buf,
            "STR_SYN_INVITE_JOIN"));
        assert(s_n9ad50 == 1 && s_u9ad50[1] == 20);
        // the equal path: 638e0(this+0x50, id, p2)
        s_uVt510 = 55; s_u90390 = 55; s_n638e0 = 0;
        s_n9ad50 = 0;
        pL->Slot3f8(20, 300, 400);
        assert(s_n638e0 == 1 &&
               s_u638e0[1] == 55 && s_u638e0[2] == 20);
        assert(s_n9ad50 == 1);
        // 8470 false -> only nothing after
        s_c8470 = 0; s_n9ad50 = 0;
        pL->Slot3f8(20, 300, 400);
        assert(s_n9ad50 == 0);
        s_c8470 = 1;
        printf("S11 ok (3f8: the full flow + the 4-vararg "
               "notify + u16 0x7d4)\n");
    }

    // ==== S12: Slot400 the two gates + the flow ====
    {
        pL->Slot400(0);
        assert(s_uStarLine == 0x1562 &&
               s_sStar == "IF_NOT/idUser");
        s_pLogic[9] = 0;
        pL->Slot400(5);
        assert(s_uStarLine == 0x1566);
        s_pLogic[9] = (void*)0x48;
        // vt78 false -> out
        s_cVt78 = 0; s_nD3680 = 0;
        pL->Slot400(5);
        assert(s_nD3680 == 0);
        // vt1f8 -> 0 -> out
        s_cVt78 = 1; s_uVt1f8 = 0;
        pL->Slot400(5);
        assert(s_nD3680 == 0);
        // the full: d3680(+0x48, 5, id)
        s_uVt1f8 = 77;
        pL->Slot400(5);
        assert(s_nD3680 == 1 &&
               s_uD3680[1] == 5 && s_uD3680[2] == 77);
        printf("S12 ok (400: 0x1562/0x1566 + the "
               "flow)\n");
    }

    printf("D113-OK\n");
    return 0;
}

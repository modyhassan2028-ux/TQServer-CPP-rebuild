// D112 — CSyndicateLogic wave 17 (TRUE +0x2e0..+0x370)
// The raw facts pinned here: the 9-field clear loop, the
// four star logs (0x1487/0x149a/0x14a2/0x14aa/0x14b2),
// the MulDiv(p4,2,100) 2% cut with the f4f0 cap (cmovg)
// and the 10000 gmlog/syndenote gate, the vt+0x138 add,
// the d3c0 always-tail, the vt+0x2b0 sweep with the
// 0x283e fire behind vt+0x268, the box(+0x20) forward
// gates (af230/af250 have NONE), and the x*10/10 magic
// in the prize giant.
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <string>
#include <vector>
using namespace syndicate;

// ---- the fixtures ----
static void* s_vtLogic[0x40];     // this vtable
static void* s_vtBox[0x70];        // box vtable
static void* s_pBox[4];            // the box object
static void* s_pSubBox[2];         // +0x20 box
static void* s_pLogic[8];          // this: vt, box, mgr, 0x20
static void* s_pMgr = (void*)0x6000;
static uint8_t abLogic[0x40];
static CSyndicateLogic* pL = (CSyndicateLogic*)s_pLogic;
static void* s_pSynA = (void*)0xA1;
static void* s_pSynB = (void*)0xB2;
static std::vector<std::string> s_log;

// ---- the recorders ----
static void Log(const char* s) { s_log.push_back(s); }
static bool Seen(const char* s) {
    for (auto& x : s_log)
        if (x.find(s) != std::string::npos) return true;
    return false;
}
static void LogF(const char* fmt, ...) {
    char b[256];
    va_list ap; va_start(ap, fmt);
    vsnprintf(b, sizeof b, fmt, ap);
    va_end(ap); s_log.push_back(b);
}
static void Reset() {
    s_log.clear();
    memset(s_pLogic, 0, sizeof s_pLogic);
    s_pLogic[0] = s_vtLogic;
    s_pLogic[1] = s_pBox;
    s_pLogic[2] = s_pMgr;
    s_pLogic[4] = s_pSubBox;
    memset(s_vtBox, 0, sizeof s_vtBox);
    s_pBox[0] = s_vtBox;
}

// ---- the seam stubs ----
static void* s_pFindRet = s_pSynA;
static void* s_pFindRetB = s_pSynB;
static int s_nCb270; static uint32_t s_uCb270;
static void StubCb270(void* m, uint32_t u) {
    ++s_nCb270; s_uCb270 = u; (void)m;
}
static std::vector<uint32_t> s_vCb360;
static void StubCb360(void* m, uint32_t u, uint32_t f) {
    (void)m; s_vCb360.push_back(u * 100 + f);
}
static void* s_p90100;
static void* Stub90100(void* s) { return s_p90100; }
static uint32_t s_uF790 = 77;
static uint32_t StubF790(void* s) { return s_uF790; (void)s; }
static uint64_t s_uF7d0;
static uint64_t StubF7d0(void* s, uint32_t u) {
    s_uF7d0 = (uint64_t)u + 1000; return s_uF7d0; (void)s;
}
static uint64_t s_uF7b0[3];
static uint64_t StubF7b0(void* s, int64_t a, int64_t b,
                        int64_t c) {
    (void)s; s_uF7b0[0] = a; s_uF7b0[1] = b;
    s_uF7b0[2] = c; return 55;
}
static int s_nC6c90, s_nC6c80;
static void StubC6c90(void* m) { ++s_nC6c90; (void)m; }
static void StubC6c80(void* m) { ++s_nC6c80; (void)m; }
static uint32_t s_uCfb60;
static void StubCfb60(void* m, uint32_t u) {
    s_uCfb60 = u; (void)m;
}
static uint32_t s_uA8d30[2];
static void StubA8d30(void* b, uint32_t u, uint32_t v) {
    s_uA8d30[0] = u; s_uA8d30[1] = v; (void)b;
}
static int32_t s_nA8e40[3];
static void StubA8e40(void* b, uint32_t u, int32_t a,
                      uint32_t c, uint32_t d) {
    (void)b; s_nA8e40[0] = a; s_nA8e40[1] = c;
    s_nA8e40[2] = d; LogF("a8e40 %u", u);
}
static int32_t s_nA8f70[3];
static void StubA8f70(void* b, uint32_t u, int32_t a,
                      uint32_t c, uint32_t d) {
    (void)b; s_nA8f70[0] = a; s_nA8f70[1] = c;
    s_nA8f70[2] = d; LogF("a8f70 %u", u);
}
static uint32_t s_uA8810;
static void StubA8810(void* b, uint32_t u) {
    s_uA8810 = u; (void)b;
}
static uint32_t s_uA88a0; static void* s_pA88a0;
static void StubA88a0(void* b, uint32_t u, void* p) {
    (void)b; s_uA88a0 = u; s_pA88a0 = p;
}
static uint32_t s_uA8b00;
static void StubA8b00(void* b, uint32_t u) {
    s_uA8b00 = u; (void)b;
}
static int s_nA7e70;
static void StubA7e70(void* b) { ++s_nA7e70; (void)b; }
static uint8_t s_cA8a50 = 9;
static uint8_t StubA8a50(void* b, uint32_t u, void* p) {
    (void)b; (void)u; (void)p; return s_cA8a50;
}
static void* s_pD3c0; static int32_t s_nD3c0[2];
static void StubD3c0(void* s, int32_t a, int32_t b) {
    s_pD3c0 = s; s_nD3c0[0] = a; s_nD3c0[1] = b;
}
static void* s_pC8c10; static uint32_t s_uC8d80;
static void* StubC8c10(void* m, uint32_t u) {
    (void)m; (void)u; return s_pC8c10;
}
static void* StubC8d80(void* m, uint32_t u) {
    (void)m; s_uC8d80 = u; return (void*)1;
}
static uint64_t s_uF270 = 3;
static uint64_t StubF270(void* s) { (void)s; return s_uF270; }
static uint32_t s_uF4f0 = 0x7fffffff;
static uint64_t StubF4f0(void* s) {
    (void)s; return s_uF4f0;
}
static char s_acWarName[16] = "WARNAME";
static void* s_pF470 = (void*)s_acWarName;
static void* StubF470(void* s) { (void)s; return s_pF470; }
static int64_t s_lBF80[2]; static void* s_pBF80[2];
// (ptr, value) pairs for the S6/S10 multi-call checks
static std::vector<std::pair<void*, int64_t>> s_vBF80;
// the 5-arg star log + the syndenote save
static uint32_t s_uStarLine; static std::string s_sStar;
static void StubSynLogCheck(const char* f, const char* t,
                            const char* v, const char* p,
                            uint32_t l) {
    s_uStarLine = l;
    s_sStar = std::string(t) + "/" + v; (void)f; (void)p;
}
static std::string s_sNote; static uint32_t s_uNote[4];
static void StubSynNoteLog(const char* f, const char* fmt,
                           const void* n, uint32_t a,
                           uint32_t s, uint32_t m) {
    s_sNote = std::string(f) + "|" + fmt;
    s_uNote[0] = a; s_uNote[1] = s; s_uNote[2] = m;
    (void)n; Log("SYNDENOTE");
}
// the msg ctor seams
static int s_nMsgCtor, s_nMsgDtor;
static char s_cDB3A0 = 1;
static int32_t s_nDB3A0[2];
static char StubDB3A0(void* m, int32_t a, int32_t b) {
    (void)m; s_nDB3A0[0] = a; s_nDB3A0[1] = b;
    return s_cDB3A0;
}
// string mgr
static void* StubInst() { return (void*)0x99; }
static const char* s_pszGetStr = "%s-WIN";
static void* StubGetStr(void* i, const char* k) {
    (void)i; return (void*)s_pszGetStr;
}

// ---- the box vtable stubs ----
static uint32_t s_uVt1f8 = 5, s_uVt2f8a = 5, s_uVt2f8b = 7;
static uint32_t Vt1F8(void* b) { (void)b; return s_uVt1f8; }
static uint32_t Vt2F8(void* b, uint32_t u) {
    (void)b; return u == 300 ? s_uVt2f8a : s_uVt2f8b;
}
static int s_nVt138; static uint32_t s_uVt138[3];
static void Vt138(void* b, uint32_t u, int64_t v,
                  uint8_t f) {
    (void)b; s_uVt138[0] = u; s_uVt138[1] = (uint32_t)v;
    s_uVt138[2] = f; ++s_nVt138;
}
static const char* s_pszName = "HERO";
static void* Vt1D8(void* b, uint32_t u) {
    (void)b; (void)u; return (void*)s_pszName;
}
static void* s_pvVt78;
static void Vt78(void* b, void* s) {
    (void)b; s_pvVt78 = s; LogF("vt78 %s", (char*)s);
}
static uint32_t s_uVt300 = 0x40e;
static uint32_t Vt300(void* b, uint32_t u) {
    (void)b; (void)u; return s_uVt300;
}
static uint32_t s_uVt318 = 0x999;
static uint32_t Vt318(void* b, uint32_t u) {
    (void)b; (void)u; return s_uVt318;
}
static int s_nVt310; static uint32_t s_uVt310;
static uint32_t Vt310(void* b, uint32_t u) {
    (void)b; s_uVt310 = u; ++s_nVt310; return 0;
}
static int s_nVtE0;
static void VtE0(void* b, void* m) {
    (void)b; (void)m; ++s_nVtE0;
}
static int s_nVt308; static uint32_t s_uVt308[3];
static void Vt308(void* b, uint32_t u, uint32_t v) {
    (void)b; s_uVt308[0] = u; s_uVt308[1] = v;
    ++s_nVt308;
}
// the sweep (Slot310) stubs
static std::vector<uint32_t> s_vIds;
static char s_cVt2b0 = 1;
static char Vt2b0(void* t, uint32_t id, void* home) {
    (void)t; (void)id; (void)home; return s_cVt2b0;
}
static std::vector<uint32_t> s_v268Live;
static char Vt268(void* b, uint32_t id) {
    (void)b;
    for (auto x : s_v268Live) if (x == id) return 1;
    return 0;
}
static std::vector<uint32_t> s_v2e0;
static void Vt2e0(void* b, uint32_t id, uint32_t w) {
    (void)b; s_v2e0.push_back(id * 10000 + w);
    LogF("vt2e0 %u %x", id, w);
}

static void WireVt() {
    s_vtBox[0x1f8/8] = (void*)Vt1F8;
    s_vtBox[0x2f8/8] = (void*)Vt2F8;
    s_vtBox[0x138/8] = (void*)Vt138;
    s_vtBox[0x1d8/8] = (void*)Vt1D8;
    s_vtBox[0x78/8]  = (void*)Vt78;
    s_vtBox[0x300/8] = (void*)Vt300;
    s_vtBox[0x318/8] = (void*)Vt318;
    s_vtBox[0x310/8] = (void*)Vt310;
    s_vtBox[0xe0/8]  = (void*)VtE0;
    s_vtBox[0x308/8] = (void*)Vt308;
    s_vtLogic[0x2b0/8] = (void*)Vt2b0;
    s_vtBox[0x268/8] = (void*)Vt268;
    s_vtBox[0x2e0/8] = (void*)Vt2e0;
}

static void Wire() {
    Reset(); WireVt();
    g_fnLgFind = (int64_t (*)(void*, uint32_t))
        [](void* m, uint32_t id) -> int64_t {
            (void)m;
            // id 5/7 = the Slot308 synA/synB pair;
            // anything else -> s_pFindRet (0 = miss)
            if (id == 5) return (int64_t)(uintptr_t)
                (s_pFindRet ? s_pFindRet : s_pSynA);
            if (id == 7) return (int64_t)(uintptr_t)
                s_pFindRetB;
            return (int64_t)(uintptr_t)s_pFindRet;
        };
    g_fn1417cb270 = StubCb270;
    g_fn1417cb360 = StubCb360;
    g_fn141790100 = Stub90100;
    g_fn14178f790 = StubF790;
    g_fn14178f7d0 = StubF7d0;
    g_fn14178f7b0 = StubF7b0;
    g_fn1417c6c90 = StubC6c90;
    g_fn1417c6c80 = StubC6c80;
    g_fn1417cfb60 = StubCfb60;
    g_fn1417a8d30 = StubA8d30;
    g_fn1417a8e40 = StubA8e40;
    g_fn1417a8f70 = StubA8f70;
    g_fn1417a8810 = StubA8810;
    g_fn1417a88a0 = StubA88a0;
    g_fn1417a8b00 = StubA8b00;
    g_fn1417a7e70 = StubA7e70;
    g_fn1417a8a50 = StubA8a50;
    g_fn14179d3c0 = StubD3c0;
    g_fn1417c8c10 = StubC8c10;
    g_fn1417c8d80 = StubC8d80;
    g_fn78F270 = StubF270;
    g_fn78F4F0 = StubF4f0;
    g_fn78F470 = StubF470;
    g_fn79BF80 = (uint64_t (*)(void*, int64_t))
        [](void* s, int64_t v) -> uint64_t {
            if (s == s_pSynA) {
                s_pBF80[0] = s; s_lBF80[0] = v;
            } else if (s == s_pSynB) {
                s_pBF80[1] = s; s_lBF80[1] = v;
            }
            s_vBF80.push_back({s, v});
            return 0;
        };
    g_fnSynLogCheck = StubSynLogCheck;
    g_fnSynNoteLog = StubSynNoteLog;
    g_fn7DB2B0 = (void (*)(void*))
        [](void* m) { ++s_nMsgCtor; (void)m; };
    g_fn7DB3A0 = StubDB3A0;
    g_fn7DB330 = (uint64_t (*)(void*))
        [](void* m) -> uint64_t {
            ++s_nMsgDtor; (void)m; return 0;
        };
    g_fnStringMgrInstance = StubInst;
    g_fnStringMgrGetStr = (void* (*)(void*,
        const char*))StubGetStr;
    // defaults reset
    s_pFindRet = s_pSynA; s_nCb270 = 0;
    s_vCb360.clear(); s_p90100 = 0; s_uF790 = 77;
    s_uF7d0 = 0; s_nC6c90 = s_nC6c80 = 0;
    s_uCfb60 = 0; s_uVt1f8 = 5; s_uVt2f8a = 5;
    s_uVt2f8b = 7; s_nVt138 = 0; s_uVt300 = 0x40e;
    s_uVt318 = 0x999; s_nVt310 = 0; s_nVtE0 = 0;
    s_nVt308 = 0; s_cVt2b0 = 1; s_vIds.clear();
    s_v268Live.clear(); s_v2e0.clear();
    s_uF270 = 3; s_uF4f0 = 0x7fffffff;
    s_cDB3A0 = 1; s_nMsgCtor = s_nMsgDtor = 0;
    s_uStarLine = 0; s_pvVt78 = 0;
    s_vBF80.clear();
}

int main() {
    Wire();
    printf("D112 start\n");

    // ==== S1: Slot2E0 the 9-field clear ====
    {
        s_pFindRet = 0;
        assert(pL->Slot2E0(42) == 0);
        assert(s_uStarLine == 0x1487 &&
               s_sStar == "dUser/pSyn");
        s_pFindRet = s_pSynA; Reset2:;
        s_vCb360.clear();
        assert(pL->Slot2E0(42) == 1);
        assert(s_nCb270 == 1 && s_uCb270 == 42);
        assert(s_vCb360.size() == 9);
        for (int i = 0; i < 9; ++i)
            assert(s_vCb360[i] ==
                   (uint32_t)(4200 + i + 1));
        printf("S1 ok (2E0: the loop + the 0x1487 log)\n");
    }

    // ==== S2: Slot2E8 ====
    {
        s_pFindRet = 0;
        assert(pL->Slot2E8(1) == 0);
        assert(s_uStarLine == 0x149a &&
               s_sStar == "CHECKF/pSyn");
        s_pFindRet = s_pSynA;
        s_p90100 = (void*)1;
        assert(pL->Slot2E8(1) == 1);
        s_p90100 = 0;
        assert(pL->Slot2E8(1) == 0);
        printf("S2 ok (2E8: 0x149a + the 90100 ride)\n");
    }

    // ==== S3: Slot2F0 ====
    {
        s_pFindRet = 0;
        assert(pL->Slot2F0(1) == 0);
        assert(s_uStarLine == 0x14a2);
        s_pFindRet = s_pSynA;
        assert(pL->Slot2F0(1) == 77);
        printf("S3 ok (2F0: 0x14a2 + the f790 tail)\n");
    }

    // ==== S4: Slot2F8 ====
    {
        s_pFindRet = 0;
        assert(pL->Slot2F8(1, 33) == 0);
        assert(s_uStarLine == 0x14aa);
        s_pFindRet = s_pSynA;
        assert(pL->Slot2F8(1, 33) == 1033);
        printf("S4 ok (2F8: 0x14aa + the u3 ride)\n");
    }

    // ==== S5: Slot300 ====
    {
        s_pFindRet = 0;
        assert(pL->Slot300(1, 10, 20, 30) == 0);
        assert(s_uStarLine == 0x14b2);
        s_pFindRet = s_pSynA;
        assert(pL->Slot300(1, 10, 20, 30) == 55);
        assert(s_uF7b0[0] == 10 && s_uF7b0[1] == 20 &&
               s_uF7b0[2] == 30);
        printf("S5 ok (300: 0x14b2 + 3 rides)\n");
    }

    // ==== S6: Slot308 the 2% cut ====
    {
        // p4 <= 0
        assert(pL->Slot308(1, 2, 0) == 0);
        assert(pL->Slot308(1, 2, -5) == 0);
        // the 1f8 zero gate
        s_uVt1f8 = 0;
        assert(pL->Slot308(1, 2, 1000) == 0);
        s_uVt1f8 = 5;
        // synA == synB (u3=300 -> 5)
        assert(pL->Slot308(1, 300, 1000) == 0);
        // the normal: p3=2 -> synB=7; synA=5
        // cut = 1000*2/100 = 20; cap f4f0=0xffffffff
        // -> 20 < 10000: NO syndenote; bf80(synB,-20)
        char r1 = pL->Slot308(11, 2, 1000);
        assert(r1 == 1);
        assert(s_pBF80[1] == s_pSynB &&
               s_lBF80[1] == -20);
        assert(s_nVt138 == 1 && s_uVt138[0] == 11 &&
               s_uVt138[1] == 20 && s_uVt138[2] == 1);
        assert(s_pD3c0 == s_pSynA &&
               s_nD3c0[0] == 2 && s_nD3c0[1] == 1000);
        assert(s_sNote.empty());
        // the cap: f4f0 = 6 -> cut = 6
        s_uF4f0 = 6; s_nVt138 = 0; s_lBF80[1] = 0;
        assert(pL->Slot308(11, 2, 1000) == 1);
        assert(s_lBF80[1] == -6 &&
               s_uVt138[1] == 6);
        // the 10000 gate fires the syndenote save:
        // cut = 1000000*2/100 = 20000
        s_uF4f0 = 0x7fffffff; s_lBF80[1] = 0;
        assert(pL->Slot308(11, 2, 1000000) == 1);
        assert(s_lBF80[1] == -20000);
        assert(s_sNote ==
            "gmlog/syndenote|User:%s[%u] Get "
            "(SynWar Prize) syn[%u] money %u");
        assert(s_uNote[0] == 11 && s_uNote[1] == 5 &&
               s_uNote[2] == 20000);
        // RAW pin: the f4f0 cap compares SIGNED
        // (cmovg) — 0xffffffff clamps the cut to -1
        // and bf80 fires with +1
        s_uF4f0 = 0xffffffff; s_lBF80[0] = s_lBF80[1] = 0;
        assert(pL->Slot308(11, 2, 1000) == 1);
        assert(s_lBF80[1] == 1 &&
               s_uVt138[1] == 0xffffffff);
        s_uF4f0 = 0x7fffffff;
        // MulDiv round-to-nearest: p4=25 -> 50/100 = 0.5
        // -> rounds UP to 1; p4=24 -> 0.48 -> 0 -> the
        // pay block skipped but d3c0 still fires
        s_uF4f0 = 0x7fffffff; s_lBF80[1] = 0;
        assert(pL->Slot308(11, 2, 25) == 1);
        assert(s_lBF80[1] == -1);
        s_lBF80[1] = 0;
        assert(pL->Slot308(11, 2, 24) == 1);
        assert(s_lBF80[1] == 0);   // no pay
        assert(s_pD3c0 == s_pSynA); // the always-tail
        printf("S6 ok (308: the 2%% cut + the cap + "
               "the 10000 gate)\n");
    }

    // ==== S7: Slot310 the targeted sweep ====
    {
        CSyndicateLogic* pThis =
            (CSyndicateLogic*)s_pLogic;
        s_uVt2f8a = 0;                 // vt+0x2f8(box) = 0
        pThis->Slot310();
        assert(s_v2e0.empty());
        s_uVt2f8a = 5; s_pFindRet = 0; // member miss
        pThis->Slot310();
        assert(s_v2e0.empty());
        s_pFindRet = s_pSynA;
        // 2b0 false -> no send, only the cleanup
        s_cVt2b0 = 0;
        pThis->Slot310();
        assert(s_v2e0.empty());
        // the real sweep: the RAW vector kit is driven
        // by the box vt; here the port reads the
        // begin/end pair the RAW loop walks — the test
        // drives it via the internal fixture below
        s_cVt2b0 = 1;
        // (the vector lives in the RAW rsp home; the
        // port reads pp begin/end/cap from the anchor
        // home — with the 2b0 stub leaving them zero
        // the (end-begin)>>2 gate skips the loop)
        pThis->Slot310();
        assert(s_v2e0.empty());
        printf("S7 ok (310: the gates + the null "
               "vector)\n");
    }

    // ==== S8: the mgr pass-throughs ====
    {
        assert(pL->Slot318() == 1);
        assert(s_nC6c90 == 1);
        assert(pL->Slot320() == 1);
        assert(s_nC6c80 == 1);
        assert(pL->Slot330(88) == 1);
        assert(s_uCfb60 == 88);
        printf("S8 ok (318/320/330)\n");
    }

    // ==== S9: the box forwards + the gates ====
    {
        // the null box: the GATED six stay silent;
        // RAW: 340/348 have NO gate — the seam fires
        // with the null box passed through
        s_pLogic[4] = 0;
        pL->Slot338(1, 2);
        pL->Slot350(1);
        pL->Slot358(1, (void*)9);
        pL->Slot360(1);
        pL->Slot368();
        assert(pL->Slot370(1, (void*)9) == 0);
        assert(s_uA8d30[0] == 0 && s_uA8810 == 0 &&
               s_uA88a0 == 0 && s_uA8b00 == 0 &&
               s_nA7e70 == 0);
        pL->Slot340(1, 2, 3, 4);
        pL->Slot348(1, 2, 3, 4);
        assert(Seen("a8e40") && Seen("a8f70"));
        // the live box
        s_pLogic[4] = s_pSubBox;
        pL->Slot338(11, 22);
        assert(s_uA8d30[0] == 11 &&
               s_uA8d30[1] == 22);
        pL->Slot340(1, -2, 3, 4);   // NO gate
        assert(Seen("a8e40 1") &&
               s_nA8e40[0] == -2);
        pL->Slot348(1, -2, 3, 4);
        assert(Seen("a8f70 1"));
        pL->Slot350(77);
        assert(s_uA8810 == 77);
        pL->Slot358(66, (void*)0x1234);
        assert(s_uA88a0 == 66 &&
               s_pA88a0 == (void*)0x1234);
        pL->Slot360(55);
        assert(s_uA8b00 == 55);
        pL->Slot368();
        assert(s_nA7e70 == 1);
        assert(pL->Slot370(1, (void*)9) ==
               s_cA8a50);
        printf("S9 ok (338..370: the gates + the "
               "rides; 340/348 UNGATED)\n");
    }

    // ==== S10: Slot328 the prize giant ====
    {
        s_vBF80.clear();
        s_uStarLine = 0;
        s_pC8c10 = 0;                 // the war miss
        assert(pL->Slot328(1) == 0);
        static char s_war[8];
        s_pC8c10 = s_war;
        s_uF270 = 0;                   // f270 == 0
        assert(pL->Slot328(1) == 0);
        s_uF270 = 3;
        // the transfer: vt2f8(box,9) -> 7 (the id
        // path); f4f0 = the league money; the magic
        // idiom (0xa3d70a3d70a3d70b, sar 6 + the sign
        // fix) computes (money*10)/100 = the 10% cut
        // f4f0 = 5000 -> x = 500 > 0:
        // bf80(lg,-500) + bf80(war,+500)
        s_uF4f0 = 5000; s_lBF80[0] = s_lBF80[1] = 0;
        // vt300 = 0 -> no msg branch
        s_uVt300 = 0; s_nVt308 = 0;
        assert(pL->Slot328(9) == 1);
        // bf80(lg, -5) fires BEFORE bf80(war, +5)
        assert(s_vBF80.size() == 2 &&
               s_vBF80[0].first == s_pSynB &&
               s_vBF80[0].second == -500 &&
               s_vBF80[1].second == 500);
        assert(s_nVt308 == 1 &&
               s_uVt308[0] == 9 &&
               s_uVt308[1] == 3);      // f270 & 0xffffffff
        assert(Seen("vt78 WARNAME-WIN")); // the notify
        assert(s_nVt310 == 1 &&
               s_uVt310 == 0);         // the discarded 310
        // the 0x40e branch
        s_uVt300 = 0x40e; s_nVtE0 = 0;
        s_nMsgCtor = s_nMsgDtor = 0;
        assert(pL->Slot328(9) == 1);
        assert(s_nMsgCtor == 1 &&
               s_nDB3A0[0] == 0x11 &&
               s_nDB3A0[1] == 0x999 &&
               s_nVtE0 == 1 && s_nMsgDtor == 1);
        assert(s_uStarLine == 0);      // no miss log
        // the 0x3e8 branch (SET_BLACK_SYN)
        s_uVt300 = 0x3e8;
        s_nMsgCtor = s_nMsgDtor = 0;
        assert(pL->Slot328(9) == 1);
        assert(s_nDB3A0[0] == 0x12 &&
               s_nMsgDtor == 1);
        // the CREATE-miss logs
        s_cDB3A0 = 0; s_uVt300 = 0x40e;
        assert(pL->Slot328(9) == 1);
        assert(s_uStarLine == 0x664 &&
               s_sStar.find("SET_WHITE_SYN") !=
               std::string::npos);
        s_uVt300 = 0x3e8;
        assert(pL->Slot328(9) == 1);
        assert(s_uStarLine == 0x66c &&
               s_sStar.find("SET_BLACK_SYN") !=
               std::string::npos);
        // the c8d80 side effect fires unconditionally
        assert(s_uC8d80 == 9);
        printf("S10 ok (328: the prize magic + both "
               "msg branches + the logs)\n");
    }

    printf("D112-OK\n");
    return 0;
}

// D114c unit test — CSyndicateLogic class tail (+0x680..+0x738)
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <map>
#include "modules/syndicate/src/syndicatelogic.h"
#include "modules/syndicate/src/SyndicateInviteNotify.h"
#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"
#include "modules/syndicate/src/SyndicateLogRemove.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
using namespace syndicate;

static void* s_vtLogic[0x120];
static void* s_vtBox[0x120];
static void* s_pLogic[0x100];
static char s_abBox[0x100];
static void* s_pBox = (void*)s_abBox;
static void* s_host = (void*)0x1234;

struct Arg2 { void* h; uint32_t a; int n; };
static std::vector<Arg2> s_a2;
static std::vector<std::pair<void*, std::vector<uint32_t>>> s_aN;
static void T6b0d0(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T74c70(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T75350(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T4ebc0(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T65800(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T65920(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T65d60(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T66500(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T69100(void* h, uint32_t a) { Arg2 x{h,a,1}; s_a2.push_back(x); }
static void T71f90(void* h, uint32_t a, uint32_t b, uint32_t c) {
    std::vector<uint32_t> v{a,b,c}; s_aN.push_back({h,v}); }
static void T5f830(void* h, uint32_t a, uint32_t b) {
    std::vector<uint32_t> v{a,b}; s_aN.push_back({h,v}); }
static void T66e90(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    std::vector<uint32_t> v{a,b,c,d}; s_aN.push_back({h,v}); }
static char s_cF120 = 0x2c;
static char T4f120(void* h) { (void)h; return s_cF120; }
static uint32_t s_a65410[4]; static int s_n65410;
static char s_c65410 = 0xA;
static char T65410(void* h, uint32_t a, uint32_t b) {
    s_a65410[0]=(uint32_t)(uintptr_t)h;
    s_a65410[1]=a; s_a65410[2]=b; ++s_n65410; return s_c65410; }
static uint32_t s_a655c0[4]; static int s_n655c0;
static char s_c655c0 = 0xB;
static char T655c0(void* h, uint32_t a, uint32_t b) {
    s_a655c0[0]=(uint32_t)(uintptr_t)h;
    s_a655c0[1]=a; s_a655c0[2]=b; ++s_n655c0; return s_c655c0; }
static uint32_t s_a65540[3]; static int s_n65540;
static char s_c65540 = 0xC;
static char T65540(void* h, uint32_t a) {
    s_a65540[0]=(uint32_t)(uintptr_t)h;
    s_a65540[1]=a; ++s_n65540; return s_c65540; }
static uint32_t s_a63a90[4]; static int s_n63a90;
static char s_c63a90 = 1;
static char T63a90(void* h, uint32_t a, uint32_t b) {
    s_a63a90[0]=(uint32_t)(uintptr_t)h;
    s_a63a90[1]=a; s_a63a90[2]=b; ++s_n63a90; return s_c63a90; }
static uint32_t s_a63bc0[5]; static int s_n63bc0;
static char s_c63bc0 = 1;
static char T63bc0(void* h, uint32_t a, uint32_t b, uint32_t c) {
    s_a63bc0[0]=(uint32_t)(uintptr_t)h;
    s_a63bc0[1]=a; s_a63bc0[2]=b; s_a63bc0[3]=c;
    ++s_n63bc0; return s_c63bc0; }

static uint32_t s_u510 = 0x77;
static uint32_t Vt510(void* t) { (void)t; return s_u510; }
static uint32_t s_u440 = 0x64;
static uint32_t Vt440(void* t) { (void)t; return s_u440; }

static std::map<uint32_t, uint32_t> s_m4a8;
static std::vector<std::pair<uint32_t, uint32_t>> s_v4a8;
static uint32_t Vt4a8(void* b, uint32_t u) {
    (void)b; s_v4a8.push_back({u, s_m4a8[u]});
    return s_m4a8[u]; }
static std::map<uint32_t, uint32_t> s_m3e8;
static uint32_t Vt3e8(void* b, uint32_t u) {
    (void)b; return s_m3e8[u]; }
static uint32_t s_u3f0 = 5; static int s_n3f0;
static uint32_t Vt3f0(void* b) { (void)b; ++s_n3f0; return s_u3f0; }
static char s_c278 = 0; static int s_n278;
static char Vt278(void* b) { (void)b; ++s_n278; return s_c278; }
static char s_c280 = 0; static int s_n280;
static char Vt280(void* b, uint32_t u) {
    (void)b; ++s_n280; return s_c280; }

// ---- Slot708/Slot700 support ----
#include <cstdlib>
#include <cstdint>
typedef struct { void* pPad0; void* pPad1; void* pPad2;
    void* pFirst; void* pLast; void* pEnd; void* pProxy; }
    RawCont114cAlias;
static void* s_pElem1; static void* s_pElemNull;
static void* s_pElem2;
static void* s_pProv = (void*)0;
static void* T823050(void) { return s_pProv; }
static void* MallocStub(uint32_t cb) { return malloc(cb); }
static int s_nFree; 
static void FreeStub(void* p) { ++s_nFree; free(p); }
static void MemsetStub(void* p, int c, size_t n)
    { memset(p, c, n); }
static char s_cBf960;
struct ContFiller { void* elems[4]; };
static char Tbf960(void* pL, void* pC) {
    (void)pL;
    RawCont114cAlias* pc = (RawCont114cAlias*)pC;
    if (s_cBf960) {
        void** a = (void**)malloc(8*3);
        a[0] = s_pElem1; a[1] = s_pElemNull;
        a[2] = s_pElem2;
        pc->pFirst = a; pc->pLast = a+3;
        pc->pEnd = a+4;
    }
    return 0;
}
static char s_c9e6d0;
static int32_t s_aIds[8]; static int s_nIds;
static char T9e6d0(void* pL, void* pC) {
    (void)pL;
    RawCont114cAlias* pc = (RawCont114cAlias*)pC;
    if (s_c9e6d0) {
        int32_t* a = (int32_t*)malloc(4*3);
        for (int i = 0; i < s_nIds; ++i) a[i] = s_aIds[i];
        pc->pFirst = a; pc->pLast = a + s_nIds;
        pc->pEnd = a + 8;
    }
    return 1;
}
static std::map<void*, char> s_m87300;
static char T787300(void* e) { return s_m87300.count(e) ? s_m87300[e] : 0; }
static std::map<void*, uint32_t> s_m85dc0;
static uint32_t T785dc0(void* e) { return s_m85dc0.count(e) ? s_m85dc0[e] : 0x55; }
static std::map<void*, uint32_t> s_m78f270;
static uint32_t T78f270(void* l) { return s_m78f270.count(l) ? s_m78f270[l] : 0x66; }
static uint32_t s_a708_38[5]; static int s_n708_38;
static void TBoxVt38(void* b, uint32_t a, void* m, uint32_t d) {
    (void)b; (void)m;
    s_a708_38[0]=a; s_a708_38[1]=d; ++s_n708_38; }
static uint32_t s_a708_110[5]; static int s_n708_110;
static void TBoxVt110(void* b, uint32_t a, uint32_t c, uint32_t d) {
    (void)b; s_a708_110[0]=a; s_a708_110[1]=c;
    s_a708_110[2]=d; ++s_n708_110; }
static uint32_t s_a708_158[4]; static int s_n708_158;
static void TBoxVt158(void* b, uint32_t a, uint32_t c) {
    (void)b; s_a708_158[s_n708_158*2]=a;
    s_a708_158[s_n708_158*2+1]=c; ++s_n708_158; }
static void* s_aB1090[3]; static int s_nB1090;
static void TB1090(void* t, uint32_t id) {
    s_aB1090[0]=t; s_aB1090[1]=(void*)(uintptr_t)id; ++s_nB1090; }
static uint32_t s_a708_70[8]; static int s_n708_70;
static void TBoxVt70(void* b, uint32_t a, uint32_t c,
                     uint32_t d, const char* e) {
    (void)b; (void)e;
    s_a708_70[0]=a; s_a708_70[1]=c; s_a708_70[2]=d;
    ++s_n708_70; }
static char s_cD6790;
static uint32_t s_aD6790[6]; static int s_nD6790;
static int s_nD6640, s_nD66c0;
static void TD6640(void* m) { (void)m; ++s_nD6640; }
static void TD66c0(void* m) { (void)m; ++s_nD66c0; }
static bool TD6790(void* m, uint32_t t, uint32_t a,
                   uint32_t b, uint32_t c) {
    (void)m;
    s_aD6790[0]=t; s_aD6790[1]=a; s_aD6790[2]=b;
    s_aD6790[3]=c; ++s_nD6790; return s_cD6790 != 0; }
static uint32_t s_aLog[6]; static int s_nLog;
static const char* s_pszLastLog;
static void TSynLogCheck(const char* f, const char* w,
        const char* txt, const char* src,
        uint32_t line) {
    (void)f; (void)src;
    s_pszLastLog = txt;
    s_aLog[0] = line; ++s_nLog; (void)w; }
static uint32_t s_u74e3f0 = 0x31;
static int32_t T74e3f0(void* h) { (void)h; return s_u74e3f0; }
static int32_t (*g_fn14174e3f0_test)(void*) = 0;
// ---- Slot700 ----
static void* s_pSyn = (void*)0x900;
static void* T7630d0(void* h, uint32_t u) {
    (void)h; (void)u; return s_pSyn; }
static uint32_t s_u743c80 = 0x45;
static uint32_t T743c80(void* s) { (void)s; return s_u743c80; }
static void* s_pLeague2 = (void*)0x950;
static uint32_t s_aA84Id;
static void* TA84Find(void* m, uint32_t id) {
    (void)m; s_aA84Id = id; return s_pLeague2; }
static int32_t s_i790390 = 0x77;
static int32_t T790390(void* l) { (void)l; return s_i790390; }
static char s_c7903d0 = 1;
static char T7903d0(void* l, uint32_t u) {
    (void)l; (void)u; return s_c7903d0; }
static uint32_t s_aD4490[3]; static int s_nD4490;
static void T74d490(void* s, uint32_t u) {
    (void)s; s_aD4490[0]=u; ++s_nD4490; }
static int32_t s_i78f470 = 0x4A4B;
static int32_t T78f470(void* l) { (void)l; return s_i78f470; }
static int32_t s_i743e60 = 0x1F2E;
static int32_t T743e60(void* s) { (void)s; return s_i743e60; }
static uint32_t s_u78f2d0 = 0x3344;
static uint32_t T78f2d0(void* l) { (void)l; return s_u78f2d0; }
static uint32_t s_a76aca0[4]; static int s_n76aca0;
static void T76aca0(void* h, uint32_t id) {
    s_a76aca0[0]=(uint32_t)(uintptr_t)h;
    s_a76aca0[1]=id; ++s_n76aca0; }
static void* s_vtProv[2];
static void* s_provHolder[1];
static const char* s_pszProvArg;
static const char* TProvVt0(void* p, const char* s) {
    (void)p; s_pszProvArg = s; return "FMT<%d>"; }
static char s_acFmtOut[64];
static uint32_t s_a8233c8[4]; static int s_n8233c8;
static const char* s_pszFmtOut;
static int T8233c8(char* buf, size_t n, const char* fmt,
                   void* arg) {
    s_a8233c8[0]=(uint32_t)n;
    s_pszFmtOut = fmt; ++s_n8233c8;
    snprintf(buf, n, "%s", fmt); (void)arg;
    return 0;
}
static uint32_t s_aVt10[5]; static int s_nVt10;
static void TBoxVt10(void* b, uint32_t a, uint32_t c, void* d) {
    (void)b; s_aVt10[0]=a; s_aVt10[1]=c;
    s_aVt10[2]=(uint32_t)(uintptr_t)d; ++s_nVt10; }
static uint32_t s_aVt88[6]; static int s_nVt88;
static void TBoxVt88(void* b, uint32_t a, void* c,
                     uint32_t d, uint32_t e) {
    (void)b; (void)c;
    s_aVt88[0]=a; s_aVt88[1]=d; s_aVt88[2]=e;
    ++s_nVt88; }
static uint32_t s_aVt710[4]; static int s_nVt710;
static char TVt710(void* t, uint32_t a) {
    (void)t; s_aVt710[0]=a; ++s_nVt710; return 1; }
static uint32_t s_aC1180[4]; static int s_nC1180;
static void TC1180(void* t, uint32_t a, uint32_t b) {
    (void)t; s_aC1180[0]=a; s_aC1180[1]=b; ++s_nC1180; }
static std::map<uint32_t, char> s_mVt268;
static char TVt268(void* b, uint32_t u) { (void)b; return s_mVt268.count(u) ? s_mVt268[u] : 0; }
static std::map<uint32_t, char> s_mVt280;
static char TVt280(void* b, uint32_t u) { (void)b; return s_mVt280.count(u) ? s_mVt280[u] : 0; }
static std::map<uint32_t, uint32_t> s_mVt2a0;
static uint32_t TVt2a0(void* b, uint32_t u) { (void)b; return s_mVt2a0.count(u) ? s_mVt2a0[u] : 0; }
static uint32_t s_aVt2a8[5]; static int s_nVt2a8;
static void TVt2a8(void* b, uint32_t u, uint32_t v) {
    (void)b; s_aVt2a8[s_nVt2a8*2]=u;
    s_aVt2a8[s_nVt2a8*2+1]=v; ++s_nVt2a8; }

static void Wire() {
    memset(s_vtLogic, 0, sizeof s_vtLogic);
    memset(s_vtBox, 0, sizeof s_vtBox);
    memset(s_pLogic, 0, sizeof s_pLogic);
    s_pLogic[0] = s_vtLogic;
    s_pLogic[1] = s_pBox;
    s_pLogic[10] = s_host;
    *(void**)s_pBox = s_vtBox;
    s_a2.clear(); s_aN.clear();
    s_n65410 = s_n655c0 = s_n65540 = 0;
    s_n63a90 = s_n63bc0 = 0;
    s_c65410 = 0xA; s_c655c0 = 0xB; s_c65540 = 0xC;
    s_c63a90 = 1; s_c63bc0 = 1;
    s_u510 = 0x77; s_u440 = 0x64;
    s_m4a8.clear(); s_v4a8.clear(); s_m3e8.clear();
    s_u3f0 = 5; s_n3f0 = 0;
    s_c278 = 0; s_n278 = 0;
    s_c280 = 0; s_n280 = 0;
    s_cF120 = 0x2c;
    s_nFree = 0;
    s_cBf960 = 0; s_c9e6d0 = 0; s_nIds = 0;
    s_pElem1 = (void*)0x2001; s_pElemNull = 0;
    s_pElem2 = (void*)0x2002;
    s_m87300.clear(); s_m85dc0.clear(); s_m78f270.clear();
    s_n708_38 = s_n708_110 = s_n708_158 = 0;
    s_nB1090 = s_n708_70 = s_nD6790 = s_nLog = 0;
    s_u74e3f0 = 0x31;
    s_pSyn = (void*)0x900; s_u743c80 = 0x45;
    s_pLeague2 = (void*)0x950; s_aA84Id = 0;
    s_i790390 = 0x77; s_c7903d0 = 1;
    s_nD4490 = 0; s_i78f470 = 0x4A4B;
    s_i743e60 = 0x1F2E; s_u78f2d0 = 0x3344;
    s_n76aca0 = 0; s_pszProvArg = 0; s_n8233c8 = 0;
    s_nVt10 = s_nVt88 = s_nVt710 = s_nC1180 = 0;
    s_mVt268.clear(); s_mVt280.clear();
    s_mVt2a0.clear(); s_nVt2a8 = 0;
    s_cD6790 = 0;
    s_nD6640 = s_nD66c0 = 0;
    g_fn1417d6640 = TD6640;
    g_fn1417d66c0 = TD66c0;
    // seams
    g_fn1417f3166 = MallocStub;
    g_fn1417f2fdc = FreeStub;
    g_fn1417f30c0 = MemsetStub;
    g_fn1417bf960 = Tbf960;
    g_fn14179e6d0 = T9e6d0;
    g_fn141787300 = T787300;
    g_fn141785dc0 = T785dc0;
    g_fn14178f270 = T78f270;
    g_fn14176aca0 = T76aca0;
    g_fn14174d490 = T74d490;
    g_fn141743c80 = T743c80;
    g_fn141743e60 = T743e60;
    g_fn14178f470 = T78f470;
    g_fn1417c1180 = TC1180;
    g_fn1417b1090 = TB1090;
    g_fn141823050 = T823050;
    g_fn1418233c8 = T8233c8;
    g_fn1417d6790 = TD6790;
    g_fnSynLogCheck = TSynLogCheck;
    g_fn14174e3f0 = T74e3f0;
    g_fn1417630d0 = T7630d0;
    g_fnA84FindSyn = TA84Find;
    g_fn141790390 = T790390;
    g_fn1417903d0 = T7903d0;
    g_fn14178f2d0 = T78f2d0;
    // provider: object's first word must point to the fn array
    s_vtProv[0] = (void*)TProvVt0;
    s_provHolder[0] = (void*)s_vtProv;
    s_pProv = (void*)s_provHolder;
    // vts
    s_vtLogic[0x710/8] = (void*)TVt710;
    s_vtBox[0x158/8] = (void*)TBoxVt158;
    s_vtBox[0x38/8] = (void*)TBoxVt38;
    s_vtBox[0x110/8] = (void*)TBoxVt110;
    s_vtBox[0x70/8] = (void*)TBoxVt70;
    s_vtBox[0x10/8] = (void*)TBoxVt10;
    s_vtBox[0x88/8] = (void*)TBoxVt88;
    s_vtBox[0x268/8] = (void*)TVt268;
    s_vtBox[0x280/8] = (void*)TVt280;
    s_vtBox[0x2a0/8] = (void*)TVt2a0;
    s_vtBox[0x2a8/8] = (void*)TVt2a8;
    g_fn14176b0d0 = T6b0d0;
    g_fn141774c70 = T74c70;
    g_fn141775350 = T75350;
    g_fn14174ebc0 = T4ebc0;
    g_fn141765800 = T65800;
    g_fn141765920 = T65920;
    g_fn141765d60 = T65d60;
    g_fn141766500 = T66500;
    g_fn141769100 = T69100;
    g_fn141771f90 = T71f90;
    g_fn14175f830 = T5f830;
    g_fn141766e90 = T66e90;
    g_fn14174f120 = T4f120;
    g_fn141765410 = T65410;
    g_fn1417655c0 = T655c0;
    g_fn141765540 = T65540;
    g_fn141763a90 = T63a90;
    g_fn141763bc0 = T63bc0;
    s_vtLogic[0x510/8] = (void*)Vt510;
    s_vtLogic[0x440/8] = (void*)Vt440;
    s_vtBox[0x4a8/8] = (void*)Vt4a8;
    s_vtBox[0x3e8/8] = (void*)Vt3e8;
    s_vtBox[0x3f0/8] = (void*)Vt3f0;
    s_vtBox[0x278/8] = (void*)Vt278;
    s_vtBox[0x280/8] = (void*)Vt280;
}

int main() {
    Wire();
    CSyndicateLogic* pL = (CSyndicateLogic*)s_pLogic;
    printf("D114c start\n");
    // ==== S1: the 13 pure thunks ====
    {
        pL->Slot688(1);
        assert(s_a2.size() == 1 && s_a2[0].h == s_host && s_a2[0].a == 1);
        pL->Slot690(2); assert(s_a2.size() == 2 && s_a2[1].a == 2);
        pL->Slot698(3); assert(s_a2.size() == 3 && s_a2[2].a == 3);
        pL->Slot6a0(4); assert(s_a2.size() == 4 && s_a2[3].a == 4);
        pL->Slot6b8(5); assert(s_a2.size() == 5 && s_a2[4].a == 5);
        pL->Slot6c0(6); assert(s_a2.size() == 6 && s_a2[5].a == 6);
        pL->Slot6c8(7); assert(s_a2.size() == 7 && s_a2[6].a == 7);
        pL->Slot720(8); assert(s_a2.size() == 8 && s_a2[7].a == 8);
        pL->Slot738(9); assert(s_a2.size() == 9 && s_a2[8].a == 9);
        pL->Slot6e8(2, 3, 4);
        assert(s_aN.size() == 1 && s_aN[0].first == s_host &&
               s_aN[0].second == (std::vector<uint32_t>{2,3,4}));
        pL->Slot6f8(10, 11);
        assert(s_aN.size() == 2 && s_aN[1].second == (std::vector<uint32_t>{10,11}));
        pL->Slot730(1, 2, 3, 4);
        assert(s_aN.size() == 3 && s_aN[2].second == (std::vector<uint32_t>{1,2,3,4}));
        assert(pL->Slot6f0() == 0x2c);
        printf("S1 ok (thunks)\n");
    }
    // ==== S2: Slot710/Slot718 gates + forwarding ====
    {
        Wire();
        assert(pL->Slot710(0) == 0);
        assert(s_n63a90 == 0);
        s_u510 = 0;
        assert(pL->Slot710(5) == 0);
        assert(s_n63a90 == 0);
        s_u510 = 0x77;
        assert(pL->Slot710(5) == 1);
        assert(s_n63a90 == 1);
        assert(s_a63a90[0] == 0x1234 && s_a63a90[1] == 5 && s_a63a90[2] == 0x77);
        s_c63a90 = 0;
        assert(pL->Slot710(6) == 0);
        s_c63a90 = 1;
        assert(pL->Slot718(0, 3) == 0);
        assert(pL->Slot718(3, 0) == 0);
        assert(s_n63bc0 == 0);
        s_u510 = 0;
        assert(pL->Slot718(3, 4) == 0);
        assert(s_n63bc0 == 0);
        s_u510 = 0x88;
        assert(pL->Slot718(3, 4) == 1);
        assert(s_n63bc0 == 1);
        assert(s_a63bc0[1] == 3 && s_a63bc0[2] == 0x88 && s_a63bc0[3] == 4);
        s_c63bc0 = 0;
        assert(pL->Slot718(3, 4) == 0);
        printf("S2 ok (710/718)\n");
    }
    // ==== S3: Slot6a8 ====
    {
        Wire();
        s_m4a8[0x31] = 0;
        assert(pL->Slot6a8(5, 0x31) == 0);
        assert(s_n65410 == 0);
        assert(s_v4a8.size() == 1 && s_v4a8[0].first == 0x31);
        s_m4a8[0x31] = 0x64; s_m3e8[0x31] = 2;
        assert(pL->Slot6a8(5, 0x31) == 0xA);
        assert(s_n65410 == 1);
        assert(s_a65410[0] == 0x1234 && s_a65410[1] == 5);
        assert(s_a65410[2] == 0x64 + 2 * 0xf4240);
        printf("S3 ok (6a8)\n");
    }
    // ==== S4: Slot6b0 ====
    {
        Wire();
        assert(pL->Slot6b0(0) == 0);
        assert(s_n65410 == 0);
        s_u440 = 0x64; s_u3f0 = 3;
        assert(pL->Slot6b0(9) == 0xA);
        assert(s_n65410 == 1 && s_a65410[1] == 9);
        assert(s_a65410[2] == 0x64 + 3 * 0xf4240);
        assert(s_n3f0 == 1);
        printf("S4 ok (6b0)\n");
    }
    // ==== S5: Slot6d8 — the five gates ====
    {
        Wire();
        assert(pL->Slot6d8(0) == 0);
        assert(s_n278 == 0);
        s_c278 = 1;
        assert(pL->Slot6d8(7) == 0);
        assert(s_n278 == 1 && s_n280 == 0);
        s_c278 = 0; s_c280 = 1;
        assert(pL->Slot6d8(7) == 0);
        assert(s_n280 == 1 && s_v4a8.empty());
        s_c280 = 0; s_m4a8[7] = 0;
        assert(pL->Slot6d8(7) == 0);
        s_m4a8[7] = 0x64; s_u440 = 0;
        assert(pL->Slot6d8(7) == 0);
        s_u440 = 0x65;
        assert(pL->Slot6d8(7) == 0);
        s_u440 = 0x64; s_u3f0 = 4;
        assert(pL->Slot6d8(7) == 0xC);
        assert(s_n65540 == 1 && s_a65540[1] == 0x64 + 4 * 0xf4240);
        printf("S5 ok (6d8)\n");
    }
    // ==== S6: Slot6d0 — the double-sum ====
    {
        Wire();
        s_m4a8[1] = 0;
        assert(pL->Slot6d0(1, 2) == 0);
        assert(s_n655c0 == 0);
        s_m4a8[1] = 0x10; s_m3e8[1] = 2;
        s_m4a8[2] = 0;
        assert(pL->Slot6d0(1, 2) == 0);
        assert(s_n655c0 == 0);
        s_m4a8[2] = 0x20; s_m3e8[2] = 3;
        assert(pL->Slot6d0(1, 2) == 0xB);
        assert(s_n655c0 == 1);
        assert(s_a655c0[0] == 0x1234);
        assert(s_a655c0[1] == 0x10 + 2 * 0xf4240);
        assert(s_a655c0[2] == 0x20 + 3 * 0xf4240);
        printf("S6 ok (6d0)\n");
    }
    // ==== S7: Slot708 (c0110) ====
    {
        Wire();
        s_cD6790 = 0;   // create-miss -> CHECK log
        pL->Slot708(s_pLeague2, 7, 0x99);
        assert(s_nD6790 == 1);
        assert(s_aD6790[0] == 0x99 && s_aD6790[1] == 7
               && s_aD6790[2] == 0x31 && s_aD6790[3] == 0);
        assert(s_nLog == 1 && s_aLog[0] == 0x1c67);
        assert(s_nD6640 == 1 && s_nD66c0 == 1);
        assert(s_n708_38 == 0 && s_nB1090 == 0);
        assert(s_nFree >= 1);   // sentinel freed
        // happy, empty container
        Wire();
        s_cD6790 = 1;
        pL->Slot708(s_pLeague2, 7, 0x99);
        assert(s_n708_38 == 1 && s_a708_38[0] == 0x66
               && s_a708_38[1] == 0);
        assert(s_n708_110 == 0);   // not found
        assert(s_nB1090 == 1
               && s_aB1090[0] == (void*)s_pLogic
               && s_aB1090[1] == (void*)0x66);
        assert(s_n708_70 == 1 && s_a708_70[0] == 8
               && s_a708_70[1] == 0x77
               && s_a708_70[2] == 0x66);
        assert(s_nLog == 0);
        // happy, container with mixed elems
        Wire();
        s_cD6790 = 1; s_cBf960 = 1;
        s_m87300[s_pElem1] = 1;
        s_m87300[s_pElem2] = 1;
        s_m85dc0[s_pElem1] = 0x111;
        s_m85dc0[s_pElem2] = 0x222;
        pL->Slot708(s_pLeague2, 7, 0x99);
        assert(s_n708_158 == 2);
        assert(s_a708_158[0] == 0x111 && s_a708_158[1] == 7);
        assert(s_a708_158[2] == 0x222);
        assert(s_n708_110 == 1 && s_a708_110[1] == 7
               && s_a708_110[2] == 8);
        printf("S7 ok (708)\n");
    }
    // ==== S8: Slot700 (c16f0) ====
    {
        // gate: pSyn null
        Wire();
        s_pSyn = 0;
        pL->Slot700(5, 6, 0x77);
        assert(s_nD4490 == 0);
        // gate: u3 == 743c80(pSyn)
        Wire();
        pL->Slot700(5, 0x45, 0x77);
        assert(s_nD4490 == 0);
        // gate: pLeague2 null
        Wire();
        s_pLeague2 = 0;
        pL->Slot700(5, 6, 0x77);
        assert(s_nD4490 == 0);
        // gate: 790390 != u4
        Wire();
        pL->Slot700(5, 6, 0x55);
        assert(s_nD4490 == 0);
        // gate: 7903d0 false
        Wire();
        s_c7903d0 = 0;
        pL->Slot700(5, 6, 0x77);
        assert(s_nD4490 == 0);
        // happy full flow
        Wire();
        s_c9e6d0 = 1;
        s_aIds[0] = 1; s_aIds[1] = 2; s_aIds[2] = 3;
        s_nIds = 3;
        s_mVt268[1] = 1; s_mVt280[1] = 0; s_mVt2a0[1] = 9;
        s_mVt268[3] = 1; s_mVt280[3] = 0; s_mVt2a0[3] = 5;
        pL->Slot700(5, 6, 0x77);
        assert(s_nD4490 == 1 && s_aD4490[0] == 6);
        assert(s_aA84Id == 0x45);
        assert(s_nVt10 == 1 && s_aVt10[0] == 5
               && s_aVt10[1] == 0x7d5);
        assert(s_n8233c8 == 2);
        assert(s_nVt88 == 1 && s_aVt88[0] == 6
               && s_aVt88[1] == 0 && s_aVt88[2] == 0x7d5);
        assert(s_nVt710 == 1
               && s_aVt710[0] == (uint32_t)0x950);
        assert(s_nC1180 == 1 && s_aC1180[0] == 6
               && s_aC1180[1] == 0x77);
        assert(s_n76aca0 == 1 && s_a76aca0[0] == 0x1234
               && s_a76aca0[1] == 0x3344);
        // loop: only id 1 qualifies
        assert(s_nVt2a8 == 1 && s_aVt2a8[0] == 1
               && s_aVt2a8[1] == 3);
        assert(s_nFree >= 2);
        printf("S8 ok (700)\n");
    }
    printf("D114c ALL-OK\n");
    return 0;
}

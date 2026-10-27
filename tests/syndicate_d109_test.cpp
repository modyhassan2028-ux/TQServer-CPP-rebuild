// D109 — CSyndicateLogic wave 14 (+0x230/+0x238)
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static int s_nLog;
static int s_nVt1F8, s_nVt2F0, s_nVt108, s_nVt368,
    s_nVt2E8, s_nVt3D8, s_nVt18;
static uint32_t s_uVt1F8Ret;
static uint32_t s_uVt2F0Args[3]; static int64_t s_lVt2F0[2];
static uint32_t s_uVt108Args[3];
static uint32_t s_uVt108First;
static uint32_t s_uVt3D8Args[6];
static char s_pcVt18Arg[64];
static char s_cVt2E8Ret;
static std::vector<uint32_t> s_vec;
static uint32_t s_uCEC20Ret;
static int s_n77D180[3]; static int s_n77BEB0, s_n73F9C0,
    s_n73F4B0, s_n7D4870;
static uint32_t s_u77D180Args[2][3];
static uint32_t s_u73F4B0Arg, s_u7D4870Args[2];
static char s_cCD250; static int s_nCD250, s_nC8AA0;
static int64_t s_iC8AA0Ret;
static char s_c868C0; static int s_n868C0;
static uint64_t s_u85EA0Ret;
static int64_t s_iLgFindRet;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    s_nLog = 0;
    s_nVt1F8 = s_nVt2F0 = s_nVt108 = s_nVt368 = 0;
    s_nVt2E8 = s_nVt3D8 = s_nVt18 = 0;
    s_uVt1F8Ret = 0x11;
    s_cVt2E8Ret = 1; s_cCD250 = 1; s_nCD250 = 0;
    s_nC8AA0 = 0; s_iC8AA0Ret = 0;
    s_c868C0 = 1; s_n868C0 = 0; s_u85EA0Ret = 0x22;
    s_iLgFindRet = 0x55; s_uCEC20Ret = 0x33;
    memset(s_n77D180, 0, sizeof(s_n77D180));
    s_n77BEB0 = s_n73F9C0 = s_n73F4B0 = s_n7D4870 = 0;
    s_vec = {101, 102, 103};
    static void* apBox[1]; static void* apBoxVt[0x500/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x1f8/8] = (void*)+[](void*, uint32_t u)
        -> uint32_t {
        s_nVt1F8++; return s_uVt1F8Ret; };
    apBoxVt[0x2f0/8] = (void*)+[](void*, uint32_t a,
        void* b, int64_t c, uint64_t d) {
        s_nVt2F0++;
        s_uVt2F0Args[0] = a;
        s_lVt2F0[0] = c; s_lVt2F0[1] = (int64_t)d;
        *(std::vector<uint32_t>*)b = s_vec; return 0; };
    apBoxVt[0x108/8] = (void*)+[](void*, uint32_t a,
        uint32_t b, int64_t c) -> uint64_t {
        s_nVt108++;
        if (s_nVt108 == 1) s_uVt108First = a;
        s_uVt108Args[0] = a; s_uVt108Args[1] = b;
        (void)c; return 0; };
    apBoxVt[0x368/8] = (void*)+[](void*, uint32_t a) {
        s_nVt368++; s_uVt108Args[2] = a; return 0; };
    apBoxVt[0x2e8/8] = (void*)+[](void*,
        const char* n) -> char {
        s_nVt2E8++; assert(!strcmp(n, "NewName"));
        return s_cVt2E8Ret; };
    apBoxVt[0x3d8/8] = (void*)+[](void*, uint32_t a,
        uint32_t b, const char* c, uint32_t d,
        uint32_t e) -> uint64_t {
        s_nVt3D8++;
        s_uVt3D8Args[0] = a; s_uVt3D8Args[1] = b;
        s_uVt3D8Args[2] = d; s_uVt3D8Args[3] = e;
        assert(!strcmp(c, "NewName"));
        return 0x77; };
    apBoxVt[0x18/8] = (void*)+[](void*, uint32_t u,
        const void* p) -> uint64_t {
        s_nVt18++; (void)u;
        snprintf(s_pcVt18Arg, sizeof(s_pcVt18Arg),
                 "%s", (const char*)p);
        return 0; };
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[2] = (void*)0x22;
    ((void**)abLogic)[3] = (void*)0x33;
    ((void**)abLogic)[6] = (void*)0x44;
    ((void**)abLogic)[7] = (void*)0x55;
    ((void**)abLogic)[9] = (void*)0x99;
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
    g_fn7CEC20 = [](void* p, uint32_t u) -> uint64_t {
        assert(p == (void*)0x22); (void)u;
        return s_uCEC20Ret; };
    g_fn77D180 = [](void* p, uint32_t u, int32_t n) {
        assert(p == (void*)0x55); assert(u == 0x33);
        assert(n == 2 || n == 1 || n == 3);
        s_n77D180[n - 1]++; };
    g_fn77BEB0 = [](void* p, uint32_t u, int32_t n,
                    int64_t l) {
        s_n77BEB0++; assert(p == (void*)0x44);
        assert(u == 0x33 && n == 3); (void)l; };
    g_fn73F9C0 = []() -> void* {
        s_n73F9C0++; return (void*)0x66; };
    g_fn73F4B0 = [](void* p, uint32_t u) {
        s_n73F4B0++; assert(p == (void*)0x66);
        s_u73F4B0Arg = u; };
    g_fn7D4870 = [](void* p, uint32_t u, void* v,
                    int64_t l) {
        s_n7D4870++; assert(p == (void*)0x99);
        assert(u == 0x33); (void)v; (void)l; };
    g_fn7CD250 = [](void* p, const char* n) -> char {
        s_nCD250++; assert(p == (void*)0x22);
        assert(!strcmp(n, "NewName"));
        return s_cCD250; };
    g_fn7C8AA0 = [](void* p, const char* n) -> int64_t {
        s_nC8AA0++; assert(p == (void*)0x22);
        assert(!strcmp(n, "NewName"));
        return s_iC8AA0Ret; };
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        assert(p == (void*)0x33);
        return u == 1 ? (void*)0x77 : 0; };
    g_fn7868C0 = [](void* p) -> char {
        s_n868C0++; assert(p == (void*)0x77);
        return s_c868C0; };
    g_fn785EA0 = [](void* p) -> uint64_t {
        assert(p == (void*)0x77); return s_u85EA0Ret; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        assert(p == (void*)0x22); (void)u;
        return s_iLgFindRet; };
    static const char* s_apStrs[] = {
        "STR_SYNDICATE_CHANGE_NAME_ERR_DUPLICATE",
        "STR_INVALID_GUILD_NAME"};
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x10; };
    g_fnStringMgrGetStr = [](void* p,
        const char* n) -> void* {
        assert(p == (void*)0x10);
        assert(!strcmp(n, s_apStrs[0]) ||
               !strcmp(n, s_apStrs[1]));
        return (void*)n; };
}

int main() {
    // ---- S1: +0x230 happy path ----
    Reset();
    assert(pL->Slot230(5) == 1);
    // RAW: vt+0x2f0 gets uVar2 (the vt+0x1f8 return)
    assert(s_nVt1F8 == 1 && s_uVt2F0Args[0] == 0x11);
    assert(s_nVt2F0 == 1);
    assert(s_lVt2F0[1] == (int64_t)
        0xfffffffffffffffeULL);
    assert(s_nVt108 == 3);      // the 3 member ids
    assert(s_uVt108First == 101 &&
           s_uVt108Args[1] == 0x33);
    assert(s_n77D180[1] == 1 && s_n77D180[0] == 1 &&
           s_n77D180[2] == 1);   // 2, 1, 3
    assert(s_n77BEB0 == 1 && s_nVt368 == 1);
    assert(s_n73F9C0 == 1 && s_n73F4B0 == 1 &&
           s_u73F4B0Arg == 0x33);
    assert(s_n7D4870 == 1);
    // ---- S2: +0x230 the zero-id reject ----
    Reset();
    s_uCEC20Ret = 0;
    assert(pL->Slot230(5) == 0);
    assert(s_nVt108 == 0 && s_n7D4870 == 0 &&
           s_nVt368 == 0);
    // ---- S3: +0x238 happy path ----
    Reset();
    // CONCAT71: (0x77 & ~0xff) | 1 == 1
    assert(pL->Slot238(1, "NewName", 7, 8) == 1);
    assert(s_nVt2E8 == 1 && s_n868C0 == 1);
    assert(s_nCD250 == 1 && s_nC8AA0 == 1);
    assert(s_nVt3D8 == 1 && s_nVt18 == 0);
    assert(s_uVt3D8Args[0] == 1);
    assert(s_uVt3D8Args[1] == 0x22);
    assert(s_uVt3D8Args[2] == 7 && s_uVt3D8Args[3] == 8);
    // ---- S4: +0x238 the dup-name rejections ----
    Reset();
    s_cCD250 = 0;      // 7cd250 says dup
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nVt18 == 1 &&
           !strcmp(s_pcVt18Arg,
               "STR_SYNDICATE_CHANGE_NAME_ERR_DUPLICATE"));
    Reset();
    s_iC8AA0Ret = 0x66;   // by-name find hit -> dup
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nVt18 == 1 &&
           !strcmp(s_pcVt18Arg,
               "STR_SYNDICATE_CHANGE_NAME_ERR_DUPLICATE"));
    // ---- S5: +0x238 the bad-name length ----
    Reset();
    assert(pL->Slot238(1, "A", 7, 8) == 0);   // len 1
    assert(s_nVt2E8 == 0 && s_nVt18 == 1 &&
           !strcmp(s_pcVt18Arg,
               "STR_INVALID_GUILD_NAME"));
    Reset();
    char szLong[40]; memset(szLong, 'x', 36);
    szLong[36] = 0;    // len 36 >= 0x24
    assert(pL->Slot238(1, szLong, 7, 8) == 0);
    assert(s_nVt18 == 1 &&
           !strcmp(s_pcVt18Arg,
               "STR_INVALID_GUILD_NAME"));
    // ---- S6: +0x238 vt+0x2e8 rejects ----
    Reset();
    s_cVt2E8Ret = 0;
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nVt18 == 1 &&
           !strcmp(s_pcVt18Arg,
               "STR_INVALID_GUILD_NAME"));
    // ---- S7: +0x238 the early-outs ----
    Reset();
    ((void**)abLogic)[3] = 0;
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nLog == 1);
    Reset();
    ((void**)abLogic)[2] = 0;
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nLog == 1);
    Reset();
    ((void**)abLogic)[1] = 0;
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nLog == 1);
    Reset();
    assert(pL->Slot238(0, "NewName", 7, 8) == 0);
    assert(pL->Slot238(1, 0, 7, 8) == 0);
    // ---- S8: +0x238 the player paths ----
    Reset();
    assert(pL->Slot238(2, "NewName", 7, 8) == 0);
    assert(s_n868C0 == 0);   // player find missed
    Reset();
    s_c868C0 = 0;           // 7868c0 says not leader
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nVt3D8 == 0);
    Reset();
    s_u85EA0Ret = 0;        // league id 0 -> log
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nLog == 1);
    Reset();
    s_iLgFindRet = 0;       // LgFind miss -> plain 0
    assert(pL->Slot238(1, "NewName", 7, 8) == 0);
    assert(s_nLog == 0 && s_nCD250 == 0);
    puts("SYNDICATE_D109_OK: wave 14");
    return 0;
}

// D111 — CSyndicateLogic wave 16 (+0x038/+0x0e8/+0x118)
#include "modules/syndicate/src/syndicatelogic.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace syndicate;

static uint8_t abLogic[0x90];
static CSyndicateLogic* pL = (CSyndicateLogic*)abLogic;
static int s_nLog;
static void* s_pPlayer[3];   // 0: user, 1: by-name target, 2: deputy
static char s_cE590, s_c868C0, s_c87300, s_c87390,
    s_c86960, s_c87390b;
static uint64_t s_u85EA0[3];
static int64_t s_lLgFind;
static std::vector<uint32_t> s_vecAll;
static uint32_t s_uVt1F8Ret; static int s_nVt1F8;
static char s_c97750; static int s_n97750;
static int s_nVt50, s_nVt48, s_nVt18, s_nVt88,
    s_nVt328, s_nVt8, s_nVt3b8;
static std::vector<uint32_t> s_vecVt50;
static void* s_pvVt48; static uint32_t s_uVt18Arg;
static char s_pcVt18Str[64];
static uint32_t s_uVt88Arg, s_uVt328Arg, s_uVt8Arg;
static uint64_t s_u85DC0; static uint64_t s_u867D0[3];
static uint64_t s_u87380[3];
static int s_nF650, s_nC6BD0, s_nFA60, s_nF900,
    s_nF960, s_nDB630, s_nE020, s_n7A0760, s_nB92B0,
    s_n96390, s_n86E30, s_nMyLog;
static int32_t s_iF650[3];
static uint32_t s_uDB630Type;
static char s_cAEB, s_cDB630;
static int64_t s_lF4E0;
static char s_cVt3b8Seen;

static void Reset() {
    memset(abLogic, 0, sizeof(abLogic));
    s_nLog = 0;
    s_pPlayer[0] = s_pPlayer[1] = s_pPlayer[2] = 0;
    s_cE590 = 0; s_c868C0 = 1; s_c87300 = 1;
    s_c87390 = 0; s_c87390b = 0; s_c86960 = 0;
    s_u85EA0[0] = 5; s_u85EA0[1] = 5;
    s_u85EA0[2] = 5;
    s_lLgFind = 0x66;
    s_vecAll = {1, 2, 0, 4};
    s_uVt1F8Ret = 5; s_nVt1F8 = 0;
    s_c97750 = 0; s_n97750 = 0;
    s_nVt50 = s_nVt48 = s_nVt18 = s_nVt88 = 0;
    s_nVt328 = s_nVt8 = s_nVt3b8 = 0;
    s_vecVt50.clear(); s_pvVt48 = 0;
    s_uVt18Arg = 0; s_pcVt18Str[0] = 0;
    s_uVt88Arg = s_uVt328Arg = s_uVt8Arg = 0;
    s_u85DC0 = 9; s_u867D0[0] = 1000;
    s_u867D0[1] = 100; s_u867D0[2] = 100;
    s_u87380[0] = 30; s_u87380[1] = 40;
    s_u87380[2] = 50;
    s_nF650 = s_nC6BD0 = s_nFA60 = s_nF900 = 0;
    s_nF960 = s_nDB630 = s_nE020 = s_n7A0760 = 0;
    s_nB92B0 = s_n96390 = s_n86E30 = s_nMyLog = 0;
    memset(s_iF650, 0, sizeof(s_iF650));
    s_uDB630Type = 0; s_cAEB = 1; s_cDB630 = 1;
    s_lF4E0 = 0x77; s_cVt3b8Seen = 0;
    static void* apBox[1]; static void* apBoxVt
        [0x400/8];
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    apBoxVt[0x50/8] = (void*)+[](void*, void* v,
        uint32_t u, uint64_t z) -> uint64_t {
        s_nVt50++; assert(u == 1 && z == 0);
        *(std::vector<uint32_t>*)v = s_vecAll;
        return 0; };
    apBoxVt[0x48/8] = (void*)+[](void*, int64_t l,
        void* v) -> uint64_t {
        s_nVt48++; assert(l == 0x99);
        s_pvVt48 = v; return 0; };
    apBoxVt[0x1f8/8] = (void*)+[](void*, uint32_t i)
        -> uint32_t {
        s_nVt1F8++; return i == 4 ? 77 :
            s_uVt1F8Ret; };
    apBoxVt[0x18/8] = (void*)+[](void*, uint32_t a,
        const void* c, void* d) -> uint64_t {
        s_nVt18++; s_uVt18Arg = a;
        snprintf(s_pcVt18Str, sizeof(s_pcVt18Str),
                 "%s", (const char*)c);
        if (!strcmp((const char*)c,
                    "STR_KICKOUT_ME_s"))
            snprintf(s_pcVt18Str +
                strlen(s_pcVt18Str), 32, "|%s",
                (char*)d);
        return 0; };
    apBoxVt[0x88/8] = (void*)+[](void*, uint32_t a,
        void* b, uint64_t d) -> uint64_t {
        s_nVt88++; s_uVt88Arg = a;
        assert(d == 0); (void)b; return 0; };
    apBoxVt[0x328/8] = (void*)+[](void*, uint32_t a)
        -> uint32_t {
        s_nVt328++; s_uVt328Arg = a; return 0x77; };
    apBoxVt[8/8] = (void*)+[](void*, uint32_t a,
        void* b) -> uint64_t {
        s_nVt8++; s_uVt8Arg = a; (void)b; return 0; };
    apBoxVt[0x3b8/8] = (void*)+[](void*, int64_t a,
        uint32_t b, const void* c) -> uint64_t {
        s_nVt3b8++; s_cVt3b8Seen = 1;
        assert(!strcmp((const char*)c,
            "STR_SYN_REPLACE_SUCCESS_LEAVEWORD"));
        assert(a == s_lF4E0 && b == 9);
        return 0; };
    ((void**)abLogic)[1] = apBox;
    ((void**)abLogic)[2] = (void*)0x22;
    ((void**)abLogic)[3] = (void*)0x33;
    ((void**)abLogic)[10] = (void*)0x55;
    g_fnT1LogError = [](const char* s) {
        s_nLog++; (void)s; };
    g_fn78C8E0 = [](void* p, uint32_t u) -> void* {
        assert(p == (void*)0x33);
        return u == 1 ? s_pPlayer[0] :
               u == 30 ? s_pPlayer[2] : 0; };
    g_fn785EA0 = [](void* p) -> uint64_t {
        if (p == s_pPlayer[0]) return s_u85EA0[0];
        if (p == s_pPlayer[1]) return s_u85EA0[1];
        return s_u85EA0[2]; };
    g_fnLgFind = [](void* p, uint32_t u) -> int64_t {
        (void)p; (void)u; return s_lLgFind; };
    g_fn78E590 = [](void* p) -> char {
        (void)p; return s_cE590; };
    g_fn7868C0 = [](void* p) -> char {
        (void)p; return s_c868C0; };
    g_fn78C9F0 = [](void* p, void* s) -> void* {
        assert(p == (void*)0x33);
        assert(!strcmp((char*)*(void**)s, "Target"));
        return s_pPlayer[1]; };
    g_fn787300 = [](void* p) -> char {
        (void)p; return s_c87300; };
    g_fn785DC0 = [](void* p) -> uint64_t {
        (void)p; return s_u85DC0; };
    g_fn7867D0 = [](void* p) -> int64_t {
        if (p == s_pPlayer[0]) return s_u867D0[0];
        if (p == s_pPlayer[1]) return s_u867D0[1];
        return s_u867D0[2]; };
    g_fn786960 = [](void* p) -> char {
        (void)p; return s_c86960; };
    g_fn787390 = [](void* p) -> char {
        (void)p; return s_c87390; };
    g_fn787380 = [](void* p) -> uint64_t {
        if (p == s_pPlayer[0]) return s_u87380[0];
        if (p == s_pPlayer[1]) return s_u87380[1];
        return s_u87380[2]; };
    g_fn797750 = [](void* p, uint32_t u) -> char {
        s_n97750++; (void)p;
        return u == 77 ? s_c97750 : 0; };
    g_fn79F650 = [](void* l, void* p, int32_t n) {
        (void)l; (void)p;
        s_iF650[s_nF650++ % 8] = n; };
    g_fn7C6BD0 = [](void* m, void* p, void* l,
                    uint32_t u) {
        s_nC6BD0++; assert(m == (void*)0x22);
        assert(u == 0x77); (void)p; (void)l; };
    g_fn79FA60 = [](void* l, uint32_t u) {
        s_nFA60++; (void)l; assert(u == 1); };
    g_fn78F900 = [](void* l, const char* s) {
        s_nF900++; (void)l;
        assert(!strcmp(s, "Target")); };
    g_fn78F960 = [](void* l, uint32_t u) {
        s_nF960++; (void)l; assert(u == 9); };
    g_fn7DB630 = [](void* m, int32_t t, int32_t c,
                    uint32_t u, void* s) -> char {
        s_nDB630++; s_uDB630Type = t;
        assert(c == 1000 && u == 0x77);
        assert(!strcmp((char*)s, "Target") ||
               !strcmp((char*)s, "LeaderName"));
        return s_cDB630; };
    g_fn79E020 = [](void* l) { s_nE020++; (void)l; };
    g_fn790390 = [](void* l) -> uint64_t {
        (void)l; return 0x66; };
    g_fn763680 = [](void* p, uint32_t u) -> uint64_t {
        assert(p == (void*)0x55); (void)u;
        return 0x99; };
    g_fn7B92B0 = [](void* p, uint32_t a, uint32_t b,
                    uint32_t c, const char* d) {
        s_nB92B0++; assert(p == (void*)abLogic);
        assert(a == 1 && b == 9 && c == 0x66);
        // (the 790390 id passes through)
        assert(!strcmp(d, "Target")); };
    g_fn787120 = [](void*) -> char* {
        return (char*)"LeaderName"; };
    g_fn78F270 = [](void*) -> uint64_t {
        return 0x99; };
    g_fn78F4E0 = [](void*) -> int64_t {
        return s_lF4E0; };
    g_fn7A0760 = [](void* a, void* b, int32_t c,
                    uint32_t d, char e) {
        s_n7A0760++; (void)a; (void)b;
        assert(d == 0x77); (void)c; (void)e; };
    g_fn7DB2B0 = [](void* p) { (void)p; };
    g_fn7DB3A0 = [](void* p, int32_t a, int32_t b)
        -> char { (void)p;
        assert(a == 0x2c && b == 0); return 1; };
    g_fn7DB330 = [](void* p) -> uint64_t {
        (void)p; return 0x55; };
    g_fn7AEBB0 = [](void* a, void* b, void* c,
                    const char* d, char e, char f,
                    char g) -> uint64_t {
        (void)a; (void)b; (void)c;
        assert(strstr(d, "KickOutMember By Name"));
        (void)e; assert(f == 1); (void)g;
        return (uint64_t)(uint8_t)s_cAEB; };
    g_fn796390 = [](void* l, int32_t i) -> void* {
        s_n96390++; (void)l; assert(i == 9);
        return (void*)0x88; };
    g_fn786E30 = [](void* p, int32_t i) {
        s_n86E30++; assert(p == (void*)0x88);
        assert(i == 0); };
    g_fnMyLogSave = [](const char* f, const char* m) {
        s_nMyLog++;
        assert(!strcmp(f, "gmlog/syn_demise"));
        assert(strstr(m, "player:%u to player:%u")); };
    static const char* s_apStrs[] = {
        "STR_TOO_LOWER_SYN_MONEY",
        "STR_SYN_APPOINT_TARGET_OFFLINE",
        "STR_DEMISE_SUCCESS",
        "STR_SYN_REPLACE_SUCCESS",
        "STR_SYN_REPLACE_SUCCESS_LEAVEWORD",
        "STR_KICKOUT_ME_s", "STR_KICKOUT_MEMBER_s"};
    g_fnStringMgrInstance = []() -> void* {
        return (void*)0x10; };
    g_fnStringMgrGetStr = [](void* p,
        const char* n) -> void* {
        assert(p == (void*)0x10);
        bool ok = false;
        for (auto s : s_apStrs)
            if (!strcmp(n, s)) ok = true;
        assert(ok); return (void*)n; };
}

int main() {
    // ===== +0x038 =====
    // S1: null third arg / missing box
    Reset();
    pL->Slot038(1, 0);
    assert(s_nVt50 == 0);
    // S2: player miss
    Reset();
    pL->Slot038(2, 0x99);
    assert(s_nVt50 == 0);
    // S3: league too poor
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_cE590 = 1;
    pL->Slot038(1, 0x99);
    assert(s_nVt18 == 1 && !strcmp(s_pcVt18Str,
        "STR_TOO_LOWER_SYN_MONEY"));
    assert(s_nVt50 == 0);
    // S4: the sweep — ids 1,2 match league 5,
    // 0 skipped, 4 via 797750
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_c97750 = 1;
    pL->Slot038(1, 0x99);
    assert(s_nVt50 == 1 && s_nVt1F8 == 4);
    assert(s_n97750 == 1);
    assert(s_nVt48 == 1);
    {
        auto* v = (std::vector<uint32_t>*)s_pvVt48;
        assert(v->size() == 3 && (*v)[0] == 1 &&
               (*v)[1] == 2 && (*v)[2] == 4);
    }
    // S5: empty match -> no vt+0x48
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_c97750 = 0; s_uVt1F8Ret = 0;
    pL->Slot038(1, 0x99);
    assert(s_nVt48 == 0 && s_nVt1F8 == 4);
    // ===== +0x0e8 =====
    // S6: null name
    Reset();
    assert(pL->Slot0e8(1, 0, 0) == 0);
    assert(s_nLog == 1);
    // S7: player miss / league miss / not leader
    Reset();
    assert(pL->Slot0e8(2, "Target", 0) == 0);
    Reset();
    s_pPlayer[0] = (void*)0x50; s_lLgFind = 0;
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    Reset();
    s_pPlayer[0] = (void*)0x50; s_c868C0 = 0;
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    // S8: target not found / offline
    Reset();
    s_pPlayer[0] = (void*)0x50;
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60; s_c87300 = 0;
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    assert(s_nVt18 == 1 && !strcmp(s_pcVt18Str,
        "STR_SYN_APPOINT_TARGET_OFFLINE"));
    // S9: self-appoint
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60; s_u85DC0 = 1;
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    // S10: different league
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60; s_u85EA0[1] = 6;
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    // S11: the online+rank gate fails (0x25a check)
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    s_u867D0[1] = 0x300; s_c86960 = 1;
    // not 0x25a and 86960 != 0 -> blocked
    assert(pL->Slot0e8(1, "Target", 0) == 0);
    assert(s_nF650 == 0);
    // S12: full demise success (c4=0)
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    s_pPlayer[2] = (void*)0x70; s_c87390 = 1;
    s_u867D0[2] = 0x398;
    assert(pL->Slot0e8(1, "Target", 0) == 1);
    // the plV8 (id 40) lookup finds no player,
    // so only 3 of the 4 RAW pairs execute
    assert(s_nF650 == 3 && s_nC6BD0 == 3);
    assert(s_iF650[0] == 200 &&   // leader demote
           s_iF650[1] == 200 &&    // deputy
           s_iF650[2] == 1000);   // target promote
    assert(s_nVt328 == 1 && s_uVt328Arg == 5);
    assert(s_nVt88 == 1 && s_uVt88Arg == 0x99);
    assert(s_nDB630 == 2);
    assert(s_nVt8 == 2);
    assert(s_nMyLog == 1);
    assert(s_nB92B0 == 1);
    assert(s_nVt3b8 == 0);
    // S13: replace flow (c4=1) + leaveword
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    s_pPlayer[2] = (void*)0x70; s_c87390 = 1;
    s_u867D0[2] = 0x398;
    assert(pL->Slot0e8(1, "Target", 1) == 1);
    assert(s_nDB630 == 1);
    assert(s_uDB630Type == 0x2e);
    assert(s_nVt3b8 == 1 && s_cVt3b8Seen == 1);
    // ===== +0x118 =====
    // S14: null name
    Reset();
    assert(pL->Slot118(1, 0) == 0);
    assert(s_nLog == 1);
    // S15: user miss / target miss
    Reset();
    assert(pL->Slot118(2, "Target") == 0);
    Reset();
    s_pPlayer[0] = (void*)0x50;
    assert(pL->Slot118(1, "Target") == 0);
    // S16: different leagues
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60; s_u85EA0[1] = 6;
    assert(pL->Slot118(1, "Target") == 0);
    // S17: rank gate closed
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    s_u867D0[0] = 500; s_u867D0[1] = 100;
    assert(pL->Slot118(1, "Target") == 0);
    // S18: league too poor
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    s_cE590 = 1;
    assert(pL->Slot118(1, "Target") == 0);
    assert(s_nVt18 == 1 && !strcmp(s_pcVt18Str,
        "STR_TOO_LOWER_SYN_MONEY"));
    // S19: kickout-by-name success
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60;
    assert(pL->Slot118(1, "Target") == 1);
    assert(s_nVt18 == 1 && !strcmp(s_pcVt18Str,
        "STR_KICKOUT_ME_s|LeaderName"));
    assert(s_n96390 == 1 && s_n86E30 == 1);
    assert(s_nVt88 == 1 && s_uVt88Arg == 0x99);
    assert(s_nVt8 == 1 && s_uVt8Arg == 1);
    // S20: kick fails
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60; s_cAEB = 0;
    assert(pL->Slot118(1, "Target") == 0);
    assert(s_nVt88 == 0 && s_n96390 == 0);
    // S21: target offline -> skip KICKOUT_ME tip
    Reset();
    s_pPlayer[0] = (void*)0x50;
    s_pPlayer[1] = (void*)0x60; s_c87300 = 0;
    assert(pL->Slot118(1, "Target") == 1);
    assert(s_nVt18 == 0);
    assert(s_nVt88 == 1);   // the member broadcast
    puts("SYNDICATE_D111_OK: wave 16");
    return 0;
}

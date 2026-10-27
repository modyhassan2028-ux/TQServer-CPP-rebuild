// D86 tests: FUN_1417873a0 rank-name resolver — 43 known ids
// + STR_ERROR fallback + range boundaries.
#include "modules/syndicate/src/SyndicateRankName.h"
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
static std::vector<const char*> g_last;
static void* FakeMgr86() { return (void*)0x777; }
static void* FakeGet86(void* m, const char* s) {
    if (m != (void*)0x777) { printf("  FAIL bad mgr\n"); return nullptr; }
    g_last.push_back(s);
    return (void*)s;
}
static int g_fail = 0;
#define CHECK(c, msg) do { if (c) printf("  ok %s\n", msg); \
    else { printf("  FAIL %s\n", msg); g_fail++; } } while (0)
static const char* One(int rank) {
    g_last.clear();
    void* r = syndicate::SyndicateRankName(rank);
    if (g_last.size() != 1) return "<none>";
    return (const char*)r;
}
int main() {
    syndicate::g_fnD86StrMgr = FakeMgr86;
    syndicate::g_fnD86GetStr = FakeGet86;
    struct P { int id; const char* s; };
    const P tbl[] = {
        {0x1a4, "STR_SYN_COMMANDER_MATE"}, {200, "STR_SYN_MEMBER"},
        {0xd2, "STR_SYN_SENIOR_MEMBER"},
        {0x348, "STR_SYN_HONOR_ASSEMBLYMAN"},
        {0x1ea, "STR_SYN_ELITE_MEMBER"},
        {0x1eb, "STR_SYN_LILY_ELITE_MEMBER"},
        {0x1ec, "STR_SYN_FLOWER_R_ELITE_MEMBER"},
        {0x1ed, "STR_SYN_PK_ELITE_MEMBER"},
        {0x1ee, "STR_SYN_EDU_ELITE_MEMBER"},
        {0x1ef, "STR_SYN_MONEY_ELITE_MEMBER"},
        {0x1f0, "STR_SYN_TOTEM_ELITE_MEMBER"},
        {0x1f1, "STR_SYN_EMONEY_ELITE_MEMBER"},
        {0x1f2, "STR_SYN_FLOWER_W_ELITE_MEMBER"},
        {0x1fe, "STR_SYN_VIZIR_ASSISTANT"},
        {0x1ff, "STR_SYN_ASSEMBLYMAN_ASSISTANT"},
        {0x208, "STR_SYN_VIZIR_MATE"},
        {0x209, "STR_SYN_ASSEMBLYMAN_MATE"},
        {0x24e, "STR_SYN_EXECUTIVE_OFFICER"},
        {0x24f, "STR_SYN_LILY_EXEC_OFFICER"},
        {0x250, "STR_SYN_FLOWER_R_EXEC_OFFICER"},
        {0x251, "STR_SYN_PK_EXEC_OFFICER"},
        {0x252, "STR_SYN_EDU_EXEC_OFFICER"},
        {0x253, "STR_SYN_MONEY_EXEC_OFFICER"},
        {0x254, "STR_SYN_TOTEM_EXEC_OFFICER"},
        {0x255, "STR_SYN_EMONEY_EXEC_OFFICER"},
        {0x256, "STR_SYN_FLOWER_W_EXEC_OFFICER"},
        {0x25a, "STR_SYN_LEADER_FAVORITE"},
        {0x262, "STR_SYN_LEADER_MATE_ASSISTANT"},
        {0x263, "STR_SYN_VICE_LEADER_ASSISTANT"},
        {0x26c, "STR_SYN_VICE_LEADER_MATE"},
        {0x28a, "STR_SYN_VICE_COMMANDER"},
        {0x2a8, "STR_SYN_HONOR_COMMANDER"},
        {0x2b2, "STR_SYN_COMMANDER"},
        {0x352, "STR_SYN_ASSEMBLYMAN"},
        {0x353, "STR_SYN_LILY_ASSEMBLYMAN_RANK"},
        {0x354, "STR_SYN_FLOWER_R_ASSEMBLYMAN"},
        {0x355, "STR_SYN_PK_ASSEMBLYMAN"},
        {0x356, "STR_SYN_EDU_ASSEMBLYMAN"},
        {0x357, "STR_SYN_MONEY_ASSEMBLYMAN"},
        {0x358, "STR_SYN_TOTEM_ASSEMBLYMAN"},
        {0x359, "STR_SYN_EMONEY_ASSEMBLYMAN"},
        {0x35a, "STR_SYN_FLOWER_W_ASSEMBLYMAN"},
        {0x35b, "STR_SYN_LUTIP_ASSEMBLYMAN"},
        {0x370, "STR_SYN_HONOR_VIZIR"},
        {0x37a, "STR_SYN_VIZIR"},
        {0x398, "STR_SYN_LEADER_MATE"},
        {0x3d4, "STR_SYN_HONOR_VICE_LEADER"},
        {0x3de, "STR_SYN_VICE_LEADER"},
        {1000, "STR_SYN_LEADER"},
    };
    printf("D86-1 known ranks\n");
    int nOK = 0;
    for (auto& p : tbl)
        if (strcmp(One(p.id), p.s) == 0) nOK++;
    const int NTBL = (int)(sizeof(tbl) / sizeof(tbl[0]));
    CHECK(nOK == NTBL && NTBL == 49,
          "all 49 rank mappings exact");
    printf("D86-2 fallback + boundaries\n");
    CHECK(strcmp(One(0), "STR_ERROR") == 0, "0 -> STR_ERROR");
    CHECK(strcmp(One(-5), "STR_ERROR") == 0, "negative -> STR_ERROR");
    CHECK(strcmp(One(0x1a5), "STR_ERROR") == 0, "0x1a5 boundary");
    CHECK(strcmp(One(0x1f3), "STR_ERROR") == 0, "gap id -> STR_ERROR");
    CHECK(strcmp(One(0x349), "STR_ERROR") == 0, "0x349 boundary");
    CHECK(strcmp(One(0x351), "STR_ERROR") == 0, "0x351 gap");
    CHECK(strcmp(One(999), "STR_ERROR") == 0, "999 -> STR_ERROR");
    CHECK(strcmp(One(1001), "STR_ERROR") == 0, "1001 -> STR_ERROR");
    if (g_fail == 0) printf("D86-OK: 49 ranks + 8 fallback checks\n");
    else printf("D86-FAIL\n");
    return g_fail ? 1 : 0;
}

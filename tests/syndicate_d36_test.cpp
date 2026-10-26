// ============================================================
// syndicate_d36_test — the league member/token LOOKUP layer
// (T10/D36 part 1): the getters (145520/1417d4e70), the CToken
// ctor (1417d4d60), the two map finds (14172b520 users / 141749980
// members-0x3d), the member-data lookup (14174bac0) and the
// user's-league chain (14174be40) — on REAL D32-built maps.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueTree.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueEntity.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateLeagueMember.h"

using namespace syndicate;

static int s_nInvalid = 0;
static void TestInvalid() { s_nInvalid++; }
static int s_nLogs = 0;
static void* TestLogFactory() { s_nLogs++; return (void*)0x1; }
static void TestLogWrite(void*, uint32_t, int) {}
namespace syndicate {
extern void (*g_fnMeritInvalid)();
extern void (*g_fnMeritOpDelete)(void*);
using syndicate::g_fnMeritInvalid;
using syndicate::g_fnMeritOpDelete;
}

// the D32 insert helper (same as the d35 test)
static void MkMember(char* pcMap, uint32_t key, uint64_t value) {
    uint64_t kv[2] = { key, value };
    char* head = *(char**)(pcMap + 0x30);
    char* attach = head; bool bLeft = true;
    if (*(char*)(*(char**)(head + 8) + 0x29) == '\0') {
        char* cur = *(char**)(head + 8);
        do { attach = cur; bLeft = key < *(uint32_t*)(cur + 0x18);
             cur = bLeft ? *(char**)cur : *(char**)(cur + 0x10);
        } while (*(char*)(cur + 0x29) == '\0');
    }
    char out[2][8];
    LeagueInsert(pcMap, out[0], bLeft ? 1 : 0, attach, kv);
}

int main() {
    g_fnLeagueInvalid = TestInvalid;
    g_fnMeritInvalid = TestInvalid;
    g_fnMeritOpDelete = [](void* p) { free(p); };
    g_fnLeagueLogFactory = TestLogFactory;
    g_fnLeagueLogWrite = TestLogWrite;

    // ================= D36-1: the getters =================
    {
        static void* recVt[16]; static void* provVt[16];
        uint64_t idResult = 0;
        recVt[9] = (void*)(+[](void** r) { (void)r; return (uint64_t)777; });
        recVt[8] = (void*)(+[](void** r) { (void)r; return (uint64_t)888; });   // +0x40
        static void* recObj[4];
        recObj[0] = recVt;
        provVt[2] = (void*)(+[](void** p, uint64_t idx) { (void)p; return (void*)recObj; });
        static void* provObj[4];
        provObj[0] = provVt;

        static char ent[0x120]; memset(ent, 0, sizeof(ent));
        *(void**)(ent + 8) = provObj;
        idResult = LeagueGetId((int64_t)ent);
        assert(idResult == 777);   // resolve(0) → vt+0x48 = slot 9
        uint64_t keyResult = LeagueTokenKey((int64_t)ent);
        assert(keyResult == 888);  // resolve(2) → vt+0x40 = slot 8
        // the null-provider path: log + 0
        static char ent2[0x120]; memset(ent2, 0, sizeof(ent2));
        int logs0 = s_nLogs;
        assert(LeagueGetId((int64_t)ent2) == 0);
        assert(LeagueTokenKey((int64_t)ent2) == 0);
        assert(s_nLogs == logs0 + 2);
        printf("D36-1 getters ok (resolve chains + the null-provider gates)\n");
    }

    // ================= D36-2: the CToken ctor =================
    {
        g_pLeagueTokenVft = (void*)0xBEEF00;
        assert(LeagueTokenNew(0) == nullptr);
        void** tok = (void**)LeagueTokenNew((int64_t)0x1234);
        assert(tok != nullptr);
        assert(tok[0] == (void*)0xBEEF00);
        assert(tok[1] == (void*)0x1234);
        free(tok);
        printf("D36-2 CToken ctor ok\n");
    }

    // ================= D36-3: the users find (0x29) =================
    {
        static char map[0x40]; memset(map, 0, sizeof(map));
        LeagueMemberCtor(map);
        MkMember(map, 10, 0xAAA);
        MkMember(map, 20, 0xBBB);
        MkMember(map, 30, 0xCCC);
        void* it[2];
        uint32_t k = 20;
        LeagueUserFind((int64_t)map, it, &k);
        assert(it[0] == *(void**)map);                // the anchor object
        assert(it[1] != (void*)*(char**)(map + 0x30));   // found: node != head
        assert(*(uint32_t*)((char*)it[1] + 0x18) == 20);
        k = 99;
        LeagueUserFind((int64_t)map, it, &k);
        assert(it[1] == (void*)*(char**)(map + 0x30));   // not found: the head
        printf("D36-3 users find ok\n");
    }

    // ================= D36-4: the members find (0x3d) =================
    {
        // a HAND-BUILT single-node 0x3d map: {anchor, .., head@+0x30, size@+0x38}
        static char map[0x40]; memset(map, 0, sizeof(map));
        char* head = (char*)calloc(1, 0x40);
        char* root = (char*)calloc(1, 0x40);
        *(void**)(map + 0) = (void*)0x1;        // the anchor (nonzero)
        *(void**)(map + 0x30) = head;
        *(uint64_t*)(map + 0x38) = 1;          // the size
        *(void**)(head + 8) = root;            // head->parent = the root
        *(char*)(head + 0x3d) = 1;            // the head isnil
        *(void**)root = head;                  // left = head
        *(void**)(root + 0x10) = head;         // right = head
        *(void**)(root + 8) = head;             // parent = head
        *(uint32_t*)(root + 0x18) = 42;        // the key
        *(uint64_t*)(root + 0x20) = 0x777;     // the value
        *(char*)(root + 0x3d) = 0;             // a real node

        void* it[2];
        uint32_t k = 42;
        LeagueMemberFind((int64_t)map, it, &k);
        assert(it[1] == (void*)root);
        k = 43;
        LeagueMemberFind((int64_t)map, it, &k);
        assert(it[1] == (void*)head);
        free(head); free(root);
        printf("D36-4 members find (0x3d) ok\n");
    }

    // ================= D36-5: the member-data lookup =================
    {
        static char ent[0x120]; memset(ent, 0, sizeof(ent));
        char* pcMap = ent + 0xd8;
        LeagueMemberCtor(pcMap);
        MkMember(pcMap, 100, (uint64_t)(uintptr_t)"DATA-100");
        MkMember(pcMap, 200, (uint64_t)(uintptr_t)"DATA-200");
        void* p = LeagueMemberData((int64_t)ent, 200);
        assert(p != nullptr && strcmp((char*)p, "DATA-200") == 0);
        assert(LeagueMemberData((int64_t)ent, 999) == nullptr);
        printf("D36-5 member-data lookup ok (found + the 0 path)\n");
    }

    // ================= D36-6: the user's league chain =================
    {
        // the member record: resolve(3) → {vt+0x20 → 999}
        static void* resVt[16];
        static void* recVt[16];
        resVt[4] = (void*)(+[](void** r) { (void)r; return (uint64_t)999; });
        static void* resObj[4];
        resObj[0] = resVt;
        recVt[2] = (void*)(+[](void** r, uint64_t idx) { (void)r; assert(idx == 3); return (void*)resObj; });
        static void* recObj[4];
        recObj[0] = recVt;

        static char ent[0x120]; memset(ent, 0, sizeof(ent));
        char* pcMap = ent + 0x58;   // the users map
        LeagueMemberCtor(pcMap);
        MkMember(pcMap, 7, (uint64_t)(uintptr_t)recObj);
        MkMember(pcMap, 8, 0);   // a null record member

        uint64_t lg = LeagueUserLeague((int64_t)ent, 7);
        assert(lg == 999);
        // the null-record member → the masked anchor tail
        char* anchor = *(char**)(ent + 0x58);
        uint64_t expect = (uint64_t)(uintptr_t)anchor & (uint64_t)0xffffffffffffff00;
        assert(LeagueUserLeague((int64_t)ent, 8) == expect);
        // the missing user → the same masked tail
        assert(LeagueUserLeague((int64_t)ent, 77) == expect);
        printf("D36-6 user's league chain ok (found + null-record + missing)\n");
    }

    printf("SYNDICATE-D36-OK (part 1): the lookup layer complete — "
           "LeagueGetId 141745520 (resolve(0) → vt+0x48), LeagueTokenKey "
           "1417d4e70 (resolve(2) → vt+0x40), LeagueTokenNew 1417d4d60 (the "
           "CToken {vftable, rec} ctor), LeagueUserFind 14172b520 + "
           "LeagueMemberFind 141749980 (the 0x29/0x3d lower_bound finds "
           "with the end-iterator gate), LeagueMemberData 14174bac0 (the "
           "tokens-map inline walk → value@+0x20), LeagueUserLeague "
           "14174be40 (the users-map walk + resolve(3) → vt+0x20)\n");
    return 0;
}

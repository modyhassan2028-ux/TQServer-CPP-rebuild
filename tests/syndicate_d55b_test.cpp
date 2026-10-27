// syndicate_d55b_test — the DistributeSynMeed flow
// (141784cd0) + the collect/award family
// (49f0/c50/46e0/2d0/1b10/0b0/ae630/21d0/1860/
//  f0d0/9b60/f250/fa90/fa60)
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cmath>

#include "modules/syndicate/src/SyndicateMeedDistribute.h"
#include "modules/syndicate/src/SyndicateMeedEntry.h"
#include "modules/syndicate/src/SyndicateMeedEnd.h"
#include "modules/syndicate/src/SyndicateMeedApply.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
#include "modules/syndicate/src/SyndicateMeedInfo.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include "modules/syndicate/src/SyndicateLeagueTree.h"
#include "modules/syndicate/src/SyndicateSynMeed.h"

using namespace syndicate;

// ---------- the vtable kit ----------
struct SVt { void* s[0x100]; };

// ---------- the base mocks ----------
static int g_nLog = 0;
static void MockLog() { ++g_nLog; }
static int g_nInvalid = 0;
static void MockInvalid() {
    ++g_nInvalid; }
static int g_nLive = 0;
static void* MockOpNew(size_t n) {
    void* p = malloc(n);
    memset(p, 0xcd, n);
    ++g_nLive;
    return p; }
static void MockOpDelete(void* p) {
    --g_nLive; free(p); }
static int g_nSnprintf = 0;
static char g_bufSnprintf[0x400];
static void MockSnprintf(char* pDst, size_t u,
                        const char* pFmt) {
    ++g_nSnprintf;
    (void)u;
    snprintf(pDst, 0x400, "%s",
             pFmt ? pFmt : "(null)");
    strncpy(g_bufSnprintf, pDst,
            sizeof(g_bufSnprintf) - 1);
}
struct StrInstObj { void* vt; SVt vtS; };
static StrInstObj g_strInst;
static void* StrInst() { return &g_strInst; }
static char* StrGet(void* p, const char* pKey) {
    (void)p;
    return (char*)pKey;
}
// the log save captures (file, fmt, id)
static int g_nLogSave = 0;
static const char* g_fileLogSave[16];
static uint32_t g_idLogSave[16];
static void MockLogSave(const char* pFile,
                       const char* pFmt,
                       uint32_t uId) {
    (void)pFmt;
    if (g_nLogSave < 16) {
        g_fileLogSave[g_nLogSave] = pFile;
        g_idLogSave[g_nLogSave] = uId;
    }
    ++g_nLogSave;
}
static int g_nTimeGet = 0;
static uint64_t MockTimeGet(int n) {
    (void)n; ++g_nTimeGet; return 0x1234;
}
static int g_nRand = 0; static int g_argRand = 0;
static uint32_t g_retRand = 0;
static uint32_t MockRandGet(int n) {
    ++g_nRand; g_argRand = n;
    return g_retRand;
}

// the descending-point comparator (the
// LAB_141780100 seam — the awards order)
static char CmpPointDesc(
    const MeedEntry5* a, const MeedEntry5* b) {
    return a->v[2] > b->v[2] ? 1 : 0;
}

// ---------- the record-system mock ----------
struct RecField {
    void* vt; SVt vtS;
    // the capture buffers: 64 writes (the whole
    // suite writes each field ~10 times — 8
    // overflowed and smashed the next fld's vt)
    int nWrites; int64_t i64s[64];
    int i32s[64];
};
static void RecSetB8(void* p, uint32_t v) {
    RecField* f = (RecField*)p;
    f->i64s[f->nWrites] = (int64_t)(int32_t)v;
    f->i32s[f->nWrites] = (int32_t)v;
    ++f->nWrites;
}
static void RecSetB0(void* p, int64_t v) {
    RecField* f = (RecField*)p;
    f->i64s[f->nWrites] = v;
    f->i32s[f->nWrites] = (int)v;
    ++f->nWrites;
}
static void BindRecField(RecField* f) {
    f->vt = f->vtS.s;
    f->vtS.s[0xb8/8] = (void*)RecSetB8;
    f->vtS.s[0xb0/8] = (void*)RecSetB0;
}
struct RecTable {
    void* vt; SVt vtS;
    RecField fld[8];
    int nCommit50; int nArg50; int nArgFlag50;
    int nCommit0;  int nArgCommit0;
    uint8_t uRet50;
};
static void* RecField10(void* p, int64_t n) {
    RecTable* t = (RecTable*)p;
    assert(n >= 1 && n <= 8);
    return &t->fld[n - 1];
}
static uint8_t RecCommit50(void* p, int n) {
    RecTable* t = (RecTable*)p;
    ++t->nCommit50; t->nArg50 = n;
    t->nArgFlag50 = n;
    return t->uRet50;
}
static void RecCommit0(void* p, int n) {
    RecTable* t = (RecTable*)p;
    ++t->nCommit0; t->nArgCommit0 = n;
}
static void BindRecTable(RecTable* t) {
    t->vt = t->vtS.s;
    t->vtS.s[0x10/8] = (void*)RecField10;
    t->vtS.s[0x50/8] = (void*)RecCommit50;
    t->vtS.s[0x0]    = (void*)RecCommit0;
    for (int i = 0; i < 8; ++i)
        BindRecField(&t->fld[i]);
}
struct RecSys {
    void* vt; SVt vtS;
    RecTable tblMeed, tblPoint;
    int nTbl = 0;
};
static void* RecGetTable(void* p, const char* n) {
    RecSys* s = (RecSys*)p;
    ++s->nTbl;
    if (strcmp(n, "cq_meedrecord") == 0)
        return &s->tblMeed;
    if (strcmp(n, "cq_pointrecord") == 0)
        return &s->tblPoint;
    return nullptr;
}
static void BindRecSys(RecSys* s) {
    s->vt = s->vtS.s;
    s->vtS.s[0x20/8] = (void*)RecGetTable;
    BindRecTable(&s->tblMeed);
    BindRecTable(&s->tblPoint);
}
static RecSys g_recSys;
static void* MockInstGet() { return &g_recSys; }

// reset tblPoint's captures between the sections
// (the vts wiped by the memset are re-bound)
static void ResetPointTable() {
    RecTable& t = g_recSys.tblPoint;
    t.nCommit50 = 0; t.nCommit0 = 0;
    t.nArg50 = 0; t.nArgCommit0 = 0;
    memset(t.fld, 0, sizeof(t.fld));
    for (int i = 0; i < 8; ++i)
        BindRecField(&t.fld[i]);
}

// ---------- the user mock ----------
struct UserObj {
    void* vt; SVt vtS;
    int nOnline; char cOnline;
    int n350; int e350, a350, b350;
    int n358; char* s358; uint32_t u358;
    const char* p358;
};
static char UserIsOnline268(void* p) {
    UserObj* u = (UserObj*)p;
    ++u->nOnline;
    return u->cOnline;
}
static void UserDisplay350(void* p, int e,
                           int a, uint32_t b) {
    UserObj* u = (UserObj*)p;
    ++u->n350;
    u->e350 = e; u->a350 = a; u->b350 = b;
}
static void UserSend358(void* p, const char* s,
                        uint32_t id, char* buf) {
    UserObj* u = (UserObj*)p;
    ++u->n358; u->p358 = s; u->u358 = id;
    u->s358 = buf;
}
static void BindUser(UserObj* u) {
    u->vt = u->vtS.s;
    u->vtS.s[0x268/8] = (void*)UserIsOnline268;
    u->vtS.s[0x350/8] = (void*)UserDisplay350;
    u->vtS.s[0x358/8] = (void*)UserSend358;
}

// ---------- the game-mgr mock ----------
struct GameMgr {
    void* vt; void* pPad;
    void* pInner;   // +0x10 (the member map)
    SVt vtS;
    int n2b0; uint32_t u2b0; void* p2b0;
    int nB8; int idB8;
    int n40; uint32_t u40; char* s40; int a40;
};
static void MgrFillIds2b0(void* p, uint32_t id,
                          void* pVec) {
    GameMgr* m = (GameMgr*)p;
    ++m->n2b0; m->u2b0 = id; m->p2b0 = pVec;
    // the ids {101, 102, 103} — heap so the
    // cleanup's op-delete balances
    int* s_ids = (int*)MockOpNew(8 * 4);
    s_ids[0] = 101; s_ids[1] = 102;
    s_ids[2] = 103;
    char* v = (char*)pVec;
    *(void**)(v + 0x18) = s_ids;
    *(void**)(v + 0x20) = s_ids + 3;
    *(void**)(v + 0x28) = s_ids + 8;
}
static void MgrNameB8(void* p, int id) {
    GameMgr* m = (GameMgr*)p;
    ++m->nB8; m->idB8 = id;
}
static void MgrAnnounce40(void* p, uint32_t id,
                          char* s, int a) {
    GameMgr* m = (GameMgr*)p;
    ++m->n40; m->u40 = id; m->s40 = s;
    m->a40 = a;
}
static void BindGameMgr(GameMgr* m) {
    m->vt = m->vtS.s;
    m->vtS.s[0x2b0/8] = (void*)MgrFillIds2b0;
    m->vtS.s[0xb8/8]  = (void*)MgrNameB8;
    m->vtS.s[0x40/8]  = (void*)MgrAnnounce40;
}
static GameMgr g_gameMgr;
// reset the game-mgr capture counters between
// the E2E sections (the cumulative announce/name
// counts otherwise double)
static void ResetGameMgr() {
    g_gameMgr.n2b0 = 0; g_gameMgr.nB8 = 0;
    g_gameMgr.n40 = 0;
    g_gameMgr.idB8 = 0; g_gameMgr.u40 = 0;
}

// the vt378 scorer (compete type 1): the per-user
// points
static int g_ptOf[256];
static uint64_t MockVt378(void* p, int n) {
    (void)p;
    return (uint64_t)g_ptOf[n & 0xff];
}
// the cross scorer (compete type 3)
static int g_nCrossPt = 0;
static int MockCrossPoint(void* p, uint64_t syn,
                          uint32_t user) {
    (void)p; (void)syn; ++g_nCrossPt;
    return g_ptOf[user & 0xff];
}
// the list fill (the pots)
static int g_nListFill = 0;
static int g_potMoney = 0, g_potEmoney = 0;
static void MockListFill(void* p, int* pnA,
                        int* pnB, uint32_t id,
                        int nType) {
    (void)p; (void)id; (void)nType;
    ++g_nListFill;
    *pnA = g_potMoney; *pnB = g_potEmoney;
}
// the online award seam
static int g_nAwardOnline = 0;
static uint32_t g_uAwardOnline = 0;
static int g_tAwardOnline = 0;
static int g_pAwardOnline = 0;
static int g_mAwardOnline = 0;
static int g_eAwardOnline = 0;
static void MockAwardOnline(void* p, uint32_t u,
    int t, int pt, int m, int e) {
    (void)p; ++g_nAwardOnline;
    g_uAwardOnline = u; g_tAwardOnline = t;
    g_pAwardOnline = pt; g_mAwardOnline = m;
    g_eAwardOnline = e;
}

// ---------- the league + the meed map fixtures --
// the league: the vec at +8 (+0x18 begin...) and
// the byte at +0x38
struct League {
    char raw[0x40];
    void* cells[16];
};
static void BindLeague(League* l) {
    memset(l, 0, sizeof(*l));
    char* v = l->raw + 8;
    *(void**)v = v;           // the self proxy
    *(void**)(v + 0x18) = l->cells;
    *(void**)(v + 0x20) = l->cells;
    *(void**)(v + 0x28) = l->cells + 16;
}

// the meed-map node (the d45 kit)
static char* Node(uint32_t id, void* val, int black) {
    char* n = (char*)calloc(1, 0x30);
    *(char**)n = nullptr;
    *(char**)(n + 8) = nullptr;
    *(char**)(n + 0x10) = nullptr;
    *(uint32_t*)(n + 0x18) = id;
    *(void**)(n + 0x20) = val;
    // +0x28 = the black mark; +0x29 stays 0
    // (the sentinel flag) — the d45 Node kit
    *(uint8_t*)(n + 0x28) = black ? 1 : 0;
    return n;
}
static void BuildMeedMap(void* meed, uint32_t id,
                         void* league) {
    char* mc = (char*)meed;
    char* head = *(char**)(mc + 0x30);
    char* r = Node(id, league, 1);
    *(char**)(head + 8) = r;      // the root
    *(char**)head = r;            // the leftmost
    *(char**)(head + 0x10) = r;   // the rightmost
    *(char**)(r + 8) = head;      // the parent
    *(char**)r = head;            // left
    *(char**)(r + 0x10) = head;   // right
    *(uint64_t*)(mc + 0x38) = 1;  // the size
}

// the pool (the empty self-proxied per-type vecs)
static char g_pool[0xd0];
static void ResetPool() {
    memset(g_pool, 0, sizeof(g_pool));
    g_pMeedPool = g_pool;
    for (int t = 1; t <= 4; ++t) {
        char* v = g_pool + (t - 1) * 0x30;
        *(void**)v = v;
    }
}

// ---------- the member map (the syn lookup) ----
// the REAL 0x30-node tree via the D32/D34 kit
// (LeagueMemberCtor + LeagueInsert) — the map
// lives at mgr+8 (the lookup's pcMgr+8)
static char g_inner[0x100];
static void BuildMemberMap(uint32_t uId) {
    memset(g_inner, 0, sizeof(g_inner));
    char* pmap = g_inner + 8;
    LeagueMemberCtor(pmap);
    // the first insert: attach = the head, left
    uint64_t kv[2] = {(uint64_t)uId,
                      0x900};
    char* head = *(char**)(pmap + 0x30);
    char out[2][8];
    LeagueInsert(pmap, out[0], 1, head, kv);
}
// the empty map (the not-found branch)
static void BuildEmptyMemberMap() {
    memset(g_inner, 0, sizeof(g_inner));
    LeagueMemberCtor(g_inner + 8);
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);

    // ---- bind the seams ----
    g_fnMeedLog = MockLog;
    g_fnMeritInvalid = MockInvalid;
    g_fnMeritOpNew = MockOpNew;
    g_fnMeritOpDelete = MockOpDelete;
    g_fnMeedSnprintf = MockSnprintf;
    g_fnMeedStrInst = StrInst;
    g_fnMeedStrGet = StrGet;
    g_fnMeedLogSave = MockLogSave;
    g_fnMeedTimeGet = MockTimeGet;
    g_fnMeedRandGet = MockRandGet;
    g_fnMeedEntryCmp = CmpPointDesc;
    g_fnMeedInstGet = MockInstGet;
    g_fnMeedListFill = MockListFill;
    g_fnMeedAwardOnline = MockAwardOnline;
    g_fnMgrVt378 = MockVt378;
    g_fnMeedCrossPoint = MockCrossPoint;
    g_fnGetGameMgr = []() -> void* {
        return &g_gameMgr; };
    // the D28 node alloc (the cross ctor's head)
    g_fnNodeAlloc = []() -> void* {
        return MockOpNew(0x68); };
    BindRecSys(&g_recSys);
    BindGameMgr(&g_gameMgr);
    ResetPool();
    MeedUserMgrReset();
    // the ids random pick default
    g_retRand = 0;

    // ================= D55b-1: 1417800b0 =====
    {
        g_nLog = 0;
        assert(MeedTypeByCompeteGet(nullptr, 0)
            == 2);
        assert(MeedTypeByCompeteGet(nullptr, 1)
            == 2);
        assert(MeedTypeByCompeteGet(nullptr, 2)
            == 1);
        assert(MeedTypeByCompeteGet(nullptr, 3)
            == 3);
        assert(g_nLog == 0);
        assert(MeedTypeByCompeteGet(nullptr, 4)
            == 0);
        assert(g_nLog == 1);
        printf("D55b-1 the type map ok\n");
    }

    // ================= D55b-2: 141781b10 =====
    {
        int ids[3] = {11, 22, 33};
        uint64_t ivec[6] = {};
        void* prox = MockOpNew(8);
        *(void**)prox = ivec;
        ivec[0] = (uint64_t)(uintptr_t)prox;
        ivec[3] = (uint64_t)(uintptr_t)ids;
        ivec[4] = (uint64_t)(uintptr_t)(ids + 3);
        ivec[5] = (uint64_t)(uintptr_t)(ids + 8);
        g_retRand = 0;
        assert(MeedRandomMemberPick(nullptr, ivec)
            == 11);
        assert(g_argRand == 2
            && "RandGet(count-1) with count=3");
        g_retRand = 2;
        assert(MeedRandomMemberPick(nullptr, ivec)
            == 33);
        g_retRand = 3;   // out of range
        assert(MeedRandomMemberPick(nullptr, ivec)
            == 0);
        // the empty vec
        uint64_t ivec2[6] = {};
        void* prox2 = MockOpNew(8);
        *(void**)prox2 = ivec2;
        ivec2[0] = (uint64_t)(uintptr_t)prox2;
        g_retRand = 0;
        assert(MeedRandomMemberPick(nullptr, ivec2)
            == 0);
        assert(g_argRand == -1
            && "RandGet(-1) when empty");
        MockOpDelete(prox);
        MockOpDelete(prox2);
        printf("D55b-2 the random pick ok\n");
    }

    // ================= D55b-3: 1417849f0 ======
    {
        // the ids {101, 102, 103}; vt378 points
        g_ptOf[101] = 100; g_ptOf[102] = 50;
        g_ptOf[103] = 50;
        g_ptOf[104] = 0;   // the zero-point user
        int ids[4] = {101, 102, 103, 104};
        uint64_t ivec[6] = {};
        void* prox = MockOpNew(8);
        *(void**)prox = ivec;
        ivec[0] = (uint64_t)(uintptr_t)prox;
        ivec[3] = (uint64_t)(uintptr_t)ids;
        ivec[4] = (uint64_t)(uintptr_t)(ids + 4);
        ivec[5] = (uint64_t)(uintptr_t)(ids + 8);
        uint64_t evec[6] = {};
        void* eprox = MockOpNew(8);
        *(void**)eprox = evec;
        evec[0] = (uint64_t)(uintptr_t)eprox;
        int nTotal = 0, nMaxU = 0, nMaxP = 0;
        g_nLog = 0;
        uint64_t r = MeedCollectPoint(
            (void*)0x10, 50, evec, &nTotal,
            &nMaxU, &nMaxP, 1, ivec);
        assert(r == 1 && g_nLog == 0);
        assert(nTotal == 200
            && "100+50+50, the zero user skipped");
        assert(nMaxU == 101 && nMaxP == 100);
        // 3 entries pushed (user 104 skipped)
        MeedEntry5* e = (MeedEntry5*)
            (uintptr_t)evec[3];
        int n = (int)((evec[4] - evec[3]) / 0x14);
        assert(n == 3);
        assert(e[0].v[1] == 101
            && e[0].v[2] == 100);
        assert(e[1].v[1] == 102
            && e[1].v[2] == 50);
        assert(e[2].v[1] == 103
            && e[2].v[2] == 50);
        // all the {0, id, pt, 0, 0} shape
        for (int i = 0; i < 3; ++i) {
            assert(e[i].v[0] == 0
                && e[i].v[3] == 0
                && e[i].v[4] == 0);
        }
        MockOpDelete((void*)evec[3]);
        // the null scorer (type 0, fa40 unbound)
        g_nLog = 0;
        r = MeedCollectPoint((void*)0x10, 50, evec,
            &nTotal, &nMaxU, &nMaxP, 0, ivec);
        assert(r == 0 && g_nLog == 1);
        // the bad type
        g_nLog = 0;
        r = MeedCollectPoint((void*)0x10, 50, evec,
            &nTotal, &nMaxU, &nMaxP, 4, ivec);
        assert(r == 0 && g_nLog == 1);
        // the null out params
        g_nLog = 0;
        r = MeedCollectPoint((void*)0x10, 50,
            evec, nullptr, &nMaxU, &nMaxP, 1,
            ivec);
        assert(r == 0 && g_nLog == 1);
        MockOpDelete(prox);
        MockOpDelete(eprox);
        printf("D55b-3 the collect point ok\n");
    }

    // ============ D55b-4: 1417846e0 (types 1/3)
    {
        auto mk = [](MeedEntry5* e, int user,
                     int pt) {
            for (int i = 0; i < 5; ++i) e->v[i] = 0;
            e->v[1] = user; e->v[2] = pt;
        };
        // case A: emoney 100 fully consumed
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = MockOpNew(8);
            *(void**)prox = vec;
            vec[0] = (uint64_t)(uintptr_t)prox;
            vec[3] = (uint64_t)(uintptr_t)e;
            vec[4] = (uint64_t)(uintptr_t)(e + 3);
            vec[5] = (uint64_t)(uintptr_t)(e + 8);
            uint64_t r = MeedCollectAward13(
                nullptr, vec, 200, 300, 100);
            assert(r == 1
                && "the emoney pot consumed");
            // money floor 300*pt/200
            assert(e[0].v[3] == 150
                && e[1].v[3] == 75
                && e[2].v[3] == 75);
            // emoney ceil 100*pt/200
            assert(e[0].v[4] == 50
                && e[1].v[4] == 25
                && e[2].v[4] == 25);
            assert(e[0].v[3] + e[1].v[3]
                + e[2].v[3] == 300);
            assert(e[0].v[4] + e[1].v[4]
                + e[2].v[4] == 100);
            MockOpDelete(prox);
        }
        // case B: the clamped tail (emoney 10 with
        // ceil shares 5/3/3 = 11 > 10)
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = MockOpNew(8);
            *(void**)prox = vec;
            vec[0] = (uint64_t)(uintptr_t)prox;
            vec[3] = (uint64_t)(uintptr_t)e;
            vec[4] = (uint64_t)(uintptr_t)(e + 3);
            vec[5] = (uint64_t)(uintptr_t)(e + 8);
            uint64_t r = MeedCollectAward13(
                nullptr, vec, 200, 0, 10);
            assert(r == 1);
            assert(e[0].v[4] == 5
                && "the first ceil share 5");
            assert(e[1].v[4] == 3);
            assert(e[2].v[4] == 2
                && "the last clamped to the rest");
            assert(e[0].v[4] + e[1].v[4]
                + e[2].v[4] == 10);
            assert(e[0].v[3] == 0
                && e[1].v[3] == 0
                && e[2].v[3] == 0
                && "no money pot, no shares");
            MockOpDelete(prox);
        }
        printf("D55b-4 the collect 13 ok\n");
    }

    // ============ D55b-5: 1417842d0 (type 2) ===
    {
        auto mk = [](MeedEntry5* e, int user,
                     int pt) {
            for (int i = 0; i < 5; ++i) e->v[i] = 0;
            e->v[1] = user; e->v[2] = pt;
        };
        auto wire = [](uint64_t* vec, MeedEntry5* e,
                       int n) {
            void* prox = MockOpNew(8);
            *(void**)prox = vec;
            vec[0] = (uint64_t)(uintptr_t)prox;
            vec[3] = (uint64_t)(uintptr_t)e;
            vec[4] = (uint64_t)(uintptr_t)(e + n);
            vec[5] = (uint64_t)(uintptr_t)(e + 8);
            return prox;
        };
        // case A: the +1 remainder path (emoney
        // 101: floor 50/25/25, rem 1 -> +1 top)
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = wire(vec, e, 3);
            uint64_t r = MeedCollectAward2(
                nullptr, vec, 200, 300, 101);
            assert(r == 1);
            assert(e[0].v[3] == 150
                && e[1].v[3] == 75
                && e[2].v[3] == 75);
            assert(e[0].v[4] == 51
                && "the +1 goes to the top sorted");
            assert(e[1].v[4] == 25
                && e[2].v[4] == 25);
            assert(e[0].v[4] + e[1].v[4]
                + e[2].v[4] == 101);
            MockOpDelete(prox);
        }
        // case B: rem 2 -> +1 to the top two
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = wire(vec, e, 3);
            uint64_t r = MeedCollectAward2(
                nullptr, vec, 200, 300, 103);
            assert(r == 1);
            assert(e[0].v[4] == 52
                && e[1].v[4] == 26
                && e[2].v[4] == 25);
            assert(e[0].v[4] + e[1].v[4]
                + e[2].v[4] == 103);
            MockOpDelete(prox);
        }
        // case C: the exact split (rem 0 -> early 1)
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = wire(vec, e, 3);
            uint64_t r = MeedCollectAward2(
                nullptr, vec, 200, 300, 100);
            assert(r == 1);
            assert(e[0].v[4] == 50
                && e[1].v[4] == 25
                && e[2].v[4] == 25);
            MockOpDelete(prox);
        }
        // case D: the per-entry spread (emoney 900:
        // floor 450/225/225 rem 0?? -> actually
        // 900*100/200=450, 225, 225 -> consumed
        // exactly) — use 901: rem 1
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = wire(vec, e, 3);
            uint64_t r = MeedCollectAward2(
                nullptr, vec, 200, 0, 901);
            assert(r == 1);
            // rem 1, count 3, rem/count = 0 -> the
            // +1 path to the top
            assert(e[0].v[4] == 451);
            assert(e[1].v[4] == 225
                && e[2].v[4] == 225);
            assert(e[0].v[4] + e[1].v[4]
                + e[2].v[4] == 901);
            MockOpDelete(prox);
        }
        // case E: rem 30 -> 30/3 = 10 each
        {
            MeedEntry5 e[3];
            mk(&e[0], 101, 100);
            mk(&e[1], 102, 50);
            mk(&e[2], 103, 50);
            uint64_t vec[6] = {};
            void* prox = wire(vec, e, 3);
            uint64_t r = MeedCollectAward2(
                nullptr, vec, 200, 0, 730);
            assert(r == 1);
            // floor 365/182/182 = 729, rem 1?? —
            // 730*100/200 = 365, 730*50/200 = 182
            // (int div), sum 729, rem 1 → +1 top
            assert(e[0].v[4] == 366
                && e[1].v[4] == 182
                && e[2].v[4] == 182);
            assert(e[0].v[4] + e[1].v[4]
                + e[2].v[4] == 730);
            MockOpDelete(prox);
        }
        // case F: the empty vec + a remainder ->
        // the size log
        {
            uint64_t vec[6] = {};
            void* prox = MockOpNew(8);
            *(void**)prox = vec;
            vec[0] = (uint64_t)(uintptr_t)prox;
            vec[3] = 0; vec[4] = 0; vec[5] = 0;
            g_nLog = 0;
            uint64_t r = MeedCollectAward2(
                nullptr, vec, 200, 0, 50);
            assert(r == 0 && g_nLog == 1);
            MockOpDelete(prox);
        }
        printf("D55b-5 the collect 2 ok\n");
    }

    // ============ D55b-6: 141779b60 (the record)
    {
        League lg;
        BindLeague(&lg);
        int entry[5] = {7, 101, 100, 150, 50};
        g_recSys.tblMeed.nCommit50 = 0;
        memset(g_recSys.tblMeed.fld, 0,
               sizeof(g_recSys.tblMeed.fld));
        // the memset wipes the bound vt ptrs —
        // re-bind the field objects
        for (int i = 0; i < 8; ++i)
            BindRecField(&g_recSys.tblMeed.fld[i]);
        uint64_t r = MeedRecordInsert(&lg, 2,
                                      entry);
        assert(r == 1);
        // the fields: 1 = entry[0] (7), 3 = type,
        // 2 = entry[1] (101), 4 = point, 5 = money,
        // 6 = emoney
        assert(g_recSys.tblMeed.fld[0].nWrites
            == 1 && g_recSys.tblMeed.fld[0]
                .i32s[0] == 7);
        assert(g_recSys.tblMeed.fld[2].nWrites
            == 1 && g_recSys.tblMeed.fld[2]
                .i32s[0] == 2);
        assert(g_recSys.tblMeed.fld[1].nWrites
            == 1 && g_recSys.tblMeed.fld[1]
                .i32s[0] == 101);
        assert(g_recSys.tblMeed.fld[3].nWrites
            == 1 && g_recSys.tblMeed.fld[3]
                .i32s[0] == 100);
        assert(g_recSys.tblMeed.fld[4].nWrites
            == 1 && g_recSys.tblMeed.fld[4]
                .i32s[0] == 150);
        assert(g_recSys.tblMeed.fld[5].nWrites
            == 1 && g_recSys.tblMeed.fld[5]
                .i32s[0] == 50);
        assert(g_recSys.tblMeed.nCommit50 == 1
            && g_recSys.tblMeed.nArg50 == 0);
        // the push to the league vec at +8
        assert(*(void**)(lg.raw + 8 + 0x18)
            == lg.cells);
        assert(*(void**)(lg.raw + 8 + 0x20)
            == (void*)(lg.cells + 1));
        assert(*(uint8_t*)(lg.raw + 0x38) == 0
            && "the byte at league+0x38 cleared");
        // the bad type
        g_nLog = 0;
        r = MeedRecordInsert(&lg, 4, entry);
        assert(r == 0 && g_nLog == 1);
        printf("D55b-6 the meed record ok\n");
    }

    // ====== D55b-7: 14177f0d0 (the point record)
    {
        RecTable& t = g_recSys.tblPoint;
        t.nCommit50 = 0; t.nCommit0 = 0;
        t.uRet50 = 1;
        memset(t.fld, 0, sizeof(t.fld));
        for (int i = 0; i < 8; ++i)
            BindRecField(&t.fld[i]);
        // negative -> 0, no writes
        assert(MeedRecordUserPoint(
            nullptr, 101, 2, -1, 5) == 0);
        assert(MeedRecordUserPoint(
            nullptr, 101, 2, 5, -1) == 0);
        assert(t.nCommit50 == 0);
        // both zero -> 1, no writes
        assert(MeedRecordUserPoint(
            nullptr, 101, 2, 0, 0) == 1);
        assert(t.nCommit50 == 0
            && t.nCommit0 == 0);
        // the write path: fields 1(user)/4(type)/
        // 2(money)/3(emoney); vt+0x50 flag =
        // emoney != 0; the vt+0 commit (1)
        uint8_t r = MeedRecordUserPoint(
            nullptr, 101, 2, 150, 50);
        assert(r == 1);
        assert(t.fld[0].nWrites == 1
            && t.fld[0].i32s[0] == 101);
        assert(t.fld[3].nWrites == 1
            && t.fld[3].i32s[0] == 2);
        assert(t.fld[1].nWrites == 1
            && t.fld[1].i32s[0] == 150);
        assert(t.fld[2].nWrites == 1
            && t.fld[2].i32s[0] == 50);
        assert(t.nCommit50 == 1 && t.nArg50 == 1
            && "the flag = emoney != 0");
        assert(t.nCommit0 == 1
            && t.nArgCommit0 == 1);
        // the emoney-0 variant: the flag 0
        t.nCommit50 = 0; t.nArg50 = -1;
        MeedRecordUserPoint(nullptr, 101, 2,
                            150, 0);
        assert(t.nArg50 == 0);
        // the bad type
        g_nLog = 0;
        assert(MeedRecordUserPoint(
            nullptr, 101, 4, 1, 1) == 0);
        assert(g_nLog == 1);
        printf("D55b-7 the point record ok\n");
    }

    // ===== D55b-8: 141781860 + 1417821d0 ======
    {
        UserObj user;
        memset(&user, 0, sizeof(user));
        BindUser(&user);
        user.cOnline = 0;   // disonline
        void* pThis = &user;  // *pThis = &user??
        // the CSynArenicMeed's first qword points
        // at the user object
        static void* s_pUser;
        s_pUser = &user;
        void** aThis = &s_pUser;

        // type 1, emoney > 0
        g_nTimeGet = 0; g_nSnprintf = 0;
        g_nLogSave = 0;
        g_recSys.tblPoint.uRet50 = 1;
        MeedAwardUserDisonline(aThis, 101, 1,
                               100, 150, 50);
        assert(user.n350 == 1 && user.e350 == 0x1c
            && "the type-1 emoney display id");
        assert(user.a350 == 0 && user.b350 == 101);
        assert(g_nTimeGet == 1);
        assert(g_nSnprintf == 1);
        assert(user.n358 == 1);
        assert(strcmp(user.p358, "SYSTEM") == 0);
        assert(user.u358 == 101);
        assert(g_nLogSave == 1);
        assert(strcmp(g_fileLogSave[0],
                      "gmlog/vlm_meed_award") == 0);
        assert(g_idLogSave[0] == 101);
        // the prompt string per type
        assert(strcmp(g_bufSnprintf,
            "STR_VLM_ARENIC_DISTRIBUTEMEED2") == 0);

        // type 2
        g_nLogSave = 0;
        MeedAwardUserDisonline(aThis, 102, 2,
                               50, 75, 25);
        assert(user.e350 == 0x17);
        assert(strcmp(g_fileLogSave[0],
                      "gmlog/syn_meed_award") == 0);
        assert(strcmp(g_bufSnprintf,
            "STR_SYN_ARENIC_DISTRIBUTEMEED2") == 0);

        // type 3
        g_nLogSave = 0;
        MeedAwardUserDisonline(aThis, 103, 3,
                               50, 75, 25);
        assert(user.e350 == 0x27);
        assert(strcmp(g_fileLogSave[0],
            "gmlog/cross_vlm_meed_award") == 0);
        assert(strcmp(g_bufSnprintf,
            "STR_CROSS_VLM_ARENIC_DISTRIBUTEMEED2")
            == 0);

        // emoney == 0 -> NO display
        user.n350 = 0;
        MeedAwardUserDisonline(aThis, 104, 1,
                               10, 100, 0);
        assert(user.n350 == 0);

        // the record fail -> the log, no display
        g_nLog = 0; user.n350 = 0;
        g_recSys.tblPoint.uRet50 = 0;
        MeedAwardUserDisonline(aThis, 105, 1,
                               10, 100, 5);
        assert(g_nLog == 1 && user.n350 == 0);
        g_recSys.tblPoint.uRet50 = 1;

        // the bad type
        g_nLog = 0;
        MeedAwardUserDisonline(aThis, 106, 4,
                               10, 100, 5);
        assert(g_nLog == 1);

        // ---- MeedAwardUser: the dispatch ----
        // disonline (vt+0x268 -> 0)
        user.cOnline = 0; user.n350 = 0;
        g_nAwardOnline = 0;
        MeedAwardUser(aThis, 201, 2, 50, 75, 25);
        assert(user.n350 == 1
            && g_nAwardOnline == 0);
        // online -> the seam
        user.cOnline = 1; user.n350 = 0;
        MeedAwardUser(aThis, 201, 2, 50, 75, 25);
        assert(g_nAwardOnline == 1
            && g_uAwardOnline == 201
            && g_tAwardOnline == 2
            && g_pAwardOnline == 50
            && g_mAwardOnline == 75
            && g_eAwardOnline == 25
            && user.n350 == 0);
        // the bad type
        g_nLog = 0;
        MeedAwardUser(aThis, 201, 4, 50, 75, 25);
        assert(g_nLog == 1);
        printf("D55b-8 the award paths ok\n");
    }

    // ===== D55b-9: the E2E (compete 1) ========
    {
        // the member map: syn 50 found
        BuildMemberMap(50);
        g_gameMgr.pInner = g_inner;
        // the meed map: syn 50 -> the league
        MeedResetSingleton();
        void* meed = MeedSingletonGet();
        static League s_lg;
        BindLeague(&s_lg);
        BuildMeedMap(meed, 50, &s_lg);
        // the scorer points
        ResetGameMgr();
        g_ptOf[101] = 100; g_ptOf[102] = 50;
        g_ptOf[103] = 50;
        g_potMoney = 300; g_potEmoney = 101;
        g_retRand = 1;   // the random keeper = 102
        g_recSys.tblPoint.uRet50 = 1;
        ResetPointTable();
        g_nListFill = 0; g_nLogSave = 0;
        g_nInvalid = 0;
        int nLive0 = g_nLive;

        // the user (disonline)
        static UserObj s_user;
        memset(&s_user, 0, sizeof(s_user));
        BindUser(&s_user);
        s_user.cOnline = 0;
        static void* s_pUser = &s_user;
        MeedDistributeSyn(&s_pUser, 50, 1);

        // the flow asserts
        assert(g_gameMgr.n2b0 == 1
            && g_gameMgr.u2b0 == 50
            && "the ids fill via vt+0x2b0");
        assert(g_nListFill == 1
            && "the pot query");
        // 3 disonline awards (record ok)
        assert(s_user.n350 == 3
            && "three emoney displays");
        assert(s_user.n358 == 3);
        assert(g_nLogSave == 3
            && "three award gmlogs");
        // the award amounts: collect2 with emoney
        // 101: 51/25/25 money 150/75/75 — the
        // record fields capture the last write
        // per field; the award order is the vec
        // order (101, 102, 103) — the last = 103
        // (75 money, 25 emoney)
        RecTable& tp = g_recSys.tblPoint;
        assert(tp.fld[1].nWrites == 3
            && tp.fld[2].nWrites == 3);
        // the meed records pushed: 3
        assert(*(void**)(s_lg.raw + 8 + 0x20)
            == (void*)(s_lg.cells + 3));
        // the keeper announce: maxUser = 101
        assert(g_gameMgr.nB8 == 1
            && g_gameMgr.idB8 == 101);
        assert(g_gameMgr.n40 == 1
            && g_gameMgr.u40 == 50
            && g_gameMgr.a40 == 0);
        // the cleanup: the live balance restored
        // (the proxies + the vec buffers freed)
        assert(g_nLive == nLive0
            && "the full cleanup (the user-mgr was"
               " created back in section 8)");
        assert(g_nInvalid == 0);
        printf("D55b-9 the E2E compete-1 ok\n");
    }

    // ===== D55b-10: the E2E (compete 3) =======
    {
        // the scorer = the cross (fa60)
        MeedResetSingleton();
        void* meed = MeedSingletonGet();
        static League s_lg;
        BindLeague(&s_lg);
        BuildMeedMap(meed, 50, &s_lg);
        ResetGameMgr();
        g_ptOf[101] = 100; g_ptOf[102] = 50;
        g_ptOf[103] = 50;
        g_nCrossPt = 0;
        g_potMoney = 0; g_potEmoney = 10;
        g_retRand = 0;
        g_recSys.tblPoint.uRet50 = 1;
        ResetPointTable();
        g_nLogSave = 0;
        static UserObj s_user;
        memset(&s_user, 0, sizeof(s_user));
        BindUser(&s_user);
        s_user.cOnline = 0;
        static void* s_pUser = &s_user;
        MeedDistributeSyn(&s_pUser, 50, 3);
        // the cross scorer used
        assert(g_nCrossPt == 3);
        // collect13 (meedType 3): ceil 5/3 clamped
        // to 5/3/2 — the displays: 0x27 emoney type
        assert(s_user.n350 == 3
            && s_user.e350 == 0x27);
        assert(g_nLogSave == 3
            && strcmp(g_fileLogSave[2],
                "gmlog/cross_vlm_meed_award") == 0);
        printf("D55b-10 the E2E compete-3 ok\n");
    }

    // ===== D55b-11: the failure branches ======
    {
        // the syn NOT found (an empty member map)
        BuildEmptyMemberMap();
        g_gameMgr.pInner = g_inner;
        g_nLogSave = 0; g_nLog = 0;
        static void* s_pUser = nullptr;
        MeedDistributeSyn(&s_pUser, 50, 1);
        assert(g_nLogSave == 1
            && "the not-find gmlog");
        assert(g_idLogSave[0] == 50);

        // the bad compete type
        g_nLog = 0;
        MeedDistributeSyn(&s_pUser, 50, 4);
        assert(g_nLog == 1
            && "the literal not-found log");

        // the empty-entries synthetic path:
        // the scorer returns 0 for all (type 1
        // proceeds with total 0) -> the random
        // keeper gets the whole pot
        MeedResetSingleton();
        void* meed = MeedSingletonGet();
        static League s_lg;
        BindLeague(&s_lg);
        BuildMeedMap(meed, 50, &s_lg);
        BuildMemberMap(50);
        g_gameMgr.pInner = g_inner;
        ResetGameMgr();
        g_ptOf[101] = 0; g_ptOf[102] = 0;
        g_ptOf[103] = 0;
        g_potMoney = 300; g_potEmoney = 100;
        g_retRand = 2;   // the keeper = 103
        g_nLogSave = 0;
        static UserObj s_user;
        memset(&s_user, 0, sizeof(s_user));
        BindUser(&s_user);
        s_user.cOnline = 0;
        static void* s_pUser2 = &s_user;
        g_recSys.tblPoint.uRet50 = 1;
        ResetPointTable();
        int nLive0 = g_nLive;
        MeedDistributeSyn(&s_pUser2, 50, 1);
        // the synthetic award: user 103 gets
        // 300 money / 100 emoney (point 0)
        assert(s_user.n350 == 1);
        RecTable& tp = g_recSys.tblPoint;
        // the last point record: money 300,
        // emoney 100, user 103
        assert(tp.fld[0].nWrites == 1
            && tp.fld[0].i32s[0] == 103);
        assert(tp.fld[1].i32s[0] == 300);
        assert(tp.fld[2].i32s[0] == 100);
        // the "no user get point !!" gmlog
        assert(g_nLogSave == 2
            && "the synthetic-path log + the award"
               " gmlog");
        // the announce: the keeper = 103
        assert(g_gameMgr.idB8 == 103);
        assert(g_gameMgr.n40 == 1);
        assert(g_nLive == nLive0
            && "the full cleanup");
        printf("D55b-11 the failure branches ok\n");
    }

    printf(
      "SYNDICATE_D55B_OK: the distribute flow\n");
    return 0;
}

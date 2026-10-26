#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>

#include "Exe/Dll/Syndicate/Port/SyndicateMeedEnd.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedApply.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedInfo.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueCmp.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include "Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"

using namespace syndicate;

// ---------- the vtable kit ----------
struct SVt { void* s[0x80]; };

// the field object: the member sub (money/emoney)
struct FieldObj {
    void* vt; SVt vtS; int* pStore;
};
static int  FldGet48(void* p) {
    return *(((FieldObj*)p)->pStore); }
static void FldSetB0(void* p, int64_t v) {
    *(((FieldObj*)p)->pStore) = (int)v; }
static void BindField(FieldObj* f, int* p) {
    f->vt = f->vtS.s;
    f->pStore = p;
    f->vtS.s[0x48/8]  = (void*)FldGet48;
    f->vtS.s[0xb0/8] = (void*)FldSetB0;
}

// the id field: vt+0x40() = the id
struct IdField {
    void* vt; SVt vtS; uint32_t uId;
};
static uint32_t IdGet40(void* p) {
    return ((IdField*)p)->uId; }
static uint64_t IdRel40(void* p, uint64_t u) {
    ++*(int*)0; (void)p; (void)u;
    return 0; }   // (unused in the id field)
static void BindIdField(IdField* f, uint32_t u) {
    f->vt = f->vtS.s; f->uId = u;
    f->vtS.s[0x40/8] = (void*)IdGet40;
}

// the member: vt+0x10(idx)->field, vt+8(2)->
// the id field, vt+0x40/0 = the release pair
struct MemObj {
    void* vt; SVt vtS;
    IdField fId;
    FieldObj f3, f4;
    int money, emoney;
    // captures
    int nRel40; int nDtor0; int nSave38;
    // the count registry
    static int s_nLive;
    MemObj() : nRel40(0), nDtor0(0),
               nSave38(0), money(0), emoney(0) {
        vt = vtS.s;
        fId.vt = fId.vtS.s;
        BindField(&f3, &money);
        BindField(&f4, &emoney);
        ++s_nLive;
    }
};
int MemObj::s_nLive = 0;
static void* MemField10(void* p, int64_t n) {
    MemObj* m = (MemObj*)p;
    if (n == 3) return &m->f3;
    if (n == 4) return &m->f4;
    return &m->fId;   // 2 (and the rest)
}
static void* MemField8(void* p, int64_t n) {
    (void)n;
    return &((MemObj*)p)->fId;
}
static uint64_t MemRel40(void* p, uint64_t u) {
    (void)u; ++((MemObj*)p)->nRel40;
    return 1; }
static uint64_t MemDtor0(void* p, uint64_t u) {
    (void)u; ++((MemObj*)p)->nDtor0;
    return 1; }
static uint64_t MemSave38(void* p, uint64_t u) {
    (void)u; ++((MemObj*)p)->nSave38;
    return 1; }
static void BindMem(MemObj* m, uint32_t u) {
    m->vt = m->vtS.s;
    BindIdField(&m->fId, u);
    m->vtS.s[0x8/8]    = (void*)MemField8;
    m->vtS.s[0x10/8]   = (void*)MemField10;
    m->vtS.s[0x40/8]   = (void*)MemRel40;
    m->vtS.s[0x38/8]   = (void*)MemSave38;
    m->vtS.s[0x0]      = (void*)MemDtor0;
}

// ---------- the seams ----------
static int g_nLogs = 0;
static void MockLog() { ++g_nLogs; }
static void MockInvalid() { ++g_nLogs; }

// the sub seams (GetSynMeed + the comparators)
static void* MemSub(void* p, int n) {
    MemObj* m = (MemObj*)p;
    if (n == 3) return &m->money;
    if (n == 4) return &m->emoney;
    return &m->fId.uId;   // 2: the id
}
static int SubId(void* p) {
    return (int)(*(uint32_t*)p); }
static int SubVal(void* p) {
    return (int)(*(int*)p); }
static uint32_t SubVVal(void* p) {
    return (uint32_t)(*(int*)p); }

// the string mgr
static char g_sStrRet[0x40];
static void* StrInst() { return (void*)1; }
static char* StrGet(void*, const char* k) {
    snprintf(g_sStrRet, 0x40, "S(%s)", k);
    return g_sStrRet; }

// snprintf
static char g_sBuf[0x400];
static void MockSnprintf(char* pDst, size_t,
                         const char* pFmt) {
    snprintf(pDst, 0x400, "F(%s)", pFmt);
    snprintf(g_sBuf, 0x400, "F(%s)", pFmt);
}

// MyLogSave
static const char* g_szSaveFile = nullptr;
static uint32_t g_uSaveId = 0;
static void MockLogSave(const char* f,
                        const char*, uint32_t id) {
    g_szSaveFile = f; g_uSaveId = id; }

// the int-vec grow (14172d120): store or append
static int g_nGrow = 0;
static void MockVecInsertInt(void* pVec,
                             void* pPair[2],
                             int64_t, void* pVal) {
    (void)pPair; ++g_nGrow;
    void** v = (void**)pVec;
    int** ppBegin = (int**)&v[3];
    int** ppEnd   = (int**)&v[4];
    int** ppCap   = (int**)&v[5];
    if (*ppBegin == nullptr) {
        int* a = (int*)malloc(8 * sizeof(int));
        a[0] = *(int*)pVal;
        *ppBegin = a; *ppEnd = a + 1;
        *ppCap = a + 8;
        return;
    }
    **ppEnd = *(int*)pVal;
    ++*ppEnd;
}

// the mgr mock (the refunds + the announce)
static char g_cRefund1f0 = 1;
static char g_cRefund1f8 = 1;
static int  g_nRefund1f0 = 0, g_nRefund1f8 = 0;
static int  g_vRefund1f0 = 0, g_vRefund1f8 = 0;
static int  g_nAnn = 0; static int g_idAnn = 0;
static void* g_pAnnStr = nullptr;
struct Mgr {
    void* vt; SVt vtS;
};
static char MgrRefund1f0(void* p, int id,
                         int64_t v) {
    (void)p; ++g_nRefund1f0;
    g_vRefund1f0 = (int)v;
    return g_cRefund1f0; }
static char MgrRefund1f8(void* p, int id,
                         uint32_t v) {
    (void)p; ++g_nRefund1f8;
    g_vRefund1f8 = (int)v;
    return g_cRefund1f8; }
static void MgrAnnounce40(void* p, int id,
                          void* s, int a) {
    (void)p; (void)a;
    ++g_nAnn; g_idAnn = id; g_pAnnStr = s; }

// the user mock (the emoney display)
static int g_n350 = 0; static int g_e350 = 0;
static int g_a350 = 0; static int g_b350 = 0;
struct UserObj { void* vt; SVt vtS; };
static void UserDisplay350(void* p, int e,
                           int a, int b) {
    (void)p; ++g_n350;
    g_e350 = e; g_a350 = a; g_b350 = b; }

// pool helpers (as the D52 test)
static void* MockOpNew(size_t n) {
    void* p = malloc(n);
    memset(p, 0xcd, n);
    return p; }
static void MockOpDelete(void* p) { free(p); }

static void WireVec(char* pool, int nType,
                    void** cells, int n) {
    char* v = pool + (nType - 1) * 0x30;
    *(void**)(v + 0x18) = cells;
    *(void**)(v + 0x20) = cells + n;
    *(void**)(v + 0x28) = cells + 8;
    *(void**)v = v;   // the self proxy
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeedLog = MockLog;
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubId;
    g_fnMeedSubNType = SubVal;
    g_fnMeedSubNScore = SubVal;
    g_fnMeedMemSubV = [](void* p) -> void* {
        return (void*)&((MemObj*)p)->emoney; };
    g_fnMeedSubVVal = SubVVal;
    g_fnMeedStrInst = StrInst;
    g_fnMeedStrGet = StrGet;
    g_fnMeedSnprintf = MockSnprintf;
    g_fnMeedLogSave = MockLogSave;
    g_fnMeedVecInsertInt = MockVecInsertInt;
    g_fnMeritOpNew = MockOpNew;
    g_fnMeritOpDelete = MockOpDelete;
    g_nMeedMoneyCap = 2000000000;
    g_fnMeedReqId = [](void*) -> int {
        return 0; };
    g_pMeedPool = nullptr;

    // ---------- D54-1: MeedIdListBuild ------
    {
        static MemObj m1, m2, m3;
        BindMem(&m1, 101); BindMem(&m2, 102);
        BindMem(&m3, 103);
        static void* cells[8];
        cells[0] = &m1; cells[1] = &m2;
        cells[2] = &m3;
        static char pool[0xd0];
        memset(pool, 0, 0xd0);
        MeedPoolCtorReal(pool);
        WireVec(pool, 1, cells, 3);
        // the int vec with spare capacity
        static int ids[8];
        void* ivec[6] = {};
        void* prox = MockOpNew(8);
        *(void**)prox = ivec;
        ivec[0] = prox;
        ivec[3] = ids;
        ivec[4] = ids;
        ivec[5] = ids + 8;
        MeedIdListBuild(pool, 1, ivec);
        assert(ids[0] == 101 && ids[1] == 102
            && ids[2] == 103);
        assert(ivec[4] == (void*)(ids + 3)
            && "the end advanced by 3");
        assert(g_nGrow == 0
            && "the direct store used");
        printf("D54-1 idlist ok\n");
    }

    // ---------- D54-2: MeedDeleteSynMeed ----
    {
        static MemObj m1, m2, m3;
        BindMem(&m1, 201); BindMem(&m2, 202);
        BindMem(&m3, 203);
        static void* cells[8];
        cells[0] = &m1; cells[1] = &m2;
        cells[2] = &m3;
        static char pool[0xd0];
        memset(pool, 0, 0xd0);
        MeedPoolCtorReal(pool);
        WireVec(pool, 1, cells, 3);
        uint64_t r = MeedDeleteSynMeed(pool,
                                       202, 1);
        assert(r == 1);
        assert(m2.nRel40 == 1 && m2.nDtor0 == 1
            && "the release pair on the match");
        assert(m1.nRel40 == 0 && m3.nRel40 == 0);
        char* v = pool;
        assert(*(void**)(v + 0x20)
            == (void*)(cells + 2)
            && "the end shrunk by one");
        assert(cells[0] == (void*)&m1
            && cells[1] == (void*)&m3
            && "the compaction moved m3 up");
        // the not-found: returns 1, no change
        r = MeedDeleteSynMeed(pool, 999, 1);
        assert(r == 1
            && *(void**)(v + 0x20)
            == (void*)(cells + 2));
        // the bad type -> 0 + log
        int nLogs = g_nLogs;
        r = MeedDeleteSynMeed(pool, 1, 9);
        assert((r & 0xff) == 0
            && g_nLogs == nLogs + 1);
        // the double match: both erased, rescan
        BindMem(&m1, 777);
        BindMem(&m3, 777);
        cells[0] = &m1; cells[1] = &m3;
        *(void**)(v + 0x18) = cells;
        *(void**)(v + 0x20) = cells + 2;
        r = MeedDeleteSynMeed(pool, 777, 1);
        assert(r == 1
            && m1.nRel40 == 1 && m3.nRel40 == 1
            && *(void**)(v + 0x20) == cells
            && "both 777s erased via the rescan");
        printf("D54-2 delete ok\n");
    }

    // ---------- D54-3: MeedProcessEnd E2E ---
    {
        static MemObj m1, m2;
        BindMem(&m1, 301); BindMem(&m2, 302);
        m1.money = 500000; m1.emoney = 100;
        m2.money = 200000; m2.emoney = 0;
        static void* cells[8];
        cells[0] = &m1; cells[1] = &m2;
        static char pool[0xd0];
        memset(pool, 0, 0xd0);
        MeedPoolCtorReal(pool);
        WireVec(pool, 1, cells, 2);
        g_pMeedPool = pool;

        // the mgr mock: vt+0x1f0/0x1f8/0x40
        static Mgr mgr;
        mgr.vt = mgr.vtS.s;
        mgr.vtS.s[0x1f0/8] = (void*)MgrRefund1f0;
        mgr.vtS.s[0x1f8/8] = (void*)MgrRefund1f8;
        mgr.vtS.s[0x40/8]  = (void*)MgrAnnounce40;
        g_pLeagueDatInstance = &mgr;

        // the user mock: vt+0x350
        static UserObj u;
        u.vt = u.vtS.s;
        u.vtS.s[0x350/8] =
            (void*)UserDisplay350;
        static void* uProxy[1];
        uProxy[0] = &u;

        // the resets
        g_nRefund1f0 = 0; g_nRefund1f8 = 0;
        g_nAnn = 0; g_n350 = 0; g_nGrow = 0;
        g_nLogs = 0;
        g_szSaveFile = nullptr;
        g_sBuf[0] = '\0';

        uint64_t r = MeedProcessEnd(uProxy, 1);
        assert((r & 0xff) == 1);
        // both members processed
        assert(g_nRefund1f0 == 2
            && g_nRefund1f8 == 2);
        // the refunds POSITIVE (the verbatim
        //  (int)local_4b8 / (u32)local_4c0):
        assert(g_vRefund1f0 == 500000
            || g_vRefund1f0 == 200000);
        // the m1 emoney display fired (100 > 0)
        //  with the mt=4 type (0x29 for type1)
        assert(g_n350 == 1 && g_e350 == 0x29
            && g_a350 == 0 && g_b350 == 301
            && "the mt=4 display with (0, id)");
        // the gmlog + the prompt(7) announces
        assert(g_nAnn == 2);
        assert(strcmp(g_szSaveFile,
            "gmlog/money_vlmarenic") == 0);
        assert(strcmp(g_sBuf,
            "F(S(STR_VLM_ARENIC_END_PROCESS))")
            == 0
            && "the prompt(7) formatted");
        // both members erased + released
        assert(m1.nRel40 == 1 && m2.nRel40 == 1);
        assert(*(void**)(pool + 0x20)
            == (void*)cells
            && "the pool vector emptied");
        printf("D54-3 processend E2E ok\n");

        // the type-2 no-op path: returns 1,
        //  NOTHING happens
        g_nRefund1f0 = 0;
        r = MeedProcessEnd(uProxy, 2);
        assert((r & 0xff) == 1
            && g_nRefund1f0 == 0
            && "the type-2 no-op");

        // the bad type -> 0 + log
        int nLogs = g_nLogs;
        r = MeedProcessEnd(uProxy, 9);
        assert((r & 0xff) == 0
            && g_nLogs == nLogs + 1);
        printf("D54-4 the gates ok\n");
    }

    printf(
      "SYNDICATE_D54_OK: ProcessEndMeed + the "
      "id list + the erase\n");
    return 0;
}

// ============================================================
// Syndicate — unit D53: the SetArenicMeed flow (141780cb0)
// + the CMeedSetMgr apply family (14177db90 / 14177d5f0 /
// 14177cbd0 / 14177cb90 / 14177caa0 / 14177ff70 /
// 14177fbc0 / 14177fad0 / 1417da0d0 / 141732200).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "modules/syndicate/src/SyndicateMeedApply.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
#include "modules/syndicate/src/SyndicateMeedInfo.h"
#include "modules/syndicate/src/SyndicateMeedSort.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include "modules/syndicate/src/SyndicateSynMeed.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"

using namespace syndicate;

// ---------- the shared fixtures ----------
struct SVt { void* s[0x80]; };   // 0x400 of slots

static int g_nLog = 0;
static void MockLog() { ++g_nLog; }
static void MockInvalid() {
    fprintf(stderr, "INVALID\n"); abort(); }

// the member: {id(sub2), money(sub3), emoney(sub4)}
struct Member { uint64_t id, money, emoney; };
static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    if (n == 3) return &m->money;
    if (n == 4) return &m->emoney;
    return &m->id;
}
static int SubId(void* pS) {
    return (int)((uint64_t*)pS)[0]; }
static int SubVal(void* pS) {
    return (int)((uint64_t*)pS)[0]; }

// the logic-singleton mock (the vtable holder)
struct Mgr {
    void* vt; SVt vtS;
    bool gate78;
    int money268, emoney278;
    char deduct1f0, deduct1f8;
    int nTouch, idTouch;
    int nAnn, idAnn; void* sAnn; int aAnn;
    int nD0, idD0; int64_t vD0;
    int nD8, idD8;
};
static Mgr* g_pMgr = nullptr;

// the user-object mock (the vt at *(user))
struct UserObj {
    void* vt; SVt vtS;
    int out388; char r390; char gate360;
    int n18; uint32_t id18; void* s18;
    int n200; void* s200;
    int n8; uint32_t id8; void* s8;
    int n398; uint32_t id398; int a398, b398;
    int n350; int e350; int id350;
};
static UserObj* g_pUser = nullptr;

// the recordset mock chain (for Insert)
struct FieldObj {
    void* vt; SVt vtS;
    int* pStore;
};
struct Rs {
    void* vt; SVt vtS;
    FieldObj fld[8];
    int store[8];
    int nExec; char execRet;
    int nRel;
};
static Rs* g_pRs = nullptr;
static char g_sLastKey[64];

// the string-manager seam state
static char g_sStrRet[64];
static const char* g_szLastKey = nullptr;
static void* StrInst() { return (void*)1; }
static char* StrGet(void*, const char* pKey) {
    g_szLastKey = pKey;
    snprintf(g_sStrRet, 64, "S(%s)", pKey);
    return g_sStrRet;
}

// the snprintf seam state
static const char* g_szSnprintfFmt = nullptr;
static void MockSnprintf(char* pDst, size_t,
                         const char* pFmt) {
    g_szSnprintfFmt = pFmt;
    snprintf(pDst, 0x400, "F(%s)", pFmt);
}

// the gmlog state
static const char* g_szLogSaveFile = nullptr;
static const char* g_szLogSaveFmt = nullptr;
static uint32_t g_uLogSaveId = 0;
static void MockLogSave(const char* pFile,
                        const char* pFmt,
                        uint32_t uId) {
    g_szLogSaveFile = pFile;
    g_szLogSaveFmt = pFmt;
    g_uLogSaveId = uId;
}

// the vec-insert (grow) seam
static int g_nVecInsert = 0;
static void MockVecInsert(void* pVec,
                          void* itOut[2],
                          void* pPair[2],
                          void* pVal) {
    (void)pVec; (void)pPair;
    ++g_nVecInsert;
    (void)itOut; (void)pVal;
}

// ---------- the vtable thunks ----------
static uint64_t MgrGate78(void* p, uint32_t id) {
    (void)id; return ((Mgr*)p)->gate78 ? 1 : 0; }
static uint64_t MgrMoney268(void* p, int id) {
    (void)id; return ((Mgr*)p)->money268; }
static uint64_t MgrEmoney278(void* p, int id) {
    (void)id; return ((Mgr*)p)->emoney278; }
static char MgrDeduct1f0(void* p, int id,
                         int64_t v) {
    Mgr* m = (Mgr*)p;
    ++m->nD0; m->idD0 = id; m->vD0 = v;
    return m->deduct1f0; }
static char MgrDeduct1f8(void* p, int id) {
    Mgr* m = (Mgr*)p;
    ++m->nD8; m->idD8 = id;
    return m->deduct1f8; }
static void MgrTouch290(void* p, int id) {
    Mgr* m = (Mgr*)p;
    ++m->nTouch; m->idTouch = id; }
static void MgrAnn40(void* p, int id, void* s,
                     int a) {
    Mgr* m = (Mgr*)p;
    ++m->nAnn; m->idAnn = id; m->sAnn = s;
    m->aAnn = a; }

static int UserRank388(void* p, int id, int* out) {
    (void)id; *out = g_pUser->out388;
    return 1; }
static char UserCross390(void* p) {
    (void)p; return g_pUser->r390; }
static char UserGate360(void* p) {
    (void)p; return g_pUser->gate360; }
static uint64_t UserSend18(void* p, uint32_t id,
                           void* s) {
    UserObj* u = (UserObj*)p;
    ++u->n18; u->id18 = id; u->s18 = s;
    return 1; }
static char g_sFrozen200[0x400];
static uint64_t UserSend200(void* p, void* s) {
    UserObj* u = (UserObj*)p;
    ++u->n200; u->s200 = s;
    // freeze a copy (the stack buffer gets reused)
    snprintf(g_sFrozen200, 0x400, "%s", (char*)s);
    return 1; }
static void UserSend8(void* p, uint32_t id,
                      void* s) {
    UserObj* u = (UserObj*)p;
    ++u->n8; u->id8 = id; u->s8 = s; }
static void UserAward398(void* p, uint32_t id,
                         int a, int b) {
    UserObj* u = (UserObj*)p;
    ++u->n398; u->id398 = id; u->a398 = a;
    u->b398 = b; }
static void UserShow350(void* p, int e, int id,
                        int z) {
    UserObj* u = (UserObj*)p;
    ++u->n350; u->e350 = e; u->id350 = id;
    (void)z; }

// the recordset/field thunks (Insert chain)
static void FieldSetB0(void* p, int64_t v) {
    *(((FieldObj*)p)->pStore) = (int)v; }
static void FieldSetB8(void* p, int64_t v) {
    *(((FieldObj*)p)->pStore) = (int)v; }
static void* RsField(void* p, int idx) {
    return &((Rs*)p)->fld[idx]; }
static char RsExec(void* p, int) {
    ++((Rs*)p)->nExec;
    return ((Rs*)p)->execRet; }
static uint64_t RsRelease(void* p, uint64_t) {
    ++((Rs*)p)->nRel;
    return 0; }
static void* InstQuery20(void*, const char* key) {
    snprintf(g_sLastKey, 64, "%s", key);
    return g_pRs; }

// the fake DB instance (its first qword = the vt)
static void* s_fakeInst[2];
static void* s_instVtStorage[0x80];

static void BindAll() {
    g_fnMeedLog = MockLog;
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubId;
    g_fnMeedSubNType = SubVal;
    g_fnMeedMemSubV =
        +[](void* pM) -> void* {
            return MemSub(pM, 4); };
    g_fnMeedSubVVal =
        +[](void* pS) -> uint32_t {
            return (uint32_t)((uint64_t*)pS)[0]; };
    g_fnMeedReqId = [](void*) -> int { return 777; };
    g_fnMeedStrInst = StrInst;
    g_fnMeedStrGet = StrGet;
    g_fnMeedSnprintf = MockSnprintf;
    g_fnMeedLogSave = MockLogSave;
    g_fnMeedVecInsert = MockVecInsert;
    g_fnTqCMsgInit = [](void*) {};
    // the DB instance: the object at +0 holds the vt
    memset(s_instVtStorage, 0, sizeof s_instVtStorage);
    s_instVtStorage[0x20 / 8] = (void*)InstQuery20;
    s_fakeInst[0] = s_instVtStorage;
    g_fnMeedInstGet = []() -> void* {
        return s_fakeInst; };
}

static void BindRs(Rs* r) {
    memset(r, 0, sizeof *r);
    r->vt = r->vtS.s;
    memset(r->vtS.s, 0, sizeof r->vtS.s);
    for (int i = 0; i < 8; ++i) {
        r->fld[i].vt = r->fld[i].vtS.s;
        memset(r->fld[i].vtS.s, 0,
               sizeof r->fld[i].vtS.s);
        r->fld[i].pStore = &r->store[i];
        r->fld[i].vtS.s[0xb0 / 8] =
            (void*)FieldSetB0;
        r->fld[i].vtS.s[0xb8 / 8] =
            (void*)FieldSetB8;
    }
    r->execRet = 1;
    r->vtS.s[0x10 / 8] = (void*)RsField;
    r->vtS.s[0x50 / 8] = (void*)RsExec;
    r->vtS.s[0x0] = (void*)RsRelease;
    g_pRs = r;
}

static void BindMgr(Mgr* m) {
    memset(m, 0, sizeof *m);
    m->vt = m->vtS.s;
    memset(m->vtS.s, 0, sizeof m->vtS.s);
    m->gate78 = true; m->deduct1f0 = 1;
    m->deduct1f8 = 1;
    m->money268 = 5000000; m->emoney278 = 5000;
    m->vtS.s[0x78 / 8] = (void*)MgrGate78;
    m->vtS.s[0x268 / 8] = (void*)MgrMoney268;
    m->vtS.s[0x278 / 8] = (void*)MgrEmoney278;
    m->vtS.s[0x1f0 / 8] = (void*)MgrDeduct1f0;
    m->vtS.s[0x1f8 / 8] = (void*)MgrDeduct1f8;
    m->vtS.s[0x290 / 8] = (void*)MgrTouch290;
    m->vtS.s[0x40 / 8] = (void*)MgrAnn40;
    g_pMgr = m;
    g_pLeagueDatInstance = m;
}

static void BindUser(UserObj* u) {
    memset(u, 0, sizeof *u);
    u->vt = u->vtS.s;
    memset(u->vtS.s, 0, sizeof u->vtS.s);
    u->out388 = 0; u->r390 = 0; u->gate360 = 0;
    u->vtS.s[0x388 / 8] = (void*)UserRank388;
    u->vtS.s[0x390 / 8] = (void*)UserCross390;
    u->vtS.s[0x360 / 8] = (void*)UserGate360;
    u->vtS.s[0x18 / 8] = (void*)UserSend18;
    u->vtS.s[200 / 8] = (void*)UserSend200;
    u->vtS.s[0x8 / 8] = (void*)UserSend8;
    u->vtS.s[0x398 / 8] = (void*)UserAward398;
    u->vtS.s[0x350 / 8] = (void*)UserShow350;
    g_pUser = u;
}

// ---- the static field/member thunks ----
static int FldGet48(void* p) {
    return *(((FieldObj*)p)->pStore); }
static uint64_t FldGet58(void* p) {
    return (uint64_t)
        *(((FieldObj*)p)->pStore); }

// the pool-member mock (satisfies BOTH the sub
// seams AND the vt field access)
struct PMem {
    void* vt; SVt vtS;
    FieldObj f3, f4;
    int m3, m4;
    uint32_t id;
};
static void* PMemField10(void* p, int64_t n) {
    PMem* m = (PMem*)p;
    return (n == 3)
        ? (void*)&m->f3 : (void*)&m->f4; }
static void PMemSave38(void*, int64_t) {}

// a pool with the REAL ctor (as in the D52 test)
static char* MakePool() {
    char* pool = (char*)calloc(1, 0xd0);
    MeedPoolCtorReal(pool);
    return pool;
}
// wire a vector with the given elems (self-proxy)
static void WireVec(char* pool, int nType,
                    void** cells, int n) {
    char* v = pool + (nType - 1) * 0x30;
    *(void**)(v + 0x18) = cells;
    *(void**)(v + 0x20) = cells + n;
    *(void**)(v + 0x28) = cells + n;
    *(void**)v = v;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    BindAll();

    // ---- D53-1: MeedApplyBounds (14177caa0) ----
    {
        g_nMeedMoneyCap = 1000;
        assert(MeedApplyBounds(500, 500) == 1);
        assert(MeedApplyBounds(0, 0) == 0);
        assert(MeedApplyBounds(1000, 0) == 0
            && "cap: n < cap strict");
        assert(MeedApplyBounds(1000, 1000) == 0);
        assert(MeedApplyBounds(-1, 50) == 0);
        assert(MeedApplyBounds(50, -1) == 0);
        assert(MeedApplyBounds(0, 50) == 1);
        assert(MeedApplyBounds(999, 999) == 1);
        printf("D53-1 bounds ok\n");
    }

    // ---- D53-2: MeedSortFlagGet (14177cb90) ----
    {
        char pool[0xd0]; memset(pool, 0, 0xd0);
        assert(MeedSortFlagGet(pool, 1)
            == (uint8_t*)(pool + 0x90));
        assert(MeedSortFlagGet(pool, 2)
            == (uint8_t*)(pool + 0x91));
        assert(MeedSortFlagGet(pool, 3)
            == (uint8_t*)(pool + 0x92));
        g_nLog = 0;
        assert(MeedSortFlagGet(pool, 9)
            == (uint8_t*)(pool + 200)
            && g_nLog == 1
            && "the dead +0xc8 (200 decimal) path");
        printf("D53-2 sortflag ok\n");
    }

    // ---- D53-3: MeedEmonyType (14177ff70) ----
    {
        // type 1
        assert(MeedEmonyType(nullptr, 1, 0) == 0x1a);
        assert(MeedEmonyType(nullptr, 1, 1) == 0x1b);
        assert(MeedEmonyType(nullptr, 1, 2) == 0x1c);
        assert(MeedEmonyType(nullptr, 1, 3) == 0x1d);
        assert(MeedEmonyType(nullptr, 1, 4) == 0x29);
        // type 2
        assert(MeedEmonyType(nullptr, 2, 0) == 0x15);
        assert(MeedEmonyType(nullptr, 2, 1) == 0x16);
        assert(MeedEmonyType(nullptr, 2, 2) == 0x17);
        assert(MeedEmonyType(nullptr, 2, 3) == 0x18);
        g_nLog = 0;
        assert(MeedEmonyType(nullptr, 2, 4) == 0
            && g_nLog == 1
            && "type 2 + mt 4 -> the log path");
        // type 3
        assert(MeedEmonyType(nullptr, 3, 0) == 0x25);
        assert(MeedEmonyType(nullptr, 3, 1) == 0x26);
        assert(MeedEmonyType(nullptr, 3, 2) == 0x27);
        assert(MeedEmonyType(nullptr, 3, 3) == 0x28);
        assert(MeedEmonyType(nullptr, 3, 4) == 0x2a);
        // bad gates
        g_nLog = 0;
        assert(MeedEmonyType(nullptr, 9, 0) == 0
            && g_nLog == 1);
        g_nLog = 0;
        assert(MeedEmonyType(nullptr, 1, 5) == 0
            && g_nLog == 1
            && "mt >= 5 -> the log path");
        printf("D53-3 emonytype ok\n");
    }

    // ---- D53-4: MeedGmLogName (14177fad0) ----
    {
        assert(strcmp(MeedGmLogName(1, 1),
            "gmlog/money_vlmarenic") == 0);
        assert(strcmp(MeedGmLogName(1, 2),
            "gmlog/vlm_meed_award") == 0);
        assert(strcmp(MeedGmLogName(1, 3),
            "gmlog/vlm_meed_overflow") == 0);
        assert(strcmp(MeedGmLogName(2, 1),
            "gmlog/money_synarenic") == 0);
        assert(strcmp(MeedGmLogName(2, 2),
            "gmlog/syn_meed_award") == 0);
        assert(strcmp(MeedGmLogName(2, 3),
            "gmlog/syn_meed_overflow") == 0);
        assert(strcmp(MeedGmLogName(3, 1),
            "gmlog/cross_money_vlmarenic") == 0);
        assert(strcmp(MeedGmLogName(3, 2),
            "gmlog/cross_vlm_meed_award") == 0);
        assert(strcmp(MeedGmLogName(3, 3),
            "gmlog/cross_vlm_meed_overflow") == 0);
        g_nLog = 0;
        assert(strcmp(MeedGmLogName(9, 1),
            "gmlog/meed_error") == 0
            && g_nLog == 1);
        assert(strcmp(MeedGmLogName(1, 4),
            "gmlog/meed_error") == 0);
        printf("D53-4 gmlog names ok\n");
    }

    // ---- D53-5: CMsgAwardRankEncode (1417da0d0) --
    {
        static char buf[0x30];
        memset(buf, 0, sizeof buf);
        static void* msg[0x86];
        memset(msg, 0, sizeof msg);
        *(void**)((char*)msg + 0x408) = buf;
        static int nInit = 0;
        nInit = 0;
        g_fnTqCMsgInit =
            +[](void*) { ++nInit; };
        uint64_t r = CMsgAwardRankEncode(
            msg, 0x1234, 2, 3000000ULL, 0xABCD);
        assert(r == 1 && nInit == 1);
        assert(*(uint16_t*)(buf + 0) == 0x20);
        assert(*(uint16_t*)(buf + 2) == 0x427);
        assert(*(uint16_t*)(buf + 4) == 0x1234);
        assert(*(uint32_t*)(buf + 6) == 2);
        assert(*(uint32_t*)(buf + 0xe) == 0);
        assert(*(uint32_t*)(buf + 0x12) == 0xABCD);
        assert(*(uint64_t*)(buf + 0x16) == 3000000ULL);
        printf("D53-5 encode ok\n");
    }

    // ---- D53-6: MeedPromptGet (14177fbc0) ----
    {
        UserObj u; BindUser(&u);
        static void* proxy6[1];
        proxy6[0] = &u;
        // the vt+0x360 gate
        u.gate360 = 1;
        assert(strcmp(MeedPromptGet(proxy6, 1, 1),
            "S(STR_VLM_ARENIC_MEED1_1)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 1, 2),
            "S(STR_VLM_ARENIC_MEED2_1)") == 0);
        u.gate360 = 0;
        assert(strcmp(MeedPromptGet(proxy6, 1, 1),
            "S(STR_VLM_ARENIC_MEED1_2)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 1, 2),
            "S(STR_VLM_ARENIC_MEED2_2)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 1, 3),
            "S(STR_VLM_ARENIC_DISTRIBUTEMEED1)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 1, 4),
            "S(STR_VLM_ARENIC_DISTRIBUTEMEED2)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 1, 5),
            "S(STR_VLM_ARENIC_OVER)") == 0);
        // type 2
        assert(strcmp(MeedPromptGet(proxy6, 2, 1),
            "S(STR_SYN_ARENIC_MEED1)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 2, 2),
            "S(STR_SYN_ARENIC_MEED2)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 2, 3),
            "S(STR_SYN_ARENIC_DISTRIBUTEMEED1)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 2, 4),
            "S(STR_SYN_ARENIC_DISTRIBUTEMEED2)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 2, 5),
            "S(STR_SYN_ARENIC_OVER)") == 0);
        assert(MeedPromptGet(proxy6, 2, 6) == nullptr
            && "type 2 has no case 6");
        // type 3
        assert(strcmp(MeedPromptGet(proxy6, 3, 1),
            "S(STR_CROSS_VLM_ARENIC_MEED1)") == 0);
        assert(strcmp(MeedPromptGet(proxy6, 3, 6),
            "S(STR_CROSS_VLM_ARENIC_FIRST)") == 0);
        printf("D53-6 prompts ok\n");
    }

    // ---- D53-7: MeedVecPush (141732200) ----
    {
        static void* cells[4];
        memset(cells, 0, sizeof cells);
        // the MSVC-debug vector: proxy@0, begin@0x18,
        // end@0x20, cap@0x28
        char vec[0x30]; memset(vec, 0, sizeof vec);
        *(void**)(vec + 0x18) = cells;
        *(void**)(vec + 0x20) = cells;
        *(void**)(vec + 0x28) = cells + 4;
        *(void**)vec = vec;
        static void* val = (void*)0x1234;
        MeedVecPush(vec, &val);
        assert(cells[0] == (void*)0x1234
            && *(void**)(vec + 0x20) == cells + 1);
        // fill to capacity -> the grow seam
        g_nVecInsert = 0;
        *(void**)(vec + 0x20) = cells + 4;
        *(void**)(vec + 0x28) = cells + 4;
        MeedVecPush(vec, &val);
        assert(g_nVecInsert == 1);
        printf("D53-7 vecpush ok\n");
    }

    // ---- D53-8: MeedSetMgrAddMore (14177cbd0) ----
    {
        // the member mock with vt+0x10 field access
        static struct MemM {
            void* vt; SVt vtS;
            FieldObj f3, f4;
            int m3, m4;
            int nSave; uint64_t saveA;
        } s_mm;
        memset(&s_mm, 0, sizeof s_mm);
        s_mm.vt = s_mm.vtS.s;
        static void* (*memField)(void*, int64_t) =
            +[](void* p, int64_t n) -> void* {
                MemM* m = (MemM*)p;
                return (n == 3)
                    ? (void*)&m->f3 : (void*)&m->f4; };
        // RAW 14177cbd0: cVar1 = (vt+0x38)(member, 0)
        // is a REAL return value read as char — the void
        // mock used to depend on leftover AL garbage
        static char (*memSave)(void*, int64_t) =
            +[](void* p, int64_t a) -> char {
                ((MemM*)p)->nSave++;
                ((MemM*)p)->saveA =
                    (uint64_t)a;
                return 1; };
        s_mm.vtS.s[0x10 / 8] = (void*)memField;
        s_mm.vtS.s[0x38 / 8] = (void*)memSave;
        // the fields: get@0x48, set@0xb0
        for (int i = 0; i < 2; ++i) {
            FieldObj* f = i ? &s_mm.f4 : &s_mm.f3;
            f->vt = f->vtS.s;
            memset(f->vtS.s, 0, sizeof f->vtS.s);
            f->pStore = i ? &s_mm.m4 : &s_mm.m3;
            f->vtS.s[0x48 / 8] =
                (void*)+[](void* p) -> int {
                    return *(((FieldObj*)p)
                        ->pStore); };
            f->vtS.s[0xb0 / 8] =
                (void*)FieldSetB0;
        }
        s_mm.m3 = 1000000; s_mm.m4 = 500;
        char pool[0xd0]; memset(pool, 0, 0xd0);
        g_nMeedMoneyCap = 2000000000;
        int entry[3] = { 777, 5000000, 1000 };
        bool r = MeedSetMgrAddMore(
            pool, &s_mm, entry, 1);
        assert(r && s_mm.m3 == 6000000
            && s_mm.m4 == 1500 && s_mm.nSave == 1
            && s_mm.saveA == 0
            && "sum + the vt+0x38(row,0) save");
        assert(pool[0x90] == 0
            && "the +0x90 flag cleared");
        // the bounds fail (over the cap)
        g_nMeedMoneyCap = 6000000;
        r = MeedSetMgrAddMore(pool, &s_mm, entry, 1);
        assert(!r && "cap violation -> false");
        g_nMeedMoneyCap = 2000000000;
        // the both-zero sum
        s_mm.m3 = 0; s_mm.m4 = 0;
        int entry0[3] = { 777, 0, 0 };
        r = MeedSetMgrAddMore(pool, &s_mm, entry0, 1);
        assert(!r && "both sums < 1 -> false");
        // the null member + the bad type
        g_nLog = 0;
        r = MeedSetMgrAddMore(pool, nullptr, entry, 1);
        assert(!r && g_nLog == 1);
        g_nLog = 0;
        r = MeedSetMgrAddMore(pool, &s_mm, entry, 9);
        assert(!r && g_nLog == 1);
        printf("D53-8 addmore ok\n");
    }

    // ---- D53-9: MeedSetMgrInsert (14177d5f0) ----
    {
        static Rs rs; BindRs(&rs);
        char* pool = MakePool();
        static void* cells[8];
        memset(cells, 0, sizeof cells);
        WireVec(pool, 1, cells, 0);
        // spare capacity: end=cells, cap=cells+8
        *(void**)(pool + 0x20) = cells;
        *(void**)(pool + 0x28) = cells + 8;
        g_nMeedMoneyCap = 2000000000;
        int entry[3] = { 777, 3000000, 100 };
        uint8_t r = MeedSetMgrInsert(
            pool, entry, 1);
        assert(r == 1);
        assert(strcmp(g_sLastKey, "cq_setmeed") == 0);
        assert(rs.store[1] == 1   // field1 b0 = type
            && rs.store[2] == 777 // field2 b8 = id
            && rs.store[3] == 3000000
            && rs.store[4] == 100);
        assert(rs.nExec == 1);
        assert(cells[0] == (void*)&rs
            && "the rs pushed into the vector");
        assert(*(void**)(pool + 0x20) == cells + 1);
        assert(pool[0x90] == 0
            && "the +0x90 flag cleared");
        // exec fail -> the raw 0 return (the
        // ORIGINAL has no release here — verbatim)
        static Rs rs2; BindRs(&rs2);
        rs2.execRet = 0;
        static void* cells2[8];
        WireVec(pool, 1, cells2, 0);
        *(void**)(pool + 0x20) = cells2;
        *(void**)(pool + 0x28) = cells2 + 8;
        r = MeedSetMgrInsert(pool, entry, 1);
        assert(r == 0 && rs2.nRel == 0
            && cells2[0] == (void*)&rs2
            && "exec fail: pushed anyway, no release");
        // the bounds gate
        int entryBad[3] = { 777, 0, 0 };
        r = MeedSetMgrInsert(pool, entryBad, 1);
        assert(r == 0 && "both < 1 -> 0");
        // the bad type
        g_nLog = 0;
        r = MeedSetMgrInsert(pool, entry, 9);
        assert(r == 0 && g_nLog == 1);
        free(pool);
        printf("D53-9 insert ok\n");
    }

    // ---- D53-10: MeedSetMgrSetSynMeed (14177db90) --
    {
        static Rs rs; BindRs(&rs);
        char* pool = MakePool();
        static void* cells[8];
        memset(cells, 0, sizeof cells);
        WireVec(pool, 1, cells, 0);
        *(void**)(pool + 0x20) = cells;
        *(void**)(pool + 0x28) = cells + 8;
        g_nMeedMoneyCap = 2000000000;
        int entry[3] = { 777, 5000000, 100 };
        uint8_t out = 0;
        // empty vector -> *out=1 + the insert path
        uint64_t r = MeedSetMgrSetSynMeed(
            pool, entry, 1, &out);
        assert((r & 0xff) == 1 && out == 1
            && "empty: the flag + Insert");
        assert(cells[0] == (void*)&rs);
        // the entry gate
        int entryZ[3] = { 1, 0, 0 };
        g_nLog = 0;
        r = MeedSetMgrSetSynMeed(pool, entryZ, 1,
                                 &out);
        assert((r & 0xff) == 0 && g_nLog == 1);
        // the bad type
        g_nLog = 0;
        r = MeedSetMgrSetSynMeed(pool, entry, 9,
                                 &out);
        assert((r & 0xff) == 0 && g_nLog == 1);
        free(pool);
        printf("D53-10 setsynmeed (insert) ok\n");
    }

    // ---- D53-11: MeedSetArenic E2E (141780cb0) ----
    {
        static Mgr mgr; BindMgr(&mgr);
        static UserObj u; BindUser(&u);
        static void* uProxy[1];
        uProxy[0] = &u;
        static Rs rs; BindRs(&rs);
        g_pMeedPool = nullptr;
        char* pool = MakePool();
        g_pMeedPool = pool;
        static void* cells[8];
        memset(cells, 0, sizeof cells);
        WireVec(pool, 1, cells, 0);
        *(void**)(pool + 0x20) = cells;
        *(void**)(pool + 0x28) = cells + 8;
        g_nMeedMoneyCap = 2000000000;

        // -- the type gate --
        g_nLog = 0;
        assert((MeedSetArenic(uProxy, 1001, 9,
                              3000000, 0, 1)
                & 0xff) == 0
            && g_nLog == 1);
        // -- the vt+0x78 gate --
        mgr.gate78 = false;
        assert((MeedSetArenic(uProxy, 1001, 1,
                              3000000, 0, 1)
                & 0xff) == 0);
        mgr.gate78 = true;
        // -- the type-3 ERROR1 path --
        u.out388 = 1;
        uint64_t r = MeedSetArenic(uProxy, 1001, 3,
                                   3000000, 0, 1);
        assert((r & 0xff) == 0 && u.n18 == 1
            && u.id18 == 1001
            && strcmp((char*)u.s18,
                      "F(S(STR_VLM_ARENIC_MEED_ERROR1))")
                == 0);
        u.out388 = 0;
        // -- the money shortfall --
        mgr.money268 = 1000000;
        r = MeedSetArenic(uProxy, 1001, 1, 3000000, 0,
                         1);
        assert((r & 0xff) == 0);
        mgr.money268 = 5000000;
        // -- the emoney shortfall --
        mgr.emoney278 = 50;
        r = MeedSetArenic(uProxy, 1001, 1, 3000000,
                         100, 1);
        assert((r & 0xff) == 0);
        mgr.emoney278 = 5000;
        // -- the FRESH donate path (the full E2E) --
        r = MeedSetArenic(uProxy, 1001, 1, 3000000, 0,
                         0x1234);
        assert((r & 0xff) == 1
            && "the fresh donate: AL = 1");
        // the deduct (money only, emoney = 0)
        assert(mgr.nD0 == 1 && mgr.idD0 == 777
            && mgr.vD0 == -3000000);
        assert(mgr.nD8 == 0
            && "the || short-circuit: vt+0x1f8 "
               "skipped when vt+0x1f0 succeeded");
        // the insert happened
        assert(cells[0] == (void*)&rs
            && rs.store[2] == 777);
        // the flag family fired
        assert(mgr.nTouch == 1
            && mgr.idTouch == 777);
        assert(u.n200 == 1
            && strcmp(g_sFrozen200,
                      "F(S(STR_VLM_ARENIC_FIRST))") == 0);
        // the gmlog (fresh fmt) + the announce
        assert(strcmp(g_szLogSaveFile,
                      "gmlog/money_vlmarenic") == 0);
        assert(g_uLogSaveId == 1001);
        assert(mgr.nAnn == 1 && mgr.idAnn == 777
            && mgr.aAnn == 0);
        // the final 0x427 msg sent to the USER id
        assert(u.n8 == 1 && u.id8 == 1001
            && u.s8 != nullptr);
        assert(u.n398 == 0
            && "type 1 -> no vt+0x398");
        printf("D53-11 arenic fresh E2E ok\n");

        // -- the EXISTING member path (AddMore) --
        static Rs rsX; BindRs(&rsX);
        g_pMeedPool = nullptr;
        char* pool2 = MakePool();
        g_pMeedPool = pool2;
        static void* cells2[8];
        memset(cells2, 0, sizeof cells2);
        // the pool member: {id=777, money=1M,
        // emoney=200}
        static PMem pm;
        memset(&pm, 0, sizeof pm);
        pm.id = 777; pm.m3 = 1000000; pm.m4 = 200;
        pm.vt = pm.vtS.s;
        memset(pm.vtS.s, 0, sizeof pm.vtS.s);
        pm.vtS.s[0x10 / 8] = (void*)PMemField10;
        pm.vtS.s[0x38 / 8] = (void*)PMemSave38;
        for (int i = 0; i < 2; ++i) {
            FieldObj* f = i ? &pm.f4 : &pm.f3;
            f->vt = f->vtS.s;
            memset(f->vtS.s, 0, sizeof f->vtS.s);
            f->pStore = i ? &pm.m4 : &pm.m3;
            f->vtS.s[0x48 / 8] =
                (void*)FldGet48;
            f->vtS.s[0xb0 / 8] = (void*)FieldSetB0;
            f->vtS.s[0x58 / 8] =
                (void*)FldGet58;
        }
        // the sub seams for the PMem layout
        g_fnMeedMemSub =
            +[](void* pM, int n) -> void* {
                PMem* m = (PMem*)pM;
                if (n == 3) return &m->m3;
                if (n == 4) return &m->m4;
                return &m->id; };
        cells2[0] = &pm;
        WireVec(pool2, 1, cells2, 1);
        mgr.nAnn = mgr.nTouch = mgr.nD0 = 0;
        u.n8 = u.n200 = 0;
        r = MeedSetArenic(uProxy, 1001, 1, 3000000, 0,
                         0x5678);
        assert((r & 0xff) == 1);
        assert(pm.m3 == 4000000
            && "AddMore summed the money");
        assert(mgr.nD0 == 1
            && mgr.vD0 == -3000000);
        // VERBATIM: the top elem IS the user ->
        //  *out = 1 unconditionally (the 79345
        //  store) -> the announce + the touch
        assert(mgr.nTouch == 1
            && mgr.idTouch == 777
            && "the user IS the top -> the "
               "announce fires");
        // the type-3 emoney display family
        g_pMeedPool = nullptr;
        char* pool3 = MakePool();
        g_pMeedPool = pool3;
        static void* cells3[8];
        memset(cells3, 0, sizeof cells3);
        WireVec(pool3, 3, cells3, 0);
        *(void**)(pool3 + 0x20) = cells3;
        *(void**)(pool3 + 0x28) = cells3 + 8;
        static Rs rs3; BindRs(&rs3);
        mgr.nD0 = 0;
        u.n350 = 0;
        r = MeedSetArenic(uProxy, 1001, 3, 3000000,
                         100, 0x9999);
        assert((r & 0xff) == 1);
        assert(u.n350 == 1 && u.e350 == 0x25
            && "the emony type 3/0 = 0x25 shown");
        assert(u.n398 == 1 && u.id398 == 777
            && "type 3 -> the vt+0x398 award");
        assert(rs3.store[1] == 3
            && "the type-3 insert");
        free(pool); free(pool2); free(pool3);
        printf("D53-12 arenic existing+type3 ok\n");
    }

    printf("SYNDICATE_D53_OK: the SetArenicMeed flow "
           "+ the apply family\n");
    return 0;
}

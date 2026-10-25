// ============================================================
// Peerage.dll — unit D23: the donation family
// (141551750/60/70/80, 141554c40, 141554b10, 1415558a0,
// 141555dc0, 1415520c0, 141556db0). Mock bodies: the
// raw CPeerageSort-shaped SElem (row at +8 — the layout
// the original reads), the db/kernel/recordset/rows/fields
// seams, and the D20 walk kit (BindCommon/BindD20-style).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include "../Exe/Dll/Peerage/Port/PeerageDonate.h"
#include "../Exe/Dll/Peerage/Port/PeerageModule.h"
#include "../Exe/Dll/Peerage/Port/PeerageSortMgr.h"
#include "../Exe/Dll/Peerage/Port/PeerageSort.h"
#include "../Exe/Dll/Peerage/Port/PeeragePromote.h"
#include "../Exe/Dll/Peerage/Port/PeerageMsgWire.h"

using namespace peerage;
using std::string;
using std::to_string;

// ---- the capture state ----
static std::vector<string> g_vLog;
static std::vector<string> g_vSvc;     // kernel seam log
static std::vector<string> g_vDb;      // db seam log
static std::vector<string> g_vQry;    // query seam log
static std::vector<string> g_vMisc;    // rec/vt38/mylog log
static string g_sLastAppend;
static string g_sLastKey;
static std::vector<void*> g_vElemDelP;   // elem ptrs
static std::vector<void*> g_vRowDel;
static int g_nRelease = 0;
static uint64_t g_uLastPair = 0;

// the elem (raw CPeerageSort-shaped buffer, 0x30):
// row at +8 — the +8-VC-inside-SElem trap the parallel
// environment hit is avoided by mirroring the original
struct SElem {
    void* vft;          // +0x00
    void* row;          // +0x08
    uint32_t rank10;    // +0x10
    uint32_t state14;   // +0x14
    uint32_t key18;     // +0x18
    char ab1c[0x14];    // +0x1c..0x2b (the pair/name)
};
static_assert(sizeof(SElem) == 0x30);
static_assert(offsetof(SElem, ab1c) == 0x1c);

struct MockRow { uint32_t id; int64_t value; };
// the shared query object (MockRow-shaped: it becomes
// the created elem's row — see BindD23)
static MockRow s_qobj{77, 42};

static void BindCommon() {
    g_fnSortLogError = []() {
        g_vLog.push_back("log"); };
    g_fnInvalidParameter = []() {
        fprintf(stderr, "INVALID\n"); abort(); };
    g_fnProxyAlloc = [](size_t n) {
        return malloc(n); };
    g_fnProxyDelete = [](void* p) { free(p); };
    g_fnVecAlloc = [](size_t n) {
        return malloc(n); };
    g_fnVecDelete = [](void* p) { free(p); };
    g_fnSortAlloc = [](size_t n) {
        return malloc(n); };
    g_fnRowQuery = [](void* pRow, int n) {
        (void)n; return pRow; };
    g_fnRowGetInt = [](void* pRec) {
        return (int)((MockRow*)pRec)->id; };
    g_fnRowQuery2 = [](void* pRow, int n) {
        (void)n; return pRow; };
    g_fnRowGetValue = [](void* pRec) {
        return ((MockRow*)pRec)->value; };
    g_fnRowGetId = [](void* pRec) {
        return ((MockRow*)pRec)->id; };
    g_fnSortLogError2 = []() {};
    g_fnInvalidParameter2 = []() { abort(); };
    g_fnPackerCtor = [](void*) {};
    g_fnPackerDtor = [](void*) {};
    g_fnPackerSetBuf = [](void*, char*, uint32_t,
                          bool) {};
}

static void BindD20Kit() {
    g_fnBuildArg4 = []() { return 7; };
    g_fnBuild1Arg4 = []() -> uint64_t {
        return 555; };
    g_fnMsgAppend = [](void* p, char* s) {
        (void)p; g_sLastAppend = s;
        return true; };
    g_fnDbSendRank = [](void* db, uint32_t id,
                        void* msg) {
        (void)db; (void)msg;
        g_vDb.push_back("sendRank:" +
                        to_string(id)); };
    g_fnDbAnnounce = [](void* db, const char* buf,
                        uint32_t color,
                        uint16_t type) {
        (void)db;
        g_vDb.push_back("announce:" + string(buf)
                        + ":" + to_string(color)
                        + ":" + to_string(type)); };
    g_fnDbSendAnnounce = [](void* db, uint32_t id,
                            void* msg) {
        (void)db; (void)msg;
        g_vDb.push_back("sendAnn:" +
                        to_string(id)); };
    g_fnDbGetGender = [](void* db, uint32_t id) {
        (void)db; (void)id; return 1; };
    g_fnDbTouch = [](void* db, uint32_t id) {
        (void)db;
        g_vDb.push_back("touch:" +
                        to_string(id)); };
    g_fnDbAnnounceEnabled = [](void* db) {
        (void)db; return true; };
    g_fnTheInstance = []() { return (void*)0x99; };
    g_fnStrMgrGet = [](void* p, const char* key) {
        (void)p; g_sLastKey = key;
        return "PROMPT"; };
    g_fnRowVt40Release = [](void*, int, void*,
                            void*, int64_t) {
        ++g_nRelease; };
    g_fnRowDelete = [](void* p, uint64_t) {
        g_vRowDel.push_back(p); };
    g_fnElemDelete = [](void* p, uint64_t) {
        // NOTE: the ORIGINAL 141552110 cleanup zeroes
        // elem+8 before the deleting dtor runs, so the
        // row is gone by now — capture the elem ptr
        g_vElemDelP.push_back(p); };
}

// the D23 db/kernel seams (static values the sections
// override per case)
static int g_nLevel = 70;
static int g_nTypeGate = 1;
static int g_nChargeRet = 1;
static int64_t g_nDonated = 5000000;
static const char* g_sPairName = "BBB";
static uint32_t g_nUnderline = 42;
static int g_nQryExec = 1;

static void BindD23() {
    g_fnSvcGetLevel = [](void* k, uint32_t id) {
        (void)k;
        g_vSvc.push_back("level:" + to_string(id));
        return (uint32_t)g_nLevel; };
    g_fnSvcTypeGate = [](void* k, uint32_t id) {
        (void)k;
        g_vSvc.push_back("gate:" + to_string(id));
        return (char)g_nTypeGate; };
    g_fnSvcCharge10 = [](void* k, uint32_t id,
                         int64_t m) {
        (void)k;
        g_vSvc.push_back("c10:" + to_string(id)
                         + ":" + to_string(m));
        return (char)g_nChargeRet; };
    g_fnSvcCharge18 = [](void* k, uint32_t id,
                         int64_t m) {
        (void)k;
        g_vSvc.push_back("c18:" + to_string(id)
                         + ":" + to_string(m));
        return (char)g_nChargeRet; };
    g_fnSvcCharge20 = [](void* k, uint32_t id,
                         int64_t m) {
        (void)k;
        g_vSvc.push_back("c20:" + to_string(id)
                         + ":" + to_string(m));
        return (char)g_nChargeRet; };
    g_fnSvcSendStr = [](void* k, uint32_t id,
                        const char* s,
                        uint32_t color,
                        uint32_t chan) {
        (void)k;
        g_vSvc.push_back("str:" + string(s) + ":"
                         + to_string(color) + ":"
                         + to_string(chan)); };
    g_fnSvcSend88 = [](void* k, uint32_t id,
                       uint32_t a3) {
        (void)k;
        g_vSvc.push_back("vt88:" + to_string(id)
                         + ":" + to_string(a3)); };
    g_fnDbGetNamePair = [](void* db, uint32_t id) {
        (void)db;
        static char buf[16];
        memset(buf, 0, sizeof buf);
        strncpy(buf, g_sPairName, 15);
        g_vDb.push_back("pair:" + to_string(id));
        return (void*)buf; };
    g_fnDbGetDonated = [](void* db, uint32_t id) {
        (void)db;
        g_vDb.push_back("get:" + to_string(id));
        return g_nDonated; };
    g_fnDbSetDonated = [](void* db, uint32_t id,
                          int64_t t) {
        (void)db;
        g_vDb.push_back("set:" + to_string(id)
                        + ":" + to_string(t)); };
    g_fnDbGetUnderline = [](void* db,
                            uint32_t id) {
        (void)db; (void)id;
        return g_nUnderline; };
    g_fnRecSetTotalA0 = [](void* r, int64_t t) {
        g_vMisc.push_back("recSet:" + to_string(t)); };
    g_fnRecGetTotalA0 = [](void* r) {
        g_vMisc.push_back("recGet");
        (void)r; return (int64_t)0; };
    g_fnRowVt38 = [](void* row, int n) {
        g_vMisc.push_back("vt38:" + to_string(n)); };
    // the query object doubles as the created elem's
    // row (141555dc0 passes it to 141552340), so it
    // must be MockRow-shaped for FindSortById
    g_fnInstanceGet = []() {
        g_vQry.push_back("inst");
        return (void*)&s_qobj; };
    g_fnQryGetTab = [](void* o, const char* t) {
        g_vQry.push_back(string("tab:") + t);
        (void)o; return (void*)&s_qobj; };
    g_fnQryField = [](void* q, int n) {
        g_vQry.push_back("field:" + to_string(n));
        (void)q; return (void*)(size_t)(0x100 + n); };
    g_fnFieldSetB8 = [](void* f, int64_t v) {
        g_vQry.push_back(
            "b8:" + to_string((size_t)f) + ":"
            + to_string(v)); };
    g_fnFieldSetB0 = [](void* f, int64_t v) {
        g_vQry.push_back(
            "b0:" + to_string((size_t)f) + ":"
            + to_string(v)); };
    g_fnQryExec = [](void* q, int n) {
        (void)q;
        g_vQry.push_back("exec:" + to_string(n));
        return g_nQryExec != 0; };
    g_fnQryDestroy = [](void* q, uint64_t f) {
        (void)q; (void)f;
        g_vQry.push_back("destroy"); };
    g_fnMyLogSave = [](const char* file,
                       const char* fmt, uint32_t id,
                       int64_t m, int t) {
        (void)fmt;
        g_vMisc.push_back(string("mylog:")
                          + file + ":"
                          + to_string(id) + ":"
                          + to_string(m) + ":"
                          + to_string(t)); };
}

static void Reset() {
    g_vLog.clear(); g_vSvc.clear(); g_vDb.clear();
    g_vQry.clear(); g_vMisc.clear();
    g_vElemDelP.clear(); g_vRowDel.clear();
    g_nRelease = 0;
    g_sLastAppend.clear(); g_sLastKey.clear();
    g_nLevel = 70; g_nTypeGate = 1;
    g_nChargeRet = 1; g_nDonated = 5000000;
    g_sPairName = "BBB"; g_nUnderline = 42;
    g_nQryExec = 1;
}

int main() {
    setbuf(stdout, nullptr);
    BindCommon();
    BindD20Kit();
    BindD23();

    // ---- 1. SetNamePair (FUN_1415520c0) ----
    {
        Reset();
        SetNamePair((CPeerageSort*)0, nullptr);
        assert(g_vLog.size() == 1);   // null -> log
        SElem e; memset(&e, 0, sizeof e);
        uint64_t pair[2] = {0x4443424142, 0x484746};
        SetNamePair((CPeerageSort*)&e, pair);
        assert(*(uint64_t*)((char*)&e + 0x1c)
               == pair[0]);
        assert(*(uint64_t*)((char*)&e + 0x24)
               == pair[1]);
        assert(*(uint8_t*)((char*)&e + 0x2b) == 0);
        printf("D23-1 name pair ok\n");
    }

    // ---- 2. GetPeerageRank (FUN_141554c40) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        MockRow row{77, 5};
        SElem e; memset(&e, 0, sizeof e);
        e.row = &row; e.rank10 = 2;
        void* p = &e; VecPushBack(&mgr, &p);
        // the elem hit: elem+0x10
        assert(GetPeerageRank(&mgr, 77) == 2);
        // the db-total thresholds
        g_nDonated = 25000000;
        assert(GetPeerageRank(&mgr, 99) == 0);
        g_nDonated = 30000000;
        assert(GetPeerageRank(&mgr, 99) == 1);
        g_nDonated = 199999999;
        assert(GetPeerageRank(&mgr, 99) == 3);
        g_nDonated = 200000000;
        assert(GetPeerageRank(&mgr, 99) == 5);
        printf("D23-2 rank ok\n");
    }

    // ---- 3. the service wrappers (141551750/60/70) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        CPeerageService svc; memset(&svc, 0,
                                    sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        // rank passthrough (id 88: no elem -> the db
        // threshold path)
        g_nDonated = 30000000;
        ServiceGetRank(&svc, 88);
        assert(g_vDb.back() == "get:88");
        // send-state passthrough
        g_vDb.clear();
        ServiceSendState(&svc, 88);
        assert(g_vDb.size() == 2);
        assert(g_vDb[0] == "get:88");
        assert(g_vDb[1] == "sendRank:88");
        assert(g_sLastAppend ==
            "1 30000000 4294967295 7");
        // sweep passthrough: an elem that matches
        g_vDb.clear(); g_vElemDelP.clear();
        g_vRowDel.clear();
        MockRow row{31, 1};
        SElem e; memset(&e, 0, sizeof e);
        e.vft = (void*)1; e.row = &row;
        void* p = &e; VecPushBack(&mgr, &p);
        size_t nBefore =
            (mgr.m_vec.m_ppEnd
             - mgr.m_vec.m_ppBegin);
        ServiceSweepDelete(&svc, 31,
                           (char*)0x1234,
                           (char*)0x5678);
        assert(g_nRelease == 1);   // the cleanup
        assert(g_vElemDelP.size() == 1
            && g_vElemDelP[0] == &e);
        assert((mgr.m_vec.m_ppEnd
                - mgr.m_vec.m_ppBegin)
               == nBefore - 1);
        printf("D23-3 wrappers ok\n");
    }

    // ---- 4. ServiceDonate gates (FUN_141551780) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        CPeerageService svc; memset(&svc, 0,
                                    sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        // level gate: 69 < 0x46 (70) — the resolved
        // prompt (PROMPT) is sent, the KEY is the
        // lookup: color 0xff0000 = 16711680,
        // channel 0x7d5 = 2005
        g_nLevel = 69;
        ServiceDonate(&svc, 5, 3000000LL, 0);
        assert(g_vSvc.size() == 2);
        assert(g_vSvc[0] == "level:5");
        assert(g_vSvc[1] ==
            "str:PROMPT:16711680:2005");
        assert(g_sLastKey ==
            "STR_PEERAGE_DONATE_ERR_BELOW_LEVEL");
        // the underline gate
        Reset(); g_nLevel = 70;
        ServiceDonate(&svc, 5, 2999999LL, 0);
        assert(g_vSvc.size() == 2);
        assert(g_vSvc[1] ==
            "str:PROMPT:16711680:2005");
        assert(g_sLastKey ==
            "STR_PEERAGE_DONATE_ERR_BELOW_"
            "UNDERLINE");
        // the overflow gate
        Reset(); g_nLevel = 70;
        ServiceDonate(&svc, 5, 1000000000LL, 0);
        assert(g_vSvc.size() == 2);
        assert(g_vSvc[1] ==
            "str:PROMPT:16711680:2005");
        assert(g_sLastKey ==
            "STR_PEERAGE_DONATE_OVERFLOW");
        printf("D23-4 donate gates ok\n");
    }

    // ---- 5. ServiceDonate money types ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        CPeerageService svc; memset(&svc, 0,
                                    sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        mgr.m_uSpare38 = 10000000000LL;
        mgr.m_nRankNum48 = 0;
        // type 0: vt+0x10 with the full money (the
        // level probe runs first, always)
        Reset();
        ServiceDonate(&svc, 5, 3000000LL, 0);
        assert(g_vSvc.size() == 2);
        assert(g_vSvc[0] == "level:5");
        assert(g_vSvc[1] == "c10:5:3000000");
        // DonateCore ran (the set is a db seam) + the
        // normal-path type-1 send
        assert(g_vDb.size() == 3);
        assert(g_vDb[0] == "get:5");
        assert(g_vDb[1] == "set:5:8000000");
        assert(g_vDb[2] == "sendRank:5");
        // type 1: the gate, then vt+0x18 with
        // money / 50000
        Reset();
        ServiceDonate(&svc, 5, 3000000LL, 1);
        assert(g_vSvc.size() == 3);
        assert(g_vSvc[0] == "level:5");
        assert(g_vSvc[1] == "gate:5");
        assert(g_vSvc[2] == "c18:5:60");
        assert(g_vDb.size() == 3
            && g_vDb[1] == "set:5:8000000"
            && g_vDb[2] == "sendRank:5");
        // type 2: the gate, then vt+0x20
        Reset();
        ServiceDonate(&svc, 5, 3000000LL, 2);
        assert(g_vSvc.size() == 3);
        assert(g_vSvc[2] == "c20:5:60");
        assert(g_vDb.size() == 3
            && g_vDb[1] == "set:5:8000000"
            && g_vDb[2] == "sendRank:5");
        // type 3: vt+0x88 (id, 0x3c) + the silent
        // return (NO STR send, NO charge)
        Reset();
        ServiceDonate(&svc, 5, 3000000LL, 3);
        assert(g_vSvc.size() == 2);
        assert(g_vSvc[0] == "level:5");
        assert(g_vSvc[1] == "vt88:5:60");
        // type 1 with the gate down: the silent
        // return
        Reset(); g_nTypeGate = 0;
        ServiceDonate(&svc, 5, 3000000LL, 1);
        // level + gate, no charge (the silent return)
        assert(g_vSvc.size() == 2);
        assert(g_vSvc[0] == "level:5");
        assert(g_vSvc[1] == "gate:5");
        printf("D23-5 money types ok\n");
    }

    // ---- 6. ServiceDonate charge fail ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        CPeerageService svc; memset(&svc, 0,
                                    sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        g_nChargeRet = 0;
        ServiceDonate(&svc, 5, 3000000LL, 0);
        // level + c10 + the error STR send
        assert(g_vSvc.size() == 3);
        assert(g_vSvc[2] ==
            "str:PROMPT:16711680:2005");
        assert(g_sLastKey ==
            "STR_PEERAGE_DONATE_ERR_NO_ENOUGH_"
            "MONEY");
        assert(g_vDb.empty());   // no DonateCore
        printf("D23-6 charge fail ok\n");
    }

    // ---- 7. SendPeerageState (FUN_141554b10) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        // no elem (or rank < 1): the db fallback —
        // state = the threshold, rank = -1,
        // value = the total
        g_nDonated = 30000000;
        SendPeerageState(&mgr, 9);
        assert(g_sLastAppend ==
            "1 30000000 4294967295 7");
        assert(g_vDb.size() == 2
            && g_vDb[1] == "sendRank:9");
        // the elem hit: rank >= 1 — the elem fields
        // + the rec value
        Reset();
        MockRow row{44, 12345LL};
        SElem e; memset(&e, 0, sizeof e);
        e.row = &row; e.rank10 = 3; e.state14 = 6;
        void* p = &e; VecPushBack(&mgr, &p);
        SendPeerageState(&mgr, 44);
        assert(g_sLastAppend == "3 12345 6 7");
        assert(g_vDb.size() == 1
            && g_vDb[0] == "sendRank:44");
        printf("D23-7 state send ok\n");
    }

    // ---- 8. SweepDeleteById (FUN_1415558a0) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        MockRow rows[3] = {{101, 1}, {202, 2},
                           {303, 3}};
        SElem elems[3];
        for (int i = 0; i < 3; ++i) {
            memset(&elems[i], 0, sizeof(SElem));
            elems[i].vft = (void*)1;
            elems[i].row = &rows[i];
            void* p = &elems[i];
            VecPushBack(&mgr, &p);
        }
        // match on the middle elem: 202
        SweepDeleteById(&mgr, 202,
                        (char*)0x1111, (char*)0x2222);
        assert(g_nRelease == 1);
        assert(g_vElemDelP.size() == 1
            && g_vElemDelP[0] == &elems[1]);
        assert((mgr.m_vec.m_ppEnd
                - mgr.m_vec.m_ppBegin) == 2);
        // the survivors keep their order: 101, 303
        SElem* e0 =
            *(SElem**)mgr.m_vec.m_ppBegin;
        SElem* e1 =
            *(SElem**)(mgr.m_vec.m_ppBegin + 1);
        assert(e0->row == &rows[0]);
        assert(e1->row == &rows[2]);
        // no match: untouched
        Reset(); g_nRelease = 0;
        SweepDeleteById(&mgr, 999,
                        (char*)0x1111, (char*)0x2222);
        assert(g_nRelease == 0
            && g_vElemDelP.empty());
        assert((mgr.m_vec.m_ppEnd
                - mgr.m_vec.m_ppBegin) == 2);
        printf("D23-8 sweep ok\n");
    }

    // ---- 9. GetOrCreateSort (FUN_141555dc0) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        // exec down: destroy + null
        g_nQryExec = 0;
        void* r = GetOrCreateSort(&mgr, 77);
        assert(r == nullptr);
        assert(g_vQry.back() == "destroy");
        // inst, tab, 4 x (field + set), exec, destroy
        assert(g_vQry.size() == 12);
        // exec up: the full sequence
        Reset(); g_nQryExec = 1;
        r = GetOrCreateSort(&mgr, 77);
        assert(r != nullptr);
        // the query order: inst, tab, field 0..3
        // with the b8/b0 sets (0x2dc6c3 on field 1,
        // the id on field 3)
        assert(g_vQry[0] == "inst");
        assert(g_vQry[1] == "tab:dyna_rank_rec");
        assert(g_vQry[2] == "field:0");
        assert(g_vQry[3] == "b8:256:0");
        assert(g_vQry[4] == "field:1");
        assert(g_vQry[5] ==
            "b8:257:3000003");   // 0x2dc6c3
        assert(g_vQry[6] == "field:2");
        assert(g_vQry[7] == "b0:258:0");
        assert(g_vQry[8] == "field:3");
        assert(g_vQry[9] == "b8:259:77");
        assert(g_vQry[10] == "exec:1");
        // the ctor + the underline + the push
        SElem* e = (SElem*)r;
        assert(strcmp(e->ab1c, "BBB") == 0);
        assert(e->key18 == 42);   // +0x18 = underline
        assert(e->row == (void*)&s_qobj);
        assert((mgr.m_vec.m_ppEnd
                - mgr.m_vec.m_ppBegin) == 1);
        printf("D23-9 get-or-create ok\n");
    }

    // ---- 10. DonateCore (FUN_141556db0): the normal
    // path (total <= mgr+0x38 AND rankNum <= size) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        mgr.m_uSpare38 = 10000000000LL;
        mgr.m_nRankNum48 = 0;
        g_nDonated = 5000000;
        DonateCore(&mgr, 5, 3000000LL);
        // the get + the set (5M + 3M)
        assert(g_vDb[0] == "get:5");
        assert(g_vDb[1] == "set:5:8000000");
        // no rank change (0 -> 0): no announce
        // (no pair lookup), one sendRank
        assert(g_vDb.size() == 3);
        assert(g_vDb[2] == "sendRank:5");
        // the type-1 build: rank 0, money, total,
        // TBD arg 555, -1
        assert(g_sLastAppend ==
            "0 3000000 8000000 555 -1");
        // the gmlog
        assert(g_vMisc.size() == 1);
        assert(g_vMisc[0] ==
            "mylog:gmlog/peerage_donate:5:"
            "3000000:0");
        printf("D23-10 donate normal ok\n");
    }

    // ---- 11. DonateCore: the rank-change announce ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        mgr.m_uSpare38 = 10000000000LL;
        mgr.m_nRankNum48 = 0;
        g_nDonated = 29999999;   // old rank 0
        DonateCore(&mgr, 5, 3000001LL);
        // total 33000000 -> new rank 1: the pair +
        // the announce + the type-1 send
        assert(g_vDb[1] == "set:5:33000000");
        assert(g_vDb[2] == "pair:5");
        // the BARON announce (gender 1)
        assert(g_sLastKey ==
            "STR_PEERAGE_PROMPT_BARON");
        assert(g_sLastAppend ==
            "1 3000001 33000000 555 -1");
        assert(g_vMisc.size() == 1);
        printf("D23-11 rank change ok\n");
    }

    // ---- 12. DonateCore: the upper path (elem hit) --
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        mgr.m_nRankNum48 = 10;   // keep the elem
        MockRow row{77, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.vft = (void*)1; e.row = &row;
        strcpy(e.ab1c, "AAA");
        e.rank10 = 0xc;   // quiet in the walk
        e.state14 = 0;
        void* p = &e; VecPushBack(&mgr, &p);
        g_nDonated = 4000000;
        // spare38 = 0 -> total > 0 -> the upper path
        DonateCore(&mgr, 77, 3000000LL);
        assert(g_vDb[0] == "get:77");
        assert(g_vDb[1] == "set:77:7000000");
        // the name differs -> the refresh
        assert(strcmp(e.ab1c, "BBB") == 0);
        // the rec get + the vt38 pair (LAB) — the
        // walk + the tail send
        bool bRecGet = false, bVt38 = false;
        for (auto& s : g_vMisc)
            if (s == "recGet") bRecGet = true;
            else if (s == "vt38:0") bVt38 = true;
        assert(bRecGet && bVt38);
        // the tail: the type-1 with the elem fields
        // (rank 0xc kept by the quiet walk)
        assert(g_sLastAppend ==
            "12 3000000 7000000 555 0");
        assert(g_vMisc.back().substr(0, 5)
               == "mylog");
        printf("D23-12 upper path ok\n");
    }

    // ---- 13. DonateCore: the create path ------
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        mgr.m_nRankNum48 = 10;
        g_nDonated = 4000000;
        // the pair name matches the created elem name
        // ("BBB" from the ctor) -> NO refresh in LAB
        g_sPairName = "BBB";
        DonateCore(&mgr, 77, 3000000LL);
        // the query family ran (the create)
        assert(g_vQry.size() >= 11);
        assert(g_vQry[0] == "inst");
        // the elem created + pushed
        assert((mgr.m_vec.m_ppEnd
                - mgr.m_vec.m_ppBegin) == 1);
        SElem* e =
            *(SElem**)mgr.m_vec.m_ppBegin;
        assert(strcmp(e->ab1c, "BBB") == 0);
        assert(e->key18 == 42);
        // the tail found the fresh elem: sendRank
        bool bSent = false;
        for (auto& s : g_vDb)
            if (s == "sendRank:77") bSent = true;
        assert(bSent);
        assert(g_vMisc.back().substr(0, 5)
               == "mylog");
        printf("D23-13 create path ok\n");
    }

    // ---- 14. DonateCore: the create fails ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        uint32_t fakeDb = 1; mgr.m_pDb = &fakeDb;
        mgr.m_nRankNum48 = 10;
        g_nDonated = 4000000;
        g_nQryExec = 0;   // the query fails
        DonateCore(&mgr, 77, 3000000LL);
        // the tail: FindSortById still null -> the log
        assert(!g_vLog.empty());
        assert(g_vMisc.back().substr(0, 5)
               == "mylog");
        printf("D23-14 create fail ok\n");
    }

    puts("PEERAGE-D23-OK: donation family literal — "
         "name pair, rank thresholds, service "
         "wrappers, donate gates (level 0x46/underline "
         "3M/overflow 1G), money types (/50000, "
         "vt+0x88), charge fail, state send, sweep "
         "delete, get-or-create (0x2dc6c3), donate "
         "core normal/rank-change/upper/create paths, "
         "gmlog/peerage_donate");
    return 0;
}

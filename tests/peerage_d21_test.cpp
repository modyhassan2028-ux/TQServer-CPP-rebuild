// ============================================================
// Peerage.dll — unit D21: the DB load (FUN_1415569f0).
// Mock DB objects with hand-built vtables at the
// ORIGINAL offsets: the instance (vt+0x10 query), the
// recordset (0x00 release / 0x30 set-row / 0x38 get-row
// / 0x40 row-count), the row (0x10 get-field / 0x40 the
// empty-skip 2-arg call / 0x00 release), the field
// (0x40 get-int / 0x78 get-string), the dbobj
// (0x80 the id translate).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "../modules/peerage/src/PeerageDbLoad.h"
#include "../modules/peerage/src/PeerageModule.h"
#include "../modules/peerage/src/PeerageSortMgr.h"
#include "../modules/peerage/src/PeeragePromote.h"

using namespace peerage;

// ---- the call log ----
static std::vector<std::string> g_vLog;
static int g_nLogErr = 0;
struct LogReset {
    LogReset() {
        g_fnSortLogError = []() { g_nLogErr++; };
        g_fnDbInstanceGet = []() -> void* {
            return nullptr; };
        g_szDbQueryRankNum =
            "SELECT rank_num FROM dyna_rank_t";
        g_szDbQueryDynaRec =
            "SELECT dyna_rank_rec_..._FROM cq_user";
    }
};
static LogReset g_reset;

// ---- the mock field (vt+0x40 int / vt+0x78 string)
struct MockField {
    void** m_pVt;
    int m_nVal;
    uint64_t m_pair[2];   // the "string" (16 bytes)
    MockField() : m_pVt(nullptr), m_nVal(0) {
        m_pair[0] = m_pair[1] = 0; }
};
static uint32_t field_getint(void* p) {
    MockField* f = (MockField*)p;
    g_vLog.push_back("fieldGetInt");
    return (uint32_t)f->m_nVal;
}
static uint64_t* field_getstr(void* p) {
    MockField* f = (MockField*)p;
    g_vLog.push_back("fieldGetStr");
    return f->m_pair;
}

// ---- the mock row ----
struct MockRow {
    void** m_pVt;
    std::vector<MockField*> m_fields;
};
static void* row_getfield(void* p, int64_t n) {
    MockRow* r = (MockRow*)p;
    g_vLog.push_back("rowGetField:" +
        std::to_string((int)n));
    return r->m_fields[(size_t)n];
}
static void row_vt40_skip(void* p, uint64_t a) {
    (void)p; (void)a;
    g_vLog.push_back("rowSkip40");
}
static uint64_t row_release2(void* p, uint64_t f) {
    (void)f;
    g_vLog.push_back("rowRelease");
    return 0xABCD;   // a visible RAX
}

// ---- the mock recordset ----
struct MockRs {
    void** m_pVt;
    std::vector<MockRow*> m_rows;
    size_t m_nCur = 0;
    size_t m_nSkipChecked = 0;
};
static uint64_t rs_rowcount(void* p) {
    MockRs* rs = (MockRs*)p;
    g_vLog.push_back("rsRowCount:" +
        std::to_string(rs->m_rows.size()));
    return rs->m_rows.size();
}
static void rs_setrow(void* p, uint64_t i) {
    MockRs* rs = (MockRs*)p;
    rs->m_nCur = (size_t)i;
    g_vLog.push_back("rsSetRow:" +
        std::to_string((int)i));
}
static void* rs_getrow(void* p) {
    MockRs* rs = (MockRs*)p;
    g_vLog.push_back("rsGetRow");
    return rs->m_rows[rs->m_nCur];
}
static uint64_t rs_release1(void* p) {
    g_vLog.push_back("rsRelease");
    return 0x1234;   // a visible RAX
}

// ---- the mock dbobj (mgr+0x40): vt+0x80 translate
static uint32_t g_nTranslateIn = 0;
static uint32_t dbobj_translate(void* p, uint32_t id) {
    (void)p;
    g_nTranslateIn = id;
    g_vLog.push_back("dbTranslate:" +
        std::to_string(id));
    return id * 7 + 3;
}

// ---- the mock instance (vt+0x10 query) ----
struct MockInstance {
    void** m_pVt;
    int m_nQ1Calls = 0;
    int m_nQ2Calls = 0;
    MockRs* m_pRs1 = nullptr;
    MockRs* m_pRs2 = nullptr;
};
static void* inst_query(void* p, const char* sql,
                        int64_t flag) {
    MockInstance* inst = (MockInstance*)p;
    if (sql == g_szDbQueryRankNum) {
        inst->m_nQ1Calls++;
        g_vLog.push_back("q1:" + std::to_string(flag));
        return inst->m_pRs1;
    }
    inst->m_nQ2Calls++;
    // (the 2nd call passes only 2 visible args; the
    // flag register is NOT read on this path)
    g_vLog.push_back("q2");
    return inst->m_pRs2;
}

// ---- vtable builders (slots at the ORIGINAL off.)
static void* g_vtField[0x80 / 8];
static void* g_vtRow[0x48 / 8];
static void* g_vtRs[0x48 / 8];
static void* g_vtInst[0x18 / 8];
static void* g_vtDb[0x88 / 8];
struct VtInit {
    VtInit() {
        memset(g_vtField, 0, sizeof g_vtField);
        memset(g_vtRow, 0, sizeof g_vtRow);
        memset(g_vtRs, 0, sizeof g_vtRs);
        memset(g_vtInst, 0, sizeof g_vtInst);
        memset(g_vtDb, 0, sizeof g_vtDb);
        g_vtField[0x40 / 8] = (void*)field_getint;
        g_vtField[0x78 / 8] = (void*)field_getstr;
        g_vtRow[0x00 / 8] = (void*)row_release2;
        g_vtRow[0x10 / 8] = (void*)row_getfield;
        g_vtRow[0x40 / 8] = (void*)row_vt40_skip;
        g_vtRs[0x00 / 8] = (void*)rs_release1;
        g_vtRs[0x30 / 8] = (void*)rs_setrow;
        g_vtRs[0x38 / 8] = (void*)rs_getrow;
        g_vtRs[0x40 / 8] = (void*)rs_rowcount;
        g_vtInst[0x10 / 8] = (void*)inst_query;
        g_vtDb[0x80 / 8] = (void*)dbobj_translate;
    }
};
static VtInit g_vtInit;

// ---- the D20 seams (the final walk) — count + rank
static std::vector<uint32_t> g_vWalkTouch;
struct WalkSeams {
    WalkSeams() {
        g_fnDbTouch = [](void* db, uint32_t id) {
            (void)db; g_vWalkTouch.push_back(id); };
        g_fnDbSendRank = [](void*, uint32_t, void*) {};
        g_fnDbAnnounce = [](void*, const char*,
                           uint32_t, uint16_t) {};
        g_fnDbSendAnnounce = [](void*, uint32_t, void*) {};
        g_fnDbGetGender = [](void*, uint32_t) -> int {
            return 1; };
        g_fnDbAnnounceEnabled = [](void*) -> bool {
            return false; };
        g_fnMsgAppend = [](void*, char*) -> bool {
            return true; };
        g_fnTheInstance = []() -> void* {
            return (void*)1; };
        g_fnStrMgrGet = [](void*, const char* key)
            -> const char* { (void)key; return ""; };
        g_fnBuildArg4 = []() -> int { return 0; };
        g_fnRowVt40Release = [](void*, int, void*,
                               void*, int64_t) {};
        g_fnRowDelete = [](void*, uint64_t) {};
        g_fnElemDelete = [](void*, uint64_t) {};
        g_fnInvalidParameter = []() {
            assert(!"invalid_parameter"); };
    }
};
static WalkSeams g_walkSeams;

// a fresh mgr per section (the real D18 ctor)
static CPeerageSortMgr* MakeMgr() {
    static CPeerageSortMgr mgr;
    memset(&mgr, 0, sizeof mgr);
    CtorPeerageSortMgr(&mgr);
    return &mgr;
}

int main() {
    setbuf(stdout, nullptr);

    // ---- 1. the null-db gate ----
    {
        g_vLog.clear(); g_nLogErr = 0;
        uint64_t r = PeerageDbLoad(MakeMgr(), nullptr);
        assert(r == 0);
        assert(g_nLogErr == 1);
        assert(g_vLog.empty());   // no instance call
        puts("D21-1 nulldb ok");
    }

    // (NOTE: a null InstanceGet result is NOT
    // checked by the original — the very next
    // vtable call would fault. No test case for it.)

    // ---- 2. the null first recordset ----
    {
        g_vLog.clear(); g_nLogErr = 0;
        static MockInstance inst = {};
        inst.m_pVt = g_vtInst;
        g_fnDbInstanceGet = [&inst]() -> void* {
            return &inst; };
        CPeerageSortMgr* pMgr = MakeMgr();
        uint64_t r = PeerageDbLoad(pMgr, (void*)7);
        assert(r == 0);
        assert(g_nLogErr == 1);
        assert(inst.m_nQ1Calls == 1);
        assert(pMgr->m_pDb == (void*)7);   // stored
        puts("D21-2 nullrs ok");
    }

    // ---- 4. rank_num: zero rows -> the release
    //      return masked (RAX & ~0xff) ----
    {
        g_vLog.clear(); g_nLogErr = 0;
        static MockInstance inst = {};
        inst.m_pVt = g_vtInst;
        static MockRs rs1 = {};
        rs1.m_pVt = g_vtRs;
        inst.m_pRs1 = &rs1;
        g_fnDbInstanceGet = [&inst]() -> void* {
            return &inst; };
        uint64_t r = PeerageDbLoad(MakeMgr(), (void*)9);
        // rsRelease returns 0x1234 -> masked 0x1200
        assert(r == (0x1234 & 0xffffffffffffff00ULL));
        assert(g_nLogErr == 0);
        assert(inst.m_nQ2Calls == 0);   // no 2nd query
        puts("D21-3 emptyrank ok");
    }

    // ---- 5. the null row of the rank query ----
    {
        g_vLog.clear(); g_nLogErr = 0;
        static MockInstance inst = {};
        inst.m_pVt = g_vtInst;
        static MockRs rs1 = {};
        rs1.m_pVt = g_vtRs;
        rs1.m_rows = {(MockRow*)1};   // 1 row; getrow
        rs1.m_nCur = 0;               // returns null?
        // (need a null row: use a special vt)
        static void* vtRsNull[0x48 / 8] = {};
        vtRsNull[0x00 / 8] = (void*)rs_release1;
        vtRsNull[0x40 / 8] = (void*)rs_rowcount;
        vtRsNull[0x30 / 8] = (void*)rs_setrow;
        static void* (*rsNullGetRow)(void*) =
            [](void*) -> void* { return nullptr; };
        vtRsNull[0x38 / 8] = (void*)rsNullGetRow;
        rs1.m_pVt = vtRsNull;
        inst.m_pRs1 = &rs1;
        g_fnDbInstanceGet = [&inst]() -> void* {
            return &inst; };
        uint64_t r = PeerageDbLoad(MakeMgr(), (void*)9);
        assert(r == (0x1234 & 0xffffffffffffff00ULL));
        assert(g_nLogErr == 1);
        puts("D21-4 nullrow ok");
    }

    // ---- 6. the full success path ----
    {
        g_vLog.clear(); g_nLogErr = 0;
        g_vWalkTouch.clear();
        g_nTranslateIn = 0;
        static MockInstance inst = {};
        inst.m_pVt = g_vtInst;
        // rs1: one row, field0 = 51 (the rank_num)
        static MockField f0 = {};
        f0.m_pVt = g_vtField; f0.m_nVal = 51;
        static MockRow row1 = {};
        row1.m_pVt = g_vtRow;
        row1.m_fields = {&f0};
        static MockRs rs1 = {};
        rs1.m_pVt = g_vtRs; rs1.m_nCur = 0;
        rs1.m_rows = {&row1};
        inst.m_pRs1 = &rs1;
        // rs2: 4 rows; one empty name (skip), three
        // named (create + translate + push)
        static MockField nm[4];
        static MockField idf[4];
        static MockRow row2[4];
        static MockRs rs2 = {};
        rs2.m_pVt = g_vtRs; rs2.m_nCur = 0;
        const char* names[4] =
            {"Alice", "", "Bob", "Cara"};
        const int ids[4] = {10, 11, 12, 13};
        for (int i = 0; i < 4; ++i) {
            nm[i].m_pVt = g_vtField;
            // the pair: the first 16 bytes of the
            // name storage (offsets +0x1c/+0x24)
            memcpy(nm[i].m_pair, "0123456789abc", 14);
            if (i == 1) {
                memset(nm[i].m_pair, 0, 16);
                // the empty-name: an EMPTY string
                nm[i].m_pair[0] = 0;
            } else {
                memcpy(nm[i].m_pair, names[i],
                       strlen(names[i]) + 1);
            }
            idf[i].m_pVt = g_vtField;
            idf[i].m_nVal = ids[i];
            row2[i].m_pVt = g_vtRow;
            // field 3 = the id (the create path reads
            // vt+0x10(row,3) -> vt+0x40 int); field 4
            // = the name storage (read twice)
            row2[i].m_fields = {&idf[i], &idf[i],
                                &idf[i], &idf[i],
                                &nm[i]};
            rs2.m_rows.push_back(&row2[i]);
        }
        inst.m_pRs2 = &rs2;
        g_fnDbInstanceGet = [&inst]() -> void* {
            return &inst; };
        // a REAL dbobj (the vt+0x80 translate slot)
        static struct { void** vt; } dbobj = {
            g_vtDb };
        CPeerageSortMgr* pMgr = MakeMgr();
        uint64_t r = PeerageDbLoad(pMgr, &dbobj);
        assert(r == 1);                    // AL = 1
        assert(g_nLogErr == 0);
        assert(pMgr->m_pDb == &dbobj);
        assert(pMgr->m_nRankNum48 == 51);    // +0x48
        // the queries
        assert(inst.m_nQ1Calls == 1);
        assert(inst.m_nQ2Calls == 1);
        // the walk: 3 pushed elems, ranks 0..2,
        // no erase (rankNum 51 > 3)
        assert(pMgr->m_vec.m_ppEnd -
               pMgr->m_vec.m_ppBegin == 3);
        // the keys: translate(id) = id*7+3; the walk
        // SORTS the vector (descending by +0x18), so
        // the first elem is Cara (id 13 -> 94)
        CPeerageSort* pE =
            (CPeerageSort*)pMgr->m_vec.m_ppBegin[0];
        assert(pE->Row() == (void*)&row2[3]);
        assert(pE->N18() == (uint32_t)(13 * 7 + 3));
        // the pair copy from the name storage
        assert(pE->Field1c() == nm[3].m_pair[0]);
        assert(pE->Field24() == nm[3].m_pair[1]);
        // the walk ran (bNoSend=1: touch per elem,
        // no packets — the D20 contract)
        assert(g_vWalkTouch.size() == 3);
        // ranks assigned 0..2
        for (int i = 0; i < 3; ++i) {
            CPeerageSort* pe =
                (CPeerageSort*)
                    pMgr->m_vec.m_ppBegin[i];
            assert(pe->N14() == (uint32_t)i);
        }
        puts("D21-5 full ok");
    }

    // ---- 7. the ctor-null path (141552340 -> 0) ----
    {
        g_vLog.clear(); g_nLogErr = 0;
        g_vWalkTouch.clear();
        static MockInstance inst = {};
        inst.m_pVt = g_vtInst;
        static MockField f0 = {};
        f0.m_pVt = g_vtField; f0.m_nVal = 1;
        static MockRow row1 = {};
        row1.m_pVt = g_vtRow;
        row1.m_fields = {&f0};
        static MockRs rs1 = {};
        rs1.m_pVt = g_vtRs;
        rs1.m_rows = {&row1};
        inst.m_pRs1 = &rs1;
        static MockField nm = {};
        nm.m_pVt = g_vtField;
        memcpy(nm.m_pair, "X", 2);
        static MockRow row2 = {};
        row2.m_pVt = g_vtRow;
        row2.m_fields = {&nm, &nm, &nm, &nm, &nm};
        static MockRs rs2 = {};
        rs2.m_pVt = g_vtRs;
        rs2.m_rows = {&row2};
        inst.m_pRs2 = &rs2;
        g_fnDbInstanceGet = [&inst]() -> void* {
            return &inst; };
        // force the ctor seam: alloc -> null
        auto savedAlloc = g_fnSortAlloc;
        g_fnSortAlloc = [](size_t) -> void* {
            return nullptr; };
        CPeerageSortMgr* pMgr = MakeMgr();
        uint64_t r = PeerageDbLoad(pMgr, (void*)3);
        assert(r == 1);              // the walk ran
        assert(g_nLogErr == 1);       // the ctor-null
        // nothing pushed
        assert(pMgr->m_vec.m_ppEnd -
               pMgr->m_vec.m_ppBegin == 0);
        g_fnSortAlloc = savedAlloc;
        puts("D21-6 ctornull ok");
    }

    // ---- 8. the caller glue (1415516a0 -> D17
    //      g_fnPeerageObjInit) ----
    {
        static MockInstance inst = {};
        inst.m_pVt = g_vtInst;
        static MockRs rs1 = {};
        rs1.m_pVt = g_vtRs;
        inst.m_pRs1 = &rs1;   // 0 rows -> masked ret
        g_fnDbInstanceGet = [&inst]() -> void* {
            return &inst; };
        // bind the D17 seams to the REAL bodies
        g_fnMakePeerageObj = []() -> void* {
            return MakeMgr(); };
        g_fnPeerageObjInit =
            [](void* obj, void* kernel) -> uint64_t {
                return PeerageDbLoad(
                    (CPeerageSortMgr*)obj, kernel);
            };
        CPeerageService svc = {};
        svc.m_pVftable = (void*)1;
        uint64_t r = AttachPeerageService(&svc, (void*)0x77);
        assert(r == (0x1234 & 0xffffffffffffff00ULL));
        assert(svc.m_pKernel == (void*)0x77);
        assert(svc.m_pObj10 != nullptr);
        puts("D21-7 attach ok");
    }

    puts("PEERAGE-D21-OK");
    return 0;
}

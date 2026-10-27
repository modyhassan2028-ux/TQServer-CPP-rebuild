// ============================================================
// Peerage.dll — unit D24: the remaining service functions
// (141551920/1a00/1b00/1b90/1bf0/1c20/1eb0) + the rank
// lookup helpers (1415549d0/141555070). Mock kit: same raw
// SElem layout as D23 (row at +8).
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

#include "../modules/peerage/src/PeerageService.h"
#include "../modules/peerage/src/PeerageModule.h"
#include "../modules/peerage/src/PeerageSortMgr.h"
#include "../modules/peerage/src/PeerageSort.h"
#include "../modules/peerage/src/PeeragePromote.h"
#include "../modules/peerage/src/PeerageMsgWire.h"
#include "../modules/peerage/src/PeerageDonate.h"

using namespace peerage;
using std::string;
using std::to_string;

// ---- the mocks ----
struct MockRow { uint32_t id; int64_t value; };
struct SElem {
    void* vft;              // +0x00
    void* row;              // +0x08
    uint32_t state10;       // +0x10
    uint32_t rank14;        // +0x14
    uint32_t key18;         // +0x18
    char ab1c[0x14];        // +0x1c (name + the bool)
};

// ---- the captures ----
static std::vector<string> g_vSvc;    // kernel seam log
static std::vector<string> g_vDb;
static std::vector<string> g_vLog;
static std::vector<void*> g_vFree;
static std::vector<uint32_t> g_vVisible;   // IsVisible ids
static std::vector<uint32_t> g_vVt78;      // Vt78 ids
static std::vector<string> g_vAppend;      // the append strings
static std::vector<void*> g_vSentMsg;     // SendMsg msg ptrs
static std::vector<uint32_t> g_vSentId;
static string g_sLastAppend;
static uint64_t g_uBuildArg4 = 7;
static uint64_t g_uBuild1Arg4 = 555;
static int64_t g_nDonated = 0;
static int g_nInvalid = 0;
static int g_nChargeRet = 1;

static void Reset() {
    g_vSvc.clear(); g_vDb.clear(); g_vLog.clear();
    g_vFree.clear(); g_vVisible.clear(); g_vVt78.clear();
    g_vAppend.clear(); g_vSentMsg.clear();
    g_vSentId.clear(); g_sLastAppend.clear();
}

static void Bind() {
    // ---- the alloc/log seams ----
    g_fnSortLogError = []() {
        g_vLog.push_back("sort"); };
    g_fnInlineLogError = []() {
        g_vLog.push_back("inline"); };
    g_fnInvalidParameter = []() {
        ++g_nInvalid; };
    g_fnProxyAlloc = [](size_t n) {
        return malloc(n); };
    g_fnProxyDelete = [](void* p) {
        free(p); };
    g_fnVecAlloc = [](size_t n) {
        return malloc(n); };
    g_fnVecDelete = [](void* p) {
        free(p); };
    g_fnSortAlloc = [](size_t n) {
        return malloc(n); };
    g_fnFree = [](void* p) {
        g_vFree.push_back(p); };
    g_fnAlloc = [](size_t n) {
        return malloc(n); };
    // ---- the row/record seams ----
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
    // ---- the msg seams ----
    g_fnPackerCtor = [](void*) {};
    g_fnPackerDtor = [](void*) {};
    g_fnPackerSetBuf = [](void*, char*, uint32_t,
                          bool) {};
    g_fnMsgAppend = [](void* p, char* s) {
        (void)p; g_sLastAppend = s;
        g_vAppend.push_back(s); return true; };
    g_fnBuildArg4 = []() -> int {
        return (int)g_uBuildArg4; };
    g_fnBuild1Arg4 = []() -> uint64_t {
        return g_uBuild1Arg4; };
    // ---- the service-kernel seams (svc+8) ----
    g_fnSvcGetDonated = [](void* k, uint32_t id) {
        (void)k; g_vSvc.push_back(
            "donated:" + to_string(id));
        return g_nDonated; };
    g_fnSvcSendMsg = [](void* k, uint32_t id,
                        void* msg) {
        (void)k; g_vSentId.push_back(id);
        // the ORIGINAL builds the top-list message in a
        // STACK CMsg local (local_468[1072] in the
        // decompile); the real kernel's send seam
        // consumes it inside the call, and the frame
        // dies on return. Recording the bare pointer
        // dangles (heisenbug depending on later stack
        // use) — deep-copy the 0x430 buffer verbatim.
        char* pCopy = (char*)malloc(0x430);
        memcpy(pCopy, msg, 0x430);
        g_vSentMsg.push_back(pCopy); };
    g_fnSvcIsVisible = [](void* k, uint32_t id) {
        (void)k; g_vVisible.push_back(id);
        return (char)1; };
    g_fnSvcGetVt78 = [](void* k, uint32_t id) {
        (void)k; g_vVt78.push_back(id);
        return (uint32_t)0x99; };
    // ---- the db seams (used by DonateInfo) ----
    g_fnDbSendRank = [](void* db, uint32_t id,
                        void* msg) {
        (void)db; (void)msg;
        g_vDb.push_back("sendRank:" + to_string(id)); };
}

int main() {
    Bind();

    // ---- 1. StateFromValue (141552980, exported) ----
    {
        assert(StateFromValue(29999999LL) == 0);
        assert(StateFromValue(30000000LL) == 1);
        assert(StateFromValue(100000000LL) == 3);
        assert(StateFromValue(200000000LL) == 5);
        puts("D24-1 state-from-value ok");
    }

    // ---- 2. VecSlotAt (141551b90) ----
    {
        void* slots[4] = {(void*)1, (void*)2,
                          (void*)3, (void*)4};
        struct { void* proxy; char pad[0x10];
                 void** begin; void** end; void** cap; }
            vec = { (void*)0x11, {}, slots,
                    slots + 4, slots + 4 };
        g_nInvalid = 0;
        // operator[] returns &slot[i] (the address)
        assert(VecSlotAt(&vec, 2) == (void*)&slots[2]);
        assert(g_nInvalid == 0);
        assert(VecSlotAt(&vec, 3) == (void*)&slots[3]);
        VecSlotAt(&vec, 4);   // out of range
        assert(g_nInvalid == 1);
        puts("D24-2 vec slot ok");
    }

    // ---- 3. ServiceScalarDeletingDtor (141551bf0) ----
    {
        Reset();
        CPeerageService svc;
        memset(&svc, 0, sizeof svc);
        // flags 0: no free
        ServiceScalarDeletingDtor(&svc, 0, 0, 0);
        assert(g_vFree.empty());
        // flags 1: the free runs
        ServiceScalarDeletingDtor(&svc, 1, 0, 0);
        assert(g_vFree.size() == 1
            && g_vFree[0] == &svc);
        puts("D24-3 scalar dtor ok");
    }

    // ---- 4. FindSortByRank (1415549d0, backward) ----
    {
        Reset();
        g_nInvalid = 0;   // section 2 fired one
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        const int N = 3;
        MockRow rows[N] = {{11, 10}, {22, 20},
                           {33, 30}};
        SElem elems[N];
        for (int i = 0; i < N; ++i) {
            memset(&elems[i], 0, sizeof elems[i]);
            elems[i].vft = (void*)1;
            elems[i].row = &rows[i];
            elems[i].state10 = (uint32_t)(7 - i);
        }
        for (int i = 0; i < N; ++i) {
            void* p = &elems[i];
            VecPushBack(&mgr, &p);
        }
        // rank 5: only elems[2] (state10 5) -> the
        // backward walk finds it
        void* r = FindSortByRank(&mgr, 5);
        assert(r == &elems[2]);
        // rank 7: elems[0]; the walk starts from the
        // END and 7 exists only at the head
        r = FindSortByRank(&mgr, 7);
        assert(r == &elems[0]);
        // no match
        r = FindSortByRank(&mgr, 1);
        assert(r == nullptr);
        assert(g_nInvalid == 0);   // fresh: no checks fire
        puts("D24-4 find-by-rank ok");
    }

    // ---- 5. CountBelowThreshold (141555070) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        MockRow rows[3] = {{1, 50000000},
                          {2, 25000000},
                          {3, 15000000}};
        SElem elems[3];
        for (int i = 0; i < 3; ++i) {
            memset(&elems[i], 0, sizeof elems[i]);
            elems[i].vft = (void*)1;
            elems[i].row = &rows[i];
            elems[i].rank14 = (uint32_t)(10 + i);
        }
        for (int i = 0; i < 3; ++i) {
            void* p = &elems[i];
            VecPushBack(&mgr, &p);
        }
        // threshold 30M: first value below is
        // rows[1] (25M) -> elem[1]+0x14 = 11
        assert(CountBelowThreshold(&mgr, 30000000)
               == 11);
        // threshold 10M: no value below -> -1
        assert(CountBelowThreshold(&mgr, 10000000)
               == 0xffffffff);
        puts("D24-5 count-below ok");
    }

    // ---- 6. ServiceQueryRank (141551920) ----
    {
        // elem null: the donated total path
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        CPeerageService svc;
        memset(&svc, 0, sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        g_nDonated = 100000000;
        ServiceQueryRank(&svc, 9);
        // StateFromValue(100M) = 3; append "3 100000000
        // -1 7"; the send
        assert(g_sLastAppend == "3 100000000 4294967295 7");
        assert(g_vSentId.size() == 1
            && g_vSentId[0] == 9);
        // elem path: elem+0x10/+0x14 + the rec value
        Reset();
        MockRow row{21, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.vft = (void*)1; e.row = &row;
        e.state10 = 4; e.rank14 = 2;
        void* p = &e; VecPushBack(&mgr, &p);
        ServiceQueryRank(&svc, 21);
        // append "4 42 2 7"
        assert(g_sLastAppend == "4 42 2 7");
        assert(g_vSentId.size() == 1);
        puts("D24-6 query rank ok");
    }

    // ---- 7. ServiceDonateInfo (141551a00) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        CPeerageService svc;
        memset(&svc, 0, sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        uint32_t uOut = 0;
        // empty mgr, rank 1: out=-1 then the 30M
        // threshold count (empty vec -> -1), base 3M;
        // NO donated probe (the by-rank lookup found
        // nothing)
        int64_t v = ServiceDonateInfo(&svc, 5, 1,
                                      &uOut);
        assert(v == 3000000);
        assert(uOut == 0xffffffff);
        assert(g_vSvc.empty());
        // rank 9 (>= 7): out stays -1, no threshold
        Reset(); uOut = 0;
        v = ServiceDonateInfo(&svc, 5, 9, &uOut);
        assert(v == 3000000
            && uOut == 0xffffffff);
        // gate: rank >= 0xd -> 0
        Reset(); uOut = 0;
        v = ServiceDonateInfo(&svc, 5, 0xd, &uOut);
        assert(v == 0 && uOut == 0);
        assert(g_vSvc.empty());
        // gate: elem exists with rank >= requested -> 0
        Reset(); uOut = 0;
        MockRow row{5, 42};
        SElem e; memset(&e, 0, sizeof e);
        e.vft = (void*)1; e.row = &row;
        e.state10 = 5;
        void* p = &e; VecPushBack(&mgr, &p);
        v = ServiceDonateInfo(&svc, 5, 5, &uOut);
        assert(v == 0 && uOut == 0);
        // elem with a LOWER rank + a by-rank elem:
        // value - total + 1
        Reset(); uOut = 0;
        g_nDonated = 1000000;
        e.state10 = 1;        // below rank 3 now
        e.rank14 = 9;
        MockRow rowHi{77, 100000000};
        SElem eHi; memset(&eHi, 0, sizeof eHi);
        eHi.vft = (void*)1; eHi.row = &rowHi;
        eHi.state10 = 3;      // rank 3 holder
        void* pH = &eHi; VecPushBack(&mgr, &pH);
        v = ServiceDonateInfo(&svc, 5, 3, &uOut);
        // by-rank value 100M - donated 1M + 1
        assert(v == 100000000 - 1000000 + 1);
        // the 100M threshold count: first value <
        // 100M = row(5, 42) elem -> its +0x14 (9)
        assert(uOut == 9);
        assert(g_vSvc.size() == 1);   // one probe
        // floor: value < total -> 3M
        Reset(); uOut = 0;
        g_nDonated = 500000000;
        v = ServiceDonateInfo(&svc, 5, 3, &uOut);
        assert(v == 3000000);
        puts("D24-7 donate info ok");
    }

    // ---- 8. ServiceSendState (141551b00) ----
    {
        Reset();
        CPeerageService svc;
        memset(&svc, 0, sizeof svc);
        svc.m_pKernel = (void*)0x55;
        ServiceSendState(&svc, 5, 9);
        assert(g_sLastAppend == "9 0 0 7");
        assert(g_vSentId.size() == 1
            && g_vSentId[0] == 5);
        puts("D24-8 send state ok");
    }

    // ---- 9. ServiceSendTopList (141551c20) ----
    {
        Reset();
        // null mgr -> the log
        CPeerageService svcNull;
        memset(&svcNull, 0, sizeof svcNull);
        ServiceSendTopList(&svcNull, 5, 0);
        assert(g_vLog.size() == 1);
        assert(g_vSentId.empty());
        // 12 elems: count 12+9=21 -> build (0, 2);
        // the page loop appends 10
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        CPeerageService svc;
        memset(&svc, 0, sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        const int N = 12;
        MockRow rows[N];
        SElem elems[N];
        for (int i = 0; i < N; ++i) {
            rows[i].id = (uint32_t)(100 + i);
            rows[i].value = 1000 + i;
            memset(&elems[i], 0, sizeof elems[i]);
            elems[i].vft = (void*)1;
            elems[i].row = &rows[i];
            elems[i].state10 = 1;
            elems[i].rank14 = (uint32_t)i;
            strcpy(elems[i].ab1c, "NM");
        }
        for (int i = 0; i < N; ++i) {
            void* p = &elems[i];
            VecPushBack(&mgr, &p);
        }
        ServiceSendTopList(&svc, 5, 0);
        char* buf = (char*)g_vSentMsg[0];
        // the header (msg+8 buffer): type 2
        assert(*(uint16_t*)(buf + 8 + 4) == 2);
        assert(*(uint16_t*)(buf + 8 + 2) == 0x810);
        // count at buf+0xc: 10 records
        assert(*(uint32_t*)(buf + 8 + 0xc) == 10);
        // header size: written BEFORE the count
        // increments — verbatim the size LAGS one
        // record: (10-1)*0x30 + 0xa8
        assert(*(uint16_t*)(buf + 8)
               == 9 * 0x30 + 0xa8);
        // record 0 at +0x78: id 100, name "NM"
        assert(*(uint32_t*)(buf + 8 + 0x78) == 100);
        // name at rec+0xc (rec[1]+4, the strncpy
        // target — verbatim append layout)
        assert(strcmp(buf + 8 + 0x78 + 0xc, "NM")
               == 0);
        // the visible/vt78 probes: 10 elems
        assert(g_vVisible.size() == 10);
        assert(g_vVt78.size() == 10);
        // the send is one packet
        assert(g_vSentId.size() == 1
            && g_vSentId[0] == 5);
        // page 2 (idx 20..): beyond the 12 elems ->
        // the loop breaks immediately, the send still
        // runs (unconditional — verbatim)
        Reset();
        ServiceSendTopList(&svc, 5, 2);
        assert(g_vVisible.empty());
        assert(g_vSentId.size() == 1);
        puts("D24-9 top list ok");
    }

    // ---- 10. ServiceQueryAllRanks (141551eb0) ----
    {
        Reset();
        CPeerageSortMgr mgr;
        CtorPeerageSortMgr(&mgr);
        CPeerageService svc;
        memset(&svc, 0, sizeof svc);
        svc.m_pKernel = (void*)0x55;
        svc.m_pObj10 = &mgr;
        g_nDonated = 0;
        ServiceQueryAllRanks(&svc, 5);
        // the type-4 packet: memcpy 0x60 at buf+8
        char* buf = (char*)g_vSentMsg[0];
        assert(*(uint16_t*)(buf + 8 + 4) == 4);
        assert(*(uint16_t*)(buf + 8 + 2) == 0x810);
        // the 6x16 array: {3M, -1, rank}
        struct SPair {
            uint64_t uVal; uint32_t uOut;
            uint32_t uRank; };
        SPair* recs = (SPair*)(buf + 8 + 8);
        const uint32_t want[6] = {1, 3, 5, 7, 9, 0xc};
        for (int i = 0; i < 6; ++i) {
            assert(recs[i].uVal == 3000000);
            assert(recs[i].uOut == 0xffffffff);
            assert(recs[i].uRank == want[i]);
        }
        // the donated probe fires only inside the
        // FindSortByRank hit — empty mgr -> 0 probes
        assert(g_vSvc.empty());
        puts("D24-10 all ranks ok");
    }

    puts("PEERAGE-D24-OK: service family literal — "
         "query rank (state-from-value + elem fields), "
         "donate-info pair (gates 0xd/7, thresholds "
         "30M/100M/200M, value-total+1 floor 3M), send "
         "state, vec slot, scalar deleting dtor, top "
         "list (count+9 cap 0x32, 10-per-page append, "
         "unconditional send), all-ranks type-4 6x16 "
         "memcpy, find-by-rank backward, "
         "count-below-threshold");
    return 0;
}

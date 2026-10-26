// D58: the module-family tail — the checked-set
// pair, the scalar dtor, the static free, the
// array loop, the stride-4/0x14 vector helpers,
// the meed heap family, and the LeaveAwardFlow.
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>

#include "Exe/Dll/Syndicate/Port/SyndicateModuleTail.h"
#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeaveAward.h"

using namespace syndicate;

// ---------- the seams ----------
static int g_nLog = 0;
static void MockLog(const char* p) {
    (void)p; ++g_nLog;
}
static int g_nInvalid = 0;
static void MockInvalid() { ++g_nInvalid; }
static int g_nBadAlloc = 0;
static size_t g_nLastThrow = 0;
static void MockBadAlloc(size_t n) {
    ++g_nBadAlloc; g_nLastThrow = n;
}
static void* MockOpNew8() { return malloc(8); }
static std::vector<void*> g_aDeleted;
static void MockOpDelete(void* p) {
    g_aDeleted.push_back(p);
    free(p);   // record AND release (ASan)
}
static size_t g_nLastAlloc = 0;
static void* MockTailOpNew(size_t n) {
    g_nLastAlloc = n;
    return malloc(n ? n : 1);
}
static int g_nHeapCtor = 0;
static void MockHeapCtor(void*, const char*) {
    ++g_nHeapCtor;
}
static int g_nAtexit = 0;
static void MockAtexit(void*) { ++g_nAtexit; }
static int g_nHAlloc = 0;
static void* MockHeapAlloc(void*, size_t n) {
    ++g_nHAlloc; return malloc(n ? n : 1);
}
static int g_nHFree = 0;
static void MockHeapFree(void*, void*) {
    ++g_nHFree;
}
static int g_nHValid = 0;
static char MockHeapValid(void*, void*) {
    ++g_nHValid; return 1;
}
static char g_cSendOk = 1;
static uint32_t g_uSendId;
static int g_nSendType, g_nSendMoney, g_nSendEMoney;
static char MockSendLeaveAward(void*, uint32_t uId,
    int nType, int nMoney, int nEMoney) {
    g_uSendId = uId; g_nSendType = nType;
    g_nSendMoney = nMoney; g_nSendEMoney = nEMoney;
    return g_cSendOk;
}

// ---- the D58-8 record/mgr mocks ----
static void* s_aRecVt[16];       // the record vtable
static void* s_aSubObj[2];       // the sub object
static void* s_aSubVt[16];       // the sub vtable
static int s_nSubIdx;
static char s_cDeleteOk = 1;
static int s_nRecDtor = 0;
static void* s_aRec[2];
static void* s_aMgrVt[0x80];
static void* s_aMgr[2];
static void* s_aMod[2];
static int s_nQuery = 0;
static int s_pVecFill = 0;   // 0: one rec, 1: null,
                             // 2: empty
static void* s_pVecBuf = nullptr;

static void* RecSubGet(void* p, int idx) {
    (void)p; s_nSubIdx = idx;
    return s_aSubObj;
}
static uint32_t SubGet(void*) {
    switch (s_nSubIdx) {
    case 2: return 0x100;   // money
    case 3: return 0x200;   // emoney
    case 4: return 0x300;   // type
    }
    return 0;
}
static char RecDelete(void*, int) {
    return s_cDeleteOk;
}
static void RecDtor(void*, uint64_t u) {
    if (u == 1) ++s_nRecDtor;
}
static void MgrQuery(void* pMgr, void* pCtx,
                     uint32_t uId, int e) {
    (void)pMgr; (void)uId;
    assert(e == 0xe);
    ++s_nQuery;
    struct SCtxMirror {
        void* pNode; void* a1; void* a2;
        void* pBegin; void* pEnd; void* pCap;
    };
    SCtxMirror* pC = (SCtxMirror*)pCtx;
    // (the flow frees the previous buffer through
    // the delete seam itself; a fresh one here)
    if (s_pVecFill == 2) {
        pC->pBegin = nullptr;
        pC->pEnd = nullptr;
        return;
    }
    pC->pBegin = s_pVecBuf = malloc(8);
    *(void**)pC->pBegin = (s_pVecFill == 1)
        ? nullptr : (void*)s_aRec;
    pC->pEnd = (char*)pC->pBegin + 8;
}

static std::vector<std::string> s_aLeaveLogs;
static void MockLeaveLogError(const char* p, ...) {
    s_aLeaveLogs.push_back(p);
}
static void MockLeaveGmLog(const char* pCat,
                           const char* pFmt, ...) {
    s_aLeaveLogs.push_back(std::string(pCat)
        + "|" + pFmt);
}

static void BuildLeaveMocks() {
    s_aRecVt[2] = (void*)RecSubGet;   // +0x10
    s_aSubVt[9] = (void*)SubGet;      // +0x48
    s_aSubObj[0] = s_aSubVt;
    s_aRecVt[8] = (void*)RecDelete;  // +0x40
    s_aRecVt[0] = (void*)RecDtor;    // vt[0]
    s_aRec[0] = s_aRecVt;            // the record
    s_aMgrVt[0x3a0 / 8] = (void*)MgrQuery;
    s_aMgr[0] = s_aMgrVt;
    s_aMod[0] = s_aMgr;
}

int main() {
    BuildLeaveMocks();
    g_fnTailLogError = MockLog;
    g_fnTailInvalid = MockInvalid;
    g_fnTailThrowBadAlloc = MockBadAlloc;
    g_fnOpNew8 = MockOpNew8;
    g_fnOpDelete = MockOpDelete;   // the flow's frees
                                  // go through the
                                  // module-layer seam
    g_fnOpDelete = MockOpDelete;
    g_fnTailOpNew = MockTailOpNew;
    g_fnCMyHeapCtor = MockHeapCtor;
    g_fnTailAtexit = MockAtexit;
    g_fnCMyHeapAlloc = MockHeapAlloc;
    g_fnCMyHeapFree = MockHeapFree;
    g_fnCMyHeapIsValidPt = MockHeapValid;
    g_fnSendLeaveAward = MockSendLeaveAward;

    // ---- D58-1: the checked-set pair ----
    {
        void* p = nullptr;
        assert(SetPtrCheckA(&p, nullptr) == 0);
        assert(g_nLog == 1);
        int x = 5;
        assert(SetPtrCheckA(&p, &x) == 1);
        assert(p == &x);
        void* q = nullptr;
        assert(SetPtrCheckB(&q, nullptr) == 0);
        assert(g_nLog == 2);
        assert(SetPtrCheckB(&q, &x) == 1);
        assert(q == &x);
        printf("D58-1 the checked-set pair ok\n");
    }

    // ---- D58-2: the scalar dtor + the static buf -
    // ---- (FreeStaticBuf works the DAT slot via
    // a single static; exercised through the
    // module-level API — the nullptr paths) ----
    {
        g_aDeleted.clear();
        int y = 7;
        assert(ScalarDtorDel(&y, 0) == &y);
        assert(g_aDeleted.size() == 0);
        void* p = malloc(8);
        void* pSnap = p;
        ScalarDtorDel(p, 1);
        assert(g_aDeleted.size() == 1);
        assert(g_aDeleted[0] == pSnap);
        printf("D58-2 the scalar dtor ok\n");
    }

    // ---- D58-3: CallNTimes ----
    {
        static int nCalls = 0;
        static void* s_pLast;
        auto fn = [](void* p) {
            ++nCalls; s_pLast = p;
        };
        char base[0x30];
        CallNTimes(base, 0x10, 3, fn);
        assert(nCalls == 3);
        assert(s_pLast == base + 0x20);
        printf("D58-3 the array loop ok\n");
    }

    // ---- D58-4: Vec4At ----
    {
        // the container: +0x18 begin, +0x20 end
        struct { void* pad[3]; int32_t* pBeg;
                int32_t* pEnd; } v;
        static int32_t s_a[4] = {10, 20, 30, 40};
        v.pBeg = s_a; v.pEnd = s_a + 4;
        assert(*(int32_t*)Vec4At(&v, 2) == 30);
        assert(g_nInvalid == 0);
        Vec4At(&v, 4);   // end is exclusive ->
        assert(g_nInvalid == 1);   // invalid
        printf("D58-4 the stride-4 at ok\n");
    }

    // ---- D58-5: the stride-0x14 family ----
    {
        // the container mirror: +0x18 begin,
        // +0x20 end (the vector data)
        static char s_aData[5][0x14];
        char c[0x30];
        memset(c, 0, sizeof c);
        *(void**)(c + 0x18) = s_aData;
        *(void**)(c + 0x20) =
            (char*)s_aData + 4 * 0x14;
        // the proxy: [0] = the container, and the
        // iterator = {proxy, cursor}
        static void* s_aProxy[2];
        s_aProxy[0] = c;
        void* it[2] = { s_aProxy, ((char*)s_aData + 0x14) };
        // deref
        assert(Vec14Deref(it) == ((char*)s_aData + 0x14));
        assert(Vec14DerefB(it) == ((char*)s_aData + 0x14));
        // next
        assert(Vec14Next(it) == it);
        assert(it[1] == ((char*)s_aData + 0x28));
        assert(Vec14NextB(it) == it);
        assert(it[1] == ((char*)s_aData + 0x3c));
        // eq/diff
        void* it2[2] = { s_aProxy, ((char*)s_aData + 0x14) };
        assert(Vec14Eq(it, it2) == 0);
        assert(Vec14Diff(it, it2) == 2);
        assert(Vec14DiffB(it2, it) == -2);
        // advance (within bounds)
        assert(Vec14Advance(it2, 2) == it2);
        assert(it2[1] == ((char*)s_aData + 0x3c));
        assert(Vec14Advance(it2, 1) == it2);
        assert(it2[1] == (char*)s_aData + 4*0x14);
        assert(g_nInvalid == 1);   // no new faults
        // OOB advance (past end)
        Vec14Advance(it2, 1);
        assert(g_nInvalid == 2);
        // a null proxy deref
        void* itBad[2] = { nullptr, nullptr };
        Vec14Deref(itBad);
        assert(g_nInvalid == 3);
        // the eq identity fault
        void* itX[2] = { s_aProxy, nullptr };
        void* itY[2] = { nullptr, nullptr };
        Vec14Eq(itX, itY);
        assert(g_nInvalid == 4);
        printf("D58-5 the stride-0x14 family ok\n");
    }

    // ---- D58-6: Vec14New ----
    {
        g_nBadAlloc = 0;
        void* p = Vec14New(3);
        assert(g_nBadAlloc == 0);
        assert(g_nLastAlloc == 3 * 0x14);
        free(p);
        // (> max -> the throw fires BEFORE the
        // op_new, so no allocation happens)
        g_fnTailOpNew = [](size_t) -> void* {
            return nullptr;   // unreachable anyway
        };
        Vec14New(~0ull / 8);
        assert(g_nBadAlloc == 1);
        g_fnTailOpNew = MockTailOpNew;
        printf("D58-6 the checked new ok\n");
    }

    // ---- D58-7: the meed heap family ----
    {
        g_nHeapCtor = 0; g_nAtexit = 0;
        g_bMeedHeapInit = 0;
        void* p = MeedHeapAlloc(0x20);
        assert(g_nHeapCtor == 1);
        assert(g_nAtexit == 1);
        assert(g_nHAlloc == 1);
        assert(p != nullptr);
        MeedHeapFree(p);
        assert(g_nHFree == 1);
        assert(MeedHeapValid(p) == 1);
        assert(g_nHValid == 1);
        free(p);   // (the valid-mock reads only)
        // the init flag short-circuits
        void* p2 = MeedHeapAlloc(4);
        assert(g_nHeapCtor == 1);
        assert(g_nAtexit == 1);
        free(p2);
        printf("D58-7 the meed heap ok\n");
    }

    // ---- D58-8: LeaveAwardFlow E2E ----
    {
        g_nLog = 0;
        uint64_t uRet = LeaveAwardFlow(s_aMod, 0x77);
        assert(uRet == 1);
        assert(s_nQuery == 1);
        assert(g_uSendId == 0x77);
        assert(g_nSendMoney == (int)0x100);
        assert(g_nSendEMoney == (int)0x200);
        assert(g_nSendType == (int)0x300);
        assert(s_nRecDtor == 1);
        assert(g_nLog == 0);
        // Delete fails -> the log, no send
        s_cDeleteOk = 0;
        s_nRecDtor = 0;
        LeaveAwardFlow(s_aMod, 0x77);
        assert(g_nLog == 1);
        assert(s_nRecDtor == 1);   // dtor still runs
        assert(g_uSendId == 0x77); // not re-sent
        s_cDeleteOk = 1;
        // the send fails -> the log
        g_cSendOk = 0;
        LeaveAwardFlow(s_aMod, 0x78);
        assert(g_nLog == 2);
        assert(s_nRecDtor == 2);
        g_cSendOk = 1;
        // a null record entry is skipped
        s_pVecFill = 1;
        LeaveAwardFlow(s_aMod, 0x79);
        assert(g_nLog == 2);
        assert(s_nRecDtor == 2);
        s_pVecFill = 0;
        // an empty vector
        s_pVecFill = 2;
        LeaveAwardFlow(s_aMod, 0x7a);
        assert(g_nLog == 2);
        s_pVecFill = 0;
        printf("D58-8 the leave-award flow ok\n");
    }


    // ---- D58-9: the REAL SendLeaveAward wired ----
    {
        // the mock mgr slots
        static int s_nEmoney = 0;
        static int s_nSyn = 0x55;
        static char s_szName[8] = "tester";
        static char s_cDel = 1;
        static int s_nCap = 1000;
        static void* s_pBufB =
            (void*)(uintptr_t)0x1000;
        static void* s_pBufE =
            (void*)(uintptr_t)(0x1000 + 0x40);
        static int s_nLastGain; static int s_nLastCb;
        static char s_cDelLast1;
        static int64_t s_nLastMoneyGain;
        static char s_cAddLast1;
        g_fnMgrGetEmoney = [](void*, uint32_t) {
            return s_nEmoney; };
        g_fnMgrGetBuf = [](void*, uint32_t) {
            return s_pBufB; };
        g_fnMgrDeleteRecord = [](void*, uint32_t a,
            uint32_t, int nGain, int cb, char b) {
            s_nLastGain = nGain; s_nLastCb = cb;
            s_cDelLast1 = b; (void)a;
            return s_cDel; };
        g_fnMgrGetSynId = [](void*, uint32_t) {
            return s_nSyn; };
        g_fnMgrGetName = [](void*, uint32_t) {
            return s_szName; };
        g_fnMgrGetBufEnd = [](void*) {
            return s_pBufE; };
        g_fnMgrAddMoney = [](void*, uint32_t,
            int64_t n, char b) {
            s_nLastMoneyGain = n;
            s_cAddLast1 = b; };
        s_aLeaveLogs.clear();
        g_fnLeaveLogError = MockLeaveLogError;
        g_fnLeaveGmLog = MockLeaveGmLog;
        g_nLeaveEmoneyCap = s_nCap;

        // type out of range
        assert(SendLeaveAward(s_aMod, 7, 0, 5, 5)
            == 0);
        assert(s_aLeaveLogs.size() == 1);
        s_aLeaveLogs.clear();
        // emoney type 2 -> cb 0x18, gain = min(
        // cap-emoney, requested)
        s_nEmoney = 900;   // cap-emoney = 100
        assert(SendLeaveAward(s_aMod, 7, 2, 0,
            500) == 1);
        assert(s_nLastGain == 100);
        assert(s_nLastCb == 0x18);
        assert(s_cDelLast1 == 1);
        // the emoney leg logged syndenote
        // partial gain (100 < 500) -> the overflow
        // log fires too: 3 logs total
        assert(s_aLeaveLogs.size() == 3);
        s_aLeaveLogs.clear();
        // gain fits -> no overflow log
        s_nEmoney = 600;
        SendLeaveAward(s_aMod, 7, 2, 0, 300);
        assert(s_nLastGain == 300);
        assert(s_aLeaveLogs.size() == 2);
        s_aLeaveLogs.clear();
        // the money leg: capped by the buf space
        SendLeaveAward(s_aMod, 7, 1, 0x100, 0);
        assert(s_nLastMoneyGain == 0x40);
        // partial (0x40 < 0x100): no 10000-branch;
        // summary + overflow = 2
        assert(s_aLeaveLogs.size() == 2);
        s_aLeaveLogs.clear();
        // money >= 0x2710 -> the extra syndenote
        SendLeaveAward(s_aMod, 7, 1, 0x2710, 0);
        assert(s_aLeaveLogs.size() == 3);
        s_aLeaveLogs.clear();
        // overflow: partial gain
        SendLeaveAward(s_aMod, 7, 3, 0x100, 0);
        assert(s_aLeaveLogs.size() == 2);   // summary+
        // overflow (0x40 < 0x100)
        s_aLeaveLogs.clear();
        // DeleteRecord fails -> the error log
        s_cDel = 0;
        SendLeaveAward(s_aMod, 7, 3, 0, 50);
        assert(s_aLeaveLogs.size() == 3);
        s_cDel = 1;
        s_aLeaveLogs.clear();
        // ---- E2E: the flow drives the real fn ----
        // rebind the module-tail seam to the port
        g_fnSendLeaveAward = [](void* p,
            uint32_t uId, int nT, int nM, int nE)
            -> char {
            return SendLeaveAward(p, uId, nT,
                                  nM, nE);
        };
        s_pVecFill = 0;   // one record (the mock
        // SubGet returns money 0x100, emoney 0x200,
        // type 0x300)
        uint64_t uR = LeaveAwardFlow(s_aMod, 9);
        assert(uR == 1);
        printf("D58-9 the real leave-award ok\n");
    }

    printf("SYNDICATE_D58_OK: the module tail\n");
    return 0;
}

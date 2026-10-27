// syndicate_d52_test — D52/T16: the SendMeedInfo
// flow (141780a30) + its callees: the score
// comparator (14177c970 — sub4@0x58*50000 +
// sub3@0x58 desc, tie → id asc), the grade
// comparator (14177c870 — grade desc → type
// desc → id asc), SortByMeed (14177d9b0 — the
// per-type lazy flag +0x90), GetCount
// (14177cd40), GetMeedList (14177dfe0 — the
// offset/span walk + the self capture), the
// self-rank CMsg family (1417d9f90/1417da210/
// 1417da420) and the requester-id seam
// (1417ac810).
#include "../modules/syndicate/src/SyndicateMeedInfo.h"
#include "../modules/syndicate/src/SyndicateMeedFlow.h"
#include "../modules/syndicate/src/SyndicateMeedSort.h"
#include "../modules/syndicate/src/SyndicateSynMeed.h"
#include "../modules/syndicate/src/SyndicateCrossMerit.h"
#include "../modules/syndicate/src/SyndicateModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace syndicate;

static int g_nInvalid = 0;
static void MockInvalid() { ++g_nInvalid; }
static int g_nLog = 0;
static void MockLog() { ++g_nLog; }

// the member: {id(sub2@0x40), type(sub3@0x48),
// grade(sub4@0x48), score fields @0x58}
struct Member {
    uint64_t id, type, grade, s4, s3;
};
static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    if (n == 2) return &m->id;
    if (n == 3) return &m->type;
    if (n == 4) return &m->grade;
    return &m->id;
}
static int SubId(void* pS) {
    return (int)((uint64_t*)pS)[0];
}
static int SubVal(void* pS) {
    return (int)((uint64_t*)pS)[0];
}
static int SubScore(void* pS) {
    return (int)((uint64_t*)pS)[0];
}

// the pool: 3 vectors x 0x30 + the anchor — the
// REAL ctor from D51 (with malloc seams)
static void* MockOpNew(size_t n) {
    void* p = malloc(n);
    memset(p, 0xcd, n);
    return p;
}
static void MockOpDelete(void* p) { free(p); }

static void* g_pSent = nullptr;
static void MockSend(void* a, void* b, void* c) {
    (void)a; (void)b;
    g_pSent = c;
    // freeze a copy for inspection
    static char copy[0x820];
    memcpy(copy, c, 0x820);
    g_pSent = copy;
}

static char* MockNameOf(void* pSvc, uint32_t uId) {
    (void)pSvc;
    static char buf[8][0x28];
    static int n = 0;
    char* p = buf[n++ % 8];
    snprintf(p, 0x28, "NAM%u", uId);
    return p;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedLog = MockLog;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubId;
    g_fnMeedSubNType = SubVal;
    g_fnMeedSubNScore = SubScore;
    g_fnMeedReqId = [](void*) -> int {
        return 0;   // default: no requester
    };
    g_fnMgrNameOfSvc = MockNameOf;
    g_fnMeedSendTarget = MockSend;
    g_fnMeritOpNew = MockOpNew;
    g_fnMeritOpDelete = MockOpDelete;

    // ---------- D52-1: the comparators ---------
    static Member a = { 100, 3, 90, 5, 2 };
    static Member b = { 200, 3, 80, 5, 2 };
    static Member c2 = { 150, 3, 80, 5, 2 };
    static Member d2 = { 300, 2, 99, 1, 1 };
    // score: 5*50000+2 equal → tie → id asc
    assert(MeedCmpScore(&a, &b) == true
        && "score tie: the smaller id first");
    assert(MeedCmpScore(&b, &a) == false);
    // nulls (verbatim)
    assert(!MeedCmpScore(nullptr, &a));
    assert(MeedCmpScore(&a, nullptr));
    // grade: a(90) > b(80) → a first
    assert(MeedCmpGrade(&a, &b) == true);
    assert(MeedCmpGrade(&c2, &b) == true
        && "grade tie → id asc (150 first)");
    assert(MeedCmpGrade(&b, &c2) == false);
    assert(MeedCmpGrade(&d2, &a) == true
        && "higher grade first even with lower"
           " type");
    printf("D52-1 the comparators ok\n");

    // ---------- D52-2: GetCount + SortByMeed ---
    char* pool = (char*)calloc(1, 0xd0);
    MeedPoolCtorReal(pool);
    // fill the type-1 vector with 6 members
    // (sorted keys: grade desc, tie id asc)
    static Member mem[6] = {
        { 1001, 3, 50, 0, 0 },
        { 1002, 3, 80, 0, 0 },
        { 1003, 3, 80, 0, 0 },
        { 1004, 3, 70, 0, 0 },
        { 1005, 3, 60, 0, 0 },
        { 1006, 3, 90, 0, 0 },
    };
    void** cells[6];
    for (int i = 0; i < 6; ++i) {
        cells[i] = (void**)&mem[i];
    }
    char* v1 = pool;   // the type-1 vector
    *(void**)(v1 + 0x18) = cells;
    *(void**)(v1 + 0x20) = cells + 6;
    *(void**)(v1 + 0x28) = cells + 6;
    *(void**)v1 = v1;   // the self proxy
    assert(MeedGetCount(pool, 1) == 6);
    assert(MeedGetCount(pool, 2) == 0);
    g_nLog = 0;
    assert(MeedGetCount(pool, 9) == 0
        && g_nLog == 1
        && "the bad-type count → the anchor"
           " fallback + log");
    // the flag starts 0 → SortByMeed sorts
    assert(*(uint8_t*)(pool + 0x90) == 0);
    MeedSortByType(pool, 1);
    assert(*(uint8_t*)(pool + 0x90) == 1
        && "the flag set after the sort");
    // verify: sorted by the GRADE comparator
    // (grade desc, tie → id asc)
    void** walk = *(void***)(v1 + 0x18);
    uint64_t prevG = 999;
    uint64_t prevId = 0;
    for (int i = 0; i < 6; ++i) {
        Member* m = (Member*)walk[i];
        assert(m->grade <= prevG);
        if (m->grade == prevG) {
            assert(m->id > prevId);
        }
        prevG = m->grade;
        prevId = m->id;
    }
    printf("D52-2 GetCount + SortByMeed ok\n");

    // ---------- D52-3: GetMeedList ------------
    int32_t ids[24];
    memset(ids, 0, sizeof(ids));
    int32_t selfA = 0, selfB = 0;
    // page 2 of type 1: offset 5, span 5
    int n = MeedGetList(pool, 0, ids, 1, 5, 5,
                        &selfA, &selfB);
    assert(n == 1 && "only 1 entry past offset 5");
    // the 6th (index 5) = the smallest grade
    assert(ids[0] == 1001
        && ids[1] == 3 && ids[2] == 50);
    // the self capture: requester 1002 in-page
    n = MeedGetList(pool, 1002, ids, 1, 0, 5,
                    &selfA, &selfB);
    assert(n == 5);
    assert(selfA == 3 && selfB == 80
        && "the self entry captured in-page");
    // the requester 1004 in the OUT-of-page scan
    // (offset 0 span 2 covers grades 90,80)
    selfA = 0; selfB = 0;
    n = MeedGetList(pool, 1004, ids, 1, 0, 2,
                    &selfA, &selfB);
    assert(n == 2);
    assert(selfA == 3 && selfB == 70
        && "the self entry found by the rescan");
    // a missing requester → no capture
    selfA = 77; selfB = 77;
    n = MeedGetList(pool, 4242, ids, 1, 0, 2,
                    &selfA, &selfB);
    assert(n == 2 && selfA == 77
        && "no capture for a missing requester");
    // the already-sorted flag skips re-sort
    assert(*(uint8_t*)(pool + 0x90) == 1);
    printf("D52-3 GetMeedList ok\n");

    // ---------- D52-4: the CMsg self family ---
    static char msg[0x820];
    memset(msg, 0, sizeof(msg));
    CMsgMemAwardRankCtor(msg);
    assert(CMsgSelfRankCreate(msg, 1, 42) == 1);
    char* hdr = *(char**)(msg + 0x408);
    assert(*(uint16_t*)hdr == 0x20
        && *(uint16_t*)(hdr + 2) == 0x427
        && "the size head + the msg id");
    assert(*(uint32_t*)(hdr + 6) == 1
        && "the type at +6");
    assert(*(uint32_t*)(hdr + 0xa) == 42
        && "the total at +10 DEC");
    // the self counts
    CMsgSelfRankCounts(msg, 3, 90);
    assert(*(int32_t*)(hdr + 0x12) == 90
        && *(int64_t*)(hdr + 0x16) == 3);
    // the entry append (0x34 each)
    int32_t e[3] = { 1001, 3, 50 };
    assert(CMsgSelfRankAppend(msg, e, "TEST")
        == 1);
    assert(*(uint16_t*)hdr == 0x54
        && "the size grew by 0x34");
    assert(*(int32_t*)(hdr + 0xe) == 1
        && "the entry count");
    // the entry body at hdr + 0x1e
    assert(*(int32_t*)(hdr + 0x1e + 0) == 50
        && "field2 (grade) at +0x1e");
    assert(*(int64_t*)(hdr + 0x22) == 3
        && "field1 (type) at +0x22");
    assert(strncmp(hdr + 0x2a, "TEST", 4) == 0
        && "the name at +0x2a");
    assert(*(int32_t*)(hdr + 0x4e) == 1001
        && "the id at +0x4e");
    // the 0x3ff size gate: fill until overflow
    // (0x20 + n*0x34 <= 0x3ff → n <= 23)
    int nAppended = 1;
    while (CMsgSelfRankAppend(msg, e, "X")
        == 1) {
        ++nAppended;
        if (nAppended > 40) {
            break;   // safety
        }
    }
    assert(nAppended <= 24
        && *(uint16_t*)hdr + 0x34 > 0x3ff
        && "the append stops at the 0x3ff gate");
    printf("D52-4 the CMsg self family ok\n");

    // ---------- D52-5: the flow E2E ----------
    // the flow's this: a holder → the target obj
    static void* fakeObj = (void*)0x1;
    static void* holder = &fakeObj;
    void* pThis = &holder;
    // the flow uses the GLOBAL pool: point it at
    // our populated one
    g_pMeedPool = pool;
    g_nLog = 0;
    // the bad type → log + false
    assert(MeedSendInfo(pThis, nullptr, 9, 1)
        == false && g_nLog == 1);
    // page 0 → false (no log)
    g_nLog = 0;
    assert(MeedSendInfo(pThis, nullptr, 1, 0)
        == false && g_nLog == 0);
    // the full type-1 flow: page 1 (5 entries)
    // — 6 members → 5 + 1 remainder, page 1
    // shows grades 90,80,80,70,60
    g_pSent = nullptr;
    assert(MeedSendInfo(pThis, nullptr, 1, 1)
        == true);
    assert(g_pSent != nullptr && "the msg sent");
    char* h =
        *(char**)((char*)g_pSent + 0x408);
    assert(*(uint32_t*)(h + 6) == 1);
    assert(*(uint32_t*)(h + 0xa) == 6
        && "the total = 6 (GetCount)");
    assert(*(int32_t*)(h + 0xe) == 5
        && "5 entries appended");
    // the first entry = the top grade 90 (id 1006)
    assert(*(int32_t*)(h + 0x4e) == 1006);
    assert(*(int32_t*)(h + 0x1e) == 90);
    // the requester seam: player 1002
    g_fnMeedReqId = [](void*) -> int {
        return 1002;
    };
    g_pSent = nullptr;
    assert(MeedSendInfo(pThis, nullptr, 1, 1)
        == true);
    h = *(char**)((char*)g_pSent + 0x408);
    assert(*(int64_t*)(h + 0x16) == 3
        && *(int32_t*)(h + 0x12) == 80
        && "the self rank captured in the flow");
    g_fnMeedReqId = [](void*) -> int {
        return 0;
    };
    // type 2: span 8, offset page*8-8
    g_pSent = nullptr;
    assert(MeedSendInfo(pThis, nullptr, 2, 1)
        == true);
    h = *(char**)((char*)g_pSent + 0x408);
    assert(*(int32_t*)(h + 0xe) == 8
        && "type 2 appends 8 slots (empty vec"
           " → zeros)");
    printf("D52-5 the flow E2E ok\n");

    printf(
      "SYNDICATE-D52-OK: the REAL SendMeedInfo"
      " flow (141780a30) + the score comparator"
      " (14177c970), the grade comparator"
      " (14177c870), SortByMeed (14177d9b0 with"
      " the +0x90 per-type lazy flag), GetCount"
      " (14177cd40), GetMeedList (14177dfe0 with"
      " the self capture + the rescan), the"
      " self-rank CMsg family (1417d9f90/"
      " 1417da210/1417da420) and the"
      " requester-id seam (1417ac810); the sort"
      " family now takes the comparator as a"
      " parameter (as the original ABI) — d50"
      " semantics preserved\n");
    return 0;
}

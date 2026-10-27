// syndicate_d47_test — D47/T16: the meed CMsg flow
// (SendMemberGrade 14177f700): the CMsg ctor/dtor +
// the 0x427 header encode + the 0x3c entry append,
// the pool lazy get, the grade-type counter
// (141778e60) and the full page flow (the gates, the
// empty page, the filled page, the send capture).
#include "../modules/syndicate/src/SyndicateMeedFlow.h"
#include "../modules/syndicate/src/SyndicateSynMeed.h"
#include "../modules/syndicate/src/SyndicateCrossMerit.h"
#include "../modules/syndicate/src/SyndicateModule.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace syndicate;

static int g_nInvalid = 0, g_nLog = 0;
static void MockInvalid() { ++g_nInvalid; }
static void MockLog() { ++g_nLog; }
static int g_nOpNew = 0;
static void* CountNew(size_t n) {
    ++g_nOpNew; return malloc(n ? n : 1);
}

// ---------- the meed map fixture (as d45) ----------
struct Member { uint64_t id, type, grade; };
static void* MemSub(void* pM, int n) {
    Member* m = (Member*)pM;
    return (n == 2) ? &m->id : &m->type;
}
static int SubNId(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static int SubNType(void* pS) {
    return (int)(((uint64_t*)pS)[0] & 0xffffffff);
}
static void* Sub4(void* pM) { return &((Member*)pM)->grade; }
static uint64_t Sub4Val(void* pS) {
    return ((uint64_t*)pS)[0];
}
struct League {
    void* pad0; void* dbg; void* pad2; void* pad3;
    void** begin; void** end;
};
static char* NodeAlloc() {
    return (char*)calloc(1, 0x2a);
}
static char* g_head;
static char* Node(uint32_t key, void* league, int black) {
    char* n = NodeAlloc();
    *(char**)n = g_head;
    *(char**)(n + 8) = g_head;
    *(char**)(n + 0x10) = g_head;
    *(uint32_t*)(n + 0x18) = key;
    *(void**)(n + 0x20) = league;
    *(uint8_t*)(n + 0x28) = black ? 1 : 0;
    return n;
}

// ---------- the mocks ----------
static void* g_pLgFixture = nullptr;
static void* g_mgr = (void*)0x999;
static int MockMgrUserId(void* m) {
    assert(m == g_mgr); return 0x50;
}
static char* MockMgrName(void* m, uint32_t id) {
    assert(m == g_mgr);
    static char names[4][16];
    int i = (int)id;
    snprintf(names[i], 16, "user%d", i);
    return names[i];
}
static int g_nListFill = 0;
static int g_fillA = 0, g_fillB = 0;
static void MockListFill(void* p, int* a, int* b,
                         uint32_t id, int t) {
    assert(p != nullptr);
    assert(id == 0x50);
    assert(t == 2);
    ++g_nListFill;
    *a = g_fillA; *b = g_fillB;
}
static int g_pageRet = 0;
static int g_nPage = 0;
static int MockGradePage(void* pL, uint64_t u,
                         int32_t* pOut, int t,
                         int limit, int stride) {
    assert(pL == g_pLgFixture);
    assert(u == 0x777);
    assert(t == 2);
    ++g_nPage;
    // (page 2 of stride 8: limit = 8)
    assert(limit == 8);
    assert(stride == 8);
    if (g_pageRet == 2) {
        pOut[0] = 1; pOut[1] = 11; pOut[2] = 0;
        pOut[3] = 22; pOut[4] = 33;
        pOut[5] = 2; pOut[6] = 12; pOut[7] = 0;
        pOut[8] = 23; pOut[9] = 44;
    }
    return g_pageRet;
}
static void* g_sentObj = nullptr;
static void* g_sentData = nullptr;
static char g_sentMsg[8320];
static int g_nSend = 0;
static void MockSend(void* obj, void* data, void* msg) {
    g_sentObj = obj; g_sentData = data;
    memcpy(g_sentMsg, msg, sizeof(g_sentMsg));
    ++g_nSend;
}
static void* g_userProxyObj = (void*)0x888;

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedLog = MockLog;
    g_fnMeritOpNew = CountNew;
    g_fnMeritOpDelete = [](void* p) { free(p); };
    g_fnGetServiceInst = []() { return g_mgr; };
    g_fnMgrUserId = MockMgrUserId;
    g_fnMgrNameOf = MockMgrName;
    g_fnMeedListFill = MockListFill;
    g_fnMeedGradePage = MockGradePage;
    g_fnMeedSend = MockSend;
    g_fnMeedMemSub = MemSub;
    g_fnMeedSubNId = SubNId;
    g_fnMeedSubNType = SubNType;
    g_fnMeedSub4 = Sub4;
    g_fnMeedSub4Val = Sub4Val;
    // the user proxy: *proxy = the user object
    static void* userProxy[1] = { g_userProxyObj };

    // ---------- D47-1: the CMsg ctor/dtor ----------
    char buf[8320];
    memset(buf, 0xAB, sizeof(buf));
    CMsgMemAwardRankCtor(buf);
    assert(*(void**)buf == g_pMsgMemAwardRankVft
        && "the ctor ends on the DERIVED vft");
    assert(*(void**)(buf + 0x408) == buf + 8
        && "the anchor = msg+8");
    CMsgMemAwardRankDtor(buf);
    assert(*(void**)buf == g_pTqCMsgVft
        && "the dtor ends on the base vft");
    printf("D47-1 the CMsg ctor/dtor ok\n");

    // ---------- D47-2: the header encode ----------
    memset(buf, 0xAB, sizeof(buf));
    *(void**)(buf + 0x408) = buf + 8;
    int rc = CMsgMemAwardRankHead(buf, 2, 5,
                                 0x1122, 0x33);
    assert(rc == 1);
    char* h = buf + 8;
    assert(*(uint16_t*)(h + 2) == 0x427);
    assert(*(uint16_t*)h == 0x20);
    assert(*(uint16_t*)(h + 4) == 1);
    assert(*(uint32_t*)(h + 6) == 2);
    assert(*(uint32_t*)(h + 0xe) == 0);
    assert(*(uint32_t*)(h + 0xa) == 5);
    assert(*(uint64_t*)(h + 0x16) == 0x1122);
    assert(*(uint32_t*)(h + 0x12) == 0x33);
    printf("D47-2 the header encode ok\n");

    // ---------- D47-3: the entry append ----------
    int32_t e1[5] = { 1, 11, 0, 22, 33 };
    rc = CMsgMemAwardRankAppend(buf, e1, "user11");
    assert(rc == 1);
    assert(*(uint16_t*)h == 0x20 + 0x3c
        && "the size grew by 0x3c");
    assert(*(uint32_t*)(h + 0xe) == 1
        && "the entry count");
    // entry0 at h+0x1e
    assert(*(uint32_t*)(h + 0x1e) == 1);
    assert(*(uint32_t*)(h + 0x22) == 0);
    assert(*(uint32_t*)(h + 0x26) == 33);
    assert(*(uint64_t*)(h + 0x2a) == 22);
    assert(*(uint32_t*)(h + 0x32) == 11);
    assert(strncmp(h + 0x36, "user11", 6) == 0);
    // a second entry (no name)
    int32_t e2[5] = { 2, 12, 0, 23, 44 };
    rc = CMsgMemAwardRankAppend(buf, e2, nullptr);
    assert(rc == 1 && *(uint32_t*)(h + 0xe) == 2);
    assert(*(uint32_t*)(h + 0x10 + 0x3c + 6)
        == *(uint32_t*)(h + 0x16 + 0x3c) && "");
    // (entry1's fields)
    assert(*(uint32_t*)(h + 0x1e + 0x3c) == 2);
    assert(*(uint32_t*)(h + 0x32 + 0x3c) == 12);
    assert(*(uint64_t*)(h + 0x36 + 0x3c) == 0
        && "the name slot zeroed");
    printf("D47-3 the entry append ok\n");

    // ---------- D47-4: the pool lazy get ----------
    MeedPoolReset();
    g_nOpNew = 0; g_nLog = 0;
    g_fnMeedPoolCtor = [](void* p) -> void* {
        return p; };
    void* pool = MeedPoolGet();
    assert(pool != nullptr && g_nOpNew == 1
        && g_nLog == 0);
    assert(MeedPoolGet() == pool && g_nOpNew == 1);
    // the ctor fail → the log
    MeedPoolReset();
    g_fnMeedPoolCtor = [](void*) -> void* {
        return nullptr; };
    assert(MeedPoolGet() == nullptr);
    assert(g_nLog == 1);
    g_fnMeedPoolCtor = [](void* p) -> void* {
        return p; };
    printf("D47-4 the pool lazy get ok\n");

    // ---------- D47-5: the grade-type counter -----
    // (three members on the league fixture: types
    // 2, 2, 3)
    static Member mem[3] = {
        { 0x9911, 2, 100 }, { 0x9912, 2, 200 },
        { 0x9913, 3, 300 } };
    static void* cells[3] = { &mem[0], &mem[1],
                              &mem[2] };
    static void* dbgC[8] = { nullptr };
    dbgC[0] = dbgC; dbgC[4] = &cells[3];
    League lg = { nullptr, &dbgC[0], nullptr,
                  nullptr, &cells[0], &cells[3] };
    g_pLgFixture = &lg;
    g_nInvalid = 0;
    assert(MeedGradeTypeCount(&lg, 2) == 2);
    assert(MeedGradeTypeCount(&lg, 3) == 1);
    assert(MeedGradeTypeCount(&lg, 1) == 0);
    assert(g_nInvalid == 0);
    printf("D47-5 the grade-type counter ok\n");

    // ---------- D47-6: the full flow ----------
    // wire the league into the meed singleton
    MeedResetSingleton();
    char* mc = (char*)MeedSingletonGet();
    g_head = *(char**)(mc + 0x30);
    char* r = Node(0x50, &lg, 1);
    *(char**)(g_head + 8) = r;
    *(char**)g_head = r;
    *(char**)(g_head + 0x10) = r;
    *(char**)r = g_head;
    *(char**)(r + 8) = g_head;
    *(char**)(r + 0x10) = g_head;
    *(uint64_t*)(mc + 0x38) = 1;

    // the type gate
    g_nLog = 0;
    assert(MeedSendMemberGrade(&userProxy[0], 0x777,
                               4, 1)
        == 0);
    assert(g_nLog == 1);
    // the page gate
    assert(MeedSendMemberGrade(&userProxy[0], 0x777,
                               2, 0)
        == 0);
    // the id not in the map → 0 (no send)
    g_nSend = 0;
    // (the id 0x50 IS in the map — build the miss
    //  via a type absent league? the miss path:
    //  unmap the id)
    *(uint32_t*)(r + 0x18) = 0x99;
    assert(MeedSendMemberGrade(&userProxy[0], 0x777,
                               2, 1)
        == 0);
    assert(g_nSend == 0);
    *(uint32_t*)(r + 0x18) = 0x50;

    // the empty page (page query returns 0)
    g_pageRet = 0; g_nSend = 0; g_nPage = 0;
    assert(MeedSendMemberGrade(&userProxy[0], 0x777,
                               2, 2)
        == 1);
    assert(g_nPage == 1 && g_nSend == 1);
    assert(g_sentObj == g_userProxyObj
        && g_sentData == (void*)0x777);
    char* sh = g_sentMsg + 8;
    assert(*(uint16_t*)(sh + 2) == 0x427);
    assert(*(uint32_t*)(sh + 6) == 2
        && "the type");
    assert(*(uint32_t*)(sh + 0xa) == 2
        && "the count = the type counter (2)");
    assert(*(uint32_t*)(sh + 0xe) == 0
        && "no entries appended");
    assert(g_nInvalid == 0);

    // the filled page (2 entries)
    g_pageRet = 2; g_nSend = 0;
    assert(MeedSendMemberGrade(&userProxy[0], 0x777,
                               2, 2)
        == 1);
    assert(g_nSend == 1);
    sh = g_sentMsg + 8;
    assert(*(uint32_t*)(sh + 0xe) == 2
        && "two entries appended");
    assert(*(uint32_t*)(sh + 0x1e) == 1);
    assert(*(uint32_t*)(sh + 0x32) == 11);
    assert(strncmp(sh + 0x36, "user11", 6) == 0
        && "the name from the mgr lookup");
    assert(*(uint32_t*)(sh + 0x1e + 0x3c) == 2);
    assert(strncmp(sh + 0x36 + 0x3c, "user12", 6)
        == 0);
    assert(*(uint16_t*)sh == 0x20 + 2 * 0x3c
        && "the size = 0x20 + 2×0x3c");
    assert(g_nInvalid == 0 && g_nLog == 1);
    // (the type-gate log above)
    printf("D47-6 the full flow ok\n");

    printf(
      "SYNDICATE-D47-OK: the SendMemberGrade CMsg flow"
      " REAL - the 0x427 header encode + the 0x3c"
      " entry append + the count/size bookkeeping, the"
      " pool lazy get, the grade-type counter (the"
      " vt+8 sub(3) protocol) and the full page flow"
      " (the gates, the miss, the empty page, the"
      " filled page, the send capture); 14177cdc0 +"
      " 141779f40 stay seams for D48/D49\n");
    return 0;
}

// tests/syndicate_d71_test.cpp — the syndicate::
// CMsgLeagueRobOpt family (0xa52), unit D71: the wrapper
// ctor (reused from SyndicateCMsgCtors), the dtor/deleting
// dtor, Create, Clear, Serialize (the two failure logs),
// the CreateBufMsg parse (wire check, buf skip, the failure
// logs), GetCount/GetEntry, GetOrAddEntry (reuse + grow
// via the shared Reserve), AppendDword (+4 gate),
// AppendDwordString (+0x24 gate, the 0x10 capped str1,
// the EMPTY str2 skip), the entry SetStr1/SetStr2 lazy
// slots, the entry ctor/dtor/copy ctor/New, Swap,
// CopyFrom (the CHECK FATAL + the 3 has-bit merges + the
// inline append tail), and the PB dtor's allocated-bound
// loop with the operator delete[] elements array.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptClass.h"
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRob.h"
#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using namespace syndicate;

static int g_fail = 0;
#define CHECK(cond, name) do { \
    if (cond) printf("  ok  %s\n", name); \
    else { printf("  FAIL %s\n", name); g_fail = 1; } \
} while (0)
#define SECT(n) printf("== %s ==\n", n)

// ================= the recorders =================
static std::vector<std::string> g_calls;
static void C(const std::string& s) { g_calls.push_back(s); }
static bool Has(const std::string& s) {
    for (auto& x : g_calls)
        if (x.find(s) != std::string::npos) return true;
    return false;
}
static int CountTag(const std::string& s) {
    int n = 0;
    for (auto& x : g_calls) if (x == s) ++n;
    return n;
}
static void Reset() { g_calls.clear(); }

// ================= the seams =================
static int   g_nInit = 0;
static void  FakeTqInit(void*) { ++g_nInit; }
static void  FakeOpNew_rec(size_t n) { (void)n; }
static void* FakeOpNew(size_t n) {
    void* p = calloc(1, n + 16);
    C("opnew:" + std::to_string(n));
    return p;
}
static std::vector<void*> g_freed;
static void  FakeOpDel(void* p) {
    C("opdel"); g_freed.push_back(p); free(p);
}
static void  FakeOpDelArr(void* p) { C("opdelarr"); free(p); }
static void  FakePbDefaultInit() { C("pbdefaultinit"); }
static char  g_serOk = 1;
static char  FakeSerialize(void*, void*, size_t cap) {
    C("ser:cap=" + std::to_string(cap));
    return g_serOk;
}
static char  g_parseOk = 1;   // the 1417dedc0 model
static int   g_parseLen = -1;
static char  FakeParse(void*, const void* p, int n) {
    (void)p; g_parseLen = n;
    C("parse:len=" + std::to_string(n));
    return g_parseOk;
}
static const int* FakeIntMax(const int* a, const int* b) {
    return (*a >= *b) ? a : b;
}
static const int s_floor = 4;   // DAT_14183f028 model
static void  FakePbBaseDtor(void*) { C("pbbasedtor"); }
static void  FakeLog2(const void* fmt, const char* s) {
    char z[32]; snprintf(z, 32, "%llx",
        (unsigned long long)(uintptr_t)fmt);
    C("log2:" + std::string(z) + ":" +
      std::string(s ? s : "(null)"));
}
static void  FakeLog1(const void* fmt) {
    char z[32]; snprintf(z, 32, "%llx",
        (unsigned long long)(uintptr_t)fmt);
    C("log1:" + std::string(z));
}
// the CHECK FATAL machinery (1417e0d30/90/e0/da0)
static void* FakeCheckBuild(void* b, int lvl, const void*,
                            int line) {
    C("chk:build:" + std::to_string(lvl) + ":" +
      std::to_string(line));
    return b;
}
static void* FakeCheckText(void* m, const void*) {
    // the raw text pointer is a VA constant — record
    // the fixed tag only (no dereference)
    C("chk:text:CHECK failed");
    return m;
}
static void  FakeCheckStream(void*, void*) { C("chk:stream"); }
static void  FakeCheckDone(void*) { C("chk:done"); }

// ---- the PB vt fakes ----
static uint64_t g_cachedSize = 0x20;
static uint64_t FakeGetCachedSize(void*) {
    return g_cachedSize;
}
static char g_isInit = 0;
static char FakeIsInit(void*) { return g_isInit; }
static char g_errInline = 1;
static char g_errHeap[64] = "heap-error-string";
static uint64_t FakeErrString(void*, void* pOut) {
    char* p = (char*)pOut;
    if (g_errInline) {
        *(uint64_t*)(p + 0x20) = 5;
        memcpy(p + 8, "abcde", 6);
    } else {
        *(uint64_t*)(p + 0x20) = 0x11;
        *(uint64_t*)(p + 8) =
            (uint64_t)(uintptr_t)g_errHeap;
    }
    return (uint64_t)(uintptr_t)pOut;
}
static int  g_nClear = 0;
static void FakePbClear(void*) { ++g_nClear; }

// ---- the entry deleting dtor (vt[0] with flags 1) ----
static int g_nEntryDel = 0;
static void FakeEntryDeletingDtor(void* p, uint64_t f) {
    ++g_nEntryDel;
    C("entrydel:" + std::to_string(f));
    EntryDtorLeagueRobOptServer(p);   // the REAL dtor
    free(p);
}

// ---- the fake vtables ----
static void* s_vtPb[16];       // the PB object vtable
static void* s_vtEntry[2];     // the entry vtable

static void WireSeams() {
    g_pTqCMsgVft = (void*)0x111;
    g_pVtPbMessageLite = (void*)0x222;
    g_pVtCMsgLeagueRobOpt = (void*)0x333;
    g_pVtCMsgLeagueRobOptPB = s_vtPb;
    g_pVtCMsgLeagueRobOptServer = s_vtEntry;
    g_pPbDefaultInstance = (void*)0x666;
    g_fnTqCMsgInit = FakeTqInit;
    g_fnOpNew = FakeOpNew;
    g_fnOpDelete = FakeOpDel;
    g_fnOpDeleteArr = FakeOpDelArr;
    g_fnPbDefaultInit = FakePbDefaultInit;
    g_fnPbSerializeToArray = FakeSerialize;
    g_fnPbParseFromArray = FakeParse;
    g_fnPbIntMax = FakeIntMax;
    g_pPbReserveFloor = &s_floor;
    g_fnPbBaseDtor = FakePbBaseDtor;
    g_fnLogRobOptErr = FakeLog2;
    g_fnLogRobOptFail = FakeLog1;
    g_fnPbCheckBuild = FakeCheckBuild;
    g_fnPbCheckText = FakeCheckText;
    g_fnPbCheckStream = FakeCheckStream;
    g_fnPbCheckDone = FakeCheckDone;

    s_vtPb[3] = (void*)FakePbClear;
    s_vtPb[4] = (void*)FakeIsInit;
    s_vtPb[5] = (void*)FakeErrString;
    s_vtPb[8] = (void*)FakeGetCachedSize;
    s_vtEntry[0] = (void*)FakeEntryDeletingDtor;
}

// the raw wrapper size (local_5a8 in FUN_14176b0d0)
static const size_t MSG = 0x460;

int main() {
    WireSeams();

    // ========= ctor / PB layout =========
    SECT("D71-ctor");
    {
        char* ab = (char*)calloc(1, MSG);
        memset(ab, 0xCD, MSG);
        Reset(); g_nInit = 0;
        CtorCMsgLeagueRobOpt(ab);
        CHECK(g_nInit == 2, "ctor runs tq Init TWICE");
        CHECK(*(void**)ab == (void*)0x333,
              "ctor final vptr = CMsgLeagueRobOpt");
        char* pb = ab + 0x408;
        CHECK(*(void**)pb == (void*)s_vtPb,
              "PB vptr = the class vtable");
        CHECK(*(uint32_t*)(pb + 0x30) == 0,
              "PB has-bits zeroed");
        CHECK(*(uint64_t*)(pb + 0x40) == 0 &&
              *(uint32_t*)(pb + 0x48) == 0 &&
              *(uint32_t*)(pb + 0x4c) == 0 &&
              *(uint32_t*)(pb + 0x50) == 0,
              "PB repeated field zeroed (0x40..0x50)");
        CHECK(*(uint32_t*)(pb + 0x34) == 0 &&
              *(uint32_t*)(pb + 0x38) == 0 &&
              *(uint32_t*)(pb + 0x3c) == 0,
              "PB cached/f1/f2 zeroed");
        CHECK(!Has("pbdefaultinit"),
              "RobOpt PB ctor does NOT call the default "
              "init (unlike D69's)");
        std::string* pEmbedded = (std::string*)(pb + 8);
        CHECK(pEmbedded->empty(), "PB +0x08 string empty");
        DtorCMsgLeagueRobOpt(ab);
        CHECK(Has("pbbasedtor"), "dtor reaches the PB dtor");
        CHECK(Has("opdelarr"), "dtor frees the (null) "
              "elements array with delete[]");
        CHECK(*(void**)ab == (void*)0x111,
              "msg dtor restores the tq vptr");
        free(ab);
    }

    // ========= the entry class =========
    SECT("D71-entry");
    {
        char* e = (char*)calloc(1, 0x50);
        Reset();
        EntryCtorLeagueRobOptServer(e);
        CHECK(*(void**)e == (void*)s_vtEntry,
              "entry vptr = the class vtable");
        CHECK(Has("pbdefaultinit"), "entry ctor calls "
              "1417e8050 (the PB default init)");
        CHECK(*(void**)(e + 0x38) == (void*)0x666 &&
              *(void**)(e + 0x40) == (void*)0x666,
              "str1/str2 slots = default instance");
        CHECK(*(uint32_t*)(e + 0x30) == 0 &&
              *(uint32_t*)(e + 0x34) == 0 &&
              *(uint32_t*)(e + 0x48) == 0,
              "has-bits/cached/value zeroed");
        CHECK(((std::string*)(e + 8))->empty(),
              "entry +0x08 string empty");
        CHECK(EntryGetCachedLeagueRobOptServer(e) == 0,
              "entry +0x34 read");

        // New (1417efd70): op_new(0x50) + ctor
        Reset(); g_nEntryDel = 0;
        void* p = EntryNewLeagueRobOptServer();
        CHECK(p != nullptr && Has("opnew:80"),
              "entry New: op_new(0x50)");
        EntryDeletingHelperRobOpt(p);   // 1417efb90
        CHECK(g_nEntryDel == 1, "deleting helper fires "
              "vt[0](,1) once");
        // p was already freed by the helper's fake
        // deleting dtor — do NOT free again

        // SetStr1/SetStr2: the lazy slots
        Reset();
        SetStr1EntryRobOpt(e, "alpha", 5);
        std::string* s1 = *(std::string**)(e + 0x38);
        CHECK(s1 != (std::string*)0x666 && *s1 == "alpha",
              "SetStr1: lazy slot assigned 'alpha'");
        CHECK(*(uint32_t*)(e + 0x30) == 2, "has-bits |= 2");
        CHECK(CountTag("opnew:40") == 1,
              "SetStr1 allocated one 0x28 slot");
        Reset();
        SetStr1EntryRobOpt(e, "beta", 4);   // slot exists
        CHECK(!Has("opnew:40") && *s1 == "beta",
              "SetStr1 reuse: no new slot, reassigned");

        Reset();
        SetStr2EntryRobOpt(e, "gamma", 5);
        std::string* s2 = *(std::string**)(e + 0x40);
        CHECK(s2 != (std::string*)0x666 && *s2 == "gamma",
              "SetStr2: lazy slot assigned 'gamma'");
        CHECK((*(uint32_t*)(e + 0x30) & 4) != 0,
              "has-bits |= 4");

        // dtor: frees BOTH heap strings (scalar delete)
        Reset();
        EntryDtorLeagueRobOptServer(e);
        CHECK(CountTag("opdel") == 2, "entry dtor "
              "scalar-deletes both strings");
        CHECK(Has("pbbasedtor"), "entry dtor tail = "
              "the base dtor");
        free(e);
    }

    // ========= CopyFrom + Swap =========
    SECT("D71-copyfrom");
    {
        char* a = (char*)calloc(1, 0x50);
        char* b = (char*)calloc(1, 0x50);
        EntryCtorLeagueRobOptServer(a);
        EntryCtorLeagueRobOptServer(b);
        // from b: value + str1 + str2 + the inline append
        *(uint32_t*)(b + 0x30) = 1 | 2 | 4;
        *(uint32_t*)(b + 0x48) = 777;
        // placement-new over malloc so the raw dtor's
        // scalar op_delete seam (free-based in this
        // test) deallocates consistently
        void* m1 = malloc(32);
        *(void**)(b + 0x38) = new (m1) std::string("s1-src");
        void* m2 = malloc(32);
        *(void**)(b + 0x40) = new (m2) std::string("s2-src");
        ((std::string*)(b + 8))->assign("inline-src");

        Reset();
        EntryCopyFromLeagueRobOptServer(a, b);
        CHECK(*(uint32_t*)(a + 0x48) == 777 &&
              (*(uint32_t*)(a + 0x30) & 1) != 0,
              "CopyFrom bit0: value copied");
        CHECK(*(std::string**)(a + 0x38) !=
                  (std::string*)0x666 &&
              **(std::string**)(a + 0x38) == "s1-src",
              "CopyFrom bit1: str1 merged (assign)");
        CHECK(**(std::string**)(a + 0x40) == "s2-src",
              "CopyFrom bit2: str2 merged (assign)");
        CHECK(((std::string*)(a + 8))->find(
                  "inline-src") != std::string::npos,
              "CopyFrom tail: inline string appended");
        CHECK(!Has("chk:build"), "no CHECK fired "
              "(a != b)");

        // the CHECK FATAL path (this == from)
        Reset();
        EntryCopyFromLeagueRobOptServer(a, a);
        CHECK(Has("chk:build:3:288"),
              "CHECK FATAL: build(3, file, 0x120=288)");
        CHECK(Has("chk:text:CHECK failed"),
              "CHECK FATAL: the message text");
        CHECK(Has("chk:done"), "CHECK FATAL: destroyed");

        // copy ctor (1417efc50): ctor + CopyFrom
        char* c = (char*)calloc(1, 0x50);
        memset(c, 0xCD, 0x50);
        Reset();
        EntryCopyCtorLeagueRobOptServer(c, b);
        CHECK(*(uint32_t*)(c + 0x48) == 777 &&
              **(std::string**)(c + 0x38) == "s1-src",
              "copy ctor: fields copied");
        CHECK(*(void**)c == (void*)s_vtEntry,
              "copy ctor builds the real class vt");

        // Swap (1417efdb0): the pairwise swaps
        *(uint32_t*)(a + 0x34) = 11;
        *(uint32_t*)(c + 0x34) = 22;
        void *sa1 = *(void**)(a + 0x38);
        void *sc1 = *(void**)(c + 0x38);
        EntrySwapLeagueRobOptServer(a, c);
        CHECK(*(void**)(c + 0x38) == sa1 &&
              *(void**)(a + 0x38) == sc1,
              "Swap: str1 pointers exchanged");
        CHECK(*(uint32_t*)(a + 0x34) == 22 &&
              *(uint32_t*)(c + 0x34) == 11,
              "Swap: cached values exchanged");

        // cleanup via the real dtors
        EntryDtorLeagueRobOptServer(a);
        EntryDtorLeagueRobOptServer(b);
        EntryDtorLeagueRobOptServer(c);
        free(a); free(b); free(c);
    }

    // ========= Create / Clear / Serialize =========
    SECT("D71-create");
    {
        char* ab = (char*)calloc(1, MSG);
        CtorCMsgLeagueRobOpt(ab);
        Reset(); g_cachedSize = 0x123; g_nInit = 0;
        CHECK(CreateLeagueRobOpt(ab, 4, 9) == true,
              "Create -> true");
        CHECK(g_nInit == 1, "Create calls tq Init once");
        char* pb = ab + 0x408;
        CHECK(*(uint32_t*)(pb + 0x30) == (1 | 2),
              "has-bits 1|2");
        CHECK(*(uint32_t*)(pb + 0x38) == 4, "f1 = 4");
        CHECK(*(uint32_t*)(pb + 0x3c) == 9, "f2 = 9");
        CHECK(*(uint16_t*)(ab + 0xa) == 0xa52,
              "wire id 0xa52 at +0xa");
        CHECK(*(uint16_t*)(ab + 8) == 0x123,
              "cached size at +8");

        g_cachedSize = 0x77;
        g_nClear = 0;
        ClearLeagueRobOpt(ab);
        CHECK(g_nClear == 1, "Clear: PB vt[3] once");
        CHECK(*(uint16_t*)(ab + 8) == 0x77,
              "Clear refreshes the cached size");

        // serialize ok
        Reset();
        CHECK(SerializeLeagueRobOpt(ab) == 1,
              "Serialize ok");
        CHECK(Has("ser:cap=1020"), "SerializeToArray cap "
              "0x3fc");
        CHECK(*(uint16_t*)(ab + 8) == 0x77,
              "Serialize refreshes the cached size");

        // serialize fail, IsInitialized == 0 -> the
        // 2-arg log with the inline sret string
        g_serOk = 0; g_isInit = 0; g_errInline = 1;
        Reset();
        CHECK(SerializeLeagueRobOpt(ab) == 0,
              "Serialize fail -> 0");
        CHECK(Has("log2:14183cdd0:abcde"),
              "fail+notinit: 2-arg log, DAT fmt, inline "
              "string");   // 0x14183cdd0 = 54136622352
        // serialize fail, IsInitialized != 0 -> the 1-arg
        // literal log
        g_isInit = 1;
        Reset();
        CHECK(SerializeLeagueRobOpt(ab) == 0,
              "Serialize fail -> 0 (init ok)");
        CHECK(Has("log1:1417d85f9"),
              "fail+init: 1-arg literal log");  // 1417d85f9
        g_serOk = 1;
        free(ab);
    }

    // ========= CreateBufMsg =========
    SECT("D71-parse");
    {
        char* ab = (char*)calloc(1, MSG);
        CtorCMsgLeagueRobOpt(ab);
        char buf[32] = {0};

        Reset();
        CHECK(CreateBufMsgLeagueRobOpt(ab, nullptr, 8) ==
              false, "parse(null buf) -> false");
        CHECK(!Has("parse:"), "no parse call on null");

        // wrong wire id
        *(uint16_t*)(ab + 0xa) = 0xa51;
        CHECK(CreateBufMsgLeagueRobOpt(ab, buf, 8) ==
              false, "parse(wire 0xa51) -> false");
        CHECK(!Has("parse:"), "no parse call on wire "
              "mismatch");
        *(uint16_t*)(ab + 0xa) = 0xa52;

        // ok
        g_parseOk = 1;
        Reset();
        CHECK(CreateBufMsgLeagueRobOpt(ab, buf, 10) ==
              true, "parse ok -> true");
        CHECK(g_parseLen == 6, "parse len = uLen-4");
        CHECK(!Has("log1:") && !Has("log2:"), "no logs "
              "on success");

        // fail + IsInitialized -> 1-arg literal
        g_parseOk = 0; g_isInit = 1;
        Reset();
        CHECK(CreateBufMsgLeagueRobOpt(ab, buf, 10) ==
              false, "parse fail -> false");
        CHECK(Has("log1:1417d84b1"),
              "parse fail+init: literal log");  // 1417d84b1
        // fail + !init -> 2-arg DAT log
        g_isInit = 0; g_errInline = 1;
        Reset();
        CHECK(CreateBufMsgLeagueRobOpt(ab, buf, 10) ==
              false, "parse fail -> false");
        CHECK(Has("log2:14183cd30:abcde"),
              "parse fail+!init: 2-arg log");  // 14183cd30
        free(ab);
    }

    // ========= the repeated field =========
    SECT("D71-rep");
    {
        char* ab = (char*)calloc(1, MSG);
        CtorCMsgLeagueRobOpt(ab);
        char* rep = ab + 0x448;
        g_cachedSize = 0;   // keep the gates open

        // pre-place 2 constructed entries: alloc=2,
        // cap=2 -> first two calls take the reuse path
        void* e0 = EntryNewLeagueRobOptServer();
        void* e1 = EntryNewLeagueRobOptServer();
        void** arr = (void**)calloc(4, 8);
        arr[0] = e0; arr[1] = e1;
        *(void***)rep = arr;
        *(int32_t*)(rep + 8) = 0;     // current
        *(int32_t*)(rep + 0xc) = 2;   // allocated
        *(int32_t*)(rep + 0x10) = 2;  // capacity

        Reset();
        void* r0 = GetOrAddEntryLeagueRobOpt(rep);
        CHECK(r0 == e0, "reuse path returns elements[0]");
        CHECK(*(int32_t*)(rep + 8) == 1, "current 0->1");

        // AppendDword: its INTERNAL GetOrAddEntry takes
        // the NEXT slot (elements[1] = e1) — the raw
        // append never touches the first slot
        *(uint32_t*)((char*)e1 + 0x30) = 0;
        CHECK((AppendDwordLeagueRobOpt(ab, 42) & 1) == 1,
              "AppendDword ok");
        CHECK(*(int32_t*)((char*)e1 + 0x48) == 42,
              "entry value = 42 (on elements[1])");
        CHECK((*(uint32_t*)((char*)e1 + 0x30) & 1) != 0,
              "entry has-bits |= 1");
        CHECK(GetCountLeagueRobOpt(ab) == 2,
              "GetCount (u16 @+0x450) = 2");
        CHECK(GetEntryLeagueRobOpt(ab, 1) == e1,
              "GetEntry(1) == elements[1]");

        // zero value -> gate rejects
        Reset();
        CHECK((AppendDwordLeagueRobOpt(ab, 0) & 1) == 0,
              "AppendDword(0) -> AL=0");
        CHECK(!Has("opnew:80"), "no entry allocated");

        // the size gate: cached + 4 >= 0x400
        g_cachedSize = 0x3fc;
        CHECK((AppendDwordLeagueRobOpt(ab, 5) & 1) == 0,
              "cached+4 >= 0x400 -> AL=0");
        g_cachedSize = 0;

        // current == alloc == cap == 2: the GROW path
        Reset();
        void* r2 = GetOrAddEntryLeagueRobOpt(rep);
        CHECK(r2 != nullptr && r2 != e0 && r2 != e1,
              "grow path constructs a new entry");
        CHECK(Has("opnew:80"), "grow: op_new(0x50)");
        CHECK(*(int32_t*)(rep + 0xc) == 3,
              "allocated 2->3");
        CHECK(*(int32_t*)(rep + 8) == 3, "current -> 3");
        // the shared Reserve (1417e0110) grew the array:
        CHECK(Has("opdelarr"), "Reserve freed the old "
              "elements array");

        // AppendDwordString: value + str1 (0x10 cap) +
        // the EMPTY str2 skip. NOTE: each Append's
        // internal GetOrAddEntry creates a NEW entry
        // (current == alloc at the grow point) — assert
        // on elements[current-1] via the last slot.
        #define LAST_ENTRY \
            ((char*)*(void***)rep[*(int32_t*)(rep + 8) - 1])
        char longstr[33];
        memset(longstr, 'A', 32); longstr[32] = 0;
        // 16-byte fixed buffers like the raw callers
        char b16[16]; memset(b16, 0, 16); b16[0] = 'b';
        char r16[16]; memset(r16, 0, 16);
        memcpy(r16, "real", 4);
        int nBase = *(int32_t*)(rep + 8);
        CHECK((AppendDwordStringLeagueRobOpt(
                  ab, 7, longstr, nullptr) & 1) == 1,
              "AppendDwordString ok (null str2)");
        char* x7 = (char*)(*(void***)rep)[
            *(int32_t*)(rep + 8) - 1];
        CHECK(*(int32_t*)(x7 + 0x48) == 7,
              "value = 7");
        CHECK((*(std::string**)(x7 + 0x38))->size() ==
              0x10, "str1 capped at 0x10");
        CHECK(*(void**)(x7 + 0x40) == (void*)0x666,
              "str2 untouched (null)");

        CHECK((AppendDwordStringLeagueRobOpt(
                  ab, 8, b16, "") & 1) == 1,
              "AppendDwordString ok (empty str2)");
        char* x8 = (char*)(*(void***)rep)[
            *(int32_t*)(rep + 8) - 1];
        CHECK(*(void**)(x8 + 0x40) == (void*)0x666,
              "EMPTY str2 skipped (the raw scasb gate)");

        CHECK((AppendDwordStringLeagueRobOpt(
                  ab, 9, b16, r16) & 1) == 1,
              "AppendDwordString ok (real str2)");
        char* x9 = (char*)(*(void***)rep)[
            *(int32_t*)(rep + 8) - 1];
        {
            std::string* p2 =
                *(std::string**)(x9 + 0x40);
            CHECK(p2->size() == 0x10 &&
                  p2->compare(0, 4, "real") == 0,
                  "str2 assigned (0x10 raw + 'real')");
        }

        // the +0x24 gate
        g_cachedSize = 0x3dc;   // +0x24 = 0x400 -> jae
        CHECK((AppendDwordStringLeagueRobOpt(
                  ab, 10, "x", "y") & 1) == 0,
              "cached+0x24 >= 0x400 -> AL=0");
        g_cachedSize = 0;

        // null str1 gate
        CHECK((AppendDwordStringLeagueRobOpt(
                  ab, 11, nullptr, "y") & 1) == 0,
              "null str1 -> AL=0");

        // PB New (1417f06f0)
        Reset();
        void* pPb = NewLeagueRobOptPB();
        CHECK(pPb != nullptr && Has("opnew:88"),
              "PB New: op_new(0x58)");
        CHECK(*(void**)pPb == (void*)s_vtPb,
              "PB New: the class vtable");
        DtorLeagueRobOptPB(pPb);
        free(pPb);

        // the PB dtor's allocated-bound loop: 3
        // allocated entries -> 3 entry deletes + one
        // delete[] for the array
        Reset(); g_nEntryDel = 0;
        int nAllocAtDtor = *(int32_t*)(rep + 0xc);
        DtorCMsgLeagueRobOpt(ab);
        CHECK(g_nEntryDel == nAllocAtDtor,
              "PB dtor deletes ALL allocated entries");
        CHECK(Has("opdelarr"), "PB dtor frees the "
              "elements array");
        CHECK(Has("pbbasedtor"), "PB base dtor tail");
        free(ab);
    }

    // ========= the deleting dtor flag =========
    SECT("D71-deletingdtor");
    {
        char* ab = (char*)calloc(1, MSG);
        CtorCMsgLeagueRobOpt(ab);
        Reset(); g_freed.clear();
        DeletingDtorCMsgLeagueRobOpt(ab, 1);
        CHECK(Has("pbbasedtor"),
              "deleting dtor runs the full dtor chain");
        // flags 1: the wrapper itself goes through the
        // scalar op delete seam
        bool bFreed = false;
        for (void* q : g_freed) if (q == ab) bFreed = true;
        CHECK(bFreed,
              "flags 1: the wrapper freed via op_delete");
        // ab is already freed by the seam — do NOT free

        // flags 0: the dtor chain runs, no wrapper free
        char* ab2 = (char*)calloc(1, MSG);
        CtorCMsgLeagueRobOpt(ab2);
        Reset(); g_freed.clear();
        DeletingDtorCMsgLeagueRobOpt(ab2, 0);
        bool bFreed2 = false;
        for (void* q : g_freed) if (q == ab2) bFreed2 = true;
        CHECK(!bFreed2, "flags 0: no wrapper delete");
        free(ab2);
    }

    printf(g_fail ? "D71-FAIL\n" : "D71-OK\n");
    return g_fail;
}

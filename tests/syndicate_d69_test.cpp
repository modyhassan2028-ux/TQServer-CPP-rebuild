// tests/syndicate_d69_test.cpp — the syndicate::
// CMsgLeagueBeRob family (0xa51): the ctor/dtor pair,
// Create, Clear, Serialize, GetCount, the repeated
// field (GetOrAddEntry/AppendDword/Reserve), the PB
// ctor/dtor, the entry ctor, NewEntry and the +0x34
// getters. Verbatim facts checked: the double Init,
// the +0xa wire id, the (i64)(i32)+4 < 0x400 size
// gate, the rax&~0xff tails, the max(cap*2,n) then
// floor reserve, op_new(8*cap), the elements-store-
// then-copy order, the entry vt[0](,1) deletes, the
// |= 8 name has-bit and the lazy 0x28 string slot.
#include "modules/syndicate/src/SyndicateLeagueBeRob.h"
#include "modules/syndicate/src/SyndicateModule.h"
#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
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
static void Reset() { g_calls.clear(); }

// ================= the seams =================
static int   g_nInit = 0;
static void  FakeTqInit(void*) { ++g_nInit; }
static void* FakeOpNew(size_t n) {
    void* p = calloc(1, n + 16);
    C("opnew:" + std::to_string(n));
    return p;
}
static void  FakeOpDel(void* p) { C("opdel:"); free(p); }
static void  FakeOpDelArr(void* p) { C("opdelarr"); free(p); }
static void  FakePbDefaultInit() { C("pbdefaultinit"); }
static char  g_serOk = 1;
static char  FakeSerialize(void*, void*, size_t cap) {
    C("ser:cap=" + std::to_string(cap));
    return g_serOk;
}
static const int* FakeIntMax(const int* a, const int* b) {
    return (*a >= *b) ? a : b;
}
static const int s_floor = 4;   // DAT_14183f028 model
static void  FakePbBaseDtor(void*) { C("pbbasedtor"); }
static void  FakeLog2(const void* fmt, const char* s) {
    (void)fmt; C("log2:" + std::string(s ? s : "(null)"));
}
static void  FakeLog1(const void* fmt) {
    (void)fmt; C("log1:literal"); }

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
    // the raw shape the family reads: qword@+0x20 <0x10
    // -> inline@+8, else the qword ptr@+8
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
    ((std::string*)((char*)p + 8))->~basic_string();
    free(p);
}

// ---- the fake vtables ----
static void* s_vtPb[16];       // the PB object vtable
static void* s_vtEntry[2];     // the entry vtable

static void WireSeams() {
    g_pTqCMsgVft = (void*)0x111;
    g_pVtPbMessageLite = (void*)0x222;
    g_pVtCMsgLeagueBeRob = (void*)0x333;
    g_pVtCMsgLeagueBeRobPB = s_vtPb;   // the ctor stores
    g_pVtCMsgLeagueBeRobRePB = s_vtEntry; // it as the vptr
    g_pPbDefaultInstance = (void*)0x666;
    g_fnTqCMsgInit = FakeTqInit;
    g_fnOpNew = FakeOpNew;
    g_fnOpDelete = FakeOpDel;
    g_fnOpDeleteArr = FakeOpDelArr;
    g_fnPbDefaultInit = FakePbDefaultInit;
    g_fnPbSerializeToArray = FakeSerialize;
    g_fnPbIntMax = FakeIntMax;
    g_pPbReserveFloor = &s_floor;
    g_fnPbBaseDtor = FakePbBaseDtor;
    g_fnLogBeRobSerializeErr = FakeLog2;
    g_fnLogBeRobSerializeFail = FakeLog1;

    s_vtPb[3] = (void*)FakePbClear;
    s_vtPb[4] = (void*)FakeIsInit;
    s_vtPb[5] = (void*)FakeErrString;
    s_vtPb[8] = (void*)FakeGetCachedSize;
    s_vtEntry[0] = (void*)FakeEntryDeletingDtor;
}

int main() {
    WireSeams();

    SECT("D69-ctor");
    {
        char ab[0x470];
        memset(ab, 0xCD, sizeof(ab));
        Reset(); g_nInit = 0;
        CtorCMsgLeagueBeRob(ab);
        CHECK(g_nInit == 2, "ctor runs tq Init TWICE");
        CHECK(*(void**)ab == (void*)0x333,
              "ctor final vptr = CMsgLeagueBeRob");
        char* pb = ab + 0x408;
        CHECK(*(void**)pb == (void*)s_vtPb,
              "PB vptr = the class vtable");
        CHECK(*(uint32_t*)(pb + 0x30) == 0,
              "PB has-bits zeroed");
        CHECK(*(uint64_t*)(pb + 0x40) ==
              (uint64_t)(uintptr_t)g_pPbDefaultInstance,
              "PB name slot = default instance");
        CHECK(*(uint64_t*)(pb + 0x48) == 0 &&
              *(uint32_t*)(pb + 0x50) == 0 &&
              *(uint32_t*)(pb + 0x54) == 0 &&
              *(uint32_t*)(pb + 0x58) == 0,
              "PB repeated field zeroed");
        CHECK(*(uint32_t*)(pb + 0x38) == 0 &&
              *(uint32_t*)(pb + 0x3c) == 0 &&
              *(uint32_t*)(pb + 0x60) == 0,
              "PB f1/f2/f3 zeroed");
        CHECK(Has("pbdefaultinit"), "the 1417e8050 thunk ran");
        std::string* pEmbedded = (std::string*)(pb + 8);
        CHECK(pEmbedded->empty(), "PB +0x08 string empty");
        DtorCMsgLeagueBeRob(ab, 0, 0, 0);
        CHECK(Has("pbbasedtor"), "dtor reaches the PB dtor");
        CHECK(*(void**)ab == (void*)0x111,
              "msg dtor restores the tq vptr");
    }

    SECT("D69-create");
    {
        char ab[0x470];
        memset(ab, 0, sizeof(ab));
        CtorCMsgLeagueBeRob(ab);
        Reset();
        CHECK(CreateLeagueBeRob(ab, 0, 0, 0, nullptr) == false,
              "Create(null name) -> false");
        g_cachedSize = 0x123;
        CHECK(CreateLeagueBeRob(ab, 3, 77, 55, "Mizo") == true,
              "Create(valid) -> true");
        char* pb = ab + 0x408;
        CHECK(*(uint32_t*)(pb + 0x30) == (1 | 2 | 4 | 8),
              "has-bits 1|2|4|8");
        CHECK(*(uint32_t*)(pb + 0x38) == 3, "f1 = 3");
        CHECK(*(uint32_t*)(pb + 0x3c) == 77, "f2 = 77");
        CHECK(*(uint32_t*)(pb + 0x60) == 55, "f3 = 55");
        CHECK(*(uint16_t*)(ab + 0xa) == 0xa51,
              "wire id 0xa51 at +0xa");
        CHECK(*(uint16_t*)(ab + 8) == 0x123,
              "cached size at +8");
        std::string* pName = *(std::string**)(pb + 0x40);
        CHECK(pName != nullptr && *pName == "Mizo",
              "name slot assigned Mizo");
        DtorCMsgLeagueBeRob(ab, 0, 0, 0);  // frees Mizo str
    }

    SECT("D69-append-growth");
    {
        char ab[0x470];
        memset(ab, 0, sizeof(ab));
        CtorCMsgLeagueBeRob(ab);
        char* pb = ab + 0x408;
        char* rep = ab + 0x450;

        // pre-place 2 constructed entries: alloc=2,
        // cap=2 -> first two calls take the reuse path
        void* e0 = EntryCtorLeagueBeRobRe(calloc(1, 0x40));
        void* e1 = EntryCtorLeagueBeRobRe(calloc(1, 0x40));
        // heap array: the grow path delete[]s it (raw)
        void** elems = (void**)calloc(4, sizeof(void*));
        elems[0] = e0; elems[1] = e1;
        *(void***)rep = elems;
        *(int32_t*)(rep + 0xc) = 2;   // allocated
        *(int32_t*)(rep + 0x10) = 2;  // capacity

        g_cachedSize = 8;
        CHECK(AppendDwordLeagueBeRob(ab, 100) == 1,
              "append#1 ok");
        CHECK(*(int32_t*)(rep + 8) == 1, "rep size 1");
        CHECK(*(int32_t*)((char*)e0 + 0x38) == 100,
              "entry#1 value 100");
        CHECK(*(uint32_t*)((char*)e0 + 0x30) == 1,
              "entry#1 has-bit 1");
        CHECK(AppendDwordLeagueBeRob(ab, 200) == 1,
              "append#2 ok (reuse path)");
        CHECK(*(void**)rep == (void*)elems,
              "reuse: same elements array, no realloc");
        CHECK(AppendDwordLeagueBeRob(ab, 0) == 0,
              "append(0) -> 0 (the rax&~0xff tail)");
        // third append: alloc==cap -> reserve(cap+1):
        // max(2*2, 3)=4 then the floor max(4,4)=4 -> 4
        Reset();
        CHECK(AppendDwordLeagueBeRob(ab, 300) == 1,
              "append#3 ok (grow path)");
        CHECK(*(int32_t*)(rep + 0x10) == 4, "cap = 4");
        CHECK(*(int32_t*)(rep + 0xc) == 3, "alloc = 3");
        CHECK(Has("opdelarr"), "old array freed");
        CHECK(*(int32_t*)(rep + 8) == 3, "rep size 3");
        // the fresh entry keeps the ctor string alive at
        // +8 (EntryCtor verbatim)
        void* e2 = ((void***)rep)[0][2];
        CHECK(*(int32_t*)((char*)e2 + 0x38) == 300,
              "entry#3 value 300");
        // the size gate: cached + 4 >= 0x400 -> fail
        g_cachedSize = 0x3fd;
        // the raw tail: the STALE cached size rides rax,
        // masked &~0xff (AL=0 -> "failed" for the caller)
        CHECK(AppendDwordLeagueBeRob(ab, 400) ==
              (0x3fd & ~(uint64_t)0xff),
              "size gate 0x3fd+4 >= 0x400 -> rax&~0xff (AL=0)");
        // cleanup: the three entries + the array
        FakeEntryDeletingDtor(e0, 1);
        FakeEntryDeletingDtor(e1, 1);
        FakeEntryDeletingDtor(e2, 1);
        free(*(void***)rep);
        // rep now points at freed memory: clear it before
        // the dtor runs (the PB dtor would delete[] it)
        *(void***)rep = nullptr;
        *(int32_t*)(rep + 0xc) = 0;        // allocated = 0
        *(int32_t*)(rep + 0x10) = 0;       // capacity = 0
        DtorCMsgLeagueBeRob(ab, 0, 0, 0);
    }

    SECT("D69-reserve");
    {
        // ReserveEntries alone: max(cap*2, n) then the
        // floor; copy of allocated*8; the elements-store-
        // BEFORE-memcpy order; overflow -> op_new(~0)
        char rep[0x18];
        memset(rep, 0, sizeof(rep));
        // a REAL heap array holding the sentinel value:
        // memcpy reads alloc*8 bytes from it (the raw copy)
        void** old = (void**)calloc(2, sizeof(void*));
        old[0] = (void*)0xABCDEF0;
        *(void***)rep = old;
        *(int32_t*)(rep + 8) = 2;    // size
        *(int32_t*)(rep + 0xc) = 2;  // allocated
        *(int32_t*)(rep + 0x10) = 2; // capacity
        Reset();
        ReserveEntriesLeagueBeRob(rep, 3);
        CHECK(Has("opnew:32"), "op_new(8*4) for new cap 4");
        CHECK(*(int32_t*)(rep + 0x10) == 4, "cap = 4");
        CHECK(Has("opdelarr"), "old elements freed");
        CHECK(((void**)*(void**)rep)[0] == (void*)0xABCDEF0,
              "contents copied (alloc*8 = 16 bytes)");
        free(*(void***)rep);
        // n below cap: no-op
        Reset();
        ReserveEntriesLeagueBeRob(rep, 1);
        CHECK(g_calls.empty(), "cap >= n -> no-op");
        // the floor: cap 1, n 1 -> max(2,1)=2 -> max(4,2)=4
        char rep2[0x18];
        memset(rep2, 0, sizeof(rep2));
        *(int32_t*)(rep2 + 0x10) = 1;   // capacity
        ReserveEntriesLeagueBeRob(rep2, 2);
        CHECK(*(int32_t*)(rep2 + 0x10) == 4,
              "the DAT floor: cap 1 -> 4");
        free(*(void***)rep2);
    }

    SECT("D69-serialize");
    {
        char ab[0x470];
        memset(ab, 0, sizeof(ab));
        CtorCMsgLeagueBeRob(ab);

        g_serOk = 1; g_cachedSize = 0x99;
        Reset();
        CHECK(SerializeLeagueBeRob(ab) == 1,
              "serialize ok -> 1");
        CHECK(Has("ser:cap=1020"),
              "SerializeToArray cap 0x3fc");
        CHECK(*(uint16_t*)(ab + 8) == 0x99,
              "size refreshed");

        // fail + IsInitialized -> the literal 1-arg log
        g_serOk = 0; g_isInit = 1;
        Reset();
        CHECK(SerializeLeagueBeRob(ab) == 0,
              "serialize fail (init ok) -> 0");
        CHECK(Has("log1:literal"),
              "the literal 'SerializeToArray failed' log");

        // fail + not-init -> the sret error string
        g_isInit = 0; g_errInline = 1;
        Reset();
        CHECK(SerializeLeagueBeRob(ab) == 0,
              "serialize fail (not init) -> 0");
        CHECK(Has("log2:abcde"),
              "inline error string logged");
        g_errInline = 0;
        Reset();
        CHECK(SerializeLeagueBeRob(ab) == 0,
              "serialize fail (heap string) -> 0");
        CHECK(Has("log2:heap-error-string"),
              "heap error string logged");
        DtorCMsgLeagueBeRob(ab, 0, 0, 0);
    }

    SECT("D69-clear-count");
    {
        char ab[0x470];
        memset(ab, 0, sizeof(ab));
        CtorCMsgLeagueBeRob(ab);
        g_nClear = 0; g_cachedSize = 0x77;
        ClearLeagueBeRob(ab);
        CHECK(g_nClear == 1, "PB vt[3] clear called");
        CHECK(*(uint16_t*)(ab + 8) == 0x77,
              "size refreshed after clear");
        *(uint16_t*)(ab + 0x458) = 0xBEEF;
        CHECK(GetCountLeagueBeRob(ab) == 0xBEEF,
              "GetCount reads u16 @+0x458");
        DtorCMsgLeagueBeRob(ab, 0, 0, 0);
    }

    SECT("D69-newentry-dtors");
    {
        Reset();
        void* pEntry = NewLeagueBeRobRe();
        CHECK(pEntry != nullptr && Has("opnew:64"),
              "NewEntry: op_new(0x40) + ctor");
        CHECK(*(void**)pEntry == (void*)s_vtEntry,
              "entry vptr set");
        CHECK(EntryGetCachedLeagueBeRobRe(pEntry) == 0,
              "entry +0x34 getter");
        *(uint32_t*)((char*)pEntry + 0x34) = 0x42;
        CHECK(EntryGetCachedLeagueBeRobRe(pEntry) == 0x42,
              "entry +0x34 read");
        FakeEntryDeletingDtor(pEntry, 1);

        // ProtoGetCached (+0x34)
        char pb[0x68];
        memset(pb, 0, sizeof(pb));
        *(uint32_t*)(pb + 0x34) = 0x77;
        CHECK(ProtoGetCachedLeagueBeRobPB(pb) == 0x77,
              "PB +0x34 read");

        // the PB dtor: entries deleted via vt[0](,1);
        // the name slot freed; delete[] elements; the
        // base dtor tail
        char pb2[0x68];
        memset(pb2, 0, sizeof(pb2));
        void* en0 = EntryCtorLeagueBeRobRe(calloc(1, 0x40));
        void* en1 = EntryCtorLeagueBeRobRe(calloc(1, 0x40));
        // heap array: the PB dtor delete[]s it (raw)
        void** arr = (void**)calloc(2, sizeof(void*));
        arr[0] = en0; arr[1] = en1;
        *(void**)(pb2 + 0x48) = arr;
        *(uint32_t*)(pb2 + 0x54) = 2;   // allocated
        // via the op-new seam so the dtor's scalar
        // delete matches (raw: op_new(0x28) + string)
        void* pNameBuf = FakeOpNew(0x28);
        std::string* pName = new (pNameBuf) std::string("named");
        *(void**)(pb2 + 0x40) = pName;
        new (pb2 + 8) std::string();
        Reset(); g_nEntryDel = 0;
        ProtoDtorLeagueBeRobPB(pb2, 0, 0, 0);
        CHECK(g_nEntryDel == 2, "both entries deleted");
        CHECK(Has("entrydel:1"), "entry vt[0] with flags 1");
        CHECK(Has("opdelarr"), "elements array delete[]");
        CHECK(Has("pbbasedtor"), "the 1417de5a0 tail");
        CHECK(Has("opdel:"), "the name string freed");

        // null/default name slot: no delete
        char pb3[0x68];
        memset(pb3, 0, sizeof(pb3));
        *(void**)(pb3 + 0x40) = g_pPbDefaultInstance;
        new (pb3 + 8) std::string();
        Reset();
        ProtoDtorLeagueBeRobPB(pb3, 0, 0, 0);
        CHECK(!Has("opdel:"), "default name -> no delete");

        // the deleting dtor: flags&1 -> delete (heap
        // buffers: the raw delete frees the message)
        char* ab3 = (char*)calloc(1, 0x470);
        CtorCMsgLeagueBeRob(ab3);
        Reset();
        void* pVptrAfterDtor = nullptr;   // read BEFORE
        // (the flags&1 path deletes the buffer itself)
        DeletingDtorCMsgLeagueBeRob(ab3, 1);
        CHECK(Has("opdel"), "flags&1 -> op delete");
        CHECK(Has("pbbasedtor"), "PB dtor ran first");
        // flags&0 -> no delete (leak check avoided by
        // calling it again with 1 on the same buffer)
        char* ab4 = (char*)calloc(1, 0x470);
        CtorCMsgLeagueBeRob(ab4);
        Reset();
        DeletingDtorCMsgLeagueBeRob(ab4, 0);
        CHECK(!Has("opdel:"), "flags 0 -> no delete");
        DeletingDtorCMsgLeagueBeRob(ab4, 1);  // cleanup
    }

    SECT("D69-setname");
    {
        char pb[0x68];
        memset(pb, 0, sizeof(pb));
        *(void**)(pb + 0x40) = g_pPbDefaultInstance;
        Reset();
        SetNameLeagueBeRobPB(pb, "Tariq");
        CHECK(*(uint32_t*)(pb + 0x30) == 8,
              "name has-bits |= 8");
        CHECK(Has("opnew:40"), "lazy string op_new(0x28)");
        std::string* p = *(std::string**)(pb + 0x40);
        CHECK(p && *p == "Tariq", "assigned Tariq");
        // second set on the SAME string: no new alloc
        Reset();
        SetNameLeagueBeRobPB(pb, "Hoda");
        CHECK(*p == "Hoda", "reassigned Hoda");
        CHECK(!Has("opnew:40"), "no second alloc");
        p->~basic_string();
        free(p);
    }

    if (g_fail == 0) printf("D69-LEAGUE-BE-ROB-OK\n");
    else printf("D69-LEAGUE-BE-ROB-FAIL\n");
    return g_fail;
}

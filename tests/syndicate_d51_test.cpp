// syndicate_d51_test — D51/T16: the REAL pool ctor
// family (14177cfa0): the 0x30 vector element
// ctor (141729200), the dtor (141727880), the
// anchor clear (14172cfe0 — verbatim, the memmove
// size computes to 0 in the original) and the pool
// ctor itself (the _eh_vector 3x0x30 + the anchor
// proxy at +0x98 + the +0xb0/b8/c0 zeros + the
// +0xc8 byte = 1). The seam g_fnMeedPoolCtor now
// defaults to the REAL family.
#include "../Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"
#include "../Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace syndicate;

static int g_nInvalid = 0;
static void MockInvalid() { ++g_nInvalid; }
static void MockLog() {}
static size_t g_nAllocs = 0;
static size_t g_nFrees = 0;
static void* MockOpNew(size_t n) {
    ++g_nAllocs;
    void* p = malloc(n);
    assert(p != nullptr);
    memset(p, 0xcd, n);
    return p;
}
static void MockOpDelete(void* p) {
    if (p != nullptr) {
        ++g_nFrees;
    }
    free(p);
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_fnMeritInvalid = MockInvalid;
    g_fnMeedLog = MockLog;
    g_fnMeritOpNew = MockOpNew;
    g_fnMeritOpDelete = MockOpDelete;

    // ---------- D51-1: the vector element ctor --
    char elem[0x30];
    memset(elem, 0xcd, sizeof(elem));
    g_nAllocs = 0;
    void* r = MeedPoolVecElemCtor(elem);
    assert(r == elem);
    assert(g_nAllocs == 1
        && "one 8-byte proxy alloc");
    void** proxy = *(void***)elem;
    assert(proxy != nullptr);
    assert(*proxy == (void*)elem
        && "the proxy points back at the element");
    assert(*(void***)(elem + 0x18) == nullptr
        && *(void***)(elem + 0x20) == nullptr
        && *(void***)(elem + 0x28) == nullptr
        && "begin/end/cap zeroed");
    assert(g_nInvalid == 0);
    printf("D51-1 the vector element ctor ok\n");

    // ---------- D51-2: the clear (end = begin) --
    // a nonzero vector: begin != end → end = begin
    static void* buf[4] = { nullptr };
    char vec[0x30];
    memset(vec, 0, sizeof(vec));
    void** v = (void**)vec;
    v[0] = (void**)vec;    // the self proxy
    v[3] = buf;                     // begin
    v[4] = buf + 3;                 // end
    v[5] = buf + 4;                 // cap
    int invBefore = g_nInvalid;
    MeedPoolVecClearKeepCap(vec);
    assert(g_nInvalid == invBefore
        && "no gate fires for a valid vector");
    assert(v[3] == buf
        && "the begin stays");
    assert(v[4] == buf
        && "the END snaps back to the begin");
    assert(v[5] == buf + 4
        && "the capacity kept");
    // the empty vector: begin == end → untouched
    v[4] = v[3];
    MeedPoolVecClearKeepCap(vec);
    assert(v[4] == v[3]);
    printf("D51-2 the anchor clear ok\n");

    // ---------- D51-3: the REAL pool ctor ------
    // (the pool = 0xd0 bytes: 3 vectors x 0x30 +
    // 0x98 anchor + 0x10 + the 0xc8 byte)
    char* pool = (char*)calloc(1, 0xd0);
    g_nAllocs = 0;
    void* pr = MeedPoolCtorReal(pool);
    assert(pr == pool);
    assert(g_nAllocs == 4
        && "3 element proxies + the anchor proxy");
    // the three type vectors at 0/0x30/0x60
    for (int i = 0; i < 3; ++i) {
        char* e = pool + i * 0x30;
        assert(*(void**)e != nullptr
            && "the element proxy set");
        assert(**(void***)e == (void*)e
            && "the proxy points back");
        assert(*(void***)(e + 0x18) == nullptr
            && *(void***)(e + 0x20) == nullptr
            && *(void***)(e + 0x28) == nullptr);
    }
    // the anchor at +0x98
    void** anchor = *(void***)(pool + 0x98);
    assert(anchor != nullptr);
    assert(*anchor == (void*)(pool + 0x98));
    // +0xb0/+0xb8/+0xc0 zeroed (the anchor's
    // begin/end/cap)
    assert(*(void***)(pool + 0xb0) == nullptr
        && *(void***)(pool + 0xb8) == nullptr
        && *(void***)(pool + 0xc0) == nullptr);
    // the byte at 200 DECIMAL = 0xc8
    assert(*(uint8_t*)(pool + 0xc8) == 1
        && "the +0xc8 flag = 1 (200 decimal)");
    assert(g_nInvalid == 0);
    printf("D51-3 the REAL pool ctor ok\n");

    // ---------- D51-4: D48 compatibility -------
    // GetVecByMeedType reads pool+(type-1)*0x30
    // and the +0x98 anchor — the REAL ctor's
    // layout must match those offsets exactly
    {
        // type 1 → +0x0, type 3 → +0x60
        void* v1 = MeedPoolVecByType(pool, 1);
        void* v3 = MeedPoolVecByType(pool, 3);
        assert(v1 == (void*)pool
            && v3 == (void*)(pool + 0x60)
            && "the type vectors at the D48\n" "offsets");
        void* va = MeedPoolVecByType(pool, 9);
        assert(va == (void*)(pool + 0x98)
            && "the anchor for a bad type");
    }
    printf("D51-4 the D48 compatibility ok\n");

    // ---------- D51-5: the lazy get integration
    // MeedPoolGet → the seam → the REAL ctor
    MeedPoolReset();
    void* p1 = MeedPoolGet();
    assert(p1 != nullptr
        && "the lazy get allocated the pool");
    assert(*(uint8_t*)((char*)p1 + 0xc8) == 1
        && "the REAL pool behind the seam");
    void* p2 = MeedPoolGet();
    assert(p1 == p2 && "the pool cached");
    // the seam = the real function
    assert(g_fnMeedPoolCtor == &MeedPoolCtorReal);
    printf("D51-5 the lazy get integration ok\n");

    // ---------- D51-6: the element dtor --------
    g_nFrees = 0;
    MeedPoolVecElemDtor(elem);
    assert(g_nFrees == 1
        && "only the proxy freed (the buffer was"
           " null)");
    printf("D51-6 the element dtor ok\n");

    printf(
      "SYNDICATE-D51-OK: the REAL pool ctor family"
      " (14177cfa0): the _eh_vector 3x0x30 + the"
      " anchor proxy at +0x98 + the +0xb0/b8/c0"
      " zeros + the +0xc8 byte; the element"
      " ctor/dtor (141729200/141727880) and the"
      " anchor clear (14172cfe0, end=begin,"
      " capacity kept) verbatim; the seam"
      " g_fnMeedPoolCtor now defaults to the REAL"
      " family — the D48 pool offsets verified"
      " against the real layout\n");
    return 0;
}

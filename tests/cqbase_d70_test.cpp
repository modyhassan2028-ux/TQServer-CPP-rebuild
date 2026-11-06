// ============================================================================
// cqbase_d70 — ten ported primitives. Every assertion is a branch of the original body:
//   the two destructor stamps, the holder release-then-assign order, the allocate-only-when-
//   null rule, and the flush's four outcomes including the failure reset.
// ============================================================================
#include "modules/syndicate/src/synpioprim.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nReleased = 0; void* g_pReleased = (void*)1;
void ReleaseHook(void* p) { ++g_nReleased; g_pReleased = p; }
int64_t g_nAllocSize = -1;
void* g_pAlloc = (void*)0xBEEF;
void* AllocHook(int64_t n) { g_nAllocSize = n; return g_pAlloc; }
int g_nResets = 0;
void ResetHook(void*) { ++g_nResets; }

bool g_bWriteOk = true;
int32_t g_nLastWritten = -1;
void* g_pLastBuf = nullptr;
bool WriteHook(void* pStream, void* pBuf, int32_t n) {
    (void)pStream; g_pLastBuf = pBuf; g_nLastWritten = n; return g_bWriteOk;
}

struct Obj {
    std::vector<uint8_t> a;
    Obj(size_t n = 0x40) : a(n, 0) {}
    uint8_t* p() { return a.data(); }
    uintptr_t vft() { return *(uintptr_t*)a.data(); }
    void set(int o, int32_t v) { *(int32_t*)(a.data() + o) = v; }
    int32_t get(int o) { return *(int32_t*)(a.data() + o); }
    void setp(int o, void* v) { *(void**)(a.data() + o) = v; }
    void* getp(int o) { return *(void**)(a.data() + o); }
};

}  // namespace

int main() {
    g_fnPrimRelease = &ReleaseHook;
    g_fnPrimAlloc = &AllocHook;
    g_fnPrimReset = &ResetHook;

    // ---- the two destructor stamps
    {
        Obj o;
        SynZeroInDtorBody(o.p());
        CHECK(o.vft() == 0x141840c70ULL);
        SynZeroOutDtorBody(o.p());
        CHECK(o.vft() == 0x141840cd8ULL);
    }

    // ---- the two plain readers
    {
        Obj o;
        o.setp(0x00, (void*)0xCAFE);
        CHECK(SynHolderGet(o.p()) == (void*)0xCAFE);
        Obj o2;
        o2.set(0x00, -77);
        CHECK(SynProbeInt(o2.p()) == -77);
    }

    // ---- available bytes are the pointer difference, truncated to an int
    {
        std::vector<uint8_t> aBuf(0x100, 0);
        Obj o;
        o.setp(0x08, aBuf.data());
        o.setp(0x10, aBuf.data() + 40);
        CHECK(SynReaderAvail(o.p()) == 40);
        o.setp(0x10, aBuf.data());
        CHECK(SynReaderAvail(o.p()) == 0);
    }

    // ---- advancing moves the pointer, and a negative count moves it back
    {
        std::vector<uint8_t> aBuf(0x20, 0);
        Obj o;
        o.setp(0x08, aBuf.data());
        SynReaderAdvance(o.p(), 5);
        CHECK(o.getp(0x08) == aBuf.data() + 5);
        SynReaderAdvance(o.p(), -2);
        CHECK(o.getp(0x08) == aBuf.data() + 3);
    }

    // ---- the minimum clamp returns the pointer to the smaller value
    {
        int32_t nA = 9, nB = 4;
        CHECK(SynClampMin(&nA, &nB) == &nB);
        CHECK(*SynClampMin(&nA, &nB) == 4);
        int32_t nC = 4, nD = 9;
        CHECK(SynClampMin(&nC, &nD) == &nC);
        int32_t nE = 7, nF = 7;
        CHECK(SynClampMin(&nE, &nF) == &nE);   // equal keeps the first
    }

    // ---- the holder setter releases the old value only when it differs
    {
        Obj o;
        o.setp(0x00, (void*)0x1111);
        g_nReleased = 0; g_pReleased = (void*)1;
        SynHolderSet(o.p(), (void*)0x1111);          // identical: nothing happens
        CHECK(g_nReleased == 0);
        CHECK(o.getp(0x00) == (void*)0x1111);

        SynHolderSet(o.p(), (void*)0x2222);          // different: release then store
        CHECK(g_nReleased == 1);
        CHECK(g_pReleased == (void*)0x1111);         // the OLD value was released
        CHECK(o.getp(0x00) == (void*)0x2222);
    }

    // ---- the block is allocated only while the holder is still null
    {
        Obj o;
        o.set(0x28, 4096);
        g_nAllocSize = -1; g_nReleased = 0;
        SynAllocateBuffer(o.p());
        CHECK(g_nAllocSize == 4096);
        CHECK(o.getp(0x20) == g_pAlloc);

        // a second call must not allocate again
        g_nAllocSize = -1;
        SynAllocateBuffer(o.p());
        CHECK(g_nAllocSize == -1);
    }

    // ---- the flush: the failure flag short-circuits
    {
        Obj o;
        o.p()[0x11] = 1;
        o.set(0x2c, 10);
        g_nLastWritten = -1;
        CHECK(SynOutAdaptorFlush(o.p()) == false);
        CHECK(g_nLastWritten == -1);        // the stream was never asked
    }

    // ---- an empty buffer answers true without touching the stream
    {
        Obj o;
        o.p()[0x11] = 0;
        o.set(0x2c, 0);
        g_nLastWritten = -1;
        CHECK(SynOutAdaptorFlush(o.p()) == true);
        CHECK(g_nLastWritten == -1);
    }

    // ---- a successful write moves the bytes into the count and clears the buffer
    {
        static void* apVt[2] = {nullptr, (void*)&WriteHook};
        struct StreamObj { void** ppVt; };
        StreamObj stream;
        stream.ppVt = apVt;
        Obj o;
        o.setp(0x08, &stream);
        std::vector<uint8_t> aBuf(16, 0xAB);
        o.setp(0x20, aBuf.data());
        o.set(0x2c, 12);
        o.p()[0x11] = 0;
        *(int64_t*)(o.a.data() + 0x18) = 100;
        g_bWriteOk = true; g_nLastWritten = -1;
        CHECK(SynOutAdaptorFlush(o.p()) == true);
        CHECK(g_nLastWritten == 12);
        CHECK(g_pLastBuf == aBuf.data());
        CHECK(*(int64_t*)(o.a.data() + 0x18) == 112);
        CHECK(o.get(0x2c) == 0);
    }

    // ---- a failed write marks the failure, resets, and answers 0
    {
        static void* apVt[2] = {nullptr, (void*)&WriteHook};
        struct StreamObj { void** ppVt; };
        StreamObj stream;
        stream.ppVt = apVt;
        Obj o;
        o.setp(0x08, &stream);
        std::vector<uint8_t> aBuf(16, 0);
        o.setp(0x20, aBuf.data());
        o.set(0x2c, 5);
        o.p()[0x11] = 0;
        *(int64_t*)(o.a.data() + 0x18) = 7;
        g_bWriteOk = false; g_nResets = 0;
        CHECK(SynOutAdaptorFlush(o.p()) == false);
        CHECK(o.p()[0x11] == 1);
        CHECK(g_nResets == 1);
        CHECK(*(int64_t*)(o.a.data() + 0x18) == 7);   // the count is untouched on failure
        CHECK(o.get(0x2c) == 5);
        g_bWriteOk = true;
    }

    std::printf("SYNDICATE_D70_OK: ten ported primitives, %d checks\n", g_nChecks);
    return 0;
}

// ============================================================================
// cqbase_d69 — the base constructors and the three body destructors that were seams.
//   The destructor order is the thing worth pinning: own vtable, flush, the optional
//   destroy of the underlying stream, the member, then the base destructor.
// ============================================================================
#include "modules/syndicate/src/synpiobases.h"
#include "modules/syndicate/src/synpioctors.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

std::vector<int> g_aOrder;
void ZeroOutDtorHook(void*) { g_aOrder.push_back(4); }
void ZeroInDtorHook(void*) { g_aOrder.push_back(5); }
bool g_bFlush = true;
bool FlushHook(void*) { g_aOrder.push_back(2); return g_bFlush; }
void HolderDtorHook(void*) { g_aOrder.push_back(3); }

struct Stream {
    void** ppVt;
    uint32_t uFlagSeen;
    int nDestroys;
};
void* StreamDestroy(void* p, uint32_t f) {
    Stream* pS = (Stream*)p;
    pS->uFlagSeen = f;
    ++pS->nDestroys;
    g_aOrder.push_back(1);
    return p;
}

struct Obj {
    std::vector<uint8_t> a;
    Obj(size_t n = 0x40) : a(n, 0xEE) {}
    uint8_t* p() { return a.data(); }
    uintptr_t vft() { return *(uintptr_t*)a.data(); }
};

}  // namespace

int main() {
    g_fnBaseZeroOutDtor = &ZeroOutDtorHook;
    g_fnBaseZeroInDtor = &ZeroInDtorHook;
    g_fnBaseFlush = &FlushHook;
    g_fnBaseHolderDtor = &HolderDtorHook;

    // ---- the two base constructors only stamp their own vtable
    {
        Obj o;
        CHECK(SynZeroOutCtor(o.p()) == o.p());
        CHECK(o.vft() == kSynVftZeroOut);
        CHECK(kSynVftZeroOut == 0x141840cd8ULL);
        CHECK(o.a[0x08] == 0xEE);           // nothing else is touched

        Obj o2;
        CHECK(SynZeroInCtor(o2.p()) == o2.p());
        CHECK(o2.vft() == kSynVftZeroIn);
        CHECK(kSynVftZeroIn == 0x141840c70ULL);
    }

    // ---- the holder assignment stores the pointer it is given
    {
        Obj o;
        CHECK(SynHolderAssign(o.p(), (void*)0x1234) == o.p());
        CHECK(*(void**)o.p() == (void*)0x1234);
        SynHolderAssign(o.p(), nullptr);
        CHECK(*(void**)o.p() == nullptr);
    }

    // ---- the two simple body destructors: own vtable then the base
    {
        Obj o;
        g_aOrder.clear();
        SynArrayOutBodyDtor(o.p());
        CHECK(o.vft() == kSynVftArrayOut);
        CHECK(kSynVftArrayOut == 0x141840ca0ULL);
        CHECK(g_aOrder.size() == 1);
        CHECK(g_aOrder[0] == 4);

        Obj o2;
        g_aOrder.clear();
        SynStringOutBodyDtor(o2.p());
        CHECK(o2.vft() == kSynVftStringOut);
        CHECK(kSynVftStringOut == 0x141840d10ULL);
        CHECK(g_aOrder.size() == 1);
        CHECK(g_aOrder[0] == 4);
    }

    // ---- the adaptor destructor: flush, destroy only when the flag is set, member, base
    {
        static void* apVt[2] = {nullptr, nullptr};
        apVt[0] = (void*)&StreamDestroy;
        Stream stream;
        stream.ppVt = apVt;
        stream.uFlagSeen = 0;
        stream.nDestroys = 0;

        Obj o;
        *(void**)(o.a.data() + 0x08) = &stream;
        o.a[0x10] = 0;                      // does not own the stream
        g_aOrder.clear();
        g_bFlush = true;
        SynCopyOutAdaptorBodyDtor(o.p());
        CHECK(o.vft() == kSynVftCopyOutAdaptor);
        CHECK(kSynVftCopyOutAdaptor == 0x141840db0ULL);
        CHECK(g_aOrder.size() == 3);        // flush, member, base — no destroy
        CHECK(g_aOrder[0] == 2);
        CHECK(g_aOrder[1] == 3);
        CHECK(g_aOrder[2] == 4);
        CHECK(stream.nDestroys == 0);

        // with the ownership byte set the stream is destroyed first, through vt[0] with 1
        Obj o2;
        *(void**)(o2.a.data() + 0x08) = &stream;
        o2.a[0x10] = 1;
        g_aOrder.clear();
        SynCopyOutAdaptorBodyDtor(o2.p());
        CHECK(g_aOrder.size() == 4);
        CHECK(g_aOrder[0] == 2);            // the flush still comes first
        CHECK(g_aOrder[1] == 1);            // then the destroy
        CHECK(g_aOrder[2] == 3);
        CHECK(g_aOrder[3] == 4);
        CHECK(stream.nDestroys == 1);
        CHECK(stream.uFlagSeen == 1);

        // a null stream with the flag set must not crash
        Obj o3;
        *(void**)(o3.a.data() + 0x08) = nullptr;
        o3.a[0x10] = 1;
        g_aOrder.clear();
        SynCopyOutAdaptorBodyDtor(o3.p());
        CHECK(g_aOrder.size() == 3);        // flush, member, base
        CHECK(stream.nDestroys == 1);
    }

    // ---- the flush answer is ignored: a failing flush changes nothing downstream
    {
        static void* apVt[2] = {nullptr, nullptr};
        apVt[0] = (void*)&StreamDestroy;
        Stream stream;
        stream.ppVt = apVt;
        stream.nDestroys = 0;
        Obj o;
        *(void**)(o.a.data() + 0x08) = &stream;
        o.a[0x10] = 1;
        g_bFlush = false;
        g_aOrder.clear();
        SynCopyOutAdaptorBodyDtor(o.p());
        CHECK(g_aOrder.size() == 4);        // still destroys and finishes
        g_bFlush = true;
    }

    std::printf("SYNDICATE_D69_OK: base constructors and three body destructors, %d checks\n",
                g_nChecks);
    return 0;
}

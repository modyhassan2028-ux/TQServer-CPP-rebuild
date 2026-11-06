// ============================================================================
// cqbase_d68 — three constructors plus a 64-bit read and a string read. The constructors
//   are the strongest kind of evidence: each stores the vtable that names its class, so the
//   field offsets they write can be checked against the rows ported earlier.
// ============================================================================
#include "modules/syndicate/src/synpioctors.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nBase7960 = 0, g_nBase78C0 = 0, g_nMember7B50 = 0;
void* g_pMemberArg = (void*)1;
void Base7960(void*) { ++g_nBase7960; }
void Base78C0(void*) { ++g_nBase78C0; }
void Member7B50(void*, void* a) { ++g_nMember7B50; g_pMemberArg = a; }

int32_t g_nAvail = 0;
int32_t AvailHook(void*) { return g_nAvail; }
void ResizeHook(void* pStr, int64_t n) { if (n >= 0) ((std::string*)pStr)->resize((size_t)n); }
void* DataHook(void* pStr) { return (void*)((std::string*)pStr)->data(); }
int64_t g_nCopyLen = -1;
void* CopyHook(void* pDst, void* pSrc, int64_t n) {
    g_nCopyLen = n;
    std::memcpy(pDst, pSrc, (size_t)n);
    return pDst;
}
int32_t g_nAdvanced = -1;
void AdvanceHook(void*, int32_t n) { g_nAdvanced = n; }
bool g_bSlowOk = true;
int g_nSlowCalls = 0;
bool SlowHook(void*, void*, int32_t) { ++g_nSlowCalls; return g_bSlowOk; }

struct Obj {
    std::vector<uint8_t> a;
    Obj(size_t n = 0x40) : a(n, 0xEE) {}
    uint8_t* p() { return a.data(); }
    uintptr_t vft() { return *(uintptr_t*)a.data(); }
    int32_t get(int o) { return *(int32_t*)(a.data() + o); }
    void* getp(int o) { return *(void**)(a.data() + o); }
};

}  // namespace

int main() {
    g_fnCtorBase7960 = &Base7960;
    g_fnCtorBase78C0 = &Base78C0;
    g_fnCtorMember7B50 = &Member7B50;
    g_fnCtorAvail = &AvailHook;
    g_fnCtorStrResize = &ResizeHook;
    g_fnCtorStrData = &DataHook;
    g_fnCtorCopy = &CopyHook;
    g_fnCtorAdvance = &AdvanceHook;
    g_fnCtorSlowRead = &SlowHook;

    // ---- ArrayOutputStream: the vtable, the buffer, the size and the block size
    {
        int nBuf = 0;
        Obj o;
        g_nBase7960 = 0;
        CHECK(SynCtorArrayOut(o.p(), &nBuf, 64, 32) == o.p());
        CHECK(g_nBase7960 == 1);
        CHECK(o.vft() == kSynVftArrayOut);
        CHECK(kSynVftArrayOut == 0x141840ca0ULL);
        CHECK(o.getp(0x08) == &nBuf);
        CHECK(o.get(0x10) == 64);
        CHECK(o.get(0x14) == 32);       // the block size wins when positive
        CHECK(o.get(0x18) == 0);
        CHECK(o.get(0x1c) == 0);

        Obj o2;
        SynCtorArrayOut(o2.p(), &nBuf, 64, 0);
        CHECK(o2.get(0x14) == 64);      // a zero block size falls back to the size
        Obj o3;
        SynCtorArrayOut(o3.p(), &nBuf, 64, -5);
        CHECK(o3.get(0x14) == 64);
    }

    // ---- CopyingInputStreamAdaptor: the fields the earlier rows already used
    {
        int nStream = 0;
        Obj o;
        g_nBase78C0 = 0; g_nMember7B50 = 0; g_pMemberArg = (void*)1;
        CHECK(SynCtorCopyInAdaptor(o.p(), &nStream, 1024) == o.p());
        CHECK(g_nBase78C0 == 1);
        CHECK(o.vft() == kSynVftCopyInAdaptor);
        CHECK(kSynVftCopyInAdaptor == 0x141840d68ULL);
        CHECK(o.getp(0x08) == &nStream);
        CHECK(o.a[0x10] == 0);
        CHECK(o.a[0x11] == 0);
        CHECK(*(uint64_t*)(o.a.data() + 0x18) == 0);
        CHECK(g_nMember7B50 == 1);
        CHECK(g_pMemberArg == nullptr);
        CHECK(o.get(0x28) == 1024);
        CHECK(o.get(0x2c) == 0);
        CHECK(o.get(0x30) == 0);

        Obj o2;
        SynCtorCopyInAdaptor(o2.p(), &nStream, 0);
        CHECK(o2.get(0x28) == 0x2000);  // the default block
    }

    // ---- CopyingOutputStreamAdaptor: the same shape without the +0x30 store
    {
        int nOut = 0;
        Obj o;
        g_nBase7960 = 0; g_nMember7B50 = 0;
        CHECK(SynCtorCopyOutAdaptor(o.p(), &nOut, 512) == o.p());
        CHECK(g_nBase7960 == 1);        // this base is 0x1417e7960, like ArrayOutputStream
        CHECK(o.vft() == kSynVftCopyOutAdaptor);
        CHECK(kSynVftCopyOutAdaptor == 0x141840db0ULL);
        CHECK(o.getp(0x08) == &nOut);
        CHECK(o.get(0x28) == 512);
        CHECK(o.get(0x2c) == 0);
        CHECK(o.get(0x30) == 0xEEEEEEEE);   // untouched: this constructor does not write it
    }

    // ---- the little-endian 64-bit read
    {
        const uint8_t aBytes[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xAA, 0xBB};
        uint64_t uValue = 0;
        CHECK(SynReadLe64(aBytes, &uValue) == (const void*)(aBytes + 8));
        CHECK(uValue == 0x0807060504030201ULL);

        const uint8_t aHigh[8] = {0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF};
        SynReadLe64(aHigh, &uValue);
        CHECK(uValue == 0xFFFFFFFF00000000ULL);
    }

    // ---- the string read: sized from the available bytes
    {
        std::vector<uint8_t> aSrc = {10, 20, 30, 40};
        Obj o;
        *(void**)(o.a.data() + 0x08) = aSrc.data();
        std::string sOut;
        g_nAvail = 4; g_nCopyLen = -1; g_nAdvanced = -1; g_nSlowCalls = 0;
        CHECK(SynReadString(o.p(), &sOut, 4) == true);
        CHECK(sOut.size() == 4);
        CHECK((uint8_t)sOut[0] == 10 && (uint8_t)sOut[3] == 40);
        CHECK(g_nCopyLen == 4);
        CHECK(g_nAdvanced == 4);
        CHECK(g_nSlowCalls == 0);
    }

    // ---- a negative count answers 0 before anything else
    {
        Obj o;
        std::string sOut;
        g_nSlowCalls = 0;
        CHECK(SynReadString(o.p(), &sOut, -1) == false);
        CHECK(g_nSlowCalls == 0);
        CHECK(sOut.empty());
    }

    // ---- asking for more than the available bytes goes to the slow path
    {
        Obj o;
        std::string sOut;
        g_nAvail = 2; g_nSlowCalls = 0; g_bSlowOk = true;
        CHECK(SynReadString(o.p(), &sOut, 10) == true);
        CHECK(g_nSlowCalls == 1);
        CHECK(sOut.empty());            // the fast body did not touch it

        g_bSlowOk = false;
        CHECK(SynReadString(o.p(), &sOut, 10) == false);
    }

    // ---- a zero count still resizes (to zero) but copies nothing
    {
        Obj o;
        std::string sOut = "previous";
        g_nAvail = 8; g_nCopyLen = -1; g_nAdvanced = -1;
        CHECK(SynReadString(o.p(), &sOut, 0) == true);
        CHECK(sOut.empty());
        CHECK(g_nCopyLen == -1);        // the copy is skipped when the count is zero
        CHECK(g_nAdvanced == -1);
    }

    std::printf("SYNDICATE_D68_OK: three constructors and two bodies, %d checks\n", g_nChecks);
    return 0;
}

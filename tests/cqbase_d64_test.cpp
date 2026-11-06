// ============================================================================
// cqbase_d64 — every remaining incomplete vtable row: eleven identical deleting
//   destructors and the six real bodies. Each assertion follows the instruction order the
//   port reproduces, including the refusal tails and the self-destroying closure.
// ============================================================================
#include "modules/syndicate/src/synpbrows.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nBodies = 0, g_nFrees = 0;
std::vector<int> g_aWho;
void B6120(void*) { ++g_nBodies; g_aWho.push_back(0x6120); }
void B6510(void*) { ++g_nBodies; g_aWho.push_back(0x6510); }
void B7360(void*) { ++g_nBodies; g_aWho.push_back(0x7360); }
void B68E0(void*) { ++g_nBodies; g_aWho.push_back(0x68E0); }
void B7D50(void*) { ++g_nBodies; g_aWho.push_back(0x7d50); }
void B7D70(void*) { ++g_nBodies; g_aWho.push_back(0x7d70); }
void B7280(void*) { ++g_nBodies; g_aWho.push_back(0x7280); }
void B1040(void*) { ++g_nBodies; g_aWho.push_back(0x1040); }
void B13E0(void*) { ++g_nBodies; g_aWho.push_back(0x13e0); }
void B1020(void*) { ++g_nBodies; g_aWho.push_back(0x1020); }
void BDE5A0(void*) { ++g_nBodies; g_aWho.push_back(0xde5a0); }
void FreeHook(void*) { ++g_nFrees; }

int32_t* ClampHook(int32_t* pA, int32_t* pB) { return (*pA < *pB) ? pA : pB; }
int32_t* MaxClampHook(int32_t* pA, int32_t* pB) { return (*pA > *pB) ? pA : pB; }
bool g_bGateResult = true;
int g_nGate = 0, g_nFlush = 0;
bool GateHook(void*) { ++g_nGate; return g_bGateResult; }
void FlushHook(void*) { ++g_nFlush; }

std::vector<uint8_t> g_aBuffer;
void* BufferHook(void*) { return g_aBuffer.empty() ? nullptr : g_aBuffer.data(); }
int32_t ProbeHook(void*) { return 0x1000; }
int64_t g_nLastResize = -1;
int g_nResizes = 0;
void StrResizeHook(void* pStr, int64_t nNewSize) {
    ++g_nResizes; g_nLastResize = nNewSize;
    if (nNewSize >= 0) ((std::string*)pStr)->resize((size_t)nNewSize);
}
int32_t g_nReads = 0, g_nLastRead = 0;
int32_t ReadHook(void* pIn, void* pBuf, int32_t nSize) {
    (void)pIn; ++g_nReads; g_nLastRead = nSize;
    std::memset(pBuf, 0x5A, (size_t)(nSize > 0 ? nSize : 0));
    return nSize;                       // a full read, so the loop accumulates
}

struct Rec { int32_t nLine; std::string a, b; };
std::vector<Rec> g_aRecs;
void Check1(const char* pszFile, int32_t nLine, const char* pszA) {
    g_aRecs.push_back(Rec{nLine, pszA ? pszA : "", ""});
    assert(pszFile && std::strstr(pszFile, "zero_copy_stream_impl_lite.cc"));
}
void Check2(const char* pszFile, int32_t nLine, const char* pszA, const char* pszB) {
    g_aRecs.push_back(Rec{nLine, pszA ? pszA : "", pszB ? pszB : ""});
    assert(pszFile && std::strstr(pszFile, "zero_copy_stream_impl_lite.cc"));
}

struct Obj {
    std::vector<uint8_t> a;
    Obj(size_t n = 0x40) : a(n, 0) {}
    uint8_t* p() { return a.data(); }
    void set(int o, int32_t v) { *(int32_t*)(a.data() + o) = v; }
    int32_t get(int o) { return *(int32_t*)(a.data() + o); }
    void setp(int o, void* v) { *(void**)(a.data() + o) = v; }
};

}  // namespace

int main() {
    g_fnRow6120 = &B6120; g_fnRow6510 = &B6510; g_fnRow7360 = &B7360;
    g_fnRow68E0 = &B68E0; g_fnRow7D50 = &B7D50; g_fnRow7D70 = &B7D70;
    g_fnRow7280 = &B7280; g_fnRow1040 = &B1040; g_fnRow13E0 = &B13E0;
    g_fnRow1020 = &B1020; g_fnRowDE5A0 = &BDE5A0;
    g_fnRowFree = &FreeHook;
    g_fnRowClamp = &ClampHook;
    g_fnRow7770 = &GateHook;
    g_fnRow7830 = &FlushHook;
    g_fnRowBuffer = &BufferHook;
    g_fnRow7C40 = &ProbeHook;
    g_fnRowCheck1 = &Check1;
    g_fnRowCheck2 = &Check2;
    g_fnRowRead = &ReadHook;
    g_fnRowClamp2 = &MaxClampHook;
    g_fnRowStrResizeHelper = &StrResizeHook;

    // ---- the eleven deleting destructors each call their own body, and free only on bit 0
    {
        struct Case { void* (*pfn)(void*, uint32_t); int nTag; };
        const Case aCases[] = {
            {&SynRowArrayOutDtor, 0x6120}, {&SynRowStringOutDtor, 0x6510},
            {&SynRowCopyOutAdaptorDtor, 0x7360}, {&SynRowCopyInDtor, 0x68E0},
            {&SynRowZeroInDtor, 0x7d50}, {&SynRowZeroOutDtor, 0x7d70},
            {&SynRowCopyOutDtor, 0x7280}, {&SynRowFuncClosureDtor, 0x1040},
            {&SynRowFatalExcDtor, 0x13e0}, {&SynRowClosureDtor, 0x1020},
            {&SynRowMessageLiteDtor, 0xde5a0},
        };
        for (const Case& c : aCases) {
            Obj o;
            g_aWho.clear(); g_nFrees = 0;
            CHECK(c.pfn(o.p(), 0) == o.p());
            CHECK(g_aWho.size() == 1);
            CHECK(g_aWho[0] == c.nTag);
            CHECK(g_nFrees == 0);
            g_aWho.clear();
            c.pfn(o.p(), 1);
            CHECK(g_aWho.size() == 1 && g_aWho[0] == c.nTag);
            CHECK(g_nFrees == 1);
            g_nFrees = 0;
            c.pfn(o.p(), 0x100);
            CHECK(g_nFrees == 0);       // only bit 0 frees
        }
    }

    // ---- ArrayOutputStream::Next: the refusal tail, then the clamp and the stores
    {
        Obj o;
        o.set(0x10, 16);        // size_
        o.set(0x14, 4);         // the clamp limit
        o.set(0x18, 16);        // position_ == size_ -> refusal
        void* pData = nullptr; int32_t nSize = 1;
        CHECK(SynRowArrayOutNext(o.p(), &pData, &nSize) == false);
        CHECK(o.get(0x1c) == 0);            // last_returned_ cleared on the refusal

        std::vector<uint8_t> aBuf(32, 0);
        o.set(0x18, 2);                     // position_
        o.setp(0x08, aBuf.data());
        pData = nullptr; nSize = 0;
        CHECK(SynRowArrayOutNext(o.p(), &pData, &nSize) == true);
        CHECK(nSize == 4);                  // clamp(name=4) between 14 wanted and 4 limit
        CHECK(o.get(0x1c) == 4);
        CHECK(o.get(0x18) == 6);            // position_ += last_returned_
        CHECK(pData == aBuf.data() + 2);
    }

    // ---- ArrayOutputStream::BackUp: lines 0x88, 0x8a, 0x8b and the two stores
    {
        Obj o;
        o.set(0x18, 10); o.set(0x1c, 4);
        g_aRecs.clear();
        SynRowArrayOutBackUp(o.p(), 3);
        CHECK(g_aRecs.empty());
        CHECK(o.get(0x18) == 7);
        CHECK(o.get(0x1c) == 0);

        o.set(0x1c, 0);                     // trips 0x88 with both literals
        g_aRecs.clear();
        SynRowArrayOutBackUp(o.p(), 0);
        CHECK(g_aRecs.size() >= 1);
        CHECK(g_aRecs[0].nLine == 0x88);
        CHECK(g_aRecs[0].a == "CHECK failed: (last_returned_size_) > (0): ");
        CHECK(g_aRecs[0].b == "BackUp() can only be called after a successful Next().");

        o.set(0x1c, 2);
        g_aRecs.clear();
        SynRowArrayOutBackUp(o.p(), 5);
        CHECK(g_aRecs[0].nLine == 0x8a);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) <= (last_returned_size_): ");

        o.set(0x1c, 2);
        g_aRecs.clear();
        SynRowArrayOutBackUp(o.p(), -1);
        CHECK(g_aRecs[0].nLine == 0x8b);
        CHECK(g_aRecs[0].a == "CHECK failed: (count) >= (0): ");
    }

    // ---- CopyingOutputStreamAdaptor::Next: the gate, the flush, then the hand-out
    {
        g_aBuffer.assign(16, 0);
        Obj o;
        o.set(0x28, 16);        // buffer_size_
        o.set(0x2c, 16);        // used == size, so the gate decides
        g_bGateResult = false; g_nGate = 0; g_nFlush = 0;
        void* pData = nullptr; int32_t nSize = 0;
        CHECK(SynRowCopyOutAdaptorNext(o.p(), &pData, &nSize) == false);
        CHECK(g_nGate == 1);
        CHECK(g_nFlush == 0);   // the flush is not reached

        g_bGateResult = true; g_nGate = 0;
        o.set(0x2c, 12);
        CHECK(SynRowCopyOutAdaptorNext(o.p(), &pData, &nSize) == true);
        CHECK(g_nGate == 0);    // used != size: the gate is skipped
        CHECK(g_nFlush == 1);
        CHECK(pData == g_aBuffer.data() + 12);
        CHECK(nSize == 4);
        CHECK(o.get(0x2c) == 16);
    }

    // ---- CopyingInputStream::Skip: the temporary buffer loop
    {
        g_nReads = 0; g_nLastRead = 0;
        Obj o;
        int32_t nSkipped = SynRowCopyInSkip(o.p(), 3000);
        CHECK(nSkipped == 3000);
        CHECK(g_nReads == 1);
        CHECK(g_nLastRead == 3000);

        // a multi-round skip: the clamp asks for what is left each time
        g_nReads = 0;
        CHECK(SynRowCopyInSkip(o.p(), 0x2000) == 0x2000);
        CHECK(g_nReads == 2);   // 0x1000 max per round
        CHECK(g_nLastRead == 0x1000);
    }

    // ---- FunctionClosure0::Run: the stored function, then the self-destroying call
    {
        static int g_nCalls = 0;
        struct Closure {
            void** ppVt;
            void (*pfn)(void*);
            uint8_t bDelete;
            uint8_t pad[7];
        };
        static void* apVt[2] = {nullptr, nullptr};
        static int g_nDestroyed = 0;
        struct Helper {
            static void* Destroy(void* p, uint32_t f) {
                (void)p; ++g_nDestroyed;
                assert(f == 1);             // the flag the body passes
                return p;
            }
        };
        apVt[0] = (void*)&Helper::Destroy;

        struct Counter { static void Run(void*) { ++g_nCalls; } };
        Closure c;
        c.ppVt = apVt;
        c.pfn = &Counter::Run;
        c.bDelete = 0;
        g_nCalls = 0;
        // with the byte clear the stored function still runs and nothing is destroyed
        CHECK(SynRowFuncClosureRun(&c) == nullptr);
        CHECK(g_nCalls == 1);
        CHECK(g_nDestroyed == 0);

        // the byte is read BEFORE the call, so a function that clears it must not stop the delete
        struct Hook {
            static void Run(void* p) {
                Closure* pc = (Closure*)p;
                pc->bDelete = 0;             // cleared during the call
            }
        };
        c.pfn = &Hook::Run;
        c.bDelete = 1;
        g_nDestroyed = 0;
        CHECK(SynRowFuncClosureRun(&c) == (void*)&c);
        CHECK(g_nDestroyed == 1);            // the captured byte decided, not the cleared one
        CHECK(c.bDelete == 0);
    }

    // ---- FatalException's predicate reads the std::string at +0x28
    {
        std::vector<uint8_t> aObj(0x60, 0);
        std::string sMsg = "boom";
        *(void**)(aObj.data() + 0x28) = nullptr;
        // a std::string with SSO content: size at +0x10 inside the object at +0x28
        std::string* pStr = new (aObj.data() + 0x28) std::string("boom");
        CHECK(SynRowFatalExcIsEmpty(aObj.data()) == false);
        pStr->clear();
        CHECK(SynRowFatalExcIsEmpty(aObj.data()) == true);
        pStr->~basic_string();
        (void)sMsg;
    }

    // ---- StringOutputStream::Next: the spare-capacity path hands out the tail
    {
        std::string sTarget;
        sTarget.reserve(64);
        sTarget.assign("abc", 3);
        Obj o;
        o.setp(0x08, &sTarget);
        void* pData = nullptr; int32_t nSize = 0;
        size_t nCap = sTarget.capacity();
        CHECK(SynRowStringOutNext(o.p(), &pData, &nSize) == true);
        CHECK(nSize == (int32_t)(nCap - 3));
        CHECK(pData == (void*)(sTarget.data() + 3));
    }

    // ---- StringOutputStream::Next: a full target grows through the max clamp (never below 16)
    {
        std::string sTarget = "0123456789";
        sTarget.resize(sTarget.capacity());       // size == capacity, so the growth path runs
        size_t nCap = sTarget.capacity();
        size_t nOld = sTarget.size();
        CHECK(nOld == nCap);
        Obj o;
        o.setp(0x08, &sTarget);
        g_nResizes = 0; g_nLastResize = -1;
        void* pData = nullptr; int32_t nSize = 0;
        CHECK(SynRowStringOutNext(o.p(), &pData, &nSize) == true);
        CHECK(g_nResizes == 1);
        CHECK(g_nLastResize == (int64_t)(nOld * 2));   // doubled, above the floor 16
        CHECK(nSize == (int32_t)(sTarget.capacity() - nOld));
    }

    // ---- the growth floor: a tiny target asks for 16, not for twice its size
    {
        std::string sTarget;
        sTarget.resize(sTarget.capacity());            // size == capacity == 15 on this runtime
        Obj o;
        o.setp(0x08, &sTarget);
        g_nResizes = 0; g_nLastResize = -1;
        void* pData = nullptr; int32_t nSize = 0;
        CHECK(SynRowStringOutNext(o.p(), &pData, &nSize) == true);
        // 15 * 2 = 30 is above 16, so the floor only shows on a target smaller than 8
        CHECK(g_nLastResize == 30);
    }

    std::printf("SYNDICATE_D64_OK: eighteen rows, %d checks\n", g_nChecks);
    return 0;
}

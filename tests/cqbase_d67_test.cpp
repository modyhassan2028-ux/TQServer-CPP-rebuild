// ============================================================================
// cqbase_d67 — four coded-reader bodies. The seams the originals call (the stream's Next,
//   the consumer, the advance and the general varint read) are faked, so each body's own
//   decisions are what the assertions pin: when it refreshes, what it zeroes on failure, and
//   where the single-byte varint stops being enough.
// ============================================================================
#include "modules/syndicate/src/synpbcodec.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

// the fake underlying stream
std::vector<uint8_t> g_aSource;
size_t g_nCursor = 0;
bool g_bStreamOk = true;
int g_nStreamCalls = 0;
int32_t g_nChunk = 8;
bool StreamNext(void* pStream, void** ppData, int32_t* pnSize) {
    (void)pStream; ++g_nStreamCalls;
    if (!g_bStreamOk) return false;
    size_t nLeft = g_aSource.size() - g_nCursor;
    int32_t n = (int32_t)(nLeft < (size_t)g_nChunk ? nLeft : (size_t)g_nChunk);
    if (n <= 0) return false;
    *ppData = g_aSource.data() + g_nCursor;
    *pnSize = n;
    g_nCursor += (size_t)n;
    return true;
}
int32_t g_nConsumed = -1;
void ConsumeHook(void*, int32_t n) { g_nConsumed = n; }
int32_t g_nAdvanced = -1;
void AdvanceHook(void*, int32_t n) { g_nAdvanced = n; }
bool g_bGeneralOk = true;
uint64_t g_uGeneralValue = 0xDEAD;
int g_nGeneralCalls = 0;
bool GeneralHook(void*, uint64_t* pValue) {
    ++g_nGeneralCalls; *pValue = g_uGeneralValue; return g_bGeneralOk;
}

// layout A: +0x00 stream, +0x08 buffer, +0x10 size(int), +0x14 total(int), +0x18 flag
struct ObjA {
    std::vector<uint8_t> a;
    ObjA() : a(0x20, 0) {}
    uint8_t* p() { return a.data(); }
    void set(int o, int32_t v) { *(int32_t*)(a.data() + o) = v; }
    int32_t get(int o) { return *(int32_t*)(a.data() + o); }
    void setp(int o, void* v) { *(void**)(a.data() + o) = v; }
    void* getp(int o) { return *(void**)(a.data() + o); }
};

}  // namespace

int main() {
    g_fnCodecStreamNext = &StreamNext;
    g_fnCodecConsume = &ConsumeHook;
    g_fnCodecAdvance = &AdvanceHook;
    g_fnCodecReadVarint = &GeneralHook;

    // ---- Refresh: a successful refill stores the buffer and adds to the total
    {
        g_aSource = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        g_nCursor = 0; g_bStreamOk = true; g_nStreamCalls = 0; g_nChunk = 8;
        ObjA o;
        o.setp(0x00, (void*)0x1234);        // the stream pointer handed to the seam
        o.set(0x14, 100);                   // total_
        CHECK(SynCodecRefresh(o.p()) == true);
        CHECK(g_nStreamCalls == 1);
        CHECK(o.getp(0x08) == (void*)g_aSource.data());
        CHECK(o.get(0x10) == 8);            // the size the stream reported
        CHECK(o.get(0x14) == 108);          // total_ grew by it
    }

    // ---- Refresh failure: buffer and size zeroed, the end flag set
    {
        g_bStreamOk = false;
        ObjA o;
        o.setp(0x08, (void*)0xAAAA);
        o.set(0x10, 32);
        o.set(0x14, 7);
        CHECK(SynCodecRefresh(o.p()) == false);
        CHECK(o.getp(0x08) == nullptr);
        CHECK(o.get(0x10) == 0);
        CHECK(o.get(0x14) == 7);            // the total is untouched on failure
        CHECK(o.p()[0x18] == 1);
    }

    // ---- Next: already buffered contents are handed over without touching the stream
    {
        g_aSource = {9, 9, 9}; g_nCursor = 0; g_bStreamOk = true; g_nStreamCalls = 0;
        ObjA o;
        static uint8_t aBlock[4] = {1, 2, 3, 4};
        o.setp(0x08, aBlock);
        o.set(0x10, 4);
        void* pData = nullptr; int32_t nSize = 0;
        CHECK(SynCodecNext(o.p(), &pData, &nSize) == true);
        CHECK(g_nStreamCalls == 0);
        CHECK(pData == (void*)aBlock);
        CHECK(nSize == 4);

        // an empty buffer forces a refresh
        o.set(0x10, 0);
        CHECK(SynCodecNext(o.p(), &pData, &nSize) == true);
        CHECK(g_nStreamCalls == 1);
        CHECK(pData == (void*)g_aSource.data());
        CHECK(nSize == 3);
    }

    // ---- Next with a failing stream answers 0
    {
        g_bStreamOk = false;
        ObjA o;
        o.set(0x10, 0);
        void* pData = nullptr; int32_t nSize = 0;
        CHECK(SynCodecNext(o.p(), &pData, &nSize) == false);
    }

    // ---- Skip: a negative count answers 0 and touches nothing
    {
        g_nConsumed = -1;
        ObjA o;
        CHECK(SynCodecSkip(o.p(), -1) == false);
        CHECK(g_nConsumed == -1);
    }

    // ---- Skip inside the buffered block consumes the count and answers 1
    {
        g_aSource = {1, 2, 3, 4, 5, 6, 7, 8}; g_nCursor = 0; g_bStreamOk = true; g_nStreamCalls = 0;
        ObjA o;
        o.set(0x10, 8);
        g_nConsumed = -1;
        CHECK(SynCodecSkip(o.p(), 5) == true);
        CHECK(g_nStreamCalls == 0);
        CHECK(g_nConsumed == 5);
    }

    // ---- Skip larger than the block refreshes for the remainder
    {
        g_aSource = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        g_nCursor = 0; g_bStreamOk = true; g_nStreamCalls = 0; g_nChunk = 8;
        ObjA o;
        o.set(0x10, 8);                     // 8 buffered, skip 10 -> refresh gives 4 more
        g_nConsumed = -1;
        CHECK(SynCodecSkip(o.p(), 10) == true);
        // the body subtracts first and then refreshes, so the size it ends up with is the one
        // the refresh delivered, not a leftover: one call, eight bytes, two consumed
        CHECK(g_nStreamCalls == 1);
        CHECK(o.get(0x10) == 8);
        CHECK(g_nConsumed == 2);            // 10 - 8
    }

    // ---- Skip: with a genuinely pre-filled block the refresh really only fetches the rest
    {
        g_aSource = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        g_nCursor = 8;                      // the first eight bytes are already in the block
        g_bStreamOk = true; g_nStreamCalls = 0; g_nChunk = 8;
        ObjA o;
        o.set(0x10, 8);
        g_nConsumed = -1;
        CHECK(SynCodecSkip(o.p(), 10) == true);
        CHECK(g_nStreamCalls == 1);
        CHECK(o.get(0x10) == 4);            // only the remainder was fetched
        CHECK(g_nConsumed == 2);
    }

    // ---- Skip stops when the refresh fails
    {
        g_bStreamOk = false;
        ObjA o;
        o.set(0x10, 2);
        CHECK(SynCodecSkip(o.p(), 10) == false);
    }

    // ---- the single-byte varint
    {
        std::vector<uint8_t> aBuf = {0x2A, 0x80};
        uint8_t* pBuf = aBuf.data();
        uint8_t* pEnd = aBuf.data() + aBuf.size();
        std::vector<uint8_t> aObj(0x20, 0);
        *(void**)(aObj.data() + 0x08) = pBuf;
        *(void**)(aObj.data() + 0x10) = pEnd;
        uint64_t uValue = 0;
        g_nAdvanced = -1; g_nGeneralCalls = 0;
        CHECK(SynCodecReadVarintFast(aObj.data(), &uValue) == true);
        CHECK(uValue == 0x2A);
        CHECK(g_nAdvanced == 1);
        CHECK(g_nGeneralCalls == 0);

        // a byte at or above 0x80 falls through to the general read
        *(void**)(aObj.data() + 0x08) = pBuf + 1;
        g_nGeneralCalls = 0;
        g_bGeneralOk = true;
        CHECK(SynCodecReadVarintFast(aObj.data(), &uValue) == true);
        CHECK(g_nGeneralCalls == 1);
        CHECK(uValue == 0xDEAD);

        // and an exhausted buffer does the same
        *(void**)(aObj.data() + 0x08) = pEnd;
        g_nGeneralCalls = 0;
        SynCodecReadVarintFast(aObj.data(), &uValue);
        CHECK(g_nGeneralCalls == 1);
    }

    std::printf("SYNDICATE_D67_OK: four coded-reader bodies, %d checks\n", g_nChecks);
    return 0;
}

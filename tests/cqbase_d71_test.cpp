// ============================================================================
// cqbase_d71 — four coded-output bodies. The correction that matters is recorded here: the
//   helpers write little-endian values, so these are writers, not readers. The fake stream
//   records the vt[2] flush and the vt[4] write so the buffered-versus-direct split is proved.
// ============================================================================
#include "modules/syndicate/src/synpbraw.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

int g_nFlushes = 0, g_nFlushCount = -1;
int g_nWrites = 0, g_nWriteCount = -1; const void* g_pWriteSrc = nullptr;
bool g_bWriteOk = true;
void FlushHook(void*, int32_t n) { ++g_nFlushes; g_nFlushCount = n; }
bool WriteHook(void*, const void* pSrc, int32_t n) {
    ++g_nWrites; g_pWriteSrc = pSrc; g_nWriteCount = n; return g_bWriteOk;
}
int32_t g_nConsumed = -1;
void ConsumeHook(void*, int32_t n) { g_nConsumed = n; }
int32_t g_nAppends = 0, g_nAppendCount = -1; std::vector<uint8_t> g_aAppended;
bool AppendHook(void*, const void* pSrc, int32_t n) {
    ++g_nAppends; g_nAppendCount = n;
    const uint8_t* b = (const uint8_t*)pSrc;
    g_aAppended.assign(b, b + n);
    return true;
}
void* Le32Hook(uint32_t uValue, void* pDst) {
    uint8_t* d = (uint8_t*)pDst;
    for (int i = 0; i < 4; ++i) d[i] = (uint8_t)(uValue >> (8 * i));
    return d + 4;
}
void* Le64Hook(uint64_t uValue, void* pDst) {
    uint8_t* d = (uint8_t*)pDst;
    for (int i = 0; i < 8; ++i) d[i] = (uint8_t)(uValue >> (8 * i));
    return d + 8;
}
void* VarintHook(uint64_t uValue, void* pDst) {
    uint8_t* d = (uint8_t*)pDst;
    while (uValue > 0x7f) { *d++ = (uint8_t)((uValue & 0x7f) | 0x80); uValue >>= 7; }
    *d++ = (uint8_t)uValue;
    return d;
}

struct Obj {
    std::vector<uint8_t> a;
    Obj(size_t n = 0x40) : a(n, 0) {}
    uint8_t* p() { return a.data(); }
    void set(int o, int32_t v) { *(int32_t*)(a.data() + o) = v; }
    int32_t get(int o) { return *(int32_t*)(a.data() + o); }
    void setp(int o, void* v) { *(void**)(a.data() + o) = v; }
    void* getp(int o) { return *(void**)(a.data() + o); }
};
struct Stream { void** ppVt; };

}  // namespace

int main() {
    g_fnRawConsume = &ConsumeHook;
    g_fnRawAppend = &AppendHook;
    g_fnRawLe32 = &Le32Hook;
    g_fnRawLe64 = &Le64Hook;
    g_fnRawVarint = &VarintHook;

    static void* apVt[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    apVt[2] = (void*)&FlushHook;
    apVt[4] = (void*)&WriteHook;
    Stream stream;
    stream.ppVt = apVt;

    // ---- WriteRaw that fits in the buffer goes through the append helper only
    {
        Obj o;
        o.set(0x10, 10);
        std::vector<uint8_t> aData(4, 0xAB);
        g_nAppendCount = -1; g_nAppends = 0; g_nWrites = 0; g_nFlushes = 0;
        SynOutWriteRaw(o.p(), aData.data(), 4);
        CHECK(g_nAppends == 1);
        CHECK(g_nAppendCount == 4);
        CHECK(g_nWrites == 0 && g_nFlushes == 0);
    }

    // ---- WriteRaw beyond the buffer: flush what is buffered, then write straight out
    {
        Obj o;
        o.setp(0x00, &stream);
        std::vector<uint8_t> aBuf(16, 1);
        o.setp(0x08, aBuf.data());
        o.set(0x10, 6);
        o.set(0x14, 100);
        std::vector<uint8_t> aData(32, 0xCD);
        g_nFlushes = 0; g_nFlushCount = -1; g_nWrites = 0; g_nWriteCount = -1; g_bWriteOk = true;
        SynOutWriteRaw(o.p(), aData.data(), 20);
        CHECK(g_nFlushes == 1);
        CHECK(g_nFlushCount == 6);          // the buffered size
        CHECK(g_nWrites == 1);
        CHECK(g_pWriteSrc == aData.data());
        CHECK(g_nWriteCount == 20);
        CHECK(o.getp(0x08) == nullptr);     // the buffer is cleared
        CHECK(o.get(0x10) == 0);
        CHECK(o.get(0x14) == 114);          // 100 - 6 + 20, exactly as the body does it
        CHECK(o.p()[0x18] == 0);
    }

    // ---- a zero answer from the stream sets the error bit, and an existing bit survives
    {
        Obj o;
        o.setp(0x00, &stream);
        o.set(0x10, 0);
        o.set(0x14, 5);
        std::vector<uint8_t> aData(8, 0);
        g_bWriteOk = false;
        SynOutWriteRaw(o.p(), aData.data(), 8);
        CHECK(o.p()[0x18] == 1);
        CHECK(o.get(0x14) == 13);           // nothing was flushed
        o.p()[0x18] = 2;
        g_bWriteOk = true;
        SynOutWriteRaw(o.p(), aData.data(), 8);
        CHECK(o.p()[0x18] == 2);            // the OR keeps what was there
    }

    // ---- WriteLittleEndian32 fast path writes into the buffer and consumes four
    {
        Obj o;
        std::vector<uint8_t> aBuf(8, 0);
        o.setp(0x08, aBuf.data());
        o.set(0x10, 8);
        g_nConsumed = -1; g_nAppends = 0;
        SynOutWriteLe32(o.p(), 0x12345678u);
        CHECK(aBuf[0] == 0x78 && aBuf[1] == 0x56 && aBuf[2] == 0x34 && aBuf[3] == 0x12);
        CHECK(g_nConsumed == 4);
        CHECK(g_nAppends == 0);
    }

    // ---- the slow path assembles into a local and appends it
    {
        Obj o;
        o.set(0x10, 3);                     // under four
        g_nConsumed = -1; g_nAppends = 0; g_nAppendCount = -1;
        SynOutWriteLe32(o.p(), 0xAABBCCDDu);
        CHECK(g_nAppends == 1);
        CHECK(g_nAppendCount == 4);
        CHECK(g_aAppended.size() == 4);
        CHECK(g_aAppended[0] == 0xDD && g_aAppended[3] == 0xAA);
        CHECK(g_nConsumed == -1);
    }

    // ---- WriteLittleEndian64 needs eight
    {
        Obj o;
        std::vector<uint8_t> aBuf(8, 0);
        o.setp(0x08, aBuf.data());
        o.set(0x10, 8);
        g_nConsumed = -1;
        SynOutWriteLe64(o.p(), 0x0807060504030201ULL);
        CHECK(g_nConsumed == 8);
        CHECK(aBuf[0] == 0x01 && aBuf[7] == 0x08);

        Obj o2;
        o2.set(0x10, 7);
        g_nAppendCount = -1; g_nConsumed = -1;
        SynOutWriteLe64(o2.p(), 0x0807060504030201ULL);
        CHECK(g_nAppendCount == 8);
        CHECK(g_nConsumed == -1);
    }

    // ---- WriteVarint64 with room goes straight into the buffer
    {
        Obj o;
        std::vector<uint8_t> aBuf(16, 0);
        o.setp(0x08, aBuf.data());
        o.set(0x10, 12);
        g_nConsumed = -1; g_nAppends = 0;
        SynOutWriteVarint64(o.p(), 300);
        CHECK(g_nConsumed == 2);
        CHECK(aBuf[0] == 0xAC && aBuf[1] == 0x02);
        CHECK(g_nAppends == 0);
    }

    // ---- without room the local builder runs
    {
        Obj o;
        o.set(0x10, 5);                     // under ten
        g_nAppendCount = -1;
        SynOutWriteVarint64(o.p(), 300);
        CHECK(g_nAppendCount == 2);
        CHECK(g_aAppended.size() == 2);
        CHECK(g_aAppended[0] == 0xAC && g_aAppended[1] == 0x02);

        g_nAppendCount = -1;
        SynOutWriteVarint64(o.p(), 0xFFFFFFFFFFFFFFFFULL);
        CHECK(g_nAppendCount == 10);
        for (int i = 0; i < 9; ++i) CHECK(g_aAppended[(size_t)i] == 0xFF);
        CHECK(g_aAppended[9] == 0x01);
    }

    std::printf("SYNDICATE_D71_OK: four coded-output bodies, %d checks\n", g_nChecks);
    return 0;
}

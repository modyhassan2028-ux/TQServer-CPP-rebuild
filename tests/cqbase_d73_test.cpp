// ============================================================================
// cqbase_d73 — the varint pair. The reader is exercised on every byte boundary where the
//   accumulator splits (bit 28 and bit 56), because that is where the three-part assemble
//   would go wrong, and on the malformed eleven-byte case.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "modules/syndicate/src/synpbvarint.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

// ---- the reader object: +0x08 position, +0x10 end
struct Reader {
    uint8_t a[0x40];
    void setPos(uint8_t* p) { *(uint8_t**)(a + 0x08) = p; }
    void setEnd(uint8_t* p) { *(uint8_t**)(a + 0x10) = p; }
};

static std::vector<uint8_t> Encode(uint64_t u) {
    std::vector<uint8_t> out;
    while (u >= 0x80) { out.push_back((uint8_t)(u | 0x80)); u >>= 7; }
    out.push_back((uint8_t)u);
    return out;
}

static int32_t g_nAvail = 0;
static int32_t g_nAdvanced = -1;
static bool g_bSlowCalled = false;
static int32_t AvailHook(void*) { return g_nAvail; }
static void AdvanceHook(void*, int32_t n) { g_nAdvanced = n; }
static bool SlowHook(void*, uint64_t* pOut) { g_bSlowCalled = true; *pOut = 0xDEADBEEF; return false; }

static void ReaderCase(uint64_t uValue) {
    std::vector<uint8_t> aBytes = Encode(uValue);
    aBytes.resize(16, 0);                        // room so the unrolled read never runs off
    Reader r;
    std::memset(&r, 0, sizeof(r));
    r.setPos(aBytes.data());
    r.setEnd(aBytes.data() + 16);
    g_nAvail = 16; g_nAdvanced = -1; g_bSlowCalled = false;
    uint64_t uOut = 0;
    CHECK(SynReadVarint64(&r, &uOut) == true);
    CHECK(g_bSlowCalled == false);
    CHECK(uOut == uValue);
    CHECK(g_nAdvanced == (int32_t)Encode(uValue).size());
}

int main() {
    g_fnViAvail = &AvailHook;
    g_fnViAdvance = &AdvanceHook;
    g_fnViSlow = &SlowHook;

    // ---- every accumulator boundary
    ReaderCase(0);
    ReaderCase(1);
    ReaderCase(127);
    ReaderCase(128);
    ReaderCase(300);
    ReaderCase(0xFFFFFFFu);            // the end of the low accumulator
    ReaderCase(0x10000000ULL);         // the first bit of the middle accumulator
    ReaderCase(0x00FFFFFFFFFFFFFFULL); // middle accumulator filled
    ReaderCase(0x100000000000000ULL);  // the first bit of the top accumulator
    ReaderCase(0xFFFFFFFFFFFFFFFFULL); // the widest value the ten bytes carry

    // ---- the guard falls to the slow path when the buffer cannot hold ten bytes and the last
    //      byte still asks for more
    {
        std::vector<uint8_t> aBytes = {0x01, 0x80};
        Reader r;
        std::memset(&r, 0, sizeof(r));
        r.setPos(aBytes.data());
        r.setEnd(aBytes.data() + 2);
        g_nAvail = 2; g_bSlowCalled = false;
        uint64_t uOut = 0;
        CHECK(SynReadVarint64(&r, &uOut) == false);   // the slow hook answers false
        CHECK(g_bSlowCalled == true);
    }

    // ---- with the same short buffer but a clean last byte the unrolled read is used
    {
        std::vector<uint8_t> aBytes = {0x7F, 0x00, 0x00, 0x00};
        Reader r;
        std::memset(&r, 0, sizeof(r));
        r.setPos(aBytes.data());
        r.setEnd(aBytes.data() + 4);
        g_nAvail = 4; g_bSlowCalled = false; g_nAdvanced = -1;
        uint64_t uOut = 0;
        CHECK(SynReadVarint64(&r, &uOut) == true);
        CHECK(g_bSlowCalled == false);
        CHECK(uOut == 0x7F);
        CHECK(g_nAdvanced == 1);
    }

    // ---- an eleventh byte is malformed and answers false without touching the position
    {
        std::vector<uint8_t> aBytes(12, 0x80);
        aBytes[10] = 0x01;
        Reader r;
        std::memset(&r, 0, sizeof(r));
        r.setPos(aBytes.data());
        r.setEnd(aBytes.data() + 12);
        g_nAvail = 12; g_bSlowCalled = false; g_nAdvanced = -1;
        uint64_t uOut = 0;
        CHECK(SynReadVarint64(&r, &uOut) == false);
        CHECK(g_nAdvanced == -1);            // the advance is never reached
    }

    // ---- the writer: one byte per boundary, the last one without the continuation bit
    {
        struct { uint32_t u; int nLen; } aCases[] = {
            {0u, 1}, {1u, 1}, {127u, 1},
            {128u, 2}, {0x3FFFu, 2},
            {0x4000u, 3}, {0x1FFFFFu, 3},
            {0x200000u, 4}, {0xFFFFFFFu, 4},
            {0x10000000u, 5}, {0xFFFFFFFFu, 5},
        };
        for (auto& c : aCases) {
            uint8_t a[8];
            std::memset(a, 0xCC, sizeof(a));
            void* pEnd = SynWriteVarint32ToArray(c.u, a);
            CHECK(pEnd == a + c.nLen);
            // what it wrote must decode back, and only the last byte may lack the high bit
            for (int i = 0; i < c.nLen - 1; ++i) CHECK((a[i] & 0x80) != 0);
            CHECK((a[c.nLen - 1] & 0x80) == 0);
            uint32_t uBack = 0; int nShift = 0;
            for (int i = 0; i < c.nLen; ++i) { uBack |= (uint32_t)(a[i] & 0x7F) << nShift; nShift += 7; }
            CHECK(uBack == c.u);
        }
    }

    std::printf("SYNDICATE_D73_OK: the varint pair, %d checks\n", g_nChecks);
    return 0;
}

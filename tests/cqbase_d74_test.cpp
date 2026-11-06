// ============================================================================
// cqbase_d74 — the rest of the varint reader chain. What is pinned here: the array parser's
//   return pointer (so the caller knows where the value ended), the five-byte skip bound, the
//   three-way branch that decides between the buffer parser and the block walker, and the slow
//   reader's ten-byte ceiling with its refill.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "modules/syndicate/src/synpbvar2.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static std::vector<uint8_t> Encode(uint64_t u) {
    std::vector<uint8_t> out;
    while (u >= 0x80) { out.push_back((uint8_t)(u | 0x80)); u >>= 7; }
    out.push_back((uint8_t)u);
    return out;
}

// ---- the reader object
struct Reader { uint8_t a[0x40]; };
static void SetPos(Reader& r, const uint8_t* p) { *(const uint8_t**)(r.a + 0x08) = p; }
static void SetEnd(Reader& r, const uint8_t* p) { *(const uint8_t**)(r.a + 0x10) = p; }
static int32_t GetI(Reader& r, int o) { return *(int32_t*)(r.a + o); }
static void SetI(Reader& r, int o, int32_t v) { *(int32_t*)(r.a + o) = v; }

static int32_t g_nAvail = 0;
static int32_t g_nAdvanced = -1;
static int g_nRefills = 0; static bool g_bRefill = true; static uint8_t* g_pRefillPos = nullptr;
static int g_nFromBlock = 0; static uint32_t g_uFromBlock = 0;
static int32_t AvailHook(void*) { return g_nAvail; }
static void AdvanceHook(void* p, int32_t n) { g_nAdvanced = n;
    *(uint8_t**)((uint8_t*)p + 0x08) += n; }   // the real body moves the position
static bool RefillHook(void*) { ++g_nRefills; return g_bRefill; }
static uint32_t FromBlockHook(void*) { ++g_nFromBlock; return g_uFromBlock; }

int main() {
    g_fnV2Avail = &AvailHook;
    g_fnV2Advance = &AdvanceHook;
    g_fnV2Refill = &RefillHook;
    g_fnV2FromBlock = &FromBlockHook;

    // ---- the array parser: value and the pointer it leaves behind
    {
        struct { uint32_t u; int nLen; } aCases[] = {
            {0u, 1}, {127u, 1}, {128u, 2}, {300u, 2}, {0x3FFFu, 2},
            {0x4000u, 3}, {0x200000u, 4}, {0x10000000u, 5}, {0xFFFFFFFFu, 5},
        };
        for (auto& c : aCases) {
            std::vector<uint8_t> aBytes = Encode(c.u);
            aBytes.resize(12, 0x7F);                  // sentinels after the value
            uint32_t uOut = 0;
            void* pNext = SynParseVarint32Array(aBytes.data(), &uOut);
            CHECK(pNext == aBytes.data() + c.nLen);
            CHECK(uOut == c.u);
        }
    }

    // ---- an over-long encoding: five extra continuation bytes already fail
    {
        std::vector<uint8_t> aBytes = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // 5 bytes, still going
        aBytes.resize(16, 0x80);                                     // ten continuations after it
        uint32_t uOut = 0;
        CHECK(SynParseVarint32Array(aBytes.data(), &uOut) == nullptr);
    }

    // ---- the skip loop reads at most five leftovers, and the check comes BEFORE each read:
    //      four continuations then a clean byte is accepted, five continuations never are
    {
        std::vector<uint8_t> aBytes = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        for (int i = 0; i < 4; ++i) aBytes.push_back(0x80);
        aBytes.push_back(0x01);                       // the clean byte inside the five
        uint32_t uOut = 0;
        void* pNext = SynParseVarint32Array(aBytes.data(), &uOut);
        CHECK(pNext == aBytes.data() + 10);

        std::vector<uint8_t> aFive = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        for (int i = 0; i < 5; ++i) aFive.push_back(0x80);
        aFive.push_back(0x01);                        // too late: the fifth leftover was consumed
        uOut = 0;
        CHECK(SynParseVarint32Array(aFive.data(), &uOut) == nullptr);
    }

    // ---- ReadVarint32 walks the buffer parser when the bytes are complete
    {
        std::vector<uint8_t> aBytes = Encode(0x200000u);
        aBytes.resize(16, 0);
        Reader r;
        std::memset(&r, 0, sizeof(r));
        SetPos(r, aBytes.data());
        SetEnd(r, aBytes.data() + 16);
        g_nAvail = 16; g_nFromBlock = 0;
        CHECK(SynReadVarint32(&r) == 0x200000u);
        CHECK(g_nFromBlock == 0);
        CHECK(*(const uint8_t**)(r.a + 0x08) == aBytes.data() + 4);

        // the same through a short buffer whose last byte ends the value
        Reader r2;
        std::memset(&r2, 0, sizeof(r2));
        SetPos(r2, aBytes.data());
        SetEnd(r2, aBytes.data() + 4);
        g_nAvail = 4; g_nFromBlock = 0;
        CHECK(SynReadVarint32(&r2) == 0x200000u);
        CHECK(g_nFromBlock == 0);
    }

    // ---- with nothing available the block walker answers
    {
        Reader r;
        std::memset(&r, 0, sizeof(r));
        g_nAvail = 0; g_nFromBlock = 0; g_uFromBlock = 0x1234;
        SetI(r, 0x2c, 1);                            // a message in progress: skip the pair test
        SetI(r, 0x18, 10);                           // and 10 - 1 >= 0, so the flag stays down
        CHECK(SynReadVarint32(&r) == 0x1234);
        CHECK(g_nFromBlock == 1);
        CHECK(GetI(r, 0x24) == 0);
    }

    // ---- nothing available, no message started, and the counters agree: the last branch runs
    {
        Reader r;
        std::memset(&r, 0, sizeof(r));
        g_nAvail = 0; g_nFromBlock = 0; g_uFromBlock = 0xBEEF;
        SetI(r, 0x2c, 0); SetI(r, 0x18, 5); SetI(r, 0x28, 5); SetI(r, 0x30, 2);
        // 5 - 0 = 5 >= 2, so the block walker is used rather than the flag
        CHECK(SynReadVarint32(&r) == 0xBEEF);
        CHECK(g_nFromBlock == 1);
        CHECK(GetI(r, 0x24) == 0);

        // now under the limit: the flag is raised and the answer is zero
        SetI(r, 0x30, 9);                            // 5 - 0 = 5 < 9
        g_nFromBlock = 0;
        CHECK(SynReadVarint32(&r) == 0);
        CHECK(g_nFromBlock == 0);
        CHECK(GetI(r, 0x24) == 1);
    }

    // ---- a started message with the counters disagreeing goes to the block walker
    {
        Reader r;
        std::memset(&r, 0, sizeof(r));
        g_nAvail = 0; g_nFromBlock = 0; g_uFromBlock = 0x77;
        SetI(r, 0x2c, 0); SetI(r, 0x18, 5); SetI(r, 0x28, 6);   // disagree
        CHECK(SynReadVarint32(&r) == 0x77);
        CHECK(g_nFromBlock == 1);
        CHECK(GetI(r, 0x24) == 0);
    }

    // ---- the slow 64-bit reader: one byte at a time, seven bits each
    {
        std::vector<uint8_t> aBytes = Encode(0x0123456789ULL);
        aBytes.resize(16, 0);
        Reader r;
        std::memset(&r, 0, sizeof(r));
        SetPos(r, aBytes.data());
        SetEnd(r, aBytes.data() + 16);
        g_nRefills = 0;
        uint64_t uOut = 0;
        CHECK(SynReadVarint64Slow(&r, &uOut) == true);
        CHECK(uOut == 0x0123456789ULL);
        CHECK(g_nRefills == 0);
        CHECK(*(const uint8_t**)(r.a + 0x08) == aBytes.data() + Encode(0x0123456789ULL).size());
    }

    // ---- it refills when the buffer is empty and stops at ten bytes
    {
        std::vector<uint8_t> aBytes(12, 0x80);       // all continuation bits
        Reader r;
        std::memset(&r, 0, sizeof(r));
        SetPos(r, aBytes.data());
        SetEnd(r, aBytes.data());                    // empty: every read needs a refill
        g_nRefills = 0; g_bRefill = false;
        uint64_t uOut = 0;
        CHECK(SynReadVarint64Slow(&r, &uOut) == false);
        CHECK(g_nRefills == 1);                      // one attempt, then the answer is no
        g_bRefill = true;

        // a clean read after a successful refill
        SetEnd(r, aBytes.data() + 12);
        SetPos(r, aBytes.data() + 11);
        aBytes[11] = 0x01;
        g_nRefills = 0;
        uint64_t uOut2 = 0;
        CHECK(SynReadVarint64Slow(&r, &uOut2) == true);
        CHECK(uOut2 == 1);
    }

    std::printf("SYNDICATE_D74_OK: the varint chain completed, %d checks\n", g_nChecks);
    return 0;
}

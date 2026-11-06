// ============================================================================
// cqbase_d76 — three reader helpers. The 32-bit-through-64 helper is checked for the truncation
//   it performs, the fast reader for which of its two routes it takes, and the bound reset for
//   the order it moves the end pointer (forward by the held-back bytes, then back again).
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "modules/syndicate/src/synpbread2.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static int32_t g_nAvail = 0; static int g_nAvailCalls = 0;
static uint64_t g_u64 = 0; static bool g_b64Ok = true; static int g_n64Calls = 0;
static int32_t* g_pMinReturn = nullptr; static int g_nClampCalls = 0;
static int32_t AvailHook(void*) { ++g_nAvailCalls; return g_nAvail; }
static bool Read64Hook(void*, uint64_t* pOut) { ++g_n64Calls; *pOut = g_u64; return g_b64Ok; }
static int32_t* ClampHook(int32_t* pA, int32_t* pB) { ++g_nClampCalls; return (*pA < *pB) ? pA : pB; }

struct Obj { uint8_t a[0x40]; };
static void SetP(Obj& o, int off, void* v) { *(void**)(o.a + off) = v; }
static void* GetP(Obj& o, int off) { return *(void**)(o.a + off); }
static void SetI(Obj& o, int off, int32_t v) { *(int32_t*)(o.a + off) = v; }
static int32_t GetI(Obj& o, int off) { return *(int32_t*)(o.a + off); }

int main() {
    g_fnR2Avail = &AvailHook;
    g_fnR2ReadVarint64 = &Read64Hook;
    g_fnR2ClampMin = &ClampHook;

    // ---- the 64-bit read keeps only the low word
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        g_u64 = 0x1122334455667788ULL; g_b64Ok = true; g_n64Calls = 0;
        uint32_t uOut = 0;
        CHECK(SynReadVarint32Via64(&o, &uOut) == true);
        CHECK(uOut == 0x55667788u);
        CHECK(g_n64Calls == 1);

        // a refusal from the 64-bit reader is passed straight through, and the value is left
        g_b64Ok = false; uOut = 0xAAAAAAAAu;
        CHECK(SynReadVarint32Via64(&o, &uOut) == false);
        CHECK(uOut == 0xAAAAAAAAu);
        g_b64Ok = true;
    }

    // ---- the fast reader: complete bytes go through the array parser
    {
        std::vector<uint8_t> aBytes = {0xAC, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, aBytes.data());
        SetP(o, 0x10, aBytes.data() + 12);
        g_nAvail = 12; g_n64Calls = 0;
        uint32_t uOut = 0;
        CHECK(SynReadVarint32Fast(&o, &uOut) == true);
        CHECK(uOut == 300);
        CHECK(GetP(o, 0x08) == aBytes.data() + 2);   // the parser moved the position
        CHECK(g_n64Calls == 0);
    }

    // ---- fewer than ten bytes but the last one ends the value: still the array parser
    {
        std::vector<uint8_t> aBytes = {0xAC, 0x02, 0x00, 0x00};
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, aBytes.data());
        SetP(o, 0x10, aBytes.data() + 4);
        g_nAvail = 4; g_n64Calls = 0;
        uint32_t uOut = 0;
        CHECK(SynReadVarint32Fast(&o, &uOut) == true);
        CHECK(uOut == 300);
        CHECK(g_n64Calls == 0);
    }

    // ---- an empty buffer falls to the 64-bit reader
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 0x20);
        SetP(o, 0x10, o.a + 0x20);
        g_nAvail = 0; g_n64Calls = 0; g_u64 = 0x99; g_b64Ok = true;
        uint32_t uOut = 0;
        CHECK(SynReadVarint32Fast(&o, &uOut) == true);
        CHECK(uOut == 0x99);
        CHECK(g_n64Calls == 1);
    }

    // ---- an unfinished value at the end of a short buffer also falls to the 64-bit reader
    {
        std::vector<uint8_t> aBytes = {0xFF, 0xFF};
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, aBytes.data());
        SetP(o, 0x10, aBytes.data() + 2);
        g_nAvail = 2; g_n64Calls = 0; g_u64 = 42;
        uint32_t uOut = 0;
        CHECK(SynReadVarint32Fast(&o, &uOut) == true);
        CHECK(uOut == 42);
        CHECK(g_n64Calls == 1);
        g_b64Ok = true;
    }

    // ---- the bound reset: end moves forward by the held-back bytes, then the smaller count
    //      decides what is held back again
    {
        std::vector<uint8_t> aBuf(64, 0);
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x10, aBuf.data() + 10);      // end
        SetI(o, 0x2c, 4);                     // back-up bytes
        SetI(o, 0x28, 6);
        SetI(o, 0x30, 2);                     // the smaller is +0x30 = 2
        SetI(o, 0x18, 20);
        g_nClampCalls = 0;
        SynResetBlockBounds(&o);
        CHECK(g_nClampCalls == 1);
        // end: 10 + 4 = 14, then back_up = 20 - 2 = 18, end = 14 - 18 = -4
        CHECK(GetP(o, 0x10) == aBuf.data() - 4);
        CHECK(GetI(o, 0x2c) == 18);
    }

    // ---- and when the smaller count is not below the total, nothing is held back
    {
        std::vector<uint8_t> aBuf(64, 0);
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x10, aBuf.data() + 10);
        SetI(o, 0x2c, 3);
        SetI(o, 0x28, 40);
        SetI(o, 0x30, 30);                    // the smaller is 30
        SetI(o, 0x18, 20);                    // 30 is not below 20
        SynResetBlockBounds(&o);
        CHECK(GetI(o, 0x2c) == 0);
        CHECK(GetP(o, 0x10) == aBuf.data() + 13);   // only the first move happened
    }

    std::printf("SYNDICATE_D76_OK: three reader helpers, %d checks\n", g_nChecks);
    return 0;
}

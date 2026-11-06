// ============================================================================
// cqbase_d75 — the walker. Every branch of the end-of-message pair is exercised, and what the
//   position does (must not move) is checked because the value read never advances it here.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "modules/syndicate/src/synpbblk.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static int g_nRefills = 0; static bool g_bRefill = false;
static int g_nReads = 0; static bool g_bRead = true; static int32_t g_nValue = 0;
static bool RefillHook(void*) { ++g_nRefills; return g_bRefill; }
static bool ReadHook(void*, int32_t* pOut) { ++g_nReads; *pOut = g_nValue; return g_bRead; }

struct Obj { uint8_t a[0x40]; };
static void SetP(Obj& o, int off, void* v) { *(void**)(o.a + off) = v; }
static void SetI(Obj& o, int off, int32_t v) { *(int32_t*)(o.a + off) = v; }
static int32_t GetI(Obj& o, int off) { return *(int32_t*)(o.a + off); }

int main() {
    g_fnBlkRefill = &RefillHook;
    g_fnBlkReadValue = &ReadHook;

    // ---- a position inside the block goes straight to the read
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 1);
        SetP(o, 0x10, o.a + 8);
        g_nRefills = 0; g_nReads = 0; g_nValue = 0x2A;
        CHECK(SynReadVarint32Walker(&o) == 0x2A);
        CHECK(g_nReads == 1);
        CHECK(g_nRefills == 0);
    }

    // ---- an empty block that refills also reads
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 8);
        SetP(o, 0x10, o.a + 8);
        g_nRefills = 0; g_nReads = 0; g_nValue = 7; g_bRefill = true;
        CHECK(SynReadVarint32Walker(&o) == 7);
        CHECK(g_nRefills == 1);
        CHECK(g_nReads == 1);
    }

    // ---- empty, no refill, less than the limit consumed: the flag is raised and zero answers
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 8);
        SetP(o, 0x10, o.a + 8);
        SetI(o, 0x18, 4); SetI(o, 0x2c, 0); SetI(o, 0x30, 9);   // 4 < 9
        SetI(o, 0x28, 12345);
        g_nRefills = 0; g_nReads = 0; g_bRefill = false;
        CHECK(SynReadVarint32Walker(&o) == 0);
        CHECK(g_nReads == 0);
        CHECK(GetI(o, 0x24) == 1);
    }

    // ---- empty, no refill, enough consumed and the pair agrees: the flag is one
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 8);
        SetP(o, 0x10, o.a + 8);
        SetI(o, 0x18, 20); SetI(o, 0x2c, 1); SetI(o, 0x30, 5);   // 19 >= 5
        SetI(o, 0x28, 5);                                        // agrees with +0x30
        g_bRefill = false; g_nReads = 0;
        CHECK(SynReadVarint32Walker(&o) == 0);
        CHECK(GetI(o, 0x24) == 1);
        CHECK(g_nReads == 0);
    }

    // ---- the same but the pair disagrees: the flag is cleared
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 8);
        SetP(o, 0x10, o.a + 8);
        SetI(o, 0x18, 20); SetI(o, 0x2c, 1); SetI(o, 0x30, 5);
        SetI(o, 0x28, 6);                                        // differs
        SetI(o, 0x24, 1);                                        // a stale flag must be cleared
        g_bRefill = false; g_nReads = 0;
        CHECK(SynReadVarint32Walker(&o) == 0);
        CHECK(GetI(o, 0x24) == 0);
        CHECK(g_nReads == 0);
    }

    // ---- the block read failing answers zero without consulting the pair
    {
        Obj o;
        std::memset(&o, 0, sizeof(o));
        SetP(o, 0x08, o.a + 1);
        SetP(o, 0x10, o.a + 8);
        SetI(o, 0x24, 0);
        g_bRead = false; g_nReads = 0;
        CHECK(SynReadVarint32Walker(&o) == 0);
        CHECK(g_nReads == 1);
        CHECK(GetI(o, 0x24) == 0);
        g_bRead = true;
    }

    std::printf("SYNDICATE_D75_OK: the block walker, %d checks\n", g_nChecks);
    return 0;
}

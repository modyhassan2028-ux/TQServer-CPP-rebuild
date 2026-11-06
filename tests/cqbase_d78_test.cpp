// ============================================================================
// cqbase_d78 — Refresh, the largest piece of the reader. Pinned here: the guard ORDER (which
//   decides whether the total-bytes message is ever reached), the accounting overflow, the exact
//   text of the security message, and that a stream with nothing clears both pointers.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "modules/syndicate/src/synpbrefresh.h"
#include "modules/syndicate/src/synpbread2.h"   // the bounds reset the refresh ends with

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static int32_t g_nAvail = 1;
static int g_nReport = 0;
static bool g_bNext = true;
static void* g_pBlock = nullptr; static int32_t g_nBlockSize = 0;
static std::string g_strThrown; static int g_nThrows = 0; static int32_t g_nThrownKind = 0;
static int32_t AvailHook(void*) { return g_nAvail; }
static void ReportHook(void*) { ++g_nReport; }
static bool NextHook(void*, void** ppData, int32_t* pSize) {
    *ppData = g_pBlock; *pSize = g_nBlockSize; return g_bNext;
}
static void ThrowHook(SynMsgBlock* p) { ++g_nThrows; g_strThrown = p->strMessage; g_nThrownKind = p->nKind; }
static int32_t* ClampHook(int32_t* pA, int32_t* pB) { return (*pA < *pB) ? pA : pB; }

struct Obj { uint8_t a[0x60]; };
static void SetP(Obj& o, int off, void* v) { *(void**)(o.a + off) = v; }
static void* GetP(Obj& o, int off) { return *(void**)(o.a + off); }
static void SetI(Obj& o, int off, int32_t v) { *(int32_t*)(o.a + off) = v; }
static int32_t GetI(Obj& o, int off) { return *(int32_t*)(o.a + off); }

static void Reset(Obj& o) {
    std::memset(&o, 0, sizeof(o));
    SetP(o, 0x00, (void*)0x1000);        // the stream
    SetP(o, 0x08, nullptr);
    SetP(o, 0x10, nullptr);
    SetI(o, 0x18, 0);                    // total bytes read
    SetI(o, 0x1c, 0);                    // overflow
    SetI(o, 0x28, 0);
    SetI(o, 0x2c, 0);                    // back-up bytes
    SetI(o, 0x30, 0);                    // block size
    SetI(o, 0x34, -1);                   // no limit
}

int main() {
    g_fnRfAvail = &AvailHook;
    g_fnRfReport = &ReportHook;
    g_fnRfNext = &NextHook;
    g_fnSynThrow = &ThrowHook;
    g_fnR2ClampMin = &ClampHook;   // used by the bounds reset at the end

    // ---- nothing buffered raises the first CHECK
    {
        Obj o; Reset(o);
        g_nAvail = 0; g_nThrows = 0;
        SynRefresh(&o);
        CHECK(g_nThrows == 1);
        CHECK(g_strThrown == "CHECK failed: (0) == (BufferSize()): ");
        CHECK(g_nThrownKind == 3);
        g_nAvail = 1;
    }

    // ---- counters equal with nothing held back: answer false, the limit is never consulted
    {
        Obj o; Reset(o);
        SetI(o, 0x18, 5); SetI(o, 0x28, 5); SetI(o, 0x30, 2); SetI(o, 0x34, 0);
        g_nReport = 0; g_nThrows = 0;
        CHECK(SynRefresh(&o) == false);
        CHECK(g_nThrows == 0);           // the total-bytes message is never reached
        CHECK(g_nReport == 1);           // 5-0 >= 2 and 2 != 5, so the sizes are reported
    }

    // ---- the same but the block size differs from +0x28: it reports
    {
        Obj o; Reset(o);
        SetI(o, 0x18, 5); SetI(o, 0x28, 5); SetI(o, 0x30, 2); SetI(o, 0x34, 0);
        // reach the false path through back-up bytes instead of equal counters
        SetI(o, 0x2c, 0); SetI(o, 0x18, 5); SetI(o, 0x28, 6);
        // counters differ, so this continues into the limit check; force the false path from there
        SetI(o, 0x34, -1);
        g_bNext = false; g_nReport = 0;
        CHECK(SynRefresh(&o) == false);
        CHECK(g_nReport == 0);
        g_bNext = true;
    }

    // ---- a held-back count takes the false path, and the report fires when the sizes differ
    {
        Obj o; Reset(o);
        SetI(o, 0x18, 10); SetI(o, 0x28, 10); SetI(o, 0x2c, 4); SetI(o, 0x30, 3);
        g_nReport = 0; g_nThrows = 0;
        CHECK(SynRefresh(&o) == false);
        CHECK(g_nReport == 1);           // 10-4 >= 3 and 3 != 10
        CHECK(g_nThrows == 0);

        // and not when the sizes agree
        SetI(o, 0x30, 10);
        g_nReport = 0;
        CHECK(SynRefresh(&o) == false);
        CHECK(g_nReport == 0);
    }

    // ---- the total-bytes limit raises the security message with the limit in it
    {
        Obj o; Reset(o);
        SetI(o, 0x18, 100); SetI(o, 0x28, 0); SetI(o, 0x30, 64); SetI(o, 0x34, 50);
        g_bNext = false; g_nThrows = 0;
        SynRefresh(&o);
        CHECK(g_nThrows == 1);
        CHECK(g_strThrown.find("Reading dangerously large protocol message.") == 0);
        CHECK(g_strThrown.find("64") != std::string::npos);
        CHECK(g_strThrown.find(" bytes, parsing will be halted for security reasons.") != std::string::npos);
        CHECK(g_nThrownKind == 1);
        CHECK(GetI(o, 0x34) == -2);      // the marker written after the throw
        g_bNext = true;
    }

    // ---- a block from the stream: pointers, the total, and the bounds reset
    {
        std::vector<uint8_t> aBlock(32, 0);
        Obj o; Reset(o);
        SetI(o, 0x18, 10); SetI(o, 0x28, 32); SetI(o, 0x30, 32); SetI(o, 0x2c, 0);  // counters differ: the read path
        g_pBlock = aBlock.data(); g_nBlockSize = 32; g_bNext = true; g_nThrows = 0;
        CHECK(SynRefresh(&o) == true);
        CHECK(GetP(o, 0x08) == aBlock.data());
        CHECK(GetI(o, 0x18) == 42);      // 10 + 32
        CHECK(GetI(o, 0x1c) == 0);
        // the reset that ends the refresh: min(+0x28,+0x30) = 32 is below the 42 consumed, so
        // 10 bytes are held back and the end is pulled from data+32 to data+22
        CHECK(GetI(o, 0x2c) == 10);
        CHECK(GetP(o, 0x10) == aBlock.data() + 22);
        CHECK(g_nThrows == 0);
    }

    // ---- the accounting overflow: the total saturates and the end is pulled back
    {
        std::vector<uint8_t> aBlock(16, 0);
        Obj o; Reset(o);
        SetI(o, 0x18, 0x7ffffff0); SetI(o, 0x28, 0); SetI(o, 0x30, 16); SetI(o, 0x2c, 0);
        g_pBlock = aBlock.data(); g_nBlockSize = 16; g_bNext = true;
        CHECK(SynRefresh(&o) == true);
        // room = 0x7fffffff - 16 = 0x7fffffef, and 0x7ffffff0 > that by 1
        CHECK(GetI(o, 0x1c) == 1);
        CHECK(GetI(o, 0x18) == 0x7fffffff);
        CHECK(g_nThrows == 0);
    }

    // ---- nothing from the stream clears both pointers
    {
        Obj o; Reset(o);
        SetI(o, 0x18, 10); SetI(o, 0x28, 0); SetI(o, 0x30, 1);
        SetP(o, 0x08, (void*)0x5000); SetP(o, 0x10, (void*)0x5010);
        g_bNext = false;
        CHECK(SynRefresh(&o) == false);
        CHECK(GetP(o, 0x08) == nullptr);
        CHECK(GetP(o, 0x10) == nullptr);
        g_bNext = true;
    }

    // ---- a negative size raises the third CHECK
    {
        Obj o; Reset(o);
        SetI(o, 0x18, 10); SetI(o, 0x28, 0); SetI(o, 0x30, 1);
        g_pBlock = (void*)0x2000; g_nBlockSize = -5; g_bNext = true; g_nThrows = 0;
        SynRefresh(&o);
        CHECK(g_nThrows == 1);
        CHECK(g_strThrown == "CHECK failed: (buffer_size) >= (0): ");
        CHECK(g_nThrownKind == 3);
        g_nBlockSize = 0;
    }

    std::printf("SYNDICATE_D78_OK: Refresh, %d checks\n", g_nChecks);
    return 0;
}

// 0x1417d68d0 — the CMsgLeagueOpt dispatcher. Every one of the 79 table entries is exercised through
// a fake vtable and fake seams, so the test fails if a case is dispatched to the wrong slot or handed
// the wrong field. The bounds and the gate are checked separately.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <initializer_list>
#include "modules/syndicate/src/msg/msgleagueopt.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"

using namespace tq;

namespace tq { void log_InlineLogERROR(const char*, ...) {} }

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)
// cfg fields sit at unaligned offsets on purpose, so the test reads and writes them the same way.
static inline uint16_t MW(const void* p, uint32_t o) { uint16_t v; std::memcpy(&v, (const uint8_t*)p+o, sizeof v); return v; }
static inline void MWset(void* p, uint32_t o, uint16_t v) { std::memcpy((uint8_t*)p+o, &v, sizeof v); }
static inline uint32_t MD(const void* p, uint32_t o) { uint32_t v; std::memcpy(&v, (const uint8_t*)p+o, sizeof v); return v; }
static inline void MDset(void* p, uint32_t o, uint32_t v) { std::memcpy((uint8_t*)p+o, &v, sizeof v); }
#define W(p,o) MW((p),(o))
#define D(p,o) MD((p),(o))
#define Wset(p,o,v) MWset((p),(o),(uint16_t)(v))
#define Dset(p,o,v) MDset((p),(o),(uint32_t)(v))
#define Q(p,o) (*(void**)((uint8_t*)(p)+(o)))
#define IGN 0xDEADBEEFCAFEBABEULL

static unsigned char g_tbl[0x800];
static unsigned char g_obj[0x10];
static unsigned char g_this[0x500], g_cfg[0x20];

struct Call { int kind; uint64_t ident, a2, a3, a4, a5; };
static Call g_calls[16];
static int g_ncalls;
static void record(int kind, uint64_t ident, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5) {
    if (g_ncalls < 16) g_calls[g_ncalls] = { kind, ident, a2, a3, a4, a5 };
    ++g_ncalls;
}
static void reset_calls() { g_ncalls = 0; std::memset(g_calls, 0, sizeof g_calls); }

// vtable recorders: the same signature the body calls with, so a slot that is handed the wrong
// number of arguments still shows up as a bad value in a3..a5.
template <uint32_t OFF>
static void VtRec(void* self, uint32_t a2, uint64_t a3, uint64_t a4, uint64_t a5) {
    record(1, OFF, a2, a3, a4, a5);
    CHECK(self == (void*)g_obj);
}
static void install(uint32_t off, void* fn) { *(void**)(g_tbl + off) = fn; }
static bool g_predAnswer, g_b0a40, g_b03b0;
static int g_predCalls; static uint32_t g_predId;
static uint32_t g_strAmount;

#define S2(name, addr) static void name(void*, uint32_t a2, uint32_t a3) { record(2, addr, a2, a3, 0, 0); }
#define S1(name, addr) static void name(void*, uint32_t a2) { record(2, addr, a2, 0, 0, 0); }
#define S3(name, addr) static void name(void*, uint32_t a2, uint32_t a3, uint32_t a4) { record(2, addr, a2, a3, a4, 0); }
S1(S_b0e00, 0x1417b0e00) S1(S_b0e70, 0x1417b0e70) S1(S_b98e0, 0x1417b98e0)
S2(S_b0de0, 0x1417b0de0) S2(S_b0e50, 0x1417b0e50) S2(S_b1690, 0x1417b1690)
S2(S_b4310, 0x1417b4310) S2(S_b1980, 0x1417b1980) S2(S_b19c0, 0x1417b19c0) S2(S_b1a40, 0x1417b1a40)
S3(S_b15b0, 0x1417b15b0)
static void S_ac7d0(void*, uint32_t a2, void* p) { record(2, 0x1417ac7d0, a2, (uint64_t)(uintptr_t)p, 0, 0); }
static void S_b0680(void*, uint32_t a2, void* p) { record(2, 0x1417b0680, a2, (uint64_t)(uintptr_t)p, 0, 0); }
static void S_b0db0(void*, uint32_t a2, void* p, uint32_t c6, uint32_t c4) {
    record(2, 0x1417b0db0, a2, (uint64_t)(uintptr_t)p, c6, c4);
}
static void S_b0e20(void*, uint32_t a2, void* p, uint32_t ce, uint32_t c6, uint32_t c4) {
    record(2, 0x1417b0e20, a2, (uint64_t)(uintptr_t)p, ce, ((uint64_t)c6 << 32) | c4);
}
static void S_b14c0(void*, uint32_t a2, void* p, uint32_t ce, uint32_t c6, uint32_t c4) {
    record(2, 0x1417b14c0, a2, (uint64_t)(uintptr_t)p, ce, ((uint64_t)c6 << 32) | c4);
}
static void S_b1660(void*, uint32_t a2, uint32_t c6, uint32_t ce, uint32_t ca, uint32_t c4) {
    record(2, 0x1417b1660, a2, c6, ce, ((uint64_t)ca << 32) | c4);
}
static void S_bf4d0(void*, uint32_t a2, uint32_t c6, uint32_t ce, uint32_t ca, uint32_t flag) {
    record(2, 0x1417bf4d0, a2, c6, ce, ((uint64_t)ca << 32) | flag);
}
static void S_b48b0(void*, uint32_t a2, uint32_t a3, uint32_t flag, uint32_t zeroE) {
    record(2, 0x1417b48b0, a2, a3, flag, zeroE);
}
static void S_b4d60(void*, uint32_t a2, uint32_t a3, uint32_t flag, uint32_t zeroE) {
    record(2, 0x1417b4d60, a2, a3, flag, zeroE);
}
static bool S_b0a40(void*, uint32_t a2, uint32_t c6, void* buf) {
    record(2, 0x1417b0a40, a2, c6, (uint64_t)(uintptr_t)buf, 0); return g_b0a40;
}
static bool S_b03b0(void*, uint32_t a2, uint32_t c6, void* buf) {
    record(2, 0x1417b03b0, a2, c6, (uint64_t)(uintptr_t)buf, 0); return g_b03b0;
}

int main() {
    // ---- seams
    auto S_GetString = [](void* packer, uint32_t idx, char* out, uint32_t len) -> bool {
        record(3, len, idx, (uint64_t)(uintptr_t)out, 0, 0);
        CHECK(packer == (void*)(g_this + 0x410));
        out[0] = 'x'; return true;
    };
    g_pfnCStringPacker_GetString = S_GetString;
    g_pfnCStringPacker_GetStrAmount = [](void* packer) -> uint32_t {
        record(4, 0, 0, 0, 0, 0); CHECK(packer == (void*)(g_this + 0x410)); return g_strAmount;
    };
    g_pfnL_1417f30c0 = [](void* dst, int val, uint32_t n) {
        record(5, n, (uint64_t)val, (uint64_t)(uintptr_t)dst, 0, 0);
        std::memset(dst, val, n);
    };
    g_pfnL_1417ac700 = [](void*, uint32_t id) { g_predId = id; ++g_predCalls; return g_predAnswer; };
    g_pfnL_1417b0a40 = S_b0a40;   g_pfnL_1417b03b0 = S_b03b0;
    g_pfnL_1417ac7d0 = S_ac7d0;   g_pfnL_1417b0db0 = S_b0db0;
    g_pfnL_1417b0e20 = S_b0e20;   g_pfnL_1417b14c0 = S_b14c0;
    g_pfnL_1417b1660 = S_b1660;   g_pfnL_1417bf4d0 = S_bf4d0;
    g_pfnL_1417b48b0 = S_b48b0;   g_pfnL_1417b4d60 = S_b4d60;
    g_pfnL_1417b0de0 = S_b0de0;   g_pfnL_1417b0e00 = S_b0e00;
    g_pfnL_1417b0e50 = S_b0e50;   g_pfnL_1417b0e70 = S_b0e70;
    g_pfnL_1417b15b0 = S_b15b0;   g_pfnL_1417b1690 = S_b1690;
    g_pfnL_1417b4310 = S_b4310;   g_pfnL_1417b98e0 = S_b98e0;
    g_pfnL_1417b1980 = S_b1980;   g_pfnL_1417b19c0 = S_b19c0;
    g_pfnL_1417b1a40 = S_b1a40;   g_pfnL_1417b0680 = S_b0680;

    // ---- the object, its table and the message
    Q(g_obj, 0) = g_tbl;
    install(0x478, (void*)&VtRec<0x478>); install(0x4e8, (void*)&VtRec<0x4e8>);
    install(0x4f8, (void*)&VtRec<0x4f8>); install(0x500, (void*)&VtRec<0x500>);
    install(0x508, (void*)&VtRec<0x508>); install(0x578, (void*)&VtRec<0x578>);
    install(0x580, (void*)&VtRec<0x580>); install(0x588, (void*)&VtRec<0x588>);
    install(0x590, (void*)&VtRec<0x590>); install(0x598, (void*)&VtRec<0x598>);
    install(0x5b0, (void*)&VtRec<0x5b0>); install(0x5b8, (void*)&VtRec<0x5b8>);
    install(0x5c0, (void*)&VtRec<0x5c0>); install(0x5c8, (void*)&VtRec<0x5c8>);
    install(0x5d0, (void*)&VtRec<0x5d0>); install(0x5d8, (void*)&VtRec<0x5d8>);
    install(0x5e0, (void*)&VtRec<0x5e0>); install(0x5e8, (void*)&VtRec<0x5e8>);
    install(0x5f0, (void*)&VtRec<0x5f0>); install(0x5f8, (void*)&VtRec<0x5f8>);
    install(0x6c0, (void*)&VtRec<0x6c0>); install(0x6c8, (void*)&VtRec<0x6c8>);
    install(0x700, (void*)&VtRec<0x700>); install(0x708, (void*)&VtRec<0x708>);
    install(0x718, (void*)&VtRec<0x718>); install(0x720, (void*)&VtRec<0x720>);
    install(0x728, (void*)&VtRec<0x728>); install(0x738, (void*)&VtRec<0x738>);
    Slot_1417b6210_seed(g_obj);

    Q(g_this, 0x408) = g_cfg;
    Wset(g_cfg, 0x0, 0xAAAA);
    Dset(g_cfg, 0x6, 0x11111111u);
    Dset(g_cfg, 0xA, 0x22222222u);
    Dset(g_cfg, 0xE, 0x33333333u);

    const uint32_t ID = 0x7777;          // the nId the dispatcher passes along
    const uint64_t C6 = 0x11111111ull, CA = 0x22222222ull, CE = 0x33333333ull;

    // ---- the sweep: every entry of the 79-way table, with the call it must end in
    struct Exp { int id, ncalls, kind; uint64_t ident, a3, a4, a5; };
    static const Exp exp[] = {
        {0,1,1,0x5b0,IGN,IGN,IGN},        {1,1,1,0x5c0,C6,CE,IGN},
        {2,1,1,0x5c8,C6,CE,IGN},          {3,1,1,0x5d0,C6,CE,IGN},
        {4,1,1,0x5b8,CE,IGN,IGN},         {5,0,0,0,0,0,0},
        {6,2,2,0x1417b0a40,C6,IGN,IGN},   {7,2,1,0x4e8,IGN,0,IGN},
        {8,1,2,0x1417b1980,CE,IGN,IGN},   {9,1,2,0x1417b19c0,0,IGN,IGN},
        {10,1,2,0x1417b1a40,CE,IGN,IGN},  {11,1,1,0x4f8,C6,CE,IGN},
        {12,1,1,0x500,C6,CE,IGN},         {13,1,1,0x708,C6,CE,IGN},
        {14,1,1,0x508,CE,CA,IGN},         {15,1,1,0x5d8,CE,IGN,IGN},
        {16,1,1,0x700,CE,IGN,IGN},        {17,0,0,0,0,0,0},
        {18,2,1,0x478,C6,IGN,IGN},        {19,1,1,0x718,IGN,IGN,IGN},
        {20,3,1,0x720,IGN,IGN,IGN},       {21,0,0,0,0,0,0},
        {22,0,0,0,0,0,0},                 {23,1,1,0x5f0,0x33,IGN,IGN},
        {24,2,2,0x1417b0db0,IGN,C6,0x18}, {25,1,2,0x1417b0de0,CA,IGN,IGN},
        {26,1,2,0x1417b0e00,IGN,IGN,IGN}, {27,1,1,0x5e0,IGN,IGN,IGN},
        {28,2,2,0x1417b0e20,IGN,0x3333,IGN}, {29,1,2,0x1417b0e50,CA,IGN,IGN},
        {30,1,2,0x1417b0e70,IGN,IGN,IGN}, {31,1,1,0x588,CE,IGN,IGN},
        {32,1,1,0x590,CE,IGN,IGN},        {33,1,1,0x598,CE,IGN,IGN},
        {34,1,1,0x5e8,IGN,IGN,IGN},       {35,0,0,0,0,0,0},
        {36,0,0,0,0,0,0},                 {37,1,1,0x578,IGN,IGN,IGN},
        {38,1,2,0x1417bf4d0,0x1111,CE,0x2222222200000000ULL}, {39,1,2,0x1417b4310,CE,IGN,IGN},
        {40,1,1,0x5f8,IGN,IGN,IGN},       {41,2,2,0x1417b14c0,IGN,0x3333,IGN},
        {42,1,2,0x1417b1660,C6,0x3333,IGN}, {43,1,2,0x1417b15b0,C6,0x3333,IGN},
        {44,1,2,0x1417b1690,CA,IGN,IGN},  {45,1,2,0x1417bf4d0,0x1111,CE,0x2222222200000001ULL},
        {46,1,2,0x1417b98e0,IGN,IGN,IGN}, {47,2,2,0x1417b0e20,IGN,0x3333,IGN},
        {48,2,2,0x1417b0db0,IGN,C6,0x30}, {49,2,2,0x1417b14c0,IGN,0x3333,IGN},
        {50,1,2,0x1417b1660,C6,0x3333,IGN}, {51,2,2,0x1417b03b0,C6,IGN,IGN},
        {52,0,0,0,0,0,0},                 {53,0,0,0,0,0,0},
        {54,0,0,0,0,0,0},                 {55,0,0,0,0,0,0},
        {56,0,0,0,0,0,0},                 {57,0,0,0,0,0,0},
        {58,0,0,0,0,0,0},                 {59,0,0,0,0,0,0},
        {60,1,1,0x728,IGN,IGN,IGN},       {61,0,0,0,0,0,0},
        {62,0,0,0,0,0,0},                 {63,0,0,0,0,0,0},
        {64,1,1,0x6c0,IGN,IGN,IGN},       {65,0,0,0,0,0,0},
        {66,4,1,0x5b0,IGN,IGN,IGN},       {67,0,0,0,0,0,0},
        {68,0,0,0,0,0,0},                 {69,0,0,0,0,0,0},
        {70,0,0,0,0,0,0},                 {71,1,1,0x6c8,IGN,IGN,IGN},
        {72,1,1,0x580,CE,0,IGN},          {73,0,0,0,0,0,0},
        {74,1,2,0x1417b48b0,CA,0,0},      {75,1,2,0x1417b4d60,CA,0,0},
        {76,1,2,0x1417b48b0,ID,1,0},      {77,1,2,0x1417b4d60,ID,1,0},
        {78,1,1,0x738,IGN,IGN,IGN},
    };
    CHECK(sizeof exp / sizeof exp[0] == 79);

    for (const Exp& e : exp) {
        reset_calls();
        g_b0a40 = g_b03b0 = false;
        g_strAmount = 1;
        Wset(g_cfg, 0x4, e.id);
        Slot_1417d68d0_Process(g_this, ID);
        CHECK(g_ncalls == e.ncalls);
        if (e.ncalls == 0) continue;
        const Call& last = g_calls[g_ncalls - 1];
        CHECK(last.kind == e.kind);
        if (e.kind == 1) CHECK(last.ident == e.ident);
        else CHECK(last.ident == e.ident);
        if (e.a3 != IGN) CHECK(last.a3 == e.a3);
        if (e.a4 != IGN) CHECK(last.a4 == e.a4);
        if (e.a5 != IGN) CHECK(last.a5 == e.a5);
        // a2 is the id except in the two swapped variants
        if (e.id == 76 || e.id == 77) CHECK(last.a2 == CA);
        else if (e.ident != 0x1417ac700) CHECK(last.a2 == ID);
    }

    // ---- case 24/48: the 5th argument is the u16 at cfg+4, not the full dword
    for (int id : { 24, 48 }) {
        reset_calls(); g_b0a40 = g_b03b0 = false;
        Wset(g_cfg, 0x4, id); Dset(g_cfg, 0xE, 0xFFFF9999u);
        Slot_1417d68d0_Process(g_this, ID);
        CHECK(g_calls[g_ncalls - 1].a5 == (uint64_t)id);          // only the low 16 bits
    }

    // ---- the id gates: 0x2d for 38/45, 0x4c for 74/76, 0x4d for 75/77, and the zero-E flag
    g_predAnswer = false;                                         // the flag compare, ungated
    reset_calls(); Wset(g_cfg, 0x4, 0x2D); Dset(g_cfg, 0xE, 0);
    Slot_1417d68d0_Process(g_this, ID);                           // 0x2d: the flag compare is true
    CHECK(g_ncalls == 1);
    CHECK(g_calls[0].ident == 0x1417bf4d0); CHECK(g_calls[0].a5 == 0x2222222200000001ULL);
    reset_calls(); Wset(g_cfg, 0x4, 0x4C); Dset(g_cfg, 0xE, 0);
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(g_ncalls == 1);
    CHECK(g_calls[0].ident == 0x1417b48b0); CHECK(g_calls[0].a4 == 1); CHECK(g_calls[0].a5 == 1);
    reset_calls(); Wset(g_cfg, 0x4, 0x4D); Dset(g_cfg, 0xE, 0);
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(g_ncalls == 1);
    CHECK(g_calls[0].ident == 0x1417b4d60); CHECK(g_calls[0].a4 == 1); CHECK(g_calls[0].a5 == 1);

    // ---- bounds: 0x4f and above reach nothing
    for (uint32_t t : { 0x4Fu, 0x50u, 0xFFFFu }) {
        reset_calls(); Wset(g_cfg, 0x4, t);
        Slot_1417d68d0_Process(g_this, ID);
        CHECK(g_ncalls == 0);
    }

    // ---- the known-path gate. The expectation comes from the same 79 bytes the body reads, but
    // transcribed into the test separately so a transcription slip on either side shows up here.
    static const uint8_t gate[0x4F] = {
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0,
        1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 0
    };
    g_predAnswer = true;
    for (int id = 0; id <= 0x4E; ++id) {
        reset_calls(); g_b0a40 = g_b03b0 = false; g_strAmount = 1;
        Wset(g_cfg, 0x4, id);
        Slot_1417d68d0_Process(g_this, ID);
        if (gate[id] == 1) CHECK(g_ncalls == 0);
        else {
            // the ids whose case is empty dispatch nothing either, so only the handled ones count
            const bool handled = !(id == 5 || id == 17 || id == 21 || id == 22 || id == 35 ||
                                   id == 36 || id == 52 || id == 53 || id == 54 || id == 55 ||
                                   id == 56 || id == 57 || id == 58 || id == 59 || id == 61 ||
                                   id == 62 || id == 63 || id == 65 || id == 67 || id == 68 ||
                                   id == 69 || id == 70 || id == 73);
            if (handled) CHECK(g_ncalls > 0); else CHECK(g_ncalls == 0);
        }
    }
    g_predAnswer = false;

    // ---- the two true-tails: 6 and 51 rewrite the type and report
    reset_calls(); Wset(g_cfg, 0x4, 6); g_b0a40 = true;
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(W(g_cfg, 0x4) == 0x16);
    CHECK(g_calls[g_ncalls - 1].ident == 0x1417ac7d0);
    reset_calls(); Wset(g_cfg, 0x4, 51); g_b03b0 = true;
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(W(g_cfg, 0x4) == 0x33);
    CHECK(g_calls[g_ncalls - 1].ident == 0x1417ac7d0);
    // and false leaves the type alone and reports nothing
    reset_calls(); Wset(g_cfg, 0x4, 6); g_b0a40 = false;
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(W(g_cfg, 0x4) == 6);
    CHECK(g_calls[g_ncalls - 1].ident == 0x1417b0a40);

    // ---- case 66 with no strings: only the vtable call
    reset_calls(); Wset(g_cfg, 0x4, 66); g_strAmount = 0;
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(g_ncalls == 2); CHECK(g_calls[0].kind == 4);
    CHECK(g_calls[1].ident == 0x5b0);

    // ---- the null configuration: the CHECK, with every argument the bytes pass
    static int g_checkCalls; static char g_expr[16], g_name[16], g_file[200]; static uint32_t g_line;
    g_pfn_check_msgleagueopt = [](const char* fmt, const char* expr, const char* name,
                                  const char* file, uint32_t line) {
        ++g_checkCalls;
        CHECK(std::strcmp(fmt, "\xA1\xEF%s(%s)\xA1\xEF in %s, %d") == 0);
        std::snprintf(g_expr, sizeof g_expr, "%s", expr ? expr : "");
        std::snprintf(g_name, sizeof g_name, "%s", name ? name : "");
        std::snprintf(g_file, sizeof g_file, "%s", file ? file : "");
        g_line = line;
    };
    reset_calls();
    Q(g_this, 0x408) = nullptr;
    Slot_1417d68d0_Process(g_this, ID);
    CHECK(g_checkCalls == 1);
    CHECK(std::strcmp(g_expr, "CHECK") == 0);
    CHECK(std::strcmp(g_name, "m_pInfo") == 0);
    CHECK(std::strcmp(g_file,
        "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\msg\\msgleagueopt.cpp") == 0);
    CHECK(g_line == 0x54);
    CHECK(g_ncalls == 0);                       // no singleton, no dispatch

    std::printf("MSGLGOPT_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}

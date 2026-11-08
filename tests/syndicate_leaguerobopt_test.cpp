// 0x1417d8920 — the CMsgLeagueRobOpt dispatcher: the early return on id 0, the two-mode known-path
// gate, the unconditional bound, the ten-slot clamping, and the divide-by-1000 pair.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <initializer_list>
#include "modules/syndicate/src/msg/msgleaguerobopt.h"
#include "modules/syndicate/src/msg/msgleagueopt.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"

using namespace tq;
namespace tq { void log_InlineLogERROR(const char*, ...) {} }

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)
static inline uint32_t RD(const void* p, uint32_t o) { uint32_t v; std::memcpy(&v, (const uint8_t*)p+o, 4); return v; }
static inline void WR(void* p, uint32_t o, uint32_t v) { std::memcpy((uint8_t*)p+o, &v, 4); }
static inline void WQ(void* p, uint32_t o, void* v) { std::memcpy((uint8_t*)p+o, &v, 8); }

static unsigned char g_tbl[0x800], g_obj[0x10], g_this[0x480];
static unsigned char g_elem[8][0x60];
static void* g_list[40];

static int g_calls, g_slot; static uint32_t g_a2, g_a3, g_b, g_e; static void* g_arr; static uint32_t g_arrcopy[10];

static void rec(int slot, void* self, uint32_t a2, uint32_t a3, void* arr, uint32_t b, uint32_t e) {
    ++g_calls; g_slot = slot; g_a2 = a2; g_a3 = a3; g_arr = arr; g_b = b; g_e = e;
    if (arr) std::memcpy(g_arrcopy, arr, sizeof g_arrcopy);
    CHECK(self == (void*)g_obj);
    if (g_calls > 4) CHECK(false);
}
static void V680(void* s, uint32_t a2, uint32_t a3, void* arr, uint32_t b, uint32_t e) { rec(0x680, s,a2,a3,arr,b,e); }
static void V6E0(void* s, uint32_t a2, uint32_t a3, void* arr, uint32_t b, uint32_t e) { rec(0x6e0, s,a2,a3,arr,b,e); }
static void V730(void* s, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5) { rec(0x730, s,a2,a3,nullptr,a4,a5); }

static bool g_pred; static int g_predCalls;
static void reset() {
    g_calls = 0; g_slot = 0; g_a2 = g_a3 = g_b = g_e = 0; g_arr = nullptr;
    std::memset(g_arrcopy, 0, sizeof g_arrcopy);
    g_predCalls = 0;
}
static void setMode(uint32_t m) { WR(g_this, 0x440, m); }

int main() {
    std::memset(g_tbl, 0, sizeof g_tbl);
    *(void**)(g_tbl + 0x680) = (void*)&V680;
    *(void**)(g_tbl + 0x6e0) = (void*)&V6E0;
    *(void**)(g_tbl + 0x730) = (void*)&V730;
    WQ(g_obj, 0, g_tbl);
    Slot_1417b6210_seed(g_obj);
    g_pfnL_1417ac700 = [](void*, uint32_t) { ++g_predCalls; return g_pred; };
    WQ(g_this, 0x448, g_list);
    for (int i = 0; i < 8; ++i) { g_list[i] = g_elem[i]; WR(g_elem[i], 0x48, 0x1000u + (uint32_t)i); }
    // the list must be long enough for the fifteen-element clamp case; the elements repeat
    for (int i = 8; i < 40; ++i) g_list[i] = g_elem[i % 8];

    // ---- id 0 returns before anything else happens (no singleton, no predicate)
    reset(); g_pred = false; setMode(0);
    Slot_1417d8920_Process(g_this, 0);
    CHECK(g_calls == 0); CHECK(g_predCalls == 0);

    // ---- the known path: 0,1,4,7 and above return; 2,3,5,6 dispatch
    g_pred = true;
    for (uint32_t m : { 0u, 1u, 4u, 7u, 8u, 0xFFFFFFFFu }) {
        reset(); setMode(m); WR(g_this, 0x450, 3);
        Slot_1417d8920_Process(g_this, 0x10);
        CHECK(g_predCalls == 1);
        CHECK(g_calls == 0);
    }
    for (uint32_t m : { 2u, 3u, 5u, 6u }) {
        reset(); setMode(m); WR(g_this, 0x450, 3);
        Slot_1417d8920_Process(g_this, 0x10);
        CHECK(g_calls == 1);
        CHECK(g_a2 == 0x10);
        if (m != 2 && m != 3) CHECK(g_a3 == 3);      // 2/3 carry the switch value, not the count
    }

    // ---- the unknown path skips the gate: every mode 0..6 dispatches, 4 does nothing, 7 returns
    g_pred = false;
    for (uint32_t m = 0; m <= 6; ++m) {
        reset(); setMode(m); WR(g_this, 0x450, 2); WR(g_this, 0x444, 4321);
        Slot_1417d8920_Process(g_this, 0x20);
        CHECK(g_predCalls == 1);
        CHECK(g_calls == (m == 4 ? 0 : 1));
        if (g_calls && m != 2 && m != 3) CHECK(g_a2 == 0x20 && g_a3 == 2);
    }
    reset(); setMode(7); Slot_1417d8920_Process(g_this, 0x20); CHECK(g_calls == 0);
    reset(); setMode(0xFFFF); Slot_1417d8920_Process(g_this, 0x20); CHECK(g_calls == 0);

    // ---- case 0: the list is copied from each element's +0x48, and the callee gets slot 0x680 with
    //      a zero flag and a zero extra word
    reset(); setMode(0); WR(g_this, 0x450, 5);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_calls == 1); CHECK(g_slot == 0x680);
    CHECK(g_a2 == 0x77 && g_a3 == 5 && g_b == 0 && g_e == 0);
    for (int i = 0; i < 5; ++i) CHECK(g_arrcopy[i] == 0x1000u + (uint32_t)i);
    for (int i = 5; i < 10; ++i) CHECK(g_arrcopy[i] == 0);

    // ---- case 1: same slot, but the flag is 1 and the extra word is this+0x444
    reset(); setMode(1); WR(g_this, 0x450, 2); WR(g_this, 0x444, 0xCAFEF00Du);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_slot == 0x680 && g_b == 1 && g_e == 0xCAFEF00Du);

    // ---- case 5 / 6 share slot 0x6e0 and differ only in those two words
    reset(); setMode(5); WR(g_this, 0x450, 3); WR(g_this, 0x444, 0x1234);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_slot == 0x6e0 && g_b == 0 && g_e == 0);
    CHECK(g_a3 == 3 && g_arrcopy[2] == 0x1002u);
    reset(); setMode(6); WR(g_this, 0x450, 3); WR(g_this, 0x444, 0xABCD);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_slot == 0x6e0 && g_b == 1 && g_e == 0xABCDu);

    // ---- the clamp: fifteen elements fill ten slots but the callee still sees fifteen
    reset(); setMode(0); WR(g_this, 0x450, 15);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_a3 == 15);
    // ten slots, taken from the first ten list entries (the fake list repeats every eight)
    for (int i = 0; i < 10; ++i) CHECK(g_arrcopy[i] == 0x1000u + (uint32_t)(i % 8));
    // and eleven is enough to stop at ten
    reset(); setMode(0); WR(g_this, 0x450, 11);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_a3 == 11);
    for (int i = 0; i < 10; ++i) CHECK(g_arrcopy[i] == 0x1000u + (uint32_t)(i % 8));
    // the eleventh element exists but the tenth slot is the last one the loop will ever write
    CHECK(g_arrcopy[9] == 0x1001u);

    // ---- a negative count: no loop, and the negative value is passed through unchanged
    reset(); setMode(0); WR(g_this, 0x450, 0xFFFFFFFEu);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_a3 == 0xFFFFFFFEu);
    for (int i = 0; i < 10; ++i) CHECK(g_arrcopy[i] == 0);
    // zero count likewise
    reset(); setMode(0); WR(g_this, 0x450, 0);
    Slot_1417d8920_Process(g_this, 0x77);
    CHECK(g_a3 == 0 && g_calls == 1);

    // ---- cases 2 and 3: the divide by 1000, with the switch value riding in r8
    for (uint32_t m : { 2u, 3u }) {
        for (uint32_t v : { 0u, 999u, 1000u, 4321u, 123456789u, 0xFFFFFFFFu }) {
            reset(); setMode(m); WR(g_this, 0x444, v);
            Slot_1417d8920_Process(g_this, 0x99);
            CHECK(g_calls == 1); CHECK(g_slot == 0x730);
            CHECK(g_a2 == 0x99);          // nId
            CHECK(g_a3 == m);             // r8 = the untouched switch value
            CHECK(g_b == v % 1000u);      // r9 = remainder
            CHECK(g_e == v / 1000u);      // [0x20] = quotient
        }
    }

    std::printf("LEAGUEROB_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}

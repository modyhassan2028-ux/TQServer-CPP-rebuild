// 0x1417ac700 / 0x1417ac710 / 0x1417ac720 / 0x1417ac730 / 0x1417ac5e0. The first three are pure
// thunks, so what is worth proving is that they hop through this+0x8 to the sub-object's table at the
// right slot and pass the id along; the fourth inverts; the fifth only calls for non-null fields.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/slotforwarders.h"

using namespace tq;
namespace tq { void log_InlineLogERROR(const char*, ...) {} }

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char g_holder[0x80], g_sub[0x40], g_tbl[0x400];
static int g_slotHit; static uint32_t g_seenId; static void* g_seenSelf;
static uint64_t g_answer;

static uintptr_t Common(void* self, uint32_t id, int which) {
    g_slotHit = which; g_seenSelf = self; g_seenId = id; return (uintptr_t)g_answer;
}
static uintptr_t S278(void* s, uint32_t i) { return Common(s, i, 0x278); }
static uintptr_t S2D8(void* s, uint32_t i) { return Common(s, i, 0x2d8); }
static uintptr_t S2C8(void* s, uint32_t i) { return Common(s, i, 0x2c8); }
static uint32_t S1F8(void* s, uint32_t i) { Common(s, i, 0x1f8); return (uint32_t)g_answer; }

static void* g_seen[3]; static int g_nSeen;
static void A(void* p) { g_seen[g_nSeen++] = p; }

int main() {
    std::memset(g_tbl, 0, sizeof g_tbl);
    *(void**)(g_tbl + 0x278) = (void*)&S278;
    *(void**)(g_tbl + 0x2D8) = (void*)&S2D8;
    *(void**)(g_tbl + 0x2C8) = (void*)&S2C8;
    *(void**)(g_tbl + 0x1F8) = (void*)&S1F8;
    *(void**)g_sub = g_tbl;
    *(void**)(g_holder + 0x8) = g_sub;          // the thunks hop through this+0x8

    // ---- the three thunks reach their own slot, on the sub-object, with the id intact
    for (int k = 0; k < 3; ++k) {
        g_slotHit = 0; g_seenId = 0; g_seenSelf = nullptr; g_answer = 0x1234;
        uintptr_t r = 0;
        if (k == 0) r = Slot_1417ac700_Forward(g_holder, 0x77);
        if (k == 1) r = Slot_1417ac710_Forward(g_holder, 0x77);
        if (k == 2) r = Slot_1417ac720_Forward(g_holder, 0x77);
        const int want = (k == 0) ? 0x278 : (k == 1) ? 0x2D8 : 0x2C8;
        CHECK(g_slotHit == want);
        CHECK(g_seenSelf == (void*)g_sub);      // the sub-object, not the holder
        CHECK(g_seenId == 0x77);
        CHECK(r == 0x1234);                     // the answer passes straight back out
    }

    // ---- a zero answer stays zero, so the dispatchers' `!= 0` reading is sound
    g_answer = 0;
    CHECK(Slot_1417ac700_Forward(g_holder, 1) == 0);
    g_answer = 0xFFFFFFFFFFFFFFFFULL;
    CHECK(Slot_1417ac700_Forward(g_holder, 1) != 0);

    // ---- 0x1417ac730 inverts: non-zero becomes false, zero becomes true
    g_slotHit = 0; g_answer = 5;
    CHECK(Slot_1417ac730_IsZero(g_holder, 9) == false);
    CHECK(g_slotHit == 0x1F8); CHECK(g_seenId == 9);
    g_answer = 0;
    CHECK(Slot_1417ac730_IsZero(g_holder, 9) == true);
    // and it really is the low 32 bits that decide, because the original tests eax
    g_answer = 0x100000000ULL;
    CHECK(Slot_1417ac730_IsZero(g_holder, 9) == true);

    // ---- 0x1417ac5e0: three optional calls in field order
    g_pfnL_1417a7d70 = &A; g_pfnL_1417d4a10 = &A; g_pfnL_14176aa20 = &A;
    std::memset(g_holder, 0, sizeof g_holder);
    *(void**)(g_holder + 0x20) = (void*)0x2000;
    *(void**)(g_holder + 0x48) = (void*)0x4800;
    *(void**)(g_holder + 0x50) = (void*)0x5000;
    g_nSeen = 0;
    Slot_1417ac5e0_ReleaseRefs(g_holder);
    CHECK(g_nSeen == 3);
    CHECK(g_seen[0] == (void*)0x2000 && g_seen[1] == (void*)0x4800 && g_seen[2] == (void*)0x5000);
    // each field is independent: nulls are skipped and the others still run
    *(void**)(g_holder + 0x20) = nullptr;
    *(void**)(g_holder + 0x50) = nullptr;
    g_nSeen = 0;
    Slot_1417ac5e0_ReleaseRefs(g_holder);
    CHECK(g_nSeen == 1); CHECK(g_seen[0] == (void*)0x4800);
    *(void**)(g_holder + 0x48) = nullptr;
    g_nSeen = 0;
    Slot_1417ac5e0_ReleaseRefs(g_holder);
    CHECK(g_nSeen == 0);

    std::printf("SLOTFWD_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}

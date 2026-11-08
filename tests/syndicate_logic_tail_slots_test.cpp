// Batteries for the twelve CSyndicateLogic slots in CsyndicateLogicTailSlots.h.
// Each expectation is read off the body: which member offset is loaded, which callee is
// jumped to, whether `this` survives the tail jump, and what the comparison answers for
// the boundary and negative arguments.
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"
#include <cstdio>
#include <cstring>

using namespace tq;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static uint64_t g_a, g_b, g_c, g_d;
static int g_calls;
static uint64_t g_ret;

static uint64_t hook(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    ++g_calls;
    g_a = a; g_b = b; g_c = c; g_d = d;
    return g_ret;
}

static void reset_hooks(uint64_t ret) {
    g_calls = 0;
    g_a = g_b = g_c = g_d = 0;
    g_ret = ret;
    g_pfnLogic_1417cadb0 = hook;
    g_pfnLogic_1417caa00 = hook;
    g_pfnLogic_1417cad90 = hook;
    g_pfnLogic_1417cb000 = hook;
    g_pfnLogic_1417873a0 = hook;
    g_pfnLogic_1417a8a50 = hook;
    g_pfnLogic_1417a8940 = hook;
    g_pfnLogic_14177f980 = hook;
}

int main() {
    unsigned char object[0x40];
    std::memset(object, 0, sizeof(object));
    void* self = object;

    // --- the four forwarders: member at +0x10 reaches the callee, the other registers ride along
    {
        uint64_t member = 0x1122334455667788ULL;
        *(uint64_t*)(object + 0x10) = member;
        struct F { uint64_t (*fn)(void*, uint64_t, uint64_t, uint64_t); const char* which; };
        F fns[4] = {
            {Slot_1417abe60, "0x1417cadb0"},
            {Slot_1417ac010, "0x1417caa00"},
            {Slot_1417ab1d0, "0x1417cad90"},
            {Slot_1417ab1c0, "0x1417cb000"},
        };
        for (int i = 0; i < 4; ++i) {
            reset_hooks(0xAABBCCDDEEFF0011ULL);
            uint64_t r = fns[i].fn(self, 0x21, 0x32, 0x43);
            CHECK(r == 0xAABBCCDDEEFF0011ULL);      // the callee's answer is the slot's answer
            CHECK(g_calls == 1);
            CHECK(g_a == member);                   // rcx = *(this+0x10)
            CHECK(g_b == 0x21 && g_c == 0x32 && g_d == 0x43);   // tail jump keeps the registers
        }
        // a null member is still forwarded: the body loads and jumps unconditionally
        *(uint64_t*)(object + 0x10) = 0;
        reset_hooks(7);
        CHECK(Slot_1417abe60(self, 1, 2, 3) == 7);
        CHECK(g_calls == 1 && g_a == 0);
    }

    // --- the argument forwarder drops `this`
    {
        reset_hooks(0x55);
        CHECK(Slot_1417aeba0((void*)0xDEAD, 0x1FFFFFFFFULL, 8, 9) == 0x55);
        CHECK(g_calls == 1);
        CHECK(g_a == 0xFFFFFFFFULL);   // mov ecx,edx zero-extends the low 32 bits
        CHECK(g_b == 0x1FFFFFFFFULL);  // rdx itself is untouched
        CHECK(g_c == 8 && g_d == 9);
    }

    // --- the two constants
    {
        reset_hooks(0);
        CHECK(Slot_1417aaf90(self) == 15);
        CHECK(Slot_1417aafa0(self) == 15);
        CHECK(g_calls == 0);           // both are `mov eax,0xf / ret`, they call nothing
    }

    // --- the two comparisons, signed on the 32-bit argument
    {
        CHECK(Slot_1417abc50(self, 0x3dd) == 0);
        CHECK(Slot_1417abc50(self, 0x3de) == 1);      // >= 990
        CHECK(Slot_1417abc50(self, 0x3df) == 1);
        CHECK(Slot_1417abc50(self, 0) == 0);
        CHECK(Slot_1417abc50(self, -1) == 0);         // signed: -1 is below the bound
        CHECK(Slot_1417abc50(self, 0x7FFFFFFF) == 1);

        CHECK(Slot_1417abc60(self, 0x379) == 1);
        CHECK(Slot_1417abc60(self, 0x37a) == 1);      // <= 890
        CHECK(Slot_1417abc60(self, 0x37b) == 0);
        CHECK(Slot_1417abc60(self, -1) == 1);         // signed: -1 is below the bound
        CHECK(Slot_1417abc60(self, 0) == 1);
        CHECK(Slot_1417abc60(self, -0x80000000LL) == 1);
        CHECK(g_calls == 0);
    }

    // --- the three guarded forwarders: null member answers 0 without calling anything
    {
        struct F { int (*fn)(void*, uint64_t, uint64_t, uint64_t); size_t off; uint64_t ret; };
        F fns[3] = {
            {Slot_1417af2f0, 0x20, 1},
            {Slot_1417af310, 0x20, 0x1234},
            {Slot_1417afac0, 0x28, 0x99},
        };
        for (int i = 0; i < 3; ++i) {
            std::memset(object, 0, sizeof(object));
            reset_hooks(fns[i].ret);
            CHECK(fns[i].fn(self, 4, 5, 6) == 0);      // member is null
            CHECK(g_calls == 0);

            *(uint64_t*)(object + fns[i].off) = 0xCAFE;
            reset_hooks(fns[i].ret);
            CHECK(fns[i].fn(self, 4, 5, 6) == (int)fns[i].ret);
            CHECK(g_calls == 1);
            CHECK(g_a == 0xCAFE);
            CHECK(g_b == 4 && g_c == 5 && g_d == 6);
        }

        // 0x1417af2f0 and 0x1417af310 read the SAME offset (+0x20); 0x1417afac0 reads +0x28.
        // Put a value at +0x28 only and the first two must still answer 0.
        std::memset(object, 0, sizeof(object));
        *(uint64_t*)(object + 0x28) = 0xBEEF;
        reset_hooks(3);
        CHECK(Slot_1417af2f0(self, 0, 0, 0) == 0);
        CHECK(Slot_1417af310(self, 0, 0, 0) == 0);
        CHECK(Slot_1417afac0(self, 0, 0, 0) == 3);
        CHECK(g_a == 0xBEEF);
    }

    std::printf("%s checks=%d fails=%d\n", g_fails ? "LOGIC_SLOTS_FAIL" : "LOGIC_SLOTS_OK",
                g_checks, g_fails);
    return g_fails ? 1 : 0;
}

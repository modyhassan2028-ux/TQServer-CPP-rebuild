// D140 — three bodies from the 0x1417c6c80 stretch: the two vtable-slot-0 tails
//   (0x1417c6c80 reading the object at this+0x98, 0x1417c6c90 using `this` itself) and
//   0x1417c6ca0, the setne comparison on the two +0x8 words.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

namespace tq {
bool SynAccIterNe_1417c6ca0(void*, void*);
}  // namespace tq
using namespace tq;

static int g_virtCalls = 0;
static void* g_virtObj = nullptr;
static void* g_virtFn = nullptr;

int main() {
    alignas(16) unsigned char self[0xB0];
    alignas(16) unsigned char slotObj[0x10];
    alignas(16) unsigned char vft[0x20];
    alignas(16) unsigned char a[0x20], b[0x20];
    static unsigned char target[0x10];

    std::memset(self, 0, sizeof self);
    std::memset(vft, 0, sizeof vft);
    *(void**)slotObj = target;                 // jmp *(%rax) takes the value at the slot
    *(void**)(self + 0x98) = slotObj;

    g_pfnSynVirt0_1417c6c80 = [](void* pSlot, void* pFn) -> void* {
        ++g_virtCalls; g_virtObj = pSlot; g_virtFn = pFn; return (void*)0x1234;
    };

    // ---- 0x1417c6c80: the object comes from this+0x98
    {
        g_virtCalls = 0; g_virtObj = nullptr; g_virtFn = nullptr;
        assert(SynAccVirt0At98_1417c6c80(self) == (void*)0x1234);
        assert(g_virtCalls == 1);
        assert(g_virtObj == (void*)slotObj);          // add $0x98,%rcx / mov (%rcx),...
        assert(g_virtFn == (void*)target);            // jmp *(%rax): the value at the slot
    }

    // ---- 0x1417c6c90: this itself is the object, and its own lead is the vtable
    {
        std::memset(a, 0, sizeof a);
        *(void**)a = target;
        g_virtCalls = 0; g_virtObj = nullptr; g_virtFn = nullptr;
        assert(SynAccVirt0_1417c6c90(a) == (void*)0x1234);
        assert(g_virtCalls == 1);
        assert(g_virtObj == (void*)a);
        assert(g_virtFn == (void*)target);
    }

    // ---- an unset seam invents no target
    {
        g_pfnSynVirt0_1417c6c80 = nullptr;
        assert(SynAccVirt0At98_1417c6c80(self) == nullptr);
        assert(SynAccVirt0_1417c6c90(a) == nullptr);
        g_pfnSynVirt0_1417c6c80 = [](void* pSlot, void* pFn) -> void* {
            ++g_virtCalls; g_virtObj = pSlot; g_virtFn = pFn; return (void*)0x1234;
        };
    }

    // ---- 0x1417c6ca0: equal words answer false, different words true
    {
        std::memset(a, 0, sizeof a);
        std::memset(b, 0, sizeof b);
        *(void**)a = a; *(void**)b = a;
        *(void**)(a + 8) = (void*)0x11;
        *(void**)(b + 8) = (void*)0x11;
        assert(SynAccIterNe_1417c6ca0(a, b) == false);
        *(void**)(b + 8) = (void*)0x22;
        assert(SynAccIterNe_1417c6ca0(a, b) == true);
        *(void**)(b + 8) = (void*)0x11;
        *(void**)b = slotObj;                        // different leads, equal words
        assert(SynAccIterNe_1417c6ca0(a, b) == false);
        *(void**)b = nullptr;                        // the null lead still answers on the words
        assert(SynAccIterNe_1417c6ca0(a, b) == false);
    }

    std::printf("SYNDICATE_D140_OK: two vtable tails and one comparison, 3 units, 15 checks\n");
    return 0;
}

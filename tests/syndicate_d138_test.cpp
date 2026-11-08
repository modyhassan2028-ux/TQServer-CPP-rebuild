// D138 — 0x1417c69e0, the tail call that hands `this + 0x18` to the slot at 0x141823290.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

static void* g_arg = nullptr;
static int g_calls = 0;

int main() {
    alignas(16) unsigned char self[0x80];
    alignas(16) unsigned char marker[0x10];
    std::memset(self, 0, sizeof self);

    g_pfnSynTail_141823290 = [](void* pArg) -> void* {
        ++g_calls; g_arg = pArg; return (void*)0xABCD;
    };

    // ---- the argument is this shifted by 0x18, and the answer is the callee's
    void* pRet = SynAccTail18_1417c69e0(self);
    assert(g_calls == 1);
    assert(g_arg == (void*)(self + 0x18));
    assert(pRet == (void*)0xABCD);

    // ---- and it really is `this + 0x18`, not the frame's home slot
    std::memset(self, 0x5C, sizeof self);
    *(void**)(self + 0x18) = marker;
    (void)SynAccTail18_1417c69e0(self);
    assert(g_arg == (void*)(self + 0x18));
    assert(*(void**)g_arg == (void*)marker);

    // ---- an unset seam answers nothing rather than inventing a target
    g_pfnSynTail_141823290 = nullptr;
    g_calls = 0;
    assert(SynAccTail18_1417c69e0(self) == nullptr);
    assert(g_calls == 0);

    std::printf("SYNDICATE_D138_OK: the 0x18 tail call, 1 unit, 7 checks\n");
    return 0;
}

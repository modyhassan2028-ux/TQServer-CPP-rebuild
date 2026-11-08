// D137 — the two checked forwarders 0x1417c6a60 and 0x1417c6b30 and the seams they read:
//   the assertion at 0x141823030 with its two lines (0x32a / 0x32b / 0x339) and the four
//   pointers each failing branch carries, then the prepare step and the shared forward.
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

static int g_assertCalls = 0;
static uint32_t g_line = 0;
static const void* g_p1 = nullptr;
static const void* g_p2 = nullptr;
static const void* g_p3 = nullptr;
static const void* g_p4 = nullptr;

static int g_prepCalls = 0;
static int g_prepSlotCalls = 0;
static void* g_prepArg = nullptr;
static uint32_t g_prepA3 = 0;
static void* g_slotRead = nullptr;

static int g_fwdCalls = 0;
static void* g_fwdThis = nullptr;
static void* g_fwdA2 = nullptr;
static void* g_fwdA3 = nullptr;
static int g_fwdFrom = 0;
static unsigned char g_fwdFlag = 0;

static void resetCounters() {
    g_assertCalls = 0; g_line = 0;
    g_p1 = g_p2 = g_p3 = g_p4 = nullptr;
    g_prepCalls = g_prepSlotCalls = 0; g_prepArg = nullptr; g_prepA3 = 0; g_slotRead = nullptr;
    g_fwdCalls = 0; g_fwdThis = g_fwdA2 = g_fwdA3 = nullptr; g_fwdFrom = 0; g_fwdFlag = 0;
}

int main() {
    alignas(16) unsigned char self[0x100];
    alignas(16) unsigned char a2[0x10];
    alignas(16) unsigned char a3[0x10];
    alignas(16) unsigned char slot[0x10];
    std::memset(self, 0, sizeof self);
    *(void**)(self + 0x90) = slot;

    g_pfnSynAssert_141823030 = [](const void* p1, const void* p2, const void* p3, const void* p4,
                                  uint32_t line) {
        ++g_assertCalls; g_p1 = p1; g_p2 = p2; g_p3 = p3; g_p4 = p4; g_line = line;
    };
    g_pfnSynPrep_141785dc0 = [](void* pArg) -> int {
        ++g_prepCalls; g_prepArg = pArg; return 7;
    };
    g_pfnSynPrep_14178c8e0 = [](void* pSlot90, uint32_t uA3) -> void* {
        ++g_prepSlotCalls; g_slotRead = pSlot90; g_prepA3 = uA3; return (void*)0xBEEF;
    };
    g_pfnSynFwd_1417c5640 = [](void* pThis, void* pA2, void* pA3, int nFrom, unsigned char uFlag) {
        ++g_fwdCalls; g_fwdThis = pThis; g_fwdA2 = pA2; g_fwdA3 = pA3;
        g_fwdFrom = nFrom; g_fwdFlag = uFlag;
    };

    // ---- 0x1417c6a60, both arguments present: the prepare result rides in the fourth slot
    {
        resetCounters();
        assert(SynAccChecked2_1417c6a60(self, a2, a3, 0x5A) == (void*)self);
        assert(g_assertCalls == 0);
        assert(g_prepCalls == 1 && g_prepArg == (void*)a3);
        assert(g_fwdCalls == 1);
        assert(g_fwdThis == (void*)self && g_fwdA2 == (void*)a2 && g_fwdA3 == (void*)a3);
        assert(g_fwdFrom == 7);                       // mov %eax,%r9d
        assert(g_fwdFlag == 0x5A);                    // mov %sil,0x20(%rsp)
    }

    // ---- 0x1417c6a60, missing second argument: line 0x32a, nothing forwarded
    {
        resetCounters();
        (void)SynAccChecked2_1417c6a60(self, nullptr, a3, 0x11);
        assert(g_assertCalls == 1);
        assert(g_line == 0x32a);
        assert(g_p1 == (const void*)(uintptr_t)0x141824ca8ULL);
        assert(g_p2 == (const void*)(uintptr_t)0x14182664cULL);
        assert(g_p3 == (const void*)(uintptr_t)0x141836e5cULL);
        assert(g_p4 == (const void*)(uintptr_t)0x141839fe0ULL);
        assert(g_prepCalls == 0 && g_fwdCalls == 0);
    }

    // ---- 0x1417c6a60, missing third argument: line 0x32b and a different text pointer
    {
        resetCounters();
        (void)SynAccChecked2_1417c6a60(self, a2, nullptr, 0x11);
        assert(g_assertCalls == 1);
        assert(g_line == 0x32b);
        assert(g_p3 == (const void*)(uintptr_t)0x141831610ULL);
        assert(g_fwdCalls == 0);
    }

    // ---- 0x1417c6b30, the second argument present: the 0x90 slot is read, not `this`
    {
        resetCounters();
        assert(SynAccChecked3_1417c6b30(self, a2, 0x77, 0x33) == (void*)self);
        assert(g_assertCalls == 0);
        assert(g_prepSlotCalls == 1);
        assert(g_slotRead == (void*)slot);            // mov 0x90(%rcx),%rcx
        assert(g_prepA3 == 0x77);                     // mov %r8d,%edx
        assert(g_fwdCalls == 1);
        assert(g_fwdThis == (void*)self && g_fwdA2 == (void*)a2);
        assert(g_fwdA3 == (void*)0xBEEF);             // mov %rax,%r8
        assert(g_fwdFrom == 0x77);                    // mov %edi,%r9d
        assert(g_fwdFlag == 0x33);
    }

    // ---- 0x1417c6b30, missing second argument: line 0x339
    {
        resetCounters();
        (void)SynAccChecked3_1417c6b30(self, nullptr, 0x77, 0x33);
        assert(g_assertCalls == 1);
        assert(g_line == 0x339);
        assert(g_p3 == (const void*)(uintptr_t)0x141836e5cULL);
        assert(g_prepSlotCalls == 0 && g_fwdCalls == 0);
    }

    std::printf("SYNDICATE_D137_OK: two checked forwarders, 2 units, 34 checks\n");
    return 0;
}

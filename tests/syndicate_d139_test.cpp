// D139 — 0x1417c6bd0: the checked forwarder that also dispatches through `*(this+0x88)` and
//   `0x1a0(vtable)`, then hands the work to 0x1417c6a60 with a zero flag.
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

static int g_boolCalls = 0;
static bool g_boolAnswer = true;
static int g_prepCalls = 0;

static int g_virtCalls = 0;
static void* g_virtSlot = nullptr;
static void* g_virtFn = nullptr;
static int g_virtN = 0;
static unsigned char g_virtFlag = 0;

static int g_fwdCalls = 0;
static int g_fwdFrom = -1;
static unsigned char g_fwdFlag = 0xEE;
static void* g_fwdA3 = nullptr;

int main() {
    alignas(16) unsigned char self[0xA0];
    alignas(16) unsigned char slotObj[0x10];
    alignas(16) unsigned char vft[0x1C0];
    alignas(16) unsigned char a2[0x10];
    alignas(16) unsigned char a3[0x10];
    static unsigned char sentinelFn[0x10];

    std::memset(self, 0, sizeof self);
    std::memset(vft, 0, sizeof vft);
    *(void**)(self + 0x88) = slotObj;                 // the slot the bytes read
    *(void**)slotObj = vft;                           // its vtable
    *(void**)(vft + 0x1a0) = sentinelFn;              // the 0x1a0 entry

    g_pfnSynAssert_141823030 = [](const void* p1, const void* p2, const void* p3, const void* p4,
                                  uint32_t line) {
        ++g_assertCalls; g_p1 = p1; g_p2 = p2; g_p3 = p3; g_p4 = p4; g_line = line;
    };
    g_pfnSynPrepBool_141787300 = [](void*) -> bool { ++g_boolCalls; return g_boolAnswer; };
    g_pfnSynPrep_141785dc0 = [](void*) -> int { ++g_prepCalls; return 9; };
    g_pfnSynVirt_1417c6bd0 = [](void* pSlot, void* pFn, int n, unsigned char flag) {
        ++g_virtCalls; g_virtSlot = pSlot; g_virtFn = pFn; g_virtN = n; g_virtFlag = flag;
    };
    g_pfnSynFwd_1417c5640 = [](void*, void*, void* pA3, int n, unsigned char flag) {
        ++g_fwdCalls; g_fwdA3 = pA3; g_fwdFrom = n; g_fwdFlag = flag;
    };

    // ---- the missing second argument: line 0x39c, four pointers, and a false answer
    {
        g_assertCalls = 0; g_boolCalls = 0; g_virtCalls = 0; g_prepCalls = 0;
        bool bRet = SynAccChecked4_1417c6bd0(self, nullptr, a3, 0x11);
        assert(bRet == false);
        assert(g_assertCalls == 1);
        assert(g_line == 0x39c);
        assert(g_p1 == (const void*)(uintptr_t)0x141824ca8ULL);
        assert(g_p2 == (const void*)(uintptr_t)0x141827b98ULL);
        assert(g_p3 == (const void*)(uintptr_t)0x141831610ULL);
        assert(g_p4 == (const void*)(uintptr_t)0x141839fe0ULL);
        assert(g_boolCalls == 0 && g_virtCalls == 0 && g_prepCalls == 0);
    }

    // ---- the boolean true: prepare, dispatch through the slot, then hand on with a zero flag
    {
        g_boolAnswer = true;
        g_assertCalls = g_boolCalls = g_virtCalls = g_prepCalls = 0;
        g_virtN = 0; g_virtFlag = 0; g_fwdCalls = 0; g_fwdFrom = -1; g_fwdFlag = 0xEE;
        g_fwdA3 = nullptr;
        bool bRet = SynAccChecked4_1417c6bd0(self, a2, a3, 0x5A);
        assert(bRet == true);
        assert(g_assertCalls == 0);
        assert(g_boolCalls == 1);
        assert(g_prepCalls == 2);                        // once here, once inside 0x1417c6a60
        assert(g_virtCalls == 1);
        assert(g_virtSlot == (void*)slotObj);            // mov 0x88(%rdi),%rcx
        assert(g_virtFn == (void*)sentinelFn);           // call *0x1a0(%r9)
        assert(g_virtN == 9);                            // mov %eax,%edx
        assert(g_virtFlag == 0x5A);                      // mov %esi,%r8d
    }

    // ---- the boolean false: no dispatch, no forward, and the answer is still true
    {
        g_boolAnswer = false;
        g_assertCalls = g_boolCalls = g_virtCalls = g_prepCalls = 0;
        g_fwdCalls = 0;
        bool bRet = SynAccChecked4_1417c6bd0(self, a2, a3, 0x5A);
        assert(bRet == true);
        assert(g_boolCalls == 1);
        assert(g_virtCalls == 0 && g_prepCalls == 0 && g_fwdCalls == 0);
    }

    std::printf("SYNDICATE_D139_OK: the dispatching checked forwarder, 1 unit, 22 checks\n");
    return 0;
}

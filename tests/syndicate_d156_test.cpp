// D156 — three bodies: the fourth self node 0x1417c8900, the 0x18 tail call 0x1417c8950 and the
//   copied-temp comparison 0x1417c8980 (setne).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
using namespace tq;
namespace tq {
void* SynAccTail18b_1417c8950(void* pThis);
bool  SynAccIterNeCopied_1417c8980(void* pThis, void* pOther);
}
static void* g_pPool = nullptr;
static void* NewHook(uint64_t) { return g_pPool; }
static void* g_pTailArg = nullptr;
static int   g_tailCalls = 0;
static void* TailHook(void* p) { g_pTailArg = p; g_tailCalls++; return (void*)0x77; }
int main() {
    alignas(16) unsigned char owner[0x60], pool[0x40];
    std::memset(owner, 0, sizeof owner);
    std::memset(pool, 0xCD, sizeof pool);

    // ---- 0x1417c8900: the block goes into the owner, the owner into the block
    g_pPool = pool;
    g_pfnSynNew_1417f3166 = &NewHook;
    assert(SynAccSelf8_1417c8900(owner) == (void*)owner);
    assert(*(void**)(owner) == (void*)pool);
    assert(*(void**)(pool) == (void*)owner);

    // a null answer leaves the owner's first qword zero
    g_pfnSynNew_1417f3166 = nullptr;
    *(void**)(owner) = (void*)0xAA;
    assert(SynAccSelf8_1417c8900(owner) == (void*)owner);
    assert(*(void**)(owner) == nullptr);

    // ---- 0x1417c8950: the answer comes from this+0x18, and it is what the slot returns
    g_pfnSynTail_141823290 = &TailHook;
    assert(SynAccTail18b_1417c8950(owner) == (void*)0x77);
    assert(g_tailCalls == 1);
    assert(g_pTailArg == (void*)(owner + 0x18));

    // ---- 0x1417c8980: same word at +8 answers false, different answers true
    alignas(16) unsigned char lhs[0x10], rhs[0x10], lead[0x60];
    std::memset(lhs, 0, sizeof lhs); std::memset(rhs, 0, sizeof rhs);
    *(void**)(lhs) = lead; *(void**)(rhs) = lead;
    *(void**)(lhs + 8) = (void*)0x11; *(void**)(rhs + 8) = (void*)0x11;
    assert(SynAccIterNeCopied_1417c8980(lhs, rhs) == false);
    *(void**)(rhs + 8) = (void*)0x12;
    assert(SynAccIterNeCopied_1417c8980(lhs, rhs) == true);

    std::printf("SYNDICATE_D156_OK: self node, tail call, copied comparison, 3 units\n");
    return 0;
}

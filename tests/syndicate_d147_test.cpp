// D147 — twelve bodies: 0x1417c7600 / 0x1417c76b0 / 0x1417c7830 (the decrement wrappers),
//   0x1417c7620 (the 48-byte allocator again), 0x1417c7690, 0x1417c76a0, the four node
//   builders 0x1417c76d0 / 0x1417c7710 / 0x1417c7750 / 0x1417c7790, 0x1417c77d0 and the
//   deleting destructor 0x1417c77e0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"

using namespace tq;

static int      g_nNew, g_nThrow, g_nTail, g_nFree;
static uint64_t g_uSize;
static void*    g_pTailArg;
static void*    g_pFreed;
static unsigned char g_aPool[0x100];

static void* NewHook(uint64_t uBytes) { ++g_nNew; g_uSize = uBytes; return g_aPool; }
static void* NewNull(uint64_t) { ++g_nNew; return nullptr; }
static void  ThrowHook(void*, const void*) { ++g_nThrow; }
static void  CtorHook(void*, void*) {}
static void* TailHook(void* pArg) { ++g_nTail; g_pTailArg = pArg; return nullptr; }
static void  FreeHook(void* pMem) { ++g_nFree; g_pFreed = pMem; }

int main() {
    alignas(16) unsigned char it[0x10], node[0x60], other[0x60];
    std::memset(it, 0, sizeof it);
    std::memset(node, 0, sizeof node);
    std::memset(other, 0, sizeof other);

    // ---- 0x1417c7620: the 48-byte allocator with its count in rdx
    {
        g_pfnSynNew_1417f3166 = &NewHook;
        g_pfnSynThrow_1417f3154 = &ThrowHook;
        g_pfnSynErrCtor_1418233e8 = &CtorHook;
        g_nThrow = 0; g_uSize = 0;
        assert(SynAccNew48Count2_1417c7620(nullptr, 3) == (void*)g_aPool);
        assert(g_uSize == 144 && g_nThrow == 0);
        g_uSize = 0xFFFF; g_nThrow = 0;
        SynAccNew48Count2_1417c7620(nullptr, 0x1000000000000000ull);
        assert(g_nThrow == 1 && g_uSize == 0);       // the count register was zeroed first
        g_pfnSynNew_1417f3166 = nullptr;
        g_pfnSynThrow_1417f3154 = nullptr;
        g_pfnSynErrCtor_1418233e8 = nullptr;
    }

    // ---- 0x1417c7690 and 0x1417c76a0
    SynAccNoop_1417c7690();
    {
        unsigned char src[0x20], dst[0x20];
        std::memset(src, 0, sizeof src); std::memset(dst, 0xAB, sizeof dst);
        *(void**)src = (void*)0x99;
        SynAccStoreFromR8_1417c76a0(nullptr, dst, src);
        assert(*(void**)dst == (void*)0x99);
        SynAccStoreFromR8_1417c76a0(nullptr, nullptr, src);   // a null destination is untouched
        assert(*(void**)dst == (void*)0x99);
    }

    // ---- the four node builders: eight bytes from the seam, the object written into them,
    //      the block (or zero) stored in the object's first qword, the object handed back
    {
        unsigned char obj[0x40];
        g_pfnSynNew_1417f3166 = &NewHook;
        std::memset(g_aPool, 0, 8);
        std::memset(obj, 0xAB, sizeof obj);
        assert(SynAccNewNode_1417c76d0(obj) == (void*)obj);
        assert(*(void**)obj == (void*)g_aPool);
        assert(*(void**)g_aPool == (void*)obj);      // mov %rbx,(%rax)

        std::memset(obj, 0xAB, sizeof obj);
        assert(SynAccNewNode_1417c7710(obj) == (void*)obj);
        assert(*(void**)obj == (void*)g_aPool);

        std::memset(obj, 0xAB, sizeof obj);
        assert(SynAccNewNode_1417c7750(obj) == (void*)obj);
        assert(*(void**)obj == (void*)g_aPool);

        std::memset(obj, 0xAB, sizeof obj);
        assert(SynAccNewNode_1417c7790(obj) == (void*)obj);
        assert(*(void**)obj == (void*)g_aPool);

        // a seam that answers zero stores zero and still hands the object back
        g_pfnSynNew_1417f3166 = &NewNull;
        std::memset(obj, 0xAB, sizeof obj);
        assert(SynAccNewNode_1417c76d0(obj) == (void*)obj);
        assert(*(void**)obj == nullptr);
        g_pfnSynNew_1417f3166 = nullptr;
    }

    // ---- 0x1417c77d0 stores the two dwords it is handed
    {
        unsigned char dst[0x20];
        std::memset(dst, 0xAB, sizeof dst);
        assert(SynAcc2Words_1417c77d0(dst, 0xAABBCCDDu, 0x11223344u) == (void*)dst);
        assert(*(uint32_t*)dst == 0xAABBCCDDu);
        assert(*(uint32_t*)(dst + 4) == 0x11223344u);
        assert(dst[8] == 0xAB);
    }

    // ---- the three decrement wrappers answer with the iterator they were handed
    {
        g_pfnSynTail_141823290 = &TailHook;
        std::memset(it, 0, sizeof it);
        node[0x21] = 1; node[0x29] = 1; node[0x41] = 1;
        *(void**)(it) = node;
        *(void**)(it + 8) = other;
        other[0x21] = 1; other[0x29] = 1; other[0x41] = 1;
        assert(SynAccDecCall_1417c7600(it) == (void*)it);
        assert(SynAccDecCall_1417c76b0(it) == (void*)it);
        assert(SynAccDecCall_1417c7830(it) == (void*)it);
    }

    // ---- the deleting destructor: 0x18 goes to the slot, and only bit 0 reaches the free
    {
        g_nTail = g_nFree = 0; g_pTailArg = nullptr; g_pFreed = nullptr;
        g_pfnSynTail_141823290 = &TailHook;
        g_pfnLogic_1417f2fdc = &FreeHook;

        std::memset(node, 0, sizeof node);
        assert(SynAccDtor_1417c77e0(node, 0) == (void*)node);
        assert(g_nTail == 1 && g_pTailArg == (void*)(node + 0x18));
        assert(g_nFree == 0);                        // bit 0 clear: no free

        g_nTail = g_nFree = 0;
        assert(SynAccDtor_1417c77e0(node, 3) == (void*)node);
        assert(g_nTail == 1 && g_nFree == 1 && g_pFreed == (void*)node);

        g_nTail = g_nFree = 0;
        SynAccDtor_1417c77e0(node, 0xFE);
        assert(g_nTail == 1 && g_nFree == 0);        // every bit but the low one is ignored

        g_pfnSynTail_141823290 = nullptr;
        g_pfnLogic_1417f2fdc = nullptr;
    }

    std::printf("SYNDICATE_D147_OK: twelve bodies, 12 units, 30 checks\n");
    return 0;
}

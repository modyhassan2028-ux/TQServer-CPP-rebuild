// D146 — sixteen bodies: 0x1417c7300 / 0x1417c7310 / 0x1417c7320 / 0x1417c7360,
//   the three count-in-rdx allocators 0x1417c7370 / 0x1417c73e0 / 0x1417c7450,
//   0x1417c74c0 (the 0x21 increment), the two call wrappers 0x1417c7560 / 0x1417c7590,
//   0x1417c7580, 0x1417c75b0 and the three guarded stores.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"

namespace tq {
void* SynAccCurrPlus18_1417c7320(void* pIter);
void  SynAccInc21_1417c74c0(void* pIter);
void* SynAccDecCall_1417c7560(void* pIter);
void* SynAccIncCall_1417c7590(void* pIter);
}
using namespace tq;

static int      g_nNewCalls, g_nThrowCalls, g_nCtorCalls;
static uint64_t g_uNewSize;
static unsigned char g_aPool[0x400];

static void* NewHook(uint64_t uBytes) {
    ++g_nNewCalls;
    g_uNewSize = uBytes;
    return g_aPool;
}
static void ThrowHook(void*, const void*) { ++g_nThrowCalls; }
static void CtorHook(void*, void*) { ++g_nCtorCalls; }

int main() {
    alignas(16) unsigned char node[0x60], other[0x60];
    std::memset(node, 0, sizeof node);
    std::memset(other, 0, sizeof other);

    // ---- 0x1417c7300 hands back this+0x18
    assert(SynAccPlus18_1417c7300(node) == (void*)(node + 0x18));

    // ---- the two ret $0x0 stubs are callable and do nothing
    SynAccNoop_1417c7310();
    SynAccNoop_1417c75e0();

    // ---- both zero-lead bodies clear the first qword and answer with the object
    {
        std::memset(node, 0xAB, sizeof node);
        assert(SynAccZeroLead_1417c7360(node) == (void*)node);
        assert(*(void**)node == nullptr);
        assert(node[8] == 0xAB);                       // nothing past the first qword moves
        std::memset(node, 0xAB, sizeof node);
        assert(SynAccZeroLead_1417c75b0(node) == (void*)node);
        assert(*(void**)node == nullptr);
        assert(node[8] == 0xAB);
    }

    // ---- the three allocators: count in rdx, the element width from the lea, and the
    //      throw branch zeroing the count register so a returning seam gives a zero size
    {
        g_pfnSynNew_1417f3166 = &NewHook;
        g_pfnSynThrow_1417f3154 = &ThrowHook;
        g_pfnSynErrCtor_1418233e8 = &CtorHook;

        g_nNewCalls = g_nThrowCalls = g_nCtorCalls = 0; g_uNewSize = 0;
        assert(SynAccNew48FromCount_1417c7370(nullptr, 2) == (void*)g_aPool);
        assert(g_uNewSize == 96 && g_nThrowCalls == 0);

        g_uNewSize = 0;
        assert(SynAccNew72FromCount_1417c73e0(nullptr, 2) == (void*)g_aPool);
        assert(g_uNewSize == 144 && g_nThrowCalls == 0);

        g_uNewSize = 0;
        assert(SynAccNew40FromCount_1417c7450(nullptr, 2) == (void*)g_aPool);
        assert(g_uNewSize == 80 && g_nThrowCalls == 0);

        const uint64_t uHuge = 0x1000000000000000ull;   // max/uHuge < the limits
        g_nThrowCalls = g_nCtorCalls = 0; g_uNewSize = 0xFFFF;
        SynAccNew48FromCount_1417c7370(nullptr, uHuge);
        assert(g_nThrowCalls == 1 && g_nCtorCalls == 1);
        assert(g_uNewSize == 0);                        // r8 was zeroed before the size

        g_nThrowCalls = g_nCtorCalls = 0; g_uNewSize = 0xFFFF;
        SynAccNew72FromCount_1417c73e0(nullptr, uHuge);
        assert(g_nThrowCalls == 1 && g_uNewSize == 0);

        g_nThrowCalls = g_nCtorCalls = 0; g_uNewSize = 0xFFFF;
        SynAccNew40FromCount_1417c7450(nullptr, uHuge);
        assert(g_nThrowCalls == 1 && g_uNewSize == 0);

        g_pfnSynNew_1417f3166 = nullptr;
        g_pfnSynThrow_1417f3154 = nullptr;
        g_pfnSynErrCtor_1418233e8 = nullptr;
    }

    // ---- the constant
    assert(SynAccConst_1417c7580() == 0x0fffffffffffffffull);

    // ---- the three guarded stores take rdx as the destination and r8 as the source
    {
        unsigned char src[0x20], dst[0x20];
        std::memset(src, 0, sizeof src); std::memset(dst, 0xAB, sizeof dst);
        *(void**)src = (void*)0x1234;
        SynAccStoreFromR8_1417c75c0(nullptr, dst, src);
        assert(*(void**)dst == (void*)0x1234);
        *(void**)dst = nullptr;
        SynAccStoreFromR8_1417c75c0(nullptr, nullptr, src);   // a null destination writes nothing
        assert(*(void**)dst == nullptr);
        SynAccStoreFromR8_1417c75d0(nullptr, dst, src);
        assert(*(void**)dst == (void*)0x1234);
        SynAccStoreFromR8_1417c75f0(nullptr, dst, src);
        assert(*(void**)dst == (void*)0x1234);
    }

    // ---- 0x1417c7320: the lead's 0x30 slot against the iterator's node, answer node+0x18
    {
        unsigned char it[0x10], lead[0x60], owner[0x60];
        std::memset(it, 0, sizeof it);
        std::memset(lead, 0, sizeof lead);
        std::memset(owner, 0, sizeof owner);
        *(void**)(it) = lead;
        *(void**)(lead) = owner;
        *(void**)(owner + 0x30) = (void*)0x777;
        *(void**)(it + 8) = node;                        // not 0x777, so no second check
        assert(SynAccCurrPlus18_1417c7320(it) == (void*)(node + 0x18));
        *(void**)(it + 8) = (void*)0x777;                // equal: the check runs and the answer holds
        assert(SynAccCurrPlus18_1417c7320(it) == (void*)((unsigned char*)0x777 + 0x18));
    }

    // ---- 0x1417c74c0: the 0x21 increment, header case moves the node to the 0x10 side
    {
        unsigned char it[0x10], h[0x60], r[0x60];
        std::memset(it, 0, sizeof it);
        std::memset(h, 0, sizeof h);
        std::memset(r, 0, sizeof r);
        *(void**)(it) = (void*)0x1;
        h[0x21] = 1; r[0x21] = 0;
        *(void**)(h + 0x10) = r;
        *(void**)(it + 8) = h;
        SynAccInc21_1417c74c0(it);
        assert(*(void**)(it + 8) == (void*)r);
    }

    // ---- the two wrappers answer with the iterator, not with the increment's work
    {
        unsigned char it[0x10], h[0x60], r[0x60];
        std::memset(it, 0, sizeof it);
        std::memset(h, 0, sizeof h);
        std::memset(r, 0, sizeof r);
        *(void**)(it) = h;
        h[0x29] = 1; r[0x29] = 0;
        *(void**)(h + 0x10) = r;
        *(void**)(it + 8) = h;
        assert(SynAccIncCall_1417c7590(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)r);           // 0x1417c64b0 ran

        std::memset(it, 0, sizeof it);
        r[0x41] = 1;                                     // the node itself carries the flag, so the
        *(void**)(it) = h;                               // decrement takes the tail seam and the
        *(void**)(it + 8) = r;                          // node slot never moves
        assert(SynAccDecCall_1417c7560(it) == (void*)it);
        assert(*(void**)(it + 8) == (void*)r);
    }

    std::printf("SYNDICATE_D146_OK: sixteen bodies, 16 units, 33 checks\n");
    return 0;
}

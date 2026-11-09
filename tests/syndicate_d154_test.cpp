// D154 — five bodies: the zeroed 0x28 / 0x30 nodes 0x1417c8590 / 0x1417c8620, the 0x30 pair
//   node 0x1417c8680, the copy-then-step 0x1417c85f0 and the iterator builder 0x1417c8700.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
using namespace tq;

namespace tq {
extern void (*g_pfn_invalid_parameter_noinfo)(void);
void* SynAccCopyThenDec21_1417c85f0(void* pSrc, void* pOut);
void* SynAccIterCtor3_1417c8700(void* pThis, void* pNode, void* pLeadHolder);
}

static unsigned char g_pool[0x200];
static int g_cbSeen = 0;
static void* NewHook(uint64_t cb) { g_cbSeen = (int)cb; std::memset(g_pool, 0xCD, cb); return g_pool; }

int main() {
    g_pfnSynNew_1417f3166 = &NewHook;

    // ---- 0x1417c8590: 0x28 bytes, three slots cleared, the pair at 0x20
    {
        g_cbSeen = 0;
        unsigned char* b = (unsigned char*)SynAccNew28Zero_1417c8590();
        assert(g_cbSeen == 0x28);
        assert(b == g_pool);
        assert(*(void**)b == nullptr);
        assert(*(void**)(b + 8) == nullptr);
        assert(*(void**)(b + 0x10) == nullptr);
        assert(b[0x20] == 1);
        assert(b[0x21] == 0);
        assert(b[0x22] == 0xCD);                 // nothing past the pair
    }

    // ---- 0x1417c8620: the same for 0x30, pair at 0x28
    {
        g_cbSeen = 0;
        unsigned char* b = (unsigned char*)SynAccNew30Zero2_1417c8620();
        assert(g_cbSeen == 0x30);
        assert(b == g_pool);
        assert(*(void**)b == nullptr);
        assert(*(void**)(b + 8) == nullptr);
        assert(*(void**)(b + 0x10) == nullptr);
        assert(b[0x28] == 1);
        assert(b[0x29] == 0);
        assert(b[0x2A] == 0xCD);
    }

    // ---- 0x1417c8680: three pointers in, both pair qwords, the flag byte
    {
        g_cbSeen = 0;
        void* pair[2] = { (void*)0x11, (void*)0x22 };
        unsigned char* b = (unsigned char*)SynAccNew30Pair_1417c8680(nullptr, (void*)0xA1, (void*)0xA2, (void*)0xA3, pair, 0x5A);
        assert(g_cbSeen == 0x30);
        assert(*(void**)b == (void*)0xA1);
        assert(*(void**)(b + 8) == (void*)0xA2);
        assert(*(void**)(b + 0x10) == (void*)0xA3);
        assert(*(void**)(b + 0x18) == (void*)0x11);
        assert(*(void**)(b + 0x20) == (void*)0x22);
        assert(b[0x28] == 0x5A);
        assert(b[0x29] == 0);
        assert(b[0x2A] == 0xCD);
    }

    // ---- 0x1417c85f0: the pair goes out first, then the SOURCE steps down
    {
        alignas(16) unsigned char src[0x10], out[0x10], srcNode[0x60], srcLead[0x60], stop[0x60];
        std::memset(srcNode, 0, sizeof srcNode); std::memset(srcLead, 0, sizeof srcLead);
        std::memset(stop, 0, sizeof stop);
        stop[0x21] = 1;
        *(void**)(src) = srcLead;
        *(void**)(src + 8) = srcNode;            // the node the step works on
        *(void**)(srcNode + 0x10) = stop;        // 0x1417c6580 walks the 0x10 side first
        *(void**)(srcNode + 8) = srcLead;
        srcLead[0x21] = 1;                       // the climb ends on the lead
        std::memset(out, 0, sizeof out);
        assert(SynAccCopyThenDec21_1417c85f0(src, out) == (void*)out);
        assert(*(void**)out == (void*)srcLead);   // the copy happened before the step
        assert(*(void**)(out + 8) == (void*)srcNode);
        assert(*(void**)(src + 8) == (void*)srcLead);   // and the source moved
    }

    // ---- 0x1417c8700: the iterator builder
    {
        alignas(16) unsigned char it[0x10], lead[0x10];
        std::memset(it, 0xAB, sizeof it);
        *(void**)(lead) = (void*)0x77;
        assert(SynAccIterCtor3_1417c8700(it, (void*)0x55, lead) == (void*)it);
        assert(*(void**)it == (void*)0x77);
        assert(*(void**)(it + 8) == (void*)0x55);
    }

    std::printf("SYNDICATE_D154_OK: five bodies, 5 units, 30 checks\n");
    return 0;
}

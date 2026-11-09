// D151 — five bodies: the two-bound pass 0x1417c7ff0, the 0x30 node 0x1417c80d0,
//   the header pair 0x1417c8150 / 0x1417c8170 and the comparator range 0x1417c81c0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
namespace tq {
extern bool (*g_pfnSynCmp_141823260)(void* pA, void* pB);
}
using namespace tq;

static unsigned char* g_pPool;
static uint64_t g_cbSeen;
static void* NewHook(uint64_t cb) { g_cbSeen = cb; return g_pPool; }
static bool Cmp32(void* a, void* b) {
    return (*(const uint32_t*)a < *(const uint32_t*)b);
}

int main() {
    alignas(16) unsigned char tree[0x40], h[0x60], root[0x60], n5[0x60], stop[0x60];
    alignas(16) unsigned char out[0x40], arg[0x60], pool[0x60], other[0x60];
    std::memset(tree, 0, sizeof tree); std::memset(h, 0, sizeof h);
    std::memset(root, 0, sizeof root); std::memset(n5, 0, sizeof n5);
    std::memset(stop, 0, sizeof stop); std::memset(arg, 0, sizeof arg);
    std::memset(pool, 0, sizeof pool); std::memset(other, 0, sizeof other);

    *(void**)(tree) = (void*)0xAA;
    *(void**)(tree + 0x30) = h;
    h[0x29] = 1; h[0x41] = 1;
    *(void**)(h + 8) = root;
    root[0x29] = 0; root[0x41] = 0;
    *(void**)(root + 0x18) = (void*)(uintptr_t)10;
    *(void**)(root) = n5;
    *(void**)(root + 8) = h;
    *(void**)(root + 0x10) = stop;
    n5[0x29] = 0; n5[0x41] = 0;
    *(void**)(n5 + 0x18) = (void*)(uintptr_t)5;
    *(void**)(n5) = stop;
    *(void**)(n5 + 8) = root;
    *(void**)(n5 + 0x10) = stop;
    stop[0x29] = 1; stop[0x41] = 1;

    // ---- 0x1417c7ff0: key 7 leaves both bounds on the root
    {
        uint32_t key = 7;
        std::memset(out, 0, sizeof out);
        assert(SynAccLowerUpper_1417c7ff0(tree, out, &key) == (void*)out);
        assert(*(void**)(out) == (void*)0xAA);
        assert(*(void**)(out + 8) == (void*)root);
        assert(*(void**)(out + 0x10) == (void*)0xAA);
        assert(*(void**)(out + 0x18) == (void*)root);
    }

    // ---- 0x1417c80d0: the 0x30 node takes the two pair qwords and the flag
    {
        g_pPool = pool;
        g_pfnSynNew_1417f3166 = &NewHook;   // the body allocates through this seam
        std::memset(pool, 0xCD, sizeof pool);
        *(void**)(arg) = (void*)0x11;
        *(void**)(arg + 8) = (void*)0x22;
        void* r = SynAccNew30_1417c80d0(nullptr, (void*)0x01, (void*)0x02, (void*)0x03,
                                        arg, (unsigned char)0x5A);
        assert(g_cbSeen == 0x30);
        assert(r == (void*)pool);
        assert(*(void**)(pool) == (void*)0x01);
        assert(*(void**)(pool + 8) == (void*)0x02);
        assert(*(void**)(pool + 0x10) == (void*)0x03);
        assert(*(void**)(pool + 0x18) == (void*)0x11);
        assert(*(void**)(pool + 0x20) == (void*)0x22);
        assert(pool[0x28] == 0x5A);
        assert(pool[0x29] == 0x00);       // the body clears the byte beside the colour
    }

    // ---- 0x1417c8150 / 0x1417c8170: the two pair fills
    {
        std::memset(out, 0, sizeof out);
        assert(SynAccPairHeader_1417c8150(tree, out) == (void*)out);
        assert(*(void**)(out + 8) == (void*)h);
        assert(*(void**)(out) == (void*)0xAA);

        std::memset(out, 0, sizeof out);
        *(void**)(arg + 8) = (void*)0x77;
        assert(SynAccPairChecked_1417c8170(other, out, arg) == (void*)out);
        assert(*(void**)(out) == *(void**)other);
        assert(*(void**)(out + 8) == (void*)0x77);
    }

    // ---- 0x1417c81c0: the comparator range, 0x41 flags
    {
        g_pfnSynCmp_141823260 = &Cmp32;
        uint32_t key = 7;
        std::memset(out, 0, sizeof out);
        assert(SynAccRangeCmp_1417c81c0(tree, out, &key) == (void*)out);
        assert(*(void**)(out) == (void*)0xAA);
        assert(*(void**)(out + 8) == (void*)root);
        assert(*(void**)(out + 0x10) == (void*)0xAA);
        assert(*(void**)(out + 0x18) == (void*)root);
    }

    std::printf("SYNDICATE_D151_OK: five bodies, 5 units, 22 checks\n");
    return 0;
}

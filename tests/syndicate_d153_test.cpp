// D153 — seven bodies: the iterator builder 0x1417c83f0, the two call wrappers
//   0x1417c8430 / 0x1417c84b0, the copy-then-step pair 0x1417c8450 / 0x1417c8480 and the two
//   zeroed nodes 0x1417c84d0 (0x30) / 0x1417c8530 (0x48).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
namespace tq {
extern void (*g_pfn_invalid_parameter_noinfo)(void);
void* SynAccIterCtor2_1417c83f0(void*, void*, void*);
void* SynAccInc21Call_1417c8430(void*);
void* SynAccCopyAndDec_1417c8450(void*, void*);
void* SynAccCopyAndDec41_1417c8480(void*, void*);
void* SynAccInc29Call_1417c84b0(void*);
}
using namespace tq;

static unsigned char g_pool[0x80];
static uint64_t g_cb;
static void* NewHook(uint64_t cb) { g_cb = cb; std::memset(g_pool, 0xCD, sizeof g_pool); return g_pool; }

int main() {
    alignas(16) unsigned char it[0x10], out[0x10], node[0x60], hold[0x08], hdr[0x60];

    // ---- 0x1417c83f0
    {
        std::memset(node, 0, sizeof node); std::memset(it, 0xAB, sizeof it);
        *(void**)(hold) = node;
        assert(SynAccIterCtor2_1417c83f0(it, node, hold) == (void*)it);
        assert(*(void**)(it) == (void*)node);
        assert(*(void**)(it + 8) == (void*)node);
    }

    // ---- 0x1417c8430 and 0x1417c84b0: the answer is the iterator, whatever the step does
    {
        alignas(16) unsigned char stop[0x60];
        std::memset(hdr, 0, sizeof hdr); std::memset(node, 0, sizeof node);
        std::memset(stop, 0, sizeof stop);
        stop[0x21] = 1; stop[0x29] = 1; stop[0x41] = 1;   // every family stops on this node
        hdr[0x21] = 1; hdr[0x29] = 1; hdr[0x41] = 1;      // each family reads its own byte
        *(void**)(hdr + 0x10) = node;                     // the header names the root
        *(void**)(node + 0x10) = stop;                    // and the root descends to the stop node
        *(void**)(node) = stop;                           // the 0x29 increment looks at 0x0 first
        *(void**)(node + 8) = hdr;                        // its parent is the header
        *(void**)(it) = hdr; *(void**)(it + 8) = hdr;
        assert(SynAccInc21Call_1417c8430(it) == (void*)it);
        assert(SynAccInc29Call_1417c84b0(it) == (void*)it);
    }

    // ---- 0x1417c8450: the pair leaves first, then the source steps down
    {
        std::memset(node, 0, sizeof node); std::memset(out, 0xCD, sizeof out);
        std::memset(it, 0, sizeof it);
        *(void**)(it) = node;                       // lead
        *(void**)(it + 8) = hdr;                    // a node flagged 0x29, so the step keeps it
        assert(SynAccCopyAndDec_1417c8450(it, out) == (void*)out);
        assert(*(void**)(out) == (void*)node);
        assert(*(void**)(out + 8) == (void*)hdr);
        assert(*(void**)(it + 8) == (void*)hdr);
    }

    // ---- 0x1417c8480: the same with the 0x41 step
    {
        std::memset(out, 0xCD, sizeof out);
        std::memset(it, 0, sizeof it);
        *(void**)(it) = node;
        *(void**)(it + 8) = hdr;                    // flagged 0x41 too, so nothing moves
        assert(SynAccCopyAndDec41_1417c8480(it, out) == (void*)out);
        assert(*(void**)(out) == (void*)node);
        assert(*(void**)(out + 8) == (void*)hdr);
    }

    // ---- 0x1417c84d0 / 0x1417c8530: the zeroed nodes and their colour pair
    {
        g_pfnSynNew_1417f3166 = &NewHook;
        g_cb = 0;
        assert(SynAccNew30Zero_1417c84d0() == (void*)g_pool);
        assert(g_cb == 0x30);
        assert(*(void**)(g_pool) == nullptr);
        assert(*(void**)(g_pool + 8) == nullptr);
        assert(*(void**)(g_pool + 0x10) == nullptr);
        assert(g_pool[0x28] == 1 && g_pool[0x29] == 0);
        assert(g_pool[0x2a] == 0xCD);                       // nothing past the pair is touched

        g_cb = 0;
        assert(SynAccNew48Zero_1417c8530() == (void*)g_pool);
        assert(g_cb == 0x48);
        assert(*(void**)(g_pool + 0x10) == nullptr);
        assert(g_pool[0x40] == 1 && g_pool[0x41] == 0);
        assert(g_pool[0x42] == 0xCD);
        g_pfnSynNew_1417f3166 = nullptr;
    }

    std::printf("SYNDICATE_D153_OK: seven bodies, 6 units, 25 checks\n");
    return 0;
}

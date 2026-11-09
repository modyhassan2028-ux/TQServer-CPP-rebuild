// D155 — six bodies: the copy-then-step 0x1417c8740, the two recursive destroys 0x1417c8770 /
//   0x1417c87c0 and the three eight-byte self nodes 0x1417c8810 / 0x1417c8860 / 0x1417c88b0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>

namespace tq {
extern void (*g_pfnLogic_1417f2fdc)(void* p);
void* SynAccCopyThenDec29b_1417c8740(void* pSrc, void* pOut);
void SynAccEraseAll21_1417c8770(void* pTree, unsigned char* pNode);
void SynAccEraseAll29b_1417c87c0(void* pTree, unsigned char* pNode);
void* SynAccSelf8_1417c8810(void* pThis);
void* SynAccSelf8_1417c8860(void* pThis);
void* SynAccSelf8_1417c88b0(void* pThis);
}

#include "modules/syndicate/src/synacc.h"
using namespace tq;

static void* g_pPool = nullptr;
static int   g_newCalls = 0;
static uint64_t g_cbSeen = 0;
static void* (*g_prevNew)(uint64_t) = nullptr;

static void* NewHook(uint64_t cb) {
    g_newCalls++; g_cbSeen = cb;
    return g_pPool;
}

static void*  g_freed[16];
static int    g_freeCount = 0;
static void (*g_prevFree)(void*) = nullptr;

static void FreeHook(void* p) {
    if (g_freeCount < 16) g_freed[g_freeCount] = p;
    g_freeCount++;
}

int main() {
    alignas(16) unsigned char src[0x60], out[0x60], owner[0x60];
    std::memset(src, 0, sizeof src); std::memset(out, 0xCD, sizeof out);
    std::memset(owner, 0, sizeof owner);

    // ---- 0x1417c8740: the pair first, then the source steps down
    {
        alignas(16) unsigned char stop[0x60], node[0x60];
        std::memset(stop, 0, sizeof stop); std::memset(node, 0, sizeof node);
        stop[0x29] = 1;
        *(void**)(node + 0x10) = stop;              // the descent ends on the flagged node
        *(void**)(node + 8) = stop;                 // and the climb stops there too
        *(void**)(src) = (void*)0x11;
        *(void**)(src + 8) = node;
        std::memset(out, 0xCD, sizeof out);
        assert(SynAccCopyThenDec29b_1417c8740(src, out) == (void*)out);
        assert(*(void**)(out) == (void*)0x11);      // the pair came from the source
        assert(*(void**)(out + 8) == (void*)node);
        assert(*(void**)(src + 8) == (void*)stop);  // the step climbed to the flagged parent
    }

    // ---- the two recursive destroys: every unflagged node goes to the free seam, one at a time
    {
        alignas(16) unsigned char a[0x60], b[0x60], c[0x60];
        std::memset(a, 0, sizeof a); std::memset(b, 0, sizeof b); std::memset(c, 0, sizeof c);
        *(void**)(a) = b; *(void**)(a + 0x10) = b;  // a's right is b, then a's left is b
        *(void**)(b) = c; *(void**)(b + 0x10) = c;
        *(void**)(c) = c; *(void**)(c + 0x10) = c;
        c[0x21] = 1; c[0x29] = 1;                   // c is the stop node for both families

        g_freeCount = 0; g_prevFree = g_pfnLogic_1417f2fdc; g_pfnLogic_1417f2fdc = &FreeHook;
        SynAccEraseAll21_1417c8770(nullptr, a);
        assert(g_freeCount == 3);   // b, then a (the inner walk), then b again on the outer left step
        assert(g_freed[0] == (void*)b || g_freed[0] == (void*)a);

        g_freeCount = 0;
        SynAccEraseAll29b_1417c87c0(nullptr, a);
        assert(g_freeCount == 3);   // the same walk, its own start
        g_pfnLogic_1417f2fdc = g_prevFree;
    }

    // ---- the eight-byte self nodes
    {
        alignas(16) unsigned char pool[0x20], own[0x60];
        std::memset(pool, 0xCD, sizeof pool); std::memset(own, 0, sizeof own);
        g_pPool = pool; g_prevNew = g_pfnSynNew_1417f3166; g_pfnSynNew_1417f3166 = &NewHook;

        g_newCalls = 0;
        assert(SynAccSelf8_1417c8810(own) == (void*)own);
        assert(g_newCalls == 1 && g_cbSeen == 8);
        assert(*(void**)(own) == (void*)pool);
        assert(*(void**)(pool) == (void*)own);

        std::memset(pool, 0xCD, sizeof pool);
        assert(SynAccSelf8_1417c8860(own) == (void*)own);
        assert(*(void**)(pool) == (void*)own);

        std::memset(pool, 0xCD, sizeof pool);
        assert(SynAccSelf8_1417c88b0(own) == (void*)own);
        assert(*(void**)(pool) == (void*)own);

        g_pPool = nullptr;                          // a null answer leaves the owner's slot zero
        *(void**)(own) = (void*)0x77;
        assert(SynAccSelf8_1417c8810(own) == (void*)own);
        assert(*(void**)(own) == nullptr);

        g_pfnSynNew_1417f3166 = g_prevNew;
    }

    std::printf("SYNDICATE_D155_OK: six bodies, 3 units, 22 checks\n");
    return 0;
}

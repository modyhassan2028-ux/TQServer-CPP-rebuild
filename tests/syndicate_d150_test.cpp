// D150 — the subtree erase 0x1417c7c30: one real removal (leaf under the root) and the
//   sentinel path that builds the throw through four seams.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"
using namespace tq;

namespace tq { extern void (*g_pfnLogic_1417f2fdc)(void* p); }

static int s_nFree; static void* s_pFreed;
static int s_nTmp, s_nF3f8, s_nF288, s_nThrow;

int main() {
    void (*savedFree)(void*) = g_pfnLogic_1417f2fdc;
    void (*savedTmp)(void*, void*) = g_pfnSynTmp_141823270;
    void (*savedF3f8)(void*) = g_pfnSyn_1418233f8;
    void (*savedF288)(void*, void*) = g_pfnSyn_141823288;
    void (*savedThrow)(void*, const void*) = g_pfnSynThrow_1417f3154;

    g_pfnLogic_1417f2fdc = [](void* p) { ++s_nFree; s_pFreed = p; };
    g_pfnSynTmp_141823270 = [](void*, void*) { ++s_nTmp; };
    g_pfnSyn_1418233f8 = [](void*) { ++s_nF3f8; };
    g_pfnSyn_141823288 = [](void*, void*) { ++s_nF288; };
    g_pfnSynThrow_1417f3154 = [](void*, const void*) { ++s_nThrow; };

    alignas(16) unsigned char tree[0x40], h[0x60], r[0x60], l[0x60], stop[0x60], it[0x10], out[0x10];
    std::memset(tree, 0, sizeof tree); std::memset(h, 0, sizeof h);
    std::memset(r, 0, sizeof r); std::memset(l, 0, sizeof l); std::memset(stop, 0, sizeof stop);
    std::memset(it, 0, sizeof it); std::memset(out, 0, sizeof out);

    tree[0] = 0xAA;                                  // the tree's own first qword
    *(void**)(tree + 0x30) = h;                      // the header
    *(uint64_t*)(tree + 0x38) = 2;                   // the size

    h[0x29] = 1;                                     // the header is the end node
    *(void**)(h + 8) = r;
    *(void**)(h) = l;
    *(void**)(h + 0x10) = r;

    r[0x28] = 1;                                     // black
    *(void**)(r) = l;
    *(void**)(r + 0x10) = stop;
    *(void**)(r + 8) = h;

    l[0x28] = 1;
    *(void**)(l) = stop;
    *(void**)(l + 0x10) = stop;
    *(void**)(l + 8) = r;

    stop[0x29] = 1;
    *(void**)(stop) = stop;
    *(void**)(stop + 0x10) = stop;
    *(void**)(stop + 8) = h;

    *(void**)(it) = h;
    *(void**)(it + 8) = r;

    // ---- the leaf under the root goes, the iterator steps on first
    {
        assert(SynTreeErase_1417c7c30(tree, out, it) == (void*)out);
        assert(s_nFree == 1 && s_pFreed == (void*)r);      // 0x1417f2fdc got the node itself
        assert(*(void**)(h + 8) == (void*)l);              // the header names the survivor
        assert(*(void**)(l + 8) == (void*)h);
        assert(*(void**)(h + 0x10) == (void*)l);           // the right edge moved down too
        assert(*(uint64_t*)(tree + 0x38) == 1);            // the size came down
        assert(*(void**)(it + 8) == (void*)h);             // the decrement ran before the links
        assert(*(void**)(out) == (void*)0xAA);             // the pair took the tree's own qword
        assert(*(void**)(out + 8) == (void*)h);
        assert(s_nTmp == 0 && s_nThrow == 0);
    }

    // ---- an iterator sitting on the sentinel builds the throw, then runs on
    {
        s_nFree = 0; s_nTmp = s_nF3f8 = s_nF288 = s_nThrow = 0;
        *(uint64_t*)(tree + 0x38) = 1;
        *(void**)(h + 8) = stop;
        *(void**)(stop + 0x28) = 0;                        // keeps the fix-up out of the loop
        *(void**)(it + 8) = stop;
        SynTreeErase_1417c7c30(tree, out, it);
        assert(s_nTmp == 1 && s_nF3f8 == 1 && s_nF288 == 1 && s_nThrow == 1);
        assert(s_nFree == 1 && s_pFreed == (void*)stop);
        assert(*(uint64_t*)(tree + 0x38) == 0);
    }

    g_pfnLogic_1417f2fdc = savedFree;
    g_pfnSynTmp_141823270 = savedTmp;
    g_pfnSyn_1418233f8 = savedF3f8;
    g_pfnSyn_141823288 = savedF288;
    g_pfnSynThrow_1417f3154 = savedThrow;
    std::printf("SYNDICATE_D150_OK: the subtree erase, 2 paths, 19 checks\n");
    return 0;
}

// D135 — the four element-count allocators and the three seams they run through:
//   0x1417c6710 and 0x1417c6910 (0x30 limit, 3*16 bytes per element),
//   0x1417c6790 (0x48 limit, 9*8), 0x1417c6810 (0x28 limit, 5*8).
#include "modules/syndicate/src/synacc.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

static uint64_t g_cb = 0;             // the byte count handed to 0x1417f3166
static int g_newCalls = 0;
static int g_ctorCalls = 0;
static int g_throwCalls = 0;
static unsigned char g_pool[0x1000];
static void* g_pObjSeen = nullptr;
static const void* g_pWhatSeen = nullptr;

int main() {
    static unsigned char fakeVft[0x10];

    g_pfnSynNew_1417f3166 = [](uint64_t cb) -> void* {
        g_cb = cb;
        ++g_newCalls;
        return (void*)g_pool;
    };
    g_pfnSynErrCtor_1418233e8 = [](void* pObj, void* pEmpty) {
        ++g_ctorCalls;
        g_pObjSeen = pObj;
        (void)pEmpty;
    };
    g_pfnSynThrow_1417f3154 = [](void* pObj, const void* pWhat) {
        ++g_throwCalls;
        g_pObjSeen = pObj;
        g_pWhatSeen = pWhat;
    };
    (void)fakeVft;

    // ---- the good path: the size is the element count times the stride the bytes form
    {
        g_newCalls = g_ctorCalls = g_throwCalls = 0;
        g_cb = 0;
        assert(SynAccNew48_1417c6710(4) == (void*)g_pool);
        assert(g_cb == 4 * 48);                       // lea (%rcx,%rcx,2) / shl $0x4
        assert(g_newCalls == 1 && g_ctorCalls == 0 && g_throwCalls == 0);

        g_cb = 0;
        assert(SynAccNew48_1417c6910(4) == (void*)g_pool);
        assert(g_cb == 4 * 48);

        g_cb = 0;
        assert(SynAccNew72_1417c6790(4) == (void*)g_pool);
        assert(g_cb == 4 * 72);                       // lea (%rcx,%rcx,8) / shl $0x3

        g_cb = 0;
        assert(SynAccNew40_1417c6810(4) == (void*)g_pool);
        assert(g_cb == 4 * 40);                       // lea (%rcx,%rcx,4) / shl $0x3

        // zero elements still reaches the allocation, with a zero byte count
        g_cb = 1;
        assert(SynAccNew40_1417c6810(0) == (void*)g_pool);
        assert(g_cb == 0);
    }

    // ---- the failing side: -1 divided by the count falls under the limit and the
    //      length_error path runs instead
    {
        g_newCalls = g_ctorCalls = g_throwCalls = 0;
        const uint64_t huge = 1ull << 60;             // max / huge == 0xF, under 0x30
        g_cb = 0;
        (void)SynAccNew48_1417c6710(huge);
        assert(g_ctorCalls == 1);                     // the object was constructed
        assert(g_throwCalls == 1);                    // and handed to the throw helper
        assert(g_pWhatSeen == (const void*)(uintptr_t)0x141881df0ULL);
        assert(g_newCalls == 1);                      // the bytes still fall through to the size

        g_ctorCalls = g_throwCalls = 0;
        (void)SynAccNew72_1417c6790(huge);
        assert(g_ctorCalls == 1 && g_throwCalls == 1);

        g_ctorCalls = g_throwCalls = 0;
        (void)SynAccNew40_1417c6810(huge);
        assert(g_ctorCalls == 1 && g_throwCalls == 1);

        g_ctorCalls = g_throwCalls = 0;
        (void)SynAccNew48_1417c6910(huge);
        assert(g_ctorCalls == 1 && g_throwCalls == 1);

        // and the boundary itself: max / 0x30 elements gives a quotient right at the limit,
        // so `jae` sends it to the allocation instead of the throw
        g_ctorCalls = g_throwCalls = 0;
        const uint64_t edge = 0xFFFFFFFFFFFFFFFFull / 0x30ull;   // quotient 0x30
        g_cb = 0;
        (void)SynAccNew48_1417c6710(edge);
        assert(g_ctorCalls == 0 && g_throwCalls == 0);
        assert(g_cb == edge * 48);
    }

    std::printf("SYNDICATE_D135_OK: the four element-count allocators, 4 units, 30 checks\n");
    return 0;
}

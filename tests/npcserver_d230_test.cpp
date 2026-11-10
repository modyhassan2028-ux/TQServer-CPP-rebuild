// D230 — the alloc, forward-move, range-check and position bodies of 0x140080000..0x140090000.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <new>
#include "modules/npcserver/unattributed/stl-shapes.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_invalid = 0;
static int g_news = 0, g_moves = 0;
static long long g_lastBytes = 0;

static void InvalidParam(void) { ++g_invalid; }
static char g_aArena[1 << 20];
static void* FakeNew(long long n) { ++g_news; g_lastBytes = n; (void)g_aArena; return g_aArena; }
static void FakeMove(void* pDst, size_t, const void* pSrc, size_t cbSrc) {
    ++g_moves;
    std::memmove(pDst, pSrc, cbSrc);
}

int main() {
    g_pfnNpcInvalidParameter = &InvalidParam;
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcMemmoveS = &FakeMove;

    assert(g_nNpcShape_140080000 == 30);
    int nAlloc = 0, nMoves = 0, nBounds = 0, nPos = 0;

    for (int i = 0; i < g_nNpcShape_140080000; ++i) {
        const NpcShapeEntry& e = g_aNpcShape_140080000[i];
        assert(e.pszAddress && e.pszFamily && e.pfn);

        if (std::strcmp(e.pszFamily, "alloc-raw") == 0) {
            const long long nElem = e.nElem;
            g_news = 0; g_lastBytes = 0;
            // nArg is the index of the count parameter in the image's own signature: 1 = (nCount),
            // 2 = (pAllocator, nCount)
            if (e.nArg == 1) {
                ((void (*)(unsigned long long))e.pfn)(5);
            } else {
                ((void (*)(void*, unsigned long long))e.pfn)(nullptr, 5);   // allocator arg is ignored
            }
            assert(g_news == 1 && g_lastBytes == 5 * nElem);

            g_news = 0;
            if (e.nArg == 1) {
                ((void (*)(unsigned long long))e.pfn)(0);   // zero skips the guard and still asks
            } else {
                ((void (*)(void*, unsigned long long))e.pfn)(nullptr, 0);
            }
            assert(g_news == 1 && g_lastBytes == 0);

            // the over-allocation guard: a count whose product overflows is refused before operator_new
            g_news = 0;
            bool caught = false;
            try {
                const unsigned long long nOver = 0xFFFFFFFFFFFFFFFFull / (unsigned long long)nElem + 1;
                if (e.nArg == 1) {
                    ((void (*)(unsigned long long))e.pfn)(nOver);
                } else {
                    ((void (*)(void*, unsigned long long))e.pfn)(nullptr, nOver);
                }
            } catch (const std::bad_alloc&) {
                caught = true;
            }
            assert(caught && g_news == 0);
            ++nAlloc;

        } else if (std::strcmp(e.pszFamily, "memmove-forward") == 0) {
            const long long nElem = e.nElem;
            unsigned char aFrom[64], aTo[64];
            std::memset(aFrom, 0x5A, sizeof aFrom);
            std::memset(aTo, 0, sizeof aTo);
            g_moves = 0;
            // three elements: the byte count is three times the element size
            void* pRet = ((void* (*)(void*, long long, void*))e.pfn)(aFrom, (long long)aFrom + 3 * nElem, aTo);
            assert(pRet == aTo + 3 * nElem);
            assert(g_moves == 1);
            assert(aTo[0] == 0x5A && aTo[3 * nElem - 1] == 0x5A);
            assert(aTo[3 * nElem] == 0);                 // nothing past the count is touched
            g_moves = 0;
            pRet = ((void* (*)(void*, long long, void*))e.pfn)(aFrom, (long long)aFrom, aTo);
            assert(pRet == aTo && g_moves == 0);         // an empty range moves nothing
            ++nMoves;

        } else if (std::strcmp(e.pszFamily, "iterator-bounds") == 0) {
            // nElem is the low word index and nArg the high one, straight out of the body's own offsets
            unsigned long long aSource[6] = { 0, 0, 0, 10, 20, 0 };
            const unsigned long long nLow = e.nElem, nHigh = e.nArg;
            unsigned long long aOut[3] = { 0xEE, 0xEE, 0xEE };
            g_invalid = 0;
            unsigned long long* pRet =
                ((unsigned long long* (*)(unsigned long long*, unsigned long long, unsigned long long*))e.pfn)
                (aOut, 15, aSource);
            (void)nLow; (void)nHigh;
            assert(pRet == aOut && aOut[0] == 0 && aOut[1] == 15 && g_invalid == 0);
            // inside the range the pair carries the source word
            aSource[0] = 0xAB;
            ((unsigned long long* (*)(unsigned long long*, unsigned long long, unsigned long long*))e.pfn)
                (aOut, 10, aSource);
            assert(aOut[0] == 0xAB && aOut[1] == 10 && g_invalid == 0);
            // below the low bound and above the high bound are both rejected
            g_invalid = 0;
            ((unsigned long long* (*)(unsigned long long*, unsigned long long, unsigned long long*))e.pfn)
                (aOut, 9, aSource);
            assert(g_invalid == 1);
            g_invalid = 0;
            ((unsigned long long* (*)(unsigned long long*, unsigned long long, unsigned long long*))e.pfn)
                (aOut, 21, aSource);
            assert(g_invalid == 1);
            ++nBounds;

        } else if (std::strcmp(e.pszFamily, "position-build") == 0) {
            unsigned long long aSource[6] = { 0x77, 0, 0, 10, 20, 0 };
            const unsigned long long nWord = aSource[e.nElem];
            unsigned long long aOut[3] = { 0xEE, 0xEE, 0xEE };
            g_invalid = 0;
            unsigned long long* pRet =
                ((unsigned long long* (*)(unsigned long long*, unsigned long long*))e.pfn)(aOut, aSource);
            assert(pRet == aOut && aOut[0] == 0x77 && aOut[1] == nWord && g_invalid == 0);
            // invert the two words: the guard fires, and the pair is still built from the same word
            unsigned long long aSwapped[6] = { 0x77, 0, 0, 20, 10, 0 };
            // swap only the two words this body actually compares
            aSwapped[e.nElem] = aSource[e.nArg];
            aSwapped[e.nArg] = aSource[e.nElem];
            g_invalid = 0;
            ((unsigned long long* (*)(unsigned long long*, unsigned long long*))e.pfn)(aOut, aSwapped);
            assert(g_invalid == 1);
            ++nPos;

        } else {
            assert(!"unknown family in the manifest");
        }
    }

    assert(nAlloc == 12 && nMoves == 4 && nBounds == 6 && nPos == 8);
    std::printf("NPCSERVER_D230_OK: 30 alloc/move/bounds/position bodies\n");
    return 0;
}

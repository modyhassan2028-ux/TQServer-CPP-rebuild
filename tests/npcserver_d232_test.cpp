// D232 — the four tail shapes of 0x140080000..0x140090000 (three bodies each).
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/stl-tail.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_invalid = 0, g_moves = 0, g_assigns = 0;
static void InvalidParam(void) { ++g_invalid; }
static void FakeMove(void* pDst, size_t, const void* pSrc, size_t cbSrc) { ++g_moves; std::memmove(pDst, pSrc, cbSrc); }

int main() {
    g_pfnNpcInvalidParameter = &InvalidParam;
    g_pfnNpcMemmoveS = &FakeMove;

    assert(g_nNpcTail_140080000 == 12);
    int nMove = 0, nDrop = 0, nFill = 0, nPos = 0;

    for (int i = 0; i < g_nNpcTail_140080000; ++i) {
        const NpcTailEntry& e = g_aNpcTail_140080000[i];
        assert(e.pszAddress && e.pszFamily && e.pfn);

        if (std::strcmp(e.pszFamily, "move-backward") == 0) {
            const long long nElem = e.nValue;
            unsigned char aFrom[64], aTo[128];
            std::memset(aFrom, 0x3C, sizeof aFrom);
            std::memset(aTo, 0, sizeof aTo);
            g_moves = 0;
            // three elements ending at three elements before the destination
            void* pRet = ((void* (*)(void*, long long, long long))e.pfn)
                (aFrom, (long long)aFrom + 3 * nElem, (long long)aTo + 6 * nElem);
            assert(pRet == aTo + 3 * nElem);              // the destination end is the range length back
            assert(g_moves == 1);
            assert(aTo[3 * nElem] == 0x3C && aTo[6 * nElem - 1] == 0x3C);
            assert(aTo[3 * nElem - 1] == 0);
            g_moves = 0;
            pRet = ((void* (*)(void*, long long, long long))e.pfn)(aFrom, (long long)aFrom, (long long)aTo);
            assert(pRet == aTo && g_moves == 0);          // an empty range moves nothing
            ++nMove;

        } else if (std::strcmp(e.pszFamily, "clear-or-drop") == 0) {
            unsigned long long aPair[2] = { 0, 0 };
            ((void (*)(unsigned long long*))e.pfn)(aPair);          // nothing held: just cleared
            assert(aPair[0] == 0 && aPair[1] == 0);
            ++nDrop;

        } else if (std::strcmp(e.pszFamily, "ref-fill") == 0) {
            unsigned long long aSource[2] = { 0x21, 0 };
            unsigned long long aOut[2] = { 0xEE, 0xEE };
            ((void (*)(unsigned long long*, unsigned long long*))e.pfn)(aOut, aSource);
            assert(aOut[0] == 0x21 && aOut[1] == 0);
            // a null destination is left alone
            ((void (*)(unsigned long long*, unsigned long long*))e.pfn)(nullptr, aSource);
            ++nFill;

        } else if (std::strcmp(e.pszFamily, "position-member") == 0) {
            unsigned long long aSource[6] = { 0x66, 0, 0, 5, 30, 0 };
            unsigned long long aOut[3] = { 0xEE, 0xEE, 0xEE };
            unsigned long long aMember[3] = { 0, 17, 0 };          // the word sits at the member's +8
            g_invalid = 0;
            unsigned long long* pRet =
                ((unsigned long long* (*)(unsigned long long*, unsigned long long*, long long))e.pfn)
                (aSource, aOut, (long long)aMember);
            assert(pRet == aOut && aOut[0] == 0x66 && aOut[1] == 17 && g_invalid == 0);
            // a word outside the range is refused
            aMember[1] = 40;
            g_invalid = 0;
            ((unsigned long long* (*)(unsigned long long*, unsigned long long*, long long))e.pfn)
                (aSource, aOut, (long long)aMember);
            assert(g_invalid == 1);
            // a null source is not exercised: after the hook the body still reads pSource[0], so with a no-op
            // hook it faults by design (the same shape as the other range checks).
            ++nPos;

        } else {
            assert(!"unknown family in the manifest");
        }
    }

    assert(nMove == 3 && nDrop == 3 && nFill == 3 && nPos == 3);
    std::printf("NPCSERVER_D232_OK: 12 tail bodies\n");
    return 0;
}

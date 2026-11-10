// D229 — the forwarding wrappers and pair constructs of 0x140080000..0x140090000, walked through the manifest.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/stl-iterators.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_invalid = 0;
static void InvalidParam(void) { ++g_invalid; }

// every seam the wrappers use, so a call can be counted
static int g_called[20];
static long long SeamV(long long*, long long) { ++g_called[19]; return 0; }
static long long Seam0(long long*) { ++g_called[0]; return 0; }
static long long Seam1(long long*) { ++g_called[1]; return 0; }
static long long Seam2(long long*) { ++g_called[2]; return 0; }
static long long Seam3(long long*) { ++g_called[3]; return 0; }
static long long Seam4(long long*) { ++g_called[4]; return 0; }
static long long Seam5(long long*) { ++g_called[5]; return 0; }
static long long Seam6(long long*) { ++g_called[6]; return 0; }
static long long Seam7(long long*) { ++g_called[7]; return 0; }
static long long Seam8(long long*) { ++g_called[8]; return 0; }
static long long Seam9(long long*) { ++g_called[9]; return 0; }
static long long Seam10(long long*) { ++g_called[10]; return 0; }

int main() {
    g_pfnNpcInvalidParameter = &InvalidParam;
    // the two-argument wrappers get the two-argument seam, the rest the one-argument seam
    g_pfnNpc_140080450 = &SeamV;  g_pfnNpc_140080560 = &SeamV;  g_pfnNpc_140080610 = &SeamV;
    g_pfnNpc_1400848c0 = &Seam0;  g_pfnNpc_140085580 = &SeamV;  g_pfnNpc_1400857f0 = &Seam1;
    g_pfnNpc_14008dd10 = &Seam2;  g_pfnNpc_14008dfc0 = &SeamV;  g_pfnNpc_14008e4e0 = &Seam3;
    g_pfnNpc_14008e580 = &Seam4;  g_pfnNpc_14008e610 = &Seam5;

    assert(g_nNpcIter_140080000 == 23);
    int nFwd = 0, nPair = 0;

    for (int i = 0; i < g_nNpcIter_140080000; ++i) {
        const NpcIteratorEntry& e = g_aNpcIter_140080000[i];
        assert(e.pszAddress != nullptr && e.pfn != nullptr);

        if (std::strcmp(e.pszFamily, "forwarder") == 0) {
            // the wrapper passes its own argument through and hands the same pointer back
            long long aObject[3] = { 0x11, 0x22, 0x33 };
            std::memset(g_called, 0, sizeof g_called);
            long long* pRet = ((long long* (*)(long long*))e.pfn)(aObject);
            assert(pRet == aObject);
            assert(aObject[0] == 0x11 && aObject[2] == 0x33);   // the wrapper itself touches nothing
            int nTotal = 0;
            for (int k = 0; k < 20; ++k) nTotal += g_called[k];
            assert(nTotal == 1);                                // exactly one forward, once
            ++nFwd;
        } else if (std::strcmp(e.pszFamily, "pair-construct") == 0) {
            unsigned long long aSource[2] = { 0xABCDEF, 0x123 };
            unsigned long long aPair[4];
            std::memset(aPair, 0xEE, sizeof aPair);
            g_invalid = 0;
            unsigned long long* pRet =
                ((unsigned long long* (*)(unsigned long long*, unsigned long long, unsigned long long*))e.pfn)
                (aPair, 0x55, aSource);
            assert(pRet == aPair);
            assert(aPair[0] == 0xABCDEF);        // the first word is copied out of the source
            assert(aPair[1] == 0x55);            // the second is stored as given
            assert(g_invalid == 0);

            // a null source is not exercised: after the hook the body dereferences the source word, so with a
            // no-op hook it faults by design (same as the iterator-check family).
            (void)0;
            ++nPair;
        } else {
            assert(!"unknown family in the manifest");
        }
    }

    assert(nFwd == 15 && nPair == 8);
    std::printf("NPCSERVER_D229_OK: 23 wrapper and pair bodies\n");
    return 0;
}

// D239 — the six checked vector accessors: the size check at +0x20, the two steps, and the two tail readers.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/vector-accessors.h"

using namespace tq;

static int g_invalid = 0;
static void Invalid(void) { ++g_invalid; }

int main() {
    g_pfnNpcInvalidParameter = &Invalid;

    // the owner's first qword points at a block whose +0x20 is the size and +0x30 the end marker
    char aBlock[0x40];
    std::memset(aBlock, 0, sizeof aBlock);
    *(long long*)(aBlock + 0x20) = 16;              // size
    *(long long*)(aBlock + 0x30) = 0xE000;          // end marker

    long long aOwner[2] = { (long long)aBlock, 0 };

    assert(g_nNpcVectorAccessor == 6);
    int nPos = 0, nStep = 0, nTail = 0;

    for (int i = 0; i < g_nNpcVectorAccessor; ++i) {
        const NpcVectorAccessorEntry& e = g_aNpcVectorAccessor[i];
        assert(e.pszAddress && e.pszKind && e.pfn);

        if (std::strcmp(e.pszKind, "position") == 0) {
            long long aIter[2] = { (long long)aOwner, 8 };
            g_invalid = 0;
            long long nRet = ((long long (*)(long long*))e.pfn)(aIter);
            assert(g_invalid == 0 && nRet == 8);           // inside the range: quiet, and the position comes back
            aIter[1] = 16;
            g_invalid = 0;
            nRet = ((long long (*)(long long*))e.pfn)(aIter);
            assert(g_invalid == 1);                        // the end is refused
            assert(nRet == 16);                            // but the position is still answered
            ++nPos;

        } else if (std::strcmp(e.pszKind, "step") == 0) {
            long long aIter[2] = { (long long)aOwner, 8 };
            g_invalid = 0;
            long long* pRet = ((long long* (*)(long long*))e.pfn)(aIter);
            assert(g_invalid == 0);
            assert(pRet == aIter);
            assert(aIter[1] == 8 + e.nValue);              // 8 or 4, as the body says
            aIter[1] = 16;
            g_invalid = 0;
            ((long long* (*)(long long*))e.pfn)(aIter);
            assert(g_invalid == 1);
            assert(aIter[1] == 16 + e.nValue);             // it steps even when it complains
            ++nStep;

        } else if (std::strcmp(e.pszKind, "tail") == 0) {
            long long aIter[2] = { (long long)aOwner, 0xE100 };
            g_invalid = 0;
            long long nRet = ((long long (*)(long long*))e.pfn)(aIter);
            assert(g_invalid == 0);
            assert(nRet == 0xE100 + e.nValue);             // the slot after the position
            aIter[1] = 0xE000;                             // the end marker itself
            g_invalid = 0;
            nRet = ((long long (*)(long long*))e.pfn)(aIter);
            assert(g_invalid == 1);
            assert(nRet == 0xE000 + e.nValue);
            ++nTail;
        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nPos == 2 && nStep == 2 && nTail == 2);
    // the two steps are 8 and 4, one per element width
    assert(g_aNpcVectorAccessor[2].nValue == 8 && g_aNpcVectorAccessor[3].nValue == 4);

    std::printf("NPCSERVER_D239_OK: 6 checked vector accessors\n");
    return 0;
}

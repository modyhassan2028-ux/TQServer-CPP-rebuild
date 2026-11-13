// D252 — every generated small body, driven from its manifest entry.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/small-bodies.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"

using namespace tq;

static unsigned char g_aObject[0x200];
static unsigned char g_aInner[0x200];
static long long g_aBase[16];
static int g_invalids = 0;
static void Invalid(void) { ++g_invalids; }

static unsigned long long Pattern(int nSize) {
    switch (nSize) {
        case 1: return 0x00000000000000ABULL;
        case 2: return 0x000000000000BEEFULL;
        case 4: return 0x00000000DEADBEEFULL;
        default: return 0x123456789ABCDEF0ULL;
    }
}

static void StoreAt(void* pDst, int nSize, unsigned long long nValue) {
    switch (nSize) {
        case 1: *(unsigned char*)pDst = (unsigned char)nValue; break;
        case 2: *(unsigned short*)pDst = (unsigned short)nValue; break;
        case 4: *(unsigned*)pDst = (unsigned)nValue; break;
        default: *(unsigned long long*)pDst = nValue; break;
    }
}

int main() {
    g_pfnNpcInvalidParameter = &Invalid;
    g_pNpcModuleBase_1401045b8 = g_aBase;

    assert(g_nNpcSmallBody > 100);
    int nSeen[9] = { 0 };
    int nKinds = 0;

    for (int i = 0; i < g_nNpcSmallBody; ++i) {
        const NpcSmallBodyEntry& e = g_aNpcSmallBody[i];
        const unsigned long long nValue = Pattern(e.nSize);

        if (std::strcmp(e.pszKind, "get-offset") == 0) {
            std::memset(g_aObject, 0, sizeof g_aObject);
            StoreAt(g_aObject + e.nOffset, e.nSize, nValue);
            assert(((unsigned long long (*)(long long))e.pfn)((long long)g_aObject) == nValue);
            ++nSeen[0];

        } else if (std::strcmp(e.pszKind, "get-deref") == 0) {
            std::memset(g_aInner, 0, sizeof g_aInner);
            StoreAt(g_aInner, e.nSize, nValue);
            long long aHolder[1] = { (long long)g_aInner };
            assert(((unsigned long long (*)(long long*))e.pfn)(aHolder) == nValue);
            ++nSeen[1];

        } else if (std::strcmp(e.pszKind, "get-base") == 0) {
            std::memset(g_aBase, 0, sizeof g_aBase);
            StoreAt((char*)g_aBase + e.nOffset, e.nSize, nValue);
            assert(((unsigned long long (*)(void))e.pfn)() == nValue);
            ++nSeen[2];

        } else if (std::strcmp(e.pszKind, "compare") == 0) {
            long long aA[1] = { 0x1122 }, aB[1] = { 0x1122 }, aC[1] = { 0x3344 };
            const bool bEq = (e.nExtra == 0);
            assert(((bool (*)(long long*, long long*))e.pfn)(aA, aB) == bEq);
            assert(((bool (*)(long long*, long long*))e.pfn)(aA, aC) == !bEq);
            ++nSeen[3];

        } else if (std::strcmp(e.pszKind, "range") == 0) {
            const int nBase = (int)e.nOffset;
            const int nWidth = (int)e.nExtra;
            bool (*pfn)(int) = (bool (*)(int))e.pfn;
            assert(pfn(nBase - 1) == false);
            assert(pfn(nBase) == true);
            assert(pfn(nBase + nWidth - 1) == true);
            assert(pfn(nBase + nWidth) == false);
            ++nSeen[4];

        } else if (std::strcmp(e.pszKind, "set-deref") == 0) {
            long long aObject[1] = { 0 };
            ((void (*)(long long*, long long))e.pfn)(aObject, 0x55667788AABBCCDDLL);
            assert(aObject[0] == 0x55667788AABBCCDDLL);
            ++nSeen[5];

        } else if (std::strcmp(e.pszKind, "noop") == 0) {
            ((void (*)(void))e.pfn)();
            ++nSeen[6];

        } else if (std::strcmp(e.pszKind, "iter-cmp") == 0) {
            long long aA[2] = { 0x1000, 0x2000 };
            long long aB[2] = { 0x1000, 0x2000 };
            long long aC[2] = { 0x1000, 0x3000 };
            const bool bEq = (e.nExtra == 0);
            g_invalids = 0;
            assert(((bool (*)(long long*, long long*))e.pfn)(aA, aB) == bEq);
            assert(g_invalids == 0);
            assert(((bool (*)(long long*, long long*))e.pfn)(aA, aC) == !bEq);
            long long aBad[2] = { 0, 0x2000 };
            g_invalids = 0;
            ((bool (*)(long long*, long long*))e.pfn)(aBad, aB);   // a null owner is reported
            assert(g_invalids == 1);
            ++nSeen[7];

        } else {
            std::printf("unknown kind: %s\n", e.pszKind);
            assert(false);
        }
        ++nKinds;
    }

    assert(nKinds == g_nNpcSmallBody);
    // every shape present in this batch was exercised; a shape with no body in the batch stays at zero
    int nShapes = 0;
    for (int i = 0; i < 8; ++i) if (nSeen[i] > 0) ++nShapes;
    assert(nShapes >= 6);
    std::printf("NPCSERVER_D252_OK: %d small bodies driven from the manifest\n", g_nNpcSmallBody);
    return 0;
}

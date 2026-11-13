// D252 — every generated small body, driven from its manifest entry.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/small-bodies.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"
#include "modules/npcserver/unattributed/stl-global.h"

using namespace tq;

static unsigned char g_aObject[0x200];
static unsigned char g_aCopyDst[0x400];
static unsigned char g_aCopySrc[0x400];
static size_t g_cbCopied = 0;
static int g_deletes = 0;
static int g_logs = 0;

static void MemmoveS(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc) {
    assert(cbDst == cbSrc);
    g_cbCopied += cbSrc;
    std::memcpy(pDst, pSrc, cbSrc);
}
static void* OperatorDelete(void* p) { ++g_deletes; return p; }
static void InlineLogError(const void*, ...) { ++g_logs; }
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
    g_pfnNpcMemmoveS = &MemmoveS;
    g_pfnNpcOperatorDelete = &OperatorDelete;
    g_pfnNpcInlineLogError = &InlineLogError;
    g_pNpcModuleBase_1401045b8 = g_aBase;

    assert(g_nNpcSmallBody > 100);
    int nSeen[20] = { 0 };
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

        } else if (std::strcmp(e.pszKind, "get-offset-guard") == 0) {
            std::memset(g_aObject, 0, sizeof g_aObject);
            StoreAt(g_aObject + e.nOffset, e.nSize, nValue);
            assert(((unsigned long long (*)(long long))e.pfn)((long long)g_aObject) == nValue);
            assert(((unsigned long long (*)(long long))e.pfn)(0) == 0);
            ++nSeen[10];

        } else if (std::strcmp(e.pszKind, "zero") == 0) {
            assert(((unsigned long long (*)(void))e.pfn)() == 0);
            ++nSeen[11];

        } else if (std::strcmp(e.pszKind, "identity") == 0) {
            assert(((unsigned long long (*)(unsigned long long))e.pfn)(0x1122334455667788ULL) == 0x1122334455667788ULL);
            ++nSeen[12];

        } else if (std::strcmp(e.pszKind, "deref-get") == 0) {
            unsigned long long nSlot = 0x99AABBCCDDEEFF00ULL;
            assert(((unsigned long long (*)(unsigned long long*))e.pfn)(&nSlot) == nSlot);
            ++nSeen[13];

        } else if (std::strcmp(e.pszKind, "ptr-add") == 0) {
            assert(((unsigned long long (*)(unsigned long long))e.pfn)(0x1000) == 0x1000 + (unsigned long long)e.nOffset);
            ++nSeen[14];

        } else if (std::strcmp(e.pszKind, "size-getter") == 0) {
            std::memset(g_aObject, 0, sizeof g_aObject);
            *(long long*)(g_aObject + e.nOffset) = 0x400;
            *(long long*)(g_aObject + e.nExtra) = 0x100;
            assert(((long long (*)(long long))e.pfn)((long long)g_aObject) == ((0x400 - 0x100) >> e.nSize));
            ++nSeen[15];

        } else if (std::strcmp(e.pszKind, "refcount-dtor") == 0) {
            long long aObject[4] = { 0, 0, 0, 0 };
            g_deletes = 0;
            assert(((long long* (*)(long long*, unsigned long long))e.pfn)(aObject, 0) == aObject);
            assert((const void*)aObject[0] == (const void*)e.nOffset);
            assert(g_deletes == 0);
            ((long long* (*)(long long*, unsigned long long))e.pfn)(aObject, 1);
            assert(g_deletes == 1);
            ++nSeen[16];

        } else if (std::strcmp(e.pszKind, "log-clear-iter") == 0) {
            unsigned long long aOut[2] = { 0xAA, 0xBB };
            g_logs = 0;
            assert(((unsigned long long* (*)(long long, unsigned long long*))e.pfn)(0, aOut) == aOut);
            assert(aOut[0] == 0 && aOut[1] == 0);
            assert(g_logs == 1);
            ++nSeen[17];

        } else if (std::strcmp(e.pszKind, "move-a") == 0 || std::strcmp(e.pszKind, "move-c") == 0) {
            const int cbElem = e.nSize;
            const int nElems = 4;
            std::memset(g_aCopySrc, 0x5A, sizeof g_aCopySrc);
            std::memset(g_aCopyDst, 0, sizeof g_aCopyDst);
            g_cbCopied = 0;
            void* pFirst = g_aCopySrc;
            long long nLast = (long long)g_aCopySrc + (long long)nElems * cbElem;
            void* pDst = g_aCopyDst + 64;
            void* pBack = nullptr;
            if (std::strcmp(e.pszKind, "move-a") == 0) {
                pBack = ((void* (*)(void*, long long, long long))e.pfn)(pFirst, nLast, (long long)pDst);
            } else if (e.nExtra != 0) {
                // the body sits behind one or more leading parameters that this shape does not touch
                pBack = ((void* (*)(long long, void*, long long, void*))e.pfn)(0, pFirst, nLast, pDst);
            } else {
                pBack = ((void* (*)(void*, long long, void*))e.pfn)(pFirst, nLast, pDst);
            }
            const size_t cbTotal = (size_t)nElems * cbElem;
            // move-a lands the block so that it ends at the destination pointer and returns its start;
            // move-c starts at the pointer and returns the end of the block
            unsigned char* pStart = (std::strcmp(e.pszKind, "move-a") == 0)
                                        ? (unsigned char*)pDst - cbTotal
                                        : (unsigned char*)pDst;
            assert(g_cbCopied == cbTotal);
            assert(std::memcmp(pStart, g_aCopySrc, cbTotal) == 0);
            unsigned char* pExpected = (std::strcmp(e.pszKind, "move-a") == 0) ? pStart : pStart + cbTotal;
            assert((unsigned char*)pBack == pExpected);
            ++nSeen[18];

        } else if (std::strcmp(e.pszKind, "move-b") == 0) {
            const int cbElem = e.nSize;
            std::memset(g_aObject, 0, sizeof g_aObject);
            std::memset(g_aCopySrc, 0x33, sizeof g_aCopySrc);
            std::memset(g_aCopyDst, 0, sizeof g_aCopyDst);
            *(void**)(g_aObject + e.nOffset) = g_aCopySrc;        // the last pointer
            *(void**)(g_aObject + e.nExtra) = g_aCopySrc;         // and it is also the source
            g_cbCopied = 0;
            void* pDst = g_aCopyDst + 32;
            void* pBack = ((void* (*)(long long, long long, void*))e.pfn)((long long)g_aObject,
                                                                         (long long)g_aObject, pDst);
            assert(g_cbCopied == 0);                               // an empty range copies nothing
            assert(pBack == pDst);
            ++nSeen[19];

        } else if (std::strcmp(e.pszKind, "iter-assign") == 0) {
            typedef unsigned long long* (*AssignFn)(unsigned long long*, unsigned long long, unsigned long long*);
            AssignFn pfnA = (AssignFn)e.pfn;
            unsigned long long aOut[2] = { 0xDEAD, 0xBEEF };
            unsigned long long aSrc[2] = { 0xABCD, 0x1234 };
            g_invalids = 0;
            assert(pfnA(aOut, 0x77, aSrc) == aOut);
            assert(aOut[0] == 0xABCD && aOut[1] == 0x77);
            assert(g_invalids == 0);
            ++nSeen[8];
        } else if (std::strcmp(e.pszKind, "vtable-set") == 0) {
            typedef void (*VtableFn)(long long);
            VtableFn pfnV = (VtableFn)e.pfn;
            long long aObject[2] = { 0, 0 };
            pfnV((long long)aObject);
            assert((const void*)aObject[0] == (const void*)e.nOffset);
            ++nSeen[9];
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
    for (int i = 0; i < 20; ++i) if (nSeen[i] > 0) ++nShapes;
    assert(nShapes >= 6);
    std::printf("NPCSERVER_D252_OK: %d small bodies driven from the manifest\n", g_nNpcSmallBody);
    return 0;
}

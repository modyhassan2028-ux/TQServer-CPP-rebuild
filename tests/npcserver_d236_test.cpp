// D236 — the container/interface bodies around NpcManager: vtable stores, the deleting destructor,
// the vtable release, the iterator comparisons and one member address.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/container-bodies.h"

using namespace tq;

static int g_invalid = 0, g_deletes = 0, g_releases = 0;
static void* g_pDeleted = nullptr;
static void* g_pReleased = nullptr;

static void Invalid(void) { ++g_invalid; }
static void* FakeDelete(void* p) { ++g_deletes; g_pDeleted = p; return p; }
static void FakeSlot(void* pSelf, int nFlag) { ++g_releases; g_pReleased = pSelf; }

int main() {
    g_pfnNpcInvalidParameter = &Invalid;
    g_pfnNpcOperatorDelete = &FakeDelete;

    assert(g_nNpcContainer >= 17);
    int nSet = 0, nDtor = 0, nRel = 0, nCmp = 0, nAddr = 0;
    const void* aVtables[8];
    int nVtables = 0;

    for (int i = 0; i < g_nNpcContainer; ++i) {
        const NpcContainerEntry& e = g_aNpcContainer[i];
        assert(e.pszAddress && e.pszKind && e.pfn);

        if (std::strcmp(e.pszKind, "vtable-set") == 0) {
            unsigned long long aObject[4] = { 0, 0x11, 0x22, 0x33 };
            void (*pfn)(void*) = (void (*)(void*))e.pfn;
            pfn(aObject);
            assert(aObject[0] != 0);                       // the table went in
            assert(aObject[1] == 0x11 && aObject[3] == 0x33);  // and nothing else was touched
            if (nVtables < 8) aVtables[nVtables++] = (const void*)aObject[0];
            ++nSet;

        } else if (std::strcmp(e.pszKind, "vtable-dtor") == 0) {
            unsigned long long aObject[4] = { 0, 0x44, 0, 0 };
            g_deletes = 0; g_pDeleted = nullptr;
            void* pRet = ((void* (*)(void*, unsigned char))e.pfn)(aObject, 0);
            assert(pRet == aObject && g_deletes == 0);      // flag 0 keeps the object alive
            assert(aObject[0] != 0);
            pRet = ((void* (*)(void*, unsigned char))e.pfn)(aObject, 1);
            assert(pRet == aObject && g_deletes == 1);      // flag 1 frees it and still answers the pointer
            assert(g_pDeleted == aObject);
            ++nDtor;

        } else if (std::strcmp(e.pszKind, "vtable-release") == 0) {
            g_releases = 0; g_pReleased = nullptr;
            long long nRet = ((long long (*)(void*))e.pfn)(nullptr);
            assert(nRet == 0 && g_releases == 0);           // a null object is not released
            void* aVtbl[1] = { (void*)&FakeSlot };
            void* aObject[2] = { aVtbl, nullptr };
            nRet = ((long long (*)(void*))e.pfn)(aObject);
            assert(nRet == 0);
            assert(g_releases == 1);
            assert(g_pReleased == aObject);                 // slot 0 is called with the object and the flag 1
            ++nRel;

        } else if (std::strcmp(e.pszKind, "iter-compare") == 0) {
            long long aLeft[2] = { (long long)0x9000, 40 };
            long long aRight[2] = { (long long)0x9000, 40 };
            g_invalid = 0;
            long long nRet = ((long long (*)(long long*, long long*))e.pfn)(aLeft, aRight);
            assert(g_invalid == 0);
            aLeft[1] = 41;
            ((long long (*)(long long*, long long*))e.pfn)(aLeft, aRight);
            assert(g_invalid == 0);                         // same owner: no complaint, whatever the answer
            (void)nRet;
            long long aOther[2] = { (long long)0xA000, 40 };
            g_invalid = 0;
            ((long long (*)(long long*, long long*))e.pfn)(aLeft, aOther);
            assert(g_invalid == 1);                         // a different owner is reported
            g_invalid = 0;
            aLeft[0] = 0;
            ((long long (*)(long long*, long long*))e.pfn)(aLeft, aRight);
            assert(g_invalid == 1);                         // and so is a null owner
            ++nCmp;

        } else if (std::strcmp(e.pszKind, "member-address") == 0) {
            unsigned char aObject[0x40];
            long long nRet = ((long long (*)(void*))e.pfn)(aObject);
            assert(nRet == (long long)(aObject + e.nValue));
            ++nAddr;
        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nSet == 3 && nDtor == 3 && nRel == 1 && nCmp == 9 && nAddr == 1);
    // the three interface tables are distinct objects in the image
    assert(nVtables == 3 && aVtables[0] != aVtables[1] && aVtables[1] != aVtables[2] && aVtables[0] != aVtables[2]);

    std::printf("NPCSERVER_D236_OK: %d container bodies\n", nSet + nDtor + nRel + nCmp + nAddr);
    return 0;
}

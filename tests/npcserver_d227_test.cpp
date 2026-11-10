// D227 — the container-internal families of 0x140080000..0x140090000. The suite walks the whole generated manifest,
// so every ported body is exercised, not just one representative of each shape.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/stl-internals.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_invalid = 0, g_dtor = 0, g_dealloc = 0;
static void InvalidParam(void) { ++g_invalid; }
static void RefDtor(void* p) { (void)p; ++g_dtor; }
static void RefDealloc(void* p) { (void)p; ++g_dealloc; }

static void* g_refVt[2] = { (void*)&RefDtor, (void*)&RefDealloc };

int main() {
    g_pfnNpcInvalidParameter = &InvalidParam;

    int nSeen[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    assert(g_nNpcStl_140080000 == 86);

    for (int i = 0; i < g_nNpcStl_140080000; ++i) {
        const NpcStlEntry& e = g_aNpcStl_140080000[i];
        assert(e.pszAddress != nullptr && e.pszFamily != nullptr && e.pfn != nullptr);

        if (std::strcmp(e.pszFamily, "delete-thunk") == 0) {
            // the body deletes whatever the slot holds and leaves the slot alone
            void* pBlock = ::operator new(16);
            void* aSlot[2] = { pBlock, (void*)0x1234 };
            ((void (*)(void**))e.pfn)(aSlot);
            assert(aSlot[1] == (void*)0x1234);
            ++nSeen[0];
        } else if (std::strcmp(e.pszFamily, "new-and-store") == 0) {
            // the body allocates the object, points it back at the slot, and installs it in the slot
            void* aSlot[2] = { (void*)0, (void*)0x55 };
            void** pRet = ((void** (*)(void**))e.pfn)(aSlot);
            assert(pRet == aSlot);
            assert(aSlot[0] != nullptr);
            assert(*(void**)aSlot[0] == (void*)aSlot);       // the new object points back at the slot
            assert(aSlot[1] == (void*)0x55);
            ::operator delete(aSlot[0]);
            ++nSeen[1];
        } else if (std::strcmp(e.pszFamily, "decref") == 0) {
            const int nOwn = e.nArg1, nUses = e.nArg2, nWeak = e.nArg3;
            unsigned char aOwner[0x80];
            unsigned char aRef[0x40];

            // two readers: the count only drops, and nothing is destroyed
            std::memset(aOwner, 0, sizeof aOwner); std::memset(aRef, 0, sizeof aRef);
            *(void**)aRef = (void*)g_refVt;
            *(int*)(aRef + nUses) = 2; *(int*)(aRef + nWeak) = 1;
            *(void**)(aOwner + nOwn) = aRef;
            g_dtor = g_dealloc = 0;
            ((void (*)(unsigned char*))e.pfn)(aOwner);
            assert(*(int*)(aRef + nUses) == 1 && g_dtor == 0 && g_dealloc == 0);

            // the last reader destroys, and with no weak references left it also deallocates
            g_dtor = g_dealloc = 0;
            ((void (*)(unsigned char*))e.pfn)(aOwner);
            assert(*(int*)(aRef + nUses) == 0 && g_dtor == 1);
            assert(*(int*)(aRef + nWeak) == 0 && g_dealloc == 1);

            // a slot with no reference object is left alone
            std::memset(aOwner, 0, sizeof aOwner);
            g_dtor = g_dealloc = 0;
            ((void (*)(unsigned char*))e.pfn)(aOwner);
            assert(g_dtor == 0 && g_dealloc == 0);
            ++nSeen[2];
        } else if (std::strcmp(e.pszFamily, "iterator-check") == 0) {
            const int nOffset = e.nArg1, bLessEq = e.nArg2, nDelta = e.nArg3;
            long long aContainer[16];
            long long aHolder[1];
            long long aIt[2];

            std::memset(aContainer, 0, sizeof aContainer);
            aHolder[0] = (long long)aContainer;
            aIt[0] = (long long)aHolder;
            aIt[1] = 0x2000;

            g_invalid = 0;
            *(long long*)((unsigned char*)aContainer + nOffset) = 0x3000;   // past the iterator
            long long nAnswer = ((long long (*)(long long*))e.pfn)(aIt);
            assert(nAnswer == 0x2000 + nDelta);
            assert(g_invalid == 0);

            // and the boundary the body rejects
            g_invalid = 0;
            *(long long*)((unsigned char*)aContainer + nOffset) = bLessEq ? 0x2000 : 0x2000;
            nAnswer = ((long long (*)(long long*))e.pfn)(aIt);
            assert(nAnswer == 0x2000 + nDelta);              // the answer comes back either way
            assert(g_invalid == 1);
            ++nSeen[3];
        } else if (std::strcmp(e.pszFamily, "iterator-compare") == 0) {
            const int bEqual = e.nArg1;
            long long aFirst[2] = { (long long)0x9000, 10 };
            long long aSecond[2] = { (long long)0x9000, 10 };
            g_invalid = 0;
            bool bSame = ((bool (*)(long long*, long long*))e.pfn)(aFirst, aSecond);
            assert(g_invalid == 0);
            assert(bSame == (bEqual ? true : false));

            aSecond[1] = 11;
            bool bDiff = ((bool (*)(long long*, long long*))e.pfn)(aFirst, aSecond);
            assert(bDiff == (bEqual ? false : true));

            // a different container pointer is the debug failure
            g_invalid = 0;
            aSecond[0] = (long long)0x9001;
            ((bool (*)(long long*, long long*))e.pfn)(aFirst, aSecond);
            assert(g_invalid == 1);
            ++nSeen[4];
        } else {
            assert(!"unknown family in the manifest");
        }
    }

    assert(nSeen[0] == 23 && nSeen[1] == 21 && nSeen[2] == 17 && nSeen[3] == 15 && nSeen[4] == 10);
    std::printf("NPCSERVER_D227_OK: 86 container-internal bodies\n");
    return 0;
}

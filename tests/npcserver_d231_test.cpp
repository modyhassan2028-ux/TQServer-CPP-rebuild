// D231 — the shared-owner pair, the release wrapper and the length-error throwers of 0x140080000..0x140090000.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "modules/npcserver/unattributed/stl-refs.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

typedef void (*DestroyFn)(void*);
typedef void (*DeleteFn)(void*);

struct ControlProbe {
    DestroyFn pfnDestroy;
    DeleteFn  pfnDelete;
    int       nStrong;
    int       nWeak;
    int       nDestroyed;
    int       nFreed;
};

static int g_destroyed = 0, g_freed = 0, g_deleted = 0;
static void* g_pDeleted = nullptr;

static void DestroyHook(void* p) { ++g_destroyed; ((ControlProbe*)p)->nDestroyed = 1; }
static void DeleteHook(void* p) { ++g_freed; ((ControlProbe*)p)->nFreed = 1; }
static void* FakeDelete(void* p) { ++g_deleted; g_pDeleted = p; return p; }

static void MakeControl(ControlProbe& c, int strong, int weak) {
    c.pfnDestroy = &DestroyHook;
    c.pfnDelete = &DeleteHook;
    c.nStrong = strong;
    c.nWeak = weak;
    c.nDestroyed = c.nFreed = 0;
}

int main() {
    g_pfnNpcOperatorDelete = &FakeDelete;

    assert(g_nNpcRef_140080000 == 16);
    int nAssign = 0, nCopy = 0, nRelease = 0, nLong = 0;

    for (int i = 0; i < g_nNpcRef_140080000; ++i) {
        const NpcRefEntry& e = g_aNpcRef_140080000[i];
        assert(e.pszAddress && e.pszFamily && e.pfn);

        if (std::strcmp(e.pszFamily, "ref-assign") == 0) {
            // keeping a reference bumps the strong count before anything is released
            ControlProbe cNew; MakeControl(cNew, 1, 1);
            unsigned long long aPair[2] = { 0, 0 };
            g_destroyed = g_freed = 0;
            ((void (*)(unsigned long long*, unsigned long long, void*))e.pfn)(aPair, 0x42, &cNew);
            assert(aPair[0] == 0x42);
            assert(aPair[1] == (unsigned long long)(void*)&cNew);
            assert(cNew.nStrong == 2 && g_destroyed == 0);          // took its own reference, freed nothing

            // storing over a held block releases that block: strong to zero destroys, weak to zero frees
            ControlProbe cOld; MakeControl(cOld, 1, 1);
            aPair[0] = 0x99;
            aPair[1] = (unsigned long long)(void*)&cOld;
            ((void (*)(unsigned long long*, unsigned long long, void*))e.pfn)(aPair, 0x7, &cNew);
            assert(aPair[0] == 0x7 && aPair[1] == (unsigned long long)(void*)&cNew);
            assert(cOld.nStrong == 0 && cOld.nDestroyed == 1 && cOld.nFreed == 1);
            assert(cNew.nStrong == 3);                              // the new block gained one more reference
            ++nAssign;

        } else if (std::strcmp(e.pszFamily, "ref-copy") == 0) {
            ControlProbe c; MakeControl(c, 1, 1);
            unsigned long long aFrom[2] = { 0x11, (unsigned long long)(void*)&c };
            unsigned long long aTo[2] = { 0xEE, 0xEE };
            g_destroyed = g_freed = 0;
            unsigned long long* pRet =
                ((unsigned long long* (*)(unsigned long long*, unsigned long long*))e.pfn)(aTo, aFrom);
            assert(pRet == aTo);
            assert(aTo[0] == 0x11 && aTo[1] == aFrom[1]);
            assert(c.nStrong == 2 && g_destroyed == 0);             // forwards into ref-assign, one reference
            ++nCopy;

        } else if (std::strcmp(e.pszFamily, "ref-release") == 0) {
            ControlProbe c; MakeControl(c, 1, 1);
            unsigned long long aHolder[2] = { 0x5, (unsigned long long)(void*)&c };
            g_destroyed = g_freed = g_deleted = 0; g_pDeleted = nullptr;
            void* pRet = ((void* (*)(void*, unsigned int))e.pfn)(aHolder, 0);
            assert(pRet == aHolder);
            assert(c.nStrong == 0 && c.nDestroyed == 1 && c.nFreed == 1);
            assert(g_deleted == 0);                                 // no flag: the object itself survives

            g_deleted = 0; g_pDeleted = nullptr;
            ((void* (*)(void*, unsigned int))e.pfn)(aHolder, 1);
            assert(g_deleted == 1 && g_pDeleted == aHolder);         // the low bit frees the object
            ++nRelease;

        } else if (std::strcmp(e.pszFamily, "too-long") == 0) {
            bool caught = false;
            try {
                ((void (*)(void))e.pfn)();
            } catch (const std::length_error& ex) {
                caught = true;
                assert(e.pszText[0] != 0);
                assert(std::strcmp(ex.what(), e.pszText) == 0);
            }
            assert(caught);
            ++nLong;

        } else {
            assert(!"unknown family in the manifest");
        }
    }

    assert(nAssign == 4 && nCopy == 4 && nRelease == 1 && nLong == 7);
    std::printf("NPCSERVER_D231_OK: 16 shared-owner and length-error bodies\n");
    return 0;
}

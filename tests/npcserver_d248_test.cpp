// D248 — the kernel singleton getters and the counted release.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/module-singletons.h"

using namespace tq;

static long long g_aBase[16];
static long long g_aObject[4];
static long long g_aVt[4];
static int g_releases = 0, g_destroys = 0;

static void Release(long long* p) { ++g_releases; assert(p == g_aObject); }
static void Destroy(long long* p) { ++g_destroys; assert(p == g_aObject); }

static void Reset() {
    g_releases = g_destroys = 0;
    std::memset(g_aObject, 0, sizeof g_aObject);
    std::memset(g_aVt, 0, sizeof g_aVt);
    g_aVt[0] = (long long)&Release;
    g_aVt[1] = (long long)&Destroy;
    g_aObject[0] = (long long)g_aVt;
}

int main() {
    std::memset(g_aBase, 0, sizeof g_aBase);
    *(long long*)((char*)g_aBase + 0x28) = 0x2828;
    *(long long*)((char*)g_aBase + 0x30) = 0x3030;
    *(long long*)((char*)g_aBase + 0x40) = 0x4040;
    g_pNpcModuleBase_1401045b8 = g_aBase;

    assert(g_nNpcModuleSingleton == 5);
    int nGet28 = 0, nGet30 = 0, nGet40 = 0, nRelease = 0, nBase = 0;

    for (int i = 0; i < g_nNpcModuleSingleton; ++i) {
        const NpcModuleSingletonEntry& e = g_aNpcModuleSingleton[i];

        if (std::strcmp(e.pszKind, "module-base") == 0) {
            assert(((long long (*)(void))e.pfn)() == (long long)g_aBase);
            ++nBase;
        } else if (std::strcmp(e.pszKind, "get-0x28") == 0) {
            assert(((long long (*)(void))e.pfn)() == 0x2828);
            ++nGet28;
        } else if (std::strcmp(e.pszKind, "get-0x30") == 0) {
            assert(((long long (*)(void))e.pfn)() == 0x3030);
            ++nGet30;
        } else if (std::strcmp(e.pszKind, "get-0x40") == 0) {
            assert(((long long (*)(void))e.pfn)() == 0x4040);
            ++nGet40;
        } else if (std::strcmp(e.pszKind, "release") == 0) {
            typedef void (*ReleaseFn)(long long);
            ReleaseFn pfn = (ReleaseFn)e.pfn;

            // no object at all: nothing happens
            Reset();
            long long aOwner[2] = { 0, 0 };
            pfn((long long)aOwner);
            assert(g_releases == 0 && g_destroys == 0);

            // one reference left after the drop: the object lives on
            Reset();
            ((int*)g_aObject)[4] = 1;          // +0x10
            ((int*)g_aObject)[5] = 1;          // +0x14
            aOwner[1] = (long long)g_aObject;
            ((int*)g_aObject)[4] = 2;
            pfn((long long)aOwner);
            assert(((int*)g_aObject)[4] == 1);
            assert(g_releases == 0 && g_destroys == 0);

            // the count reaches zero: the object is released, and the second count decides the destroy
            Reset();
            ((int*)g_aObject)[4] = 1;
            ((int*)g_aObject)[5] = 2;
            pfn((long long)aOwner);
            assert(((int*)g_aObject)[4] == 0);
            assert(g_releases == 1);
            assert(((int*)g_aObject)[5] == 1);   // the object's own count was not at zero
            assert(g_destroys == 0);

            // both counts at zero: released, then destroyed
            Reset();
            ((int*)g_aObject)[4] = 1;
            ((int*)g_aObject)[5] = 1;
            pfn((long long)aOwner);
            assert(g_releases == 1);
            assert(((int*)g_aObject)[5] == 0);
            assert(g_destroys == 1);
            ++nRelease;
        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nGet28 == 1 && nGet30 == 1 && nGet40 == 1 && nRelease == 1 && nBase == 1);
    std::printf("NPCSERVER_D248_OK: singleton getters and the counted release\n");
    return 0;
}

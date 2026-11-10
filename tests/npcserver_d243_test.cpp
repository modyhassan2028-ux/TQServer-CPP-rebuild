// D243 — CInstance: the type getter, the deleting destructor, the map release and the constructor.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/cinstance.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_news = 0, g_logs = 0;
static void* g_pNew = nullptr;
static long long g_singleton = 0x5151;
static long long g_nCcId = 0, g_nCcSingleton = 0;
static int g_releases = 0;
static long long g_pReleased = 0;
static int g_creates = 0;
static unsigned char g_createOk = 1;
static long long g_pDeleted = 0;
static long long g_nDeleteFlag = 0;
static unsigned char g_aObject[0x20];

static void* FakeNew(long long nBytes) { ++g_news; assert(nBytes == 0x18); return g_aObject; }
static void Log(const void* pMsg, ...) { ++g_logs; assert((long long)pMsg == 0x1400be0b0); }
static long long Singleton(void) { return g_singleton; }
static unsigned long long ReleaseMap(long long pSingleton, unsigned nId) {
    ++g_releases; g_nCcSingleton = pSingleton; g_nCcId = nId; return 1;
}
static unsigned long long BringUp(long long pInstance) { ++g_creates; assert(pInstance == (long long)g_aObject); return g_createOk; }
static void DeletingDtor(long long* pObj, long long nFlag) { g_pDeleted = (long long)pObj; g_nDeleteFlag = nFlag; }

static void Reset() {
    g_news = g_logs = g_releases = g_creates = 0;
    g_nCcId = g_nCcSingleton = 0;
    g_pDeleted = 0; g_nDeleteFlag = 0;
    g_createOk = 1;
    g_pNew = g_aObject;
    std::memset(g_aObject, 0xCC, sizeof g_aObject);
}

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcInlineLogError = &Log;
    g_pfnNpc_14001c790 = &Singleton;
    g_pfnNpc_14003cc10 = &ReleaseMap;
    g_pfnNpc_140048fb0 = &BringUp;

    assert(g_nNpcCInstance == 4);
    int nRelease = 0, nGetter = 0, nHolder = 0, nCreate = 0;

    for (int i = 0; i < g_nNpcCInstance; ++i) {
        const NpcCInstanceEntry& e = g_aNpcCInstance[i];

        if (std::strcmp(e.pszKind, "type-getter") == 0) {
            unsigned long long aObject[3];
            std::memset(aObject, 0, sizeof aObject);
            *(unsigned*)((char*)aObject + 8) = 0xC0DE;
            assert(((unsigned (*)(long long))e.pfn)((long long)aObject) == 0xC0DE);
            ++nGetter;

        } else if (std::strcmp(e.pszKind, "delete-holder") == 0) {
            Reset();
            ((void (*)(long long*))e.pfn)(0);
            assert(g_pDeleted == 0);                         // a null holder is left alone
            long long aObject[3];
            aObject[0] = (long long)&DeletingDtor;
            ((void (*)(long long*))e.pfn)(aObject);
            assert(g_pDeleted == (long long)aObject);        // slot 0 with the delete flag
            assert(g_nDeleteFlag == 1);
            ++nHolder;

        } else if (std::strcmp(e.pszKind, "release-map") == 0) {
            Reset();
            long long aObject[3];
            std::memset(aObject, 0, sizeof aObject);
            *(unsigned*)((char*)aObject + 0xc) = 0x77;
            ((void (*)(long long))e.pfn)((long long)aObject);
            assert(g_releases == 1);
            assert(g_nCcSingleton == g_singleton);           // the singleton came from 0x14001c790
            assert(g_nCcId == 0x77);                         // and the id from +0xc
            ++nRelease;

        } else if (std::strcmp(e.pszKind, "create") == 0) {
            typedef long long* (*CreateFn)(unsigned, long long, unsigned);

            // no map: one log line and nothing allocated
            Reset();
            assert(((CreateFn)e.pfn)(3, 0, 9) == 0);
            assert(g_news == 0 && g_logs == 1);

            // the map brings the instance up
            Reset();
            long long* pInstance = ((CreateFn)e.pfn)(3, 0xAB, 9);
            assert(pInstance == (long long*)g_aObject);
            assert(g_news == 1 && g_creates == 1 && g_logs == 0);
            assert(((long long*)g_aObject)[0] == (long long)0x1400c7340);   // CInstance::vftable
            assert(*(unsigned*)(g_aObject + 8) == 3);                       // the type
            assert(*(long long*)(g_aObject + 0x10) == 0xAB);                // the map
            assert(*(unsigned*)(g_aObject + 0xc) == 9);                     // the low dword

            // the object was built, but its map refused to come up
            Reset();
            g_createOk = 0;
            assert(((CreateFn)e.pfn)(3, 0xAB, 9) == 0);
            assert(g_news == 1 && g_creates == 1 && g_logs == 0);           // no second log on this path

            // the allocation itself failed
            Reset();
            g_pfnNpcOperatorNew = nullptr;
            g_pfnNpcOperatorNew = [](long long) -> void* { return nullptr; };
            assert(((CreateFn)e.pfn)(3, 0xAB, 9) == 0);
            assert(g_logs == 1 && g_creates == 0);
            g_pfnNpcOperatorNew = &FakeNew;
            ++nCreate;

        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nRelease == 1 && nGetter == 1 && nHolder == 1 && nCreate == 1);
    std::printf("NPCSERVER_D243_OK: CInstance getter, holder, release and constructor\n");
    return 0;
}

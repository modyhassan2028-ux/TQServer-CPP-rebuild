// D243/D244 — CInstance: getter, deleting destructor, map release, constructor, and the map bring-up.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/cinstance.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_news = 0, g_logs = 0;
static void* g_pNew = nullptr;
static const void* g_pLastMsg = nullptr;
static long long g_singleton = 0x5151;
static long long g_nCcSingleton = 0;
static unsigned g_nCcId = 0;
static int g_releases = 0;
static int g_mapCalls = 0;
static long long g_aMapArgs[8];
static int g_mapError = 0;
static long long g_pDeleted = 0;
static long long g_nDeleteFlag = 0;
static unsigned char g_aObject[0x20];
static long long g_aMapObj[4];
static long long g_aMapVt[4];
static int g_mapSlotArg = 0;

static void* FakeNew(long long nBytes) { ++g_news; assert(nBytes == 0x18); return g_aObject; }
static void* NoNew(long long) { return nullptr; }
static void Log(const void* pMsg, ...) { ++g_logs; g_pLastMsg = pMsg; }
static long long Singleton(void) { return g_singleton; }
static unsigned long long ReleaseMap(long long pSingleton, unsigned nId) {
    ++g_releases; g_nCcSingleton = pSingleton; g_nCcId = nId; return 1;
}
static unsigned long long CreateMap(long long pSingleton, unsigned nMapId, unsigned nLow) {
    if (g_mapCalls < 8) {
        g_aMapArgs[g_mapCalls * 3 + 0] = pSingleton;
        g_aMapArgs[g_mapCalls * 3 + 1] = (long long)nMapId;
        g_aMapArgs[g_mapCalls * 3 + 2] = (long long)nLow;
    }
    ++g_mapCalls;
    return g_mapError ? 0 : 1;
}
static unsigned MapId(void* pMap, long long nWhat) { g_mapSlotArg = (int)nWhat; assert(pMap == (void*)g_aMapObj); return 0x42; }
static void DeletingDtor(long long* pObj, long long nFlag) { g_pDeleted = (long long)pObj; g_nDeleteFlag = nFlag; }

static void Reset() {
    g_news = g_logs = g_releases = g_mapCalls = 0;
    g_nCcId = 0; g_nCcSingleton = 0;
    g_pDeleted = 0; g_nDeleteFlag = 0;
    g_pLastMsg = nullptr;
    g_mapError = 0;
    g_mapSlotArg = 0;
    std::memset(g_aObject, 0xCC, sizeof g_aObject);
    std::memset(g_aMapObj, 0, sizeof g_aMapObj);
    std::memset(g_aMapVt, 0, sizeof g_aMapVt);
    g_aMapObj[0] = (long long)g_aMapVt;
    g_aMapVt[2] = (long long)&MapId;                 // the map's slot at +0x10
}

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcInlineLogError = &Log;
    g_pfnNpc_14001c790 = &Singleton;
    g_pfnNpc_14003cc10 = &ReleaseMap;
    g_pfnNpc_14003cd80 = &CreateMap;

    assert(g_nNpcCInstance == 5);
    int nRelease = 0, nGetter = 0, nHolder = 0, nCreate = 0, nBring = 0;

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
            assert(g_pDeleted == (long long)aObject);
            assert(g_nDeleteFlag == 1);                      // slot 0 with the delete flag
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

            // no map: one log line, nothing allocated
            Reset();
            assert(((CreateFn)e.pfn)(3, 0, 9) == 0);
            assert(g_news == 0 && g_logs == 1);
            assert(g_pLastMsg == (const void*)0x1400be0b0);

            // the map comes up through 0x140048fb0
            Reset();
            long long* pInstance = ((CreateFn)e.pfn)(3, (long long)g_aMapObj, 9);
            assert(pInstance == (long long*)g_aObject);
            assert(g_news == 1 && g_logs == 0);
            assert(((long long*)g_aObject)[0] == (long long)0x1400c7340);   // CInstance::vftable
            assert(*(unsigned*)(g_aObject + 8) == 3);                       // the type
            assert(*(long long*)(g_aObject + 0x10) == (long long)g_aMapObj);
            assert(*(unsigned*)(g_aObject + 0xc) == 9);
            assert(g_mapCalls == 1 && g_mapSlotArg == 2);                   // slot 0x10 asked with 2
            assert(g_aMapArgs[0] == g_singleton);                           // singleton from 0x14001c790
            assert(g_aMapArgs[1] == 0x42);                                  // the map id
            assert(g_aMapArgs[2] == 9);                                     // the low dword

            // the map refused to come up: the error line, and a null answer
            Reset();
            g_mapError = 1;
            assert(((CreateFn)e.pfn)(3, (long long)g_aMapObj, 9) == 0);
            assert(g_news == 1 && g_mapCalls == 1 && g_logs == 1);
            assert(std::strcmp((const char*)g_pLastMsg,
                               "CInstance::Create NPCServer Map Create Error, map:%u") == 0);

            // the allocation itself failed
            Reset();
            g_pfnNpcOperatorNew = &NoNew;
            assert(((CreateFn)e.pfn)(3, (long long)g_aMapObj, 9) == 0);
            assert(g_logs == 1 && g_mapCalls == 0);
            g_pfnNpcOperatorNew = &FakeNew;
            ++nCreate;

        } else if (std::strcmp(e.pszKind, "bring-up") == 0) {
            typedef unsigned long long (*BringFn)(long long);

            // no map on the instance
            Reset();
            long long aInstance[3];
            std::memset(aInstance, 0, sizeof aInstance);
            assert(((BringFn)e.pfn)((long long)aInstance) == 0);
            assert(g_logs == 1 && g_pLastMsg == (const void*)0x1400be0b0 && g_mapCalls == 0);

            // the map id goes to the singleton along with the instance's low dword
            Reset();
            long long aLive[3];
            aLive[0] = (long long)0x1400c7340;
            *(long long*)((char*)aLive + 0x10) = (long long)g_aMapObj;
            *(unsigned*)((char*)aLive + 0xc) = 0x31;
            assert(((BringFn)e.pfn)((long long)aLive) == 1);
            assert(g_logs == 0 && g_mapCalls == 1 && g_mapSlotArg == 2);
            assert(g_aMapArgs[0] == g_singleton && g_aMapArgs[1] == 0x42 && g_aMapArgs[2] == 0x31);

            // the singleton refused the map
            Reset();
            g_mapError = 1;
            assert(((BringFn)e.pfn)((long long)aLive) == 0);
            assert(g_logs == 1);
            assert(std::strcmp((const char*)g_pLastMsg,
                               "CInstance::Create NPCServer Map Create Error, map:%u") == 0);
            ++nBring;

        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nRelease == 1 && nGetter == 1 && nHolder == 1 && nCreate == 1 && nBring == 1);
    std::printf("NPCSERVER_D243_OK: CInstance getter, holder, release, constructor and bring-up\n");
    return 0;
}

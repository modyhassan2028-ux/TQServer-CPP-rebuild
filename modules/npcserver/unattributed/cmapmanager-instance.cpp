// Transcribed from NpcServer.exe; see cmapmanager-instance.h.
#include "modules/npcserver/unattributed/cmapmanager-instance.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"
#include <cstdio>

namespace tq {

// The seams this file owns until their own batches land.
void* (*g_pfnNpc_1400550f0)(void* pStorage) = nullptr;
long long* (*g_pfnNpcInstanceGet)(long long pModule) = nullptr;
unsigned long long (*g_pfnNpc_140032e20)(long long pSingleton, unsigned nMapId, unsigned nLow) = nullptr;

// 0x14003ca10 - CMapManager::FindMap: the cache first, then one row from cq_dynamap
//
// The image formats the statement into a 1024-byte stack buffer and asks the database instance for it with mode 2; the
// cache is the collection at pManager+8, whose slot 0x10 is the count and slot 0x18 the indexed getter (the call site
// passes mapmanager.cpp and line 0x72).
long long* FUN_14003ca10(long long pManager, int nMapId) {
    char cVar1;
    int iVar2;
    long long lVar3;
    long long* plVar4;
    long long uVar5;
    long long* plVar6;
    long long* plVar7;
    long long* plVar8;
    long long aCollection;
    char local_428[1024];

    if (nMapId == 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
        plVar6 = 0;
    } else {
        plVar6 = 0;
        long long* pCache = *(long long**)(pManager + 8);
        long long* pCacheVt = (long long*)*pCache;
        lVar3 = ((long long (*)(long long*))pCacheVt[0x10 / 8])(pCache);
        plVar7 = plVar6;
        if (lVar3 != 0) {
            do {
                pCache = *(long long**)(pManager + 8);
                pCacheVt = (long long*)*pCache;
                plVar4 = (long long*)((long long (*)(long long*, long long*, const char*, long long))pCacheVt[0x18 / 8])(
                    pCache, plVar7,
                    "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\mapmanager.cpp", 0x72);
                if (plVar4 != 0) {
                    long long* pObjVt = (long long*)*plVar4;
                    iVar2 = ((int (*)(long long*))pObjVt[0x8 / 8])(plVar4);   // the cached object's id
                    if (iVar2 == nMapId) {
                        return plVar4;
                    }
                }
                plVar7 = (long long*)((long long)plVar7 + 1);
                pCache = *(long long**)(pManager + 8);
                pCacheVt = (long long*)*pCache;
                plVar4 = (long long*)((long long (*)(long long*))pCacheVt[0x10 / 8])(pCache);
            } while (plVar7 < plVar4);
        }
        std::snprintf(local_428, sizeof local_428,
                      "SELECT * FROM cq_dynamap WHERE id=%u && del_flag=0 LIMIT 1", (unsigned)nMapId);
        uVar5 = FUN_14001c200();
        plVar8 = g_pfnNpcInstanceGet(uVar5);
        long long* pDbVt = (long long*)*plVar8;
        plVar7 = (long long*)((long long (*)(long long*, char*, long long))pDbVt[0x10 / 8])(plVar8, local_428, 2);
        long long* pRecordVt = nullptr;
        if (plVar7 == 0) {
            plVar6 = 0;
        } else {
            pRecordVt = (long long*)*plVar7;
            lVar3 = ((long long (*)(long long*))pRecordVt[0x40 / 8])(plVar7);   // did the row come back?
        }
        if ((plVar7 == 0) || (lVar3 == 0)) {
            if (plVar7 != 0) {
                ((void (*)(long long*))pRecordVt[0])(plVar7);
            }
            plVar6 = 0;
        } else {
            void* pStorage = g_pfnNpcOperatorNew(0x90);
            if (pStorage != 0) {
                plVar6 = (long long*)g_pfnNpc_1400550f0(pStorage);
            }
            if (plVar6 == 0) {
                ((void (*)(long long*))pRecordVt[0])(plVar7);
                plVar6 = 0;
            } else {
                long long* pInstanceVt = (long long*)*plVar6;
                cVar1 = ((char (*)(long long*, long long*, long long))pInstanceVt[0x20 / 8])(plVar6, plVar7, 1);
                if (cVar1 == '\0') {
                    if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
                    ((void (*)(long long*))pInstanceVt[0x38 / 8])(plVar6);
                    ((void (*)(long long*))pRecordVt[0])(plVar7);
                    plVar6 = 0;
                } else {
                    long long* pCache2 = *(long long**)(pManager + 8);
                    long long* pCacheVt2 = (long long*)*pCache2;
                    ((void (*)(long long*, long long*))pCacheVt2[0x20 / 8])(pCache2, plVar6);
                    ((void (*)(long long*))pRecordVt[0])(plVar7);
                }
            }
        }
        (void)aCollection;
    }
    return plVar6;
}

// 0x14003cd80 - find the map, build its instance (0x90 bytes), initialise it, then register it on the manager
long long* FUN_14003cd80(long long pManager, unsigned nMapId, unsigned nLow) {
    char cVar1;
    long long* plVar2;
    void* puVar3;
    long long* plVar4;
    long long lVar5;

    plVar2 = FUN_14003ca10(pManager, (int)nMapId);
    if (plVar2 == 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
        plVar4 = 0;
    } else {
        puVar3 = g_pfnNpcOperatorNew(0x90);
        if (puVar3 == 0) {
            plVar4 = 0;
        } else {
            plVar4 = (long long*)g_pfnNpc_1400550f0(puVar3);
        }
        if (plVar4 == 0) {
            if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
            plVar4 = 0;
        } else {
            long long* pVt = (long long*)*plVar4;                       // the instance's vtable
            char (*pfnInit)(long long*, long long*, unsigned) =
                (char (*)(long long*, long long*, unsigned))pVt[0x28 / 8];
            cVar1 = pfnInit(plVar4, plVar2, nLow);
            if (cVar1 == '\0') {
                if (g_pfnNpcInlineLogError != nullptr) {
                    g_pfnNpcInlineLogError("CMapManager::CreateNewInstanceMap error %u");
                }
                void (*pfnRelease)(long long*) = (void (*)(long long*))pVt[0x38 / 8];
                pfnRelease(plVar4);
                plVar4 = 0;
            } else {
                void* pSlots = (void*)*(long long*)(pManager + 8);
                long long* pSlotVt = (long long*)*(long long*)pSlots;
                void (*pfnRegister)(void*, long long*) = (void (*)(void*, long long*))pSlotVt[0x20 / 8];
                pfnRegister(pSlots, plVar4);
                lVar5 = FUN_14001c7a0();
                g_pfnNpc_140032e20(lVar5, nMapId, nLow);
            }
        }
    }
    return plVar4;
}

const NpcMapInstanceEntry g_aNpcMapInstance[] = {
    { "14003ca10", "find-map",            (void*)&FUN_14003ca10 },
    { "14003cd80", "create-map-instance", (void*)&FUN_14003cd80 },
};

const int g_nNpcMapInstance = 2;

}  // namespace tq

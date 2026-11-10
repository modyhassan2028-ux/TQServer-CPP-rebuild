// Transcribed from NpcServer.exe; see cmapmanager-instance.h.
#include "modules/npcserver/unattributed/cmapmanager-instance.h"
#include "modules/npcserver/unattributed/front-of-image.h"

namespace tq {

// The seams this file owns until their own batches land.
long long* (*g_pfnNpc_14003ca10)(long long pManager, unsigned nMapId) = nullptr;
void* (*g_pfnNpc_1400550f0)(void* pStorage) = nullptr;
long long (*g_pfnNpc_14001c7a0)(void) = nullptr;
unsigned long long (*g_pfnNpc_140032e20)(long long pSingleton, unsigned nMapId, unsigned nLow) = nullptr;

// 0x14003cd80 - find the map, build its instance (0x90 bytes), initialise it, then register it on the manager
long long* FUN_14003cd80(long long pManager, unsigned nMapId, unsigned nLow) {
    char cVar1;
    long long* plVar2;
    void* puVar3;
    long long* plVar4;
    long long lVar5;

    plVar2 = g_pfnNpc_14003ca10(pManager, nMapId);
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
                lVar5 = g_pfnNpc_14001c7a0();
                g_pfnNpc_140032e20(lVar5, nMapId, nLow);
            }
        }
    }
    return plVar4;
}

const NpcMapInstanceEntry g_aNpcMapInstance[] = {
    { "14003cd80", "create-map-instance", (void*)&FUN_14003cd80 },
};

const int g_nNpcMapInstance = 1;

}  // namespace tq

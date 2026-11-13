// Transcribed from NpcServer.exe; see cinstance.h.
#include "modules/npcserver/unattributed/cinstance.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"

namespace tq {

// The seams this file owns until their own batches land.
unsigned long long (*g_pfnNpc_14003cc10)(long long pSingleton, unsigned nId) = nullptr;
unsigned long long (*g_pfnNpc_14003cd80)(long long pSingleton, unsigned nMapId, unsigned nLow) = nullptr;

// 0x140049050 - hand the instance's map id to the module singleton
void FUN_140049050(long long pInstance) {
    long long lVar1 = FUN_14001c790();
    g_pfnNpc_14003cc10(lVar1, *(unsigned*)(pInstance + 0xc));
    return;
}

// 0x140049070 - the instance type
unsigned FUN_140049070(long long pInstance) {
    return *(unsigned*)(pInstance + 8);
}

// 0x140048f90 - deleting destructor through the object's own first slot
void FUN_140048f90(long long* pObject) {
    if (pObject != 0) {
        void (*pfnSlot0)(long long*, long long) = (void (*)(long long*, long long))(*pObject);
        pfnSlot0(pObject, 1);
    }
    return;
}

// 0x1400491b0 - build a CInstance and let 0x140048fb0 bring its map up
long long* FUN_1400491b0(unsigned nType, long long pMap, unsigned nLow) {
    long long* puVar1;
    unsigned long long uVar2;
    long long* puVar3;
    if (pMap == 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
        puVar3 = 0;
    } else {
        puVar1 = (long long*)g_pfnNpcOperatorNew(0x18);
        puVar3 = 0;
        if (puVar1 != 0) {
            *puVar1 = (long long)0x1400c7340;                 // CInstance::vftable
            *(unsigned*)((long long)puVar1 + 8) = nType;
            *(long long*)((long long)puVar1 + 0x10) = pMap;
            *(unsigned*)((long long)puVar1 + 0xc) = nLow;
            puVar3 = puVar1;
        }
        if (puVar3 == 0) {
            if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
            puVar3 = 0;
        } else {
            uVar2 = FUN_140048fb0((long long)puVar3);
            if ((char)uVar2 == '\0') {
                puVar3 = 0;
            }
        }
    }
    return puVar3;
}

// 0x140048fb0 - the instance's map, asked for its id through slot 0x10, comes up through the singleton
unsigned long long FUN_140048fb0(long long pInstance) {
    long long lVar2;
    long long* plVar3;
    if (*(long long*)(pInstance + 0x10) == 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
        return 0;
    }
    void* pMap = (void*)*(long long*)(pInstance + 0x10);
    unsigned nMapId = (*(unsigned (**)(void*, long long))(*(long long*)pMap + 0x10))(pMap, 2);
    lVar2 = FUN_14001c790();
    plVar3 = (long long*)g_pfnNpc_14003cd80(lVar2, nMapId, *(unsigned*)(pInstance + 0xc));
    if (plVar3 == 0) {
        if (g_pfnNpcInlineLogError != nullptr) {
            g_pfnNpcInlineLogError("CInstance::Create NPCServer Map Create Error, map:%u");
        }
        return 0;
    }
    return 1;
}

const NpcCInstanceEntry g_aNpcCInstance[] = {
    { "140049050", "release-map",   (void*)&FUN_140049050 },
    { "140049070", "type-getter",   (void*)&FUN_140049070 },
    { "140048f90", "delete-holder", (void*)&FUN_140048f90 },
    { "1400491b0", "create",        (void*)&FUN_1400491b0 },
    { "140048fb0", "bring-up",      (void*)&FUN_140048fb0 },
};

const int g_nNpcCInstance = 5;

}  // namespace tq

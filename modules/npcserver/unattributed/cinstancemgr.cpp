// Transcribed from NpcServer.exe; see cinstancemgr.h.
#include "modules/npcserver/unattributed/cinstancemgr.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/cinstance.h"
#include "modules/npcserver/unattributed/map-insert-erase.h"

namespace tq {

// 0x1400250e0 - the instance stored at node+0x20 for a type id
unsigned long long FUN_1400250e0(long long pMgr, unsigned nType) {
    char cVar1;
    unsigned long long* puVar8;
    unsigned long long* puVar3;
    unsigned long long* puVar5;
    long long lVar4;
    long long lVar9;
    long long* plVar2;
    long long* plVar7;
    unsigned long long uVar6;
    unsigned long long* puVar2;
    long long aMain[2];   // local_38, local_30
    long long aAlt[2];    // local_28, local_20

    puVar8 = (unsigned long long*)(*(long long**)(pMgr + 0x78))[1];
    cVar1 = *(char*)((long long)puVar8 + 0x29);
    puVar3 = *(unsigned long long**)(pMgr + 0x78);
    while (cVar1 == '\0') {
        if (*(unsigned*)(puVar8 + 3) < nType) {
            puVar5 = (unsigned long long*)puVar8[2];
            puVar8 = puVar3;
        } else {
            puVar5 = (unsigned long long*)*puVar8;
        }
        puVar3 = puVar8;
        puVar8 = puVar5;
        cVar1 = *(char*)((long long)puVar5 + 0x29);
    }
    puVar2 = *(unsigned long long**)(pMgr + 0x78);
    aMain[1] = (long long)puVar3;
    aMain[0] = *(long long*)(pMgr + 0x48);
    if (*(long long*)(pMgr + 0x48) == 0) {
        g_pfnNpcInvalidParameter();
    }
    if ((puVar3 == puVar2) || (nType < *(unsigned*)(puVar3 + 3))) {
        plVar7 = aAlt;
        aAlt[1] = *(long long*)(pMgr + 0x78);
        aAlt[0] = *(long long*)(pMgr + 0x48);
    } else {
        plVar7 = aMain;
    }
    plVar2 = (long long*)*plVar7;
    lVar9 = *(long long*)(pMgr + 0x78);
    lVar4 = plVar7[1];
    if ((plVar2 == 0) || (plVar2 != *(long long**)(pMgr + 0x48))) {
        g_pfnNpcInvalidParameter();
    }
    if (lVar4 == lVar9) {
        uVar6 = 0;
    } else {
        if (plVar2 == 0) {
            g_pfnNpcInvalidParameter();
            lVar9 = 0;
        } else {
            lVar9 = *plVar2;
        }
        if (lVar4 == *(long long*)(lVar9 + 0x30)) {
            g_pfnNpcInvalidParameter();
        }
        uVar6 = *(unsigned long long*)(lVar4 + 0x20);
    }
    return uVar6;
}

// 0x140025690 - CInstanceMgr::CreateInstance
unsigned long long FUN_140025690(long long pMgr, unsigned nParam2, unsigned nParam3, unsigned nType) {
    long long lVar1;
    long long* plVar3;
    unsigned long long uVar2;
    long long* plVar30;
    unsigned long long aKeyPair[2];   // the image's local_38 (uint[2]) and local_30 share a stack slot run: the key the
                                      // instance reports, followed by the instance pointer itself
    long long aPair[4];               // local_28: {owner, node, byte at +0x10}

    lVar1 = (long long)FUN_140024fe0(pMgr, nType);
    if (lVar1 == 0) {
        if (g_pfnNpcInlineLogError != nullptr) {
            g_pfnNpcInlineLogError("CInstanceMgr::CreateInstance InstanceType:%u not find");
        }
        uVar2 = 0;
    } else {
        plVar30 = FUN_1400491b0(nParam3, lVar1, nParam2);
        if (plVar30 == 0) {
            if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError((const void*)0x1400be0b0);
            uVar2 = 0;
        } else {
            aKeyPair[0] = (unsigned long long)(unsigned)FUN_140049070((long long)plVar30);
            aKeyPair[1] = (unsigned long long)plVar30;
            plVar3 = FUN_140024970((long long*)(pMgr + 0x48), aPair, (unsigned*)aKeyPair);
            (void)plVar3;
            uVar2 = 1;
        }
    }
    return uVar2;
}

// 0x140025750 - find the instance of a type, release it and erase its entry
void FUN_140025750(long long pMgr, unsigned nType) {
    long long* puVar1;
    unsigned aKey[2];

    aKey[0] = nType;
    puVar1 = (long long*)FUN_1400250e0(pMgr, nType);
    if (puVar1 != 0) {
        FUN_140049050((long long)puVar1);
        FUN_140048f90(puVar1);
        FUN_140024b20((long long*)(pMgr + 0x48), aKey);
    }
    return;
}

const NpcInstanceMgrEntry g_aNpcInstanceMgr[] = {
    { "1400250e0", "find-instance",  (void*)&FUN_1400250e0 },
    { "140025690", "create-instance", (void*)&FUN_140025690 },
    { "140025750", "destroy-instance", (void*)&FUN_140025750 },
};

const int g_nNpcInstanceMgr = 3;

}  // namespace tq

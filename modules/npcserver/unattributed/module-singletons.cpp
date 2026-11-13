// Transcribed from NpcServer.exe; see module-singletons.h.
#include "modules/npcserver/unattributed/module-singletons.h"

namespace tq {

void* g_pNpcModuleBase_1401045b8 = nullptr;

// 0x14001c200 - the module base
long long FUN_14001c200(void) {
    return (long long)g_pNpcModuleBase_1401045b8;
}

// 0x14001c790 - the kernel singleton at base+0x28
long long FUN_14001c790(void) {
    return *(long long*)((char*)g_pNpcModuleBase_1401045b8 + 0x28);
}

// 0x14001c7a0 - the kernel singleton at base+0x30
long long FUN_14001c7a0(void) {
    return *(long long*)((char*)g_pNpcModuleBase_1401045b8 + 0x30);
}

// 0x14001c7b0 - the kernel singleton at base+0x40
long long FUN_14001c7b0(void) {
    return *(long long*)((char*)g_pNpcModuleBase_1401045b8 + 0x40);
}

// 0x14001c7f0 - drop a reference; at zero release the object, and at the second zero destroy it
void FUN_14001c7f0(long long pOwner) {
    long long* plVar3 = *(long long**)(pOwner + 8);
    if (plVar3 != 0) {
        int* piVar1 = (int*)(plVar3 + 2);                                // LOCK(); *(int*)(plVar3 + 2) -= 1; UNLOCK();
        __atomic_sub_fetch(piVar1, 1, __ATOMIC_SEQ_CST);
        if (*piVar1 == 0) {
            long long* pVt = (long long*)*plVar3;                        // the object's vtable
            void (*pfnRelease)(long long*) = (void (*)(long long*))pVt[0];
            pfnRelease(plVar3);
            int* piVar2 = (int*)((long long)plVar3 + 0x14);              // LOCK(); *(int*)(plVar3 + 0x14) -= 1; UNLOCK();
            __atomic_sub_fetch(piVar2, 1, __ATOMIC_SEQ_CST);
            if (*piVar2 == 0) {
                void (*pfnDestroy)(long long*) = (void (*)(long long*))pVt[1];
                pfnDestroy(plVar3);
            }
        }
    }
    return;
}

const NpcModuleSingletonEntry g_aNpcModuleSingleton[] = {
    { "14001c200", "module-base", (void*)&FUN_14001c200 },
    { "14001c790", "get-0x28",  (void*)&FUN_14001c790 },
    { "14001c7a0", "get-0x30",  (void*)&FUN_14001c7a0 },
    { "14001c7b0", "get-0x40",  (void*)&FUN_14001c7b0 },
    { "14001c7f0", "release",   (void*)&FUN_14001c7f0 },
};

const int g_nNpcModuleSingleton = 5;

}  // namespace tq

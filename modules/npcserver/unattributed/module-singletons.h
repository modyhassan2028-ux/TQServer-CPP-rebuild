// The kernel's singleton accessors and the reference-counted release of the 0x14001c7xx cluster.
//
// Everything here hangs off the module base at DAT_1401045b8; 0x14001c790/0x14001c7a0 are the two getters that the
// CInstance and CMapManager batches had been reaching through seams, and they are real bodies now.
#ifndef TQ_NPCSERVER_MODULE_SINGLETONS_H
#define TQ_NPCSERVER_MODULE_SINGLETONS_H

namespace tq {

extern void* g_pNpcModuleBase_1401045b8;   // DAT_1401045b8

long long FUN_14001c200(void);             // the module base itself
long long FUN_14001c790(void);             // *(base + 0x28)
long long FUN_14001c7a0(void);             // *(base + 0x30)
long long FUN_14001c7b0(void);             // *(base + 0x40)
void FUN_14001c7f0(long long pOwner);      // drop a counted reference, freeing at zero

struct NpcModuleSingletonEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcModuleSingletonEntry g_aNpcModuleSingleton[];
extern const int g_nNpcModuleSingleton;

}  // namespace tq

#endif

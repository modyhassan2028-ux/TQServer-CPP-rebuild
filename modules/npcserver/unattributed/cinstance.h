// CInstance: the object CInstanceMgr hands out, plus its two small free helpers.
//
// Object shape (0x18 bytes): vtable +0, instance type +8, map head +0x10, low +0xc.
// The vtable is CInstance::vftable at 0x1400c7340 (read from the `lea` in 0x1400491b0, not guessed).
#ifndef TQ_NPCSERVER_CINSTANCE_H
#define TQ_NPCSERVER_CINSTANCE_H

namespace tq {

extern long long (*g_pfnNpc_14001c790)(void);                                  // the module singleton
extern unsigned long long (*g_pfnNpc_14003cc10)(long long pSingleton, unsigned nId);
extern unsigned long long (*g_pfnNpc_140048fb0)(long long pInstance);

void FUN_140049050(long long pInstance);        // release the instance's map through the singleton
unsigned FUN_140049070(long long pInstance);    // the instance type at +8
void FUN_140048f90(long long* pObject);         // deleting destructor through slot 0
long long* FUN_1400491b0(unsigned nType, long long pMap, unsigned nLow);

struct NpcCInstanceEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcCInstanceEntry g_aNpcCInstance[];
extern const int g_nNpcCInstance;

}  // namespace tq

#endif

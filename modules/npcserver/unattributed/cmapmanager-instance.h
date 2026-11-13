// CMapManager::CreateNewInstanceMap — the manager's map-instance factory.
//
// Transcribed verbatim from NpcServer.exe (0x14003cd80). Four callees are still outside this batch, so they are
// entered through seams until their own bodies land.
#ifndef TQ_NPCSERVER_CMAPMANAGER_INSTANCE_H
#define TQ_NPCSERVER_CMAPMANAGER_INSTANCE_H

namespace tq {

extern void* (*g_pfnNpc_1400550f0)(void* pStorage);
extern long long* (*g_pfnNpcInstanceGet)(long long pModule);   // the 0x14001c110 import thunk
extern unsigned long long (*g_pfnNpc_140032e20)(long long pSingleton, unsigned nMapId, unsigned nLow);

long long* FUN_14003ca10(long long pManager, int nMapId);
long long* FUN_14003cd80(long long pManager, unsigned nMapId, unsigned nLow);

struct NpcMapInstanceEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcMapInstanceEntry g_aNpcMapInstance[];
extern const int g_nNpcMapInstance;

}  // namespace tq

#endif

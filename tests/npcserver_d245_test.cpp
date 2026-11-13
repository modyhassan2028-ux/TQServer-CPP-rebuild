// D245 — CMapManager::CreateNewInstanceMap: lookup, allocation, init, registration and every failure path.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/cmapmanager-instance.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"

using namespace tq;

static int g_logs = 0, g_news = 0, g_ctors = 0, g_inits = 0, g_releases = 0, g_registers = 0, g_records = 0;
static const void* g_pLastMsg = nullptr;
static void* g_pFound = (void*)0xABCD;
static int g_newNull = 0, g_ctorNull = 0, g_initOk = 1;
static long long g_aArgs[16];
static unsigned char g_aStorage[0x90];
static long long g_aInstanceVt[8];
static long long g_aInstance[2];
static long long g_aSlotsVt[8];
static long long g_aSlots[2];
static long long g_aManager[4];
static long long g_singleton2 = 0x7A7A;
static long long g_aModuleBase2[16];

static void* FakeNew(long long n) { ++g_news; assert(n == 0x90); return g_newNull ? nullptr : g_aStorage; }
static void Log(const void* pMsg, ...) { ++g_logs; g_pLastMsg = pMsg; }
static long long* FindMap(long long pManager, unsigned nMapId) {
    g_aArgs[0] = pManager; g_aArgs[1] = (long long)nMapId;
    return (long long*)g_pFound;
}
static void* Construct(void* pStorage) {
    ++g_ctors; assert(pStorage == (void*)g_aStorage);
    return g_ctorNull ? nullptr : (void*)g_aInstance;
}

static unsigned long long Record(long long pSingleton, unsigned nMapId, unsigned nLow) {
    ++g_records;
    g_aArgs[10] = pSingleton; g_aArgs[11] = (long long)nMapId; g_aArgs[12] = (long long)nLow;
    return 1;
}
static char Init(long long* pInstance, long long* pMap, unsigned nLow) {
    ++g_inits;
    g_aArgs[3] = (long long)pInstance; g_aArgs[4] = (long long)pMap; g_aArgs[5] = (long long)nLow;
    return g_initOk;
}
static void Release(long long* pInstance) {
    ++g_releases;
    g_aArgs[6] = (long long)pInstance;
}
static void Register(void* pSlots, long long* pInstance) {
    ++g_registers;
    g_aArgs[7] = (long long)pSlots; g_aArgs[8] = (long long)pInstance;
}

static void Reset() {
    g_logs = g_news = g_ctors = g_inits = g_releases = g_registers = g_records = 0;
    g_pLastMsg = nullptr;
    g_pFound = (void*)0xABCD;
    g_newNull = g_ctorNull = 0;
    g_initOk = 1;
    std::memset(g_aArgs, 0, sizeof g_aArgs);
    std::memset(g_aStorage, 0, sizeof g_aStorage);
    std::memset(g_aInstanceVt, 0, sizeof g_aInstanceVt);
    std::memset(g_aInstance, 0, sizeof g_aInstance);
    g_aInstance[0] = (long long)g_aInstanceVt;   // the object's first field is its vtable
    std::memset(g_aSlots, 0, sizeof g_aSlots);
    std::memset(g_aManager, 0, sizeof g_aManager);
    g_aInstanceVt[0x28 / 8] = (long long)&Init;
    g_aInstanceVt[0x38 / 8] = (long long)&Release;
    g_aSlotsVt[0x20 / 8] = (long long)&Register;
    g_aSlots[0] = (long long)g_aSlotsVt;
    g_aManager[1] = (long long)g_aSlots;      // the manager's +8 holds the slot object
}

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcInlineLogError = &Log;
    g_pfnNpc_14003ca10 = &FindMap;
    g_pfnNpc_1400550f0 = &Construct;
    std::memset(g_aModuleBase2, 0, sizeof g_aModuleBase2);
    *(long long*)((char*)g_aModuleBase2 + 0x30) = g_singleton2;
    g_pNpcModuleBase_1401045b8 = g_aModuleBase2;
    g_pfnNpc_140032e20 = &Record;

    assert(g_nNpcMapInstance == 1);
    int nCase = 0;

    for (int i = 0; i < g_nNpcMapInstance; ++i) {
        const NpcMapInstanceEntry& e = g_aNpcMapInstance[i];
        assert(std::strcmp(e.pszKind, "create-map-instance") == 0);
        typedef long long* (*Fn)(long long, unsigned, unsigned);
        Fn pfn = (Fn)e.pfn;

        // the map does not exist: one log line, nothing allocated
        Reset();
        g_pFound = nullptr;
        assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
        assert(g_logs == 1 && g_pLastMsg == (const void*)0x1400be0b0);
        assert(g_news == 0 && g_ctors == 0 && g_inits == 0);
        assert(g_aArgs[0] == (long long)g_aManager && g_aArgs[1] == 0x11);   // lookup got both ids

        // the 0x90-byte allocation failed
        Reset();
        g_newNull = 1;
        assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
        assert(g_news == 1 && g_ctors == 0 && g_logs == 1);
        assert(g_pLastMsg == (const void*)0x1400be0b0);

        // the constructor answered null
        Reset();
        g_ctorNull = 1;
        assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
        assert(g_news == 1 && g_ctors == 1 && g_logs == 1 && g_inits == 0);

        // the instance refused to initialise: the error line, the release slot, and a null answer
        Reset();
        g_initOk = 0;
        assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
        assert(g_inits == 1);
        assert(g_aArgs[3] == (long long)g_aInstance);        // the instance
        assert(g_aArgs[4] == (long long)0xABCD);                 // the map from the lookup
        assert(g_aArgs[5] == 0x22);                            // the low dword
        assert(g_logs == 1);
        assert(std::strcmp((const char*)g_pLastMsg, "CMapManager::CreateNewInstanceMap error %u") == 0);
        assert(g_releases == 1 && g_aArgs[6] == (long long)g_aInstance);
        assert(g_registers == 0 && g_records == 0);            // nothing was registered

        // the happy path: registered on the manager's slots, then recorded on the second singleton
        Reset();
        long long* pResult = pfn((long long)g_aManager, 0x11, 0x22);
        assert(pResult == g_aInstance);
        assert(g_logs == 0 && g_releases == 0);
        assert(g_registers == 1);
        assert(g_aArgs[7] == (long long)g_aSlots);             // *(pManager + 8)
        assert(g_aArgs[8] == (long long)g_aInstance);
        assert(g_records == 1);
        assert(g_aArgs[10] == g_singleton2);                   // from 0x14001c7a0
        assert(g_aArgs[11] == 0x11 && g_aArgs[12] == 0x22);    // the two ids, in order
        ++nCase;
    }

    assert(nCase == 1);
    std::printf("NPCSERVER_D245_OK: map instance create, every failure path and registration\n");
    return 0;
}

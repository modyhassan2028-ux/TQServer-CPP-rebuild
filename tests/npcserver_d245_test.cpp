// D245/D249 — CMapManager::FindMap and CreateNewInstanceMap, over a fake cache, a fake row and a fake instance.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "modules/npcserver/unattributed/cmapmanager-instance.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/module-singletons.h"

using namespace tq;

// ---- what the suites record -------------------------------------------------------------------------------------
static int g_logs = 0, g_news = 0, g_ctors = 0, g_inits = 0, g_releases = 0, g_registers = 0, g_records = 0;
static int g_cacheGets = 0, g_cacheAdds = 0, g_dbQueries = 0, g_rowReleases = 0;
static const void* g_pLastMsg = nullptr;
static char g_lastSql[512];
static const char* g_pGetterFile = nullptr;
static long long g_nGetterLine = 0;
static long long g_aArgs[16];

// ---- the objects -----------------------------------------------------------------------------------------------
static long long g_aCacheVt[8], g_aCacheObj[2], g_aObjs[3][4], g_aObjVt[8];
static int g_nCacheCount = 0, g_cacheIds[3] = { 0, 0, 0 };
static long long g_aRowVt[12], g_aRow[2], g_pRowDbg = 0;
static int g_rowEmpty = 0;
static long long g_aDbVt[8], g_aDb[2];
static long long g_aInstanceVt[12], g_aInstance[2];
static long long g_aSlotsVt[8], g_aSlots[2];
static long long g_aManager[4];
static long long g_aModuleBase[16];
static long long g_singleton2 = 0x7A7A;
static int g_newNull = 0, g_ctorNull = 0, g_initOk = 1;

static void* FakeNew(long long n) { ++g_news; assert(n == 0x90); return g_newNull ? nullptr : (void*)g_aInstance; }
static void Log(const void* pMsg, ...) { ++g_logs; g_pLastMsg = pMsg; }

// the cache collection: +0x10 count, +0x18 indexed getter, +0x20 add
static long long CacheCount(long long* pCache) { assert(pCache == g_aCacheObj); return g_nCacheCount; }
static long long* CacheAt(long long* pCache, long long nIndex, const char* pFile, long long nLine) {
    assert(pCache == g_aCacheObj);
    ++g_cacheGets;
    g_pGetterFile = pFile;
    g_nGetterLine = nLine;
    if (nIndex < 0 || nIndex >= g_nCacheCount) return nullptr;
    return g_aObjs[nIndex];
}
static void CacheAdd(long long* pCache, long long* pEntry) {
    assert(pCache == g_aCacheObj);
    ++g_cacheAdds;
    g_aArgs[9] = (long long)pEntry;
}

// every cached object answers its id through slot +8, read from +0x10
static int ObjId(long long* pObj) { return (int)*(long long*)((char*)pObj + 0x10); }

// the database instance: slot +0x10 runs the statement and answers the row
static long long* DbQuery(long long* pDb, char* pSql, long long nMode) {
    assert(pDb == g_aDb);
    assert(nMode == 2);
    ++g_dbQueries;
    std::snprintf(g_lastSql, sizeof g_lastSql, "%s", pSql);
    return (long long*)g_pRowDbg;
}

// the row: +0x40 answers "not empty", slot 0 releases it
static long long RowHasData(long long* pRow) { assert(pRow == g_aRow); return g_rowEmpty ? 0 : 1; }
static void RowRelease(long long* pRow) { ++g_rowReleases; assert(pRow == g_aRow); }

// the instance being built: +0x20 init, +0x38 release
static char InstanceInit(long long* pInstance, long long* pMap, long long nLow) {
    ++g_inits;
    g_aArgs[3] = (long long)pInstance;
    g_aArgs[4] = (long long)pMap;
    g_aArgs[5] = nLow;
    return g_initOk;
}
static void InstanceRelease(long long* pInstance) { ++g_releases; g_aArgs[6] = (long long)pInstance; }
static void Register(void* pSlots, long long* pEntry) {
    ++g_registers;
    g_aArgs[7] = (long long)pSlots;
    g_aArgs[8] = (long long)pEntry;
}
static long long* InstanceGetFake(long long pModule) { assert(pModule == (long long)g_aModuleBase); return g_aDb; }
static unsigned long long Record(long long pSingleton, unsigned nMapId, unsigned nLow) {
    ++g_records;
    g_aArgs[10] = pSingleton; g_aArgs[11] = (long long)nMapId; g_aArgs[12] = (long long)nLow;
    return 1;
}
static void* Construct(void* pStorage) { ++g_ctors; assert(pStorage == (void*)g_aInstance); return g_ctorNull ? nullptr : (void*)g_aInstance; }

static void Reset() {
    g_logs = g_news = g_ctors = g_inits = g_releases = g_registers = g_records = 0;
    g_cacheGets = g_cacheAdds = g_dbQueries = g_rowReleases = 0;
    g_pLastMsg = nullptr;
    g_pGetterFile = nullptr;
    g_nGetterLine = 0;
    g_lastSql[0] = 0;
    g_newNull = g_ctorNull = 0;
    g_initOk = 1;
    g_rowEmpty = 0;
    g_nCacheCount = 0;
    g_pRowDbg = (long long)g_aRow;
    std::memset(g_aArgs, 0, sizeof g_aArgs);
}

static void BuildFixtures() {
    std::memset(g_aModuleBase, 0, sizeof g_aModuleBase);
    *(long long*)((char*)g_aModuleBase + 0x30) = g_singleton2;
    g_pNpcModuleBase_1401045b8 = g_aModuleBase;

    g_aManager[1] = (long long)g_aCacheObj;      // the cache at +8

    g_aCacheVt[0x10 / 8] = (long long)&CacheCount;
    g_aCacheVt[0x18 / 8] = (long long)&CacheAt;
    g_aCacheVt[0x20 / 8] = (long long)&CacheAdd;
    g_aCacheObj[0] = (long long)g_aCacheVt;

    g_aObjVt[0x8 / 8] = (long long)&ObjId;
    for (int i = 0; i < 3; ++i) {
        std::memset(g_aObjs[i], 0, sizeof g_aObjs[i]);
        g_aObjs[i][0] = (long long)g_aObjVt;
        *(long long*)((char*)g_aObjs[i] + 0x10) = (long long)g_cacheIds[i];
    }

    g_aRowVt[0] = (long long)&RowRelease;
    g_aRowVt[0x40 / 8] = (long long)&RowHasData;
    g_aRow[0] = (long long)g_aRowVt;

    g_aDbVt[0x10 / 8] = (long long)&DbQuery;
    g_aDb[0] = (long long)g_aDbVt;

    g_aInstanceVt[0x20 / 8] = (long long)&InstanceInit;   // from a row
    g_aInstanceVt[0x28 / 8] = (long long)&InstanceInit;   // from a map
    g_aInstanceVt[0x38 / 8] = (long long)&InstanceRelease;
    g_aInstance[0] = (long long)g_aInstanceVt;

    g_aSlotsVt[0x20 / 8] = (long long)&Register;
    g_aSlots[0] = (long long)g_aSlotsVt;
}

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcInlineLogError = &Log;
    g_pfnNpcInstanceGet = &InstanceGetFake;
    g_pfnNpc_1400550f0 = &Construct;
    g_pfnNpc_140032e20 = &Record;
    BuildFixtures();

    assert(g_nNpcMapInstance == 2);
    int nFind = 0, nCreate = 0;

    for (int i = 0; i < g_nNpcMapInstance; ++i) {
        const NpcMapInstanceEntry& e = g_aNpcMapInstance[i];

        if (std::strcmp(e.pszKind, "find-map") == 0) {
            typedef long long* (*FindFn)(long long, int);
            FindFn pfn = (FindFn)e.pfn;

            // a zero id never reaches the cache
            Reset();
            assert(pfn((long long)g_aManager, 0) == 0);
            assert(g_logs == 1 && g_pLastMsg == (const void*)0x1400be0b0 && g_cacheGets == 0);

            // the cache answers: the loop stops on the matching id
            Reset();
            g_nCacheCount = 3;
            g_cacheIds[0] = 5; g_cacheIds[1] = 7; g_cacheIds[2] = 9;
            BuildFixtures(); g_nCacheCount = 3;
            assert(pfn((long long)g_aManager, 7) == g_aObjs[1]);
            assert(g_cacheGets == 2);                       // 0 was asked, then 1
            assert(g_dbQueries == 0);
            assert(g_pGetterFile != nullptr && g_nGetterLine == 0x72);
            assert(std::strcmp(g_pGetterFile,
                   "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\mapmanager.cpp") == 0);

            // a miss: the statement carries the id, and the row builds the instance
            Reset();
            g_nCacheCount = 2;
            g_cacheIds[0] = 5; g_cacheIds[1] = 7;
            assert(pfn((long long)g_aManager, 0x33) == g_aInstance);
            assert(g_dbQueries == 1);
            assert(std::strcmp(g_lastSql,
                   "SELECT * FROM cq_dynamap WHERE id=51 && del_flag=0 LIMIT 1") == 0);
            assert(g_cacheAdds == 1 && g_aArgs[9] == (long long)g_aInstance);   // the cache's slot 0x20
            assert(g_rowReleases == 1 && g_logs == 0);

            // the row came back empty
            Reset();
            g_rowEmpty = 1;
            assert(pfn((long long)g_aManager, 0x33) == 0);
            assert(g_rowReleases == 1 && g_logs == 0 && g_registers == 0);

            // the allocation failed
            Reset();
            g_newNull = 1;
            assert(pfn((long long)g_aManager, 0x33) == 0);
            assert(g_rowReleases == 1 && g_registers == 0 && g_logs == 0);

            // the instance refused the row: the 0x1400be0b0 line, its release slot, and the row released
            Reset();
            g_initOk = 0;
            assert(pfn((long long)g_aManager, 0x33) == 0);
            assert(g_logs == 1 && g_pLastMsg == (const void*)0x1400be0b0);
            assert(g_aArgs[6] == (long long)g_aInstance);
            assert(g_rowReleases == 1 && g_registers == 0 && g_records == 0);
            ++nFind;

        } else if (std::strcmp(e.pszKind, "create-map-instance") == 0) {
            typedef long long* (*CreateFn)(long long, unsigned, unsigned);
            CreateFn pfn = (CreateFn)e.pfn;

            // the map is not there: one line, nothing built
            Reset();
            g_rowEmpty = 1;
            assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
            assert(g_logs == 1 && g_pLastMsg == (const void*)0x1400be0b0);
            assert(g_news == 0 && g_inits == 0 && g_records == 0);

            // the happy path: the cached map is handed to the instance, which is registered and recorded
            Reset();
            g_nCacheCount = 1; g_cacheIds[0] = 0x11;
            BuildFixtures(); g_nCacheCount = 1; g_cacheIds[0] = 0x11;
            std::memset(g_aObjs[0], 0, sizeof g_aObjs[0]);
            g_aObjs[0][0] = (long long)g_aObjVt;
            *(long long*)((char*)g_aObjs[0] + 0x10) = 0x11;
            assert(pfn((long long)g_aManager, 0x11, 0x22) == g_aInstance);
            assert(g_news == 1 && g_ctors == 1 && g_inits == 1);
            assert(g_aArgs[4] == (long long)g_aObjs[0]);        // the cached map
            assert(g_aArgs[5] == 0x22);
            assert(g_cacheAdds == 1 && g_aArgs[9] == (long long)g_aInstance);   // the manager's slot 0x20
            assert(g_records == 1 && g_aArgs[10] == g_singleton2);
            assert(g_aArgs[11] == 0x11 && g_aArgs[12] == 0x22);

            // the allocation failed
            Reset();
            g_nCacheCount = 1; g_cacheIds[0] = 0x11;
            g_newNull = 1;
            assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
            assert(g_news == 1 && g_logs == 1 && g_inits == 0);

            // the constructor answered null
            Reset();
            g_nCacheCount = 1; g_cacheIds[0] = 0x11;
            g_ctorNull = 1;
            assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
            assert(g_ctors == 1 && g_logs == 1 && g_inits == 0);

            // the instance refused to initialise: the literal line and the release slot
            Reset();
            g_nCacheCount = 1; g_cacheIds[0] = 0x11;
            g_initOk = 0;
            assert(pfn((long long)g_aManager, 0x11, 0x22) == 0);
            assert(g_inits == 1 && g_releases == 1);
            assert(g_aArgs[6] == (long long)g_aInstance);
            assert(g_logs == 1);
            assert(std::strcmp((const char*)g_pLastMsg,
                               "CMapManager::CreateNewInstanceMap error %u") == 0);
            assert(g_cacheAdds == 0 && g_records == 0);
            ++nCreate;

        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(g_nNpcMapInstance == 2 && nFind == 1 && nCreate == 1);
    std::printf("NPCSERVER_D245_OK: FindMap and CreateNewInstanceMap\n");
    return 0;
}

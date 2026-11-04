// ============================================================================
// cqbase_d43 — the singleton destroyer, the consumer setter, and the option get/set pair with
//   the guard strings read off the instructions
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/synmanager3.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

namespace tq { extern void* g_pSynManager; }

static std::vector<std::string> g_sLogs;
static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

static int g_nSlot8 = 0;
static void* g_pSlot8Flag = nullptr;
static int g_nHolderSlot0 = 0;
static int g_nMapSet = 0;
static void* g_pMapSetArg = nullptr;
static int32_t g_nMapSetId = 0;
static uint32_t g_uMapSetValue = 0;

static void* g_aManagerVft[0x10 / 8];
static void* g_aHolderVft[0x08 / 8];
static void* g_aMapVft[0x108 / 8];

static void ManagerSlot8(void*, void* pFlag) {
    ++g_nSlot8;
    g_pSlot8Flag = pFlag;
}
static void HolderSlot0(void*) { ++g_nHolderSlot0; }
static void MapSlot100(void*, int32_t nId, uint32_t uValue) {
    ++g_nMapSet;
    g_nMapSetId = nId;
    g_uMapSetValue = uValue;
    (void)g_pMapSetArg;
}

int main() {
    LogApi savedLog = g_LogApi;
    g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    g_aManagerVft[0x08 / 8] = (void*)&ManagerSlot8;
    g_aHolderVft[0x00 / 8] = (void*)&HolderSlot0;
    g_aMapVft[0x100 / 8] = (void*)&MapSlot100;

    uint8_t aManager[0xb0];
    std::memset(aManager, 0, sizeof(aManager));
    void* aManagerObj[0x10 / 8];
    aManagerObj[0] = g_aManagerVft;

    uint8_t aHolder[0x90];
    std::memset(aHolder, 0, sizeof(aHolder));
    uint8_t aHolderObj[0x90];
    std::memset(aHolderObj, 0, sizeof(aHolderObj));
    *(void**)aHolderObj = g_aHolderVft;

    uint8_t aMap[0x110];
    std::memset(aMap, 0, sizeof(aMap));
    aMap[0] = 0;
    *(void**)aMap = g_aMapVft;

    // ---- the singleton destroyer: one call through slot 8 with flag one, then the slot clears
    {
        g_nSlot8 = 0;
        g_pSlot8Flag = nullptr;
        g_pSynManager = aManagerObj;
        SynManagerDestroySingleton();
        CHECK(g_nSlot8 == 1);
        CHECK(g_pSlot8Flag == (void*)1);
        CHECK(g_pSynManager == nullptr);
        // and with no singleton nothing happens at all
        SynManagerDestroySingleton();
        CHECK(g_nSlot8 == 1);
    }

    // ---- the consumer setter
    {
        void* pA = (void*)0xAAAA;
        void* pB = (void*)0xBBBB;
        CHECK(SynManagerSetConsumers(aManager, pA, pB) == 1);
        CHECK(*(void**)(aManager + 0x88) == pA);
        CHECK(*(void**)(aManager + 0x90) == pB);

        g_sLogs.clear();
        CHECK(SynManagerSetConsumers(aManager, nullptr, pB) == 0);
        CHECK(g_sLogs.size() == 1);
        CHECK(g_sLogs[0].find("pConsumer") != std::string::npos);
        CHECK(g_sLogs[0].find("67") != std::string::npos);

        g_sLogs.clear();
        CHECK(SynManagerSetConsumers(aManager, pA, nullptr) == 0);
        CHECK(g_sLogs.size() == 1);
        CHECK(g_sLogs[0].find("pSynAttrMgr") != std::string::npos);
        CHECK(g_sLogs[0].find("68") != std::string::npos);
        CHECK(*(void**)(aManager + 0x88) == pA);      // the first store already happened? no
    }

    // ---- the option getter
    {
        *(int32_t*)(aManager + 0xa8) = 4711;
        *(int32_t*)(aManager + 0xac) = 1000 + 7;
        CHECK(SynManagerItemGet(aManager, 0x40e) == 4711);
        CHECK(SynManagerItemGet(aManager, 1000) == 1007);
        CHECK(SynManagerItemGet(aManager, 1) == 0);
        CHECK(SynManagerItemGet(aManager, 0) == 0);
    }

    // ---- the option setter
    {
        g_nHolderSlot0 = 0;
        g_nMapSet = 0;
        *(void**)(aManager + 0x08) = aHolderObj;
        *(void**)(aHolderObj + 0x88) = aMap;
        SynManagerItemSet(aManager, 0x40e, 0x99);
        CHECK(g_nHolderSlot0 == 1);                    // the holder was asked first
        CHECK(g_nMapSet == 1);
        CHECK(g_nMapSetId == 0x40e);
        CHECK(g_uMapSetValue == 0x99);

        g_sLogs.clear();
        g_nHolderSlot0 = 0;
        SynManagerItemSet(aManager, 0, 0x99);
        CHECK(g_nHolderSlot0 == 0);                    // a zero id does nothing
        CHECK(g_sLogs.size() == 1);
        CHECK(g_sLogs[0].find("idMap") != std::string::npos);
        CHECK(g_sLogs[0].find("1054") != std::string::npos);
    }

    g_LogApi = savedLog;
    std::printf("SYNDICATE_D43_OK: the singleton destroyer, the consumer setter and the option "
                "pair, 4 units, %d checks\n", g_nChecks);
    return 0;
}

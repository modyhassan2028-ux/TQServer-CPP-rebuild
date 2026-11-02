// ============================================================================
// cqbase_d24 — the foundation of the Syndicate objects: the two constructors and the two
//   releases, checked field by field and in the order the binary writes them
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/crossvlmresult.h"
#include "modules/syndicate/src/meedrecord.h"
#include "modules/syndicate/src/synobjects.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static int g_nListInit = 0;
static void* g_pListSeen = nullptr;
static std::string g_strOrder;
static std::string g_strRelease;
static void* g_pReleaseArg = nullptr;

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }
static void HookInitList(void** ppHead) {
    ++g_nListInit;
    g_pListSeen = (void*)ppHead;
    g_strOrder += "list;";
}

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    tq::g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    // ---- CCrossVlmResult: the node, the three qwords, the list hook, then +0x00 last
    {
        alignas(8) unsigned char acMem[0x38];
        std::memset(acMem, 0xCD, sizeof(acMem));       // the constructor must clear what it owns
        CCrossVlmResult* pObj = (CCrossVlmResult*)acMem;

        g_pfnInitCrossVlmList = &HookInitList;
        assert(pObj->Construct() == pObj);

        // +0x08 holds the node, and that node points back at the head
        void* pHead = *(void**)(acMem + 0x08);
        assert(pHead != nullptr);
        assert(*(void**)pHead == (void*)(acMem + 0x08));

        assert(*(uint64_t*)(acMem + 0x20) == 0);
        assert(*(uint64_t*)(acMem + 0x28) == 0);
        assert(*(uint64_t*)(acMem + 0x30) == 0);
        assert(*(uint64_t*)(acMem + 0x00) == 0);        // written after the hook ran
        assert(g_nListInit == 1);
        assert(g_pListSeen == (void*)(acMem + 0x08));   // the hook is given the head itself
        assert(g_strOrder == "list;");

        // +0x10 and +0x18 are left as they were: the constructor never writes them
        assert(*(uint64_t*)(acMem + 0x10) == 0xCDCDCDCDCDCDCDCDull);
        assert(*(uint64_t*)(acMem + 0x18) == 0xCDCDCDCDCDCDCDCDull);

        ::operator delete(pHead);
    }

    // ---- CMeedRecord: the id first, then the node, then the cleared block
    {
        alignas(8) unsigned char acMem[0x40];
        std::memset(acMem, 0xCD, sizeof(acMem));
        CMeedRecord* pRec = (CMeedRecord*)acMem;

        g_sLogs.clear();
        assert(pRec->Construct(0x2A) == pRec);
        assert(*(uint32_t*)(acMem + 0x00) == 0x2A);

        void* pHead = *(void**)(acMem + 0x08);
        assert(pHead != nullptr);
        assert(*(void**)pHead == (void*)(acMem + 0x08));

        for (int i = 0; i < 6; ++i) assert(*(uint32_t*)(acMem + 0x20 + 4 * i) == 0);
        assert(*(uint8_t*)(acMem + 0x38) == 0);
        // +0x10 and +0x18 stay untouched, exactly like the binary leaves them
        assert(*(uint64_t*)(acMem + 0x10) == 0xCDCDCDCDCDCDCDCDull);
        assert(*(uint64_t*)(acMem + 0x18) == 0xCDCDCDCDCDCDCDCDull);
        assert(g_sLogs.empty());                        // a real id is not reported

        ::operator delete(pHead);

        // An id of zero makes the binary report it through a log call that is handed the
        // format and nothing else, so the %s inside it reads whatever the registers happen
        // to hold. That is the binary's own undefined behaviour and it is kept verbatim in
        // meedrecord.cpp; the test does not execute it, because under the sanitizers it
        // aborts instead of reading registers the way the shipped build does.
    }

    // ---- the releases: null is ignored, anything else is taken apart then handed back
    {
        g_pfnDestroyDomain = [](void* p, void*, void*) { g_strRelease += "destroy;"; g_pReleaseArg = p; };
        g_pfnFreeDomainAlloc = [](void* p) { g_strRelease += "free;"; assert(p == g_pReleaseArg); };
        g_pfnDestroyFacility = [](void* p, void*, void*) { g_strRelease += "fdestroy;"; g_pReleaseArg = p; };
        g_pfnFreeFacilityAlloc = [](void* p) { g_strRelease += "ffree;"; assert(p == g_pReleaseArg); };

        g_strRelease.clear();
        CSynDomain::Release(nullptr);
        CSynFacility::Release(nullptr);
        assert(g_strRelease.empty());          // a null object touches nothing

        g_strRelease.clear();
        CSynDomain::Release((CSynDomain*)(void*)0xD0);
        assert(g_strRelease == "destroy;free;");   // torn down first, handed back second

        g_strRelease.clear();
        CSynFacility::Release((CSynFacility*)(void*)0xF0);
        assert(g_strRelease == "fdestroy;ffree;");
        assert(g_pReleaseArg == (void*)0xF0);
    }

    tq::g_LogApi = savedLog;
    std::printf("SYNDICATE_D24_OK: the two constructors and the two releases, 4 units, 27 checks\n");
    return 0;
}

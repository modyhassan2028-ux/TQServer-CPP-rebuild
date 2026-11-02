// ============================================================================
// cqbase_d23 — the syndicate manager's three calls and the packet string writer
// ============================================================================
#include "modules/cqbase/src/cstrpacker.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"
#include "modules/syndicate/src/synmanager.h"
#include "modules/syndicate/src/synmsg.h"
#include "modules/syndicate/src/synobjects.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <new>

using namespace tq;

static std::vector<std::string> g_sLogs;
static std::vector<void*> g_pMade;
static int g_nFound = 0, g_nDomainInit = 0, g_nDomainRelease = 0, g_nAddDomain = 0;
static int g_nFacilityInit = 0, g_nFacilityRelease = 0, g_nAddFacility = 0;
static int g_nMapFind = 0, g_nMapRename = 0;
static uint32_t g_uDomainId = 0, g_uFacilityId = 0;
static int32_t g_nFacilityType = 0;
static std::string g_strMapFound, g_strMapOld, g_strMapNew;

static bool HookRunning() { return false; }
static void HookWrite(const char*, const char* pszText, int) {
    g_sLogs.push_back(pszText != nullptr ? pszText : "");
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

static void* TestSyn = (void*)0x5ee;
static void* HookFindSyn(CSynManager*, uint32_t) { ++g_nFound; return TestSyn; }
static void* HookGetSynName(void*) { static const char kName[] = "HOSTILE"; return (void*)kName; }
static bool HookDomainInit(CSynDomain*, uint32_t uId, void* pName) {
    ++g_nDomainInit;
    g_uDomainId = uId;
    return pName == (void*)&"HOSTILE"[0] || std::strcmp((const char*)pName, "HOSTILE") == 0;
}
static void HookDomainRelease(CSynDomain* p) { ++g_nDomainRelease; g_pMade.push_back(p); }
static bool HookFacilityInit(CSynFacility*, uint32_t uId, int32_t nType) {
    ++g_nFacilityInit;
    g_uFacilityId = uId;
    g_nFacilityType = nType;
    return true;
}
static void HookFacilityRelease(CSynFacility*) { ++g_nFacilityRelease; }
static void HookAddDomain(void*, CSynDomain* p) { ++g_nAddDomain; g_pMade.push_back(p); }
static void HookAddFacility(void*, CSynFacility* p) { ++g_nAddFacility; g_pMade.push_back(p); }
static void HookMapFind(void*, const std::string& rName) { ++g_nMapFind; g_strMapFound = rName; }
static void HookMapRename(void*, const std::string* pOld, const std::string& rNew) {
    ++g_nMapRename;
    g_strMapOld = *pOld;
    g_strMapNew = rNew;
}

// the heap seam, so the creators' memory is the test's to free
static void* TestCreate(uint32_t, size_t, size_t) { return (void*)1; }
static void* TestAlloc(void*, uint32_t, size_t uBytes) { return std::calloc(1, uBytes); }
static bool TestFree(void*, uint32_t, void* pMem) { std::free(pMem); return true; }
static bool TestValid(void*, uint32_t, const void*) { return true; }
static bool TestDestroy(void*) { return true; }

int main() {
    tq::LogApi savedLog = tq::g_LogApi;
    tq::g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};
    HeapApi savedHeap = tq::g_HeapApi;
    tq::g_HeapApi = {&TestCreate, &TestAlloc, &TestFree, &TestValid, &TestDestroy};

    g_pfnFindSyn = &HookFindSyn;
    g_pfnGetSynName = &HookGetSynName;
    g_pfnDomainInit = &HookDomainInit;
    g_pfnDomainRelease = &HookDomainRelease;
    g_pfnFacilityInit = &HookFacilityInit;
    g_pfnFacilityRelease = &HookFacilityRelease;
    g_pfnAddDomainToSyn = &HookAddDomain;
    g_pfnAddFacilityToSyn = &HookAddFacility;
    g_pfnMapFindByName = &HookMapFind;
    g_pfnMapRename = &HookMapRename;

    CSynManager mgr;
    std::memset(&mgr, 0, sizeof(mgr));
    mgr.pSynOwner = (void*)0xAA;
    mgr.pSecondOwner = (void*)0xBB;

    // ---- a domain is built, initialised with the id and the name, then handed to the syn
    {
        assert(mgr.CreateDomain(0x31) == true);
        assert(g_nFound == 1);
        assert(g_nDomainInit == 1 && g_uDomainId == 0x31);
        assert(g_nAddDomain == 1);
        assert(g_nDomainRelease == 0);      // nothing to release on the good path
        assert(g_sLogs.empty());
    }

    // ---- a facility goes the same way and carries its type
    {
        assert(mgr.CreateFacility(0x41, 7) == true);
        assert(g_nFacilityInit == 1 && g_uFacilityId == 0x41 && g_nFacilityType == 7);
        assert(g_nAddFacility == 1);
        assert(g_nFacilityRelease == 0);
    }

    // ---- a failed init releases what was made and answers false
    {
        const int nBefore = g_nDomainRelease;
        g_pfnDomainInit = [](CSynDomain*, uint32_t, void*) { return false; };
        g_sLogs.clear();
        assert(mgr.CreateDomain(0x51) == false);
        assert(g_nDomainRelease == nBefore + 1);
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("IF_NOT") != std::string::npos &&
               g_sLogs[0].find("pDomain->Create(idSyn, pSyn->GetSynName())") != std::string::npos);
        g_pfnDomainInit = &HookDomainInit;
    }

    // ---- no syndicate, no work at all
    {
        g_pfnFindSyn = [](CSynManager*, uint32_t) -> void* { return nullptr; };
        const int nInit = g_nDomainInit, nFac = g_nFacilityInit;
        g_sLogs.clear();
        assert(mgr.CreateDomain(0x61) == false);
        assert(mgr.CreateFacility(0x62, 1) == false);
        assert(g_nDomainInit == nInit && g_nFacilityInit == nFac);
        assert(g_sLogs.empty());
        g_pfnFindSyn = &HookFindSyn;
    }

    // ---- the rename checks each name at its own line before it touches the table
    {
        g_sLogs.clear();
        assert(mgr.RenameSyn(nullptr, "new") == false);
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("CHECKF") != std::string::npos);
        assert(g_nMapFind == 0 && g_nMapRename == 0);

        g_sLogs.clear();
        assert(mgr.RenameSyn("old", nullptr) == false);
        assert(g_nMapFind == 0 && g_nMapRename == 0);

        assert(mgr.RenameSyn("old", "new") == true);
        assert(g_nMapFind == 1 && g_strMapFound == "old");
        assert(g_nMapRename == 1 && g_strMapOld == "old" && g_strMapNew == "new");
    }

    // ---- the packet writer: the advertised size is the packer's plus 0x1b
    {
        alignas(16) char acPacket[0x460];
        std::memset(acPacket, 0, sizeof(acPacket));
        char acBuf[128];
        std::memset(acBuf, 0, sizeof(acBuf));

        CStringPacker* pPacker = new (static_cast<void*>(acPacket + 0x410)) CStringPacker();
        pPacker->SetBuf(acBuf, sizeof(acBuf), false);
        int16_t nSize = -1;
        *(int16_t**)(acPacket + 0x408) = &nSize;

        g_sLogs.clear();
        assert(SynMsgAddString(acPacket, nullptr) == false);
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("CHECKF") != std::string::npos);
        assert(nSize == -1);                       // untouched on the null path

        assert(SynMsgAddString(acPacket, "HOSTILE") == true);
        assert(nSize == (int16_t)((uint16_t)pPacker->GetSize() + 0x1b));
        assert(pPacker->GetSize() >= 8);           // the string did go in
        pPacker->~CStringPacker();
    }

    // every object the creators handed out is freed here, so the run is leak clean
    for (size_t i = 0; i < g_pMade.size(); ++i) std::free(g_pMade[i]);

    tq::g_HeapApi = savedHeap;
    std::printf("SYNDICATE_D23_OK: the manager three calls and the packet string, 4 units, 31 checks\n");
    return 0;
}

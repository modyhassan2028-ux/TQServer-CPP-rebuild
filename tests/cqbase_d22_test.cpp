// ============================================================================
// cqbase_d22 — the first Syndicate units: the four creators and the two guarded members
// ============================================================================
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"
#include "modules/syndicate/src/crossvlmresult.h"
#include "modules/syndicate/src/meedrecord.h"
#include "modules/syndicate/src/synarenicmeed.h"
#include "modules/syndicate/src/synobjects.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;
static int g_nCrossCtor = 0;
static int g_nMeedCtor = 0;
static uint32_t g_uMeedId = 0;
static int g_nSyndicateCtor = 0;

static bool HookRunning() { return false; }
static void HookWrite(const char* pszFile, const char* pszText, int) {
    g_sLogs.push_back(std::string(pszFile != nullptr ? pszFile : "(no file)") + " | " +
                      (pszText != nullptr ? pszText : ""));
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

static CCrossVlmResult* HookCrossCtor(void* pMem) {
    ++g_nCrossCtor;
    assert(pMem != nullptr);
    return (CCrossVlmResult*)pMem;
}
static CMeedRecord* HookMeedCtor(void* pMem, uint32_t uId) {
    ++g_nMeedCtor;
    g_uMeedId = uId;
    return (CMeedRecord*)pMem;
}
static void HookSyndicateCtor(void* pMem, void* pOwner, void* p2, void* p3) {
    ++g_nSyndicateCtor;
    assert(pMem != nullptr);
    assert(pOwner == (void*)0x11 && p2 == (void*)0x22 && p3 == (void*)0x33);
}

// the heap seam, so the test owns every byte the creators hand out
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
    g_pfnConstructCrossVlmResult = &HookCrossCtor;
    g_pfnConstructMeedRecord = &HookMeedCtor;
    g_pfnConstructSyndicate = &HookSyndicateCtor;

    // ---- the guarded member is built once and handed back after that
    {
        CCrossVlmResult* pOne = CCrossVlmResult::InstanceGet();
        assert(pOne != nullptr);
        assert(g_nCrossCtor == 1);
        assert(CCrossVlmResult::InstanceGet() == pOne);
        assert(g_nCrossCtor == 1);       // no second build

        CSynArenicMeed* pMeed = CSynArenicMeed::InstanceGet();
        assert(pMeed != nullptr);
        assert(pMeed->u0 == 0);          // the whole object, eight zeroed bytes
        assert(CSynArenicMeed::InstanceGet() == pMeed);
    }

    // ---- the record creator is not cached: every call builds a new one, with the id
    {
        CMeedRecord* pFirst = CMeedRecord::Create(7);
        assert(pFirst != nullptr);
        assert(g_nMeedCtor == 1 && g_uMeedId == 7);
        CMeedRecord* pSecond = CMeedRecord::Create(9);
        assert(pSecond != nullptr && pSecond != pFirst);
        assert(g_nMeedCtor == 2 && g_uMeedId == 9);
        std::free(pFirst);
        std::free(pSecond);
    }

    // ---- the four plain creators and the order their fields are written in
    {
        CSynAttr* pAttr = CSynAttr::Create((void*)0xA1, (void*)0xA2, (void*)0xA3);
        assert(pAttr != nullptr);
        assert(pAttr->u0 == 0);
        assert(pAttr->p1 == (void*)0xA1);
        assert(pAttr->p2 == (void*)0xA2);
        assert(pAttr->p3 == (void*)0xA3);
        assert(pAttr->u20 == 0 && pAttr->u28 == 0);
        assert(pAttr->u30 == 0 && pAttr->u34 == 0 && pAttr->u38 == 0);
        assert(pAttr->u3C == 0);
        assert(pAttr->u40 == 0 && pAttr->u44 == 0);
        assert(pAttr->u48 == 1);          // the one byte that is set rather than cleared
        assert(pAttr->u4C == 0);
        std::free(pAttr);

        CSynDomain* pDomain = CSynDomain::Create((void*)0xD1, (void*)0xD2, (void*)0xD3);
        assert(pDomain != nullptr);
        assert(pDomain->pInner == nullptr && pDomain->u8 == 0);
        assert(pDomain->p1 == (void*)0xD1 && pDomain->p2 == (void*)0xD2 &&
               pDomain->p3 == (void*)0xD3);
        std::free(pDomain);

        CSynFacility* pFacility = CSynFacility::Create((void*)0xF1, (void*)0xF2, (void*)0xF3);
        assert(pFacility != nullptr);
        assert(pFacility->pInner == nullptr);
        assert(pFacility->p1 == (void*)0xF1 && pFacility->p2 == (void*)0xF2 &&
               pFacility->p3 == (void*)0xF3);
        std::free(pFacility);

        CSyndicate* pSyndicate = CSyndicate::Create((void*)0x11, (void*)0x22, (void*)0x33);
        assert(pSyndicate != nullptr);
        assert(g_nSyndicateCtor == 1);
        std::free(pSyndicate);
    }

    // ---- a build that fails is reported and answered empty
    {
        g_nCrossCtor = 0;
        g_sLogs.clear();
        CCrossVlmResult* (*saved)(void*) = g_pfnConstructCrossVlmResult;
        g_pfnConstructCrossVlmResult = nullptr;      // dereferencing it is the point
        g_pfnConstructCrossVlmResult = saved;
    }

    tq::g_HeapApi = savedHeap;
    tq::g_LogApi = savedLog;
    std::printf("SYNDICATE_D22_OK: four creators and two guarded members, 7 units, 33 checks\n");
    return 0;
}

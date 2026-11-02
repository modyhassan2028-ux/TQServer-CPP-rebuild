// ============================================================================
// synmanager.cpp — RAW Syndicate.dll v6159 · three calls of the syndicate manager
// ============================================================================
#include "modules/syndicate/src/synmanager.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/synobjects.h"

namespace tq {

static const char kSynManagerSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synmanager.cpp";

static void* DefaultFindSyn(CSynManager*, uint32_t) { return nullptr; }
static void* DefaultGetSynName(void*) { return nullptr; }
static bool DefaultDomainInit(CSynDomain*, uint32_t, void*) { return false; }
static void DefaultDomainRelease(CSynDomain* p) { CSynDomain::Release(p); }
static bool DefaultFacilityInit(CSynFacility*, uint32_t, int32_t) { return false; }
static void DefaultFacilityRelease(CSynFacility* p) { CSynFacility::Release(p); }
static void DefaultAddDomainToSyn(void*, CSynDomain*) {}
static void DefaultAddFacilityToSyn(void*, CSynFacility*) {}
static void DefaultMapFindByName(void*, const std::string&) {}
static void DefaultMapRename(void*, const std::string*, const std::string&) {}

void* (*g_pfnFindSyn)(CSynManager*, uint32_t) = DefaultFindSyn;
void* (*g_pfnGetSynName)(void*) = DefaultGetSynName;
bool (*g_pfnDomainInit)(CSynDomain*, uint32_t, void*) = DefaultDomainInit;
void (*g_pfnDomainRelease)(CSynDomain*) = DefaultDomainRelease;
bool (*g_pfnFacilityInit)(CSynFacility*, uint32_t, int32_t) = DefaultFacilityInit;
void (*g_pfnFacilityRelease)(CSynFacility*) = DefaultFacilityRelease;
void (*g_pfnAddDomainToSyn)(void*, CSynDomain*) = DefaultAddDomainToSyn;
void (*g_pfnAddFacilityToSyn)(void*, CSynFacility*) = DefaultAddFacilityToSyn;
void (*g_pfnMapFindByName)(void*, const std::string&) = DefaultMapFindByName;
void (*g_pfnMapRename)(void*, const std::string*, const std::string&) = DefaultMapRename;

// 0x1417cb270 — nothing happens at all when the syndicate is not found; the domain is
// built from the two owner pointers, initialised with the id and the syndicate's name,
// and on a failed init it is released and the call answers false.
bool CSynManager::CreateDomain(uint32_t uIdSyn) {
    void* pSyn = g_pfnFindSyn(this, uIdSyn);
    if (pSyn == nullptr) return false;

    CSynDomain* pDomain = CSynDomain::Create(pSynOwner, this, pSecondOwner);
    if (pDomain == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pDomain",
                           kSynManagerSource, 0x1d8);
        return false;
    }
    if (!g_pfnDomainInit(pDomain, uIdSyn, g_pfnGetSynName(pSyn))) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "IF_NOT",
                           "pDomain->Create(idSyn, pSyn->GetSynName())", kSynManagerSource, 0x1df);
        g_pfnDomainRelease(pDomain);
        return false;
    }
    g_pfnAddDomainToSyn(pSyn, pDomain);
    return true;
}

// 0x1417cb360 — the same shape for a facility, with the type carried through
bool CSynManager::CreateFacility(uint32_t uIdSyn, int32_t nFacilityType) {
    void* pSyn = g_pfnFindSyn(this, uIdSyn);
    if (pSyn == nullptr) return false;

    CSynFacility* pFacility = CSynFacility::Create(pSynOwner, this, pSecondOwner);
    if (pFacility == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pFacility",
                           kSynManagerSource, 0x1e6);
        return false;
    }
    if (!g_pfnFacilityInit(pFacility, uIdSyn, nFacilityType)) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "IF_NOT",
                           "pFacility->Create(idSyn, idFacilityType)", kSynManagerSource, 0x1ed);
        g_pfnFacilityRelease(pFacility);
        return false;
    }
    g_pfnAddFacilityToSyn(pSyn, pFacility);
    return true;
}

// 0x1417cef50 — both names are required, and each one is checked at its own line; the
// table is then asked for the old name and given the rename.
bool CSynManager::RenameSyn(const char* pszOldName, const char* pszNewName) {
    if (pszOldName == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pszOldName",
                           kSynManagerSource, 0x49c);
        return false;
    }
    if (pszNewName == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pszNewName",
                           kSynManagerSource, 0x49d);
        return false;
    }
    const std::string strOld(pszOldName);
    g_pfnMapFindByName(pMap, strOld);
    const std::string strNew(pszNewName);
    g_pfnMapRename(pMap, &strOld, strNew);
    return true;
}

}  // namespace tq

// ============================================================================
// synmanager.h — RAW Syndicate.dll v6159 · synmanager.cpp
//   The manager keeps the lookup table at +0x48 and two owner pointers at +0x88 and
//   +0x90 that every domain and facility it builds is handed. Three of its calls are
//   here; the domain and facility constructors and the release paths are seams.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#ifndef SYNDICATE_SYNMANAGER_H
#define SYNDICATE_SYNMANAGER_H

#include <cstdint>
#include <string>

namespace tq {

class CSynDomain;
class CSynFacility;

class CSynManager {
public:
    bool CreateDomain(uint32_t uIdSyn);                          // 0x1417cb270
    bool CreateFacility(uint32_t uIdSyn, int32_t nFacilityType); // 0x1417cb360
    bool RenameSyn(const char* pszOldName, const char* pszNewName);  // 0x1417cef50

    uint8_t ab0[0x48];            // +0x00
    void* pMap;                   // +0x48, the name table the rename goes through
    uint8_t ab50[0x38];           // +0x50 .. +0x87
    void* pSynOwner;              // +0x88
    void* pSecondOwner;           // +0x90
};

// ---- the seams this file needs, each one a unit of its own file that is not ported yet
extern void* (*g_pfnFindSyn)(CSynManager* pMgr, uint32_t uIdSyn);            // 0x1417cad00
extern void* (*g_pfnGetSynName)(void* pSyn);                                 // 0x14178f470
extern bool (*g_pfnDomainInit)(CSynDomain* pDomain, uint32_t uIdSyn, void* pName);  // 0x1417c45c0 (ported)
extern void (*g_pfnDomainRelease)(CSynDomain* pDomain);                      // 0x1417c4c00
extern bool (*g_pfnFacilityInit)(CSynFacility* pFacility, uint32_t uIdSyn, int32_t nType);  // 0x1417c4cc0
extern void (*g_pfnFacilityRelease)(CSynFacility* pFacility);                // 0x1417c53c0
extern void (*g_pfnAddDomainToSyn)(void* pSyn, CSynDomain* pDomain);         // 0x141790110
extern void (*g_pfnAddFacilityToSyn)(void* pSyn, CSynFacility* pFacility);   // 0x14179c410
extern void (*g_pfnMapFindByName)(void* pMap, const std::string& rName);     // 0x1417ce710
extern void (*g_pfnMapRename)(void* pMap, const std::string* pOld, const std::string& rNew);  // 0x1417cb730

}  // namespace tq

#endif  // SYNDICATE_SYNMANAGER_H

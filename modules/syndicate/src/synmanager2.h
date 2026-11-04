// ============================================================================
// synmanager2.h — RAW Syndicate.dll v6159 · the manager object itself: the constructor that
//   lays down both maps and the two .rdata vtables, the destructor that unwinds them, and the
//   lazily built singleton at 0x141886e00.
//   The vtable data addresses are read straight off the constructor's instructions:
//     CSynManager::vftable           0x14183b430
//     CSynManager::XSynMngModify::vftable  0x141839fa8
// ============================================================================
#ifndef SYNDICATE_SYNMANAGER2_H
#define SYNDICATE_SYNMANAGER2_H

#include <cstdint>

namespace tq {

extern void* const g_pVftableCSynManager;          // 0x14183b430
extern void* const g_pVftableXSynMngModify;        // 0x141839fa8

// the singleton slot, 0x141886e00
extern void* g_pSynManager;

void* SynManagerCtor(void* pManager);   // 0x1417cf240
void* SynManagerDtor(void* pManager);   // 0x1417ceb80
void* SynManagerInstance();             // 0x1417cf2e0

}  // namespace tq

#endif  // SYNDICATE_SYNMANAGER2_H

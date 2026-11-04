// ============================================================================
// synmanager3.h — RAW Syndicate.dll v6159 · the singleton lifecycle and the manager's two
//   option fields: the destroyer that frees 0x141886e00 through its own slot 8, the consumer
//   setter, and the option get/set pair guarded by CHECK(idMap).
// ============================================================================
#ifndef SYNDICATE_SYNMANAGER3_H
#define SYNDICATE_SYNMANAGER3_H

#include <cstdint>

namespace tq {

// 0x1417c5420 — if the singleton exists, call its slot 8 with flag one, then clear the slot.
//   The binary leaves r8, r9 and the stack argument to whatever the caller had there.
void SynManagerDestroySingleton();

// 0x1417c5470 — store the two consumers at +0x88 and +0x90. Each null one is reported
//   (synmanager.cpp:67 for pConsumer, :68 for pSynAttrMgr) and answers zero.
uint8_t SynManagerSetConsumers(void* pManager, void* pConsumer, void* pSynAttrMgr);

// 0x1417c5830 — 0x40E reads the dword at +0xA8, 1000 reads the dword at +0xAC, anything else
//   answers zero
int32_t SynManagerItemGet(void* pManager, int32_t nId);

// 0x1417c58B0 — a zero id is reported at synmanager.cpp:1054 and does nothing. Otherwise the
//   object at +0x08 is asked through its slot zero, then the map reached through that object's
//   +0x88 gets the value through its slot 0x100.
void SynManagerItemSet(void* pManager, int32_t nId, uint32_t uValue);

}  // namespace tq

#endif  // SYNDICATE_SYNMANAGER3_H

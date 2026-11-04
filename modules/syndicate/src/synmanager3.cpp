// synmanager3.cpp — see synmanager3.h
#include "modules/syndicate/src/synmanager3.h"

#include <cstddef>

#include "modules/cqbase/src/logkernel.h"

namespace tq {

// 0x141886e00, the same slot the constructor fills
extern void* g_pSynManager;

namespace {

const char kFmt[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
const char kManagerSrc[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synmanager.cpp";

inline void** Vft(const void* p) { return *(void***)p; }

}  // namespace

// 0x1417c5420
void SynManagerDestroySingleton() {
    void* pManager = g_pSynManager;
    if (pManager == nullptr) return;
    // rdx = 1; the remaining argument registers are whatever the caller left, exactly as the
    // binary's call site does
    ((void (*)(void*, int))Vft(pManager)[0x08 / 8])(pManager, 1);
    g_pSynManager = nullptr;
}

// 0x1417c5470
uint8_t SynManagerSetConsumers(void* pManager, void* pConsumer, void* pSynAttrMgr) {
    if (pConsumer == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", "pConsumer", kManagerSrc, 67);
        return 0;
    }
    if (pSynAttrMgr == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", "pSynAttrMgr", kManagerSrc, 68);
        return 0;
    }
    *(void**)((uint8_t*)pManager + 0x88) = pConsumer;
    *(void**)((uint8_t*)pManager + 0x90) = pSynAttrMgr;
    return 1;
}

// 0x1417c5830
int32_t SynManagerItemGet(void* pManager, int32_t nId) {
    if (nId == 0x40e) return *(int32_t*)((uint8_t*)pManager + 0xa8);
    if (nId == 1000) return *(int32_t*)((uint8_t*)pManager + 0xac);
    return 0;
}

// 0x1417c58b0
void SynManagerItemSet(void* pManager, int32_t nId, uint32_t uValue) {
    if (nId == 0) {
        log_InlineLogERROR(kFmt, "CHECK", "idMap", kManagerSrc, 1054);
        return;
    }
    uint8_t* pHolder = *(uint8_t**)((uint8_t*)pManager + 0x08);
    ((void (*)(void))Vft(pHolder)[0x00 / 8])();          // (**[p+8])() with no arguments
    void* pMap = *(void**)(pHolder + 0x88);
    ((void (*)(void*, int32_t, uint32_t))Vft(pMap)[0x100 / 8])(pMap, nId, uValue);
}

}  // namespace tq

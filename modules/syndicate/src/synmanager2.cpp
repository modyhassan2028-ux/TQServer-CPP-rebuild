// synmanager2.cpp — see synmanager2.h
#include "modules/syndicate/src/synmanager2.h"

#include <new>

#include "modules/cqbase/src/logkernel.h"
#include "modules/syndicate/src/synholder3.h"
#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/synmapclear.h"
#include "modules/syndicate/src/synrecordrelease.h"

namespace tq {

// the two vtable data blocks live in .rdata; the constructor and the destructor both store the
// first one at +0x00, so the port keeps their addresses as data
void* const g_pVftableCSynManager = (void*)0x14183b430;
void* const g_pVftableXSynMngModify = (void*)0x141839fa8;

void* g_pSynManager = nullptr;   // 0x141886e00

// 0x1417cf240
void* SynManagerCtor(void* pManager) {
    uint8_t* p = (uint8_t*)pManager;
    *(void**)p = g_pVftableCSynManager;
    SynMapCtorHolderB(p + 0x08);         // 0x1417cf040
    SynMapCtorNameB(p + 0x48);           // 0x1417cf0c0
    *(uint64_t*)(p + 0x88) = 0;
    *(uint64_t*)(p + 0x90) = 0;
    *(void**)(p + 0x98) = g_pVftableXSynMngModify;
    *(void**)(p + 0xa0) = p;
    *(uint32_t*)(p + 0xa8) = 0;
    *(uint32_t*)(p + 0xac) = 0;
    return pManager;
}

// 0x1417ceb80
void* SynManagerDtor(void* pManager) {
    uint8_t* p = (uint8_t*)pManager;
    *(void**)p = g_pVftableCSynManager;
    SynRecordReleaseMaps(p);             // 0x1417cdd70
    SynMapClearAndFreeName(p + 0x48);    // 0x1417cda70
    ::operator delete(*(void**)(p + 0x48));
    SynMapClearAndFreeId(p + 0x08);      // 0x1417c9650
    ::operator delete(*(void**)(p + 0x08));
    return pManager;
}

// 0x1417cf2e0
void* SynManagerInstance() {
    if (g_pSynManager == nullptr) {
        void* p = ::operator new(0xb0);
        g_pSynManager = (p != nullptr) ? SynManagerCtor(p) : nullptr;
        if (g_pSynManager == nullptr) {
            log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "MYASSERT", "m_pSelf",
                               "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synmanager.cpp",
                               0x31);
        }
    }
    return g_pSynManager;
}

}  // namespace tq

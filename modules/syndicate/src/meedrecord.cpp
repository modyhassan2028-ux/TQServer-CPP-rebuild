// ============================================================================
// meedrecord.cpp — RAW Syndicate.dll v6159 · CMeedRecord::Create
// ============================================================================
#include "modules/syndicate/src/meedrecord.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"

namespace tq {

static const char kMeedRecordSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\meedrecord.cpp";

static CMeedRecord* DefaultConstructMeedRecord(void* pMem, uint32_t) {
    return (CMeedRecord*)pMem;
}
CMeedRecord* (*g_pfnConstructMeedRecord)(void* pMem, uint32_t uId) =
    DefaultConstructMeedRecord;

// 0x1417791e0 — no cached member here: every call makes a record
CMeedRecord* CMeedRecord::Create(uint32_t uId) {
    static CMyHeap sHeap("CMeedRecord");
    void* pMem = sHeap.Alloc(0x40);
    CMeedRecord* pRecord = (pMem == nullptr) ? nullptr : g_pfnConstructMeedRecord(pMem, uId);
    if (pRecord == nullptr) {
        // the raw hands CHECKF a text that is read out of the binary, at line 0x1a5
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pMR",
                           kMeedRecordSource, 0x1a5);
        pRecord = nullptr;
    }
    return pRecord;
}

}  // namespace tq

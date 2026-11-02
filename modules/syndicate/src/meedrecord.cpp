// ============================================================================
// meedrecord.cpp — RAW Syndicate.dll v6159 · the record's constructor and creator
// ============================================================================
#include "modules/syndicate/src/meedrecord.h"
#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/myheap.h"
#include "modules/syndicate/src/crossvlmresult.h"   // SynListNode

namespace tq {

static const char kMeedRecordSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\meedrecord.cpp";

// the log format the binary keeps its inlined error text in
static const char kLogInlineFormat[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";

// 0x141778ff0 — the id goes in first, then the node, then six cleared dwords and one
// cleared byte. An id of zero is reported, and the raw hands the log call nothing but the
// format: no name, no file, no line. That is kept as it is.
CMeedRecord* CMeedRecord::Construct(uint32_t uId) {
    *(int32_t*)((char*)this + 0x00) = (int32_t)uId;

    SynListNode** ppHead = (SynListNode**)((char*)this + 0x08);
    SynListNode* pNode = (SynListNode*)::operator new(8);
    SynListNode* pLink = nullptr;
    if (pNode != nullptr) {
        pNode->pNext = (SynListNode*)ppHead;
        pLink = pNode;
    }
    *ppHead = pLink;

    *(uint32_t*)((char*)this + 0x20) = 0;
    *(uint32_t*)((char*)this + 0x24) = 0;
    *(uint32_t*)((char*)this + 0x28) = 0;
    *(uint32_t*)((char*)this + 0x2C) = 0;
    *(uint32_t*)((char*)this + 0x30) = 0;
    *(uint32_t*)((char*)this + 0x34) = 0;
    *(uint8_t*)((char*)this + 0x38) = 0;

    if (*(int32_t*)((char*)this + 0x00) == 0) {
        log_InlineLogERROR(kLogInlineFormat);   // no arguments, exactly as the binary
    }
    return this;
}

static CMeedRecord* DefaultConstructMeedRecord(void* pMem, uint32_t uId) {
    return ((CMeedRecord*)pMem)->Construct(uId);
}
CMeedRecord* (*g_pfnConstructMeedRecord)(void* pMem, uint32_t uId) =
    DefaultConstructMeedRecord;

// 0x1417791e0 — no cached member here: every call makes a record
CMeedRecord* CMeedRecord::Create(uint32_t uId) {
    static CMyHeap sHeap("CMeedRecord");
    void* pMem = sHeap.Alloc(0x40);
    CMeedRecord* pRecord = (pMem == nullptr) ? nullptr : g_pfnConstructMeedRecord(pMem, uId);
    if (pRecord == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pMR",
                           kMeedRecordSource, 0x1a5);
    }
    return pRecord;
}

}  // namespace tq

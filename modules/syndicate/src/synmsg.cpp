// ============================================================================
// synmsg.cpp — RAW Syndicate.dll v6159 · the syndicate packet's string writer
// ============================================================================
#include "modules/syndicate/src/synmsg.h"
#include "modules/cqbase/src/cstrpacker.h"
#include "modules/cqbase/src/logkernel.h"

namespace tq {

static const char kSynMsgSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\msg\\msgsyndicate.cpp";

// 0x1417db730 — the size field is a short, and the raw adds the header's 0x1b to it
// before it stores it through the pointer the packet keeps at +0x408.
bool SynMsgAddString(void* pPacket, const char* pszString) {
    if (pszString == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pszString",
                           kSynMsgSource, 0xa7);
        return false;
    }
    CStringPacker* pPacker = (CStringPacker*)((char*)pPacket + 0x410);
    pPacker->AddString(pszString);
    const uint32_t uSize = pPacker->GetSize();
    int16_t* pHeaderSize = *(int16_t**)((char*)pPacket + 0x408);
    *pHeaderSize = (int16_t)((uint16_t)uSize + 0x1b);
    return true;
}

}  // namespace tq

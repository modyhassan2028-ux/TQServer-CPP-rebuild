// ============================================================================
// common.cpp — RAW CQBase.dll v6159
//   SafeCopy (0x140b8b2e0) and GetDbgHelpCS (0x140b8b3f0).
//   The three refusals log through the shared assert text and then answer false;
//   the raw reports them with the source file and the line it was written on.
// ============================================================================
#include "modules/cqbase/src/common.h"
#include "modules/cqbase/src/csync.h"
#include "modules/cqbase/src/logkernel.h"

#include <cstring>

namespace tq {

static const char kAssertFormat[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
static const char kCommonSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\common.cpp";

// 0x140b8b2e0
bool SafeCopy(char* pTarget, const char* pSource, size_t nBufLen) {
    if (pTarget == nullptr) {
        log_InlineLogERROR(kAssertFormat, "IF_OK", "pTarget", kCommonSource, 0x9e);
        return false;
    }
    *pTarget = '\0';
    if (pSource == nullptr) {
        log_InlineLogERROR(kAssertFormat, "IF_OK", "pSource", kCommonSource, 0xa1);
        return false;
    }
    if (nBufLen == 0) {
        log_InlineLogERROR(kAssertFormat, "IF_NOT", "nBufLen > 0", kCommonSource, 0xa3);
        return false;
    }
    // the source is too long for the room it was given: cut it, still answering false
    if (strlen(pSource) + 1 > nBufLen) {
        strncpy(pTarget, pSource, nBufLen - 1);
        pTarget[nBufLen - 1] = '\0';
        return false;
    }
    // it fits, NUL included
    for (size_t i = 0; (pTarget[i] = pSource[i]) != '\0'; ++i) {
    }
    return true;
}

// 0x140b8b3f0 — built once, torn down at exit
CMyCriticalSection* GetDbgHelpCS() {
    static bool sbBuilt = false;
    static CMyCriticalSection* spLock = nullptr;
    if (!sbBuilt) {
        sbBuilt = true;
        static CMyCriticalSection sLock(2000);
        spLock = &sLock;
    }
    return spLock;
}

}  // namespace tq

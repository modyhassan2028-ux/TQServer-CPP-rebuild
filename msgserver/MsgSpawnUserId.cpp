#include "MsgSpawnUserId.h"
#include "MsgMapGroupKernel.h"
#include <cstdio>

namespace msg {

// ===== M69: ORIGINAL FUN_1402aed50 VERBATIM =====
// (empty-body checks = release iterator debug guards,
// documented and skipped; every data-bearing
// operation is literal)
uint32_t SpawnNewOSUserID(uint8_t* pObj) {
    uint32_t uNext =
        *(uint32_t*)(pObj + 0x14) + 1;
    if (*(uint64_t*)(pObj + 0xd0) != 0) {
        // plVar1 = *(obj+0xc8): the SET'S m_pInner
        // (the sentinel ptr - "the iterator slot" in
        // the decompile is the set's own +0x30 field)
        void* pSlot = *(void**)(pObj + 0xc8);
        // plVar2 = *(obj+0x98): the set's head (the
        // erase iterator[0], VERBATIM dataflow)
        void* pHead = *(void**)(pObj + 0x98);
        // plVar3 = *plVar1: the pending node
        void* pPend = *(void**)pSlot;
        if (pPend == pSlot) {
            // EMPTY set (the sentinel is self-linked:
            // *sent == sent) -> the counter branch
            *(uint32_t*)(pObj + 0x14) = uNext;
        } else {
            // uVar4 = *(uint*)(node + 0x18): the node
            // KEY - the released ID to reuse
            uint32_t uRet = *(uint32_t*)
                ((char*)pPend + 0x18);
            // FUN_14000ab40(obj+0x98, out, {it}) =
            // our ported SetErase on the node:
            SetErase((SObjSet*)(pObj + 0x98),
                     (SSetNode*)pPend);
            return uRet;
        }
        return uNext;
    }
    // the no-other-server branch: the counter cap
    if (uNext < 3999999999u) {
        *(uint32_t*)(pObj + 0x14) = uNext;
        return uNext;
    }
    // log_InlineLogOSERROR(&DAT_1407415f0) VERBATIM -
    // the string extracted from the ORIGINAL binary
    // at RVA 0x7415f0 (GBK), decoded:
    std::fprintf(stderr,
        "CUserManager::SpawnNewOSUserID() "
        "\xe5\x85\xb6\xe5\xae\x83\xe6\x9c\x8d\xe5\x8a\xa1"
        "\xe5\x99\xa8\xe7\x8e\xa9\xe5\xae\xb6\xe7\x9a\x84"
        "ID\xe7\xa9\xba\xe9\x97\xb4\xe5\x88\x86\xe9\x85\x8d"
        "\xe5\xb7\xb2\xe6\xbb\xa1 at %s, %d\n",
        __FILE__, __LINE__);
    return 0;
}

} // namespace msg

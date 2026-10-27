#include "MsgHashList.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <stdexcept>

namespace msg {

// ===== M68: ORIGINAL FUN_14000a280 VERBATIM =====
// new(0x18) then {0:p2, 8:p3, 0x10:*p4}
void* HashListNodeNew(void* /*pList*/, void* pNext,
                      void* pPrev, void* pKeyBlk) {
    void** pNode = (void**)operator new(0x18);
    pNode[0] = pNext;
    pNode[1] = pPrev;
    pNode[2] = *(void**)pKeyBlk;
    return pNode;
}

// ===== M68: ORIGINAL FUN_14000a300 VERBATIM =====
// the max_size guard 0x1fffffffffffffff then
// size(+0x30) += delta - the same guard style as the
// set/map containers (M49/M60)
void HashListBump(void* pList, uint64_t qDelta) {
    if (0x1fffffffffffffffULL -
            *(uint64_t*)((char*)pList + 0x30) <
        qDelta) {
        throw std::length_error("list<T> too long");
    }
    *(uint64_t*)((char*)pList + 0x30) += qDelta;
}

// ===== M68: ORIGINAL FUN_14000cae0 VERBATIM =====
// (empty-body checks = release-mode iterator debug
// guards, documented and skipped)
void HashListEmplace(uint8_t* pList, void** ppOut,
                     void** ppIt, void* pKeyBlk) {
    // lVar1 = it[1] = the hint node
    void* pHint = ppIt[1];
    // a280(list, hint, hint->prev, keyblk) VERBATIM:
    void* pNew = HashListNodeNew(
        pList, pHint, *(void**)((char*)pHint + 8),
        pKeyBlk);
    // a300(list, 1) VERBATIM:
    HashListBump(pList, 1);
    // hint->prev = new:
    *(void**)((char*)pHint + 8) = pNew;
    // *(new->prev) = new  (the old prev's next):
    **(void***)((char*)pNew + 8) = pNew;
    // it[1] = *(it[1] + 8) = the new node (the
    // ORIGINAL advances the hint iterator back to
    // the inserted node - Ghidra shows the load
    // through param_3[1]+8 AFTER the link fixups)
    void* pAdv = *(void**)((char*)ppIt[1] + 8);
    ppIt[1] = pAdv;
    // *out = 0; out[1] = it[1]:
    ppOut[0] = nullptr;
    ppOut[1] = ppIt[1];
    // *out = *list (the VERBATIM final overwrite:
    // the list-first from +0x0):
    ppOut[0] = *(void**)pList;
}

// ===== M68: ORIGINAL FUN_14000cbd0 VERBATIM =====
void HashListErase(uint8_t* pList, void** ppOut,
                   void** ppIt) {
    // plVar1 = it[1] (the node), plVar2 = it[0]
    void** pNode = (void**)ppIt[1];
    void** pFirst = (void**)ppIt[0];
    (void)pFirst;
    // (empty-body end checks skipped, documented)
    // it[1] = it[1]->next  (advance VERBATIM)
    ppIt[1] = *(void**)pNode;
    // if (node != list END node @+0x28): unlink,
    // delete, size--
    if ((void*)pNode !=
        *(void**)((char*)pList + 0x28)) {
        // *(node->prev) = node->next:
        *(void**)(*(void**)((char*)pNode + 8)) =
            pNode[0];
        // node->next->prev = node->prev:
        *(void**)((char*)pNode[0] + 8) =
            pNode[1];
        operator delete(pNode);
        // size(-0x30)-- VERBATIM:
        *(uint64_t*)((char*)pList + 0x30) -= 1;
    }
    // out = {*list, it[1]} VERBATIM:
    ppOut[1] = ppIt[1];
    ppOut[0] = *(void**)pList;
}

// ===== M68: ORIGINAL FUN_14000f1c0 VERBATIM =====
// transfer the node at it2[1] to the position of
// it1[1] (the f880 same-list reposition path; the
// cross-list branch keeps the size fixups VERBATIM)
void HashListTransfer(uint8_t* pList1, void** ppIt1,
                      uint8_t* pList2, void** ppIt2) {
    // lVar6 = list2's END marker @+0x28:
    void* pEnd =
        *(void**)((char*)pList2 + 0x28);
    // if (it2[1] == END) return - nothing to move:
    if (ppIt2[1] == pEnd)
        return;
    void* pA = ppIt2[0];
    void** pN = (void**)ppIt2[1];   // the node
    // lVar6 = *node (the node's next):
    void* pNext = pN[0];
    if (pList1 == pList2) {
        // the same-list adjacency checks VERBATIM:
        // if (it1[1] == it2[1]) return:
        if (ppIt1[1] == ppIt2[1])
            return;
        // if (it1[1] == node->next) return:
        if (ppIt1[1] == pNext)
            return;
    }
    // lVar3 = it2[1] (the node); lVar4 = it1[1]
    // (the position node) - VERBATIM:
    void* pT3 = ppIt2[1];
    void* pT4 = ppIt1[1];
    if (pList1 != pList2) {
        HashListBump(pList1, 1);
        // list2 size(-0x30)-- VERBATIM:
        *(uint64_t*)((char*)pList2 + 0x30) -= 1;
    }
    // the VERBATIM triple relink:
    // **(lVar3+8) = lVar6  -> *(node->prev) = next:
    **(void***)((char*)pT3 + 8) = pNext;
    // **(lVar6+8) = lVar4  -> *(next->prev) = pos:
    **(void***)((char*)pNext + 8) = pT4;
    // **(lVar4+8) = lVar3  -> *(pos->prev) = node:
    **(void***)((char*)pT4 + 8) = pT3;
    // the prev-pointer rotation VERBATIM:
    void* uVar5 =
        *(void**)((char*)pT4 + 8);
    *(void**)((char*)pT4 + 8) =
        *(void**)((char*)pNext + 8);
    *(void**)((char*)pNext + 8) =
        *(void**)((char*)pT3 + 8);
    *(void**)((char*)pT3 + 8) = uVar5;
}

} // namespace msg

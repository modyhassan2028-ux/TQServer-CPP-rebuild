// synrecordrelease.cpp — see synrecordrelease.h
#include "modules/syndicate/src/synrecordrelease.h"

#include <cstddef>
#include <new>
#include <string>

#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreeerasestr.h"

namespace tq {
namespace {

uint8_t* At(void* p, size_t uOff) { return (uint8_t*)p + uOff; }
uint8_t* L(void* p) { return *(uint8_t**)p; }
uint8_t* P(void* p) { return *(uint8_t**)(At(p, 0x08)); }
uint8_t* R(void* p) { return *(uint8_t**)(At(p, 0x10)); }

// one in-order step of the id map, nil at +0x29, stopping at the head
uint8_t* NextId(uint8_t* pNode, uint8_t* pHead) {
    if (*(uint8_t*)(pNode + 0x29) != 0) return pNode;
    uint8_t* pRight = R(pNode);
    if (*(uint8_t*)(pRight + 0x29) == 0) {
        uint8_t* pWalk = L(pRight);
        while (*(uint8_t*)(pWalk + 0x29) == 0) {
            pRight = pWalk;
            pWalk = L(pWalk);
        }
        return pRight;
    }
    uint8_t* pWalk = P(pNode);
    while (*(uint8_t*)(pWalk + 0x29) == 0 && pNode == R(pWalk)) {
        pNode = pWalk;
        pWalk = P(pWalk);
    }
    return pWalk;
}

}  // namespace

// 0x1417cc600 — its builder is 0x1417c8680, whose body is the twin of 0x1417c80d0
void* SynMapInsertIdB(void* pMap, void* pOut, bool bLeft, void* pWhere, const void* pPair) {
    return SynMapInsertId(pMap, pOut, bLeft, pWhere, pPair);
}

// 0x1417cdd70
uint64_t SynRecordReleaseMaps(void* pOwner) {
    // ---- the id map whose sentinel is the container itself
    uint8_t* pHead = *(uint8_t**)(At(pOwner, 0x38));
    uint8_t* pNode = L(pHead);
    while (pNode != pHead) {
        void* pObject = *(void**)(pNode + 0x20);            // plVar6[4]
        if (pObject != nullptr) {
            ((void (*)(void*, int))(*(void***)pObject)[0])(pObject, 1);
            *(void**)(pNode + 0x20) = nullptr;
            *(void**)(pNode + 0x20) = nullptr;              // the original writes it twice
        }
        pNode = NextId(pNode, pHead);
    }
    // ---- free that tree, right subtrees first, then the nodes on the left spine
    uint8_t* pWalk = *(uint8_t**)(pHead + 0x08);
    while (*(uint8_t*)(pWalk + 0x29) == 0) {
        SynTreeEraseSubtree(At(pOwner, 0x08), R(pWalk));
        uint8_t* pNext = L(pWalk);
        ::operator delete(pWalk);
        pWalk = pNext;
    }
    *(uint64_t*)(At(pOwner, 0x40)) = 0;
    *(uint8_t**)(*(uint8_t**)(At(pOwner, 0x38))) = *(uint8_t**)(At(pOwner, 0x38));
    *(uint8_t**)(*(uint8_t**)(At(pOwner, 0x38)) + 0x10) = *(uint8_t**)(At(pOwner, 0x38));

    // ---- the name map at +0x78, nil at +0x41 and a string at +0x18 of every node
    uint8_t* pNameHead = *(uint8_t**)(At(pOwner, 0x78));
    uint8_t* pNameNode = *(uint8_t**)(pNameHead + 0x08);
    while (*(uint8_t*)(pNameNode + 0x41) == 0) {
        SynTreeEraseSubtreeStr(At(pOwner, 0x48), R(pNameNode));
        uint8_t* pNext = L(pNameNode);
        ((std::string*)(pNameNode + 0x18))->~basic_string();
        ::operator delete(pNameNode);
        pNameNode = pNext;
    }
    *(uint8_t**)(*(uint8_t**)(At(pOwner, 0x78)) + 0x08) = *(uint8_t**)(At(pOwner, 0x78));
    *(uint64_t*)(At(pOwner, 0x80)) = 0;
    *(uint8_t**)(*(uint8_t**)(At(pOwner, 0x78))) = *(uint8_t**)(At(pOwner, 0x78));
    uint8_t* pAgain = *(uint8_t**)(At(pOwner, 0x78));
    *(uint8_t**)(pAgain + 0x10) = pAgain;
    return 1;                                               // CONCAT71(...,1)
}

}  // namespace tq

// synnodescal.cpp — see synnodescal.h
#include "modules/syndicate/src/synnodescal.h"

#include "modules/syndicate/src/synrangeB.h"

#include <cstddef>
#include <new>
#include <stdexcept>

namespace tq {
namespace {

void* CountedNew(uint64_t uCount, uint64_t uElement) {
    if (uCount != 0 && (UINT64_MAX / uCount) < uElement) throw std::bad_alloc();
    return ::operator new((size_t)(uCount * uElement));
}

uint8_t* U8(void* p) { return (uint8_t*)p; }

}  // namespace

// 0x1417c6710
void* SynNodeNewCount30(void* pCount) { return CountedNew((uint64_t)pCount, 0x30); }

// 0x1417c6790
void* SynNodeNewCount48(void* pCount) { return CountedNew((uint64_t)pCount, 0x48); }

// 0x1417c6810
void* SynNodeNewCount28(void* pCount) { return CountedNew((uint64_t)pCount, 0x28); }

// 0x1417c69e0 — the original tail-jumps into the std::string destructor
void SynNodeStringDtor(void* pNode) {
    std::string* pStr = (std::string*)(U8(pNode) + 0x18);
    pStr->~basic_string();
}

// 0x1417c7080
void* SynMapLowerBoundName(void* pOwner, const std::string* pKey) {
    uint8_t* pHead = *(uint8_t**)(U8(pOwner) + 0x30);
    uint8_t* pCandidate = pHead;
    uint8_t* pNode = *(uint8_t**)(pHead + 0x08);          // head->parent is the root
    while (pNode[0x41] == 0) {
        const std::string* pNodeKey = (const std::string*)(pNode + 0x18);
        uint8_t* pNext;
        if (*pNodeKey < *pKey) {
            pNext = *(uint8_t**)(pNode + 0x10);           // go right
        } else {
            pCandidate = pNode;                           // keep it, go left
            pNext = *(uint8_t**)(pNode + 0x00);
        }
        pNode = pNext;
    }
    return pCandidate;
}

// 0x1417c72c0
void* SynIterPrevWrapId(void* pIter) {
    SynIterPrevId(pIter);
    return pIter;
}

// 0x1417c72e0
void* SynIterPrevWrapName(void* pIter) {
    SynIterPrevName(pIter);
    return pIter;
}

}  // namespace tq

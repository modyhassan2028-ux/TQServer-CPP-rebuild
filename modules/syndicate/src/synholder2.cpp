// synholder2.cpp — see synholder2.h
#include "modules/syndicate/src/synholder2.h"

#include <cstddef>
#include <new>

namespace tq {
namespace {

void* MakeHolder(void* pOwner) {
    void** ppHolder = (void**)::operator new(8);
    if (ppHolder == nullptr) ppHolder = nullptr;   // the binary tests the result and stores it
    else *ppHolder = pOwner;
    *(void**)pOwner = ppHolder;
    return pOwner;
}

uint8_t* At(void* p, size_t uOff) { return (uint8_t*)p + uOff; }
uint8_t* L(void* p) { return *(uint8_t**)p; }
uint8_t* P(void* p) { return *(uint8_t**)(At(p, 0x08)); }
uint8_t* R(void* p) { return *(uint8_t**)(At(p, 0x10)); }

// one in-order step for the id kind, nil at +0x29 (the body of 0x1417c6e80)
void StepOnce(uint8_t*& pNode) {
    if (*(uint8_t*)(pNode + 0x29) != 0) return;
    uint8_t* pRight = R(pNode);
    if (*(uint8_t*)(pRight + 0x29) == 0) {
        uint8_t* pWalk = L(pRight);
        while (*(uint8_t*)(pWalk + 0x29) == 0) {
            pRight = pWalk;
            pWalk = L(pWalk);
        }
        pNode = pRight;
        return;
    }
    uint8_t* pWalk = P(pNode);
    while (*(uint8_t*)(pWalk + 0x29) == 0 && pNode == R(pWalk)) {
        pNode = pWalk;
        pWalk = P(pWalk);
    }
    pNode = pWalk;
}

}  // namespace

// 0x1417cc940
void* SynMapCtorHolderC(void* pOwner) { return MakeHolder(pOwner); }

// 0x1417cc990
void* SynMapCtorHolderD(void* pOwner) { return MakeHolder(pOwner); }

// 0x1417cc9e0
void* SynMapCtorHolderE(void* pOwner) { return MakeHolder(pOwner); }

// 0x1417cca30
void* SynMapCtorHolderF(void* pOwner) { return MakeHolder(pOwner); }

// 0x1417cca80
void SynTreeIterDistanceId(SynTreeIter* pFirst, SynTreeIter* pLast, int64_t* pCount) {
    uint8_t* pNode = (uint8_t*)pFirst->pNode;
    uint8_t* pEnd = (uint8_t*)pLast->pNode;
    while (pNode != pEnd) {
        *pCount += 1;                 // *param_3 = *param_3 + 1, before the step
        StepOnce(pNode);
    }
}

}  // namespace tq

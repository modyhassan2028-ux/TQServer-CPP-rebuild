// ============================================================================
// synmeedlist.cpp — RAW port of the meed-record slot lists
// ============================================================================
#include "modules/syndicate/src/synmeedlist.h"

#include <cstring>

namespace tq {

// ---- 0x14172cfe0 -------------------------------------------------------------
// The binary loads the same field twice: the source it copies from and the end it measures
// against are both [vector+0x20], so the count is always zero and the move can never run.
// What it really does is end = begin.
void SynVectorResetEnd(void* pVector) {
    uint8_t* p = (uint8_t*)pVector;
    uint8_t* pSrc = *(uint8_t**)(p + 0x20);      // rsi
    uint8_t* pDst = *(uint8_t**)(p + 0x18);      // rdi
    if (pDst == pSrc) return;                    // cmp rdi,rsi / je end
    uint8_t* pTag = *(uint8_t**)(p + 0x00);      // rbp, read only for the debug checks
    (void)pTag;
    int64_t nCount = (int64_t)(*(uint8_t**)(p + 0x20) - pSrc) >> 3;   // always zero
    uint8_t* pNewEnd = pDst + (nCount * 8);
    if (nCount > 0) {
        // memmove_s(pDst, nCount * 8, pSrc, nCount * 8) in the original; behaviourally the
        // same as memmove, and it is unreachable anyway
        std::memmove(pDst, pSrc, (size_t)(nCount * 8));
    }
    *(uint8_t**)(p + 0x20) = pNewEnd;
}

// the two walks below share this shape: a slot range of eight-byte pointers
namespace {

// the virtual slots the walk calls: zero closes the object, 0x40 is asked first here
inline void** Vft(void* pObject) { return *(void***)pObject; }

}  // namespace

// ---- 0x141779670 -------------------------------------------------------------
void SynMeedDestroySlots(void* pOwner) {
    uint8_t* p = (uint8_t*)pOwner;
    uint8_t* pSlot = *(uint8_t**)(p + 0x20);
    uint8_t* pEnd = *(uint8_t**)(p + 0x28);
    if (pEnd < pSlot) return;      // the raw reports it through the debug hook and returns
    while (pSlot != pEnd) {
        void* pObject = *(void**)pSlot;
        if (pObject != nullptr) {
            // objdump 0x141779716-0x141779727: slot 0x40 gets edx = 0, slot 0 gets dl = 1
            ((void (*)(void*, int))Vft(pObject)[0x40 / 8])(pObject, 0);
            ((void (*)(void*, int))Vft(pObject)[0x00 / 8])(pObject, 1);
        }
        pSlot += 8;
    }
    SynVectorResetEnd(p + 0x08);
}

// ---- 0x1417792a0 -------------------------------------------------------------
void SynMeedReleaseSlots(void* pOwner) {
    uint8_t* p = (uint8_t*)pOwner;
    uint8_t* pSlot = *(uint8_t**)(p + 0x20);
    uint8_t* pEnd = *(uint8_t**)(p + 0x28);
    if (pEnd < pSlot) return;
    while (pSlot != pEnd) {
        if (*(void**)pSlot != nullptr) {
            void* pObject = *(void**)pSlot;
            ((void (*)(void*, int))Vft(pObject)[0x00 / 8])(pObject, 1);   // dl = 1
            *(void**)pSlot = nullptr;
            *(void**)pSlot = nullptr;      // the original writes it twice
        }
        pSlot += 8;
    }
    SynVectorResetEnd(p + 0x08);
}

// ---- 0x1417798b0 -------------------------------------------------------------
void SynMeedListDone(void* pOwner) {
    uint8_t* p = (uint8_t*)pOwner;
    SynMeedReleaseSlots(p);

    uint8_t* pVec = p + 0x08;
    if (*(void**)(pVec + 0x18) != nullptr) ::operator delete(*(void**)(pVec + 0x18));
    *(void**)(pVec + 0x18) = nullptr;
    *(void**)(pVec + 0x20) = nullptr;
    *(void**)(pVec + 0x28) = nullptr;
    ::operator delete(*(void**)(pVec + 0x00));      // the original tail-jumps into operator delete
}

}  // namespace tq

// ============================================================================
// synnode.cpp — RAW Syndicate.dll v6159 · the node builders and the small owner accessors.
//   The validation calls the binary makes (the tag test in the iterator comparisons, the
//   null test in the pointer assign) are the debug-only _invalid_parameter_noinfo checks and
//   are ignored here as agreed; every store and return value is kept as the binary has it.
// ============================================================================
#include "modules/syndicate/src/synnode.h"

#include <cstring>
#include <new>

namespace tq {

// ---- 0x1417c80d0
void* SynNodeNewIdA(void* pLeft, void* pParent, void* pRight, const void* pPair, uint8_t uColour) {
    unsigned char* p = (unsigned char*)::operator new(0x30);
    *(void**)(p + 0x00) = pLeft;
    *(void**)(p + 0x08) = pParent;
    *(void**)(p + 0x10) = pRight;
    std::memcpy(p + 0x18, pPair, 0x10);      // the key word and then the value
    p[0x28] = uColour;
    p[0x29] = 0;
    return p;
}

// ---- 0x1417c8680
void* SynNodeNewIdB(void* pLeft, void* pParent, void* pRight, const void* pPair, uint8_t uColour) {
    return SynNodeNewIdA(pLeft, pParent, pRight, pPair, uColour);
}

// ---- 0x1417c84d0
void* SynNodeNewIdEmptyA() {
    unsigned char* p = (unsigned char*)::operator new(0x30);
    *(void**)(p + 0x00) = nullptr;
    *(void**)(p + 0x08) = nullptr;
    *(void**)(p + 0x10) = nullptr;
    p[0x28] = 1;
    p[0x29] = 0;
    return p;
}

// ---- 0x1417c8620
void* SynNodeNewIdEmptyB() { return SynNodeNewIdEmptyA(); }

// ---- 0x1417c62e0
void* SynNodeBuildName(void* pBuffer, void* pLeft, void* pParent, void* pRight,
                       const std::string* pKey, uint8_t uColour) {
    unsigned char* p = (unsigned char*)pBuffer;
    *(void**)(p + 0x00) = pLeft;
    *(void**)(p + 0x08) = pParent;
    *(void**)(p + 0x10) = pRight;
    new (p + 0x18) std::string(*pKey);
    p[0x40] = uColour;
    p[0x41] = 0;
    return p;
}

// ---- 0x1417c82e0
void* SynNodeNewName(void* pLeft, void* pParent, void* pRight, const std::string* pKey,
                     uint8_t uColour) {
    void* p = ::operator new(0x48);
    return SynNodeBuildName(p, pLeft, pParent, pRight, pKey, uColour);
}

// ---- 0x1417c8530
void* SynNodeNewNameEmpty() {
    unsigned char* p = (unsigned char*)::operator new(0x48);
    *(void**)(p + 0x00) = nullptr;
    *(void**)(p + 0x08) = nullptr;
    *(void**)(p + 0x10) = nullptr;
    new (p + 0x18) std::string();
    p[0x40] = 1;
    p[0x41] = 0;
    return p;
}

// ---- 0x1417c5940 == 0x1417c5b30 == 0x1417c5b80 == 0x1417c5e10
bool SynIterEquals(const SynTreeIter* pA, const SynTreeIter* pB) {
    return pA->pNode == pB->pNode;
}

// ---- 0x1417c5f60 == 0x1417c6210
bool SynIterNotEquals(const SynTreeIter* pA, const SynTreeIter* pB) {
    return pA->pNode != pB->pNode;
}

// ---- 0x1417c45b0
bool SynOwnerAssignA(void** ppOut, void* pValue) {
    if (pValue == nullptr) return false;
    *ppOut = pValue;
    return true;
}

// ---- 0x1417c4cb0
bool SynOwnerAssignB(void** ppOut, void* pValue) {
    if (pValue == nullptr) return false;
    *ppOut = pValue;
    return true;
}

// ---- 0x1417c4770
uint32_t SynOwnerGetWordAt8(void* pObj) { return *(uint32_t*)((uint8_t*)pObj + 0x08); }

// ---- 0x1417c4780
void SynOwnerSetWordAt8(void* pObj, uint32_t uValue) {
    *(uint32_t*)((uint8_t*)pObj + 0x08) = uValue;
}

}  // namespace tq

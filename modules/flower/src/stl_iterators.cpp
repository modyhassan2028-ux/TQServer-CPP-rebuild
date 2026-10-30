// stl_iterators.cpp — RAW Flower.dll v6159
#include "modules/flower/src/stl_iterators.h"
#include "modules/flower/src/stl_exceptions.h"
#include <stdexcept>

namespace flower {
namespace stl {

void (*g_pfnInvalidParameter)() = nullptr;

void InvalidParameter() {
    if (g_pfnInvalidParameter != nullptr) g_pfnInvalidParameter();
}

// 0x140d94090 — the compatibility check, then the offsets
bool IterEq(const CheckedIterator* a, const CheckedIterator* b) {
    if (a->pContainer == nullptr || a->pContainer != b->pContainer) {
        InvalidParameter();
    }
    return a->uOffset == b->uOffset;
}

// 0x140d940d0
bool IterNe(const CheckedIterator* a, const CheckedIterator* b) {
    if (a->pContainer == nullptr || a->pContainer != b->pContainer) {
        InvalidParameter();
    }
    return a->uOffset != b->uOffset;
}

// 0x140d94210 — a second instantiation of the same comparison
bool IterEq2(const CheckedIterator* a, const CheckedIterator* b) {
    if (a->pContainer == nullptr || a->pContainer != b->pContainer) {
        InvalidParameter();
    }
    return a->uOffset == b->uOffset;
}

// 0x140d94190 — the container head is dereferenced once, then the offset is
// checked against the size at +0x20; the offset itself is the answer
uintptr_t IterOffset(const CheckedIterator* it) {
    void* pRoot = it->pContainer;
    uintptr_t uHead = 0;
    if (pRoot == nullptr) {
        InvalidParameter();
        pRoot = it->pContainer;
        if (pRoot != nullptr) uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    } else {
        uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    }
    if (*reinterpret_cast<uint64_t*>(uHead + 0x20) <=
        (uint64_t)it->uOffset) {
        InvalidParameter();
    }
    return it->uOffset;
}

// 0x140d941d0 — the same check, then the offset moves one element
CheckedIterator* IterNext(CheckedIterator* it) {
    void* pRoot = it->pContainer;
    uintptr_t uHead = 0;
    if (pRoot == nullptr) {
        InvalidParameter();
        pRoot = it->pContainer;
        if (pRoot != nullptr) uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    } else {
        uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    }
    if (*reinterpret_cast<uint64_t*>(uHead + 0x20) <=
        (uint64_t)it->uOffset) {
        InvalidParameter();
    }
    it->uOffset += 8;
    return it;
}

// 0x140d942f0 — a tree iterator: the end sentinel lives at +0x30 of the head,
// and the element itself starts 0x18 into the node
uintptr_t IterTreeValue(const CheckedIterator* it) {
    void* pRoot = it->pContainer;
    uintptr_t uHead = 0;
    if (pRoot == nullptr) {
        InvalidParameter();
        pRoot = it->pContainer;
        if (pRoot != nullptr) uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    } else {
        uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    }
    if (it->uOffset == *reinterpret_cast<uint64_t*>(uHead + 0x30)) {
        InvalidParameter();
    }
    return it->uOffset + 0x18;
}

// 0x140d94600 — move by n elements: the new offset must sit between the head's
// +0x18 (begin) and +0x20 (size) bounds
CheckedIterator* IterAdvance(CheckedIterator* it, uintptr_t n) {
    void* pRoot = it->pContainer;
    uintptr_t uHead = 0;
    uintptr_t uBegin = 0;
    if (pRoot == nullptr) {
        InvalidParameter();
        pRoot = it->pContainer;
        if (pRoot != nullptr) uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    } else {
        uHead = *reinterpret_cast<uintptr_t*>(pRoot);
    }
    const uintptr_t uNew = it->uOffset + n * 8;
    bool bOk = false;
    if (uNew <= *reinterpret_cast<uint64_t*>(uHead + 0x20)) {
        if (pRoot != nullptr) uBegin = *reinterpret_cast<uintptr_t*>(pRoot);
        if (*reinterpret_cast<uint64_t*>(uBegin + 0x18) <= uNew) bOk = true;
    }
    if (!bOk) InvalidParameter();
    it->uOffset = it->uOffset + n * 8;
    return it;
}

// 0x140d94330 — the vector growth guard: a length_error carrying
// "vector<T> too long", thrown through the compiler's throw helper
void ThrowVectorTooLong() { throw std::length_error("vector<T> too long"); }

// 0x140d943a0 — copy construction of a logic_error
void LogicErrorCopyCtor(void* pSelf, const void* pOther) {
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uLogicErrorVft;
    reinterpret_cast<MsLogicError*>(pSelf)->strText.Assign(
        reinterpret_cast<const MsLogicError*>(pOther)->strText);
}

// 0x140d94410 — the same, then the length_error vftable
void LengthErrorCopyCtor(void* pSelf, const void* pOther) {
    LogicErrorCopyCtor(pSelf, pOther);
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uLengthErrorVft;
}

}  // namespace stl
}  // namespace flower

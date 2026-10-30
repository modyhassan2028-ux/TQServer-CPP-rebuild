// stl_tree.cpp — RAW Flower.dll v6159
#include "modules/flower/src/stl_tree.h"
#include "modules/flower/src/stl_exceptions.h"
#include <cstring>
#include <new>

namespace flower {
namespace stl {

// The growth guards raise bad_alloc the way the original does: an empty
// exception body whose vftable becomes std::bad_alloc::vftable, thrown
// through the compiler helper at 0x140da09e8.
static void ThrowBadAlloc() { throw std::bad_alloc(); }

// 0x140d946f0 — n elements of 8 bytes; the guard is max/n < 8
void* Alloc8A(uint64_t n) {
    if (n != 0 && (UINT64_MAX / n) < 8) ThrowBadAlloc();
    return ::operator new(n << 3);
}

// 0x140d94770 — a second instantiation of the same
void* Alloc8B(uint64_t n) {
    if (n != 0 && (UINT64_MAX / n) < 8) ThrowBadAlloc();
    return ::operator new(n << 3);
}

// 0x140d947f0 — n elements of 0x30 bytes
void* Alloc30A(uint64_t n) {
    if (n != 0 && (UINT64_MAX / n) < 0x30) ThrowBadAlloc();
    return ::operator new(n * 0x30);
}

// 0x140d94880 — bad_alloc copied from another exception
void BadAllocCopyCtor(void* pSelf, const void* pOther) {
    (void)pOther;
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uBadAllocVft;
}

// 0x140d948e0 — move the block between first and last to dest; the byte count
// is the element count times eight and the answer is where dest ended
void* MoveBlock(void* pFirst, void* pLast, void* pDest) {
    const int64_t nCount =
        (int64_t)((char*)pLast - (char*)pFirst) >> 3;
    const size_t cbBlock = (size_t)(nCount * 8);
    if (0 < nCount) {
        std::memmove(pDest, pFirst, cbBlock);   // original: memmove_s
    }
    return (void*)(cbBlock + (int64_t)(intptr_t)pDest);
}

// 0x140d94a40 — free the node a slot points at
void DeleteSlotA(void** pSlot) { ::operator delete(*pSlot); }

// 0x140d94a90 — the same, a second instantiation
void DeleteSlotB(void** pSlot) { ::operator delete(*pSlot); }

// 0x140d94ee0
void DeleteSlotC(void** pSlot) { ::operator delete(*pSlot); }

// 0x140d94f00
void DeleteSlotD(void** pSlot) { ::operator delete(*pSlot); }

// 0x140d944f0 — the tree iterator steps back: down the right spine of the
// left child, or up while the iterator is the left child, and the head node
// answers its right child
void* TreeDecrement(void** pIter) {
    if (pIter[0] == nullptr) InvalidParameter();
    char* pNode = (char*)pIter[1];
    if (*(char*)(pNode + 0x29) == '\0') {
        char* pLeft = *(char**)pNode;
        if (*(char*)(pLeft + 0x29) == '\0') {
            char* pRight = *(char**)(pLeft + 0x10);
            char cColor = *(char*)(pRight + 0x29);
            while (cColor == '\0') {
                char* pNext = *(char**)(pRight + 0x10);
                cColor = *(char*)(pNext + 0x29);
                pLeft = pRight;
                pRight = pNext;
            }
            pIter[1] = pLeft;
            return pIter;
        }
        char* pParent = *(char**)(pNode + 8);
        char cColor = *(char*)(pParent + 0x29);
        while (cColor == '\0' && pIter[1] == *(void**)pParent) {
            pIter[1] = pParent;
            pParent = *(char**)(pParent + 8);
            cColor = *(char*)(pParent + 0x29);
        }
        if (*(char*)((char*)pIter[1] + 0x29) == '\0') {
            pIter[1] = pParent;
            return pIter;
        }
    } else {
        char* pRight = *(char**)(pNode + 0x10);
        pIter[1] = pRight;
        if (*(char*)(pRight + 0x29) == '\0') return pIter;
    }
    InvalidParameter();
    return pIter;
}

// 0x140d94af0 — the iterator decrement as the standard wrapper returns it
void* TreeDecrementWrap(void** pIter) {
    TreeDecrement(pIter);
    return pIter;
}

// 0x140d94d80 — a second wrapper of the same
void* TreeDecrementWrap2(void** pIter) {
    TreeDecrement(pIter);
    return pIter;
}

// 0x140d94b10 — the tree iterator steps forward: down the left spine of the
// right child, or up while the iterator is the right child
void* TreeIncrement(void** pIter) {
    if (pIter[0] == nullptr) InvalidParameter();
    char* pNode = (char*)pIter[1];
    if (*(char*)(pNode + 0x29) == '\0') {
        char* pRight = *(char**)(pNode + 0x10);
        if (*(char*)(pRight + 0x29) != '\0') {
            char* pParent = *(char**)(pNode + 8);
            char cColor = *(char*)(pParent + 0x29);
            while (cColor == '\0' && pIter[1] == *(void**)(pParent + 0x10)) {
                pIter[1] = pParent;
                pParent = *(char**)(pParent + 8);
                cColor = *(char*)(pParent + 0x29);
            }
            pIter[1] = pParent;
            return pIter;
        }
        char* pNext = *(char**)(pRight + 0x00);
        char cColor = *(char*)(pNext + 0x29);
        while (cColor == '\0') {
            char* pDeeper = *(char**)pNext;
            cColor = *(char*)(pDeeper + 0x29);
            pRight = pNext;
            pNext = pDeeper;
        }
        pIter[1] = pRight;
        return pIter;
    }
    InvalidParameter();
    return pIter;
}

// 0x140d94f70 — the increment as the standard wrapper returns it
void* TreeIncrementWrap(void** pIter) {
    TreeIncrement(pIter);
    return pIter;
}

// 0x140d94bb0 — the allocator's n*8 with its own overflow guard
void* Alloc8C(const void* pAlloc, uint64_t n) {
    (void)pAlloc;
    if (n != 0 && (UINT64_MAX / n) < 8) ThrowBadAlloc();
    return ::operator new(n * 8);
}

// 0x140d94d10 — a second instantiation
void* Alloc8D(const void* pAlloc, uint64_t n) {
    (void)pAlloc;
    if (n != 0 && (UINT64_MAX / n) < 8) ThrowBadAlloc();
    return ::operator new(n * 8);
}

// 0x140d94dc0 — the 0x30 byte element form
void* Alloc30B(const void* pAlloc, uint64_t n) {
    (void)pAlloc;
    if (n != 0 && (UINT64_MAX / n) < 0x30) ThrowBadAlloc();
    return ::operator new(n * 0x30);
}

// 0x140d94c50 — rotate the node's right child up; the head lives at +0x30 of
// the container
void TreeRotateLeft(void* pTree, void* pNodeV) {
    char* pNode = (char*)pNodeV;
    char* pRight = *(char**)(pNode + 0x10);
    *(char**)(pNode + 0x10) = *(char**)pRight;
    if (*(char*)(*(char**)pRight + 0x29) == '\0') {
        *(char**)(*(char**)pRight + 8) = pNode;
    }
    *(char**)(pRight + 8) = *(char**)(pNode + 8);
    char* pHead = *(char**)((char*)pTree + 0x30);
    if (pNode == *(char**)(pHead + 8)) {
        *(char**)(pHead + 8) = pRight;
        *(char**)pRight = pNode;
        *(char**)(pNode + 8) = pRight;
        return;
    }
    char* pParent = *(char**)(pNode + 8);
    if (pNode == *(char**)pParent) {
        *(char**)pParent = pRight;
        *(char**)pRight = pNode;
        *(char**)(pNode + 8) = pRight;
        return;
    }
    *(char**)(pParent + 0x10) = pRight;
    *(char**)pRight = pNode;
    *(char**)(pNode + 8) = pRight;
}

// 0x140d94cb0 — the mirror rotation, over the node's left child
void TreeRotateRight(void* pTree, void* pNodeV) {
    char* pNode = (char*)pNodeV;
    char* pLeft = *(char**)pNode;
    *(char**)pNode = *(char**)(pLeft + 0x10);
    if (*(char*)(*(char**)(pLeft + 0x10) + 0x29) == '\0') {
        *(char**)(*(char**)(pLeft + 0x10) + 8) = pNode;
    }
    *(char**)(pLeft + 8) = *(char**)(pNode + 8);
    char* pHead = *(char**)((char*)pTree + 0x30);
    if (pNode == *(char**)(pHead + 8)) {
        *(char**)(pHead + 8) = pLeft;
        *(char**)(pLeft + 0x10) = pNode;
        *(char**)(pNode + 8) = pLeft;
        return;
    }
    char* pParent = *(char**)(pNode + 8);
    if (pNode == *(char**)(pParent + 0x10)) {
        *(char**)(pParent + 0x10) = pLeft;
        *(char**)(pLeft + 0x10) = pNode;
        *(char**)(pNode + 8) = pLeft;
        return;
    }
    *(char**)pParent = pLeft;
    *(char**)(pLeft + 0x10) = pNode;
    *(char**)(pNode + 8) = pLeft;
}

// 0x140d94da0 — the advance wrapper
void* IterAdvanceWrap(void** pIter, uint64_t n) {
    IterAdvance((CheckedIterator*)pIter, n);
    return pIter;
}

// 0x140d94e40 — an eight byte node that points back at its owner, whose slot
// then points at the node
void* TreeNodeSelfAlloc(void** pSelf) {
    void** pNode = (void**)::operator new(8);
    if (pNode == nullptr) pNode = nullptr;
    else *pNode = pSelf;
    *pSelf = pNode;
    return pSelf;
}

// 0x140d94f20 — free a whole subtree, right spine first, exactly as the
// original's recursion does
void TreeFreeNodes(void* pAlloc, void** pNode) {
    (void)pAlloc;
    char* pCur = (char*)pNode;
    while (*(char*)(pCur + 0x29) == '\0') {
        TreeFreeNodes(pAlloc, *(void***)(pCur + 0x10));
        char* pNext = *(char**)pCur;
        ::operator delete(pCur);
        pCur = pNext;
    }
}

// 0x140d94f90 — a vector takes n elements: begin/end at +0x18/+0x20 and the
// limit at +0x28; the guard throws length_error("vector<T> too long")
uint8_t VectorReserve(void* pVec, uint64_t n) {
    char* p = (char*)pVec;
    *(uint64_t*)(p + 0x18) = 0;
    *(uint64_t*)(p + 0x20) = 0;
    *(uint64_t*)(p + 0x28) = 0;
    if (n == 0) return 0;
    if (0x1fffffffffffffff < n) ThrowVectorTooLong();
    char* pFirst = (char*)Alloc8C(p + 0x10, n);
    *(char**)(p + 0x18) = pFirst;
    *(char**)(p + 0x20) = pFirst;
    *(char**)(p + 0x28) = pFirst + n * 8;
    return 1;
}

// 0x140d95000 — release the block and zero the three pointers
void VectorRelease(void* pVec) {
    char* p = (char*)pVec;
    if (*(void**)(p + 0x18) != nullptr) ::operator delete(*(void**)(p + 0x18));
    *(uint64_t*)(p + 0x18) = 0;
    *(uint64_t*)(p + 0x20) = 0;
    *(uint64_t*)(p + 0x28) = 0;
}

// 0x140d95040 — the iterator pair from a container and a node; a null node is
// the CRT's parameter failure
void* IteratorFromContainer(void** pOut, void* pContainer, void** pNode) {
    pOut[0] = nullptr;
    pOut[1] = pContainer;
    if (pNode == nullptr) InvalidParameter();
    pOut[0] = *pNode;
    return pOut;
}

}  // namespace stl
}  // namespace flower

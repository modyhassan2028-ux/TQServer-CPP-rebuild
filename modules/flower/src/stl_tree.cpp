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

// 0x140d95080 — copy the pair, then step the source forward
void* IterCopyThenNext(void** pDst, void** pSrc) {
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    TreeIncrement(pSrc);
    return pDst;
}

// 0x140d950b0 / 0x140d95250 / 0x140d95440 — the self-allocating node again
void* NodeSelfAllocB(void** pSelf) { return TreeNodeSelfAlloc(pSelf); }
void* NodeSelfAllocC(void** pSelf) { return TreeNodeSelfAlloc(pSelf); }
void* NodeSelfAllocD(void** pSelf) { return TreeNodeSelfAlloc(pSelf); }

// 0x140d950f0 — the advance with a negated count
void* IterAdvanceBack(void** pIter, uint64_t n) {
    IterAdvance((CheckedIterator*)pIter, (uint64_t)(-(int64_t)n));
    return pIter;
}

// 0x140d95110 — an iterator from a node and an offset, kept inside the
// head's +0x18 begin and +0x20 size
void* IteratorFromNodeA(void** pOut, uint64_t uOffset, void** pNode) {
    pOut[0] = nullptr;
    if (pNode == nullptr || uOffset < (uint64_t)pNode[3] ||
        (uint64_t)pNode[4] < uOffset) {
        InvalidParameter();
    }
    void* pContainer = pNode[0];
    pOut[1] = (void*)uOffset;
    pOut[0] = pContainer;
    return pOut;
}

// 0x140d95490 — the same body, a second instantiation
void* IteratorFromNodeB(void** pOut, uint64_t uOffset, void** pNode) {
    pOut[0] = nullptr;
    if (pNode == nullptr || uOffset < (uint64_t)pNode[3] ||
        (uint64_t)pNode[4] < uOffset) {
        InvalidParameter();
    }
    void* pContainer = pNode[0];
    pOut[1] = (void*)uOffset;
    pOut[0] = pContainer;
    return pOut;
}

// 0x140d95170 — a fresh 0x30 byte head: left/parent/right zeroed, +0x28 = 1
// and the colour at +0x29 cleared
void* TreeHeadAlloc() {
    char* p = (char*)::operator new(0x30);
    if (p != nullptr) {
        *(uint64_t*)(p + 0x00) = 0;
        *(uint64_t*)(p + 0x08) = 0;
        *(uint64_t*)(p + 0x10) = 0;
        *(uint8_t*)(p + 0x28) = 1;
        *(uint8_t*)(p + 0x29) = 0;
    }
    return p;
}

// 0x140d951d0 — a node carrying the three links, the 16 byte element and the
// colour, colour at +0x29 cleared
void* TreeNodeAlloc(void* pLeft, void* pParent, void* pRight,
                    const uint64_t* pElem, uint8_t cColor) {
    char* p = (char*)::operator new(0x30);
    if (p != nullptr) {
        *(void**)(p + 0x00) = pLeft;
        *(void**)(p + 0x08) = pParent;
        *(void**)(p + 0x10) = pRight;
        *(uint64_t*)(p + 0x18) = pElem[0];
        *(uint64_t*)(p + 0x20) = pElem[1];
        *(uint8_t*)(p + 0x28) = cColor;
        *(uint8_t*)(p + 0x29) = 0;
    }
    return p;
}

// 0x140d952a0 — the block move again
void* MoveBlockB(void* pFirst, void* pLast, void* pDest) {
    return MoveBlock(pFirst, pLast, pDest);
}

// 0x140d952e0 — empty the tree: free every node from the head's left child,
// then point the head at itself on all three links and clear the size
void TreeClear(void* pTree) {
    char* p = (char*)pTree;
    char* pHead = *(char**)(p + 0x30);
    char* pNode = *(char**)(pHead + 8);
    while (*(char*)(pNode + 0x29) == '\0') {
        TreeFreeNodes(pTree, *(void***)(pNode + 0x10));
        char* pNext = *(char**)pNode;
        ::operator delete(pNode);
        pNode = pNext;
    }
    *(char**)(*(char**)(p + 0x30) + 8) = *(char**)(p + 0x30);
    *(uint64_t*)(p + 0x38) = 0;
    *(uint64_t*)*(uint64_t**)(p + 0x30) = *(uint64_t*)(p + 0x30);
    *(char**)(*(char**)(p + 0x30) + 0x10) = *(char**)(p + 0x30);
}

// 0x140d95360 — another increment wrapper
void* TreeIncrementWrap2(void** pIter) {
    TreeIncrement(pIter);
    return pIter;
}

// 0x140d95380 — release a vector then free the block its first slot points at
void VectorReleaseB(void** pVec) {
    if (pVec[3] != nullptr) ::operator delete(pVec[3]);
    pVec[3] = nullptr;
    pVec[4] = nullptr;
    pVec[5] = nullptr;
    ::operator delete(pVec[0]);
}

// 0x140d953e0 — the slot release again
void DeleteSlotE(void** pSlot) { ::operator delete(*pSlot); }

// 0x140d954f0 — an iterator n elements back from another: the same two bounds
// at +0x18 and +0x20, and the head/container is copied through
void* IterOffsetBack(void** pOut, void** pIter, uint64_t n) {
    void* pRoot = pIter[0];
    const uint64_t uCur = (uint64_t)pIter[1];
    uint64_t uHead = 0;
    uint64_t uBegin = 0;
    if (pRoot == nullptr) {
        InvalidParameter();
    } else {
        uHead = *reinterpret_cast<uint64_t*>(pRoot);
    }
    const uint64_t uNew = uCur + n * (uint64_t)-8;
    bool bOk = false;
    if (uNew <= *reinterpret_cast<uint64_t*>(uHead + 0x20)) {
        if (pRoot != nullptr) uBegin = *reinterpret_cast<uint64_t*>(pRoot);
        if (*reinterpret_cast<uint64_t*>(uBegin + 0x18) <= uNew) bOk = true;
    }
    if (!bOk) InvalidParameter();
    pOut[0] = (void*)pRoot;
    pOut[1] = (void*)uNew;
    return pOut;
}

// 0x140d95590 — the container and the offset are taken from the iterator and
// the node's +0x08
void* IterCopyFromNode(void** pOut, void** pIter, void* pNode) {
    void* pOffset = *(void**)((char*)pNode + 8);
    if (pIter == nullptr) InvalidParameter();
    pOut[0] = pIter[0];
    pOut[1] = pOffset;
    return pOut;
}

// 0x140d959a0 — copy construction of an out_of_range
void OutOfRangeCopyCtor(void* pSelf, const void* pOther) {
    LogicErrorCopyCtor(pSelf, pOther);
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uOutOfRangeVft;
}

// 0x140d95ae0 — stand the container up: a fresh head marked at +0x29, all
// three links back to itself and the size cleared
void TreeInit(void* pTree) {
    char* p = (char*)pTree;
    char* pHead = (char*)TreeHeadAlloc();
    *(char**)(p + 0x30) = pHead;
    *(uint8_t*)(pHead + 0x29) = 1;
    *(char**)(*(char**)(p + 0x30) + 8) = *(char**)(p + 0x30);
    *(uint64_t*)*(uint64_t**)(p + 0x30) = *(uint64_t*)(p + 0x30);
    *(char**)(*(char**)(p + 0x30) + 0x10) = *(char**)(p + 0x30);
    *(uint64_t*)(p + 0x38) = 0;
}

// 0x140d95e60 — an iterator from a node, offset taken from +0x08 of a third
// object, bounded by the node's +0x18 and +0x20
void* IterFromNodeChecked(void** pOut, void** pNode, void* pFrom) {
    const uint64_t uOffset = *(uint64_t*)((char*)pFrom + 8);
    pOut[0] = nullptr;
    if (pNode == nullptr || uOffset < (uint64_t)pNode[3] ||
        (uint64_t)pNode[4] < uOffset) {
        InvalidParameter();
    }
    void* pContainer = pNode[0];
    pOut[1] = (void*)uOffset;
    pOut[0] = pContainer;
    return pOut;
}

// 0x140d95ec0 — the self-allocating node once more
void* NodeSelfAllocE(void** pSelf) { return TreeNodeSelfAlloc(pSelf); }

}  // namespace stl
}  // namespace flower

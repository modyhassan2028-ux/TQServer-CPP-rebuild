// stl_tree.cpp — RAW Flower.dll v6159
#include "modules/flower/src/stl_tree.h"
#include "modules/flower/src/stl_exceptions.h"
#include <cstring>
#include <new>
#include <stdexcept>

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

// 0x140d955e0 — erase one node: a nil iterator is out_of_range("invalid
// map/set<T> iterator"), otherwise the node is unlinked, its successor
// rebalanced and the size stepped down. Colours live at +0x28, the nil mark
// at +0x29, the head at +0x30 and the size at +0x38.
void* TreeErase(void** pTree, void** pOut, void** pIter) {
    char* pT = (char*)pTree;
    (void)pT;
    int64_t* pNode = (int64_t*)pIter[1];
    if (*(char*)((char*)pNode + 0x29) != '\0') {
        throw std::out_of_range("invalid map/set<T> iterator");
    }
    TreeIncrement(pIter);
    int64_t* x = (int64_t*)*pNode;
    int64_t* y;
    int64_t* z;
    bool bSkip = false;
    if (*(char*)((char*)x + 0x29) == '\0') {
        y = x;
        if (*(char*)(pNode[2] + 0x29) == '\0') {
            int64_t* pSucc = (int64_t*)pIter[1];
            y = (int64_t*)pSucc[2];
            if (pSucc != pNode) {
                x[1] = (int64_t)pSucc;
                *pSucc = *pNode;
                x = pSucc;
                if (pSucc != (int64_t*)pNode[2]) {
                    x = (int64_t*)pSucc[1];
                    if (*(char*)((char*)y + 0x29) == '\0') {
                        y[1] = (int64_t)x;
                    }
                    *x = (int64_t)y;
                    pSucc[2] = pNode[2];
                    *(int64_t*)(pNode[2] + 8) = (int64_t)pSucc;
                }
                if (*(int64_t**)(pT + 0x30) != nullptr &&
                    *(int64_t**)(*(int64_t*)(pT + 0x30) + 8) == pNode) {
                    *(int64_t**)(*(int64_t*)(pT + 0x30) + 8) = pSucc;
                } else {
                    int64_t* pParent = (int64_t*)pNode[1];
                    if ((int64_t*)*pParent == pNode) {
                        *pParent = (int64_t)pSucc;
                    } else {
                        pParent[2] = (int64_t)pSucc;
                    }
                }
                pSucc[1] = pNode[1];
                char* a = (char*)(pNode + 5);
                char* b = (char*)(pSucc + 5);
                if (b != a) {
                    const char cTmp = *b;
                    *b = *a;
                    *a = cTmp;
                }
                bSkip = true;
            }
        }
    } else {
        y = (int64_t*)pNode[2];
    }
    if (!bSkip) {
        x = (int64_t*)pNode[1];
        if (*(char*)((char*)y + 0x29) == '\0') {
            y[1] = (int64_t)x;
        }
        if (*(int64_t**)(pT + 0x30) != nullptr &&
            *(int64_t**)(*(int64_t*)(pT + 0x30) + 8) == pNode) {
            *(int64_t**)(*(int64_t*)(pT + 0x30) + 8) = y;
        } else if ((int64_t*)*x == pNode) {
            *x = (int64_t)y;
        } else {
            x[2] = (int64_t)y;
        }
        if (*(int64_t**)*(int64_t**)(pT + 0x30) == pNode) {
            z = x;
            if (*(char*)((char*)y + 0x29) == '\0') {
                char cColor = *(char*)(*y + 0x29);
                int64_t* pLeft = (int64_t*)*y;
                z = y;
                while (cColor == '\0') {
                    int64_t* pCur = pLeft;
                    pLeft = (int64_t*)*pCur;
                    cColor = *(char*)((char*)pLeft + 0x29);
                    z = pCur;
                }
            }
            *(int64_t**)*(int64_t**)(pT + 0x30) = z;
        }
        if (*(int64_t**)(*(int64_t*)(pT + 0x30) + 0x10) == pNode) {
            z = x;
            if (*(char*)((char*)y + 0x29) == '\0') {
                char cColor = *(char*)(y[2] + 0x29);
                int64_t* pRight = (int64_t*)y[2];
                z = y;
                while (cColor == '\0') {
                    int64_t* pCur = pRight;
                    pRight = (int64_t*)pCur[2];
                    cColor = *(char*)((char*)pRight + 0x29);
                    z = pCur;
                }
            }
            *(int64_t**)(*(int64_t*)(pT + 0x30) + 0x10) = z;
        }
    }
    if ((char)pNode[5] == '\x01') {
        int64_t* pRootParent = *(int64_t**)(*(int64_t*)(pT + 0x30) + 8);
        if (y != pRootParent) {
            do {
                z = x;
                if ((char)y[5] != '\x01') break;
                x = (int64_t*)*z;
                if (y == x) {
                    x = (int64_t*)z[2];
                    if ((char)x[5] == '\0') {
                        *(char*)((char*)x + 0x28) = '\x01';
                        *(char*)((char*)z + 0x28) = '\0';
                        TreeRotateLeft(pTree, z);
                        x = (int64_t*)z[2];
                    }
                    if (*(char*)((char*)x + 0x29) == '\0') {
                        if ((*(char*)(*x + 0x28) != '\x01') ||
                            (*(char*)(x[2] + 0x28) != '\x01')) {
                            if (*(char*)(x[2] + 0x28) == '\x01') {
                                *(char*)(*x + 0x28) = '\x01';
                                *(char*)((char*)x + 0x28) = '\0';
                                TreeRotateRight(pTree, x);
                                x = (int64_t*)z[2];
                            }
                            *(char*)((char*)x + 0x28) = (char)z[5];
                            *(char*)((char*)z + 0x28) = '\x01';
                            *(char*)(x[2] + 0x28) = '\x01';
                            TreeRotateLeft(pTree, z);
                            break;
                        }
                        *(char*)((char*)x + 0x28) = '\0';
                    }
                } else {
                    if ((char)x[5] == '\0') {
                        *(char*)((char*)x + 0x28) = '\x01';
                        *(char*)((char*)z + 0x28) = '\0';
                        TreeRotateRight(pTree, z);
                        x = (int64_t*)*z;
                    }
                    if (*(char*)((char*)x + 0x29) == '\0') {
                        if ((*(char*)(x[2] + 0x28) != '\x01') ||
                            (*(char*)(*x + 0x28) != '\x01')) {
                            if (*(char*)(*x + 0x28) == '\x01') {
                                *(char*)(x[2] + 0x28) = '\x01';
                                *(char*)((char*)x + 0x28) = '\0';
                                TreeRotateLeft(pTree, x);
                                x = (int64_t*)*z;
                            }
                            *(char*)((char*)x + 0x28) = (char)z[5];
                            *(char*)((char*)z + 0x28) = '\x01';
                            *(char*)(*x + 0x28) = '\x01';
                            TreeRotateRight(pTree, z);
                            break;
                        }
                        *(char*)((char*)x + 0x28) = '\0';
                    }
                }
                x = (int64_t*)z[1];
                y = z;
            } while (z != *(int64_t**)(*(int64_t*)(pT + 0x30) + 8));
        }
        *(char*)((char*)y + 0x28) = '\x01';
    }
    ::operator delete(pNode);
    if (*(uint64_t*)(pT + 0x38) != 0) {
        *(uint64_t*)(pT + 0x38) = *(uint64_t*)(pT + 0x38) - 1;
    }
    const int64_t uKept = (int64_t)pIter[1];
    pOut[0] = pTree[0];
    pOut[1] = (void*)uKept;
    return pOut;
}

// 0x140d96020 — a cursor owner: an eight byte node pointing at itself, and the
// three slots at +0x18/+0x20/+0x28 cleared
void* ContainerInitA(void** pVec) {
    void** pNode = (void**)::operator new(8);
    void** pStore = nullptr;
    if (pNode != nullptr) {
        *pNode = pVec;
        pStore = pNode;
    }
    *pVec = pStore;
    pVec[3] = nullptr;
    pVec[4] = nullptr;
    pVec[5] = nullptr;
    return pVec;
}

// 0x140d96080 — the first cursor: its offset is the one at +0x18 and the
// size at +0x20 must not be under it
void* ContainerBegin(void** pVec, void** pOut) {
    const uint64_t uOffset = (uint64_t)pVec[3];
    pOut[0] = nullptr;
    if ((uint64_t)pVec[4] < uOffset) InvalidParameter();
    void* pContainer = pVec[0];
    pOut[1] = (void*)uOffset;
    pOut[0] = pContainer;
    return pOut;
}

// 0x140d960d0 — the second cursor: its offset is the one at +0x20
void* ContainerEnd(void** pVec, void** pOut) {
    const uint64_t uOffset = (uint64_t)pVec[4];
    pOut[0] = nullptr;
    if (uOffset < (uint64_t)pVec[3]) InvalidParameter();
    void* pContainer = pVec[0];
    pOut[1] = (void*)uOffset;
    pOut[0] = pContainer;
    return pOut;
}

// 0x140d95a00 — look a key up in the record set: the lower bound and the upper
// bound come back as two iterator pairs, each carrying the container
void* TreeFind(void** pTree, void** pOut, uint32_t* pKey) {
    char* pHead = (char*)pTree[6];
    void** pHi = (void**)pHead;
    void** pLow = (void**)pHead;
    if (*(char*)(*(uint64_t*)(pHead + 8) + 0x29) == '\0') {
        void** p = *(void***)(pHead + 8);
        void** pNext;
        do {
            if (*(uint32_t*)((char*)p + 0x18) < *pKey) {
                pNext = (void**)p[2];
            } else {
                if (*(char*)(pHead + 0x29) != '\0' &&
                    *pKey < *(uint32_t*)((char*)p + 0x18)) {
                    pHi = p;
                }
                pNext = (void**)*p;
                pLow = p;
            }
            p = pNext;
        } while (*(char*)((char*)pNext + 0x29) == '\0');
    }
    void** pStart;
    if (*(char*)((char*)pHi + 0x29) == '\0') {
        pStart = (void**)*pHi;
    } else {
        pStart = *(void***)((char*)pTree[6] + 8);
    }
    if (*(char*)((char*)pStart + 0x29) == '\0') {
        void** pNext;
        do {
            if (*pKey < *(uint32_t*)((char*)pStart + 0x18)) {
                pNext = (void**)*pStart;
                pHi = pStart;
            } else {
                pNext = (void**)pStart[2];
            }
            pStart = pNext;
        } while (*(char*)((char*)pNext + 0x29) == '\0');
    }
    void* pContainer = pTree[0];
    pOut[0] = pContainer;
    pOut[1] = pLow;
    pOut[2] = pContainer;
    pOut[3] = pHi;
    return pOut;
}

// 0x140d963e0 — the same lookup as the standard wrapper returns it
void* TreeFindWrap(void** pTree, void** pOut, uint32_t* pKey) {
    TreeFind(pTree, pOut, pKey);
    return pOut;
}

// 0x140d97b10 — a cursor owner plus a standing record set: the eight byte node
// at the front, then the head from 0x140d95170 marked at +0x29 with all three
// links to itself and the size cleared at +0x38
void* TreeInitSelf(void** pTree) {
    void** pNode = (void**)::operator new(8);
    if (pNode == nullptr) pNode = nullptr;
    else *pNode = pTree;
    *pTree = pNode;
    char* pHead = (char*)TreeHeadAlloc();
    pTree[6] = pHead;
    *(uint8_t*)(pHead + 0x29) = 1;
    *(char**)((char*)pTree[6] + 8) = (char*)pTree[6];
    *(char**)((char*)pTree[6]) = (char*)pTree[6];
    *(char**)((char*)pTree[6] + 0x10) = (char*)pTree[6];
    pTree[7] = nullptr;
    return pTree;
}

// 0x140d97b90 — the same container without the cursors: slot 0 cleared, then
// the set stood up at +8
void* ContainerInitB(void** pVec) {
    pVec[0] = nullptr;
    TreeInitSelf(pVec + 1);
    return pVec;
}

// 0x140d95b20 — insert one node under the hint and rebalance. The decompiled
// names are kept so the two rotation shapes can be checked line for line:
// plVar2 is the parent, plVar3 the grandparent, lVar4 the uncle (or the node
// being rotated), plVar5 the fresh node, plVar6 the walker and plVar7 the
// pointer to the parent slot. Colours at +0x28, the nil mark at +0x29.
void* TreeInsert(void** pTree, void** pOut, char cLeft, void** pParent,
                 void** pValue) {
    if (0x0ffffffffffffffdULL < (uint64_t)pTree[7]) {
        throw std::length_error("map/set<T> too long");
    }
    char* const pHead = (char*)pTree[6];
    int64_t* plVar5 = (int64_t*)TreeNodeAlloc(pTree[6], pParent, pTree[6],
                                              (const uint64_t*)pValue, 0);
    pTree[7] = (void*)((uint64_t)pTree[7] + 1);
    if (pParent == (void**)pHead) {
        *(int64_t**)(pHead + 8) = plVar5;
        *(int64_t**)pHead = plVar5;
        *(int64_t**)(pHead + 0x10) = plVar5;
    } else if (cLeft == '\0') {
        pParent[2] = plVar5;
        if (pParent == *(void***)(pHead + 0x10)) {
            *(int64_t**)(pHead + 0x10) = plVar5;
        }
    } else {
        *pParent = plVar5;
        if (pParent == *(void***)pHead) {
            *(int64_t**)pHead = plVar5;
        }
    }
    int64_t* plVar7 = plVar5 + 1;
    char cVar1 = *(char*)(*plVar7 + 0x28);
    int64_t* plVar6 = plVar5;
    while (cVar1 == '\0') {
        int64_t* plVar2 = (int64_t*)*plVar7;
        int64_t* plVar3 = (int64_t*)plVar2[1];
        if (plVar2 == (int64_t*)*plVar3) {
            int64_t lVar4 = plVar3[2];
            if (*(char*)(lVar4 + 0x28) == '\0') {
                *(uint8_t*)((char*)plVar2 + 0x28) = 1;
                *(uint8_t*)(lVar4 + 0x28) = 1;
                *(uint8_t*)(*(int64_t*)(*plVar7 + 8) + 0x28) = 0;
                plVar6 = *(int64_t**)(*plVar7 + 8);
            } else {
                if (plVar6 == (int64_t*)plVar2[2]) {
                    plVar6 = (int64_t*)plVar2[2];
                    plVar2[2] = *plVar6;
                    if (*(char*)(*plVar6 + 0x29) == '\0') {
                        *(int64_t**)(*plVar6 + 8) = plVar2;
                    }
                    plVar7 = plVar2 + 1;
                    plVar6[1] = *plVar7;
                    if (plVar2 == *(int64_t**)(pHead + 8)) {
                        *(int64_t**)(pHead + 8) = plVar6;
                    } else {
                        plVar3 = (int64_t*)*plVar7;
                        if (plVar2 == (int64_t*)*plVar3) {
                            *plVar3 = (int64_t)plVar6;
                        } else {
                            plVar3[2] = (int64_t)plVar6;
                        }
                    }
                    *plVar6 = (int64_t)plVar2;
                    *plVar7 = (int64_t)plVar6;
                    plVar6 = plVar2;
                }
                *(uint8_t*)(*plVar7 + 0x28) = 1;
                *(uint8_t*)(*(int64_t*)(*plVar7 + 8) + 0x28) = 0;
                plVar7 = *(int64_t**)(*plVar7 + 8);
                int64_t lVar4b = *plVar7;
                *plVar7 = *(int64_t*)(lVar4b + 0x10);
                if (*(char*)(*(int64_t*)(lVar4b + 0x10) + 0x29) == '\0') {
                    *(int64_t**)(*(int64_t*)(lVar4b + 0x10) + 8) = plVar7;
                }
                *(int64_t*)(lVar4b + 8) = plVar7[1];
                if (plVar7 == *(int64_t**)(pHead + 8)) {
                    *(int64_t**)(pHead + 8) = (int64_t*)lVar4b;
                } else {
                    plVar2 = (int64_t*)plVar7[1];
                    if (plVar7 == (int64_t*)plVar2[2]) {
                        plVar2[2] = lVar4b;
                    } else {
                        *plVar2 = lVar4b;
                    }
                }
                *(int64_t**)(lVar4b + 0x10) = plVar7;
                plVar7[1] = lVar4b;
            }
        } else {
            int64_t lVar4 = *plVar3;
            if (*(char*)(lVar4 + 0x28) == '\0') {
                *(uint8_t*)((char*)plVar2 + 0x28) = 1;
                *(uint8_t*)(lVar4 + 0x28) = 1;
                *(uint8_t*)(*(int64_t*)(*plVar7 + 8) + 0x28) = 0;
                plVar6 = *(int64_t**)(*plVar7 + 8);
            } else {
                if (plVar6 == (int64_t*)*plVar2) {
                    int64_t lVar4b = *plVar2;
                    *plVar2 = *(int64_t*)(lVar4b + 0x10);
                    if (*(char*)(*(int64_t*)(lVar4b + 0x10) + 0x29) == '\0') {
                        *(int64_t**)(*(int64_t*)(lVar4b + 0x10) + 8) = plVar2;
                    }
                    plVar7 = plVar2 + 1;
                    *(int64_t*)(lVar4b + 8) = *plVar7;
                    if (plVar2 == *(int64_t**)(pHead + 8)) {
                        *(int64_t*)(pHead + 8) = lVar4b;
                    } else {
                        plVar6 = (int64_t*)*plVar7;
                        if (plVar2 == (int64_t*)plVar6[2]) {
                            plVar6[2] = lVar4b;
                        } else {
                            *plVar6 = lVar4b;
                        }
                    }
                    *(int64_t**)(lVar4b + 0x10) = plVar2;
                    *plVar7 = lVar4b;
                    plVar6 = plVar2;
                }
                *(uint8_t*)(*plVar7 + 0x28) = 1;
                *(uint8_t*)(*(int64_t*)(*plVar7 + 8) + 0x28) = 0;
                int64_t lVar4c = *(int64_t*)(*plVar7 + 8);
                plVar7 = *(int64_t**)(lVar4c + 0x10);
                *(int64_t*)(lVar4c + 0x10) = *plVar7;
                if (*(char*)(*plVar7 + 0x29) == '\0') {
                    *(int64_t*)(*plVar7 + 8) = lVar4c;
                }
                plVar7[1] = *(int64_t*)(lVar4c + 8);
                if (lVar4c == *(int64_t*)(pHead + 8)) {
                    *(int64_t**)(pHead + 8) = plVar7;
                } else {
                    plVar2 = *(int64_t**)(lVar4c + 8);
                    if (lVar4c == *plVar2) {
                        *plVar2 = (int64_t)plVar7;
                    } else {
                        plVar2[2] = (int64_t)plVar7;
                    }
                }
                *plVar7 = lVar4c;
                *(int64_t**)(lVar4c + 8) = plVar7;
            }
        }
        plVar7 = plVar6 + 1;
        cVar1 = *(char*)(*plVar7 + 0x28);
    }
    *(uint8_t*)(*(int64_t*)(pHead + 8) + 0x28) = 1;
    pOut[1] = plVar5;
    pOut[0] = pTree[0];
    return pOut;
}

// 0x140d961f0 — erase the range [first, last). An iterator that belongs to
// another container is refused, an empty range collapses to the clear, and
// every step advances the first iterator inline (the same walk as
// 0x140d94b10) before handing the pair to the erase.
int64_t* TreeEraseRange(int64_t* pTree, int64_t* pOut, int64_t* pFirst,
                        int64_t* pLast) {
    int64_t lVar2 = *(int64_t*)pTree[6];
    if ((*pFirst == 0) || (*pFirst != *pTree)) InvalidParameter();
    if (pFirst[1] == lVar2) {
        lVar2 = pTree[6];
        if ((*pLast == 0) || (*pLast != *pTree)) InvalidParameter();
        if (pLast[1] == lVar2) {
            TreeClear((void*)pTree);
            pOut[1] = *(int64_t*)pTree[6];
            pOut[0] = *pTree;
            return pOut;
        }
    }
    for (;;) {
        if ((*pFirst == 0) || (*pFirst != *pLast)) InvalidParameter();
        lVar2 = *pFirst;
        if (pFirst[1] == pLast[1]) break;
        const int64_t lVar3 = pFirst[1];
        if (*pFirst == 0) InvalidParameter();
        const int64_t lVar4 = pFirst[1];
        if (*(char*)(lVar4 + 0x29) == '\0') {
            int64_t* plVar6 = *(int64_t**)(lVar4 + 0x10);
            if (*(char*)((char*)plVar6 + 0x29) == '\0') {
                char cVar1 = *(char*)(*plVar6 + 0x29);
                int64_t* plVar5 = (int64_t*)*plVar6;
                while (cVar1 == '\0') {
                    cVar1 = *(char*)(*plVar5 + 0x29);
                    plVar6 = plVar5;
                    plVar5 = (int64_t*)*plVar5;
                }
            } else {
                plVar6 = *(int64_t**)(lVar4 + 8);
                char cVar1 = *(char*)((char*)plVar6 + 0x29);
                while ((cVar1 == '\0') && (pFirst[1] == plVar6[2])) {
                    pFirst[1] = (int64_t)plVar6;
                    plVar6 = (int64_t*)plVar6[1];
                    cVar1 = *(char*)((char*)plVar6 + 0x29);
                }
            }
            pFirst[1] = (int64_t)plVar6;
        } else {
            InvalidParameter();
        }
        int64_t local_28[2];
        int64_t local_18[2];
        local_28[0] = lVar2;
        local_28[1] = lVar3;
        TreeErase((void**)pTree, (void**)local_18, (void**)local_28);
    }
    const int64_t lVar2b = pFirst[1];
    pOut[0] = *pTree;
    pOut[1] = lVar2b;
    return pOut;
}

// 0x140d96400 — the teardown of a record set: erase from the begin to the end
// iterator, then free the head and clear +0x30 and +0x38
void TreeDestroy(int64_t* pTree) {
    int64_t local_38[4];
    int64_t local_18[2];
    local_38[0] = *pTree;                     // the container
    local_38[1] = pTree[6];                   // the head, as the end iterator
    local_38[2] = *pTree;                     // the begin iterator's container
    local_38[3] = *(int64_t*)pTree[6];        // head->left, the begin iterator's node
    TreeEraseRange(pTree, local_18, &local_38[2], &local_38[0]);
    ::operator delete((void*)pTree[6]);
    pTree[6] = 0;
    pTree[7] = 0;
}

// 0x140d96560 — insert a value without a hint. The set is walked from the root
// keeping the last direction, the duplicate test compares the neighbour at
// +0x18, and the insert goes through 0x140d95b20 with that direction. The
// third slot of the output is the inserted flag at +0x10.
void* TreeInsertValue(int64_t* pTree, int64_t* pOut, uint32_t* pKey) {
    int64_t* plVar6 = (int64_t*)pTree[6];
    bool bVar7 = true;
    if (*(char*)(plVar6[1] + 0x29) == '\0') {
        int64_t* plVar5 = (int64_t*)plVar6[1];
        do {
            plVar6 = plVar5;
            bVar7 = *pKey < *(uint32_t*)((char*)plVar6 + 0x18);
            if (bVar7) {
                plVar5 = (int64_t*)*plVar6;
            } else {
                plVar5 = (int64_t*)plVar6[2];
            }
        } while (*(char*)((char*)plVar5 + 0x29) == '\0');
    }
    const int64_t lVar2 = *pTree;
    int64_t* plVar5 = plVar6;
    int64_t local_38[2];
    int64_t* plVar4 = plVar6;
    int64_t* local_30 = nullptr;
    local_38[0] = lVar2;
    if (bVar7 == false) {
LAB_966bd:
        local_30 = plVar4;
        if (*pKey <= *(uint32_t*)((char*)plVar5 + 0x18)) {
            *(uint8_t*)((char*)pOut + 0x10) = 0;
            pOut[0] = local_38[0];
            goto LAB_966ec;
        }
    } else {
        plVar5 = *(int64_t**)pTree[6];
        local_30 = plVar6;
        if (lVar2 == 0) InvalidParameter();
        if (plVar6 != plVar5) {
            if (lVar2 == 0) InvalidParameter();
            if (*(char*)((char*)plVar6 + 0x29) == '\0') {
                plVar5 = (int64_t*)*plVar6;
                if (*(char*)((char*)plVar5 + 0x29) == '\0') {
                    char cVar1 = *(char*)(plVar5[2] + 0x29);
                    int64_t* plVar3 = (int64_t*)plVar5[2];
                    while ((plVar4 = plVar5), cVar1 == '\0') {
                        cVar1 = *(char*)(plVar3[2] + 0x29);
                        plVar5 = plVar3;
                        plVar3 = (int64_t*)plVar3[2];
                    }
                } else {
                    char cVar1 = *(char*)(plVar6[1] + 0x29);
                    plVar4 = (int64_t*)plVar6[1];
                    int64_t* plVar3 = plVar6;
                    for (;;) {
                        plVar5 = plVar4;
                        if (!((cVar1 == '\0') && (plVar3 == (int64_t*)*plVar5))) break;
                        cVar1 = *(char*)(plVar5[1] + 0x29);
                        plVar4 = (int64_t*)plVar5[1];
                        plVar3 = plVar5;
                        local_30 = plVar5;
                    }
                    plVar4 = plVar5;
                    if (*(char*)((char*)plVar3 + 0x29) != '\0') {
                        InvalidParameter();
                        plVar5 = plVar3;
                        plVar4 = local_30;
                    }
                }
            } else {
                plVar5 = (int64_t*)plVar6[2];
                plVar4 = plVar5;
                if (*(char*)((char*)plVar5 + 0x29) != '\0') {
                    local_30 = plVar5;
                    InvalidParameter();
                    plVar4 = local_30;
                }
            }
            goto LAB_966bd;
        }
        bVar7 = true;
    }
    plVar6 = (int64_t*)TreeInsert((void**)pTree, (void**)local_38, bVar7 ? 1 : 0,
                                  (void**)plVar6, (void**)pKey);
    *(uint8_t*)((char*)pOut + 0x10) = 1;
    local_30 = (int64_t*)plVar6[1];
    pOut[0] = *plVar6;
LAB_966ec:
    pOut[1] = (int64_t)local_30;
    return pOut;
}

// 0x140d96b40 — insert with a hint. An empty set goes straight to the insert
// with the head as the parent; otherwise the hint is checked against the
// leftmost, the rightmost and the neighbour on either side, and only when the
// hint is useless does the plain insert at 0x140d96560 run.
void* TreeInsertHint(int64_t* pTree, int64_t* pOut, int64_t* pHint,
                     uint32_t* pKey) {
    if (pTree[7] == 0) {
        TreeInsert((void**)pTree, (void**)pOut, 1, (void**)pTree[6], (void**)pKey);
    } else {
        void** puVar2 = *(void***)pTree[6];
        if ((*pHint == 0) || (*pHint != *pTree)) InvalidParameter();
        void* puVar3 = (void*)pHint[1];
        if (puVar3 == puVar2) {
            if (*pKey < *(uint32_t*)((char*)puVar3 + 0x18)) {
                TreeInsert((void**)pTree, (void**)pOut, 1, (void**)puVar3, (void**)pKey);
                return pOut;
            }
        } else {
            const int64_t lVar4 = pTree[6];
            if ((*pHint == 0) || (*pHint != *pTree)) InvalidParameter();
            if (pHint[1] == lVar4) {
                if (*(uint32_t*)(*(void**)((char*)pTree[6] + 0x10) + 0x18) < *pKey) {
                    TreeInsert((void**)pTree, (void**)pOut, 0,
                               *(void***)((char*)pTree[6] + 0x10), (void**)pKey);
                    return pOut;
                }
            } else {
                uint32_t uVar8 = *pKey;
                if (uVar8 < *(uint32_t*)(pHint[1] + 0x18)) {
                    int64_t local_38[2];
                    int64_t* local_30;
                    local_38[0] = *pHint;
                    local_30 = (int64_t*)pHint[1];
                    if (local_38[0] == 0) InvalidParameter();
                    if (*(char*)((char*)local_30 + 0x29) == '\0') {
                        int64_t* plVar7 = (int64_t*)*local_30;
                        if (*(char*)((char*)plVar7 + 0x29) == '\0') {
                            char cVar1 = *(char*)(plVar7[2] + 0x29);
                            int64_t* plVar9 = (int64_t*)plVar7[2];
                            while ((local_30 = plVar7), cVar1 == '\0') {
                                cVar1 = *(char*)(plVar9[2] + 0x29);
                                plVar7 = plVar9;
                                plVar9 = (int64_t*)plVar9[2];
                            }
                        } else {
                            char cVar1 = *(char*)(local_30[1] + 0x29);
                            int64_t* plVar5 = (int64_t*)local_30[1];
                            int64_t* plVar9 = local_30;
                            for (;;) {
                                plVar7 = plVar5;
                                if (!((cVar1 == '\0') && (plVar9 == (int64_t*)*plVar7))) break;
                                cVar1 = *(char*)(plVar7[1] + 0x29);
                                plVar5 = (int64_t*)plVar7[1];
                                plVar9 = plVar7;
                            }
                            local_30 = plVar7;
                            if (*(char*)((char*)plVar9 + 0x29) != '\0') {
                                local_30 = plVar9;
                                InvalidParameter();
                                plVar7 = plVar9;
                            }
                        }
                    } else {
                        int64_t* plVar7 = (int64_t*)local_30[2];
                        local_30 = plVar7;
                        if (*(char*)((char*)plVar7 + 0x29) != '\0') {
                            InvalidParameter();
                        }
                    }
                    uVar8 = *pKey;
                    int64_t* plVar7b = (int64_t*)local_30;
                    if (*(uint32_t*)((char*)plVar7b + 0x18) < uVar8) {
                        if (*(char*)(plVar7b[2] + 0x29) != '\0') {
                            TreeInsert((void**)pTree, (void**)pOut, 0,
                                       (void**)plVar7b, (void**)pKey);
                            return pOut;
                        }
                        TreeInsert((void**)pTree, (void**)pOut, 1,
                                   (void**)pHint[1], (void**)pKey);
                        return pOut;
                    }
                }
                if (*(uint32_t*)(pHint[1] + 0x18) < uVar8) {
                    int64_t local_38[2];
                    local_38[0] = *pHint;
                    int64_t* plVar7 = (int64_t*)pTree[6];
                    int64_t* local_30 = (int64_t*)pHint[1];
                    const int64_t lVar4b = *pTree;
                    if (local_38[0] == 0) InvalidParameter();
                    int64_t* plVar9 = local_30;
                    if (*(char*)((char*)local_30 + 0x29) == '\0') {
                        plVar9 = (int64_t*)local_30[2];
                        if (*(char*)((char*)plVar9 + 0x29) == '\0') {
                            char cVar1 = *(char*)(*plVar9 + 0x29);
                            int64_t* plVar5 = (int64_t*)*plVar9;
                            while (cVar1 == '\0') {
                                cVar1 = *(char*)(*plVar5 + 0x29);
                                plVar9 = plVar5;
                                plVar5 = (int64_t*)*plVar5;
                            }
                        } else {
                            char cVar1 = *(char*)(local_30[1] + 0x29);
                            int64_t* plVar6 = (int64_t*)local_30[1];
                            int64_t* plVar5 = local_30;
                            for (;;) {
                                plVar9 = plVar6;
                                if (!((cVar1 == '\0') && (plVar5 == (int64_t*)plVar9[2]))) break;
                                cVar1 = *(char*)(plVar9[1] + 0x29);
                                plVar6 = (int64_t*)plVar9[1];
                                plVar5 = plVar9;
                            }
                        }
                    } else {
                        InvalidParameter();
                    }
                    if ((local_38[0] == 0) || (local_38[0] != lVar4b)) InvalidParameter();
                    if ((plVar9 == plVar7) || (*pKey < *(uint32_t*)((char*)plVar9 + 0x18))) {
                        if (*(char*)(((void**)pHint[1])[2] + 0x29) != '\0') {
                            TreeInsert((void**)pTree, (void**)pOut, 0,
                                       (void**)pHint[1], (void**)pKey);
                            return pOut;
                        }
                        TreeInsert((void**)pTree, (void**)pOut, 1,
                                   (void**)plVar9, (void**)pKey);
                        return pOut;
                    }
                }
            }
        }
        // the decompiled slot is one qword; 0x140d96560 also writes the
        // inserted flag at +0x10, so the slot is widened to three
        int64_t local_38[3];
        int64_t* plVar7 = (int64_t*)TreeInsertValue(pTree, local_38, pKey);
        pOut[0] = *plVar7;
        pOut[1] = plVar7[1];
    }
    return pOut;
}

}  // namespace stl
}  // namespace flower

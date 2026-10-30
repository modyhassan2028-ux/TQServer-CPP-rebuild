// D142 — the tree, allocator and vector machinery of Flower.dll
#include "modules/flower/src/stl_tree.h"
#include "modules/flower/src/stl_exceptions.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <stdexcept>
using namespace flower::stl;

// 0x30 byte node: left +0, parent +8, right +0x10, element +0x18, colour +0x29
struct Node {
    Node* pLeft;
    Node* pParent;
    Node* pRight;
    uint64_t uElem0;
    uint64_t uElem1;
    uint8_t pad28;
    uint8_t cColor;      // 0 = live, anything else = nil/head
    uint8_t tail[6];
};
static void Reset(Node& n, uint8_t color) {
    std::memset(&n, 0, sizeof n);
    n.cColor = color;
}

struct Container {
    uint64_t pad[6];     // 0x00..0x2f
    Node* pHead;         // +0x30
};

int main() {
    int nBad = 0;
    g_pfnInvalidParameter = nullptr;
    struct Hook { static void F() {} };
    Node head, A, B, C;
    Reset(head, 1);
    Reset(A, 0); Reset(B, 0); Reset(C, 0);
    Container ct;
    std::memset(&ct, 0, sizeof ct);
    ct.pHead = &head;
    // head: left = leftmost (B), right = root (A), parent = rightmost (C)
    head.pLeft = &B;
    head.pRight = &A;
    head.pParent = &C;
    A.pParent = &head; A.pLeft = &B; A.pRight = &C;
    B.pParent = &A; B.pLeft = &head; B.pRight = &head;
    C.pParent = &A; C.pLeft = &head; C.pRight = &head;

    // ---- the iterator pair walks the tree in order
    void* it[2];
    it[0] = &head;                       // the container the iterator belongs to
    it[1] = &B;
    TreeIncrement(it);
    assert(it[1] == &A);
    TreeIncrement(it);
    assert(it[1] == &C);
    TreeIncrement(it);
    assert(it[1] == &head);              // past the last node
    it[1] = &A;
    TreeDecrement(it);
    assert(it[1] == &B);
    it[1] = &C;
    TreeDecrement(it);
    assert(it[1] == &A);
    it[1] = &A;
    assert(TreeIncrementWrap(it) == it && it[1] == &C);
    it[1] = &C;
    assert(TreeDecrementWrap(it) == it && it[1] == &A);
    assert(TreeDecrementWrap2(it) == it && it[1] == &B);

    // ---- the rotations move the same pointers the original does
    std::memset(&ct, 0, sizeof ct);
    ct.pHead = &head;
    head.pLeft = &B; head.pRight = &A; head.pParent = &C;
    A.pParent = &head; A.pLeft = &B; A.pRight = &C;
    C.pParent = &A; C.pLeft = &head; C.pRight = &head;
    TreeRotateLeft(&ct, &A);
    assert(head.pRight == &C);
    assert(C.pLeft == &A);
    assert(A.pRight == &head);
    assert(A.pParent == &C);
    // and back
    std::memset(&ct, 0, sizeof ct);
    ct.pHead = &head;
    head.pLeft = &C; head.pRight = &A; head.pParent = &B;
    A.pParent = &head; A.pLeft = &B; A.pRight = &C;
    B.pParent = &A; B.pLeft = &head; B.pRight = &head;
    TreeRotateRight(&ct, &A);
    assert(head.pRight == &B);
    assert(B.pRight == &A);
    assert(A.pParent == &B);

    // ---- the allocators: size and the overflow guards
    void* p8 = Alloc8A(4);
    std::memset(p8, 0, 32);
    ::operator delete(p8);
    p8 = Alloc8B(2);
    ::operator delete(p8);
    p8 = Alloc8C(&ct, 3);
    ::operator delete(p8);
    p8 = Alloc8D(&ct, 1);
    ::operator delete(p8);
    void* p30 = Alloc30A(2);
    ::operator delete(p30);
    p30 = Alloc30B(&ct, 1);
    ::operator delete(p30);
    bool bBad = false;
    try { Alloc8A(UINT64_MAX / 4); } catch (const std::bad_alloc&) { bBad = true; }
    assert(bBad);
    bBad = false;
    try { Alloc30A(UINT64_MAX / 4); } catch (const std::bad_alloc&) { bBad = true; }
    assert(bBad);

    // ---- the block move answers where the destination ended
    uint64_t src[3] = {1, 2, 3};
    uint64_t dst[3] = {0, 0, 0};
    void* pEnd = MoveBlock(src, src + 3, dst);
    assert(dst[0] == 1 && dst[1] == 2 && dst[2] == 3);
    assert(pEnd == (void*)((char*)dst + 24));

    // ---- the vector reservation: begin/end/limit and its guard
    unsigned char vec[0x30];
    std::memset(vec, 0xAA, sizeof vec);
    assert(VectorReserve(vec, 4) == 1);
    char* pBegin = *(char**)(vec + 0x18);
    assert(pBegin != nullptr);
    assert(*(char**)(vec + 0x20) == pBegin);
    assert(*(char**)(vec + 0x28) == pBegin + 32);
    VectorRelease(vec);
    assert(*(void**)(vec + 0x18) == nullptr);
    assert(*(void**)(vec + 0x20) == nullptr);
    assert(*(void**)(vec + 0x28) == nullptr);
    assert(VectorReserve(vec, 0) == 0);
    bBad = false;
    try { VectorReserve(vec, 0x2000000000000000ull); }
    catch (const std::length_error&) { bBad = true; }
    assert(bBad);

    // ---- the free of a subtree and the self-allocating node
    Node* pN1 = new Node(); Reset(*pN1, 0);
    pN1->pLeft = &head; pN1->pRight = &head;
    TreeFreeNodes(&ct, (void**)pN1);      // deletes the node
    void** pSelf = (void**)::operator new(sizeof(void*));
    *pSelf = nullptr;
    void* pRet = TreeNodeSelfAlloc(pSelf);
    assert(pRet == pSelf && *pSelf != nullptr && *(void**)*pSelf == pSelf);
    ::operator delete(*pSelf);
    ::operator delete(pSelf);

    // ---- deleting a slot, and the iterator built from a container + node
    void** pSlot = (void**)::operator new(sizeof(void*));
    *pSlot = ::operator new(8);
    DeleteSlotA(pSlot);
    *pSlot = ::operator new(8);
    DeleteSlotB(pSlot);
    *pSlot = ::operator new(8);
    DeleteSlotC(pSlot);
    *pSlot = ::operator new(8);
    DeleteSlotD(pSlot);
    ::operator delete(pSlot);
    void* pIter[2];
    pIter[0] = nullptr; pIter[1] = nullptr;
    void* pNodeSlot[1];
    pNodeSlot[0] = &A;
    assert(IteratorFromContainer(pIter, &head, pNodeSlot) == pIter);
    assert(pIter[0] == &A && pIter[1] == &head);

    // ---- the bad_alloc copy keeps the vftable
    g_uBadAllocVft = 0xC1;
    unsigned char ex[0x40];
    std::memset(ex, 0, sizeof ex);
    BadAllocCopyCtor(ex, ex);
    assert(*(uintptr_t*)ex == 0xC1);
    (void)nBad;
    printf("FLOWER_D142_OK: tree walks, rotations, allocators, vector\n");
    return 0;
}

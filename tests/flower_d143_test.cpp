// D143 — the second family of container instantiations
#include "modules/flower/src/stl_tree.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace flower::stl;

struct Node {
    Node* pLeft; Node* pParent; Node* pRight;
    uint64_t uElem0, uElem1;
    uint8_t pad28, cColor, tail[6];
};
static void Reset(Node& n, uint8_t c) {
    std::memset(&n, 0, sizeof n);
    n.cColor = c;
}

int main() {
    g_pfnInvalidParameter = nullptr;
    Node head, A, B, C;
    Reset(head, 1); Reset(A, 0); Reset(B, 0); Reset(C, 0);
    head.pLeft = &B; head.pRight = &A; head.pParent = &C;
    A.pParent = &head; A.pLeft = &B; A.pRight = &C;
    B.pParent = &A; B.pLeft = &head; B.pRight = &head;
    C.pParent = &A; C.pLeft = &head; C.pRight = &head;

    // ---- copy-then-step, and the backwards move
    void* src[2]; src[0] = &head; src[1] = &B;
    void* dst[2]; dst[0] = nullptr; dst[1] = nullptr;
    assert(IterCopyThenNext(dst, src) == dst);
    assert(dst[0] == &head && dst[1] == &B);
    assert(src[1] == &A);                     // the source stepped
    void* it[2]; it[0] = &head; it[1] = &C;
    assert(IterAdvanceBack(it, 1) == it);
    assert(TreeIncrementWrap2(it) == it);

    // ---- the iterator built from a node keeps the head's bounds
    void* pNode[6];
    pNode[0] = &head;      // container
    pNode[3] = (void*)0x8; // begin
    pNode[4] = (void*)0x40;// size
    void* out[2]; out[0] = nullptr; out[1] = nullptr;
    assert(IteratorFromNodeA(out, 0x10, pNode) == out);
    assert(out[0] == &head && out[1] == (void*)0x10);
    void* out2[2]; out2[0] = nullptr; out2[1] = nullptr;
    assert(IteratorFromNodeB(out2, 0x40, pNode) == out2);
    assert(out2[1] == (void*)0x40);
    int nBad = 0;
    struct H { static void F() { } };
    g_pfnInvalidParameter = nullptr;          // the hook stays optional

    // ---- the head and node allocations keep the original fields
    char* pHeadNew = (char*)TreeHeadAlloc();
    assert(pHeadNew != nullptr);
    assert(*(uint64_t*)(pHeadNew + 0x00) == 0);
    assert(*(uint64_t*)(pHeadNew + 0x08) == 0);
    assert(*(uint64_t*)(pHeadNew + 0x10) == 0);
    assert(*(uint8_t*)(pHeadNew + 0x28) == 1);
    assert(*(uint8_t*)(pHeadNew + 0x29) == 0);
    ::operator delete(pHeadNew);
    uint64_t elem[2] = {0x11, 0x22};
    char* pN = (char*)TreeNodeAlloc(&A, &head, &C, elem, 0x7);
    assert(*(void**)(pN + 0x00) == &A);
    assert(*(void**)(pN + 0x08) == &head);
    assert(*(void**)(pN + 0x10) == &C);
    assert(*(uint64_t*)(pN + 0x18) == 0x11 && *(uint64_t*)(pN + 0x20) == 0x22);
    assert(*(uint8_t*)(pN + 0x28) == 0x7 && *(uint8_t*)(pN + 0x29) == 0);
    ::operator delete(pN);

    // ---- the block move and the tree clear
    uint64_t s2[2] = {5, 6}, d2[2] = {0, 0};
    assert(MoveBlockB(s2, s2 + 2, d2) == (void*)((char*)d2 + 16));
    assert(d2[0] == 5 && d2[1] == 6);
    // a container with its head at +0x30 and one node on the left spine
    unsigned char tree[0x40];
    std::memset(tree, 0, sizeof tree);
    Node* pRoot = new Node(); Reset(*pRoot, 0);
    pRoot->pLeft = &head; pRoot->pRight = &head;
    head.pLeft = pRoot;                    // the head's left child is the root
    head.pParent = pRoot;                  // and +0x08 carries the root itself
    head.pRight = &head;
    *(void**)(tree + 0x30) = &head;
    *(uint64_t*)(tree + 0x38) = 1;
    TreeClear(tree);
    assert(*(uint64_t*)(tree + 0x38) == 0);
    assert(head.pLeft == &head && head.pRight == &head &&
           head.pParent == &head);

    // ---- the vector release and the last slot free
    void* vec[6];
    std::memset(vec, 0, sizeof vec);
    vec[0] = ::operator new(8);
    vec[3] = ::operator new(8);
    VectorReleaseB(vec);
    // the original frees the first slot without clearing it
    assert(vec[3] == nullptr && vec[4] == nullptr && vec[5] == nullptr);
    void** pSlot = (void**)::operator new(sizeof(void*));
    *pSlot = ::operator new(8);
    DeleteSlotE(pSlot);
    ::operator delete(pSlot);

    // ---- the three self-allocating node forms agree
    void** selfs[3];
    for (int i = 0; i < 3; ++i) {
        selfs[i] = (void**)::operator new(sizeof(void*));
        *selfs[i] = nullptr;
    }
    NodeSelfAllocB(selfs[0]);
    NodeSelfAllocC(selfs[1]);
    NodeSelfAllocD(selfs[2]);
    for (int i = 0; i < 3; ++i) {
        assert(*selfs[i] != nullptr && *(void**)*selfs[i] == selfs[i]);
        ::operator delete(*selfs[i]);
        ::operator delete(selfs[i]);
    }
    (void)nBad;
    printf("FLOWER_D143_OK: second instantiation family\n");
    return 0;
}

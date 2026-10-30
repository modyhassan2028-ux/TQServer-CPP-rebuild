// D146 — the record container: cursors, init and lookup
#include "modules/flower/src/stl_tree.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace flower::stl;

// node: left +0, parent +8, right +0x10, key at +0x18, colour +0x28, nil +0x29
struct Node {
    Node* pLeft; Node* pParent; Node* pRight;
    uint64_t uElem0, uElem1;
    uint8_t cColor, cNil, tail[6];
};
static Node* NewNode(Node* nil, uint32_t key) {
    Node* p = new Node();
    std::memset(p, 0, sizeof *p);
    p->pLeft = nil; p->pRight = nil; p->pParent = nil;
    p->uElem0 = key;
    return p;
}

int main() {
    g_pfnInvalidParameter = nullptr;

    // ---- the cursor owner and its two cursors
    void* vec[6];
    std::memset(vec, 0xEE, sizeof vec);
    assert(ContainerInitA(vec) == vec);
    assert(vec[0] != nullptr && *(void**)vec[0] == vec);
    assert(vec[3] == nullptr && vec[4] == nullptr && vec[5] == nullptr);
    void* out[2];
    ContainerBegin(vec, out);
    assert(out[0] == vec[0] && out[1] == nullptr);
    vec[3] = (void*)0x10;
    vec[4] = (void*)0x40;
    ContainerBegin(vec, out);
    assert(out[0] == vec[0] && out[1] == (void*)0x10);
    ContainerEnd(vec, out);
    assert(out[1] == (void*)0x40);
    ::operator delete(vec[0]);

    // ---- a record set: root 5 with children 3 and 7, all linking to the nil
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInitSelf(tree);
    Node* nil = (Node*)tree[6];
    assert(nil->cNil == 1);
    assert(nil->pLeft == nil && nil->pRight == nil && nil->pParent == nil);
    assert(tree[7] == nullptr);
    Node* pRoot = NewNode(nil, 5);
    Node* pL = NewNode(nil, 3);
    Node* pR = NewNode(nil, 7);
    pRoot->pLeft = pL; pRoot->pRight = pR;
    pL->pParent = pRoot; pR->pParent = pRoot;
    nil->pLeft = pL; nil->pRight = pR; nil->pParent = pRoot;
    *(uint64_t*)((char*)tree[6] + 8) = (uint64_t)pRoot;   // head +8 = root

    // an exact hit answers {lower, upper} around the node
    uint32_t key = 5;
    void* res[4];
    assert(TreeFind(tree, res, &key) == res);
    assert(res[0] == tree[0] && res[2] == tree[0]);
    assert(res[1] == (void*)pRoot);     // lower bound settles on the node
    assert(res[3] == (void*)pR);        // upper bound passes it
    // a miss below everything answers the leftmost on both sides
    key = 1;
    TreeFindWrap(tree, res, &key);
    assert(res[1] == (void*)pL && res[3] == (void*)pL);
    // a miss above everything answers the nil on both sides
    key = 9;
    TreeFind(tree, res, &key);
    assert(res[1] == (void*)nil && res[3] == (void*)nil);

    // ---- the container that carries the set at +8
    void* vec2[12];
    std::memset(vec2, 0, sizeof vec2);
    assert(ContainerInitB(vec2) == vec2);
    assert(vec2[0] == nullptr);
    assert(vec2[1] != nullptr && *(void**)vec2[1] == &vec2[1]);
    char* pHead = (char*)vec2[7];        // [1+6] = the head
    assert(pHead != nullptr && *(uint8_t*)(pHead + 0x29) == 1);
    assert(*(char**)(pHead + 8) == pHead);
    assert(*(char**)pHead == pHead);
    assert(*(char**)(pHead + 0x10) == pHead);
    // the set lives at +8, so its size at +0x38 of the set is vec2[8]
    assert(*(uint64_t*)((char*)vec2 + 8 + 0x38) == 0);   // vec2[8]

    delete pRoot; delete pL; delete pR; delete nil;
    ::operator delete(vec2[1]);          // the cursor node
    ::operator delete(vec2[7]);          // and the set's head
    ::operator delete(tree[0]);          // the first container's cursor node
    // (its head is the `nil` node freed above)
    printf("FLOWER_D146_OK: cursors, record set, container init\n");
    return 0;
}

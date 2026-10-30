// D145 — the erase with its rebalancing (0x140d955e0)
#include "modules/flower/src/stl_tree.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
using namespace flower::stl;

// node: left +0, parent +8, right +0x10, element +0x18, colour +0x28, nil +0x29
struct Node {
    Node* pLeft; Node* pParent; Node* pRight;
    uint64_t uElem0, uElem1;
    uint8_t cColor;     // 1 = black
    uint8_t cNil;       // non-zero marks the nil/head
    uint8_t tail[6];
};
static Node* NewNode(Node* nil, uint8_t color) {
    Node* p = new Node();
    std::memset(p, 0, sizeof *p);
    p->pLeft = nil; p->pRight = nil; p->pParent = nil;
    p->cColor = color; p->cNil = 0;
    return p;
}

int main() {
    g_pfnInvalidParameter = nullptr;

    // ---- a nil iterator is refused with the original text
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInit(tree);
    void* it[2];
    it[0] = tree;                      // container
    it[1] = tree[6];    // the head is the nil node
    void* out[2];
    bool bThrown = false;
    try { TreeErase(tree, out, it); }
    catch (const std::out_of_range& e) {
        bThrown = true;
        assert(std::strcmp(e.what(), "invalid map/set<T> iterator") == 0);
    }
    assert(bThrown);

    // ---- erasing a red leaf: unlink, leftmost moves up, size steps down
    {
        Node* nil = (Node*)tree[6];
        Node* pRoot = NewNode(nil, 1);
        Node* pL = NewNode(nil, 0);
        Node* pG = NewNode(nil, 0);
        pRoot->pLeft = pL; pRoot->pRight = pG;
        pL->pParent = pRoot; pG->pParent = pRoot;
        nil->pLeft = pL; nil->pRight = pG; nil->pParent = pRoot;
        *(uint64_t*)&tree[7] = 3;
        void* iter[2];
        iter[0] = tree; iter[1] = pL;
        void* res[2];
        assert(TreeErase(tree, res, iter) == res);
        assert(pRoot->pLeft == nil);
        assert(nil->pLeft == pRoot);
        assert(*(uint64_t*)&tree[7] == 2);
        assert(iter[1] == pRoot);            // the iterator advanced first
        assert(res[1] == pRoot);
        delete pRoot; delete pG; delete nil;
    }

    // ---- erasing a black node with two children: the successor takes its
    // place, links and colours swap, the size steps down
    {
        std::memset(tree, 0, sizeof tree);
        TreeInit(tree);
        Node* nil = (Node*)tree[6];
        Node* pRoot = NewNode(nil, 1);
        Node* pL = NewNode(nil, 0);
        Node* pG = NewNode(nil, 0);
        pRoot->pLeft = pL; pRoot->pRight = pG;
        pL->pParent = pRoot; pG->pParent = pRoot;
        nil->pLeft = pL; nil->pRight = pG; nil->pParent = pRoot;
        *(uint64_t*)&tree[7] = 3;
        void* iter[2];
        iter[0] = tree; iter[1] = pRoot;
        void* res[2];
        TreeErase(tree, res, iter);
        assert(nil->pParent == pG);          // the successor is the new root
        assert(pG->pLeft == pL);
        assert(pL->pParent == pG);
        assert(pG->pParent == nil);
        assert(pG->cColor == 1);             // took the erased node's colour
        assert(*(uint64_t*)&tree[7] == 2);
        assert(res[1] == pG);
        delete pG; delete pL;
        ::operator delete(tree[6]);
    }
    printf("FLOWER_D145_OK: erase unlink, successor swap, size\n");
    return 0;
}

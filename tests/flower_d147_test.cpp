// D147 — insertion with the hint and the rebalancing (0x140d95b20)
#include "modules/flower/src/stl_tree.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace flower::stl;

// node: left +0, parent +8, right +0x10, key +0x18, colour +0x28, nil +0x29
struct Node {
    Node* pLeft; Node* pParent; Node* pRight;
    uint64_t uKey, uVal;
    uint8_t cColor, cNil, tail[6];
};

// a harness insert: find the place the way a set does, then hand it to the port
static void* InsertKey(void** tree, uint64_t key) {
    char* head = (char*)tree[6];
    void* pRoot = *(void**)(head + 8);
    uint64_t elem[2] = { key, key * 10 };
    void* out[2];
    if (*(char*)((char*)pRoot + 0x29) != '\0') {      // empty: hint is the head
        TreeInsert(tree, out, 1, (void**)head, (void**)elem);
        return out[1];
    }
    void* p = pRoot;
    void* pParent = nullptr;
    char cLeft = 0;
    for (;;) {
        Node* n = (Node*)p;
        if (key < n->uKey) {
            if (n->pLeft->cNil) { pParent = p; cLeft = 1; break; }
            p = n->pLeft;
        } else {
            if (n->pRight->cNil) { pParent = p; cLeft = 0; break; }
            p = n->pRight;
        }
    }
    TreeInsert(tree, out, cLeft, (void**)pParent, (void**)elem);
    return out[1];
}

static int BlackHeight(Node* n) {
    if (n->cNil) return 1;
    const int l = BlackHeight(n->pLeft);
    const int r = BlackHeight(n->pRight);
    assert(l == r);                                   // equal black heights
    return l + (n->cColor == 1 ? 1 : 0);
}
static void CheckRed(Node* n) {
    if (n->cNil) return;
    if (n->cColor == 0) {                             // a red node has black kids
        assert(!n->pLeft->cNil ? n->pLeft->cColor == 1 : true);
        assert(!n->pRight->cNil ? n->pRight->cColor == 1 : true);
    }
    CheckRed(n->pLeft);
    CheckRed(n->pRight);
}
static void FreeTree(Node* n, Node* nil) {
    if (n->cNil) return;
    FreeTree(n->pLeft, nil);
    FreeTree(n->pRight, nil);
    delete n;
}

int main() {
    g_pfnInvalidParameter = nullptr;

    // ---- an empty set refuses nothing, and too long is length_error
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInitSelf(tree);
    tree[7] = (void*)0x0ffffffffffffffeULL;
    uint64_t elem[2] = { 1, 10 };
    void* out[2];
    bool bThrown = false;
    try { TreeInsert(tree, out, 1, (void**)tree[6], (void**)elem); }
    catch (const std::length_error& e) {
        bThrown = true;
        assert(std::strcmp(e.what(), "map/set<T> too long") == 0);
    }
    assert(bThrown);
    tree[7] = nullptr;

    // ---- seven keys in an order that walks both rotation shapes
    const uint64_t keys[] = { 10, 5, 15, 3, 7, 12, 20 };
    for (uint64_t k : keys) InsertKey(tree, k);
    assert((uint64_t)tree[7] == 7);

    char* head = (char*)tree[6];
    Node* nil = (Node*)head;
    Node* root = (Node*)*(void**)(head + 8);
    assert(root != nil && root->cColor == 1);          // the root is black
    assert(((Node*)*(void**)(head + 0))->uKey == 3);   // leftmost
    assert(((Node*)*(void**)(head + 0x10))->uKey == 20);// rightmost
    CheckRed(root);
    BlackHeight(root);

    // an in-order walk through the ported increment gives the sorted keys
    std::vector<uint64_t> seen;
    void* it[2];
    it[0] = tree;
    it[1] = *(void**)(head + 0);                       // the leftmost
    while (!((Node*)it[1])->cNil) {
        seen.push_back(((Node*)it[1])->uKey);
        TreeIncrement(it);
    }
    std::vector<uint64_t> want(keys, keys + 7);
    std::sort(want.begin(), want.end());
    assert(seen == want);

    FreeTree(root, nil);
    ::operator delete(tree[0]);
    ::operator delete(nil);
    printf("FLOWER_D147_OK: insert, rebalance, in-order\n");
    return 0;
}

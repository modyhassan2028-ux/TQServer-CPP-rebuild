// D149 — insert by value and insert with a hint (0x140d96560, 0x140d96b40)
#include "modules/flower/src/stl_tree.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace flower::stl;

struct Node {
    Node* pLeft; Node* pParent; Node* pRight;
    uint64_t uKey, uVal;
    uint8_t cColor, cNil, tail[6];
};
static Node* Find(Node* n, uint64_t key) {
    while (!n->cNil) {
        if (key < n->uKey) n = n->pLeft;
        else if (n->uKey < key) n = n->pRight;
        else return n;
    }
    return n;
}
static std::vector<uint64_t> Keys(void** tree) {
    std::vector<uint64_t> seen;
    void* it[2];
    it[0] = tree;
    it[1] = *(void**)((char*)tree[6] + 0);
    while (!((Node*)it[1])->cNil) {
        seen.push_back(((Node*)it[1])->uKey);
        TreeIncrement(it);
    }
    return seen;
}
static Node* Root(void** tree) { return (Node*)*(void**)((char*)tree[6] + 8); }

// the element the set carries is 16 bytes: the key first, then its payload
static Node* InsertValue(void** tree, uint32_t key, bool* pbInserted) {
    uint64_t elem[2] = { key, 0 };
    int64_t out[3] = { 0, 0, 0 };
    TreeInsertValue((int64_t*)tree, out, (uint32_t*)elem);
    if (pbInserted) *pbInserted = *(uint8_t*)((char*)out + 0x10) != 0;
    return (Node*)out[1];
}
static Node* InsertHint(void** tree, int64_t* hint, uint32_t key) {
    uint64_t elem[2] = { key, 0 };
    int64_t hout[2] = { 0, 0 };
    TreeInsertHint((int64_t*)tree, hout, hint, (uint32_t*)elem);
    return (Node*)hout[1];
}

int main() {
    g_pfnInvalidParameter = nullptr;
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInitSelf(tree);
    Node* nil = (Node*)tree[6];

    // ---- insert by value: the flag is set the first time only
    bool bIns = false;
    Node* p10 = InsertValue(tree, 10, &bIns);
    assert(bIns && p10 != nil && p10->uKey == 10);
    for (uint32_t v : { 5u, 15u, 3u, 7u }) {
        InsertValue(tree, v, &bIns);
        assert(bIns);
    }
    assert((uint64_t)tree[7] == 5);

    // ---- a duplicate answers the existing node with the flag clear
    Node* pDup = InsertValue(tree, 5, &bIns);
    assert(!bIns);
    assert((uint64_t)tree[7] == 5);
    assert(pDup == Find(Root(tree), 5));

    // ---- a hint before the leftmost inserts on that side (parent = leftmost)
    int64_t hint[2];
    hint[0] = (int64_t)tree[0];
    hint[1] = *(int64_t*)((char*)tree[6] + 0);        // the leftmost, 3
    assert(InsertHint(tree, hint, 1)->uKey == 1);

    // ---- a hint at the end inserts past the rightmost
    int64_t endHint[2];
    endHint[0] = (int64_t)tree[0];
    endHint[1] = (int64_t)tree[6];                    // the head
    assert(InsertHint(tree, endHint, 25)->uKey == 25);
    assert(((Node*)*(void**)((char*)tree[6] + 0x10))->uKey == 25);   // rightmost

    // ---- a useless hint falls through to the plain insert
    int64_t badHint[2];
    badHint[0] = (int64_t)tree[0];
    badHint[1] = (int64_t)Find(Root(tree), 3);        // 3 is far from 12
    assert(InsertHint(tree, badHint, 12)->uKey == 12);
    assert((uint64_t)tree[7] == 8);

    // ---- a duplicate through the hint keeps the count
    int64_t dupHint[2];
    dupHint[0] = (int64_t)tree[0];
    dupHint[1] = (int64_t)Find(Root(tree), 12);
    assert(InsertHint(tree, dupHint, 12)->uKey == 12);
    assert((uint64_t)tree[7] == 8);

    // ---- the whole set reads back in order
    std::vector<uint64_t> want = { 1, 3, 5, 7, 10, 12, 15, 25 };
    assert(Keys(tree) == want);

    TreeDestroy((int64_t*)tree);
    ::operator delete(tree[0]);
    printf("FLOWER_D149_OK: insert by value and by hint\n");
    return 0;
}

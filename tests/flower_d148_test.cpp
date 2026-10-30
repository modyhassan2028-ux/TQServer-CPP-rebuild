// D148 — the range erase and the teardown (0x140d961f0, 0x140d96400)
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

static void* InsertKey(void** tree, uint64_t key) {
    char* head = (char*)tree[6];
    void* pRoot = *(void**)(head + 8);
    uint64_t elem[2] = { key, key * 10 };
    void* out[2];
    if (*(char*)((char*)pRoot + 0x29) != '\0') {
        TreeInsert(tree, out, 1, (void**)head, (void**)elem);
        return out[1];
    }
    void* p = pRoot; void* pParent = nullptr; char cLeft = 0;
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

int main() {
    g_pfnInvalidParameter = nullptr;
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInitSelf(tree);
    const uint64_t keys[] = { 10, 5, 15, 3, 7, 12, 20 };
    for (uint64_t k : keys) InsertKey(tree, k);
    assert((uint64_t)tree[7] == 7);
    Node* nil = (Node*)tree[6];

    // ---- erase [node(3), node(12)): 3 and 7 go
    int64_t it[2], last[2], out[2];
    it[0] = (int64_t)tree[0]; it[1] = (int64_t)Find((Node*)*(void**)((char*)tree[6] + 8), 3);
    last[0] = (int64_t)tree[0]; last[1] = (int64_t)Find((Node*)*(void**)((char*)tree[6] + 8), 12);
    assert(TreeEraseRange((int64_t*)tree, out, it, last) == out);
    assert((uint64_t)tree[7] == 3);      // 3, 5, 7 and 10 are inside the range
    std::vector<uint64_t> left = Keys(tree);
    assert(left.size() == 3);
    assert(left[0] == 12 && left[1] == 15 && left[2] == 20);

    // ---- an empty range collapses to the clear-and-return path
    int64_t begin[2];
    begin[0] = (int64_t)tree[0];
    begin[1] = *(int64_t*)((char*)tree[6] + 0);          // the leftmost
    int64_t end2[2];
    end2[0] = (int64_t)tree[0];
    end2[1] = (int64_t)tree[6];                          // the head
    TreeEraseRange((int64_t*)tree, out, begin, begin);   // first == last
    assert(out[0] == (int64_t)tree[0]);
    (void)end2;

    // ---- the teardown empties the set and frees the head
    TreeDestroy((int64_t*)tree);
    assert(tree[6] == nullptr);
    assert(tree[7] == nullptr);
    ::operator delete(tree[0]);
    printf("FLOWER_D148_OK: range erase and teardown\n");
    return 0;
}

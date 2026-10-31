// D150 — erase by key, the distance, the single-node find and the vector erase
// (0x140d96850, 0x140d96760, 0x140d96990, 0x140d96470)
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
static uint64_t Size(void** tree) { return (uint64_t)tree[7]; }
// the element the set carries is 16 bytes: the key first, then its payload
static Node* InsertValue(void** tree, uint32_t key) {
    uint64_t elem[2] = { key, 0 };
    int64_t out[3] = { 0, 0, 0 };
    TreeInsertValue((int64_t*)tree, out, (uint32_t*)elem);
    return (Node*)out[1];
}
static uint64_t EraseKey(void** tree, uint32_t key) {
    uint32_t k = key;
    int64_t out[2] = { 0, 0 };
    return TreeEraseKey((int64_t*)tree, out, &k);
}

int main() {
    g_pfnInvalidParameter = nullptr;
    void* tree[8];
    std::memset(tree, 0, sizeof tree);
    TreeInitSelf(tree);
    Node* nil = (Node*)tree[6];
    const uint64_t want[7] = { 3, 5, 7, 10, 12, 15, 20 };
    for (int i = 0; i < 7; ++i) InsertValue(tree, (uint32_t)want[i]);
    assert(Size(tree) == 7);

    // ---- erase by key: the count, the members that remain, the size
    assert(EraseKey(tree, 10) == 1);
    std::vector<uint64_t> after = { 3, 5, 7, 12, 15, 20 };
    assert(Keys(tree) == after);
    assert(Size(tree) == 6);
    assert(EraseKey(tree, 99) == 0);                 // absent: nothing taken out
    assert(Size(tree) == 6);
    assert(EraseKey(tree, 3) == 1);                  // the leftmost
    std::vector<uint64_t> after2 = { 5, 7, 12, 15, 20 };
    assert(Keys(tree) == after2);
    assert(EraseKey(tree, 20) == 1);                 // the rightmost
    std::vector<uint64_t> after3 = { 5, 7, 12, 15 };
    assert(Keys(tree) == after3);
    assert(Size(tree) == 4);

    // ---- the single-node find: the lower-bound walk, then the exact match
    uint32_t k7 = 7, k8 = 8, k1 = 1, k100 = 100, k15 = 15;
    int64_t lb[2];
    TreeFindKey((int64_t*)tree, lb, &k7);
    assert(((Node*)lb[1])->uKey == 7);               // an exact hit
    TreeFindKey((int64_t*)tree, lb, &k8);
    assert(((Node*)lb[1]) == nil);                   // the candidate 12 is not equal
    TreeFindKey((int64_t*)tree, lb, &k1);
    assert(((Node*)lb[1]) == nil);                   // below everything: the end
    TreeFindKey((int64_t*)tree, lb, &k15);
    assert(((Node*)lb[1])->uKey == 15);              // the rightmost still hits
    TreeFindKey((int64_t*)tree, lb, &k100);
    assert(((Node*)lb[1]) == nil);                   // past the end: the head
    assert((void*)lb[0] == tree[0]);                 // the container travels with it

    // ---- the distance adds to the counter it is given
    int64_t itBegin[2], itEnd[2];
    itBegin[0] = (int64_t)tree[0];
    itBegin[1] = (int64_t)*(void**)((char*)tree[6] + 0);
    itEnd[0] = (int64_t)tree[0];
    itEnd[1] = (int64_t)tree[6];
    uint64_t uCount = 0;
    TreeDistance(itBegin, itEnd, &uCount);
    assert(uCount == 4);
    uCount = 10;                                     // a pre-loaded counter
    TreeDistance(itBegin, itEnd, &uCount);
    assert(uCount == 14);
    uCount = 7;
    TreeDistance(itBegin, itBegin, &uCount);         // an empty range adds nothing
    assert(uCount == 7);

    // ---- the vector range erase: the tail moves over the gap
    int64_t aVec[8];
    std::memset(aVec, 0, sizeof aVec);
    int64_t aStore[5] = { 10, 20, 30, 40, 50 };
    aVec[0] = (int64_t)&aVec;                        // the container tag
    aVec[3] = (int64_t)&aStore[0];                   // the begin
    aVec[4] = (int64_t)&aStore[5];                   // the end
    int64_t itFirst[2] = { aVec[0], (int64_t)&aStore[1] };
    int64_t itLast[2] = { aVec[0], (int64_t)&aStore[3] };
    int64_t out[2] = { 0, 0 };
    VectorEraseRange(aVec, out, itFirst, itLast);
    assert(aStore[0] == 10 && aStore[1] == 40 && aStore[2] == 50);
    assert((int64_t)(aVec[4] - aVec[3]) == 3 * 8);   // two members fewer
    assert(out[1] == (int64_t)&aStore[1]);           // the gap position comes back
    assert(out[0] == aVec[0]);
    // an empty range leaves the vector untouched
    int64_t itSame[2] = { aVec[0], (int64_t)&aStore[2] };
    VectorEraseRange(aVec, out, itSame, itSame);
    assert((int64_t)(aVec[4] - aVec[3]) == 3 * 8);
    assert(aStore[0] == 10 && aStore[1] == 40 && aStore[2] == 50);

    TreeDestroy((int64_t*)tree);
    ::operator delete(tree[0]);
    printf("FLOWER_D150_OK: erase by key, distance, single-node find, vector erase\n");
    return 0;
}

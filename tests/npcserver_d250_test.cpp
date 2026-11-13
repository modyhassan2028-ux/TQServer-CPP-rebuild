// D250 — the node builder and the insert repair, checked against the red-black invariants.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "modules/npcserver/unattributed/tree-insert.h"
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

namespace {

struct Node {
    long long left, parent, right;
    unsigned long long key, value;
    unsigned char color, isnil;
};

Node* g_aPool[64];
int g_nPool = 0;
long long g_aHeader[6];       // [0] leftmost, [1] root, [2] rightmost, [3] unused, [4] unused
long long g_aMap[8];          // [0] owner, [6] head, [7] size

void* FakeNew(long long nBytes) {
    assert(nBytes == 0x30);
    assert(g_nPool < 64);
    Node* p = (Node*)std::calloc(1, sizeof(Node));
    g_aPool[g_nPool++] = p;
    return p;
}

void ResetTree() {
    for (int i = 0; i < g_nPool; ++i) std::free(g_aPool[i]);
    g_nPool = 0;
    std::memset(g_aHeader, 0, sizeof g_aHeader);
    std::memset(g_aMap, 0, sizeof g_aMap);
    Node* pHead = (Node*)g_aHeader;
    pHead->left = (long long)pHead;
    pHead->parent = (long long)pHead;
    pHead->right = (long long)pHead;
    pHead->isnil = 1;
    pHead->color = 1;
    g_aMap[0] = 0xB0B;                       // the owner an iterator carries
    g_aMap[6] = (long long)pHead;
}

Node* Head() { return (Node*)g_aHeader; }
Node* Root() { return (Node*)Head()->parent; }

// walk the whole tree and check every red-black invariant the repair must keep
int Check(Node* pNode, Node* pH, unsigned long long nLow, unsigned long long nHigh,
          std::vector<unsigned long long>& order, int& nBlack) {
    if (pNode == pH) {                        // the head stands in for nil
        nBlack = 1;
        return 0;
    }
    assert(!pNode->isnil);
    assert(pNode->key > nLow && pNode->key < nHigh);
    assert(pNode->parent != 0);
    int nLeftBlack = 0, nRightBlack = 0;
    Check((Node*)pNode->left, pH, nLow, pNode->key, order, nLeftBlack);
    order.push_back(pNode->key);                 // in-order, so the vector comes out sorted
    Check((Node*)pNode->right, pH, pNode->key, nHigh, order, nRightBlack);
    assert(nLeftBlack == nRightBlack);         // equal black height on both sides
    if (pNode->color == 0) {                   // red: both children must be black
        assert(((Node*)pNode->left)->color == 1);
        assert(((Node*)pNode->right)->color == 1);
    }
    nBlack = nLeftBlack + (pNode->color == 1 ? 1 : 0);
    return 1;
}

void CheckTree(int nExpected) {
    Node* pH = Head();
    assert(pH->isnil == 1 && pH->color == 1);
    if (nExpected == 0) {
        assert(pH->parent == (long long)pH && pH->left == (long long)pH && pH->right == (long long)pH);
        assert(g_aMap[7] == 0);
        return;
    }
    Node* pRoot = Root();
    assert(pRoot != pH);
    assert(pRoot->color == 1);                 // the root is black
    std::vector<unsigned long long> order;
    int nBlack = 0;
    Check(pRoot, pH, 0, ~0ull, order, nBlack);
    assert((int)order.size() == nExpected);
    for (size_t i = 1; i < order.size(); ++i) assert(order[i - 1] < order[i]);   // sorted
    assert(((Node*)pH->left)->key == order.front());                            // leftmost
    assert(((Node*)pH->right)->key == order.back());                            // rightmost
    assert(g_aMap[7] == nExpected);
}

// the position map::insert would hand over: the parent the key belongs under, and which side it went
void FindHint(unsigned long long nKey, unsigned long long*& pHint, char& bWentLeft, bool& bKeyPresent) {
    Node* pH = Head();
    pHint = (unsigned long long*)pH;
    bWentLeft = 1;
    bKeyPresent = false;
    if (pH->parent == (long long)pH) return;   // empty: the head itself
    Node* pNode = Root();
    for (;;) {
        if (nKey == pNode->key) { bKeyPresent = true; return; }
        if (nKey < pNode->key) {
            if ((Node*)pNode->left == pH) { pHint = (unsigned long long*)pNode; bWentLeft = 1; return; }
            pNode = (Node*)pNode->left;
        } else {
            if ((Node*)pNode->right == pH) { pHint = (unsigned long long*)pNode; bWentLeft = 0; return; }
            pNode = (Node*)pNode->right;
        }
    }
}

void Insert(unsigned long long nKey) {
    unsigned long long* pHint = nullptr;
    char bWentLeft = 0;
    bool bPresent = false;
    FindHint(nKey, pHint, bWentLeft, bPresent);
    assert(!bPresent);
    unsigned long long aValue[2] = { nKey, nKey * 7 };
    unsigned long long aOut[2] = { 0, 0 };
    unsigned long long* pOut = FUN_140024000(g_aMap, aOut, bWentLeft, pHint, aValue);
    assert(pOut == aOut);
    assert(aOut[0] == 0xB0B);                       // the owner
    assert(((Node*)aOut[1])->key == nKey);          // the new node
    assert(((Node*)aOut[1])->value == nKey * 7);    // the value pair travelled intact
}

}  // namespace

int main() {
    g_pfnNpcOperatorNew = &FakeNew;

    // ---- 0x1400228f0: the builder writes every field of the 0x30-byte node --------------------------------
    {
        ResetTree();
        unsigned long long aValue[2] = { 0x1234, 0x5678 };
        Node* pNode = (Node*)FUN_1400228f0((long long)g_aMap, 0xAA, 0xBB, 0xCC, aValue, 0);
        assert(pNode != nullptr);
        assert(pNode->left == 0xAA && pNode->parent == 0xBB && pNode->right == 0xCC);
        assert(pNode->key == 0x1234 && pNode->value == 0x5678);
        assert(pNode->color == 0);          // a new node is red
        assert(pNode->isnil == 0);
    }

    // ---- 0x140024000: a whole tree, ascending, then descending, then mixed -------------------------------
    const unsigned long long aAsc[] = { 10, 20, 30, 40, 50, 60, 70 };
    ResetTree();
    for (unsigned long long k : aAsc) {
        Insert(k);
        CheckTree((int)g_aMap[7]);
    }

    ResetTree();
    for (int i = 6; i >= 0; --i) {
        Insert(aAsc[i]);
        CheckTree((int)g_aMap[7]);
    }

    const unsigned long long aMixed[] = { 50, 20, 80, 10, 30, 70, 90, 25, 35, 65, 85, 5, 15 };
    ResetTree();
    for (unsigned long long k : aMixed) {
        Insert(k);
        CheckTree((int)g_aMap[7]);
    }
    assert(g_aMap[7] == 13);
    for (unsigned long long k : aMixed) {     // every value is still reachable and intact
        Node* pNode = Root();
        Node* pH = Head();
        for (;;) {
            if (pNode == pH) { assert(!"key lost"); break; }
            if (pNode->key == k) { assert(pNode->value == k * 7); break; }
            pNode = (Node*)(k < pNode->key ? pNode->left : pNode->right);
        }
    }

    // ---- the first insert special case: the hint is the head itself ----------------------------------------
    ResetTree();
    {
        unsigned long long aValue[2] = { 42, 1 };
        unsigned long long aOut[2];
        FUN_140024000(g_aMap, aOut, 1, (unsigned long long*)Head(), aValue);
        Node* pH = Head();
        Node* pNew = (Node*)aOut[1];
        assert(pH->parent == (long long)pNew);      // root
        assert(pH->left == (long long)pNew);        // leftmost
        assert(pH->right == (long long)pNew);       // rightmost
        assert(pNew->color == 1);                   // and blackened on the way out
        assert(pNew->parent == (long long)pH);
        assert(g_aMap[7] == 1);
        CheckTree(1);
    }

    // ---- the size limit throws ---------------------------------------------------------------------------
    ResetTree();
    g_aMap[7] = (long long)0xffffffffffffffeULL;   // one past the image's limit
    {
        unsigned long long aValue[2] = { 1, 1 };
        unsigned long long aOut[2];
        bool bThrew = false;
        try {
            FUN_140024000(g_aMap, aOut, 1, (unsigned long long*)Head(), aValue);
        } catch (const std::length_error& e) {
            bThrew = true;
            assert(std::strcmp(e.what(), "map/set<T> too long") == 0);
        }
        assert(bThrew);
        assert(g_nPool == 0);                       // nothing was allocated before the throw
        assert(g_aMap[7] == (long long)0xffffffffffffffeULL);
    }

    ResetTree();
    assert(g_nNpcTreeInsert == 2);
    std::printf("NPCSERVER_D250_OK: node builder and insert repair keep the red-black invariants\n");
    return 0;
}

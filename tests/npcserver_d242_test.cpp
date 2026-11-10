// D242 — the two range erases: a sub-range, an empty range, and the whole-tree clear.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/tree-erase-range.h"
#include "modules/npcserver/unattributed/tree-erase.h"
#include "modules/npcserver/unattributed/tree-links.h"

using namespace tq;

static int g_deletes = 0;
static void* g_aFreed[8];
static int g_invalid = 0;

static void* FakeDelete(void* p) { g_aFreed[g_deletes++ & 7] = p; return p; }
static void Invalid(void) { ++g_invalid; }

struct Node {
    long long nLeft, nParent, nRight;
    long long aPad[2];
    char      cColor;              // +0x28
    char      cNil;                // +0x29
    char      aTail[6];
};

static Node g_aNode[6];
static Node g_nil;
static long long g_aHead[4];       // [0] leftmost, [1] root, [2] rightmost
static long long g_aTree[8];
static long long g_aOut[4];

static void Reset() {
    std::memset(g_aNode, 0, sizeof g_aNode);
    std::memset(&g_nil, 0, sizeof g_nil);
    std::memset(g_aHead, 0, sizeof g_aHead);
    std::memset(g_aTree, 0, sizeof g_aTree);
    std::memset(g_aOut, 0, sizeof g_aOut);
    g_nil.cColor = 1;
    g_nil.cNil = 1;
    for (int i = 0; i < 6; ++i) { g_aNode[i].cNil = 0; g_aNode[i].cColor = 1; }
    g_aTree[0] = (long long)g_aHead;      // the iterator owner slot the range checks compare against
    g_aTree[6] = (long long)g_aHead;
    g_aTree[7] = 0;
    g_invalid = 0;
}

static void Link(Node* pNode, Node* pParent, Node* pLeft, Node* pRight) {
    pNode->nParent = (long long)pParent;
    pNode->nLeft = (long long)pLeft;
    pNode->nRight = (long long)pRight;
}

// A(red) sits left of B(red) which sits left of the black root C; E(black) is the right child of C.
static void BuildTree() {
    Reset();
    Node* pC = &g_aNode[0];
    Node* pB = &g_aNode[1];
    Node* pA = &g_aNode[2];
    Node* pE = &g_aNode[3];
    Link(pC, &g_nil, pB, pE);
    Link(pB, pC, pA, &g_nil);
    Link(pA, pB, &g_nil, &g_nil);
    Link(pE, pC, &g_nil, &g_nil);
    pA->cColor = 0; pB->cColor = 0; pC->cColor = 1; pE->cColor = 1;
    g_aHead[0] = (long long)pA;
    g_aHead[1] = (long long)pC;
    ((long long*)g_aHead)[2] = (long long)pE;
    g_aTree[7] = 4;
    g_deletes = 0;
}

static int Count(long long nNode, int* pSeen) {
    if (nNode == (long long)&g_nil) return 0;
    int nIndex = (int)((nNode - (long long)&g_aNode[0]) / (long long)sizeof(Node));
    assert(nIndex >= 0 && nIndex < 6);
    assert(pSeen[nIndex] == 0);
    pSeen[nIndex] = 1;
    int n = 1;
    n += Count(g_aNode[nIndex].nLeft, pSeen);
    n += Count(g_aNode[nIndex].nRight, pSeen);
    return n;
}

static void Check(int nExpected) {
    int aSeen[6] = { 0, 0, 0, 0, 0, 0 };
    assert(Count(g_aHead[1], aSeen) == nExpected);
    assert(g_aTree[7] == nExpected);
    // every live node points back at its parent
    for (int i = 0; i < 6; ++i) {
        if (!aSeen[i]) continue;
        Node* pNode = &g_aNode[i];
        if (pNode->nLeft != (long long)&g_nil) {
            assert(((Node*)pNode->nLeft)->nParent == (long long)pNode);
        }
        if (pNode->nRight != (long long)&g_nil) {
            assert(((Node*)pNode->nRight)->nParent == (long long)pNode);
        }
    }
}

int main() {
    g_pfnNpcOperatorDelete = &FakeDelete;
    g_pfnNpcInvalidParameter = &Invalid;
    g_pfnNpcThrowOutOfRange = nullptr;      // never reached in these ranges

    assert(g_nNpcTreeEraseRange == 2);
    int nSub = 0, nAll = 0, nEmpty = 0;

    for (int i = 0; i < g_nNpcTreeEraseRange; ++i) {
        const NpcTreeEraseRangeEntry& e = g_aNpcTreeEraseRange[i];
        typedef long long* (*EraseRangeFn)(long long*, long long*, long long*, long long*);
        EraseRangeFn pfn = (EraseRangeFn)e.pfn;

        // [A, C): two red nodes go, the black root stays, and C comes back as the new position
        {
            BuildTree();
            Node* pC = &g_aNode[0];
            Node* pB = &g_aNode[1];
            Node* pA = &g_aNode[2];
            long long aFirst[2] = { g_aTree[0], (long long)pA };
            long long aLast[2]  = { g_aTree[0], (long long)pC };
            long long* pRet = pfn(g_aTree, g_aOut, aFirst, aLast);
            assert(pRet == g_aOut);
            assert(g_invalid == 0);
            assert(g_deletes == 2);
            assert(g_aFreed[0] == (void*)pA);
            assert(g_aFreed[1] == (void*)pB);            // the successor was stepped to before the erase
            assert(aFirst[1] == (long long)pC);          // the iterator came back on the last node
            assert(g_aOut[1] == (long long)pC);
            assert(g_aOut[0] == g_aTree[0]);
            Check(2);
            ++nSub;
        }

        // an empty range does nothing at all
        {
            BuildTree();
            Node* pC = &g_aNode[0];
            long long aFirst[2] = { g_aTree[0], (long long)pC };
            long long aLast[2]  = { g_aTree[0], (long long)pC };
            pfn(g_aTree, g_aOut, aFirst, aLast);
            assert(g_deletes == 0);
            assert(g_aOut[1] == (long long)pC);
            Check(4);
            ++nEmpty;
        }

        // the whole tree: first is the leftmost node and last is the head, so the clear runs instead
        {
            BuildTree();
            Node* pA = &g_aNode[2];
            long long aFirst[2] = { g_aTree[0], (long long)pA };
            long long aLast[2]  = { g_aTree[0], (long long)g_aHead };
            pfn(g_aTree, g_aOut, aFirst, aLast);
            assert(g_deletes == 4);                      // every node, through the clear
            assert(g_aTree[7] == 0);
            assert(g_aHead[1] == (long long)g_aHead);    // the head is closed on itself
            assert(g_aHead[0] == (long long)g_aHead);
            assert(((long long*)g_aHead)[2] == (long long)g_aHead);
            assert(g_aOut[1] == (long long)g_aHead);     // the end iterator
            ++nAll;
        }
    }

    assert(nSub == 2 && nEmpty == 2 && nAll == 2);
    std::printf("NPCSERVER_D242_OK: range erase, empty range and full clear\n");
    return 0;
}

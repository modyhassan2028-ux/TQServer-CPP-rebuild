// D241 — the erase-with-iterator pair, its successor and its rotations.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string>
#include "modules/npcserver/unattributed/tree-erase.h"

using namespace tq;

static std::string g_thrown;
static int g_deletes = 0;
static void* g_aFreed[8];

static void* FakeDelete(void* p) { g_aFreed[g_deletes++ & 7] = p; return p; }
static void FakeThrow(const char* pszMessage) { g_thrown = pszMessage; throw std::runtime_error(pszMessage); }

struct Node {
    long long nLeft, nParent, nRight;
    long long aPad[2];             // +0x18, +0x20
    char      cColor;              // +0x28
    char      cNil;                // +0x29
    char      aTail[6];
};

static Node g_aNode[8];
static Node g_nil;
static long long g_aHead[4];   // head+0 = leftmost, +8 = root, +0x10 = rightmost
static long long g_aTree[8];
static long long g_aOut[4];

static void Reset() {
    std::memset(g_aNode, 0, sizeof g_aNode);
    std::memset(&g_nil, 0, sizeof g_nil);
    std::memset(g_aHead, 0, sizeof g_aHead);
    std::memset(g_aTree, 0, sizeof g_aTree);
    std::memset(g_aOut, 0, sizeof g_aOut);
    g_nil.cColor = 1;                 // the sentinel is black
    g_nil.cNil = 1;
    for (int i = 0; i < 8; ++i) { g_aNode[i].cNil = 0; g_aNode[i].cColor = 1; }
    g_aTree[6] = (long long)g_aHead;
    g_aTree[7] = 0;
    g_deletes = 0;
}

static void Link(Node* pNode, Node* pParent, Node* pLeft, Node* pRight) {
    pNode->nParent = (long long)pParent;
    pNode->nLeft = (long long)pLeft;
    pNode->nRight = (long long)pRight;
}

// walk from the root and check every link, then confirm the head's cached ends
static int Walk(long long* pHead, long long nNode, long long nParent, int* pSeen, int nLimit) {
    if (nNode == (long long)&g_nil) return 0;
    assert(nNode != 0);
    int nIndex = (int)((nNode - (long long)&g_aNode[0]) / (long long)sizeof(Node));
    assert(nIndex >= 0 && nIndex < 8);
    assert(pSeen[nIndex] == 0);                      // no cycles
    pSeen[nIndex] = 1;
    assert(g_aNode[nIndex].nParent == nParent);      // the parent link is consistent
    int n = 1;
    n += Walk(pHead, g_aNode[nIndex].nLeft, nNode, pSeen, nLimit);
    n += Walk(pHead, g_aNode[nIndex].nRight, nNode, pSeen, nLimit);
    assert(n <= nLimit);
    return n;
}

static void Check(long long* pHead, int nExpected, int nLimit) {
    int aSeen[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int n = Walk(pHead, pHead[1], (long long)&g_nil, aSeen, nLimit);
    assert(n == nExpected);
}

int main() {
    g_pfnNpcOperatorDelete = &FakeDelete;
    g_pfnNpcThrowOutOfRange = &FakeThrow;

    assert(g_nNpcTreeErase == 5);
    int nErase = 0, nSucc = 0, nRotL = 0, nRotR = 0;

    for (int i = 0; i < g_nNpcTreeErase; ++i) {
        const NpcTreeEraseEntry& e = g_aNpcTreeErase[i];

        if (std::strcmp(e.pszKind, "erase") == 0) {
            typedef long long* (*EraseFn)(long long*, long long*, long long*);
            EraseFn pfn = (EraseFn)e.pfn;

            // the end node cannot be erased: the message is reported and nothing moves
            {
                Reset();
                long long aIter[2] = { (long long)g_aTree, (long long)&g_nil };
                g_thrown.clear();
                bool bThrew = false;
                try {
                    pfn(g_aTree, g_aOut, aIter);
                } catch (const std::runtime_error&) {
                    bThrew = true;
                }
                assert(bThrew);
                assert(g_thrown == "invalid map/set<T> iterator");
                assert(g_deletes == 0);
            }

            // a red leaf: the node goes, its parent takes the empty slot, the successor comes back
            {
                Reset();
                Node* pB = &g_aNode[0];
                Node* pA = &g_aNode[1];
                Node* pC = &g_aNode[2];
                Link(pB, &g_nil, pA, pC);
                Link(pA, pB, &g_nil, &g_nil);
                Link(pC, pB, &g_nil, &g_nil);
                pB->cColor = 1; pA->cColor = 0; pC->cColor = 1;
                g_aHead[0] = (long long)pA; g_aHead[1] = (long long)pB; ((long long*)g_aHead)[2] = (long long)pC;
                g_aTree[7] = 3;
                long long aIter[2] = { (long long)g_aTree, (long long)pA };
                long long* pRet = pfn(g_aTree, g_aOut, aIter);
                assert(pRet == g_aOut);
                assert(g_deletes == 1 && g_aFreed[0] == (void*)pA);
                assert(g_aTree[7] == 2);
                assert(g_aOut[1] == (long long)pB);                 // the successor
                assert(g_aHead[1] == (long long)pB);                // the root stayed put
                assert((void*)pB->nLeft == (void*)&g_nil);
                Check(g_aHead, 2, 3);
            }

            // a black leaf: the same rewire, and the nil sentinel is painted black by the rebalance
            {
                Reset();
                Node* pB = &g_aNode[0];
                Node* pA = &g_aNode[1];
                Node* pC = &g_aNode[2];
                Link(pB, &g_nil, pA, pC);
                Link(pA, pB, &g_nil, &g_nil);
                Link(pC, pB, &g_nil, &g_nil);
                g_aHead[0] = (long long)pA; g_aHead[1] = (long long)pB; ((long long*)g_aHead)[2] = (long long)pC;
                g_aTree[7] = 3;
                long long aIter[2] = { (long long)g_aTree, (long long)pA };
                pfn(g_aTree, g_aOut, aIter);
                assert(g_deletes == 1 && g_aFreed[0] == (void*)pA);
                assert(g_aTree[7] == 2);
                assert(g_aOut[1] == (long long)pB);
                assert(g_nil.cColor == 1);                          // the sentinel is black before and after
                Check(g_aHead, 2, 3);
            }

            // a black node with one black child: the child is promoted and the rebalance walks upward
            {
                Reset();
                Node* pRoot = &g_aNode[0];
                Node* pMid = &g_aNode[1];
                Node* pLeaf = &g_aNode[2];
                Node* pChild = &g_aNode[3];
                Node* pRight = &g_aNode[4];
                Link(pRoot, &g_nil, pMid, pRight);
                Link(pMid, pRoot, pLeaf, &g_nil);
                Link(pLeaf, pMid, pChild, &g_nil);
                Link(pChild, pLeaf, &g_nil, &g_nil);
                Link(pRight, pRoot, &g_nil, &g_nil);
                g_aHead[0] = (long long)pChild; g_aHead[1] = (long long)pRoot; ((long long*)g_aHead)[2] = (long long)pRight;
                g_aTree[7] = 5;
                long long aIter[2] = { (long long)g_aTree, (long long)pLeaf };
                pfn(g_aTree, g_aOut, aIter);
                assert(g_deletes == 1 && g_aFreed[0] == (void*)pLeaf);
                assert(g_aTree[7] == 4);
                assert(g_aOut[1] == (long long)pMid);               // the parent, since the leaf was a left child
                assert((void*)pMid->nLeft == (void*)pChild);        // the child was promoted into its place
                assert((void*)pChild->nParent == (void*)pMid);
                Check(g_aHead, 4, 5);
            }

            // both children present: the successor is spliced into the node's place
            {
                Reset();
                Node* pB = &g_aNode[0];
                Node* pA = &g_aNode[1];
                Node* pC = &g_aNode[2];
                Link(pB, &g_nil, pA, pC);
                Link(pA, pB, &g_nil, &g_nil);
                Link(pC, pB, &g_nil, &g_nil);
                pA->cColor = 0; pC->cColor = 0;                     // pB is the black root
                g_aHead[0] = (long long)pA; g_aHead[1] = (long long)pB; ((long long*)g_aHead)[2] = (long long)pC;
                g_aTree[7] = 3;
                long long aIter[2] = { (long long)g_aTree, (long long)pB };
                pfn(g_aTree, g_aOut, aIter);
                assert(g_deletes == 1 && g_aFreed[0] == (void*)pB);
                assert(g_aTree[7] == 2);
                assert(g_aOut[1] == (long long)pC);                 // the successor took the root's place
                assert(g_aHead[1] == (long long)pC);
                assert((void*)pC->nLeft == (void*)pA);              // and inherited the left child
                assert((void*)pA->nParent == (void*)pC);
                assert(pC->cColor == 1);                            // the colours were exchanged
                assert(pA->cColor == 0);
                Check(g_aHead, 2, 3);
            }
            ++nErase;

        } else if (std::strcmp(e.pszKind, "successor") == 0) {
            Reset();
            Node* pTarget = &g_aNode[0];
            Node* pRight = &g_aNode[1];
            Node* pLeftmost = &g_aNode[2];
            Link(pTarget, &g_nil, &g_nil, pRight);
            Link(pRight, pTarget, pLeftmost, &g_nil);
            Link(pLeftmost, pRight, &g_nil, &g_nil);
            long long aIter[2] = { (long long)g_aTree, (long long)pTarget };
            ((void (*)(long long*))e.pfn)(aIter);
            assert(aIter[1] == (long long)pLeftmost);
            ++nSucc;

        } else if (std::strcmp(e.pszKind, "rotate-left") == 0) {
            Reset();
            Node* pRoot = &g_aNode[0];
            Node* pRight = &g_aNode[1];
            Node* pInner = &g_aNode[2];
            Link(pRoot, &g_nil, &g_nil, pRight);
            Link(pRight, pRoot, pInner, &g_nil);
            Link(pInner, pRight, &g_nil, &g_nil);
            g_aHead[1] = (long long)pRoot;
            ((void (*)(long long, long long))e.pfn)((long long)g_aTree, (long long)pRoot);
            assert((void*)g_aHead[1] == (void*)pRight);
            assert((void*)pRoot->nRight == (void*)pInner);
            assert((void*)pInner->nParent == (void*)pRoot);
            assert((void*)pRight->nLeft == (void*)pRoot);
            ++nRotL;

        } else if (std::strcmp(e.pszKind, "rotate-right") == 0) {
            Reset();
            Node* pRoot = &g_aNode[0];
            Node* pLeft = &g_aNode[1];
            Node* pInner = &g_aNode[2];
            Link(pRoot, &g_nil, pLeft, &g_nil);
            Link(pLeft, pRoot, &g_nil, pInner);
            Link(pInner, pLeft, &g_nil, &g_nil);
            g_aHead[1] = (long long)pRoot;
            ((void (*)(long long, long long*))e.pfn)((long long)g_aTree, (long long*)pRoot);
            assert((void*)g_aHead[1] == (void*)pLeft);
            assert((void*)pRoot->nLeft == (void*)pInner);
            assert((void*)pInner->nParent == (void*)pRoot);
            assert((void*)pLeft->nRight == (void*)pRoot);
            ++nRotR;
        } else {
            assert(!"unknown kind in the manifest");
        }
    }

    assert(nErase == 2 && nSucc == 1 && nRotL == 1 && nRotR == 1);
    std::printf("NPCSERVER_D241_OK: erase pair, successor and rotations\n");
    return 0;
}

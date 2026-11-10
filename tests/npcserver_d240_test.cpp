// D240 — the successor step and the two rotations, exercised on hand-built node graphs.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/tree-links.h"

using namespace tq;

static int g_invalid = 0;
static void Invalid(void) { ++g_invalid; }

struct Node {
    long long nLeft;
    long long nParent;
    long long nRight;
    long long aPad[2];        // +0x18, +0x20
    char      cColor;         // +0x28
    char      cNil;           // +0x29
    char      aTail[6];
};

static Node g_aNode[8];
static Node g_nil;
static long long g_aHead[4];
static long long g_aTree[8];

static void Reset() {
    std::memset(g_aNode, 0, sizeof g_aNode);
    std::memset(&g_nil, 0, sizeof g_nil);
    std::memset(g_aHead, 0, sizeof g_aHead);
    std::memset(g_aTree, 0, sizeof g_aTree);
    g_nil.cNil = 1;                                   // the sentinel
    for (int i = 0; i < 8; ++i) g_aNode[i].cNil = 0;  // the rest are real
    g_aTree[6] = (long long)g_aHead;                  // the head sits at tree + 0x30
    g_invalid = 0;
}

static void Link(Node* pNode, Node* pParent, Node* pLeft, Node* pRight) {
    pNode->nParent = (long long)pParent;
    pNode->nLeft = (long long)pLeft;
    pNode->nRight = (long long)pRight;
}

int main() {
    g_pfnNpcInvalidParameter = &Invalid;

    assert(g_nNpcTreeLink == 3);
    const char* aSeen[3] = { 0, 0, 0 };
    for (int i = 0; i < g_nNpcTreeLink; ++i) aSeen[i] = g_aNpcTreeLink[i].pszKind;

    // ---- successor ----
    {
        // the node has a right subtree: the successor is its leftmost node
        Reset();
        Node* pTarget = &g_aNode[0];
        Node* pRight = &g_aNode[1];
        Node* pLeftmost = &g_aNode[2];
        Link(pTarget, &g_nil, &g_nil, pRight);
        Link(pRight, pTarget, pLeftmost, &g_nil);
        Link(pLeftmost, pRight, &g_nil, &g_nil);
        long long aIter[2] = { (long long)g_aTree, (long long)pTarget };
        FUN_140021f50(aIter);
        assert(g_invalid == 0);
        assert(aIter[1] == (long long)pLeftmost);

        // no right subtree: it climbs while the node is its parent's right child
        Reset();
        Node* pTop = &g_aNode[0];
        Node* pMid = &g_aNode[1];
        Node* pLow = &g_aNode[2];
        Link(pTop, &g_nil, &g_nil, pMid);
        Link(pMid, pTop, &g_nil, pLow);
        Link(pLow, pMid, &g_nil, &g_nil);
        long long aClimb[2] = { (long long)g_aTree, (long long)pLow };
        FUN_140021f50(aClimb);
        assert(g_invalid == 0);
        // pLow is the tree's maximum, so the climb runs past the root and stops on the head
        assert(aClimb[1] == (long long)&g_nil);

        // the end node cannot be stepped
        Reset();
        long long aEnd[2] = { (long long)g_aTree, (long long)&g_nil };
        FUN_140021f50(aEnd);
        assert(g_invalid == 1);
        assert(aEnd[1] == (long long)&g_nil);          // the iterator is left where it was

        // a null owner is reported first
        Reset();
        long long aNull[2] = { 0, (long long)&g_nil };
        FUN_140021f50(aNull);
        assert(g_invalid == 2);                        // the owner complained, then the end node

        // ---- rotate left: the node is the root ----
        Reset();
        Node* pP = &g_aNode[0];
        Node* pR = &g_aNode[1];
        Node* pInner = &g_aNode[2];
        Link(pP, &g_nil, &g_nil, pR);
        Link(pR, pP, pInner, &g_nil);
        Link(pInner, pR, &g_nil, &g_nil);
        g_aHead[1] = (long long)pP;                    // head + 8 is the root
        FUN_140021e60((long long)g_aTree, (long long)pP);
        assert((void*)g_aHead[1] == (void*)pR);          // the root moved down into R
        assert((void*)pP->nRight == (void*)pInner);      // P took R's left child
        assert((void*)pInner->nParent == (void*)pP);     // and the inner node was reparented
        assert((void*)pR->nLeft == (void*)pP);
        assert((void*)pP->nParent == (void*)pR);
        assert((void*)pR->nParent == (void*)&g_nil);

        // ---- rotate left: the node is a left child ----
        Reset();
        pP = &g_aNode[0]; pR = &g_aNode[1]; pInner = &g_aNode[2];
        Node* pG = &g_aNode[3];
        Link(pG, &g_nil, pP, &g_nil);
        Link(pP, pG, &g_nil, pR);
        Link(pR, pP, pInner, &g_nil);
        Link(pInner, pR, &g_nil, &g_nil);
        g_aHead[1] = (long long)pG;
        FUN_140021e60((long long)g_aTree, (long long)pP);
        assert((void*)pG->nLeft == (void*)pR);           // the grandparent's left link now names R
        assert((void*)pR->nParent == (void*)pG);
        assert((void*)pR->nLeft == (void*)pP);
        assert((void*)pP->nRight == (void*)pInner);

        // ---- rotate left: the node is a right child ----
        Reset();
        pP = &g_aNode[0]; pR = &g_aNode[1]; pInner = &g_aNode[2];
        pG = &g_aNode[3];
        Link(pG, &g_nil, &g_nil, pP);
        Link(pP, pG, &g_nil, pR);
        Link(pR, pP, pInner, &g_nil);
        Link(pInner, pR, &g_nil, &g_nil);
        g_aHead[1] = (long long)pG;
        FUN_140021e60((long long)g_aTree, (long long)pP);
        assert((void*)pG->nRight == (void*)pR);
        assert((void*)pR->nParent == (void*)pG);

        // ---- rotate right: the node is the root ----
        Reset();
        pP = &g_aNode[0];
        Node* pL = &g_aNode[1];
        pInner = &g_aNode[2];
        Link(pP, &g_nil, pL, &g_nil);
        Link(pL, pP, &g_nil, pInner);
        Link(pInner, pL, &g_nil, &g_nil);
        g_aHead[1] = (long long)pP;
        FUN_140021ec0((long long)g_aTree, (long long*)pP);
        assert((void*)g_aHead[1] == (void*)pL);
        assert((void*)pP->nLeft == (void*)pInner);
        assert((void*)pInner->nParent == (void*)pP);
        assert((void*)pL->nRight == (void*)pP);
        assert((void*)pP->nParent == (void*)pL);
        assert((void*)pL->nParent == (void*)&g_nil);

        // ---- rotate right: the node is a right child ----
        Reset();
        pP = &g_aNode[0]; pL = &g_aNode[1]; pInner = &g_aNode[2];
        pG = &g_aNode[3];
        Link(pG, &g_nil, &g_nil, pP);
        Link(pP, pG, pL, &g_nil);
        Link(pL, pP, &g_nil, pInner);
        Link(pInner, pL, &g_nil, &g_nil);
        g_aHead[1] = (long long)pG;
        FUN_140021ec0((long long)g_aTree, (long long*)pP);
        assert((void*)pG->nRight == (void*)pL);
        assert((void*)pL->nParent == (void*)pG);
        assert((void*)pL->nRight == (void*)pP);

        // ---- rotate right: the node is a left child ----
        Reset();
        pP = &g_aNode[0]; pL = &g_aNode[1]; pInner = &g_aNode[2];
        pG = &g_aNode[3];
        Link(pG, &g_nil, pP, &g_nil);
        Link(pP, pG, pL, &g_nil);
        Link(pL, pP, &g_nil, pInner);
        Link(pInner, pL, &g_nil, &g_nil);
        g_aHead[1] = (long long)pG;
        FUN_140021ec0((long long)g_aTree, (long long*)pP);
        assert((void*)pG->nLeft == (void*)pL);
        assert((void*)pL->nParent == (void*)pG);
    }

    assert(std::strcmp(aSeen[0], "successor") == 0);
    assert(std::strcmp(aSeen[1], "rotate-left") == 0);
    assert(std::strcmp(aSeen[2], "rotate-right") == 0);
    std::printf("NPCSERVER_D240_OK: successor and both rotations\n");
    return 0;
}

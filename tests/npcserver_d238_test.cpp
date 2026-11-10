// D238 — the red-black tree helpers: two sentinel heads, two subtree frees, two tree clears.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/map-tree.h"

using namespace tq;

static char g_aBlock[0x30];
static int g_news = 0, g_deletes = 0;
static void* g_aFreed[16];

static void* FakeNew(long long nBytes) { ++g_news; assert(nBytes == 0x30); return g_aBlock; }
static void* FakeDelete(void* p) { g_aFreed[g_deletes++ & 15] = p; return p; }

// a three-node tree: head -> child A (left) -> child B (right of A), all with the +0x29 flag clear
struct Node { long long aLink[2]; long long pParent; char aPad[0x18]; };   // the image walks 0x30-byte nodes
static Node g_aNodes[4];

static void Reset() {
    std::memset(g_aBlock, 0xEE, sizeof g_aBlock);
    std::memset(g_aNodes, 0, sizeof g_aNodes);
    for (int i = 0; i < 4; ++i) *(char*)((long long)&g_aNodes[i] + 0x29) = 0;
    g_news = 0; g_deletes = 0;
}

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcOperatorDelete = &FakeDelete;

    assert(g_nNpcMapTree == 6);
    int nHead = 0, nFree = 0, nClear = 0;

    for (int i = 0; i < g_nNpcMapTree; ++i) {
        const NpcMapTreeEntry& e = g_aNpcMapTree[i];
        assert(e.pszAddress && e.pszKind && e.pfn);

        if (std::strcmp(e.pszKind, "sentinel-head") == 0) {
            Reset();
            void* pHead = ((void* (*)(void))e.pfn)();
            assert(g_news == 1);
            assert(pHead == (void*)g_aBlock);
            assert(*(long long*)(g_aBlock + 0) == 0);
            assert(*(long long*)(g_aBlock + 8) == 0);
            assert(*(long long*)(g_aBlock + 0x10) == 0);
            assert(*(unsigned char*)(g_aBlock + 0x28) == 1);
            assert(*(unsigned char*)(g_aBlock + 0x29) == 0);
            ++nHead;

        } else if (std::strcmp(e.pszKind, "subtree-free") == 0) {
            Reset();
            // head(clear) -> [2] = B(clear) -> [2] = head ; B[0] = A(clear) -> head ; A[0] = head
            Node* pHeadNode = &g_aNodes[0];
            *(char*)((long long)pHeadNode + 0x29) = 1;            // the walk stops on a flagged node
            Node* pA = &g_aNodes[1];
            Node* pB = &g_aNodes[2];
            pB->aLink[0] = (long long)pA;
            pB->aLink[1] = (long long)pHeadNode;
            pA->aLink[0] = (long long)pHeadNode;
            pA->aLink[1] = (long long)pHeadNode;
            pA->pParent = (long long)pHeadNode;      // [2] is the right link in this layout
            pB->pParent = (long long)pHeadNode;
            pHeadNode->aLink[0] = (long long)pHeadNode;
            pHeadNode->aLink[1] = (long long)pB;     // the head's parent is the root

            ((void (*)(void*, long long*))e.pfn)((void*)0x1234, (long long*)pB);
            // the entry node goes first, then the node its left link named; the head is never touched
            assert(g_deletes == 2);
            assert(g_aFreed[0] == (void*)pB);
            assert(g_aFreed[1] == (void*)pA);
            ++nFree;

        } else if (std::strcmp(e.pszKind, "tree-clear") == 0) {
            Reset();
            long long aSet[8];
            std::memset(aSet, 0, sizeof aSet);
            Node* pHeadNode = &g_aNodes[0];
            *(char*)((long long)pHeadNode + 0x29) = 1;
            Node* pA = &g_aNodes[1];
            pA->aLink[0] = (long long)pHeadNode;      // leftmost node points its left link at the head
            pA->aLink[1] = (long long)pHeadNode;
            pA->pParent = (long long)pHeadNode;        // one node: all three links meet the head
            pHeadNode->aLink[0] = (long long)pHeadNode;
            pHeadNode->aLink[1] = (long long)pA;       // the head's parent is the root
            aSet[6] = (long long)pHeadNode;
            aSet[7] = 0x99;

            ((void (*)(long long))e.pfn)((long long)aSet);
            assert(g_deletes == 1);
            assert(g_aFreed[0] == (void*)pA);
            assert(pHeadNode->aLink[1] == (long long)pHeadNode);   // the head closes on itself
            assert(pHeadNode->aLink[0] == (long long)pHeadNode);
            assert(*(long long*)((long long)pHeadNode + 0x10) == (long long)pHeadNode);
            assert(aSet[7] == 0);                                  // the count is cleared
            ++nClear;
        }
    }

    assert(nHead == 2 && nFree == 2 && nClear == 2);
    std::printf("NPCSERVER_D238_OK: 6 red-black tree helpers\n");
    return 0;
}

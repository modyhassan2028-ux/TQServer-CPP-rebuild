// Transcribed from NpcServer.exe; see tree-links.h.
#include "modules/npcserver/unattributed/tree-links.h"

namespace tq {

// +0 / +8 / +0x10 / +0x28 / +0x29 of a container node
#define NPC_NODE_LEFT(p)   (*(long long*)((long long)(p) + 0x00))
#define NPC_NODE_PARENT(p) (*(long long*)((long long)(p) + 0x08))
#define NPC_NODE_RIGHT(p)  (*(long long*)((long long)(p) + 0x10))
#define NPC_NODE_COLOR(p)  (*(char*)((long long)(p) + 0x28))
#define NPC_NODE_NIL(p)    (*(char*)((long long)(p) + 0x29))

// 0x140021f50 - the successor of the iterator's node
void FUN_140021f50(long long* pIter) {
    if (pIter[0] == 0) {
        g_pfnNpcInvalidParameter();
    }
    long long nNode = pIter[1];
    if (NPC_NODE_NIL(nNode) == '\0') {
        long long nRight = NPC_NODE_RIGHT(nNode);
        if (NPC_NODE_NIL(nRight) != '\0') {
            // no right subtree: climb while the node is its parent's right child
            nNode = NPC_NODE_PARENT(nNode);
            char nFlag = NPC_NODE_NIL(nNode);
            while ((nFlag == '\0') && (pIter[1] == NPC_NODE_RIGHT(nNode))) {
                pIter[1] = nNode;
                nNode = NPC_NODE_PARENT(nNode);
                nFlag = NPC_NODE_NIL(nNode);
            }
            pIter[1] = nNode;
            return;
        }
        // otherwise the successor is the leftmost node of the right subtree
        char nFlag = NPC_NODE_NIL(NPC_NODE_LEFT(nRight));
        long long nWalk = NPC_NODE_LEFT(nRight);
        while (nFlag == '\0') {
            nFlag = NPC_NODE_NIL(NPC_NODE_LEFT(nWalk));
            nRight = nWalk;
            nWalk = NPC_NODE_LEFT(nWalk);
        }
        pIter[1] = nRight;
        return;
    }
    g_pfnNpcInvalidParameter();
    return;
}

// 0x140021e60 - rotate left over pNode
void FUN_140021e60(long long pTree, long long pNode) {
    long long nRight = NPC_NODE_RIGHT(pNode);
    NPC_NODE_RIGHT(pNode) = NPC_NODE_LEFT(nRight);
    if (NPC_NODE_NIL(NPC_NODE_LEFT(nRight)) == '\0') {
        NPC_NODE_PARENT(NPC_NODE_LEFT(nRight)) = pNode;
    }
    NPC_NODE_PARENT(nRight) = NPC_NODE_PARENT(pNode);
    if (pNode == *(long long*)(*(long long*)(pTree + 0x30) + 8)) {
        *(long long*)(*(long long*)(pTree + 0x30) + 8) = nRight;
        NPC_NODE_LEFT(nRight) = pNode;
        NPC_NODE_PARENT(pNode) = nRight;
        return;
    }
    long long nParent = NPC_NODE_PARENT(pNode);
    if (pNode == NPC_NODE_LEFT(nParent)) {
        NPC_NODE_LEFT(nParent) = nRight;
        NPC_NODE_LEFT(nRight) = pNode;
        NPC_NODE_PARENT(pNode) = nRight;
        return;
    }
    NPC_NODE_RIGHT(nParent) = nRight;
    NPC_NODE_LEFT(nRight) = pNode;
    NPC_NODE_PARENT(pNode) = nRight;
    return;
}

// 0x140021ec0 - rotate right over pNode
void FUN_140021ec0(long long pTree, long long* pNode) {
    long long nLeft = NPC_NODE_LEFT(pNode);
    NPC_NODE_LEFT(pNode) = NPC_NODE_RIGHT(nLeft);
    if (NPC_NODE_NIL(NPC_NODE_RIGHT(nLeft)) == '\0') {
        NPC_NODE_PARENT(NPC_NODE_RIGHT(nLeft)) = (long long)pNode;
    }
    NPC_NODE_PARENT(nLeft) = NPC_NODE_PARENT(pNode);
    if (pNode == *(long long**)(*(long long*)(pTree + 0x30) + 8)) {
        *(long long*)(*(long long*)(pTree + 0x30) + 8) = nLeft;
        NPC_NODE_RIGHT(nLeft) = (long long)pNode;
        NPC_NODE_PARENT(pNode) = nLeft;
        return;
    }
    long long nParent = NPC_NODE_PARENT(pNode);
    if (pNode == (long long*)NPC_NODE_RIGHT(nParent)) {
        NPC_NODE_RIGHT(nParent) = nLeft;
        NPC_NODE_RIGHT(nLeft) = (long long)pNode;
        NPC_NODE_PARENT(pNode) = nLeft;
        return;
    }
    NPC_NODE_LEFT(nParent) = nLeft;
    NPC_NODE_RIGHT(nLeft) = (long long)pNode;
    NPC_NODE_PARENT(pNode) = nLeft;
    return;
}

const NpcTreeLinkEntry g_aNpcTreeLink[] = {
    { "140021f50", "successor",    (void*)&FUN_140021f50 },
    { "140021e60", "rotate-left",  (void*)&FUN_140021e60 },
    { "140021ec0", "rotate-right", (void*)&FUN_140021ec0 },
};

const int g_nNpcTreeLink = 3;

}  // namespace tq

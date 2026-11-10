// Transcribed from NpcServer.exe; see map-tree.h.
#include "modules/npcserver/unattributed/map-tree.h"

namespace tq {

// 0x140022a40 - the sentinel head of a container: three cleared links, +0x28 = 1, +0x29 = 0
void* FUN_140022a40(void) {
    void** pHead = (void**)g_pfnNpcOperatorNew(0x30);
    if (pHead != nullptr) {
        pHead[0] = nullptr;
    }
    if (pHead + 1 != nullptr) {          // written this way in the image; the guard can never fail
        pHead[1] = nullptr;
    }
    if (pHead + 2 != nullptr) {          // the same
        pHead[2] = nullptr;
    }
    *(unsigned char*)(pHead + 5) = 1;                    // +0x28
    *(unsigned char*)((long long)pHead + 0x29) = 0;      // +0x29
    return pHead;
}

// 0x140022af0 - the same body
void* FUN_140022af0(void) {
    void** pHead = (void**)g_pfnNpcOperatorNew(0x30);
    if (pHead != nullptr) {
        pHead[0] = nullptr;
    }
    if (pHead + 1 != nullptr) {
        pHead[1] = nullptr;
    }
    if (pHead + 2 != nullptr) {
        pHead[2] = nullptr;
    }
    *(unsigned char*)(pHead + 5) = 1;
    *(unsigned char*)((long long)pHead + 0x29) = 0;
    return pHead;
}

// 0x140022aa0 - free the subtree, walking the right child first and then following the left link
void FUN_140022aa0(void* pUnused, long long* pNode) {
    char nFlag = *(char*)((long long)pNode + 0x29);
    while (nFlag == '\0') {
        FUN_140022aa0(pUnused, (long long*)pNode[2]);
        long long* pNext = (long long*)pNode[0];
        g_pfnNpcOperatorDelete(pNode);
        pNode = pNext;
        nFlag = *(char*)((long long)pNext + 0x29);
    }
    return;
}

// 0x140022b80 - the same body
void FUN_140022b80(void* pUnused, long long* pNode) {
    char nFlag = *(char*)((long long)pNode + 0x29);
    while (nFlag == '\0') {
        FUN_140022b80(pUnused, (long long*)pNode[2]);
        long long* pNext = (long long*)pNode[0];
        g_pfnNpcOperatorDelete(pNode);
        pNode = pNext;
        nFlag = *(char*)((long long)pNext + 0x29);
    }
    return;
}

// 0x140023210 - clear the tree, then leave the head linked only to itself
void FUN_140023210(long long pSet) {
    long long* pNode = *(long long**)(*(long long*)(pSet + 0x30) + 8);
    char nFlag = *(char*)((long long)pNode + 0x29);
    while (nFlag == '\0') {
        FUN_140022aa0((void*)pSet, (long long*)pNode[2]);
        long long* pNext = (long long*)pNode[0];
        g_pfnNpcOperatorDelete(pNode);
        pNode = pNext;
        nFlag = *(char*)((long long)pNext + 0x29);
    }
    *(long long*)(*(long long*)(pSet + 0x30) + 8) = *(long long*)(pSet + 0x30);
    *(long long*)(pSet + 0x38) = 0;
    *(long long*)*(long long*)(pSet + 0x30) = *(long long*)(pSet + 0x30);
    *(long long*)(*(long long*)(pSet + 0x30) + 0x10) = *(long long*)(pSet + 0x30);
    return;
}

// 0x1400237c0 - the same shape over 0x140022b80
void FUN_1400237c0(long long pSet) {
    long long* pNode = *(long long**)(*(long long*)(pSet + 0x30) + 8);
    char nFlag = *(char*)((long long)pNode + 0x29);
    while (nFlag == '\0') {
        FUN_140022b80((void*)pSet, (long long*)pNode[2]);
        long long* pNext = (long long*)pNode[0];
        g_pfnNpcOperatorDelete(pNode);
        pNode = pNext;
        nFlag = *(char*)((long long)pNext + 0x29);
    }
    *(long long*)(*(long long*)(pSet + 0x30) + 8) = *(long long*)(pSet + 0x30);
    *(long long*)(pSet + 0x38) = 0;
    *(long long*)*(long long*)(pSet + 0x30) = *(long long*)(pSet + 0x30);
    *(long long*)(*(long long*)(pSet + 0x30) + 0x10) = *(long long*)(pSet + 0x30);
    return;
}

const NpcMapTreeEntry g_aNpcMapTree[] = {
    { "140022a40", "sentinel-head", (void*)&FUN_140022a40 },
    { "140022af0", "sentinel-head", (void*)&FUN_140022af0 },
    { "140022aa0", "subtree-free",  (void*)&FUN_140022aa0 },
    { "140022b80", "subtree-free",  (void*)&FUN_140022b80 },
    { "140023210", "tree-clear",    (void*)&FUN_140023210 },
    { "1400237c0", "tree-clear",    (void*)&FUN_1400237c0 },
};

const int g_nNpcMapTree = 6;

}  // namespace tq

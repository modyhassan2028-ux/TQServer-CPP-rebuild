// Transcribed from NpcServer.exe; see container-nodes.h.
#include "modules/npcserver/unattributed/container-nodes.h"
#include "modules/npcserver/unattributed/map-tree.h"
#include "modules/npcserver/unattributed/tree-erase-range.h"

namespace tq {

// 0x1400257a0 - node builder, sentinel head from 0x140022a40
void* FUN_1400257a0(void* pThis) {
    void** pNode = (void**)g_pfnNpcOperatorNew(8);
    if (pNode == nullptr) {
        pNode = nullptr;
    } else {
        *pNode = pThis;
    }
    *(void**)pThis = pNode;
    long long nHead = (long long)FUN_140022a40();
    ((long long*)pThis)[6] = nHead;
    *(unsigned char*)(nHead + 0x29) = 1;
    *(long long*)(((long long*)pThis)[6] + 8) = ((long long*)pThis)[6];
    *(long long*)((long long*)pThis)[6] = ((long long*)pThis)[6];
    *(long long*)(((long long*)pThis)[6] + 0x10) = ((long long*)pThis)[6];
    ((long long*)pThis)[7] = 0;
    return pThis;
}

// 0x1400258d0 - the same body, sentinel head from 0x140022a40
void* FUN_1400258d0(void* pThis) {
    void** pNode = (void**)g_pfnNpcOperatorNew(8);
    if (pNode == nullptr) {
        pNode = nullptr;
    } else {
        *pNode = pThis;
    }
    *(void**)pThis = pNode;
    long long nHead = (long long)FUN_140022a40();
    ((long long*)pThis)[6] = nHead;
    *(unsigned char*)(nHead + 0x29) = 1;
    *(long long*)(((long long*)pThis)[6] + 8) = ((long long*)pThis)[6];
    *(long long*)((long long*)pThis)[6] = ((long long*)pThis)[6];
    *(long long*)(((long long*)pThis)[6] + 0x10) = ((long long*)pThis)[6];
    ((long long*)pThis)[7] = 0;
    return pThis;
}

// 0x140025820 - the same body, sentinel head from 0x140022af0
void* FUN_140025820(void* pThis) {
    void** pNode = (void**)g_pfnNpcOperatorNew(8);
    if (pNode == nullptr) {
        pNode = nullptr;
    } else {
        *pNode = pThis;
    }
    *(void**)pThis = pNode;
    long long nHead = (long long)FUN_140022af0();
    ((long long*)pThis)[6] = nHead;
    *(unsigned char*)(nHead + 0x29) = 1;
    *(long long*)(((long long*)pThis)[6] + 8) = ((long long*)pThis)[6];
    *(long long*)((long long*)pThis)[6] = ((long long*)pThis)[6];
    *(long long*)(((long long*)pThis)[6] + 0x10) = ((long long*)pThis)[6];
    ((long long*)pThis)[7] = 0;
    return pThis;
}

// 0x140025950 - the same body, sentinel head from 0x140022af0
void* FUN_140025950(void* pThis) {
    void** pNode = (void**)g_pfnNpcOperatorNew(8);
    if (pNode == nullptr) {
        pNode = nullptr;
    } else {
        *pNode = pThis;
    }
    *(void**)pThis = pNode;
    long long nHead = (long long)FUN_140022af0();
    ((long long*)pThis)[6] = nHead;
    *(unsigned char*)(nHead + 0x29) = 1;
    *(long long*)(((long long*)pThis)[6] + 8) = ((long long*)pThis)[6];
    *(long long*)((long long*)pThis)[6] = ((long long*)pThis)[6];
    *(long long*)(((long long*)pThis)[6] + 0x10) = ((long long*)pThis)[6];
    ((long long*)pThis)[7] = 0;
    return pThis;
}

// 0x140024340 - erase everything through 0x140023df0, then release the head
void FUN_140024340(long long* pSet) {
    long long nOwner = *pSet;                                  // local_38
    void* pHead = (void*)pSet[6];                              // puStack_30
    long long nLeftmost = *(long long*)pHead;                  // uStack_20
    long long aFirst[2];
    aFirst[0] = nOwner;
    aFirst[1] = nLeftmost;                                     // the range starts at the leftmost node
    long long aLast[2];
    aLast[0] = nOwner;
    aLast[1] = (long long)pHead;                               // and ends at the head, so it covers the tree
    long long aOut[2];
    FUN_140023df0(pSet, aOut, aFirst, aLast);
    g_pfnNpcOperatorDelete((void*)pSet[6]);
    pSet[6] = 0;
    pSet[7] = 0;
    return;
}

// 0x140024d70 - the same shape through 0x1400243b0
void FUN_140024d70(long long* pSet) {
    long long nOwner = *pSet;
    void* pHead = (void*)pSet[6];
    long long nLeftmost = *(long long*)pHead;
    long long aFirst[2];
    aFirst[0] = nOwner;
    aFirst[1] = nLeftmost;
    long long aLast[2];
    aLast[0] = nOwner;
    aLast[1] = (long long)pHead;
    long long aOut[2];
    FUN_1400243b0(pSet, aOut, aFirst, aLast);
    g_pfnNpcOperatorDelete((void*)pSet[6]);
    pSet[6] = 0;
    pSet[7] = 0;
    return;
}

// 0x140025210
void FUN_140025210(long long* pSet) {
    FUN_140024340(pSet);
    g_pfnNpcOperatorDelete((void*)*pSet);
    return;
}

// 0x140025310
void FUN_140025310(long long* pSet) {
    FUN_140024340(pSet);
    g_pfnNpcOperatorDelete((void*)*pSet);
    return;
}

// 0x1400251e0
void FUN_1400251e0(long long* pSet) {
    FUN_140024d70(pSet);
    g_pfnNpcOperatorDelete((void*)*pSet);
    return;
}

// 0x1400252e0
void FUN_1400252e0(long long* pSet) {
    FUN_140024d70(pSet);
    g_pfnNpcOperatorDelete((void*)*pSet);
    return;
}

const NpcContainerNodeEntry g_aNpcContainerNode[] = {
    { "1400257a0", "node-builder-140022a40", (void*)&FUN_1400257a0 },
    { "1400258d0", "node-builder-140022a40", (void*)&FUN_1400258d0 },
    { "140025820", "node-builder-140022af0", (void*)&FUN_140025820 },
    { "140025950", "node-builder-140022af0", (void*)&FUN_140025950 },
    { "140024340", "destructor-140023df0",   (void*)&FUN_140024340 },
    { "140024d70", "destructor-1400243b0",   (void*)&FUN_140024d70 },
    { "140025210", "deleter-140024340",      (void*)&FUN_140025210 },
    { "140025310", "deleter-140024340",      (void*)&FUN_140025310 },
    { "1400251e0", "deleter-140024d70",      (void*)&FUN_1400251e0 },
    { "1400252e0", "deleter-140024d70",      (void*)&FUN_1400252e0 },
};

const int g_nNpcContainerNode = 10;

}  // namespace tq

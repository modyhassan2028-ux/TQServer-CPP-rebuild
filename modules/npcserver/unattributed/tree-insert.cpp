// Transcribed from NpcServer.exe; see tree-insert.h.
#include "modules/npcserver/unattributed/tree-insert.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include <stdexcept>

namespace tq {

// 0x1400228f0 - the node builder: left, parent, right, the value pair, colour and isnil
void* FUN_1400228f0(long long pTree, long long pLeft, long long pParent, long long pRight,
                    unsigned long long* pValue, unsigned char nColor) {
    (void)pTree;
    unsigned long long* puVar1 = (unsigned long long*)g_pfnNpcOperatorNew(0x30);
    if (puVar1 != 0) {
        puVar1[0] = (unsigned long long)pLeft;
        puVar1[1] = (unsigned long long)pParent;
        puVar1[2] = (unsigned long long)pRight;
        puVar1[3] = pValue[0];
        puVar1[4] = pValue[1];
        *(unsigned char*)(puVar1 + 5) = nColor;                    // +0x28
        *(unsigned char*)((long long)puVar1 + 0x29) = 0;           // +0x29, not nil
    }
    return puVar1;
}

// 0x140024000 - insert at the hint, then repair the tree
unsigned long long* FUN_140024000(long long* pMap, unsigned long long* pOut, char bWentLeft,
                                  unsigned long long* pHint, unsigned long long* pKey) {
    char cVar1;
    long long* plVar2;
    long long* plVar3;
    long long lVar4;
    long long* plVar5;
    long long* plVar6;
    long long* plVar7;

    if (0xffffffffffffffdULL < (unsigned long long)pMap[7]) {
        throw std::length_error("map/set<T> too long");
    }
    plVar5 = (long long*)FUN_1400228f0((long long)pMap, pMap[6], (long long)pHint, pMap[6], pKey, 0);
    pMap[7] = pMap[7] + 1;
    if (pHint == (unsigned long long*)pMap[6]) {
        ((unsigned long long*)pMap[6])[1] = (unsigned long long)plVar5;
        *(long long**)pMap[6] = plVar5;
        *(long long**)(pMap[6] + 0x10) = plVar5;
    } else if (bWentLeft == '\0') {
        pHint[2] = (unsigned long long)plVar5;
        if (pHint == *(unsigned long long**)(pMap[6] + 0x10)) {
            *(long long**)(pMap[6] + 0x10) = plVar5;
        }
    } else {
        *pHint = (unsigned long long)plVar5;
        if (pHint == *(unsigned long long**)pMap[6]) {
            *(long long**)pMap[6] = plVar5;
        }
    }
    plVar7 = plVar5 + 1;
    cVar1 = *(char*)(*plVar7 + 0x28);
    plVar6 = plVar5;
    while (cVar1 == '\0') {
        plVar2 = (long long*)*plVar7;
        plVar3 = (long long*)plVar2[1];
        if (plVar2 == (long long*)*plVar3) {
            lVar4 = plVar3[2];
            if (*(char*)(lVar4 + 0x28) == '\0') {
                *(unsigned char*)(plVar2 + 5) = 1;
                *(unsigned char*)(lVar4 + 0x28) = 1;
                *(unsigned char*)(*(long long*)(*plVar7 + 8) + 0x28) = 0;
                plVar6 = *(long long**)(*plVar7 + 8);
            } else {
                if (plVar6 == (long long*)plVar2[2]) {
                    plVar6 = (long long*)plVar2[2];
                    plVar2[2] = *plVar6;
                    if (*(char*)(*plVar6 + 0x29) == '\0') {
                        *(long long**)(*plVar6 + 8) = plVar2;
                    }
                    plVar7 = plVar2 + 1;
                    plVar6[1] = *plVar7;
                    if (plVar2 == *(long long**)(pMap[6] + 8)) {
                        *(long long**)(pMap[6] + 8) = plVar6;
                    } else {
                        plVar3 = (long long*)*plVar7;
                        if (plVar2 == (long long*)*plVar3) {
                            *plVar3 = (long long)plVar6;
                        } else {
                            plVar3[2] = (long long)plVar6;
                        }
                    }
                    *plVar6 = (long long)plVar2;
                    *plVar7 = (long long)plVar6;
                    plVar6 = plVar2;
                }
                *(unsigned char*)(*plVar7 + 0x28) = 1;
                *(unsigned char*)(*(long long*)(*plVar7 + 8) + 0x28) = 0;
                plVar7 = *(long long**)(*plVar7 + 8);
                lVar4 = *plVar7;
                *plVar7 = *(long long*)(lVar4 + 0x10);
                if (*(char*)(*(long long*)(lVar4 + 0x10) + 0x29) == '\0') {
                    *(long long**)(*(long long*)(lVar4 + 0x10) + 8) = plVar7;
                }
                *(long long*)(lVar4 + 8) = plVar7[1];
                if (plVar7 == *(long long**)(pMap[6] + 8)) {
                    *(long long*)(pMap[6] + 8) = lVar4;
                } else {
                    plVar2 = (long long*)plVar7[1];
                    if (plVar7 == (long long*)plVar2[2]) {
                        plVar2[2] = lVar4;
                    } else {
                        *plVar2 = lVar4;
                    }
                }
                *(long long**)(lVar4 + 0x10) = plVar7;
                plVar7[1] = lVar4;
            }
        } else {
            lVar4 = *plVar3;
            if (*(char*)(lVar4 + 0x28) == '\0') {
                *(unsigned char*)(plVar2 + 5) = 1;
                *(unsigned char*)(lVar4 + 0x28) = 1;
                *(unsigned char*)(*(long long*)(*plVar7 + 8) + 0x28) = 0;
                plVar6 = *(long long**)(*plVar7 + 8);
            } else {
                if (plVar6 == (long long*)*plVar2) {
                    lVar4 = *plVar2;
                    *plVar2 = *(long long*)(lVar4 + 0x10);
                    if (*(char*)(*(long long*)(lVar4 + 0x10) + 0x29) == '\0') {
                        *(long long**)(*(long long*)(lVar4 + 0x10) + 8) = plVar2;
                    }
                    plVar7 = plVar2 + 1;
                    *(long long*)(lVar4 + 8) = *plVar7;
                    if (plVar2 == *(long long**)(pMap[6] + 8)) {
                        *(long long*)(pMap[6] + 8) = lVar4;
                    } else {
                        plVar6 = (long long*)*plVar7;
                        if (plVar2 == (long long*)plVar6[2]) {
                            plVar6[2] = lVar4;
                        } else {
                            *plVar6 = lVar4;
                        }
                    }
                    *(long long**)(lVar4 + 0x10) = plVar2;
                    *plVar7 = lVar4;
                    plVar6 = plVar2;
                }
                *(unsigned char*)(*plVar7 + 0x28) = 1;
                *(unsigned char*)(*(long long*)(*plVar7 + 8) + 0x28) = 0;
                lVar4 = *(long long*)(*plVar7 + 8);
                plVar7 = *(long long**)(lVar4 + 0x10);
                *(long long*)(lVar4 + 0x10) = *plVar7;
                if (*(char*)(*plVar7 + 0x29) == '\0') {
                    *(long long*)(*plVar7 + 8) = lVar4;
                }
                plVar7[1] = *(long long*)(lVar4 + 8);
                if (lVar4 == *(long long*)(pMap[6] + 8)) {
                    *(long long**)(pMap[6] + 8) = plVar7;
                } else {
                    plVar2 = *(long long**)(lVar4 + 8);
                    if (lVar4 == *plVar2) {
                        *plVar2 = (long long)plVar7;
                    } else {
                        plVar2[2] = (long long)plVar7;
                    }
                }
                *plVar7 = lVar4;
                *(long long**)(lVar4 + 8) = plVar7;
            }
        }
        plVar7 = plVar6 + 1;
        cVar1 = *(char*)(*plVar7 + 0x28);
    }
    *(unsigned char*)(*(long long*)(pMap[6] + 8) + 0x28) = 1;
    pOut[1] = (unsigned long long)plVar5;
    pOut[0] = (unsigned long long)*pMap;
    return pOut;
}

const NpcTreeInsertEntry g_aNpcTreeInsert[] = {
    { "1400228f0", "node-builder", (void*)&FUN_1400228f0 },
    { "140024000", "insert-repair", (void*)&FUN_140024000 },
};

const int g_nNpcTreeInsert = 2;

}  // namespace tq


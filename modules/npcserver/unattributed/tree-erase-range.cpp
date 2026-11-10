// Transcribed from NpcServer.exe; see tree-erase-range.h.
#include "modules/npcserver/unattributed/tree-erase-range.h"
#include "modules/npcserver/unattributed/tree-erase.h"
#include "modules/npcserver/unattributed/tree-links.h"
#include "modules/npcserver/unattributed/map-tree.h"

namespace tq {

// 0x140023df0 - erase [first, last)
long long* FUN_140023df0(long long* pTree, long long* pOut, long long* pFirst, long long* pLast) {
    long long nLeftmost = *(long long*)pTree[6];
    if ((pFirst[0] == 0) || (pFirst[0] != *pTree)) {
        g_pfnNpcInvalidParameter();
    }
    if (pFirst[1] == nLeftmost) {
        long long nHead = pTree[6];
        if ((pLast[0] == 0) || (pLast[0] != *pTree)) {
            g_pfnNpcInvalidParameter();
        }
        if (pLast[1] == nHead) {
            FUN_140023210((long long)pTree);
            pOut[1] = *(long long*)pTree[6];
            *pOut = *pTree;
            return pOut;
        }
    }
    for (;;) {
        if ((pFirst[0] == 0) || (pFirst[0] != pLast[0])) {
            g_pfnNpcInvalidParameter();
        }
        long long lVar2 = *pFirst;
        if (pFirst[1] == pLast[1]) break;
        long long lVar3 = pFirst[1];
        if (*pFirst == 0) {
            g_pfnNpcInvalidParameter();
        }
        long long lVar4 = pFirst[1];
        if (*(char*)(lVar4 + 0x29) == '\0') {
            long long* plVar6 = *(long long**)(lVar4 + 0x10);
            if (*(char*)((long long)plVar6 + 0x29) == '\0') {
                char cVar1 = *(char*)(*plVar6 + 0x29);
                long long* plVar5 = (long long*)*plVar6;
                while (cVar1 == '\0') {
                    cVar1 = *(char*)(*plVar5 + 0x29);
                    plVar6 = plVar5;
                    plVar5 = (long long*)*plVar5;
                }
            } else {
                plVar6 = *(long long**)(lVar4 + 8);
                char cVar1 = *(char*)((long long)plVar6 + 0x29);
                while ((cVar1 == '\0') && (pFirst[1] == plVar6[2])) {
                    pFirst[1] = (long long)plVar6;
                    plVar6 = (long long*)plVar6[1];
                    cVar1 = *(char*)((long long)plVar6 + 0x29);
                }
            }
            pFirst[1] = (long long)plVar6;
        } else {
            g_pfnNpcInvalidParameter();
        }
        long long local_28[2];
        local_28[0] = lVar2;
        local_28[1] = lVar3;
        long long local_18[2];
        FUN_140022e50(pTree, local_18, local_28);
    }
    long long lVar2 = pFirst[1];
    *pOut = *pTree;
    pOut[1] = lVar2;
    return pOut;
}

// 0x1400243b0 - the same body with FUN_1400237c0 and FUN_140023400 behind it
long long* FUN_1400243b0(long long* pTree, long long* pOut, long long* pFirst, long long* pLast) {
    long long nLeftmost = *(long long*)pTree[6];
    if ((pFirst[0] == 0) || (pFirst[0] != *pTree)) {
        g_pfnNpcInvalidParameter();
    }
    if (pFirst[1] == nLeftmost) {
        long long nHead = pTree[6];
        if ((pLast[0] == 0) || (pLast[0] != *pTree)) {
            g_pfnNpcInvalidParameter();
        }
        if (pLast[1] == nHead) {
            FUN_1400237c0((long long)pTree);
            pOut[1] = *(long long*)pTree[6];
            *pOut = *pTree;
            return pOut;
        }
    }
    for (;;) {
        if ((pFirst[0] == 0) || (pFirst[0] != pLast[0])) {
            g_pfnNpcInvalidParameter();
        }
        long long lVar2 = *pFirst;
        if (pFirst[1] == pLast[1]) break;
        long long lVar3 = pFirst[1];
        if (*pFirst == 0) {
            g_pfnNpcInvalidParameter();
        }
        long long lVar4 = pFirst[1];
        if (*(char*)(lVar4 + 0x29) == '\0') {
            long long* plVar6 = *(long long**)(lVar4 + 0x10);
            if (*(char*)((long long)plVar6 + 0x29) == '\0') {
                char cVar1 = *(char*)(*plVar6 + 0x29);
                long long* plVar5 = (long long*)*plVar6;
                while (cVar1 == '\0') {
                    cVar1 = *(char*)(*plVar5 + 0x29);
                    plVar6 = plVar5;
                    plVar5 = (long long*)*plVar5;
                }
            } else {
                plVar6 = *(long long**)(lVar4 + 8);
                char cVar1 = *(char*)((long long)plVar6 + 0x29);
                while ((cVar1 == '\0') && (pFirst[1] == plVar6[2])) {
                    pFirst[1] = (long long)plVar6;
                    plVar6 = (long long*)plVar6[1];
                    cVar1 = *(char*)((long long)plVar6 + 0x29);
                }
            }
            pFirst[1] = (long long)plVar6;
        } else {
            g_pfnNpcInvalidParameter();
        }
        long long local_28[2];
        local_28[0] = lVar2;
        local_28[1] = lVar3;
        long long local_18[2];
        FUN_140023400(pTree, local_18, local_28);
    }
    long long lVar2 = pFirst[1];
    *pOut = *pTree;
    pOut[1] = lVar2;
    return pOut;
}

const NpcTreeEraseRangeEntry g_aNpcTreeEraseRange[] = {
    { "140023df0", "140023210", (void*)&FUN_140023df0 },
    { "1400243b0", "1400237c0", (void*)&FUN_1400243b0 },
};

const int g_nNpcTreeEraseRange = 2;

}  // namespace tq

// Transcribed from NpcServer.exe; see map-insert-erase.h.
#include "modules/npcserver/unattributed/map-insert-erase.h"
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/unattributed/tree-erase-range.h"
#include "modules/npcserver/unattributed/tree-insert.h"

namespace tq {


// 0x140024970 - insert at the position the search found
long long* FUN_140024970(long long* pMap, long long* pOut, unsigned* pKey) {
    char cVar1;
    long long lVar2;
    long long* plVar3;
    long long* plVar4;
    long long* plVar5;
    long long* plVar6;
    bool bVar7;
    long long aPair[2];        // local_38, local_30: the two slots the insert writes as a pair
    long long* local_30;

    plVar6 = (long long*)pMap[6];
    bVar7 = true;
    if (*(char*)(plVar6[1] + 0x29) == '\0') {
        plVar5 = (long long*)plVar6[1];
        do {
            plVar6 = plVar5;
            bVar7 = *pKey < *(unsigned*)(plVar6 + 3);
            if (bVar7) {
                plVar5 = (long long*)plVar6[0];
            } else {
                plVar5 = (long long*)plVar6[2];
            }
        } while (*(char*)((long long)plVar5 + 0x29) == '\0');
    }
    lVar2 = pMap[0];
    plVar5 = plVar6;
    aPair[0] = lVar2;
    plVar4 = plVar6;
    if (!bVar7) {
    label_acd:
        local_30 = plVar4;
        if (*pKey <= *(unsigned*)(plVar5 + 3)) {
            *(unsigned char*)(pOut + 2) = 0;
            *pOut = aPair[0];
            goto label_afc;
        }
    } else {
        plVar5 = (long long*)((long long*)pMap[6])[0];
        local_30 = plVar6;
        if (lVar2 == 0) {
            g_pfnNpcInvalidParameter();
        }
        if (plVar6 != plVar5) {
            if (lVar2 == 0) {
                g_pfnNpcInvalidParameter();
            }
            if (*(char*)((long long)plVar6 + 0x29) == '\0') {
                plVar5 = (long long*)plVar6[0];
                if (*(char*)((long long)plVar5 + 0x29) == '\0') {
                    cVar1 = *(char*)(plVar5[2] + 0x29);
                    plVar3 = (long long*)plVar5[2];
                    while (plVar4 = plVar5, cVar1 == '\0') {
                        cVar1 = *(char*)(plVar3[2] + 0x29);
                        plVar5 = plVar3;
                        plVar3 = (long long*)plVar3[2];
                    }
                } else {
                    cVar1 = *(char*)(plVar6[1] + 0x29);
                    plVar4 = (long long*)plVar6[1];
                    plVar3 = plVar6;
                    while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (long long*)*plVar5))) {
                        cVar1 = *(char*)(plVar5[1] + 0x29);
                        plVar4 = (long long*)plVar5[1];
                        plVar3 = plVar5;
                        local_30 = plVar5;
                    }
                    plVar4 = plVar5;
                    if (*(char*)((long long)plVar3 + 0x29) != '\0') {
                        g_pfnNpcInvalidParameter();
                        plVar5 = plVar3;
                        plVar4 = local_30;
                    }
                }
            } else {
                plVar5 = (long long*)plVar6[2];
                plVar4 = plVar5;
                if (*(char*)((long long)plVar5 + 0x29) != '\0') {
                    local_30 = plVar5;
                    g_pfnNpcInvalidParameter();
                    plVar4 = local_30;
                }
            }
            goto label_acd;
        }
        bVar7 = true;
    }
    FUN_140024000(pMap, (unsigned long long*)aPair, bVar7, (unsigned long long*)plVar6,
                  (unsigned long long*)pKey);
    *(unsigned char*)(pOut + 2) = 1;
    local_30 = (long long*)aPair[1];
    *pOut = aPair[0];
label_afc:
    pOut[1] = (long long)local_30;
    return pOut;
}

// 0x140024b20 - count the nodes of the range, then erase exactly that range
//
// The image keeps three iterator pairs in adjacent stack slots (local_38/30, local_48/40, local_58/50) and hands their
// addresses to the erase, which reads them as two-slot arrays. Here the pairs are real arrays so that the layout the
// callee depends on is guaranteed by the declaration instead of by the compiler's stack ordering.
long long FUN_140024b20(long long* pMap, unsigned* pKey) {
    char cVar1;
    long long* plVar2;
    long long lVar3;
    long long lVar4;
    long long* plVar5;
    long long* plVar6;
    long long* plVar7;
    long long lVar8;
    long long aBegin[2];      // local_38, local_30
    long long aEnd[2];        // local_28, local_20
    long long aEraseFirst[2]; // local_48, local_40
    long long aEraseLast[2];  // local_58, local_50

    long long aRange[4];      // the two pairs as the lookup writes them: begin, then end
    FUN_140023290(pMap, aRange, pKey);
    aBegin[0] = aRange[0];
    aBegin[1] = aRange[1];
    aEnd[0] = aRange[2];
    aEnd[1] = aRange[3];
    plVar5 = (long long*)aEnd[1];
    lVar4 = aEnd[0];
    lVar3 = aBegin[0];
    lVar8 = 0;
    aEraseLast[0] = aBegin[0];
    aEraseLast[1] = (long long)aBegin[1];
    plVar7 = (long long*)aBegin[1];
    while (true) {
        if ((lVar3 == 0) || (lVar3 != lVar4)) {
            g_pfnNpcInvalidParameter();
        }
        if (plVar7 == plVar5) break;
        lVar8 = lVar8 + 1;
        if (lVar3 == 0) {
            g_pfnNpcInvalidParameter();
        }
        if (*(char*)((long long)plVar7 + 0x29) == '\0') {
            plVar2 = (long long*)plVar7[2];
            if (*(char*)((long long)plVar2 + 0x29) == '\0') {
                cVar1 = *(char*)(*plVar2 + 0x29);
                plVar7 = plVar2;
                plVar2 = (long long*)*plVar2;
                while (cVar1 == '\0') {
                    cVar1 = *(char*)(*plVar2 + 0x29);
                    plVar7 = plVar2;
                    plVar2 = (long long*)*plVar2;
                }
            } else {
                cVar1 = *(char*)(plVar7[1] + 0x29);
                plVar6 = (long long*)plVar7[1];
                plVar2 = plVar7;
                while ((plVar7 = plVar6, cVar1 == '\0' && (plVar2 == (long long*)plVar7[2]))) {
                    cVar1 = *(char*)(plVar7[1] + 0x29);
                    plVar6 = (long long*)plVar7[1];
                    plVar2 = plVar7;
                }
            }
        } else {
            g_pfnNpcInvalidParameter();
        }
    }
    aEraseLast[0] = aEnd[0];
    aEraseLast[1] = aEnd[1];
    aEraseFirst[0] = aBegin[0];
    aEraseFirst[1] = aBegin[1];
    FUN_140023df0(pMap, aBegin, aEraseFirst, aEraseLast);
    return lVar8;
}

// 0x140023290 - the equal range: the lower bound first, then the upper bound
long long* FUN_140023290(long long* pMap, long long* pOut, unsigned* pKey) {
    unsigned long long uVar1;
    unsigned long long* puVar2;
    unsigned long long* puVar3;
    unsigned long long* puVar4;
    unsigned long long* puVar5;

    puVar4 = (unsigned long long*)pMap[6];
    puVar5 = puVar4;
    if (*(char*)((long long)puVar4[1] + 0x29) == '\0') {
        puVar2 = (unsigned long long*)puVar4[1];
        do {
            if (*(unsigned*)(puVar2 + 3) < *pKey) {
                puVar3 = (unsigned long long*)puVar2[2];
            } else {
                if ((*(char*)((long long)puVar4 + 0x29) != '\0') && (*pKey < *(unsigned*)(puVar2 + 3))) {
                    puVar4 = puVar2;
                }
                puVar3 = (unsigned long long*)*puVar2;
                puVar5 = puVar2;
            }
            puVar2 = puVar3;
        } while (*(char*)((long long)puVar3 + 0x29) == '\0');
    }
    if (*(char*)((long long)puVar4 + 0x29) == '\0') {
        puVar2 = (unsigned long long*)*puVar4;
    } else {
        puVar2 = *(unsigned long long**)(pMap[6] + 8);
    }
    if (*(char*)((long long)puVar2 + 0x29) == '\0') {
        do {
            if (*pKey < *(unsigned*)(puVar2 + 3)) {
                puVar3 = (unsigned long long*)*puVar2;
                puVar4 = puVar2;
            } else {
                puVar3 = (unsigned long long*)puVar2[2];
            }
            puVar2 = puVar3;
        } while (*(char*)((long long)puVar3 + 0x29) == '\0');
    }
    uVar1 = (unsigned long long)*pMap;
    pOut[0] = (long long)uVar1;
    pOut[1] = (long long)puVar5;
    pOut[2] = (long long)uVar1;
    pOut[3] = (long long)puVar4;
    return pOut;
}

// 0x140024fe0 - the value stored at node+0x20 for a key, or zero when the key is absent
//
// The image builds the answer position on the stack as two adjacent slots and then takes the address of whichever pair
// it chose; the pair is an array here so the layout is explicit.
unsigned long long FUN_140024fe0(long long pLookup, unsigned nKey) {
    char cVar1;
    unsigned long long* puVar8;
    unsigned long long* puVar3;
    unsigned long long* puVar5;
    long long lVar4;
    long long lVar9;
    long long* plVar2;
    long long* plVar7;
    unsigned long long uVar6;
    unsigned long long* puVar2;
    long long aMain[2];   // local_38, local_30
    long long aAlt[2];    // local_28, local_20

    puVar8 = (unsigned long long*)(*(long long**)(pLookup + 0x38))[1];
    cVar1 = *(char*)((long long)puVar8 + 0x29);
    puVar3 = *(unsigned long long**)(pLookup + 0x38);
    while (cVar1 == '\0') {
        if (*(unsigned*)(puVar8 + 3) < nKey) {
            puVar5 = (unsigned long long*)puVar8[2];
            puVar8 = puVar3;
        } else {
            puVar5 = (unsigned long long*)*puVar8;
        }
        puVar3 = puVar8;
        puVar8 = puVar5;
        cVar1 = *(char*)((long long)puVar5 + 0x29);
    }
    puVar2 = *(unsigned long long**)(pLookup + 0x38);
    aMain[1] = (long long)puVar3;
    aMain[0] = *(long long*)(pLookup + 8);
    if (*(long long*)(pLookup + 8) == 0) {
        g_pfnNpcInvalidParameter();
    }
    if ((puVar3 == puVar2) || (nKey < *(unsigned*)(puVar3 + 3))) {
        plVar7 = aAlt;
        aAlt[1] = *(long long*)(pLookup + 0x38);
        aAlt[0] = *(long long*)(pLookup + 8);
    } else {
        plVar7 = aMain;
    }
    plVar2 = (long long*)*plVar7;
    lVar9 = *(long long*)(pLookup + 0x38);
    lVar4 = plVar7[1];
    if ((plVar2 == 0) || (plVar2 != *(long long**)(pLookup + 8))) {
        g_pfnNpcInvalidParameter();
    }
    if (lVar4 == lVar9) {
        uVar6 = 0;
    } else {
        if (plVar2 == 0) {
            g_pfnNpcInvalidParameter();
            lVar9 = 0;
        } else {
            lVar9 = *plVar2;
        }
        if (lVar4 == *(long long*)(lVar9 + 0x30)) {
            g_pfnNpcInvalidParameter();
        }
        uVar6 = *(unsigned long long*)(lVar4 + 0x20);
    }
    return uVar6;
}

const NpcMapInsertEntry g_aNpcMapInsert[] = {
    { "140024970", "insert-hinted", (void*)&FUN_140024970 },
    { "140024b20", "erase-counted", (void*)&FUN_140024b20 },
    { "140024fe0", "find-value",    (void*)&FUN_140024fe0 },
    { "140023290", "equal-range",   (void*)&FUN_140023290 },
};

const int g_nNpcMapInsert = 4;

}  // namespace tq

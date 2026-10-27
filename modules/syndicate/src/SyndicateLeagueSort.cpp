// ============================================================
// Syndicate.dll port — unit T7/D33: the league member-list
// SORT family, verbatim (see the header for the map).
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_14174cb10 @ 14174cb10 (the introsort loop)
//   FUN_141747090 @ 141747090 (the insertion sort)
//   FUN_141747c80 @ 141747c80 (the quicksort partition)
//   FUN_141746f30 @ 141746f30 (the median-of-3/9 net)
//   FUN_141746310 @ 141746310 (the 3-element net)
//   FUN_141747ec0 @ 141747ec0 (the make_heap loop)
//   FUN_1417463a0 @ 1417463a0 (the sift-down hole loop)
//   FUN_141748e30 @ 141748e30 (the sort_heap loop)
//   FUN_141745480 @ 141745480 (the sift-up final place)
// ============================================================
#include "modules/syndicate/src/SyndicateLeagueSort.h"
#include <cstring>

namespace syndicate {

// the comparator seam: FUN_1417ba4c0 (the D34 family)
bool (*g_fnLeagueCmp)(int* pState, uint32_t uA, uint32_t uB) = nullptr;

// ================= FUN_141746310 =================
// the 3-element ordered net: after it returns,
// *a <= *b <= *c under the comparator order.
void LeagueSortOrder3(uint32_t* puA, uint32_t* puB, uint32_t* puC, int nState) {
    uint32_t uVar1;
    bool bVar2;
    int local_res20[2];

    local_res20[0] = nState;
    // ORIGINAL: bVar2 = FUN_1417ba4c0(local_res20,*param_2,*param_1);
    bVar2 = g_fnLeagueCmp(local_res20, *puB, *puA);
    if ((bVar2) && (puB != puA)) {
        uVar1 = *puB;
        *puB = *puA;
        *puA = uVar1;
    }
    // ORIGINAL: bVar2 = FUN_1417ba4c0(local_res20,*param_3,*param_2);
    bVar2 = g_fnLeagueCmp(local_res20, *puC, *puB);
    if ((bVar2) && (puC != puB)) {
        uVar1 = *puC;
        *puC = *puB;
        *puB = uVar1;
    }
    // ORIGINAL: bVar2 = FUN_1417ba4c0(local_res20,*param_2,*param_1);
    bVar2 = g_fnLeagueCmp(local_res20, *puB, *puA);
    if ((bVar2) && (puB != puA)) {
        uVar1 = *puB;
        *puB = *puA;
        *puA = uVar1;
    }
}

// ================= FUN_141746f30 =================
// the pivot ordering: 0x28 or more elements → the
// 9-sample net, else the plain 3-net.
void LeagueSortMedianNet(uint32_t* puFirst, uint32_t* puMid, uint32_t* puLast, int nState) {
    int64_t lVar1;

    // ORIGINAL: lVar1 = (longlong)param_3 - (longlong)param_1 >> 2;
    lVar1 = ((int64_t)puLast - (int64_t)puFirst) >> 2;
    if (0x28 < lVar1) {
        lVar1 = lVar1 + 1;
        // ORIGINAL: lVar1 = (longlong)(lVar1 + (ulonglong)((uint)(lVar1 >> 0x3f) & 7)) >> 3;
        lVar1 = (int64_t)(lVar1 + (uint64_t)((uint32_t)(lVar1 >> 0x3f) & 7)) >> 3;
        LeagueSortOrder3(puFirst, puFirst + lVar1, puFirst + lVar1 * 2, nState);
        LeagueSortOrder3(puMid + -lVar1, puMid, puMid + lVar1, nState);
        LeagueSortOrder3(puLast + lVar1 * -2, puLast + -lVar1, puLast, nState);
        LeagueSortOrder3(puFirst + lVar1, puMid, puLast + -lVar1, nState);
        return;
    }
    LeagueSortOrder3(puFirst, puMid, puLast, nState);
}

// ================= FUN_141745480 =================
// the sift-up hole walk (the final place after the
// sift-down); NOTE: the decompile lost the comparator
// state argument (it shows the unnamed stack slot
// &stack0x00000028 = the caller's state home) — the
// port threads it as the 5th parameter.
void LeagueSortPushHole(int64_t lFirst, int64_t lHole, int64_t lTop, uint32_t uVal, int nState) {
    bool bVar1;
    int64_t lVar2;
    int nStateHome[1];
    nStateHome[0] = nState;

    if (lTop < lHole) {
        do {
            // ORIGINAL: lVar2 = (param_2 + -1) / 2;
            lVar2 = (lHole + -1) / 2;
            // ORIGINAL: bVar1 = FUN_1417ba4c0((int *)&stack0x00000028, *(uint *)(param_1 + lVar2 * 4), param_4);
            bVar1 = g_fnLeagueCmp(nStateHome, *(uint32_t*)(lFirst + lVar2 * 4), uVal);
            if (!bVar1) break;
            *(uint32_t*)(lFirst + lHole * 4) = *(uint32_t*)(lFirst + lVar2 * 4);
            lHole = lVar2;
        } while (lTop < lVar2);
        *(uint32_t*)(lFirst + lHole * 4) = uVal;
    }
    else {
        *(uint32_t*)(lFirst + lHole * 4) = uVal;
    }
}

// ================= FUN_1417463a0 =================
// the sift-down hole loop.
void LeagueSortSiftDown(int64_t lFirst, int64_t lHole, int64_t lLen, uint32_t uVal, int nState) {
    bool bVar1;
    int64_t lVar2;
    int64_t lVar3;
    int nStateHome[1];
    nStateHome[0] = nState;

    lVar3 = lHole;
    while (true) {
        // ORIGINAL: lVar2 = lVar3 * 2 + 2;
        lVar2 = lVar3 * 2 + 2;
        if (lLen <= lVar2) break;
        // ORIGINAL: bVar1 = FUN_1417ba4c0(&param_5, *(uint *)(param_1 + lVar2 * 4), *(uint *)(param_1 + -4 + lVar2 * 4));
        bVar1 = g_fnLeagueCmp(nStateHome,
            *(uint32_t*)(lFirst + lVar2 * 4),
            *(uint32_t*)(lFirst + -4 + lVar2 * 4));
        if (bVar1) {
            lVar2 = lVar3 * 2 + 1;
        }
        *(uint32_t*)(lFirst + lVar3 * 4) = *(uint32_t*)(lFirst + lVar2 * 4);
        lVar3 = lVar2;
    }
    if (lVar2 == lLen) {
        *(uint32_t*)(lFirst + lVar3 * 4) = *(uint32_t*)(lFirst + -4 + lLen * 4);
        lVar3 = lLen + -1;
    }
    // ORIGINAL: FUN_141745480(param_1,lVar3,param_2,param_4);
    // the third arg = param_2 = the ORIGINAL hole (the top), NOT lVar2
    LeagueSortPushHole(lFirst, lVar3, lHole, uVal, nState);
}

// ================= FUN_141747ec0 =================
// make_heap: the Floyd loop from the last parent down.
void LeagueSortMakeHeap(int64_t lFirst, int64_t lLast, int nState) {
    int64_t lVar1;
    int64_t lVar2;
    int64_t lVar3;

    lVar3 = (lLast - lFirst) >> 2;
    if (1 < lVar3) {
        // ORIGINAL: lVar2 = lVar3 - (param_2 - param_1 >> 0x3f) >> 1;
        lVar2 = lVar3 - ((lLast - lFirst) >> 0x3f) >> 1;
        while (0 < lVar2) {
            lVar1 = lVar2 * 4;
            lVar2 = lVar2 + -1;
            LeagueSortSiftDown(lFirst, lVar2, lVar3,
                *(uint32_t*)(lFirst + -4 + lVar1), nState);
        }
    }
}

// ================= FUN_141748e30 =================
// sort_heap: swap the front/back + re-sift until 1.
void LeagueSortSortHeap(uint32_t* puFirst, int64_t lLast, int nState) {
    uint32_t uVar1;
    int64_t lVar2;

    for (lVar2 = lLast - (int64_t)puFirst; 1 < lVar2 >> 2; lVar2 = lVar2 + -4) {
        uVar1 = *(uint32_t*)((int64_t)puFirst + lVar2 + -4);
        *(uint32_t*)((int64_t)puFirst + lVar2 + -4) = *puFirst;
        LeagueSortSiftDown((int64_t)puFirst, 0, lVar2 + -4 >> 2, uVar1, nState);
    }
}

// ================= FUN_141747090 =================
// the guarded insertion sort.
void LeagueSortInsertion(uint32_t* puFirst, uint32_t* puLast, int nState) {
    uint32_t uVar1;
    bool bVar2;
    int64_t lVar3;
    uint32_t* puVar4;
    uint32_t* puVar5;
    uint32_t* puVar6;
    int local_res18[4];

    if ((puFirst != puLast) && (puVar4 = puFirst + 1, puVar4 != puLast)) {
        local_res18[0] = nState;
        do {
            uVar1 = *puVar4;
            // ORIGINAL: bVar2 = FUN_1417ba4c0(local_res18,uVar1,*param_1);
            bVar2 = g_fnLeagueCmp(local_res18, uVar1, *puFirst);
            if (bVar2) {
                // the value belongs before the first: the
                // end-gallop — shift [first, cur) up by one
                lVar3 = ((int64_t)puVar4 - (int64_t)puFirst) >> 2;
                if (0 < lVar3) {
                    // ORIGINAL: memmove_s(puVar4 + (1 - lVar3),lVar3 * 4,param_1,lVar3 * 4);
                    memmove(puVar4 + (1 - lVar3), puFirst, lVar3 * 4);
                }
                *puFirst = uVar1;
            }
            else {
                // ORIGINAL: bVar2 = FUN_1417ba4c0(local_res18,uVar1,puVar4[-1]);
                bVar2 = g_fnLeagueCmp(local_res18, uVar1, puVar4[-1]);
                puVar5 = puVar4;
                puVar6 = puVar4;
                if (bVar2) {
                    do {
                        puVar6 = puVar5 + -1;
                        *puVar5 = *puVar6;
                        // ORIGINAL: bVar2 = FUN_1417ba4c0(local_res18,uVar1,puVar5[-2]);
                        bVar2 = g_fnLeagueCmp(local_res18, uVar1, puVar5[-2]);
                        puVar5 = puVar6;
                    } while (bVar2);
                }
                *puVar6 = uVar1;
            }
            puVar4 = puVar4 + 1;
        } while (puVar4 != puLast);
    }
}

// ================= FUN_141747c80 =================
// the quicksort partition; the output pair (as two
// qwords at pOut) = {the cut, the next loop bound}.
void LeagueSortPartition(uint64_t* pOut, uint32_t* puFirst, uint32_t* puLast, int nState) {
    uint32_t uVar1;
    bool bVar3;
    uint32_t* puVar2;
    uint32_t* puVar4;
    uint32_t* puVar5;
    uint32_t* puVar6;
    uint32_t* puVar7;
    uint32_t* puVar8;
    uint32_t* puVar9;
    int local_res20[2];

    // ORIGINAL: puVar7 = param_2 + (((longlong)param_3 - (longlong)param_2 >> 2) - ((longlong)param_3 - (longlong)param_2 >> 0x3f) >> 1);
    puVar7 = puFirst +
        ((((int64_t)puLast - (int64_t)puFirst) >> 2) -
        (((int64_t)puLast - (int64_t)puFirst) >> 0x3f) >> 1);
    local_res20[0] = nState;
    LeagueSortMedianNet(puFirst, puVar7, puLast + -1, nState);
    puVar8 = puVar7;
    // the left sentinel walk (down from the pivot)
    while (puVar9 = puVar8, puFirst < puVar9) {
        // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,puVar9[-1],*puVar9);
        bVar3 = g_fnLeagueCmp(local_res20, puVar9[-1], *puVar9);
        if (bVar3) break;   // the || short-circuit: puVar8 NOT updated
        // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,*puVar9,puVar9[-1]), puVar8 = puVar9 + -1, bVar3;
        bVar3 = g_fnLeagueCmp(local_res20, *puVar9, puVar9[-1]);
        puVar8 = puVar9 + -1;
        if (bVar3) break;
    }
    // the right walk (up from the pivot+1)
    do {
        puVar7 = puVar7 + 1;
        puVar8 = puVar7;
        puVar4 = puVar9;
        if (puLast <= puVar7) break;
        // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,*puVar7,*puVar9);
        bVar3 = g_fnLeagueCmp(local_res20, *puVar7, *puVar9);
        if ((bVar3) ||
            (bVar3 = g_fnLeagueCmp(local_res20, *puVar9, *puVar7), bVar3)) break;
    } while (true);

joined_r0x000141747d5a:
    puVar2 = puVar8;
    puVar8 = puVar9;
    puVar5 = puVar4;
    if (puVar2 < puLast) {
        // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,*puVar4,*puVar2);
        bVar3 = g_fnLeagueCmp(local_res20, *puVar4, *puVar2);
        puVar6 = puVar7;
        if (!bVar3) {
            // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,*puVar2,*puVar4);
            bVar3 = g_fnLeagueCmp(local_res20, *puVar2, *puVar4);
            if (bVar3) goto joined_r0x000141747da6;
            puVar6 = puVar7 + 1;
            if (puVar7 != puVar2) {
                uVar1 = *puVar7;
                *puVar7 = *puVar2;
                *puVar2 = uVar1;
            }
        }
        puVar7 = puVar6;
        puVar8 = puVar2 + 1;
        goto joined_r0x000141747d5a;
    }
joined_r0x000141747da6:
    for (; puFirst < puVar9; puVar9 = puVar9 + -1) {
        puVar8 = puVar8 + -1;
        // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,*puVar8,*puVar5);
        bVar3 = g_fnLeagueCmp(local_res20, *puVar8, *puVar5);
        if (!bVar3) {
            // ORIGINAL: bVar3 = FUN_1417ba4c0(local_res20,*puVar5,*puVar8);
            bVar3 = g_fnLeagueCmp(local_res20, *puVar5, *puVar8);
            if (bVar3) break;
            puVar5 = puVar5 + -1;
            if (puVar5 != puVar8) {
                uVar1 = *puVar5;
                *puVar5 = *puVar8;
                *puVar8 = uVar1;
            }
        }
    }
    if (puVar9 == puFirst) {
        if (puVar2 == puLast) {
            // ORIGINAL: *param_1 = puVar5; param_1[1] = puVar7;
            pOut[0] = (uint64_t)puVar5;
            pOut[1] = (uint64_t)puVar7;
            return;
        }
        if ((puVar7 != puVar2) && (puVar5 != puVar7)) {
            uVar1 = *puVar5;
            *puVar5 = *puVar7;
            *puVar7 = uVar1;
        }
        puVar7 = puVar7 + 1;
        puVar8 = puVar2 + 1;
        puVar4 = puVar5 + 1;
        if (puVar5 != puVar2) {
            uVar1 = *puVar5;
            *puVar5 = *puVar2;
            *puVar2 = uVar1;
        }
    }
    else {
        puVar9 = puVar9 + -1;
        if (puVar2 == puLast) {
            puVar4 = puVar5 + -1;
            if (puVar9 != puVar4) {
                uVar1 = *puVar9;
                *puVar9 = *puVar4;
                *puVar4 = uVar1;
            }
            puVar7 = puVar7 + -1;
            puVar8 = puVar2;
            if (puVar4 != puVar7) {
                uVar1 = *puVar4;
                *puVar4 = *puVar7;
                *puVar7 = uVar1;
            }
        }
        else {
            if (puVar2 != puVar9) {
                uVar1 = *puVar2;
                *puVar2 = *puVar9;
                *puVar9 = uVar1;
            }
            puVar8 = puVar2 + 1;
            puVar4 = puVar5;
        }
    }
    goto joined_r0x000141747d5a;
}

// ================= FUN_14174cb10 =================
// the introsort entry: (first, one-past-last, depth, state).
void LeagueSortIntro(uint32_t* puFirst, uint32_t* puLast, int64_t nDepth, int nState) {
    uint32_t* puCut;
    uint32_t* puNext;
    int64_t lVar2;
    uint64_t local_18[2];

    lVar2 = (int64_t)puLast - (int64_t)puFirst;
    do {
        lVar2 = lVar2 >> 2;   // the element count
        if (lVar2 < 0x21) {
LAB_14174cbe5:
            if (1 < lVar2) {
                LeagueSortInsertion(puFirst, puLast, nState);
            }
            return;
        }
        if (nDepth < 1) {
            if (0x20 < lVar2) {
                LeagueSortMakeHeap((int64_t)puFirst, (int64_t)puLast, nState);
                LeagueSortSortHeap(puFirst, (int64_t)puLast, nState);
                return;
            }
            goto LAB_14174cbe5;
        }
        // ORIGINAL: FUN_141747c80(&local_18,param_1,param_2,param_4);
        LeagueSortPartition(local_18, puFirst, puLast, nState);
        puCut = (uint32_t*)local_18[0];
        puNext = (uint32_t*)local_18[1];
        // ORIGINAL: param_3 = param_3 / 2 + (param_3 / 2) / 2;
        nDepth = nDepth / 2 + (nDepth / 2) / 2;
        // ORIGINAL: if ((longlong)((longlong)local_18 - (longlong)param_1 & 0xfffffffffffffffcU) < (longlong)((longlong)param_2 - (longlong)local_10 & 0xfffffffffffffffcU))
        if (((int64_t)puCut - (int64_t)puFirst & (int64_t)0xfffffffffffffffcU) <
            ((int64_t)puLast - (int64_t)puNext & (int64_t)0xfffffffffffffffcU)) {
            LeagueSortIntro(puFirst, puCut, nDepth, nState);
            puFirst = puNext;
        }
        else {
            LeagueSortIntro(puNext, puLast, nDepth, nState);
            puLast = puCut;
        }
        lVar2 = (int64_t)puLast - (int64_t)puFirst;
    } while (true);
}

}  // namespace syndicate

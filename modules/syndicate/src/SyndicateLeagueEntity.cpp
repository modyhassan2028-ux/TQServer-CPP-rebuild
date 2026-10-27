// ============================================================
// Syndicate.dll port — unit T9/D35: the league ENTITY
// member-vector ops + the special-member erase, verbatim
// (see the header for the map).
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_14174a350 @ 14174a350 (vector<8>::insert_n)
//   FUN_14174c5a0 @ 14174c5a0 (vector<8>::insert_one)
//   FUN_14174c6d0 @ 14174c6d0 (vector<0x2d>::insert_n)
//   FUN_14174a300 @ 14174a300 (the wrap helper)
//   FUN_141745f80 @ 141745f80 (the 8-byte allocator)
//   FUN_141745f00 @ 141745f00 (the 0x2d allocator)
//   FUN_141746e20 @ 141746e20 (the 0x2d fill)
//   FUN_141746480 @ 141746480 (the 0x2d move)
//   FUN_1417461f0 @ 1417461f0 (the 0x2d backward copy)
//   FUN_141748dd0 @ 141748dd0 (the 8-byte shift)
//   FUN_141746d00 @ 141746d00 (the 8-byte backshift)
//   FUN_141744b50 @ 141744b50 (the 8-byte overflow throw)
//   FUN_141744ad0 @ 141744ad0 (the 0x2d overflow throw)
//   FUN_1417d5070 @ 1417d5070 (the record release)
//   FUN_1417d4db0 @ 1417d4db0 (the dual release)
//   FUN_14174c0c0 @ 14174c0c0 (the special-member erase)
// ============================================================
#include "modules/syndicate/src/SyndicateLeagueEntity.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"   // g_fnLeagueInvalid + the log seams
#include "modules/syndicate/src/SyndicateLeagueTree.h"  // the D32 LeagueErase
#include <cstring>
#include <new>
#include <stdexcept>

namespace syndicate {

// ================= FUN_141745f80 =================
// the 8-byte element allocator: the MSVC 128-bit overflow
// divide (0xffffffffffffffff_ffffffff / n < 8) then the
// tail call operator_new(n * 8). The allocator slot
// (param_1) is stateless and unused.
void* LeagueVec8Alloc(void* pAlloc, uint64_t uCount) {
    (void)pAlloc;
    // ORIGINAL: if ((param_2 != 0) && (SUB168((2^128-1) / param_2, 0) < 8))
    //            throw bad_alloc;
    if ((uCount != 0) &&
        (uCount > (uint64_t)0xffffffffffffffff / 8)) {
        throw std::bad_alloc();
    }
    // ORIGINAL: operator_new(param_2 * 8);
    return operator new(uCount * 8);
}

// ================= FUN_141745f00 =================
// the same for the 0x2d-byte records.
void* LeagueVec45Alloc(void* pAlloc, uint64_t uCount) {
    (void)pAlloc;
    if ((uCount != 0) &&
        (uCount > (uint64_t)0xffffffffffffffff / 0x2d)) {
        throw std::bad_alloc();
    }
    return operator new(uCount * 0x2d);
}

// ================= FUN_141744b50 / FUN_141744ad0 =================
// the "vector<T> too long" length_error throws (identical
// bodies — the CRT-compliant throw convention of the
// earlier units).
[[noreturn]] void LeagueThrowVecTooLong8() {
    throw std::length_error("vector<T> too long");
}
[[noreturn]] void LeagueThrowVecTooLong45() {
    throw std::length_error("vector<T> too long");
}

// ================= FUN_141746e20 =================
// the 0x2d fill: copy the 45-byte record count times.
void LeagueVec45Fill(void* pDest, int64_t lCount, void* pSrc) {
    char* pcDst = (char*)pDest;
    char* pcSrc = (char*)pSrc;
    for (; lCount != 0; lCount = lCount - 1) {
        if (pcDst != (void*)0x0) {
            *(uint64_t*)(pcDst + 0x00) = *(uint64_t*)(pcSrc + 0x00);
            *(uint64_t*)(pcDst + 0x08) = *(uint64_t*)(pcSrc + 0x08);
            *(uint64_t*)(pcDst + 0x10) = *(uint64_t*)(pcSrc + 0x10);
            *(uint64_t*)(pcDst + 0x18) = *(uint64_t*)(pcSrc + 0x18);
            *(uint64_t*)(pcDst + 0x20) = *(uint64_t*)(pcSrc + 0x20);
            *(uint32_t*)(pcDst + 0x28) = *(uint32_t*)(pcSrc + 0x28);
            *(uint8_t*)(pcDst + 0x2c) = *(uint8_t*)(pcSrc + 0x2c);
        }
        pcDst = pcDst + 0x2d;
    }
}

// ================= FUN_141746480 =================
// the 0x2d move: [first, last) → dest, returns the
// advanced dest.
void* LeagueVec45Move(void* pFirst, void* pLast, void* pDest) {
    char* pcSrc = (char*)pFirst;
    char* pcDst = (char*)pDest;
    for (; pcSrc != pLast; pcSrc = pcSrc + 0x2d) {
        if (pcDst != (void*)0x0) {
            *(uint64_t*)(pcDst + 0x00) = *(uint64_t*)(pcSrc + 0x00);
            *(uint64_t*)(pcDst + 0x08) = *(uint64_t*)(pcSrc + 0x08);
            *(uint64_t*)(pcDst + 0x10) = *(uint64_t*)(pcSrc + 0x10);
            *(uint64_t*)(pcDst + 0x18) = *(uint64_t*)(pcSrc + 0x18);
            *(uint64_t*)(pcDst + 0x20) = *(uint64_t*)(pcSrc + 0x20);
            *(uint32_t*)(pcDst + 0x28) = *(uint32_t*)(pcSrc + 0x28);
            *(uint8_t*)(pcDst + 0x2c) = *(uint8_t*)(pcSrc + 0x2c);
        }
        pcDst = pcDst + 0x2d;
    }
    return pcDst;
}

// ================= FUN_1417461f0 =================
// the 0x2d backward copy (last→first): the -0x2d stepwise
// field copy; returns dest - count*0x2d... see the tail.
int64_t LeagueVec45BackCopy(int64_t lFirst, int64_t lLast, int64_t lDest) {
    int64_t lVar1;
    int64_t lVar2;
    int64_t lVar3;

    if (lFirst != lLast) {
        lVar1 = lDest - lLast;
        lVar2 = lLast;
        do {
            lVar3 = lVar2 + -0x2d;
            *(uint64_t*)(lVar1 + lVar3) = *(uint64_t*)(lVar2 + -0x2d);
            *(uint64_t*)(lVar1 + 8 + lVar3) = *(uint64_t*)(lVar2 + -0x25);
            *(uint64_t*)(lVar1 + 0x10 + lVar3) = *(uint64_t*)(lVar2 + -0x1d);
            *(uint64_t*)(lVar1 + 0x18 + lVar3) = *(uint64_t*)(lVar2 + -0x15);
            *(uint64_t*)(lVar1 + 0x20 + lVar3) = *(uint64_t*)(lVar2 + -0xd);
            *(uint32_t*)(lVar1 + 0x28 + lVar3) = *(uint32_t*)(lVar2 + -5);
            *(uint8_t*)(lVar1 + 0x2c + lVar3) = *(uint8_t*)(lVar2 + -1);
            lVar2 = lVar3;
        } while (lVar3 != lFirst);
    }
    // ORIGINAL: return param_3 + ((param_2 - param_1) / 0x2d) * -0x2d;
    return lDest + ((lLast - lFirst) / 0x2d) * -0x2d;
}

// ================= FUN_141748dd0 =================
// the 8-byte forward shift: memmove [first, last) to the
// DEST (param_4 — param_1 is the unused allocator slot);
// returns dst + bytes.
void* LeagueVec8Shift(void* pUnused, void* pFirst, int64_t lLast, void* pDst) {
    (void)pUnused;
    int64_t lVar1;
    lVar1 = (lLast - (int64_t)pFirst) >> 3;
    if (lVar1 != 0) {
        // ORIGINAL: memmove_s(param_4, lVar1 * 8, param_2, lVar1 * 8);
        memmove(pDst, pFirst, lVar1 * 8);
    }
    return (void*)(lVar1 * 8 + (int64_t)pDst);
}

// ================= FUN_141746d00 =================
// the 8-byte backshift: memmove [first, last) to
// dstEnd - n.
void* LeagueVec8BackShift(void* pFirst, int64_t lLast, int64_t lDstEnd) {
    int64_t lVar1;
    void* pvDst;
    lVar1 = (lLast - (int64_t)pFirst) >> 3;
    pvDst = (void*)(lDstEnd + lVar1 * -8);
    if (0 < lVar1) {
        memmove(pvDst, pFirst, lVar1 * 8);
    }
    return pvDst;
}

// ================= FUN_14174a300 =================
// the wrap helper: new 8 storing the CALLER's slot address,
// then the slot takes the new block; returns the slot.
void* LeagueWrapQword(void* pSlot) {
    void** ppSlot = (void**)pSlot;
    void** ppNew;
    ppNew = (void**)operator new(8);
    if (ppNew == (void**)0x0) {
        ppNew = (void**)0x0;
    }
    else {
        *ppNew = (void*)ppSlot;
    }
    *ppSlot = (void*)ppNew;
    return pSlot;
}

// ================= FUN_14174a350 =================
// vector<8>::insert_n — vec layout: alloc@+0x10,
// begin@+0x18, finish@+0x20, endcap@+0x28; whereIter =
// {ptr-pair} with where[1] = the insertion pointer.
void LeagueVec8InsertN(int64_t lVec, void* pWhere, uint64_t uCount, void* pValue) {
    char* pcVec = (char*)lVec;
    char** ppWhere = (char**)pWhere;
    void* pvVar2;
    int64_t lVar3;
    uint64_t uVar4;
    char* pcOldBegin;
    int64_t lVar6;
    uint64_t uVar8;
    void* pvVar9;
    uint64_t uVar10;

    // ORIGINAL: lVar3 = *(longlong *)(param_1 + 0x18);
    lVar3 = *(int64_t*)(pcVec + 0x18);       // begin
    if (lVar3 == 0) {
        uVar4 = 0;
    }
    else {
        uVar4 = (uint64_t)(*(int64_t*)(pcVec + 0x28) - lVar3) >> 3;   // capacity
    }
    uVar8 = 0;
    if (uCount != 0) {
        // ORIGINAL: lVar6 = *(longlong *)(param_1 + 0x20); lVar3 = lVar6 - lVar3 >> 3;
        lVar6 = *(int64_t*)(pcVec + 0x20);   // finish
        lVar3 = (lVar6 - lVar3) >> 3;        // the old size
        // ORIGINAL: if (0x1fffffffffffffffU - lVar3 < param_3) FUN_141744b50();
        if ((uint64_t)0x1fffffffffffffff - lVar3 < uCount) {
            LeagueThrowVecTooLong8();
        }
        uVar10 = uCount + lVar3;             // the new size
        if (uVar4 < uVar10) {
            // ---- the realloc-grow path ----
            if (uVar4 <= 0x1fffffffffffffff - (uVar4 >> 1)) {
                uVar8 = uVar4 + (uVar4 >> 1);
            }
            if (uVar8 < uVar10) {
                uVar8 = uVar10;
            }
            pvVar2 = LeagueVec8Alloc(pcVec + 0x10, uVar8);
            lVar3 = (int64_t)((*(int64_t*)((char*)ppWhere + 8)) - *(int64_t*)(pcVec + 0x18)) >> 3;
            // fill [mid, mid+count) with the value
            char* pcFill = (char*)pvVar2 + lVar3 * 8;
            for (uVar4 = uCount; uVar4 != 0; uVar4 = uVar4 - 1) {
                *(void**)pcFill = *(void**)pValue;
                pcFill = pcFill + 8;
            }
            // move [begin, where) ahead
            lVar6 = (*(int64_t*)((char*)ppWhere + 8) - *(int64_t*)(pcVec + 0x18)) >> 3;
            if (lVar6 != 0) {
                memmove(pvVar2, (void*)*(int64_t*)(pcVec + 0x18), lVar6 * 8);
            }
            // move [where, finish) after
            lVar6 = (*(int64_t*)(pcVec + 0x20) - *(int64_t*)((char*)ppWhere + 8)) >> 3;
            if (lVar6 != 0) {
                memmove((void*)((int64_t)pvVar2 + (lVar3 + (int64_t)uCount) * 8),
                        (void*)*(int64_t*)((char*)ppWhere + 8), lVar6 * 8);
            }
            pcOldBegin = *(char**)(pcVec + 0x18);
            lVar3 = *(int64_t*)(pcVec + 0x20);
            if (pcOldBegin != (void*)0x0) {
                operator delete(pcOldBegin);
            }
            *(int64_t*)(pcVec + 0x28) = (int64_t)pvVar2 + uVar8 * 8;
            *(int64_t*)(pcVec + 0x20) =
                (int64_t)pvVar2 + (uCount + ((lVar3 - (int64_t)pcOldBegin) >> 3)) * 8;
            *(int64_t*)(pcVec + 0x18) = (int64_t)pvVar2;
        }
        else if ((uint64_t)((lVar6 - *(int64_t*)((char*)ppWhere + 8)) >> 3) < uCount) {
            // ---- the shift-mid path (the insertion tail splits) ----
            void* pvVal = *(void**)pValue;
            // ORIGINAL: FUN_141748dd0(param_1, where, lVar6, where + count*8);
            LeagueVec8Shift(pcVec, (void*)*(int64_t*)((char*)ppWhere + 8), lVar6,
                (void*)((int64_t)*(int64_t*)((char*)ppWhere + 8) + (int64_t)uCount * 8));
            char* pcFill = *(char**)(pcVec + 0x20);
            char* pcWhere1 = *(char**)((char*)ppWhere + 8);
            for (lVar3 = (int64_t)uCount -
                     ((pcFill - pcWhere1) >> 3);
                 lVar3 != 0; lVar3 = lVar3 + -1) {
                *(void**)pcFill = pvVal;
                pcFill = pcFill + 8;
            }
            *(int64_t*)(pcVec + 0x20) = *(int64_t*)(pcVec + 0x20) + uCount * 8;
            lVar3 = *(int64_t*)(pcVec + 0x20);
            for (char* pc = *(char**)((char*)ppWhere + 8);
                 pc != (char*)(lVar3 + (int64_t)uCount * -8); pc = pc + 8) {
                *(void**)pc = pvVal;
            }
        }
        else {
            // ---- the shift-tail path ----
            void* pvVal = *(void**)pValue;
            void* pvVar9 = (void*)(lVar6 + (int64_t)uCount * -8);
            // ORIGINAL: FUN_141748dd0(param_1, pvVar9, lVar6, (void*)lVar6);
            void* pvVar2 = LeagueVec8Shift(pcVec, pvVar9, lVar6, (void*)lVar6);
            *(int64_t*)(pcVec + 0x20) = (int64_t)pvVar2;
            LeagueVec8BackShift((void*)*(int64_t*)((char*)ppWhere + 8),
                (int64_t)pvVar9, lVar6);
            char* pc = *(char**)((char*)ppWhere + 8);
            char* pcEnd = pc + uCount * 8;
            for (; pc != pcEnd; pc = pc + 8) {
                *(void**)pc = pvVal;
            }
        }
    }
}

// ================= FUN_14174c5a0 =================
// vector<8>::insert_one: captures the offset of where,
// delegates to insert_n, then re-validates and returns the
// {begin', offset} iterator.
void* LeagueVec8InsertOne(int64_t lVec, void* pOut, void* pWhere, void* pValue) {
    char* pcVec = (char*)lVec;
    int64_t** pplWhere = (int64_t**)pWhere;
    int64_t** pplOut = (int64_t**)pOut;
    uint64_t uVar1;
    int64_t lVar3;
    int64_t lVar4;
    int64_t lVar5;
    int64_t* local_28[2];   // the where copy {ptr, off-ptr} — ADJACENT

    lVar3 = 0;
    // ORIGINAL: uVar1 = param_1[3];
    uVar1 = *(uint64_t*)(pcVec + 0x18);   // begin
    lVar4 = lVar3;
    if ((uint64_t)(*(uint64_t*)(pcVec + 0x20) - uVar1) & 0xfffffffffffffff8) {
        if (*(uint64_t*)(pcVec + 0x20) < uVar1) {
            g_fnLeagueInvalid();
        }
        // ORIGINAL: if ((*param_3 == 0) || (*param_3 != *param_1))
        if ((*pplWhere == (int64_t*)0x0) || (*pplWhere != *(int64_t**)pcVec)) {
            g_fnLeagueInvalid();
        }
        // ORIGINAL: lVar4 = (longlong)(param_3[1] - uVar1) >> 3;
        lVar4 = (int64_t)((int64_t)pplWhere[1] - (int64_t)uVar1) >> 3;
    }
    // ORIGINAL: local_28 = *param_3; uStack_20 = param_3[1];
    // the where copy {owner, ptr}
    local_28[0] = *pplWhere;
    local_28[1] = (int64_t*)pplWhere[1];
    LeagueVec8InsertN(lVec, (void*)local_28, 1, pValue);
    // ORIGINAL: uVar1 = param_1[3]; (the new begin)
    uVar1 = *(uint64_t*)(pcVec + 0x18);
    if (*(uint64_t*)(pcVec + 0x20) < uVar1) {
        g_fnLeagueInvalid();
    }
    int64_t* plBegin = *(int64_t**)pcVec;   // ORIGINAL: plVar2 = (longlong *)*param_1;
    local_28[0] = plBegin;
    local_28[1] = (int64_t*)uVar1;
    if (plBegin == (int64_t*)0x0) {
        g_fnLeagueInvalid();
        lVar5 = lVar3;
    }
    else {
        lVar5 = *plBegin;
    }
    // ORIGINAL: uVar1 = uVar1 + lVar4 * 8;
    uVar1 = uVar1 + (uint64_t)lVar4 * 8;
    if (uVar1 <= *(uint64_t*)(lVar5 + 0x20)) {
        if (plBegin != (int64_t*)0x0) {
            lVar3 = *plBegin;
        }
        if (*(uint64_t*)(lVar3 + 0x18) <= uVar1) {
            goto LAB_14174c694;
        }
    }
    g_fnLeagueInvalid();
LAB_14174c694:
    pplOut[0] = (int64_t*)local_28[0];
    pplOut[1] = (int64_t*)uVar1;
    return pOut;
}

// ================= FUN_14174c6d0 =================
// vector<0x2d>::insert_n — the same tri-path for the
// 45-byte DefRecords. The MSVC EH unwind state (the
// security cookie at DAT_141886c40, the local_94 stage
// markers 1/2, the local_a0/local_a8 zero-writes) is
// COMPILER-GENERATED bookkeeping — documented, not logic.
void LeagueVec45InsertN(int64_t lVec, void* pWhere, uint64_t uCount, void* pValue) {
    char* pcVec = (char*)lVec;
    char** ppWhere = (char**)pWhere;
    void* pvVar3;
    void* pvVar4;
    uint64_t uVar6;
    uint64_t uVar1;
    int64_t lVar2;
    char* pcSrc;
    char* pcDst;
    void* pvVar9;
    void* pvVar5;
    // the value copy (the 45-byte record lifted to locals)
    uint64_t local_78 = *(uint64_t*)((char*)pValue + 0x00);
    uint64_t local_70 = *(uint64_t*)((char*)pValue + 0x08);
    uint64_t local_68 = *(uint64_t*)((char*)pValue + 0x10);
    uint64_t local_60 = *(uint64_t*)((char*)pValue + 0x18);
    uint64_t local_58 = *(uint64_t*)((char*)pValue + 0x20);
    uint32_t local_50 = *(uint32_t*)((char*)pValue + 0x28);
    uint8_t local_4c = *(uint8_t*)((char*)pValue + 0x2c);

    lVar2 = *(int64_t*)(pcVec + 0x18);       // begin
    if (lVar2 == 0) {
        uVar6 = 0;
    }
    else {
        uVar6 = (uint64_t)(*(int64_t*)(pcVec + 0x28) - lVar2) / 0x2d;
    }
    if (uCount != 0) {
        pvVar4 = *(void**)(pcVec + 0x20);    // finish
        lVar2 = ((int64_t)pvVar4 - lVar2) / 0x2d;
        // ORIGINAL: if (0x5b05b05b05b05b0U - lVar2 < param_3) FUN_141744ad0();
        if ((uint64_t)0x5b05b05b05b05b0 - lVar2 < uCount) {
            LeagueThrowVecTooLong45();
        }
        uVar1 = lVar2 + uCount;
        if (uVar6 < uVar1) {
            // ---- the realloc-grow path ----
            if (0x5b05b05b05b05b0 - (uVar6 >> 1) < uVar6) {
                uVar6 = 0;
            }
            else {
                uVar6 = uVar6 + (uVar6 >> 1);
            }
            if (uVar6 < uVar1) {
                uVar6 = uVar1;
            }
            pvVar4 = LeagueVec45Alloc(pcVec + 0x10, uVar6);
            lVar2 = (*(int64_t*)((char*)ppWhere + 8) - *(int64_t*)(pcVec + 0x18)) / 0x2d;
            LeagueVec45Fill((void*)(lVar2 * 0x2d + (int64_t)pvVar4), uCount, pValue);
            LeagueVec45Move(*(void**)(pcVec + 0x18), *(void**)((char*)ppWhere + 8), pvVar4);
            LeagueVec45Move(*(void**)((char*)ppWhere + 8), *(void**)(pcVec + 0x20),
                (void*)((uCount + lVar2) * 0x2d + (int64_t)pvVar4));
            char* pcOld = *(char**)(pcVec + 0x18);
            lVar2 = *(int64_t*)(pcVec + 0x20);
            if (pcOld != (void*)0x0) {
                operator delete(pcOld);
            }
            *(uint64_t*)(pcVec + 0x28) = uVar6 * 0x2d + (uint64_t)pvVar4;
            *(uint64_t*)(pcVec + 0x20) =
                (uCount + (uint64_t)(lVar2 - (int64_t)pcOld) / 0x2d) * 0x2d + (uint64_t)pvVar4;
            *(uint64_t*)(pcVec + 0x18) = (uint64_t)pvVar4;
        }
        else if ((uint64_t)(((int64_t)pvVar4 - *(int64_t*)((char*)ppWhere + 8)) / 0x2d) < uCount) {
            // ---- the shift-mid path ----
            LeagueVec45Move(*(void**)((char*)ppWhere + 8), pvVar4,
                (void*)((int64_t)*(void**)((char*)ppWhere + 8) + uCount * 0x2d));
            LeagueVec45Fill(*(void**)(pcVec + 0x20),
                uCount - ((int64_t)*(void**)(pcVec + 0x20) -
                          *(int64_t*)((char*)ppWhere + 8)) / 0x2d,
                &local_78);
            *(int64_t*)(pcVec + 0x20) = *(int64_t*)(pcVec + 0x20) + uCount * 0x2d;
            lVar2 = *(int64_t*)(pcVec + 0x20);
            for (char* pc = *(char**)((char*)ppWhere + 8);
                 pc != (char*)(lVar2 + (int64_t)uCount * -0x2d);
                 pc = pc + 0x2d) {
                *(uint64_t*)(pc + 0x00) = local_78;
                *(uint64_t*)(pc + 0x08) = local_70;
                *(uint64_t*)(pc + 0x10) = local_68;
                *(uint64_t*)(pc + 0x18) = local_60;
                *(uint64_t*)(pc + 0x20) = local_58;
                *(uint32_t*)(pc + 0x28) = local_50;
                *(uint8_t*)(pc + 0x2c) = local_4c;
            }
        }
        else {
            // ---- the shift-tail path ----
            void* pvVar7 = (void*)((int64_t)pvVar4 + (int64_t)uCount * -0x2d);
            void* pvVar5 = LeagueVec45Move(pvVar7, pvVar4, pvVar4);
            *(void**)(pcVec + 0x20) = pvVar5;
            LeagueVec45BackCopy(*(int64_t*)((char*)ppWhere + 8), (int64_t)pvVar7,
                (int64_t)pvVar4);
            char* pc = *(char**)((char*)ppWhere + 8);
            char* pcEnd = pc + uCount * 0x2d;
            for (; pc != pcEnd; pc = pc + 0x2d) {
                *(uint64_t*)(pc + 0x00) = local_78;
                *(uint64_t*)(pc + 0x08) = local_70;
                *(uint64_t*)(pc + 0x10) = local_68;
                *(uint64_t*)(pc + 0x18) = local_60;
                *(uint64_t*)(pc + 0x20) = local_58;
                *(uint32_t*)(pc + 0x28) = local_50;
                *(uint8_t*)(pc + 0x2c) = local_4c;
            }
        }
    }
}

// ================= FUN_1417d5070 =================
// the record release: if rec+8 holds a holder, call its
// vt+0x40 with arg 0.
void LeagueRecRelease(int64_t lRec) {
    char* pcRec = (char*)lRec;
    if (*(int64_t*)(pcRec + 8) != 0) {
        void** pplHolder = *(void***)(pcRec + 8);
        void** ppvt = *(void***)pplHolder;
        // ORIGINAL: (**(code **)(**(longlong **)(param_1 + 8) + 0x40))(...,0);
        void (*pfn)(void**, uint64_t) = (void (*)(void**, uint64_t))((void**)ppvt)[8];
        pfn(pplHolder, 0);
    }
}

// ================= FUN_1417d4db0 =================
// the dual release: the rec[1] holder call with (1, msg3,
// msg4, -2) + the DOUBLE zero of rec[1] + the rec[0]
// vt call with arg 1. (param_2 is ignored — the iter.)
void LeagueRecRelease2(void* pRec, void* pIter, uint64_t uMsg1, uint64_t uMsg2) {
    (void)pIter;
    void** ppRec = (void**)pRec;
    if (ppRec[1] != (void**)0x0) {
        // ORIGINAL: (*(code *)**(undefined8 **)param_1[1])(param_1[1],1,param_3,param_4,-2);
        // the DOUBLE deref: holder[0] = the vtable, vtable[0] = the fn
        void** pplHolder = (void**)ppRec[1];
        void (*pfn)(void**, uint64_t, uint64_t, uint64_t, int64_t) =
            (void (*)(void**, uint64_t, uint64_t, uint64_t, int64_t))
                **(void***)pplHolder;
        pfn(pplHolder, 1, uMsg1, uMsg2, (int64_t)0xfffffffffffffffe);
        ppRec[1] = (void**)0x0;
        ppRec[1] = (void**)0x0;   // the verbatim double store
    }
    // ORIGINAL: (**(code **)*param_1)(param_1,1);
    {
        void** ppvt = *(void***)ppRec;
        void (*pfn)(void**, uint64_t) = (void (*)(void**, uint64_t))*(void**)ppvt;
        pfn(ppRec, 1);
    }
}

// ================= FUN_14174c0c0 =================
// the special-member erase: resolves the league's records
// through the +8 provider, then erases the fixed member
// keys 0xcc and 0xcd from the map at entity+0xd8 with the
// record releases + the D32 map erase.
void LeagueEntityEraseSpecial(int64_t lEntity) {
    char* pcEnt = (char*)lEntity;
    int64_t* plVar5;
    void** pplProvider;
    void** pplHolder;
    char* pcVar11;

    // ---- the record setup ----
    if (*(int64_t*)(pcEnt + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
    }
    else {
        // ORIGINAL: plVar5 = (resolve(provider, 3));
        pplProvider = *(void***)(pcEnt + 8);
        {
            void** ppvt = *(void***)pplProvider;
            void* (*pfnResolve)(void**, uint64_t) =
                (void* (*)(void**, uint64_t))((void**)ppvt)[2];   // vt+0x10
            void** pplRec = (void**)pfnResolve(pplProvider, 3);
            // ORIGINAL: (**(code **)(*plVar5 + 0xb0))(plVar5,0);
            void** ppvt2 = *(void***)pplRec;
            void (*pfnB0)(void**, uint64_t) =
                (void (*)(void**, uint64_t))((void**)ppvt2)[22];   // 0xb0/8
            pfnB0(pplRec, 0);
        }
    }
    if (*(int64_t*)(pcEnt + 8) == 0) {
        void* pLog = g_fnLeagueLogFactory();
        g_fnLeagueLogWrite(pLog, 0, 1);
        pcVar11 = (char*)"m_pRec";
    }
    else {
        pplProvider = *(void***)(pcEnt + 8);
        {
            void** ppvt = *(void***)pplProvider;
            void* (*pfnResolve)(void**, uint64_t) =
                (void* (*)(void**, uint64_t))((void**)ppvt)[2];
            void** pplRec = (void**)pfnResolve(pplProvider, 4);
            pcVar11 = *(char**)pplRec;   // the inner object
            // ORIGINAL: (**(code **)((longlong)pcVar11 + 0x80))(puVar6,&DAT_141827409);
            void** ppvt2 = *(void***)pplRec;
            void (*pfn80)(void**, void*) =
                (void (*)(void**, void*))((void**)ppvt2)[16];   // 0x80/8
            pfn80(pplRec, (void*)"DAT_141827409");
        }
        // ORIGINAL: (**(code **)(**(longlong **)(param_1 + 8) + 0x38))(...,0);
        pplProvider = *(void***) (pcEnt + 8);
        {
            void** ppvt = *(void***)pplProvider;
            void (*pfn38)(void**, uint64_t) =
                (void (*)(void**, uint64_t))((void**)ppvt)[7];   // 0x38/8
            pfn38(pplProvider, 0);
        }
    }

    // ---- the two fixed-key erases (0xcc then 0xcd) ----
    for (int nPass = 0; nPass < 2; nPass++) {
        uint32_t uKey = (nPass == 0) ? 0xcc : 0xcd;
        char* pcMap = pcEnt + 0xd8;
        char* pcAnchor = *(char**)pcMap;
        char* pcHead = *(char**)(pcEnt + 0x108);   // map+0x30
        char* pcVar4;
        char* pcVar6;

        // the inline lower_bound (the while-shaped descent).
        // VERBATIM NOTE: the right branch carries the Ghidra round-trip
        // `puVar6 = puVar4` — the candidate does NOT advance when going
        // right (the standard lower_bound semantics).
        pcVar6 = *(char**)(pcHead + 8);   // the root = head[1]
        char cVar1 = *(char*)(pcVar6 + 0x29);
        pcVar4 = pcHead;
        while (cVar1 == '\0') {
            char* pcVar8;
            if (*(uint32_t*)(pcVar6 + 0x18) < uKey) {
                pcVar8 = *(char**)(pcVar6 + 0x10);   // right
                pcVar6 = pcVar4;                       // the round-trip (candidate → current)
            }
            else {
                pcVar8 = *(char**)pcVar6;             // left
            }
            pcVar4 = pcVar6;
            pcVar6 = pcVar8;
            cVar1 = *(char*)(pcVar8 + 0x29);
        }

        // the found/end gate + the iterator pairs (adjacent!)
        char* foundPair[2] = { pcAnchor, pcVar4 };     // {anchor, node}
        char* endPair[2] = { pcAnchor, pcHead };        // {anchor, head}
        char** pplVar9;
        if (pcAnchor == (char*)0x0) {
            g_fnLeagueInvalid();
        }
        if ((pcVar4 == pcHead) || (uKey < *(uint32_t*)(pcVar4 + 0x18))) {
            pplVar9 = endPair;
        }
        else {
            pplVar9 = foundPair;
        }
        // the copy of the chosen iterator
        char* iterCopy[2] = { pplVar9[0], pplVar9[1] };
        if ((pcAnchor == (char*)0x0) || (pcAnchor != iterCopy[0])) {
            g_fnLeagueInvalid();
        }
        // ORIGINAL: plVar3 = *(longlong **)(param_1 + 0x108); (the head)
        if (pcHead != iterCopy[1]) {
            int64_t lVar7;
            if (iterCopy[0] == (char*)0x0) {
                g_fnLeagueInvalid();
                lVar7 = 0;
            }
            else {
                lVar7 = *(int64_t*)iterCopy[0];   // the owner back-ref
            }
            if (iterCopy[1] == *(char**)(lVar7 + 0x30)) {
                g_fnLeagueInvalid();
            }
            // the record release pair
            void** pvRec = *(void***)(iterCopy[1] + 0x20);
            if (pvRec != (void**)0x0) {
                LeagueRecRelease((int64_t)pvRec);
                // ORIGINAL: FUN_1417d4db0(puVar6,pplVar10,pcVar11,param_4);
                // (the msg args are the file-path / m_pRec string slots —
                //  forwarded opaquely to the record's vt call)
                LeagueRecRelease2(pvRec, (void*)iterCopy,
                    (uint64_t)(uintptr_t)"m_pRec",
                    (uint64_t)(uintptr_t)"league.cpp");
            }
            // the erase: (map, the found pair, the copy pair)
            LeagueErase(pcMap, (void*)foundPair, (void*)iterCopy);
        }
    }
}

}  // namespace syndicate

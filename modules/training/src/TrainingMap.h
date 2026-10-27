// ============================================================
// Training.dll port — the std::map machinery (the RB tree).
// Wave 1, unit T2/D14. Addresses verbatim (1419e2ac0 /
// 1419e3320 / 1419e3240 / 1419e3360 / 1419e2d50 /
// 1419e2000 / 1419e26a0 / 1419e2100).
// ============================================================
#pragma once
#include "TrainingMgr.h"
#include <cstdint>

namespace training {

// ---- the iterator (4 qwords: 1419e3240's out) ----
struct SMapIterator {
    void* m_pProxy00;        // +0x00 (the map's proxy)
    STreeNode* m_pNode08;    // +0x08 (the current node)
    void* m_pProxy10;        // +0x10 (proxy again)
    STreeNode* m_pParent18;  // +0x18 (the insert parent)
};

// ---- the value record (3 qwords; 1419e2ac0 copies all
// three: key@+0x18, val@+0x20, val2@+0x28) ----
struct SValRec {
    uint64_t m_nKey;         // key: the low uint is the id
    void* m_pVal;
    uint64_t m_nVal2;
};

// ---- FUN_1419e2100: iterator ++ ----
// (at the end: the ORIGINAL falls into the unrecovered
// jumptable -> _invalid_parameter_noinfo; modeled by the
// seam g_fnInvalidParameter)
extern void (*g_fnInvalidParameter)();
void IteratorNext(SMapIterator* pIt);

// ---- FUN_1419e2ac0: the node make ----
// left = head, parent = pPar, right = head, RED, copies
// the 3 record qwords, isnil = 0
STreeNode* MakeNode(STreeNode* pHead, STreeNode* pPar,
                   const SValRec* pRec, uint8_t uColor);

// ---- FUN_1419e3320: the head (re)creation ----
// head = NewHeadNode(); isnil=1; the circular links;
// size = 0 (no proxy write — the caller owns it)
void InitMapHead(SMapKernel* pKern);

// ---- FUN_1419e2000: rotate RIGHT about param_2 (its
// LEFT child rises) ----
void RotateRight(SMapKernel* pKern, STreeNode* pP);

// ---- FUN_1419e26a0: rotate LEFT about param_2 (its
// RIGHT child rises) ----
void RotateLeft(SMapKernel* pKern, STreeNode* pP);

// ---- FUN_1419e3240: lower_bound ----
// (the 2-phase verbatim walk; out: {proxy, pLoc, proxy,
// pPar})
void LowerBound(SMapKernel* pKern, SMapIterator* pOut,
                uint32_t uKey);

// ---- FUN_1419e3360: insert (the fixup INLINE) ----
// (the "map/set<T> too long" length gate at size
// 0xaaaaaaaaaaaaaa8 documented — CRT, out of scope)
void InsertNode(SMapKernel* pKern, SMapIterator* pOut,
               bool bAddLeft, STreeNode* pPar,
               const SValRec* pRec);

// ---- FUN_1419e2d50: erase at the iterator ----
// (advances pWhere via 1419e2100; the "invalid map/set<T>
// iterator" out_of_range throw gate documented — CRT;
// splice/attach + the INLINE rebalance + the rotations)
void EraseAt(SMapKernel* pKern, SMapIterator* pOut,
             SMapIterator* pWhere);

} // namespace training

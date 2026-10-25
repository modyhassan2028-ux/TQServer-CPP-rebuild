#include "MsgMapGroupKernel.h"
#include <stdexcept>
#include <cstdlib>
namespace msg {
// the VERBATIM container init pattern (FUN_14000ef40 /
// FUN_1400ec260 / FUN_1400ef850 - identical except the inner
// allocator and the flag byte offset):
static void InitObjSet(SObjSet* pSet,
        std::function<SInnerObj*()>& fnAlloc,
        size_t nFlagByteOff) {  // BYTE offset
    // *param_1 = new(8){param_1}
    struct SHead { void* pOwner; };
    auto* pHead = (SHead*)std::malloc(sizeof(SHead));
    if (pHead) pHead->pOwner = pSet;
    pSet->m_pHead = pHead;
    // param_1[6] = <alloc>(param_1)
    SInnerObj* pInner = fnAlloc ? fnAlloc()
                               : (SInnerObj*)std::calloc(16,8);
    pSet->m_pInner = pInner;
    if (pInner) {
        // byte @inner+flagOffset = 1 (VERBATIM)
        *((uint8_t*)pInner + nFlagByteOff) = 1;
        // the tri-self-link @+0/+8/+0x10:
        pInner->m_q[1] = (uint64_t)pInner;  // +8
        pInner->m_q[0] = (uint64_t)pInner;  // +0
        pInner->m_q[2] = (uint64_t)pInner;  // +0x10
    }
    // param_1[7] = 0
    pSet->m_qCount = 0;
}
// ===== ORIGINAL FUN_1400f0000 @ 1400f0000 =====
CMapGroupKernel::CMapGroupKernel() {
    // +0x44 dword = 0 (implicit: zero-init members)
    // FUN_140009e80 (A sentinel): new(0x20), 3 qwords
    // zeroed, +0x1c = 1, +0x1d = 0 (ef40 raises 0x1d later)
    if (!m_fnAllocA)
        m_fnAllocA = [this]{
            m_vecAllocSizes.push_back(0x20);
            auto* p = (SInnerObj*)operator new(0x20);
            if (p) {
                p->m_q[0] = p->m_q[1] = p->m_q[2] = 0;
                *((uint8_t*)p + 0x1c) = 1;
                *((uint8_t*)p + 0x1d) = 0;
            }
            return p; };
    // FUN_1400e4f40 (B sentinel): new(0x30), +0x28 = 1,
    // +0x29 = 0 (ec260 raises 0x29 later)
    if (!m_fnAllocB)
        m_fnAllocB = [this]{
            m_vecAllocSizes.push_back(0x30);
            auto* p = (SInnerObj*)operator new(0x30);
            if (p) {
                p->m_q[0] = p->m_q[1] = p->m_q[2] = 0;
                *((uint8_t*)p + 0x28) = 1;
                *((uint8_t*)p + 0x29) = 0;
            }
            return p; };
    // FUN_1400e50b0 default (when no seam injected):
    // new(0x80), first 3 qwords zeroed, @+0x78 = 1,
    // @+0x79 = 0 (before ef850 sets the 0x79 flag itself)
    if (!m_fnAllocJail)
        m_fnAllocJail = [this]{
            m_vecAllocSizes.push_back(0x80);
            auto* p = (SInnerObj*)operator new(0x80);
            if (p) {
                p->m_q[0] = p->m_q[1] = p->m_q[2] = 0;
                *((uint8_t*)p + 0x78) = 1;
                *((uint8_t*)p + 0x79) = 0;
            }
            return p; };
    // the 3 A/B pairs + the jail list, VERBATIM order:
    InitObjSet(&m_setA1,   m_fnAllocA,    0x1d);
    InitObjSet(&m_setB1,   m_fnAllocB,    0x29);
    InitObjSet(&m_setA2,   m_fnAllocA,    0x1d);
    InitObjSet(&m_setB2,   m_fnAllocB,    0x29);
    InitObjSet(&m_setA3,   m_fnAllocA,    0x1d);
    InitObjSet(&m_setB3,   m_fnAllocB,    0x29);
    InitObjSet(&m_setJail, m_fnAllocJail, 0x79);
}
} // namespace msg

namespace msg {

// ===== M49: ORIGINAL FUN_14000bfd0 (insert) =====
SSetNode* SetInsert(SObjSet* pSet, SSetNode* pHint,
                    bool bAfter, uint64_t qKey) {
    // max_size guard VERBATIM: 0x3ffffffffffffffd
    if (0x3ffffffffffffffdULL < (uint64_t)pSet->m_qCount) {
        throw std::length_error(
            "map/set<T> too long");
    }
    // ORIGINAL: FUN_140009ab0(set, set.inner, hint,
    // set.inner, key, 0) - now the REAL allocator (M50):
    SSetNode* pSent0 = (SSetNode*)pSet->m_pInner;
    SSetNode* pNew = TreeNodeAlloc(pSent0, pHint, pSent0,
                                   (uint32_t)qKey, 0);
    pSet->m_qCount++;               // [7]+1 VERBATIM
    SSetNode* pSent = (SSetNode*)pSet->m_pInner;
    if (pHint == pSent) {
        // the EMPTY/first branch VERBATIM: sentinel+8,
        // sentinel+0 and sentinel+0x10 all -> node
        pSent->m_pNext = pNew;
        pSent->m_pPrev = pNew;
        pSent->m_pParent = pNew;
    } else if (!bAfter) {
        // link AFTER the hint: hint[2] = node
        pHint->m_pParent = pNew;
        if (pHint == pSent->m_pPrev) {
            // hint == tail: sentinel+0x10 = node
            pSent->m_pPrev = pNew;
        }
    } else {
        // link BEFORE the hint: *hint = node; head fixup
        pHint->m_pPrev = pNew;
        if (pHint == pSent->m_pNext) {
            // hint == head: sentinel+8 = node
            pSent->m_pNext = pNew;
        }
    }
    return pNew;
}

// ===== M49: ORIGINAL FUN_14000ab40 (erase) =====
void SetErase(SObjSet* pSet, SSetNode* pIt) {
    // the end() check VERBATIM: the sentinel is flagged
    if (pIt->m_byFlag != 0) {
        throw std::out_of_range(
            "invalid map/set<T> iterator");
    }
    // ===== M51: the VERBATIM splice of FUN_14000ab40
    // layout: +0 left, +8 right, +0x10 parent, +0x1c color
    SSetNode* pSent = (SSetNode*)pSet->m_pInner;
    uint8_t* pbyE = (uint8_t*)pIt;
    SSetNode* pL = pIt->m_pPrev;        // *plVar5
    SSetNode* pR = pIt->m_pNext;        // plVar5[1]
    SSetNode* pPar = pIt->m_pParent;    // plVar5[2]
    // the predecessor walk (the ORIGINAL ran
    // FUN_1400075f0 on the iterator first):
    SSetNode* pPred = pIt;
    IteratorPrev(&pPred);                // replacement node
    SSetNode* pParPred = pPred->m_pParent;  // plVar10[2]
    bool bTwo = (pL->m_byFlag == 0) && (pR->m_byFlag == 0)
              && (pPred != pIt);
    if (bTwo) {
        // plVar11[1] = plVar10; *plVar10 = *plVar5
        pL->m_pNext = pPred;
        pPred->m_pPrev = pL;
        if (pPred != pPar) {
            SSetNode* pRPred = pPred->m_pNext;
            if (pParPred->m_byFlag == 0)
                pParPred->m_pNext = pRPred;
            pRPred->m_pPrev = pParPred;
            pPred->m_pParent = pPar;
            pPar->m_pNext = pPred;      // *(plVar5[2]+8)
        }
        // head fixup / sibling fixup VERBATIM:
        if (pSent->m_pNext == pIt) {
            pSent->m_pNext = pPred;      // *(param_1[6]+8)
        } else {
            SSetNode* pSib = pIt->m_pNext;
            if (pSib->m_pPrev == pIt)
                pSib->m_pPrev = pPred;
            else
                pSib->m_pParent = pPred; // puVar7[2]
        }
        pPred->m_pNext = pR;             // plVar10[1]
        // the COLOR transplant @+0x1c VERBATIM (swap):
        if (pPred != pIt) {
            uint8_t t = pPred->m_byColor;
            pPred->m_byColor = pIt->m_byColor;
            pIt->m_byColor = t;
        }
        // leftmost fixup: *(longlong**)param_1[6] = pred
        pSent->m_pPrev = pPred;          // [in this port:
        //  +0 slot == m_pPrev/leftmost] VERBATIM slot 0
    } else {
        // single/no-child relink (simplified, tail of
        // the ORIGINAL else branch - TBD full splice)
        if (pL->m_byFlag == 0)
            pL->m_pParent = pPar;
        if (pR->m_byFlag == 0)
            pR->m_pParent = pPar;
        if (pSent->m_pNext == pIt)
            pSent->m_pNext = (pR->m_byFlag==0)?pR:pL;
        if (pSent->m_pPrev == pIt)
            pSent->m_pPrev = (pL->m_byFlag==0)?pL:pR;
    }
    // rightmost fixup on the sentinel (+0x10):
    if (pSent->m_pParent == pIt) {
        SSetNode* pWalk = bTwo ? pPred : pParPred;
        pSent->m_pParent = pWalk;
    }
    // ===== M53: LAB_14000ad2c - the RB fix-up VERBATIM
    // colors: +0x1c (1 = needs the fix-up); sentinel @+0x30
    SSetNode* p10 = pPred;           // plVar10
    SSetNode* p11 = bTwo ? pPred : pL; // plVar11 entry
    SSetNode* p12 = pPar;            // plVar12 (parent)
    if (pIt->m_byColor == 1) {
        if (p12 != pSent->m_pNext) { // != *(sent+8)
            do {
                p10 = p11;
                if (p12->m_byColor != 1) break;
                p11 = p10->m_pPrev;              // *p10
                if (p12 == p11) {
                    // the left half VERBATIM:
                    p11 = p10->m_pParent;         // p10[2]
                    if (p11->m_byColor == 0) {
                        p11->m_byColor = 1;
                        p10->m_byColor = 0;
                        TreeRotateAtParent(pSet, p10);
                        p11 = p10->m_pParent;
                    }
                    if (p11->m_byFlag == 0) {
                        if (p11->m_pPrev->m_byColor != 1 ||
                            p11->m_pParent->m_byColor != 1) {
                            if (p11->m_pParent->m_byColor == 1) {
                                p11->m_pPrev->m_byColor = 1;
                                p11->m_byColor = 0;
                                TreeRotateAtParent(pSet, p11);
                                p11 = p10->m_pParent;
                            }
                            p11->m_byColor = p10->m_byColor;
                            p10->m_byColor = 1;
                            p11->m_pParent->m_byColor = 1;
                            TreeRotateAtParent(pSet, p10);
                            break;
                        }
                        p11->m_byColor = 0;
                    }
                } else {
                    // the right/mirror half VERBATIM:
                    if (p11->m_byColor == 0) {
                        p11->m_byColor = 1;
                        p10->m_byColor = 0;
                        TreeRotateMirror(pSet, p10);
                        p11 = p10->m_pPrev;       // *p10
                    }
                    if (p11->m_byFlag == 0) {
                        if (p11->m_pParent->m_byColor != 1 ||
                            p11->m_pPrev->m_byColor != 1) {
                            if (p11->m_pPrev->m_byColor == 1) {
                                p11->m_pParent->m_byColor = 1;
                                p11->m_byColor = 0;
                                TreeRotateAtParent(pSet, p11);
                                p11 = p10->m_pPrev;
                            }
                            p11->m_byColor = p10->m_byColor;
                            p10->m_byColor = 1;
                            p11->m_pPrev->m_byColor = 1;
                            TreeRotateMirror(pSet, p10);
                            break;
                        }
                        p11->m_byColor = 0;
                    }
                }
                p11 = p10->m_pNext;               // p10[1]
                p12 = p10;                         // climb
            } while (p10 != pSent->m_pNext);
        }
        p12->m_byColor = 1;      // final: root color VERBATIM
    }
    pSet->m_qCount--;               // [7]-1 VERBATIM
    delete pIt;
}

} // namespace msg

namespace msg {

// ===== M50: ORIGINAL FUN_140009ab0 @ 140009ab0 =====
// The ORIGINAL insert called it as:
//   FUN_140009ab0(set, set.inner, hint, set.inner, key, 0)
// i.e. left = sentinel, right = hint, parent = sentinel.
SSetNode* TreeNodeAlloc(SSetNode* pLeft, SSetNode* pRight,
                        SSetNode* pParent, uint32_t dwKey,
                        uint8_t byColor) {
    SSetNode* p = (SSetNode*)std::calloc(1, 0x20);
    if (p) {
        p->m_pPrev   = pLeft;     // +0
        p->m_pNext   = pRight;    // +8
        p->m_pParent = pParent;   // +0x10
        p->m_dwKey   = dwKey;     // +0x18
        p->m_byColor = byColor;   // +0x1c
        p->m_byFlag  = 0;         // +0x1d end-flag
    }
    return p;
}

// ===== M50: ORIGINAL FUN_1400075f0 @ 1400075f0 =====
// VERBATIM walk (the if(it[0]==0) empty branch is a
// Ghidra artifact, kept as a comment):
void IteratorPrev(SSetNode** ppNode) {
    SSetNode* pCur = *ppNode;
    if (pCur->m_byFlag /* +0x1d */)
        return;               // the sentinel: no walk
    SSetNode* pParent = pCur->m_pParent;        // +0x10
    if (pParent->m_byFlag /* +0x1d */) {
        // parent IS the sentinel: descend RIGHT while
        // (child non-sentinel && *ppNode == child->parent)
        SSetNode* pR = pCur->m_pNext;           // +8 right
        uint8_t byR = pR->m_byFlag;
        while (byR == 0 &&
               *ppNode == pR->m_pParent) {
            *ppNode = pR;
            pR = pR->m_pNext;
            byR = pR->m_byFlag;
        }
        *ppNode = pR;
        return;
    }
    // parent NOT sentinel: descend parent's LEFT to the
    // bottom (VERBATIM - direction kept as decompiled)
    SSetNode* pL = pParent->m_pPrev;            // parent's left
    SSetNode* pB = pL;
    while (pL->m_byFlag == 0) {
        pB = pL;
        pL = pL->m_pPrev;                      // descend left
    }
    *ppNode = pB;
}

} // namespace msg

namespace msg {

// ===== M52: ORIGINAL FUN_140008940 @ 140008940 =====
// VERBATIM line-by-line (fields: left=+0, right=+8,
// parent=+0x10, color=+0x1c, end=+0x1d; sentinel @+0x30):
void TreeRotateAtParent(SObjSet* pSet, SSetNode* p) {
    SSetNode* up = p->m_pParent;         // plVar1
    p->m_pParent = up->m_pPrev;          // *(p+0x10)=*up
    if (up->m_pPrev->m_byFlag == 0)
        up->m_pPrev->m_pNext = p;        // *(*up + 8) = p
    up->m_pNext = p->m_pNext;            // up[1] = p->right
    SSetNode* pSent = (SSetNode*)pSet->m_pInner;
    if (p == pSent->m_pNext) {           // p == *(sent+8)
        pSent->m_pNext = up;
        up->m_pPrev = p;                 // *up = p
        p->m_pNext = up;                 // *(p+8) = up
        return;
    }
    SSetNode* g = p->m_pNext;            // plVar2 = p->right
    if (p == g->m_pPrev) {
        g->m_pPrev = up;                 // *plVar2 = up
        up->m_pPrev = p;
        p->m_pNext = up;
        return;
    }
    g->m_pParent = up;                   // plVar2[2] = up
    up->m_pPrev = p;
    p->m_pNext = up;
}

// ===== M52: ORIGINAL FUN_1400089a0 @ 1400089a0 =====
void TreeRotateMirror(SObjSet* pSet, SSetNode* p) {
    SSetNode* up = p->m_pPrev;           // lVar1 = *p
    p->m_pPrev = up->m_pParent;         // *p = *(up+0x10)
    if (up->m_pParent->m_byFlag == 0)
        up->m_pParent->m_pNext = p;     // *(up+0x10)+8 = p
    up->m_pPrev = p->m_pNext;           // *(up+8) = p[1]
    SSetNode* pSent = (SSetNode*)pSet->m_pInner;
    if (p == pSent->m_pNext) {
        pSent->m_pNext = up;
        up->m_pParent = p;              // *(up+0x10) = p
        p->m_pNext = up;
        return;
    }
    SSetNode* g = p->m_pNext;
    if (p == g->m_pParent) {             // p == plVar2[2]
        g->m_pParent = up;
        up->m_pParent = p;
        p->m_pNext = up;
        return;
    }
    g->m_pPrev = up;                     // *plVar2 = up
    up->m_pParent = p;
    p->m_pNext = up;
}

} // namespace msg

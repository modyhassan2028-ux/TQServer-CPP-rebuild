#include "MsgMapGroupKernel.h"
#include <stdexcept>
#include <cstdlib>
#include <cstring>
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
        if (pHint == pSent->m_pParent) {
            // hint == RIGHTMOST (sent+0x10): fixup
            pSent->m_pParent = pNew;
        }
    } else {
        // link BEFORE the hint: *hint = node (ORIGINAL
        // else branch: if (hint == sent+0) sent+0 = node
        // - the LEFTMOST fixup, NOT the head slot)
        pHint->m_pPrev = pNew;
        if (pHint == pSent->m_pPrev) {
            pSent->m_pPrev = pNew;
        }
    }
    return pNew;
}

// ===== M49: ORIGINAL FUN_14000ab40 (erase) =====
SSetNode* SetErase(SObjSet* pSet, SSetNode* pIt) {
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
        // ===== M56: the VERBATIM single/leaf splice
        // (FUN_14000ab40 decompile 8628-8668) =====
        if (pPar->m_byFlag == 0)
            pPar->m_pNext = pR;   // plVar12[1] = plVar11
        if (pSent->m_pNext == pIt)
            pSent->m_pNext = pPar;   // head-child fixup
        else if (pR->m_pPrev == pIt)
            pR->m_pPrev = pPar;      // *plVar11
        else
            pR->m_pParent = pPar;    // plVar11[2]
        // leftmost fixup (sentinel +0 slot):
        if (pSent->m_pPrev == pIt) {
            SSetNode* pW = pR;       // plVar10 = plVar11
            if (pPar->m_byFlag == 0) {
                SSetNode* p9 = pPar;
                SSetNode* p6 = pPar->m_pPrev;
                while (p6->m_byFlag == 0) {
                    p9 = p6; p6 = p6->m_pPrev;
                }
                pW = p9;
            }
            pSent->m_pPrev = pW;
        }
        // rightmost fixup (sentinel +0x10 slot):
        if (pSent->m_pParent == pIt) {
            SSetNode* pW2 = pR;
            if (pPar->m_byFlag == 0) {
                SSetNode* p9 = pPar;
                SSetNode* p6 = pPar->m_pParent;
                while (p6->m_byFlag == 0) {
                    p9 = p6; p6 = p6->m_pParent;
                }
                pW2 = p9;
            }
            pSent->m_pParent = pW2;
        }
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
    // the ORIGINAL tail VERBATIM:
    // if (param_1[7] != 0) param_1[7] -= 1;
    if (pSet->m_qCount != 0)
        pSet->m_qCount--;
    delete pIt;                        // operator_delete(plVar5)
    // the return: uVar8 = *(param_3+8); ret[1] = uVar8
    // = the iterator node after the prev-walk (pPred)
    return pPred;
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

namespace msg {

// ===== M55: ORIGINAL FUN_14000d480 @ 14000d480 =====
SSetNode* SetInsertKeyed(SObjSet* pSet, uint32_t dwKey,
                         bool* pbExists) {
    SSetNode* pSent = (SSetNode*)pSet->m_pInner;
    SSetNode* pLeaf = pSent;
    bool bLess = true;
    // the walk VERBATIM: from inner->right (+8) while
    // non-sentinel: less -> +0, else -> +0x10
    if (pSent->m_pNext->m_byFlag == 0) {
        SSetNode* pCur = pSent->m_pNext;
        do {
            pLeaf = pCur;
            bLess = dwKey < pCur->m_dwKey;
            if (bLess)
                pCur = pCur->m_pPrev;       // *node (+0)
            else
                pCur = pCur->m_pParent;    // node[2](+0x10)
        } while (pCur->m_byFlag == 0);
    }
    if (!bLess) {
        // right path: duplicate check VERBATIM
        // (key <= leaf key -> exists, no insert)
        if (dwKey <= pLeaf->m_dwKey) {
            if (pbExists) *pbExists = true;
            return nullptr;    // ret flag 0 + head node
        }
    } else {
        // left path: the predecessor-equality check
        // (the ORIGINAL walks the left subtree's
        // rightmost via the parent chain - semantics
        // VERBATIM, the register dance simplified TBD)
        SSetNode* pLeft = pLeaf->m_pPrev;
        if (pLeft->m_byFlag == 0) {
            while (pLeft->m_pParent->m_byFlag == 0)
                pLeft = pLeft->m_pParent;   // rightmost
            if (dwKey <= pLeft->m_dwKey) {
                if (pbExists) *pbExists = true;
                return nullptr;
            }
        }
    }
    if (pbExists) *pbExists = false;
    // the insert call VERBATIM:
    // FUN_14000bfd0(set, &iter, bLess, hint, key) -
    // param_3 == bLess (0 -> the +0x10 RIGHT branch)
    return SetInsert(pSet, pLeaf, bLess, dwKey);
}

} // namespace msg

namespace msg {

// ===== M57: the prison-map list segment VERBATIM =====
SPrisonMaps::SPrisonMaps() {
    // the local sentinel (the 0x20 A-type node):
    std::memset(&m_inner, 0, sizeof m_inner);
    SSetNode* pSent = (SSetNode*)&m_inner;
    pSent->m_byFlag = 1;               // +0x1d raised
    pSent->m_pPrev = pSent; pSent->m_pNext = pSent;
    pSent->m_pParent = pSent;          // the 3 self-links
    m_set.m_pHead = nullptr;
    m_set.m_pInner = &m_inner;
    m_set.m_qCount = 0;
}

void SPrisonMaps::Build() {
    // the CLEAR walk VERBATIM (14470-14485): delete every
    // non-sentinel node front-to-back with the callback
    SSetNode* pSent = (SSetNode*)m_set.m_pInner;
    SSetNode* pCur = pSent->m_pNext;    // local_508[1]
    while (pCur->m_byFlag == 0) {
        if (m_fnOnClearNode)
            m_fnOnClearNode(pCur->m_dwKey);  // 1400098c0
        SSetNode* pNext = pCur->m_pPrev;    // *plVar13
        delete pCur;                        // operator_delete
        pCur = pNext;
    }
    pSent->m_pNext = pSent;     // re-self-link VERBATIM
    m_set.m_qCount = 0;
    pSent->m_pPrev = pSent;
    pSent->m_pParent = pSent;
    // the VERBATIM literal inserts:
    SetInsertKeyed(&m_set, 0x177a, nullptr);
    SetInsertKeyed(&m_set, 0x177b, nullptr);
    SetInsertKeyed(&m_set, 0x177e, nullptr);
    // the FUN_14008ac00 gate:
    if (m_fnGate && m_fnGate()) {
        SetInsertKeyed(&m_set, 0x177f, nullptr);
        SetInsertKeyed(&m_set, 0x1780, nullptr);
        SetInsertKeyed(&m_set, 0x1781, nullptr);
    }
}

bool SPrisonMaps::Has(uint32_t dwMapId) {
    // walk probe (for tests; mirrors the M55 walk)
    SSetNode* pSent = (SSetNode*)m_set.m_pInner;
    SSetNode* pCur = pSent->m_pNext;
    while (pCur->m_byFlag == 0) {
        if (pCur->m_dwKey == dwMapId) return true;
        pCur = dwMapId < pCur->m_dwKey ? pCur->m_pPrev
                                       : pCur->m_pParent;
    }
    return false;
}

} // namespace msg

namespace msg {

// ===== M58: ORIGINAL FUN_14000aff0 @ 14000aff0 =====
SSetNode* SetFind(SObjSet* pSet, uint32_t dwKey) {
    SSetNode* pSent = (SSetNode*)pSet->m_pInner;
    SSetNode* pCand = pSent;         // puVar4 (lower track)
    SSetNode* pLast = pSent;         // puVar5
    SSetNode* pCur  = pSent->m_pNext;  // root (sent+8)
    while (pCur->m_byFlag == 0) {
        if (pCur->m_dwKey < dwKey) {
            pCur = pCur->m_pParent;  // +0x10 RIGHT
        } else {
            if (pCand->m_byFlag != 0 &&
                dwKey < pCur->m_dwKey) {
                pCand = pCur;
            }
            pLast = pCur;
            pCur = pCur->m_pPrev;    // +0 LEFT
        }
    }
    // the exact-match resolution (cand/lower trackers):
    if (pLast->m_byFlag == 0 && pLast->m_dwKey == dwKey)
        return pLast;
    if (pCand->m_byFlag == 0 && pCand->m_dwKey == dwKey)
        return pCand;
    return nullptr;
}

// ===== M58: ORIGINAL FUN_14000d630 @ 14000d630 =====
uint32_t SetEraseKeyed(SObjSet* pSet, uint32_t dwKey) {
    uint32_t n = 0;
    SSetNode* p;
    while ((p = SetFind(pSet, dwKey)) != nullptr) {
        SetErase(pSet, p);
        n++;
    }
    return n;
}

// ===== M59: the percent-config block VERBATIM =====
uint32_t SPercentCfg::LoadPercentConfig(
        uint32_t dwId, uint32_t dwType,
        const char* szDescrib) {
    // local_578[0] = 0; memset(+1, 0, 0x30)
    uint32_t v[13] = {0};
    // sscanf VERBATIM (13 x "%u", gaps counted):
    int n = std::sscanf(szDescrib,
        "%u %u %u %u %u %u %u %u %u %u %u %u %u",
        &v[0], &v[1], &v[2], &v[3], &v[4], &v[5],
        &v[6], &v[7], &v[8], &v[9], &v[10], &v[11],
        &v[12]);
    // ORIGINAL gate: iVar9 - 1U < 0xd (n in 1..13)
    if ((uint32_t)(n - 1U) >= 0xdU)
        return 0;
    for (int i = 0; i < n; i++) {
        // the over-100 zeroing + the VERBATIM log:
        if (v[i] > 100) {
            v[i] = 0;
            char sz[128];
            std::snprintf(sz, sizeof sz,
                "table:cq_config ID[%u] Type[%u]"
                " precent config over 100!",
                dwId, dwType);
            m_vecErrs.push_back(sz);
        }
        // the dispatch: id 0x177a -> target +0xe0
        // (FUN_14000d860(param_1+0xe0,...)), else +0x128
        if (dwId == 0x177a) {
            if (m_fnSinkA) m_fnSinkA((uint32_t)i, v[i]);
        } else {
            if (m_fnSinkB) m_fnSinkB((uint32_t)i, v[i]);
        }
    }
    return (uint32_t)n;
}

// ===== M60: ORIGINAL FUN_140011280 @ 140011280 =====
uint32_t* MapOperatorAt(SObjMap* pMap, uint32_t dwKey) {
    SMapNode* pSent = (SMapNode*)pMap->m_pInner;
    SMapNode* pCand = pSent;              // puVar3
    // the VERBATIM walk (sentinel +8 = root):
    SMapNode* pCur = pSent->m_pParent;
    while (pCur->m_byFlag == 0) {
        if (pCur->m_dwKey < dwKey)
            pCur = pCur->m_pRight;        // puVar1[2]
        else {
            pCand = pCur;                 // lower-bound
            pCur = pCur->m_pLeft;         // *puVar1
        }
    }
    // the ORIGINAL exact check: candidate == sentinel
    // || key < candidate->key -> MISS
    if (pCand == pSent || dwKey < pCand->m_dwKey) {
        // default record VERBATIM: local_c0 =
        // {key, 0,0,0,0,0,0}
        SMapNode* pNew = new SMapNode();
        pNew->m_dwKey = dwKey;
        // (the two local container ctors + the copy
        // FUN_14000e970/cleanup FUN_14000c310 = the
        // record sub-set - seam: zero-initialized here)
        // the new node's NIL links (the ORIGINAL
        // allocator FUN_140010280 gives NIL/parent/NIL):
        pNew->m_pLeft = pNew->m_pRight = pSent;
        pNew->m_pParent = pSent;
        // ===== M61: the FUN_140010ec0 head branches
        // VERBATIM =====
        SMapNode* pLeftM = pSent->m_pLeft;   // *(sent+0)
        SMapNode* pRightM = pSent->m_pRight; // sent+0x10
        if (pMap->m_qCount == 0) {
            // ORIGINAL: count==0 -> 600(map, ret, 1,
            // SENTINEL, key) - the root branch
            MapInsertLink(pMap, pSent, true, pNew);
        } else if (pCand == pLeftM &&
                   dwKey < pLeftM->m_dwKey) {
            // ORIGINAL ec0: if (pCand == leftmost &&
            // key < leftmost->key) -> 600(1, leftmost)
            MapInsertLink(pMap, pLeftM, true, pNew);
        } else if (pCand == pSent &&
                   pRightM->m_dwKey < dwKey) {
            // ORIGINAL ec0 else: if (pCand == SENTINEL &&
            // rightmost->key < key) -> 600(0, rightmost)
            MapInsertLink(pMap, pRightM, false, pNew);
        } else {
            // the ec0 INTERIOR hint-validation walk is
            // TBD; provisional route: link left/right of
            // the lower-bound candidate
            MapInsertLink(pMap, pCand,
                          dwKey < pCand->m_dwKey, pNew);
        }
        return &pNew->m_aRecord[0];   // node + 0x1c
    }
    // HIT: return node + 0x1c
    return &pCand->m_aRecord[0];
}

// ===== M61: ORIGINAL FUN_140010600 @ 140010600
// (the link core) =====
void MapInsertLink(SObjMap* pMap, SMapNode* pHint,
                   bool bAfter, SMapNode* pNew) {
    SMapNode* pSent = (SMapNode*)pMap->m_pInner;
    // the VERBATIM max_size gate:
    // 0x2c8590b21642c83 -> length_error
    // ("map/set<T> too long") - unreachable in practice
    if ((uint64_t)pMap->m_qCount >
            0x02c8590b21642c83ULL) {
        throw std::length_error("map/set<T> too long");
    }
    // (the node alloc FUN_140010280 + record copy =
    // the caller already built pNew - TBD note)
    pMap->m_qCount++;            // param_1[7] += 1
    // the VERBATIM link branches:
    if (pHint == pSent) {
        pSent->m_pParent = pNew;     // sent+8 (root)
        pSent->m_pLeft  = pNew;      // sent+0 (leftmost)
        pSent->m_pRight = pNew;      // sent+0x10 (right)
    } else if (!bAfter) {
        pHint->m_pRight = pNew;      // param_4[2]
        if (pHint == pSent->m_pRight)
            pSent->m_pRight = pNew;  // rightmost fixup
    } else {
        pHint->m_pLeft = pNew;       // *param_4
        if (pHint == pSent->m_pLeft)
            pSent->m_pLeft = pNew;   // leftmost fixup
    }
    // the ORIGINAL RB-fixup walk (the +0x74 flag chain
    // with rotations) - TBD: the set rotations are at
    // +0x1d; the map node variant is not yet ported
}

} // namespace msg

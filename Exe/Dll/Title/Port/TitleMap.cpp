#include "TitleMap.h"
#include "TitleModule.h"   // g_fnAlloc / g_fnFree
#include <cstring>

namespace title {

// the kernel base = mgr+0x08 (this == &mgr.m_pProxy08)
// node: +0x00 left, +0x08 PARENT, +0x10 right,
//       +0x18 key, +0x20 value, +0x28 color, +0x29 isnil

// ============ FUN_141974090: the proxy node ============
void SMapKernel::MakeProxyNode() {
    void** ppNode = (void**)g_fnAlloc(8);
    if (ppNode == nullptr) { }
    else { *ppNode = this; }
    m_pProxy08 = ppNode;
}

// ============ FUN_141972cf0-model head + 141974580 ============
// the map ctor: proxy node + head (isnil=1, circular) +
// size 0. (The head's +0x29 is set to 1 by the ctor AFTER
// the 141972cf0 model zeroed it — verbatim order.)
void SMapKernel::Ctor() {
    MakeProxyNode();
    STreeNode* pHead = NewNode();
    pHead->m_pLeft00 = pHead;
    pHead->m_pParent08 = pHead;
    pHead->m_pRight10 = pHead;
    pHead->m_bIsnil29 = 1;
    // VERBATIM 141972cf0: the head's +0x28 flag = 1
    // (the NIL sentinel must read BLACK in the fixups)
    pHead->m_bColor28 = 1;
    m_pHead38 = pHead;
    m_nSize40 = 0;
}

// ============ FUN_141974550 (via 141974360): dtor ============
void SMapKernel::FullDtor() {
    Dtor();                       // clear + free the head
    g_fnFree(m_pProxy08);          // the proxy delete
    m_pProxy08 = nullptr;
}

// ============ FUN_141973ad0: lower_bound ============
STreeNode* SMapKernel::LowerBound(uint32_t uKey) {
    STreeNode* pLast = m_pHead38;
    STreeNode* pCur = m_pHead38->m_pParent08;
    while (pCur != nullptr && !pCur->m_bIsnil29) {
        STreeNode* pNext;
        if (pCur->m_nKey18 < (int32_t)uKey) {
            pNext = pCur->m_pRight10;
        } else {
            pNext = pCur->m_pLeft00;
            pLast = pCur;
        }
        pCur = pNext;
    }
    return pLast;
}

// ============ FUN_141974260: find (exact) ============
STreeNode* SMapKernel::FindNode(uint32_t uKey) {
    STreeNode* pLast = LowerBound(uKey);
    if (pLast == m_pHead38 || uKey < (uint32_t)pLast->m_nKey18)
        return nullptr;
    return pLast;
}

// ============ FUN_141972330: rotate RIGHT ============
void SMapKernel::InsertFixup(STreeNode* pP, STreeNode* pN) {
    STreeNode* pS = pN->m_pRight10;
    pP->m_pLeft00 = pS;
    if (!pS->m_bIsnil29) pS->m_pParent08 = pP;
    pN->m_pParent08 = pP->m_pParent08;
    STreeNode* pG = pN->m_pParent08;
    if (pP == m_pHead38->m_pParent08) {
        m_pHead38->m_pParent08 = pN;
    } else if (pP == pG->m_pRight10) {
        pG->m_pRight10 = pN;
    } else {
        pG->m_pLeft00 = pN;
    }
    pN->m_pRight10 = pP;
    pP->m_pParent08 = pN;
}

// ============ FUN_141972930: rotate LEFT ============
void SMapKernel::EraseFixup(STreeNode* pP, STreeNode* pN) {
    STreeNode* pS = pN->m_pLeft00;
    pP->m_pRight10 = pS;
    if (!pS->m_bIsnil29) pS->m_pParent08 = pP;
    pN->m_pParent08 = pP->m_pParent08;
    STreeNode* pG = pN->m_pParent08;
    if (pP == m_pHead38->m_pParent08) {
        m_pHead38->m_pParent08 = pN;
    } else if (pP == pG->m_pLeft00) {
        pG->m_pLeft00 = pN;
    } else {
        pG->m_pRight10 = pN;
    }
    pN->m_pLeft00 = pP;
    pP->m_pParent08 = pN;
}

// ============ FUN_141972ae0/141972d50: node make ============
STreeNode* SMapKernel::NewNode() {
    STreeNode* p = (STreeNode*)g_fnAlloc(sizeof(STreeNode));
    if (p) { std::memset(p, 0, sizeof(*p)); p->m_bIsnil29 = 0; }
    return p;
}
// FUN_141972d50: new(0x30); left=head, parent=pParent,
// right=head, key, value, color; isnil=0
STreeNode* SMapKernel::MakeNode(STreeNode* pParent,
                                uint32_t uKey, void* pValue,
                                uint8_t uColor) {
    STreeNode* p = NewNode();
    if (p) {
        p->m_pLeft00 = m_pHead38;      // *puVar1 = param_2
        p->m_pParent08 = pParent;     // puVar1[1] = param_3
        p->m_pRight10 = m_pHead38;    // puVar1[2] = param_4
        p->m_nKey18 = (int32_t)uKey;   // puVar1[3] = key
        p->m_pValue20 = pValue;       // puVar1[4] = value
        p->m_bColor28 = uColor;
    }
    return p;
}

// ============ FUN_141972f30: the RB insert ============
// (the literal "map/set<T> too long" gate: the ORIGINAL
//  throws at size >= 0xffffffffffffffd — unreachable
//  physically; documented, not thrown in the port)
// NOTE: the original's fixup rotations are compiler-
// INLINED copies of 141972330/141972930 — the port
// calls the ported rotations (identical sequences).
STreeNode* SMapKernel::InsertRB(STreeNode* pHint, bool bAddLeft,
                                uint32_t uKey, void* pValue) {
    // FUN_141972d50(map, head, hint, head, value, 0=red)
    STreeNode* pN = MakeNode(pHint, uKey, pValue, 0);
    if (pN == nullptr) return nullptr;
    m_nSize40 = m_nSize40 + 1;           // param_1[7] += 1
    // link:
    if (pHint == m_pHead38) {            // the empty tree
        m_pHead38->m_pParent08 = pN;
        m_pHead38->m_pLeft00 = pN;
        m_pHead38->m_pRight10 = pN;
    } else if (!bAddLeft) {              // the hint's right
        pHint->m_pRight10 = pN;
        if (pHint == m_pHead38->m_pRight10)
            m_pHead38->m_pRight10 = pN; // Rmost
    } else {                             // the hint's left
        pHint->m_pLeft00 = pN;
        if (pHint == m_pHead38->m_pLeft00)
            m_pHead38->m_pLeft00 = pN;   // Lmost
    }
    // the RB insert fixup: while the parent is RED
    STreeNode* p = pN;
    while (p != m_pHead38->m_pParent08
           && !p->m_pParent08->m_bIsnil29
           && p->m_pParent08->m_bColor28 == 0) {
        STreeNode* pParent = p->m_pParent08;
        STreeNode* pG = pParent->m_pParent08;
        if (pParent == pG->m_pLeft00) {  // parent is a LEFT
            STreeNode* pUncle = pG->m_pRight10;
            if (pUncle->m_bColor28 == 0) {
                // uncle red: recolor + move up
                pParent->m_bColor28 = 1;
                pUncle->m_bColor28 = 1;
                pG->m_bColor28 = 0;
                p = pG;
            } else {
                if (p == pParent->m_pRight10) {
                    // LR: rotate the parent LEFT first
                    // (the inlined 141972930 sequence)
                    EraseFixup(pParent, p);
                    p = pParent;
                }
                p->m_pParent08->m_bColor28 = 1;
                p->m_pParent08->m_pParent08->m_bColor28 = 0;
                // rotate the grandparent RIGHT (the inlined
                // 141972330 sequence)
                InsertFixup(
                    p->m_pParent08->m_pParent08,
                    p->m_pParent08);
                break;   // done per the original's loop exit
            }
        } else {                          // parent is a RIGHT
            STreeNode* pUncle = pG->m_pLeft00;
            if (pUncle->m_bColor28 == 0) {
                pParent->m_bColor28 = 1;
                pUncle->m_bColor28 = 1;
                pG->m_bColor28 = 0;
                p = pG;
            } else {
                if (p == pParent->m_pLeft00) {
                    // RL: rotate the parent RIGHT first
                    InsertFixup(pParent, p);
                    p = pParent;
                }
                p->m_pParent08->m_bColor28 = 1;
                p->m_pParent08->m_pParent08->m_bColor28 = 0;
                EraseFixup(
                    p->m_pParent08->m_pParent08,
                    p->m_pParent08);
                break;
            }
        }
    }
    // ORIGINAL: blacken the root
    m_pHead38->m_pParent08->m_bColor28 = 1;
    return pN;
}

// ============ FUN_141974260: operator-at ============
// lower_bound; if missing insert under the found parent;
// returns &node->m_pValue20 (the ORIGINAL: puVar4 + 4)
void** SMapKernel::OperatorAt(uint32_t uKey) {
    STreeNode* pWhere = LowerBound(uKey);
    if (pWhere == m_pHead38 || uKey < (uint32_t)pWhere->m_nKey18) {
        bool bAddLeft;
        STreeNode* pHint;
        if (pWhere == m_pHead38) {
            // empty tree / beyond Rmost: the head's right
            bAddLeft = false;
            pHint = m_pHead38->m_pRight10;
            // (the ORIGINAL inserts at Lmost when empty)
            if (m_pHead38->m_pParent08 == m_pHead38) {
                bAddLeft = true;
                pHint = m_pHead38;
            }
        } else {
            // the ORIGINAL's hint logic (141973bc0):
            // left of the successor if its left is empty,
            // else right of the PREDECESSOR
            if (pWhere->m_pLeft00 == m_pHead38) {
                bAddLeft = true;
                pHint = pWhere;
            } else {
                // the predecessor = the rightmost node of
                // the successor's left subtree
                STreeNode* pPred = pWhere->m_pLeft00;
                while (pPred->m_pRight10 != m_pHead38)
                    pPred = pPred->m_pRight10;
                bAddLeft = false;
                pHint = pPred;
            }
        }
        InsertRB(pHint, bAddLeft, uKey, nullptr);
        pWhere = LowerBound(uKey);   // refetch
    }
    return &pWhere->m_pValue20;
}

// ============ FUN_1419736b0: erase with rebalance ============
void SMapKernel::EraseNode(STreeNode* pX) {
    // splice: promote the single child (pY) into pX's slot
    STreeNode* pY =
        (pX->m_pLeft00->m_bIsnil29) ? pX->m_pRight10
                                    : pX->m_pLeft00;
    STreeNode* pP = pX->m_pParent08;
    if (!pY->m_bIsnil29) pY->m_pParent08 = pP;
    if (pP == m_pHead38) {
        // X was the root
        m_pHead38->m_pParent08 = pY;
    } else if (pX == pP->m_pLeft00) {
        pP->m_pLeft00 = pY;
    } else {
        pP->m_pRight10 = pY;
    }
    // Lmost / Rmost updates
    if (m_pHead38->m_pLeft00 == pX) {
        STreeNode* q = pP;
        if (!pY->m_bIsnil29) {
            q = pY;
            while (!q->m_pLeft00->m_bIsnil29) q = q->m_pLeft00;
        }
        m_pHead38->m_pLeft00 = q;
    }
    if (m_pHead38->m_pRight10 == pX) {
        STreeNode* q = pP;
        if (!pY->m_bIsnil29) {
            q = pY;
            while (!q->m_pRight10->m_bIsnil29) q = q->m_pRight10;
        }
        m_pHead38->m_pRight10 = q;
    }
    // the RB delete-rebalance. The ORIGINAL loops
    // while the node != ROOT (head+0x08) and is BLACK,
    // and skips entirely when the spliced child IS root
    if (pX->m_bColor28 == 1
        && pY != m_pHead38->m_pParent08) {
        STreeNode* pRoot = m_pHead38->m_pParent08;
        STreeNode* pN = pY;             // the current node
        STreeNode* pPar = pP;
        while (pN != pRoot && pN->m_bColor28 == 1) {
            STreeNode* pSib;
            if (pN == pPar->m_pLeft00) {
                pSib = pPar->m_pRight10;
                if (pSib->m_bColor28 == 0) {
                    // red sibling: recolor + rotate LEFT
                    pSib->m_bColor28 = 1;
                    pPar->m_bColor28 = 0;
                    EraseFixup(pPar, pSib);   // rotate left
                    pSib = pPar->m_pRight10;
                }
                if (pSib->m_pLeft00->m_bColor28 != 1
                    || pSib->m_pRight10->m_bColor28 != 1) {
                    if (pSib->m_pRight10->m_bColor28 == 1) {
                        // the far nephew is black: rotate
                        // the sibling RIGHT first
                        pSib->m_pLeft00->m_bColor28 = 1;
                        pSib->m_bColor28 = 0;
                        InsertFixup(pSib, pSib->m_pLeft00);
                        pSib = pPar->m_pRight10;
                    }
                    pSib->m_bColor28 = pPar->m_bColor28;
                    pPar->m_bColor28 = 1;
                    pSib->m_pRight10->m_bColor28 = 1;
                    EraseFixup(pPar, pSib);   // rotate left
                    break;   // done (the ORIGINAL's exit)
                }
                pSib->m_bColor28 = 0;   // both nephews black
            } else {                     // the mirrored side
                pSib = pPar->m_pLeft00;
                if (pSib->m_bColor28 == 0) {
                    pSib->m_bColor28 = 1;
                    pPar->m_bColor28 = 0;
                    InsertFixup(pPar, pSib); // rotate right
                    pSib = pPar->m_pLeft00;
                }
                if (pSib->m_pLeft00->m_bColor28 != 1
                    || pSib->m_pRight10->m_bColor28 != 1) {
                    if (pSib->m_pLeft00->m_bColor28 == 1) {
                        pSib->m_pRight10->m_bColor28 = 1;
                        pSib->m_bColor28 = 0;
                        EraseFixup(pSib, pSib->m_pRight10);
                        pSib = pPar->m_pLeft00;
                    }
                    pSib->m_bColor28 = pPar->m_bColor28;
                    pPar->m_bColor28 = 1;
                    pSib->m_pLeft00->m_bColor28 = 1;
                    InsertFixup(pPar, pSib); // rotate right
                    break;
                }
                pSib->m_bColor28 = 0;
            }
            pN = pPar;                    // move up
            pPar = pN->m_pParent08;
        }
        // ORIGINAL: *(byte*)(plVar9 + 0x28) = 1 — blacken
        // the spliced child when the loop ends
        pY->m_bColor28 = 1;
    }
    g_fnFree(pX);                          // operator_delete
    m_nSize40 = m_nSize40 - 1;
}

// ============ FUN_141972c50: subtree destroy ============
static void SubtreeDestroy(STreeNode* p) {
    while (p != nullptr && !p->m_bIsnil29) {
        SubtreeDestroy(p->m_pRight10);
        STreeNode* pNext = p->m_pLeft00;
        g_fnFree(p);
        p = pNext;
    }
}

// ============ FUN_141972e10: clear ============
void SMapKernel::Clear() {
    STreeNode* p = m_pHead38->m_pParent08;
    while (p != nullptr && !p->m_bIsnil29) {
        SubtreeDestroy(p->m_pRight10);
        STreeNode* pNext = p->m_pLeft00;
        g_fnFree(p);
        p = pNext;
    }
    m_pHead38->m_pParent08 = m_pHead38;
    m_nSize40 = 0;
    m_pHead38->m_pLeft00 = m_pHead38;
    m_pHead38->m_pRight10 = m_pHead38;
}

// ============ FUN_141974360: the map dtor ============
void SMapKernel::Dtor() {
    Clear();
    g_fnFree(m_pHead38);
    m_pHead38 = nullptr;
    m_nSize40 = 0;
}

} // namespace

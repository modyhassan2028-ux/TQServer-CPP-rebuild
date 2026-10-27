// ============================================================
// Training.dll port — the std::map machinery. VERBATIM from
// the Ghidra listing. All node/link operations preserved.
// ============================================================
#include "TrainingMap.h"
#include <cstdlib>

namespace training {

void (*g_fnInvalidParameter)() = abort;

// ============ FUN_1419e2100: iterator ++ ============
void IteratorNext(SMapIterator* pIt) {
    if (pIt->m_pProxy00 == nullptr) {
        // *param_1 == 0 gate (the ORIGINAL's handler
        // never returns; the seam models that)
        g_fnInvalidParameter();
        return;
    }
    STreeNode* pN = pIt->m_pNode08;
    if (pN->m_bIsnil31 == 0) {
        // the right subtree's minimum
        STreeNode* pR = pN->m_pRight10;
        if (pR->m_bIsnil31 != 0) {
            // climb while the node is the parent's RIGHT
            STreeNode* pPar = pN->m_pParent08;
            uint8_t isnil = pPar->m_bIsnil31;
            while (isnil == 0
                   && (STreeNode*)pIt->m_pNode08
                          == pPar->m_pRight10) {
                pIt->m_pNode08 = pPar;
                pPar = pIt->m_pNode08->m_pParent08;
                isnil = pPar->m_bIsnil31;
            }
            pIt->m_pNode08 = pPar;   // the head stops it
            return;
        }
        // the leftmost of the right subtree
        STreeNode* pL = pR->m_pLeft00;
        uint8_t isnil = pL->m_bIsnil31;
        while (isnil == 0) {
            isnil = pL->m_pLeft00->m_bIsnil31;
            pR = pL;
            pL = pL->m_pLeft00;
        }
        pIt->m_pNode08 = pR;
        return;
    }
    // at the end (the head): the ORIGINAL's unrecovered
    // jumptable -> _invalid_parameter_noinfo
    g_fnInvalidParameter();
    return;
}

// ============ FUN_1419e2ac0: the node make ============
STreeNode* MakeNode(STreeNode* pHead, STreeNode* pPar,
                   const SValRec* pRec, uint8_t uColor) {
    STreeNode* p = (STreeNode*)g_fnAlloc(
        sizeof(STreeNode));
    if (p != nullptr) {
        p->m_pLeft00 = pHead;        // *puVar1 = param_2
        p->m_pParent08 = pPar;       // puVar1[1] = param_3
        p->m_pRight10 = pHead;       // puVar1[2] = param_4
        p->m_nKey18 = pRec->m_nKey;  // puVar1[3] = *param_5
        p->m_pValue20 = pRec->m_pVal;// puVar1[4] = param_5[1]
        p->m_nVal28 = pRec->m_nVal2; // puVar1[5] = param_5[2]
        p->m_bColor30 = uColor;      // puVar1[6] = param_6
        p->m_bIsnil31 = 0;
    }
    return p;
}

// ============ FUN_1419e3320: the head (re)creation ============
void InitMapHead(SMapKernel* pKern) {
    STreeNode* pHead = NewHeadNode();
    pKern->m_pHead30 = pHead;
    pHead->m_bIsnil31 = 1;           // +0x31 = 1
    pHead->m_pParent08 = pKern->m_pHead30;
    pHead->m_pLeft00 = pKern->m_pHead30;
    pHead->m_pRight10 = pKern->m_pHead30;
    pKern->m_nSize38 = 0;
}

// ============ FUN_1419e2000: rotate RIGHT (left rises) ============
void RotateRight(SMapKernel* pKern, STreeNode* pP) {
    // lVar1 = *param_2 (the LEFT child)
    STreeNode* pL = pP->m_pLeft00;
    // *param_2 = left->right
    pP->m_pLeft00 = pL->m_pRight10;
    if (pL->m_pRight10->m_bIsnil31 == 0) {
        pL->m_pRight10->m_pParent08 = pP;
    }
    // left->parent = pP->parent
    pL->m_pParent08 = pP->m_pParent08;
    if (pP == pKern->m_pHead30->m_pParent08) {   // the root
        pKern->m_pHead30->m_pParent08 = pL;
        pL->m_pRight10 = pP;
        pP->m_pParent08 = pL;
        return;
    }
    STreeNode* pPar = pP->m_pParent08;
    if (pP == pPar->m_pRight10) {
        pPar->m_pRight10 = pL;
        pL->m_pRight10 = pP;
        pP->m_pParent08 = pL;
        return;
    }
    pPar->m_pLeft00 = pL;           // *plVar2 = lVar1
    pL->m_pRight10 = pP;
    pP->m_pParent08 = pL;
}

// ============ FUN_1419e26a0: rotate LEFT (right rises) ============
void RotateLeft(SMapKernel* pKern, STreeNode* pP) {
    // plVar1 = param_2->RIGHT
    STreeNode* pR = pP->m_pRight10;
    pP->m_pRight10 = pR->m_pLeft00;
    if (pR->m_pLeft00->m_bIsnil31 == 0) {
        pR->m_pLeft00->m_pParent08 = pP;
    }
    pR->m_pParent08 = pP->m_pParent08;
    if (pP == pKern->m_pHead30->m_pParent08) {   // the root
        pKern->m_pHead30->m_pParent08 = pR;
        pR->m_pLeft00 = pP;
        pP->m_pParent08 = pR;
        return;
    }
    STreeNode* pPar = pP->m_pParent08;
    if (pP == pPar->m_pLeft00) {     // plVar2[2] = plVar1
        pPar->m_pLeft00 = pR;
        pR->m_pLeft00 = pP;
        pP->m_pParent08 = pR;
        return;
    }
    pPar->m_pRight10 = pR;
    pR->m_pLeft00 = pP;
    pP->m_pParent08 = pR;
}

// ============ FUN_1419e3240: lower_bound ============
void LowerBound(SMapKernel* pKern, SMapIterator* pOut,
                uint32_t uKey) {
    STreeNode* pFound = pKern->m_pHead30;   // puVar4
    STreeNode* pLoc = pKern->m_pHead30;     // puVar5
    // phase 1: the down-walk from the root
    if (pKern->m_pHead30->m_pParent08->m_bIsnil31 == 0) {
        STreeNode* pN = pKern->m_pHead30->m_pParent08;
        STreeNode* pNext;
        do {
            if ((uint32_t)pN->m_nKey18 < uKey) {
                pNext = pN->m_pRight10;    // puVar3
            } else {
                // the FIRST candidate only (pFound still
                // the head/isnil): puVar4 = puVar2
                if (pFound->m_bIsnil31 != 0
                        && uKey < (uint32_t)pN->m_nKey18) {
                    pFound = pN;
                }
                pNext = pN->m_pLeft00;
                pLoc = pN;
            }
            pN = pNext;
        } while (pNext->m_bIsnil31 == 0);
    }
    // the found-node selection
    STreeNode* pRes;
    if (pFound->m_bIsnil31 == 0) {
        pRes = pFound;
    } else {
        pRes = pKern->m_pHead30->m_pParent08;
    }
    // phase 2: the verbatim second descent (updates the
    // candidate puVar4 ONLY; puVar5 untouched)
    STreeNode* pWalk = pRes;
    if (pRes->m_bIsnil31 == 0) {
        do {
            if (uKey < (uint32_t)pWalk->m_nKey18) {
                pFound = pWalk;       // puVar4 = puVar2
                pWalk = pWalk->m_pLeft00;
            } else {
                pWalk = pWalk->m_pRight10;
            }
        } while (pWalk->m_bIsnil31 == 0);
    }
    // out: {proxy, pLoc, proxy, pFound}
    pOut->m_pProxy00 = pKern->m_pProxy00;
    pOut->m_pNode08 = pLoc;
    pOut->m_pProxy10 = pKern->m_pProxy00;
    pOut->m_pParent18 = pFound;
}

// ============ FUN_1419e3360: insert ============
void InsertNode(SMapKernel* pKern, SMapIterator* pOut,
               bool bAddLeft, STreeNode* pPar,
               const SValRec* pRec) {
    // the length gate (size > 0xaaaaaaaaaaaaaa8):
    // "map/set<T> too long" length_error throw — CRT,
    // out of scope; documented
    // 1419e2ac0(map, head, par, head, rec, 0=RED)
    STreeNode* pN = MakeNode(pKern->m_pHead30, pPar,
                             pRec, 0);
    if (pN == nullptr) {
        // operator_new failed: the ORIGINAL returns the
        // unmodified out iterator
        pOut->m_pProxy00 = pKern->m_pProxy00;
        return;
    }
    pKern->m_nSize38 = pKern->m_nSize38 + 1;
    // the attach
    if (pPar == pKern->m_pHead30) {
        // the empty tree: the new node is the root
        pKern->m_pHead30->m_pParent08 = pN;
        pKern->m_pHead30->m_pLeft00 = pN;
        pKern->m_pHead30->m_pRight10 = pN;
    } else if (!bAddLeft) {
        // the parent's RIGHT
        pPar->m_pRight10 = pN;
        if (pPar == pKern->m_pHead30->m_pRight10)
            pKern->m_pHead30->m_pRight10 = pN;
    } else {
        // the parent's LEFT
        pPar->m_pLeft00 = pN;
        if (pPar == pKern->m_pHead30->m_pLeft00)
            pKern->m_pHead30->m_pLeft00 = pN;
    }
    // ---- the INLINE RB fixup (compiler-inlined in the
    // ORIGINAL; the rotations use the ported 1419e26a0 /
    // 1419e2000 — identical code sequences) ----
    STreeNode* pPar2 = pN->m_pParent08;    // plVar7 = pN+1
    STreeNode* pX = pN;                    // plVar6
    while (pPar2->m_bColor30 == 0) {       // the RED parent
        STreeNode* pGp = pPar2->m_pParent08;
        if (pPar2 == pGp->m_pLeft00) {
            // the parent is the grandparent's LEFT
            STreeNode* pU = pGp->m_pRight10;   // lVar4
            if (pU->m_bColor30 == 0) {
                // recolor and climb
                pPar2->m_bColor30 = 1;
                pU->m_bColor30 = 1;
                pGp->m_bColor30 = 0;
                pX = pGp;
            } else {
                // the inner (LR) case: _Pnode = the parent,
                // rotate-left about it (1419e26a0 inlined),
                // then the parent's NEW parent (the lifted
                // node) gets black, the GP red,
                // rotate-right about the GP
                if (pX == pPar2->m_pRight10) {
                    pX = pPar2;
                    RotateLeft(pKern, pX);
                }
                pX->m_pParent08->m_bColor30 = 1;
                pX->m_pParent08->m_pParent08->m_bColor30
                    = 0;
                RotateRight(pKern,
                    pX->m_pParent08->m_pParent08);
                break;
            }
        } else {
            // the parent is the grandparent's RIGHT
            STreeNode* pU = pGp->m_pLeft00;
            if (pU->m_bColor30 == 0) {
                pPar2->m_bColor30 = 1;
                pU->m_bColor30 = 1;
                pGp->m_bColor30 = 0;
                pX = pGp;
            } else {
                // the inner (RL) case: mirrored
                if (pX == pPar2->m_pLeft00) {
                    pX = pPar2;
                    RotateRight(pKern, pX);
                }
                pX->m_pParent08->m_bColor30 = 1;
                pX->m_pParent08->m_pParent08->m_bColor30
                    = 0;
                RotateLeft(pKern,
                    pX->m_pParent08->m_pParent08);
                break;
            }
        }
        pPar2 = pX->m_pParent08;
    }
    // the root black
    pKern->m_pHead30->m_pParent08->m_bColor30 = 1;
    // out: {proxy, node}
    pOut->m_pProxy00 = pKern->m_pProxy00;
    pOut->m_pNode08 = pN;
}

// ============ FUN_1419e2d50: erase at the iterator ============
void EraseAt(SMapKernel* pKern, SMapIterator* pOut,
             SMapIterator* pWhere) {
    STreeNode* pN = pWhere->m_pNode08;
    if (pN->m_bIsnil31 != 0) {
        // "invalid map/set<T> iterator" out_of_range
        // throw — CRT, out of scope; the ORIGINAL throws
        // (never returns); the seam models that
        g_fnInvalidParameter();
        return;
    }
    // ++where (the successor becomes where->node)
    IteratorNext(pWhere);
    STreeNode* pLeft = pN->m_pLeft00;      // plVar8
    STreeNode* pFix;                       // plVar9
    STreeNode* pFixPar = nullptr;   // plVar8 at LAB_2f3c:
    // the splice path = the successor; the attach path =
    // the erased node's parent (NOT pFix->parent: when
    // pFix = the head/nil its parent is the ROOT)
    if (pLeft->m_bIsnil31 == 0) {
        pFix = pLeft;
        if (pN->m_pRight10->m_bIsnil31 == 0) {
            // two children: splice the successor up
            STreeNode* pS = pWhere->m_pNode08;
            pFix = pS->m_pRight10;
            if (pS != pN) {
                pLeft->m_pParent08 = pS;
                pS->m_pLeft00 = pLeft;
                if (pS != pN->m_pRight10) {
                    STreeNode* pSP = pS->m_pParent08;
                    if (pFix->m_bIsnil31 == 0)
                        pFix->m_pParent08 = pSP;
                    pSP->m_pLeft00 = pFix;
                    pS->m_pRight10 = pN->m_pRight10;
                    pN->m_pRight10->m_pParent08 = pS;
                }
            }
            // replace pN with pS at the parent
            if (pKern->m_pHead30->m_pParent08 == pN)
                pKern->m_pHead30->m_pParent08 = pS;
            else if (pN->m_pParent08->m_pLeft00 == pN)
                pN->m_pParent08->m_pLeft00 = pS;
            else
                pN->m_pParent08->m_pRight10 = pS;
            pS->m_pParent08 = pN->m_pParent08;
            // swap the colors (+0x30)
            uint8_t c = pS->m_bColor30;
            pS->m_bColor30 = pN->m_bColor30;
            pN->m_bColor30 = c;
            pFixPar = pS;        // plVar8 = the successor
            goto rebalance;   // (LAB_1419e2f3c)
        }
    } else {
        pFix = pN->m_pRight10;
    }
    {   // the one/zero-child attach
        STreeNode* pPar = pN->m_pParent08;   // plVar8
        pFixPar = pPar;   // plVar8 carried to LAB_2f3c
        if (pFix->m_bIsnil31 == 0)
            pFix->m_pParent08 = pPar;
        if (pKern->m_pHead30->m_pParent08 == pN)
            pKern->m_pHead30->m_pParent08 = pFix;
        else if (pPar->m_pLeft00 == pN)
            pPar->m_pLeft00 = pFix;
        else
            pPar->m_pRight10 = pFix;
        // the Lmost/Rmost maintenance
        if (pKern->m_pHead30->m_pLeft00 == pN) {
            // plVar7 = par; if !pFix->isnil: plVar7 =
            // pFix THEN descend the LEFT
            STreeNode* pL = pPar;
            if (pFix->m_bIsnil31 == 0) {
                pL = pFix;
                STreeNode* pCur = pFix->m_pLeft00;
                while (pCur->m_bIsnil31 == 0) {
                    pL = pCur;
                    pCur = pCur->m_pLeft00;
                }
            }
            pKern->m_pHead30->m_pLeft00 = pL;
        }
        if (pKern->m_pHead30->m_pRight10 == pN) {
            // mirrored: pR = par; if !pFix->isnil: pR =
            // pFix THEN descend the RIGHT
            STreeNode* pR = pPar;
            if (pFix->m_bIsnil31 == 0) {
                pR = pFix;
                STreeNode* pCur = pFix->m_pRight10;
                while (pCur->m_bIsnil31 == 0) {
                    pR = pCur;
                    pCur = pCur->m_pRight10;
                }
            }
            pKern->m_pHead30->m_pRight10 = pR;
        }
    }
rebalance:
    if (pN->m_bColor30 == 1) {
        // the rebalance: walk while not the root
        STreeNode* pX = pFix;            // plVar9
        STreeNode* pP = pFixPar;         // plVar8
        if (pX != pKern->m_pHead30->m_pParent08) {
            do {
                STreeNode* pPar2 = pP;   // plVar7
                if (pX->m_bColor30 != 1) break;
                if (pX == pPar2->m_pLeft00) {
                    // pX is the LEFT child: S = par->right
                    STreeNode* pS = pPar2->m_pRight10;
                    if (pS->m_bColor30 == 0) {
                        pS->m_bColor30 = 1;
                        pPar2->m_bColor30 = 0;
                        RotateLeft(pKern, pPar2);
                        pS = pPar2->m_pRight10;
                    }
                    if (pS->m_bIsnil31 == 0) {
                        if (pS->m_pLeft00->m_bColor30 != 1
                            || pS->m_pRight10->m_bColor30
                                   != 1) {
                            if (pS->m_pRight10->m_bColor30
                                    == 1) {
                                // the inner case: rotate
                                // S RIGHT (1419e2000)
                                pS->m_pLeft00->m_bColor30
                                    = 1;
                                pS->m_bColor30 = 0;
                                RotateRight(pKern, pS);
                                pS = pPar2->m_pRight10;
                            }
                            pS->m_bColor30 =
                                pPar2->m_bColor30;
                            pPar2->m_bColor30 = 1;
                            pS->m_pRight10->m_bColor30
                                = 1;
                            RotateLeft(pKern, pPar2);
                            break;
                        }
                        pS->m_bColor30 = 0;
                    }
                } else {
                    // pX is the RIGHT child: S = par->left
                    STreeNode* pS = pPar2->m_pLeft00;
                    if (pS->m_bColor30 == 0) {
                        pS->m_bColor30 = 1;
                        pPar2->m_bColor30 = 0;
                        RotateRight(pKern, pPar2);
                        pS = pPar2->m_pLeft00;
                    }
                    if (pS->m_bIsnil31 == 0) {
                        if (pS->m_pRight10->m_bColor30
                                != 1
                            || pS->m_pLeft00->m_bColor30
                                   != 1) {
                            if (pS->m_pLeft00->m_bColor30
                                    == 1) {
                                pS->m_pRight10->m_bColor30
                                    = 1;
                                pS->m_bColor30 = 0;
                                RotateLeft(pKern, pS);
                                pS = pPar2->m_pLeft00;
                            }
                            pS->m_bColor30 =
                                pPar2->m_bColor30;
                            pPar2->m_bColor30 = 1;
                            pS->m_pLeft00->m_bColor30
                                = 1;
                            RotateRight(pKern, pPar2);
                            break;
                        }
                        pS->m_bColor30 = 0;
                    }
                }
                pP = pPar2->m_pParent08;  // climb
                pX = pPar2;
            } while (pX != pKern->m_pHead30->m_pParent08);
        }
        pX->m_bColor30 = 1;   // *(plVar9 + 6) = 1
    }
    g_fnFree(pN);
    if (pKern->m_nSize38 != 0) {
        pKern->m_nSize38 = pKern->m_nSize38 - 1;
    }
    // out: {proxy, the advanced node}
    pOut->m_pProxy00 = pKern->m_pProxy00;
    pOut->m_pNode08 = pWhere->m_pNode08;
}

} // namespace training

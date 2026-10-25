// ============================================================
// Training.dll port — the std::map PUBLIC-API wrapper
// family + the mgr accessor. VERBATIM from the Ghidra
// listing (addresses in the header).
// ============================================================
#include "TrainingMapApi.h"

namespace training {

// the _time64 seam (defaults to a fixed test clock)
int64_t (*g_fnTime64)() = []() -> int64_t { return 0; };

// ============ FUN_1419e3750: distance ============
// NOTE the ORIGINAL's param order: (FIRST pair, LAST
// pair, &count) — the walk advances the FIRST node.
void Distance(const void* const* ppFirst,
              const void* const* ppLast, uint64_t* pnCount) {
    void* pPrxLast = *(void**)&ppLast[0];
    STreeNode* pNdLast = (STreeNode*)ppLast[1];
    void* pPrxFirst = *(void**)&ppFirst[0];
    STreeNode* pNdFirst = (STreeNode*)ppFirst[1];
    while (true) {
        if (pPrxFirst == nullptr
                || pPrxFirst != pPrxLast)
            g_fnInvalidParameter();
        if (pNdFirst == pNdLast)
            break;
        *pnCount = *pnCount + 1;
        if (pPrxFirst == nullptr)
            g_fnInvalidParameter();
        if (pNdFirst->m_bIsnil31 == 0) {
            // the inline ++ (min-of-right / climb)
            STreeNode* pR = pNdFirst->m_pRight10;
            if (pR->m_bIsnil31 == 0) {
                // the leftmost of the right subtree
                STreeNode* pL = pR->m_pLeft00;
                uint8_t isnil = pL->m_bIsnil31;
                STreeNode* pEnd = pR;
                while (isnil == 0) {
                    isnil = pL->m_pLeft00->m_bIsnil31;
                    pEnd = pL;
                    pL = pL->m_pLeft00;
                }
                pNdFirst = pEnd;
            } else {
                // climb while the node is the parent's RIGHT
                STreeNode* pPar =
                    pNdFirst->m_pParent08;
                uint8_t isnil = pPar->m_bIsnil31;
                while (isnil == 0
                        && pNdFirst
                               == pPar->m_pRight10) {
                    pNdFirst = pPar;
                    pPar =
                        pNdFirst->m_pParent08;
                    isnil = pPar->m_bIsnil31;
                }
                pNdFirst = pPar;   // the head stops it
            }
        } else {
            g_fnInvalidParameter();
        }
    }
}

// ============ FUN_1419e3840 / FUN_1419e3de0 ============
void DeletePtr(void** pp) {
    g_fnFree(*pp);
}
void DeletePtr2(void** pp) {
    g_fnFree(*pp);
}

// ============ FUN_1419e3860: erase(first, last) ============
void EraseRange(SMapKernel* pKern, SMapIterator* pOut,
                void** ppFirst, void** ppLast) {
    // lVar2 = *(head) = the Lmost
    if (ppFirst[0] == nullptr
            || ppFirst[0] != pKern->m_pProxy00)
        g_fnInvalidParameter();
    if ((STreeNode*)ppFirst[1]
            == pKern->m_pHead30->m_pLeft00) {
        // first == begin()
        if (ppLast[0] == nullptr
                || ppLast[0] != pKern->m_pProxy00)
            g_fnInvalidParameter();
        if ((STreeNode*)ppLast[1]
                == pKern->m_pHead30) {
            // last == end() -> the whole-tree Clear
            Clear(pKern);
            // out.node = *(head) = head->left
            // (== head after the Clear); out.proxy
            pOut->m_pNode08 =
                pKern->m_pHead30->m_pLeft00;
            pOut->m_pProxy00 = pKern->m_pProxy00;
            return;
        }
    }
    while (true) {
        if (ppFirst[0] == nullptr
                || ppFirst[0] != ppLast[0])
            g_fnInvalidParameter();
        void* pPrx = ppFirst[0];
        if ((STreeNode*)ppFirst[1]
                == (STreeNode*)ppLast[1])
            break;
        STreeNode* pErase = (STreeNode*)ppFirst[1];
        if (pPrx == nullptr)
            g_fnInvalidParameter();
        if (pErase->m_bIsnil31 == 0) {
            // the inline ++ ADVANCE FIRST (verbatim
            // order: advance, then erase the saved old
            // node)
            STreeNode* pR = pErase->m_pRight10;
            if (pR->m_bIsnil31 == 0) {
                STreeNode* pL = pR->m_pLeft00;
                uint8_t isnil = pL->m_bIsnil31;
                STreeNode* pEnd = pR;
                while (isnil == 0) {
                    isnil = pL->m_pLeft00->m_bIsnil31;
                    pEnd = pL;
                    pL = pL->m_pLeft00;
                }
                ppFirst[1] = pEnd;
            } else {
                STreeNode* pPar =
                    pErase->m_pParent08;
                uint8_t isnil = pPar->m_bIsnil31;
                while (isnil == 0
                        && (STreeNode*)ppFirst[1]
                               == pPar->m_pRight10) {
                    ppFirst[1] = pPar;
                    pPar = ((STreeNode*)ppFirst[1])
                        ->m_pParent08;
                    isnil = pPar->m_bIsnil31;
                }
                ppFirst[1] = pPar;
            }
        } else {
            g_fnInvalidParameter();
        }
        // the saved AT iterator {proxy, the OLD node}
        SMapIterator it;
        it.m_pProxy00 = pPrx;
        it.m_pNode08 = pErase;
        SMapIterator outAt;
        EraseAt(pKern, &outAt, &it);
    }
    pOut->m_pProxy00 = pKern->m_pProxy00;
    pOut->m_pNode08 = (STreeNode*)ppFirst[1];
}

// ============ FUN_1419e3a10: lower_bound wrapper ============
void* LowerBoundRef(SMapKernel* pKern,
                    SMapIterator* pOut, uint32_t uKey) {
    LowerBound(pKern, pOut, uKey);
    return pOut;
}

// ============ FUN_1419e3aa0: try-emplace ============
// VERBATIM variable mapping: pNode = plVar6 (the walked
// node), bLeft = bVar7, pCmp = plVar5 (the LAB_3bfd
// compare node), pDup = plVar4/local_30 (the dup-out
// node), pCur = plVar3 (the climb node).
STryEmplaceOut* TryEmplace(SMapKernel* pKern,
                           STryEmplaceOut* pOut,
                           const SValRec* pRec) {
    uint32_t uKey = (uint32_t)pRec->m_nKey;
    STreeNode* pNode = pKern->m_pHead30;   // plVar6
    bool bLeft = true;                      // bVar7
    if (pNode->m_pParent08->m_bIsnil31 == 0) {
        STreeNode* pNext = pNode->m_pParent08;
        do {
            pNode = pNext;
            bLeft = uKey
                    < (uint32_t)pNode->m_nKey18;
            if (bLeft)
                pNext = pNode->m_pLeft00;
            else
                pNext = pNode->m_pRight10;
        } while (pNext->m_bIsnil31 == 0);
    }
    void* pProxy = pKern->m_pProxy00;   // local_38
    STreeNode* pCmp = pNode;            // plVar5
    STreeNode* pDup = pNode;            // plVar4
    if (!bLeft) {
        // LAB_1419e3bfd (the right path: the dup check
        // vs the walked node)
        pDup = pNode;
        if (uKey <= (uint32_t)pCmp->m_nKey18) {
            pOut->m_bInserted10 = 0;
            pOut->m_pProxy00 = pProxy;
            pOut->m_pNode08 = pDup;
            return pOut;
        }
    } else {
        // the LEFT path: the Lmost/predecessor check
        pCmp = pKern->m_pHead30->m_pLeft00;
        pDup = pNode;               // local_30 = plVar6
        if (pProxy == nullptr)
            g_fnInvalidParameter();
        if (pNode != pCmp) {         // walked != Lmost
            if (pProxy == nullptr)
                g_fnInvalidParameter();
            if (pNode->m_bIsnil31 == 0) {
                pCmp = pNode->m_pLeft00;
                if (pCmp->m_bIsnil31 == 0) {
                    // the RIGHTMOST of the left subtree
                    // (pCur = plVar3, pDup = plVar4 =
                    // the last pCmp = the pred)
                    STreeNode* pCur =
                        pCmp->m_pRight10;  // plVar3
                    uint8_t isnil =
                        pCur->m_bIsnil31; // cVar1
                    pDup = pCmp;   // plVar4 = plVar5
                    while (isnil == 0) {
                        pCmp = pCur;   // plVar5=plVar3
                        pCur =
                            pCmp->m_pRight10;
                        isnil =
                            pCur->m_bIsnil31;
                        pDup = pCmp;
                    }
                } else {
                    // climb while the node is the
                    // parent's LEFT (pCur = plVar3)
                    STreeNode* pCur = pNode;
                    STreeNode* pP =
                        pNode->m_pParent08;
                    uint8_t isnil =
                        pP->m_bIsnil31;
                    while (isnil == 0
                            && pCur
                                   == pP->m_pLeft00) {
                        STreeNode* pOld = pP;
                        pCur = pOld;  // plVar3=plVar5
                        pP =
                            pOld->m_pParent08;
                        isnil =
                            pP->m_bIsnil31;
                        pDup = pOld;  // local_30
                    }
                    // exit: plVar5 = plVar4
                    pCmp = pP;
                    pDup = pP;
                    if (pCur->m_bIsnil31 != 0) {
                        // the climb consumed the head
                        // (the unrecovered invalid
                        // handler + the post
                        // assignments: plVar5 =
                        // plVar3, plVar4 = local_30)
                        g_fnInvalidParameter();
                        pCmp = pCur;
                        pDup = pCur;
                    }
                }
            } else {
                // the walked node is the head (the
                // empty-tree sentinel; its right = the
                // tree max — unrecovered invalid path)
                pCmp = pNode->m_pRight10;
                pDup = pCmp;
                if (pCmp->m_bIsnil31 != 0) {
                    pDup = pCmp;
                    g_fnInvalidParameter();
                    pDup = pDup;
                }
            }
            // LAB_1419e3bfd (the left path: the dup
            // check vs the PREDECESSOR)
            pDup = pDup;
            if (uKey
                    <= (uint32_t)pCmp->m_nKey18) {
                pOut->m_bInserted10 = 0;
                pOut->m_pProxy00 = pProxy;
                pOut->m_pNode08 = pDup;
                return pOut;
            }
        }
        // the walked node == Lmost: insert LEFT there
        bLeft = true;
    }
    // insert via 1419e3360 at the WALKED node
    SMapIterator outIns;
    InsertNode(pKern, &outIns, bLeft, pNode,
               pRec);
    pOut->m_bInserted10 = 1;
    pOut->m_pProxy00 = outIns.m_pProxy00;
    pOut->m_pNode08 = outIns.m_pNode08;
    return pOut;
}

// ============ FUN_1419e3c50 / 1419e4120 / 1419e42d0:
// the proxy chain push (three IDENTICAL bodies) ============
// node = operator_new(8); on null: node = 0;
// else node->q0 = *pp; *pp = node
void ProxyChainPush(void** pp) {
    void* p = g_fnAlloc(8);
    if (p == nullptr) {
        p = nullptr;
    } else {
        *(void**)p = *pp;
    }
    *pp = p;
}
void ProxyChainPush4120(void** pp) {
    ProxyChainPush(pp);
}
void ProxyChainPush42d0(void** pp) {
    ProxyChainPush(pp);
}

// ============ FUN_1419e3ca0: erase(key) -> count ============
uint64_t EraseKeyCount(SMapKernel* pKern, uint32_t uKey) {
    SMapIterator lb;
    LowerBound(pKern, &lb, uKey);
    // first = {proxy, pLoc}, last = {proxy2, pFound}
    void* pPrx = lb.m_pProxy00;       // local_38
    void* pPrx2 = lb.m_pProxy10;      // local_28
    STreeNode* pFrom = lb.m_pNode08;    // plVar7
    STreeNode* pTo = lb.m_pParent18;   // plVar5
    uint64_t n = 0;                     // lVar8
    while (true) {
        if (pPrx == nullptr || pPrx != pPrx2)
            g_fnInvalidParameter();
        if (pFrom == pTo)
            break;
        n = n + 1;
        if (pPrx == nullptr)
            g_fnInvalidParameter();
        if (pFrom->m_bIsnil31 == 0) {
            // the inline ++ advance
            STreeNode* pR = pFrom->m_pRight10;
            if (pR->m_bIsnil31 == 0) {
                STreeNode* pL = pR->m_pLeft00;
                uint8_t isnil = pL->m_bIsnil31;
                STreeNode* pEnd = pR;
                while (isnil == 0) {
                    isnil =
                        pL->m_pLeft00->m_bIsnil31;
                    pEnd = pL;
                    pL = pL->m_pLeft00;
                }
                pFrom = pEnd;
            } else {
                STreeNode* pPar =
                    pFrom->m_pParent08;
                uint8_t isnil = pPar->m_bIsnil31;
                while (isnil == 0
                        && pFrom
                               == pPar->m_pRight10) {
                    pFrom = pPar;
                    pPar =
                        pFrom->m_pParent08;
                    isnil = pPar->m_bIsnil31;
                }
                pFrom = pPar;
            }
        } else {
            g_fnInvalidParameter();
        }
    }
    // the ORIGINAL copies the pairs, then the range
    // erase [lower_bound, upper_marker)
    void* aLast[2];
    aLast[0] = pPrx2;   // local_58 = {local_28,
    aLast[1] = pTo;     //  local_20}
    void* aFirst[2];
    aFirst[0] = pPrx;    // local_48 = {local_38,
    aFirst[1] =
        lb.m_pNode08;   //  local_30}
    SMapIterator out;
    EraseRange(pKern, &out, aFirst, aLast);
    return n;
}

// ============ FUN_1419e3e00: emplace_hint ============
// hint = the {proxy, node} pair (ppHint).
SMapIterator* EmplaceHint(SMapKernel* pKern,
                          SMapIterator* pOut,
                          const void* const* ppHint,
                          const SValRec* pRec) {
    uint32_t uKey = (uint32_t)pRec->m_nKey;
    if (pKern->m_nSize38 == 0) {
        // the empty tree: insert LEFT of the head
        // ('\x01', head)
        InsertNode(pKern, pOut, true,
                   pKern->m_pHead30, pRec);
        return pOut;
    }
    // else branch (the full cascade)
    STreeNode* pLmost = pKern->m_pHead30->m_pLeft00;
    if (*(void**)&ppHint[0] == nullptr
            || ppHint[0] != pKern->m_pProxy00)
        g_fnInvalidParameter();
    STreeNode* pHint =
        (STreeNode*)ppHint[1];   // puVar3
    if (pHint == pLmost) {
        // the hint == begin()
        if (uKey
                < (uint32_t)pHint->m_nKey18) {
            InsertNode(pKern, pOut, true,
                       pHint, pRec);   // LEFT of hint
            return pOut;
        }
    } else {
        if (pHint == pKern->m_pHead30) {
            // the hint == end()
            if ((uint32_t)pKern->m_pHead30
                     ->m_pRight10->m_nKey18
                    < uKey) {   // Rmost->key < key
                InsertNode(pKern, pOut, false,
                           pKern->m_pHead30
                               ->m_pRight10,
                           pRec);   // RIGHT of Rmost
                return pOut;
            }
        } else {
            // a middle hint
            if (uKey
                    < (uint32_t)pHint->m_nKey18) {
                // ---- the PREDECESSOR walk ----
                if (ppHint[0] == nullptr)
                    g_fnInvalidParameter();
                STreeNode* pCur =
                    pHint;   // local_30/plVar3
                STreeNode* pPred;   // plVar7
                if (pHint->m_bIsnil31 == 0) {
                    pPred =
                        pHint->m_pLeft00;
                    if (pPred->m_bIsnil31
                            == 0) {
                        // the RIGHTMOST of the
                        // left subtree
                        STreeNode* pR =
                            pPred->m_pRight10;
                        uint8_t isnil =
                            pR->m_bIsnil31;
                        while (isnil == 0) {
                            pPred = pR;
                            pR =
                                pPred->m_pRight10;
                            isnil =
                                pR->m_bIsnil31;
                        }
                    } else {
                        // climb while the node is
                        // the parent's LEFT
                        STreeNode* pP =
                            pHint->m_pParent08;
                        uint8_t isnil =
                            pP->m_bIsnil31;
                        while (isnil == 0
                                && pCur
                                       == pP
                                              ->m_pLeft00) {
                            pCur = pP;
                            pP =
                                pCur
                                    ->m_pParent08;
                            isnil =
                                pP->m_bIsnil31;
                        }
                        pPred = pP;   // plVar7=plVar5
                        if (pCur->m_bIsnil31
                                != 0) {
                            // the climb consumed
                            // the head (unrecovered
                            // invalid + the posts)
                            g_fnInvalidParameter();
                            pCur = pCur;
                            pPred = pCur;
                        }
                    }
                } else {
                    // the hint node is the head:
                    // prev = its RIGHT (the tree max)
                    pPred = pHint->m_pRight10;
                    if (pPred->m_bIsnil31
                            != 0) {
                        g_fnInvalidParameter();
                        pPred = pPred;
                    }
                }
                uKey = (uint32_t)pRec->m_nKey;
                if ((uint32_t)pPred->m_nKey18
                        < uKey) {
                    // pred->key < key: insert between
                    if (pPred->m_pRight10
                            ->m_bIsnil31
                            != 0) {
                        // pred has NO right child:
                        // RIGHT of pred
                        InsertNode(pKern, pOut,
                                   false, pPred,
                                   pRec);
                        return pOut;
                    }
                    // else LEFT of the hint
                    InsertNode(pKern, pOut, true,
                               pHint, pRec);
                    return pOut;
                }
            }
            if ((uint32_t)pHint->m_nKey18
                    < uKey) {
                // ---- the SUCCESSOR walk ----
                if (ppHint[0] == nullptr)
                    g_fnInvalidParameter();
                STreeNode* pHead =
                    pKern->m_pHead30;   // plVar7
                STreeNode* pCur = pHint;
                void* pPrx =
                    pKern->m_pProxy00;   // lVar4
                STreeNode* pNext;   // plVar9
                if (pHint->m_bIsnil31 == 0) {
                    pNext =
                        pHint->m_pRight10;
                    if (pNext->m_bIsnil31
                            == 0) {
                        // the LEFTMOST of the right
                        // subtree
                        STreeNode* pL =
                            pNext->m_pLeft00;
                        uint8_t isnil =
                            pL->m_bIsnil31;
                        while (isnil == 0) {
                            pNext = pL;
                            pL =
                                pNext->m_pLeft00;
                            isnil =
                                pL->m_bIsnil31;
                        }
                    } else {
                        // climb while the node is
                        // the parent's LEFT
                        STreeNode* pP =
                            pHint->m_pParent08;
                        uint8_t isnil =
                            pP->m_bIsnil31;
                        while (isnil == 0
                                && pCur
                                       == pP
                                              ->m_pLeft00) {
                            pNext = pP;
                            pCur = pP;
                            pP =
                                pCur
                                    ->m_pParent08;
                            isnil =
                                pP->m_bIsnil31;
                        }
                        pNext = pP;
                    }
                } else {
                    g_fnInvalidParameter();
                }
                if (ppHint[0] == nullptr
                        || ppHint[0] != pPrx)
                    g_fnInvalidParameter();
                if (pNext == pHead
                        || uKey
                               < (uint32_t)pNext
                                      ->m_nKey18) {
                    // next == end || key < next->key
                    if (pHint->m_pRight10
                            ->m_bIsnil31
                            != 0) {
                        // hint has NO right child:
                        // RIGHT of hint
                        InsertNode(pKern, pOut,
                                   false, pHint,
                                   pRec);
                        return pOut;
                    }
                    // else LEFT of next
                    InsertNode(pKern, pOut, true,
                               pNext, pRec);
                    return pOut;
                }
            }
        }
        // no hint branch taken: the hint is unusable
        // -> the full try-emplace
        STryEmplaceOut te;
        TryEmplace(pKern, &te, pRec);
        pOut->m_pProxy00 = te.m_pProxy00;
        pOut->m_pNode08 = te.m_pNode08;
    }
    return pOut;
}

// ============ FUN_1419e42a0 / 1419e4320 ============
// (identical: the kernel-core dtor + the proxy free)
void KernelDtorProxy(SMapKernel* pKern) {
    DtorKernelCore(pKern);
    g_fnFree(pKern->m_pProxy00);
}
void KernelDtorProxy4320(SMapKernel* pKern) {
    DtorKernelCore(pKern);
    g_fnFree(pKern->m_pProxy00);
}

// ============ FUN_1419e4350: the mgr dtor proxy ============
// *param_1 = vftable; 1419e3a30(this + 0x18);
// operator_delete(this[3]) = the kernel's proxy
void MgrDtorProxy(void* pMgrBase) {
    void** pMgr = (void**)pMgrBase;
    pMgr[0] =
        (void*)"training::CTrainingMgr::vftable";
    SMapKernel* pKern =
        (SMapKernel*)((uint8_t*)pMgrBase + 0x18);
    DtorKernelCore(pKern);
    g_fnFree(pKern->m_pProxy00);
}

// ============ FUN_1419e4170: the mgr accessor ============
// returns node + 0x20 (the value slot); the caller
// writes it (e.g. slot[1] = node+0x28 = the time)
void** MgrOpIndex(SMapKernel* pKern, uint32_t* pKey) {
    STreeNode* pCand = pKern->m_pHead30;   // puVar4
    // the inline lower-bound walk
    if (pCand->m_pParent08->m_bIsnil31 == 0) {
        STreeNode* pN = pCand->m_pParent08;
        do {
            if ((uint32_t)pN->m_nKey18
                    < *pKey) {
                pN = pN->m_pRight10;
            } else {
                pCand = pN;
                pN = pN->m_pLeft00;
            }
        } while (pN->m_bIsnil31 == 0);
    }
    void* pProxy = pKern->m_pProxy00;   // plVar6
    STreeNode* pHead = pKern->m_pHead30;
    if (pProxy == nullptr)
        g_fnInvalidParameter();
    if (pCand == pHead
            || *pKey
                   < (uint32_t)pCand->m_nKey18) {
        // MISS: emplace {key, pad-noise, _time64(0)}
        // via emplace_hint, hint = {proxy, cand}
        SValRec rec;
        rec.m_nKey = (uint64_t)*pKey;
        // rec[1] = the pad-noise qword
        // (uninitialized in the ORIGINAL: local_30 =
        // uStack_64 << 0x20 — the key slot's upper
        // half; deterministic 0 here)
        rec.m_pVal = nullptr;
        rec.m_nVal2 = (uint64_t)g_fnTime64();
        const void* aHint[2];
        aHint[0] = pProxy;
        aHint[1] = pCand;
        SMapIterator out;
        EmplaceHint(pKern, &out, aHint, &rec);
        pProxy = out.m_pProxy00;
        pCand = out.m_pNode08;
    }
    if (pProxy == nullptr) {
        g_fnInvalidParameter();
    } else {
        // the proxy holds the kernel base; the
        // node-vs-head end gate
        SMapKernel* pBase =
            *(SMapKernel**)pProxy;
        if (pCand == pBase->m_pHead30)
            g_fnInvalidParameter();
    }
    // puVar4 + 4 (qwords) = node + 0x20
    return (void**)((uint8_t*)pCand + 0x20);
}

} // namespace training

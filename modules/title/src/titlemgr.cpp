#include "TitleMgr.h"
#include "TitleGrant.h"     // g_fnMgrGetRecord etc.
#include "TitleMap.h"
#include "TitleRecord.h"    // CreateTitle

namespace title {

// ============ FUN_141971580: the safe destroy ============
// if (p) vt+0 (p, 1) — the deleting dtor
void CTitleMgrPort::SafeDestroyTitle(void* pTitle) {
    if (pTitle != nullptr) {
        g_fnTitleFree(pTitle);   // modeled: the vt+0 (p,1)
    }
}

// ============ FUN_141974420: GetUserTitle (vt+0x28) ============
// find-or-create the user's CTitle. On a MISS:
//   CreateTitle(id, mgr+0x48)  [1419718f0]
//   then op[] into the map storing the title at node+0x20
void* CTitleMgrPort::GetUserTitle(CTitleMgr* pMgr, int nId) {
    if (nId == 0) {
        g_fnLogError("DAT_141978310");
        return nullptr;
    }
    // the map kernel base = mgr+0x08
    SMapKernel* pMap =
        (SMapKernel*)((uint8_t*)pMgr + 0x08);
    // lower_bound by id
    STreeNode* pWhere = pMap->LowerBound((uint32_t)nId);
    if (pWhere == pMap->m_pHead38 ||
        (uint32_t)nId < (uint32_t)pWhere->m_nKey18) {
        // MISS: create the title with mgr+0x48 as the
        // "name" slot (the mask HOLDER)
        void* pTitle = (void*)::title::CreateTitle(
            nId, *(void**)((uint8_t*)pMgr + 0x48));
        if (pTitle == nullptr) {
            g_fnLogError("DAT_141978310");
            return nullptr;
        }
        // op[] into the map: node+0x20 = the title
        void** ppValue = pMap->OperatorAt((uint32_t)nId);
        *ppValue = pTitle;
        return pTitle;
    }
    // HIT: node+0x20
    return pWhere->m_pValue20;
}

// ============ FUN_1419740e0: DeleteUserTitle ============
bool CTitleMgrPort::DeleteUserTitle(CTitleMgr* pMgr, int nId) {
    SMapKernel* pMap =
        (SMapKernel*)((uint8_t*)pMgr + 0x08);
    if (nId == 0) {
        g_fnLogError("DAT_141978310");
        return false;
    }
    // lower_bound (the ORIGINAL calls 141973ad0 through
    // the iterator stack then re-checks deref validity)
    STreeNode* pWhere = pMap->LowerBound((uint32_t)nId);
    if (pWhere == pMap->m_pHead38 ||
        (uint32_t)nId < (uint32_t)pWhere->m_nKey18) {
        return false;             // masked 0: not found
    }
    // destroy the CTitle at node+0x20 (141971580 =
    // vt+0 (p,1)), then ZERO the slot TWICE verbatim
    SafeDestroyTitle(pWhere->m_pValue20);
    pWhere->m_pValue20 = nullptr;
    pWhere->m_pValue20 = nullptr;   // the verbatim repeat
    // erase the node with the RB rebalance (1419736b0)
    pMap->EraseNode(pWhere);
    return true;                    // CONCAT71(..., 1)
}


// ============ FUN_141974630: the mgr deleting dtor ============
// ORIGINAL flow: vftable write; walk Lmost..Rmost destroying
// each node's CTitle (log ERROR if the slot is null; zero
// the slot TWICE verbatim); erase-all the nodes; the head
// freed and nulled (+0x38/+0x40); the proxy (+0x08) freed.
void CTitleMgrPort::DeletingDtor(CTitleMgr* pMgr) {
    // *param_1 = title::CTitleMgr::vftable (modeled)
    SMapKernel* pMap =
        (SMapKernel*)((uint8_t*)pMgr + 0x08);
    STreeNode* pHead = pMap->m_pHead38;
    // plVar5 = head->left (the Lmost)
    STreeNode* pNode = pHead->m_pLeft00;
    while (pNode != pHead) {
        if (pNode->m_pValue20 == nullptr) {
            // plVar5[4] == 0 -> log ERROR (verbatim)
            g_fnLogError("DAT_141978310");
        } else {
            // FUN_141971580 (node+0x20)
            SafeDestroyTitle(pNode->m_pValue20);
            // the TWICE-verbatim zero
            pNode->m_pValue20 = nullptr;
            pNode->m_pValue20 = nullptr;
        }
        // the in-order successor (the ORIGINAL's iterator
        // ++ body: leftmost of the right subtree, else
        // climb while the node is the parent's right)
        if (!pNode->m_pRight10->m_bIsnil29) {
            STreeNode* q = pNode->m_pRight10;
            while (!q->m_pLeft00->m_bIsnil29)
                q = q->m_pLeft00;
            pNode = q;
        } else {
            // the ORIGINAL's climb: continues ONLY while
            // the parent is NOT the sentinel (its +0x29
            // isnil) and the node is the parent's RIGHT
            STreeNode* par = pNode->m_pParent08;
            while (!par->m_bIsnil29
                   && pNode == par->m_pRight10) {
                pNode = par;
                par = pNode->m_pParent08;
            }
            pNode = par;   // the head stops the walk
        }
    }
    // erase-all the nodes (the 141972c50-walk from the
    // root: subtree-destroy, free, move left) + the
    // head re-circularization + size 0
    pMap->Clear();
    // 141973ee0(end,end) -> 141972e10 (clear again —
    // the no-op path) then the head teardown:
    g_fnFree(pMap->m_pHead38);
    pMap->m_pHead38 = nullptr;          // param_1[7] = 0
    pMap->m_nSize40 = 0;                // param_1[8] = 0
    // the proxy free (operator_delete(*plVar5))
    g_fnFree(pMap->m_pProxy08);
    pMap->m_pProxy08 = nullptr;
}

} // namespace



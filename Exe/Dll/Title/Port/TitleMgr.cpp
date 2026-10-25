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

} // namespace

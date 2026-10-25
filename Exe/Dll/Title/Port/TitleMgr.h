#pragma once
// ============================================================
// Title.dll — Port — Unit D11: the mgr CRUD layer
//  FUN_141974420 — GetUserTitle (vt+0x28): find or
//    create the CTitle via 1419718f0 + the map op[]
//  FUN_1419740e0 — DeleteUserTitle: destroy the CTitle
//    at node+0x20 (twice-verbatim zero) + erase the node
//  FUN_141971580 — the safe title destroy (vt+0 (p,1))
//  FUN_141974630 — the CTitleMgr deleting dtor
// RECONCILED FINDING: STitleMaskRec == CTitle
//   (holder@+8 == the name slot, id@+0x10, stamp@+0x14)
// ============================================================
#include <cstdint>
#include "TitleModule.h"

namespace title {

class CTitleMgrPort {          // operates on a CTitleMgr
public:
    // ORIGINAL FUN_141974420 (mgr, id) -> the CTitle*
    static void* GetUserTitle(CTitleMgr* pMgr, int nId);
    // ORIGINAL FUN_1419740e0 (mgr, id) -> bool
    static bool DeleteUserTitle(CTitleMgr* pMgr, int nId);
    // ORIGINAL FUN_141971580 (title)
    static void SafeDestroyTitle(void* pTitle);
    // ORIGINAL FUN_141974630: the mgr DELETING dtor —
    // vtable write + destroy every node's CTitle (the
    // DAT_141978310 ERROR log when the slot is null +
    // the TWICE-verbatim zero) + erase-all the nodes +
    // free the head (nulled) + free the proxy
    static void DeletingDtor(CTitleMgr* pMgr);
};

} // namespace

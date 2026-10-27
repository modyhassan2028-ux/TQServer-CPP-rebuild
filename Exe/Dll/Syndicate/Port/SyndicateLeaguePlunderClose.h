#pragma once
#include <cstdint>
// ============================================================================
// SyndicateLeaguePlunderClose.h — unit D79:
// CLeagueMgr::PlunderWarClose (FUN_141774c70, 301 lines)
// — the plunder-war END: the 0x43 walk over the
// PLUNDERING map, the 0x44 walk over the PLUNDERED map,
// mgr+0x35c = 3, the five-map tree destruction + head
// re-init, vt+0x528, and the closing 0x46 broadcast.
namespace syndicate {
extern void (*g_fnPwcTreeDestroy)(void* pMap, void* pRoot);   // FUN_1417713d0
extern void (*g_fnPwcWarUiState)(void* pLogic, int32_t nA,
                                 int32_t nB);                 // vt+0x528
void PlunderWarClose(void* pMgr);                             // FUN_141774c70
}

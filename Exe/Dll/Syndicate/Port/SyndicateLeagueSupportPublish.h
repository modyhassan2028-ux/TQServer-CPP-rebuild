#pragma once
#include <cstdint>
// ============================================================================
// SyndicateLeagueSupportPublish.h — unit D80:
// CSyndicateLogic::PublishSupportTokenFromClient
// (FUN_1417c3230, 530 lines) — the SUPPORT-token publish
// sibling of D78. RAW-verified differences from D78:
//   - gate: FUN_14174ebd0(mgr) == 1 OR == 2 (TWO calls,
//     verbatim) instead of == 0; NO FUN_141766a70 check
//   - compose-path skip compares vs the USER LEAGUE (not
//     the member key)
//   - NEW per-target gate: FUN_141768ec0(mgr, key, target)
//     must be true before the push
//   - post-loop gate: the LAST resolved target != 0 AND
//     the vector non-empty
//   - token type 0x6a; DB log line 0x2774
//   - the pages msg: create(6, ceil((max-ppl)/cfg))
//   - support branch: NO vt+0x238 count gate; charge
//     vt+0x140; MyLogSave 350/4323; the notify string is
//     STR_LEAGUE_NOTIFY_USER_SUPPORT_TOKEN_BY_EMONEY
//   - NO msg1 (1417d61c0) block; straight to the msg2
//     (1417d7350) status family
namespace syndicate {
extern char (*g_fnPstTargetAllowed)(void* pMgr, uint32_t uKey,
                                     uint32_t uTarget);   // FUN_141768ec0
int32_t PublishSupportTokenFromClient(void** apLogic, uint32_t uUser,
        int32_t nCount, uint32_t* apTargets, char bSupport,
        uint32_t uParam6);                                    // FUN_1417c3230
}

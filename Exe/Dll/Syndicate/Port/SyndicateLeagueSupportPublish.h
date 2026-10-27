// ============================================================================
// SyndicateLeagueSupportPublish.h — unit D80: RAW-verbatim port of
// FUN_1417c3230 (CSyndicateLogic::PublishSupportTokenFromClient).
// (Header reconstructed from the D80 commit ae21d1d — the .cpp was
// pushed without this file, breaking the build at HEAD.)
#ifndef SYNDICATE_LEAGUE_SUPPORT_PUBLISH_H
#define SYNDICATE_LEAGUE_SUPPORT_PUBLISH_H

#include <cstdint>

namespace syndicate {

// ---- the seams (bodies in later units / test mocks) ----
extern char (*g_fnPstTargetAllowed)(void*, uint32_t,
                                     uint32_t);

// ---- the body (FUN_1417c3230) ----
int32_t PublishSupportTokenFromClient(void** apLogic,
    uint32_t uUser, int32_t nCount,
    uint32_t* apTargets, char bSupport,
    uint32_t uParam6);

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_SUPPORT_PUBLISH_H

// FORWARDING SHIM — the real source now lives at the
// ORIGINAL path: modules/syndicate/src/league.{h,cpp}.
#ifndef SHIM_SYNDICATE_LEAGUE_INVADE_WARN_H
#define SHIM_SYNDICATE_LEAGUE_INVADE_WARN_H
#include "modules/syndicate/src/league.h"
#include <cstdint>
namespace syndicate {
inline uint8_t FlyToInvadeWarning(int64_t lMgr,
    uint32_t uUser, uint32_t uTarget) {
    return ((CLeagueMgr*)lMgr)->FlyToInvadeWarning(
        lMgr, uUser, uTarget);
}
}  // namespace syndicate
#endif

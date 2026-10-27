// ============================================================
// Syndicate.dll port — unit T14/D39: the RELEASE walks —
// verbatim.
//   141748ea0 — LeagueReleaseUsers(entity, ...): the
//     begin-walk over the USERS map (entity+0x58, head
//     +0x88): the CRT iterator gates + the value
//     dual-release (node+0x20 → rec->vt[0](rec,1) when
//     non-null) + the inline successor advance, then the
//     inlined map clear (the users-family subtree free +
//     delete + the head relinks + size 0).
//   1417d4db0 — LeagueTokenRelease(token, p2, p3, p4):
//     token+8 (a sub-object) dual-release via vt[0]
//     (sub, 1, p3, p4, -2) + the token's OWN deleting
//     dtor via vt slot 0 (token, 1).
//   141749040 — LeagueReleaseTokens(entity, p2, p3, p4):
//     the same begin-walk over the TOKENS map (entity
//     +0xd8, head +0x108): the triple CRT check blocks
//     around the direct LeagueTokenRelease call + the
//     value zeroed TWICE (the compiler duplicated the
//     check block — verbatim), then the inlined clear
//     with the D32-family subtree free.
// These replace the D38 SEAMS g_fnLeagueReleaseUsers /
// g_fnLeagueReleaseTokens — SyndicateLeagueLife.cpp now
// DEFAULTS those seams to these functions (tests may
// still override them for isolation).
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// 141748ea0 — the users release walk
void LeagueReleaseUsers(int64_t lEntity, int64_t lP2,
                        int64_t lP3, int64_t lP4);
// 1417d4db0 — the token release (dual + self)
void LeagueTokenRelease(void* pToken, int64_t lP2,
                        int64_t lP3, int64_t lP4);
// 141749040 — the tokens release walk
void LeagueReleaseTokens(int64_t lEntity, int64_t lP2,
                         int64_t lP3, int64_t lP4);

}  // namespace syndicate

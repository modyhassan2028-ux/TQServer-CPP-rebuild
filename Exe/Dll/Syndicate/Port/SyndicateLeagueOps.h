// ============================================================
// Syndicate.dll port — unit T11/D36 (part 2c): the three big
// CLeague member/token OPERATIONS, verbatim.
//   14174b6c0 — AddMember(entity, idUser, pMemberData):
//       the double find (users map + members map), the
//       MakeDefRecord("cq_league_member") record setup
//       (SetId(user) / SetId(league) via the record vt
//       +0xb8 slots), the def insert gate (vt+0x50), the
//       users-map unique insert, the 9-u32 member record
//       copy from pMemberData, and the members-map unique
//       insert. Any existing membership → the provider
//       notify (entity+8 resolve(0) → vt+0x48) + the
//       "user[%u] is league[%u] member!" log → 0.
//   14174b960 — RemoveMember(entity, idUser): the users
//       find; found → the member-record dual release
//       (vt+0x40 with 0, then vt[0] with 1), the users
//       erase-at-iter, the members erase(key) count,
//       → 1; not found → 0.
//   14174bbe0 — CreateToken(entity, idToken, ?, p4): the
//       INLINE lower_bound descent on the tokens map (the
//       0x29-isnil rule, the remember-updates-only-left),
//       the found/end gate, MakeDefRecord("cq_league_token"),
//       SetId(token)/SetId(league), the CToken ctor
//       (1417d4d60), the def insert gate (vt+0x50, NO
//       arg), the token key getter (1417d4e70) and the
//       tokens-map insert {key | anchor-high, CToken*}
//       (141749a50); exists → the provider notify + the
//       "token %u is exist,league=%u" log → 0.
// The singletons/vtables/records are SEAMS:
//   g_fnLeagueOpsInstance — InstanceGet (the module
//     singleton getter; its body lives in the instance
//     layer, not yet ported)
//   the record objects are plain {vftable, ...} blocks
//     driven by the tests' fake vtables — the port calls
//     the vtable slots by the ORIGINAL offsets verbatim.
// The logs are the g_fnLeagueLogFactory/g_fnLeagueLogWrite
// seams (the string constants documented per site).
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// ---------- the seams ----------
// InstanceGet — the module singleton (seam)
extern void* (*g_fnLeagueOpsInstance)();

// 14174b6c0 — AddMember(entity, idUser, pMemberData) → 1/0
uint8_t LeagueAddMember(int64_t lEntity, uint32_t uUser,
                        void* pMemberData);

// 14174b960 — RemoveMember(entity, idUser) → 1/0
uint8_t LeagueRemoveMember(int64_t lEntity, uint32_t uUser);

// 14174bbe0 — CreateToken(entity, idToken, p3, p4) → CToken*
void* LeagueCreateToken(int64_t lEntity, uint32_t uToken,
                        int64_t lP3, uint64_t uP4);

}  // namespace syndicate

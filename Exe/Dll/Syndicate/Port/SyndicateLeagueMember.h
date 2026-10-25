// ============================================================
// Syndicate.dll port — unit T10/D36 (part 1): the league
// member/token LOOKUP layer, verbatim.
// The CLeague entity keeps three member maps:
//   users   @ entity+0x58 (anchor@+0x58, head@+0x88) — 0x30 nodes
//   members @ entity+0x98 (0x3d-isnil nodes — a DIFFERENT node family)
//   tokens  @ entity+0xd8 (anchor@+0xd8, head@+0x108) — 0x30 nodes
// This part: the getters + the finds + the two inline lookups.
//   141745520 — the league id getter (resolve(0) → vt+0x48)
//   1417d4e70 — the token key getter (resolve(2) → vt+0x40)
//   1417d4d60 — the CToken ctor (new 0x10 {vftable, rec})
//   14172b520 — the find on the users map (the 0x29-isnil walk)
//   141749980 — the find on the members map (the 0x3d-isnil walk)
//   14174bac0 — the member-data lookup on the tokens map
//               (the inline lower_bound + the value@+0x20)
//   14174be40 — the user's league lookup: the walk on the users
//               map + the record resolve(3) → vt+0x20
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// 141745520 — the league id getter (entity) → uint32
uint64_t LeagueGetId(int64_t lEntity);

// 1417d4e70 — the token key getter (token rec) → uint32
uint64_t LeagueTokenKey(int64_t lToken);

// 1417d4d60 — the CToken ctor: new 0x10 {CToken::vftable, rec}
// (the vftable is a seam — g_pLeagueTokenVft)
void* LeagueTokenNew(int64_t lRec);

// 14172b520 — the find on the users map (0x29-isnil 0x30 nodes)
//   (map, outIter[2], key*) → outIter {anchor, node|head}
void* LeagueUserFind(int64_t lMap, void* pOutIter, uint32_t* pKey);

// 141749980 — the find on the members map (0x3d-isnil nodes)
void* LeagueMemberFind(int64_t lMap, void* pOutIter, uint32_t* pKey);

// 14174bac0 — the member-data value lookup on the tokens map
//   (entity, token key) → the value at node+0x20 or 0
void* LeagueMemberData(int64_t lEntity, uint32_t uToken);

// 14174be40 — the user's league: the users-map walk + the record
// resolve chain → the league id (or 0)
uint64_t LeagueUserLeague(int64_t lEntity, uint32_t uUser);

// the seams bound by the tests
extern void* g_pLeagueTokenVft;   // syndicate::CToken::vftable

}  // namespace syndicate

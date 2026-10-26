// ============================================================
// Syndicate.dll port — unit T13/D38: the CLeague LIFE
// cycle — the ctor/dtor/factory family, verbatim.
//   Entity layout (0x118 bytes, confirmed against
//   FUN_14174d830/14174cfc0):
//     +0x00 vftable, +0x08 provider, +0x10 leader(u32),
//     +0x14 name[16], +0x28 the PROXY of a SECOND
//     container (opnew(8) with the owner back-ref,
//     cleared by 1417495d0 in the fail path), +0x40
//     ..+0x50 zeroed in the ctor (the +0x28 container's
//     data tail), +0x58 the USERS map {proxy@+0,
//     head@+0x30, size@+0x38} (head 0x30, _Isnil@0x29),
//     +0x98 the MEMBERS map (head 0x40, _Isnil@0x3d),
//     +0xd8 the TOKENS map (head 0x30, _Isnil@0x29).
//   141726c90/141746a00/141746a60 — the three family
//     HEAD allocs (0x30/0x40/0x30, the first 3 qwords
//     zeroed; the _Isnil flag + self-links are written
//     by the map ctor, NOT here).
//   141733570/14174cc70/14174d6b0 — the three entity
//     MAP ctors (proxy opnew(8) with the owner back-ref
//     + the head via the family alloc + the self-links
//     + size 0).
//   141730e80/141748720/14174c530 — the three map DTORS
//     (the erase-range with BOTH iterators = END — the
//     {proxy, *head} / {proxy, head} iterator homes —
//     then delete head, head=0, size=0).
//   1417262c0/1417276c0/14172d3c0 — the users-family
//     subtree free / the clear / the erase-range (the
//     same MSVC template as the D32 family, the
//     isnil@0x29 offsets).
//   1417495d0 — the +0x28 container's truncate (the
//     checked-iterator gates + the memmove_s tail).
//   14174d830 — LeagueCtor (vftable + the +0x28 proxy +
//     the zero tail + the three map ctors + provider=0 +
//     leader=0 + the name qwords 0).
//   14174cfc0 — LeagueDtor (the three map dtors WITH the
//     interleaved proxy deletes, the +0x40 block, the
//     +0x28 proxy delete).
//   14174d8d0 — the SCALAR deleting dtor.
//   141743b60 — LeagueInit (the four gates + the
//     InstanceGet + the provider vt[2]("cq_league") +
//     the leader copy + StrCopy(name,0x10) + resolve(2)
//     →vt[23](id) + resolve(1)→vt[16](p3) + the p4 gate
//     resolve(8)→vt[22](1) + the save vt[10](1)).
//   14174a650 — the fail cleanup (the users release
//     walk + the tokens release walk + the members
//     clear + the +0x28 truncate + the provider
//     dual-release vt[0](1) + the self deleting dtor).
//   14174d900 — LeagueCreate (the four gates + opnew
//     (0x118) + the ctor + the null log + the init +
//     the fail cleanup).
// The unported callees are SEAMS:
//   g_fnLeagueReleaseUsers — 141748ea0 (the users
//     release walk, the entity+0x58 map, the node
//     value dual-release)
//   g_fnLeagueReleaseTokens — 141749040 (the tokens
//     release walk, the entity+0xd8 map)
//   g_fnLeagueMemMoveS — the memmove_s tail of 1417495d0
//   g_fnLeagueLifeVftable — syndicate::CLeague::vftable
// Reused seams: g_fnLeagueOpsInstance (InstanceGet),
// g_fnLeagueLogFactory/g_fnLeagueLogWrite (the
// DAT_141824ca8 error), g_fnMgrStrCopy (tq::StrCopy),
// g_fnMeritOpNew/g_fnMeritOpDelete/g_fnMeritInvalid.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---------- the seams ----------
extern void* g_fnLeagueLifeVftable;   // CLeague::vftable
extern void (*g_fnLeagueReleaseUsers)(int64_t lEntity,
    int64_t lP2, int64_t lP3, int64_t lP4);   // 141748ea0
extern void (*g_fnLeagueReleaseTokens)(int64_t lEntity,
    int64_t lP2, int64_t lP3, int64_t lP4);   // 141749040
extern int (*g_fnLeagueMemMoveS)(void* pDst,
    size_t uDstSize, const void* pSrc,
    size_t uSrcSize);

// 141726c90 — the users-family head alloc (0x30)
void* LeagueUsersHeadAlloc();
// 141746a00 — the members-family head alloc (0x40)
void* LeagueMembersHeadAlloc();
// 141746a60 — the tokens-family head alloc (0x30)
void* LeagueTokensHeadAlloc();

// 141733570 — the entity users map ctor @+0x58
void* LeagueUsersMapCtor(void* pMap);
// 14174cc70 — the entity members map ctor @+0x98
void* LeagueMembersMapCtor(void* pMap);
// 14174d6b0 — the entity tokens map ctor @+0xd8
void* LeagueTokensMapCtor(void* pMap);

// 1417262c0 — the users-family subtree free
void UsersFreeSubtree(void* pMap, void* pNode);
// 1417276c0 — the users-family clear
void UsersClear(void* pMap);
// 14172d3c0 — the users-family erase-range
void* UsersEraseRange(void* pMap, void* pOutIter,
                      void* pBegin, void* pEnd);

// 141730e80 — the users map dtor
void LeagueUsersMapDtor(void* pMap);
// 141748720 — the members map dtor
void LeagueMembersMapDtor(void* pMap);
// 14174c530 — the tokens map dtor
void LeagueTokensMapDtor(void* pMap);

// 1417495d0 — the +0x28 container truncate
void StringVecEraseTail(void* pContainer);

// 14174d830 — LeagueCtor(entity)
void* LeagueCtor(void* pEntity);
// 14174cfc0 — LeagueDtor(entity)
void LeagueDtor(void* pEntity);
// 14174d8d0 — the scalar deleting dtor
void LeagueDeletingDtor(void* pEntity, uint32_t uFlags);
// 141743b60 — LeagueInit(entity, id, p3, p4, p5, name)
uint32_t LeagueInit(int64_t lEntity, int32_t nId,
                    int64_t lP3, uint8_t uP4, int32_t nP5,
                    const char* pName);
// 14174a650 — the fail cleanup
void LeagueFailCleanup(void* pEntity, int64_t lP2,
                       int64_t lP3, int64_t lP4);
// 14174d900 — LeagueCreate(id, p2, p3, p4, name)
void* LeagueCreate(uint32_t uId, int64_t lP2,
                   uint8_t uP3, int32_t nP4,
                   const char* pName);

}  // namespace syndicate

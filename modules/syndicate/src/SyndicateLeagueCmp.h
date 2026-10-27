// ============================================================
// Syndicate.dll port — unit T8/D34: the league SORT
// COMPARATOR subgraph, verbatim.
// The D33 introsort orders member lists through
// FUN_1417ba4c0 (g_fnLeagueCmp); this unit ports that
// comparator and everything it resolves through:
//   1417b6210 — the CSyndicateLogic singleton (DAT_141886dd0:
//     new 0x88, the IProvider then CSyndicateLogic vftable
//     stores — the final vptr = CSyndicateLogic::vftable —
//     the zero fill [1..0xb] + the byte at +0xc + the
//     UNALIGNED qword zeros at +0x61/+0x69/+0x71/+0x79,
//     the log on alloc fail)
//   1417cad00 — the member lookup by uint ID (the 0-key
//     gate + the map find at mgr+8 + the iterator checks +
//     the value fetch at node+0x20; 0 when absent)
//   1417c8f70 — the map find on the 0x30-node member map
//     (the lower_bound descent on isnil@+0x29 + the
//     found/end gate; the output iter {anchor, node|head})
//   14178f270 — the rank getter (the +0x428 provider gate
//     + the log + the resolve vt+0x10 with arg 0 + the
//     read vt+0x40)
//   14178f410 — the secondary getter (the same chain with
//     arg 0x2d + the read vt+0x48)
//   1417ba4c0 — the comparator itself: a missing → false;
//     b missing OR rank(a) == the state → true;
//     state == rank(b) → false; sec(a) == sec(b) →
//     rank(a) < rank(b) (uint); else sec(b) < sec(a)
//     (int — the DESCENDING secondary key).
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the seams (the existing mock-kit convention) ----
extern void* (*g_fnLeagueOpNew)(size_t);        // operator_new
extern void (*g_fnLeagueInvalid)();             // _invalid_parameter_noinfo
extern void* (*g_fnLeagueLogFactory)();          // the log object factory
extern void (*g_fnLeagueLogWrite)(void* pLog, uint32_t uId, int nLevel);
extern void* g_pLeagueVftLogic;                 // syndicate::CSyndicateLogic::vftable
extern void* g_pLeagueVftProvider;              // syndicate::IProvider::vftable
extern void* g_pLeagueDatInstance;              // DAT_141886dd0
// bound by the D33 unit once this port lands:
extern bool (*g_fnLeagueCmp)(int* pState, uint32_t uA, uint32_t uB);

// 1417b6210 — the CSyndicateLogic singleton
void* LeagueSingleton();

// 1417c8f70 — the map find (map, outIter[2], key)
void* LeagueMapFind(void* pMap, void** pOutIter, uint32_t* pKey);

// 1417cad00 — the member lookup (mgr, id) → the member or 0
int64_t LeagueMemberLookup(void* pMgr, uint32_t uId);

// 14178f270 — the rank getter (member)
uint64_t LeagueMemberRank(int64_t lMember);

// 14178f410 — the secondary getter (member)
uint64_t LeagueMemberSec(int64_t lMember);

// 1417ba4c0 — the comparator (state, a, b)
bool LeagueMemberCmp(int* pState, uint32_t uA, uint32_t uB);

}  // namespace syndicate

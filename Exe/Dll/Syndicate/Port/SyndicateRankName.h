// D86: FUN_1417873a0 — the syndicate rank-id -> localized
// name resolver (IStringManager). ~333 RAW lines: three
// direct checks, then two switches by id range, then the
// STR_ERROR fallback.
#pragma once
#include <cstdint>
namespace syndicate {
// seams: theInstance() + the first-vt-slot GetStr call
extern void* (*g_fnD86StrMgr)();                    // theInstance
extern void* (*g_fnD86GetStr)(void*, const char*);  // (mgr, name)
void* SyndicateRankName(int nRank);
}

// D87: FUN_14179ad50 — builds the CMsgSynBaseProffer
// rank-count list: for each of the 34 ranks (in the
// RAW's exact order), count members via FUN_141798160
// and append the (rank, count) pair via FUN_1417dad20.
// Kit (verbatim): FUN_1417dace0 (create), FUN_1417dad20
// (append), FUN_1417dac80 (dtor).
#pragma once
#include <cstdint>
namespace syndicate {
// seams
extern void (*g_fnD87Ctor)(void*);            // 1417dac30
extern void (*g_fnD87CMsgInit)(void*);        // tq::CMsg::Init
extern void (*g_fnD87Log)(const char*);        // log_InlineLogERROR(DAT_141824ca8)
extern int (*g_fnD87Count)(void*, int);       // 141798160
extern void* g_pvD87ProfferVft;               // CMsgSynBaseProffer::vftable
extern void* g_pvD87CMsgVft;                  // tq::CMsg::vftable
// verbatim kit
uint32_t SynProfferCreate87(void* pMsg);       // 1417dace0
uint32_t SynProfferAppend87(void* pMsg, uint32_t uId, uint32_t uVal); // 1417dad20
void SynProfferDtor87(void* pMsg);            // 1417dac80
// the main chain
void SynProfferRankList87(void* pMgr, int nArg); // 14179ad50
}

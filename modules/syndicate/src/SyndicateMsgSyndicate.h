// SyndicateMsgSyndicate.h — D67
//
// CMsgSyndicate::Process @ 0x1417db7b0 (4297 bytes, the
// biggest body of the DLL family) — the 29-case main
// dispatcher (PB+4 u16, cases 1..0x32, jumptable at
// 0x1417dc87c) + the case-0x25 two-level RANK dispatch
// (byte table 0x1417dc95c -> dword table 0x1417dc944).
//
// RAW CORRECTIONS vs the decompile (the final judge):
//   * EVERY _snprintf in case 0x25 takes FIVE varargs
//     ("%d %d %d %d %d"): (rank, ce0ret/1, a50ret/1,
//     ac430ret, per-rank-const). The decompile showed
//     ONE vararg and dropped the ac430 return + the
//     per-rank 5th constants entirely.
//   * the per-rank 5th vararg constants: 0x3de->0,
//     0x3d4->0x28a, 0x370->0x140, 0x348->0x10e,
//     0x2a8->0x64, 0x25a->0.
//   * ac430(logic, actor) RETURNS and rides as the 4th
//     vararg (r12d) — the decompile called it void.
//   * ac7f0(logic, STRING-BUFFER) — 2nd arg is the
//     GetString buffer (the decompile hid it).
//   * ac700/ac720/ac730/ac7e0/ac800/ac820/ac9c0 all
//     take (logic, actor) — edx rides (same family
//     as D66's ac6f0/ac710/ac810).
//   * case 0x1b: ac750's 4th arg = r9 STALE = the
//     GetString size 0x100 (verbatim ride).
//   * case 0x1d: ac750's 4th arg = ac800's return
//     (mov r9, rdi — a real ride, kept verbatim).
//   * the case-0x1c rank ladder is a signed chain:
//     {0x1fe,0x1ff,0x25a,0x262,0x263} -> b7ae0;
//     0x3de -> acda0; 1000 -> logic-vt[29](...,0);
//     else the Illegal rank log. Same valid set for
//     0x1d (minus 1000) -> b7c10.
//   * the 0x348/0x352 rank handler has NO memset of
//     the snprintf buffer (the only one without).
//   * case 0x25 writes its reply through a STACK
//     CMsgSyndicate (ctor 1417db2b0 = D57's ported
//     CtorCMsgSyndicate), ac7d0 sends it, then the
//     vftable restores + the packer dtor.
#ifndef SYNDICATE_MSG_SYNDICATE_H
#define SYNDICATE_MSG_SYNDICATE_H

#include <cstdint>

namespace syndicate {

// ---- the new gate seams (all (logic, actor)) ----
extern bool (*g_fnAc700Gate)(void* pLogic, uint32_t uIdActor); // 1417ac700 (D63's body; the actor rides edx)
extern bool (*g_fnAc720Gate)(void* pLogic, uint32_t uIdActor); // 1417ac720
extern bool (*g_fnAc730Gate)(void* pLogic, uint32_t uIdActor); // 1417ac730
extern int64_t (*g_fnAc7e0)(void* pLogic, uint32_t uIdActor);  // 1417ac7e0
extern uint32_t (*g_fnAc7f0)(void* pLogic, const char* pszName); // 1417ac7f0 (logic, buf!)
extern int64_t (*g_fnAc800)(void* pLogic, uint32_t uIdActor);  // 1417ac800
extern void (*g_fnAc820)(void* pLogic, uint32_t uIdActor,
                         uint32_t uTarget);                    // 1417ac820
extern void (*g_fnAc9c0)(void* pLogic, uint32_t uIdActor,
                         int32_t iTarget);                     // 1417ac9c0
extern uint32_t (*g_fnAc430)(void* pLogic,
                             uint32_t uIdActor);               // 1417ac430 (RET used)

// ---- the deep-body seams ----
extern void (*g_fnBad50)(void* pLogic, uint32_t uIdActor,
    uint32_t uTarget, void* pR9Stale);                          // 1417bad50
extern void (*g_fnBb0e0)(void* pLogic, uint32_t uIdActor,
                         uint32_t uTarget);                     // 1417bb0e0
extern void (*g_fnB7850)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417b7850
extern void (*g_fnBb500)(void* pLogic, uint32_t uIdActor,
    const char* psz, uint32_t uTarget);                         // 1417bb500
extern void (*g_fnAab70)(void* pLogic, uint32_t uIdActor,
    uint32_t uP1, uint32_t uP2, uint32_t uP3);                  // 1417aab70
extern void (*g_fnAcc80)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417acc80
extern void (*g_fnAcda0)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417acda0
extern void (*g_fnB7ae0)(void* pLogic, uint32_t uIdActor,
    const char* psz, int32_t iRank);                            // 1417b7ae0
extern void (*g_fnB7c10)(void* pLogic, uint32_t uIdActor,
    uint32_t uFrom, int32_t iRank);                             // 1417b7c10 (logic, ac7f0ret, actor, rank)
extern void (*g_fnB7e70)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417b7e70
extern void (*g_fnAdeb0)(void* pLogic, uint32_t uIdActor);      // 1417adeb0
extern void (*g_fnAe130)(void* pLogic, uint32_t uIdActor);       // 1417ae130
extern void (*g_fnAe3a0)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417ae3a0
extern void (*g_fnAd190)(void* pLogic, uint32_t uIdActor,
    const char* psz, uint32_t uTarget);                         // 1417ad190
extern void (*g_fnAd790)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417ad790
extern void (*g_fnAdbb0)(void* pLogic, uint32_t uIdActor,
                         const char* psz);                      // 1417adbb0
extern void (*g_fnAe6b0)(void* pLogic, uint32_t uIdActor,
                         uint32_t uTarget);                     // 1417ae6b0

// ---- the record-side seams (on the ae630 record) ----
extern uint32_t (*g_fn791a50)(void* pRec, uint32_t uRank);      // 141791a50
extern uint32_t (*g_fn797ce0)(void* pRec, uint32_t uRank);      // 141797ce0
extern bool (*g_fn7983e0)(void* pRec, int32_t iArg);            // 1417983e0 (rec, 0)
extern bool (*g_fn79c700)(void* pRec, uint32_t uIdActor,
                          uint32_t uTarget);                    // 14179c700
extern bool (*g_fn79c820)(void* pRec, uint32_t uIdActor,
                          uint32_t uTarget);                    // 14179c820

// ---- the packer reply seams ----
extern void (*g_fnCStrPackerAddString)(void* pPacker,
                                       const char* psz);       // AddString
extern uint32_t (*g_fnCStrPackerGetSize)(void* pPacker);        // GetSize

// ---- the logs ----
extern void (*g_fnIllegalRankLog)(const char* pcFmt,
    int32_t iRank, int32_t iAction);  // the 3-arg InlineLogERROR import

// REUSED: g_fnGetGameMgr (1417b6210),
// g_fnMgrGateUserOnline (ac6f0), g_fnMgrGate710 (ac710),
// g_fnMgrAc810 (ac810), g_fnAnnounce750 (ac750) [D66],
// g_fnStringMgrInstance/GetStr, g_fnCStrPackerGetString/
// GetStrAmount [LeagueOpt.h], g_fnAnnounceStrCheck [D66],
// CtorCMsgSyndicate [D57], g_fnCMsgInitThunk [D59,
// tq::CMsg::Init 1417e8016], g_fnCStrPackerDtor [D65],
// SynMemberFind (1417ae630) [MeedDistribute], g_fnMsgBatchLog
// [D66 — the quintuple, line 0xb4 here].

// the CMsgSyndicate/CMsg vftable constants (the epilogue
// vptr restores; numeric VAs verbatim)
constexpr uint64_t kVftCMsgSyndicate = 0x14183dc10ull;
constexpr uint64_t kVftTqCMsg        = 0x14182e368ull;

void MsgSyndicateProcess(void* pMsg, uint32_t uIdActor);

} // namespace syndicate
#endif

// SyndicateMsgProcess2.h — D66 (the class BATCH unit)
//
// The 12 remaining small CMsg::Process bodies of the
// 18-handler CModule family (the vt scan bound every
// class vftable to its Process slot; CMsgSyndicate's
// 416-line body 1417db7b0 is D67 on its own).
//
//   class                         vt           Process
//   CMsgSynDomain            0x14183de00  -> 0x1417dcf90
//   CMsgSynProffer           0x14183e180  -> 0x1417dd960
//   CMsgSynAttrInfo          0x14183d768  -> 0x1417daba0
//   CMsgSynMemberInfo        0x14183df00  -> 0x1417dd1c0
//   CMsgSynMemberList        0x14183e010  -> 0x1417dd610
//   CMsgSynBaseProffer       0x14183d888  -> 0x1417dadb0
//   CMsgSynProfferRank       0x14183e2b0  -> 0x1417ddbb0
//   CMsgSelfSynMemAwardRank  0x14183d558  -> 0x1417da570
//   CMsgSynRecruitAdvertising     0x14183e3f8  -> 0x1417ddd90
//   CMsgSynRecruitAdvertisingOpt  0x14183e620  -> 0x1417de2f0
//   CMsgSynRecruitAdvertisingList 0x14183e508  -> 0x1417de120
//   CMsgLeagueToken          0x14183cfa0  -> 0x1417d92d0
//
// Raw-disasm corrections vs the decompile (the final
// judge per the porting rules):
//   * 1417ac6f0/1417ac710 take (logic, actor) — edx
//     rides through the mgr-thunk (the decompile
//     showed 1 arg).
//   * 1417ac810(logic, actor) — the case-0xb body
//     loads edx=actor BEFORE the call (decompile
//     claimed 1 arg).
//   * 1417b2df0(logic, actor, u32* out1, u32* out2,
//     u32* out3) — r8/r9/[rsp+0x20] are OUT pointers
//     the decompile dropped entirely (it read the
//     three pre-zeroed locals as plain zeros).
//   * the SelfSynMemAwardRank case-2..7 path carries
//     a verbatim `cmp r12d, r12d; jne` — always-equal
//     no-op, kept as a comment in the port.
//   * the jumptable (0x1417da7d0, 13 entries) maps
//     cases 8/9 to the shared default end.
//   * STR ride: at every 1417ac750 call in these
//     bodies r9 is NOT set — it rides STALE from the
//     Process caller. The port passes 0 with this
//     comment; ac750's 4th slot is a stale artifact.
#ifndef SYNDICATE_MSG_PROCESS2_H
#define SYNDICATE_MSG_PROCESS2_H

#include <cstdint>

namespace syndicate {

// ---- the mgr-vt thunks (all on *(pLogic+8) = mgr) ----
// 1417ac6f0: mgr-vt[0x2d0/8=90](mgr, actor) -> bool
extern bool (*g_fnMgrGateUserOnline)(void* pLogic,
                                      uint32_t uIdActor);
// 1417ac710: mgr-vt[0x2d8/8=91](mgr, actor) -> bool
extern bool (*g_fnMgrGate710)(void* pLogic,
                               uint32_t uIdActor);
// 1417ac810: mgr-vt[0x1f8/8=63](mgr, actor) -> int32
extern int32_t (*g_fnMgrAc810)(void* pLogic,
                                uint32_t uIdActor);
// 1417ac750 — the announce flow (a REAL function,
// not a thunk): (logic, actor, psz, r9-stale)
extern void (*g_fnAnnounce750)(void* pLogic,
    uint32_t uIdActor, const char* psz,
    void* pR9Stale);
// 1417b2df0 — mgr-vt[0x4b8/8=147](mgr, actor, out*,
// out*, out*) -> bool (the three OUT pointers!)
extern bool (*g_fnB2df0)(void* pLogic, uint32_t uIdActor,
    uint32_t* puOut78, uint32_t* puOut70,
    uint32_t* puOut68);
// 1417b2e20 — mgr-vt[0x3f0/8=126](mgr) -> u32
extern uint32_t (*g_fnB2e20)(void* pLogic);

// ---- the deep-body seams (bodies of later units) ----
extern void (*g_fnAe640)(void* pLogic, uint32_t uIdActor,
                        uint32_t uParam);      // 1417ae640
extern void (*g_fnAe720)(void* pLogic, uint32_t uIdActor,
    uint8_t uB4, uint8_t uB5);                 // 1417ae720
extern void (*g_fnAe790)(void* pLogic, uint32_t uIdActor,
                        uint32_t uParam);      // 1417ae790
extern void (*g_fnAe9b0)(void* pLogic,
                        uint32_t uIdActor);    // 1417ae9b0
extern void (*g_fnAf620)(void* pLogic, uint32_t uIdActor,
    uint32_t uP6, uint32_t uPA);               // 1417af620
extern void (*g_fnAf670)(void* pLogic, uint32_t uIdActor,
    uint32_t uP6, uint32_t uPA);               // 1417af670
extern void (*g_fnAf6c0)(void* pLogic, uint32_t uIdActor,
    uint32_t uP6, uint32_t uS16, uint32_t uU12,
    uint16_t uWord4);                          // 1417af6c0
extern void* (*g_fnGetSomeObj41a30)();         // 141741a30
extern void (*g_fn410f0)(void* pObj, uint32_t uIdActor,
    uint32_t uPA);                             // 1417410f0
extern int32_t (*g_fn40fd0)(void* pObj,
    int32_t iArg);                             // 141740fd0
extern void (*g_fn41410)(void* pObj,
    uint32_t uIdActor);                        // 141741410
extern void* (*g_fnD77d350)();                 // 14177d350
extern bool (*g_fnD77caa0)(void* pObj, int32_t iS16,
    int32_t iU12);                             // 14177caa0

// ---- the checks + the logs ----
// tq::AnnounceStrCheck(psz, n) -> bool (import)
extern bool (*g_fnAnnounceStrCheck)(const char* psz,
                                     int32_t n);
// the InlineLogERROR quintuple — the fixed fmt obj
// 0x141824ca8 ("\xa1\xef%s(%s)\xa1\xef in %s, %d")
// rides the doc; the seam takes the 4 vararg parts
extern void (*g_fnMsgBatchLog)(const char* pcTag,
    const char* pcExpr, const char* pcFile,
    uint32_t uLine);
// the printf-style tail log (the IAT slot right below
// InlineLogERROR — 0x14182302f): (fmt, action)
extern void (*g_fnInvalidActionLog)(const char* pcFmt,
                                    int32_t iAction);

// REUSED: g_fnGetGameMgr (1417b6210, CrossMerit.h),
// g_fnStringMgrInstance / g_fnStringMgrGetStr
// (LeagueOpt.h — theInstance + vt[0](mgr, key))

// ---- the 12 Process bodies (verbatim) ----
void MsgSynDomainProcess(void* pMsg, uint32_t uIdActor);
void MsgSynProfferProcess(void* pMsg, uint32_t uIdActor);
void MsgSynAttrInfoProcess(void* pMsg, uint32_t uIdActor);
void MsgSynMemberInfoProcess(void* pMsg, uint32_t uIdActor);
void MsgSynMemberListProcess(void* pMsg, uint32_t uIdActor);
void MsgSynBaseProfferProcess(void* pMsg, uint32_t uIdActor);
void MsgSynProfferRankProcess(void* pMsg, uint32_t uIdActor);
void MsgSelfSynMemAwardRankProcess(void* pMsg,
                                   uint32_t uIdActor);
void MsgSynRecruitAdvertisingProcess(void* pMsg,
                                     uint32_t uIdActor);
void MsgSynRecruitAdvertisingOptProcess(void* pMsg,
                                        uint32_t uIdActor);
void MsgSynRecruitAdvertisingListProcess(void* pMsg,
                                         uint32_t uIdActor);
void MsgLeagueTokenProcess(void* pMsg, uint32_t uIdActor);

} // namespace syndicate
#endif

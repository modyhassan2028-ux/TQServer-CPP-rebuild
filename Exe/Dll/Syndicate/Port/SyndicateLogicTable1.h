// ============================================================================
// SyndicateLogicTable1.h — unit D90 (the WHOLE-CLASS wave 1):
// the CSyndicateLogic vtable (0x141835068, 232 slots) — the
// first 18 real bodies, verbatim from the RAW.
//
// The class object layout (recovered across D26-D88):
//   +0x00 the logic vtable   +0x08 the game-mgr box
//   +0x10 the members map     +0x18 the log-record map
//   [1] = the mgr box, [2] = the map, [3] = the log map,
//   [10] = the acct mgr (+0x50)
//
// THE SLOTS (index = vtable offset / 8):
//   +0x000 1417b61e0 deleting dtor (base a9680 seam)
//   +0x008 1417a9f20 pushSynAttrInfo (msg kit a860/a910/a8b0)
//   +0x010 1417a9fc0 destroySoon flow (cad00/92cb0/8f4f0/c5830
//          + the CMsgSyndicate kit db2b0/db3a0/db330)
//   +0x018 1417aa170 pushMemberInfo (8c8e0/5ea0/cad00/888040)
//   +0x020 1417aa280 pushAttrChange (a860/dab00/a8b0)
//   +0x028 1417aa320 pushProffer (dd6e0/dd790/dd730)
//   +0x030 1417aa3c0 donate flow (8e590 + vt+0x30)
//   +0x040 1417aa4b0 vt+0x88 forward
//   +0x048 1417aa4e0 member-online fwd (8e540)
//   +0x058 1417aa510 log-rec syn id (785d00)
//   +0x068 1417b6620 the rank-swap flow (787370/785ea0/
//          786aa0/vt+0x328/a0760/9f650/c6bd0)
//   +0x070 1417abe60 set-player fwd (cadb0)
//   +0x078 1417ab080 rank == 1000 (vt+0xf8)
//   +0x080 1417ab0a0 rank-clear fwd (7869f0)
//   +0x088 1417ab0c0 rank == 0x3de
//   +0x090 1417ab0e0 rank == 0x37a
//   +0x098 1417ab100 the assemblyman family gate
//   +0x0a0 1417ab170 the 0x2b2/0x28a gate
//   +0x0a8 1417b6e70 OnUserDelRole (767560/cad00/5ee00/
//          630d0/74b960/8c8e0/aebb0 + the literal log)
//
// SEAMS (deep bodies, later units):
//   g_fnT1DtorBody 1417a9680, g_fnT1MsgInitA 1417da910,
//   g_fnT1MsgInitB 1417dab00, g_fnT1MsgInitC 1417dd790,
//   g_fnT1MsgInitD 1417db3a0, g_fnT1MsgDtorA 1417da8b0,
//   g_fnT1MsgDtorC 1417dd730, g_fnT1RecGetData 141788040,
//   g_fnT1IsLowMoney 14178e590, g_fnT1MemberOnline 14178e540,
//   g_fnT1DelRoleSoon 141792cb0, g_fnT1GetDestroyDays 14178f4f0,
//   g_fnT1OptGet 1417c5830, g_fnT1SetPlayer 1417cadb0,
//   g_fnT1HasFlag 1417cad90, g_fnT1RankClear 1417869f0,
//   g_fnT1IsConfirmed 141786aa0, g_fnT1FlagClear 141787370,
//   g_fnT1DelRole 14174b960, g_fnT1QuitFlow 1417aebb0,
//   g_fnT1LogError (log_InlineLogERROR, 1-arg)
// REUSED: LeagueMemberLookup (1417cad00, LeagueCmp),
//   LogRecMapFind (14178c8e0, D60), CtorCMsgSynAttrInfo
//   (1417da860), CtorCMsgSynProffer (1417dd6e0),
//   CtorCMsgSyndicate (1417db2b0), MgrUserLeagueId
//   (14175ee00), MgrLeagueFind (1417630d0),
//   g_fnA84RankSetMisc/RecordUpdate/SetMemberRank (Appoint3de),
//   g_fnStringMgrInstance/GetStr (D61),
//   g_fnLbrOpDelete (operator_delete)
#ifndef SYNDICATE_LOGIC_TABLE1_H
#define SYNDICATE_LOGIC_TABLE1_H

#include <cstdint>

namespace syndicate {

// ---- the seams ----
extern void  (*g_fnT1DtorBody)(void*, uint64_t, void*, char*);
extern uint64_t (*g_fnT1MsgInitA)(void*, int64_t, int64_t);
extern uint64_t (*g_fnT1MsgInitB)(void*, int32_t, const char*);
extern uint64_t (*g_fnT1MsgInitC)(void*, uint32_t, void*);
extern uint64_t (*g_fnT1MsgInitD)(void*, uint32_t, int32_t);
extern void  (*g_fnT1MsgDtorA)(void*);
extern void  (*g_fnT1MsgDtorC)(void*);
extern void  (*g_fnT1RecGetData)(void*, void*);
extern char  (*g_fnT1IsLowMoney)(void*);
extern void  (*g_fnT1MemberOnline)(void*);
extern void  (*g_fnT1DelRoleSoon)(void*, uint32_t);
extern int64_t (*g_fnT1GetDestroyDays)(void*);
extern int32_t (*g_fnT1OptGet)(void*, uint32_t);
extern void  (*g_fnT1SetPlayer)(void*, uint32_t, uint32_t);
extern char  (*g_fnT1HasFlag)(void*, uint32_t);
extern void  (*g_fnT1RankClear)(int32_t);
extern uint64_t (*g_fnT1IsConfirmed)(void*);
extern uint64_t (*g_fnT1LogRecSynId)(void*);   // 141785d0
extern void  (*g_fnT1FlagClear)(int64_t, int32_t);
extern uint64_t (*g_fnT1DelRole)(void*, uint32_t);
extern uint64_t (*g_fnT1QuitFlow)(void*, void*, void*,
                                  const char*, char, char, char);
extern void  (*g_fnT1LogError)(const char*);

// ---- the bodies ----
void* Slot000DelDtor(void* p, uint64_t u2, void* p3, char* p4);
void  Slot008PushSynAttrInfo(void* pLogic, uint32_t uUser);
uint64_t Slot010DestroySoon(void* pLogic, int32_t nUser);
void  Slot018PushMemberInfo(void* pLogic, uint32_t uUser);
void  Slot020PushAttrChange(void* pLogic, int32_t nWho,
                            int32_t nWhat, const char* pName);
uint8_t Slot028PushProffer(void* pLogic, uint32_t uUser,
                           int64_t lA, int64_t lB);
uint64_t Slot030Donate(void* pLogic, uint32_t uUser,
                       int64_t lMoney);
uint64_t Slot040Fwd88(void* pLogic);
void  Slot048MemberOnline(void* pLogic, uint32_t uUser);
uint64_t Slot058LogRecSynId(void* pLogic, uint32_t uUser);
uint64_t Slot068RankSwap(void* pLogic, uint32_t uA, uint32_t uB);
void  Slot070SetPlayer(void* pLogic, uint32_t uA, uint32_t uB);
bool  Slot078IsRank1000(void* pLogic);
void  Slot080RankClear(void* pLogic);
bool  Slot088IsRank3de(void* pLogic);
bool  Slot090IsRank37a(void* pLogic);
int64_t Slot098AssemblymanGate(void* pLogic);
int64_t Slot0a0Gate2b228a(void* pLogic);
uint64_t Slot0a8OnUserDelRole(void* pLogic, uint32_t uUser);

}  // namespace syndicate

#endif  // SYNDICATE_LOGIC_TABLE1_H

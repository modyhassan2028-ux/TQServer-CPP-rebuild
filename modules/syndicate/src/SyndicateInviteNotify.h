// SyndicateInviteNotify.h — D68
//
// The five deep CSyndicateLogic bodies (the invite/notify
// family), all raw-verified call by call:
//   1417b0680  SynTalkGate      — the syndicate "say" gate
//   1417b0ea0  MemberOverhead   — the overhead-member notify
//   1417b98e0  LeagueInfoPush    — the league info + 0x2e broadcast
//   1417b48b0  InviteSynReply   — invite reply (syn variant, 10)
//   1417b4d60  InviteLeagueReply— invite reply (league variant, 0xb)
//
// RAW CORRECTIONS vs the decompile (the recurring lies):
//   * EVERY _snprintf here has varargs the decompile hid:
//     refuse → (1d8ret); leave-soon → (e7e0ret); join-league
//     → (lVar8, 1d8ret); syn-join → (lVar8, dd0ret);
//     join-success → (1d8ret, dd0ret).
//   * b98e0's "uVar/1000000" is a LIE: raw = imul 0x431bde83
//     + shr 0x12 = the MSVC magic for /1000 (BOTH values).
//   * The first mgr-vt[0x278] gate takes NO edx (stale ride)
//     in b48b0/b4d60/b98e0; the second one takes param_3.
//   * mgr-vt[0x2d0] takes (mgr, param_2) then (mgr, param_3)
//     — the decompile showed the second one argless.
//   * mgr-vt[0x268]/[0x280] in b0ea0 take (mgr, stale-edx)
//     and (mgr, actor); vt+0x410 takes SIX args (mgr, actor,
//     id, c10, c9, pszName) — the decompile showed four.
//   * The sends are ALL mgr-vt[8](mgr, actor, msg) — the
//     decompile dropped the msg arg in b98e0.
//   * b98e0's build fail log = the quintuple, line 0x2415,
//     expr "msgLeagueInfo.Create(stLeagueInfo, ...)", file
//     syndicatelogic.cpp; b0ea0's = line 0x1a36, expr
//     "msg.Create(OVERHEAD_USER, ...)".
//   * FUN_14174e7f0 takes (host, param_3, uVar4, 1, 8).
#ifndef SYNDICATE_INVITE_NOTIFY_H
#define SYNDICATE_INVITE_NOTIFY_H

#include <cstdint>
#include <cstddef>

namespace syndicate {

// ---- the seams (all new; bodies not yet ported) ----
extern uint32_t (*g_fn1417b0370)(void* pLogic, uint32_t uId);   // b0680 chain
extern bool (*g_fn14174f020)(void* pHost, uint32_t uActor,
                             void* pRec);                        // b98e0
extern void (*g_fn141745580)(void* pRec, void* pOut);            // b98e0
extern uint32_t (*g_fn1417b5370)(void* pLogic, uint32_t uActor,
                                 void* pRec);                    // b98e0
extern void (*g_fn141766b60)(void* pHost, uint32_t uId,
    void* pOut, void* pOutBuf, uint32_t uCap);                   // b98e0
extern void (*g_fn141766d10)(void* pHost, uint32_t uId,
    void* pOut, void* pOutBuf, uint32_t uCap);                   // b98e0
extern void (*g_fn1417d6110)(void* pMsg);                        // ctor (b98e0)
extern bool (*g_fn1417d61c0)(void* pMsg, const void* pRec,
    uint32_t uRank, uint32_t uA, uint32_t uB,
    const char* psz1, const char* psz2);                         // b98e0
extern void (*g_fn1417d6160)(void* pMsg);                        // dtor
extern bool (*g_fn1417d6790)(void* pMsg, uint32_t uType,
    uint32_t a, uint32_t b, uint32_t c);                        // b98e0
extern bool (*g_fn1417d6820)(void* pMsg, uint32_t uType,
    const char* psz, uint32_t a, uint32_t uActor,
    uint32_t b);                                                // b48b0/b4d60
extern void (*g_fn1417d66c0)(void* pMsg);                        // dtor
extern void (*g_fn1417d9900)(void* pMsg);                        // ctor (b0ea0)
// RAW: r12b = the LEADER flag (the cmove at
// 0x1417b0f32), r13b = the COUNTRY flag (the set at
// 0x1417b0f3c). d9b30 gets arg5=r12b(Leader),
// arg6=r13b(Country) — the decompile was RIGHT.
extern bool (*g_fn1417d9b30)(void* pMsg, uint32_t a,
    uint32_t uActor, uint32_t uId, uint8_t bLeader,
    uint8_t bCountry, const char* pszName,
    uint32_t uServerId);                                        // b0ea0
extern void (*g_fn1417d9950)(void* pMsg);                        // dtor
extern bool (*g_fn14174b6c0)(void* pRec, uint32_t uTarget,
                             void* pInfo);                      // b4d60
extern uint32_t (*g_fn14174e7e0)(void* pHost);                   // b48b0/b4d60
extern void (*g_fn14174e7f0)(void* pHost, uint32_t uTarget,
    uint32_t uArg, uint8_t bOne, uint16_t uEight);               // b4d60
extern bool (*g_fn141763920)(void* pHost, uint32_t uTarget);     // b48b0/b4d60
extern void (*g_fn14176ca70)(void* pHost, uint32_t uId,
    uint32_t uTarget, uint32_t uArg);                            // b48b0/b4d60
extern uint32_t (*g_fn14178f2d0)(void* pLeague);                 // b48b0/b4d60
extern int32_t (*g_fn14178f470)(void* pLeague);     // b48b0 (raw returns int)
extern int32_t (*g_fn141790390)(void* pLeague);                  // b48b0/b4d60
extern char (*g_fn1417903d0)(void* pLeague, uint32_t uId);     // b48b0
extern void (*g_fn14174dcd0)(void* pRec, uint32_t uArg);         // b48b0
extern void (*g_fnTqStrCopy)(char* pDst, const char* pSrc,
                             size_t uCap);                       // b4d60 (import)

// REUSED REAL (already-ported, called directly):
//   MgrLeagueFind        1417630d0  (LeagueMgr)
//   MgrGetLeaderId       1417647e0  (LeagueMgr)
//   LeagueGetLeaderId    141743e70  (LeagueMgr)
//   LeagueGetRec1Str     141743dd0  (LeagueMgr)
//   LeagueSetRecStr      141743f90  (LeagueMgr)
//   LeagueGetId          141745520  (LeagueMember)
//   LeagueMemberLookup   1417cad00  (LeagueCmp — via *(logic+0x10))
//   CtorCMsgLeagueOpt    1417d6640  (CMsgCtors)
// SEAMS REUSED: g_fnStringMgrInstance/GetStr (D66),
// g_fnAnnounce750 (D66), g_fnMsgBatchLog quintuple (D66),
// g_fnAnnounceStrCheck (D66).

// the five bodies
bool SynTalkGate(void* pLogic, uint32_t uActor,
                 const char* psz, void* pR9Stale);   // 1417b0680
void MemberOverhead(void* pLogic, uint32_t uActor,
                    uint8_t bFlag);                   // 1417b0ea0
void LeagueInfoPush(void* pLogic, uint32_t uActor);   // 1417b98e0
void InviteSynReply(void* pLogic, uint32_t uActor,
    uint32_t uTarget, uint8_t bAccept,
    uint8_t bRefuse);                                 // 1417b48b0
void InviteLeagueReply(void* pLogic, uint32_t uActor,
    uint32_t uTarget, uint8_t bAccept,
    uint8_t bRefuse);                                 // 1417b4d60

} // namespace syndicate
#endif

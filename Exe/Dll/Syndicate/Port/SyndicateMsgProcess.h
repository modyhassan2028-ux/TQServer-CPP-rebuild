// SyndicateMsgProcess.h — D59: the FIRST two
// CMsg Process handlers (the bodies behind the
// vtable [+0x18] slots recovered from the
// original binary's RTTI inventory).
//
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_1417d97c0 @ 1417d97c0 — syndicate::
//          CMsgLog::Process (vt @ 0x14182e4a0)
//   FUN_1417daee0 @ 1417daee0 — syndicate::
//          CMsgSynChgDomName::Process (vt @
//          0x14182e520)
//   FUN_1417dae90 @ 1417dae90 — the CMsgSyn-
//          ChgDomName reply Init (inlined into
//          the Process in the index as a callee)
//
// SEAMS (documented TBD, ported in later units):
//   1417b7010  the recruit-advertising record
//              flow (a deep body: 3x1072-byte
//              stack CMsg bufs) — g_fnLogRecord
//   1417ac620  the user log-record removal flow —
//              g_fnLogRemove
//   1417afb20  the chg-dom-name check flow —
//              g_fnChgDomCheck
//   1417b6210  the CSyndicateLogic singleton —
//              REUSED: g_fnGetGameMgr
//              (SyndicateCrossMerit.h, DAT_141886dd0)
//   1417ac7d0  the tail indirect call
//              `(**(code***)(*(longlong**)(p+8)+8))()`
//              — ported verbatim (a vt[+0x00]
//              dispatch on * (p+8), the mgr
//              member) — no seam needed.
//   log_InlineLogERROR — reused: g_fnMeedLog
//              (SyndicateSynMeed.h)
//
// The literal strings (verbatim):
//   "syndicate::CMsgLog::Process(idActor), "
//   "idActor:%d, Type:%d, MsgType:%d"
//   (the Process fallback ERROR log)
//   FUN_1417dae90 writes (to the PB at +0x408):
//   +0x18 = the success ushort (0/1),
//   +0x02 = 0x837 (msg id), +0x00 = 0x1c (type)
#ifndef SYNDICATE_MSG_PROCESS_H
#define SYNDICATE_MSG_PROCESS_H

#include <cstdint>

namespace syndicate {

// ---- seams ----
extern void (*g_fnLogRecord)(void* pLogic,
    uint32_t uIdActor);       // 1417b7010
extern void (*g_fnLogRemove)(void* pLogic,
    uint32_t uIdActor);       // 1417ac620
extern uint64_t (*g_fnChgDomCheck)(void* pLogic,
    uint32_t uIdActor, uint32_t uSynId,
    char* pszName);           // 1417afb20
extern void (*g_fnD59LogError)(const char* p, ...);
                              // InlineLogERROR
// tq::CMsg::Init @ 1417e8016 — the PB-runtime
// re-Init thunk (the shared Init the ctors call)
extern void (*g_fnCMsgInitThunk)(void* pMsg);

// ---- the bodies ----
void MsgLogProcess(void* pMsg, uint32_t uIdActor);
void MsgChgDomNameProcess(void* pMsg,
                          uint32_t uIdActor);

}  // namespace syndicate

#endif  // SYNDICATE_MSG_PROCESS_H

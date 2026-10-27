// SyndicateLeagueSalary.h — D65: the league salary
// grant flow FUN_1417b4310 (the D61 case-0x27 seam
// body) + 12 verbatim helpers.
//
// ORIGINAL (Syndicate.dll, ImageBase 0x141720000):
//   1417b4310  LeagueSalaryGrant(logic, actor,
//              type) — type 1 free / 2 contribution
//              / 3 emoney; 1433 bytes
//   141768870  SalaryCountGet(host, pos) — the
//              salary map lower_bound (host+0x568
//              head / host+0x538 cont), key WORD
//              @ +0x18, value @ +0x20, resolve(3),
//              sub vt+0x40
//   141768730  SalaryAmountGet(host, pos) — the
//              same walk, resolve(4), vt+0x40
//   14174be40  LeagueMemberPostGet(entity, actor)
//              — the member map lower_bound (entity
//              +0x88/+0x58), key DWORD @ +0x18,
//              resolve(3), sub vt+0x20 (byte)
//   14174bf70  LeagueMemberPostSet(entity, actor,
//              val, flush) — same walk, resolve(3),
//              sub vt+0xd8(val); flush = provider
//              vt+0x38(0)
//   141787de0  MemberRecPostGet(rec) — *rec ->
//              resolve(0x1b) -> vt+0x48
//   141787d80  MemberRecPostSet(rec, val, flush) —
//              *rec -> resolve(0x1b) -> vt+0xb0(val);
//              flush = *rec's provider vt+0x38(0)
//   14174e960  *(host+0x2fc) — the emoney price
//   14174e970  *(host+0x2f8) — the contribution cost
//   14174e980  *(host+0x300) — the free amount
//   14174e990  *(host+0x304) — the contribution amt
//   14174e9a0  *(host+0x308) — the emoney amount
//   1417d6790  ReplyInitCMsgLeagueOpt(msg, 0x27, 0,
//              flag, 0) — the PB writes (+6, +0xe,
//              +4, +10, +2=0xa3e, +0=0x13)
//   1417d66c0  DtorCMsgLeagueOpt(msg)
//
// THE D65 DISCOVERIES (raw disasm, 602 lines):
//   1. The lower_bound walks: key DWORD (WORD for
//      the salary map) at node+0x18 — NOT +3 as
//      the decompile's byte math suggested; isnil
//      @ +0x29; left/right @ +0/+0x10; the head's
//      +8 = the root. Result==head || key>target
//      -> the not-found iterator pair {cont, head}.
//   2. The vt+0x140 charge in type 3 carries
//      0x49 (73) — D64's was 0x43 — same six-arg
//      shape (dword code + byte 1 on stack).
//   3. MyLogSave 4318 fmt stages FIVE args —
//      REUSED seam g_fnGmNameLogSave (D64).
//   4. tq::TimeGet(3) drives a verbatim date
//      decomposition: days = sec/86400 (magic
//      0xd1b71759, shr 13); year = days + 0x76c;
//      rem = sec % 100; mid = (sec - days*10000)
//      / 100 (magic 0x51eb851f, shr 5) — fed to
//      the mail-content _snprintf(dst, 0xff, fmt,
//      year, mid, rem).
//   5. The mail struct (vt+0x118): actor@+0,
//      sender[0x10]@+4 (STR_SYSTEM_NAME), title
//      [0x20]@+0x24 (STR_LEAGUE_TITLE_ORDER_
//      SALARY, NO varargs) + manual NUL @ +0x43,
//      content[0xff]@+0x44 (3 date args) + manual
//      NUL @ +0x142, 0@+0x144/+0x148/+0x150, the
//      amount@+0x14c, 6@+0x154, 0 byte@+0x158.
//   6. The reply flag: single-shot (vt+0x508
//      true -> vt+0x500) = 1; the mail loop = 0 —
//      it rides the reply Init's PB+0xe.
//   7. Case 3 keeps esi = the FREE amount
//      (14174e980) — it never reloads esi for
//      the emoney loop count (verbatim quirk).
//
// LITERALS (verbatim, .rdata-verified):
//   "cq_config: type=%u ,contribution salary amount is not config" 0x141837c60
//   "cq_config: type=%u ,emoney salary amount is not config"       0x141837c28
//   "cq_config: type=%u ,free salary amount is not config"         0x141837bd0
//   "STR_TRAINING_GONGFU_EMONEY_NOT_ENOUGH" 0x141837848
//   "STR_SYSTEM_NAME"                       0x141837bc0
//   "STR_LEAGUE_TITLE_ORDER_SALARY"        0x141837ba0
//   "STR_LEAGUE_ORDER_SALARY_MAIL_CONTENT" 0x141837b78
//   "gmlog/emoney_buy"                     0x141830c38
//   "%lu\t%s\t%lu\t350\t4318\t%u\t%u\t1\t" 0x141837c08
//   the DBERROR code 0x249ff (all three config
//   errors); the mail color 0xffff00; the reply
//   ids 0xa3e / 0x13.
#ifndef SYNDICATE_LEAGUE_SALARY_H
#define SYNDICATE_LEAGUE_SALARY_H

#include <cstdint>

namespace syndicate {

// ---- seams ----
// log_InlineLogDBERROR(str, 0x249ff)
extern void (*g_fnSalaryDbError)(const char* pcMsg,
                                  uint32_t uCode);
// tq::TimeGet(mode) -> the raw seconds dword
extern uint32_t (*g_fnSalaryTimeGet)(uint32_t uMode);
// _invalid_parameter_noinfo
extern void (*g_fnSalaryInvalid)();
// tq::CStringPacker::~CStringPacker (the reply
// dtor — a seam here, CMsgCtors owns the ctor side)
extern void (*g_fnCStrPackerDtor)(void* pPacker);
// REUSED: g_fnGmNameLogSave (D64 — the
// gmlog/emoney_buy MyLogSave family, 5 varargs)
// REUSED: g_fnStringMgrInstance/GetStr,
// g_fnGetGameMgr, g_fn1417b4310's caller (D61)

// ---- the config getters (trivial dword reads)
uint32_t HostEmoneyPriceGet(void* pHost);   // +0x2fc
uint32_t HostContribCostGet(void* pHost);   // +0x2f8
uint32_t HostFreeAmountGet(void* pHost);    // +0x300
uint32_t HostContribAmountGet(void* pHost); // +0x304
uint32_t HostEmoneyAmountGet(void* pHost); // +0x308

// ---- the map lookups ----
uint32_t SalaryCountGet(void* pHost,
                        uint16_t uPos);     // 141768870
uint32_t SalaryAmountGet(void* pHost,
                        uint16_t uPos);     // 141768730
uint8_t  LeagueMemberPostGet(void* pEntity,
                             uint32_t uActor);  // 14174be40
void LeagueMemberPostSet(void* pEntity,
    uint32_t uActor, uint8_t uVal,
    uint8_t uFlush);                        // 14174bf70
uint64_t MemberRecPostGet(void* pRec);      // 141787de0
void MemberRecPostSet(void* pRec, uint32_t uVal,
                     uint8_t uFlush);       // 141787d80

// ---- the reply pair ----
void* ReplyInitCMsgLeagueOpt(void* pMsg,
    uint16_t uOpt, uint32_t uArg3,
    uint32_t uFlag, uint32_t uArg5);         // 1417d6790
void DtorCMsgLeagueOpt(void* pMsg);          // 1417d66c0

// ---------- FUN_1417b4310 @ 1417b4310 ----------
// (logic, actor, type) — the salary grant. Gates
// in the literal order:
//   1. mgr vt+0x278(mgr) != 0 -> bail (NO extra
//      arg — the D62-style gate inlined)
//   2. logic vt+0x510(logic, actor) -> the synId
//   3. MgrLeagueFind(host, synId) == 0 -> bail
//   4. LogRecMapFind(logic+0x18, actor):
//      hit -> 141787de0(rec) != 1 -> bail
//      miss -> 14174be40(entity, actor) != 1 -> bail
//   5. mgr vt+0x518(mgr, actor) -> the rank (edi)
//   6. esi = *(host+0x300) (the FREE amount)
//   type 2: e990<=0 -> DBERROR; cost(e970) >
//      vt+0x290(mgr,actor) -> bail; cost <= 0 ->
//      bail; vt+0x298(mgr, actor, -cost, byte 1);
//      esi = e990
//   type 3: !vt+0x248(mgr,actor) -> bail; e9a0<=0
//      -> DBERROR; price(e960)=0 -> bail; price >
//      vt+0x238(mgr,actor) -> STR_TRAINING_GONGFU_
//      EMONEY_NOT_ENOUGH via vt+0x28(mgr, actor,
//      str, 0xffff00) -> bail; vt+0x140(mgr, actor,
//      0, price, 0x49, 1) false -> bail; the
//      MyLogSave 4318 line; esi stays = the FREE
//      amount (quirk)
//   type not in {1,2,3} -> bail
//   7. esi <= 0 -> the free DBERROR -> bail
//   8. SalaryCountGet(host, rank) == 0 -> bail
//   9. vt+0x508(mgr, actor, cnt, esi, byte 1,
//      word 1) true -> vt+0x500(mgr, actor, cnt,
//      1, esi, byte 1); flag = 1
//      else esi mails: SalaryAmountGet(host, rank)
//      -> the mail (vt+0x118); flag = 0
//  10. the record flag: rec ? 141787d80(rec,2,1)
//      : 14174bf70(entity, actor, 2, 1)
//  11. the reply: CtorCMsgLeagueOpt ->
//      ReplyInitCMsgLeagueOpt(msg, 0x27, 0,
//      flag, 0) -> vt+0x8(mgr, actor, msg) ->
//      DtorCMsgLeagueOpt
void LeagueSalaryGrant(void* pLogic, uint32_t uActor,
                       int32_t nType);

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_SALARY_H

#pragma once
// ============================================================================
// SyndicateLeaguePlunderSignup.h — unit D78:
// CSyndicateLogic::SignUpPlunderWarFromClient
// (FUN_1417c2470, 600 lines) — the CLIENT entry for
// signing a league up into the plunder war. RAW-verified
// against the recovered original Syndicate.dll.
//
// ENTRY (RAW): param_1 = the logic ARRAY — param_1[1] is
// the vt object, param_1[10] is CLeagueMgr; param_4 = the
// target id array (nCount entries, 1..10); param_5 =
// the support/emoney flag; param_6 = the emoney count.
//
// FLOW (verbatim):
//  (1) the eight gates: uUser, 1<=n<=10, vt+0x278 == 0,
//      FUN_14174ebd0 == 0, vt+0x4a8 != 0, FUN_1417630d0
//      != 0, vt+0x568 != 0, FUN_141766a70 == false.
//  (2) the REAL MSVC std::vector<uint32_t> build: proxy =
//      OpNew(8) self-pointing; per target: == myLeague
//      (vt+0x3f0) -> FUN_14174e3f0 then the compose
//      myLeague*1e6 + target; else FUN_141766950; skip
//      zero + the member-key duplicate; push_back with
//      the capacity fast-path and FUN_14172d120 insert.
//      Empty -> delete vector+proxy -> return 0.
//  (3) the token: FUN_14174bac0(league, 0x65), retry
//      FUN_14174bbe0; both null -> cleanup + return 0.
//      id = FUN_1417d4ed0; row = FUN_141764870(mgr, id);
//      null -> the DB log (with the ORIGINAL source path)
//      -> cleanup + return 0.
//  (4) std::string ctor + FUN_1417b2570 (the sign text);
//      fail -> string dtor + cleanup + return 0.
//  (5) ppl = FUN_1417440d0(league); lVar18 = the row's
//      field-4 chain (vt+0x10 -> vt+0x58).
//  (6) NOT support: ppl < lVar18 -> the ceil path:
//      FUN_14174e940 < 1 -> out; pages =
//      ceil((lVar18-ppl)/cfg); the D71 RobOpt msg (ctor
//      1417d8390 + create(1, pages)); the vector walk
//      appending FUN_1417d8810(msg, id/1e6) with the
//      over-size break; count FUN_1417d8700 -> serialize
//      1417d8570 -> vt+8 send -> dtor -> cleanup ->
//      return 1. ppl >= lVar18 -> fall to the tails.
//  (7) support: param_6 == 0 -> the vt+0x28 talk
//      (STR_PLUNDER_WAR_TOKEN_USE_FAIL, 0xffff00) -> out;
//      vt+0x238(logic,user) < param_6 -> out;
//      lVar18 -= cfg*param_6; < 0 -> out; ppl < lVar18 ->
//      the token-fail talk; vt+0x140(logic,user,0,param_6)
//      (the emoney charge) fail -> the EMONEY_NOT_ENOUGH
//      talk; vt+0x200(logic,user); vt+0x1d8(logic,user)
//      -> name; tq::MyLogSave("gmlog/emoney_buy",
//      "%lu\t%s\t%lu\t350\t4238\t%u\t%u\t1\t", user,
//      name); the 0x200 buffer + memset(+0x21, 0, 0x1ff);
//      GetStr("STR_LEAGUE_NOTIFY_USER_PLUNDER_WAR_BY_
//      EMONEY") -> _snprintf(buf+0x20, 0x200, fmt);
//      vt+0x90(logic, buf+0x20, 0x7d5) the notify talk.
//  (8) the tails (both paths): FUN_141744130(league,
//      ppl-lVar18, 1); FUN_1417d4f30(token, 3, id+1, 0);
//      tq::TimeGet(1); FUN_1417d4f30(token, 4, time, 1);
//      memset(info, 0, 0x146); FUN_141745580(league,
//      info); FUN_141766b60(mgr, key, &idA, buf+0x10,
//      0x10); FUN_141766d10(mgr, key, &idB, buf, 0x10);
//      msg1: ctor 1417d6110 + FUN_1417b5370(logic,user,
//      league) + create 1417d61c0(msg, info, flag,
//      idB/1e6, idA/1e6, buf+0x10, buf); fail -> the
//      4-arg ERROR log (CONTINUES); ok -> vt+8 send;
//      msg2: ctor 1417d7350 + check 1417d73e0; ok ->
//      id + TimeGet + the row's field-3 chain (vt+0x10,
//      vt+0x50) + the expiry compose + create 1417d7770
//      (flag, id, expiry) + 1417d7440 + vt+8 send;
//      vt+0x560(logic); dtors 1417d73a0 + 1417d6160 +
//      string dtor; delete vector + proxy; return 1.
// ============================================================================
#include <cstdint>

namespace syndicate {

// ---- the gates / lookups ----
extern char     (*g_fnSupWarState)(void* pVtObj);              // vt+0x278
extern char     (*g_fnSplMgrGate)(void* pMgr);                 // FUN_14174ebd0
extern uint32_t (*g_fnSupUserLeague)(void* pVtObj,
                                     uint32_t uUser);  // vt+0x4a8 (the 2-arg view; D75's g_fnSplUserLeague is the same vt with the arg Ghidra dropped)
extern void*    (*g_fnSupFindLeague)(void* pMgr,
                                     uint32_t uId);            // FUN_1417630d0 (same raw as D75's g_fnSplFindLeague)
extern uint32_t (*g_fnSupMemberKey)(void* pVtObj, uint32_t uUser,
                                    uint32_t uLeague);         // vt+0x568 (the 3-arg view; D76's g_fnCqpMemberKey is the same vt)
extern char     (*g_fnSplAlreadySigned)(void* pMgr,
                                        uint32_t uKey);       // FUN_141766a70

// ---- the vector build ----
extern uint32_t (*g_fnSplMyTarget)(void* pMgr);                // FUN_14174e3f0
extern uint32_t (*g_fnSplResolveId)(void* pMgr,
                                    uint32_t uId);             // FUN_141766950
extern void*    (*g_fnSplVecInsert)(void* pVec, void* pIter,
                                    uint64_t n, void* pVal);   // FUN_14172d120

// ---- the token ----
extern void*    (*g_fnSplTokenAcquire)(void* pLeague,
                                       int32_t nType);         // FUN_14174bac0
extern void*    (*g_fnSplTokenRetry)(void* pLeague,
                                     int32_t nType);          // FUN_14174bbe0
extern uint32_t (*g_fnSplTokenId)(void* pToken);               // FUN_1417d4ed0
extern uint32_t (*g_fnSplTokenFlag)(void* pToken);             // FUN_1417d4e70
extern void     (*g_fnSplTokenSet)(void* pToken, int32_t nIdx,
                                   uint32_t uVal, char bArg); // FUN_1417d4f30
extern void*    (*g_fnSplTokenRow)(void* pMgr,
                                   uint32_t uId);              // FUN_141764870

// ---- the text / league ----
extern char     (*g_fnSplBuildText)(void* pLogic, uint32_t uUser,
    void* pLeague, void* pToken, void* pRow, void* pStr);      // FUN_1417b2570
extern void*    (*g_fnSplLeagueCount)(void* pLeague);          // FUN_1417440d0
extern void     (*g_fnSplLeagueAdd)(void* pLeague, int64_t n,
                                    char b);                   // FUN_141744130
extern void     (*g_fnSplLeagueInfo)(void* pLeague,
                                     void* pOut);              // FUN_141745580
extern void     (*g_fnSplGetNameA)(void* pMgr, uint32_t uKey,
    uint32_t* pOutId, char* pOut, int32_t nCap);               // FUN_141766b60
extern void     (*g_fnSplGetNameB)(void* pMgr, uint32_t uKey,
    uint32_t* pOutId, char* pOut, int32_t nCap);               // FUN_141766d10
extern int32_t  (*g_fnSplTargetCfg)(void* pMgr);               // FUN_14174e940
extern char     (*g_fnSupMsgAppend)(void* pMsg, int32_t nId); // FUN_1417d8810
extern int16_t  (*g_fnSupMsgCount)(void* pMsg);                // FUN_1417d8700

// ---- the talks / logs ----
extern void     (*g_fnSupTalk)(void* pVtObj, uint32_t uUser,
    const void* pStr, uint32_t uColor);                       // vt+0x28
extern uint32_t (*g_fnSplSupportCnt)(void* pVtObj,
                                     uint32_t uUser);         // vt+0x238
extern char     (*g_fnSplChargeEmoney)(void* pVtObj,
    uint32_t uUser, int32_t n0, uint32_t uCnt);                // vt+0x140
extern void     (*g_fnSplEmoneyPaid)(void* pVtObj,
                                     uint32_t uUser);         // vt+0x200
extern void*    (*g_fnSplUserName)(void* pVtObj,
                                   uint32_t uUser);           // vt+0x1d8
extern void     (*g_fnSupMyLogSave)(const char* pFile,
    const char* pFmt, uint64_t uUser, void* pName);           // tq::MyLogSave
extern void     (*g_fnSupSnprintf)(char* pDst, uint64_t n,
                                   const char* pFmt);         // _snprintf
extern void     (*g_fnSupNotifyTalk)(void* pVtObj, const char* pText,
                                     uint16_t uChannel);      // vt+0x90
extern uint32_t (*g_fnSupTimeGet)(int32_t n);                  // tq::TimeGet
extern void     (*g_fnSplDbLog)(const char* pFmt, uint64_t uId,
    const char* pPath, uint32_t uLine);                        // DBERROR log
extern void     (*g_fnSplInfoFailLog)(const char* pA, const char* pB,
    const char* pC, const char* pD);                           // ERROR log 4

// ---- the two NEW msg families ----
extern void     (*g_fnSplMsgInfoCtor)(void* pMsg);             // FUN_1417d6110
extern char     (*g_fnSplMsgInfoCreate)(void* pMsg, void* pInfo,
    uint32_t uFlag, uint32_t uA, uint32_t uB, const char* pN1,
    const char* pN2);                                          // FUN_1417d61c0
extern void     (*g_fnSplMsgInfoDtor)(void* pMsg);             // FUN_1417d6160
extern uint32_t (*g_fnSplAwardFlag)(void* pLogic, uint32_t uUser,
                                    void* pLeague);            // FUN_1417b5370
extern void     (*g_fnSplMsgStCtor)(void* pMsg);              // FUN_1417d7350
extern char     (*g_fnSplMsgStCheck)(void* pMsg);              // FUN_1417d73e0
extern char     (*g_fnSplMsgStCreate)(void* pMsg, uint8_t uFlag,
    uint8_t uId, uint64_t uExp);                               // FUN_1417d7770
extern void     (*g_fnSplMsgStFlush)(void* pMsg);              // FUN_1417d7440
extern void     (*g_fnSplMsgStDtor)(void* pMsg);               // FUN_1417d73a0
extern void     (*g_fnSplDbSave)(void* pVtObj);                // vt+0x560

// ---- the token row's field chains ----
extern void*    (*g_fnSplRowField)(void* pRow,
                                   int32_t nIdx);              // row vt+0x10
extern int64_t  (*g_fnSplRowValA)(void* pFieldObj);            // vt+0x58
extern int32_t  (*g_fnSplRowValB)(void* pFieldObj);            // vt+0x50

// ---- reused: the D71 RobOpt family (D74 seams), the
//      vector/pair OpNew/OpDelete (D70 kit), the name
//      getters (D70), vt+8 send (D75), vt+0x3f0 (kit),
//      the string manager (D66), _invalid (kit) ----

// the unit entry
int32_t SignUpPlunderWarFromClient(void** apLogic, uint32_t uUser,
    int32_t nCount, uint32_t* apTargets, char bSupport,
    uint32_t uParam6);

} // namespace syndicate

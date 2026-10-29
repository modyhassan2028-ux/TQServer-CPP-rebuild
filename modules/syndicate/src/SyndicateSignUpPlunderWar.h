#ifndef SYNDICATE_SIGN_UP_PLUNDER_WAR_H
#define SYNDICATE_SIGN_UP_PLUNDER_WAR_H
// ===== D78 — CSyndicateLogic::SignUpPlunderWarFromClient =====
// RAW: Syndicate.dll @1417c2470, 591 decompiled lines (v6159).
//
// Signature, verified against the RAW header:
//   uint FUN_1417c2470(longlong *param_1, uint uUser, uint nCount,
//                      longlong **pTargets, char bSupport, uint uParam6)
// param_1 is the logic array: param_1[1] = the vt object, param_1[10] = the
// CLeagueMgr. All vt calls below are `(**(code**)(*(longlong*)param_1[1] + N))()`.
//
// PHASE 1 — the gates, all verified from the RAW body:
//      uUser != 0, 1 <= nCount <= 10
//      vt+0x278 == 0                    (the war has not started)
//      14174ebd0(mgr) == 0
//      vt+0x4a8(uUser) != 0             -> the league id (uVar7)
//      1417630d0(mgr, league) != 0      -> lVar12
//      vt+0x568(uUser) != 0             -> the member key (local_1118)
//      141766a70(mgr, key) == false
// Every failure returns through the same tail with uVar6 zeroed.
//
// PHASE 2 — the target vector: operator_new(8) proxy holding a self pointer,
// then 14172d120 inserts. For each target (skip 0): if it equals
// vt+0x3f0() -> 14174e3f0(mgr) must be non-zero and differ from uVar7, then
// the id becomes 14174e3f0's result * 1000000 + target (the CONCAT44 in the RAW
// keeps the high half of the proxy pointer, i.e. only the low 32 bits matter);
// otherwise 141766950(mgr, id). Duplicates against the member key are dropped.
//
// PHASES 3-7 (token, sign-up string, the two page ceilings, the tails and the
// single cleanup path) are specced in Docs/D78_SIGNUP_PLUNDER_WAR_PLAN.md; the
// bodies land in SyndicateSignUpPlunderWar.cpp.
//
// The seam set below is the whole external surface. Signatures marked "plan"
// are taken from the analysis document and must be confirmed against the RAW
// while the phase that uses them is written.
#include <cstdint>
#include <cstddef>

namespace syndicate {

struct SSignUpPlunderSeams {
    // --- phase 1 gates -------------------------------------------------
    bool     (*WarNotStarted)(void* vt);              // vt+0x278
    uint32_t (*WarStartState)(void* mgr);             // 14174ebd0
    uint32_t (*LeagueOfUser)(void* vt, uint32_t uUser);   // vt+0x4a8
    void*    (*FindLeague)(void* mgr, uint32_t league);   // 1417630d0
    uint32_t (*MemberKey)(void* vt, uint32_t uUser);  // vt+0x568
    bool     (*IsKeyPending)(void* mgr, uint32_t key);    // 141766a70
    // --- phase 2 targets ----------------------------------------------
    uint32_t (*MyLeague)(void* vt);                   // vt+0x3f0
    uint32_t (*OwnLeagueId)(void* mgr);               // 14174e3f0
    uint32_t (*TargetLeagueId)(void* mgr, uint32_t id);   // 141766950
    void     (*VectorInsert)(void* vec, uint32_t value);  // 14172d120
    void*    (*OpNew)(size_t n);
    void     (*OpDelete)(void* p);
    // --- phase 3 token -------------------------------------------------
    void*    (*TokenQuery)(void* league, uint32_t type);      // 14174bac0
    void*    (*TokenReload)(void* league, uint32_t type);     // 14174bbe0
    uint32_t (*TokenId)(void* token);                          // 1417d4ed0
    void*    (*TokenTableRow)(void* mgr, uint32_t id);          // 141764870
    bool     (*SpendToken)(void* token, int a, uint32_t b, int c);  // 1417d4f30
    // --- phase 4/5 league side ----------------------------------------
    bool     (*BuildSignUpString)(void* logic, uint32_t user, void* league,
                                  void* token, void* row, void* str);  // 1417b2570
    uint32_t (*LeaguePopulation)(void* league);   // 1417440d0
    void     (*ApplyDelta)(void* league, long long delta, int flag);  // 141744130
    void     (*SetLeagueField)(void* league, void* value);            // 141745580
    uint32_t (*FreePages)(void* mgr);             // 14174e940
    // --- phase 6 message families --------------------------------------
    void*    (*NewMsgA)(void* mem);               // 1417d8390 ctor
    void     (*MsgACreate)(void* msg, int a, uint32_t pages);   // 1417d8570 family
    void     (*MsgAAppend)(void* msg, uint32_t id);             // 1417d8810
    uint32_t (*MsgACount)(void* msg);             // 1417d8700
    void     (*MsgASerialize)(void* msg);         // 1417d8570
    void     (*GetKeyName)(void* mgr, uint32_t key, char* out, size_t cap);  // 141766b60
    void     (*GetLeagueName)(void* mgr, uint32_t id, char* out, size_t cap); // 141766d10
    void     (*FormatLine)(char* buf, size_t cap, const char* fmt);  // IStringManager
    void     (*LogDb)(const char* fmt);           // log_InlineLogERROR
};


// ---------------------------------------------------------------------------
// Phase 2 helper — id composition, verbatim from the RAW loop body:
//   uVar9 = target; if (vt+0x3f0() == target) { own = 14174e3f0(mgr);
//       if (own == 0 || own == league) skip;  id = vt+0x3f0()*1000000 + own; }
//   else id = 141766950(mgr, target);
//   insert only when id != 0 && id != memberKey.
// ---------------------------------------------------------------------------
struct STargetIdResult {
    uint32_t id;       // 0 means "do not insert"
    bool     insert;
};

STargetIdResult ComposeTargetId(void* mgr, uint32_t target, uint32_t myLeague,
                                uint32_t userLeague, uint32_t memberKey,
                                SSignUpPlunderSeams& s);

// ---------------------------------------------------------------------------
// Phase 5 helper — the RobOpt page message, verbatim:
//   pages = (int)(long long)ceil((double)(cap - current) / (double)freePages);
//   ctor 1417d8390; create(1, pages) false -> destroy + fail;
//   for each id: append(id / 1000000) — the league part of the composed id —
//   a false append logs "... msg over size" and breaks;
//   count (short) != 0 -> serialize then send through vt+0x8;
//   destroy through 1417d83e0 and report success (the RAW returns 1 here).
// ---------------------------------------------------------------------------
struct SRobOptSeams {
    void*  (*MsgNew)();                                   // 1417d8390 ctor
    bool   (*MsgCreate)(void* msg, int a, int pages);     // 1417d84d0
    void   (*MsgDestroy)(void* msg);                      // 1417d83e0
    bool   (*MsgAppend)(void* msg, int value);            // 1417d8810
    int16_t(*MsgCount)(void* msg);                        // 1417d8700
    void   (*MsgSerialize)(void* msg);                    // 1417d8570
    void   (*SendToClient)(void* vt, uint32_t user, void* msg);  // vt+0x8
    void   (*Log)(const char* text);                      // log_InlineLogERROR
};

// freePages < 1 makes the RAW clean up and fail before any message exists.
bool SendRobOptPages(SRobOptSeams& s, void* vt, uint32_t user,
                     int64_t current, int64_t cap, uint32_t freePages,
                     const uint32_t* ids, size_t nIds);


// ---------------------------------------------------------------------------
// The function itself — phases 1 to 5 (gates, target vector, token, sign-up
// string, the two ceilings and the param_5 / param_6 checks).
// Phase 6-7 (the two new message families and the tail block) still needs the
// register-passed arguments of vt+0x560 and 1417d73a0 resolved from the
// assembly, so it stays behind FinishTails and is documented as pending.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Phases 6-7 — the tails, now resolved from the assembly at 1417c2f00..1417c31fd.
// The decompiler never showed these arguments; the disassembly does:
//   141744130(league, current - cap, 1)
//   1417d4f30(token, 3, 1417d4ed0(token) + 1, 0)
//   1417d4f30(token, 4, TimeGet(1), 1)
//   memset(leagueBlob, 0, 0x146); 141745580(league, leagueBlob)
//   141766b60(mgr, key, &idA, nameA, 0x10)     <- both lookups take the KEY
//   141766d10(mgr, key, &idB, nameB, 0x10)
//   1417d6110(&msgA); award = 1417b5370(logic, user, league);
//   1417d61c0(&msgA, leagueBlob, award, idA/1000000, idB/1000000, nameA, nameB)
//       false -> LogDb at line 0x2685, true -> vt+8(vt, user, &msgA)
//   1417d7350(&msgB); if (1417d73e0(&msgB)) {
//       tid4 = 1417d4ed0(token, 4); now = TimeGet(1);
//       page = (vt+0x10)(vt, 3) then +0x50;
//       delay = 0; if (page + tid4 > now) delay = page - now + tid4;
//       tid3 = 1417d4ed0(token, 3);
//       if (1417d7770(&msgB, 1417d4e70(token), (uint8_t)tid3, delay)) {
//          1417d7440(&msgB); vt+8(vt, user, &msgB); } }
//   vt+0x560(vt, 1, key, &strA)      <- four arguments, key in r8
//   1417d73a0(&msgB)                 <- ONE argument, the rest was decompiler noise
//   1417d6160(&msgA); return 1
// ---------------------------------------------------------------------------
struct SLogicSeams;

struct STailSeams {
    uint32_t (*TimeGetSec)();                          // tq::TimeGet(1)
    uint32_t (*TokenIdIdx)(void* token, int idx);      // 1417d4ed0(token, idx)
    uint32_t (*TokenField)(void* token);               // 1417d4e70
    uint32_t (*AwardFlag)(void* logic, uint32_t user, void* league);  // 1417b5370
    void     (*GetKeyName)(void* mgr, uint32_t key, uint32_t* outId, char* name, size_t cap);
    void     (*GetLeagueName)(void* mgr, uint32_t key, uint32_t* outId, char* name, size_t cap);
    void*    (*MsgANew)();                             // 1417d6110
    bool     (*MsgACreate)(void* msg, void* leagueBlob, uint32_t award,
                           uint32_t a, uint32_t b, const char* nameA, const char* nameB);
    void     (*MsgADestroy)(void* msg);                // 1417d6160
    void*    (*MsgBNew)();                             // 1417d7350
    bool     (*MsgBReady)(void* msg);                  // 1417d73e0
    bool     (*MsgBFill)(void* msg, uint32_t field, uint8_t id, uint32_t delay);  // 1417d7770
    void     (*MsgBSerialize)(void* msg);              // 1417d7440
    void     (*MsgBDestroy)(void* msg);                // 1417d73a0, one argument
    int64_t  (*PageCapFor)(void* vt, int idx);         // (vt+0x10)(vt,idx) then +0x50
    void     (*Vt0560)(void* vt, int a, uint32_t key, void* strOut);  // vt+0x560
    void     (*LogDb)(const char* text);               // the IF_OK line
};

uint32_t RunTails(void* logic, uint32_t user, void* vt, void* mgr, void* league,
                  void* token, uint32_t key, int64_t current, int64_t cap,
                  SLogicSeams& s);

struct SLogicSeams {
    SSignUpPlunderSeams core;      // gates, vector, token, league side
    SRobOptSeams        robOpt;    // the phase-5 page message
    // --- vt gates and notifications ------------------------------------
    bool     (*WarGateBlocks)(void* vt);                      // vt+0x278
    uint32_t (*SpendablePage)(void* vt, uint32_t user);        // vt+0x238
    bool     (*SpendMoney)(void* vt, uint32_t user, int a, uint32_t amount);  // vt+0x140
    void     (*NotifyTokenFail)(void* vt, uint32_t user);      // STR_PLUNDER_WAR_TOKEN_USE_FAIL
    void     (*NotifyNoMoney)(void* vt, uint32_t user);        // STR_TRAINING_GONGFU_EMONEY_NOT_ENOUGH
    void     (*EmoneyBuyTail)(void* vt, uint32_t user);        // 0x200 + MyLogSave + i18n + 0x90
    int64_t  (*TargetCap)(void* vt);                           // (vt+0x10)->+0x58
    STailSeams tails;              // phases 6 and 7
};

uint32_t SignUpPlunderWarFromClient(void* logic, uint32_t uUser, uint32_t nCount,
                                    const uint32_t* targets, char bSupport,
                                    uint32_t uParam6, SLogicSeams& s);

} // namespace syndicate
#endif

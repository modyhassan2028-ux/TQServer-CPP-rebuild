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

} // namespace syndicate
#endif

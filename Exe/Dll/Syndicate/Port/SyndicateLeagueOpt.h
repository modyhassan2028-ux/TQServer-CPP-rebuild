// SyndicateLeagueOpt.h — D61: syndicate::
// CMsgLeagueOpt::Process — the league options
// dispatcher (45+ opt types) + the gate and the
// 12 fully-visible thin wrappers it drives.
//
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_1417d68d0 @ 1417d68d0 — the Process
//   FUN_1417ac700 @ 1417ac700 — the gate (a
//          3-instr vt forwarder: slot +0x278 on
//          the object at logic+8; the decompile
//          index garbles it as jumptable-FAIL)
//   FUN_1417b0db0/b0de0/b0e00/b0e20/b0e50/
//          b0e70/b1660/b1690 — acct-forward
//          wrappers (null gates + logic+0x50)
//   FUN_1417b15b0 / b14c0 — the concubine
//          flows (literal STR_LEAGUE_CONCUBINES_*
//          strings + the 0xffff00 vt+0x28 send)
//   FUN_1417b1980 / b1a40 — session-map check +
//          token flows
//   FUN_1417bf4d0 — the 0x67/0xcd/0xce tri-switch
//
// SEAMS (documented TBD, ported in later units):
//   the deep league bodies 1417b0a40 (name
//   apply, 122), 1417b19c0, 1417b4310 (237),
//   1417b98e0 (97), 1417b03b0 (116), 1417b0680
//   (61), 1417b48b0 (112), 1417b4d60 (154),
//   1417b0ea0, 1417b3300, 1417bed70, 1417b3a90
//   the acct layer 14174ed50/d80/da0/dc0/e00/
//          e20/e40/e70/e90/ec0/e3f0
//   the session layer 14176e600/14176ea30/
//          141767560
//   tq::CStringPacker::GetString / GetStrAmount
//          (the +0x410 packer on the CMsg)
//   IStringManager theInstance + its slot-0 fetch
//   log_InlineLogERROR (the m_pInfo CHECK log)
//
// LITERALS (verbatim, see PORTING_LOG D61):
//   "f:\\version\\cqserver-78.0.11-1204\\modules"
//   "\\syndicate\\src\\msg\\msgleagueopt.cpp"
//   "STR_LEAGUE_CONCUBINES_FAIL"
//   "STR_LEAGUE_CONCUBINES_USER_OFFLINE"
//   "STR_LEAGUE_OTHER_LEAGUE_USER"
#ifndef SYNDICATE_LEAGUE_OPT_H
#define SYNDICATE_LEAGUE_OPT_H

#include <cstdint>

namespace syndicate {

// ---- the image base (verbatim arg to the
// 1417b19c0/b0de0/b0e00/b0e50/b0e70 calls:
// &IMAGE_DOS_HEADER_141720000) ----
constexpr uint64_t kImageBase = 0x141720000ull;

// ---- seams: the deep league bodies ----
extern uint64_t (*g_fn1417b0a40)(void*, uint32_t,
    uint32_t, char*);            // name apply
extern void (*g_fn1417b19c0)(void*, uint32_t,
    char, void*);                // case 9
extern void (*g_fn1417b4310)(void*, uint32_t,
    int32_t);                    // case 0x27
extern void (*g_fn1417b98e0)(void*, uint32_t);  // 0x2e
extern char (*g_fn1417b03b0)(void*, uint32_t,
    uint32_t, char*);            // case 0x33
extern void (*g_fn1417b0680)(void*, uint32_t,
    char*, uint64_t);            // case 0x42
extern void (*g_fn1417b48b0)(void*, uint32_t,
    uint32_t, bool, bool);       // 0x4a/0x4c
extern void (*g_fn1417b4d60)(void*, uint32_t,
    uint32_t, bool, bool);       // 0x4b/0x4d
extern void (*g_fn1417b0ea0)(void*, uint32_t,
    char);                       // b1980/b1a40 tail
extern void (*g_fn1417b3300)(void*, uint32_t,
    bool, uint64_t);             // bf4d0 0x67
extern void (*g_fn1417bed70)(void*, uint32_t,
    bool, uint64_t);             // bf4d0 0xcd
extern void (*g_fn1417b3a90)(void*, uint32_t,
    bool, uint64_t);             // bf4d0 0xce

// ---- seams: the acct layer (logic+0x50) ----
extern void (*g_fn14174ed50)(void*, int32_t,
    char*, uint32_t, uint16_t);
extern void (*g_fn14174ed80)(void*, int32_t,
    uint32_t, void*);
extern void (*g_fn14174eda0)(void*, uint32_t,
    char, void*);
extern void (*g_fn14174edc0)(void*, int32_t,
    char*, uint16_t, uint32_t, uint16_t);
extern void (*g_fn14174ee00)(void*, int32_t,
    uint32_t, void*);
extern void (*g_fn14174ee20)(void*, uint32_t,
    char, void*);
extern void (*g_fn14174ee40)(void*, int32_t,
    int32_t, uint16_t, uint32_t, int32_t);
extern void (*g_fn14174ee70)(void*, int32_t,
    int32_t, int16_t);
extern void (*g_fn14174ee90)(void*, uint32_t,
    uint32_t, uint16_t, uint32_t, uint16_t);
extern void (*g_fn14174eec0)(void*, int32_t,
    uint32_t, char*);
extern int32_t (*g_fn14174e3f0)(void*);

// ---- seams: the session layer (logic[10]) ----
extern uint64_t (*g_fn14176e600)(void*, uint32_t,
    uint32_t);
extern uint64_t (*g_fn14176ea30)(void*, uint32_t,
    uint32_t, uint32_t);
extern void (*g_fn141767560)(void*, uint32_t,
    uint32_t, uint64_t);

// ---- seams: the +0x410 string packer ----
extern bool (*g_fnCStrPackerGetString)(void*,
    int32_t, char*, int32_t);
extern uint32_t (*g_fnCStrPackerGetStrAmount)(void*);

// ---- seams: the string manager + the log ----
extern void* (*g_fnStringMgrInstance)();
extern void* (*g_fnStringMgrGetStr)(void*,
    const char*);
extern void (*g_fnLeagueOptLogError)(void*,
    const char*, const char*, const char*);

// ---- the bodies ----
char LeagueOptGate(void* pLogic);      // 1417ac700
void LeagueOptProcess(void* pMsg,
                      uint32_t uIdActor);  // 1417d68d0
void Fn1417b0db0(void* pLogic, int32_t nActor,
    char* psz, uint32_t u4, uint16_t u6);
void Fn1417b0de0(void* pLogic, int32_t nActor,
    uint32_t u3, void* p4);
void Fn1417b0e00(void* pLogic, uint32_t uActor,
    uint64_t u3, void* p4);
void Fn1417b0e20(void* pLogic, int32_t nActor,
    char* psz, uint16_t u4, uint32_t u5,
    uint16_t u6);
void Fn1417b0e50(void* pLogic, int32_t nActor,
    uint32_t u3, void* p4);
void Fn1417b0e70(void* pLogic, uint32_t uActor,
    uint64_t u3, void* p4);
void Fn1417b15b0(void* pLogic, int32_t nActor,
    int32_t n3, int16_t n4);
void Fn1417b14c0(void* pLogic, int32_t nActor,
    void* p3, uint16_t u4, uint32_t u5,
    int32_t n6);
void Fn1417b1660(void* pLogic, uint32_t uActor,
    uint32_t u3, uint16_t u4, uint32_t u5,
    uint16_t u6);
void Fn1417b1690(void* pLogic, int32_t nActor,
    uint32_t u3);
void Fn1417b1980(void* pLogic, uint32_t uActor,
    uint32_t u3);
void Fn1417b1a40(void* pLogic, int32_t nActor,
    uint32_t u3);
void Fn1417bf4d0(void* pLogic, uint32_t uActor,
    int16_t n3, char c4, uint32_t u5);

}  // namespace syndicate

#endif  // SYNDICATE_LEAGUE_OPT_H

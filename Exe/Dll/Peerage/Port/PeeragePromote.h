// ============================================================
// Peerage.dll port — unit T4/D20: the promotion state
// machine (FUN_141555f80: the sort + the rank walk + the
// state families + the erase family), the packet senders
// (FUN_1415529c0 / FUN_141552a60), the msg build
// (FUN_1415574a0), and the elem cleanup (FUN_141552110).
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

struct CPeerageSortMgr;

// ---- the db seams (mgr+0x40 vtable calls) ----
// vt+0x38: (db, id, msg) — the rank-change send
extern void (*g_fnDbSendRank)(void* db, uint32_t id,
                              void* msg);
// vt+0x40: (db, buf, 0xff0000, uType) — the announce
extern void (*g_fnDbAnnounce)(void* db,
                              const char* buf,
                              uint32_t color,
                              uint16_t type);
// vt+0x48: (db, id, msg) — the announce msg send
extern void (*g_fnDbSendAnnounce)(void* db,
                                  uint32_t id,
                                  void* msg);
// vt+0x50: (db, id) -> gender (1 = male)
extern int (*g_fnDbGetGender)(void* db, uint32_t id);
// vt+0x68: (db, id) — the touch call
extern void (*g_fnDbTouch)(void* db, uint32_t id);
// vt+0x70: (db) -> announce enabled
extern bool (*g_fnDbAnnounceEnabled)(void* db);

// ---- the msg seams ----
// the msg vt+0x48: (msg, str) -> bool (the string
// append; 1415574a0 returns its result)
extern bool (*g_fnMsgAppend)(void* msg, char* str);

// ---- the string manager seam (theInstance()) ----
// theInstance() -> the string manager
extern void* (*g_fnTheInstance)();
// GetString(pMgr, "STR_...") -> the prompt text
extern const char* (*g_fnStrMgrGet)(void* pStrMgr,
                                    const char* key);

// ---- TBD-4A0-ARG4: the 4th %d argument of the
// 1415574a0 build _snprintf. Ghidra drops the varargs;
// the 4th is NOT visible in the decompile (only 3
// locals: state3, rank4, value5). Seam until the
// binary is inspected.
extern int (*g_fnBuildArg4)();

// ---- the object vtable seams ----
// the row vt+0x40 release: (row, 0, dbVt, pStr, -2)
extern void (*g_fnRowVt40Release)(void* row, int a,
                                  void* dbVt,
                                  void* pStr,
                                  int64_t e);
// the row's own vt[0] deleting dtor: (row, 1)
extern void (*g_fnRowDelete)(void* row, uint64_t f);
// the elem's own vt[0] deleting dtor: (elem, 1)
extern void (*g_fnElemDelete)(void* elem,
                              uint64_t f);

// ---- FUN_1415574a0: the 0x810 msg build ----
// (msg, id, state3, rank4, value5) — header {0xa8,
// 0x810, 3, id} at msg+8 then the "%u %I64u %u %d"
// append; returns the append result
bool BuildMsgPeerage(void* msg, uint32_t id,
                     uint32_t state, uint32_t rank,
                     int64_t value);

// ---- FUN_1415529c0: the rank-change packet ----
// (mgr, id, state, rank, value)
void SendRankChange(CPeerageSortMgr* mgr,
                    uint32_t id, uint32_t state,
                    uint32_t rank, int64_t value);

// ---- FUN_141552a60: the announce + packet ----
// (mgr, id, newState, pStrQword, oldRank,
//  bOldLessNew, value)
void SendPeerageAnnounce(CPeerageSortMgr* mgr,
                         uint32_t id,
                         uint32_t newState,
                         void* pStrQword,
                         uint32_t oldRank,
                         bool bOldLessNew,
                         int64_t value);

// ---- FUN_141552110: the elem cleanup ----
// (elem, id, dbVt, pStr1c)
void PeerageElemCleanup(void* elem, uint64_t id,
                        void* dbVt, void* pStr);

// the msg buffer = 0x430 on the caller stack
// (the object is 0x410 + the packer 0x18, rounded)
struct SMsgBuf {
    uint8_t m_ab[0x430];
};

// ---- FUN_141552980: the state-from-value thresholds
// (verbatim: 199999999 < x -> 5; 99999999 < x -> 3;
// else (uint)(29999999 < x))
uint32_t StateFromValue(int64_t v);

// ---- FUN_141555f80: the promotion walk ----
// (mgr, bNoSend param_2, id param_3) — FindById
// gate + the D19 sort + the rank/state families + the
// erase family at counter == mgr+0x48
void PeeragePromoteWalk(CPeerageSortMgr* pMgr,
                        char bNoSend, int nId);

} // namespace peerage

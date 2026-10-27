// ============================================================
// Peerage.dll port — unit T7/D23: the donation family.
// Addresses verbatim: 141551750 (svc rank wrapper),
// 141551760 (svc sweep wrapper), 141551770 (svc send-state
// wrapper), 141551780 (the donate entry: level 0x46 gate,
// the 3000000 underline gate, the 1000000000 overflow
// gate, the money-type switch with the /50000 divisions
// and the vt+0x88 invalid-type path), 141554c40 (the rank
// getter: elem+0x10 or the db-total thresholds), 141554b10
// (the state send: the 4a0 build with the elem fields or
// the db fallback), 1415558a0 (the sweep-and-delete: the
// mgr vector walk, row id match, 141552110 cleanup, elem
// deleting dtor, memmove_s shrink), 141555dc0 (the
// get-or-create: the dyna_rank_rec query with the
// 0x2dc6c3 constant, 141552340 ctor, 141552170 underline,
// push_back), 1415520c0 (the name-pair setter), 141556db0
// (the core: db total get/set, the mgr+0x38 / rankNum
// gates, the old/new rank compare + the 141552a60
// announce, the type-1 141557350 sends, the inline strcmp
// with 1415520c0 refresh, the 141555f80 walk, the
// gmlog/peerage_donate log).
// The original Peerage.dll binary is NOT available: the
// Ghidra-dropped arguments are handled with TBD seams
// documented below.
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

struct CPeerageService;   // PeerageModule.h (0x18)
struct CPeerageSortMgr;    // PeerageSortMgr.h (0x50)
struct CPeerageSort;       // PeerageSortMgr.h (0x30)

// ---- service(+0x08) kernel seams (the attached kernel
// object; all vt calls of 141551780) ----
// vt[0]: () -> uint — the donor level (0x46 = 70 gate).
// TBD-1780-ARG1: the decompile shows NO argument on this
// call; the donating id is plausibly a dropped arg. The
// seam mirrors the visible call shape and takes the id
// anyway so tests can drive it — flagged, NOT guessed.
extern uint32_t (*g_fnSvcGetLevel)(void* pKernel,
                                   uint32_t id);
// vt+0x08: () -> char — the money-type gate (0 -> the
// silent return). Same TBD-ARG1 caveat.
extern char (*g_fnSvcTypeGate)(void* pKernel,
                               uint32_t id);
// vt+0x10: (kernel, id, money) -> charged
extern char (*g_fnSvcCharge10)(void* pKernel,
                               uint32_t id,
                               int64_t nMoney);
// vt+0x18: (kernel, id, money/50000) -> charged
extern char (*g_fnSvcCharge18)(void* pKernel,
                               uint32_t id,
                               int64_t nMoney);
// vt+0x20: (kernel, id, money/50000) -> charged
extern char (*g_fnSvcCharge20)(void* pKernel,
                               uint32_t id,
                               int64_t nMoney);
// vt+0x30: (kernel, id, str, 0xff0000, 0x7d5)
extern void (*g_fnSvcSendStr)(void* pKernel,
                              uint32_t id,
                              const char* pStr,
                              uint32_t uColor,
                              uint32_t uChannel);
// vt+0x88: (kernel, id, 0x3c) — the invalid money type
extern void (*g_fnSvcSend88)(void* pKernel, uint32_t id,
                             uint32_t uA3);

// ---- db (mgr+0x40) seams new in D23 ----
// vt+0x28: (db, id) -> the 16-byte name pair (also the
// announce pair; the inline strcmp in 141556db0 reads it
// as chars)
extern void* (*g_fnDbGetNamePair)(void* pDb,
                                  uint32_t id);
// vt+0x58: (db, id) -> the donated total.
// TBD-6DB0-ARG: the 141556db0 call shows NO args (the id
// dropped); 141554b10 passes (db, id) explicitly — one
// seam, both call sites.
extern int64_t (*g_fnDbGetDonated)(void* pDb,
                                   uint32_t id);
// vt+0x60: (db, id, total)
extern void (*g_fnDbSetDonated)(void* pDb,
                                uint32_t id,
                                int64_t nTotal);
// vt+0x80: (db, id) -> the underline value
extern uint32_t (*g_fnDbGetUnderline)(void* pDb,
                                      uint32_t id);

// ---- elem/row seams (141556db0 / 141555dc0) ----
// elem+8 row vt+0x10: (row, n) -> the field record —
// REUSED from PeerageSort.h: g_fnRowQuery2; the row id
// match reuses g_fnRowGetId; the 141554b10 record value
// reuses g_fnRowGetValue
// rec vt+0xa0: (rec, total) — the set
extern void (*g_fnRecSetTotalA0)(void* pRec,
                                 int64_t nTotal);
// rec vt+0xa0: (rec) -> total — TBD-A0-ARG: the LAB call
// in 141556db0 shows NO arg (dropped)
extern int64_t (*g_fnRecGetTotalA0)(void* pRec);
// row vt+0x38: (row, 0) / (row) — TBD-38-ARG: the second
// call shows NO arg (dropped)
extern void (*g_fnRowVt38)(void* pRow, int n);

// ---- 141555dc0 query seams (InstanceGet + the
// "dyna_rank_rec" query object) ----
extern void* (*g_fnInstanceGet)();
// obj vt+0x20: (obj, "dyna_rank_rec") -> the query
extern void* (*g_fnQryGetTab)(void* pObj,
                              const char* pTab);
// q vt+0x10: (q, n) -> the field n
extern void* (*g_fnQryField)(void* pQry, int n);
// field vt+0xb8: (field, value)
extern void (*g_fnFieldSetB8)(void* pField,
                              int64_t nVal);
// field vt+0xb0: (field, 0)
extern void (*g_fnFieldSetB0)(void* pField,
                              int64_t nVal);
// q vt+0x50: (q, 1) -> bool
extern bool (*g_fnQryExec)(void* pQry, int n);
// q vt[0]: (q, 1) — the deleting dtor
extern void (*g_fnQryDestroy)(void* pQry,
                              uint64_t uFlags);

// ---- tq::MyLogSave (141556db0 tail) ----
// ("gmlog/peerage_donate", "player:%u, donate money:%I64d,
//  donate money type %d", id, money, type).
// TBD-6DB0-ARG3: the 3rd vararg (the money TYPE) is
// dropped by Ghidra — only 2 args visible.
extern void (*g_fnMyLogSave)(const char* pFile,
                             const char* pFmt,
                             uint32_t id,
                             int64_t nMoney,
                             int nType);

// ---- FUN_141551750: (svc, id) -> 141554c40(svc+0x10)
void ServiceGetRank(CPeerageService* pSvc, int nId);
// ---- FUN_141551760: (svc, id, a, b) ->
// 1415558a0(svc+0x10)
void ServiceSweepDelete(CPeerageService* pSvc, int nId,
                        char* pA, char* pB);
// ---- FUN_141551770: (svc, id) -> 141554b10(svc+0x10)
void ServiceSendState(CPeerageService* pSvc, int nId);
// ---- FUN_141551780: the donate entry
void ServiceDonate(CPeerageService* pSvc, uint32_t id,
                   int64_t nMoney, int nType);
// ---- FUN_141554c40: the rank getter
uint32_t GetPeerageRank(CPeerageSortMgr* pMgr, int nId);
// ---- FUN_141554b10: the state send
void SendPeerageState(CPeerageSortMgr* pMgr, int nId);
// ---- FUN_1415558a0: the sweep-and-delete
void SweepDeleteById(CPeerageSortMgr* pMgr, int nId,
                     char* pA, char* pB);
// ---- FUN_141555dc0: the get-or-create
void* GetOrCreateSort(CPeerageSortMgr* pMgr,
                      uint32_t id);
// ---- FUN_1415520c0: the name-pair setter
// (null -> log; obj+0x1c = pair[0], obj+0x24 = pair[1],
//  obj+0x2b = 0)
void SetNamePair(CPeerageSort* pObj, uint64_t* puPair);
// ---- FUN_141556db0: the donate core
void DonateCore(CPeerageSortMgr* pMgr, uint32_t id,
                int64_t nMoney);

} // namespace peerage

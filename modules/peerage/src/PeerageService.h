// ============================================================
// Peerage.dll port — unit T8/D24: the remaining
// service functions + the rank lookup helpers.
// Addresses verbatim: 141551920 (the rank query +
// send), 141551a00 (the donate-info pair query), 141551b00
// (the state send), 141551b90 (the vector operator[]),
// 141551bf0 (the service scalar deleting dtor), 141551c20
// (the top-list page send), 141551eb0 (the 6-rank query +
// type-4 send), 1415549d0 (find by rank, backward), 141555070
// (the first-below-threshold count), 141552a50 (mgr+8).
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

struct CPeerageService;   // PeerageModule.h
struct CPeerageSortMgr;   // PeerageSortMgr.h

// ---- the new seams (the service+8 kernel slots) ----
// vt+0x58: (kernel, id) -> the donated total.
extern int64_t (*g_fnSvcGetDonated)(void*, uint32_t);
// vt+0x38: (kernel, id, msg) — the rank packet send
extern void (*g_fnSvcSendMsg)(void*, uint32_t, void*);
// vt+0x70: (kernel, id) -> the player visible gate
extern char (*g_fnSvcIsVisible)(void*, uint32_t);
// vt+0x78: (kernel, id) -> the online value
extern uint32_t (*g_fnSvcGetVt78)(void*, uint32_t);

// ---- FUN_141551920: the elem/total rank query + the
// 0x810 type-3 send (elem null -> StateFromValue(total))
void ServiceQueryRank(CPeerageService* pSvc,
                      uint32_t uId);
// ---- FUN_141551a00: (svc, id, rank, out) -> the pair
// {value, count}. Gate: rank < 0xd && elem null or
// elem rank < rank. out = the count (or -1), value =
// 3M floor of by-rank value - total + 1. Returns 0 when
// the gate fails.
int64_t ServiceDonateInfo(CPeerageService* pSvc,
                          uint32_t uId, uint32_t uRank,
                          uint32_t* puOut);
// ---- FUN_141551b00: build (id, state, 0, 0) + send
void ServiceSendState(CPeerageService* pSvc,
                      uint32_t uId, uint32_t uState);
// ---- FUN_141551b90: operator[] on the SPtrVec-shaped
// object (begin +0x18, end +0x20) — the bounds check
// fires _invalid_parameter
void* VecSlotAt(void* pVec, uint64_t uIdx);
// ---- FUN_141551bf0: DtorPeerageService + the
// delete-if-odd scalar dtor
CPeerageService* ServiceScalarDeletingDtor(
    CPeerageService* pSvc, uint64_t uFlags,
    uint64_t uA, uint64_t uB);
// ---- FUN_141551c20: the top-list page (type-2 build
// with (end-begin)/10 capped, 10 per page, the 0x30
// record append per elem, the send UNCONDITIONAL)
void ServiceSendTopList(CPeerageService* pSvc,
                         uint32_t uId, uint16_t uPage);
// ---- FUN_141551eb0: the 6 ranks {1,3,5,7,9,0xc} pair
// query (the service vt+0x28 = 141551a00) into a 6x16
// array + the type-4 memcpy 0x60 send
void ServiceQueryAllRanks(CPeerageService* pSvc,
                          uint32_t uId);
// ---- FUN_1415549d0: the BACKWARD walk (elem+0x10 ==
// rank) with the +0x18/+0x20 debug checks
void* FindSortByRank(CPeerageSortMgr* pMgr,
                     uint32_t uRank);
// ---- FUN_141555070: forward walk; the FIRST elem with
// the row value < threshold returns elem+0x14; the tail
// returns 0xffffffff
uint32_t CountBelowThreshold(CPeerageSortMgr* pMgr,
                             int64_t nThreshold);

} // namespace peerage

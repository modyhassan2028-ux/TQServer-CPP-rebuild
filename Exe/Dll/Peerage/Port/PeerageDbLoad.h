// ============================================================
// Peerage.dll port — unit T5/D21: the DB load
// (FUN_1415569f0): rank_num query -> mgr+0x48, the
// dyna_rank_rec row scan (the empty-name skip, the
// CPeerageSort ctor 141552340 per row, the id
// translate via the dbobj vt+0x80, the sort key set
// 141552170, the push_back 141555cb0), then the final
// walk call FUN_141555f80(mgr, 1, 0).
// Caller: FUN_1415516a0 (the service Attach — D17's
// g_fnPeerageObjInit seam).
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

struct CPeerageSortMgr;

// ---- the seams ----
// theInstance/InstanceGet: () -> the DB instance
// (its vtable carries the query slots)
extern void* (*g_fnDbInstanceGet)();

// the SQL literals (PTR_14155f140 / PTR_14155f138)
extern const char* g_szDbQueryRankNum;
//   "SELECT rank_num FROM dyna_rank_t"
extern const char* g_szDbQueryDynaRec;
//   "SELECT dyna_rank_rec_..._FROM cq_user"

// FUN_1415569f0: (mgr, db) -> the low RAX byte is the
// bool result (the error paths mask AL to 0; the
// success path forces AL=1 after the walk)
uint64_t PeerageDbLoad(CPeerageSortMgr* pMgr, void* pDb);

} // namespace peerage

#pragma once
// ============================================================================
// SyndicateLeaguePlunderQuery.h — unit D76:
// CLeagueMgr::ClientQueryPlunderWarInfo — FUN_141766e90,
// RAW-verified against the recovered v6159 Syndicate.dll.
// The name is preserved by the log literal
// "CLeagueMgr::ClientQueryPlunderWarInfo msg over size".
//
// Signature: (mgr, uUser, nType, nPage, nPageSize) -> int.
// The CLIENT's paginated plunder-war query. FIRST
// pagination logic in the project.
//
// Structure (all RAW, v6159):
//   gates: uUser != 0, nPage >= 1, nPageSize >= 1;
//   vt+0x4a8 (the user's league) != 0;
//   vt+0x568 (the member key) != 0.
//   nType != 2 -> the PLUNDERED branch: lower_bound into
//   mgr+0x3b0/0x3e0; nType == 2 -> the PLUNDERING branch:
//   lower_bound into mgr+0x370/0x3a0. The two branches are
//   RAW-duplicated (kept duplicated in the port).
//   The found outer node: inner kit map {proxy@node+0x20,
//   head@node+0x50, size@node+0x58}. Pagination: total =
//   size@+0x58; empty or (nPage-1)*nPageSize >= total ->
//   return 0. Msg: the D71 RobOpt family — ctor
//   1417d8390, create 1417d84d0(msg, type, nPage +
//   total*1000); fail -> dtor + return 0.
//   Loop: in-order over the inner map (isnil@+0x1d, id
//   u32@+0x18, the standard kit advance), skipping
//   (nPage-1)*nPageSize entries, stopping on end or when
//   1417d8700 count >= nPageSize. PLUNDERED appends ONE
//   name (141766250, str2 = null); PLUNDERING appends TWO
//   (141766250 + 141766170) via 1417d8870(msg, id/1e6,
//   s1, s2). Append fail -> log "msg over size" -> close
//   (NOT D75's batch retry). Close: count != 0 ->
//   serialize 1417d8570 + send vt+8 + dtor; return 1.
// ============================================================================
#include <cstdint>

namespace syndicate {

// the new vtable probe (vt+0x568)
extern uint32_t (*g_fnCqpMemberKey)(void* pLogic, uint32_t uUser,
                                    int32_t nLeague);

// the RobOpt-family faces seamed for this unit (the real
// D71 ports are FUN 1417d8700/1417d8870):
extern uint16_t (*g_fnCqpMsgCount)(void* pMsg);            // 1417d8700
extern char     (*g_fnCqpMsgAppend)(void* pMsg, int32_t nId,
                                   const char* psz1,
                                   const char* psz2);     // 1417d8870

int32_t ClientQueryPlunderWarInfo(void* pMgr, uint32_t uUser,
                                  int32_t nType, int32_t nPage,
                                  int32_t nPageSize);

}  // namespace syndicate

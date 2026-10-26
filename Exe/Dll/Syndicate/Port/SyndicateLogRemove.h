// SyndicateLogRemove.h — D60: the USER LOG-RECORD
// REMOVAL flow — the real body of the D59 seam
// g_fnLogRemove (FUN_1417ac620).
//
// ORIGINAL: Syndicate.dll.decompiled.c
//   FUN_1417ac620 @ 1417ac620 — the flow:
//     rec = FUN_14178c8e0(*(logic+0x18), id);
//     if (rec == 0) {
//       acct = FUN_1417631d0(*(logic+0x50), id);
//       if (acct != 0) FUN_14174b360(acct, id, 8, 0);
//     } else {
//       FUN_141787310(rec, 0);
//       rank = FUN_141785ea0(rec);
//       m = FUN_1417cad00(*(logic+0x10), rank);
//       if (m != 0) FUN_14179e020(m);
//     }
//     syn = (**(logic+8)->vt[0x4a8])(logic+8, id);
//     if (syn != 0) FUN_141767cd0(*(logic+0x50), id, syn);
//     FUN_141774ba0(*(logic+0x50), id);
//
// PORTED VERBATIM (this unit):
//   FUN_14178c8e0 — the log-record map find (the
//     inline _Tree lower_bound walk; head = map[6],
//     key @ node+0x18, isnil @ node+0x29, value @
//     node+0x20; the checked-iterator unwrap)
//   FUN_1417631d0 — the account-tree find (via the
//     session-key lookup 14175ee00 = SEAM; tree
//     head @ acctmgr+0x68, anchor @ +0x38)
//   FUN_14174b360 — the field-set walk (tree @
//     mgr+0xc8, anchor @ +0x98) + the literal
//     field writes: 4→+0x1c(int), 5→+0x20(int),
//     6→+0x24(short), 8→+0x2a(bool), 9→+0x26(int)
//   FUN_141787310 — the offline flag + tick (byte
//     +0x3c, the vt+0x10(0x1a) chain, _time64 &
//     0xffffffff, vt+0xb0, vt+0x38)
//   FUN_141785ea0 — the rank getter (vt+0x10(1)
//     then vt+0x40)
//   FUN_14179e020 — the record-vec sort prep (the
//     range checks + the sort call)
//   FUN_14178f1a0 — the sort comparator (verbatim)
//   FUN_141787300 — the online-flag byte (+0x3c)
//   FUN_1417867d0 — the comparator key (vt+0x10(2)
//     then vt+0x48)
//   FUN_141785dc0 — the comparator sub-key
//     (vt+0x10(0) then vt+0x40)
//   FUN_141767cd0 — the session-map branch (the
//     141721b50 getter + the inline walk)
//   FUN_141721b50 — the *(p+0x54) getter
//   FUN_141774ba0 — the erase prep (map @ +0x2b0)
//
// SEAMS (documented TBD):
//   g_fnSessionKeyLookup — 14175ee00 (the session
//     key lookup walk; pulls the comparator
//     14174b000 + 141745520)
//   g_fnSortRange — 14179cf10 (the STL introsort:
//     14179cf10/141795d40/141793fd0/141795f70/
//     1417976e0 — the std::sort machinery; port
//     as its own unit later)
//   g_fnTreeInsertF10 — 141760f10 (the session-map
//     attach/rebalance)
//   g_fnSendToSession — 14172eae0 (the send path)
//   g_fnTreeFindAF0 — 141760af0 (the erase map find)
//   g_fnTreeErase — 141773e60 (the erase/rebalance,
//     209 lines — the biggest open seam)
//   g_fnLogRemoveInvalid — _invalid_parameter_noinfo
//   g_fnLogRemoveLogError — log_InlineLogERROR
//     (DAT_141824ca8)
//   REUSED: LeagueMemberLookup (1417cad00, D34)
#ifndef SYNDICATE_LOG_REMOVE_H
#define SYNDICATE_LOG_REMOVE_H

#include <cstdint>

namespace syndicate {

// ---- seams ----
extern uint64_t (*g_fnSessionKeyLookup)(void* pMgr,
    uint32_t uId);              // 14175ee00
extern void (*g_fnSortRange)(void* pFirst, void* pLast,
    int64_t nCount, void* pPred);   // 14179cf10
extern void* (*g_fnTreeInsertF10)(void* pMap,
    void* pOutIter, uint32_t* pKey); // 141760f10
extern void (*g_fnSendToSession)(void* pSess,
    uint32_t uId);             // 14172eae0
extern void* (*g_fnTreeFindAF0)(void* pMap,
    void* pOutIter, uint32_t* pKey); // 141760af0
extern void (*g_fnTreeErase)(void* pMap, void* pOut,
    void* pIter);              // 141773e60
extern void (*g_fnLogRemoveInvalid)();  // _invalid_parameter_noinfo
extern void (*g_fnLogRemoveLogError)(); // InlineLogERROR

// ---- the bodies ----
// 1417ac620 — the flow itself
void LogRemoveFlow(void* pLogic, uint32_t uId);
// 14178c8e0 — (pMap, key) -> the record or 0
int64_t LogRecMapFind(void* pMap, uint32_t uKey);
// 1417631d0 — (pAcctMgr, id) -> the account or 0
int64_t AcctTreeFind(void* pAcctMgr, uint32_t uId);
// 14174b360 — the field set
void AcctFieldSet(void* pAcctMgr, uint32_t uId,
                  int nField, int nVal);
// 141787310 — the offline flag + tick
void RecFlagTick(void* pRec, uint8_t bFlag);
// 141785ea0 — the rank getter
uint64_t RecRankGet(void* pRec);
// 14179e020 — the sort prep
void RecVecSort(void* pMember);
// 14178f1a0 — the comparator
bool RecComparator(void* pA, void* pB);
// 141787300
bool RecIsOnline(void* pRec);
// 1417867d0
int64_t RecCmpKey(void* pRec);
// 141785dc0
uint64_t RecCmpSub(void* pRec);
// 141767cd0
void SessionMapBranch(void* pAcctMgr, uint32_t uId,
                      uint32_t uSyn);
// 141721b50
uint32_t SessOwnerGetter(void* pSess);
// 141774ba0
void ErasePrep(void* pAcctMgr, uint32_t uId);

}  // namespace syndicate

#endif  // SYNDICATE_LOG_REMOVE_H

// ============================================================
// Syndicate.dll port — D47/T16: the meed CMsg flow
// (SendMemberGrade 14177f700) + the CMsg inline layer:
// the ctor/dtor (1417d9e60/1417d9eb0 —
// CMsgSelfSynMemAwardRank), the header encode
// (1417da020), the 0x3c entry append (1417da310), the
// pool lazy get (14177d350/DAT_141886d40) and the
// grade-type counter (141778e60 — the vt+8 protocol,
// sub(3).vt+0x48 == the requested type).
// The heavies 14177cdc0 (the pool list fill) and
// 141779f40 (the grade page query, 1030B) are SEAMS
// here (D48/D49).
// ============================================================
#pragma once
#include <cstdint>

namespace syndicate {

// ---- the vftable markers ----
extern void* g_pMsgMemAwardRankVft;  // the derived
extern void (*g_fnTqCMsgInit)(void* pMsg);
extern void (*g_fnEhVecCtor)(void* pArr);

// ---- the pool (DAT_141886d40, ctor 14177cfa0 seam) --
extern void* g_pMeedPool;
extern void* (*g_fnMeedPoolCtor)(void* p);
void MeedPoolReset();                // test hook
void* MeedPoolGet();                 // 14177d350

// ---- the seam: 14177cdc0 (the pool list fill) ----
extern void (*g_fnMeedListFill)(void* pPool,
                                int* pnA, int* pnB,
                                uint32_t uId,
                                int nType);
// ---- the seam: 141779f40 (the grade page query) --
extern int (*g_fnMeedGradePage)(
    void* pLeague, uint64_t uUser,
    int32_t* pOutEntries, int nType,
    int nLimit, int nStride);
// ---- the seam: the mgr vt+0xb8 name lookup ----
extern char* (*g_fnMgrNameOf)(void* pMgr,
                              uint32_t uId);
// ---- the seam: the user send (vt+8) ----
extern void (*g_fnMeedSend)(void* pUserProxy,
                            void* pUserData,
                            void* pMsg);

// ---- FUN_141778e60: the entries of (league, type) --
int MeedGradeTypeCount(void* pLeague, int nType);

// ---- FUN_1417d9e60/1417d9eb0: the CMsg ctor/dtor ----
void* CMsgMemAwardRankCtor(void* pMsg);
void CMsgMemAwardRankDtor(void* pMsg);

// ---- FUN_1417da020: the header encode ----
int CMsgMemAwardRankHead(void* pMsg, int nType,
                         int nCount, uint64_t uA,
                         int nB);
// ---- FUN_1417da310: the entry append ----
int CMsgMemAwardRankAppend(void* pMsg,
                           int32_t* pEntry,
                           const char* pName);

// ---- FUN_14177f700: SendMemberGrade ----
uint64_t MeedSendMemberGrade(void* pUserProxy,
                             uint64_t uUser,
                             int nType, int nPage);

// ---- D48: the pool list fill (14177cdc0) ---------
// the sub-object protocol for the B out (vt+8 idx 4)
extern void* (*g_fnMeedMemSubV)(void* pMember);
extern uint32_t (*g_fnMeedSubVVal)(void* pSub);
// ---- FUN_14177cb40: GetVecByMeedType -----------
void* MeedPoolVecByType(void* pPool, int nType);
// ---- FUN_14177cad0: IsMemberUser --------------
bool MeedIsMemberUser(void* pMember,
                      uint32_t uUser);
// ---- FUN_14177cdc0: CMeedSetMgr::GetSynMeed ---
void MeedPoolGetSynMeed(void* pPool, int* pnA,
                        int* pnB, uint32_t uUser,
                        int nType);


// ---- D49: the grade page query (141779f40) -----
// the sort seam (141779790 family — D50)
extern void (*g_fnMeedSortRaw)(void** ppBegin,
                              void** ppEnd,
                              int nCount);
// FUN_1417782c0: the entry type match
bool MeedRecMatchType(void* pL, void* pM, int nType);
// FUN_141779eb0: the lazy sort (the +0x38 flag)
void MeedSortIfNeeded(void* pL);
// FUN_141779f40: CMeedRecord::GetMeedRecord
int MeedGetRecord(void* pL, uint64_t uUser,
                  int32_t* pOut, int nType,
                  int nLimit, int nPage);

} // namespace syndicate

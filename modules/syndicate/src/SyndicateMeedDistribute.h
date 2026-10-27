// SyndicateMeedDistribute — D55b/T16: the
// CSynArenicMeed::DistributeSynMeed flow
// (141784cd0) + its award/collect family:
//   1417849f0  CollectPoint — the id walk + the
//              point scorer + the entry pushes +
//              the max tracking
//   141784c50  CollectAward — the 1/3 vs 2 dispatch
//   1417846e0  CollectAward13 — sort + the ceil /
//              floor share split (the emoney pot
//              always fully consumed)
//   1417842d0  CollectAward2 — floor shares + the
//              per-entry spread of the remainder
//              (+rem/count then +1 each in sorted
//              order)
//   141781b10  the random member pick (RandGet)
//   1417800b0  GetMeedTypeByCompeteType
//   1417ae630  the syndicate find-by-id wrapper
//   1417821d0  AwardUser — the online/disoffline
//              dispatch (vt+0x268)
//   141781860  AwardUserDisonline — the record +
//              the emoney display + the SYSTEM
//              prompt + the per-type gmlog
//   14177f0d0  CPointRecordMgr::RecordUserPoint
//   141779b60  CMeedRecord::Insert (cq_meedrecord)
//   14177f250  the user-mgr lazy singleton
//              (DAT_141886d50)
//   14177fa90  the point-scorer table (fa40 seam /
//              fa10 / fa50 seam / fa60)
//   14177fa60  the cross scorer (14173f9c0 +
//              the 14173d820 seam)
// The award ONLINE flow (1417814c0) is the next
// unit — a seam here (g_fnMeedAwardOnline).
#ifndef SYNDICATE_MEED_DISTRIBUTE_H
#define SYNDICATE_MEED_DISTRIBUTE_H

#include <cstdint>

namespace syndicate {

// ---------- the seams ----------
// LAB_14177fa40 / LAB_14177fa50 — unrecovered
// thunks of the scorer table (types 0/2)
extern int (*g_fnMeedScorer0)(void* pThis,
    uint64_t uSyn, uint32_t uUser);
extern int (*g_fnMeedScorer2)(void* pThis,
    uint64_t uSyn, uint32_t uUser);
// 14173d820 — the cross point query (the
// CQCrossServer side; 14173f9c0 IS ported)
extern int (*g_fnMeedCrossPoint)(
    void* pCross, uint64_t uSyn, uint32_t uUser);
// tq::RandGet — the platform RNG
extern uint32_t (*g_fnMeedRandGet)(int n);
// tq::TimeGet(3) — the timestamp query
extern uint64_t (*g_fnMeedTimeGet)(int n);
// 1417814c0 — AwardUserOnline (the NEXT unit)
extern void (*g_fnMeedAwardOnline)(
    void* pThis, uint32_t uUser, int nType,
    int nPoint, int nMoney, int nEmoney);
// reused from the earlier units:
//   g_fnGetGameMgr      (1417b6210)
//   g_fnMeedEntryCmp    (LAB_141780100)
//   g_fnMeedLog         (InlineLogERROR)
//   g_fnMeritInvalid    (_invalid_parameter)
//   g_fnMeritOpNew / g_fnMeritOpDelete
//   g_fnMeedInstGet     (InstanceGet)
//   g_fnMeedLogSave     (MyLogSave, varargs TBD)
//   g_fnMeedSnprintf    (_snprintf, varargs TBD)
//   g_fnMeedStrInst / g_fnMeedStrGet (the STR_
//   string manager)
//   MeedPoolGet / g_fnMeedListFill (D47)
//   MeedDeleteSynMeed   (D54)
//   MeedSingletonGet / MeedUserLeague (D33)
//   MeedGmLogName / MeedPromptGet (D53)
//   MeedVecPush         (141732200, D53)
//   MeedPostGrade       (14177fa10, D33)
//   MeritSingleton      (14173f9c0, CrossMerit)
//   MeedEntryVecPush / MeedEntryVecEraseTail /
//   MeedEntrySort       (D55a)

// ---------- FUN_1417800b0 ----------
// compete type -> meed type (0/1->2, 2->1, 3->3);
// >=4 -> the not-found log, 0
uint64_t MeedTypeByCompeteGet(void* pThis,
                              uint32_t uType);

// ---------- FUN_1417ae630 ----------
// (the game mgr, the syn id) -> the member or 0
int64_t SynMemberFind(void* pMgr, uint32_t uId);

// ---------- FUN_141781b10 ----------
// a random member id of the int vector (0 when
// empty); RandGet(count-1)
uint32_t MeedRandomMemberPick(
    void* pThis, void* pVecIds);

// ---------- FUN_14177f250 ----------
// the DAT_141886d50 lazy singleton
void* MeedUserMgrGet();

// ---------- FUN_14177fa90 ----------
// the scorer table by compete type
void* MeedPointScorerGet(void* pThis, int nType);

// ---------- FUN_14177fa60 ----------
// the cross scorer body — fa10's upgraded
// convention: RETURNS the user's points
int MeedCrossScorer(void* pThis, uint64_t uSyn,
                    uint32_t uUser);

// ---------- FUN_141779b60 ----------
// (the league, the meed type, the 5-int entry)
// -> the cq_meedrecord insert + the vec push +
// the byte+0x38 clear; false on the null table
uint64_t MeedRecordInsert(void* pLeague,
                          int nType, void* pEntry);

// ---------- FUN_14177f0d0 ----------
// (the user mgr, the id, the type, money,
// emoney): the cq_pointrecord write; 0 on
// negative amounts, 1 on both-zero, else the
// insert result (vt+0x50 with emoney!=0)
uint8_t MeedRecordUserPoint(void* pMgr,
    uint32_t uUser, int nType, int nMoney,
    int nEmoney);

// ---------- FUN_1417849f0 ----------
// (this, synId, entriesVec, pnTotal, pnMaxUser,
//  pnMaxPoint, competeType, idsVec) -> 1/0
uint64_t MeedCollectPoint(void* pThis,
    uint32_t uIdSyn, void* pVecEntries,
    int* pnTotal, int* pnMaxUser, int* pnMaxPoint,
    uint32_t uType, void* pVecIds);

// ---------- FUN_141784c50 ----------
// the collect dispatch: 1/3 -> 46e0, 2 -> 2d0
uint64_t MeedCollectAward(void* pThis,
    int nMeedType, void* pVecEntries, int nTotal,
    int nMoneyPot, int nEmoneyPot);

// ---------- FUN_1417846e0 ----------
// types 1/3: sort + the ceil/floor split;
// returns "the emoney pot fully consumed"
uint64_t MeedCollectAward13(void* pThis,
    void* pVec, int nTotal, int nMoneyPot,
    int nEmoneyPot);

// ---------- FUN_1417842d0 ----------
// type 2: the floor split + the remainder
// spread; 1 on success
uint64_t MeedCollectAward2(void* pThis,
    void* pVec, int nTotal, int nMoneyPot,
    int nEmoneyPot);

// ---------- FUN_1417821d0 ----------
// the online (vt+0x268) vs disonline dispatch
void MeedAwardUser(void* pThis, uint32_t uUser,
    int nType, int nPoint, int nMoney,
    int nEmoney);

// ---------- FUN_141781860 ----------
// the disonline award (the record + display +
// prompt + gmlog)
void MeedAwardUserDisonline(void* pThis,
    uint32_t uUser, int nType, int nPoint,
    int nMoney, int nEmoney);

// ---------- FUN_141784cd0 ----------
// DistributeSynMeed(this, synId, competeType)
void MeedDistributeSyn(void* pThis,
                       uint32_t uIdSyn,
                       uint32_t uType);

// test hook: reset the DAT_141886d50 singleton
void MeedUserMgrReset();

}  // namespace syndicate
#endif

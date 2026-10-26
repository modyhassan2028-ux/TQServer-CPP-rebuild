// SyndicateMeedInfo — D52/T16: the SendMeedInfo
// flow (141780a30) + its real callees:
//   14177c970  the score comparator (the
//              sub4@0x58*50000 + sub3@0x58
//              composite, desc; tie → id asc)
//   14177c870  the grade comparator (grade@0x48
//              desc → type@0x48 desc → id@0x40
//              asc)
//   14177d9b0  CMeedSetMgr::SortByMeed (the
//              per-type lazy flag at +0x90
//              (+0xc8 in the error path —
//              200 decimal again))
//   14177cd40  CMeedSetMgr::GetCount
//   14177dfe0  CMeedSetMgr::GetMeedList (the
//              offset/span walk + the self
//              entry capture)
//   1417d9f90  the self-rank msg create head
//   1417da210  the self-rank entry append (0x34)
//   1417da420  the self rank/grade write
//   1417ac810  the requester id (vt+0x1f8 —
//              seam g_fnMeedReqId)
#ifndef SYNDICATE_MEED_INFO_H
#define SYNDICATE_MEED_INFO_H

#include <cstdint>

namespace syndicate {

// the flow's member sub seams need +0x58 too
extern int (*g_fnMeedSubNScore)(void* pSubN);
extern int (*g_fnMeedReqId)(void* pSvc);
extern char* (*g_fnMgrNameOfSvc)(void* pSvc,
                                uint32_t uId);
extern void (*g_fnMeedSendTarget)(void* pObj,
                                  void* p2,
                                  void* pMsg);

bool MeedCmpScore(void* a, void* b);
bool MeedCmpGrade(void* a, void* b);
void MeedSortByType(void* pPool, int nType);
int MeedGetCount(void* pPool, int nType);
int MeedGetList(void* pPool, int nReqId,
                int32_t* pnOut, int nType,
                int nOffset, int nSpan,
                int32_t* pnSelfA,
                int32_t* pnSelfB);
int CMsgSelfRankCreate(void* pMsg, int nType,
                       int nCount);
int CMsgSelfRankCounts(void* pMsg, int64_t uA,
                       int nB);
int CMsgSelfRankAppend(void* pMsg, int32_t* pnE,
                       const char* pName);
bool MeedSendInfo(void* pThis, void* p2,
                  int nType, int nPage);

} // namespace syndicate
#endif

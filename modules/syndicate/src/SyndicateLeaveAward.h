// SyndicateLeaveAward.h — D58b: CPointRecordMgr::
// SendLeaveAward (0x14177eda0, 812 bytes).
//
// SOURCE: the decompiler FAILED on this body
// (index "failed"); this port is verbatim from a
// manual capstone disassembly of the original
// Syndicate.dll (ImageBase 0x141720000, binary
// restored from Conquer_Online_Source_v6159.7z).
//
// Signature (from the caller FUN_14177f340):
//   char SendLeaveAward(void* pModule, uint32_t uId,
//       int nType, int nMoney, int nEMoney)
//   rcx=pModule, edx=uId, r8d=nType, r9d=nMoney,
//   [rsp+0x28]=nEMoney
//
// The literal log strings (all @ .rdata):
//   0x14182e7f8  "CPointRecordMgr::SendLeaveAward, "
//               "Type[%d] is not found!"     (ERROR)
//   0x14182ea38  "invalid emoney type[%d]"   (ERROR)
//   0x14182e9f0  "DeleteRecord failed! idUser[%u], "
//               "nMoney[%d], nEMoney[%d], "
//               "nType[%d]"                  (ERROR)
//   0x14182e9b8  "User:%s[%u] Get (MeedAward[%d] "
//               "Leave) syn[%u] emoney %u"
//   0x14182e968  "User:%s[%u] Get (MeedAward[%d] "
//               "Leave) syn[%u] money %I64d"
//   0x14182e900  "CPointRecordMgr::SendLeaveAward "
//               "idUser[%u], nEmoney[%d], "
//               "nGainEmoney[%d], nMoney[%d], "
//               "nGainMoney[%I64d]"
//   0x14182e850  "CSynArenicMeed::AwardUserOnline "
//               "idUser[%u], nOldEMoney[%d], "
//               "nAwardEMoney[%d], nGainEMoney[%d], "
//               "nOldMoney[%I64d], nAwardMoney[%d], "
//               "nGainMoney[%I64d]"
//   categories: "gmlog/syndenote" (0x14182e9a8),
//               "gmlog/syn_meed_award" (0x14182e8e8),
//               "gmlog/award_overflow" (0x14182e830)
//   DAT_141886d58 — the emoney cap (a .data
//   global read twice at 0x14177ee73/0x14177ee8d)
//
// The mgr vtable slots used (pMgr = *pModule):
//   vt+0x238  (mgr, id) -> int   (the emoney now)
//   vt+0x230  (mgr, id) -> void* (the buf begin)
//   vt+0x148  (mgr, id, id, nGain, cbType, 1)
//                          -> bool (DeleteRecord)
//   vt+0x1f8  (mgr, id) -> int   (the syn id)
//   vt+0x1d8  (mgr, id) -> char* (the user name)
//   vt+0x3e0  (mgr) -> void*     (the buf end)
//   vt+0x138  (mgr, id, nGain64, 1)  (add money)
// The emoney type codes: 1->0x1d, 2->0x18, 3->0x28
#ifndef SYNDICATE_LEAVE_AWARD_H
#define SYNDICATE_LEAVE_AWARD_H

#include <cstdint>

namespace syndicate {

// ---- the seams (the vtable slots + the logs) --
struct SPointRecordMgrVt {
    // filled by the caller; null slots log-skip
    void* apSlots[0x80];   // indexed (off/8)
};
extern void* (*g_fnLeaveMgrVt)();    // *pModule's vt
extern int (*g_fnMgrGetEmoney)(void* pMgr,
                               uint32_t uId);   // +0x238
extern void* (*g_fnMgrGetBuf)(void* pMgr,
                             uint32_t uId);    // +0x230
extern char (*g_fnMgrDeleteRecord)(void* pMgr,
    uint32_t uId, uint32_t uId2, int nGain,
    int cbType, char b1);                       // +0x148
extern int (*g_fnMgrGetSynId)(void* pMgr,
                              uint32_t uId);   // +0x1f8
extern char* (*g_fnMgrGetName)(void* pMgr,
                               uint32_t uId);  // +0x1d8
extern void* (*g_fnMgrGetBufEnd)(void* pMgr);   // +0x3e0
extern void (*g_fnMgrAddMoney)(void* pMgr,
    uint32_t uId, int64_t nGain,
    char b1);                                   // +0x138
extern void (*g_fnLeaveLogError)(const char* p,
    ...);   // log_InlineLogERROR
extern void (*g_fnLeaveGmLog)(const char* pCat,
    const char* pFmt, ...);   // the gmlog thunk
extern int32_t g_nLeaveEmoneyCap;   // DAT_141886d58

char SendLeaveAward(void* pModule, uint32_t uId,
                    int nType, int nMoney,
                    int nEMoney);

}  // namespace syndicate

#endif  // SYNDICATE_LEAVE_AWARD_H

// SyndicateMeedApply — D53/T16: the SetArenicMeed
// flow (141780cb0) + the CMeedSetMgr apply family:
//   14177db90  CMeedSetMgr::SetSynMeed (the
//              dispatcher: IsMemberUser + the
//              rescan walk + Insert/AddMore)
//   14177d5f0  CMeedSetMgr::Insert (the cq_setmeed
//              query + the 141732200 push + the
//              flag clear)
//   14177cbd0  CMeedSetMgr::AddMore (the field
//              adds + the bounds + flag + row
//              vt+0x38)
//   14177cb90  GetSortFlagByMeedType (+0x90,
//              the +0xc8 = 200-decimal error path)
//   14177caa0  the money/emoney bounds (the
//              DAT_141886d48 cap global)
//   14177ff70  CSynArenicMeed::GetEmonyType (the
//              0x15..0x2a constants)
//   14177fbc0  CSynArenicMeed::GetStrObject (the
//              STR_VLM/STR_SYN/STR_CROSS prompts)
//   14177fad0  the gmlog name table
//   1417da0d0  the 0x427 award-rank encode (the
//              0x20-size header)
#ifndef SYNDICATE_MEED_APPLY_H
#define SYNDICATE_MEED_APPLY_H

#include <cstdint>
#include <cstddef>

namespace syndicate {

// ---------- the seams ----------
// DAT_141886d48 — the money cap (set by the config
// loader at startup; 0 in this unit's default)
extern int32_t g_nMeedMoneyCap;
// InstanceGet for the Insert query chain
extern void* (*g_fnMeedInstGet)();
// the string manager (theInstance) + GetString
extern void* (*g_fnMeedStrInst)();
extern char* (*g_fnMeedStrGet)(void* pInst,
                              const char* pKey);
// TBD-SNPRINTF: the original's _snprintf calls take
// the prompt fmt + player-data varargs that Ghidra
// DROPPED (the Syndicate.dll binary is not present
// in this workspace for an objdump pass). The seam
// receives the dest + the fmt; the default formats
// nothing.
extern void (*g_fnMeedSnprintf)(char* pDst,
                               size_t uSize,
                               const char* pFmt);
// TBD-LOGSAVE: tq::MyLogSave(file, fmtDAT, ...) —
// the varargs are dropped; only the user id
// (uVar3 = param_2, provably loaded) is passed.
extern void (*g_fnMeedLogSave)(const char* pFile,
                              const char* pFmt,
                              uint32_t uId);
// the FUN_1417311d0 grow (the vector insert family
// — a seam in this unit)
extern void (*g_fnMeedVecInsert)(void* pVec,
                                void* pItOut[2],
                                void* pPair[2],
                                void* pVal);
// reused: g_fnMeedLog (the InlineLogERROR),
// g_fnMeritInvalid, g_fnMeedReqId (1417ac810),
// g_fnTqCMsgInit (from the earlier units)

// the two MyLogSave format DATs (opaque — the
// literal strings live in .rdata)
extern const char* g_szMeedLogFmtFresh;   // 14182f690
extern const char* g_szMeedLogFmtMore;    // 14182f5d0
// the generic error log DAT (141824ca8)
// (logged via g_fnMeedLog)

// ---------- FUN_14177caa0 ----------
uint64_t MeedApplyBounds(int nMoney, int nEmoney);
// ---------- FUN_14177cb90 ----------
uint8_t* MeedSortFlagGet(void* pPool, int nType);
// ---------- FUN_14177ff70 ----------
uint64_t MeedEmonyType(void* pUser, int nType,
                       int nMoneyType);
// ---------- FUN_14177fbc0 ----------
char* MeedPromptGet(void* pUser, int nType,
                    int nStrType);
// ---------- FUN_14177fad0 ----------
const char* MeedGmLogName(int nType, int nIdx);
// ---------- FUN_1417da0d0 ----------
uint64_t CMsgAwardRankEncode(void* pMsg,
                             uint16_t uA,
                             uint32_t uType,
                             uint64_t uMoney,
                             uint32_t uB);
// ---------- FUN_141732200 (the push) ----------
void MeedVecPush(void* pVec, void** ppVal);
// ---------- FUN_14177d5f0 ----------
uint8_t MeedSetMgrInsert(void* pPool,
                         int32_t* pnEntry,
                         int nType);
// ---------- FUN_14177cbd0 ----------
bool MeedSetMgrAddMore(void* pPool, void* pMember,
                       int32_t* pnEntry,
                       int nType);
// ---------- FUN_14177db90 ----------
uint64_t MeedSetMgrSetSynMeed(void* pPool,
                             int32_t* pnEntry,
                             int nType,
                             uint8_t* pOut);
// ---------- FUN_141780cb0 ----------
// (pUser, uId, nType, nMoney, nEmoney, uParam6)
uint64_t MeedSetArenic(void* pUser, uint32_t uId,
                       int nType, int nMoney,
                       int nEmoney, uint16_t uP6);

}  // namespace syndicate
#endif

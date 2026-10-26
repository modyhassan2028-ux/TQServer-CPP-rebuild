// SyndicateCMsgCtors.h — D57: the 17 CMsg
// constructors of the syndicate module layer
// (the real bodies behind the g_aMsgCtor seams),
// plus the two protobuf-lite message ctors they
// call at +0x408.
//
// Addresses (Syndicate.dll, ImageBase 0x141720000):
//   1417d9710  CMsgLog ctor              @+0x10
//   1417db2b0  CMsgSyndicate ctor        @+0x428
//   1417dca60  CMsgSynDomain ctor        @+0x850
//   1417dd6e0  CMsgSynProffer ctor       @+0xc78
//   1417da860  CMsgSynAttrInfo ctor      @+0x1088
//   1417dae10  CMsgSynChgDomName ctor    @+0x1498
//   1417dd050  CMsgSynMemberInfo ctor    @+0x18a8
//   1417dd230  CMsgSynMemberList ctor    @+0x1cb8
//   1417dac30  CMsgSynBaseProffer ctor   @+0x20c8
//   1417dd9f0  CMsgSynProfferRank ctor   @+0x24d8
//   1417d9e60  CMsgSelfSynMemAwardRank ctor @+0x28e8
//   1417ddc60  CMsgSynRecruitAdvertising ctor @+0x2cf8
//   1417de240  CMsgSynRecruitAdvertisingOpt ctor @+0x3108
//   1417ddf50  CMsgSynRecruitAdvertisingList ctor @+0x3518
//   1417d6640  CMsgLeagueOpt ctor        @+0x3928
//   1417d9000  CMsgLeagueToken ctor      @+0x3d50
//   1417d8390  CMsgLeagueRobOpt ctor     @+0x41a8
//   1417f1600  CMsgLeagueTokenPB ctor    (the +0x408 field)
//   1417f05f0  CMsgLeagueRobOptPB ctor   (the +0x408 field)
//   1417e8050  the PB default-instance closure thunk (seam)
//   DAT_141886ea0  the PB default instance (seam global)
//
// The ctor pattern (verbatim):
//   tq::CMsg::vftable store + Init, the class
//   vftable store, then either
//   [plain]  Init + *(this+0x408) = this+8
//   [packer] CStringPacker(+0x410) + Init +
//            *(this+0x408) = this+8 +
//            SetBuf(+0x410, buf, cap, true)
//   [PB]     the PB ctor at +0x408 + Init
#ifndef SYNDICATE_CMSG_CTORS_H
#define SYNDICATE_CMSG_CTORS_H

#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---- the class vtable constants (sentinels; the
// real handler bodies arrive with their units) ----
extern void* g_pVtCMsgSyndicate;
extern void* g_pVtCMsgSynDomain;
extern void* g_pVtCMsgSynProffer;
extern void* g_pVtCMsgSynAttrInfo;
extern void* g_pVtCMsgSynMemberInfo;
extern void* g_pVtCMsgSynMemberList;
extern void* g_pVtCMsgSynBaseProffer;
extern void* g_pVtCMsgSynProfferRank;
extern void* g_pVtCMsgSelfSynMemAwardRank;
extern void* g_pVtCMsgSynRecruitAdvertising;
extern void* g_pVtCMsgSynRecruitAdvertisingOpt;
extern void* g_pVtCMsgSynRecruitAdvertisingList;
extern void* g_pVtCMsgLeagueOpt;
extern void* g_pVtCMsgLeagueToken;
extern void* g_pVtCMsgLeagueRobOpt;
extern void* g_pVtPbMessageLite;
extern void* g_pVtCMsgLeagueTokenPB;
extern void* g_pVtCMsgLeagueRobOptPB;

// DAT_141886ea0 — the PB default instance
extern void* g_pPbDefaultInstance;
// FUN_1417e8050 — the closure-gated static init
// (the FunctionClosure0 thunk; a seam here)
extern void (*g_fnPbDefaultInit)();

// tq::CStringPacker seams
extern void (*g_fnCStrPackerCtor)(void* pPacker);
extern void (*g_fnCStrPackerSetBuf)(void* pPacker,
    char* pBuf, size_t uCap, bool bOwned);

// ---- the ctors (the 14177ead0 order) ----
void* CtorCMsgLog(void* p);              // 1417d9710
void* CtorCMsgSyndicate(void* p);        // 1417db2b0
void* CtorCMsgSynDomain(void* p);       // 1417dca60
void* CtorCMsgSynProffer(void* p);      // 1417dd6e0
void* CtorCMsgSynAttrInfo(void* p);     // 1417da860
void* CtorCMsgSynChgDomName(void* p);   // 1417dae10
void* CtorCMsgSynMemberInfo(void* p);   // 1417dd050
void* CtorCMsgSynMemberList(void* p);   // 1417dd230
void* CtorCMsgSynBaseProffer(void* p);  // 1417dac30
void* CtorCMsgSynProfferRank(void* p);  // 1417dd9f0
void* CtorCMsgSelfSynMemAwardRank(void* p);  // 1417d9e60
void* CtorCMsgSynRecruitAdvertising(void* p);  // 1417ddc60
void* CtorCMsgSynRecruitAdvertisingOpt(void* p);  // 1417de240
void* CtorCMsgSynRecruitAdvertisingList(void* p);  // 1417ddf50
void* CtorCMsgLeagueOpt(void* p);       // 1417d6640
void* CtorCMsgLeagueToken(void* p);     // 1417d9000
void* CtorCMsgLeagueRobOpt(void* p);    // 1417d8390

// ---- the PB field ctors ----
void* CtorCMsgLeagueTokenPB(void* p);    // 1417f1600
void* CtorCMsgLeagueRobOptPB(void* p);   // 1417f05f0

}  // namespace syndicate

#endif  // SYNDICATE_CMSG_CTORS_H

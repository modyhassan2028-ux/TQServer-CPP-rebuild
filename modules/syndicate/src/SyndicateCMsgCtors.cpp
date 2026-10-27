// SyndicateCMsgCtors.cpp — D57
// The 17 CMsg ctor bodies verbatim from the
// decompile (Syndicate.dll.decompiled.c) + the
// two protobuf-lite field ctors.
#include "modules/syndicate/src/SyndicateCMsgCtors.h"

#include <new>
#include <string>

#include "modules/syndicate/src/SyndicateMeedFlow.h"
// g_fnTqCMsgInit + g_pTqCMsgVft
#include "modules/syndicate/src/SyndicateModule.h"
// g_pCMsgLogVft / g_pCMsgSynChgDomNameVft (the two
// vtable sentinels the earlier unit already owns)

namespace syndicate {

// ---- the vtable sentinels (unique per class so
// the tests can identify every constructed slot) --
void* g_pVtCMsgSyndicate = (void*)0x101;
void* g_pVtCMsgSynDomain = (void*)0x102;
void* g_pVtCMsgSynProffer = (void*)0x103;
void* g_pVtCMsgSynAttrInfo = (void*)0x104;
void* g_pVtCMsgSynMemberInfo = (void*)0x105;
void* g_pVtCMsgSynMemberList = (void*)0x106;
void* g_pVtCMsgSynBaseProffer = (void*)0x107;
void* g_pVtCMsgSynProfferRank = (void*)0x108;
void* g_pVtCMsgSelfSynMemAwardRank = (void*)0x109;
void* g_pVtCMsgSynRecruitAdvertising = (void*)0x10a;
void* g_pVtCMsgSynRecruitAdvertisingOpt =
    (void*)0x10b;
void* g_pVtCMsgSynRecruitAdvertisingList =
    (void*)0x10c;
void* g_pVtCMsgLeagueOpt = (void*)0x10d;
void* g_pVtCMsgLeagueToken = (void*)0x10e;
void* g_pVtCMsgLeagueRobOpt = (void*)0x10f;
void* g_pVtPbMessageLite = (void*)0x200;
void* g_pVtCMsgLeagueTokenPB = (void*)0x201;
void* g_pVtCMsgLeagueRobOptPB = (void*)0x202;

void* g_pPbDefaultInstance = (void*)0x300;
static void DefPbDefaultInit() {}
void (*g_fnPbDefaultInit)() = DefPbDefaultInit;

static void DefPackerCtor(void* pPacker) {
    (void)pPacker;
}
static void DefPackerSetBuf(void* pPacker,
    char* pBuf, size_t uCap, bool bOwned) {
    (void)pPacker; (void)pBuf; (void)uCap;
    (void)bOwned;
}
void (*g_fnCStrPackerCtor)(void*) = DefPackerCtor;
void (*g_fnCStrPackerSetBuf)(void*, char*,
    size_t, bool) = DefPackerSetBuf;

// ---- 1417d9710: CMsgLog (plain) ----
void* CtorCMsgLog(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pCMsgLogVft;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417db2b0: CMsgSyndicate (packer) ----
void* CtorCMsgSyndicate(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSyndicate;
    g_fnCStrPackerCtor(pc + 0x410);
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    g_fnCStrPackerSetBuf(pc + 0x410,
        pc + 0x20, 0x3e5, true);
    return p;
}

// ---- 1417dca60: CMsgSynDomain (packer) ----
void* CtorCMsgSynDomain(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynDomain;
    g_fnCStrPackerCtor(pc + 0x410);
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    g_fnCStrPackerSetBuf(pc + 0x410,
        pc + 0x128, 0x2d9, true);
    return p;
}

// ---- 1417dd6e0: CMsgSynProffer (plain) ----
void* CtorCMsgSynProffer(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynProffer;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417da860: CMsgSynAttrInfo (plain) ----
void* CtorCMsgSynAttrInfo(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynAttrInfo;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417dae10: CMsgSynChgDomName (plain) ----
void* CtorCMsgSynChgDomName(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pCMsgSynChgDomNameVft;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417dd050: CMsgSynMemberInfo (plain) ----
void* CtorCMsgSynMemberInfo(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynMemberInfo;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417dd230: CMsgSynMemberList (plain) ----
void* CtorCMsgSynMemberList(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynMemberList;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417dac30: CMsgSynBaseProffer (plain) ----
void* CtorCMsgSynBaseProffer(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynBaseProffer;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417dd9f0: CMsgSynProfferRank (plain) ----
void* CtorCMsgSynProfferRank(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynProfferRank;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417d9e60: CMsgSelfSynMemAwardRank ----
void* CtorCMsgSelfSynMemAwardRank(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSelfSynMemAwardRank;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417ddc60: CMsgSynRecruitAdvertising ----
void* CtorCMsgSynRecruitAdvertising(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynRecruitAdvertising;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417de240: CMsgSynRecruitAdvertisingOpt --
void* CtorCMsgSynRecruitAdvertisingOpt(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynRecruitAdvertisingOpt;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417ddf50: CMsgSynRecruitAdvertisingList --
void* CtorCMsgSynRecruitAdvertisingList(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgSynRecruitAdvertisingList;
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    return p;
}

// ---- 1417d6640: CMsgLeagueOpt (packer) ----
void* CtorCMsgLeagueOpt(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgLeagueOpt;
    g_fnCStrPackerCtor(pc + 0x410);
    g_fnTqCMsgInit(pc);
    *(void**)(pc + 0x408) = pc + 8;
    g_fnCStrPackerSetBuf(pc + 0x410,
        pc + 0x1a, 0x3ee, true);
    return p;
}

// ---- 1417f1600: CMsgLeagueTokenPB (the PB
// field ctor; verbatim field stores — the
// std::string is the port's std::string in
// place of MSVC's; the closure thunk 1417e8050
// and DAT_141886ea0 are seams) ----
void* CtorCMsgLeagueTokenPB(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pVtPbMessageLite;
    *(void**)pc = g_pVtCMsgLeagueTokenPB;
    new (pc + 8) std::string();
    g_fnPbDefaultInit();
    *(uint32_t*)(pc + 0x34) = 0;
    *(uint32_t*)(pc + 0x38) = 0;
    *(uint32_t*)(pc + 0x3c) = 0;
    *(uint32_t*)(pc + 0x40) = 0;
    *(uint32_t*)(pc + 0x44) = 0;
    *(void**)(pc + 0x48) = g_pPbDefaultInstance;
    *(uint32_t*)(pc + 0x30) = 0;
    return p;
}

// ---- 1417d9000: CMsgLeagueToken (PB) ----
void* CtorCMsgLeagueToken(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgLeagueToken;
    CtorCMsgLeagueTokenPB(pc + 0x408);
    g_fnTqCMsgInit(pc);
    return p;
}

// ---- 1417f05f0: CMsgLeagueRobOptPB ----
void* CtorCMsgLeagueRobOptPB(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pVtPbMessageLite;
    *(void**)pc = g_pVtCMsgLeagueRobOptPB;
    new (pc + 8) std::string();
    *(uint64_t*)(pc + 0x40) = 0;
    *(uint32_t*)(pc + 0x48) = 0;
    *(uint32_t*)(pc + 0x4c) = 0;
    *(uint32_t*)(pc + 0x50) = 0;
    *(uint32_t*)(pc + 0x34) = 0;
    *(uint32_t*)(pc + 0x38) = 0;
    *(uint32_t*)(pc + 0x3c) = 0;
    *(uint32_t*)(pc + 0x30) = 0;
    return p;
}

// ---- 1417d8390: CMsgLeagueRobOpt (PB) ----
void* CtorCMsgLeagueRobOpt(void* p) {
    char* pc = (char*)p;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgLeagueRobOpt;
    CtorCMsgLeagueRobOptPB(pc + 0x408);
    g_fnTqCMsgInit(pc);
    return p;
}

}  // namespace syndicate

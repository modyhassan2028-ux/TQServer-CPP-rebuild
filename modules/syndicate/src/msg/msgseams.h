// ============================================================================
// CMsgSeams.h — the tq::CMsg layer seams shared by every syndicate message
// class (Syndicate.dll v6159). Defined once in CMsgSeams.cpp.
// ============================================================================
#ifndef SYNDICATE_CMSGSEAMS_H
#define SYNDICATE_CMSGSEAMS_H
#include <cstdint>
namespace syndicate {

// 0x1417e7fda — the imported tq::CMsg::Create thunk (this, pData, uType)
extern bool (*g_pfnCMsgCreate)(void* self, char* pData, uint16_t uType);
// InlineLogERROR, resolved through the import at 0x141827030
extern void (*g_pfnInlineLogError)(const char* fmt, ...);
// 0x1417b6210 — the SyndicateMgr accessor
extern void* (*g_pfnGetSyndicateMgr)();
// 0x1417e8016 — the tq::CMsg pre-send initialiser (this, pArg, uA, uB)
extern void (*g_fn_1417e8016)(void* self, const void* pArg,
                              uint32_t uA, uint32_t uB);
// 0x1417ac6f0 — SyndicateMgr query (mgr, idActor) -> bool
extern bool (*g_fn_1417ac6f0)(void* pMgr, uint32_t idActor);
// 0x1417ae640 — SyndicateMgr member-list apply (mgr, idActor, uValue)
extern void (*g_fn_1417ae640)(void* pMgr, uint32_t idActor, uint32_t uValue);
// 0x1417ae790 — SyndicateMgr domain apply (mgr, idActor, uValue)
extern void (*g_fn_1417ae790)(void* pMgr, uint32_t idActor, uint32_t uValue);
// the CRT memcpy-ish import at 0x141823098 (dst, src)
extern void* (*g_fn_141823098)(void* pDst, const void* pSrc);
// the variadic reporter at IAT 0x141823030 — ASSERT(fmt, expr, func, file, line)
// and the plain "invalid action:%d" log call share this one import
extern void (*g_fn_141823030)(const char* fmt, ...);
// IAT 0x1418230a0 — the destructor of the sub-object at CMsgSynDomain+0x410
extern void (*g_fn_1418230a0)(void* pSub);

}  // namespace syndicate
#endif

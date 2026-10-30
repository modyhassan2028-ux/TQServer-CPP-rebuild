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
// the CRT memcpy-ish import at 0x141823098 (dst, src)
extern void* (*g_fn_141823098)(void* pDst, const void* pSrc);
// the assert reporter at 0x141823030 (fmt, expr, file, func, line)
extern void (*g_fn_141823030)(const char* fmt, const char* pExpr,
                              const char* pFile, const char* pFunc, int nLine);

}  // namespace syndicate
#endif

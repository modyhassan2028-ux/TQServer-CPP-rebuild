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

}  // namespace syndicate
#endif

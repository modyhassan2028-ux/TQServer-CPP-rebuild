// CMsgSeams.cpp — the shared tq::CMsg seams (single definition point)
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {
bool (*g_pfnCMsgCreate)(void*, char*, uint16_t) = nullptr;
void (*g_pfnInlineLogError)(const char*, ...) = nullptr;
void* (*g_pfnGetSyndicateMgr)() = nullptr;
void (*g_fn_1417e8016)(void*, const void*, uint32_t, uint32_t) = nullptr;
void* (*g_fn_141823098)(void*, const void*) = nullptr;
void (*g_fn_141823030)(const char*, const char*, const char*,
                       const char*, int) = nullptr;
}  // namespace syndicate

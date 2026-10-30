// CMsgSeams.cpp — the shared tq::CMsg seams (single definition point)
#include "modules/syndicate/src/CMsgSeams.h"
namespace syndicate {
bool (*g_pfnCMsgCreate)(void*, char*, uint16_t) = nullptr;
void (*g_pfnInlineLogError)(const char*, ...) = nullptr;
}  // namespace syndicate

// CMsgSeams.cpp — the shared tq::CMsg seams (single definition point)
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {
bool (*g_pfnCMsgCreate)(void*, char*, uint16_t) = nullptr;
void (*g_pfnInlineLogError)(const char*, ...) = nullptr;
void* (*g_pfnGetSyndicateMgr)() = nullptr;
void (*g_fn_1417e8016)(void*, const void*, uint32_t, uint32_t) = nullptr;
void* (*g_fn_141823098)(void*, const void*) = nullptr;
void (*g_fn_141823030)(const char*, ...) = nullptr;
void (*g_fn_1418230a0)(void*) = nullptr;
bool (*g_fn_1417ac6f0)(void*, uint32_t) = nullptr;
void (*g_fn_1417ae640)(void*, uint32_t, uint32_t) = nullptr;
bool (*g_fn_1417afb20)(void*, uint32_t, uint32_t, const void*) = nullptr;
void (*g_fn_1417ac7d0)(void*, uint32_t, void*) = nullptr;
void (*g_pfnMgrVf28)(void*, uint32_t) = nullptr;
void (*g_fn_1417e9440)(void*) = nullptr;
void (*g_fn_1417ae790)(void*, uint32_t, uint32_t) = nullptr;
}  // namespace syndicate

// CMsgPBCommon.cpp — definitions of the shared protobuf-lite seams
#include "modules/syndicate/src/CMsgPBCommon.h"
namespace syndicate {
void     (*g_pfnPbFree)(void*) = nullptr;
uint64_t (*g_pfnPb8050)() = nullptr;
void*     g_pPbDefaultStr = nullptr;
}  // namespace syndicate

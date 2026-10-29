// ============================================================================
// CMsgPBCommon.h — the seams every protobuf-lite message class shares
// RAW: Syndicate.dll v6159
//   0x1417e8050  the shared field-init helper called from each ctor
//   0x1417de5a0  MessageLite base dtor (body in CMsgPBMemberDtors.cpp)
//   DAT_141886ea0 the shared empty std::string sentinel
#ifndef SYNDICATE_CMSPBCOMMON_H
#define SYNDICATE_CMSPBCOMMON_H
#include <cstdint>
namespace syndicate {

extern void     (*g_pfnPbFree)(void*);        // operator_delete
extern uint64_t (*g_pfnPb8050)();             // 1417e8050
extern void*     g_pPbDefaultStr;             // DAT_141886ea0

}  // namespace syndicate
#endif

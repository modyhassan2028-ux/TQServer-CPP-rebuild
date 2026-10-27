// FORWARDING SHIM — the real source now lives at the
// ORIGINAL path: modules/syndicate/src/syndicatelogic.{h,cpp}
// (recovered from the binary literals). Kept so the
// existing tests/build keep working during the
// migration; new code must include the real path.
#ifndef SHIM_SYNDICATE_LOGIC_TABLE1_H
#define SHIM_SYNDICATE_LOGIC_TABLE1_H
#include "modules/syndicate/src/syndicatelogic.h"
#include <cstdint>
namespace syndicate {
void*   Slot000DelDtor(void* p, uint64_t u2, void* p3,
                       char* p4);
void    Slot008PushSynAttrInfo(void* pL, uint32_t u);
uint64_t Slot010DestroySoon(void* pL, int32_t n);
void    Slot018PushMemberInfo(void* pL, uint32_t u);
void    Slot020PushAttrChange(void* pL, int32_t a,
                              int32_t b, const char* c);
uint8_t Slot028PushProffer(void* pL, uint32_t u,
                           int64_t a, int64_t b);
uint64_t Slot030Donate(void* pL, uint32_t u, int64_t m);
uint64_t Slot040Fwd88(void* pL);
void    Slot048MemberOnline(void* pL, uint32_t u);
uint64_t Slot058LogRecSynId(void* pL, uint32_t u);
uint64_t Slot068RankSwap(void* pL, uint32_t a, uint32_t b);
void    Slot070SetPlayer(void* pL, uint32_t a, uint32_t b);
bool    Slot078IsRank1000(void* pL);
void    Slot080RankClear(void* pL);
bool    Slot088IsRank3de(void* pL);
bool    Slot090IsRank37a(void* pL);
int64_t Slot098AssemblymanGate(void* pL);
int64_t Slot0a0Gate2b228a(void* pL);
uint64_t Slot0a8OnUserDelRole(void* pL, uint32_t u);
}  // namespace syndicate
#endif

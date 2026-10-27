// FORWARDING SHIM (see the header note).
#include "Exe/Dll/Syndicate/Port/SyndicateLogicTable1.h"
namespace syndicate {
void* Slot000DelDtor(void* p, uint64_t u2, void* p3,
                     char* p4) {
    return ((CSyndicateLogic*)p)->Slot000DelDtor(
        p, u2, p3, p4);
}
void Slot008PushSynAttrInfo(void* pL, uint32_t u) {
    ((CSyndicateLogic*)pL)->Slot008PushSynAttrInfo(u);
}
uint64_t Slot010DestroySoon(void* pL, int32_t n) {
    return ((CSyndicateLogic*)pL)->Slot010DestroySoon(n);
}
void Slot018PushMemberInfo(void* pL, uint32_t u) {
    ((CSyndicateLogic*)pL)->Slot018PushMemberInfo(u);
}
void Slot020PushAttrChange(void* pL, int32_t a,
                           int32_t b, const char* c) {
    ((CSyndicateLogic*)pL)->Slot020PushAttrChange(a, b, c);
}
uint8_t Slot028PushProffer(void* pL, uint32_t u,
                           int64_t a, int64_t b) {
    return ((CSyndicateLogic*)pL)->Slot028PushProffer(
        u, a, b);
}
uint64_t Slot030Donate(void* pL, uint32_t u, int64_t m) {
    return ((CSyndicateLogic*)pL)->Slot030Donate(u, m);
}
uint64_t Slot040Fwd88(void* pL) {
    return ((CSyndicateLogic*)pL)->Slot040Fwd88();
}
void Slot048MemberOnline(void* pL, uint32_t u) {
    ((CSyndicateLogic*)pL)->Slot048MemberOnline(u);
}
uint64_t Slot058LogRecSynId(void* pL, uint32_t u) {
    return ((CSyndicateLogic*)pL)->Slot058LogRecSynId(u);
}
uint64_t Slot068RankSwap(void* pL, uint32_t a, uint32_t b) {
    return ((CSyndicateLogic*)pL)->Slot068RankSwap(a, b);
}
void Slot070SetPlayer(void* pL, uint32_t a, uint32_t b) {
    ((CSyndicateLogic*)pL)->Slot070SetPlayer(a, b);
}
bool Slot078IsRank1000(void* pL) {
    return ((CSyndicateLogic*)pL)->Slot078IsRank1000();
}
void Slot080RankClear(void* pL) {
    ((CSyndicateLogic*)pL)->Slot080RankClear();
}
bool Slot088IsRank3de(void* pL) {
    return ((CSyndicateLogic*)pL)->Slot088IsRank3de();
}
bool Slot090IsRank37a(void* pL) {
    return ((CSyndicateLogic*)pL)->Slot090IsRank37a();
}
int64_t Slot098AssemblymanGate(void* pL) {
    return ((CSyndicateLogic*)pL)
        ->Slot098AssemblymanGate();
}
int64_t Slot0a0Gate2b228a(void* pL) {
    return ((CSyndicateLogic*)pL)->Slot0a0Gate2b228a();
}
uint64_t Slot0a8OnUserDelRole(void* pL, uint32_t u) {
    return ((CSyndicateLogic*)pL)->OnUserDelRole(u);
}
}  // namespace syndicate

#ifndef ELITE_PK_ARENIC_ACTOR_H
#define ELITE_PK_ARENIC_ACTOR_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\adapter\src\elitepkarenicactor.cpp
// 140596b80 CElitePKArenicActor::OnUserArenicHornorChange(rank)
#include <cstdint>
namespace msg {
struct SElitePKArenicSeams {
    void* (*CurrentInstanceGet)();                        // adapter singleton
    void  (*LogNullInstance)();                           // DAT_1406d9c10 CHECKF line
    void  (*LogNoInterface)();                            // the literal module line
    void* (*GetModule)(void* inst, uint32_t id);          // inst vt+0x20
    void  (*OnHornorChange)(void* mod, uint32_t rank);    // mod vt+0x110
};
class CElitePKArenicActor {
public:
    void OnUserArenicHornorChange(uint32_t rank, SElitePKArenicSeams& s);
};
} // namespace msg
#endif

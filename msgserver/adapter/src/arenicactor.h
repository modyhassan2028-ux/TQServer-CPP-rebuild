#ifndef ARENIC_ACTOR_H
#define ARENIC_ACTOR_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\adapter\src\arenicactor.cpp
// 1405a7300 CArenicActor::OnUserArenicWin
// 1405a7400 CArenicActor::OnUserArenicCompete
#include <cstdint>
namespace adapter {
struct SArenicActorSeams {
    void* (*LuaState)();                                   // DAT_140975bf0
    void  (*LogCheck)(int line);                           // DAT_1406d9c10 + 0x3cd
    int   (*CallLua)(void* lua, const char* arg, int id, int zero); // 140286530
    void  (*LogLuaFault)(const char* who);                 // the two literals
};
class CArenicActor {
public:
    uint8_t m_Pad[0x10] = {};
    // both return 1 with an id, 0 when the id is 0
    int OnUserArenicWin(int id, uint32_t n, SArenicActorSeams& s);
    int OnUserArenicCompete(int id, uint32_t n, SArenicActorSeams& s);
};
} // namespace adapter
#endif

#ifndef STORAGE_ACTOR_H
#define STORAGE_ACTOR_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\adapter\src\storageactor.cpp
// (proven path) and the RTTI proves the namespace: the ctor writes
// adapter::CStorageActor::vftable then adapter::IActor::vftable.
#include <cstdint>
namespace adapter {
struct SStorageSeams {
    void* (*PlayerItems)(void* user);          // (*(user+0x10))+0x98
    void  (*EquipCtor)(void* obj);             // 1403f2320
    char  (*EquipBuild)(void* obj, int action, uint32_t arg, int zero); // 1403f23d0
    void  (*EquipDtor)(void* obj);              // 1403f2370
    void  (*SendToClient)(void* sink, void* obj); // (item+0x10)+0x350
    void  (*LogEquipArgs)(uint32_t user, int action, uint32_t item, uint32_t date);
    void  (*CheckFail)(void* msg);              // DAT_1406d9c10 literal
    void* (*ItemGetById)(void* mgr, uint32_t id); // mgr vt+0x60
    uint64_t (*IsAccumulate)(void* item, uint32_t type, uint16_t arg); // 140102910
    void  (*LogNoItem)(uint32_t idItem, uint32_t idType, uint32_t idUser, int type);
};
class CStorageActor {
public:
    char SendEquipLock(uint32_t user, int action, uint32_t arg,
                       uint32_t date, SStorageSeams& s);
    uint64_t IsAccumulateWith(uint32_t idItem, uint32_t idType,
                              uint16_t type, SStorageSeams& s);
    void* m_pMgr = nullptr;   // DAT_140975b60 for IsAccumulateWith
};
} // namespace adapter
#endif

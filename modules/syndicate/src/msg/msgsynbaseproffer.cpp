// msgsynbaseproffer.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynbaseproffer.h"
namespace syndicate {

// 0x1417dadc0
void* CMsgSynBaseProffer::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dacb0
bool CMsgSynBaseProffer::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417dadb0 — an empty override in the original
void CMsgSynBaseProffer::Process(void* self, uint32_t idActor) {
    (void)self; (void)idActor;
}

}  // namespace syndicate

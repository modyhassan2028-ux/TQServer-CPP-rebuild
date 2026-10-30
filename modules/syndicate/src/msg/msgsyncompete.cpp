// msgsyncompete.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsyncompete.h"
namespace syndicate {

// 0x1417db260
void* CMsgSynCompete::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dafe0 — base Create, then the single accepted message type
bool CMsgSynCompete::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

}  // namespace syndicate

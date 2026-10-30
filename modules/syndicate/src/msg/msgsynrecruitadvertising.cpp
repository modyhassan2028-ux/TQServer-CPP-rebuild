// msgsynrecruitadvertising.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynrecruitadvertising.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
namespace syndicate {

// 0x1417ddf00
void* CMsgSynRecruitAdvertising::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417ddce0 — base Create, then the single accepted message type
bool CMsgSynRecruitAdvertising::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417ddd90 — verbatim body in SyndicateMsgProcess2.cpp
void CMsgSynRecruitAdvertising::Process(void* self, uint32_t idActor) {
    MsgSynRecruitAdvertisingProcess(self, idActor);
}

}  // namespace syndicate

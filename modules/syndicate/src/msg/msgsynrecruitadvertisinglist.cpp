// msgsynrecruitadvertisinglist.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynrecruitadvertisinglist.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
namespace syndicate {

// 0x1417de1f0
void* CMsgSynRecruitAdvertisingList::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417ddfd0 — base Create, then the single accepted message type
bool CMsgSynRecruitAdvertisingList::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417de120 — verbatim body in SyndicateMsgProcess2.cpp
void CMsgSynRecruitAdvertisingList::Process(void* self, uint32_t idActor) {
    MsgSynRecruitAdvertisingListProcess(self, idActor);
}

}  // namespace syndicate

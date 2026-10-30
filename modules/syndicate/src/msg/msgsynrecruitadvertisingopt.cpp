// msgsynrecruitadvertisingopt.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynrecruitadvertisingopt.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
namespace syndicate {

// 0x1417de410
void* CMsgSynRecruitAdvertisingOpt::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417de2c0 — base Create, then the single accepted message type
bool CMsgSynRecruitAdvertisingOpt::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417de2f0 — verbatim body in SyndicateMsgProcess2.cpp
void CMsgSynRecruitAdvertisingOpt::Process(void* self, uint32_t idActor) {
    MsgSynRecruitAdvertisingOptProcess(self, idActor);
}

}  // namespace syndicate

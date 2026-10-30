// msgsyndicate.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsyndicate.h"
#include "modules/syndicate/src/SyndicateMsgSyndicate.h"
namespace syndicate {

// 0x1417dca00 — class vftable, sub-object dtor at +0x410, base vftable, delete
void* CMsgSyndicate::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    g_fn_1418230a0((unsigned char*)self + kOffSubObject);
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417db370 — base Create, then the single accepted message type
bool CMsgSyndicate::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417db7b0 — the verbatim body lives in SyndicateMsgSyndicate.cpp
void CMsgSyndicate::Process(void* self, uint32_t idActor) {
    MsgSyndicateProcess(self, idActor);
}

}  // namespace syndicate

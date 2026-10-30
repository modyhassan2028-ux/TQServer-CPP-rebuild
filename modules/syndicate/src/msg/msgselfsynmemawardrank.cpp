// msgselfsynmemawardrank.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgselfsynmemawardrank.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
namespace syndicate {

// 0x1417da810
void* CMsgSelfSynMemAwardRank::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417d9ee0 — base Create, then the single accepted message type
bool CMsgSelfSynMemAwardRank::Create(void* self, char* pData,
                                     uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417da570 — verbatim body in SyndicateMsgProcess2.cpp
void CMsgSelfSynMemAwardRank::Process(void* self, uint32_t idActor) {
    MsgSelfSynMemAwardRankProcess(self, idActor);
}

}  // namespace syndicate

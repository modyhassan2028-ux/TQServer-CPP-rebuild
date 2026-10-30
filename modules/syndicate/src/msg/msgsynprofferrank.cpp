// msgsynprofferrank.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynprofferrank.h"
namespace syndicate {

// 0x1417ddc10
void* CMsgSynProfferRank::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dda70 — base Create, then the single accepted message type
bool CMsgSynProfferRank::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417ddbb0 — the two rank bytes of the payload reach the manager
void CMsgSynProfferRank::Process(void* self, uint32_t idActor) {
    void* pMgr = g_pfnGetSyndicateMgr();
    if (!g_fn_1417ac6f0(pMgr, idActor)) return;
    unsigned char* pPayload =
        *reinterpret_cast<unsigned char**>((unsigned char*)self + kOffPayload);
    g_fn_1417ae720(pMgr, idActor, pPayload[kOffRankA], pPayload[kOffRankB]);
}

}  // namespace syndicate

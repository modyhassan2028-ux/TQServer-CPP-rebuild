// msgsynproffer.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynproffer.h"
namespace syndicate {

// 0x1417dd9a0
void* CMsgSynProffer::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dd760 — base Create, then the single accepted message type
bool CMsgSynProffer::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417dd960 — online-check, then the manager's virtual at +0x28
void CMsgSynProffer::Process(void* self, uint32_t idActor) {
    (void)self;
    void* pMgr = g_pfnGetSyndicateMgr();
    if (!g_fn_1417ac6f0(pMgr, idActor)) return;
    g_pfnMgrVf28(pMgr, idActor);
}

}  // namespace syndicate

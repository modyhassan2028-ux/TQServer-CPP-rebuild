// msgsyndomain.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsyndomain.h"
namespace syndicate {

// 0x1417dcff0 — class vftable, sub-object dtor at +0x410, base vftable, delete
void* CMsgSynDomain::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    g_fn_1418230a0((unsigned char*)self + kOffSubObject);
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dcb30
bool CMsgSynDomain::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417dcf90
void CMsgSynDomain::Process(void* self, uint32_t idActor) {
    void* pMgr = g_pfnGetSyndicateMgr();
    if (!g_fn_1417ac6f0(pMgr, idActor)) return;
    unsigned char* pPayload =
        *reinterpret_cast<unsigned char**>((unsigned char*)self + kOffPayload);
    if (*reinterpret_cast<uint16_t*>(pPayload + 4) != 0) return;
    g_fn_1417ae790(pMgr, idActor, *reinterpret_cast<uint32_t*>(pPayload + 8));
}

}  // namespace syndicate

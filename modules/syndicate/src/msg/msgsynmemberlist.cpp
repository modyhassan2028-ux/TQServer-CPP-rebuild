// msgsynmemberlist.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynmemberlist.h"
namespace syndicate {

// 0x1417dd690
void* CMsgSynMemberList::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dd2b0 — base Create, then the single accepted message type
bool CMsgSynMemberList::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417dd610
void CMsgSynMemberList::Process(void* self, uint32_t idActor) {
    void* pMgr = g_pfnGetSyndicateMgr();
    if (!g_fn_1417ac6f0(pMgr, idActor)) return;
    unsigned char* pPayload =
        *reinterpret_cast<unsigned char**>((unsigned char*)self + kOffPayload);
    unsigned int uAction = *reinterpret_cast<uint16_t*>(pPayload + 4);
    if (uAction != 0) {
        g_fn_141823030(kInvalidActionFmt, uAction);
        return;
    }
    g_fn_1417ae640(pMgr, idActor, *reinterpret_cast<uint32_t*>(pPayload + 8));
}

}  // namespace syndicate

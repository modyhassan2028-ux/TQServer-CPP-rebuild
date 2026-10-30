// msgsynchgdomname.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynchgdomname.h"
namespace syndicate {

// 0x14177e460
void* CMsgSynChgDomName::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dae60 — base Create, then the single accepted message type
bool CMsgSynChgDomName::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417dae90 — the file-local reply builder. The original hands the 64-bit
// register straight to 0x1417e8016 (a small flag here, a string elsewhere),
// so the seam receives it in its raw argument slot.
bool CMsgSynChgDomName::BuildReply(void* self, uint16_t uFlag) {
    g_fn_1417e8016(self, reinterpret_cast<const void*>(
                               static_cast<uintptr_t>(uFlag)), 0, 0);
    unsigned char* pPayload =
        *reinterpret_cast<unsigned char**>((unsigned char*)self + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPayload + kOffReplyFlag) = uFlag;
    pPayload = *reinterpret_cast<unsigned char**>((unsigned char*)self
                                                 + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPayload + kOffReplyId) = kMsgType;
    pPayload = *reinterpret_cast<unsigned char**>((unsigned char*)self
                                                 + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPayload + kOffReplyCmd) = kReplyCmd;
    return true;
}

// 0x1417daee0
void CMsgSynChgDomName::Process(void* self, uint32_t idActor) {
    void* pMgr = g_pfnGetSyndicateMgr();
    unsigned char* pPayload =
        *reinterpret_cast<unsigned char**>((unsigned char*)self + kOffPayload);
    bool bOk = g_fn_1417afb20(pMgr, idActor,
                              *reinterpret_cast<uint32_t*>(pPayload + 4),
                              pPayload + 8);
    BuildReply(self, bOk ? 1 : 0);
    g_fn_1417ac7d0(pMgr, idActor, self);
}

}  // namespace syndicate

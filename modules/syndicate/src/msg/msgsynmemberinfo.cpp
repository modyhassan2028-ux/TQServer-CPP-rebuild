// CMsgSynMemberInfo.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynmemberinfo.h"
#include <cstring>
namespace syndicate {

void (*g_fn_1417ae9b0)(void*, uint32_t) = nullptr;

// 0x1417dd1e0 — class vftable, then the tq::CMsg base, then delete when bit 0
void* CMsgSynMemberInfo::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417dd0d0 — base Create, then the single accepted message type
bool CMsgSynMemberInfo::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417dd1c0 — the manager lookup then the tail call
void CMsgSynMemberInfo::Process(void* self, uint32_t idActor) {
    (void)self;
    void* pMgr = g_pfnGetSyndicateMgr();
    g_fn_1417ae9b0(pMgr, idActor);
}

// 0x1417dd100 — the sender: CHECKF on a NULL name, then the payload
bool CMsgSynMemberInfo::Send(void* self, const char* pszName,
                             uint32_t uA, uint32_t uB) {
    unsigned char* p = (unsigned char*)self;
    if (pszName == nullptr) {
        g_fn_141823030(kAssertFmt, kAssertExpr, kAssertFunc, kAssertFile,
                       kAssertLine);
        return false;
    }
    g_fn_1417e8016(self, pszName, uA, uB);
    unsigned char* pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    g_fn_141823098(pPay + 0x0c, pszName);
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    std::memcpy(pPay + 0x08, &uA, sizeof(uint32_t));
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    std::memcpy(pPay + 0x04, &uB, sizeof(uint32_t));
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPay + 0x02) = kMsgType;
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPay + 0x00) = kKind;
    return true;
}

// 0x14177e2f0
void CMsgSynMemberInfo::BaseProcessActorInfo(void*, uint32_t, void*) {
    g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error");
}
// 0x14177e2d0
void CMsgSynMemberInfo::BaseProcessInfo(void*, void*) {
    g_pfnInlineLogError("tq::CMsg::Process(void* pInfo) error");
}

}  // namespace syndicate

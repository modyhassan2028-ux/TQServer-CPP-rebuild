// CMsgInvadeWarning.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msginvadewarning.h"
#include <cstring>
namespace syndicate {


// 0x1417d52f0 — class vftable, then the tq::CMsg base, then delete when bit 0
void* CMsgInvadeWarning::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417d5170 — base Create, then the single accepted message type
bool CMsgInvadeWarning::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417d51a0 — the sender that builds the payload
bool CMsgInvadeWarning::Send(void* self, uint32_t uA, uint32_t uB, uint32_t uC,
                             const char* pszName) {
    unsigned char* p = (unsigned char*)self;
    g_fn_1417e8016(self, nullptr, uA, uB);
    unsigned char* pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPay + 0x02) = kMsgType;
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPay + 0x00) = kKind;
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    *reinterpret_cast<uint16_t*>(pPay + 0x04) = 0;
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    std::memcpy(pPay + 0x06, &uA, sizeof(uint32_t));
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    std::memcpy(pPay + 0x0a, &uB, sizeof(uint32_t));
    pPay = *reinterpret_cast<unsigned char**>(p + kOffPayload);
    std::memcpy(pPay + 0x0e, &uC, sizeof(uint32_t));
    g_fn_141823098(
        *reinterpret_cast<char**>(p + kOffPayload) + 0x12, pszName);
    return true;
}

// 0x14177e2f0
void CMsgInvadeWarning::BaseProcessActorInfo(void*, uint32_t, void*) {
    g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error");
}
// 0x14177e2e0
void CMsgInvadeWarning::BaseProcessActor(void*, uint32_t) {
    g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor) error");
}
// 0x14177e2d0
void CMsgInvadeWarning::BaseProcessInfo(void*, void*) {
    g_pfnInlineLogError("tq::CMsg::Process(void* pInfo) error");
}

}  // namespace syndicate

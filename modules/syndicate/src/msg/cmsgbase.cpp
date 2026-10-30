// CMsgBase.cpp — RAW Syndicate.dll v6159 · tq::CMsg
#include "modules/syndicate/src/msg/cmsgbase.h"
namespace syndicate {

// 0x14177e300 — the base vftable, then delete when bit 0 is set
void* CMsgBase::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417e7fda — a pure import thunk into IAT 0x141823000
bool CMsgBase::Create(void* self, char* pData, uint16_t uType) {
    return g_pfnCMsgCreate(self, pData, uType);
}

// 0x14177e2f0
void CMsgBase::ProcessActorInfo(void*, uint32_t, void*) {
    g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error");
}
// 0x14177e2e0
void CMsgBase::ProcessActor(void*, uint32_t) {
    g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor) error");
}
// 0x14177e2d0
void CMsgBase::ProcessInfo(void*, void*) {
    g_pfnInlineLogError("tq::CMsg::Process(void* pInfo) error");
}

}  // namespace syndicate

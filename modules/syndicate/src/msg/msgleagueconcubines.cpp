// ============================================================================
// CMsgLeagueConcubines.cpp — ported from 0x1417d5c60 (verbatim)
#include "modules/syndicate/src/msg/msgleagueconcubines.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueConcubinesBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueConcubinesDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueConcubinesLogError)(const char* text) = nullptr;
void (*g_pfnCMsgLeagueConcubinesMemDtor)(void* self, uint64_t flags,
                uint64_t a3, uint64_t a4) = nullptr;

// 0x1417d5c60: class vtable, the member PB destructor, the base vftable,
// then delete on flag bit 0.
void* CMsgLeagueConcubines::Destruct(uint64_t flags, uint64_t a3, uint64_t a4) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    if (g_pfnCMsgLeagueConcubinesMemDtor != nullptr)
        g_pfnCMsgLeagueConcubinesMemDtor(reinterpret_cast<char*>(this) + kMemberOff,
                flags, a3, a4);
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flags & 1u) != 0) {
        if (g_pfnCMsgLeagueConcubinesDelete != nullptr) g_pfnCMsgLeagueConcubinesDelete(this);
    }
    return this;
}

// slot 1 (1417e7fda): the shared base create, verbatim.
bool CMsgLeagueConcubines::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueConcubinesBaseCreate == nullptr) return false;
    return g_pfnCMsgLeagueConcubinesBaseCreate(self, buf, len);
}

void CMsgLeagueConcubines::ProcessActorInfoError() { if (g_pfnCMsgLeagueConcubinesLogError) g_pfnCMsgLeagueConcubinesLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueConcubines::ProcessActorError()     { if (g_pfnCMsgLeagueConcubinesLogError) g_pfnCMsgLeagueConcubinesLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueConcubines::ProcessInfoError()      { if (g_pfnCMsgLeagueConcubinesLogError) g_pfnCMsgLeagueConcubinesLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

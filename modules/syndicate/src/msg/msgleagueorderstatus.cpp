// ============================================================================
// CMsgLeagueOrderStatus.cpp — ported from 0x1417d7550 (verbatim)
#include "modules/syndicate/src/msg/msgleagueorderstatus.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueOrderStatusBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueOrderStatusDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueOrderStatusLogError)(const char* text) = nullptr;
void (*g_pfnCMsgLeagueOrderStatusMemDtor)(void* self, uint64_t flags,
                uint64_t a3, uint64_t a4) = nullptr;

// 0x1417d7550: class vtable, the member PB destructor, the base vftable,
// then delete on flag bit 0.
void* CMsgLeagueOrderStatus::Destruct(uint64_t flags, uint64_t a3, uint64_t a4) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    if (g_pfnCMsgLeagueOrderStatusMemDtor != nullptr)
        g_pfnCMsgLeagueOrderStatusMemDtor(reinterpret_cast<char*>(this) + kMemberOff,
                flags, a3, a4);
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flags & 1u) != 0) {
        if (g_pfnCMsgLeagueOrderStatusDelete != nullptr) g_pfnCMsgLeagueOrderStatusDelete(this);
    }
    return this;
}

// slot 1 (1417e7fda): the shared base create, verbatim.
bool CMsgLeagueOrderStatus::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueOrderStatusBaseCreate == nullptr) return false;
    return g_pfnCMsgLeagueOrderStatusBaseCreate(self, buf, len);
}

void CMsgLeagueOrderStatus::ProcessActorInfoError() { if (g_pfnCMsgLeagueOrderStatusLogError) g_pfnCMsgLeagueOrderStatusLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueOrderStatus::ProcessActorError()     { if (g_pfnCMsgLeagueOrderStatusLogError) g_pfnCMsgLeagueOrderStatusLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueOrderStatus::ProcessInfoError()      { if (g_pfnCMsgLeagueOrderStatusLogError) g_pfnCMsgLeagueOrderStatusLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

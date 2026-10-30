// ============================================================================
// CMsgLeagueRobList.cpp — ported from 0x1417d8050 (verbatim)
#include "modules/syndicate/src/msg/msgleagueroblist.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueRobListBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueRobListDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueRobListLogError)(const char* text) = nullptr;
void (*g_pfnCMsgLeagueRobListMemDtor)(void* self, uint64_t flags,
                uint64_t a3, uint64_t a4) = nullptr;

// 0x1417d8050: class vtable, the member PB destructor, the base vftable,
// then delete on flag bit 0.
void* CMsgLeagueRobList::Destruct(uint64_t flags, uint64_t a3, uint64_t a4) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    if (g_pfnCMsgLeagueRobListMemDtor != nullptr)
        g_pfnCMsgLeagueRobListMemDtor(reinterpret_cast<char*>(this) + kMemberOff,
                flags, a3, a4);
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flags & 1u) != 0) {
        if (g_pfnCMsgLeagueRobListDelete != nullptr) g_pfnCMsgLeagueRobListDelete(this);
    }
    return this;
}

// slot 1 (1417e7fda): the shared base create, verbatim.
bool CMsgLeagueRobList::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueRobListBaseCreate == nullptr) return false;
    return g_pfnCMsgLeagueRobListBaseCreate(self, buf, len);
}

void CMsgLeagueRobList::ProcessActorInfoError() { if (g_pfnCMsgLeagueRobListLogError) g_pfnCMsgLeagueRobListLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueRobList::ProcessActorError()     { if (g_pfnCMsgLeagueRobListLogError) g_pfnCMsgLeagueRobListLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueRobList::ProcessInfoError()      { if (g_pfnCMsgLeagueRobListLogError) g_pfnCMsgLeagueRobListLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

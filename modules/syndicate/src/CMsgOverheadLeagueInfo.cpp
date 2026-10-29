// ============================================================================
// CMsgOverheadLeagueInfo.cpp — ported from 0x1417d99a0 (verbatim)
#include "CMsgOverheadLeagueInfo.h"

namespace syndicate {

bool (*g_pfnCMsgOverheadLeagueInfoBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgOverheadLeagueInfoDelete)(void* p) = nullptr;
void (*g_pfnCMsgOverheadLeagueInfoLogError)(const char* text) = nullptr;
void (*g_pfnCMsgOverheadLeagueInfoMemDtor)(void* self, uint64_t flags,
                uint64_t a3, uint64_t a4) = nullptr;

// 0x1417d99a0: class vtable, the member PB destructor, the base vftable,
// then delete on flag bit 0.
void* CMsgOverheadLeagueInfo::Destruct(uint64_t flags, uint64_t a3, uint64_t a4) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    if (g_pfnCMsgOverheadLeagueInfoMemDtor != nullptr)
        g_pfnCMsgOverheadLeagueInfoMemDtor(reinterpret_cast<char*>(this) + kMemberOff,
                flags, a3, a4);
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flags & 1u) != 0) {
        if (g_pfnCMsgOverheadLeagueInfoDelete != nullptr) g_pfnCMsgOverheadLeagueInfoDelete(this);
    }
    return this;
}

// slot 1 (1417e7fda): the shared base create, verbatim.
bool CMsgOverheadLeagueInfo::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgOverheadLeagueInfoBaseCreate == nullptr) return false;
    return g_pfnCMsgOverheadLeagueInfoBaseCreate(self, buf, len);
}

void CMsgOverheadLeagueInfo::ProcessActorInfoError() { if (g_pfnCMsgOverheadLeagueInfoLogError) g_pfnCMsgOverheadLeagueInfoLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgOverheadLeagueInfo::ProcessActorError()     { if (g_pfnCMsgOverheadLeagueInfoLogError) g_pfnCMsgOverheadLeagueInfoLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgOverheadLeagueInfo::ProcessInfoError()      { if (g_pfnCMsgOverheadLeagueInfoLogError) g_pfnCMsgOverheadLeagueInfoLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

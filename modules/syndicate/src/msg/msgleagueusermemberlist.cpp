// ============================================================================
// CMsgLeagueUserMemberList.cpp — ported from 0x1417d96c0 and 0x1417d9490
#include "modules/syndicate/src/msg/msgleagueusermemberlist.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueUserMemberListBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueUserMemberListDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueUserMemberListLogError)(const char* text) = nullptr;

// 0x1417d96c0: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeagueUserMemberList::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeagueUserMemberListDelete) g_pfnCMsgLeagueUserMemberListDelete(this);
    }
}

// 0x1417d9490: base create, then the id gate at +0xa.
bool CMsgLeagueUserMemberList::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueUserMemberListBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeagueUserMemberListBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeagueUserMemberList::ProcessActorInfoError() { if (g_pfnCMsgLeagueUserMemberListLogError) g_pfnCMsgLeagueUserMemberListLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueUserMemberList::ProcessActorError()     { if (g_pfnCMsgLeagueUserMemberListLogError) g_pfnCMsgLeagueUserMemberListLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueUserMemberList::ProcessInfoError()      { if (g_pfnCMsgLeagueUserMemberListLogError) g_pfnCMsgLeagueUserMemberListLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

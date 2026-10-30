// ============================================================================
// CMsgLeagueImperialCourtList.cpp — ported from 0x1417d60c0 and 0x1417d5ed0
#include "modules/syndicate/src/msg/msgleagueimperialcourtlist.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueImperialCourtListBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueImperialCourtListDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueImperialCourtListLogError)(const char* text) = nullptr;

// 0x1417d60c0: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeagueImperialCourtList::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeagueImperialCourtListDelete) g_pfnCMsgLeagueImperialCourtListDelete(this);
    }
}

// 0x1417d5ed0: base create, then the id gate at +0xa.
bool CMsgLeagueImperialCourtList::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueImperialCourtListBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeagueImperialCourtListBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeagueImperialCourtList::ProcessActorInfoError() { if (g_pfnCMsgLeagueImperialCourtListLogError) g_pfnCMsgLeagueImperialCourtListLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueImperialCourtList::ProcessActorError()     { if (g_pfnCMsgLeagueImperialCourtListLogError) g_pfnCMsgLeagueImperialCourtListLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueImperialCourtList::ProcessInfoError()      { if (g_pfnCMsgLeagueImperialCourtListLogError) g_pfnCMsgLeagueImperialCourtListLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

// ============================================================================
// CMsgLeagueList.cpp — ported from 0x1417d65f0 and 0x1417d63e0
#include "modules/syndicate/src/msg/msgleaguelist.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueListBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueListDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueListLogError)(const char* text) = nullptr;

// 0x1417d65f0: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeagueList::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeagueListDelete) g_pfnCMsgLeagueListDelete(this);
    }
}

// 0x1417d63e0: base create, then the id gate at +0xa.
bool CMsgLeagueList::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueListBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeagueListBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeagueList::ProcessActorInfoError() { if (g_pfnCMsgLeagueListLogError) g_pfnCMsgLeagueListLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueList::ProcessActorError()     { if (g_pfnCMsgLeagueListLogError) g_pfnCMsgLeagueListLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueList::ProcessInfoError()      { if (g_pfnCMsgLeagueListLogError) g_pfnCMsgLeagueListLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

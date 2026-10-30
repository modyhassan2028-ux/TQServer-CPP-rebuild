// ============================================================================
// CMsgLeagueRank.cpp — ported from 0x1417d7ce0 and 0x1417d7b30
#include "modules/syndicate/src/msg/msgleaguerank.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueRankBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueRankDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueRankLogError)(const char* text) = nullptr;

// 0x1417d7ce0: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeagueRank::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeagueRankDelete) g_pfnCMsgLeagueRankDelete(this);
    }
}

// 0x1417d7b30: base create, then the id gate at +0xa.
bool CMsgLeagueRank::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueRankBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeagueRankBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeagueRank::ProcessActorInfoError() { if (g_pfnCMsgLeagueRankLogError) g_pfnCMsgLeagueRankLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueRank::ProcessActorError()     { if (g_pfnCMsgLeagueRankLogError) g_pfnCMsgLeagueRankLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueRank::ProcessInfoError()      { if (g_pfnCMsgLeagueRankLogError) g_pfnCMsgLeagueRankLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

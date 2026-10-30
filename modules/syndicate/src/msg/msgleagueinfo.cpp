// ============================================================================
// CMsgLeagueInfo.cpp — ported from 0x1417d6310 and 0x1417d6190
#include "modules/syndicate/src/msg/msgleagueinfo.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueInfoBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueInfoDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueInfoLogError)(const char* text) = nullptr;

// 0x1417d6310: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeagueInfo::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeagueInfoDelete) g_pfnCMsgLeagueInfoDelete(this);
    }
}

// 0x1417d6190: base create, then the id gate at +0xa.
bool CMsgLeagueInfo::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueInfoBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeagueInfoBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeagueInfo::ProcessActorInfoError() { if (g_pfnCMsgLeagueInfoLogError) g_pfnCMsgLeagueInfoLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueInfo::ProcessActorError()     { if (g_pfnCMsgLeagueInfoLogError) g_pfnCMsgLeagueInfoLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueInfo::ProcessInfoError()      { if (g_pfnCMsgLeagueInfoLogError) g_pfnCMsgLeagueInfoLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

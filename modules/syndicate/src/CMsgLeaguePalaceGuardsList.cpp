// ============================================================================
// CMsgLeaguePalaceGuardsList.cpp — ported from 0x1417d7a60 and 0x1417d7880
#include "CMsgLeaguePalaceGuardsList.h"

namespace syndicate {

bool (*g_pfnCMsgLeaguePalaceGuardsListBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeaguePalaceGuardsListDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeaguePalaceGuardsListLogError)(const char* text) = nullptr;

// 0x1417d7a60: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeaguePalaceGuardsList::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeaguePalaceGuardsListDelete) g_pfnCMsgLeaguePalaceGuardsListDelete(this);
    }
}

// 0x1417d7880: base create, then the id gate at +0xa.
bool CMsgLeaguePalaceGuardsList::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeaguePalaceGuardsListBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeaguePalaceGuardsListBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeaguePalaceGuardsList::ProcessActorInfoError() { if (g_pfnCMsgLeaguePalaceGuardsListLogError) g_pfnCMsgLeaguePalaceGuardsListLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeaguePalaceGuardsList::ProcessActorError()     { if (g_pfnCMsgLeaguePalaceGuardsListLogError) g_pfnCMsgLeaguePalaceGuardsListLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeaguePalaceGuardsList::ProcessInfoError()      { if (g_pfnCMsgLeaguePalaceGuardsListLogError) g_pfnCMsgLeaguePalaceGuardsListLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

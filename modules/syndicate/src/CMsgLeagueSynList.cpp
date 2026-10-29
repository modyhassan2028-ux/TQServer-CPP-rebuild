// ============================================================================
// CMsgLeagueSynList.cpp — ported from 0x1417d8e80 and 0x1417d8ca0
#include "CMsgLeagueSynList.h"

namespace syndicate {

bool (*g_pfnCMsgLeagueSynListBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgLeagueSynListDelete)(void* p) = nullptr;
void (*g_pfnCMsgLeagueSynListLogError)(const char* text) = nullptr;

// 0x1417d8e80: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgLeagueSynList::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgLeagueSynListDelete) g_pfnCMsgLeagueSynListDelete(this);
    }
}

// 0x1417d8ca0: base create, then the id gate at +0xa.
bool CMsgLeagueSynList::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgLeagueSynListBaseCreate == nullptr) return false;
    if (!g_pfnCMsgLeagueSynListBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgLeagueSynList::ProcessActorInfoError() { if (g_pfnCMsgLeagueSynListLogError) g_pfnCMsgLeagueSynListLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgLeagueSynList::ProcessActorError()     { if (g_pfnCMsgLeagueSynListLogError) g_pfnCMsgLeagueSynListLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgLeagueSynList::ProcessInfoError()      { if (g_pfnCMsgLeagueSynListLogError) g_pfnCMsgLeagueSynListLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

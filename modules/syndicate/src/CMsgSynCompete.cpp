// ============================================================================
// CMsgSynCompete.cpp — ported from 0x1417db260 and 0x1417dafe0
#include "CMsgSynCompete.h"

namespace syndicate {

bool (*g_pfnCMsgSynCompeteBaseCreate)(void* self, const char* buf, uint16_t len) = nullptr;
void (*g_pfnCMsgSynCompeteDelete)(void* p) = nullptr;
void (*g_pfnCMsgSynCompeteLogError)(const char* text) = nullptr;

// 0x1417db260: store the class vtable, store the base vtable, then delete on flag bit 0.
void CMsgSynCompete::Destruct(unsigned char flag) {
    *reinterpret_cast<uintptr_t*>(this) = kClassVft;
    *reinterpret_cast<uintptr_t*>(this) = kBaseVft;
    if ((flag & 1u) != 0) {
        if (g_pfnCMsgSynCompeteDelete) g_pfnCMsgSynCompeteDelete(this);
    }
}

// 0x1417dafe0: base create, then the id gate at +0xa.
bool CMsgSynCompete::Create(void* self, const char* buf, uint16_t len) {
    if (g_pfnCMsgSynCompeteBaseCreate == nullptr) return false;
    if (!g_pfnCMsgSynCompeteBaseCreate(self, buf, len)) return false;
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(self) + 0x0a) == kMsgId;
}

// the three shared loggers (14177e2f0 / 14177e2e0 / 14177e2d0)
void CMsgSynCompete::ProcessActorInfoError() { if (g_pfnCMsgSynCompeteLogError) g_pfnCMsgSynCompeteLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error"); }
void CMsgSynCompete::ProcessActorError()     { if (g_pfnCMsgSynCompeteLogError) g_pfnCMsgSynCompeteLogError("tq::CMsg::Process(OBJID idActor) error"); }
void CMsgSynCompete::ProcessInfoError()      { if (g_pfnCMsgSynCompeteLogError) g_pfnCMsgSynCompeteLogError("tq::CMsg::Process(void* pInfo) error"); }

} // namespace syndicate

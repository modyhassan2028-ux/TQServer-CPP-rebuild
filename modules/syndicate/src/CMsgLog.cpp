// CMsgLog.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgLog.h"
namespace syndicate {

void* (*g_pfnGetSyndicateMgr)() = nullptr;
void (*g_pfnLogProcessA)(void*, uint32_t) = nullptr;
void (*g_pfnLogProcessB)(void*, uint32_t) = nullptr;

// 0x14177e3e0 — deleting dtor: class vftable, then the tq::CMsg base
// vftable, then operator delete (0x1417f2fdc) when bit 0 is set.
void* CMsgLog::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417d9760 — Create: the base Create, then the type gate
bool CMsgLog::Create(void* self, char* pData, uint16_t uType) {
    unsigned char* p = (unsigned char*)self;
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    uint16_t uMsgType = *reinterpret_cast<uint16_t*>(p + kOffMsgType);
    if (uMsgType == kTypeA) {
        *reinterpret_cast<int32_t*>(
            *reinterpret_cast<void**>(p + kOffPayload) + 8) = 0;
        return true;
    }
    if (uMsgType == kTypeB) {
        *reinterpret_cast<int32_t*>(
            *reinterpret_cast<void**>(p + kOffPayload) + 8) = 1;
        return true;
    }
    return false;
}

// 0x1417d97c0 — Process(idActor)
void CMsgLog::Process(void* self, uint32_t idActor) {
    unsigned char* p = (unsigned char*)self;
    void* pMgr = g_pfnGetSyndicateMgr();
    int32_t nType = *reinterpret_cast<int32_t*>(
        *reinterpret_cast<void**>(p + kOffPayload) + 8);
    if (nType == 0) {
        g_pfnLogProcessA(pMgr, idActor);
    } else if (nType == 1) {
        g_pfnLogProcessB(pMgr, idActor);
    } else {
        g_pfnInlineLogError(
            "syndicate::CMsgLog::Process(idActor), idActor:%d, Type:%d, "
            "MsgType:%d", idActor, nType,
            (int)*reinterpret_cast<uint16_t*>(p + kOffMsgType));
    }
}

// 0x14177e2f0 — the base slot 2 stub
void CMsgLog::BaseProcessActor(void* self, uint32_t idActor, void* pInfo) {
    (void)self; (void)idActor; (void)pInfo;
    g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor, void* pInfo) error");
}

// 0x14177e2d0 — the base slot 4 stub
void CMsgLog::BaseProcessInfo(void* self, void* pInfo) {
    (void)self; (void)pInfo;
    g_pfnInlineLogError("tq::CMsg::Process(void* pInfo) error");
}

}  // namespace syndicate

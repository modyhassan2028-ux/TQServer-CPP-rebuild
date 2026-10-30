// msgsynattrinfo.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgsynattrinfo.h"
namespace syndicate {

// 0x1417dabe0 — class vftable, base vftable, delete on bit 0
void* CMsgSynAttrInfo::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    *reinterpret_cast<uintptr_t*>(self) = kBaseCMsgVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417da8e0 — base Create, then the single accepted message type
bool CMsgSynAttrInfo::Create(void* self, char* pData, uint16_t uType) {
    if (!g_pfnCMsgCreate(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + kOffMsgType)
           == kMsgType;
}

// 0x1417daba0 — unreachable in the original: it reports and returns
void CMsgSynAttrInfo::Process(void* self, uint32_t idActor) {
    (void)self; (void)idActor;
    g_fn_141823030(kAssertFmt, kAssertExpr, kAssertFunc, kAssertFile,
                   kAssertLine);
}

}  // namespace syndicate

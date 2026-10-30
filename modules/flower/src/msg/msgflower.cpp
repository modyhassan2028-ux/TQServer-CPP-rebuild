// msgflower.cpp — RAW Flower.dll v6159
#include "modules/flower/src/msg/msgflower.h"

namespace flower {

// 0x140d97cb0 — the two-step Init chain, then payload = this + 8
void* CMsgFlower::Ctor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kBaseVft;
    syndicate::CMsgBase::Init(self);
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    syndicate::CMsgBase::Init(self);
    *reinterpret_cast<void**>(p + kOffPayloadPtr) = p + 8;
    return self;
}

// 0x140d97fc0 — the derived vftable back to the base one, then delete
void* CMsgFlower::DeleteDtor(void* self, uint32_t uFlag) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    *reinterpret_cast<uintptr_t*>(p) = kBaseVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x140d97ec0 — the base parse, then the type gate
bool CMsgFlower::Create(void* self, char* pData, uint16_t uType) {
    if (!syndicate::CMsgBase::Create(self, pData, uType)) return false;
    return *reinterpret_cast<uint16_t*>((unsigned char*)self + 0x0a) ==
           kMsgType;
}

// 0x140d97ef0 — dispatch on the packed sub-type at payload + 4
void CMsgFlower::Process(void* self, void* pActor, void* pInfo) {
    if (pInfo == nullptr) {
        syndicate::g_pfnInlineLogError(
            "\xA1\xEF%s(%s)\xA1\xEF in %s");   // 0x140d9b368
        return;
    }
    unsigned char* pPayload = *reinterpret_cast<unsigned char**>(
        (unsigned char*)self + kOffPayloadPtr);
    int16_t sVar1 = *reinterpret_cast<int16_t*>(pPayload + 4);
    void** vt = *reinterpret_cast<void***>(pActor);
    if (sVar1 == 2) {
        ((void (*)(void*))vt[4])(pActor);                      // +0x20
    } else if (sVar1 == 3) {
        ((void (*)(void*))vt[5])(pActor);                      // +0x28
    } else if (sVar1 == 0) {
        if (*reinterpret_cast<int32_t*>(pPayload + 8) != 0) {
            ((void (*)(void*, void*, uint32_t, uint32_t))vt[6])(
                pActor, pInfo,
                *reinterpret_cast<uint32_t*>(pPayload + 8),
                *reinterpret_cast<uint32_t*>(pPayload + 0x0c));
        }
    } else if (sVar1 == 1) {
        if (*reinterpret_cast<int32_t*>(pPayload + 8) != 0) {
            ((void (*)(void*, void*, uint32_t, uint32_t))vt[7])(
                pActor, pInfo,
                *reinterpret_cast<uint32_t*>(pPayload + 8),
                *reinterpret_cast<uint32_t*>(pPayload + 0x0c));
        }
    }
}

// 0x140d97c60 — "tq::CMsg::Process(OBJID idActor) error"
void CMsgFlower::ProcessActor(void* self, uint32_t idActor) {
    (void)self; (void)idActor;
    syndicate::g_pfnInlineLogError("tq::CMsg::Process(OBJID idActor) error");
}

// 0x140d97c50 — "tq::CMsg::Process(void* pInfo) error"
void CMsgFlower::ProcessInfo(void* self, void* pInfo) {
    (void)self; (void)pInfo;
    syndicate::g_pfnInlineLogError("tq::CMsg::Process(void* pInfo) error");
}

// 0x140d97d00 — the member dtor: class vftable back to the base one
void CMsgFlower::BaseDtor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    *reinterpret_cast<uintptr_t*>(p) = kBaseVft;
}

// 0x140d97d30 — writes straight through the payload pointer, both names are
// zero-padded to 16 bytes before the strncpy, exactly as the original does
bool CMsgFlower::Build(void* self, uint16_t uChild, const char* pSender,
                       const char* pReceiver, uint32_t uValue, uint32_t uSlot,
                       uint8_t uFlag) {
    if (pSender == nullptr || pReceiver == nullptr) return false;
    unsigned char* pay = *reinterpret_cast<unsigned char**>(
        (unsigned char*)self + kOffPayloadPtr);
    *reinterpret_cast<uint16_t*>(pay + 4) = uChild;
    *reinterpret_cast<uint16_t*>(pay + 2) = kMsgType;
    *reinterpret_cast<uint16_t*>(pay + 0) = 0x3c;
    *reinterpret_cast<uint64_t*>(pay + 0x10) = 0;
    *reinterpret_cast<uint64_t*>(pay + 0x18) = 0;
    ::strncpy((char*)(pay + 0x10), pSender, 0x10);
    *reinterpret_cast<uint64_t*>(pay + 0x20) = 0;
    *reinterpret_cast<uint64_t*>(pay + 0x28) = 0;
    ::strncpy((char*)(pay + 0x20), pReceiver, 0x10);
    *reinterpret_cast<uint32_t*>(pay + 0x30) = uValue;
    *reinterpret_cast<uint32_t*>(pay + 0x34) = uSlot;
    *reinterpret_cast<uint8_t*>(pay + 0x38) = uFlag;
    return true;
}

}  // namespace flower

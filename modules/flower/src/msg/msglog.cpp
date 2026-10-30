// msglog.cpp — RAW Flower.dll v6159
#include "modules/flower/src/msg/msglog.h"

namespace flower {

// 0x140d98010
void* CMsgLog::Ctor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kBaseVft;
    syndicate::CMsgBase::Init(self);
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    syndicate::CMsgBase::Init(self);
    *reinterpret_cast<void**>(p + kOffPayloadPtr) = p + 8;
    return self;
}

// 0x140d98170
void* CMsgLog::DeleteDtor(void* self, uint32_t uFlag) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    *reinterpret_cast<uintptr_t*>(p) = kBaseVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x140d98090 — the base parse, then the two accepted sub-types
bool CMsgLog::Create(void* self, char* pData, uint16_t uType) {
    if (!syndicate::CMsgBase::Create(self, pData, uType)) return false;
    unsigned short uSub = *reinterpret_cast<unsigned short*>(
        (unsigned char*)self + 0x0a);
    if (uSub == 0x3ea) {
        unsigned char* pPayload = *reinterpret_cast<unsigned char**>(
            (unsigned char*)self + kOffPayloadPtr);
        *reinterpret_cast<uint32_t*>(pPayload + 8) = 0;
        return true;
    }
    if (uSub == 0x3eb) {
        unsigned char* pPayload = *reinterpret_cast<unsigned char**>(
            (unsigned char*)self + kOffPayloadPtr);
        *reinterpret_cast<uint32_t*>(pPayload + 8) = 1;
        return true;
    }
    return false;
}

// 0x140d980f0
void CMsgLog::Process(void* self, void* pActor, void* pInfo) {
    if (pInfo == nullptr) {
        syndicate::g_pfnInlineLogError(
            "\xA1\xEF%s(%s)\xA1\xEF in %s");   // 0x140d9b368
        return;
    }
    int32_t iVar1 = *reinterpret_cast<int32_t*>(
        *reinterpret_cast<unsigned char**>((unsigned char*)self +
                                           kOffPayloadPtr) + 8);
    void** vt = *reinterpret_cast<void***>(pActor);
    if (iVar1 == 0) {
        ((void (*)(void*))vt[1])(pActor);       // +0x08
    } else if (iVar1 == 1) {
        ((void (*)(void*))vt[2])(pActor);       // +0x10
    }
}

}  // namespace flower

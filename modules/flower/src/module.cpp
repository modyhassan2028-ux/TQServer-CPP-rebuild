// module.cpp — RAW Flower.dll v6159
#include "modules/flower/src/module.h"
#include "modules/flower/src/flowerservice.h"

namespace flower {

void (*g_pfnPureCall)() = nullptr;

// 0x140d935b0 — base vftable, class vftable, then the two member ctors
void* CModule::Ctor(void* self, void* pKernel, uint32_t dwIndex) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = syndicate::CMsgBase::kVft;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    *reinterpret_cast<uint32_t*>(p + kOffIndex) = dwIndex;
    CMsgLog::Ctor(p + kOffLog);
    CMsgFlower::Ctor(p + kOffFlower);
    *reinterpret_cast<uint32_t*>(p + kOffZero) = 0;
    *reinterpret_cast<void**>(p + kOffKernel) = pKernel;
    *reinterpret_cast<void**>(p + kOffOwned) = nullptr;
    return self;
}

// 0x140d932f0 — release the owned object through its slot +0x58 (1, a, b, -2),
// then both message members (0x140d97d00 / 0x140d98060), then the base vftable
void CModule::Complete(void* self, uint64_t uA, void* pB, void* pC) {
    (void)uA;
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    unsigned char* pOwned = *reinterpret_cast<unsigned char**>(p + kOffOwned);
    if (pOwned != nullptr) {
        void** vt = *reinterpret_cast<void***>(pOwned);
        ((void (*)(void*, uint64_t, void*, void*, intptr_t))vt[0x58 / 8])(
            pOwned, 1, pB, pC, (intptr_t)-2);
    }
    *reinterpret_cast<uintptr_t*>(p + kOffFlower) = CMsgFlower::kClassVft;
    *reinterpret_cast<uintptr_t*>(p + kOffFlower) = CMsgFlower::kBaseVft;
    *reinterpret_cast<uintptr_t*>(p + kOffLog) = CMsgLog::kClassVft;
    *reinterpret_cast<uintptr_t*>(p + kOffLog) = CMsgLog::kBaseVft;
    *reinterpret_cast<uintptr_t*>(p) = syndicate::CMsgBase::kVft;
}

// 0x140d93290
void* CModule::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = syndicate::CMsgBase::kVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x140d93250 / 0x140d93260 / 0x140d93270 / 0x140d93280 — each `xor eax,eax`
uint64_t CModule::Slot5() { return 0; }
uint64_t CModule::Slot6() { return 0; }
uint64_t CModule::Slot7() { return 0; }
uint64_t CModule::Slot8() { return 0; }

// 0x140d982ac — the four _purecall slots
void CModule::PureCall() { g_pfnPureCall(); }

// 0x140d935a0 — answers 1 unconditionally
uint64_t CModule::Slot4() { return 1; }

// 0x140d934f0 — CModule::Initialize
//   the owned service lands at +0x420; the kernel registers this module for
//   0x47e, 0x3ea and 0x3eb through its slot +8 and attaches the service with
//   mode 9 through its slot +0x18
bool CModule::Initialize(void* self) {
    unsigned char* p = (unsigned char*)self;
    void* pOwned = CFlowerService::CreateObject();
    *reinterpret_cast<void**>(p + kOffOwned) = pOwned;
    if (pOwned == nullptr) {
        g_pfnFlowerLog(kCheckFormat);
        return false;
    }
    void* pKernel = *reinterpret_cast<void**>(p + kOffKernel);
    void** vt = *reinterpret_cast<void***>(pKernel);
    ((bool (*)(void*, uint32_t, void*))vt[8 / 8])(pKernel, 0x47e, self);
    ((bool (*)(void*, uint32_t, void*))vt[8 / 8])(pKernel, 0x3ea, self);
    ((bool (*)(void*, uint32_t, void*))vt[8 / 8])(pKernel, 0x3eb, self);
    return ((uint8_t (*)(void*, uint32_t, void*))vt[0x18 / 8])(pKernel, 9,
                                                               pOwned) != 0;
}

// 0x140d936d0 — ModuleCreate
CModule* ModuleCreate(void* pKernel, uint32_t dwIndex) {
    void* pMem = ::operator new(0x848);
    CModule* pMod = nullptr;
    if (pMem != nullptr) pMod = (CModule*)CModule::Ctor(pMem, pKernel, dwIndex);
    if (pMod != nullptr) {
        if (!CModule::Initialize(pMod)) {
            ((void (*)(void*))(*(void***)pMod)[8 / 8])(pMod);
            pMod = nullptr;
        }
    }
    return pMod;
}

}  // namespace flower
